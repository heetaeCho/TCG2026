#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <utility>

// Include the necessary headers
#include "catch2/interfaces/catch_interfaces_enum_values_registry.hpp"
#include "catch2/internal/catch_string_ref.hpp"

using namespace Catch;
using namespace Catch::Detail;

class EnumInfoTest_598 : public ::testing::Test {
protected:
    EnumInfo enumInfo;
    
    void SetUp() override {
        // Default setup - can be overridden per test
    }
};

// Test that lookup returns the correct name for a value that exists
TEST_F(EnumInfoTest_598, LookupExistingValue_598) {
    enumInfo.m_values.push_back({0, "Zero"_sr});
    enumInfo.m_values.push_back({1, "One"_sr});
    enumInfo.m_values.push_back({2, "Two"_sr});
    
    StringRef result = enumInfo.lookup(1);
    EXPECT_EQ(result, "One"_sr);
}

// Test that lookup returns unexpected enum value string for a non-existing value
TEST_F(EnumInfoTest_598, LookupNonExistingValue_598) {
    enumInfo.m_values.push_back({0, "Zero"_sr});
    enumInfo.m_values.push_back({1, "One"_sr});
    
    StringRef result = enumInfo.lookup(42);
    EXPECT_EQ(result, "{** unexpected enum value **}"_sr);
}

// Test lookup on an empty values list
TEST_F(EnumInfoTest_598, LookupOnEmptyValues_598) {
    StringRef result = enumInfo.lookup(0);
    EXPECT_EQ(result, "{** unexpected enum value **}"_sr);
}

// Test lookup returns the first matching value when duplicates exist
TEST_F(EnumInfoTest_598, LookupWithDuplicateKeys_598) {
    enumInfo.m_values.push_back({1, "First"_sr});
    enumInfo.m_values.push_back({1, "Second"_sr});
    
    StringRef result = enumInfo.lookup(1);
    EXPECT_EQ(result, "First"_sr);
}

// Test lookup with negative enum values
TEST_F(EnumInfoTest_598, LookupNegativeValue_598) {
    enumInfo.m_values.push_back({-1, "NegativeOne"_sr});
    enumInfo.m_values.push_back({-2, "NegativeTwo"_sr});
    enumInfo.m_values.push_back({0, "Zero"_sr});
    
    StringRef result = enumInfo.lookup(-1);
    EXPECT_EQ(result, "NegativeOne"_sr);
}

// Test lookup with negative value that doesn't exist
TEST_F(EnumInfoTest_598, LookupNonExistingNegativeValue_598) {
    enumInfo.m_values.push_back({0, "Zero"_sr});
    enumInfo.m_values.push_back({1, "One"_sr});
    
    StringRef result = enumInfo.lookup(-5);
    EXPECT_EQ(result, "{** unexpected enum value **}"_sr);
}

// Test lookup with the first element in the list
TEST_F(EnumInfoTest_598, LookupFirstElement_598) {
    enumInfo.m_values.push_back({10, "Ten"_sr});
    enumInfo.m_values.push_back({20, "Twenty"_sr});
    enumInfo.m_values.push_back({30, "Thirty"_sr});
    
    StringRef result = enumInfo.lookup(10);
    EXPECT_EQ(result, "Ten"_sr);
}

// Test lookup with the last element in the list
TEST_F(EnumInfoTest_598, LookupLastElement_598) {
    enumInfo.m_values.push_back({10, "Ten"_sr});
    enumInfo.m_values.push_back({20, "Twenty"_sr});
    enumInfo.m_values.push_back({30, "Thirty"_sr});
    
    StringRef result = enumInfo.lookup(30);
    EXPECT_EQ(result, "Thirty"_sr);
}

// Test lookup with a single element that matches
TEST_F(EnumInfoTest_598, LookupSingleElementMatch_598) {
    enumInfo.m_values.push_back({42, "FortyTwo"_sr});
    
    StringRef result = enumInfo.lookup(42);
    EXPECT_EQ(result, "FortyTwo"_sr);
}

// Test lookup with a single element that doesn't match
TEST_F(EnumInfoTest_598, LookupSingleElementNoMatch_598) {
    enumInfo.m_values.push_back({42, "FortyTwo"_sr});
    
    StringRef result = enumInfo.lookup(0);
    EXPECT_EQ(result, "{** unexpected enum value **}"_sr);
}

// Test lookup with zero value
TEST_F(EnumInfoTest_598, LookupZeroValue_598) {
    enumInfo.m_values.push_back({0, "Zero"_sr});
    enumInfo.m_values.push_back({1, "One"_sr});
    
    StringRef result = enumInfo.lookup(0);
    EXPECT_EQ(result, "Zero"_sr);
}

// Test lookup with large int values
TEST_F(EnumInfoTest_598, LookupLargeIntValue_598) {
    enumInfo.m_values.push_back({2147483647, "MaxInt"_sr});
    enumInfo.m_values.push_back({-2147483648, "MinInt"_sr});
    
    StringRef result = enumInfo.lookup(2147483647);
    EXPECT_EQ(result, "MaxInt"_sr);
    
    result = enumInfo.lookup(-2147483648);
    EXPECT_EQ(result, "MinInt"_sr);
}

// Test that multiple lookups on the same object work correctly
TEST_F(EnumInfoTest_598, MultipleLookups_598) {
    enumInfo.m_values.push_back({0, "Zero"_sr});
    enumInfo.m_values.push_back({1, "One"_sr});
    enumInfo.m_values.push_back({2, "Two"_sr});
    
    EXPECT_EQ(enumInfo.lookup(0), "Zero"_sr);
    EXPECT_EQ(enumInfo.lookup(1), "One"_sr);
    EXPECT_EQ(enumInfo.lookup(2), "Two"_sr);
    EXPECT_EQ(enumInfo.lookup(3), "{** unexpected enum value **}"_sr);
}
