#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>
#include <string>
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for XMLPrinter tests
class XMLPrinterTest_291 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Write to Buffer Tests ====================

TEST_F(XMLPrinterTest_291, WriteToBuffer_BasicString_291) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("root");
    printer.CloseElement();
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::string(result).find("root") != std::string::npos);
}

TEST_F(XMLPrinterTest_291, WriteToBuffer_CStrSizeNotZero_291) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("test");
    printer.CloseElement();
    EXPECT_GT(printer.CStrSize(), 0u);
}

TEST_F(XMLPrinterTest_291, WriteToBuffer_EmptyPrinterCStrSize_291) {
    XMLPrinter printer(nullptr, false, 0);
    // Even empty printer should have some size (at least null terminator)
    size_t size = printer.CStrSize();
    EXPECT_GE(size, 0u);
}

// ==================== Write to FILE Tests ====================

TEST_F(XMLPrinterTest_291, WriteToFile_BasicElement_291) {
    FILE* fp = tmpfile();
    ASSERT_NE(fp, nullptr);
    {
        XMLPrinter printer(fp, false, 0);
        printer.OpenElement("root");
        printer.CloseElement();
    }
    fseek(fp, 0, SEEK_SET);
    char buf[256] = {};
    size_t bytesRead = fread(buf, 1, sizeof(buf) - 1, fp);
    fclose(fp);
    EXPECT_GT(bytesRead, 0u);
    EXPECT_TRUE(std::string(buf).find("root") != std::string::npos);
}

// ==================== OpenElement / CloseElement Tests ====================

TEST_F(XMLPrinterTest_291, OpenAndCloseElement_ProducesXML_291) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("element");
    printer.CloseElement();
    std::string result(printer.CStr());
    EXPECT_NE(result.find("<element"), std::string::npos);
    EXPECT_NE(result.find("</element>"), std::string::npos);
}

TEST_F(XMLPrinterTest_291, CompactModeCloseElement_291) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("element", true);
    printer.CloseElement(true);
    std::string result(printer.CStr());
    EXPECT_NE(result.find("<element"), std::string::npos);
}

TEST_F(XMLPrinterTest_291, NestedElements_291) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("parent");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string result(printer.CStr());
    EXPECT_NE(result.find("<parent"), std::string::npos);
    EXPECT_NE(result.find("<child"), std::string::npos);
    EXPECT_NE(result.find("</child>"), std::string::npos);
    EXPECT_NE(result.find("</parent>"), std::string::npos);
}

// ==================== PushAttribute Tests ====================

TEST_F(XMLPrinterTest_291, PushAttributeString_291) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("name", "value");
    printer.CloseElement();
    std::string result(printer.CStr());
    EXPECT_NE(result.find("name=\"value\""), std::string::npos);
}

TEST_F(XMLPrinterTest_291, PushAttributeInt_291) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("count", 42);
    printer.CloseElement();
    std::string result(printer.CStr());
    EXPECT_NE(result.find("count=\"42\""), std::string::npos);
}

TEST_F(XMLPrinterTest_291, PushAttributeUnsignedInt_291) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("count", (unsigned int)100);
    printer.CloseElement();
    std::string result(printer.CStr());
    EXPECT_NE(result.find("count=\"100\""), std::string::npos);
}

TEST_F(XMLPrinterTest_291, PushAttributeInt64_291) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("big", (int64_t)1234567890123LL);
    printer.CloseElement();
    std::string result(printer.CStr());
    EXPECT_NE(result.find("big=\"1234567890123\""), std::string::npos);
}

TEST_F(XMLPrinterTest_291, PushAttributeUInt64_291) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("big", (uint64_t)9876543210ULL);
    printer.CloseElement();
    std::string result(printer.CStr());
    EXPECT_NE(result.find("big=\"9876543210\""), std::string::npos);
}

