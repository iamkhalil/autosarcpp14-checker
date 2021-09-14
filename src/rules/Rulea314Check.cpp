//===--- Rulea314Check.cpp - clang-tidy -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Rulea314Check.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace autosar {

void Rulea314Check::registerMatchers(MatchFinder *Finder) {
  // FIXME: Add matchers.
  Finder->addMatcher(varDecl(allOf(hasExternalFormalLinkage(),hasType(arrayType()),unless(hasType(constantArrayType())))).bind("externalLinkageArray"), this);
}

void Rulea314Check::check(const MatchFinder::MatchResult &Result) {
  // FIXME: Add callback implementation.
  const auto *MatchedDecl = Result.Nodes.getNodeAs<VarDecl>("externalLinkageArray");
  if (!(MatchedDecl->getIdentifier()))
    return;
  diag(MatchedDecl->getLocation(), "An array with external linkage is declared, its size shall be stated explicitly.")
      << MatchedDecl;
}

} // namespace autosar
} // namespace tidy
} // namespace clang
