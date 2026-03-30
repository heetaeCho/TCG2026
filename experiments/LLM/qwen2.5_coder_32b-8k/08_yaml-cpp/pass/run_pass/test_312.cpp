#include <gtest/gtest.h>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"



namespace YAML {

namespace jkj {

namespace dragonbox {

namespace detail {

namespace wuint {



class Umul96Lower64Test : public ::testing::Test {};



TEST_F(Umul96Lower64Test, NormalOperation_312) {

    stdr::uint_least64_t result = umul96_lower64(10, 20);

    EXPECT_EQ(result, 200);

}



TEST_F(Umul96Lower64Test, BoundaryConditionZeroX_312) {

    stdr::uint_least64_t result = umul96_lower64(0, UINT64_C(0xffffffffffffffff));

    EXPECT_EQ(result, 0);

}



TEST_F(Umul96Lower64Test, BoundaryConditionZeroY_312) {

    stdr::uint_least64_t result = umul96_lower64(UINT32_C(0xffffffff), 0);

    EXPECT_EQ(result, 0);

}



TEST_F(Umul96Lower64Test, BoundaryConditionMaxX_312) {

    stdr::uint_least64_t result = umul96_lower64(UINT32_C(0xffffffff), 2);

    EXPECT_EQ(result, UINT64_C(0xfffffffe));

}



TEST_F(Umul96Lower64Test, BoundaryConditionMaxY_312) {

    stdr::uint_least64_t result = umul96_lower64(2, UINT64_C(0xffffffffffffffff));

    EXPECT_EQ(result, 0);

}



TEST_F(Umul96Lower64Test, LargeValues_312) {

    stdr::uint_least64_t result = umul96_lower64(UINT32_C(0x80000000), UINT64_C(0x8000000000000000));

    EXPECT_EQ(result, 0);

}



TEST_F(Umul96Lower64Test, OverflowCase_312) {

    stdr::uint_least64_t result = umul96_lower64(UINT32_C(0xffffffff), UINT64_C(0xffffffffffffffff));

    EXPECT_EQ(result, UINT64_C(0xfffffffffffffffe));

}



}  // namespace wuint

}  // namespace detail

}  // namespace dragonbox

}  // namespace jkj

}  // namespace YAML
