#include <gtest/gtest.h>

#include "compile.cc"



namespace re2 {



class MakeRuneCacheKeyTest_305 : public ::testing::Test {

protected:

    // You can set up any common state here if needed.

};



TEST_F(MakeRuneCacheKeyTest_305, NormalOperation_305) {

    uint64_t result = MakeRuneCacheKey(1, 2, true, 3);

    EXPECT_EQ(result, (uint64_t)3 << 17 | (uint64_t)1 << 9 | (uint64_t)2 << 1 | (uint64_t)true);

}



TEST_F(MakeRuneCacheKeyTest_305, BoundaryConditions_LoHiFoldcaseZero_305) {

    uint64_t result = MakeRuneCacheKey(0, 0, false, 0);

    EXPECT_EQ(result, (uint64_t)0 << 17 | (uint64_t)0 << 9 | (uint64_t)0 << 1 | (uint64_t)false);

}



TEST_F(MakeRuneCacheKeyTest_305, BoundaryConditions_LoHiFoldcaseMax_305) {

    uint64_t result = MakeRuneCacheKey(255, 255, true, 0);

    EXPECT_EQ(result, (uint64_t)0 << 17 | (uint64_t)255 << 9 | (uint64_t)255 << 1 | (uint64_t)true);

}



TEST_F(MakeRuneCacheKeyTest_305, BoundaryConditions_NextMax_305) {

    uint64_t result = MakeRuneCacheKey(0, 0, false, 127);

    EXPECT_EQ(result, (uint64_t)127 << 17 | (uint64_t)0 << 9 | (uint64_t)0 << 1 | (uint64_t)false);

}



} // namespace re2
