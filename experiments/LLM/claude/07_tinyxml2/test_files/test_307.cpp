#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include <cstdint>
#include <climits>
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for XMLPrinter tests
class XMLPrinterTest_307 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== PushText(uint64_t) Tests ====================

TEST_F(XMLPrinterTest_307, PushTextUint64Zero_307) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(static_cast<uint64_t>(0));
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("0"), std::string::npos);
}

TEST_F(XMLPrinterTest_307, PushTextUint64One_307) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(static_cast<uint64_t>(1));
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("1"), std::string::npos);
}

TEST_F(XMLPrinterTest_307, PushTextUint64MaxValue_307) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    uint64_t maxVal = UINT64_MAX;
    printer.PushText(maxVal);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    // UINT64_MAX is 18446744073709551615
    EXPECT_NE(result.find("18446744073709551615"), std::string::npos);
}

TEST_F(XMLPrinterTest_307, PushTextUint64LargeValue_307) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem", true);
    printer.PushText(static_cast<uint64_t>(9999999999ULL));
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("9999999999"), std::string::npos);
}

TEST_F(XMLPrinterTest_307, PushTextUint64InElement_307) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("value", true);
    printer.PushText(static_cast<uint64_t>(42));
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<value>"), std::string::npos);
    EXPECT_NE(result.find("42"), std::string::npos);
    EXPECT_NE(result.find("</value>"), std::string::npos);
}

// ==================== PushText(int64_t) Tests ====================

TEST_F(XMLPrinterTest_307, PushTextInt64Negative_307) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(static_cast<int64_t>(-123456789));
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("-123456789"), std::string::npos);
}

TEST_F(XMLPrinterTest_307, PushTextInt64Zero_307) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(static_cast<int64_t>(0));
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("0"), std::string::npos);
}

TEST_F(XMLPrinterTest_307, PushTextInt64MaxValue_307) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(INT64_MAX);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("9223372036854775807"), std::string::npos);
}

TEST_F(XMLPrinterTest_307, PushTextInt64MinValue_307) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(INT64_MIN);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("-9223372036854775808"), std::string::npos);
}

// ==================== PushText(int) Tests ====================

TEST_F(XMLPrinterTest_307, PushTextInt_307) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(42);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("42"), std::string::npos);
}

TEST_F(XMLPrinterTest_307, PushTextIntNegative_307) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(-100);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("-100"), std::string::npos);
}

// ==================== PushText(unsigned int) Tests ====================

TEST_F(XMLPrinterTest_307, PushTextUnsigned_307) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(static_cast<unsigned int>(999));
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("999"), std::string::npos);
}

// ==================== PushText(bool) Tests ====================

TEST_F(XMLPrinterTest_307, PushTextBoolTrue_307) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("true"), std::string::npos);
}

TEST_F(XMLPrinterTest_307, PushTextBoolFalse_307) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(false);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("false"), std::string::npos);
}

// ==================== PushText(float) Tests ====================

TEST_F(XMLPrinterTest_307, PushTextFloat_307) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(3.14f);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

// ==================== PushText(double) Tests ====================

TEST_F(XMLPrinterTest_307, PushTextDouble_307) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(2.71828);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("2.71828"), std::string::npos);
}

// ==================== PushText(const char*) Tests ====================

TEST_F(XMLPrinterTest_307, PushTextString_307) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText("Hello World", false);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("Hello World"), std::string::npos);
}

TEST_F(XMLPrinterTest_307, PushTextCData_307) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText("Some CDATA text", true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<![CDATA[Some CDATA text]]>"), std::string::npos);
}

// ==================== OpenElement / CloseElement Tests ====================

TEST_F(XMLPrinterTest_307, OpenCloseElement_307) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test", true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<test/>"), std::string::npos);
}

TEST_F(XMLPrinterTest_307, NestedElements_307) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("parent", true);
    printer.OpenElement("child", true);
    printer.CloseElement(true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<parent>"), std::string::npos);
    EXPECT_NE(result.find("<child/>"), std::string::npos);
    EXPECT_NE(result.find("</parent>"), std::string::npos);
}

