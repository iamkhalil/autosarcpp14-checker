//===--- Rulea1323Check.cpp - clang-tidy ----------------------------------===//
//Autosar Guidelines :Rule A13-2-3 
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include <iostream>
#include "Rulea1323Check.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace autosar {

void Rulea1323Check::registerMatchers(MatchFinder *Finder) {
  //finds all function declarations that contain relational operators and do not return values that are not of boolean type  
  Finder->addMatcher((functionDecl(allOf(anyOf(hasName("operator=="),hasName("operator!="),hasName("operator>"),hasName("operator<"),hasName("operator>="),hasName("operator<=")),unless(hasDescendant(returnStmt(hasReturnValue(hasType(booleanType())))))))).bind("operators"), this);
}

void Rulea1323Check::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<FunctionDecl>("operators");

  if (MatchedDecl->getName().startswith("operator"))
    return;
  diag(MatchedDecl->getLocation(), "Wrong return value type of a relational operator, it shall return a boolean value")
      << MatchedDecl;
}

} // namespace autosar
} // namespace tidy
} // namespace clang
