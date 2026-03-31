#include <gtest/gtest.h>
#include <string>
#include "exiv2/value.hpp"

using namespace Exiv2;

class CharsetInfoTest_816 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test code() with valid CharsetId::ascii
TEST_F(CharsetInfoTest_816, CodeForAscii_816) {
    const char* result = CommentValue::CharsetInfo::code(CommentValue::ascii);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "ASCII\0\0\0");
}

// Test code() with valid CharsetId::jis
TEST_F(CharsetInfoTest_816, CodeForJis_816) {
    const char* result = CommentValue::CharsetInfo::code(CommentValue::jis);
    ASSERT_NE(result, nullptr);
}

// Test code() with valid CharsetId::unicode
TEST_F(CharsetInfoTest_816, CodeForUnicode_816) {
    const char* result = CommentValue::CharsetInfo::code(CommentValue::unicode);
    ASSERT_NE(result, nullptr);
}

// Test code() with valid CharsetId::undefined
TEST_F(CharsetInfoTest_816, CodeForUndefined_816) {
    const char* result = CommentValue::CharsetInfo::code(CommentValue::undefined);
    ASSERT_NE(result, nullptr);
}

// Test code() with invalidCharsetId - should fall back to undefined
TEST_F(CharsetInfoTest_816, CodeForInvalidCharsetId_816) {
    const char* undefinedCode = CommentValue::CharsetInfo::code(CommentValue::undefined);
    const char* invalidCode = CommentValue::CharsetInfo::code(CommentValue::invalidCharsetId);
    ASSERT_NE(invalidCode, nullptr);
    EXPECT_STREQ(invalidCode, undefinedCode);
}

// Test code() with lastCharsetId - should fall back to undefined
TEST_F(CharsetInfoTest_816, CodeForLastCharsetId_816) {
    const char* undefinedCode = CommentValue::CharsetInfo::code(CommentValue::undefined);
    const char* lastCode = CommentValue::CharsetInfo::code(CommentValue::lastCharsetId);
    ASSERT_NE(lastCode, nullptr);
    EXPECT_STREQ(lastCode, undefinedCode);
}

// Test code() with out-of-range value (large number) - should fall back to undefined
TEST_F(CharsetInfoTest_816, CodeForOutOfRangeCharsetId_816) {
    const char* undefinedCode = CommentValue::CharsetInfo::code(CommentValue::undefined);
    const char* outOfRangeCode = CommentValue::CharsetInfo::code(static_cast<CommentValue::CharsetId>(100));
    ASSERT_NE(outOfRangeCode, nullptr);
    EXPECT_STREQ(outOfRangeCode, undefinedCode);
}

// Test that different valid charset IDs return different codes
TEST_F(CharsetInfoTest_816, DifferentCharsetIdsReturnDifferentCodes_816) {
    const char* asciiCode = CommentValue::CharsetInfo::code(CommentValue::ascii);
    const char* jisCode = CommentValue::CharsetInfo::code(CommentValue::jis);
    const char* unicodeCode = CommentValue::CharsetInfo::code(CommentValue::unicode);
    
    ASSERT_NE(asciiCode, nullptr);
    ASSERT_NE(jisCode, nullptr);
    ASSERT_NE(unicodeCode, nullptr);
    
    // They should be different strings
    EXPECT_STRNE(asciiCode, jisCode);
    EXPECT_STRNE(asciiCode, unicodeCode);
    EXPECT_STRNE(jisCode, unicodeCode);
}

// Test name() with valid CharsetId::ascii
TEST_F(CharsetInfoTest_816, NameForAscii_816) {
    const char* result = CommentValue::CharsetInfo::name(CommentValue::ascii);
    ASSERT_NE(result, nullptr);
}

// Test name() with valid CharsetId::jis
TEST_F(CharsetInfoTest_816, NameForJis_816) {
    const char* result = CommentValue::CharsetInfo::name(CommentValue::jis);
    ASSERT_NE(result, nullptr);
}

// Test name() with valid CharsetId::unicode
TEST_F(CharsetInfoTest_816, NameForUnicode_816) {
    const char* result = CommentValue::CharsetInfo::name(CommentValue::unicode);
    ASSERT_NE(result, nullptr);
}

// Test name() with valid CharsetId::undefined
TEST_F(CharsetInfoTest_816, NameForUndefined_816) {
    const char* result = CommentValue::CharsetInfo::name(CommentValue::undefined);
    ASSERT_NE(result, nullptr);
}

// Test name() with invalidCharsetId
TEST_F(CharsetInfoTest_816, NameForInvalidCharsetId_816) {
    const char* result = CommentValue::CharsetInfo::name(CommentValue::invalidCharsetId);
    ASSERT_NE(result, nullptr);
}

