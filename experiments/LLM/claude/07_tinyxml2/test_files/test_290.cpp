#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include <cstdio>
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for XMLPrinter tests
class XMLPrinterTest_290 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Construction Tests ====================

TEST_F(XMLPrinterTest_290, DefaultConstructionToBuffer_290) {
    XMLPrinter printer;
    // CStr should return a valid empty-ish string
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(strlen(result), 0u);
}

TEST_F(XMLPrinterTest_290, CStrSizeInitiallyOne_290) {
    // CStrSize includes the null terminator
    XMLPrinter printer;
    EXPECT_GE(printer.CStrSize(), 1u);
}

TEST_F(XMLPrinterTest_290, ConstructionWithFilePointer_290) {
    FILE* fp = tmpfile();
    ASSERT_NE(fp, nullptr);
    XMLPrinter printer(fp);
    printer.OpenElement("test");
    printer.CloseElement();
    fflush(fp);
    
    // Read back from file
    fseek(fp, 0, SEEK_SET);
    char buf[256] = {};
    size_t n = fread(buf, 1, sizeof(buf) - 1, fp);
    buf[n] = '\0';
    fclose(fp);
    
    EXPECT_NE(std::string(buf).find("test"), std::string::npos);
}

// ==================== OpenElement / CloseElement Tests ====================

TEST_F(XMLPrinterTest_290, OpenAndCloseElement_290) {
    XMLPrinter printer;
    printer.OpenElement("root");
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root"), std::string::npos);
    EXPECT_NE(result.find("/>"), std::string::npos);
}

TEST_F(XMLPrinterTest_290, OpenAndCloseElementWithContent_290) {
    XMLPrinter printer;
    printer.OpenElement("root");
    printer.PushText("hello");
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root>"), std::string::npos);
    EXPECT_NE(result.find("hello"), std::string::npos);
    EXPECT_NE(result.find("</root>"), std::string::npos);
}

TEST_F(XMLPrinterTest_290, NestedElements_290) {
    XMLPrinter printer;
    printer.OpenElement("parent");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<parent>"), std::string::npos);
    EXPECT_NE(result.find("<child/>"), std::string::npos);
    EXPECT_NE(result.find("</parent>"), std::string::npos);
}

TEST_F(XMLPrinterTest_290, CompactModeElement_290) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    
    std::string result = printer.CStr();
    // In compact mode, no extra whitespace/newlines
    EXPECT_NE(result.find("<root><child/></root>"), std::string::npos);
}

// ==================== PushAttribute Tests ====================

TEST_F(XMLPrinterTest_290, PushAttributeString_290) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("name", "value");
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("name=\"value\""), std::string::npos);
}

TEST_F(XMLPrinterTest_290, PushAttributeInt_290) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("count", 42);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("count=\"42\""), std::string::npos);
}

TEST_F(XMLPrinterTest_290, PushAttributeUnsigned_290) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("val", (unsigned int)100);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val=\"100\""), std::string::npos);
}

TEST_F(XMLPrinterTest_290, PushAttributeInt64_290) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("big", (int64_t)1234567890123LL);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("big=\"1234567890123\""), std::string::npos);
}

TEST_F(XMLPrinterTest_290, PushAttributeUint64_290) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("ubig", (uint64_t)9876543210ULL);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("ubig=\"9876543210\""), std::string::npos);
}

TEST_F(XMLPrinterTest_290, PushAttributeBoolTrue_290) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("flag", true);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("flag=\"true\""), std::string::npos);
}

TEST_F(XMLPrinterTest_290, PushAttributeBoolFalse_290) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("flag", false);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("flag=\"false\""), std::string::npos);
}

TEST_F(XMLPrinterTest_290, PushAttributeDouble_290) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("pi", 3.14);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("pi=\""), std::string::npos);
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

TEST_F(XMLPrinterTest_290, MultipleAttributes_290) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("a", "1");
    printer.PushAttribute("b", "2");
    printer.PushAttribute("c", "3");
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("a=\"1\""), std::string::npos);
    EXPECT_NE(result.find("b=\"2\""), std::string::npos);
    EXPECT_NE(result.find("c=\"3\""), std::string::npos);
}

// ==================== PushText Tests ====================

TEST_F(XMLPrinterTest_290, PushTextString_290) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText("Hello World");
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("Hello World"), std::string::npos);
}

