#include <gtest/gtest.h>
#include <string>
#include <cstring>
#include <cstdint>
#include <climits>
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for XMLPrinter tests
class XMLPrinterTest_300 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== PushAttribute with uint64_t ====================

TEST_F(XMLPrinterTest_300, PushAttributeUint64Zero_300) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", (uint64_t)0);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val=\"0\""), std::string::npos);
}

TEST_F(XMLPrinterTest_300, PushAttributeUint64One_300) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("count", (uint64_t)1);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("count=\"1\""), std::string::npos);
}

TEST_F(XMLPrinterTest_300, PushAttributeUint64MaxValue_300) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    uint64_t maxVal = UINT64_MAX;
    printer.PushAttribute("big", maxVal);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("big=\"18446744073709551615\""), std::string::npos);
}

TEST_F(XMLPrinterTest_300, PushAttributeUint64LargeValue_300) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("num", (uint64_t)9999999999ULL);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("num=\"9999999999\""), std::string::npos);
}

TEST_F(XMLPrinterTest_300, PushAttributeUint64MidValue_300) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("mid", (uint64_t)123456789012345ULL);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("mid=\"123456789012345\""), std::string::npos);
}

// ==================== PushAttribute with various types ====================

TEST_F(XMLPrinterTest_300, PushAttributeInt_300) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("intval", 42);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("intval=\"42\""), std::string::npos);
}

TEST_F(XMLPrinterTest_300, PushAttributeNegativeInt_300) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("neg", -100);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("neg=\"-100\""), std::string::npos);
}

TEST_F(XMLPrinterTest_300, PushAttributeUnsignedInt_300) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("uval", (unsigned int)4294967295U);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("uval=\"4294967295\""), std::string::npos);
}

TEST_F(XMLPrinterTest_300, PushAttributeInt64_300) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("i64", (int64_t)-9223372036854775807LL);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("i64=\"-9223372036854775807\""), std::string::npos);
}

TEST_F(XMLPrinterTest_300, PushAttributeBoolTrue_300) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("flag", true);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("flag=\"true\""), std::string::npos);
}

TEST_F(XMLPrinterTest_300, PushAttributeBoolFalse_300) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("flag", false);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("flag=\"false\""), std::string::npos);
}

TEST_F(XMLPrinterTest_300, PushAttributeDouble_300) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("dval", 3.14);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("dval="), std::string::npos);
}

TEST_F(XMLPrinterTest_300, PushAttributeString_300) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("name", "hello");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("name=\"hello\""), std::string::npos);
}

// ==================== Multiple attributes ====================

TEST_F(XMLPrinterTest_300, PushMultipleAttributes_300) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("a", (uint64_t)1);
    printer.PushAttribute("b", (uint64_t)2);
    printer.PushAttribute("c", (uint64_t)3);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("a=\"1\""), std::string::npos);
    EXPECT_NE(result.find("b=\"2\""), std::string::npos);
    EXPECT_NE(result.find("c=\"3\""), std::string::npos);
}

TEST_F(XMLPrinterTest_300, PushMixedTypeAttributes_300) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("u64", (uint64_t)999);
    printer.PushAttribute("i64", (int64_t)-999);
    printer.PushAttribute("str", "text");
    printer.PushAttribute("b", true);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("u64=\"999\""), std::string::npos);
    EXPECT_NE(result.find("i64=\"-999\""), std::string::npos);
    EXPECT_NE(result.find("str=\"text\""), std::string::npos);
    EXPECT_NE(result.find("b=\"true\""), std::string::npos);
}

// ==================== OpenElement/CloseElement ====================

TEST_F(XMLPrinterTest_300, OpenAndCloseElement_300) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root/>"), std::string::npos);
}

TEST_F(XMLPrinterTest_300, NestedElements_300) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.PushAttribute("id", (uint64_t)42);
    printer.CloseElement();
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root>"), std::string::npos);
    EXPECT_NE(result.find("id=\"42\""), std::string::npos);
    EXPECT_NE(result.find("</root>"), std::string::npos);
}

// ==================== PushText ====================

TEST_F(XMLPrinterTest_300, PushTextUint64_300) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText((uint64_t)12345678901234ULL);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("12345678901234"), std::string::npos);
}

TEST_F(XMLPrinterTest_300, PushTextInt64_300) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText((int64_t)-12345678901234LL);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("-12345678901234"), std::string::npos);
}

TEST_F(XMLPrinterTest_300, PushTextString_300) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText("hello world");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("hello world"), std::string::npos);
}

TEST_F(XMLPrinterTest_300, PushTextBool_300) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText(true);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("true"), std::string::npos);
}

