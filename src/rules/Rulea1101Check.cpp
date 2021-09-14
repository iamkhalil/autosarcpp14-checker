//===--- Rulea1101Check.cpp - clang-tidy ----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Rulea1101Check.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace autosar {

void Rulea1101Check::registerMatchers(MatchFinder *Finder) {
  //matches all record declarations other than class
  Finder->addMatcher(cxxRecordDecl(hasDefinition(),unless(isClass())).bind("NonPodType"), this);
}

void Rulea1101Check::check(const MatchFinder::MatchResult &Result) {
  // FIXME: Add callback implementation.
  const auto *MatchedDecl = Result.Nodes.getNodeAs<CXXRecordDecl>("NonPodType");
  //verify if the matched declaration is POD or Non-POD
  if (MatchedDecl->isPOD())
    return;
  diag(MatchedDecl->getLocation(), "Use of a non-POD type in other format than a class.")<< MatchedDecl;
}

} // namespace autosar
} // namespace tidy
} // namespace clang
