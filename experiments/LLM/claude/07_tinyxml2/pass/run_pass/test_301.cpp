#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include <cstdio>
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for XMLPrinter tests
class XMLPrinterTest_301 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== PushAttribute(bool) Tests ====================

TEST_F(XMLPrinterTest_301, PushAttributeBoolTrue_301) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    printer.PushAttribute("flag", true);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("flag=\"true\""), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_301, PushAttributeBoolFalse_301) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    printer.PushAttribute("flag", false);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("flag=\"false\""), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_301, PushAttributeBoolMultiple_301) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    printer.PushAttribute("a", true);
    printer.PushAttribute("b", false);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("a=\"true\""), std::string::npos) << "Result: " << result;
    EXPECT_NE(result.find("b=\"false\""), std::string::npos) << "Result: " << result;
}

// ==================== PushAttribute(const char*) Tests ====================

TEST_F(XMLPrinterTest_301, PushAttributeString_301) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    printer.PushAttribute("name", "value");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("name=\"value\""), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_301, PushAttributeEmptyString_301) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    printer.PushAttribute("name", "");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("name=\"\""), std::string::npos) << "Result: " << result;
}

// ==================== PushAttribute(int) Tests ====================

TEST_F(XMLPrinterTest_301, PushAttributeInt_301) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    printer.PushAttribute("count", 42);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("count=\"42\""), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_301, PushAttributeIntNegative_301) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    printer.PushAttribute("count", -100);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("count=\"-100\""), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_301, PushAttributeIntZero_301) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    printer.PushAttribute("count", 0);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("count=\"0\""), std::string::npos) << "Result: " << result;
}

// ==================== PushAttribute(unsigned int) Tests ====================

TEST_F(XMLPrinterTest_301, PushAttributeUnsigned_301) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    printer.PushAttribute("val", (unsigned int)123);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val=\"123\""), std::string::npos) << "Result: " << result;
}

// ==================== PushAttribute(int64_t) Tests ====================

TEST_F(XMLPrinterTest_301, PushAttributeInt64_301) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    int64_t bigVal = 9223372036854775807LL;
    printer.PushAttribute("big", bigVal);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("big=\"9223372036854775807\""), std::string::npos) << "Result: " << result;
}

// ==================== PushAttribute(uint64_t) Tests ====================

TEST_F(XMLPrinterTest_301, PushAttributeUint64_301) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    uint64_t bigVal = 18446744073709551615ULL;
    printer.PushAttribute("big", bigVal);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("big=\"18446744073709551615\""), std::string::npos) << "Result: " << result;
}

// ==================== PushAttribute(double) Tests ====================

TEST_F(XMLPrinterTest_301, PushAttributeDouble_301) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    printer.PushAttribute("pi", 3.14);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("pi="), std::string::npos) << "Result: " << result;
    // The value should contain 3.14 in some form
    EXPECT_NE(result.find("3.14"), std::string::npos) << "Result: " << result;
}

// ==================== OpenElement / CloseElement Tests ====================

TEST_F(XMLPrinterTest_301, BasicOpenCloseElement_301) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root/>"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_301, NestedElements_301) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root>"), std::string::npos) << "Result: " << result;
    EXPECT_NE(result.find("<child/>"), std::string::npos) << "Result: " << result;
    EXPECT_NE(result.find("</root>"), std::string::npos) << "Result: " << result;
}

// ==================== PushText Tests ====================

TEST_F(XMLPrinterTest_301, PushTextString_301) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    printer.PushText("Hello World");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("Hello World"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_301, PushTextInt_301) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    printer.PushText(42);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("42"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_301, PushTextBoolTrue_301) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    printer.PushText(true);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("true"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_301, PushTextBoolFalse_301) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    printer.PushText(false);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("false"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_301, PushTextFloat_301) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    printer.PushText(2.5f);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("2.5"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_301, PushTextDouble_301) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    printer.PushText(1.23);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("1.23"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_301, PushTextInt64_301) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    printer.PushText((int64_t)123456789012345LL);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("123456789012345"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_301, PushTextUint64_301) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    printer.PushText((uint64_t)123456789012345ULL);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("123456789012345"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_301, PushTextUnsigned_301) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    printer.PushText((unsigned int)999);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("999"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_301, PushTextCData_301) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    printer.PushText("some data", true);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<![CDATA[some data]]>"), std::string::npos) << "Result: " << result;
}

