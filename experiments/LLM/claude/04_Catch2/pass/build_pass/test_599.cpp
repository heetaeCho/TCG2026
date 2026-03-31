#include <gtest/gtest.h>
#include <vector>
#include <string>

#include "catch2/internal/catch_enum_values_registry.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"
#include "catch2/interfaces/catch_interfaces_enum_values_registry.hpp"

namespace Catch {
namespace Detail {
    // Forward declaration of the function under test
    Catch::Detail::unique_ptr<EnumInfo> makeEnumInfo(
        StringRef enumName,
        StringRef allValueNames,
        std::vector<int> const& values);
}
}

class MakeEnumInfoTest_599 : public ::testing::Test {
protected:
    // Helper to invoke makeEnumInfo
    Catch::Detail::unique_ptr<Catch::Detail::EnumInfo> callMakeEnumInfo(
        Catch::StringRef enumName,
        Catch::StringRef allValueNames,
        std::vector<int> const& values) {
        return Catch::Detail::makeEnumInfo(enumName, allValueNames, values);
    }
};

// Test that makeEnumInfo creates a non-null EnumInfo
TEST_F(MakeEnumInfoTest_599, ReturnsNonNullEnumInfo_599) {
    std::vector<int> values = {0, 1, 2};
    auto info = callMakeEnumInfo("MyEnum", "Value0, Value1, Value2", values);
    ASSERT_TRUE(info.get() != nullptr);
}

// Test that the enum name is correctly set
TEST_F(MakeEnumInfoTest_599, SetsEnumNameCorrectly_599) {
    std::vector<int> values = {0, 1};
    auto info = callMakeEnumInfo("TestEnum", "A, B", values);
    EXPECT_EQ(info->m_name, Catch::StringRef("TestEnum"));
}

// Test that the correct number of values are stored
TEST_F(MakeEnumInfoTest_599, StoresCorrectNumberOfValues_599) {
    std::vector<int> values = {10, 20, 30};
    auto info = callMakeEnumInfo("Color", "Red, Green, Blue", values);
    EXPECT_EQ(info->m_values.size(), 3u);
}

// Test that integer values are correctly mapped
TEST_F(MakeEnumInfoTest_599, MapsIntegerValuesCorrectly_599) {
    std::vector<int> values = {10, 20, 30};
    auto info = callMakeEnumInfo("Color", "Red, Green, Blue", values);
    EXPECT_EQ(info->m_values[0].first, 10);
    EXPECT_EQ(info->m_values[1].first, 20);
    EXPECT_EQ(info->m_values[2].first, 30);
}

// Test that value names are correctly parsed and mapped
TEST_F(MakeEnumInfoTest_599, ParsesValueNamesCorrectly_599) {
    std::vector<int> values = {0, 1, 2};
    auto info = callMakeEnumInfo("Fruit", "Apple, Banana, Cherry", values);
    // The parsed names should match (possibly with trimming)
    EXPECT_EQ(info->m_values[0].second, Catch::StringRef("Apple"));
    EXPECT_EQ(info->m_values[1].second, Catch::StringRef("Banana"));
    EXPECT_EQ(info->m_values[2].second, Catch::StringRef("Cherry"));
}

// Test with a single value
TEST_F(MakeEnumInfoTest_599, SingleValueEnum_599) {
    std::vector<int> values = {42};
    auto info = callMakeEnumInfo("SingleEnum", "OnlyValue", values);
    ASSERT_EQ(info->m_values.size(), 1u);
    EXPECT_EQ(info->m_values[0].first, 42);
    EXPECT_EQ(info->m_values[0].second, Catch::StringRef("OnlyValue"));
}

// Test with negative integer values
TEST_F(MakeEnumInfoTest_599, NegativeIntegerValues_599) {
    std::vector<int> values = {-1, -2, -3};
    auto info = callMakeEnumInfo("NegEnum", "NegOne, NegTwo, NegThree", values);
    ASSERT_EQ(info->m_values.size(), 3u);
    EXPECT_EQ(info->m_values[0].first, -1);
    EXPECT_EQ(info->m_values[1].first, -2);
    EXPECT_EQ(info->m_values[2].first, -3);
}

// Test with empty enum (no values)
TEST_F(MakeEnumInfoTest_599, EmptyValuesEnum_599) {
    std::vector<int> values = {};
    auto info = callMakeEnumInfo("EmptyEnum", "", values);
    EXPECT_EQ(info->m_values.size(), 0u);
    EXPECT_EQ(info->m_name, Catch::StringRef("EmptyEnum"));
}

// Test lookup functionality returns the correct name for a given value
TEST_F(MakeEnumInfoTest_599, LookupReturnsCorrectName_599) {
    std::vector<int> values = {0, 1, 2};
    auto info = callMakeEnumInfo("Direction", "Up, Down, Left", values);
    Catch::StringRef result = info->lookup(1);
    EXPECT_EQ(result, Catch::StringRef("Down"));
}

