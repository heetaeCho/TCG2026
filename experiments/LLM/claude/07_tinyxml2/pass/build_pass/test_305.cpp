#include "gtest/gtest.h"
#include "tinyxml2.h"
#include <string>
#include <cstring>

using namespace tinyxml2;

// Test fixture for XMLPrinter tests
class XMLPrinterTest_305 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== PushText (const char*, bool) Tests ====================

TEST_F(XMLPrinterTest_305, PushTextCDataWrapsInCDATATags_305) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.PushText("Hello World", true);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<![CDATA[Hello World]]>"), std::string::npos);
}

TEST_F(XMLPrinterTest_305, PushTextNonCDataPrintsEscapedText_305) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.PushText("Hello World", false);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("Hello World"), std::string::npos);
    EXPECT_EQ(result.find("<![CDATA["), std::string::npos);
}

TEST_F(XMLPrinterTest_305, PushTextCDataEmptyString_305) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.PushText("", true);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<![CDATA[]]>"), std::string::npos);
}

TEST_F(XMLPrinterTest_305, PushTextNonCDataEmptyString_305) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.PushText("", false);
    printer.CloseElement();
    std::string result = printer.CStr();
    // Should still have a valid element
    EXPECT_NE(result.find("<root"), std::string::npos);
}

TEST_F(XMLPrinterTest_305, PushTextNonCDataEscapesSpecialChars_305) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.PushText("<>&\"", false);
    printer.CloseElement();
    std::string result = printer.CStr();
    // Special characters should be escaped in non-CDATA mode
    EXPECT_NE(result.find("&lt;"), std::string::npos);
    EXPECT_NE(result.find("&gt;"), std::string::npos);
    EXPECT_NE(result.find("&amp;"), std::string::npos);
}

TEST_F(XMLPrinterTest_305, PushTextCDataDoesNotEscapeSpecialChars_305) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.PushText("<>&\"", true);
    printer.CloseElement();
    std::string result = printer.CStr();
    // In CDATA mode, special characters should NOT be escaped
    EXPECT_NE(result.find("<![CDATA[<>&\"]]>"), std::string::npos);
}

// ==================== PushText with numeric types ====================

TEST_F(XMLPrinterTest_305, PushTextInt_305) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.PushText(42);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("42"), std::string::npos);
}

TEST_F(XMLPrinterTest_305, PushTextNegativeInt_305) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.PushText(-100);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("-100"), std::string::npos);
}

TEST_F(XMLPrinterTest_305, PushTextUnsignedInt_305) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.PushText(123u);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("123"), std::string::npos);
}

TEST_F(XMLPrinterTest_305, PushTextInt64_305) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.PushText(static_cast<int64_t>(9876543210LL));
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("9876543210"), std::string::npos);
}

TEST_F(XMLPrinterTest_305, PushTextUint64_305) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.PushText(static_cast<uint64_t>(18446744073709551615ULL));
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("18446744073709551615"), std::string::npos);
}

TEST_F(XMLPrinterTest_305, PushTextBoolTrue_305) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.PushText(true);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("true"), std::string::npos);
}

TEST_F(XMLPrinterTest_305, PushTextBoolFalse_305) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.PushText(false);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("false"), std::string::npos);
}

TEST_F(XMLPrinterTest_305, PushTextFloat_305) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.PushText(3.14f);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

TEST_F(XMLPrinterTest_305, PushTextDouble_305) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.PushText(2.71828);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("2.71828"), std::string::npos);
}

// ==================== OpenElement / CloseElement Tests ====================

TEST_F(XMLPrinterTest_305, OpenAndCloseElement_305) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<element/>"), std::string::npos);
}

TEST_F(XMLPrinterTest_305, NestedElements_305) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("parent");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<parent>"), std::string::npos);
    EXPECT_NE(result.find("<child/>"), std::string::npos);
    EXPECT_NE(result.find("</parent>"), std::string::npos);
}

TEST_F(XMLPrinterTest_305, NonCompactModeFormatsOutput_305) {
    XMLPrinter printer(nullptr, false);
    printer.OpenElement("parent");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string result = printer.CStr();
    // In non-compact mode, there should be newlines/indentation
    EXPECT_NE(result.find("\n"), std::string::npos);
}

TEST_F(XMLPrinterTest_305, CompactModeNoExtraWhitespace_305) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("parent");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string result = printer.CStr();
    // Compact mode should not have newlines between elements
    EXPECT_EQ(result.find("\n"), std::string::npos);
}

