#include <gtest/gtest.h>
#include <string>
#include <cstring>
#include <climits>
#include <cstdint>
#include "tinyxml2.h"

using namespace tinyxml2;

// =============================================================================
// XMLPrinter Tests
// =============================================================================

class XMLPrinterTest_299 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ---------------------------------------------------------------------------
// PushAttribute with int64_t
// ---------------------------------------------------------------------------

TEST_F(XMLPrinterTest_299, PushAttributeInt64Positive_299) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", (int64_t)42);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val=\"42\""), std::string::npos);
}

TEST_F(XMLPrinterTest_299, PushAttributeInt64Zero_299) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", (int64_t)0);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val=\"0\""), std::string::npos);
}

TEST_F(XMLPrinterTest_299, PushAttributeInt64Negative_299) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", (int64_t)-123456);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val=\"-123456\""), std::string::npos);
}

TEST_F(XMLPrinterTest_299, PushAttributeInt64Max_299) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("maxval", INT64_MAX);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("maxval=\"9223372036854775807\""), std::string::npos);
}

TEST_F(XMLPrinterTest_299, PushAttributeInt64Min_299) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("minval", INT64_MIN);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("minval=\"-9223372036854775808\""), std::string::npos);
}

TEST_F(XMLPrinterTest_299, PushAttributeInt64LargePositive_299) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("big", (int64_t)1000000000000LL);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("big=\"1000000000000\""), std::string::npos);
}

// ---------------------------------------------------------------------------
// PushAttribute with other types
// ---------------------------------------------------------------------------

TEST_F(XMLPrinterTest_299, PushAttributeString_299) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("name", "hello");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("name=\"hello\""), std::string::npos);
}

TEST_F(XMLPrinterTest_299, PushAttributeInt_299) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", 100);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val=\"100\""), std::string::npos);
}

TEST_F(XMLPrinterTest_299, PushAttributeUnsignedInt_299) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", (unsigned int)200);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val=\"200\""), std::string::npos);
}

TEST_F(XMLPrinterTest_299, PushAttributeUint64_299) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", (uint64_t)18446744073709551615ULL);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val=\"18446744073709551615\""), std::string::npos);
}

TEST_F(XMLPrinterTest_299, PushAttributeBoolTrue_299) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("flag", true);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("flag=\"true\""), std::string::npos);
}

TEST_F(XMLPrinterTest_299, PushAttributeBoolFalse_299) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("flag", false);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("flag=\"false\""), std::string::npos);
}

TEST_F(XMLPrinterTest_299, PushAttributeDouble_299) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", 3.14);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val="), std::string::npos);
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

// ---------------------------------------------------------------------------
// Multiple attributes
// ---------------------------------------------------------------------------

TEST_F(XMLPrinterTest_299, MultipleAttributesIncludingInt64_299) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("a", "text");
    printer.PushAttribute("b", (int64_t)999);
    printer.PushAttribute("c", 42);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("a=\"text\""), std::string::npos);
    EXPECT_NE(result.find("b=\"999\""), std::string::npos);
    EXPECT_NE(result.find("c=\"42\""), std::string::npos);
}

// ---------------------------------------------------------------------------
// OpenElement / CloseElement
// ---------------------------------------------------------------------------

TEST_F(XMLPrinterTest_299, OpenAndCloseElement_299) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root/>"), std::string::npos);
}

TEST_F(XMLPrinterTest_299, NestedElements_299) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root>"), std::string::npos);
    EXPECT_NE(result.find("<child/>"), std::string::npos);
    EXPECT_NE(result.find("</root>"), std::string::npos);
}

// ---------------------------------------------------------------------------
// PushText
// ---------------------------------------------------------------------------

TEST_F(XMLPrinterTest_299, PushTextString_299) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText("hello world");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("hello world"), std::string::npos);
}

TEST_F(XMLPrinterTest_299, PushTextInt64_299) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText((int64_t)987654321012345LL);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("987654321012345"), std::string::npos);
}

