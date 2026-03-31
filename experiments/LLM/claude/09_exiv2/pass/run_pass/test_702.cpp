#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/value.hpp>
#include <string>

using namespace Exiv2;

class IptcDataDetectCharsetTest_702 : public ::testing::Test {
protected:
    IptcData iptcData_;
};

// Test: Empty IptcData should return "ASCII"
TEST_F(IptcDataDetectCharsetTest_702, EmptyData_ReturnsASCII_702) {
    const char* result = iptcData_.detectCharset();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "ASCII");
}

// Test: When CharacterSet envelope is set to ESC %G (UTF-8 designation), return "UTF-8"
TEST_F(IptcDataDetectCharsetTest_702, CharacterSetEnvelopeUTF8_ReturnsUTF8_702) {
    Iptcdatum datum(IptcKey("Iptc.Envelope.CharacterSet"), nullptr);
    // ESC %G = \033%G
    datum.setValue("\033%G");
    iptcData_.add(datum);

    const char* result = iptcData_.detectCharset();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "UTF-8");
}

// Test: Pure ASCII data without CharacterSet envelope returns "ASCII"
TEST_F(IptcDataDetectCharsetTest_702, PureASCIIData_ReturnsASCII_702) {
    Iptcdatum datum(IptcKey("Iptc.Application2.Caption"), nullptr);
    datum.setValue("Hello World");
    iptcData_.add(datum);

    const char* result = iptcData_.detectCharset();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "ASCII");
}

// Test: Valid UTF-8 multibyte data returns "UTF-8"
TEST_F(IptcDataDetectCharsetTest_702, ValidUTF8Data_ReturnsUTF8_702) {
    Iptcdatum datum(IptcKey("Iptc.Application2.Caption"), nullptr);
    // "Ü" in UTF-8 is 0xC3 0x9C (two-byte sequence)
    std::string utf8str;
    utf8str += static_cast<char>(0xC3);
    utf8str += static_cast<char>(0x9C);
    datum.setValue(utf8str);
    iptcData_.add(datum);

    const char* result = iptcData_.detectCharset();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "UTF-8");
}

// Test: Valid UTF-8 three-byte sequence returns "UTF-8"
TEST_F(IptcDataDetectCharsetTest_702, ValidUTF8ThreeByteSequence_ReturnsUTF8_702) {
    Iptcdatum datum(IptcKey("Iptc.Application2.Caption"), nullptr);
    // Euro sign € in UTF-8 is 0xE2 0x82 0xAC
    std::string utf8str;
    utf8str += static_cast<char>(0xE2);
    utf8str += static_cast<char>(0x82);
    utf8str += static_cast<char>(0xAC);
    datum.setValue(utf8str);
    iptcData_.add(datum);

    const char* result = iptcData_.detectCharset();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "UTF-8");
}

// Test: Valid UTF-8 four-byte sequence returns "UTF-8"
TEST_F(IptcDataDetectCharsetTest_702, ValidUTF8FourByteSequence_ReturnsUTF8_702) {
    Iptcdatum datum(IptcKey("Iptc.Application2.Caption"), nullptr);
    // U+1F600 (grinning face) in UTF-8: 0xF0 0x9F 0x98 0x80
    std::string utf8str;
    utf8str += static_cast<char>(0xF0);
    utf8str += static_cast<char>(0x9F);
    utf8str += static_cast<char>(0x98);
    utf8str += static_cast<char>(0x80);
    datum.setValue(utf8str);
    iptcData_.add(datum);

    const char* result = iptcData_.detectCharset();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "UTF-8");
}

// Test: Invalid encoding (not ASCII, not UTF-8) returns nullptr
TEST_F(IptcDataDetectCharsetTest_702, InvalidEncoding_ReturnsNullptr_702) {
    Iptcdatum datum(IptcKey("Iptc.Application2.Caption"), nullptr);
    // 0xFE alone is not valid UTF-8 lead byte (it would need 5 continuation bytes per the code,
    // but 0xFF is never valid). Actually 0xFE => (c & 0xfe) == 0xfc is false, (c & 0xfc) == 0xf8 is false,
    // so it should fall to utf8 = false.
    // Let's use 0xFF which doesn't match any pattern
    std::string badstr;
    badstr += static_cast<char>(0xFF);
    datum.setValue(badstr);
    iptcData_.add(datum);

    const char* result = iptcData_.detectCharset();
    EXPECT_EQ(result, nullptr);
}

