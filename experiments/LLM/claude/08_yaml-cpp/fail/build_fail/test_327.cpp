#include <gtest/gtest.h>
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

using namespace YAML::jkj::dragonbox::detail::div;

// Tests for divide_by_pow10 with uint32_t, N=1
class DivideByPow10_Uint32_N1_Test_327 : public ::testing::Test {};

TEST_F(DivideByPow10_Uint32_N1_Test_327, Zero_327) {
    auto result = divide_by_pow10<1, stdr::uint_least32_t, UINT32_C(1073741828)>(0);
    EXPECT_EQ(result, 0u);
}

TEST_F(DivideByPow10_Uint32_N1_Test_327, Ten_327) {
    auto result = divide_by_pow10<1, stdr::uint_least32_t, UINT32_C(1073741828)>(10);
    EXPECT_EQ(result, 1u);
}

TEST_F(DivideByPow10_Uint32_N1_Test_327, Nine_327) {
    auto result = divide_by_pow10<1, stdr::uint_least32_t, UINT32_C(1073741828)>(9);
    EXPECT_EQ(result, 0u);
}

TEST_F(DivideByPow10_Uint32_N1_Test_327, Hundred_327) {
    auto result = divide_by_pow10<1, stdr::uint_least32_t, UINT32_C(1073741828)>(100);
    EXPECT_EQ(result, 10u);
}

TEST_F(DivideByPow10_Uint32_N1_Test_327, One_327) {
    auto result = divide_by_pow10<1, stdr::uint_least32_t, UINT32_C(1073741828)>(1);
    EXPECT_EQ(result, 0u);
}

TEST_F(DivideByPow10_Uint32_N1_Test_327, LargeValue_327) {
    auto result = divide_by_pow10<1, stdr::uint_least32_t, UINT32_C(1073741828)>(1000000);
    EXPECT_EQ(result, 100000u);
}

TEST_F(DivideByPow10_Uint32_N1_Test_327, MaxAllowed_327) {
    auto result = divide_by_pow10<1, stdr::uint_least32_t, UINT32_C(1073741828)>(UINT32_C(1073741828));
    EXPECT_EQ(result, UINT32_C(1073741828) / 10);
}

TEST_F(DivideByPow10_Uint32_N1_Test_327, Eleven_327) {
    auto result = divide_by_pow10<1, stdr::uint_least32_t, UINT32_C(1073741828)>(11);
    EXPECT_EQ(result, 1u);
}

TEST_F(DivideByPow10_Uint32_N1_Test_327, NinetyNine_327) {
    auto result = divide_by_pow10<1, stdr::uint_least32_t, UINT32_C(1073741828)>(99);
    EXPECT_EQ(result, 9u);
}

// Tests for divide_by_pow10 with uint32_t, N=2
class DivideByPow10_Uint32_N2_Test_327 : public ::testing::Test {};

TEST_F(DivideByPow10_Uint32_N2_Test_327, Zero_327) {
    auto result = divide_by_pow10<2, stdr::uint_least32_t, UINT32_C(4294967295)>(0);
    EXPECT_EQ(result, 0u);
}

TEST_F(DivideByPow10_Uint32_N2_Test_327, Hundred_327) {
    auto result = divide_by_pow10<2, stdr::uint_least32_t, UINT32_C(4294967295)>(100);
    EXPECT_EQ(result, 1u);
}

TEST_F(DivideByPow10_Uint32_N2_Test_327, NinetyNine_327) {
    auto result = divide_by_pow10<2, stdr::uint_least32_t, UINT32_C(4294967295)>(99);
    EXPECT_EQ(result, 0u);
}

TEST_F(DivideByPow10_Uint32_N2_Test_327, Thousand_327) {
    auto result = divide_by_pow10<2, stdr::uint_least32_t, UINT32_C(4294967295)>(1000);
    EXPECT_EQ(result, 10u);
}

TEST_F(DivideByPow10_Uint32_N2_Test_327, MaxUint32_327) {
    stdr::uint_least32_t n = UINT32_C(4294967295);
    auto result = divide_by_pow10<2, stdr::uint_least32_t, UINT32_C(4294967295)>(n);
    EXPECT_EQ(result, n / 100);
}

TEST_F(DivideByPow10_Uint32_N2_Test_327, One_327) {
    auto result = divide_by_pow10<2, stdr::uint_least32_t, UINT32_C(4294967295)>(1);
    EXPECT_EQ(result, 0u);
}

