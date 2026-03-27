// File: tests/make_enum_info_tests_599.cpp

#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <sstream>

// Headers under test
#include "Catch2/src/catch2/internal/catch_enum_values_registry.cpp"
#include "Catch2/src/catch2/internal/catch_stringref.hpp"
#include "Catch2/src/catch2/internal/catch_unique_ptr.hpp"
#include "Catch2/src/catch2/interfaces/catch_interfaces_enum_values_registry.hpp"

using Catch::StringRef;
using Catch::Detail::makeEnumInfo;

namespace {

std::string ToStdString(StringRef s) {
    // Use only the public interface: explicit conversion to std::string
    return static_cast<std::string>(s);
}

} // namespace

// Normal operation: single value/name pair
TEST(MakeEnumInfoTest_599, SingleValue_MapsCorrectly_599) {
    const StringRef enumName{"Color"};
    const StringRef names{"Red"};
    const std::vector<int> values{1};

    auto info = makeEnumInfo(enumName, names, values);

    ASSERT_TRUE(static_cast<bool>(info)) << "Returned unique_ptr should not be null";
    EXPECT_EQ(ToStdString(info->m_name), "Color");

    ASSERT_EQ(info->m_values.size(), 1u);
    EXPECT_EQ(info->m_values[0].first, 1);
    EXPECT_EQ(ToStdString(info->m_values[0].second), "Red");
}

// Normal operation: multiple values; verify order is preserved
TEST(MakeEnumInfoTest_599, MultipleValues_PreservesOrder_599) {
    const StringRef enumName{"State"};
    const StringRef names{"Alpha, Beta, Gamma"};
    const std::vector<int> values{10, -2, 0};

    auto info = makeEnumInfo(enumName, names, values);

    ASSERT_TRUE(static_cast<bool>(info));
    EXPECT_EQ(ToStdString(info->m_name), "State");

    ASSERT_EQ(info->m_values.size(), 3u);
    EXPECT_EQ(info->m_values[0].first, 10);
    EXPECT_EQ(ToStdString(info->m_values[0].second), "Alpha");

    EXPECT_EQ(info->m_values[1].first, -2);
    EXPECT_EQ(ToStdString(info->m_values[1].second), "Beta");

    EXPECT_EQ(info->m_values[2].first, 0);
    EXPECT_EQ(ToStdString(info->m_values[2].second), "Gamma");
}

// Boundary: empty inputs should yield empty value list, name stored as given
TEST(MakeEnumInfoTest_599, EmptyInputs_YieldEmptyValues_599) {
    const StringRef enumName{""};
    const StringRef names{""};
    const std::vector<int> values{}; // empty

    auto info = makeEnumInfo(enumName, names, values);

    ASSERT_TRUE(static_cast<bool>(info));
    EXPECT_EQ(ToStdString(info->m_name), "");
    EXPECT_TRUE(info->m_values.empty());
}

// Boundary: supports negative, zero, and large positive integers
TEST(MakeEnumInfoTest_599, SupportsVariousIntegerValues_599) {
    const StringRef enumName{"Numbers"};
    const StringRef names{"Neg, Zero, Pos"};
    const std::vector<int> values{-123, 0, 999999};

    auto info = makeEnumInfo(enumName, names, values);

    ASSERT_TRUE(static_cast<bool>(info));
    EXPECT_EQ(ToStdString(info->m_name), "Numbers");
    ASSERT_EQ(info->m_values.size(), 3u);

    EXPECT_EQ(info->m_values[0].first, -123);
    EXPECT_EQ(ToStdString(info->m_values[0].second), "Neg");

    EXPECT_EQ(info->m_values[1].first, 0);
    EXPECT_EQ(ToStdString(info->m_values[1].second), "Zero");

    EXPECT_EQ(info->m_values[2].first, 999999);
    EXPECT_EQ(ToStdString(info->m_values[2].second), "Pos");
}

// Scale: many entries; only observable via size and spot checks
TEST(MakeEnumInfoTest_599, LargeInput_HandlesManyEntries_599) {
    const int N = 100;
    std::vector<int> values;
    values.reserve(N);
    std::ostringstream oss;
    for (int i = 0; i < N; ++i) {
        values.push_back(i * 3 - 50); // arbitrary ints (observable: stored as given)
        if (i) oss << ", ";
        oss << "V" << i;
    }
    const StringRef enumName{"Bulk"};
    const StringRef names{oss.str().c_str()};

    auto info = makeEnumInfo(enumName, names, values);

    ASSERT_TRUE(static_cast<bool>(info));
    EXPECT_EQ(ToStdString(info->m_name), "Bulk");
    ASSERT_EQ(info->m_values.size(), static_cast<size_t>(N));

    // Spot checks to avoid depending on internals
    EXPECT_EQ(info->m_values.front().first, values.front());
    EXPECT_EQ(ToStdString(info->m_values.front().second), "V0");

    EXPECT_EQ(info->m_values[50].first, values[50]);
    EXPECT_EQ(ToStdString(info->m_values[50].second), "V50");

    EXPECT_EQ(info->m_values.back().first, values.back());
    EXPECT_EQ(ToStdString(info->m_values.back().second), "V99");
}
