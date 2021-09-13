//===--- Rulea391Check.h - clang-tidy ---------------------------*- C++ -*-===//
//Autosar C++14 Guidelines :Rule A3-9-1
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_AUTOSAR_RULEA391CHECK_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_AUTOSAR_RULEA391CHECK_H

#include "../ClangTidyCheck.h"

namespace clang {
namespace tidy {
namespace autosar {

/// Rule A3-9-1: Fixed width integer types from <cstdint>, indicating the size and
//signedness, shall be used in place of the basic numerical types.


///The basic numerical types of char, int, short, long are not supposed to be used,
//specific-length types from <cstdint> header need be used instead.
//Fixed width integer types are: std::int8_t, std::int16_t, std::int32_t, std::int64_t
//std::uint8_t, std::uint16_t, std::uint32_t, std::uint64_t
/// For the user-facing documentation see:
/// http://clang.llvm.org/extra/clang-tidy/checks/autosar-ruleA3-9-1.html
class Rulea391Check : public ClangTidyCheck {
public:
  Rulea391Check(StringRef Name, ClangTidyContext *Context)
      : ClangTidyCheck(Name, Context) {}
  void registerMatchers(ast_matchers::MatchFinder *Finder) override;
  void check(const ast_matchers::MatchFinder::MatchResult &Result) override;
};

} // namespace autosar
} // namespace tidy
} // namespace clang

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_AUTOSAR_RULEA391CHECK_H