TEST_F(DivideByPow10_Uint32_N2_Test_327, TenThousand_327) {
    auto result = divide_by_pow10<2, stdr::uint_least32_t, UINT32_C(4294967295)>(10000);
    EXPECT_EQ(result, 100u);
}

// Tests for divide_by_pow10 with uint64_t, N=1
class DivideByPow10_Uint64_N1_Test_327 : public ::testing::Test {};

TEST_F(DivideByPow10_Uint64_N1_Test_327, Zero_327) {
    auto result = divide_by_pow10<1, stdr::uint_least64_t, UINT64_C(4611686018427387908)>(0);
    EXPECT_EQ(result, 0u);
}

TEST_F(DivideByPow10_Uint64_N1_Test_327, Ten_327) {
    auto result = divide_by_pow10<1, stdr::uint_least64_t, UINT64_C(4611686018427387908)>(10);
    EXPECT_EQ(result, 1u);
}

TEST_F(DivideByPow10_Uint64_N1_Test_327, Nine_327) {
    auto result = divide_by_pow10<1, stdr::uint_least64_t, UINT64_C(4611686018427387908)>(9);
    EXPECT_EQ(result, 0u);
}

TEST_F(DivideByPow10_Uint64_N1_Test_327, LargeValue_327) {
    stdr::uint_least64_t n = UINT64_C(1000000000000);
    auto result = divide_by_pow10<1, stdr::uint_least64_t, UINT64_C(4611686018427387908)>(n);
    EXPECT_EQ(result, UINT64_C(100000000000));
}

TEST_F(DivideByPow10_Uint64_N1_Test_327, MaxAllowed_327) {
    stdr::uint_least64_t n = UINT64_C(4611686018427387908);
    auto result = divide_by_pow10<1, stdr::uint_least64_t, UINT64_C(4611686018427387908)>(n);
    EXPECT_EQ(result, n / 10);
}

TEST_F(DivideByPow10_Uint64_N1_Test_327, One_327) {
    auto result = divide_by_pow10<1, stdr::uint_least64_t, UINT64_C(4611686018427387908)>(1);
    EXPECT_EQ(result, 0u);
}

// Tests for divide_by_pow10 with uint64_t, N=3
class DivideByPow10_Uint64_N3_Test_327 : public ::testing::Test {};

TEST_F(DivideByPow10_Uint64_N3_Test_327, Zero_327) {
    auto result = divide_by_pow10<3, stdr::uint_least64_t, UINT64_C(15534100272597517998)>(0);
    EXPECT_EQ(result, 0u);
}

TEST_F(DivideByPow10_Uint64_N3_Test_327, Thousand_327) {
    auto result = divide_by_pow10<3, stdr::uint_least64_t, UINT64_C(15534100272597517998)>(1000);
    EXPECT_EQ(result, 1u);
}

TEST_F(DivideByPow10_Uint64_N3_Test_327, NineHundredNinetyNine_327) {
    auto result = divide_by_pow10<3, stdr::uint_least64_t, UINT64_C(15534100272597517998)>(999);
    EXPECT_EQ(result, 0u);
}

TEST_F(DivideByPow10_Uint64_N3_Test_327, Million_327) {
    auto result = divide_by_pow10<3, stdr::uint_least64_t, UINT64_C(15534100272597517998)>(1000000);
    EXPECT_EQ(result, 1000u);
}

TEST_F(DivideByPow10_Uint64_N3_Test_327, LargeValue_327) {
    stdr::uint_least64_t n = UINT64_C(15534100272597517998);
    auto result = divide_by_pow10<3, stdr::uint_least64_t, UINT64_C(15534100272597517998)>(n);
    EXPECT_EQ(result, n / 1000);
}

TEST_F(DivideByPow10_Uint64_N3_Test_327, One_327) {
    auto result = divide_by_pow10<3, stdr::uint_least64_t, UINT64_C(15534100272597517998)>(1);
    EXPECT_EQ(result, 0u);
}

// Tests for divide_by_pow10 with N=0 (fallback: divide by 10^0 = 1)
class DivideByPow10_N0_Test_327 : public ::testing::Test {};

