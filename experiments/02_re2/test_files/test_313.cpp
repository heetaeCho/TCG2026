#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/compile.cc"



using namespace re2;



class CompilerTest_313 : public ::testing::Test {

protected:

    Compiler compiler;

};



TEST_F(CompilerTest_313, AddRuneRange_NormalOperation_UTF8_313) {

    // Test normal operation with UTF-8 encoding

    EXPECT_NO_THROW(compiler.AddRuneRange(65, 90, false)); // A-Z range without case folding

}



TEST_F(CompilerTest_313, AddRuneRange_NormalOperation_Latin1_313) {

    // Test normal operation with Latin1 encoding

    compiler.encoding_ = kEncodingLatin1;

    EXPECT_NO_THROW(compiler.AddRuneRange(65, 90, false)); // A-Z range without case folding

}



TEST_F(CompilerTest_313, AddRuneRange_BoundaryCondition_LowerBound_313) {

    // Test boundary condition with lower bound

    EXPECT_NO_THROW(compiler.AddRuneRange(0, 0, false));

}



TEST_F(CompilerTest_313, AddRuneRange_BoundaryCondition_UpperBound_313) {

    // Test boundary condition with upper bound

    EXPECT_NO_THROW(compiler.AddRuneRange(0x10FFFF, 0x10FFFF, false)); // Max Unicode code point

}



TEST_F(CompilerTest_313, AddRuneRange_ErrorCase_InvertedRange_313) {

    // Test error case with inverted range (lo > hi)

    EXPECT_NO_THROW(compiler.AddRuneRange(90, 65, false)); // Z-A range, should be handled gracefully

}



TEST_F(CompilerTest_313, AddRuneRange_ErrorCase_OutOfBounds_313) {

    // Test error case with out-of-bounds values (lo or hi outside valid Unicode range)

    EXPECT_NO_THROW(compiler.AddRuneRange(-1, 0, false)); // Negative lo value

    EXPECT_NO_THROW(compiler.AddRuneRange(0x110000, 0x110000, false)); // Above max Unicode code point

}



TEST_F(CompilerTest_313, AddRuneRange_CaseFolding_UTF8_313) {

    // Test case folding with UTF-8 encoding

    EXPECT_NO_THROW(compiler.AddRuneRange(65, 90, true)); // A-Z range with case folding

}



TEST_F(CompilerTest_313, AddRuneRange_CaseFolding_Latin1_313) {

    // Test case folding with Latin1 encoding

    compiler.encoding_ = kEncodingLatin1;

    EXPECT_NO_THROW(compiler.AddRuneRange(65, 90, true)); // A-Z range with case folding

}
