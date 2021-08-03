//===--- Rulem4102Check.cpp - clang-tidy ----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Rulem4102Check.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace autosar {

void Rulem4102Check::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
      integerLiteral(equals(0),
                     hasParent(expr(anyOf(hasType(pointerType()),
                                          hasType(memberPointerType())))))
          .bind("ZeroAsNullptr"),
      this);
}

void Rulem4102Check::check(const MatchFinder::MatchResult &Result) {
  const auto *matcher = Result.Nodes.getNodeAs<Stmt>("ZeroAsNullptr");
  if (matcher) {
    const auto start = matcher->getBeginLoc();
    diag(start,
         "Literal zero (0) shall not be used as the null-pointer-constant.");
  }
}

} // namespace autosar
} // namespace tidy
} // namespace clang
