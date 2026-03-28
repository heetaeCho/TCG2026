#include <gtest/gtest.h>
#include "tinyxml2.h"
#include <cstring>
#include <string>

using namespace tinyxml2;

class XMLPrinterTest_296 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(XMLPrinterTest_296, DefaultConstructor_NullFile_296) {
    XMLPrinter printer(nullptr, false, 0);
    // Should be able to use CStr() when no file is provided (prints to internal buffer)
    EXPECT_NE(nullptr, printer.CStr());
}

TEST_F(XMLPrinterTest_296, DefaultConstructor_CompactMode_296) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("root", true);
    printer.CloseElement(true);
    const char* result = printer.CStr();
    EXPECT_NE(nullptr, result);
    // In compact mode, there should be no extra whitespace/newlines
    std::string s(result);
    EXPECT_EQ(std::string::npos, s.find('\n'));
}

// ==================== PushHeader Tests ====================

TEST_F(XMLPrinterTest_296, PushHeader_WithBOMAndDeclaration_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushHeader(true, true);
    std::string result = printer.CStr();
    // BOM is 3 bytes: 0xEF, 0xBB, 0xBF
    EXPECT_GE(result.size(), 3u);
    // Should contain XML declaration
    EXPECT_NE(std::string::npos, result.find("<?xml"));
}

TEST_F(XMLPrinterTest_296, PushHeader_WithoutBOMWithDeclaration_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushHeader(false, true);
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("<?xml"));
}

TEST_F(XMLPrinterTest_296, PushHeader_WithoutBOMWithoutDeclaration_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushHeader(false, false);
    std::string result = printer.CStr();
    // No BOM and no declaration, should be empty or minimal
    EXPECT_EQ(std::string::npos, result.find("<?xml"));
}

// ==================== OpenElement / CloseElement Tests ====================

TEST_F(XMLPrinterTest_296, OpenAndCloseElement_Simple_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("root");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("<root"));
    EXPECT_NE(std::string::npos, result.find("</root>"));
}

TEST_F(XMLPrinterTest_296, OpenAndCloseElement_SelfClosing_296) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("empty", true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("<empty/>"));
}

TEST_F(XMLPrinterTest_296, OpenAndCloseElement_Nested_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("<root"));
    EXPECT_NE(std::string::npos, result.find("<child"));
    EXPECT_NE(std::string::npos, result.find("</child>"));
    EXPECT_NE(std::string::npos, result.find("</root>"));
}

TEST_F(XMLPrinterTest_296, OpenAndCloseElement_CompactMode_296) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("root", true);
    printer.OpenElement("child", true);
    printer.CloseElement(true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("<root>"));
    EXPECT_NE(std::string::npos, result.find("<child/>"));
    EXPECT_NE(std::string::npos, result.find("</root>"));
}

// ==================== PushAttribute Tests ====================

TEST_F(XMLPrinterTest_296, PushAttribute_StringValue_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("name", "value");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("name=\"value\""));
}

TEST_F(XMLPrinterTest_296, PushAttribute_IntValue_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("count", 42);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("count=\"42\""));
}

TEST_F(XMLPrinterTest_296, PushAttribute_NegativeIntValue_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("val", -100);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("val=\"-100\""));
}

TEST_F(XMLPrinterTest_296, PushAttribute_UnsignedIntValue_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("val", (unsigned int)12345);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("val=\"12345\""));
}

TEST_F(XMLPrinterTest_296, PushAttribute_Int64Value_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("big", (int64_t)9876543210LL);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("big=\"9876543210\""));
}

TEST_F(XMLPrinterTest_296, PushAttribute_Uint64Value_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("ubig", (uint64_t)18446744073709551615ULL);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("ubig=\"18446744073709551615\""));
}

TEST_F(XMLPrinterTest_296, PushAttribute_BoolTrueValue_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("flag", true);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("flag=\"true\""));
}

TEST_F(XMLPrinterTest_296, PushAttribute_BoolFalseValue_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("flag", false);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("flag=\"false\""));
}

TEST_F(XMLPrinterTest_296, PushAttribute_DoubleValue_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("pi", 3.14159);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("pi=\""));
    EXPECT_NE(std::string::npos, result.find("3.14"));
}

