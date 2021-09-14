//===--- Rulea1241Check.cpp - clang-tidy ----------------------------------===//
//Autosar C++14 Guidelines :Rule A13-2-3
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Rulea1241Check.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace autosar {

void Rulea1241Check::registerMatchers(MatchFinder *Finder) {
  //finds all destructors which were not declared as Public&override or public&virtual or protected&non-virtual
  Finder->addMatcher(cxxDestructorDecl(unless(anyOf(allOf(isPublic(),isOverride()),allOf(isPublic(),isVirtual()),allOf(isProtected(),unless(isVirtual()))))).bind("Destructor"), this);
}

void Rulea1241Check::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<CXXDestructorDecl>("Destructor");
  if (!MatchedDecl->getCanonicalDecl())
    return ;
  diag(MatchedDecl->getLocation(), "Destructor of a base class type is incorrect, it shall be public virtual, public override or protected non-virtual.")
      << MatchedDecl;
}

} // namespace autosar
} // namespace tidy
} // namespace clang
