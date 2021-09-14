//===--- Rulem1101Check.cpp - clang-tidy ----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Rulem1101Check.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace autosar {
void Rulem1101Check::registerMatchers(MatchFinder *Finder) {
  //Match class members which were declared as Public or Protected 
  Finder->addMatcher(cxxRecordDecl(hasDefinition(),isClass(),has(accessSpecDecl(anyOf(isPublic(), isProtected())))).bind("PrivateClassMember"),this);
}

void Rulem1101Check::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<CXXRecordDecl>("PrivateClassMember");
  //verify if the matched node have POD Type or not.
  if (MatchedDecl->isPOD())
    return;
  diag(MatchedDecl->getLocation(),"Member data in non-POD class types shall be private")<<MatchedDecl;







  
}

} // namespace autosar
} // namespace tidy
} // namespace clang
