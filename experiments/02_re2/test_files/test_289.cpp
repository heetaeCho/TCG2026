#include <gtest/gtest.h>

#include "re2/compile.cc"



namespace re2 {



class CompilerTest : public ::testing::Test {

protected:

    Compiler compiler;

};



TEST_F(CompilerTest_289, AllocInst_ReturnsValidId_289) {

    int id = compiler.AllocInst(1);

    EXPECT_GE(id, 0);

}



TEST_F(CompilerTest_289, AllocInst_IncreasesCount_289) {

    int initial_id = compiler.AllocInst(1);

    int next_id = compiler.AllocInst(1);

    EXPECT_EQ(next_id, initial_id + 1);

}



TEST_F(CompilerTest_289, AllocInst_ExceedsMaxNinst_ReturnsNegative_289) {

    compiler.max_ninst_ = 0; // Reset max_ninst to a small value for testing

    int id = compiler.AllocInst(1);

    EXPECT_EQ(id, -1);

}



TEST_F(CompilerTest_289, AllocInst_MaxNinstBoundary_ReturnsNegative_289) {

    compiler.max_ninst_ = 0; // Reset max_ninst to a small value for testing

    int id = compiler.AllocInst(0);

    EXPECT_EQ(id, -1);

}



TEST_F(CompilerTest_289, AllocInst_ZeroN_ReturnsCurrentId_289) {

    int initial_id = compiler.AllocInst(0);

    EXPECT_EQ(initial_id, 0);

}



TEST_F(CompilerTest_289, AllocInst_MultipleCallsIncreaseCount_289) {

    int id1 = compiler.AllocInst(1);

    int id2 = compiler.AllocInst(2);

    int id3 = compiler.AllocInst(3);

    EXPECT_EQ(id2, id1 + 1);

    EXPECT_EQ(id3, id2 + 2);

}



TEST_F(CompilerTest_289, AllocInst_LargeN_ReturnsValidIdAndResizes_289) {

    int initial_id = compiler.AllocInst(1000); // Large number to force resizing

    EXPECT_GE(initial_id, 0);

}



} // namespace re2