TEST_F(XMLPrinterTest_299, PushTextUint64_299) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText((uint64_t)12345678901234ULL);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("12345678901234"), std::string::npos);
}

TEST_F(XMLPrinterTest_299, PushTextInt_299) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText(42);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("42"), std::string::npos);
}

TEST_F(XMLPrinterTest_299, PushTextBool_299) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText(true);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("true"), std::string::npos);
}

TEST_F(XMLPrinterTest_299, PushTextFloat_299) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText(1.5f);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("1.5"), std::string::npos);
}

TEST_F(XMLPrinterTest_299, PushTextDouble_299) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText(2.718);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("2.718"), std::string::npos);
}

// ---------------------------------------------------------------------------
// PushComment
// ---------------------------------------------------------------------------

TEST_F(XMLPrinterTest_299, PushComment_299) {
    XMLPrinter printer(nullptr, true);
    printer.PushComment("this is a comment");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!--this is a comment-->"), std::string::npos);
}

// ---------------------------------------------------------------------------
// PushDeclaration
// ---------------------------------------------------------------------------

TEST_F(XMLPrinterTest_299, PushDeclaration_299) {
    XMLPrinter printer(nullptr, true);
    printer.PushDeclaration("xml version=\"1.0\"");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml version=\"1.0\"?>"), std::string::npos);
}

// ---------------------------------------------------------------------------
// PushUnknown
// ---------------------------------------------------------------------------

TEST_F(XMLPrinterTest_299, PushUnknown_299) {
    XMLPrinter printer(nullptr, true);
    printer.PushUnknown("!DOCTYPE html");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!DOCTYPE html>"), std::string::npos);
}

// ---------------------------------------------------------------------------
// PushHeader
// ---------------------------------------------------------------------------

TEST_F(XMLPrinterTest_299, PushHeaderWithDeclaration_299) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(false, true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml"), std::string::npos);
}

TEST_F(XMLPrinterTest_299, PushHeaderWithBOM_299) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(true, false);
    std::string result = printer.CStr();
    // BOM is the UTF-8 byte order mark: 0xEF 0xBB 0xBF
    EXPECT_GE(printer.CStrSize(), (size_t)3);
}

// ---------------------------------------------------------------------------
// CStr and CStrSize
// ---------------------------------------------------------------------------

TEST_F(XMLPrinterTest_299, CStrNotNull_299) {
    XMLPrinter printer(nullptr, true);
    EXPECT_NE(printer.CStr(), nullptr);
}

TEST_F(XMLPrinterTest_299, CStrSizeInitial_299) {
    XMLPrinter printer(nullptr, true);
    // Initially, the buffer should have at least the null terminator
    size_t sz = printer.CStrSize();
    EXPECT_GE(sz, (size_t)1);
}

TEST_F(XMLPrinterTest_299, CStrSizeAfterContent_299) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test");
    printer.CloseElement();
    size_t sz = printer.CStrSize();
    std::string result = printer.CStr();
    // CStrSize should include the null terminator
    EXPECT_EQ(sz, result.size() + 1);
}

// ---------------------------------------------------------------------------
// ClearBuffer
// ---------------------------------------------------------------------------

TEST_F(XMLPrinterTest_299, ClearBuffer_299) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test");
    printer.CloseElement();
    EXPECT_GT(printer.CStrSize(), (size_t)1);
    printer.ClearBuffer();
    // After clearing, the buffer should be essentially empty
    size_t sz = printer.CStrSize();
    EXPECT_LE(sz, (size_t)1);
}

// ---------------------------------------------------------------------------
// Compact vs non-compact mode
// ---------------------------------------------------------------------------

