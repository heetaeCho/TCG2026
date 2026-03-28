#include <gtest/gtest.h>

#include "re2/compile.cc"



namespace re2 {



class CompilerTest_314 : public ::testing::Test {

protected:

    Compiler compiler_;

};



TEST_F(CompilerTest_314, AddRuneRangeLatin1_NormalOperation_314) {

    // Test normal operation within Latin1 range

    EXPECT_NO_THROW(compiler_.AddRuneRangeLatin1(65, 90, false));

}



TEST_F(CompilerTest_314, AddRuneRangeLatin1_BoundaryConditions_LowerBound_314) {

    // Test with lower boundary of Latin1 range

    EXPECT_NO_THROW(compiler_.AddRuneRangeLatin1(0, 255, false));

}



TEST_F(CompilerTest_314, AddRuneRangeLatin1_BoundaryConditions_UpperBound_314) {

    // Test with upper boundary of Latin1 range

    EXPECT_NO_THROW(compiler_.AddRuneRangeLatin1(0xFF, 0xFF, false));

}



TEST_F(CompilerTest_314, AddRuneRangeLatin1_OutOfBounds_Lower_314) {

    // Test with lo < 0 (should not add)

    compiler_.AddRuneRangeLatin1(-1, 50, false);

    // Assuming no observable effect other than the function call itself

}



TEST_F(CompilerTest_314, AddRuneRangeLatin1_OutOfBounds_Upper_314) {

    // Test with hi > 255 (should clamp to 255)

    EXPECT_NO_THROW(compiler_.AddRuneRangeLatin1(100, 300, false));

}



TEST_F(CompilerTest_314, AddRuneRangeLatin1_InvertedRange_314) {

    // Test with lo > hi (should not add)

    compiler_.AddRuneRangeLatin1(100, 50, false);

    // Assuming no observable effect other than the function call itself

}



TEST_F(CompilerTest_314, AddRuneRangeLatin1_FoldCase_True_314) {

    // Test with foldcase true

    EXPECT_NO_THROW(compiler_.AddRuneRangeLatin1(97, 122, true));

}



TEST_F(CompilerTest_314, AddRuneRangeLatin1_FoldCase_False_314) {

    // Test with foldcase false

    EXPECT_NO_THROW(compiler_.AddRuneRangeLatin1(65, 90, false));

}



} // namespace re2