TEST_F(XMLPrinterTest_290, PushTextCDATA_290) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText("some data", true);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<![CDATA[some data]]>"), std::string::npos);
}

TEST_F(XMLPrinterTest_290, PushTextInt_290) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText(42);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("42"), std::string::npos);
}

TEST_F(XMLPrinterTest_290, PushTextUnsigned_290) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText((unsigned int)999);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("999"), std::string::npos);
}

TEST_F(XMLPrinterTest_290, PushTextInt64_290) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText((int64_t)1234567890123LL);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("1234567890123"), std::string::npos);
}

TEST_F(XMLPrinterTest_290, PushTextUint64_290) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText((uint64_t)9876543210ULL);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("9876543210"), std::string::npos);
}

TEST_F(XMLPrinterTest_290, PushTextBoolTrue_290) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText(true);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("true"), std::string::npos);
}

TEST_F(XMLPrinterTest_290, PushTextBoolFalse_290) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText(false);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("false"), std::string::npos);
}

TEST_F(XMLPrinterTest_290, PushTextFloat_290) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText(1.5f);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("1.5"), std::string::npos);
}

TEST_F(XMLPrinterTest_290, PushTextDouble_290) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText(2.718);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("2.718"), std::string::npos);
}

// ==================== PushComment Tests ====================

TEST_F(XMLPrinterTest_290, PushComment_290) {
    XMLPrinter printer;
    printer.PushComment("This is a comment");
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!--This is a comment-->"), std::string::npos);
}

TEST_F(XMLPrinterTest_290, PushCommentInsideElement_290) {
    XMLPrinter printer;
    printer.OpenElement("root");
    printer.PushComment("inner comment");
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!--inner comment-->"), std::string::npos);
}

// ==================== PushDeclaration Tests ====================

TEST_F(XMLPrinterTest_290, PushDeclaration_290) {
    XMLPrinter printer;
    printer.PushDeclaration("xml version=\"1.0\"");
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml version=\"1.0\"?>"), std::string::npos);
}

// ==================== PushUnknown Tests ====================

TEST_F(XMLPrinterTest_290, PushUnknown_290) {
    XMLPrinter printer;
    printer.PushUnknown("DOCTYPE html");
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!DOCTYPE html>"), std::string::npos);
}

// ==================== PushHeader Tests ====================

TEST_F(XMLPrinterTest_290, PushHeaderWithDeclaration_290) {
    XMLPrinter printer;
    printer.PushHeader(false, true);
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml"), std::string::npos);
}

TEST_F(XMLPrinterTest_290, PushHeaderWithBOM_290) {
    XMLPrinter printer;
    printer.PushHeader(true, false);
    
    std::string result = printer.CStr();
    // BOM is \xEF\xBB\xBF
    EXPECT_GE(printer.CStrSize(), 4u);
    EXPECT_EQ((unsigned char)result[0], 0xEF);
    EXPECT_EQ((unsigned char)result[1], 0xBB);
    EXPECT_EQ((unsigned char)result[2], 0xBF);
}

TEST_F(XMLPrinterTest_290, PushHeaderWithBOMAndDeclaration_290) {
    XMLPrinter printer;
    printer.PushHeader(true, true);
    
    std::string result = printer.CStr();
    EXPECT_EQ((unsigned char)result[0], 0xEF);
    EXPECT_NE(result.find("<?xml"), std::string::npos);
}

TEST_F(XMLPrinterTest_290, PushHeaderNoBOMNoDeclaration_290) {
    XMLPrinter printer;
    printer.PushHeader(false, false);
    
    // Should produce nothing
    EXPECT_EQ(strlen(printer.CStr()), 0u);
}

// ==================== ClearBuffer Tests ====================

TEST_F(XMLPrinterTest_290, ClearBuffer_290) {
    XMLPrinter printer;
    printer.OpenElement("root");
    printer.CloseElement();
    
    EXPECT_GT(strlen(printer.CStr()), 0u);
    
    printer.ClearBuffer();
    EXPECT_EQ(strlen(printer.CStr()), 0u);
}

TEST_F(XMLPrinterTest_290, ClearBufferThenReuse_290) {
    XMLPrinter printer;
    printer.OpenElement("first");
    printer.CloseElement();
    
    printer.ClearBuffer();
    
    printer.OpenElement("second");
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_EQ(result.find("first"), std::string::npos);
    EXPECT_NE(result.find("second"), std::string::npos);
}

