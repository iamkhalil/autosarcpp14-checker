//===--- Rulea313Check.cpp - clang-tidy -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Rulea313Check.h"
#include "clang/AST/ASTContext.h"
#include "clang/Lex/Preprocessor.h"
#include "llvm/ADT/StringRef.h"
using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace autosar {
  namespace {
    class IncludeFileImplementationPPCallbacks: public PPCallbacks{
      public:
        explicit IncludeFileImplementationPPCallbacks(Rulea313Check &Check,
                                        const SourceManager &SM,
                                        Preprocessor *PP): Check(Check), PP(PP) {}

        void InclusionDirective(SourceLocation HashLoc, const Token &IncludeTok,
                          StringRef FileName, bool IsAngled,
                          CharSourceRange FilenameRange, const FileEntry *File,
                          StringRef SearchPath, StringRef RelativePath,
                          const Module *Imported,
                          SrcMgr::CharacteristicKind FileType) override;
      private:
        Rulea313Check &Check;
        Preprocessor *PP;

    };
}

/// Returns recommended default value for the list of implementation file
/// extensions.
StringRef Rulea313Check::dfltImplementationFileExtensions() {return "cpp;";}

Rulea313Check::Rulea313Check(StringRef Name,ClangTidyContext *Context): ClangTidyCheck(Name, Context),
      RawStringImplementationFileExtensions(Options.getLocalOrGlobal(
          "ImplementationFileExtensions",
          dfltImplementationFileExtensions())) {
  if (!utils::parseFileExtensions(RawStringImplementationFileExtensions,
                                  ImplementationFileExtensions,
                                  utils::defaultFileExtensionDelimiters())) {
    this->configurationDiag("Invalid implementation file extension: '%0'")
        << RawStringImplementationFileExtensions;
  }
}

void Rulea313Check::storeOptions(ClangTidyOptions::OptionMap &Opts) {
  Options.store(Opts, "ImplementationFileExtensions",
                RawStringImplementationFileExtensions);
}

void Rulea313Check::registerPPCallbacks(
    const SourceManager &SM, Preprocessor *PP, Preprocessor *ModuleExpanderPP) {
  PP->addPPCallbacks(::std::make_unique<IncludeFileImplementationPPCallbacks>(*this, SM, PP));
}

void IncludeFileImplementationPPCallbacks::InclusionDirective(
    SourceLocation HashLoc, const Token &IncludeTok, StringRef FileName,
    bool IsAngled, CharSourceRange FilenameRange, const FileEntry *File,
    StringRef SearchPath, StringRef RelativePath, const Module *Imported,
    SrcMgr::CharacteristicKind FileType) {
  if (IncludeTok.getIdentifierInfo()->getPPKeywordID() == tok::pp_import)
    return;

  SourceLocation DiagLoc = FilenameRange.getBegin().getLocWithOffset(1);

  const Optional<StringRef> IFE =
      utils::getFileExtension(FileName, Check.ImplementationFileExtensions);
  if(!IsAngled){
    std::pair< StringRef, StringRef > FName=FileName.split('.');
    if (FName.second.startswith("h"))return;
    else {
    if (IFE)
      return;
    else {
      Check.diag(DiagLoc, "Invalid #%0, file extension for implementation files shall be .cpp")<< IncludeTok.getIdentifierInfo()->getName() << *IFE;}
  }}
  else {
    if (!(FileName.contains(".")))return ;
    else {
      std::pair< StringRef, StringRef > FName=FileName.split('.');
    if (FName.second.startswith("h"))return;
    else {
      if (!IFE)
        {Check.diag(DiagLoc, "Invalid #%0, file extension for implementation files shall be .cpp ")<< IncludeTok.getIdentifierInfo()->getName();}
      else 
        return;}}

  }
  

  
}

} // namespace autosar
} // namespace tidy
} // namespace clang
