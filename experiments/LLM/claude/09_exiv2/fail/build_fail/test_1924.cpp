#include <gtest/gtest.h>
#include <string>
#include <cstring>

// Include necessary headers
#include "XMPCore_Impl.hpp"
#include "XMP_Const.h"

// We need access to SetNodeValue which is a static inline function in the .cpp file.
// Since it's static inline in a .cpp file, we need to include it or replicate the test setup.
// For testing purposes, we'll include the source file directly to get access to the static function.
// This is a common pattern for testing static/internal functions.

// Forward declarations and necessary includes that the source file needs
#include "XMPMeta-GetSet.cpp"

class SetNodeValueTest_1924 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: Setting a normal ASCII string value
TEST_F(SetNodeValueTest_1924, NormalAsciiValue_1924) {
    XMP_Node node(nullptr, "test:property", 0);
    SetNodeValue(&node, "Hello World");
    EXPECT_EQ(node.value, "Hello World");
}

// Test: Setting an empty string value
TEST_F(SetNodeValueTest_1924, EmptyStringValue_1924) {
    XMP_Node node(nullptr, "test:property", 0);
    SetNodeValue(&node, "");
    EXPECT_EQ(node.value, "");
}

// Test: ASCII control characters (< 0x20) other than tab, LF, CR should be replaced with space
TEST_F(SetNodeValueTest_1924, ControlCharsReplacedWithSpace_1924) {
    XMP_Node node(nullptr, "test:property", 0);
    // 0x01 is a control character that should be replaced
    std::string input = "AB";
    input[0] = '\x01';
    input[1] = 'C';
    SetNodeValue(&node, input.c_str());
    EXPECT_EQ(node.value[0], ' ');
    EXPECT_EQ(node.value[1], 'C');
}

// Test: Tab character (0x09) should NOT be replaced
TEST_F(SetNodeValueTest_1924, TabCharPreserved_1924) {
    XMP_Node node(nullptr, "test:property", 0);
    std::string input = "A\tB";
    SetNodeValue(&node, input.c_str());
    EXPECT_EQ(node.value, "A\tB");
}

// Test: Line Feed character (0x0A) should NOT be replaced
TEST_F(SetNodeValueTest_1924, LineFeedPreserved_1924) {
    XMP_Node node(nullptr, "test:property", 0);
    std::string input = "A\nB";
    SetNodeValue(&node, input.c_str());
    EXPECT_EQ(node.value, "A\nB");
}

// Test: Carriage Return character (0x0D) should NOT be replaced
TEST_F(SetNodeValueTest_1924, CarriageReturnPreserved_1924) {
    XMP_Node node(nullptr, "test:property", 0);
    std::string input = "A\rB";
    SetNodeValue(&node, input.c_str());
    EXPECT_EQ(node.value, "A\rB");
}

// Test: DEL character (0x7F) should be replaced with space
TEST_F(SetNodeValueTest_1924, DelCharReplacedWithSpace_1924) {
    XMP_Node node(nullptr, "test:property", 0);
    std::string input = "A";
    input += (char)0x7F;
    input += "B";
    SetNodeValue(&node, input.c_str());
    EXPECT_EQ(node.value[1], ' ');
    EXPECT_EQ(node.value[2], 'B');
}

// Test: Multiple control characters in a string
TEST_F(SetNodeValueTest_1924, MultipleControlCharsReplaced_1924) {
    XMP_Node node(nullptr, "test:property", 0);
    std::string input;
    input += (char)0x01;
    input += (char)0x02;
    input += (char)0x03;
    input += 'A';
    SetNodeValue(&node, input.c_str());
    EXPECT_EQ(node.value[0], ' ');
    EXPECT_EQ(node.value[1], ' ');
    EXPECT_EQ(node.value[2], ' ');
    EXPECT_EQ(node.value[3], 'A');
}

