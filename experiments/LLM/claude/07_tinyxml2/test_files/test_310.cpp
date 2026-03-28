#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include <cstdio>
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for XMLPrinter tests
class XMLPrinterTest_310 : public ::testing::Test {
protected:
    void SetUp() override {
        // Reset bool serialization to defaults before each test
        XMLUtil::SetBoolSerialization(nullptr, nullptr);
    }
};

// ==================== XMLPrinter Basic Construction ====================

TEST_F(XMLPrinterTest_310, DefaultConstruction_310) {
    XMLPrinter printer;
    EXPECT_NE(printer.CStr(), nullptr);
    EXPECT_EQ(printer.CStrSize(), 1u); // Just null terminator
}

TEST_F(XMLPrinterTest_310, CompactModeConstruction_310) {
    XMLPrinter printer(nullptr, true);
    EXPECT_NE(printer.CStr(), nullptr);
}

// ==================== PushText(bool) Tests ====================

TEST_F(XMLPrinterTest_310, PushTextBoolTrue_310) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("true"), std::string::npos);
}

TEST_F(XMLPrinterTest_310, PushTextBoolFalse_310) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(false);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("false"), std::string::npos);
}

TEST_F(XMLPrinterTest_310, PushTextBoolTrueCustomSerialization_310) {
    XMLUtil::SetBoolSerialization("yes", "no");
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("yes"), std::string::npos);
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
}

TEST_F(XMLPrinterTest_310, PushTextBoolFalseCustomSerialization_310) {
    XMLUtil::SetBoolSerialization("yes", "no");
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(false);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("no"), std::string::npos);
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
}

// ==================== PushText(int) Tests ====================

TEST_F(XMLPrinterTest_310, PushTextInt_310) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(42);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("42"), std::string::npos);
}

TEST_F(XMLPrinterTest_310, PushTextIntNegative_310) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(-100);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("-100"), std::string::npos);
}

TEST_F(XMLPrinterTest_310, PushTextIntZero_310) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(0);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("0"), std::string::npos);
}

// ==================== PushText(unsigned int) Tests ====================

TEST_F(XMLPrinterTest_310, PushTextUnsigned_310) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(123u);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("123"), std::string::npos);
}

// ==================== PushText(int64_t) Tests ====================

TEST_F(XMLPrinterTest_310, PushTextInt64_310) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText((int64_t)9223372036854775807LL);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("9223372036854775807"), std::string::npos);
}

// ==================== PushText(uint64_t) Tests ====================

TEST_F(XMLPrinterTest_310, PushTextUint64_310) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText((uint64_t)18446744073709551615ULL);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("18446744073709551615"), std::string::npos);
}

// ==================== PushText(float) Tests ====================

TEST_F(XMLPrinterTest_310, PushTextFloat_310) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(3.14f);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

// ==================== PushText(double) Tests ====================

TEST_F(XMLPrinterTest_310, PushTextDouble_310) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(2.71828);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("2.71828"), std::string::npos);
}

// ==================== PushText(const char*) Tests ====================

TEST_F(XMLPrinterTest_310, PushTextString_310) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText("Hello World", false);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("Hello World"), std::string::npos);
}

TEST_F(XMLPrinterTest_310, PushTextStringCDATA_310) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText("Hello World", true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<![CDATA[Hello World]]>"), std::string::npos);
}

TEST_F(XMLPrinterTest_310, PushTextEmptyString_310) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText("", false);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root>"), std::string::npos);
}

// ==================== OpenElement / CloseElement Tests ====================

TEST_F(XMLPrinterTest_310, OpenAndCloseElement_310) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<test/>"), std::string::npos);
}

TEST_F(XMLPrinterTest_310, NestedElements_310) {
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

TEST_F(XMLPrinterTest_310, NonCompactModeFormatting_310) {
    XMLPrinter printer(nullptr, false);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string result = printer.CStr();
    // Non-compact mode should have newlines
    EXPECT_NE(result.find("\n"), std::string::npos);
}

// ==================== PushAttribute Tests ====================

TEST_F(XMLPrinterTest_310, PushAttributeString_310) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushAttribute("name", "value");
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("name=\"value\""), std::string::npos);
}

TEST_F(XMLPrinterTest_310, PushAttributeInt_310) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushAttribute("count", 5);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("count=\"5\""), std::string::npos);
}

TEST_F(XMLPrinterTest_310, PushAttributeUnsigned_310) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushAttribute("val", 10u);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val=\"10\""), std::string::npos);
}