// ==================== PushComment Tests ====================

TEST_F(XMLPrinterTest_301, PushComment_301) {
    XMLPrinter printer(nullptr, true);
    printer.PushComment("This is a comment");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!--This is a comment-->"), std::string::npos) << "Result: " << result;
}

// ==================== PushDeclaration Tests ====================

TEST_F(XMLPrinterTest_301, PushDeclaration_301) {
    XMLPrinter printer(nullptr, true);
    printer.PushDeclaration("xml version=\"1.0\"");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml version=\"1.0\"?>"), std::string::npos) << "Result: " << result;
}

// ==================== PushUnknown Tests ====================

TEST_F(XMLPrinterTest_301, PushUnknown_301) {
    XMLPrinter printer(nullptr, true);
    printer.PushUnknown("something unknown");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!something unknown>"), std::string::npos) << "Result: " << result;
}

// ==================== PushHeader Tests ====================

TEST_F(XMLPrinterTest_301, PushHeaderWithDeclaration_301) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(false, true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_301, PushHeaderWithBOM_301) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(true, false);
    std::string result = printer.CStr();
    // BOM should be at the start: 0xEF 0xBB 0xBF
    EXPECT_GE(printer.CStrSize(), 3u);
}

TEST_F(XMLPrinterTest_301, PushHeaderBothBOMAndDeclaration_301) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(true, true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml"), std::string::npos) << "Result: " << result;
}

// ==================== CStr / CStrSize / ClearBuffer Tests ====================

TEST_F(XMLPrinterTest_301, CStrSizeInitial_301) {
    XMLPrinter printer(nullptr, true);
    // Initially, CStr should return an empty or near-empty string
    const char* str = printer.CStr();
    EXPECT_NE(str, nullptr);
    size_t sz = printer.CStrSize();
    // Size should include null terminator at minimum
    EXPECT_GE(sz, 1u);
}

TEST_F(XMLPrinterTest_301, CStrSizeAfterElement_301) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test");
    printer.CloseElement();
    size_t sz = printer.CStrSize();
    std::string result = printer.CStr();
    // CStrSize should be length of string + 1 for null terminator
    EXPECT_EQ(sz, result.length() + 1);
}

TEST_F(XMLPrinterTest_301, ClearBuffer_301) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test");
    printer.CloseElement();
    EXPECT_GT(printer.CStrSize(), 1u);
    printer.ClearBuffer();
    // After clearing, buffer should be minimal
    EXPECT_LE(printer.CStrSize(), 1u);
}

// ==================== Compact Mode Tests ====================

TEST_F(XMLPrinterTest_301, CompactModeOutput_301) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.PushText("text");
    printer.CloseElement();
    printer.CloseElement();
    std::string result = printer.CStr();
    // Compact mode should not have newlines between elements
    EXPECT_EQ(result.find('\n'), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_301, NonCompactModeOutput_301) {
    XMLPrinter printer(nullptr, false);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string result = printer.CStr();
    // Non-compact mode should have newlines
    EXPECT_NE(result.find('\n'), std::string::npos) << "Result: " << result;
}

// ==================== XMLUtil Tests ====================

class XMLUtilTest_301 : public ::testing::Test {};

TEST_F(XMLUtilTest_301, ToStrBoolTrue_301) {
    char buf[200];
    XMLUtil::ToStr(true, buf, 200);
    EXPECT_STREQ(buf, "true");
}

TEST_F(XMLUtilTest_301, ToStrBoolFalse_301) {
    char buf[200];
    XMLUtil::ToStr(false, buf, 200);
    EXPECT_STREQ(buf, "false");
}