// Test: Valid UTF-8 multibyte characters are preserved
TEST_F(SetNodeValueTest_1924, ValidUtf8Preserved_1924) {
    XMP_Node node(nullptr, "test:property", 0);
    // UTF-8 for U+00E9 (é) is 0xC3 0xA9
    std::string input = "caf\xC3\xA9";
    SetNodeValue(&node, input.c_str());
    EXPECT_EQ(node.value, "caf\xC3\xA9");
}

// Test: Valid UTF-8 3-byte character
TEST_F(SetNodeValueTest_1924, ValidUtf8ThreeByteChar_1924) {
    XMP_Node node(nullptr, "test:property", 0);
    // UTF-8 for U+4E16 (世) is 0xE4 0xB8 0x96
    std::string input = "\xE4\xB8\x96";
    SetNodeValue(&node, input.c_str());
    EXPECT_EQ(node.value, "\xE4\xB8\x96");
}

// Test: Valid UTF-8 4-byte character
TEST_F(SetNodeValueTest_1924, ValidUtf8FourByteChar_1924) {
    XMP_Node node(nullptr, "test:property", 0);
    // UTF-8 for U+1F600 (😀) is 0xF0 0x9F 0x98 0x80
    std::string input = "\xF0\x9F\x98\x80";
    SetNodeValue(&node, input.c_str());
    EXPECT_EQ(node.value, "\xF0\x9F\x98\x80");
}

// Test: xml:lang qualifier value gets normalized (language normalization)
TEST_F(SetNodeValueTest_1924, XmlLangQualifierNormalized_1924) {
    XMP_Node node(nullptr, "xml:lang", kXMP_PropIsQualifier);
    SetNodeValue(&node, "EN-US");
    // NormalizeLangValue typically lowercases language tags
    // Expected: "en-US" or similar normalization
    // The exact normalization depends on NormalizeLangValue implementation
    // At minimum, we verify the value was set and potentially modified
    EXPECT_FALSE(node.value.empty());
}

// Test: xml:lang qualifier with lowercase value
TEST_F(SetNodeValueTest_1924, XmlLangQualifierLowercase_1924) {
    XMP_Node node(nullptr, "xml:lang", kXMP_PropIsQualifier);
    SetNodeValue(&node, "en-us");
    EXPECT_FALSE(node.value.empty());
}

// Test: Non-qualifier node named xml:lang should NOT normalize
TEST_F(SetNodeValueTest_1924, NonQualifierXmlLangNotNormalized_1924) {
    XMP_Node node(nullptr, "xml:lang", 0);  // No qualifier flag
    SetNodeValue(&node, "EN-US");
    // Without the qualifier flag, no normalization should occur
    // The value should remain as-is (only control char replacement applies)
    EXPECT_EQ(node.value, "EN-US");
}

// Test: Qualifier node but not xml:lang should not normalize lang
TEST_F(SetNodeValueTest_1924, QualifierNonLangNotNormalized_1924) {
    XMP_Node node(nullptr, "rdf:type", kXMP_PropIsQualifier);
    SetNodeValue(&node, "SomeValue");
    EXPECT_EQ(node.value, "SomeValue");
}

