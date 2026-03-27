#include <gtest/gtest.h>

#include "re2/compile.h"

#include "re2/regexp.h"



using namespace re2;



class CompilerTest_288 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



// Test normal operation of Compile method

TEST_F(CompilerTest_288, CompileNormalOperation_288) {

    Regexp* re = Regexp::Parse("abc", Regexp::Perl, nullptr);

    ASSERT_NE(re, nullptr);



    Prog* prog = Compiler::Compile(re, false, 1024);

    EXPECT_NE(prog, nullptr);



    delete prog;

    delete re;

}



// Test boundary conditions of Compile method with minimal memory

TEST_F(CompilerTest_288, CompileMinimalMemory_288) {

    Regexp* re = Regexp::Parse("a", Regexp::Perl, nullptr);

    ASSERT_NE(re, nullptr);



    Prog* prog = Compiler::Compile(re, false, 1);

    EXPECT_EQ(prog, nullptr); // Expect failure due to insufficient memory



    delete re;

}



// Test boundary conditions of Compile method with large pattern

TEST_F(CompilerTest_288, CompileLargePattern_288) {

    std::string pattern = "a{1000}"; // Large pattern

    Regexp* re = Regexp::Parse(pattern.c_str(), Regexp::Perl, nullptr);

    ASSERT_NE(re, nullptr);



    Prog* prog = Compiler::Compile(re, false, 1024 * 1024); // Sufficient memory

    EXPECT_NE(prog, nullptr);



    delete prog;

    delete re;

}



// Test exceptional case of Compile method with null pattern

TEST_F(CompilerTest_288, CompileNullPattern_288) {

    Prog* prog = Compiler::Compile(nullptr, false, 1024);

    EXPECT_EQ(prog, nullptr); // Expect failure due to null pattern

}



// Test normal operation of CompileSet method

TEST_F(CompilerTest_288, CompileSetNormalOperation_288) {

    Regexp* re = Regexp::Parse("abc", Regexp::Perl, nullptr);

    ASSERT_NE(re, nullptr);



    Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_START, 1024);

    EXPECT_NE(prog, nullptr);



    delete prog;

    delete re;

}



// Test boundary conditions of CompileSet method with minimal memory

TEST_F(CompilerTest_288, CompileSetMinimalMemory_288) {

    Regexp* re = Regexp::Parse("a", Regexp::Perl, nullptr);

    ASSERT_NE(re, nullptr);



    Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_START, 1);

    EXPECT_EQ(prog, nullptr); // Expect failure due to insufficient memory



    delete re;

}



// Test boundary conditions of CompileSet method with large pattern

TEST_F(CompilerTest_288, CompileSetLargePattern_288) {

    std::string pattern = "a{1000}"; // Large pattern

    Regexp* re = Regexp::Parse(pattern.c_str(), Regexp::Perl, nullptr);

    ASSERT_NE(re, nullptr);



    Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_START, 1024 * 1024); // Sufficient memory

    EXPECT_NE(prog, nullptr);



    delete prog;

    delete re;

}



// Test exceptional case of CompileSet method with null pattern

TEST_F(CompilerTest_288, CompileSetNullPattern_288) {

    Prog* prog = Compiler::CompileSet(nullptr, RE2::ANCHOR_START, 1024);

    EXPECT_EQ(prog, nullptr); // Expect failure due to null pattern

}



// Test normal operation of Finish method

TEST_F(CompilerTest_288, FinishNormalOperation_288) {

    Regexp* re = Regexp::Parse("abc", Regexp::Perl, nullptr);

    ASSERT_NE(re, nullptr);



    Compiler compiler;

    Frag frag = compiler.PreVisit(re, Frag(), nullptr);

    Prog* prog = compiler.Finish(re);

    EXPECT_NE(prog, nullptr);



    delete prog;

    delete re;

}



// Test exceptional case of Finish method with null pattern

TEST_F(CompilerTest_288, FinishNullPattern_288) {

    Compiler compiler;

    Prog* prog = compiler.Finish(nullptr);

    EXPECT_EQ(prog, nullptr); // Expect failure due to null pattern

}