TEST_F(XMLUtilTest_301, ToStrInt_301) {
    char buf[200];
    XMLUtil::ToStr(42, buf, 200);
    EXPECT_STREQ(buf, "42");
}

TEST_F(XMLUtilTest_301, ToStrIntNegative_301) {
    char buf[200];
    XMLUtil::ToStr(-7, buf, 200);
    EXPECT_STREQ(buf, "-7");
}

TEST_F(XMLUtilTest_301, ToStrIntZero_301) {
    char buf[200];
    XMLUtil::ToStr(0, buf, 200);
    EXPECT_STREQ(buf, "0");
}

TEST_F(XMLUtilTest_301, ToStrUnsigned_301) {
    char buf[200];
    XMLUtil::ToStr((unsigned int)100, buf, 200);
    EXPECT_STREQ(buf, "100");
}

TEST_F(XMLUtilTest_301, ToStrDouble_301) {
    char buf[200];
    XMLUtil::ToStr(3.14, buf, 200);
    std::string result(buf);
    EXPECT_NE(result.find("3.14"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLUtilTest_301, ToStrFloat_301) {
    char buf[200];
    XMLUtil::ToStr(2.5f, buf, 200);
    std::string result(buf);
    EXPECT_NE(result.find("2.5"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLUtilTest_301, ToStrInt64_301) {
    char buf[200];
    XMLUtil::ToStr((int64_t)9223372036854775807LL, buf, 200);
    EXPECT_STREQ(buf, "9223372036854775807");
}

TEST_F(XMLUtilTest_301, ToStrUint64_301) {
    char buf[200];
    XMLUtil::ToStr((uint64_t)18446744073709551615ULL, buf, 200);
    EXPECT_STREQ(buf, "18446744073709551615");
}

TEST_F(XMLUtilTest_301, ToBoolTrue_301) {
    bool val = false;
    EXPECT_TRUE(XMLUtil::ToBool("true", &val));
    EXPECT_TRUE(val);
}

TEST_F(XMLUtilTest_301, ToBoolFalse_301) {
    bool val = true;
    EXPECT_TRUE(XMLUtil::ToBool("false", &val));
    EXPECT_FALSE(val);
}

TEST_F(XMLUtilTest_301, ToBoolInvalid_301) {
    bool val = false;
    EXPECT_FALSE(XMLUtil::ToBool("notabool", &val));
}

TEST_F(XMLUtilTest_301, ToIntValid_301) {
    int val = 0;
    EXPECT_TRUE(XMLUtil::ToInt("123", &val));
    EXPECT_EQ(val, 123);
}

TEST_F(XMLUtilTest_301, ToIntInvalid_301) {
    int val = 0;
    EXPECT_FALSE(XMLUtil::ToInt("abc", &val));
}

TEST_F(XMLUtilTest_301, ToUnsignedValid_301) {
    unsigned int val = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned("456", &val));
    EXPECT_EQ(val, 456u);
}

TEST_F(XMLUtilTest_301, ToUnsignedInvalid_301) {
    unsigned int val = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned("xyz", &val));
}

TEST_F(XMLUtilTest_301, ToFloatValid_301) {
    float val = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat("1.5", &val));
    EXPECT_FLOAT_EQ(val, 1.5f);
}

TEST_F(XMLUtilTest_301, ToFloatInvalid_301) {
    float val = 0.0f;
    EXPECT_FALSE(XMLUtil::ToFloat("notafloat", &val));
}

TEST_F(XMLUtilTest_301, ToDoubleValid_301) {
    double val = 0.0;
    EXPECT_TRUE(XMLUtil::ToDouble("2.718", &val));
    EXPECT_DOUBLE_EQ(val, 2.718);
}

TEST_F(XMLUtilTest_301, ToDoubleInvalid_301) {
    double val = 0.0;
    EXPECT_FALSE(XMLUtil::ToDouble("notadouble", &val));
}

TEST_F(XMLUtilTest_301, ToInt64Valid_301) {
    int64_t val = 0;
    EXPECT_TRUE(XMLUtil::ToInt64("9223372036854775807", &val));
    EXPECT_EQ(val, 9223372036854775807LL);
}

TEST_F(XMLUtilTest_301, ToInt64Invalid_301) {
    int64_t val = 0;
    EXPECT_FALSE(XMLUtil::ToInt64("abc", &val));
}

TEST_F(XMLUtilTest_301, ToUnsigned64Valid_301) {
    uint64_t val = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned64("18446744073709551615", &val));
    EXPECT_EQ(val, 18446744073709551615ULL);
}

