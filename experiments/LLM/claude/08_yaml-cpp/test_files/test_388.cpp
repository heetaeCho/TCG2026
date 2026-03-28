#include <gtest/gtest.h>
#include <cstdint>
#include <type_traits>
#include <limits>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using AwayFromZero = YAML::jkj::dragonbox::policy::binary_to_decimal_rounding::away_from_zero;

// Test fixture
class AwayFromZeroTest_388 : public ::testing::Test {
protected:
    AwayFromZero policy;
};

// Normal operation tests

TEST_F(AwayFromZeroTest_388, PreferRoundDownReturnsFalseForUint32Zero_388) {
    uint32_t value = 0;
    EXPECT_FALSE(AwayFromZero::prefer_round_down(value));
}

TEST_F(AwayFromZeroTest_388, PreferRoundDownReturnsFalseForUint32One_388) {
    uint32_t value = 1;
    EXPECT_FALSE(AwayFromZero::prefer_round_down(value));
}

TEST_F(AwayFromZeroTest_388, PreferRoundDownReturnsFalseForUint32Arbitrary_388) {
    uint32_t value = 42;
    EXPECT_FALSE(AwayFromZero::prefer_round_down(value));
}

TEST_F(AwayFromZeroTest_388, PreferRoundDownReturnsFalseForUint64Zero_388) {
    uint64_t value = 0;
    EXPECT_FALSE(AwayFromZero::prefer_round_down(value));
}

TEST_F(AwayFromZeroTest_388, PreferRoundDownReturnsFalseForUint64One_388) {
    uint64_t value = 1;
    EXPECT_FALSE(AwayFromZero::prefer_round_down(value));
}

TEST_F(AwayFromZeroTest_388, PreferRoundDownReturnsFalseForUint64Arbitrary_388) {
    uint64_t value = 123456789ULL;
    EXPECT_FALSE(AwayFromZero::prefer_round_down(value));
}

// Boundary condition tests

TEST_F(AwayFromZeroTest_388, PreferRoundDownReturnsFalseForUint32Max_388) {
    uint32_t value = std::numeric_limits<uint32_t>::max();
    EXPECT_FALSE(AwayFromZero::prefer_round_down(value));
}

TEST_F(AwayFromZeroTest_388, PreferRoundDownReturnsFalseForUint64Max_388) {
    uint64_t value = std::numeric_limits<uint64_t>::max();
    EXPECT_FALSE(AwayFromZero::prefer_round_down(value));
}

TEST_F(AwayFromZeroTest_388, PreferRoundDownReturnsFalseForUint16Max_388) {
    uint16_t value = std::numeric_limits<uint16_t>::max();
    EXPECT_FALSE(AwayFromZero::prefer_round_down(value));
}

TEST_F(AwayFromZeroTest_388, PreferRoundDownReturnsFalseForUint8Max_388) {
    uint8_t value = std::numeric_limits<uint8_t>::max();
    EXPECT_FALSE(AwayFromZero::prefer_round_down(value));
}

TEST_F(AwayFromZeroTest_388, PreferRoundDownReturnsFalseForUint32MidValue_388) {
    uint32_t value = std::numeric_limits<uint32_t>::max() / 2;
    EXPECT_FALSE(AwayFromZero::prefer_round_down(value));
}

TEST_F(AwayFromZeroTest_388, PreferRoundDownReturnsFalseForUint64MidValue_388) {
    uint64_t value = std::numeric_limits<uint64_t>::max() / 2;
    EXPECT_FALSE(AwayFromZero::prefer_round_down(value));
}

// Constexpr test

TEST_F(AwayFromZeroTest_388, PreferRoundDownIsConstexpr_388) {
    constexpr bool result32 = AwayFromZero::prefer_round_down(uint32_t{0});
    constexpr bool result64 = AwayFromZero::prefer_round_down(uint64_t{0});
    EXPECT_FALSE(result32);
    EXPECT_FALSE(result64);
}

// Noexcept test

TEST_F(AwayFromZeroTest_388, PreferRoundDownIsNoexcept_388) {
    uint32_t val32 = 0;
    uint64_t val64 = 0;
    EXPECT_TRUE(noexcept(AwayFromZero::prefer_round_down(val32)));
    EXPECT_TRUE(noexcept(AwayFromZero::prefer_round_down(val64)));
}

// Test that result is always false regardless of input value

TEST_F(AwayFromZeroTest_388, PreferRoundDownAlwaysReturnsFalseForVariousUint32Values_388) {
    for (uint32_t v : {0u, 1u, 2u, 100u, 1000u, 65535u, 1000000u}) {
        EXPECT_FALSE(AwayFromZero::prefer_round_down(v)) 
            << "Failed for value: " << v;
    }
}

TEST_F(AwayFromZeroTest_388, PreferRoundDownAlwaysReturnsFalseForVariousUint64Values_388) {
    for (uint64_t v : {0ULL, 1ULL, 2ULL, 1000ULL, 
                       (uint64_t)std::numeric_limits<uint32_t>::max(),
                       std::numeric_limits<uint64_t>::max()}) {
        EXPECT_FALSE(AwayFromZero::prefer_round_down(v))
            << "Failed for value: " << v;
    }
}

// Power of two values

TEST_F(AwayFromZeroTest_388, PreferRoundDownReturnsFalseForPowersOfTwo_388) {
    for (int i = 0; i < 32; ++i) {
        uint32_t value = uint32_t{1} << i;
        EXPECT_FALSE(AwayFromZero::prefer_round_down(value))
            << "Failed for 2^" << i;
    }
}

TEST_F(AwayFromZeroTest_388, PreferRoundDownReturnsFalseForPowersOfTwo64_388) {
    for (int i = 0; i < 64; ++i) {
        uint64_t value = uint64_t{1} << i;
        EXPECT_FALSE(AwayFromZero::prefer_round_down(value))
            << "Failed for 2^" << i;
    }
}

} // namespace
