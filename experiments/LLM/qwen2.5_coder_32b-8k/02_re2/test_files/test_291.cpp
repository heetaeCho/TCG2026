#include <gtest/gtest.h>

#include "re2/compile.cc"



namespace re2 {



class IsNoMatchTest_291 : public ::testing::Test {

protected:

    Frag frag;

};



TEST_F(IsNoMatchTest_291, NormalOperation_BeginZero_291) {

    frag.begin = 0;

    EXPECT_TRUE(IsNoMatch(frag));

}



TEST_F(IsNoMatchTest_291, NormalOperation_BeginNonZero_291) {

    frag.begin = 1;

    EXPECT_FALSE(IsNoMatch(frag));

}



TEST_F(IsNoMatchTest_291, BoundaryCondition_BeginMaxUInt32_291) {

    frag.begin = UINT32_MAX;

    EXPECT_FALSE(IsNoMatch(frag));

}



TEST_F(IsNoMatchTest_291, BoundaryCondition_BeginMinUInt32_291) {

    frag.begin = 0;

    EXPECT_TRUE(IsNoMatch(frag));

}



} // namespace re2