// Test charsetIdByName() with known name
TEST_F(CharsetInfoTest_816, CharsetIdByNameAscii_816) {
    const char* asciiName = CommentValue::CharsetInfo::name(CommentValue::ascii);
    ASSERT_NE(asciiName, nullptr);
    CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByName(std::string(asciiName));
    EXPECT_EQ(id, CommentValue::ascii);
}

// Test charsetIdByName() with unknown name
TEST_F(CharsetInfoTest_816, CharsetIdByNameInvalid_816) {
    CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByName("NonExistentCharset");
    EXPECT_EQ(id, CommentValue::invalidCharsetId);
}

// Test charsetIdByCode() with known code
TEST_F(CharsetInfoTest_816, CharsetIdByCodeAscii_816) {
    const char* asciiCode = CommentValue::CharsetInfo::code(CommentValue::ascii);
    ASSERT_NE(asciiCode, nullptr);
    CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByCode(std::string(asciiCode));
    EXPECT_EQ(id, CommentValue::ascii);
}

// Test charsetIdByCode() with unknown code
TEST_F(CharsetInfoTest_816, CharsetIdByCodeInvalid_816) {
    CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByCode("INVALID_CODE");
    EXPECT_EQ(id, CommentValue::invalidCharsetId);
}

// Test charsetIdByName() with empty string
TEST_F(CharsetInfoTest_816, CharsetIdByNameEmptyString_816) {
    CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByName("");
    EXPECT_EQ(id, CommentValue::invalidCharsetId);
}

// Test charsetIdByCode() with empty string
TEST_F(CharsetInfoTest_816, CharsetIdByCodeEmptyString_816) {
    CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByCode("");
    EXPECT_EQ(id, CommentValue::invalidCharsetId);
}

// Test round-trip: name -> charsetIdByName for each valid charset
TEST_F(CharsetInfoTest_816, RoundTripNameToIdForUnicode_816) {
    const char* unicodeName = CommentValue::CharsetInfo::name(CommentValue::unicode);
    ASSERT_NE(unicodeName, nullptr);
    CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByName(std::string(unicodeName));
    EXPECT_EQ(id, CommentValue::unicode);
}

// Test round-trip: code -> charsetIdByCode for each valid charset
TEST_F(CharsetInfoTest_816, RoundTripCodeToIdForUnicode_816) {
    const char* unicodeCode = CommentValue::CharsetInfo::code(CommentValue::unicode);
    ASSERT_NE(unicodeCode, nullptr);
    CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByCode(std::string(unicodeCode));
    EXPECT_EQ(id, CommentValue::unicode);
}

// Test round-trip for jis
TEST_F(CharsetInfoTest_816, RoundTripNameToIdForJis_816) {
    const char* jisName = CommentValue::CharsetInfo::name(CommentValue::jis);
    ASSERT_NE(jisName, nullptr);
    CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByName(std::string(jisName));
    EXPECT_EQ(id, CommentValue::jis);
}

// Test code() consistency - calling multiple times returns the same result
TEST_F(CharsetInfoTest_816, CodeConsistency_816) {
    const char* first = CommentValue::CharsetInfo::code(CommentValue::ascii);
    const char* second = CommentValue::CharsetInfo::code(CommentValue::ascii);
    EXPECT_STREQ(first, second);
}

// Test name() consistency - calling multiple times returns the same result
TEST_F(CharsetInfoTest_816, NameConsistency_816) {
    const char* first = CommentValue::CharsetInfo::name(CommentValue::ascii);
    const char* second = CommentValue::CharsetInfo::name(CommentValue::ascii);
    EXPECT_STREQ(first, second);
}

// Test boundary: first valid enum value
TEST_F(CharsetInfoTest_816, CodeForFirstEnumValue_816) {
    const char* result = CommentValue::CharsetInfo::code(static_cast<CommentValue::CharsetId>(0));
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, CommentValue::CharsetInfo::code(CommentValue::ascii));
}

// Test negative enum cast - should fall back to undefined
TEST_F(CharsetInfoTest_816, CodeForNegativeCharsetId_816) {
    const char* undefinedCode = CommentValue::CharsetInfo::code(CommentValue::undefined);
    const char* negativeCode = CommentValue::CharsetInfo::code(static_cast<CommentValue::CharsetId>(-1));
    ASSERT_NE(negativeCode, nullptr);
    // Negative values should trigger the fallback to undefined
    EXPECT_STREQ(negativeCode, undefinedCode);
}
