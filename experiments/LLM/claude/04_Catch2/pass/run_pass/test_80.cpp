#include <gtest/gtest.h>
#include <string>
#include <type_traits>
#include <cstdint>

// Include the header under test
#include "catch2/catch_tostring.hpp"

// Define some test enums for use in the tests
enum class SmallEnum : int8_t {
    Negative = -1,
    Zero = 0,
    One = 1,
    Max = 127,
    Min = -128
};

enum class IntEnum : int {
    Negative = -100,
    Zero = 0,
    Positive = 42,
    Large = 100000
};

enum class UnsignedEnum : unsigned int {
    Zero = 0,
    One = 1,
    Large = 999999
};

enum class UInt8Enum : uint8_t {
    Zero = 0,
    Mid = 128,
    Max = 255
};

enum class Int64Enum : int64_t {
    NegativeLarge = -1000000000LL,
    Zero = 0,
    PositiveLarge = 1000000000LL
};

enum class BoolUnderlyingEnum : bool {
    False = false,
    True = true
};

// Unscoped enum with explicit underlying type
enum UnscopedEnum : int {
    UnscopedNeg = -5,
    UnscopedZero = 0,
    UnscopedPos = 10
};

// Test fixture
class ConvertUnknownEnumToStringTest_80 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: IntEnum with zero value
TEST_F(ConvertUnknownEnumToStringTest_80, IntEnumZero_80) {
    std::string result = Catch::Detail::convertUnknownEnumToString(IntEnum::Zero);
    EXPECT_EQ(result, "0");
}

// Test: IntEnum with positive value
TEST_F(ConvertUnknownEnumToStringTest_80, IntEnumPositive_80) {
    std::string result = Catch::Detail::convertUnknownEnumToString(IntEnum::Positive);
    EXPECT_EQ(result, "42");
}

// Test: IntEnum with negative value
TEST_F(ConvertUnknownEnumToStringTest_80, IntEnumNegative_80) {
    std::string result = Catch::Detail::convertUnknownEnumToString(IntEnum::Negative);
    EXPECT_EQ(result, "-100");
}

// Test: IntEnum with large value
TEST_F(ConvertUnknownEnumToStringTest_80, IntEnumLarge_80) {
    std::string result = Catch::Detail::convertUnknownEnumToString(IntEnum::Large);
    EXPECT_EQ(result, "100000");
}

// Test: UnsignedEnum with zero
TEST_F(ConvertUnknownEnumToStringTest_80, UnsignedEnumZero_80) {
    std::string result = Catch::Detail::convertUnknownEnumToString(UnsignedEnum::Zero);
    EXPECT_EQ(result, "0");
}

// Test: UnsignedEnum with one
TEST_F(ConvertUnknownEnumToStringTest_80, UnsignedEnumOne_80) {
    std::string result = Catch::Detail::convertUnknownEnumToString(UnsignedEnum::One);
    EXPECT_EQ(result, "1");
}

// Test: UnsignedEnum with large value
TEST_F(ConvertUnknownEnumToStringTest_80, UnsignedEnumLarge_80) {
    std::string result = Catch::Detail::convertUnknownEnumToString(UnsignedEnum::Large);
    EXPECT_EQ(result, "999999");
}

// Test: SmallEnum (int8_t underlying) with zero
TEST_F(ConvertUnknownEnumToStringTest_80, SmallEnumZero_80) {
    std::string result = Catch::Detail::convertUnknownEnumToString(SmallEnum::Zero);
    EXPECT_EQ(result, "0");
}

// Test: SmallEnum (int8_t underlying) with negative value
TEST_F(ConvertUnknownEnumToStringTest_80, SmallEnumNegative_80) {
    std::string result = Catch::Detail::convertUnknownEnumToString(SmallEnum::Negative);
    EXPECT_EQ(result, "-1");
}

// Test: SmallEnum boundary max (127)
TEST_F(ConvertUnknownEnumToStringTest_80, SmallEnumMax_80) {
    std::string result = Catch::Detail::convertUnknownEnumToString(SmallEnum::Max);
    EXPECT_EQ(result, "127");
}