TEST_F(XMLPrinterTest_291, PushAttributeBoolTrue_291) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("flag", true);
    printer.CloseElement();
    std::string result(printer.CStr());
    EXPECT_NE(result.find("flag=\"true\""), std::string::npos);
}

TEST_F(XMLPrinterTest_291, PushAttributeBoolFalse_291) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("flag", false);
    printer.CloseElement();
    std::string result(printer.CStr());
    EXPECT_NE(result.find("flag=\"false\""), std::string::npos);
}

TEST_F(XMLPrinterTest_291, PushAttributeDouble_291) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("val", 3.14);
    printer.CloseElement();
    std::string result(printer.CStr());
    EXPECT_NE(result.find("val="), std::string::npos);
}

TEST_F(XMLPrinterTest_291, MultipleAttributes_291) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("a", "1");
    printer.PushAttribute("b", "2");
    printer.PushAttribute("c", "3");
    printer.CloseElement();
    std::string result(printer.CStr());
    EXPECT_NE(result.find("a=\"1\""), std::string::npos);
    EXPECT_NE(result.find("b=\"2\""), std::string::npos);
    EXPECT_NE(result.find("c=\"3\""), std::string::npos);
}

// ==================== PushText Tests ====================

TEST_F(XMLPrinterTest_291, PushTextString_291) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText("Hello World");
    printer.CloseElement();
    std::string result(printer.CStr());
    EXPECT_NE(result.find("Hello World"), std::string::npos);
}

TEST_F(XMLPrinterTest_291, PushTextCDATA_291) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText("Hello CDATA", true);
    printer.CloseElement();
    std::string result(printer.CStr());
    EXPECT_NE(result.find("<![CDATA[Hello CDATA]]>"), std::string::npos);
}

TEST_F(XMLPrinterTest_291, PushTextInt_291) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText(42);
    printer.CloseElement();
    std::string result(printer.CStr());
    EXPECT_NE(result.find("42"), std::string::npos);
}

TEST_F(XMLPrinterTest_291, PushTextUnsigned_291) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText((unsigned)99);
    printer.CloseElement();
    std::string result(printer.CStr());
    EXPECT_NE(result.find("99"), std::string::npos);
}

TEST_F(XMLPrinterTest_291, PushTextInt64_291) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText((int64_t)1234567890123LL);
    printer.CloseElement();
    std::string result(printer.CStr());
    EXPECT_NE(result.find("1234567890123"), std::string::npos);
}

TEST_F(XMLPrinterTest_291, PushTextUInt64_291) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText((uint64_t)9876543210ULL);
    printer.CloseElement();
    std::string result(printer.CStr());
    EXPECT_NE(result.find("9876543210"), std::string::npos);
}

TEST_F(XMLPrinterTest_291, PushTextBoolTrue_291) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText(true);
    printer.CloseElement();
    std::string result(printer.CStr());
    EXPECT_NE(result.find("true"), std::string::npos);
}

TEST_F(XMLPrinterTest_291, PushTextBoolFalse_291) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText(false);
    printer.CloseElement();
    std::string result(printer.CStr());
    EXPECT_NE(result.find("false"), std::string::npos);
}

TEST_F(XMLPrinterTest_291, PushTextFloat_291) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText(1.5f);
    printer.CloseElement();
    std::string result(printer.CStr());
    EXPECT_NE(result.find("1.5"), std::string::npos);
}

TEST_F(XMLPrinterTest_291, PushTextDouble_291) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText(2.718);
    printer.CloseElement();
    std::string result(printer.CStr());
    // Should contain some representation of 2.718
    EXPECT_NE(result.find("2.718"), std::string::npos);
}

// ==================== PushComment Tests ====================

TEST_F(XMLPrinterTest_291, PushComment_291) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushComment("This is a comment");
    std::string result(printer.CStr());
    EXPECT_NE(result.find("<!--This is a comment-->"), std::string::npos);
}

// ==================== PushDeclaration Tests ====================

