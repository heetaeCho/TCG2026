#include "gtest/gtest.h"
#include "tinyxml2.h"
#include <cstring>
#include <string>

using namespace tinyxml2;

class XMLPrinterTest_304 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor / Basic State ====================

TEST_F(XMLPrinterTest_304, DefaultConstructor_EmptyBuffer_304) {
    XMLPrinter printer;
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

TEST_F(XMLPrinterTest_304, CStrSizeInitiallySmall_304) {
    XMLPrinter printer;
    // Initial size should be at least 1 for null terminator
    EXPECT_GE(printer.CStrSize(), 1u);
}

// ==================== PushHeader ====================

TEST_F(XMLPrinterTest_304, PushHeader_WithDeclaration_304) {
    XMLPrinter printer;
    printer.PushHeader(false, true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml"), std::string::npos);
}

TEST_F(XMLPrinterTest_304, PushHeader_WithBOM_304) {
    XMLPrinter printer;
    printer.PushHeader(true, false);
    const char* result = printer.CStr();
    // BOM is 0xEF, 0xBB, 0xBF
    EXPECT_EQ((unsigned char)result[0], 0xEF);
    EXPECT_EQ((unsigned char)result[1], 0xBB);
    EXPECT_EQ((unsigned char)result[2], 0xBF);
}

TEST_F(XMLPrinterTest_304, PushHeader_WithBOMAndDeclaration_304) {
    XMLPrinter printer;
    printer.PushHeader(true, true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml"), std::string::npos);
    // BOM bytes at start
    EXPECT_EQ((unsigned char)result[0], 0xEF);
}

TEST_F(XMLPrinterTest_304, PushHeader_NoBOMNoDeclaration_304) {
    XMLPrinter printer;
    printer.PushHeader(false, false);
    EXPECT_STREQ(printer.CStr(), "");
}

// ==================== OpenElement / CloseElement ====================

TEST_F(XMLPrinterTest_304, OpenAndCloseElement_Simple_304) {
    XMLPrinter printer;
    printer.OpenElement("root");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root"), std::string::npos);
    EXPECT_NE(result.find("</root>"), std::string::npos);
}

TEST_F(XMLPrinterTest_304, OpenAndCloseElement_SelfClosing_304) {
    XMLPrinter printer;
    printer.OpenElement("empty");
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<empty/>"), std::string::npos);
}

TEST_F(XMLPrinterTest_304, NestedElements_304) {
    XMLPrinter printer;
    printer.OpenElement("parent");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<parent"), std::string::npos);
    EXPECT_NE(result.find("<child"), std::string::npos);
    EXPECT_NE(result.find("</child>"), std::string::npos);
    EXPECT_NE(result.find("</parent>"), std::string::npos);
}

TEST_F(XMLPrinterTest_304, CompactModeElement_304) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string result = printer.CStr();
    // In compact mode, no extra whitespace/newlines
    EXPECT_EQ(result.find('\n'), std::string::npos);
}

// ==================== PushAttribute ====================

TEST_F(XMLPrinterTest_304, PushAttribute_String_304) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("name", "value");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("name=\"value\""), std::string::npos);
}

TEST_F(XMLPrinterTest_304, PushAttribute_Int_304) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("count", 42);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("count=\"42\""), std::string::npos);
}

TEST_F(XMLPrinterTest_304, PushAttribute_UnsignedInt_304) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("val", (unsigned int)100);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val=\"100\""), std::string::npos);
}

TEST_F(XMLPrinterTest_304, PushAttribute_Int64_304) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("big", (int64_t)9999999999LL);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("big=\"9999999999\""), std::string::npos);
}

TEST_F(XMLPrinterTest_304, PushAttribute_Uint64_304) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("ubig", (uint64_t)18446744073709551615ULL);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("ubig=\"18446744073709551615\""), std::string::npos);
}

TEST_F(XMLPrinterTest_304, PushAttribute_BoolTrue_304) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("flag", true);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("flag=\"true\""), std::string::npos);
}

TEST_F(XMLPrinterTest_304, PushAttribute_BoolFalse_304) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("flag", false);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("flag=\"false\""), std::string::npos);
}