// ==================== PushComment / PushDeclaration / PushUnknown ====================

TEST_F(XMLPrinterTest_300, PushComment_300) {
    XMLPrinter printer(nullptr, true);
    printer.PushComment("this is a comment");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!--this is a comment-->"), std::string::npos);
}

TEST_F(XMLPrinterTest_300, PushDeclaration_300) {
    XMLPrinter printer(nullptr, true);
    printer.PushDeclaration("xml version=\"1.0\"");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml version=\"1.0\"?>"), std::string::npos);
}

TEST_F(XMLPrinterTest_300, PushUnknown_300) {
    XMLPrinter printer(nullptr, true);
    printer.PushUnknown("DOCTYPE html");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!DOCTYPE html>"), std::string::npos);
}

// ==================== CStr / CStrSize / ClearBuffer ====================

TEST_F(XMLPrinterTest_300, CStrNotNull_300) {
    XMLPrinter printer(nullptr, true);
    EXPECT_NE(printer.CStr(), nullptr);
}

TEST_F(XMLPrinterTest_300, CStrSizeInitial_300) {
    XMLPrinter printer(nullptr, true);
    // Initially should have at least a null terminator or be empty
    EXPECT_GE(printer.CStrSize(), (size_t)0);
}

TEST_F(XMLPrinterTest_300, ClearBuffer_300) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("x", (uint64_t)100);
    printer.CloseElement();
    EXPECT_GT(printer.CStrSize(), (size_t)0);
    printer.ClearBuffer();
    // After clearing, the buffer size should be minimal
    size_t sizeAfterClear = printer.CStrSize();
    EXPECT_LE(sizeAfterClear, (size_t)1); // null terminator at most
}

// ==================== PushHeader ====================

TEST_F(XMLPrinterTest_300, PushHeaderWithDeclaration_300) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(false, true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml"), std::string::npos);
}

TEST_F(XMLPrinterTest_300, PushHeaderWithBOM_300) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(true, false);
    std::string result = printer.CStr();
    // BOM bytes: 0xEF 0xBB 0xBF
    EXPECT_GE(printer.CStrSize(), (size_t)3);
}

// ==================== Compact vs non-compact mode ====================

TEST_F(XMLPrinterTest_300, CompactModeOutput_300) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string result = printer.CStr();
    // In compact mode, no newlines between elements
    EXPECT_EQ(result.find('\n'), std::string::npos);
}

TEST_F(XMLPrinterTest_300, NonCompactModeOutput_300) {
    XMLPrinter printer(nullptr, false);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string result = printer.CStr();
    // In non-compact mode, expect newlines
    EXPECT_NE(result.find('\n'), std::string::npos);
}

// ==================== XMLUtil::ToStr and parsing round-trip ====================

TEST_F(XMLPrinterTest_300, XMLUtilToStrUint64_300) {
    char buf[200];
    XMLUtil::ToStr((uint64_t)0, buf, 200);
    EXPECT_STREQ(buf, "0");
}

TEST_F(XMLPrinterTest_300, XMLUtilToStrUint64Max_300) {
    char buf[200];
    XMLUtil::ToStr(UINT64_MAX, buf, 200);
    EXPECT_STREQ(buf, "18446744073709551615");
}

TEST_F(XMLPrinterTest_300, XMLUtilToStrInt64Negative_300) {
    char buf[200];
    XMLUtil::ToStr((int64_t)-1, buf, 200);
    EXPECT_STREQ(buf, "-1");
}

TEST_F(XMLPrinterTest_300, XMLUtilToStrInt_300) {
    char buf[200];
    XMLUtil::ToStr(42, buf, 200);
    EXPECT_STREQ(buf, "42");
}

TEST_F(XMLPrinterTest_300, XMLUtilToStrBoolTrue_300) {
    char buf[200];
    XMLUtil::ToStr(true, buf, 200);
    EXPECT_STREQ(buf, "true");
}

TEST_F(XMLPrinterTest_300, XMLUtilToStrBoolFalse_300) {
    char buf[200];
    XMLUtil::ToStr(false, buf, 200);
    EXPECT_STREQ(buf, "false");
}

TEST_F(XMLPrinterTest_300, XMLUtilToUnsigned64RoundTrip_300) {
    char buf[200];
    uint64_t original = 9876543210ULL;
    XMLUtil::ToStr(original, buf, 200);
    uint64_t parsed = 0;
    bool ok = XMLUtil::ToUnsigned64(buf, &parsed);
    EXPECT_TRUE(ok);
    EXPECT_EQ(original, parsed);
}

