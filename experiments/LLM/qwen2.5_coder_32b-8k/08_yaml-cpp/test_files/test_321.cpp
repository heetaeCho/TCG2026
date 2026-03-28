#include <gtest/gtest.h>

#include <yaml-cpp/src/contrib/dragonbox.h>



namespace YAML { namespace jkj { namespace dragonbox { namespace detail { namespace log {



using namespace stdr;



TEST_F(DragonboxLogTest_321, FloorLog2Pow10_NormalOperation_321) {

    EXPECT_EQ(floor_log2_pow10<int>(-1233), -4079);

    EXPECT_EQ(floor_log2_pow10<int>(0), 0);

    EXPECT_EQ(floor_log2_pow10<int>(1233), 4086);

}



TEST_F(DragonboxLogTest_321, FloorLog2Pow10_BoundaryConditions_321) {

    EXPECT_EQ(floor_log2_pow10<int>(min_exponent), -4079);

    EXPECT_EQ(floor_log2_pow10<int>(max_exponent), 4086);

}



TEST_F(DragonboxLogTest_321, FloorLog2Pow10_ExceptionalCases_321) {

    // No exceptional cases observable through the interface as per the provided signature

}



TEST_F(DragonboxLogTest_321, FloorLog2Pow10_VerifyExternalInteractions_321) {

    // No external interactions to verify as the function is pure and stateless

}



} } } } }