TEST_F(XMLPrinterTest_304, PushAttribute_Double_304) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("pi", 3.14);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("pi=\""), std::string::npos);
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

TEST_F(XMLPrinterTest_304, MultipleAttributes_304) {
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

// ==================== PushText ====================

TEST_F(XMLPrinterTest_304, PushText_String_304) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText("Hello World");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("Hello World"), std::string::npos);
}

TEST_F(XMLPrinterTest_304, PushText_CDATA_304) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText("some data", true);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<![CDATA[some data]]>"), std::string::npos);
}

TEST_F(XMLPrinterTest_304, PushText_Int_304) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText(123);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("123"), std::string::npos);
}

TEST_F(XMLPrinterTest_304, PushText_UnsignedInt_304) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText((unsigned int)456);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("456"), std::string::npos);
}

TEST_F(XMLPrinterTest_304, PushText_Int64_304) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText((int64_t)1234567890123LL);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("1234567890123"), std::string::npos);
}

TEST_F(XMLPrinterTest_304, PushText_Uint64_304) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText((uint64_t)9876543210ULL);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("9876543210"), std::string::npos);
}

TEST_F(XMLPrinterTest_304, PushText_BoolTrue_304) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText(true);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("true"), std::string::npos);
}

TEST_F(XMLPrinterTest_304, PushText_BoolFalse_304) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText(false);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("false"), std::string::npos);
}

TEST_F(XMLPrinterTest_304, PushText_Float_304) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText(1.5f);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("1.5"), std::string::npos);
}

TEST_F(XMLPrinterTest_304, PushText_Double_304) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText(2.718);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("2.718"), std::string::npos);
}

// ==================== PushComment ====================

TEST_F(XMLPrinterTest_304, PushComment_304) {
    XMLPrinter printer;
    printer.PushComment("This is a comment");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!--This is a comment-->"), std::string::npos);
}

TEST_F(XMLPrinterTest_304, PushComment_InsideElement_304) {
    XMLPrinter printer;
    printer.OpenElement("root");
    printer.PushComment("inner comment");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!--inner comment-->"), std::string::npos);
}

// ==================== PushDeclaration ====================

TEST_F(XMLPrinterTest_304, PushDeclaration_304) {
    XMLPrinter printer;
    printer.PushDeclaration("xml version=\"1.0\"");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml version=\"1.0\"?>"), std::string::npos);
}

// ==================== PushUnknown ====================

TEST_F(XMLPrinterTest_304, PushUnknown_304) {
    XMLPrinter printer;
    printer.PushUnknown("DOCTYPE html");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!DOCTYPE html>"), std::string::npos);
}

// ==================== ClearBuffer ====================

TEST_F(XMLPrinterTest_304, ClearBuffer_ResetsOutput_304) {
    XMLPrinter printer;
    printer.OpenElement("root");
    printer.CloseElement();
    EXPECT_GT(printer.CStrSize(), 1u);
    
    printer.ClearBuffer();
    // After clearing, buffer should be empty (or minimal)
    std::string result = printer.CStr();
    EXPECT_STREQ(result.c_str(), "");
}

TEST_F(XMLPrinterTest_304, ClearBuffer_AllowsReuse_304) {
    XMLPrinter printer;
    printer.OpenElement("first");
    printer.CloseElement();
    
    printer.ClearBuffer();
    
    printer.OpenElement("second");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("second"), std::string::npos);
    EXPECT_EQ(result.find("first"), std::string::npos);
}

// ==================== CStr / CStrSize ====================

TEST_F(XMLPrinterTest_304, CStrSize_MatchesStringLength_304) {
    XMLPrinter printer;
    printer.OpenElement("test");
    printer.CloseElement();
    const char* str = printer.CStr();
    // CStrSize should include the null terminator
    EXPECT_EQ(printer.CStrSize(), strlen(str) + 1);
}

// ==================== SealElementIfJustOpened (observable through output) ====================

