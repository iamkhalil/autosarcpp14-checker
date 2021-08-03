//===--- Rulem1804Check.cpp - clang-tidy ----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Rulem1804Check.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace autosar {

void Rulem1804Check::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(callExpr(callee(functionDecl(matchesName(
                                  "^(std)?::(clock|ctime|asctime|gmtime|"
                                  "localtime|difftime|mktime|time)$"))))
                         .bind("func"),
                     this);
}

void Rulem1804Check::check(const MatchFinder::MatchResult &Result) {
  const auto *callExpr = Result.Nodes.getNodeAs<CallExpr>("func");
  if (callExpr) {
    auto start = callExpr->getBeginLoc();
    diag(start,
         "The time handling functions of library <ctime> shall not be used.");
  }
}

} // namespace autosar
} // namespace tidy
} // namespace clang