TEST_F(XMLUtilTest_301, ToUnsigned64Invalid_301) {
    uint64_t val = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned64("xyz", &val));
}

TEST_F(XMLUtilTest_301, StringEqualSame_301) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello"));
}

TEST_F(XMLUtilTest_301, StringEqualDifferent_301) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world"));
}

TEST_F(XMLUtilTest_301, StringEqualWithN_301) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "help", 3));
}

TEST_F(XMLUtilTest_301, IsWhiteSpaceTrue_301) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\n'));
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\r'));
}

TEST_F(XMLUtilTest_301, IsWhiteSpaceFalse_301) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('a'));
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('1'));
}

// ==================== SetBoolSerialization Tests ====================

TEST_F(XMLUtilTest_301, SetBoolSerializationCustom_301) {
    XMLUtil::SetBoolSerialization("yes", "no");
    char buf[200];
    XMLUtil::ToStr(true, buf, 200);
    EXPECT_STREQ(buf, "yes");
    XMLUtil::ToStr(false, buf, 200);
    EXPECT_STREQ(buf, "no");
    // Reset to defaults
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
}

TEST_F(XMLUtilTest_301, SetBoolSerializationReset_301) {
    XMLUtil::SetBoolSerialization("yes", "no");
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
    char buf[200];
    XMLUtil::ToStr(true, buf, 200);
    EXPECT_STREQ(buf, "true");
    XMLUtil::ToStr(false, buf, 200);
    EXPECT_STREQ(buf, "false");
}

// ==================== XMLPrinter with SetBoolSerialization ====================

TEST_F(XMLPrinterTest_301, PushAttributeBoolCustomSerialization_301) {
    XMLUtil::SetBoolSerialization("yes", "no");
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    printer.PushAttribute("flag", true);
    printer.PushAttribute("other", false);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("flag=\"yes\""), std::string::npos) << "Result: " << result;
    EXPECT_NE(result.find("other=\"no\""), std::string::npos) << "Result: " << result;
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
}

// ==================== Complex Document Tests ====================

TEST_F(XMLPrinterTest_301, ComplexDocument_301) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(false, true);
    printer.OpenElement("root");
    printer.PushAttribute("version", "1.0");
    printer.OpenElement("item");
    printer.PushAttribute("id", 1);
    printer.PushAttribute("active", true);
    printer.PushText("Item text");
    printer.CloseElement();
    printer.OpenElement("item");
    printer.PushAttribute("id", 2);
    printer.PushAttribute("active", false);
    printer.PushText("Another item");
    printer.CloseElement();
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml"), std::string::npos);
    EXPECT_NE(result.find("<root"), std::string::npos);
    EXPECT_NE(result.find("version=\"1.0\""), std::string::npos);
    EXPECT_NE(result.find("id=\"1\""), std::string::npos);
    EXPECT_NE(result.find("active=\"true\""), std::string::npos);
    EXPECT_NE(result.find("Item text"), std::string::npos);
    EXPECT_NE(result.find("id=\"2\""), std::string::npos);
    EXPECT_NE(result.find("active=\"false\""), std::string::npos);
    EXPECT_NE(result.find("Another item"), std::string::npos);
    EXPECT_NE(result.find("</root>"), std::string::npos);
}

