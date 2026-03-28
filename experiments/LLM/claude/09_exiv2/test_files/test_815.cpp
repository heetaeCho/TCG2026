#include <gtest/gtest.h>
#include <string>
#include "exiv2/value.hpp"

using namespace Exiv2;

class CharsetInfoTest_815 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test name() for ascii CharsetId
TEST_F(CharsetInfoTest_815, NameForAscii_815) {
    const char* result = CommentValue::CharsetInfo::name(CommentValue::ascii);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Ascii");
}

// Test name() for jis CharsetId
TEST_F(CharsetInfoTest_815, NameForJis_815) {
    const char* result = CommentValue::CharsetInfo::name(CommentValue::jis);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Jis");
}

// Test name() for unicode CharsetId
TEST_F(CharsetInfoTest_815, NameForUnicode_815) {
    const char* result = CommentValue::CharsetInfo::name(CommentValue::unicode);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Unicode");
}

// Test name() for undefined CharsetId
TEST_F(CharsetInfoTest_815, NameForUndefined_815) {
    const char* result = CommentValue::CharsetInfo::name(CommentValue::undefined);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Undefined");
}

// Test name() for invalidCharsetId - should fallback to undefined
TEST_F(CharsetInfoTest_815, NameForInvalidCharsetId_815) {
    const char* result = CommentValue::CharsetInfo::name(CommentValue::invalidCharsetId);
    ASSERT_NE(result, nullptr);
    // invalidCharsetId >= lastCharsetId, so it should return undefined's name
    const char* undefinedName = CommentValue::CharsetInfo::name(CommentValue::undefined);
    EXPECT_STREQ(result, undefinedName);
}

// Test name() for lastCharsetId - should fallback to undefined
TEST_F(CharsetInfoTest_815, NameForLastCharsetId_815) {
    const char* result = CommentValue::CharsetInfo::name(CommentValue::lastCharsetId);
    ASSERT_NE(result, nullptr);
    const char* undefinedName = CommentValue::CharsetInfo::name(CommentValue::undefined);
    EXPECT_STREQ(result, undefinedName);
}

// Test name() for an out-of-range value (large number) - should fallback to undefined
TEST_F(CharsetInfoTest_815, NameForOutOfRangeValue_815) {
    const char* result = CommentValue::CharsetInfo::name(static_cast<CommentValue::CharsetId>(100));
    ASSERT_NE(result, nullptr);
    const char* undefinedName = CommentValue::CharsetInfo::name(CommentValue::undefined);
    EXPECT_STREQ(result, undefinedName);
}

// Test code() for ascii CharsetId
TEST_F(CharsetInfoTest_815, CodeForAscii_815) {
    const char* result = CommentValue::CharsetInfo::code(CommentValue::ascii);
    ASSERT_NE(result, nullptr);
}

// Test code() for unicode CharsetId
TEST_F(CharsetInfoTest_815, CodeForUnicode_815) {
    const char* result = CommentValue::CharsetInfo::code(CommentValue::unicode);
    ASSERT_NE(result, nullptr);
}

// Test code() for jis CharsetId
TEST_F(CharsetInfoTest_815, CodeForJis_815) {
    const char* result = CommentValue::CharsetInfo::code(CommentValue::jis);
    ASSERT_NE(result, nullptr);
}

// Test code() for undefined CharsetId
TEST_F(CharsetInfoTest_815, CodeForUndefined_815) {
    const char* result = CommentValue::CharsetInfo::code(CommentValue::undefined);
    ASSERT_NE(result, nullptr);
}

// Test charsetIdByName with valid name "Ascii"
TEST_F(CharsetInfoTest_815, CharsetIdByNameAscii_815) {
    CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByName("Ascii");
    EXPECT_EQ(id, CommentValue::ascii);
}

// Test charsetIdByName with valid name "Unicode"
TEST_F(CharsetInfoTest_815, CharsetIdByNameUnicode_815) {
    CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByName("Unicode");
    EXPECT_EQ(id, CommentValue::unicode);
}