// ==================== CStr / CStrSize Tests ====================

TEST_F(XMLPrinterTest_290, CStrSizeMatchesContent_290) {
    XMLPrinter printer;
    printer.OpenElement("test");
    printer.CloseElement();
    
    const char* str = printer.CStr();
    size_t expectedSize = strlen(str) + 1; // including null terminator
    EXPECT_EQ(printer.CStrSize(), expectedSize);
}

// ==================== Entity Handling Tests ====================

TEST_F(XMLPrinterTest_290, TextWithSpecialCharacters_290) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText("a < b & c > d");
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("&lt;"), std::string::npos);
    EXPECT_NE(result.find("&amp;"), std::string::npos);
    EXPECT_NE(result.find("&gt;"), std::string::npos);
}

TEST_F(XMLPrinterTest_290, AttributeWithSpecialCharacters_290) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("val", "a < b & c > d");
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("&lt;"), std::string::npos);
    EXPECT_NE(result.find("&amp;"), std::string::npos);
}

// ==================== Visitor Interface Tests ====================

TEST_F(XMLPrinterTest_290, VisitEnterDocument_290) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    ASSERT_FALSE(doc.Error());
    
    XMLPrinter printer;
    doc.Accept(&printer);
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root>"), std::string::npos);
    EXPECT_NE(result.find("<child/>"), std::string::npos);
    EXPECT_NE(result.find("</root>"), std::string::npos);
}

TEST_F(XMLPrinterTest_290, VisitDocumentWithAttributes_290) {
    XMLDocument doc;
    doc.Parse("<root attr=\"val\">text</root>");
    ASSERT_FALSE(doc.Error());
    
    XMLPrinter printer;
    doc.Accept(&printer);
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("attr=\"val\""), std::string::npos);
    EXPECT_NE(result.find("text"), std::string::npos);
}

TEST_F(XMLPrinterTest_290, VisitDocumentWithComment_290) {
    XMLDocument doc;
    doc.Parse("<!-- comment --><root/>");
    ASSERT_FALSE(doc.Error());
    
    XMLPrinter printer;
    doc.Accept(&printer);
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!--"), std::string::npos);
    EXPECT_NE(result.find("comment"), std::string::npos);
}

TEST_F(XMLPrinterTest_290, VisitDocumentWithDeclaration_290) {
    XMLDocument doc;
    doc.Parse("<?xml version=\"1.0\"?><root/>");
    ASSERT_FALSE(doc.Error());
    
    XMLPrinter printer;
    doc.Accept(&printer);
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml"), std::string::npos);
}

// ==================== Complex Document Tests ====================

TEST_F(XMLPrinterTest_290, ComplexNestedDocument_290) {
    XMLPrinter printer;
    printer.OpenElement("root");
    printer.OpenElement("level1");
    printer.OpenElement("level2");
    printer.PushText("deep text");
    printer.CloseElement();
    printer.CloseElement();
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root>"), std::string::npos);
    EXPECT_NE(result.find("<level1>"), std::string::npos);
    EXPECT_NE(result.find("<level2>"), std::string::npos);
    EXPECT_NE(result.find("deep text"), std::string::npos);
    EXPECT_NE(result.find("</level2>"), std::string::npos);
    EXPECT_NE(result.find("</level1>"), std::string::npos);
    EXPECT_NE(result.find("</root>"), std::string::npos);
}

TEST_F(XMLPrinterTest_290, SiblingElements_290) {
    XMLPrinter printer(nullptr, true); // compact mode
    printer.OpenElement("root");
    printer.OpenElement("a");
    printer.CloseElement();
    printer.OpenElement("b");
    printer.CloseElement();
    printer.OpenElement("c");
    printer.CloseElement();
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root><a/><b/><c/></root>"), std::string::npos);
}

// ==================== Empty Element Tests ====================

TEST_F(XMLPrinterTest_290, EmptySelfClosingElement_290) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("empty");
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<empty/>"), std::string::npos);
}

// ==================== File Output Tests ====================