TEST_F(DivideByPow10_N0_Test_327, Uint32Zero_327) {
    auto result = divide_by_pow10<0, stdr::uint_least32_t, UINT32_C(100)>(42);
    EXPECT_EQ(result, 42u);
}

TEST_F(DivideByPow10_N0_Test_327, Uint64Zero_327) {
    auto result = divide_by_pow10<0, stdr::uint_least64_t, UINT64_C(100)>(42);
    EXPECT_EQ(result, 42u);
}

// Tests for divide_by_pow10 fallback path (higher N values)
class DivideByPow10_Fallback_Test_327 : public ::testing::Test {};

TEST_F(DivideByPow10_Fallback_Test_327, Uint32_N3_327) {
    auto result = divide_by_pow10<3, stdr::uint_least32_t, UINT32_C(4294967295)>(123456);
    EXPECT_EQ(result, 123u);
}

TEST_F(DivideByPow10_Fallback_Test_327, Uint32_N4_327) {
    auto result = divide_by_pow10<4, stdr::uint_least32_t, UINT32_C(4294967295)>(123456);
    EXPECT_EQ(result, 12u);
}

TEST_F(DivideByPow10_Fallback_Test_327, Uint32_N5_327) {
    auto result = divide_by_pow10<5, stdr::uint_least32_t, UINT32_C(4294967295)>(123456);
    EXPECT_EQ(result, 1u);
}

TEST_F(DivideByPow10_Fallback_Test_327, Uint32_N6_327) {
    auto result = divide_by_pow10<6, stdr::uint_least32_t, UINT32_C(4294967295)>(123456);
    EXPECT_EQ(result, 0u);
}

TEST_F(DivideByPow10_Fallback_Test_327, Uint64_N4_327) {
    auto result = divide_by_pow10<4, stdr::uint_least64_t, UINT64_C(18446744073709551615)>(UINT64_C(9876543210));
    EXPECT_EQ(result, UINT64_C(987654));
}

TEST_F(DivideByPow10_Fallback_Test_327, Uint64_N2_327) {
    auto result = divide_by_pow10<2, stdr::uint_least64_t, UINT64_C(18446744073709551615)>(UINT64_C(12345));
    EXPECT_EQ(result, UINT64_C(123));
}

// Boundary tests: values just around the division boundary
class DivideByPow10_Boundary_Test_327 : public ::testing::Test {};

TEST_F(DivideByPow10_Boundary_Test_327, Uint32_N1_JustBelowTen_327) {
    auto result = divide_by_pow10<1, stdr::uint_least32_t, UINT32_C(1073741828)>(9);
    EXPECT_EQ(result, 0u);
}

TEST_F(DivideByPow10_Boundary_Test_327, Uint32_N1_ExactlyTen_327) {
    auto result = divide_by_pow10<1, stdr::uint_least32_t, UINT32_C(1073741828)>(10);
    EXPECT_EQ(result, 1u);
}

TEST_F(DivideByPow10_Boundary_Test_327, Uint32_N1_JustAboveTen_327) {
    auto result = divide_by_pow10<1, stdr::uint_least32_t, UINT32_C(1073741828)>(11);
    EXPECT_EQ(result, 1u);
}

TEST_F(DivideByPow10_Boundary_Test_327, Uint32_N1_Nineteen_327) {
    auto result = divide_by_pow10<1, stdr::uint_least32_t, UINT32_C(1073741828)>(19);
    EXPECT_EQ(result, 1u);
}

TEST_F(DivideByPow10_Boundary_Test_327, Uint32_N1_Twenty_327) {
    auto result = divide_by_pow10<1, stdr::uint_least32_t, UINT32_C(1073741828)>(20);
    EXPECT_EQ(result, 2u);
}

TEST_F(DivideByPow10_Boundary_Test_327, Uint32_N2_JustBelow100_327) {
    auto result = divide_by_pow10<2, stdr::uint_least32_t, UINT32_C(4294967295)>(99);
    EXPECT_EQ(result, 0u);
}

TEST_F(DivideByPow10_Boundary_Test_327, Uint32_N2_Exactly100_327) {
    auto result = divide_by_pow10<2, stdr::uint_least32_t, UINT32_C(4294967295)>(100);
    EXPECT_EQ(result, 1u);
}

TEST_F(DivideByPow10_Boundary_Test_327, Uint32_N2_Exactly199_327) {
    auto result = divide_by_pow10<2, stdr::uint_least32_t, UINT32_C(4294967295)>(199);
    EXPECT_EQ(result, 1u);
}