// ==================== PushAttribute Tests ====================

TEST_F(XMLPrinterTest_307, PushAttributeString_307) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem", true);
    printer.PushAttribute("name", "value");
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("name=\"value\""), std::string::npos);
}

TEST_F(XMLPrinterTest_307, PushAttributeInt_307) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem", true);
    printer.PushAttribute("count", 5);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("count=\"5\""), std::string::npos);
}

TEST_F(XMLPrinterTest_307, PushAttributeUnsigned_307) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem", true);
    printer.PushAttribute("val", static_cast<unsigned int>(100));
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val=\"100\""), std::string::npos);
}

TEST_F(XMLPrinterTest_307, PushAttributeInt64_307) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem", true);
    printer.PushAttribute("big", static_cast<int64_t>(9223372036854775807LL));
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("9223372036854775807"), std::string::npos);
}

TEST_F(XMLPrinterTest_307, PushAttributeUint64_307) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem", true);
    printer.PushAttribute("ubig", static_cast<uint64_t>(18446744073709551615ULL));
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("18446744073709551615"), std::string::npos);
}

TEST_F(XMLPrinterTest_307, PushAttributeBool_307) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem", true);
    printer.PushAttribute("flag", true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("flag=\"true\""), std::string::npos);
}

TEST_F(XMLPrinterTest_307, PushAttributeDouble_307) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem", true);
    printer.PushAttribute("pi", 3.14159);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("pi=\""), std::string::npos);
    EXPECT_NE(result.find("3.14159"), std::string::npos);
}

// ==================== PushHeader Tests ====================

TEST_F(XMLPrinterTest_307, PushHeaderBOM_307) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(true, false);
    std::string result = printer.CStr();
    // BOM is 0xEF 0xBB 0xBF
    EXPECT_GE(result.size(), 3u);
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 0xEF);
    EXPECT_EQ(static_cast<unsigned char>(result[1]), 0xBB);
    EXPECT_EQ(static_cast<unsigned char>(result[2]), 0xBF);
}

TEST_F(XMLPrinterTest_307, PushHeaderDeclaration_307) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(false, true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml"), std::string::npos);
}

TEST_F(XMLPrinterTest_307, PushHeaderBoth_307) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(true, true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml"), std::string::npos);
}

// ==================== PushComment Tests ====================

TEST_F(XMLPrinterTest_307, PushComment_307) {
    XMLPrinter printer(nullptr, true);
    printer.PushComment("This is a comment");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!--This is a comment-->"), std::string::npos);
}

// ==================== PushDeclaration Tests ====================

TEST_F(XMLPrinterTest_307, PushDeclaration_307) {
    XMLPrinter printer(nullptr, true);
    printer.PushDeclaration("xml version=\"1.0\"");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml version=\"1.0\"?>"), std::string::npos);
}

// ==================== PushUnknown Tests ====================

TEST_F(XMLPrinterTest_307, PushUnknown_307) {
    XMLPrinter printer(nullptr, true);
    printer.PushUnknown("!DOCTYPE html");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!DOCTYPE html>"), std::string::npos);
}

// ==================== CStr / CStrSize / ClearBuffer Tests ====================

TEST_F(XMLPrinterTest_307, CStrReturnsNonNull_307) {
    XMLPrinter printer(nullptr, true);
    EXPECT_NE(printer.CStr(), nullptr);
}

TEST_F(XMLPrinterTest_307, CStrSizeInitial_307) {
    XMLPrinter printer(nullptr, true);
    // Initially the buffer should be minimal (just null terminator or empty)
    size_t size = printer.CStrSize();
    EXPECT_GE(size, 0u);
}

