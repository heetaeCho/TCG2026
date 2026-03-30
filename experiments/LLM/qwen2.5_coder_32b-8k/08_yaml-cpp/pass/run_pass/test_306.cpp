#include <gtest/gtest.h>

#include <cstdint>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"



namespace YAML {

namespace jkj {

namespace dragonbox {

namespace detail {

namespace wuint {



using namespace stdr;



class Umul64Test_306 : public ::testing::Test {};



TEST_F(Umul64Test_306, NormalOperation_306) {

    uint_least64_t result = umul64(12345, 6789);

    EXPECT_EQ(result, 83810205ULL);

}



TEST_F(Umul64Test_306, BoundaryCondition_MaxUint32_306) {

    uint_least64_t result = umul64(UINT32_MAX, UINT32_MAX);

    EXPECT_EQ(result, 18446744073709551615ULL);

}



TEST_F(Umul64Test_306, BoundaryCondition_Zero_306) {

    uint_least64_t result = umul64(0, UINT32_MAX);

    EXPECT_EQ(result, 0ULL);

}



TEST_F(Umul64Test_306, BoundaryCondition_One_306) {

    uint_least64_t result = umul64(1, UINT32_MAX);

    EXPECT_EQ(result, UINT32_MAX);

}



TEST_F(Umul64Test_306, MixedBoundaryConditions_306) {

    uint_least64_t result = umul64(UINT32_MAX, 0);

    EXPECT_EQ(result, 0ULL);



    result = umul64(0, 1);

    EXPECT_EQ(result, 0ULL);

}



} // namespace wuint

} // namespace detail

} // namespace dragonbox

} // namespace jkj

} // namespace YAML
