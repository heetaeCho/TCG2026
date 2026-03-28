#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include <climits>
#include <cstdint>
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for XMLPrinter tests
class XMLPrinterTest_306 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== PushText(int64_t) Tests ====================

TEST_F(XMLPrinterTest_306, PushTextInt64PositiveValue_306) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(static_cast<int64_t>(42));
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("42"), std::string::npos);
}

TEST_F(XMLPrinterTest_306, PushTextInt64Zero_306) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(static_cast<int64_t>(0));
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("0"), std::string::npos);
}

TEST_F(XMLPrinterTest_306, PushTextInt64NegativeValue_306) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(static_cast<int64_t>(-123));
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("-123"), std::string::npos);
}

TEST_F(XMLPrinterTest_306, PushTextInt64MaxValue_306) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(INT64_MAX);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    // INT64_MAX = 9223372036854775807
    EXPECT_NE(result.find("9223372036854775807"), std::string::npos);
}

TEST_F(XMLPrinterTest_306, PushTextInt64MinValue_306) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(INT64_MIN);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    // INT64_MIN = -9223372036854775808
    EXPECT_NE(result.find("-9223372036854775808"), std::string::npos);
}

TEST_F(XMLPrinterTest_306, PushTextInt64LargePositive_306) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(static_cast<int64_t>(1000000000000LL));
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("1000000000000"), std::string::npos);
}

TEST_F(XMLPrinterTest_306, PushTextInt64LargeNegative_306) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(static_cast<int64_t>(-999999999999LL));
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("-999999999999"), std::string::npos);
}

// ==================== PushText other overloads ====================

TEST_F(XMLPrinterTest_306, PushTextInt_306) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(static_cast<int>(100));
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("100"), std::string::npos);
}

TEST_F(XMLPrinterTest_306, PushTextUnsignedInt_306) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(static_cast<unsigned int>(255));
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("255"), std::string::npos);
}

TEST_F(XMLPrinterTest_306, PushTextUint64_306) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(static_cast<uint64_t>(18446744073709551615ULL));
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("18446744073709551615"), std::string::npos);
}

TEST_F(XMLPrinterTest_306, PushTextBoolTrue_306) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("true"), std::string::npos);
}

TEST_F(XMLPrinterTest_306, PushTextBoolFalse_306) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(false);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("false"), std::string::npos);
}

TEST_F(XMLPrinterTest_306, PushTextFloat_306) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(3.14f);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

TEST_F(XMLPrinterTest_306, PushTextDouble_306) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(2.718281828);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("2.718"), std::string::npos);
}

TEST_F(XMLPrinterTest_306, PushTextString_306) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText("hello world", false);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("hello world"), std::string::npos);
}

TEST_F(XMLPrinterTest_306, PushTextStringCdata_306) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText("cdata content", true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("cdata content"), std::string::npos);
    EXPECT_NE(result.find("<![CDATA["), std::string::npos);
}

// ==================== XMLPrinter general functionality ====================

TEST_F(XMLPrinterTest_306, OpenAndCloseElement_306) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test");
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<test"), std::string::npos);
    EXPECT_NE(result.find("/>"), std::string::npos);
}

TEST_F(XMLPrinterTest_306, OpenElementWithContent_306) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test", true);
    printer.PushText("content", false);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<test>"), std::string::npos);
    EXPECT_NE(result.find("content"), std::string::npos);
    EXPECT_NE(result.find("</test>"), std::string::npos);
}

TEST_F(XMLPrinterTest_306, PushAttributeString_306) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test", true);
    printer.PushAttribute("key", "value");
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("key=\"value\""), std::string::npos);
}

TEST_F(XMLPrinterTest_306, PushAttributeInt_306) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test", true);
    printer.PushAttribute("num", 42);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("num=\"42\""), std::string::npos);
}

TEST_F(XMLPrinterTest_306, PushAttributeInt64_306) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test", true);
    printer.PushAttribute("big", static_cast<int64_t>(9999999999LL));
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("big=\"9999999999\""), std::string::npos);
}

TEST_F(XMLPrinterTest_306, PushAttributeUint64_306) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test", true);
    printer.PushAttribute("ubig", static_cast<uint64_t>(12345678901234ULL));
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("ubig=\"12345678901234\""), std::string::npos);
}

TEST_F(XMLPrinterTest_306, PushAttributeBool_306) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test", true);
    printer.PushAttribute("flag", true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("flag=\"true\""), std::string::npos);
}

TEST_F(XMLPrinterTest_306, PushAttributeDouble_306) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test", true);
    printer.PushAttribute("val", 1.5);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val="), std::string::npos);
}

TEST_F(XMLPrinterTest_306, PushComment_306) {
    XMLPrinter printer(nullptr, true);
    printer.PushComment("this is a comment");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!--this is a comment-->"), std::string::npos);
}

