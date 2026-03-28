#include <gtest/gtest.h>
#include <cstring>
#include <cmath>
#include <string>
#include <limits>
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for XMLPrinter tests
class XMLPrinterTest_312 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== PushText(double) Tests ====================

TEST_F(XMLPrinterTest_312, PushTextDouble_PositiveValue_312) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(3.14);
    printer.CloseElement(true);
    std::string output = printer.CStr();
    EXPECT_NE(output.find("3.14"), std::string::npos) << "Output: " << output;
}

TEST_F(XMLPrinterTest_312, PushTextDouble_NegativeValue_312) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(-2.718);
    printer.CloseElement(true);
    std::string output = printer.CStr();
    EXPECT_NE(output.find("-2.718"), std::string::npos) << "Output: " << output;
}

TEST_F(XMLPrinterTest_312, PushTextDouble_Zero_312) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(0.0);
    printer.CloseElement(true);
    std::string output = printer.CStr();
    EXPECT_NE(output.find("0"), std::string::npos) << "Output: " << output;
}

TEST_F(XMLPrinterTest_312, PushTextDouble_LargeValue_312) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(1.0e+100);
    printer.CloseElement(true);
    std::string output = printer.CStr();
    EXPECT_NE(output.find("1"), std::string::npos) << "Output: " << output;
}

TEST_F(XMLPrinterTest_312, PushTextDouble_SmallValue_312) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(1.0e-100);
    printer.CloseElement(true);
    std::string output = printer.CStr();
    EXPECT_GT(printer.CStrSize(), 0u);
}

TEST_F(XMLPrinterTest_312, PushTextDouble_MaxDouble_312) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(std::numeric_limits<double>::max());
    printer.CloseElement(true);
    std::string output = printer.CStr();
    EXPECT_FALSE(output.empty());
}

TEST_F(XMLPrinterTest_312, PushTextDouble_MinDouble_312) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(std::numeric_limits<double>::min());
    printer.CloseElement(true);
    std::string output = printer.CStr();
    EXPECT_FALSE(output.empty());
}

TEST_F(XMLPrinterTest_312, PushTextDouble_NegativeZero_312) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(-0.0);
    printer.CloseElement(true);
    std::string output = printer.CStr();
    EXPECT_NE(output.find("0"), std::string::npos) << "Output: " << output;
}

TEST_F(XMLPrinterTest_312, PushTextDouble_IntegerLikeValue_312) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(42.0);
    printer.CloseElement(true);
    std::string output = printer.CStr();
    EXPECT_NE(output.find("42"), std::string::npos) << "Output: " << output;
}

// ==================== PushText other types ====================

TEST_F(XMLPrinterTest_312, PushTextInt_PositiveValue_312) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(42);
    printer.CloseElement(true);
    std::string output = printer.CStr();
    EXPECT_NE(output.find("42"), std::string::npos) << "Output: " << output;
}

TEST_F(XMLPrinterTest_312, PushTextInt_NegativeValue_312) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(-99);
    printer.CloseElement(true);
    std::string output = printer.CStr();
    EXPECT_NE(output.find("-99"), std::string::npos) << "Output: " << output;
}

TEST_F(XMLPrinterTest_312, PushTextUnsigned_312) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText((unsigned)100);
    printer.CloseElement(true);
    std::string output = printer.CStr();
    EXPECT_NE(output.find("100"), std::string::npos) << "Output: " << output;
}

TEST_F(XMLPrinterTest_312, PushTextBool_True_312) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(true);
    printer.CloseElement(true);
    std::string output = printer.CStr();
    EXPECT_NE(output.find("true"), std::string::npos) << "Output: " << output;
}

TEST_F(XMLPrinterTest_312, PushTextBool_False_312) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(false);
    printer.CloseElement(true);
    std::string output = printer.CStr();
    EXPECT_NE(output.find("false"), std::string::npos) << "Output: " << output;
}

