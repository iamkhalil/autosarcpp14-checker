//===--- AutosarTidyModule.cpp - clang-tidy ----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "../ClangTidy.h"
#include "../ClangTidyModule.h"
#include "../ClangTidyModuleRegistry.h"
#include "Rulea951Check.h"
#include "Rulem1804Check.h"

namespace clang {
namespace tidy {
namespace autosar {

class AutosarModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
    CheckFactories.registerCheck<Rulea951Check>("autosar-ruleA9-5-1");
    CheckFactories.registerCheck<Rulem1804Check>(
        "autosar-ruleM18-0-4");
  }
};

} // namespace autosar 

// Register the AutosarTidyModule using this statically initialized variable.
static ClangTidyModuleRegistry::Add<autosar::AutosarModule>
    X("autosar-module", "Adds my rule checks.");

// This anchor is used to force the linker to link in the generated object file
// and thus register the AutosarModule.
volatile int AutosarModuleAnchorSource = 0;

} // namespace tidy
} // namespace clang




