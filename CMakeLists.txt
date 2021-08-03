set(LLVM_LINK_COMPONENTS
  FrontendOpenMP
  Support
  )

add_clang_library(clangTidyAutosarModule
  AutosarTidyModule.cpp
  Rulea951Check.cpp
  Rulem1804Check.cpp

  LINK_LIBS
  clangTidy
  clangTidyUtils
  
  DEPENDS
  omp_gen
  )

clang_target_link_libraries(clangTidyAutosarModule
  PRIVATE
  clangAST	
  clangASTMatchers
  clangBasic
  clangLex
  )
