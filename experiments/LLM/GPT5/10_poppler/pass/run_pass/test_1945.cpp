#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <optional>
#include <string>
#include <string_view>
#include <map>
#include <ranges>

// Mock classes or types, if necessary
// Mock dependencies can be added here, but the provided code doesn't indicate any.

namespace DN {

// The function we are testing
inline std::optional<std::string> FindFirstValue(const std::map<std::string, std::string> &dn, std::string_view key) {
    auto first = std::ranges::find_if(dn, [&key](const auto &it) { return it.first == key; });
    if (first == dn.end()) {
        return {};
    }
    return first->second;
}

}  // namespace DN

// Test suite for FindFirstValue function
class FindFirstValueTest_1945 : public ::testing::Test {
protected:
    // Add any necessary setup or teardown logic here
};

// Normal Operation Test: Key is present in the map.
TEST_F(FindFirstValueTest_1945, KeyFound_1945) {
    std::map<std::string, std::string> dn = {
        {"CN", "John Doe"},
        {"O", "Example Organization"},
        {"C", "US"}
    };
    auto result = DN::FindFirstValue(dn, "CN");
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "John Doe");
}

// Normal Operation Test: Key is present as the first element.
TEST_F(FindFirstValueTest_1945, FirstElementKeyFound_1945) {
    std::map<std::string, std::string> dn = {
        {"CN", "John Doe"},
        {"O", "Example Organization"},
        {"C", "US"}
    };
    auto result = DN::FindFirstValue(dn, "CN");
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "John Doe");
}

// Boundary Condition Test: Key is present, but with empty value.
TEST_F(FindFirstValueTest_1945, KeyWithEmptyValue_1945) {
    std::map<std::string, std::string> dn = {
        {"CN", ""},
        {"O", "Example Organization"},
        {"C", "US"}
    };
    auto result = DN::FindFirstValue(dn, "CN");
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "");
}

// Boundary Condition Test: Key does not exist in the map.
TEST_F(FindFirstValueTest_1945, KeyNotFound_1945) {
    std::map<std::string, std::string> dn = {
        {"CN", "John Doe"},
        {"O", "Example Organization"},
        {"C", "US"}
    };
    auto result = DN::FindFirstValue(dn, "L");  // "L" key is not present
    EXPECT_FALSE(result.has_value());
}

// Exceptional or Error Case Test: Empty map, should return empty.
TEST_F(FindFirstValueTest_1945, EmptyMap_1945) {
    std::map<std::string, std::string> dn = {};
    auto result = DN::FindFirstValue(dn, "CN");
    EXPECT_FALSE(result.has_value());
}

// Verification of External Interactions: Mocked tests would go here if dependencies were introduced.