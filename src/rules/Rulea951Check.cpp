//===--- Rulea951Check.cpp - clang-tidy -------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Rulea951Check.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace autosar {

void Rulea951Check::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
      recordDecl(isUnion(), hasDeclContext(translationUnitDecl()))
          .bind("union"),
      this);
}

void Rulea951Check::check(const MatchFinder::MatchResult &Result) {
  const auto *rDecl = Result.Nodes.getNodeAs<RecordDecl>("union");
  if (rDecl) {
    auto start = rDecl->getBeginLoc();
    diag(start, "Unions shall not be used.");
  }
}
} // namespace autosar
} // namespace tidy
} // namespace clang
