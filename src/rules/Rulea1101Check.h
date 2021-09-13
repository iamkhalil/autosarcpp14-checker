//===--- Rulea1101Check.h - clang-tidy --------------------------*- C++ -*-===//
//Autosar C++14 Guidelines :Rule A11-0-1
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_AUTOSAR_RULEA1101CHECK_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_AUTOSAR_RULEA1101CHECK_H

#include "../ClangTidyCheck.h"

namespace clang {
namespace tidy {
namespace autosar {

/// Rule A11-0-1: A non-POD type should be defined as class.
///POD Type :POD (Plain Old Data) type is the type that is compatible with types used in the C programming language, can be manipulated using C library functions, and can be exchanged with C libraries directly in its binary form.
/// For the user-facing documentation see:
/// http://clang.llvm.org/extra/clang-tidy/checks/autosar-ruleA11-0-1.html
class Rulea1101Check : public ClangTidyCheck {
public:
  Rulea1101Check(StringRef Name, ClangTidyContext *Context)
      : ClangTidyCheck(Name, Context) {}
  void registerMatchers(ast_matchers::MatchFinder *Finder) override;
  void check(const ast_matchers::MatchFinder::MatchResult &Result) override;
};

} // namespace autosar
} // namespace tidy
} // namespace clang

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_AUTOSAR_RULEA1101CHECK_H