// Test: Incomplete UTF-8 sequence (unterminated) returns nullptr
TEST_F(IptcDataDetectCharsetTest_702, IncompleteUTF8Sequence_ReturnsNullptr_702) {
    Iptcdatum datum(IptcKey("Iptc.Application2.Caption"), nullptr);
    // Start of a two-byte sequence but no continuation byte
    std::string badstr;
    badstr += static_cast<char>(0xC3);  // expects 1 continuation byte
    // No continuation byte follows
    datum.setValue(badstr);
    iptcData_.add(datum);

    const char* result = iptcData_.detectCharset();
    EXPECT_EQ(result, nullptr);
}

// Test: Invalid continuation byte in UTF-8 sequence returns nullptr
TEST_F(IptcDataDetectCharsetTest_702, InvalidContinuationByte_ReturnsNullptr_702) {
    Iptcdatum datum(IptcKey("Iptc.Application2.Caption"), nullptr);
    // Two-byte sequence start followed by invalid continuation
    std::string badstr;
    badstr += static_cast<char>(0xC3);  // expects 1 continuation byte
    badstr += static_cast<char>(0x41);  // 'A' - not a valid continuation byte (0x41 & 0xC0 != 0x80)
    datum.setValue(badstr);
    iptcData_.add(datum);

    const char* result = iptcData_.detectCharset();
    EXPECT_EQ(result, nullptr);
}

// Test: Mixed ASCII and valid UTF-8 returns "UTF-8"
TEST_F(IptcDataDetectCharsetTest_702, MixedASCIIandUTF8_ReturnsUTF8_702) {
    Iptcdatum datum(IptcKey("Iptc.Application2.Caption"), nullptr);
    std::string mixedstr = "Hello ";
    mixedstr += static_cast<char>(0xC3);
    mixedstr += static_cast<char>(0x9C);  // Ü
    mixedstr += " World";
    datum.setValue(mixedstr);
    iptcData_.add(datum);

    const char* result = iptcData_.detectCharset();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "UTF-8");
}

// Test: Multiple IPTC entries, all ASCII, returns "ASCII"
TEST_F(IptcDataDetectCharsetTest_702, MultipleASCIIEntries_ReturnsASCII_702) {
    Iptcdatum datum1(IptcKey("Iptc.Application2.Caption"), nullptr);
    datum1.setValue("Hello");
    iptcData_.add(datum1);

    Iptcdatum datum2(IptcKey("Iptc.Application2.Keywords"), nullptr);
    datum2.setValue("World");
    iptcData_.add(datum2);

    const char* result = iptcData_.detectCharset();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "ASCII");
}

// Test: Multiple entries, one with valid UTF-8 returns "UTF-8"
TEST_F(IptcDataDetectCharsetTest_702, MultipleEntriesOneUTF8_ReturnsUTF8_702) {
    Iptcdatum datum1(IptcKey("Iptc.Application2.Caption"), nullptr);
    datum1.setValue("Hello");
    iptcData_.add(datum1);

    Iptcdatum datum2(IptcKey("Iptc.Application2.Keywords"), nullptr);
    std::string utf8str;
    utf8str += static_cast<char>(0xC3);
    utf8str += static_cast<char>(0xBC);  // ü
    datum2.setValue(utf8str);
    iptcData_.add(datum2);

    const char* result = iptcData_.detectCharset();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "UTF-8");
}

// Test: Multiple entries, one with invalid encoding returns nullptr
TEST_F(IptcDataDetectCharsetTest_702, MultipleEntriesOneInvalid_ReturnsNullptr_702) {
    Iptcdatum datum1(IptcKey("Iptc.Application2.Caption"), nullptr);
    datum1.setValue("Hello");
    iptcData_.add(datum1);

    Iptcdatum datum2(IptcKey("Iptc.Application2.Keywords"), nullptr);
    std::string badstr;
    badstr += static_cast<char>(0xFF);
    datum2.setValue(badstr);
    iptcData_.add(datum2);

    const char* result = iptcData_.detectCharset();
    EXPECT_EQ(result, nullptr);
}

