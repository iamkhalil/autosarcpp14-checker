//===--- Rulea312Check.h - clang-tidy ---------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_AUTOSAR_RULEA312CHECK_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_AUTOSAR_RULEA312CHECK_H

#include "../ClangTidyCheck.h"
#include "../utils/FileExtensionsUtils.h"

namespace clang {
namespace tidy {
namespace autosar {

/// FIXME: Write a short description.
///
/// For the user-facing documentation see:
/// http://clang.llvm.org/extra/clang-tidy/checks/autosar-ruleA3-1-2.html
class Rulea312Check : public ClangTidyCheck {
public:
  Rulea312Check(StringRef Name, ClangTidyContext *Context);
  void registerPPCallbacks(const SourceManager &SM, Preprocessor *PP,
                           Preprocessor *ModuleExpanderPP) override;
  void storeOptions(ClangTidyOptions::OptionMap &Opts) override;
  StringRef dfltHeaderFileExtensions();
  utils::FileExtensionsSet HeaderFileExtensions;
private:
  const std::string RawStringHeaderFileExtensions;
};

} // namespace autosar
} // namespace tidy
} // namespace clang

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_AUTOSAR_RULEA312CHECK_H
