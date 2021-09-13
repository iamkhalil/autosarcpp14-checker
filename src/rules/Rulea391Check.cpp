//===--- Rulea391Check.cpp - clang-tidy -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Rulea391Check.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace autosar {

void Rulea391Check::registerMatchers(MatchFinder *Finder) {
  //find all declared values with basic numerical types 
  Finder->addMatcher(valueDecl(anyOf(hasType(asString("char")),hasType(asString("short")),hasType(asString("int")),hasType(asString("long")),hasType(asString("long long")),hasType(asString("unsigned char")),hasType(asString("unsigned short")),hasType(asString("unsigned int")),hasType(asString("unsigned long")),hasType(asString("unsigned long long")))).bind("BasicNumericalType"), this);
}

void Rulea391Check::check(const MatchFinder::MatchResult &Result) {
  //
  const auto *MatchedDecl = Result.Nodes.getNodeAs<ValueDecl>("BasicNumericalType");
  if (!MatchedDecl->getIdentifier())
    return;
  diag(MatchedDecl->getLocation(), "Use of basic numerical type, fixed width integer types from <cstdint> should be used instead.")<< MatchedDecl;}

} // namespace autosar
} // namespace tidy
} // namespace clang