TEST_F(XMLPrinterTest_312, PushTextFloat_312) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(1.5f);
    printer.CloseElement(true);
    std::string output = printer.CStr();
    EXPECT_NE(output.find("1.5"), std::string::npos) << "Output: " << output;
}

TEST_F(XMLPrinterTest_312, PushTextInt64_312) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText((int64_t)1234567890123LL);
    printer.CloseElement(true);
    std::string output = printer.CStr();
    EXPECT_NE(output.find("1234567890123"), std::string::npos) << "Output: " << output;
}

TEST_F(XMLPrinterTest_312, PushTextUint64_312) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText((uint64_t)9876543210ULL);
    printer.CloseElement(true);
    std::string output = printer.CStr();
    EXPECT_NE(output.find("9876543210"), std::string::npos) << "Output: " << output;
}

TEST_F(XMLPrinterTest_312, PushTextString_312) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText("Hello World", false);
    printer.CloseElement(true);
    std::string output = printer.CStr();
    EXPECT_NE(output.find("Hello World"), std::string::npos) << "Output: " << output;
}

TEST_F(XMLPrinterTest_312, PushTextStringCDATA_312) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText("Some CDATA content", true);
    printer.CloseElement(true);
    std::string output = printer.CStr();
    EXPECT_NE(output.find("<![CDATA["), std::string::npos) << "Output: " << output;
    EXPECT_NE(output.find("Some CDATA content"), std::string::npos) << "Output: " << output;
}

// ==================== OpenElement / CloseElement Tests ====================

TEST_F(XMLPrinterTest_312, OpenAndCloseElement_312) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test", true);
    printer.CloseElement(true);
    std::string output = printer.CStr();
    EXPECT_NE(output.find("<test"), std::string::npos) << "Output: " << output;
    EXPECT_NE(output.find("/>"), std::string::npos) << "Output: " << output;
}

TEST_F(XMLPrinterTest_312, NestedElements_312) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("parent", true);
    printer.OpenElement("child", true);
    printer.CloseElement(true);
    printer.CloseElement(true);
    std::string output = printer.CStr();
    EXPECT_NE(output.find("<parent"), std::string::npos) << "Output: " << output;
    EXPECT_NE(output.find("<child"), std::string::npos) << "Output: " << output;
    EXPECT_NE(output.find("</parent>"), std::string::npos) << "Output: " << output;
}

// ==================== PushAttribute Tests ====================

TEST_F(XMLPrinterTest_312, PushAttributeString_312) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem", true);
    printer.PushAttribute("name", "value");
    printer.CloseElement(true);
    std::string output = printer.CStr();
    EXPECT_NE(output.find("name=\"value\""), std::string::npos) << "Output: " << output;
}

TEST_F(XMLPrinterTest_312, PushAttributeInt_312) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem", true);
    printer.PushAttribute("count", 42);
    printer.CloseElement(true);
    std::string output = printer.CStr();
    EXPECT_NE(output.find("count=\"42\""), std::string::npos) << "Output: " << output;
}

TEST_F(XMLPrinterTest_312, PushAttributeDouble_312) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem", true);
    printer.PushAttribute("val", 3.14);
    printer.CloseElement(true);
    std::string output = printer.CStr();
    EXPECT_NE(output.find("val="), std::string::npos) << "Output: " << output;
    EXPECT_NE(output.find("3.14"), std::string::npos) << "Output: " << output;
}

TEST_F(XMLPrinterTest_312, PushAttributeBool_312) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem", true);
    printer.PushAttribute("flag", true);
    printer.CloseElement(true);
    std::string output = printer.CStr();
    EXPECT_NE(output.find("flag=\"true\""), std::string::npos) << "Output: " << output;
}

TEST_F(XMLPrinterTest_312, PushAttributeUnsigned_312) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem", true);
    printer.PushAttribute("num", (unsigned)255);
    printer.CloseElement(true);
    std::string output = printer.CStr();
    EXPECT_NE(output.find("num=\"255\""), std::string::npos) << "Output: " << output;
}