TEST_F(XMLPrinterTest_307, ClearBuffer_307) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test", true);
    printer.CloseElement(true);
    EXPECT_GT(printer.CStrSize(), 0u);
    printer.ClearBuffer();
    // After clear, the size should be minimal
    size_t sizeAfter = printer.CStrSize();
    EXPECT_LE(sizeAfter, 1u);
}

// ==================== Non-Compact Mode Tests ====================

TEST_F(XMLPrinterTest_307, NonCompactModeFormatting_307) {
    XMLPrinter printer(nullptr, false);
    printer.OpenElement("parent");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<parent>"), std::string::npos);
    EXPECT_NE(result.find("</parent>"), std::string::npos);
    // Non-compact mode should have newlines
    EXPECT_NE(result.find("\n"), std::string::npos);
}

// ==================== Multiple PushText in sequence ====================

TEST_F(XMLPrinterTest_307, MultiplePushTextUint64_307) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("data", true);
    printer.PushText(static_cast<uint64_t>(100));
    printer.CloseElement(true);
    printer.OpenElement("data2", true);
    printer.PushText(static_cast<uint64_t>(200));
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("100"), std::string::npos);
    EXPECT_NE(result.find("200"), std::string::npos);
}

// ==================== XMLUtil::ToStr / conversion roundtrip ====================

TEST_F(XMLPrinterTest_307, ToStrUint64_307) {
    char buf[200];
    XMLUtil::ToStr(static_cast<uint64_t>(12345678901234ULL), buf, 200);
    EXPECT_STREQ(buf, "12345678901234");
}

TEST_F(XMLPrinterTest_307, ToStrUint64Zero_307) {
    char buf[200];
    XMLUtil::ToStr(static_cast<uint64_t>(0), buf, 200);
    EXPECT_STREQ(buf, "0");
}

TEST_F(XMLPrinterTest_307, ToStrUint64Max_307) {
    char buf[200];
    XMLUtil::ToStr(UINT64_MAX, buf, 200);
    EXPECT_STREQ(buf, "18446744073709551615");
}

TEST_F(XMLPrinterTest_307, ToStrInt64Negative_307) {
    char buf[200];
    XMLUtil::ToStr(static_cast<int64_t>(-42), buf, 200);
    EXPECT_STREQ(buf, "-42");
}

TEST_F(XMLPrinterTest_307, ToStrInt_307) {
    char buf[200];
    XMLUtil::ToStr(123, buf, 200);
    EXPECT_STREQ(buf, "123");
}

TEST_F(XMLPrinterTest_307, ToStrUnsignedInt_307) {
    char buf[200];
    XMLUtil::ToStr(static_cast<unsigned int>(456), buf, 200);
    EXPECT_STREQ(buf, "456");
}

TEST_F(XMLPrinterTest_307, ToStrBoolTrue_307) {
    char buf[200];
    XMLUtil::ToStr(true, buf, 200);
    EXPECT_STREQ(buf, "true");
}

TEST_F(XMLPrinterTest_307, ToStrBoolFalse_307) {
    char buf[200];
    XMLUtil::ToStr(false, buf, 200);
    EXPECT_STREQ(buf, "false");
}

// ==================== XMLUtil::ToInt / ToUnsigned64 Roundtrip ====================

TEST_F(XMLPrinterTest_307, ToUnsigned64Roundtrip_307) {
    char buf[200];
    uint64_t original = 9876543210ULL;
    XMLUtil::ToStr(original, buf, 200);
    uint64_t parsed = 0;
    bool ok = XMLUtil::ToUnsigned64(buf, &parsed);
    EXPECT_TRUE(ok);
    EXPECT_EQ(parsed, original);
}

TEST_F(XMLPrinterTest_307, ToInt64Roundtrip_307) {
    char buf[200];
    int64_t original = -9876543210LL;
    XMLUtil::ToStr(original, buf, 200);
    int64_t parsed = 0;
    bool ok = XMLUtil::ToInt64(buf, &parsed);
    EXPECT_TRUE(ok);
    EXPECT_EQ(parsed, original);
}

