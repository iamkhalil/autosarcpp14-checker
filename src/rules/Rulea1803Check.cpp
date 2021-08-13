//===--- Rulea1803Check.cpp - clang-tidy ----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Rulea1803Check.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Lex/PPCallbacks.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Lex/Token.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace autosar {
namespace {
class Rulea1803PPCallbacks : public PPCallbacks {
public:
  Rulea1803PPCallbacks(ClangTidyCheck &Check, const SourceManager &SM)
      : Check(Check), SM(SM) {}

  virtual void InclusionDirective(SourceLocation HashLoc,
                                  const Token &IncludeTok, StringRef FileName,
                                  bool IsAngled, CharSourceRange FilenameRange,
                                  const FileEntry *File, StringRef SearchPath,
                                  StringRef RelativePath,
                                  const Module *Imported,
                                  SrcMgr::CharacteristicKind FileType) override;

private:
  ClangTidyCheck &Check;
  const SourceManager &SM;
};
} // namespace

void Rulea1803PPCallbacks::InclusionDirective(
    SourceLocation HashLoc, const Token &IncludeTok, StringRef FileName,
    bool IsAngled, CharSourceRange FilenameRange, const FileEntry *File,
    StringRef SearchPath, StringRef RelativePath, const Module *Imported,
    SrcMgr::CharacteristicKind FileType) {

  if (IsAngled) {
    if (FileName.equals("clocale") || FileName.equals("locale.h")) {
      Check.diag(HashLoc.getLocWithOffset(IncludeTok.getLength() + 2),
                 "The library <clocale> (locale.h) and the setlocale function "
                 "shall not be used.");
    }
  }
}

void Rulea1803Check::registerPPCallbacks(const SourceManager &SM,
                                         Preprocessor *PP,
                                         Preprocessor *ModuleExpanderPP) {
  PP->addPPCallbacks(::std::make_unique<Rulea1803PPCallbacks>(*this, SM));
}

void Rulea1803Check::registerMatchers(ast_matchers::MatchFinder *Finder) {
  Finder->addMatcher(
      callExpr(callee(functionDecl(hasName("setlocale")))).bind("funcDecl"),
      this);
}

void Rulea1803Check::check(const ast_matchers::MatchFinder::MatchResult &Result) {
  const auto *callExpr = Result.Nodes.getNodeAs<CallExpr>("funcDecl");
  if (callExpr) {
    const auto start = callExpr->getBeginLoc();
    diag(start, "The library <clocale> (locale.h) and the setlocale function "
                "shall not be used.");
  }
}

} // namespace autosar
} // namespace tidy
} // namespace clang
