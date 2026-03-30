#include <gtest/gtest.h>

#include "re2/regexp.h"

#include "re2/prog.h"



using namespace re2;



class CompilerTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup any common resources or mocks here if needed.

    }



    void TearDown() override {

        // Clean up after each test case.

    }

};



TEST_F(CompilerTest_325, CompileNullRegexp_325) {

    Regexp* re = nullptr;

    Compiler compiler;

    Prog* prog = compiler.Compile(re, false, 1024);

    EXPECT_EQ(prog, nullptr);

}



TEST_F(CompilerTest_325, CompileSimpleLiteral_325) {

    RegexpStatus status;

    Regexp* re = Regexp::Parse("hello", Regexp::UTF8, &status);

    Compiler compiler;

    Prog* prog = compiler.Compile(re, false, 1024);

    EXPECT_NE(prog, nullptr);

    prog->Decref();

}



TEST_F(CompilerTest_325, CompileReversedLiteral_325) {

    RegexpStatus status;

    Regexp* re = Regexp::Parse("hello", Regexp::UTF8, &status);

    Compiler compiler;

    Prog* prog = compiler.Compile(re, true, 1024);

    EXPECT_NE(prog, nullptr);

    prog->Decref();

}



TEST_F(CompilerTest_325, CompileWithMaxMemZero_325) {

    RegexpStatus status;

    Regexp* re = Regexp::Parse("hello", Regexp::UTF8, &status);

    Compiler compiler;

    Prog* prog = compiler.Compile(re, false, 0);

    EXPECT_EQ(prog, nullptr);

}



TEST_F(CompilerTest_325, CompileComplexExpression_325) {

    RegexpStatus status;

    Regexp* re = Regexp::Parse("a(b|c)+d?", Regexp::UTF8, &status);

    Compiler compiler;

    Prog* prog = compiler.Compile(re, false, 1024);

    EXPECT_NE(prog, nullptr);

    prog->Decref();

}



TEST_F(CompilerTest_325, CompileAnchoredStart_325) {

    RegexpStatus status;

    Regexp* re = Regexp::Parse("^hello", Regexp::UTF8, &status);

    Compiler compiler;

    Prog* prog = compiler.Compile(re, false, 1024);

    EXPECT_NE(prog, nullptr);

    EXPECT_TRUE(prog->anchor_start());

    prog->Decref();

}



TEST_F(CompilerTest_325, CompileAnchoredEnd_325) {

    RegexpStatus status;

    Regexp* re = Regexp::Parse("hello$", Regexp::UTF8, &status);

    Compiler compiler;

    Prog* prog = compiler.Compile(re, false, 1024);

    EXPECT_NE(prog, nullptr);

    EXPECT_TRUE(prog->anchor_end());

    prog->Decref();

}



TEST_F(CompilerTest_325, CompileAnchoredBoth_325) {

    RegexpStatus status;

    Regexp* re = Regexp::Parse("^hello$", Regexp::UTF8, &status);

    Compiler compiler;

    Prog* prog = compiler.Compile(re, false, 1024);

    EXPECT_NE(prog, nullptr);

    EXPECT_TRUE(prog->anchor_start());

    EXPECT_TRUE(prog->anchor_end());

    prog->Decref();

}



TEST_F(CompilerTest_325, CompileDotStarAnchoredEnd_325) {

    RegexpStatus status;

    Regexp* re = Regexp::Parse(".*hello$", Regexp::UTF8, &status);

    Compiler compiler;

    Prog* prog = compiler.Compile(re, false, 1024);

    EXPECT_NE(prog, nullptr);

    EXPECT_TRUE(prog->anchor_end());

    prog->Decref();

}



TEST_F(CompilerTest_325, CompileDotStarAnchoredStart_325) {

    RegexpStatus status;

    Regexp* re = Regexp::Parse("^hello.*", Regexp::UTF8, &status);

    Compiler compiler;

    Prog* prog = compiler.Compile(re, false, 1024);

    EXPECT_NE(prog, nullptr);

    EXPECT_TRUE(prog->anchor_start());

    prog->Decref();

}



TEST_F(CompilerTest_325, CompileDotStarAnchoredBoth_325) {

    RegexpStatus status;

    Regexp* re = Regexp::Parse("^hello.*world$", Regexp::UTF8, &status);

    Compiler compiler;

    Prog* prog = compiler.Compile(re, false, 1024);

    EXPECT_NE(prog, nullptr);

    EXPECT_TRUE(prog->anchor_start());

    EXPECT_TRUE(prog->anchor_end());

    prog->Decref();

}
