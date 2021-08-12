//===--- Rulem1631Check.cpp - clang-tidy ----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Rulem1631Check.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Lex/MacroInfo.h"
#include "clang/Lex/PPCallbacks.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Lex/Token.h"

namespace clang {
namespace tidy {
namespace autosar {
namespace {

class Rulem1631PPCallbacks : public PPCallbacks {
public:
  Rulem1631PPCallbacks(ClangTidyCheck &Check, Preprocessor &PP)
      : Check(Check), PP(PP) {}

  virtual void MacroDefined(const Token &MacroNameTok,
                            const MacroDirective *MD) override;

private:
  ClangTidyCheck &Check;
  Preprocessor &PP;
};

} // namespace

void Rulem1631PPCallbacks::MacroDefined(const Token &MacroNameTok,
                                        const MacroDirective *MD) {

  (void)MacroNameTok;
  const MacroInfo *MI = MD->getMacroInfo();
  size_t nbr_hash = 0;

  for (MacroInfo::tokens_iterator it = MI->tokens_begin(),
                                  it_e = MI->tokens_end();
       it != it_e; ++it) {
    const std::string tokenType = it->getName();
    if (tokenType.find("hash") == 0) {
      if (++nbr_hash == 2) {

        Check.diag(it->getLocation(),
                   "There shall be at most one occurrence of the # or ## operators in a single macro definition.");
        Check.diag(
            it->getLocation(),
            "Operators # and ## are anyway not allowed, see M16-3-2. This rule is kept in case M16-3-2 is disabled in a project.",
            DiagnosticIDs::Note);
        break;
      }
    }
  }
}

void Rulem1631Check::registerPPCallbacks(const SourceManager &SM,
                                         Preprocessor *PP,
                                         Preprocessor *ModuleExpanderPP) {
  PP->addPPCallbacks(::std::make_unique<Rulem1631PPCallbacks>(*this, *PP));
}

} // namespace autosar
} // namespace tidy
} // namespace clang