// ==================== PushAttribute Tests ====================

TEST_F(XMLPrinterTest_305, PushAttributeString_305) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("name", "value");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("name=\"value\""), std::string::npos);
}

TEST_F(XMLPrinterTest_305, PushAttributeInt_305) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("count", 42);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("count=\"42\""), std::string::npos);
}

TEST_F(XMLPrinterTest_305, PushAttributeUnsigned_305) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", 99u);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val=\"99\""), std::string::npos);
}

TEST_F(XMLPrinterTest_305, PushAttributeInt64_305) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("big", static_cast<int64_t>(1234567890123LL));
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("big=\"1234567890123\""), std::string::npos);
}

TEST_F(XMLPrinterTest_305, PushAttributeUint64_305) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("ubig", static_cast<uint64_t>(9999999999ULL));
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("ubig=\"9999999999\""), std::string::npos);
}

TEST_F(XMLPrinterTest_305, PushAttributeBool_305) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("flag", true);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("flag=\"true\""), std::string::npos);
}

TEST_F(XMLPrinterTest_305, PushAttributeDouble_305) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("pi", 3.14159);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("pi="), std::string::npos);
    EXPECT_NE(result.find("3.14159"), std::string::npos);
}

TEST_F(XMLPrinterTest_305, MultipleAttributes_305) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("a", "1");
    printer.PushAttribute("b", "2");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("a=\"1\""), std::string::npos);
    EXPECT_NE(result.find("b=\"2\""), std::string::npos);
}

// ==================== PushHeader Tests ====================

TEST_F(XMLPrinterTest_305, PushHeaderWithBOM_305) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(true, true);
    std::string result = printer.CStr();
    // BOM is \xEF\xBB\xBF
    EXPECT_NE(result.find("\xEF\xBB\xBF"), std::string::npos);
}

TEST_F(XMLPrinterTest_305, PushHeaderWithDeclaration_305) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(false, true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml"), std::string::npos);
}

TEST_F(XMLPrinterTest_305, PushHeaderNoBOMNoDeclaration_305) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(false, false);
    std::string result = printer.CStr();
    EXPECT_EQ(result.find("\xEF\xBB\xBF"), std::string::npos);
    EXPECT_EQ(result.find("<?xml"), std::string::npos);
}

// ==================== PushComment Tests ====================

TEST_F(XMLPrinterTest_305, PushComment_305) {
    XMLPrinter printer(nullptr, true);
    printer.PushComment("This is a comment");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!--This is a comment-->"), std::string::npos);
}

// ==================== PushDeclaration Tests ====================

TEST_F(XMLPrinterTest_305, PushDeclaration_305) {
    XMLPrinter printer(nullptr, true);
    printer.PushDeclaration("xml version=\"1.0\"");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml version=\"1.0\"?>"), std::string::npos);
}

// ==================== PushUnknown Tests ====================

TEST_F(XMLPrinterTest_305, PushUnknown_305) {
    XMLPrinter printer(nullptr, true);
    printer.PushUnknown("SOMETHING");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!SOMETHING>"), std::string::npos);
}

// ==================== CStr / CStrSize / ClearBuffer Tests ====================

TEST_F(XMLPrinterTest_305, CStrReturnsNullTerminatedString_305) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test");
    printer.CloseElement();
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    EXPECT_GT(strlen(result), 0u);
}

TEST_F(XMLPrinterTest_305, CStrSizeReturnsCorrectSize_305) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test");
    printer.CloseElement();
    size_t size = printer.CStrSize();
    const char* result = printer.CStr();
    // CStrSize should include the null terminator
    EXPECT_EQ(size, strlen(result) + 1);
}

TEST_F(XMLPrinterTest_305, ClearBufferResetsBuffer_305) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test");
    printer.CloseElement();
    EXPECT_GT(printer.CStrSize(), 1u);
    printer.ClearBuffer();
    // After clearing, buffer should be essentially empty
    EXPECT_LE(printer.CStrSize(), 1u);
}

// ==================== Complex Document Tests ====================

