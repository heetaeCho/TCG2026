#include <gtest/gtest.h>
#include <cstdint>
#include <limits>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

using YAML::jkj::dragonbox::detail::log::floor_log2;

// ==================== Normal Operation Tests ====================

TEST(FloorLog2Test_315, ReturnsZeroForOne_315) {
    EXPECT_EQ(floor_log2<unsigned>(1), 0);
}

TEST(FloorLog2Test_315, ReturnsOneForTwo_315) {
    EXPECT_EQ(floor_log2<unsigned>(2), 1);
}

TEST(FloorLog2Test_315, ReturnsOneForThree_315) {
    EXPECT_EQ(floor_log2<unsigned>(3), 1);
}

TEST(FloorLog2Test_315, ReturnsTwoForFour_315) {
    EXPECT_EQ(floor_log2<unsigned>(4), 2);
}

TEST(FloorLog2Test_315, ReturnsTwoForFive_315) {
    EXPECT_EQ(floor_log2<unsigned>(5), 2);
}

TEST(FloorLog2Test_315, ReturnsTwoForSeven_315) {
    EXPECT_EQ(floor_log2<unsigned>(7), 2);
}

TEST(FloorLog2Test_315, ReturnsThreeForEight_315) {
    EXPECT_EQ(floor_log2<unsigned>(8), 3);
}

TEST(FloorLog2Test_315, ReturnsThreeForFifteen_315) {
    EXPECT_EQ(floor_log2<unsigned>(15), 3);
}

TEST(FloorLog2Test_315, ReturnsFourForSixteen_315) {
    EXPECT_EQ(floor_log2<unsigned>(16), 4);
}

TEST(FloorLog2Test_315, ReturnsFourForThirtyOne_315) {
    EXPECT_EQ(floor_log2<unsigned>(31), 4);
}

TEST(FloorLog2Test_315, ReturnsFiveForThirtyTwo_315) {
    EXPECT_EQ(floor_log2<unsigned>(32), 5);
}

TEST(FloorLog2Test_315, ReturnsSixForSixtyFour_315) {
    EXPECT_EQ(floor_log2<unsigned>(64), 6);
}

TEST(FloorLog2Test_315, ReturnsNineFor512_315) {
    EXPECT_EQ(floor_log2<unsigned>(512), 9);
}

TEST(FloorLog2Test_315, ReturnsTenFor1024_315) {
    EXPECT_EQ(floor_log2<unsigned>(1024), 10);
}

// ==================== Boundary Condition Tests ====================

TEST(FloorLog2Test_315, ReturnsNegativeOneForZero_315) {
    EXPECT_EQ(floor_log2<unsigned>(0), -1);
}

TEST(FloorLog2Test_315, MaxUint32_315) {
    constexpr unsigned max_val = std::numeric_limits<unsigned>::max();
    // For 32-bit unsigned, max is 2^32 - 1, so floor_log2 = 31
    EXPECT_EQ(floor_log2<unsigned>(max_val), static_cast<int>(sizeof(unsigned) * 8 - 1));
}

TEST(FloorLog2Test_315, MaxUint64_315) {
    constexpr uint64_t max_val = std::numeric_limits<uint64_t>::max();
    EXPECT_EQ(floor_log2<uint64_t>(max_val), 63);
}

TEST(FloorLog2Test_315, Uint64Zero_315) {
    EXPECT_EQ(floor_log2<uint64_t>(0), -1);
}

TEST(FloorLog2Test_315, Uint64One_315) {
    EXPECT_EQ(floor_log2<uint64_t>(1), 0);
}

TEST(FloorLog2Test_315, Uint64LargePowerOfTwo_315) {
    EXPECT_EQ(floor_log2<uint64_t>(1ULL << 40), 40);
}

TEST(FloorLog2Test_315, Uint64LargePowerOfTwoMinusOne_315) {
    EXPECT_EQ(floor_log2<uint64_t>((1ULL << 40) - 1), 39);
}