TEST_F(XMLPrinterTest_312, PushAttributeInt64_312) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem", true);
    printer.PushAttribute("bignum", (int64_t)1234567890123LL);
    printer.CloseElement(true);
    std::string output = printer.CStr();
    EXPECT_NE(output.find("bignum=\"1234567890123\""), std::string::npos) << "Output: " << output;
}

TEST_F(XMLPrinterTest_312, PushAttributeUint64_312) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem", true);
    printer.PushAttribute("ubignum", (uint64_t)9876543210ULL);
    printer.CloseElement(true);
    std::string output = printer.CStr();
    EXPECT_NE(output.find("ubignum=\"9876543210\""), std::string::npos) << "Output: " << output;
}

// ==================== PushComment Tests ====================

TEST_F(XMLPrinterTest_312, PushComment_312) {
    XMLPrinter printer(nullptr, true);
    printer.PushComment("This is a comment");
    std::string output = printer.CStr();
    EXPECT_NE(output.find("<!--This is a comment-->"), std::string::npos) << "Output: " << output;
}

// ==================== PushDeclaration Tests ====================

TEST_F(XMLPrinterTest_312, PushDeclaration_312) {
    XMLPrinter printer(nullptr, true);
    printer.PushDeclaration("xml version=\"1.0\"");
    std::string output = printer.CStr();
    EXPECT_NE(output.find("<?xml version=\"1.0\"?>"), std::string::npos) << "Output: " << output;
}

// ==================== PushUnknown Tests ====================

TEST_F(XMLPrinterTest_312, PushUnknown_312) {
    XMLPrinter printer(nullptr, true);
    printer.PushUnknown("SOMETHING");
    std::string output = printer.CStr();
    EXPECT_NE(output.find("<!SOMETHING>"), std::string::npos) << "Output: " << output;
}

// ==================== PushHeader Tests ====================

TEST_F(XMLPrinterTest_312, PushHeader_WithBOMAndDeclaration_312) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(true, true);
    std::string output = printer.CStr();
    // BOM is 0xEF 0xBB 0xBF
    EXPECT_GE(output.size(), 3u);
    EXPECT_NE(output.find("<?xml"), std::string::npos) << "Output: " << output;
}

TEST_F(XMLPrinterTest_312, PushHeader_WithoutBOMWithDeclaration_312) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(false, true);
    std::string output = printer.CStr();
    EXPECT_NE(output.find("<?xml"), std::string::npos) << "Output: " << output;
}

TEST_F(XMLPrinterTest_312, PushHeader_WithoutBOMWithoutDeclaration_312) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(false, false);
    std::string output = printer.CStr();
    // Should be empty or near-empty
    EXPECT_EQ(output.find("<?xml"), std::string::npos) << "Output: " << output;
}

// ==================== CStr / CStrSize / ClearBuffer Tests ====================

TEST_F(XMLPrinterTest_312, CStr_EmptyPrinter_312) {
    XMLPrinter printer(nullptr, true);
    const char* result = printer.CStr();
    EXPECT_NE(result, nullptr);
}

TEST_F(XMLPrinterTest_312, CStrSize_EmptyPrinter_312) {
    XMLPrinter printer(nullptr, true);
    size_t size = printer.CStrSize();
    // At minimum should be > 0 for null terminator
    EXPECT_GE(size, 0u);
}

TEST_F(XMLPrinterTest_312, CStrSize_AfterContent_312) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test", true);
    printer.CloseElement(true);
    size_t size = printer.CStrSize();
    EXPECT_GT(size, 0u);
}

TEST_F(XMLPrinterTest_312, ClearBuffer_312) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test", true);
    printer.CloseElement(true);
    EXPECT_GT(printer.CStrSize(), 0u);
    printer.ClearBuffer();
    // After clearing, should be minimal
    size_t sizeAfterClear = printer.CStrSize();
    // CStr should still be valid
    EXPECT_NE(printer.CStr(), nullptr);
}

