#include <gtest/gtest.h>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox {



using TestType = signed_significand_bits<int>; // Assuming carrier_uint is int for test purposes



class DragonBoxTests_286 : public ::testing::Test {

protected:

    TestType bits;

};



TEST_F(DragonBoxTests_286, HasAllZeroSignificandBits_AllZeros_286) {

    TestType all_zeros(0);

    EXPECT_TRUE(all_zeros.has_all_zero_significand_bits());

}



TEST_F(DragonBoxTests_286, HasAllZeroSignificandBits_NotAllZeros_286) {

    TestType not_all_zeros(1);

    EXPECT_FALSE(not_all_zeros.has_all_zero_significand_bits());

}



TEST_F(DragonBoxTests_286, BoundaryCondition_ZeroPattern_286) {

    TestType boundary_case(0x7FFFFFFF); // Assuming 32-bit integer for demonstration

    EXPECT_TRUE(boundary_case.has_all_zero_significand_bits());

}



TEST_F(DragonBoxTests_286, BoundaryCondition_MaxPattern_286) {

    TestType boundary_case(0xFFFFFFFF); // All bits set

    EXPECT_FALSE(boundary_case.has_all_zero_significand_bits());

}



}}} // namespace YAML::jkj::dragonbox
