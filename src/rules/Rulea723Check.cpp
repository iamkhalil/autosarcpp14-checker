//===--- Rulea723Check.cpp - clang-tidy -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Rulea723Check.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace autosar {

void Rulea723Check::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(enumDecl(unless(isScoped())).bind("scopedEnum"), this);
}

void Rulea723Check::check(const MatchFinder::MatchResult &Result) {
  const auto *enumDecl = Result.Nodes.getNodeAs<EnumDecl>("scopedEnum");
  if (enumDecl) {
    const auto start = enumDecl->getBeginLoc();
    diag(start, "Enumerations shall be declared as scoped enum classes.");
  }
}

} // namespace autosar
} // namespace tidy
} // namespace clang
