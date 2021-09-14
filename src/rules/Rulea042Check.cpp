//===--- Rulea042Check.cpp - clang-tidy -----------------------------------===//

//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Rulea042Check.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace autosar {

void Rulea042Check::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(expr(hasType(asString("long double"))).bind("longDouble"), this);
}

void Rulea042Check::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<Expr>("longDouble");
  diag(MatchedDecl->getExprLoc(), "Unauthorized type use, type long double shall not be used");
}

} // namespace autosar
} // namespace tidy
} // namespace clang