TEST_F(XMLPrinterTest_300, XMLUtilToInt64RoundTrip_300) {
    char buf[200];
    int64_t original = -9876543210LL;
    XMLUtil::ToStr(original, buf, 200);
    int64_t parsed = 0;
    bool ok = XMLUtil::ToInt64(buf, &parsed);
    EXPECT_TRUE(ok);
    EXPECT_EQ(original, parsed);
}

TEST_F(XMLPrinterTest_300, XMLUtilToIntRoundTrip_300) {
    char buf[200];
    int original = -12345;
    XMLUtil::ToStr(original, buf, 200);
    int parsed = 0;
    bool ok = XMLUtil::ToInt(buf, &parsed);
    EXPECT_TRUE(ok);
    EXPECT_EQ(original, parsed);
}

TEST_F(XMLPrinterTest_300, XMLUtilToBoolRoundTrip_300) {
    char buf[200];
    XMLUtil::ToStr(true, buf, 200);
    bool parsed = false;
    bool ok = XMLUtil::ToBool(buf, &parsed);
    EXPECT_TRUE(ok);
    EXPECT_TRUE(parsed);
}

TEST_F(XMLPrinterTest_300, XMLUtilToDoubleRoundTrip_300) {
    char buf[200];
    double original = 3.14159;
    XMLUtil::ToStr(original, buf, 200);
    double parsed = 0.0;
    bool ok = XMLUtil::ToDouble(buf, &parsed);
    EXPECT_TRUE(ok);
    EXPECT_NEAR(original, parsed, 1e-5);
}

// ==================== XMLDocument integration with XMLPrinter ====================

TEST_F(XMLPrinterTest_300, DocumentAcceptPrinter_300) {
    XMLDocument doc;
    doc.Parse("<root attr=\"1\"><child>text</child></root>");
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);
    
    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root"), std::string::npos);
    EXPECT_NE(result.find("attr=\"1\""), std::string::npos);
    EXPECT_NE(result.find("<child>text</child>"), std::string::npos);
}

TEST_F(XMLPrinterTest_300, DocumentWithUint64Attribute_300) {
    XMLDocument doc;
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test");
    printer.PushAttribute("bignum", (uint64_t)18446744073709551615ULL);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("bignum=\"18446744073709551615\""), std::string::npos);
}

// ==================== Edge cases for XMLUtil parsing ====================

TEST_F(XMLPrinterTest_300, XMLUtilToIntInvalidString_300) {
    int value = 0;
    bool ok = XMLUtil::ToInt("not_a_number", &value);
    EXPECT_FALSE(ok);
}

TEST_F(XMLPrinterTest_300, XMLUtilToUnsigned64InvalidString_300) {
    uint64_t value = 0;
    bool ok = XMLUtil::ToUnsigned64("abc", &value);
    EXPECT_FALSE(ok);
}

TEST_F(XMLPrinterTest_300, XMLUtilToBoolInvalidString_300) {
    bool value = false;
    bool ok = XMLUtil::ToBool("maybe", &value);
    EXPECT_FALSE(ok);
}

TEST_F(XMLPrinterTest_300, XMLUtilToDoubleInvalidString_300) {
    double value = 0.0;
    bool ok = XMLUtil::ToDouble("xyz", &value);
    EXPECT_FALSE(ok);
}

// ==================== PushText with CDATA ====================

TEST_F(XMLPrinterTest_300, PushTextCDATA_300) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText("some data", true);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<![CDATA[some data]]>"), std::string::npos);
}

TEST_F(XMLPrinterTest_300, PushTextNoCDATA_300) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText("some data", false);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("some data"), std::string::npos);
    EXPECT_EQ(result.find("CDATA"), std::string::npos);
}

// ==================== Boundary: uint64_t values near boundaries ====================

TEST_F(XMLPrinterTest_300, PushAttributeUint64PowerOf2_300) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("pow", (uint64_t)(1ULL << 63));
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("pow=\"9223372036854775808\""), std::string::npos);
}

TEST_F(XMLPrinterTest_300, PushAttributeUint64JustAboveInt64Max_300) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    uint64_t val = (uint64_t)INT64_MAX + 1;
    printer.PushAttribute("val", val);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val=\"9223372036854775808\""), std::string::npos);
}

// ==================== Empty element name ====================

TEST_F(XMLPrinterTest_300, EmptyStringAttribute_300) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("empty", "");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("empty=\"\""), std::string::npos);
}

// ==================== XMLUtil whitespace and string helpers ====================

TEST_F(XMLPrinterTest_300, XMLUtilIsWhiteSpace_300) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\n'));
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\r'));
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('a'));
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('0'));
}

TEST_F(XMLPrinterTest_300, XMLUtilStringEqual_300) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello"));
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world"));
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "help", 3));
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "help", 4));
}
