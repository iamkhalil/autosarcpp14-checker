//===--- Rulea1671Check.cpp - clang-tidy ----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Rulea1671Check.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Lex/PPCallbacks.h"
#include "clang/Lex/Preprocessor.h"

namespace clang {
namespace tidy {
namespace autosar {
namespace {
class Rulea1671PPCallbacks : public PPCallbacks {
public:
  Rulea1671PPCallbacks(ClangTidyCheck &Check, Preprocessor &PP)
      : Check(Check), PP(PP) {}
  /// Callback invoked when start reading any pragma directive.
  virtual void PragmaDirective(SourceLocation Loc,
                               PragmaIntroducerKind Introducer) override;

private:
  ClangTidyCheck &Check;
  Preprocessor &PP;
};
} // namespace

void Rulea1671PPCallbacks::PragmaDirective(SourceLocation Loc,
                                           PragmaIntroducerKind Introducer) {
  if (Introducer == PIK_HashPragma) {
    Check.diag(Loc, "The #pragma directive shall not be used.");
  }
}

void Rulea1671Check::registerPPCallbacks(const SourceManager &SM,
                                         Preprocessor *PP,
                                         Preprocessor *ModuleExpanderPP) {
  PP->addPPCallbacks(::std::make_unique<Rulea1671PPCallbacks>(*this, *PP));
}
} // namespace autosar
} // namespace tidy
} // namespace clang