TEST_F(XMLPrinterTest_304, SealElementIfJustOpened_AfterOpenElement_304) {
    // After opening an element, if we push text, the element tag should be sealed with '>'
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText("content");
    printer.CloseElement();
    std::string result = printer.CStr();
    // Should have <elem>content</elem>
    EXPECT_NE(result.find("<elem>"), std::string::npos);
    EXPECT_NE(result.find("content"), std::string::npos);
    EXPECT_NE(result.find("</elem>"), std::string::npos);
}

// ==================== Visitor Interface with XMLDocument ====================

TEST_F(XMLPrinterTest_304, VisitDocument_304) {
    XMLDocument doc;
    doc.Parse("<root><child>text</child></root>");
    ASSERT_FALSE(doc.Error());
    
    XMLPrinter printer;
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root>"), std::string::npos);
    EXPECT_NE(result.find("<child>"), std::string::npos);
    EXPECT_NE(result.find("text"), std::string::npos);
}

TEST_F(XMLPrinterTest_304, VisitDocument_WithAttributes_304) {
    XMLDocument doc;
    doc.Parse("<root attr=\"val\"/>");
    ASSERT_FALSE(doc.Error());
    
    XMLPrinter printer;
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("attr=\"val\""), std::string::npos);
}

TEST_F(XMLPrinterTest_304, VisitDocument_WithComment_304) {
    XMLDocument doc;
    doc.Parse("<!--comment--><root/>");
    ASSERT_FALSE(doc.Error());
    
    XMLPrinter printer;
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!--comment-->"), std::string::npos);
}

TEST_F(XMLPrinterTest_304, VisitDocument_WithDeclaration_304) {
    XMLDocument doc;
    doc.Parse("<?xml version=\"1.0\"?><root/>");
    ASSERT_FALSE(doc.Error());
    
    XMLPrinter printer;
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml"), std::string::npos);
}

TEST_F(XMLPrinterTest_304, VisitDocument_WithUnknown_304) {
    XMLDocument doc;
    doc.Parse("<!DOCTYPE html><root/>");
    ASSERT_FALSE(doc.Error());
    
    XMLPrinter printer;
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!DOCTYPE html>"), std::string::npos);
}

// ==================== Complex Scenarios ====================

TEST_F(XMLPrinterTest_304, ComplexDocument_304) {
    XMLPrinter printer;
    printer.PushHeader(false, true);
    printer.OpenElement("root");
    printer.PushAttribute("version", "1.0");
    printer.OpenElement("item");
    printer.PushAttribute("id", 1);
    printer.PushText("First item");
    printer.CloseElement();
    printer.OpenElement("item");
    printer.PushAttribute("id", 2);
    printer.PushText("Second item");
    printer.CloseElement();
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml"), std::string::npos);
    EXPECT_NE(result.find("<root"), std::string::npos);
    EXPECT_NE(result.find("version=\"1.0\""), std::string::npos);
    EXPECT_NE(result.find("id=\"1\""), std::string::npos);
    EXPECT_NE(result.find("First item"), std::string::npos);
    EXPECT_NE(result.find("id=\"2\""), std::string::npos);
    EXPECT_NE(result.find("Second item"), std::string::npos);
    EXPECT_NE(result.find("</root>"), std::string::npos);
}

TEST_F(XMLPrinterTest_304, EmptyElement_NoAttributes_304) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("empty");
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<empty/>"), std::string::npos);
}

TEST_F(XMLPrinterTest_304, DeeplyNestedElements_304) {
    XMLPrinter printer;
    printer.OpenElement("a");
    printer.OpenElement("b");
    printer.OpenElement("c");
    printer.OpenElement("d");
    printer.PushText("deep");
    printer.CloseElement();
    printer.CloseElement();
    printer.CloseElement();
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("deep"), std::string::npos);
    EXPECT_NE(result.find("</a>"), std::string::npos);
    EXPECT_NE(result.find("</d>"), std::string::npos);
}

TEST_F(XMLPrinterTest_304, SpecialCharactersInText_304) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText("a < b & c > d");
    printer.CloseElement();
    std::string result = printer.CStr();
    // Entities should be escaped
    EXPECT_NE(result.find("&lt;"), std::string::npos);
    EXPECT_NE(result.find("&amp;"), std::string::npos);
    EXPECT_NE(result.find("&gt;"), std::string::npos);
}