TEST_F(XMLPrinterTest_306, PushDeclaration_306) {
    XMLPrinter printer(nullptr, true);
    printer.PushDeclaration("xml version=\"1.0\"");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml version=\"1.0\"?>"), std::string::npos);
}

TEST_F(XMLPrinterTest_306, PushUnknown_306) {
    XMLPrinter printer(nullptr, true);
    printer.PushUnknown("something");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!something>"), std::string::npos);
}

TEST_F(XMLPrinterTest_306, CStrSizeNonEmpty_306) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.CloseElement(true);
    EXPECT_GT(printer.CStrSize(), static_cast<size_t>(0));
}

TEST_F(XMLPrinterTest_306, ClearBuffer_306) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.CloseElement(true);
    EXPECT_GT(printer.CStrSize(), static_cast<size_t>(0));
    printer.ClearBuffer();
    // After clearing, the buffer should be essentially empty (just null terminator or minimal)
    EXPECT_LE(printer.CStrSize(), static_cast<size_t>(1));
}

TEST_F(XMLPrinterTest_306, PushHeader_306) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(false, true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml"), std::string::npos);
}

TEST_F(XMLPrinterTest_306, PushHeaderWithBOM_306) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(true, true);
    std::string result = printer.CStr();
    // BOM bytes should be present at the start: 0xEF, 0xBB, 0xBF
    EXPECT_GE(result.size(), static_cast<size_t>(3));
}

TEST_F(XMLPrinterTest_306, NestedElements_306) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("outer", true);
    printer.OpenElement("inner", true);
    printer.PushText(static_cast<int64_t>(99));
    printer.CloseElement(true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<outer>"), std::string::npos);
    EXPECT_NE(result.find("<inner>"), std::string::npos);
    EXPECT_NE(result.find("99"), std::string::npos);
    EXPECT_NE(result.find("</inner>"), std::string::npos);
    EXPECT_NE(result.find("</outer>"), std::string::npos);
}

TEST_F(XMLPrinterTest_306, MultipleTextPushes_306) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(static_cast<int64_t>(1));
    printer.PushText(static_cast<int64_t>(2));
    printer.PushText(static_cast<int64_t>(3));
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("1"), std::string::npos);
    EXPECT_NE(result.find("2"), std::string::npos);
    EXPECT_NE(result.find("3"), std::string::npos);
}

TEST_F(XMLPrinterTest_306, CompactModeVsNonCompact_306) {
    XMLPrinter compactPrinter(nullptr, true);
    compactPrinter.OpenElement("root");
    compactPrinter.OpenElement("child");
    compactPrinter.PushText(static_cast<int64_t>(42));
    compactPrinter.CloseElement();
    compactPrinter.CloseElement();
    std::string compactResult = compactPrinter.CStr();

    XMLPrinter nonCompactPrinter(nullptr, false);
    nonCompactPrinter.OpenElement("root");
    nonCompactPrinter.OpenElement("child");
    nonCompactPrinter.PushText(static_cast<int64_t>(42));
    nonCompactPrinter.CloseElement();
    nonCompactPrinter.CloseElement();
    std::string nonCompactResult = nonCompactPrinter.CStr();

    // Non-compact mode should generally produce larger output (with whitespace/newlines)
    EXPECT_GE(nonCompactResult.size(), compactResult.size());
}

// ==================== XMLUtil Tests ====================

class XMLUtilTest_306 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(XMLUtilTest_306, ToStrInt64Positive_306) {
    char buf[200];
    XMLUtil::ToStr(static_cast<int64_t>(42), buf, 200);
    EXPECT_STREQ(buf, "42");
}

TEST_F(XMLUtilTest_306, ToStrInt64Zero_306) {
    char buf[200];
    XMLUtil::ToStr(static_cast<int64_t>(0), buf, 200);
    EXPECT_STREQ(buf, "0");
}

TEST_F(XMLUtilTest_306, ToStrInt64Negative_306) {
    char buf[200];
    XMLUtil::ToStr(static_cast<int64_t>(-500), buf, 200);
    EXPECT_STREQ(buf, "-500");
}

TEST_F(XMLUtilTest_306, ToStrInt64Max_306) {
    char buf[200];
    XMLUtil::ToStr(INT64_MAX, buf, 200);
    EXPECT_STREQ(buf, "9223372036854775807");
}

TEST_F(XMLUtilTest_306, ToStrInt64Min_306) {
    char buf[200];
    XMLUtil::ToStr(INT64_MIN, buf, 200);
    EXPECT_STREQ(buf, "-9223372036854775808");
}

TEST_F(XMLUtilTest_306, ToStrUint64_306) {
    char buf[200];
    XMLUtil::ToStr(static_cast<uint64_t>(18446744073709551615ULL), buf, 200);
    EXPECT_STREQ(buf, "18446744073709551615");
}