// ==================== Visitor pattern tests with XMLDocument ====================

TEST_F(XMLPrinterTest_301, VisitDocument_301) {
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
    EXPECT_NE(result.find("</child>"), std::string::npos) << "Result: " << result;
    EXPECT_NE(result.find("</root>"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_301, VisitDocumentWithComment_301) {
    XMLDocument doc;
    doc.Parse("<!-- comment --><root/>");
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);

    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!--"), std::string::npos) << "Result: " << result;
    EXPECT_NE(result.find("<root/>"), std::string::npos) << "Result: " << result;
}

TEST_F(XMLPrinterTest_301, VisitDocumentWithDeclaration_301) {
    XMLDocument doc;
    doc.Parse("<?xml version=\"1.0\"?><root/>");
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);

    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml"), std::string::npos) << "Result: " << result;
    EXPECT_NE(result.find("<root/>"), std::string::npos) << "Result: " << result;
}

// ==================== File output test ====================

TEST_F(XMLPrinterTest_301, OutputToFile_301) {
    const char* filename = "test_output_301.xml";
    FILE* fp = fopen(filename, "w");
    ASSERT_NE(fp, nullptr);

    XMLPrinter printer(fp, true);
    printer.OpenElement("test");
    printer.PushAttribute("val", true);
    printer.CloseElement();

    fclose(fp);

    // Read back and verify
    FILE* rfp = fopen(filename, "r");
    ASSERT_NE(rfp, nullptr);
    char buf[1024];
    size_t nread = fread(buf, 1, sizeof(buf) - 1, rfp);
    buf[nread] = '\0';
    fclose(rfp);
    remove(filename);

    std::string result(buf);
    EXPECT_NE(result.find("<test"), std::string::npos) << "Result: " << result;
    EXPECT_NE(result.find("val=\"true\""), std::string::npos) << "Result: " << result;
}

// ==================== ReadBOM Tests ====================

TEST_F(XMLUtilTest_301, ReadBOMWithBOM_301) {
    const char input[] = "\xEF\xBB\xBF<root/>";
    bool hasBOM = false;
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_TRUE(hasBOM);
    EXPECT_EQ(result, input + 3);
}

TEST_F(XMLUtilTest_301, ReadBOMWithoutBOM_301) {
    const char input[] = "<root/>";
    bool hasBOM = false;
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_FALSE(hasBOM);
    EXPECT_EQ(result, input);
}

// ==================== Empty element with attributes ====================

TEST_F(XMLPrinterTest_301, EmptyElementWithAttributes_301) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("img");
    printer.PushAttribute("src", "pic.png");
    printer.PushAttribute("width", 100);
    printer.PushAttribute("height", 200);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("src=\"pic.png\""), std::string::npos) << "Result: " << result;
    EXPECT_NE(result.find("width=\"100\""), std::string::npos) << "Result: " << result;
    EXPECT_NE(result.find("height=\"200\""), std::string::npos) << "Result: " << result;
    // Self-closing since no content
    EXPECT_NE(result.find("/>"), std::string::npos) << "Result: " << result;
}

// ==================== Multiple ClearBuffer calls ====================

TEST_F(XMLPrinterTest_301, MultipleClearBuffer_301) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("first");
    printer.CloseElement();
    std::string first = printer.CStr();
    EXPECT_NE(first.find("<first/>"), std::string::npos);

    printer.ClearBuffer();
    printer.OpenElement("second");
    printer.CloseElement();
    std::string second = printer.CStr();
    EXPECT_NE(second.find("<second/>"), std::string::npos);
    EXPECT_EQ(second.find("<first/>"), std::string::npos);
}

// ==================== IsPrefixHex Tests ====================

TEST_F(XMLUtilTest_301, IsPrefixHexTrue_301) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0x1A"));
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0X1A"));
}

TEST_F(XMLUtilTest_301, IsPrefixHexFalse_301) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("123"));
    EXPECT_FALSE(XMLUtil::IsPrefixHex("abc"));
}