TEST_F(XMLPrinterTest_310, PushAttributeInt64_310) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushAttribute("big", (int64_t)1234567890123LL);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("big=\"1234567890123\""), std::string::npos);
}

TEST_F(XMLPrinterTest_310, PushAttributeUint64_310) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushAttribute("big", (uint64_t)9876543210ULL);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("big=\"9876543210\""), std::string::npos);
}

TEST_F(XMLPrinterTest_310, PushAttributeBoolTrue_310) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushAttribute("flag", true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("flag=\"true\""), std::string::npos);
}

TEST_F(XMLPrinterTest_310, PushAttributeBoolFalse_310) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushAttribute("flag", false);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("flag=\"false\""), std::string::npos);
}

TEST_F(XMLPrinterTest_310, PushAttributeDouble_310) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushAttribute("pi", 3.14159);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("pi=\""), std::string::npos);
    EXPECT_NE(result.find("3.14159"), std::string::npos);
}

TEST_F(XMLPrinterTest_310, MultipleAttributes_310) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushAttribute("a", "1");
    printer.PushAttribute("b", "2");
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("a=\"1\""), std::string::npos);
    EXPECT_NE(result.find("b=\"2\""), std::string::npos);
}

// ==================== PushHeader Tests ====================

TEST_F(XMLPrinterTest_310, PushHeaderWithBOM_310) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(true, true);
    std::string result = printer.CStr();
    // BOM bytes: 0xEF 0xBB 0xBF
    EXPECT_EQ((unsigned char)result[0], 0xEF);
    EXPECT_EQ((unsigned char)result[1], 0xBB);
    EXPECT_EQ((unsigned char)result[2], 0xBF);
}

TEST_F(XMLPrinterTest_310, PushHeaderWithDeclaration_310) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(false, true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml"), std::string::npos);
}

TEST_F(XMLPrinterTest_310, PushHeaderNoBOMNoDeclaration_310) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(false, false);
    std::string result = printer.CStr();
    EXPECT_EQ(result.find("<?xml"), std::string::npos);
}

// ==================== PushComment Tests ====================

TEST_F(XMLPrinterTest_310, PushComment_310) {
    XMLPrinter printer(nullptr, true);
    printer.PushComment("This is a comment");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!--This is a comment-->"), std::string::npos);
}

// ==================== PushDeclaration Tests ====================

TEST_F(XMLPrinterTest_310, PushDeclaration_310) {
    XMLPrinter printer(nullptr, true);
    printer.PushDeclaration("xml version=\"1.0\"");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml version=\"1.0\"?>"), std::string::npos);
}

// ==================== PushUnknown Tests ====================

TEST_F(XMLPrinterTest_310, PushUnknown_310) {
    XMLPrinter printer(nullptr, true);
    printer.PushUnknown("!DOCTYPE html");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!DOCTYPE html>"), std::string::npos);
}

// ==================== ClearBuffer Tests ====================

TEST_F(XMLPrinterTest_310, ClearBuffer_310) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.CloseElement(true);
    EXPECT_GT(printer.CStrSize(), 1u);
    printer.ClearBuffer();
    EXPECT_EQ(printer.CStrSize(), 1u); // Just null terminator after clear
}

// ==================== CStr / CStrSize Tests ====================

TEST_F(XMLPrinterTest_310, CStrSizeIncludesNullTerminator_310) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("a", true);
    printer.CloseElement(true);
    const char* str = printer.CStr();
    size_t len = strlen(str);
    EXPECT_EQ(printer.CStrSize(), len + 1);
}

// ==================== XMLDocument printing via Visitor ====================

TEST_F(XMLPrinterTest_310, PrintDocumentViaAccept_310) {
    XMLDocument doc;
    doc.Parse("<root><child>text</child></root>");
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root>"), std::string::npos);
    EXPECT_NE(result.find("<child>"), std::string::npos);
    EXPECT_NE(result.find("text"), std::string::npos);
    EXPECT_NE(result.find("</child>"), std::string::npos);
    EXPECT_NE(result.find("</root>"), std::string::npos);
}

TEST_F(XMLPrinterTest_310, PrintDocumentWithComment_310) {
    XMLDocument doc;
    doc.Parse("<!--comment--><root/>");
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!--comment-->"), std::string::npos);
    EXPECT_NE(result.find("<root/>"), std::string::npos);
}

TEST_F(XMLPrinterTest_310, PrintDocumentWithAttributes_310) {
    XMLDocument doc;
    doc.Parse("<root attr=\"val\"/>");
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("attr=\"val\""), std::string::npos);
}