TEST_F(XMLPrinterTest_304, SpecialCharactersInAttribute_304) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("data", "a\"b");
    printer.CloseElement();
    std::string result = printer.CStr();
    // Quote should be escaped in attribute
    EXPECT_NE(result.find("&quot;"), std::string::npos);
}

TEST_F(XMLPrinterTest_304, PushAttribute_NegativeInt_304) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("neg", -42);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("neg=\"-42\""), std::string::npos);
}

TEST_F(XMLPrinterTest_304, PushText_NegativeInt_304) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText(-999);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("-999"), std::string::npos);
}

TEST_F(XMLPrinterTest_304, EmptyTextContent_304) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText("");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<elem>"), std::string::npos);
    EXPECT_NE(result.find("</elem>"), std::string::npos);
}

TEST_F(XMLPrinterTest_304, PushText_ZeroInt_304) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText(0);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("0"), std::string::npos);
}

TEST_F(XMLPrinterTest_304, MultipleTextPushes_304) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText("hello ");
    printer.PushText("world");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("hello "), std::string::npos);
    EXPECT_NE(result.find("world"), std::string::npos);
}

TEST_F(XMLPrinterTest_304, RoundTrip_ParseAndPrint_304) {
    const char* xml = "<root><a x=\"1\">text</a><b/></root>";
    XMLDocument doc;
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());
    
    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    
    // Parse the printed output again
    XMLDocument doc2;
    doc2.Parse(printer.CStr());
    ASSERT_FALSE(doc2.Error());
    
    XMLPrinter printer2(nullptr, true);
    doc2.Accept(&printer2);
    
    EXPECT_STREQ(printer.CStr(), printer2.CStr());
}

TEST_F(XMLPrinterTest_304, SiblingElements_304) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.OpenElement("a");
    printer.CloseElement();
    printer.OpenElement("b");
    printer.CloseElement();
    printer.OpenElement("c");
    printer.CloseElement();
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<a"), std::string::npos);
    EXPECT_NE(result.find("<b"), std::string::npos);
    EXPECT_NE(result.find("<c"), std::string::npos);
}

TEST_F(XMLPrinterTest_304, NonCompactModeHasNewlines_304) {
    XMLPrinter printer(nullptr, false);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find('\n'), std::string::npos);
}

TEST_F(XMLPrinterTest_304, CompactModeNoNewlines_304) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_EQ(result.find('\n'), std::string::npos);
}

TEST_F(XMLPrinterTest_304, EmptyComment_304) {
    XMLPrinter printer;
    printer.PushComment("");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!---->"), std::string::npos);
}

TEST_F(XMLPrinterTest_304, PushText_LargeInt64_304) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText((int64_t)(-9223372036854775807LL - 1));
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("-9223372036854775808"), std::string::npos);
}

TEST_F(XMLPrinterTest_304, WriteToFileAndBuffer_304) {
    // When file is nullptr, output goes to buffer
    XMLPrinter printer(nullptr);
    printer.OpenElement("test");
    printer.CloseElement();
    EXPECT_GT(printer.CStrSize(), 1u);
    EXPECT_NE(printer.CStr(), nullptr);
}

TEST_F(XMLPrinterTest_304, PushAttribute_EmptyString_304) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("empty", "");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("empty=\"\""), std::string::npos);
}

TEST_F(XMLPrinterTest_304, ClearBuffer_ResetToFirstElement_304) {
    XMLPrinter printer;
    printer.OpenElement("first");
    printer.CloseElement();
    
    printer.ClearBuffer(true);
    
    printer.OpenElement("second");
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_EQ(result.find("first"), std::string::npos);
    EXPECT_NE(result.find("second"), std::string::npos);
}

TEST_F(XMLPrinterTest_304, ClearBuffer_NoReset_304) {
    XMLPrinter printer;
    printer.OpenElement("first");
    printer.CloseElement();
    
    printer.ClearBuffer(false);
    
    // Buffer is cleared but firstElement flag is not reset
    const char* result = printer.CStr();
    EXPECT_STREQ(result, "");
}