TEST_F(XMLUtilTest_306, ToStrUint64Zero_306) {
    char buf[200];
    XMLUtil::ToStr(static_cast<uint64_t>(0), buf, 200);
    EXPECT_STREQ(buf, "0");
}

TEST_F(XMLUtilTest_306, ToStrInt_306) {
    char buf[200];
    XMLUtil::ToStr(static_cast<int>(12345), buf, 200);
    EXPECT_STREQ(buf, "12345");
}

TEST_F(XMLUtilTest_306, ToStrUnsignedInt_306) {
    char buf[200];
    XMLUtil::ToStr(static_cast<unsigned int>(4294967295U), buf, 200);
    EXPECT_STREQ(buf, "4294967295");
}

TEST_F(XMLUtilTest_306, ToStrBoolTrue_306) {
    char buf[200];
    XMLUtil::ToStr(true, buf, 200);
    EXPECT_STREQ(buf, "true");
}

TEST_F(XMLUtilTest_306, ToStrBoolFalse_306) {
    char buf[200];
    XMLUtil::ToStr(false, buf, 200);
    EXPECT_STREQ(buf, "false");
}

TEST_F(XMLUtilTest_306, ToIntValid_306) {
    int value = 0;
    bool result = XMLUtil::ToInt("42", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(value, 42);
}

TEST_F(XMLUtilTest_306, ToIntInvalid_306) {
    int value = 0;
    bool result = XMLUtil::ToInt("abc", &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilTest_306, ToInt64Valid_306) {
    int64_t value = 0;
    bool result = XMLUtil::ToInt64("9223372036854775807", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(value, INT64_MAX);
}

TEST_F(XMLUtilTest_306, ToInt64Invalid_306) {
    int64_t value = 0;
    bool result = XMLUtil::ToInt64("not_a_number", &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilTest_306, ToUnsigned64Valid_306) {
    uint64_t value = 0;
    bool result = XMLUtil::ToUnsigned64("18446744073709551615", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(value, UINT64_MAX);
}

TEST_F(XMLUtilTest_306, ToBoolTrue_306) {
    bool value = false;
    bool result = XMLUtil::ToBool("true", &value);
    EXPECT_TRUE(result);
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilTest_306, ToBoolFalse_306) {
    bool value = true;
    bool result = XMLUtil::ToBool("false", &value);
    EXPECT_TRUE(result);
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilTest_306, ToBoolInvalid_306) {
    bool value = false;
    bool result = XMLUtil::ToBool("maybe", &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilTest_306, ToFloatValid_306) {
    float value = 0.0f;
    bool result = XMLUtil::ToFloat("3.14", &value);
    EXPECT_TRUE(result);
    EXPECT_NEAR(value, 3.14f, 0.01f);
}

TEST_F(XMLUtilTest_306, ToDoubleValid_306) {
    double value = 0.0;
    bool result = XMLUtil::ToDouble("2.718281828", &value);
    EXPECT_TRUE(result);
    EXPECT_NEAR(value, 2.718281828, 0.000001);
}

TEST_F(XMLUtilTest_306, IsWhiteSpaceTrue_306) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\n'));
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\r'));
}

TEST_F(XMLUtilTest_306, IsWhiteSpaceFalse_306) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('a'));
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('1'));
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('!'));
}

TEST_F(XMLUtilTest_306, StringEqualSame_306) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello"));
}

TEST_F(XMLUtilTest_306, StringEqualDifferent_306) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world"));
}

TEST_F(XMLUtilTest_306, StringEqualWithLength_306) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello world", "hello", 5));
}

// ==================== XMLDocument/Printer integration via Visit ====================

TEST_F(XMLPrinterTest_306, VisitDocumentRoundTrip_306) {
    const char* xml = "<root><child>text</child></root>";
    XMLDocument doc;
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root>"), std::string::npos);
    EXPECT_NE(result.find("<child>"), std::string::npos);
    EXPECT_NE(result.find("text"), std::string::npos);
}

TEST_F(XMLPrinterTest_306, VisitDocumentWithAttributes_306) {
    const char* xml = "<root attr=\"value\"/>";
    XMLDocument doc;
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("attr=\"value\""), std::string::npos);
}

TEST_F(XMLPrinterTest_306, EmptyElementSelfClosing_306) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("empty", true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<empty/>"), std::string::npos);
}

TEST_F(XMLPrinterTest_306, PushTextInt64OneValue_306) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("num", true);
    printer.PushText(static_cast<int64_t>(1));
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<num>1</num>"), std::string::npos);
}

TEST_F(XMLPrinterTest_306, PushTextInt64NegativeOne_306) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("num", true);
    printer.PushText(static_cast<int64_t>(-1));
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("-1"), std::string::npos);
}