// Test: CharacterSet envelope with non-UTF-8 value, with ASCII data returns "ASCII"
TEST_F(IptcDataDetectCharsetTest_702, CharacterSetEnvelopeNonUTF8WithASCII_ReturnsASCII_702) {
    Iptcdatum datum(IptcKey("Iptc.Envelope.CharacterSet"), nullptr);
    datum.setValue("SomeOtherCharset");
    iptcData_.add(datum);

    Iptcdatum datum2(IptcKey("Iptc.Application2.Caption"), nullptr);
    datum2.setValue("Hello");
    iptcData_.add(datum2);

    const char* result = iptcData_.detectCharset();
    ASSERT_NE(result, nullptr);
    // The CharacterSet is not ESC %G, so it falls through to character analysis
    // All data is ASCII
    EXPECT_STREQ(result, "ASCII");
}

// Test: Latin-1 encoded data (single high byte like 0x80-0xBF not valid UTF-8 start) returns nullptr
TEST_F(IptcDataDetectCharsetTest_702, Latin1SingleHighByte_ReturnsNullptr_702) {
    Iptcdatum datum(IptcKey("Iptc.Application2.Caption"), nullptr);
    // 0x80 alone: (0x80 & 0xe0) == 0xc0? 0x80 & 0xe0 = 0x80, no.
    // (0x80 & 0xc0) == 0x80 but it's not in the lead byte check path correctly
    // Actually the code checks: c & 0x80 is true (non-ASCII), then checks patterns:
    // 0x80 & 0xe0 = 0x80 (not 0xc0), 0x80 & 0xf0 = 0x80 (not 0xe0), etc. => utf8 = false
    std::string latin1str;
    latin1str += static_cast<char>(0x80);
    datum.setValue(latin1str);
    iptcData_.add(datum);

    const char* result = iptcData_.detectCharset();
    EXPECT_EQ(result, nullptr);
}

// Test: Three-byte UTF-8 sequence with incomplete continuation returns nullptr
TEST_F(IptcDataDetectCharsetTest_702, ThreeByteSequenceIncomplete_ReturnsNullptr_702) {
    Iptcdatum datum(IptcKey("Iptc.Application2.Caption"), nullptr);
    // 0xE2 expects 2 continuation bytes, but only 1 provided
    std::string badstr;
    badstr += static_cast<char>(0xE2);
    badstr += static_cast<char>(0x82);
    // Missing third byte
    datum.setValue(badstr);
    iptcData_.add(datum);

    const char* result = iptcData_.detectCharset();
    EXPECT_EQ(result, nullptr);
}

// Test: Empty string value should be treated as ASCII
TEST_F(IptcDataDetectCharsetTest_702, EmptyStringValue_ReturnsASCII_702) {
    Iptcdatum datum(IptcKey("Iptc.Application2.Caption"), nullptr);
    datum.setValue("");
    iptcData_.add(datum);

    const char* result = iptcData_.detectCharset();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "ASCII");
}

// Test: Five-byte UTF-8 sequence (0xF8 lead) followed by proper continuation
TEST_F(IptcDataDetectCharsetTest_702, FiveByteSequenceValid_ReturnsUTF8_702) {
    Iptcdatum datum(IptcKey("Iptc.Application2.Caption"), nullptr);
    // 0xF8 => (c & 0xfc) == 0xf8 => seqCount = 4 (needs 4 continuation bytes)
    std::string str;
    str += static_cast<char>(0xF8);
    str += static_cast<char>(0x80);
    str += static_cast<char>(0x80);
    str += static_cast<char>(0x80);
    str += static_cast<char>(0x80);
    datum.setValue(str);
    iptcData_.add(datum);

    const char* result = iptcData_.detectCharset();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "UTF-8");
}

// Test: Six-byte UTF-8 sequence (0xFC lead) followed by proper continuation
TEST_F(IptcDataDetectCharsetTest_702, SixByteSequenceValid_ReturnsUTF8_702) {
    Iptcdatum datum(IptcKey("Iptc.Application2.Caption"), nullptr);
    // 0xFC => (c & 0xfe) == 0xfc => seqCount = 5 (needs 5 continuation bytes)
    std::string str;
    str += static_cast<char>(0xFC);
    str += static_cast<char>(0x80);
    str += static_cast<char>(0x80);
    str += static_cast<char>(0x80);
    str += static_cast<char>(0x80);
    str += static_cast<char>(0x80);
    datum.setValue(str);
    iptcData_.add(datum);

    const char* result = iptcData_.detectCharset();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "UTF-8");
}
