//===--- Rulea312Check.cpp - clang-tidy -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
#include <utility>  
#include "Rulea312Check.h"
#include "clang/AST/ASTContext.h"
#include "clang/Lex/Preprocessor.h"
#include "llvm/ADT/StringRef.h"



namespace clang {
namespace tidy {
namespace autosar {
  namespace {
    class IncludeNamePPCallbacks: public PPCallbacks{
      public:
        explicit IncludeNamePPCallbacks(Rulea312Check &Check,
                                        const SourceManager &SM,
                                        Preprocessor *PP): Check(Check), PP(PP) {}

        void InclusionDirective(SourceLocation HashLoc, const Token &IncludeTok,
                          StringRef FileName, bool IsAngled,
                          CharSourceRange FilenameRange, const FileEntry *File,
                          StringRef SearchPath, StringRef RelativePath,
                          const Module *Imported,
                          SrcMgr::CharacteristicKind FileType) override;
      private:
        Rulea312Check &Check;
        Preprocessor *PP;

    };
  
  }
  /// Returns recommended default value for the list of header file
 /// extensions.
StringRef Rulea312Check::dfltHeaderFileExtensions() { return ";h;hpp;hxx"; }

Rulea312Check::Rulea312Check(StringRef Name, ClangTidyContext *Context): ClangTidyCheck(Name,Context),RawStringHeaderFileExtensions(Options.get("HeaderFileExtensions", dfltHeaderFileExtensions()))
{
  if (!utils::parseFileExtensions(RawStringHeaderFileExtensions,
                                  HeaderFileExtensions,
                                  utils::defaultFileExtensionDelimiters())) {
    this->configurationDiag("Invalid header file extension: '%0'")
        << RawStringHeaderFileExtensions;
}
}
void Rulea312Check::storeOptions(ClangTidyOptions::OptionMap &Opts) {
  Options.store(Opts, "HeaderFileExtensions", RawStringHeaderFileExtensions);
}

void Rulea312Check::registerPPCallbacks(
    const SourceManager &SM, Preprocessor *PP, Preprocessor *ModuleExpanderPP) {
  PP->addPPCallbacks(
      ::std::make_unique<IncludeNamePPCallbacks>(*this, SM, PP));
}
void IncludeNamePPCallbacks::InclusionDirective(
    SourceLocation HashLoc, const Token &IncludeTok, StringRef FileName,
    bool IsAngled, CharSourceRange FilenameRange, const FileEntry *File,
    StringRef SearchPath, StringRef RelativePath, const Module *Imported,
    SrcMgr::CharacteristicKind FileType) {
  if (IncludeTok.getIdentifierInfo()->getPPKeywordID() == tok::pp_import)
    return;

  SourceLocation DiagLoc = FilenameRange.getBegin().getLocWithOffset(1);

  const Optional<StringRef> HFE =utils::getFileExtension(FileName, Check.HeaderFileExtensions);
  if(!IsAngled)
  {
    std::pair< StringRef, StringRef > FName=FileName.split('.');
    if (FName.second.startswith("c"))return;
    else {
    if (!HFE)Check.diag(DiagLoc, "Invalid #%0, file extension for headers shall be .h, .hpp or .hxx ")<< IncludeTok.getIdentifierInfo()->getName();
    else 
        return;}
  }
  else {
    if (!(FileName.contains(".")))return ;
    else {
      std::pair< StringRef, StringRef > FName=FileName.split('.');
      if (FName.second.startswith("c"))
        return;
      else {
          if (!HFE)
          {
            Check.diag(DiagLoc, "Invalid #%0, file extension for headers shall be .h, .hpp or .hxx ")<< IncludeTok.getIdentifierInfo()->getName();}
          else 
            return;}}}}
} // namespace autosar
} // namespace tidy
} // namespace clang