TEST_F(XMLPrinterTest_299, CompactMode_299) {
    XMLPrinter compactPrinter(nullptr, true);
    compactPrinter.OpenElement("root");
    compactPrinter.OpenElement("child");
    compactPrinter.CloseElement();
    compactPrinter.CloseElement();
    std::string compactResult = compactPrinter.CStr();

    XMLPrinter normalPrinter(nullptr, false);
    normalPrinter.OpenElement("root");
    normalPrinter.OpenElement("child");
    normalPrinter.CloseElement();
    normalPrinter.CloseElement();
    std::string normalResult = normalPrinter.CStr();

    // Non-compact should typically be longer due to whitespace/newlines
    EXPECT_GE(normalResult.size(), compactResult.size());
}

// ---------------------------------------------------------------------------
// Element with attribute and text content
// ---------------------------------------------------------------------------

TEST_F(XMLPrinterTest_299, ElementWithAttributeAndText_299) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("item");
    printer.PushAttribute("id", (int64_t)12345);
    printer.PushText("content");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("id=\"12345\""), std::string::npos);
    EXPECT_NE(result.find("content"), std::string::npos);
    EXPECT_NE(result.find("</item>"), std::string::npos);
}

// ---------------------------------------------------------------------------
// PushText with CDATA
// ---------------------------------------------------------------------------

