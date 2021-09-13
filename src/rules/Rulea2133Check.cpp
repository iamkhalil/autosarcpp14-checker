//===--- Rulea2133Check.cpp - clang-tidy ----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Rulea2133Check.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace autosar {
  //Create a matcher to verify if the type of the declared value is wchar_t
namespace {AST_MATCHER(ValueDecl,isWideCharType){return (((Node.getType().getUnqualifiedType().getAsString()).find("wchar_t"))==0);}}


void Rulea2133Check::registerMatchers(MatchFinder *Finder) {
  //match declared values whose type is wchar_t
  Finder->addMatcher(valueDecl(isWideCharType()).bind("widechar"), this);
}

void Rulea2133Check::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<ValueDecl>("widechar");
  diag(MatchedDecl->getLocation(), "Type wchar_t shall not be used")
      << MatchedDecl;
  diag(MatchedDecl->getLocation(), "Types char16_t and char32_t should be used instead of wchar_t", DiagnosticIDs::Note);
}

} // namespace autosar
} // namespace tidy
} // namespace clang
