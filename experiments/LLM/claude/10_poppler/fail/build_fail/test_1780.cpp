#include <gtest/gtest.h>
#include <cstring>
#include "poppler/StructElement.h"

class OwnerToNameTest_1780 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that known owner values return non-null, non-empty strings
TEST_F(OwnerToNameTest_1780, KnownOwnerReturnsValidString_1780) {
    // Test with a set of known owner values
    const char *result = Attribute::getOwnerName(Attribute::HTML);
    ASSERT_NE(result, nullptr);
    EXPECT_STRNE(result, "UnknownOwner");
    EXPECT_GT(strlen(result), 0u);
}

TEST_F(OwnerToNameTest_1780, CSS_OwnerReturnsValidString_1780) {
    const char *result = Attribute::getOwnerName(Attribute::CSS);
    ASSERT_NE(result, nullptr);
    EXPECT_STRNE(result, "UnknownOwner");
    EXPECT_GT(strlen(result), 0u);
}

TEST_F(OwnerToNameTest_1780, PDFOwnerReturnsValidString_1780) {
    const char *result = Attribute::getOwnerName(Attribute::Layout);
    ASSERT_NE(result, nullptr);
    EXPECT_STRNE(result, "UnknownOwner");
    EXPECT_GT(strlen(result), 0u);
}

TEST_F(OwnerToNameTest_1780, ListOwnerReturnsValidString_1780) {
    const char *result = Attribute::getOwnerName(Attribute::List);
    ASSERT_NE(result, nullptr);
    EXPECT_STRNE(result, "UnknownOwner");
    EXPECT_GT(strlen(result), 0u);
}

TEST_F(OwnerToNameTest_1780, PrintFieldOwnerReturnsValidString_1780) {
    const char *result = Attribute::getOwnerName(Attribute::PrintField);
    ASSERT_NE(result, nullptr);
    EXPECT_STRNE(result, "UnknownOwner");
    EXPECT_GT(strlen(result), 0u);
}

TEST_F(OwnerToNameTest_1780, TableOwnerReturnsValidString_1780) {
    const char *result = Attribute::getOwnerName(Attribute::Table);
    ASSERT_NE(result, nullptr);
    EXPECT_STRNE(result, "UnknownOwner");
    EXPECT_GT(strlen(result), 0u);
}

// Test that an invalid/unknown owner value returns "UnknownOwner"
TEST_F(OwnerToNameTest_1780, UnknownOwnerReturnsUnknownOwnerString_1780) {
    // Cast an invalid integer to Owner to test the fallback
    Attribute::Owner invalidOwner = static_cast<Attribute::Owner>(9999);
    const char *result = Attribute::getOwnerName(invalidOwner);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "UnknownOwner");
}

// Test that the result pointer is stable (not null) for boundary enum values
TEST_F(OwnerToNameTest_1780, ResultIsNeverNull_1780) {
    // Even for unknown owners, the function should return a valid string pointer
    for (int i = -1; i < 20; i++) {
        Attribute::Owner owner = static_cast<Attribute::Owner>(i);
        const char *result = Attribute::getOwnerName(owner);
        ASSERT_NE(result, nullptr) << "Null returned for owner value " << i;
        EXPECT_GT(strlen(result), 0u) << "Empty string returned for owner value " << i;
    }
}

// Test UserProperties owner
TEST_F(OwnerToNameTest_1780, UserPropertiesOwnerReturnsValidString_1780) {
    const char *result = Attribute::getOwnerName(Attribute::UserProperties);
    ASSERT_NE(result, nullptr);
    EXPECT_STRNE(result, "UnknownOwner");
}

// Test consistency - calling the same owner twice returns the same result
TEST_F(OwnerToNameTest_1780, ConsistentResults_1780) {
    const char *result1 = Attribute::getOwnerName(Attribute::HTML);
    const char *result2 = Attribute::getOwnerName(Attribute::HTML);
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    EXPECT_STREQ(result1, result2);
}