// ==================== XMLUtil Tests ====================

class XMLUtilTest_310 : public ::testing::Test {};

TEST_F(XMLUtilTest_310, ToStrInt_310) {
    char buf[200];
    XMLUtil::ToStr(42, buf, 200);
    EXPECT_STREQ(buf, "42");
}

TEST_F(XMLUtilTest_310, ToStrIntNegative_310) {
    char buf[200];
    XMLUtil::ToStr(-7, buf, 200);
    EXPECT_STREQ(buf, "-7");
}

TEST_F(XMLUtilTest_310, ToStrUnsigned_310) {
    char buf[200];
    XMLUtil::ToStr(100u, buf, 200);
    EXPECT_STREQ(buf, "100");
}

TEST_F(XMLUtilTest_310, ToStrBoolTrue_310) {
    char buf[200];
    XMLUtil::ToStr(true, buf, 200);
    EXPECT_STREQ(buf, "true");
}

TEST_F(XMLUtilTest_310, ToStrBoolFalse_310) {
    char buf[200];
    XMLUtil::ToStr(false, buf, 200);
    EXPECT_STREQ(buf, "false");
}

TEST_F(XMLUtilTest_310, ToStrFloat_310) {
    char buf[200];
    XMLUtil::ToStr(1.5f, buf, 200);
    std::string result(buf);
    EXPECT_NE(result.find("1.5"), std::string::npos);
}

TEST_F(XMLUtilTest_310, ToStrDouble_310) {
    char buf[200];
    XMLUtil::ToStr(2.5, buf, 200);
    std::string result(buf);
    EXPECT_NE(result.find("2.5"), std::string::npos);
}

TEST_F(XMLUtilTest_310, ToStrInt64_310) {
    char buf[200];
    XMLUtil::ToStr((int64_t)1234567890123LL, buf, 200);
    EXPECT_STREQ(buf, "1234567890123");
}

TEST_F(XMLUtilTest_310, ToStrUint64_310) {
    char buf[200];
    XMLUtil::ToStr((uint64_t)9876543210ULL, buf, 200);
    EXPECT_STREQ(buf, "9876543210");
}

TEST_F(XMLUtilTest_310, ToInt_310) {
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt("123", &value));
    EXPECT_EQ(value, 123);
}

TEST_F(XMLUtilTest_310, ToIntInvalid_310) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt("abc", &value));
}

TEST_F(XMLUtilTest_310, ToUnsigned_310) {
    unsigned value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned("456", &value));
    EXPECT_EQ(value, 456u);
}

TEST_F(XMLUtilTest_310, ToUnsignedInvalid_310) {
    unsigned value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned("xyz", &value));
}

TEST_F(XMLUtilTest_310, ToBoolTrue_310) {
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool("true", &value));
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilTest_310, ToBoolFalse_310) {
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool("false", &value));
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilTest_310, ToBoolInvalid_310) {
    bool value = false;
    EXPECT_FALSE(XMLUtil::ToBool("maybe", &value));
}

TEST_F(XMLUtilTest_310, ToFloat_310) {
    float value = 0;
    EXPECT_TRUE(XMLUtil::ToFloat("3.14", &value));
    EXPECT_NEAR(value, 3.14f, 0.01f);
}

TEST_F(XMLUtilTest_310, ToFloatInvalid_310) {
    float value = 0;
    EXPECT_FALSE(XMLUtil::ToFloat("abc", &value));
}

TEST_F(XMLUtilTest_310, ToDouble_310) {
    double value = 0;
    EXPECT_TRUE(XMLUtil::ToDouble("2.71828", &value));
    EXPECT_NEAR(value, 2.71828, 0.0001);
}

TEST_F(XMLUtilTest_310, ToDoubleInvalid_310) {
    double value = 0;
    EXPECT_FALSE(XMLUtil::ToDouble("notanum", &value));
}

TEST_F(XMLUtilTest_310, ToInt64_310) {
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64("9223372036854775807", &value));
    EXPECT_EQ(value, 9223372036854775807LL);
}

TEST_F(XMLUtilTest_310, ToInt64Invalid_310) {
    int64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToInt64("abc", &value));
}

TEST_F(XMLUtilTest_310, ToUnsigned64_310) {
    uint64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned64("18446744073709551615", &value));
    EXPECT_EQ(value, 18446744073709551615ULL);
}

TEST_F(XMLUtilTest_310, ToUnsigned64Invalid_310) {
    uint64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned64("abc", &value));
}