TEST_F(XMLPrinterTest_296, PushAttribute_MultipleAttributes_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("a", "1");
    printer.PushAttribute("b", "2");
    printer.PushAttribute("c", "3");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("a=\"1\""));
    EXPECT_NE(std::string::npos, result.find("b=\"2\""));
    EXPECT_NE(std::string::npos, result.find("c=\"3\""));
}

TEST_F(XMLPrinterTest_296, PushAttribute_SpecialCharactersInValue_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("data", "a<b>c&d\"e");
    printer.CloseElement();
    std::string result = printer.CStr();
    // Special characters should be escaped
    EXPECT_NE(std::string::npos, result.find("&lt;"));
    EXPECT_NE(std::string::npos, result.find("&gt;"));
    EXPECT_NE(std::string::npos, result.find("&amp;"));
}

TEST_F(XMLPrinterTest_296, PushAttribute_EmptyStringValue_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("empty", "");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("empty=\"\""));
}

// ==================== PushText Tests ====================

TEST_F(XMLPrinterTest_296, PushText_String_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText("Hello World");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("Hello World"));
}

TEST_F(XMLPrinterTest_296, PushText_CDATA_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText("Some <data>", true);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("<![CDATA["));
    EXPECT_NE(std::string::npos, result.find("]]>"));
}

TEST_F(XMLPrinterTest_296, PushText_IntValue_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText(42);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("42"));
}

TEST_F(XMLPrinterTest_296, PushText_UnsignedValue_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText((unsigned int)99);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("99"));
}

TEST_F(XMLPrinterTest_296, PushText_Int64Value_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText((int64_t)123456789012345LL);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("123456789012345"));
}

TEST_F(XMLPrinterTest_296, PushText_Uint64Value_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText((uint64_t)987654321ULL);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("987654321"));
}

TEST_F(XMLPrinterTest_296, PushText_BoolTrue_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText(true);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("true"));
}

TEST_F(XMLPrinterTest_296, PushText_BoolFalse_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText(false);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("false"));
}

TEST_F(XMLPrinterTest_296, PushText_FloatValue_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText(2.5f);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("2.5"));
}

TEST_F(XMLPrinterTest_296, PushText_DoubleValue_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText(1.23456789);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("1.23"));
}

TEST_F(XMLPrinterTest_296, PushText_SpecialCharacters_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText("<>&");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("&lt;"));
    EXPECT_NE(std::string::npos, result.find("&gt;"));
    EXPECT_NE(std::string::npos, result.find("&amp;"));
}

// ==================== PushComment Tests ====================

TEST_F(XMLPrinterTest_296, PushComment_Simple_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushComment("This is a comment");
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("<!--This is a comment-->"));
}

TEST_F(XMLPrinterTest_296, PushComment_InsideElement_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("root");
    printer.PushComment("inner comment");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("<!--inner comment-->"));
}

// ==================== PushDeclaration Tests ====================

TEST_F(XMLPrinterTest_296, PushDeclaration_Simple_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushDeclaration("xml version=\"1.0\"");
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("<?xml version=\"1.0\"?>"));
}

// ==================== PushUnknown Tests ====================

TEST_F(XMLPrinterTest_296, PushUnknown_Simple_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushUnknown("!DOCTYPE html");
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("<!DOCTYPE html>"));
}

// ==================== CStr / CStrSize Tests ====================

TEST_F(XMLPrinterTest_296, CStr_EmptyPrinter_296) {
    XMLPrinter printer(nullptr, false, 0);
    const char* str = printer.CStr();
    EXPECT_NE(nullptr, str);
}

TEST_F(XMLPrinterTest_296, CStrSize_EmptyPrinter_296) {
    XMLPrinter printer(nullptr, false, 0);
    size_t size = printer.CStrSize();
    // Should have at least the null terminator counted or be minimal
    EXPECT_GE(size, 0u);
}

TEST_F(XMLPrinterTest_296, CStrSize_AfterContent_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("test");
    printer.CloseElement();
    size_t size = printer.CStrSize();
    EXPECT_GT(size, 0u);
    // CStrSize should be consistent with strlen(CStr()) + 1 (null terminator)
    EXPECT_EQ(size, strlen(printer.CStr()) + 1);
}

// ==================== ClearBuffer Tests ====================

