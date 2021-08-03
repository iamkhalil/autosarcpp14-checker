//===--- Rulea716Check.cpp - clang-tidy -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Rulea716Check.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace autosar {

void Rulea716Check::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(typedefDecl(isExpansionInMainFile()).bind("typedef"),
                     this);
}

void Rulea716Check::check(const MatchFinder::MatchResult &Result) {
  const auto *tDecl = Result.Nodes.getNodeAs<TypedefDecl>("typedef");
  if (tDecl) {
    const auto start = tDecl->getBeginLoc();
    diag(start, "The typedef specifier shall not be used.");
    diag(start, "Use the using syntax instead of typedef.",
         DiagnosticIDs::Note);
  }
}

} // namespace autosar
} // namespace tidy
} // namespace clang