TEST(FloorLog2Test_315, Uint64LargePowerOfTwoPlusOne_315) {
    EXPECT_EQ(floor_log2<uint64_t>((1ULL << 40) + 1), 40);
}

// ==================== Tests with Different Unsigned Types ====================

TEST(FloorLog2Test_315, Uint8Max_315) {
    EXPECT_EQ(floor_log2<uint8_t>(255), 7);
}

TEST(FloorLog2Test_315, Uint8Zero_315) {
    EXPECT_EQ(floor_log2<uint8_t>(0), -1);
}

TEST(FloorLog2Test_315, Uint8One_315) {
    EXPECT_EQ(floor_log2<uint8_t>(1), 0);
}

TEST(FloorLog2Test_315, Uint8PowerOfTwo_315) {
    EXPECT_EQ(floor_log2<uint8_t>(128), 7);
}

TEST(FloorLog2Test_315, Uint16Max_315) {
    EXPECT_EQ(floor_log2<uint16_t>(65535), 15);
}

TEST(FloorLog2Test_315, Uint16PowerOfTwo_315) {
    EXPECT_EQ(floor_log2<uint16_t>(256), 8);
}

TEST(FloorLog2Test_315, Uint32Max_315) {
    EXPECT_EQ(floor_log2<uint32_t>(std::numeric_limits<uint32_t>::max()), 31);
}

TEST(FloorLog2Test_315, Uint32PowerOfTwo_315) {
    EXPECT_EQ(floor_log2<uint32_t>(1U << 20), 20);
}

// ==================== Constexpr Verification Tests ====================

TEST(FloorLog2Test_315, ConstexprZero_315) {
    constexpr int result = floor_log2<unsigned>(0);
    EXPECT_EQ(result, -1);
}

TEST(FloorLog2Test_315, ConstexprOne_315) {
    constexpr int result = floor_log2<unsigned>(1);
    EXPECT_EQ(result, 0);
}

TEST(FloorLog2Test_315, ConstexprPowerOfTwo_315) {
    constexpr int result = floor_log2<unsigned>(1024);
    EXPECT_EQ(result, 10);
}

TEST(FloorLog2Test_315, ConstexprNonPowerOfTwo_315) {
    constexpr int result = floor_log2<unsigned>(1000);
    EXPECT_EQ(result, 9);
}

// ==================== Sequential Values Tests ====================

TEST(FloorLog2Test_315, SequentialValuesOneToSixteen_315) {
    // Values and expected floor_log2 results
    // 1 -> 0, 2 -> 1, 3 -> 1, 4 -> 2, 5 -> 2, 6 -> 2, 7 -> 2, 8 -> 3
    // 9 -> 3, 10 -> 3, 11 -> 3, 12 -> 3, 13 -> 3, 14 -> 3, 15 -> 3, 16 -> 4
    int expected[] = {0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4};
    for (unsigned i = 1; i <= 16; ++i) {
        EXPECT_EQ(floor_log2<unsigned>(i), expected[i - 1])
            << "Failed for n = " << i;
    }
}

// ==================== All Powers of Two for uint32_t ====================

TEST(FloorLog2Test_315, AllPowersOfTwoUint32_315) {
    for (int exp = 0; exp < 32; ++exp) {
        uint32_t val = 1U << exp;
        EXPECT_EQ(floor_log2<uint32_t>(val), exp)
            << "Failed for 2^" << exp;
    }
}

// ==================== All Powers of Two Minus One for uint32_t ====================

TEST(FloorLog2Test_315, AllPowersOfTwoMinusOneUint32_315) {
    for (int exp = 1; exp < 32; ++exp) {
        uint32_t val = (1U << exp) - 1;
        EXPECT_EQ(floor_log2<uint32_t>(val), exp - 1)
            << "Failed for (2^" << exp << ") - 1 = " << val;
    }
}
