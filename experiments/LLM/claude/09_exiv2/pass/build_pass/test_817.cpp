#include <gtest/gtest.h>
#include <string>
#include "exiv2/value.hpp"

using namespace Exiv2;

// Test fixture for CharsetInfo tests
class CharsetInfoTest_817 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== charsetIdByName Tests ====================

TEST_F(CharsetInfoTest_817, CharsetIdByNameAscii_817) {
    CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByName("ASCII");
    EXPECT_EQ(id, CommentValue::ascii);
}

TEST_F(CharsetInfoTest_817, CharsetIdByNameJis_817) {
    CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByName("JIS");
    EXPECT_EQ(id, CommentValue::jis);
}

TEST_F(CharsetInfoTest_817, CharsetIdByNameUnicode_817) {
    CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByName("Unicode");
    EXPECT_EQ(id, CommentValue::unicode);
}

TEST_F(CharsetInfoTest_817, CharsetIdByNameUndefined_817) {
    CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByName("Undefined");
    EXPECT_EQ(id, CommentValue::undefined);
}

TEST_F(CharsetInfoTest_817, CharsetIdByNameInvalid_817) {
    CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByName("NonExistentCharset");
    EXPECT_EQ(id, CommentValue::invalidCharsetId);
}

TEST_F(CharsetInfoTest_817, CharsetIdByNameEmptyString_817) {
    CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByName("");
    EXPECT_EQ(id, CommentValue::invalidCharsetId);
}

TEST_F(CharsetInfoTest_817, CharsetIdByNameCaseSensitivity_817) {
    // Test that name lookup is case-sensitive (or insensitive depending on impl)
    CommentValue::CharsetId id_lower = CommentValue::CharsetInfo::charsetIdByName("ascii");
    // If case sensitive, should return invalidCharsetId; otherwise ascii
    // We just check it returns a valid CharsetId enum value
    EXPECT_TRUE(id_lower == CommentValue::ascii || id_lower == CommentValue::invalidCharsetId);
}

// ==================== charsetIdByCode Tests ====================

TEST_F(CharsetInfoTest_817, CharsetIdByCodeAscii_817) {
    CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByCode("ASCII\0\0\0");
    // Check if it returns ascii or we try the known code format
    EXPECT_TRUE(id == CommentValue::ascii || id == CommentValue::invalidCharsetId);
}

TEST_F(CharsetInfoTest_817, CharsetIdByCodeInvalid_817) {
    CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByCode("INVALID_CODE");
    EXPECT_EQ(id, CommentValue::invalidCharsetId);
}

TEST_F(CharsetInfoTest_817, CharsetIdByCodeEmptyString_817) {
    CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByCode("");
    EXPECT_EQ(id, CommentValue::invalidCharsetId);
}

// ==================== name Tests ====================

TEST_F(CharsetInfoTest_817, NameForAscii_817) {
    const char* n = CommentValue::CharsetInfo::name(CommentValue::ascii);
    ASSERT_NE(n, nullptr);
    EXPECT_STREQ(n, "ASCII");
}

TEST_F(CharsetInfoTest_817, NameForJis_817) {
    const char* n = CommentValue::CharsetInfo::name(CommentValue::jis);
    ASSERT_NE(n, nullptr);
    EXPECT_STREQ(n, "JIS");
}

TEST_F(CharsetInfoTest_817, NameForUnicode_817) {
    const char* n = CommentValue::CharsetInfo::name(CommentValue::unicode);
    ASSERT_NE(n, nullptr);
    EXPECT_STREQ(n, "Unicode");
}

TEST_F(CharsetInfoTest_817, NameForUndefined_817) {
    const char* n = CommentValue::CharsetInfo::name(CommentValue::undefined);
    ASSERT_NE(n, nullptr);
    EXPECT_STREQ(n, "Undefined");
}

// ==================== code Tests ====================

TEST_F(CharsetInfoTest_817, CodeForAscii_817) {
    const char* c = CommentValue::CharsetInfo::code(CommentValue::ascii);
    ASSERT_NE(c, nullptr);
    // ASCII code should be a known 8-byte string
    EXPECT_TRUE(std::string(c).size() > 0);
}

TEST_F(CharsetInfoTest_817, CodeForUnicode_817) {
    const char* c = CommentValue::CharsetInfo::code(CommentValue::unicode);
    ASSERT_NE(c, nullptr);
}

TEST_F(CharsetInfoTest_817, CodeForUndefined_817) {
    const char* c = CommentValue::CharsetInfo::code(CommentValue::undefined);
    ASSERT_NE(c, nullptr);
}

// ==================== Round-trip Tests ====================

TEST_F(CharsetInfoTest_817, RoundTripNameToId_817) {
    // For each known charset, getting the name and then looking up by name should return same id
    CommentValue::CharsetId ids[] = {
        CommentValue::ascii, CommentValue::jis,
        CommentValue::unicode, CommentValue::undefined
    };
    for (auto id : ids) {
        const char* n = CommentValue::CharsetInfo::name(id);
        ASSERT_NE(n, nullptr);
        CommentValue::CharsetId result = CommentValue::CharsetInfo::charsetIdByName(std::string(n));
        EXPECT_EQ(result, id) << "Round-trip failed for CharsetId: " << id;
    }
}

TEST_F(CharsetInfoTest_817, RoundTripCodeToId_817) {
    // For each known charset, getting the code and then looking up by code should return same id
    CommentValue::CharsetId ids[] = {
        CommentValue::ascii, CommentValue::jis,
        CommentValue::unicode, CommentValue::undefined
    };
    for (auto id : ids) {
        const char* c = CommentValue::CharsetInfo::code(id);
        ASSERT_NE(c, nullptr);
        CommentValue::CharsetId result = CommentValue::CharsetInfo::charsetIdByCode(std::string(c));
        EXPECT_EQ(result, id) << "Round-trip failed for CharsetId: " << id;
    }
}

// ==================== Boundary / Edge Cases ====================

TEST_F(CharsetInfoTest_817, CharsetIdByNameWithSpaces_817) {
    CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByName("  ASCII  ");
    // Likely invalid since name won't match exactly
    EXPECT_EQ(id, CommentValue::invalidCharsetId);
}

TEST_F(CharsetInfoTest_817, CharsetIdByNameVeryLongString_817) {
    std::string longName(1000, 'A');
    CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByName(longName);
    EXPECT_EQ(id, CommentValue::invalidCharsetId);
}
