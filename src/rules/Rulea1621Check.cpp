//===--- Rulea1621Check.cpp - clang-tidy ----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
#include "Rulea1621Check.h"
#include "clang/AST/ASTContext.h"
#include "clang/Lex/Preprocessor.h"
#include "llvm/ADT/StringRef.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace autosar {
namespace {
    class IncludeNameCheckPPCallbacks: public PPCallbacks{
      public:
        explicit IncludeNameCheckPPCallbacks(Rulea1621Check &Check,
                                        const SourceManager &SM,
                                        Preprocessor *PP): Check(Check), PP(PP) {}

        void InclusionDirective(SourceLocation HashLoc, const Token &IncludeTok,
                          StringRef FileName, bool IsAngled,
                          CharSourceRange FilenameRange, const FileEntry *File,
                          StringRef SearchPath, StringRef RelativePath,
                          const Module *Imported,
                          SrcMgr::CharacteristicKind FileType) override;
      private:
        Rulea1621Check &Check;
        Preprocessor *PP;

    };
  
  }

Rulea1621Check::Rulea1621Check(StringRef Name, ClangTidyContext *Context): ClangTidyCheck(Name,Context){}

void Rulea1621Check::registerPPCallbacks(
    const SourceManager &SM, Preprocessor *PP, Preprocessor *ModuleExpanderPP) {
  PP->addPPCallbacks(
      ::std::make_unique<IncludeNameCheckPPCallbacks>(*this, SM, PP));
}
void IncludeNameCheckPPCallbacks::InclusionDirective(
    SourceLocation HashLoc, const Token &IncludeTok, StringRef FileName,
    bool IsAngled, CharSourceRange FilenameRange, const FileEntry *File,
    StringRef SearchPath, StringRef RelativePath, const Module *Imported,
    SrcMgr::CharacteristicKind FileType) {
  if (IncludeTok.getIdentifierInfo()->getPPKeywordID() == tok::pp_import)
    return;

  SourceLocation DiagLoc = FilenameRange.getBegin().getLocWithOffset(1);

  if (FileName.contains("'"))
  {
    Check.diag(DiagLoc,"header file should not contain ' in its name");
  }
  if (FileName.contains("\""))
  {
    Check.diag(DiagLoc,"header file should not contain \" in its name");
  }
  if (FileName.contains("/*"))
  {
    Check.diag(DiagLoc,"header file should not contain /* in its name");
  }
  if (FileName.contains("//"))
  {
    Check.diag(DiagLoc,"header file should not contain // in its name");
  }
  if (FileName.contains("\\"))
  {
    Check.diag(DiagLoc,"header file should not contain \\ in its name");
  }
}

} // namespace autosar
} // namespace tidy
} // namespace clang