TEST_F(XMLPrinterTest_296, ClearBuffer_ResetsContent_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("test");
    printer.CloseElement();
    EXPECT_GT(strlen(printer.CStr()), 0u);
    
    printer.ClearBuffer();
    // After clearing, the buffer should be empty or minimal
    size_t sizeAfterClear = printer.CStrSize();
    // The CStr should be empty or very small
    EXPECT_LE(sizeAfterClear, 1u);
}

TEST_F(XMLPrinterTest_296, ClearBuffer_CanReuseAfterClear_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("first");
    printer.CloseElement();
    
    printer.ClearBuffer();
    
    printer.OpenElement("second");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_EQ(std::string::npos, result.find("first"));
    EXPECT_NE(std::string::npos, result.find("second"));
}

// ==================== Complex XML Structure Tests ====================

TEST_F(XMLPrinterTest_296, ComplexStructure_DeeplyNested_296) {
    XMLPrinter printer(nullptr, false, 0);
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
    EXPECT_NE(std::string::npos, result.find("<a"));
    EXPECT_NE(std::string::npos, result.find("<b"));
    EXPECT_NE(std::string::npos, result.find("<c"));
    EXPECT_NE(std::string::npos, result.find("<d"));
    EXPECT_NE(std::string::npos, result.find("deep"));
    EXPECT_NE(std::string::npos, result.find("</d>"));
    EXPECT_NE(std::string::npos, result.find("</c>"));
    EXPECT_NE(std::string::npos, result.find("</b>"));
    EXPECT_NE(std::string::npos, result.find("</a>"));
}

TEST_F(XMLPrinterTest_296, ComplexStructure_SiblingsWithAttributes_296) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("root", true);
    printer.OpenElement("child1", true);
    printer.PushAttribute("id", 1);
    printer.PushText("text1");
    printer.CloseElement(true);
    printer.OpenElement("child2", true);
    printer.PushAttribute("id", 2);
    printer.PushText("text2");
    printer.CloseElement(true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("child1"));
    EXPECT_NE(std::string::npos, result.find("child2"));
    EXPECT_NE(std::string::npos, result.find("id=\"1\""));
    EXPECT_NE(std::string::npos, result.find("id=\"2\""));
    EXPECT_NE(std::string::npos, result.find("text1"));
    EXPECT_NE(std::string::npos, result.find("text2"));
}

// ==================== Visit with XMLDocument Tests ====================

TEST_F(XMLPrinterTest_296, VisitEnter_XMLDocument_296) {
    XMLDocument doc;
    doc.Parse("<root><child attr=\"val\">text</child></root>");
    ASSERT_EQ(XML_SUCCESS, doc.ErrorID());
    
    XMLPrinter printer(nullptr, false, 0);
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("<root>"));
    EXPECT_NE(std::string::npos, result.find("<child"));
    EXPECT_NE(std::string::npos, result.find("attr=\"val\""));
    EXPECT_NE(std::string::npos, result.find("text"));
    EXPECT_NE(std::string::npos, result.find("</child>"));
    EXPECT_NE(std::string::npos, result.find("</root>"));
}

TEST_F(XMLPrinterTest_296, VisitEnter_XMLDocumentWithComment_296) {
    XMLDocument doc;
    doc.Parse("<!-- comment --><root/>");
    ASSERT_EQ(XML_SUCCESS, doc.ErrorID());
    
    XMLPrinter printer(nullptr, false, 0);
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("<!-- comment -->"));
    EXPECT_NE(std::string::npos, result.find("<root/>"));
}

TEST_F(XMLPrinterTest_296, VisitEnter_XMLDocumentWithDeclaration_296) {
    XMLDocument doc;
    doc.Parse("<?xml version=\"1.0\"?><root/>");
    ASSERT_EQ(XML_SUCCESS, doc.ErrorID());
    
    XMLPrinter printer(nullptr, false, 0);
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("<?xml"));
    EXPECT_NE(std::string::npos, result.find("<root/>"));
}

// ==================== Boundary / Edge Cases ====================

TEST_F(XMLPrinterTest_296, EmptyElementName_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(nullptr, printer.CStr());
}

TEST_F(XMLPrinterTest_296, PushText_EmptyString_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText("");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("<elem"));
    EXPECT_NE(std::string::npos, result.find("</elem>"));
}

TEST_F(XMLPrinterTest_296, PushAttribute_ZeroInt_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("val", 0);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("val=\"0\""));
}