TEST_F(XMLPrinterTest_291, PushDeclaration_291) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushDeclaration("xml version=\"1.0\"");
    std::string result(printer.CStr());
    EXPECT_NE(result.find("<?xml version=\"1.0\"?>"), std::string::npos);
}

// ==================== PushUnknown Tests ====================

TEST_F(XMLPrinterTest_291, PushUnknown_291) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushUnknown("DOCTYPE html");
    std::string result(printer.CStr());
    EXPECT_NE(result.find("<!DOCTYPE html>"), std::string::npos);
}

// ==================== PushHeader Tests ====================

TEST_F(XMLPrinterTest_291, PushHeader_WithDeclaration_291) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushHeader(false, true);
    std::string result(printer.CStr());
    EXPECT_NE(result.find("<?xml"), std::string::npos);
}

TEST_F(XMLPrinterTest_291, PushHeader_WithBOM_291) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushHeader(true, false);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    // BOM is 3 bytes: 0xEF 0xBB 0xBF
    EXPECT_EQ((unsigned char)result[0], 0xEFu);
    EXPECT_EQ((unsigned char)result[1], 0xBBu);
    EXPECT_EQ((unsigned char)result[2], 0xBFu);
}

TEST_F(XMLPrinterTest_291, PushHeader_BothBOMAndDeclaration_291) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushHeader(true, true);
    std::string result(printer.CStr());
    // Should contain BOM and declaration
    EXPECT_EQ((unsigned char)result[0], 0xEFu);
    EXPECT_NE(result.find("<?xml"), std::string::npos);
}

TEST_F(XMLPrinterTest_291, PushHeader_NoBOMNoDeclaration_291) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushHeader(false, false);
    size_t size = printer.CStrSize();
    // Should be minimal or empty
    EXPECT_LE(size, 1u); // at most null terminator
}

// ==================== ClearBuffer Tests ====================

TEST_F(XMLPrinterTest_291, ClearBuffer_ResetsOutput_291) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.CloseElement();
    EXPECT_GT(printer.CStrSize(), 1u);
    printer.ClearBuffer();
    // After clear, buffer should be minimal
    size_t sizeAfterClear = printer.CStrSize();
    EXPECT_LE(sizeAfterClear, 1u);
}

TEST_F(XMLPrinterTest_291, ClearBuffer_CanWriteAgain_291) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("first");
    printer.CloseElement();
    printer.ClearBuffer();
    printer.OpenElement("second");
    printer.CloseElement();
    std::string result(printer.CStr());
    EXPECT_EQ(result.find("first"), std::string::npos);
    EXPECT_NE(result.find("second"), std::string::npos);
}

// ==================== Compact Mode Tests ====================

TEST_F(XMLPrinterTest_291, CompactMode_NoExtraWhitespace_291) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("parent", true);
    printer.OpenElement("child", true);
    printer.CloseElement(true);
    printer.CloseElement(true);
    std::string result(printer.CStr());
    // In compact mode, there should be no newlines between elements
    // The output should be something like <parent><child/></parent>
    EXPECT_NE(result.find("<parent>"), std::string::npos);
}

TEST_F(XMLPrinterTest_291, NonCompactMode_HasFormatting_291) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("parent");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string result(printer.CStr());
    // Non-compact should have newline characters
    EXPECT_NE(result.find("\n"), std::string::npos);
}

// ==================== Self-closing Element Tests ====================

TEST_F(XMLPrinterTest_291, SelfClosingElement_NoChildren_291) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("empty", true);
    printer.CloseElement(true);
    std::string result(printer.CStr());
    // Should produce self-closing tag like <empty/>
    EXPECT_NE(result.find("<empty/>"), std::string::npos);
}

TEST_F(XMLPrinterTest_291, SelfClosingElementWithAttributes_291) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("empty", true);
    printer.PushAttribute("key", "val");
    printer.CloseElement(true);
    std::string result(printer.CStr());
    EXPECT_NE(result.find("key=\"val\""), std::string::npos);
    EXPECT_NE(result.find("/>"), std::string::npos);
}