// ==================== XMLDocument with XMLPrinter (Visitor) ====================

TEST_F(XMLPrinterTest_312, VisitDocument_312) {
    XMLDocument doc;
    doc.Parse("<root><child>text</child></root>");
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);

    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string output = printer.CStr();
    EXPECT_NE(output.find("<root>"), std::string::npos) << "Output: " << output;
    EXPECT_NE(output.find("<child>"), std::string::npos) << "Output: " << output;
    EXPECT_NE(output.find("text"), std::string::npos) << "Output: " << output;
}

TEST_F(XMLPrinterTest_312, VisitDocumentWithAttributes_312) {
    XMLDocument doc;
    doc.Parse("<root attr=\"val\"><child id=\"1\"/></root>");
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);

    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string output = printer.CStr();
    EXPECT_NE(output.find("attr=\"val\""), std::string::npos) << "Output: " << output;
    EXPECT_NE(output.find("id=\"1\""), std::string::npos) << "Output: " << output;
}

// ==================== Non-compact mode ====================

TEST_F(XMLPrinterTest_312, NonCompactMode_312) {
    XMLPrinter printer(nullptr, false);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.PushText("hello", false);
    printer.CloseElement();
    printer.CloseElement();
    std::string output = printer.CStr();
    EXPECT_NE(output.find("<root>"), std::string::npos) << "Output: " << output;
    EXPECT_NE(output.find("<child>"), std::string::npos) << "Output: " << output;
    EXPECT_NE(output.find("hello"), std::string::npos) << "Output: " << output;
    // Non-compact mode should have newlines
    EXPECT_NE(output.find("\n"), std::string::npos) << "Output: " << output;
}

// ==================== Multiple PushText double in sequence ====================

TEST_F(XMLPrinterTest_312, MultiplePushTextDouble_312) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.OpenElement("a", true);
    printer.PushText(1.1);
    printer.CloseElement(true);
    printer.OpenElement("b", true);
    printer.PushText(2.2);
    printer.CloseElement(true);
    printer.CloseElement(true);
    std::string output = printer.CStr();
    EXPECT_NE(output.find("1.1"), std::string::npos) << "Output: " << output;
    EXPECT_NE(output.find("2.2"), std::string::npos) << "Output: " << output;
}

// ==================== Entity handling in PushText string ====================

TEST_F(XMLPrinterTest_312, PushTextWithEntities_312) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText("a < b & c > d", false);
    printer.CloseElement(true);
    std::string output = printer.CStr();
    EXPECT_NE(output.find("&lt;"), std::string::npos) << "Output: " << output;
    EXPECT_NE(output.find("&amp;"), std::string::npos) << "Output: " << output;
    EXPECT_NE(output.find("&gt;"), std::string::npos) << "Output: " << output;
}

// ==================== XMLUtil::ToStr and ToXxx Tests ====================

TEST_F(XMLPrinterTest_312, XMLUtil_ToStr_Int_312) {
    char buf[200];
    XMLUtil::ToStr(42, buf, 200);
    EXPECT_STREQ(buf, "42");
}

TEST_F(XMLPrinterTest_312, XMLUtil_ToStr_NegativeInt_312) {
    char buf[200];
    XMLUtil::ToStr(-100, buf, 200);
    EXPECT_STREQ(buf, "-100");
}

TEST_F(XMLPrinterTest_312, XMLUtil_ToStr_Unsigned_312) {
    char buf[200];
    XMLUtil::ToStr((unsigned)4294967295U, buf, 200);
    EXPECT_STREQ(buf, "4294967295");
}

TEST_F(XMLPrinterTest_312, XMLUtil_ToStr_Bool_True_312) {
    char buf[200];
    XMLUtil::ToStr(true, buf, 200);
    EXPECT_STREQ(buf, "true");
}

