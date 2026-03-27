#include <gtest/gtest.h>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox { namespace detail { namespace div {



template<int N, class UInt, UInt n_max>

using DivideByPow10 = decltype(divide_by_pow10<N, UInt, n_max>);



TEST_F(DivideByPow10Test_327, NormalOperation_UInt32_N1_327) {

    EXPECT_EQ(divide_by_pow10<1, std::uint_least32_t, UINT32_C(1073741828)>(UINT32_C(1073741828)), UINT32_C(107374182));

}



TEST_F(DivideByPow10Test_327, NormalOperation_UInt64_N1_327) {

    EXPECT_EQ(divide_by_pow10<1, std::uint_least64_t, UINT64_C(4611686018427387908)>(UINT64_C(4611686018427387908)), UINT64_C(461168601842738790));

}



TEST_F(DivideByPow10Test_327, NormalOperation_UInt32_N2_327) {

    EXPECT_EQ(divide_by_pow10<2, std::uint_least32_t, UINT32_C(4294967295)>(UINT32_C(4294967295)), UINT32_C(10));

}



TEST_F(DivideByPow10Test_327, NormalOperation_UInt64_N3_327) {

    EXPECT_EQ(divide_by_pow10<3, std::uint_least64_t, UINT64_C(15534100272597517998)>(UINT64_C(15534100272597517998)), UINT64_C(15534100272597517));

}



TEST_F(DivideByPow10Test_327, BoundaryCondition_UInt32_N1_Max_327) {

    EXPECT_EQ(divide_by_pow10<1, std::uint_least32_t, UINT32_C(1073741828)>(UINT32_C(1073741828)), UINT32_C(107374182));

}



TEST_F(DivideByPow10Test_327, BoundaryCondition_UInt64_N1_Max_327) {

    EXPECT_EQ(divide_by_pow10<1, std::uint_least64_t, UINT64_C(4611686018427387908)>(UINT64_C(4611686018427387908)), UINT64_C(461168601842738790));

}



TEST_F(DivideByPow10Test_327, BoundaryCondition_UInt32_N2_Max_327) {

    EXPECT_EQ(divide_by_pow10<2, std::uint_least32_t, UINT32_C(4294967295)>(UINT32_C(4294967295)), UINT32_C(10));

}



TEST_F(DivideByPow10Test_327, BoundaryCondition_UInt64_N3_Max_327) {

    EXPECT_EQ(divide_by_pow10<3, std::uint_least64_t, UINT64_C(15534100272597517998)>(UINT64_C(15534100272597517998)), UINT64_C(15534100272597517));

}



TEST_F(DivideByPow10Test_327, BoundaryCondition_UInt32_N1_Zero_327) {

    EXPECT_EQ(divide_by_pow10<1, std::uint_least32_t, UINT32_C(1073741828)>(UINT32_C(0)), UINT32_C(0));

}



TEST_F(DivideByPow10Test_327, BoundaryCondition_UInt64_N1_Zero_327) {

    EXPECT_EQ(divide_by_pow10<1, std::uint_least64_t, UINT64_C(4611686018427387908)>(UINT64_C(0)), UINT64_C(0));

}



TEST_F(DivideByPow10Test_327, BoundaryCondition_UInt32_N2_Zero_327) {

    EXPECT_EQ(divide_by_pow10<2, std::uint_least32_t, UINT32_C(4294967295)>(UINT32_C(0)), UINT32_C(0));

}



TEST_F(DivideByPow10Test_327, BoundaryCondition_UInt64_N3_Zero_327) {

    EXPECT_EQ(divide_by_pow10<3, std::uint_least64_t, UINT64_C(15534100272597517998)>(UINT64_C(0)), UINT64_C(0));

}



TEST_F(DivideByPow10Test_327, ExceptionalCase_UInt32_N1_OutOfRange_327) {

    EXPECT_THROW(divide_by_pow10<1, std::uint_least32_t, UINT32_C(1073741828)>(UINT32_C(1073741829)), ...);

}



TEST_F(DivideByPow10Test_327, ExceptionalCase_UInt64_N1_OutOfRange_327) {

    EXPECT_THROW(divide_by_pow10<1, std::uint_least64_t, UINT64_C(4611686018427387908)>(UINT64_C(4611686018427387909)), ...);

}



TEST_F(DivideByPow10Test_327, ExceptionalCase_UInt32_N2_OutOfRange_327) {

    EXPECT_THROW(divide_by_pow10<2, std::uint_least32_t, UINT32_C(4294967295)>(UINT32_C(4294967296)), ...);

}



TEST_F(DivideByPow10Test_327, ExceptionalCase_UInt64_N3_OutOfRange_327) {

    EXPECT_THROW(divide_by_pow10<3, std::uint_least64_t, UINT64_C(15534100272597517998)>(UINT64_C(15534100272597517999)), ...);

}



}}}}} // namespace YAML::jkj::dragonbox::detail::div

```


