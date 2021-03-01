//===- CppDslEx1.cpp ---------------------------------------------===//
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

#include "CppDslEx1.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendPluginRegistry.h"
#include "clang/Sema/Sema.h"
#include "llvm/Support/raw_ostream.h"

using namespace clang;

MyCodeGen::MyCodeGen(CompilerInstance &CI) {
  TheRewriter.setSourceMgr(CI.getSourceManager(), CI.getLangOpts());
}

void MyCodeGen::createBuiltinFunc(CallExpr *callExpr,
                                           ASTContext *Context,
                                           FunctionDecl *CurrFunc,
                                           FunctionDecl *FD) {
  llvm::dbgs() << "Function Name: " << FD->getQualifiedNameAsString() << "\n";
  FullSourceLoc FDBeginLoc = Context->getFullLoc(FD->getBeginLoc());
  assert(FDBeginLoc.isValid());
  llvm::dbgs() << "Found Function Declaration begin at "
               << FDBeginLoc.getSpellingLineNumber() << ":"
               << FDBeginLoc.getSpellingColumnNumber() << "\n";
  FullSourceLoc FDEndLoc = Context->getFullLoc(FD->getEndLoc());
  assert(FDEndLoc.isValid());
  llvm::dbgs() << "Found Function Declaration end at "
               << FDEndLoc.getSpellingLineNumber() << ":"
               << FDEndLoc.getSpellingColumnNumber() << "\n";

  auto CallerFuncName = *callExpr->child_begin();
  SourceRange CallerSR = CallerFuncName->getSourceRange();
  FullSourceLoc CallerBeginLoc = Context->getFullLoc(CallerSR.getBegin());
  assert(CallerBeginLoc.isValid());
  llvm::dbgs() << "Found Caller begin at "
               << CallerBeginLoc.getSpellingLineNumber() << ":"
               << CallerBeginLoc.getSpellingColumnNumber() << "\n";
  FullSourceLoc CallerEndLoc = Context->getFullLoc(CallerSR.getEnd());
  assert(CallerEndLoc.isValid());
  llvm::dbgs() << "Found Caller end at "
               << CallerEndLoc.getSpellingLineNumber() << ":"
               << CallerEndLoc.getSpellingColumnNumber() << "\n";

  if (FD->getQualifiedNameAsString() == "A::abc") {
    // Use getSourceRange() instead of getBeginLoc() since A:: and abc may sit at
    // different lines.
    char sBuiltinFunc[] = "__builtin_fabs";
    TheRewriter.ReplaceText(CallerSR, StringRef(sBuiltinFunc));
  }
}

void MyCodeGen::outputFile() {
  SourceManager &SM = TheRewriter.getSourceMgr();
  StringRef inFileName = SM.getFileEntryForID(SM.getMainFileID())->getName();
  std::string outFileName = "output.cpp";
  llvm::dbgs() << "input file: " << inFileName << "\n";
  llvm::dbgs() << "output file: " << outFileName << "\n";

  // Now emit the rewritten buffer.
  std::error_code EC;
  llvm::raw_fd_ostream OS(outFileName, EC);
  TheRewriter.getEditBuffer(SM.getMainFileID()).write(OS);
  // TheRewriter.overwriteChangedFiles();
}

#if 0
bool MyASTVisitor::TraverseDecl(Decl *D) {
  if (D && D->isFunctionOrFunctionTemplate()) {
    // Get CurrFunc mem addr for checking whether or not this function is
    // __global__ entry function later
    CurrFunc = D->getAsFunction();
  }
  RecursiveASTVisitor<MyASTVisitor>::TraverseDecl(D);
  return true;
}
#else
bool MyASTVisitor::VisitFunctionDecl(FunctionDecl *FD) {
  CurrFunc = FD;
  return true;
}
#endif

FunctionDecl *MyASTVisitor::GetFunctionDecl(CallExpr *callExpr) {
  for (auto cait = callExpr->child_begin();
       cait != callExpr->child_end(); ++cait) {
    if (auto impexpr = dyn_cast_or_null<ImplicitCastExpr>(*cait)) {
      for (auto imit = impexpr->child_begin();
           imit != impexpr->child_end(); ++imit) {
        if (auto decl_ref = dyn_cast_or_null<DeclRefExpr>(*imit)) {
          if (auto FD = dyn_cast_or_null<FunctionDecl>(
              decl_ref->getDecl())) {
            return FD;
          }
        }
      }
    }
  }
  return nullptr;
}

bool MyASTVisitor::VisitStmt(Stmt *x) {
  if (!CurrFunc) {
    return true;
  }
  // Use _Noreturn as an example for adding keyword before function.
  // Search "_Noreturn" in clang/include clang/lib to see how to add keyword
  //   for function.
  llvm::dbgs() << "CurrFunc name: " << CurrFunc->getQualifiedNameAsString()
               << ", CurrFunc->hasAttr<C11NoReturnAttr>(): "
               << CurrFunc->hasAttr<C11NoReturnAttr>() << "\n";
  if (CurrFunc->hasAttr<C11NoReturnAttr>()) {
    if (auto cmps = dyn_cast_or_null<CompoundStmt>(x)) {
      for (auto it = cmps->child_begin(); it != cmps->child_end(); ++it) {
        if (auto decls = dyn_cast_or_null<DeclStmt>(*it)) {
          for (auto it2 = decls->child_begin(); it2 != decls->child_end(); ++it2) {
            if (auto callExpr = dyn_cast_or_null<CallExpr>(*it2)) {
              FunctionDecl *FD = GetFunctionDecl(callExpr);
              if (FD->getQualifiedNameAsString() == "A::abc") {
                CodeGen.createBuiltinFunc(callExpr, Context, CurrFunc, FD);
              }
            }
          }
        }
      }
    }
  }
  return true;
}

MyConsumer::MyConsumer(CompilerInstance &CI)
    : CodeGen(CI), Visitor(&CI.getASTContext(), CodeGen) {
  llvm::dbgs() << "** Creating MyConsumer: " << "\n";
}

// Override the method that gets called for each parsed top-level
// declaration.
bool MyConsumer::HandleTopLevelDecl(DeclGroupRef DR) {
  for (DeclGroupRef::iterator b = DR.begin(), e = DR.end(); b != e; ++b) {
    // Traverse the declaration using our AST visitor.
    Visitor.TraverseDecl(*b);
  }
  return true;
}

void MyConsumer::HandleTranslationUnit(clang::ASTContext &Context) {

  CodeGen.outputFile();
}

bool MyConsumer::TraverseDecl(Decl *D) {
  return Visitor.TraverseDecl(D);
}


std::unique_ptr<ASTConsumer>
MyAction::CreateASTConsumer(CompilerInstance &CI,
                            llvm::StringRef InFile) {
  return std::make_unique<MyConsumer>(CI);
}

bool MyAction::ParseArgs(const CompilerInstance &CI,
                         const std::vector<std::string> &args) {
  return true;
}

// http://clang-developers.42468.n3.nabble.com/AST-modifications-that-apply-to-the-binary-td4054289.html
MyAction::ActionType MyAction::getActionType() {
  return AddBeforeMainAction;
}

bool MyAction::usesPreprocessorOnly() const { return false; }

static FrontendPluginRegistry::Add<MyAction>
    X("ex1-act", "convert cpp to cpp");