// ==================== XMLDocument integration with Visitor ====================

TEST_F(XMLPrinterTest_291, VisitDocument_RoundTrip_291) {
    const char* xml = "<root><child attr=\"1\">text</child></root>";
    XMLDocument doc;
    doc.Parse(xml);
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);

    XMLPrinter printer(nullptr, true, 0);
    doc.Accept(&printer);
    std::string result(printer.CStr());
    EXPECT_NE(result.find("<root>"), std::string::npos);
    EXPECT_NE(result.find("<child"), std::string::npos);
    EXPECT_NE(result.find("attr=\"1\""), std::string::npos);
    EXPECT_NE(result.find("text"), std::string::npos);
    EXPECT_NE(result.find("</child>"), std::string::npos);
    EXPECT_NE(result.find("</root>"), std::string::npos);
}

TEST_F(XMLPrinterTest_291, VisitDocumentWithComment_291) {
    const char* xml = "<!--comment--><root/>";
    XMLDocument doc;
    doc.Parse(xml);
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);

    XMLPrinter printer(nullptr, true, 0);
    doc.Accept(&printer);
    std::string result(printer.CStr());
    EXPECT_NE(result.find("<!--comment-->"), std::string::npos);
    EXPECT_NE(result.find("<root/>"), std::string::npos);
}

TEST_F(XMLPrinterTest_291, VisitDocumentWithDeclaration_291) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    XMLDocument doc;
    doc.Parse(xml);
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);

    XMLPrinter printer(nullptr, true, 0);
    doc.Accept(&printer);
    std::string result(printer.CStr());
    EXPECT_NE(result.find("<?xml"), std::string::npos);
    EXPECT_NE(result.find("<root/>"), std::string::npos);
}

// ==================== Boundary Tests ====================

TEST_F(XMLPrinterTest_291, EmptyElementName_291) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("", true);
    printer.CloseElement(true);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    // Should still produce some output
    EXPECT_GT(printer.CStrSize(), 0u);
}

TEST_F(XMLPrinterTest_291, EmptyTextPush_291) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("elem", true);
    printer.PushText("");
    printer.CloseElement(true);
    std::string result(printer.CStr());
    EXPECT_NE(result.find("elem"), std::string::npos);
}

TEST_F(XMLPrinterTest_291, EmptyComment_291) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushComment("");
    std::string result(printer.CStr());
    EXPECT_NE(result.find("<!---->"), std::string::npos);
}

TEST_F(XMLPrinterTest_291, LargeNestedStructure_291) {
    XMLPrinter printer(nullptr, true, 0);
    const int depth = 50;
    for (int i = 0; i < depth; i++) {
        printer.OpenElement("level", true);
    }
    for (int i = 0; i < depth; i++) {
        printer.CloseElement(true);
    }
    std::string result(printer.CStr());
    EXPECT_NE(result.find("<level>"), std::string::npos);
    EXPECT_NE(result.find("</level>"), std::string::npos);
}

// ==================== Special Characters Tests ====================

TEST_F(XMLPrinterTest_291, TextWithSpecialCharacters_291) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("elem", true);
    printer.PushText("a < b & c > d");
    printer.CloseElement(true);
    std::string result(printer.CStr());
    // Special chars should be escaped
    EXPECT_NE(result.find("&lt;"), std::string::npos);
    EXPECT_NE(result.find("&amp;"), std::string::npos);
    EXPECT_NE(result.find("&gt;"), std::string::npos);
}

TEST_F(XMLPrinterTest_291, AttributeWithSpecialCharacters_291) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("elem", true);
    printer.PushAttribute("val", "a < b & c > d \"e\"");
    printer.CloseElement(true);
    std::string result(printer.CStr());
    EXPECT_NE(result.find("&lt;"), std::string::npos);
    EXPECT_NE(result.find("&amp;"), std::string::npos);
    EXPECT_NE(result.find("&quot;"), std::string::npos);
}