// Test lookup for first value
TEST_F(MakeEnumInfoTest_599, LookupFirstValue_599) {
    std::vector<int> values = {100, 200, 300};
    auto info = callMakeEnumInfo("Scores", "Low, Medium, High", values);
    Catch::StringRef result = info->lookup(100);
    EXPECT_EQ(result, Catch::StringRef("Low"));
}

// Test lookup for last value
TEST_F(MakeEnumInfoTest_599, LookupLastValue_599) {
    std::vector<int> values = {100, 200, 300};
    auto info = callMakeEnumInfo("Scores", "Low, Medium, High", values);
    Catch::StringRef result = info->lookup(300);
    EXPECT_EQ(result, Catch::StringRef("High"));
}

// Test lookup for a value that doesn't exist - should return some result (likely containing the int value)
TEST_F(MakeEnumInfoTest_599, LookupNonExistentValue_599) {
    std::vector<int> values = {0, 1, 2};
    auto info = callMakeEnumInfo("MyEnum", "A, B, C", values);
    Catch::StringRef result = info->lookup(999);
    // The result should not be empty - it should contain some representation
    EXPECT_FALSE(result.empty());
}

// Test with duplicate integer values
TEST_F(MakeEnumInfoTest_599, DuplicateIntegerValues_599) {
    std::vector<int> values = {1, 1, 2};
    auto info = callMakeEnumInfo("DupEnum", "First, Second, Third", values);
    ASSERT_EQ(info->m_values.size(), 3u);
    EXPECT_EQ(info->m_values[0].first, 1);
    EXPECT_EQ(info->m_values[1].first, 1);
    EXPECT_EQ(info->m_values[2].first, 2);
}

// Test that lookup with duplicate values returns first match
TEST_F(MakeEnumInfoTest_599, LookupWithDuplicateValuesReturnsFirst_599) {
    std::vector<int> values = {1, 1, 2};
    auto info = callMakeEnumInfo("DupEnum", "First, Second, Third", values);
    Catch::StringRef result = info->lookup(1);
    // Should return the first matching name
    EXPECT_EQ(result, Catch::StringRef("First"));
}

// Test with zero value
TEST_F(MakeEnumInfoTest_599, ZeroValue_599) {
    std::vector<int> values = {0};
    auto info = callMakeEnumInfo("ZeroEnum", "Zero", values);
    ASSERT_EQ(info->m_values.size(), 1u);
    EXPECT_EQ(info->m_values[0].first, 0);
    Catch::StringRef result = info->lookup(0);
    EXPECT_EQ(result, Catch::StringRef("Zero"));
}

// Test with names that have leading/trailing spaces (parseEnums should trim)
TEST_F(MakeEnumInfoTest_599, NamesWithExtraSpaces_599) {
    std::vector<int> values = {0, 1};
    auto info = callMakeEnumInfo("SpaceEnum", "  Alpha ,  Beta  ", values);
    ASSERT_EQ(info->m_values.size(), 2u);
    // After parsing, names should be trimmed
    EXPECT_EQ(info->m_values[0].second, Catch::StringRef("Alpha"));
    EXPECT_EQ(info->m_values[1].second, Catch::StringRef("Beta"));
}

// Test with large number of enum values
TEST_F(MakeEnumInfoTest_599, LargeNumberOfValues_599) {
    std::string allNames;
    std::vector<int> values;
    for (int i = 0; i < 100; ++i) {
        if (i > 0) allNames += ", ";
        allNames += "Val" + std::to_string(i);
        values.push_back(i);
    }
    auto info = callMakeEnumInfo("LargeEnum", Catch::StringRef(allNames), values);
    EXPECT_EQ(info->m_values.size(), 100u);
    EXPECT_EQ(info->m_values[0].first, 0);
    EXPECT_EQ(info->m_values[99].first, 99);
}

// Test enum name can be empty string
TEST_F(MakeEnumInfoTest_599, EmptyEnumName_599) {
    std::vector<int> values = {1};
    auto info = callMakeEnumInfo("", "X", values);
    EXPECT_TRUE(info->m_name.empty());
    ASSERT_EQ(info->m_values.size(), 1u);
    EXPECT_EQ(info->m_values[0].first, 1);
}

// Test with mixed positive and negative values
TEST_F(MakeEnumInfoTest_599, MixedPositiveNegativeValues_599) {
    std::vector<int> values = {-10, 0, 10};
    auto info = callMakeEnumInfo("Mixed", "Neg, Zero, Pos", values);
    ASSERT_EQ(info->m_values.size(), 3u);
    EXPECT_EQ(info->m_values[0].first, -10);
    EXPECT_EQ(info->m_values[1].first, 0);
    EXPECT_EQ(info->m_values[2].first, 10);
}