TEST_F(XMLPrinterTest_312, XMLUtil_ToStr_Bool_False_312) {
    char buf[200];
    XMLUtil::ToStr(false, buf, 200);
    EXPECT_STREQ(buf, "false");
}

TEST_F(XMLPrinterTest_312, XMLUtil_ToStr_Double_312) {
    char buf[200];
    XMLUtil::ToStr(3.14, buf, 200);
    std::string result(buf);
    EXPECT_NE(result.find("3.14"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_312, XMLUtil_ToStr_Float_312) {
    char buf[200];
    XMLUtil::ToStr(1.5f, buf, 200);
    std::string result(buf);
    EXPECT_NE(result.find("1.5"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_312, XMLUtil_ToStr_Int64_312) {
    char buf[200];
    XMLUtil::ToStr((int64_t)1234567890123LL, buf, 200);
    EXPECT_STREQ(buf, "1234567890123");
}

TEST_F(XMLPrinterTest_312, XMLUtil_ToStr_Uint64_312) {
    char buf[200];
    XMLUtil::ToStr((uint64_t)9876543210ULL, buf, 200);
    EXPECT_STREQ(buf, "9876543210");
}

TEST_F(XMLPrinterTest_312, XMLUtil_ToInt_Valid_312) {
    int value = 0;
    bool result = XMLUtil::ToInt("123", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(value, 123);
}

TEST_F(XMLPrinterTest_312, XMLUtil_ToInt_Invalid_312) {
    int value = 0;
    bool result = XMLUtil::ToInt("abc", &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLPrinterTest_312, XMLUtil_ToDouble_Valid_312) {
    double value = 0.0;
    bool result = XMLUtil::ToDouble("3.14159", &value);
    EXPECT_TRUE(result);
    EXPECT_NEAR(value, 3.14159, 1e-5);
}

TEST_F(XMLPrinterTest_312, XMLUtil_ToDouble_Invalid_312) {
    double value = 0.0;
    bool result = XMLUtil::ToDouble("not_a_number", &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLPrinterTest_312, XMLUtil_ToBool_True_312) {
    bool value = false;
    bool result = XMLUtil::ToBool("true", &value);
    EXPECT_TRUE(result);
    EXPECT_TRUE(value);
}

TEST_F(XMLPrinterTest_312, XMLUtil_ToBool_False_312) {
    bool value = true;
    bool result = XMLUtil::ToBool("false", &value);
    EXPECT_TRUE(result);
    EXPECT_FALSE(value);
}

TEST_F(XMLPrinterTest_312, XMLUtil_ToBool_Invalid_312) {
    bool value = false;
    bool result = XMLUtil::ToBool("maybe", &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLPrinterTest_312, XMLUtil_ToFloat_Valid_312) {
    float value = 0.0f;
    bool result = XMLUtil::ToFloat("2.5", &value);
    EXPECT_TRUE(result);
    EXPECT_NEAR(value, 2.5f, 1e-5f);
}

TEST_F(XMLPrinterTest_312, XMLUtil_ToUnsigned_Valid_312) {
    unsigned value = 0;
    bool result = XMLUtil::ToUnsigned("999", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(value, 999u);
}

TEST_F(XMLPrinterTest_312, XMLUtil_ToInt64_Valid_312) {
    int64_t value = 0;
    bool result = XMLUtil::ToInt64("9223372036854775807", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(value, 9223372036854775807LL);
}

TEST_F(XMLPrinterTest_312, XMLUtil_ToUnsigned64_Valid_312) {
    uint64_t value = 0;
    bool result = XMLUtil::ToUnsigned64("18446744073709551615", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(value, 18446744073709551615ULL);
}

// ==================== XMLUtil helper function tests ====================

TEST_F(XMLPrinterTest_312, XMLUtil_IsWhiteSpace_312) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\n'));
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\r'));
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('a'));
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('0'));
}

TEST_F(XMLPrinterTest_312, XMLUtil_StringEqual_312) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello"));
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world"));
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello world", 5));
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "help", 4));
}

TEST_F(XMLPrinterTest_312, XMLUtil_IsNameStartChar_312) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('a'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar('Z'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar('_'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar(':'));
    EXPECT_FALSE(XMLUtil::IsNameStartChar('0'));
    EXPECT_FALSE(XMLUtil::IsNameStartChar('-'));
}

TEST_F(XMLPrinterTest_312, XMLUtil_IsNameChar_312) {
    EXPECT_TRUE(XMLUtil::IsNameChar('a'));
    EXPECT_TRUE(XMLUtil::IsNameChar('0'));
    EXPECT_TRUE(XMLUtil::IsNameChar('-'));
    EXPECT_TRUE(XMLUtil::IsNameChar('.'));
    EXPECT_FALSE(XMLUtil::IsNameChar(' '));
}

// ==================== Complete XML round-trip with double values ====================

TEST_F(XMLPrinterTest_312, RoundTripDoubleValue_312) {
    XMLDocument doc;
    XMLElement* root = doc.NewElement("data");
    doc.InsertFirstChild(root);
    root->SetAttribute("value", 99.99);

    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string output = printer.CStr();
    EXPECT_NE(output.find("99.99"), std::string::npos) << "Output: " << output;

    // Parse back
    XMLDocument doc2;
    doc2.Parse(output.c_str());
    ASSERT_EQ(doc2.ErrorID(), XML_SUCCESS);
    double val = 0.0;
    doc2.FirstChildElement("data")->QueryDoubleAttribute("value", &val);
    EXPECT_NEAR(val, 99.99, 1e-5);
}

// ==================== SetBoolSerialization ====================

TEST_F(XMLPrinterTest_312, SetBoolSerialization_Custom_312) {
    XMLUtil::SetBoolSerialization("yes", "no");
    char buf[200];
    XMLUtil::ToStr(true, buf, 200);
    EXPECT_STREQ(buf, "yes");
    XMLUtil::ToStr(false, buf, 200);
    EXPECT_STREQ(buf, "no");
    // Reset to default
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
    XMLUtil::ToStr(true, buf, 200);
    EXPECT_STREQ(buf, "true");
    XMLUtil::ToStr(false, buf, 200);
    EXPECT_STREQ(buf, "false");
}

// ==================== ReadBOM ====================

TEST_F(XMLPrinterTest_312, ReadBOM_WithBOM_312) {
    const char bomData[] = "\xEF\xBB\xBF<root/>";
    bool hasBOM = false;
    const char* p = XMLUtil::ReadBOM(bomData, &hasBOM);
    EXPECT_TRUE(hasBOM);
    EXPECT_EQ(p, bomData + 3);
}

TEST_F(XMLPrinterTest_312, ReadBOM_WithoutBOM_312) {
    const char noBomData[] = "<root/>";
    bool hasBOM = false;
    const char* p = XMLUtil::ReadBOM(noBomData, &hasBOM);
    EXPECT_FALSE(hasBOM);
    EXPECT_EQ(p, noBomData);
}

// ==================== Printer with FILE* (write to file) ====================

TEST_F(XMLPrinterTest_312, PrinterToFile_312) {
    FILE* fp = tmpfile();
    ASSERT_NE(fp, nullptr);
    {
        XMLPrinter printer(fp, true);
        printer.OpenElement("root", true);
        printer.PushText(42.0);
        printer.CloseElement(true);
    }
    rewind(fp);
    char buf[1024];
    size_t bytesRead = fread(buf, 1, sizeof(buf) - 1, fp);
    buf[bytesRead] = '\0';
    fclose(fp);
    std::string output(buf);
    EXPECT_NE(output.find("<root>"), std::string::npos) << "Output: " << output;
    EXPECT_NE(output.find("42"), std::string::npos) << "Output: " << output;
}
