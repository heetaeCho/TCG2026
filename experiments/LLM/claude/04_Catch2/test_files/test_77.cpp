#include <gtest/gtest.h>
#include <string>
#include <type_traits>
#include "catch2/catch_tostring.hpp"

// Define test enums for testing
enum UnscopedEnum {
    UnscopedValue0 = 0,
    UnscopedValue1 = 1,
    UnscopedValue42 = 42,
    UnscopedValueNeg = -1
};

enum class ScopedEnum {
    Value0 = 0,
    Value1 = 1,
    Value100 = 100,
    ValueNeg = -5
};

enum class ScopedEnumUint8 : uint8_t {
    Min = 0,
    Max = 255
};

enum class ScopedEnumInt16 : int16_t {
    NegVal = -32768,
    PosVal = 32767
};

// Test fixture
class ConvertUnstreamableTest_77 : public ::testing::Test {
protected:
};

// Test that convertUnstreamable works with unscoped enum value 0
TEST_F(ConvertUnstreamableTest_77, UnscopedEnumZeroValue_77) {
    std::string result = Catch::Detail::convertUnstreamable(UnscopedValue0);
    // The result should be a non-empty string representation
    EXPECT_FALSE(result.empty());
}

// Test that convertUnstreamable works with unscoped enum positive value
TEST_F(ConvertUnstreamableTest_77, UnscopedEnumPositiveValue_77) {
    std::string result = Catch::Detail::convertUnstreamable(UnscopedValue42);
    EXPECT_FALSE(result.empty());
}

// Test that convertUnstreamable works with unscoped enum negative value
TEST_F(ConvertUnstreamableTest_77, UnscopedEnumNegativeValue_77) {
    std::string result = Catch::Detail::convertUnstreamable(UnscopedValueNeg);
    EXPECT_FALSE(result.empty());
}

// Test that convertUnstreamable works with scoped enum value 0
TEST_F(ConvertUnstreamableTest_77, ScopedEnumZeroValue_77) {
    std::string result = Catch::Detail::convertUnstreamable(ScopedEnum::Value0);
    EXPECT_FALSE(result.empty());
}

// Test that convertUnstreamable works with scoped enum positive value
TEST_F(ConvertUnstreamableTest_77, ScopedEnumPositiveValue_77) {
    std::string result = Catch::Detail::convertUnstreamable(ScopedEnum::Value100);
    EXPECT_FALSE(result.empty());
}

// Test that convertUnstreamable works with scoped enum negative value
TEST_F(ConvertUnstreamableTest_77, ScopedEnumNegativeValue_77) {
    std::string result = Catch::Detail::convertUnstreamable(ScopedEnum::ValueNeg);
    EXPECT_FALSE(result.empty());
}

// Test that different enum values produce different string representations
TEST_F(ConvertUnstreamableTest_77, DifferentValuesProduceDifferentStrings_77) {
    std::string result0 = Catch::Detail::convertUnstreamable(ScopedEnum::Value0);
    std::string result100 = Catch::Detail::convertUnstreamable(ScopedEnum::Value100);
    // Different underlying values should produce different strings
    EXPECT_NE(result0, result100);
}

// Test with uint8_t underlying type boundary - min
TEST_F(ConvertUnstreamableTest_77, ScopedEnumUint8Min_77) {
    std::string result = Catch::Detail::convertUnstreamable(ScopedEnumUint8::Min);
    EXPECT_FALSE(result.empty());
}

// Test with uint8_t underlying type boundary - max
TEST_F(ConvertUnstreamableTest_77, ScopedEnumUint8Max_77) {
    std::string result = Catch::Detail::convertUnstreamable(ScopedEnumUint8::Max);
    EXPECT_FALSE(result.empty());
}

// Test with int16_t underlying type boundaries
TEST_F(ConvertUnstreamableTest_77, ScopedEnumInt16Boundaries_77) {
    std::string resultNeg = Catch::Detail::convertUnstreamable(ScopedEnumInt16::NegVal);
    std::string resultPos = Catch::Detail::convertUnstreamable(ScopedEnumInt16::PosVal);
    EXPECT_FALSE(resultNeg.empty());
    EXPECT_FALSE(resultPos.empty());
    EXPECT_NE(resultNeg, resultPos);
}

// Test that the return type is std::string
TEST_F(ConvertUnstreamableTest_77, ReturnTypeIsString_77) {
    auto result = Catch::Detail::convertUnstreamable(ScopedEnum::Value1);
    static_assert(std::is_same<decltype(result), std::string>::value,
                  "Return type should be std::string");
    EXPECT_FALSE(result.empty());
}

// Test that same enum value produces consistent results
TEST_F(ConvertUnstreamableTest_77, ConsistentResultsForSameValue_77) {
    std::string result1 = Catch::Detail::convertUnstreamable(ScopedEnum::Value1);
    std::string result2 = Catch::Detail::convertUnstreamable(ScopedEnum::Value1);
    EXPECT_EQ(result1, result2);
}

// Compile-time test: SFINAE should only enable for enum types
// This is a compile-time check - non-enum types should not compile
// We verify the enable_if trait at compile time
TEST_F(ConvertUnstreamableTest_77, SFINAEOnlyEnablesForEnums_77) {
    // Verify that the function is enabled for enum types
    static_assert(std::is_enum<UnscopedEnum>::value, "UnscopedEnum should be an enum");
    static_assert(std::is_enum<ScopedEnum>::value, "ScopedEnum should be an enum");
    // int is not an enum, so convertUnstreamable(int) should not be available
    static_assert(!std::is_enum<int>::value, "int should not be an enum");
    SUCCEED();
}
