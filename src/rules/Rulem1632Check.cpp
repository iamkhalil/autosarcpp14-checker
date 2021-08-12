//===--- Rulem1632Check.cpp - clang-tidy ----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Rulem1632Check.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Lex/MacroInfo.h"
#include "clang/Lex/PPCallbacks.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Lex/Token.h"

namespace clang {
namespace tidy {
namespace autosar {

namespace {

class Rulem1632PPCallbacks : public PPCallbacks {
public:
  Rulem1632PPCallbacks(ClangTidyCheck &Check, Preprocessor &PP)
      : Check(Check), PP(PP) {}

  virtual void MacroDefined(const Token &MacroNameTok,
                            const MacroDirective *MD) override;

private:
  ClangTidyCheck &Check;
  Preprocessor &PP;
};
} // namespace

void Rulem1632PPCallbacks::MacroDefined(const Token &MacroNameTok,
                                        const MacroDirective *MD) {

  // (void)MacroNameTok;
  const MacroInfo *MI = MD->getMacroInfo();

  for (MacroInfo::tokens_iterator it = MI->tokens_begin(),
                                  it_e = MI->tokens_end();
       it != it_e; ++it) {
    const std::string tokenType = it->getName();
    if (tokenType.find("hash") == 0) {
      Check.diag(it->getLocation(),
                 "The # and ## operators should not be used");
      break;
    }
  }
}

void Rulem1632Check::registerPPCallbacks(const SourceManager &SM,
                                         Preprocessor *PP,
                                         Preprocessor *ModuleExpanderPP) {
  PP->addPPCallbacks(::std::make_unique<Rulem1632PPCallbacks>(*this, *PP));
}

} // namespace autosar
} // namespace tidy
} // namespace clang
