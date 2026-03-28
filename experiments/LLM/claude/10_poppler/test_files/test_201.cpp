#include <gtest/gtest.h>
#include <optional>
#include <string>

// Minimal stub to make EOFStream compilable based on the interface shown
// Since we only see the partial header, we need to provide enough context.
// The actual class uses override, implying a base class, but we test the concrete behavior.

#include "Stream.h"

class EOFStreamTest_201 : public ::testing::Test {
protected:
    EOFStream stream;
};

// Test that getPSFilter returns an empty optional with typical arguments
TEST_F(EOFStreamTest_201, GetPSFilterReturnsEmptyOptional_201) {
    auto result = stream.getPSFilter(1, "indent");
    EXPECT_FALSE(result.has_value());
}

// Test that getPSFilter returns empty optional with psLevel 0
TEST_F(EOFStreamTest_201, GetPSFilterWithPSLevelZero_201) {
    auto result = stream.getPSFilter(0, "");
    EXPECT_FALSE(result.has_value());
}

// Test that getPSFilter returns empty optional with negative psLevel
TEST_F(EOFStreamTest_201, GetPSFilterWithNegativePSLevel_201) {
    auto result = stream.getPSFilter(-1, "test");
    EXPECT_FALSE(result.has_value());
}

// Test that getPSFilter returns empty optional with nullptr indent
TEST_F(EOFStreamTest_201, GetPSFilterWithNullptrIndent_201) {
    auto result = stream.getPSFilter(1, nullptr);
    EXPECT_FALSE(result.has_value());
}

// Test that getPSFilter returns empty optional with large psLevel
TEST_F(EOFStreamTest_201, GetPSFilterWithLargePSLevel_201) {
    auto result = stream.getPSFilter(999, "  ");
    EXPECT_FALSE(result.has_value());
}

// Test that getPSFilter returns empty optional with psLevel 2
TEST_F(EOFStreamTest_201, GetPSFilterWithPSLevel2_201) {
    auto result = stream.getPSFilter(2, "\t");
    EXPECT_FALSE(result.has_value());
}

// Test that getPSFilter returns empty optional with psLevel 3
TEST_F(EOFStreamTest_201, GetPSFilterWithPSLevel3_201) {
    auto result = stream.getPSFilter(3, "    ");
    EXPECT_FALSE(result.has_value());
}

// Test that the returned optional compares equal to std::nullopt
TEST_F(EOFStreamTest_201, GetPSFilterReturnsNullopt_201) {
    auto result = stream.getPSFilter(1, "indent");
    EXPECT_EQ(result, std::nullopt);
}

// Test that getPSFilter returns empty optional with empty string indent
TEST_F(EOFStreamTest_201, GetPSFilterWithEmptyStringIndent_201) {
    auto result = stream.getPSFilter(1, "");
    EXPECT_EQ(result, std::optional<std::string>{});
}

// Test multiple calls return consistent results
TEST_F(EOFStreamTest_201, GetPSFilterMultipleCallsConsistent_201) {
    auto result1 = stream.getPSFilter(1, "a");
    auto result2 = stream.getPSFilter(2, "b");
    auto result3 = stream.getPSFilter(3, "c");
    EXPECT_FALSE(result1.has_value());
    EXPECT_FALSE(result2.has_value());
    EXPECT_FALSE(result3.has_value());
}

// Test with INT_MAX psLevel
TEST_F(EOFStreamTest_201, GetPSFilterWithIntMaxPSLevel_201) {
    auto result = stream.getPSFilter(INT_MAX, "indent");
    EXPECT_FALSE(result.has_value());
}

// Test with INT_MIN psLevel
TEST_F(EOFStreamTest_201, GetPSFilterWithIntMinPSLevel_201) {
    auto result = stream.getPSFilter(INT_MIN, "indent");
    EXPECT_FALSE(result.has_value());
}