// ==================== Depth Tests ====================

TEST_F(XMLPrinterTest_291, CustomInitialDepth_291) {
    XMLPrinter printer(nullptr, false, 2);
    printer.OpenElement("elem");
    printer.CloseElement();
    std::string result(printer.CStr());
    // With depth 2, there should be leading whitespace/indentation
    ASSERT_NE(result, nullptr);
    // At minimum the element should be present
    EXPECT_NE(result.find("<elem/>"), std::string::npos);
}

// ==================== Negative Int Tests ====================

TEST_F(XMLPrinterTest_291, PushTextNegativeInt_291) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("elem", true);
    printer.PushText(-42);
    printer.CloseElement(true);
    std::string result(printer.CStr());
    EXPECT_NE(result.find("-42"), std::string::npos);
}

TEST_F(XMLPrinterTest_291, PushAttributeNegativeInt_291) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("elem", true);
    printer.PushAttribute("val", -100);
    printer.CloseElement(true);
    std::string result(printer.CStr());
    EXPECT_NE(result.find("val=\"-100\""), std::string::npos);
}

TEST_F(XMLPrinterTest_291, PushTextNegativeInt64_291) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("elem", true);
    printer.PushText((int64_t)-999999999999LL);
    printer.CloseElement(true);
    std::string result(printer.CStr());
    EXPECT_NE(result.find("-999999999999"), std::string::npos);
}

// ==================== Zero value tests ====================

TEST_F(XMLPrinterTest_291, PushTextZero_291) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("elem", true);
    printer.PushText(0);
    printer.CloseElement(true);
    std::string result(printer.CStr());
    EXPECT_NE(result.find(">0<"), std::string::npos);
}

// ==================== Mixed content ====================

TEST_F(XMLPrinterTest_291, MixedContent_TextAndChildren_291) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("parent", true);
    printer.PushText("before");
    printer.OpenElement("child", true);
    printer.CloseElement(true);
    printer.PushText("after");
    printer.CloseElement(true);
    std::string result(printer.CStr());
    EXPECT_NE(result.find("before"), std::string::npos);
    EXPECT_NE(result.find("after"), std::string::npos);
    EXPECT_NE(result.find("<child/>"), std::string::npos);
}

// ==================== Sibling elements ====================

TEST_F(XMLPrinterTest_291, SiblingElements_291) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("root", true);
    printer.OpenElement("a", true);
    printer.CloseElement(true);
    printer.OpenElement("b", true);
    printer.CloseElement(true);
    printer.OpenElement("c", true);
    printer.CloseElement(true);
    printer.CloseElement(true);
    std::string result(printer.CStr());
    EXPECT_NE(result.find("<a/>"), std::string::npos);
    EXPECT_NE(result.find("<b/>"), std::string::npos);
    EXPECT_NE(result.find("<c/>"), std::string::npos);
}

// ==================== CStr and CStrSize consistency ====================

TEST_F(XMLPrinterTest_291, CStrAndCStrSize_Consistency_291) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("test");
    printer.PushAttribute("key", "value");
    printer.PushText("content");
    printer.CloseElement();
    const char* str = printer.CStr();
    size_t size = printer.CStrSize();
    ASSERT_NE(str, nullptr);
    // CStrSize should include the null terminator
    EXPECT_EQ(size, strlen(str) + 1);
}

// ==================== Writing to file verifies no buffer output ====================

TEST_F(XMLPrinterTest_291, WriteToFile_CStrReturnsNull_291) {
    FILE* fp = tmpfile();
    ASSERT_NE(fp, nullptr);
    XMLPrinter printer(fp, false, 0);
    printer.OpenElement("root");
    printer.CloseElement();
    // When writing to file, CStr may return empty or minimal buffer
    // The important thing is it doesn't crash
    const char* str = printer.CStr();
    // str might be empty since output went to file
    fclose(fp);
}
