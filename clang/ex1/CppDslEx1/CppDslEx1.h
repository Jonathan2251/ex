//===- MyAction.h ---------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Example clang plugin which simply prints the names of all the top-level decls
// in the input file.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_EXAMPLE_CPPDSLEX1_H
#define LLVM_CLANG_EXAMPLE_CPPDSLEX1_H

#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendPluginRegistry.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "clang/Sema/Sema.h"
#include "llvm/Support/raw_ostream.h"

using namespace clang;

class MyCodeGen {
public:
  explicit MyCodeGen(CompilerInstance &CI);
  void createBuiltinFunc(CallExpr *callExpr, ASTContext *Context,
                         FunctionDecl *CurrFunc, FunctionDecl *Caller);
  void outputFile();

private:
  Rewriter TheRewriter;
};

class MyASTVisitor : public RecursiveASTVisitor<MyASTVisitor> {
public:
  explicit MyASTVisitor(ASTContext *Context, MyCodeGen &CG)
      : Context(Context), CodeGen(CG), CurrFunc(nullptr) {}
  //bool TraverseDecl(Decl *D);
  bool VisitFunctionDecl(FunctionDecl *FD);
  bool VisitStmt(Stmt *x);

private:
  FunctionDecl *GetFunctionDecl(CallExpr *callExpr);
  ASTContext *Context;
  MyCodeGen &CodeGen;
  FunctionDecl *CurrFunc;
};

class MyConsumer : public clang::ASTConsumer {
public:
  explicit MyConsumer(CompilerInstance &CI);
  bool HandleTopLevelDecl(DeclGroupRef DR) override;
  void HandleTranslationUnit(clang::ASTContext &Context) override;
  bool TraverseDecl(Decl *D);

private:
  // The following order of members appear have to be same with the appearing
  // order in constructor function for clang compiler
  MyCodeGen CodeGen;
  MyASTVisitor Visitor;
};

// MyAction is plugin, so after creating MyConsumer, the
// plugin Action's members will be destroyed. Therefore no C++'s pointer or
// reference should refer to Action.
class MyAction : public PluginASTAction {
protected:
  std::unique_ptr<ASTConsumer>
  CreateASTConsumer(CompilerInstance &CI, llvm::StringRef InFile) override;
  bool ParseArgs(const CompilerInstance &CI,
                 const std::vector<std::string> &args) override;
  virtual ActionType getActionType() override;
  bool usesPreprocessorOnly() const override;
};

#endif