// Test charsetIdByName with valid name "Jis"
TEST_F(CharsetInfoTest_815, CharsetIdByNameJis_815) {
    CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByName("Jis");
    EXPECT_EQ(id, CommentValue::jis);
}

// Test charsetIdByName with valid name "Undefined"
TEST_F(CharsetInfoTest_815, CharsetIdByNameUndefined_815) {
    CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByName("Undefined");
    EXPECT_EQ(id, CommentValue::undefined);
}

// Test charsetIdByName with invalid/unknown name
TEST_F(CharsetInfoTest_815, CharsetIdByNameInvalid_815) {
    CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByName("NonExistent");
    EXPECT_EQ(id, CommentValue::invalidCharsetId);
}

// Test charsetIdByName with empty string
TEST_F(CharsetInfoTest_815, CharsetIdByNameEmpty_815) {
    CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByName("");
    EXPECT_EQ(id, CommentValue::invalidCharsetId);
}

// Test charsetIdByCode with valid code for ascii
TEST_F(CharsetInfoTest_815, CharsetIdByCodeAscii_815) {
    const char* asciiCode = CommentValue::CharsetInfo::code(CommentValue::ascii);
    ASSERT_NE(asciiCode, nullptr);
    CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByCode(asciiCode);
    EXPECT_EQ(id, CommentValue::ascii);
}

// Test charsetIdByCode with valid code for unicode
TEST_F(CharsetInfoTest_815, CharsetIdByCodeUnicode_815) {
    const char* unicodeCode = CommentValue::CharsetInfo::code(CommentValue::unicode);
    ASSERT_NE(unicodeCode, nullptr);
    CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByCode(unicodeCode);
    EXPECT_EQ(id, CommentValue::unicode);
}

// Test charsetIdByCode with invalid code
TEST_F(CharsetInfoTest_815, CharsetIdByCodeInvalid_815) {
    CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByCode("INVALID_CODE");
    EXPECT_EQ(id, CommentValue::invalidCharsetId);
}

// Test charsetIdByCode with empty string
TEST_F(CharsetInfoTest_815, CharsetIdByCodeEmpty_815) {
    CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByCode("");
    EXPECT_EQ(id, CommentValue::invalidCharsetId);
}

// Test that name and charsetIdByName are consistent (round-trip)
TEST_F(CharsetInfoTest_815, RoundTripNameToId_815) {
    for (int i = CommentValue::ascii; i <= CommentValue::undefined; ++i) {
        CommentValue::CharsetId cid = static_cast<CommentValue::CharsetId>(i);
        const char* n = CommentValue::CharsetInfo::name(cid);
        ASSERT_NE(n, nullptr);
        CommentValue::CharsetId resolved = CommentValue::CharsetInfo::charsetIdByName(n);
        EXPECT_EQ(resolved, cid) << "Round trip failed for charsetId=" << i;
    }
}

// Test that code and charsetIdByCode are consistent (round-trip)
TEST_F(CharsetInfoTest_815, RoundTripCodeToId_815) {
    for (int i = CommentValue::ascii; i <= CommentValue::undefined; ++i) {
        CommentValue::CharsetId cid = static_cast<CommentValue::CharsetId>(i);
        const char* c = CommentValue::CharsetInfo::code(cid);
        ASSERT_NE(c, nullptr);
        CommentValue::CharsetId resolved = CommentValue::CharsetInfo::charsetIdByCode(c);
        EXPECT_EQ(resolved, cid) << "Round trip failed for charsetId=" << i;
    }
}

// Test that all valid charset names are distinct
TEST_F(CharsetInfoTest_815, AllNamesDistinct_815) {
    std::set<std::string> names;
    for (int i = CommentValue::ascii; i <= CommentValue::undefined; ++i) {
        const char* n = CommentValue::CharsetInfo::name(static_cast<CommentValue::CharsetId>(i));
        ASSERT_NE(n, nullptr);
        auto result = names.insert(std::string(n));
        EXPECT_TRUE(result.second) << "Duplicate name found: " << n;
    }
}
