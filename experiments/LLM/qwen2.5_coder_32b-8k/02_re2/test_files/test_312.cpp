#include <gtest/gtest.h>

#include "re2/compile.h"



using namespace re2;



class CompilerTest_312 : public ::testing::Test {

protected:

    Compiler compiler;

};



TEST_F(CompilerTest_312, EndRange_NormalOperation_312) {

    Frag result = compiler.EndRange();

    // Assuming Frag is default constructible and comparable

    Frag expected; // Default constructed frag as expected value

    EXPECT_EQ(result, expected);

}



// Additional tests for other functions



TEST_F(CompilerTest_312, Compile_NormalOperation_312) {

    Regexp* re = new Regexp(); // Assuming Regexp is default constructible

    Prog* prog = Compiler::Compile(re, false, 1024);

    EXPECT_NE(prog, nullptr);

    delete re;

    delete prog;

}



TEST_F(CompilerTest_312, CompileSet_NormalOperation_312) {

    Regexp* re = new Regexp(); // Assuming Regexp is default constructible

    Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_START, 1024);

    EXPECT_NE(prog, nullptr);

    delete re;

    delete prog;

}



TEST_F(CompilerTest_312, NoMatch_NormalOperation_312) {

    Frag result = compiler.NoMatch();

    // Assuming Frag is default constructible and comparable

    Frag expected; // Default constructed frag as expected value

    EXPECT_EQ(result, expected);

}



TEST_F(CompilerTest_312, Cat_NormalOperation_312) {

    Frag a, b;

    Frag result = compiler.Cat(a, b);

    // Assuming Frag is default constructible and comparable

    Frag expected; // Default constructed frag as expected value

    EXPECT_EQ(result, expected); // This might need to be adjusted based on actual implementation details

}



TEST_F(CompilerTest_312, Alt_NormalOperation_312) {

    Frag a, b;

    Frag result = compiler.Alt(a, b);

    // Assuming Frag is default constructible and comparable

    Frag expected; // Default constructed frag as expected value

    EXPECT_EQ(result, expected); // This might need to be adjusted based on actual implementation details

}



TEST_F(CompilerTest_312, Plus_NormalOperation_312) {

    Frag a;

    bool nongreedy = false;

    Frag result = compiler.Plus(a, nongreedy);

    // Assuming Frag is default constructible and comparable

    Frag expected; // Default constructed frag as expected value

    EXPECT_EQ(result, expected); // This might need to be adjusted based on actual implementation details

}



TEST_F(CompilerTest_312, Star_NormalOperation_312) {

    Frag a;

    bool nongreedy = false;

    Frag result = compiler.Star(a, nongreedy);

    // Assuming Frag is default constructible and comparable

    Frag expected; // Default constructed frag as expected value

    EXPECT_EQ(result, expected); // This might need to be adjusted based on actual implementation details

}



TEST_F(CompilerTest_312, Quest_NormalOperation_312) {

    Frag a;

    bool nongreedy = false;

    Frag result = compiler.Quest(a, nongreedy);

    // Assuming Frag is default constructible and comparable

    Frag expected; // Default constructed frag as expected value

    EXPECT_EQ(result, expected); // This might need to be adjusted based on actual implementation details

}



TEST_F(CompilerTest_312, ByteRange_NormalOperation_312) {

    int lo = 0;

    int hi = 255;

    bool foldcase = false;

    Frag result = compiler.ByteRange(lo, hi, foldcase);

    // Assuming Frag is default constructible and comparable

    Frag expected; // Default constructed frag as expected value

    EXPECT_EQ(result, expected); // This might need to be adjusted based on actual implementation details

}



TEST_F(CompilerTest_312, Nop_NormalOperation_312) {

    Frag result = compiler.Nop();

    // Assuming Frag is default constructible and comparable

    Frag expected; // Default constructed frag as expected value

    EXPECT_EQ(result, expected);

}



TEST_F(CompilerTest_312, Match_NormalOperation_312) {

    int32_t match_id = 0;

    Frag result = compiler.Match(match_id);

    // Assuming Frag is default constructible and comparable

    Frag expected; // Default constructed frag as expected value

    EXPECT_EQ(result, expected); // This might need to be adjusted based on actual implementation details

}



TEST_F(CompilerTest_312, EmptyWidth_NormalOperation_312) {

    EmptyOp op = EmptyOp::kNoWidth;

    Frag result = compiler.EmptyWidth(op);

    // Assuming Frag is default constructible and comparable

    Frag expected; // Default constructed frag as expected value

    EXPECT_EQ(result, expected); // This might need to be adjusted based on actual implementation details

}



TEST_F(CompilerTest_312, Capture_NormalOperation_312) {

    Frag a;

    int n = 0;

    Frag result = compiler.Capture(a, n);

    // Assuming Frag is default constructible and comparable

    Frag expected; // Default constructed frag as expected value

    EXPECT_EQ(result, expected); // This might need to be adjusted based on actual implementation details

}



TEST_F(CompilerTest_312, Literal_NormalOperation_312) {

    Rune r = 0;

    bool foldcase = false;

    Frag result = compiler.Literal(r, foldcase);

    // Assuming Frag is default constructible and comparable

    Frag expected; // Default constructed frag as expected value

    EXPECT_EQ(result, expected); // This might need to be adjusted based on actual implementation details

}



TEST_F(CompilerTest_312, DotStar_NormalOperation_312) {

    Frag result = compiler.DotStar();

    // Assuming Frag is default constructible and comparable

    Frag expected; // Default constructed frag as expected value

    EXPECT_EQ(result, expected); // This might need to be adjusted based on actual implementation details

}



TEST_F(CompilerTest_312, BeginRange_NormalOperation_312) {

    compiler.BeginRange();

    // No return value to check, just ensuring no crash

}



TEST_F(CompilerTest_312, AddRuneRange_NormalOperation_312) {

    Rune lo = 0;

    Rune hi = 255;

    bool foldcase = false;

    compiler.AddRuneRange(lo, hi, foldcase);

    // No return value to check, just ensuring no crash

}



TEST_F(CompilerTest_312, AddRuneRangeLatin1_NormalOperation_312) {

    Rune lo = 0;

    Rune hi = 255;

    bool foldcase = false;

    compiler.AddRuneRangeLatin1(lo, hi, foldcase);

    // No return value to check, just ensuring no crash

}



TEST_F(CompilerTest_312, AddRuneRangeUTF8_NormalOperation_312) {

    Rune lo = 0;

    Rune hi = 255;

    bool foldcase = false;

    compiler.AddRuneRangeUTF8(lo, hi, foldcase);

    // No return value to check, just ensuring no crash

}



TEST_F(CompilerTest_312, Add_80_10ffff_NormalOperation_312) {

    compiler.Add_80_10ffff();

    // No return value to check, just ensuring no crash

}