TEST_F(XMLPrinterTest_305, ComplexDocumentStructure_305) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(false, true);
    printer.OpenElement("root");
    printer.PushAttribute("version", "1.0");
    printer.OpenElement("child");
    printer.PushText("Some text", false);
    printer.CloseElement();
    printer.OpenElement("data");
    printer.PushAttribute("id", 5);
    printer.PushText("content", true);
    printer.CloseElement();
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml"), std::string::npos);
    EXPECT_NE(result.find("<root"), std::string::npos);
    EXPECT_NE(result.find("version=\"1.0\""), std::string::npos);
    EXPECT_NE(result.find("<child>"), std::string::npos);
    EXPECT_NE(result.find("Some text"), std::string::npos);
    EXPECT_NE(result.find("</child>"), std::string::npos);
    EXPECT_NE(result.find("<data"), std::string::npos);
    EXPECT_NE(result.find("id=\"5\""), std::string::npos);
    EXPECT_NE(result.find("<![CDATA[content]]>"), std::string::npos);
    EXPECT_NE(result.find("</root>"), std::string::npos);
}

// ==================== XMLDocument Accept / Visitor Tests ====================

TEST_F(XMLPrinterTest_305, VisitDocumentWithPrinter_305) {
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

TEST_F(XMLPrinterTest_305, VisitDocumentWithComments_305) {
    XMLDocument doc;
    doc.Parse("<!-- comment --><root/>");
    ASSERT_FALSE(doc.Error());
    
    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!--"), std::string::npos);
    EXPECT_NE(result.find("comment"), std::string::npos);
    EXPECT_NE(result.find("-->"), std::string::npos);
}

TEST_F(XMLPrinterTest_305, VisitDocumentWithCDATA_305) {
    XMLDocument doc;
    doc.Parse("<root><![CDATA[some cdata]]></root>");
    ASSERT_FALSE(doc.Error());
    
    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<![CDATA[some cdata]]>"), std::string::npos);
}

TEST_F(XMLPrinterTest_305, VisitDocumentWithDeclaration_305) {
    XMLDocument doc;
    doc.Parse("<?xml version=\"1.0\"?><root/>");
    ASSERT_FALSE(doc.Error());
    
    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml"), std::string::npos);
}

// ==================== Self-Closing Element Tests ====================

TEST_F(XMLPrinterTest_305, EmptyElementSelfCloses_305) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("empty");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<empty/>"), std::string::npos);
}

TEST_F(XMLPrinterTest_305, ElementWithContentDoesNotSelfClose_305) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("notempty");
    printer.PushText("content", false);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<notempty>"), std::string::npos);
    EXPECT_NE(result.find("</notempty>"), std::string::npos);
    EXPECT_EQ(result.find("<notempty/>"), std::string::npos);
}

// ==================== Boundary: Zero Values ====================

TEST_F(XMLPrinterTest_305, PushTextIntZero_305) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.PushText(0);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find(">0<"), std::string::npos);
}

TEST_F(XMLPrinterTest_305, PushTextDoubleZero_305) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.PushText(0.0);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("0"), std::string::npos);
}

// ==================== Element with attributes and text ====================

TEST_F(XMLPrinterTest_305, ElementWithAttributeAndText_305) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("item");
    printer.PushAttribute("id", 1);
    printer.PushText("Hello", false);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<item id=\"1\">"), std::string::npos);
    EXPECT_NE(result.find("Hello"), std::string::npos);
    EXPECT_NE(result.find("</item>"), std::string::npos);
}

// ==================== Multiple sibling elements ====================

TEST_F(XMLPrinterTest_305, MultipleSiblingElements_305) {
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
    EXPECT_NE(result.find("<a/>"), std::string::npos);
    EXPECT_NE(result.find("<b/>"), std::string::npos);
    EXPECT_NE(result.find("<c/>"), std::string::npos);
}

// ==================== Depth parameter in constructor ====================

TEST_F(XMLPrinterTest_305, ConstructorWithDepth_305) {
    XMLPrinter printer(nullptr, false, 2);
    printer.OpenElement("root");
    printer.CloseElement();
    std::string result = printer.CStr();
    // With initial depth of 2, the element should be indented
    EXPECT_NE(result.find("<root"), std::string::npos);
}

// ==================== Special characters in CDATA ====================

TEST_F(XMLPrinterTest_305, PushTextCDataWithXMLSpecialChars_305) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.PushText("a < b && c > d", true);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<![CDATA[a < b && c > d]]>"), std::string::npos);
}

// ==================== Long text content ====================

TEST_F(XMLPrinterTest_305, PushTextLongString_305) {
    XMLPrinter printer(nullptr, true);
    std::string longText(1000, 'x');
    printer.OpenElement("root");
    printer.PushText(longText.c_str(), false);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find(longText), std::string::npos);
}

// ==================== ClearBuffer and reuse ====================

TEST_F(XMLPrinterTest_305, ClearBufferAndReuse_305) {
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
