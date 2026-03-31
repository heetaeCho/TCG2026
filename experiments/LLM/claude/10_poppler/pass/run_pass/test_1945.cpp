#include <gtest/gtest.h>
#include <optional>
#include <string>
#include <utility>
#include <vector>

// Include the header under test
#include "DistinguishedNameParser.h"

// Based on usage in FindFirstValue, Result is likely a container of pairs
// We need to determine the actual type. From the code:
// - dn has .end(), supports std::ranges::find_if
// - elements have .first and .second
// - .first is compared with std::string_view key
// - .second is returned as std::string
// Result is likely std::vector<std::pair<std::string, std::string>>

using Result = DN::Result;

class FindFirstValueTest_1945 : public ::testing::Test {
protected:
    Result empty_dn;
    
    Result single_entry_dn = {
        {"CN", "John Doe"}
    };
    
    Result multiple_entries_dn = {
        {"CN", "John Doe"},
        {"O", "Example Corp"},
        {"OU", "Engineering"},
        {"C", "US"}
    };
    
    Result duplicate_keys_dn = {
        {"CN", "First Value"},
        {"O", "Example Corp"},
        {"CN", "Second Value"},
        {"CN", "Third Value"}
    };
    
    Result empty_value_dn = {
        {"CN", ""},
        {"O", "SomeOrg"}
    };
    
    Result empty_key_dn = {
        {"", "EmptyKeyValue"},
        {"CN", "Test"}
    };
};

TEST_F(FindFirstValueTest_1945, EmptyDnReturnsNullopt_1945) {
    auto result = DN::FindFirstValue(empty_dn, "CN");
    EXPECT_FALSE(result.has_value());
}

TEST_F(FindFirstValueTest_1945, KeyNotFoundReturnsNullopt_1945) {
    auto result = DN::FindFirstValue(single_entry_dn, "O");
    EXPECT_FALSE(result.has_value());
}

TEST_F(FindFirstValueTest_1945, SingleEntryFoundReturnsValue_1945) {
    auto result = DN::FindFirstValue(single_entry_dn, "CN");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "John Doe");
}

TEST_F(FindFirstValueTest_1945, MultipleEntriesFindCorrectKey_1945) {
    auto result = DN::FindFirstValue(multiple_entries_dn, "O");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "Example Corp");
}

TEST_F(FindFirstValueTest_1945, MultipleEntriesFindFirstEntry_1945) {
    auto result = DN::FindFirstValue(multiple_entries_dn, "CN");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "John Doe");
}

TEST_F(FindFirstValueTest_1945, MultipleEntriesFindLastEntry_1945) {
    auto result = DN::FindFirstValue(multiple_entries_dn, "C");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "US");
}

TEST_F(FindFirstValueTest_1945, DuplicateKeysReturnsFirstOccurrence_1945) {
    auto result = DN::FindFirstValue(duplicate_keys_dn, "CN");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "First Value");
}

TEST_F(FindFirstValueTest_1945, EmptyValueReturnsEmptyString_1945) {
    auto result = DN::FindFirstValue(empty_value_dn, "CN");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "");
}

TEST_F(FindFirstValueTest_1945, EmptyKeyCanBeFound_1945) {
    auto result = DN::FindFirstValue(empty_key_dn, "");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "EmptyKeyValue");
}

TEST_F(FindFirstValueTest_1945, CaseSensitiveKeySearch_1945) {
    auto result = DN::FindFirstValue(single_entry_dn, "cn");
    EXPECT_FALSE(result.has_value());
}

TEST_F(FindFirstValueTest_1945, CaseSensitiveKeySearchLower_1945) {
    auto result = DN::FindFirstValue(single_entry_dn, "Cn");
    EXPECT_FALSE(result.has_value());
}

TEST_F(FindFirstValueTest_1945, NonExistentKeyInMultipleEntries_1945) {
    auto result = DN::FindFirstValue(multiple_entries_dn, "ST");
    EXPECT_FALSE(result.has_value());
}

TEST_F(FindFirstValueTest_1945, SubstringKeyDoesNotMatch_1945) {
    auto result = DN::FindFirstValue(multiple_entries_dn, "C");
    // "C" should match "C" entry, not "CN"
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "US");
}

TEST_F(FindFirstValueTest_1945, PartialKeyDoesNotMatchLongerKey_1945) {
    // Looking for "OU" should not match "O" and vice versa
    Result dn = {{"OU", "Engineering"}};
    auto result = DN::FindFirstValue(dn, "O");
    EXPECT_FALSE(result.has_value());
}

TEST_F(FindFirstValueTest_1945, LongerKeyDoesNotMatchShorterKey_1945) {
    Result dn = {{"O", "Engineering"}};
    auto result = DN::FindFirstValue(dn, "OU");
    EXPECT_FALSE(result.has_value());
}

TEST_F(FindFirstValueTest_1945, SpecialCharactersInValue_1945) {
    Result dn = {{"CN", "John \"Doe\" <test@example.com>"}};
    auto result = DN::FindFirstValue(dn, "CN");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "John \"Doe\" <test@example.com>");
}

TEST_F(FindFirstValueTest_1945, UnicodeInValue_1945) {
    Result dn = {{"CN", "José García"}};
    auto result = DN::FindFirstValue(dn, "CN");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "José García");
}

TEST_F(FindFirstValueTest_1945, WhitespaceKey_1945) {
    Result dn = {{" ", "SpaceKey"}, {"CN", "Test"}};
    auto result = DN::FindFirstValue(dn, " ");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "SpaceKey");
}

TEST_F(FindFirstValueTest_1945, EmptyDnWithEmptyKey_1945) {
    auto result = DN::FindFirstValue(empty_dn, "");
    EXPECT_FALSE(result.has_value());
}