TEST_F(XMLPrinterTest_299, PushTextCDATA_299) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText("some <data>", true);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<![CDATA["), std::string::npos);
    EXPECT_NE(result.find("]]>"), std::string::npos);
}

// ---------------------------------------------------------------------------
// XMLUtil ToStr and To* round-trip tests
// ---------------------------------------------------------------------------

class XMLUtilTest_299 : public ::testing::Test {};

TEST_F(XMLUtilTest_299, ToStrInt_299) {
    char buf[200];
    XMLUtil::ToStr(42, buf, 200);
    EXPECT_STREQ(buf, "42");
}

TEST_F(XMLUtilTest_299, ToStrNegativeInt_299) {
    char buf[200];
    XMLUtil::ToStr(-100, buf, 200);
    EXPECT_STREQ(buf, "-100");
}

TEST_F(XMLUtilTest_299, ToStrUnsigned_299) {
    char buf[200];
    XMLUtil::ToStr((unsigned)4294967295U, buf, 200);
    EXPECT_STREQ(buf, "4294967295");
}

TEST_F(XMLUtilTest_299, ToStrBoolTrue_299) {
    char buf[200];
    XMLUtil::ToStr(true, buf, 200);
    EXPECT_STREQ(buf, "true");
}

TEST_F(XMLUtilTest_299, ToStrBoolFalse_299) {
    char buf[200];
    XMLUtil::ToStr(false, buf, 200);
    EXPECT_STREQ(buf, "false");
}

TEST_F(XMLUtilTest_299, ToStrInt64Positive_299) {
    char buf[200];
    XMLUtil::ToStr((int64_t)9223372036854775807LL, buf, 200);
    EXPECT_STREQ(buf, "9223372036854775807");
}

TEST_F(XMLUtilTest_299, ToStrInt64Negative_299) {
    char buf[200];
    XMLUtil::ToStr((int64_t)-1, buf, 200);
    EXPECT_STREQ(buf, "-1");
}

TEST_F(XMLUtilTest_299, ToStrUint64_299) {
    char buf[200];
    XMLUtil::ToStr((uint64_t)18446744073709551615ULL, buf, 200);
    EXPECT_STREQ(buf, "18446744073709551615");
}

TEST_F(XMLUtilTest_299, ToIntValid_299) {
    int val = 0;
    bool ok = XMLUtil::ToInt("12345", &val);
    EXPECT_TRUE(ok);
    EXPECT_EQ(val, 12345);
}

TEST_F(XMLUtilTest_299, ToIntInvalid_299) {
    int val = 0;
    bool ok = XMLUtil::ToInt("abc", &val);
    EXPECT_FALSE(ok);
}

TEST_F(XMLUtilTest_299, ToUnsignedValid_299) {
    unsigned val = 0;
    bool ok = XMLUtil::ToUnsigned("4294967295", &val);
    EXPECT_TRUE(ok);
    EXPECT_EQ(val, 4294967295U);
}

TEST_F(XMLUtilTest_299, ToUnsignedInvalid_299) {
    unsigned val = 0;
    bool ok = XMLUtil::ToUnsigned("notanumber", &val);
    EXPECT_FALSE(ok);
}

TEST_F(XMLUtilTest_299, ToBoolTrue_299) {
    bool val = false;
    bool ok = XMLUtil::ToBool("true", &val);
    EXPECT_TRUE(ok);
    EXPECT_TRUE(val);
}

TEST_F(XMLUtilTest_299, ToBoolFalse_299) {
    bool val = true;
    bool ok = XMLUtil::ToBool("false", &val);
    EXPECT_TRUE(ok);
    EXPECT_FALSE(val);
}

TEST_F(XMLUtilTest_299, ToBoolInvalid_299) {
    bool val = false;
    bool ok = XMLUtil::ToBool("maybe", &val);
    EXPECT_FALSE(ok);
}

TEST_F(XMLUtilTest_299, ToFloatValid_299) {
    float val = 0;
    bool ok = XMLUtil::ToFloat("3.14", &val);
    EXPECT_TRUE(ok);
    EXPECT_NEAR(val, 3.14f, 0.01f);
}

TEST_F(XMLUtilTest_299, ToFloatInvalid_299) {
    float val = 0;
    bool ok = XMLUtil::ToFloat("xyz", &val);
    EXPECT_FALSE(ok);
}

TEST_F(XMLUtilTest_299, ToDoubleValid_299) {
    double val = 0;
    bool ok = XMLUtil::ToDouble("2.71828", &val);
    EXPECT_TRUE(ok);
    EXPECT_NEAR(val, 2.71828, 0.00001);
}

TEST_F(XMLUtilTest_299, ToDoubleInvalid_299) {
    double val = 0;
    bool ok = XMLUtil::ToDouble("notdouble", &val);
    EXPECT_FALSE(ok);
}

TEST_F(XMLUtilTest_299, ToInt64Valid_299) {
    int64_t val = 0;
    bool ok = XMLUtil::ToInt64("9223372036854775807", &val);
    EXPECT_TRUE(ok);
    EXPECT_EQ(val, INT64_MAX);
}

TEST_F(XMLUtilTest_299, ToInt64Invalid_299) {
    int64_t val = 0;
    bool ok = XMLUtil::ToInt64("abc", &val);
    EXPECT_FALSE(ok);
}

TEST_F(XMLUtilTest_299, ToUnsigned64Valid_299) {
    uint64_t val = 0;
    bool ok = XMLUtil::ToUnsigned64("18446744073709551615", &val);
    EXPECT_TRUE(ok);
    EXPECT_EQ(val, UINT64_MAX);
}

TEST_F(XMLUtilTest_299, ToUnsigned64Invalid_299) {
    uint64_t val = 0;
    bool ok = XMLUtil::ToUnsigned64("xyz", &val);
    EXPECT_FALSE(ok);
}

// ---------------------------------------------------------------------------
// XMLUtil helper functions
// ---------------------------------------------------------------------------

TEST_F(XMLUtilTest_299, IsWhiteSpaceTrue_299) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\n'));
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\r'));
}

TEST_F(XMLUtilTest_299, IsWhiteSpaceFalse_299) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('a'));
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('1'));
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('!'));
}

TEST_F(XMLUtilTest_299, StringEqualSame_299) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello"));
}

TEST_F(XMLUtilTest_299, StringEqualDifferent_299) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world"));
}

TEST_F(XMLUtilTest_299, StringEqualWithLength_299) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "helxyz", 3));
}

TEST_F(XMLUtilTest_299, StringEqualNullBoth_299) {
    EXPECT_TRUE(XMLUtil::StringEqual(nullptr, nullptr));
}