TEST_F(XMLPrinterTest_290, FileOutputMultipleElements_290) {
    FILE* fp = tmpfile();
    ASSERT_NE(fp, nullptr);
    
    XMLPrinter printer(fp, true);
    printer.OpenElement("root");
    printer.PushAttribute("id", 1);
    printer.PushText("content");
    printer.CloseElement();
    fflush(fp);
    
    fseek(fp, 0, SEEK_SET);
    char buf[512] = {};
    size_t n = fread(buf, 1, sizeof(buf) - 1, fp);
    buf[n] = '\0';
    fclose(fp);
    
    std::string result(buf);
    EXPECT_NE(result.find("<root"), std::string::npos);
    EXPECT_NE(result.find("id=\"1\""), std::string::npos);
    EXPECT_NE(result.find("content"), std::string::npos);
    EXPECT_NE(result.find("</root>"), std::string::npos);
}

// ==================== Negative Int Tests ====================

TEST_F(XMLPrinterTest_290, PushTextNegativeInt_290) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText(-42);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("-42"), std::string::npos);
}

TEST_F(XMLPrinterTest_290, PushAttributeNegativeInt_290) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("val", -100);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val=\"-100\""), std::string::npos);
}

// ==================== Roundtrip Tests ====================

TEST_F(XMLPrinterTest_290, RoundtripParsePrint_290) {
    const char* xml = "<root><child attr=\"val\">text</child></root>";
    XMLDocument doc;
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());
    
    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root>"), std::string::npos);
    EXPECT_NE(result.find("<child attr=\"val\">text</child>"), std::string::npos);
    EXPECT_NE(result.find("</root>"), std::string::npos);
}

// ==================== Depth / Non-Compact Mode Tests ====================

TEST_F(XMLPrinterTest_290, NonCompactModeHasNewlines_290) {
    XMLPrinter printer(nullptr, false);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find('\n'), std::string::npos);
}

TEST_F(XMLPrinterTest_290, CustomInitialDepth_290) {
    XMLPrinter printer(nullptr, false, 2);
    printer.OpenElement("elem");
    printer.CloseElement();
    
    std::string result = printer.CStr();
    // Should have indentation corresponding to depth 2
    // At minimum, should start with some spaces
    EXPECT_GT(result.size(), 0u);
}

// ==================== Attribute with Quotes Test ====================

TEST_F(XMLPrinterTest_290, AttributeWithQuotesEntity_290) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("val", "he said \"hello\"");
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("&quot;"), std::string::npos);
}

// ==================== Empty String Tests ====================

TEST_F(XMLPrinterTest_290, PushTextEmptyString_290) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText("");
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<elem>"), std::string::npos);
    EXPECT_NE(result.find("</elem>"), std::string::npos);
}

TEST_F(XMLPrinterTest_290, PushAttributeEmptyValue_290) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("key", "");
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("key=\"\""), std::string::npos);
}

// ==================== Zero Values ====================

TEST_F(XMLPrinterTest_290, PushTextZeroInt_290) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText(0);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find(">0<"), std::string::npos);
}

TEST_F(XMLPrinterTest_290, PushAttributeZero_290) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("val", 0);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val=\"0\""), std::string::npos);
}

// ==================== Large Content Test ====================

TEST_F(XMLPrinterTest_290, LargeTextContent_290) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    std::string longText(1000, 'A');
    printer.PushText(longText.c_str());
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find(longText), std::string::npos);
}

// ==================== Multiple Documents ====================

TEST_F(XMLPrinterTest_290, ClearBufferResetForNewDocument_290) {
    XMLPrinter printer;
    printer.OpenElement("first");
    printer.CloseElement();
    
    std::string first = printer.CStr();
    EXPECT_NE(first.find("first"), std::string::npos);
    
    printer.ClearBuffer();
    
    printer.OpenElement("second");
    printer.CloseElement();
    
    std::string second = printer.CStr();
    EXPECT_EQ(second.find("first"), std::string::npos);
    EXPECT_NE(second.find("second"), std::string::npos);
}

// ==================== PushUnknown edge cases ====================

TEST_F(XMLPrinterTest_290, PushUnknownEmptyString_290) {
    XMLPrinter printer;
    printer.PushUnknown("");
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!>"), std::string::npos);
}

// ==================== Mixed Content Tests ====================

TEST_F(XMLPrinterTest_290, MixedContentTextAndElements_290) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.PushText("before");
    printer.OpenElement("mid");
    printer.CloseElement();
    printer.PushText("after");
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("before"), std::string::npos);
    EXPECT_NE(result.find("<mid/>"), std::string::npos);
    EXPECT_NE(result.find("after"), std::string::npos);
}