TEST_F(XMLUtilTest_310, IsWhiteSpaceTrue_310) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\n'));
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\r'));
}

TEST_F(XMLUtilTest_310, IsWhiteSpaceFalse_310) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('a'));
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('0'));
}

TEST_F(XMLUtilTest_310, StringEqualSame_310) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello"));
}

TEST_F(XMLUtilTest_310, StringEqualDifferent_310) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world"));
}

TEST_F(XMLUtilTest_310, StringEqualWithLength_310) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "helloworld", 5));
}

TEST_F(XMLUtilTest_310, SetBoolSerialization_310) {
    XMLUtil::SetBoolSerialization("1", "0");
    char buf[200];
    XMLUtil::ToStr(true, buf, 200);
    EXPECT_STREQ(buf, "1");
    XMLUtil::ToStr(false, buf, 200);
    EXPECT_STREQ(buf, "0");
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
}

TEST_F(XMLUtilTest_310, SetBoolSerializationReset_310) {
    XMLUtil::SetBoolSerialization("yes", "no");
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
    char buf[200];
    XMLUtil::ToStr(true, buf, 200);
    EXPECT_STREQ(buf, "true");
    XMLUtil::ToStr(false, buf, 200);
    EXPECT_STREQ(buf, "false");
}

TEST_F(XMLUtilTest_310, ReadBOMPresent_310) {
    const char bomStr[] = "\xEF\xBB\xBF<root/>";
    bool hasBOM = false;
    const char* result = XMLUtil::ReadBOM(bomStr, &hasBOM);
    EXPECT_TRUE(hasBOM);
    EXPECT_EQ(result, bomStr + 3);
}

TEST_F(XMLUtilTest_310, ReadBOMAbsent_310) {
    const char noBomStr[] = "<root/>";
    bool hasBOM = false;
    const char* result = XMLUtil::ReadBOM(noBomStr, &hasBOM);
    EXPECT_FALSE(hasBOM);
    EXPECT_EQ(result, noBomStr);
}

// ==================== Complex XMLPrinter scenarios ====================

TEST_F(XMLPrinterTest_310, ElementWithTextContent_310) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("tag", true);
    printer.PushText("content", false);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<tag>content</tag>"), std::string::npos);
}

TEST_F(XMLPrinterTest_310, MultipleElementsSibling_310) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.OpenElement("a", true);
    printer.CloseElement(true);
    printer.OpenElement("b", true);
    printer.CloseElement(true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<a/>"), std::string::npos);
    EXPECT_NE(result.find("<b/>"), std::string::npos);
}

TEST_F(XMLPrinterTest_310, SelfClosingElementWithAttribute_310) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("img", true);
    printer.PushAttribute("src", "image.png");
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<img src=\"image.png\"/>"), std::string::npos);
}

TEST_F(XMLPrinterTest_310, PrintToFile_310) {
    FILE* fp = tmpfile();
    ASSERT_NE(fp, nullptr);
    {
        XMLPrinter printer(fp, true);
        printer.OpenElement("root", true);
        printer.PushText("hello", false);
        printer.CloseElement(true);
    }
    // Read back from file
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    EXPECT_GT(size, 0);
    std::string content(size, '\0');
    fread(&content[0], 1, size, fp);
    fclose(fp);
    EXPECT_NE(content.find("<root>hello</root>"), std::string::npos);
}

TEST_F(XMLPrinterTest_310, ClearBufferAndReuse_310) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("first", true);
    printer.CloseElement(true);
    printer.ClearBuffer();
    printer.OpenElement("second", true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_EQ(result.find("first"), std::string::npos);
    EXPECT_NE(result.find("<second/>"), std::string::npos);
}

// ==================== Entity handling ====================

TEST_F(XMLPrinterTest_310, PushTextWithSpecialChars_310) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText("a < b & c > d", false);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("&lt;"), std::string::npos);
    EXPECT_NE(result.find("&amp;"), std::string::npos);
    EXPECT_NE(result.find("&gt;"), std::string::npos);
}

TEST_F(XMLPrinterTest_310, PushAttributeWithSpecialChars_310) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushAttribute("val", "a&b");
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("&amp;"), std::string::npos);
}

// ==================== Depth parameter test ====================

TEST_F(XMLPrinterTest_310, CustomInitialDepth_310) {
    XMLPrinter printer(nullptr, false, 2);
    printer.OpenElement("root");
    printer.CloseElement();
    std::string result = printer.CStr();
    // With depth=2, there should be leading whitespace
    EXPECT_NE(result.find("root"), std::string::npos);
}
