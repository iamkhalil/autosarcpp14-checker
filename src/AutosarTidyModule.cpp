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
#include "Rulea1671Check.h"
#include "Rulea1803Check.h"
#include "Rulea716Check.h"
#include "Rulea723Check.h"
#include "Rulea951Check.h"
#include "Rulem1631Check.h"
#include "Rulem1632Check.h"
#include "Rulem1804Check.h"
#include "Rulem1805Check.h"
#include "Rulem4102Check.h"
#include "Rulea042Check.h"
#include "Rulea1101Check.h"
#include "Rulea1241Check.h"
#include "Rulea1323Check.h"
#include "Rulea1621Check.h"
#include "Rulea2133Check.h"
#include "Rulea312Check.h"
#include "Rulea313Check.h"
#include "Rulea314Check.h"
#include "Rulea391Check.h"
#include "Rulem1101Check.h"

namespace clang {
namespace tidy {
namespace autosar {

class AutosarModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
    CheckFactories.registerCheck<Rulea1671Check>(
        "autosar-RuleA16-7-1");
    CheckFactories.registerCheck<Rulea1803Check>(
        "autosar-RuleA18-0-3");
    CheckFactories.registerCheck<Rulem1631Check>(
        "autosar-RuleM16-3-1");
    CheckFactories.registerCheck<Rulem1632Check>(
        "autosar-RuleM16-3-2");
    CheckFactories.registerCheck<Rulea716Check>(
        "autosar-ruleA7-1-6");
    CheckFactories.registerCheck<Rulea723Check>(
        "autosar-ruleA7-2-3");
    CheckFactories.registerCheck<Rulea951Check>("autosar-ruleA9-5-1");
    CheckFactories.registerCheck<Rulem1804Check>(
        "autosar-ruleM18-0-4");
    CheckFactories.registerCheck<Rulem1805Check>(
        "autosar-ruleM18-0-5");
    CheckFactories.registerCheck<Rulem4102Check>(
        "autosar-ruleM4-10-2");
    CheckFactories.registerCheck<Rulea042Check>(
        "autosar-ruleA0-4-2");
    CheckFactories.registerCheck<Rulea1101Check>(
        "autosar-ruleA11-0-1");
    CheckFactories.registerCheck<Rulea1323Check>(
        "autosar-ruleA13-2-3");
    CheckFactories.registerCheck<Rulea1621Check>(
        "autosar-ruleA16-2-1");
    CheckFactories.registerCheck<Rulea2133Check>(
        "autosar-ruleA2-13-3");
    CheckFactories.registerCheck<Rulea312Check>(
        "autosar-ruleA3-1-2");
    CheckFactories.registerCheck<Rulea313Check>(
        "autosar-ruleA3-1-3");
    CheckFactories.registerCheck<Rulea314Check>(
        "autosar-ruleA3-1-4");
    CheckFactories.registerCheck<Rulea391Check>(
        "autosar-ruleA3-9-1");
    CheckFactories.registerCheck<Rulem1101Check>(
        "autosar-ruleM11-0-1");
    CheckFactories.registerCheck<Rulea1241Check>(
        "autosar-ruleA12-4-1");
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