TEST_F(XMLPrinterTest_307, ToIntRoundtrip_307) {
    char buf[200];
    int original = -42;
    XMLUtil::ToStr(original, buf, 200);
    int parsed = 0;
    bool ok = XMLUtil::ToInt(buf, &parsed);
    EXPECT_TRUE(ok);
    EXPECT_EQ(parsed, original);
}

TEST_F(XMLPrinterTest_307, ToBoolRoundtrip_307) {
    char buf[200];
    XMLUtil::ToStr(true, buf, 200);
    bool parsed = false;
    bool ok = XMLUtil::ToBool(buf, &parsed);
    EXPECT_TRUE(ok);
    EXPECT_EQ(parsed, true);
}

TEST_F(XMLPrinterTest_307, ToDoubleRoundtrip_307) {
    char buf[200];
    double original = 1.23456789;
    XMLUtil::ToStr(original, buf, 200);
    double parsed = 0.0;
    bool ok = XMLUtil::ToDouble(buf, &parsed);
    EXPECT_TRUE(ok);
    EXPECT_NEAR(parsed, original, 1e-6);
}

// ==================== XMLUtil parsing error cases ====================

TEST_F(XMLPrinterTest_307, ToIntInvalidString_307) {
    int value = 0;
    bool ok = XMLUtil::ToInt("notanumber", &value);
    EXPECT_FALSE(ok);
}

TEST_F(XMLPrinterTest_307, ToUnsigned64InvalidString_307) {
    uint64_t value = 0;
    bool ok = XMLUtil::ToUnsigned64("xyz", &value);
    EXPECT_FALSE(ok);
}

TEST_F(XMLPrinterTest_307, ToBoolInvalidString_307) {
    bool value = false;
    bool ok = XMLUtil::ToBool("maybe", &value);
    EXPECT_FALSE(ok);
}

// ==================== XMLPrinter with XMLDocument integration ====================

TEST_F(XMLPrinterTest_307, DocumentPrintVisitor_307) {
    XMLDocument doc;
    doc.Parse("<root><child>text</child></root>");
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);
    
    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root>"), std::string::npos);
    EXPECT_NE(result.find("<child>"), std::string::npos);
    EXPECT_NE(result.find("text"), std::string::npos);
}

// ==================== Entity handling in PushText ====================

TEST_F(XMLPrinterTest_307, PushTextWithEntities_307) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText("<>&\"", false);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    // Entities should be escaped
    EXPECT_NE(result.find("&lt;"), std::string::npos);
    EXPECT_NE(result.find("&gt;"), std::string::npos);
    EXPECT_NE(result.find("&amp;"), std::string::npos);
}

// ==================== Empty element with multiple attributes ====================

TEST_F(XMLPrinterTest_307, MultipleAttributes_307) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem", true);
    printer.PushAttribute("a", "1");
    printer.PushAttribute("b", "2");
    printer.PushAttribute("c", "3");
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("a=\"1\""), std::string::npos);
    EXPECT_NE(result.find("b=\"2\""), std::string::npos);
    EXPECT_NE(result.find("c=\"3\""), std::string::npos);
}

// ==================== Boundary: PushText uint64_t value = 1 ====================

TEST_F(XMLPrinterTest_307, PushTextUint64BoundaryOne_307) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("v", true);
    printer.PushText(static_cast<uint64_t>(1));
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find(">1<"), std::string::npos);
}

// ==================== XMLUtil StringEqual ====================

TEST_F(XMLPrinterTest_307, StringEqualBasic_307) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello"));
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world"));
}

TEST_F(XMLPrinterTest_307, StringEqualWithLength_307) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello world", "hello there", 5));
    EXPECT_FALSE(XMLUtil::StringEqual("hello world", "hello there", 6));
}

// ==================== XMLUtil IsWhiteSpace ====================

TEST_F(XMLPrinterTest_307, IsWhiteSpace_307) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\n'));
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\r'));
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('a'));
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('0'));
}
