//===--- Rulem1805Check.cpp - clang-tidy ----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Rulem1805Check.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace autosar {

void Rulem1805Check::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
      callExpr(callee(functionDecl(anyOf(
                   hasName("strcpy"), hasName("strcmp"), hasName("strcat"),
                   hasName("strchr"), hasName("strspn"), hasName("strcspn"),
                   hasName("strpbrk"), hasName("strrchr"), hasName("strstr"),
                   hasName("strtok"), hasName("strlen")))))
          .bind("stringManipulation"),
      this);
}

void Rulem1805Check::check(const MatchFinder::MatchResult &Result) {
  const auto *callExpr = Result.Nodes.getNodeAs<CallExpr>("stringManipulation");
  if (callExpr) {
    const auto start = callExpr->getBeginLoc();
    diag(start,
         "The unbounded functions of library <cstring> shall not be used.");
  }
}

} // namespace autosar
} // namespace tidy
} // namespace clang