TEST_F(XMLPrinterTest_296, PushAttribute_ZeroDouble_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("val", 0.0);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("val=\"0"));
}

TEST_F(XMLPrinterTest_296, PushText_ZeroInt_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText(0);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find(">0<"));
}

TEST_F(XMLPrinterTest_296, PushText_NegativeInt_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText(-999);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("-999"));
}

// ==================== Compact vs Non-Compact Mode ====================

TEST_F(XMLPrinterTest_296, NonCompactMode_HasIndentation_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string result = printer.CStr();
    // Non-compact mode should have newlines
    EXPECT_NE(std::string::npos, result.find('\n'));
}

TEST_F(XMLPrinterTest_296, CompactMode_NoIndentation_296) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("root", true);
    printer.OpenElement("child", true);
    printer.CloseElement(true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    // Compact mode should not have newlines
    EXPECT_EQ(std::string::npos, result.find('\n'));
}

// ==================== Multiple Elements at Same Level ====================

TEST_F(XMLPrinterTest_296, MultipleSiblingElements_296) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("root", true);
    
    printer.OpenElement("a", true);
    printer.CloseElement(true);
    
    printer.OpenElement("b", true);
    printer.CloseElement(true);
    
    printer.OpenElement("c", true);
    printer.CloseElement(true);
    
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("<a/>"));
    EXPECT_NE(std::string::npos, result.find("<b/>"));
    EXPECT_NE(std::string::npos, result.find("<c/>"));
}

// ==================== Full Document Roundtrip Test ====================

TEST_F(XMLPrinterTest_296, DocumentRoundtrip_296) {
    const char* xml = "<root><child name=\"test\">Hello</child></root>";
    XMLDocument doc;
    doc.Parse(xml);
    ASSERT_EQ(XML_SUCCESS, doc.ErrorID());
    
    XMLPrinter printer(nullptr, true, 0);
    doc.Accept(&printer);
    
    // Parse the printed result again
    XMLDocument doc2;
    doc2.Parse(printer.CStr());
    ASSERT_EQ(XML_SUCCESS, doc2.ErrorID());
    
    XMLElement* root = doc2.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(nullptr, child);
    EXPECT_STREQ("test", child->Attribute("name"));
    EXPECT_STREQ("Hello", child->GetText());
}

// ==================== PushHeader BOM Only ====================

TEST_F(XMLPrinterTest_296, PushHeader_BOMOnlyNoDeclaration_296) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushHeader(true, false);
    std::string result = printer.CStr();
    // Should have BOM but no xml declaration
    EXPECT_GE(result.size(), 3u);
    EXPECT_EQ(std::string::npos, result.find("<?xml"));
    // Check BOM bytes
    EXPECT_EQ((unsigned char)result[0], 0xEF);
    EXPECT_EQ((unsigned char)result[1], 0xBB);
    EXPECT_EQ((unsigned char)result[2], 0xBF);
}

// ==================== Depth parameter test ====================

TEST_F(XMLPrinterTest_296, ConstructorWithDepth_296) {
    XMLPrinter printer(nullptr, false, 2);
    printer.OpenElement("elem");
    printer.CloseElement();
    std::string result = printer.CStr();
    // With depth=2, the first element should be indented
    EXPECT_NE(nullptr, printer.CStr());
    EXPECT_GT(strlen(printer.CStr()), 0u);
}

// ==================== Mixed content test ====================

TEST_F(XMLPrinterTest_296, MixedContent_TextAndElements_296) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("root", true);
    printer.PushText("before ");
    printer.OpenElement("b", true);
    printer.PushText("bold");
    printer.CloseElement(true);
    printer.PushText(" after");
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("before "));
    EXPECT_NE(std::string::npos, result.find("<b>bold</b>"));
    EXPECT_NE(std::string::npos, result.find(" after"));
}

// ==================== Visit with XMLUnknown ====================

TEST_F(XMLPrinterTest_296, VisitUnknown_296) {
    XMLDocument doc;
    doc.Parse("<!DOCTYPE html><root/>");
    ASSERT_EQ(XML_SUCCESS, doc.ErrorID());
    
    XMLPrinter printer(nullptr, false, 0);
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(std::string::npos, result.find("<!DOCTYPE html>"));
}