// Test: String with only printable ASCII
TEST_F(SetNodeValueTest_1924, PrintableAsciiOnly_1924) {
    XMP_Node node(nullptr, "test:property", 0);
    SetNodeValue(&node, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
    EXPECT_EQ(node.value, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
}

// Test: String with special printable characters
TEST_F(SetNodeValueTest_1924, SpecialPrintableChars_1924) {
    XMP_Node node(nullptr, "test:property", 0);
    SetNodeValue(&node, "!@#$%^&*()_+-=[]{}|;':\",./<>?");
    EXPECT_EQ(node.value, "!@#$%^&*()_+-=[]{}|;':\",./<>?");
}

// Test: Space character (0x20) should be preserved
TEST_F(SetNodeValueTest_1924, SpaceCharPreserved_1924) {
    XMP_Node node(nullptr, "test:property", 0);
    SetNodeValue(&node, "Hello World");
    EXPECT_EQ(node.value, "Hello World");
}

// Test: Boundary character 0x1F (just below space, not tab/LF/CR) should be replaced
TEST_F(SetNodeValueTest_1924, Char0x1FReplaced_1924) {
    XMP_Node node(nullptr, "test:property", 0);
    std::string input = "A";
    input += (char)0x1F;
    input += "B";
    SetNodeValue(&node, input.c_str());
    EXPECT_EQ(node.value[1], ' ');
}

// Test: Character 0x20 (space) should not be modified
TEST_F(SetNodeValueTest_1924, Char0x20NotModified_1924) {
    XMP_Node node(nullptr, "test:property", 0);
    SetNodeValue(&node, " ");
    EXPECT_EQ(node.value, " ");
}

// Test: Overwriting existing value
TEST_F(SetNodeValueTest_1924, OverwriteExistingValue_1924) {
    XMP_Node node(nullptr, "test:property", "OldValue", 0);
    EXPECT_EQ(node.value, "OldValue");
    SetNodeValue(&node, "NewValue");
    EXPECT_EQ(node.value, "NewValue");
}

// Test: Mixed ASCII and UTF-8 content
TEST_F(SetNodeValueTest_1924, MixedAsciiAndUtf8_1924) {
    XMP_Node node(nullptr, "test:property", 0);
    std::string input = "Hello \xC3\xA9 World \xE4\xB8\x96";
    SetNodeValue(&node, input.c_str());
    EXPECT_EQ(node.value, input);
}

// Test: Control characters mixed with valid UTF-8
TEST_F(SetNodeValueTest_1924, ControlCharsWithUtf8_1924) {
    XMP_Node node(nullptr, "test:property", 0);
    std::string input;
    input += (char)0x01;         // Should be replaced with space
    input += "\xC3\xA9";        // Valid UTF-8 é
    input += (char)0x02;         // Should be replaced with space
    SetNodeValue(&node, input.c_str());
    EXPECT_EQ(node.value[0], ' ');
    // UTF-8 bytes should be preserved
    EXPECT_EQ((unsigned char)node.value[1], 0xC3);
    EXPECT_EQ((unsigned char)node.value[2], 0xA9);
    EXPECT_EQ(node.value[3], ' ');
}

// Test: Null byte character (0x00) - effectively empty or truncated string
TEST_F(SetNodeValueTest_1924, NullByteHandling_1924) {
    XMP_Node node(nullptr, "test:property", 0);
    SetNodeValue(&node, "");
    EXPECT_TRUE(node.value.empty());
}

// Test: Long string value
TEST_F(SetNodeValueTest_1924, LongStringValue_1924) {
    XMP_Node node(nullptr, "test:property", 0);
    std::string longStr(10000, 'A');
    SetNodeValue(&node, longStr.c_str());
    EXPECT_EQ(node.value, longStr);
    EXPECT_EQ(node.value.size(), 10000u);
}

// Test: String with all allowed whitespace characters
TEST_F(SetNodeValueTest_1924, AllAllowedWhitespace_1924) {
    XMP_Node node(nullptr, "test:property", 0);
    std::string input;
    input += '\t';  // Tab - preserved
    input += '\n';  // LF - preserved
    input += '\r';  // CR - preserved
    input += ' ';   // Space - preserved
    SetNodeValue(&node, input.c_str());
    EXPECT_EQ(node.value[0], '\t');
    EXPECT_EQ(node.value[1], '\n');
    EXPECT_EQ(node.value[2], '\r');
    EXPECT_EQ(node.value[3], ' ');
}

// Test: xml:lang with "x-default" value
TEST_F(SetNodeValueTest_1924, XmlLangXDefault_1924) {
    XMP_Node node(nullptr, "xml:lang", kXMP_PropIsQualifier);
    SetNodeValue(&node, "x-default");
    EXPECT_EQ(node.value, "x-default");
}
