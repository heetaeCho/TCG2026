#include <gtest/gtest.h>
#include <cmath>
#include <cstring>
#include <string>
#include <limits>
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for XMLPrinter tests
class XMLPrinterTest_311 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// PushText(float) tests
// ============================================================

TEST_F(XMLPrinterTest_311, PushTextFloat_PositiveValue_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(3.14f);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("3.14"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_311, PushTextFloat_Zero_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(0.0f);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("0"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_311, PushTextFloat_NegativeValue_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(-2.5f);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("-2.5"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_311, PushTextFloat_LargeValue_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(1.0e10f);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    // The output should contain some representation of 1e10
    EXPECT_FALSE(result.empty()) << "Result: " << result;
}

TEST_F(XMLPrinterTest_311, PushTextFloat_SmallValue_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(1.0e-10f);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_FALSE(result.empty()) << "Result: " << result;
}

TEST_F(XMLPrinterTest_311, PushTextFloat_One_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(1.0f);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("1"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_311, PushTextFloat_NegativeOne_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(-1.0f);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("-1"), std::string::npos) << "Result: " << result;
}

// ============================================================
// PushText with other types
// ============================================================

TEST_F(XMLPrinterTest_311, PushTextInt_PositiveValue_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(42);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("42"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_311, PushTextInt_NegativeValue_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(-100);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("-100"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_311, PushTextInt_Zero_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(0);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("0"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_311, PushTextUnsigned_Value_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText((unsigned int)123);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("123"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_311, PushTextBool_True_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("true"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_311, PushTextBool_False_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(false);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("false"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_311, PushTextDouble_Value_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(3.14159265358979);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("3.14159"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_311, PushTextInt64_Value_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText((int64_t)9223372036854775807LL);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("9223372036854775807"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_311, PushTextUint64_Value_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText((uint64_t)18446744073709551615ULL);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("18446744073709551615"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_311, PushTextString_Simple_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText("hello", false);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("hello"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_311, PushTextString_CDATA_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText("hello", true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<![CDATA[hello]]>"), std::string::npos) << "Result: " << result;
}

// ============================================================
// OpenElement / CloseElement tests
// ============================================================

TEST_F(XMLPrinterTest_311, OpenAndCloseElement_Simple_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test", true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<test/>"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_311, OpenAndCloseElement_WithText_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test", true);
    printer.PushText("content", false);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<test>"), std::string::npos) << "Result: " << result;
    EXPECT_NE(result.find("content"), std::string::npos) << "Result: " << result;
    EXPECT_NE(result.find("</test>"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_311, NestedElements_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("outer", true);
    printer.OpenElement("inner", true);
    printer.CloseElement(true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<outer>"), std::string::npos) << "Result: " << result;
    EXPECT_NE(result.find("<inner/>"), std::string::npos) << "Result: " << result;
    EXPECT_NE(result.find("</outer>"), std::string::npos) << "Result: " << result;
}

// ============================================================
// PushAttribute tests
// ============================================================

TEST_F(XMLPrinterTest_311, PushAttribute_String_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test", true);
    printer.PushAttribute("name", "value");
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("name=\"value\""), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_311, PushAttribute_Int_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test", true);
    printer.PushAttribute("count", 5);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("count=\"5\""), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_311, PushAttribute_Bool_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test", true);
    printer.PushAttribute("flag", true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("flag=\"true\""), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_311, PushAttribute_Double_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test", true);
    printer.PushAttribute("val", 1.5);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val=\"1.5\""), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_311, PushAttribute_Unsigned_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test", true);
    printer.PushAttribute("val", (unsigned int)99);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val=\"99\""), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_311, PushAttribute_Int64_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test", true);
    printer.PushAttribute("val", (int64_t)123456789012345LL);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val=\"123456789012345\""), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_311, PushAttribute_Uint64_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test", true);
    printer.PushAttribute("val", (uint64_t)123456789012345ULL);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val=\"123456789012345\""), std::string::npos) << "Result: " << result;
}

// ============================================================
// PushHeader tests
// ============================================================

TEST_F(XMLPrinterTest_311, PushHeader_WithDeclaration_311) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(false, true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_311, PushHeader_WithBOM_311) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(true, false);
    std::string result = printer.CStr();
    // BOM is 0xEF 0xBB 0xBF
    EXPECT_GE(printer.CStrSize(), 3u);
}

TEST_F(XMLPrinterTest_311, PushHeader_NoBOMNoDecl_311) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(false, false);
    std::string result = printer.CStr();
    // Should be essentially empty or minimal
    EXPECT_EQ(result.find("<?xml"), std::string::npos) << "Result: " << result;
}

// ============================================================
// PushComment tests
// ============================================================

TEST_F(XMLPrinterTest_311, PushComment_Simple_311) {
    XMLPrinter printer(nullptr, true);
    printer.PushComment("this is a comment");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!--this is a comment-->"), std::string::npos) << "Result: " << result;
}

// ============================================================
// PushDeclaration tests
// ============================================================

TEST_F(XMLPrinterTest_311, PushDeclaration_Simple_311) {
    XMLPrinter printer(nullptr, true);
    printer.PushDeclaration("xml version=\"1.0\"");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml version=\"1.0\"?>"), std::string::npos) << "Result: " << result;
}

// ============================================================
// PushUnknown tests
// ============================================================

TEST_F(XMLPrinterTest_311, PushUnknown_Simple_311) {
    XMLPrinter printer(nullptr, true);
    printer.PushUnknown("DOCTYPE html");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!DOCTYPE html>"), std::string::npos) << "Result: " << result;
}

// ============================================================
// CStr / CStrSize / ClearBuffer tests
// ============================================================

TEST_F(XMLPrinterTest_311, CStr_EmptyPrinter_311) {
    XMLPrinter printer(nullptr, true);
    const char* result = printer.CStr();
    EXPECT_NE(result, nullptr);
}

TEST_F(XMLPrinterTest_311, CStrSize_EmptyPrinter_311) {
    XMLPrinter printer(nullptr, true);
    size_t size = printer.CStrSize();
    // Even empty printer should have some size (at least null terminator)
    EXPECT_GE(size, 1u);
}

TEST_F(XMLPrinterTest_311, ClearBuffer_ResetsContent_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test", true);
    printer.CloseElement(true);
    EXPECT_GT(printer.CStrSize(), 1u);
    
    printer.ClearBuffer();
    // After clearing, CStrSize should be minimal
    size_t sizeAfterClear = printer.CStrSize();
    EXPECT_LE(sizeAfterClear, 1u);
}

// ============================================================
// Compact vs non-compact mode
// ============================================================

TEST_F(XMLPrinterTest_311, NonCompactMode_HasWhitespace_311) {
    XMLPrinter printer(nullptr, false);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string result = printer.CStr();
    // Non-compact mode should have newlines
    EXPECT_NE(result.find("\n"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_311, CompactMode_NoExtraWhitespace_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.OpenElement("child", true);
    printer.CloseElement(true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    // Should be compact without unnecessary newlines between elements
    EXPECT_NE(result.find("<root><child/></root>"), std::string::npos) << "Result: " << result;
}

// ============================================================
// XMLUtil tests
// ============================================================

TEST_F(XMLPrinterTest_311, XMLUtil_ToStr_Float_311) {
    char buf[200];
    XMLUtil::ToStr(1.5f, buf, 200);
    std::string result(buf);
    EXPECT_NE(result.find("1.5"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_311, XMLUtil_ToStr_Int_311) {
    char buf[200];
    XMLUtil::ToStr(42, buf, 200);
    EXPECT_STREQ(buf, "42");
}

TEST_F(XMLPrinterTest_311, XMLUtil_ToStr_Bool_True_311) {
    char buf[200];
    XMLUtil::ToStr(true, buf, 200);
    EXPECT_STREQ(buf, "true");
}

TEST_F(XMLPrinterTest_311, XMLUtil_ToStr_Bool_False_311) {
    char buf[200];
    XMLUtil::ToStr(false, buf, 200);
    EXPECT_STREQ(buf, "false");
}

TEST_F(XMLPrinterTest_311, XMLUtil_ToStr_Double_311) {
    char buf[200];
    XMLUtil::ToStr(3.14159265358979, buf, 200);
    std::string result(buf);
    EXPECT_NE(result.find("3.14159"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_311, XMLUtil_ToStr_Unsigned_311) {
    char buf[200];
    XMLUtil::ToStr((unsigned int)4294967295u, buf, 200);
    EXPECT_STREQ(buf, "4294967295");
}

TEST_F(XMLPrinterTest_311, XMLUtil_ToStr_Int64_311) {
    char buf[200];
    XMLUtil::ToStr((int64_t)-9223372036854775807LL, buf, 200);
    EXPECT_STREQ(buf, "-9223372036854775807");
}

TEST_F(XMLPrinterTest_311, XMLUtil_ToStr_Uint64_311) {
    char buf[200];
    XMLUtil::ToStr((uint64_t)18446744073709551615ULL, buf, 200);
    EXPECT_STREQ(buf, "18446744073709551615");
}

TEST_F(XMLPrinterTest_311, XMLUtil_ToInt_Valid_311) {
    int value = 0;
    bool result = XMLUtil::ToInt("123", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(value, 123);
}

TEST_F(XMLPrinterTest_311, XMLUtil_ToInt_Invalid_311) {
    int value = 0;
    bool result = XMLUtil::ToInt("abc", &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLPrinterTest_311, XMLUtil_ToFloat_Valid_311) {
    float value = 0.0f;
    bool result = XMLUtil::ToFloat("3.14", &value);
    EXPECT_TRUE(result);
    EXPECT_NEAR(value, 3.14f, 0.01f);
}

TEST_F(XMLPrinterTest_311, XMLUtil_ToFloat_Invalid_311) {
    float value = 0.0f;
    bool result = XMLUtil::ToFloat("notanumber", &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLPrinterTest_311, XMLUtil_ToDouble_Valid_311) {
    double value = 0.0;
    bool result = XMLUtil::ToDouble("2.71828", &value);
    EXPECT_TRUE(result);
    EXPECT_NEAR(value, 2.71828, 0.00001);
}

TEST_F(XMLPrinterTest_311, XMLUtil_ToBool_True_311) {
    bool value = false;
    bool result = XMLUtil::ToBool("true", &value);
    EXPECT_TRUE(result);
    EXPECT_TRUE(value);
}

TEST_F(XMLPrinterTest_311, XMLUtil_ToBool_False_311) {
    bool value = true;
    bool result = XMLUtil::ToBool("false", &value);
    EXPECT_TRUE(result);
    EXPECT_FALSE(value);
}

TEST_F(XMLPrinterTest_311, XMLUtil_ToBool_Invalid_311) {
    bool value = false;
    bool result = XMLUtil::ToBool("maybe", &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLPrinterTest_311, XMLUtil_ToUnsigned_Valid_311) {
    unsigned int value = 0;
    bool result = XMLUtil::ToUnsigned("42", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(value, 42u);
}

TEST_F(XMLPrinterTest_311, XMLUtil_ToInt64_Valid_311) {
    int64_t value = 0;
    bool result = XMLUtil::ToInt64("9223372036854775807", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(value, 9223372036854775807LL);
}

TEST_F(XMLPrinterTest_311, XMLUtil_ToUnsigned64_Valid_311) {
    uint64_t value = 0;
    bool result = XMLUtil::ToUnsigned64("18446744073709551615", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(value, 18446744073709551615ULL);
}

TEST_F(XMLPrinterTest_311, XMLUtil_StringEqual_Same_311) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello"));
}

TEST_F(XMLPrinterTest_311, XMLUtil_StringEqual_Different_311) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world"));
}

TEST_F(XMLPrinterTest_311, XMLUtil_StringEqual_Partial_311) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello world", 5));
}

TEST_F(XMLPrinterTest_311, XMLUtil_IsWhiteSpace_Space_311) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));
}

TEST_F(XMLPrinterTest_311, XMLUtil_IsWhiteSpace_Tab_311) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));
}

TEST_F(XMLPrinterTest_311, XMLUtil_IsWhiteSpace_NonWhitespace_311) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('a'));
}

// ============================================================
// Multiple PushText calls in one element
// ============================================================

TEST_F(XMLPrinterTest_311, PushTextFloat_MultipleValues_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(1.0f);
    printer.PushText(2.0f);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("1"), std::string::npos) << "Result: " << result;
    EXPECT_NE(result.find("2"), std::string::npos) << "Result: " << result;
}

// ============================================================
// Visitor interface via XMLDocument
// ============================================================

TEST_F(XMLPrinterTest_311, VisitDocument_RoundTrip_311) {
    XMLDocument doc;
    doc.Parse("<root><child attr=\"val\">text</child></root>");
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);
    
    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root>"), std::string::npos) << "Result: " << result;
    EXPECT_NE(result.find("<child"), std::string::npos) << "Result: " << result;
    EXPECT_NE(result.find("attr=\"val\""), std::string::npos) << "Result: " << result;
    EXPECT_NE(result.find("text"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_311, VisitDocument_WithComment_311) {
    XMLDocument doc;
    doc.Parse("<!-- comment --><root/>");
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);
    
    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!-- comment -->"), std::string::npos) << "Result: " << result;
    EXPECT_NE(result.find("<root/>"), std::string::npos) << "Result: " << result;
}

// ============================================================
// Boundary: float edge cases
// ============================================================

TEST_F(XMLPrinterTest_311, PushTextFloat_MaxFloat_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(std::numeric_limits<float>::max());
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_FALSE(result.empty()) << "Result: " << result;
}

TEST_F(XMLPrinterTest_311, PushTextFloat_MinFloat_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(std::numeric_limits<float>::min());
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_FALSE(result.empty()) << "Result: " << result;
}

TEST_F(XMLPrinterTest_311, PushTextFloat_NegativeZero_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(-0.0f);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("0"), std::string::npos) << "Result: " << result;
}

// ============================================================
// Multiple attributes
// ============================================================

TEST_F(XMLPrinterTest_311, PushMultipleAttributes_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test", true);
    printer.PushAttribute("a", "1");
    printer.PushAttribute("b", "2");
    printer.PushAttribute("c", "3");
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("a=\"1\""), std::string::npos) << "Result: " << result;
    EXPECT_NE(result.find("b=\"2\""), std::string::npos) << "Result: " << result;
    EXPECT_NE(result.find("c=\"3\""), std::string::npos) << "Result: " << result;
}

// ============================================================
// ClearBuffer and reuse
// ============================================================

TEST_F(XMLPrinterTest_311, ClearBufferAndReuse_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("first", true);
    printer.CloseElement(true);
    
    std::string first = printer.CStr();
    EXPECT_NE(first.find("<first/>"), std::string::npos);
    
    printer.ClearBuffer();
    
    printer.OpenElement("second", true);
    printer.CloseElement(true);
    
    std::string second = printer.CStr();
    EXPECT_NE(second.find("<second/>"), std::string::npos);
    EXPECT_EQ(second.find("<first/>"), std::string::npos);
}

// ============================================================
// Entity escaping in text
// ============================================================

TEST_F(XMLPrinterTest_311, PushTextString_WithAmpersand_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText("a&b", false);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("&amp;"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_311, PushTextString_WithLessThan_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText("a<b", false);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("&lt;"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_311, PushTextString_WithGreaterThan_311) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText("a>b", false);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("&gt;"), std::string::npos) << "Result: " << result;
}
