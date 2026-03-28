#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <string>

namespace {

// Test fixture for CharsetInfo tests
class CharsetInfoTest_818 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// ==================== charsetIdByCode Tests ====================

TEST_F(CharsetInfoTest_818, CharsetIdByCodeAscii_818) {
    // Test that the ASCII charset code returns the correct CharsetId
    std::string asciiCode(Exiv2::CommentValue::CharsetInfo::code(Exiv2::CommentValue::ascii), 8);
    Exiv2::CommentValue::CharsetId id = Exiv2::CommentValue::CharsetInfo::charsetIdByCode(asciiCode);
    EXPECT_EQ(Exiv2::CommentValue::ascii, id);
}

TEST_F(CharsetInfoTest_818, CharsetIdByCodeJis_818) {
    // Test that the JIS charset code returns the correct CharsetId
    std::string jisCode(Exiv2::CommentValue::CharsetInfo::code(Exiv2::CommentValue::jis), 8);
    Exiv2::CommentValue::CharsetId id = Exiv2::CommentValue::CharsetInfo::charsetIdByCode(jisCode);
    EXPECT_EQ(Exiv2::CommentValue::jis, id);
}

TEST_F(CharsetInfoTest_818, CharsetIdByCodeUnicode_818) {
    // Test that the Unicode charset code returns the correct CharsetId
    std::string unicodeCode(Exiv2::CommentValue::CharsetInfo::code(Exiv2::CommentValue::unicode), 8);
    Exiv2::CommentValue::CharsetId id = Exiv2::CommentValue::CharsetInfo::charsetIdByCode(unicodeCode);
    EXPECT_EQ(Exiv2::CommentValue::unicode, id);
}

TEST_F(CharsetInfoTest_818, CharsetIdByCodeUndefined_818) {
    // Test that the Undefined charset code returns the correct CharsetId
    std::string undefinedCode(Exiv2::CommentValue::CharsetInfo::code(Exiv2::CommentValue::undefined), 8);
    Exiv2::CommentValue::CharsetId id = Exiv2::CommentValue::CharsetInfo::charsetIdByCode(undefinedCode);
    EXPECT_EQ(Exiv2::CommentValue::undefined, id);
}

TEST_F(CharsetInfoTest_818, CharsetIdByCodeInvalidReturnsInvalidCharsetId_818) {
    // Test that an invalid/unknown code returns invalidCharsetId
    std::string invalidCode("XXXXXXXX");
    Exiv2::CommentValue::CharsetId id = Exiv2::CommentValue::CharsetInfo::charsetIdByCode(invalidCode);
    EXPECT_EQ(Exiv2::CommentValue::invalidCharsetId, id);
}

TEST_F(CharsetInfoTest_818, CharsetIdByCodeEmptyStringReturnsInvalid_818) {
    // Test that an empty string returns invalidCharsetId
    std::string emptyCode;
    Exiv2::CommentValue::CharsetId id = Exiv2::CommentValue::CharsetInfo::charsetIdByCode(emptyCode);
    EXPECT_EQ(Exiv2::CommentValue::invalidCharsetId, id);
}

TEST_F(CharsetInfoTest_818, CharsetIdByCodeRandomGarbageReturnsInvalid_818) {
    // Test that random garbage string returns invalidCharsetId
    std::string garbage("12345678");
    Exiv2::CommentValue::CharsetId id = Exiv2::CommentValue::CharsetInfo::charsetIdByCode(garbage);
    EXPECT_EQ(Exiv2::CommentValue::invalidCharsetId, id);
}

// ==================== charsetIdByName Tests ====================

TEST_F(CharsetInfoTest_818, CharsetIdByNameAscii_818) {
    // Test that "Ascii" name returns ascii CharsetId
    Exiv2::CommentValue::CharsetId id = Exiv2::CommentValue::CharsetInfo::charsetIdByName("Ascii");
    EXPECT_EQ(Exiv2::CommentValue::ascii, id);
}

TEST_F(CharsetInfoTest_818, CharsetIdByNameJis_818) {
    // Test that "Jis" name returns jis CharsetId
    Exiv2::CommentValue::CharsetId id = Exiv2::CommentValue::CharsetInfo::charsetIdByName("Jis");
    EXPECT_EQ(Exiv2::CommentValue::jis, id);
}

TEST_F(CharsetInfoTest_818, CharsetIdByNameUnicode_818) {
    // Test that "Unicode" name returns unicode CharsetId
    Exiv2::CommentValue::CharsetId id = Exiv2::CommentValue::CharsetInfo::charsetIdByName("Unicode");
    EXPECT_EQ(Exiv2::CommentValue::unicode, id);
}

TEST_F(CharsetInfoTest_818, CharsetIdByNameUndefined_818) {
    // Test that "Undefined" name returns undefined CharsetId
    Exiv2::CommentValue::CharsetId id = Exiv2::CommentValue::CharsetInfo::charsetIdByName("Undefined");
    EXPECT_EQ(Exiv2::CommentValue::undefined, id);
}

TEST_F(CharsetInfoTest_818, CharsetIdByNameInvalidReturnsInvalid_818) {
    // Test that an invalid/unknown name returns invalidCharsetId
    Exiv2::CommentValue::CharsetId id = Exiv2::CommentValue::CharsetInfo::charsetIdByName("NonExistent");
    EXPECT_EQ(Exiv2::CommentValue::invalidCharsetId, id);
}

TEST_F(CharsetInfoTest_818, CharsetIdByNameEmptyReturnsInvalid_818) {
    // Test that an empty name string returns invalidCharsetId
    Exiv2::CommentValue::CharsetId id = Exiv2::CommentValue::CharsetInfo::charsetIdByName("");
    EXPECT_EQ(Exiv2::CommentValue::invalidCharsetId, id);
}

// ==================== name() Tests ====================

TEST_F(CharsetInfoTest_818, NameForAscii_818) {
    // Test that name for ascii returns a non-null string
    const char* n = Exiv2::CommentValue::CharsetInfo::name(Exiv2::CommentValue::ascii);
    ASSERT_NE(nullptr, n);
    EXPECT_STREQ("Ascii", n);
}

TEST_F(CharsetInfoTest_818, NameForJis_818) {
    const char* n = Exiv2::CommentValue::CharsetInfo::name(Exiv2::CommentValue::jis);
    ASSERT_NE(nullptr, n);
    EXPECT_STREQ("Jis", n);
}

TEST_F(CharsetInfoTest_818, NameForUnicode_818) {
    const char* n = Exiv2::CommentValue::CharsetInfo::name(Exiv2::CommentValue::unicode);
    ASSERT_NE(nullptr, n);
    EXPECT_STREQ("Unicode", n);
}

TEST_F(CharsetInfoTest_818, NameForUndefined_818) {
    const char* n = Exiv2::CommentValue::CharsetInfo::name(Exiv2::CommentValue::undefined);
    ASSERT_NE(nullptr, n);
    EXPECT_STREQ("Undefined", n);
}

// ==================== code() Tests ====================

TEST_F(CharsetInfoTest_818, CodeForAsciiNotNull_818) {
    // Test that code for ascii returns non-null
    const char* c = Exiv2::CommentValue::CharsetInfo::code(Exiv2::CommentValue::ascii);
    ASSERT_NE(nullptr, c);
}

TEST_F(CharsetInfoTest_818, CodeForJisNotNull_818) {
    const char* c = Exiv2::CommentValue::CharsetInfo::code(Exiv2::CommentValue::jis);
    ASSERT_NE(nullptr, c);
}

TEST_F(CharsetInfoTest_818, CodeForUnicodeNotNull_818) {
    const char* c = Exiv2::CommentValue::CharsetInfo::code(Exiv2::CommentValue::unicode);
    ASSERT_NE(nullptr, c);
}

TEST_F(CharsetInfoTest_818, CodeForUndefinedNotNull_818) {
    const char* c = Exiv2::CommentValue::CharsetInfo::code(Exiv2::CommentValue::undefined);
    ASSERT_NE(nullptr, c);
}

// ==================== Round-trip Tests ====================

TEST_F(CharsetInfoTest_818, RoundTripCodeToCharsetIdAscii_818) {
    // Get code for ascii, then get charsetId by that code, should be ascii
    const char* c = Exiv2::CommentValue::CharsetInfo::code(Exiv2::CommentValue::ascii);
    ASSERT_NE(nullptr, c);
    std::string codeStr(c, 8);
    Exiv2::CommentValue::CharsetId id = Exiv2::CommentValue::CharsetInfo::charsetIdByCode(codeStr);
    EXPECT_EQ(Exiv2::CommentValue::ascii, id);
}

TEST_F(CharsetInfoTest_818, RoundTripCodeToCharsetIdUnicode_818) {
    const char* c = Exiv2::CommentValue::CharsetInfo::code(Exiv2::CommentValue::unicode);
    ASSERT_NE(nullptr, c);
    std::string codeStr(c, 8);
    Exiv2::CommentValue::CharsetId id = Exiv2::CommentValue::CharsetInfo::charsetIdByCode(codeStr);
    EXPECT_EQ(Exiv2::CommentValue::unicode, id);
}

TEST_F(CharsetInfoTest_818, RoundTripNameToCharsetIdAllCharsets_818) {
    // For each known charset, verify name -> charsetIdByName round-trip
    Exiv2::CommentValue::CharsetId charsets[] = {
        Exiv2::CommentValue::ascii,
        Exiv2::CommentValue::jis,
        Exiv2::CommentValue::unicode,
        Exiv2::CommentValue::undefined
    };
    for (auto cs : charsets) {
        const char* n = Exiv2::CommentValue::CharsetInfo::name(cs);
        ASSERT_NE(nullptr, n);
        Exiv2::CommentValue::CharsetId id = Exiv2::CommentValue::CharsetInfo::charsetIdByName(n);
        EXPECT_EQ(cs, id) << "Round-trip failed for charset " << n;
    }
}

TEST_F(CharsetInfoTest_818, CharsetIdByCodePartialCodeReturnsInvalid_818) {
    // A partial code (less than 8 chars) that doesn't match should return invalid
    std::string partial("ASCII");
    Exiv2::CommentValue::CharsetId id = Exiv2::CommentValue::CharsetInfo::charsetIdByCode(partial);
    EXPECT_EQ(Exiv2::CommentValue::invalidCharsetId, id);
}

TEST_F(CharsetInfoTest_818, CharsetIdByCodeLongerStringReturnsInvalid_818) {
    // A longer string that doesn't match any 8-byte code
    std::string longer("ASCII000000000000");
    Exiv2::CommentValue::CharsetId id = Exiv2::CommentValue::CharsetInfo::charsetIdByCode(longer);
    EXPECT_EQ(Exiv2::CommentValue::invalidCharsetId, id);
}

}  // namespace