TEST_F(XMLUtilTest_299, StringEqualOneNull_299) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", nullptr));
    EXPECT_FALSE(XMLUtil::StringEqual(nullptr, "hello"));
}

// ---------------------------------------------------------------------------
// XMLUtil ReadBOM
// ---------------------------------------------------------------------------

TEST_F(XMLUtilTest_299, ReadBOMWithBOM_299) {
    const char bom[] = "\xEF\xBB\xBF<root/>";
    bool hasBOM = false;
    const char* result = XMLUtil::ReadBOM(bom, &hasBOM);
    EXPECT_TRUE(hasBOM);
    EXPECT_EQ(result, bom + 3);
}

TEST_F(XMLUtilTest_299, ReadBOMWithoutBOM_299) {
    const char noBom[] = "<root/>";
    bool hasBOM = true;
    const char* result = XMLUtil::ReadBOM(noBom, &hasBOM);
    EXPECT_FALSE(hasBOM);
    EXPECT_EQ(result, noBom);
}

// ---------------------------------------------------------------------------
// XMLPrinter with XMLDocument integration
// ---------------------------------------------------------------------------

TEST_F(XMLPrinterTest_299, PrintDocumentRoundTrip_299) {
    const char* xml = "<root><child attr=\"value\">text</child></root>";
    XMLDocument doc;
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer(nullptr, true);
    doc.Print(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root>"), std::string::npos);
    EXPECT_NE(result.find("<child"), std::string::npos);
    EXPECT_NE(result.find("attr=\"value\""), std::string::npos);
    EXPECT_NE(result.find("text"), std::string::npos);
}

TEST_F(XMLPrinterTest_299, PrintEmptyDocument_299) {
    XMLDocument doc;
    XMLPrinter printer(nullptr, true);
    doc.Print(&printer);
    // Should produce something (possibly empty or just header)
    EXPECT_NE(printer.CStr(), nullptr);
}

// ---------------------------------------------------------------------------
// Int64 round-trip through XMLUtil
// ---------------------------------------------------------------------------

TEST_F(XMLUtilTest_299, Int64RoundTrip_299) {
    char buf[200];
    int64_t original = -9876543210LL;
    XMLUtil::ToStr(original, buf, 200);

    int64_t parsed = 0;
    bool ok = XMLUtil::ToInt64(buf, &parsed);
    EXPECT_TRUE(ok);
    EXPECT_EQ(parsed, original);
}

TEST_F(XMLUtilTest_299, Uint64RoundTrip_299) {
    char buf[200];
    uint64_t original = 12345678901234567ULL;
    XMLUtil::ToStr(original, buf, 200);

    uint64_t parsed = 0;
    bool ok = XMLUtil::ToUnsigned64(buf, &parsed);
    EXPECT_TRUE(ok);
    EXPECT_EQ(parsed, original);
}

// ---------------------------------------------------------------------------
// Edge case: empty attribute name / value
// ---------------------------------------------------------------------------

TEST_F(XMLPrinterTest_299, PushAttributeEmptyName_299) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("", (int64_t)5);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("=\"5\""), std::string::npos);
}

TEST_F(XMLPrinterTest_299, PushAttributeEmptyStringValue_299) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("attr", "");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("attr=\"\""), std::string::npos);
}

// ---------------------------------------------------------------------------
// Multiple elements with int64 attributes
// ---------------------------------------------------------------------------

TEST_F(XMLPrinterTest_299, MultipleElementsWithInt64Attr_299) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("items");
    for (int64_t i = 0; i < 5; ++i) {
        printer.OpenElement("item");
        printer.PushAttribute("id", i);
        printer.CloseElement();
    }
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("id=\"0\""), std::string::npos);
    EXPECT_NE(result.find("id=\"4\""), std::string::npos);
    EXPECT_NE(result.find("</items>"), std::string::npos);
}
