#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

#include "goo/GooString.h"
#include "poppler/Object.h"
#include "poppler/Dict.h"
#include "poppler/PDFDocEncoding.h"
#include "utils/HtmlFonts.h"

// Include the source file to access the static function
// This is necessary since getInfoString is file-static
#include "utils/pdftohtml.cc"

class GetInfoStringTest_2716 : public ::testing::Test {
protected:
    void SetUp() override {
        // Dict requires an XRef, passing nullptr for test purposes
        dict = new Dict(static_cast<XRef *>(nullptr));
    }

    void TearDown() override {
        delete dict;
    }

    Dict *dict;
};

// Test: When key is not present in dictionary, should return nullptr
TEST_F(GetInfoStringTest_2716, NonExistentKeyReturnsNull_2716) {
    auto result = getInfoString(dict, "NonExistent");
    EXPECT_EQ(result, nullptr);
}

// Test: When key maps to a non-string object (e.g., integer), should return nullptr
TEST_F(GetInfoStringTest_2716, NonStringValueReturnsNull_2716) {
    dict->add("IntKey", Object(42));
    auto result = getInfoString(dict, "IntKey");
    EXPECT_EQ(result, nullptr);
}

// Test: When key maps to a simple ASCII string (no BOM), should return encoded string
TEST_F(GetInfoStringTest_2716, SimpleAsciiString_2716) {
    auto str = std::make_unique<GooString>("Hello");
    dict->add("Title", Object(std::move(str)));
    auto result = getInfoString(dict, "Title");
    EXPECT_NE(result, nullptr);
    // The result should contain the filtered version of "Hello"
    EXPECT_FALSE(result->toStr().empty());
}

// Test: When key maps to an empty string, should return a result (possibly empty)
TEST_F(GetInfoStringTest_2716, EmptyString_2716) {
    auto str = std::make_unique<GooString>("");
    dict->add("Author", Object(std::move(str)));
    auto result = getInfoString(dict, "Author");
    EXPECT_NE(result, nullptr);
}

// Test: Unicode string with BOM (0xFE 0xFF prefix)
TEST_F(GetInfoStringTest_2716, UnicodeBOMString_2716) {
    // Create a UTF-16BE string with BOM: U+FEFF followed by 'A' (U+0041) and 'B' (U+0042)
    const char bom_str[] = {'\xFE', '\xFF', '\x00', 'A', '\x00', 'B', '\0'};
    auto str = std::make_unique<GooString>(bom_str, 6);
    dict->add("Subject", Object(std::move(str)));
    auto result = getInfoString(dict, "Subject");
    EXPECT_NE(result, nullptr);
    EXPECT_FALSE(result->toStr().empty());
}

// Test: Unicode string with BOM but no actual characters (just BOM)
TEST_F(GetInfoStringTest_2716, UnicodeBOMOnlyString_2716) {
    const char bom_only[] = {'\xFE', '\xFF'};
    auto str = std::make_unique<GooString>(bom_only, 2);
    dict->add("Keywords", Object(std::move(str)));
    auto result = getInfoString(dict, "Keywords");
    EXPECT_NE(result, nullptr);
}

// Test: Single character non-unicode string
TEST_F(GetInfoStringTest_2716, SingleCharString_2716) {
    auto str = std::make_unique<GooString>("A");
    dict->add("Creator", Object(std::move(str)));
    auto result = getInfoString(dict, "Creator");
    EXPECT_NE(result, nullptr);
}

// Test: PDFDocEncoding special characters (non-ASCII byte values)
TEST_F(GetInfoStringTest_2716, PDFDocEncodingSpecialChars_2716) {
    // Use a character that maps through pdfDocEncoding (e.g., 0x93 = left double quote)
    const char special[] = {'\x93', '\x94', '\0'};
    auto str = std::make_unique<GooString>(special, 2);
    dict->add("Producer", Object(std::move(str)));
    auto result = getInfoString(dict, "Producer");
    EXPECT_NE(result, nullptr);
}

// Test: Unicode string with BOM and odd-length remainder (truncation behavior)
TEST_F(GetInfoStringTest_2716, UnicodeBOMOddLength_2716) {
    // BOM + 3 bytes = odd number of content bytes, last byte should be truncated by integer division
    const char odd_str[] = {'\xFE', '\xFF', '\x00', 'A', '\x00'};
    auto str = std::make_unique<GooString>(odd_str, 5);
    dict->add("OddKey", Object(std::move(str)));
    auto result = getInfoString(dict, "OddKey");
    EXPECT_NE(result, nullptr);
}

// Test: Boolean object returns nullptr
TEST_F(GetInfoStringTest_2716, BoolValueReturnsNull_2716) {
    dict->add("BoolKey", Object(true));
    auto result = getInfoString(dict, "BoolKey");
    EXPECT_EQ(result, nullptr);
}

// Test: Null object returns nullptr
TEST_F(GetInfoStringTest_2716, NullValueReturnsNull_2716) {
    dict->add("NullKey", Object::null());
    auto result = getInfoString(dict, "NullKey");
    EXPECT_EQ(result, nullptr);
}

// Test: String with HTML-like characters that HtmlFilter might process
TEST_F(GetInfoStringTest_2716, StringWithHtmlChars_2716) {
    auto str = std::make_unique<GooString>("<b>Test</b>");
    dict->add("HtmlKey", Object(std::move(str)));
    auto result = getInfoString(dict, "HtmlKey");
    EXPECT_NE(result, nullptr);
}

// Test: Unicode string with non-ASCII unicode characters
TEST_F(GetInfoStringTest_2716, UnicodeNonAsciiChars_2716) {
    // BOM + U+00E9 (é) + U+00F1 (ñ)
    const char uni_str[] = {'\xFE', '\xFF', '\x00', '\xE9', '\x00', '\xF1'};
    auto str = std::make_unique<GooString>(uni_str, 6);
    dict->add("UniKey", Object(std::move(str)));
    auto result = getInfoString(dict, "UniKey");
    EXPECT_NE(result, nullptr);
}

// Test: Lookup with nullptr key behavior - edge case
TEST_F(GetInfoStringTest_2716, LongAsciiString_2716) {
    std::string longStr(1000, 'X');
    auto str = std::make_unique<GooString>(longStr);
    dict->add("LongKey", Object(std::move(str)));
    auto result = getInfoString(dict, "LongKey");
    EXPECT_NE(result, nullptr);
    EXPECT_FALSE(result->toStr().empty());
}