TEST_F(DivideByPow10_Boundary_Test_327, Uint32_N2_Exactly200_327) {
    auto result = divide_by_pow10<2, stdr::uint_least32_t, UINT32_C(4294967295)>(200);
    EXPECT_EQ(result, 2u);
}

// Consistency tests: compare specialized paths with generic division
class DivideByPow10_Consistency_Test_327 : public ::testing::Test {};

TEST_F(DivideByPow10_Consistency_Test_327, Uint32_N1_MultipleValues_327) {
    for (stdr::uint_least32_t n = 0; n < 10000; n += 7) {
        auto result = divide_by_pow10<1, stdr::uint_least32_t, UINT32_C(1073741828)>(n);
        EXPECT_EQ(result, n / 10) << "Failed for n=" << n;
    }
}

TEST_F(DivideByPow10_Consistency_Test_327, Uint32_N2_MultipleValues_327) {
    for (stdr::uint_least32_t n = 0; n < 100000; n += 37) {
        auto result = divide_by_pow10<2, stdr::uint_least32_t, UINT32_C(4294967295)>(n);
        EXPECT_EQ(result, n / 100) << "Failed for n=" << n;
    }
}

TEST_F(DivideByPow10_Consistency_Test_327, Uint64_N1_MultipleValues_327) {
    for (stdr::uint_least64_t n = 0; n < 10000; n += 7) {
        auto result = divide_by_pow10<1, stdr::uint_least64_t, UINT64_C(4611686018427387908)>(n);
        EXPECT_EQ(result, n / 10) << "Failed for n=" << n;
    }
}

TEST_F(DivideByPow10_Consistency_Test_327, Uint64_N3_MultipleValues_327) {
    for (stdr::uint_least64_t n = 0; n < 1000000; n += 137) {
        auto result = divide_by_pow10<3, stdr::uint_least64_t, UINT64_C(15534100272597517998)>(n);
        EXPECT_EQ(result, n / 1000) << "Failed for n=" << n;
    }
}

// Powers of 10 test
class DivideByPow10_PowersOf10_Test_327 : public ::testing::Test {};

TEST_F(DivideByPow10_PowersOf10_Test_327, Uint32_N1_PowersOf10_327) {
    EXPECT_EQ((divide_by_pow10<1, stdr::uint_least32_t, UINT32_C(1073741828)>(1)), 0u);
    EXPECT_EQ((divide_by_pow10<1, stdr::uint_least32_t, UINT32_C(1073741828)>(10)), 1u);
    EXPECT_EQ((divide_by_pow10<1, stdr::uint_least32_t, UINT32_C(1073741828)>(100)), 10u);
    EXPECT_EQ((divide_by_pow10<1, stdr::uint_least32_t, UINT32_C(1073741828)>(1000)), 100u);
    EXPECT_EQ((divide_by_pow10<1, stdr::uint_least32_t, UINT32_C(1073741828)>(10000)), 1000u);
    EXPECT_EQ((divide_by_pow10<1, stdr::uint_least32_t, UINT32_C(1073741828)>(100000)), 10000u);
    EXPECT_EQ((divide_by_pow10<1, stdr::uint_least32_t, UINT32_C(1073741828)>(1000000)), 100000u);
}

TEST_F(DivideByPow10_PowersOf10_Test_327, Uint32_N2_PowersOf10_327) {
    EXPECT_EQ((divide_by_pow10<2, stdr::uint_least32_t, UINT32_C(4294967295)>(1)), 0u);
    EXPECT_EQ((divide_by_pow10<2, stdr::uint_least32_t, UINT32_C(4294967295)>(10)), 0u);
    EXPECT_EQ((divide_by_pow10<2, stdr::uint_least32_t, UINT32_C(4294967295)>(100)), 1u);
    EXPECT_EQ((divide_by_pow10<2, stdr::uint_least32_t, UINT32_C(4294967295)>(1000)), 10u);
    EXPECT_EQ((divide_by_pow10<2, stdr::uint_least32_t, UINT32_C(4294967295)>(10000)), 100u);
    EXPECT_EQ((divide_by_pow10<2, stdr::uint_least32_t, UINT32_C(4294967295)>(100000)), 1000u);
}