// Test: SmallEnum boundary min (-128)
TEST_F(ConvertUnknownEnumToStringTest_80, SmallEnumMin_80) {
    std::string result = Catch::Detail::convertUnknownEnumToString(SmallEnum::Min);
    EXPECT_EQ(result, "-128");
}

// Test: UInt8Enum with zero
TEST_F(ConvertUnknownEnumToStringTest_80, UInt8EnumZero_80) {
    std::string result = Catch::Detail::convertUnknownEnumToString(UInt8Enum::Zero);
    EXPECT_EQ(result, "0");
}

// Test: UInt8Enum boundary max (255)
TEST_F(ConvertUnknownEnumToStringTest_80, UInt8EnumMax_80) {
    std::string result = Catch::Detail::convertUnknownEnumToString(UInt8Enum::Max);
    EXPECT_EQ(result, "255");
}

// Test: UInt8Enum mid value (128)
TEST_F(ConvertUnknownEnumToStringTest_80, UInt8EnumMid_80) {
    std::string result = Catch::Detail::convertUnknownEnumToString(UInt8Enum::Mid);
    EXPECT_EQ(result, "128");
}

// Test: Int64Enum with large negative value
TEST_F(ConvertUnknownEnumToStringTest_80, Int64EnumNegativeLarge_80) {
    std::string result = Catch::Detail::convertUnknownEnumToString(Int64Enum::NegativeLarge);
    EXPECT_EQ(result, "-1000000000");
}

// Test: Int64Enum with zero
TEST_F(ConvertUnknownEnumToStringTest_80, Int64EnumZero_80) {
    std::string result = Catch::Detail::convertUnknownEnumToString(Int64Enum::Zero);
    EXPECT_EQ(result, "0");
}

// Test: Int64Enum with large positive value
TEST_F(ConvertUnknownEnumToStringTest_80, Int64EnumPositiveLarge_80) {
    std::string result = Catch::Detail::convertUnknownEnumToString(Int64Enum::PositiveLarge);
    EXPECT_EQ(result, "1000000000");
}

// Test: Unscoped enum with explicit underlying type
TEST_F(ConvertUnknownEnumToStringTest_80, UnscopedEnumZero_80) {
    std::string result = Catch::Detail::convertUnknownEnumToString(UnscopedZero);
    EXPECT_EQ(result, "0");
}

// Test: Unscoped enum negative value
TEST_F(ConvertUnknownEnumToStringTest_80, UnscopedEnumNegative_80) {
    std::string result = Catch::Detail::convertUnknownEnumToString(UnscopedNeg);
    EXPECT_EQ(result, "-5");
}

// Test: Unscoped enum positive value
TEST_F(ConvertUnknownEnumToStringTest_80, UnscopedEnumPositive_80) {
    std::string result = Catch::Detail::convertUnknownEnumToString(UnscopedPos);
    EXPECT_EQ(result, "10");
}

// Test: Result is a non-empty string for any enum value
TEST_F(ConvertUnknownEnumToStringTest_80, ResultIsNonEmpty_80) {
    std::string result = Catch::Detail::convertUnknownEnumToString(IntEnum::Positive);
    EXPECT_FALSE(result.empty());
}

// Test: Consistency - calling twice with same value yields same result
TEST_F(ConvertUnknownEnumToStringTest_80, ConsistentResults_80) {
    std::string result1 = Catch::Detail::convertUnknownEnumToString(IntEnum::Positive);
    std::string result2 = Catch::Detail::convertUnknownEnumToString(IntEnum::Positive);
    EXPECT_EQ(result1, result2);
}

// Test: Different enum values produce different strings
TEST_F(ConvertUnknownEnumToStringTest_80, DifferentValuesDifferentStrings_80) {
    std::string result1 = Catch::Detail::convertUnknownEnumToString(IntEnum::Zero);
    std::string result2 = Catch::Detail::convertUnknownEnumToString(IntEnum::Positive);
    EXPECT_NE(result1, result2);
}
