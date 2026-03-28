#include "gtest/gtest.h"
#include "tinyxml2.h"
#include <string>
#include <cstring>

using namespace tinyxml2;

// ============================================================
// Test Fixture
// ============================================================
class XMLPrinterTest_315 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// PushUnknown Tests
// ============================================================

TEST_F(XMLPrinterTest_315, PushUnknown_BasicValue_315) {
    XMLPrinter printer(nullptr, true);
    printer.PushUnknown("DOCTYPE html");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!DOCTYPE html>"), std::string::npos);
}

TEST_F(XMLPrinterTest_315, PushUnknown_EmptyValue_315) {
    XMLPrinter printer(nullptr, true);
    printer.PushUnknown("");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!>"), std::string::npos);
}

TEST_F(XMLPrinterTest_315, PushUnknown_MultipleUnknowns_315) {
    XMLPrinter printer(nullptr, true);
    printer.PushUnknown("FIRST");
    printer.PushUnknown("SECOND");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!FIRST>"), std::string::npos);
    EXPECT_NE(result.find("<!SECOND>"), std::string::npos);
}

TEST_F(XMLPrinterTest_315, PushUnknown_CompactMode_315) {
    XMLPrinter printer(nullptr, true);
    printer.PushUnknown("DOCTYPE html");
    std::string result = printer.CStr();
    // In compact mode there should be no extra newlines/spaces before the unknown
    EXPECT_EQ(result, "<!DOCTYPE html>");
}

TEST_F(XMLPrinterTest_315, PushUnknown_NonCompactMode_315) {
    XMLPrinter printer(nullptr, false);
    printer.PushUnknown("DOCTYPE html");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!DOCTYPE html>"), std::string::npos);
}

TEST_F(XMLPrinterTest_315, PushUnknown_WithSpecialChars_315) {
    XMLPrinter printer(nullptr, true);
    printer.PushUnknown("ENTITY foo \"bar\"");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!ENTITY foo \"bar\">"), std::string::npos);
}

TEST_F(XMLPrinterTest_315, PushUnknown_InsideElement_315) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushUnknown("something");
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root>"), std::string::npos);
    EXPECT_NE(result.find("<!something>"), std::string::npos);
    EXPECT_NE(result.find("</root>"), std::string::npos);
}

// ============================================================
// CStr / CStrSize / ClearBuffer Tests
// ============================================================

TEST_F(XMLPrinterTest_315, CStr_InitiallyEmpty_315) {
    XMLPrinter printer(nullptr, true);
    const char* str = printer.CStr();
    ASSERT_NE(str, nullptr);
    // Should be an empty (or near-empty) buffer initially
    EXPECT_EQ(std::string(str), "");
}

TEST_F(XMLPrinterTest_315, CStrSize_AfterPushUnknown_315) {
    XMLPrinter printer(nullptr, true);
    printer.PushUnknown("test");
    // "<!test>" is 7 characters, CStrSize includes null terminator
    size_t size = printer.CStrSize();
    EXPECT_GE(size, 8u); // at least "<!test>" + null
}

TEST_F(XMLPrinterTest_315, ClearBuffer_ResetsContent_315) {
    XMLPrinter printer(nullptr, true);
    printer.PushUnknown("test");
    EXPECT_GT(std::strlen(printer.CStr()), 0u);
    printer.ClearBuffer();
    EXPECT_EQ(std::string(printer.CStr()), "");
}

// ============================================================
// OpenElement / CloseElement Tests
// ============================================================

TEST_F(XMLPrinterTest_315, OpenAndCloseElement_Basic_315) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("div", true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<div"), std::string::npos);
    // Could be self-closing or open/close
}

TEST_F(XMLPrinterTest_315, OpenElement_SelfClosing_315) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("br", true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    // Self-closing element when no children
    EXPECT_NE(result.find("<br/>"), std::string::npos);
}

TEST_F(XMLPrinterTest_315, NestedElements_315) {
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

// ============================================================
// PushAttribute Tests
// ============================================================

TEST_F(XMLPrinterTest_315, PushAttribute_String_315) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("tag", true);
    printer.PushAttribute("name", "value");
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("name=\"value\""), std::string::npos);
}

TEST_F(XMLPrinterTest_315, PushAttribute_Int_315) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("tag", true);
    printer.PushAttribute("count", 42);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("count=\"42\""), std::string::npos);
}

TEST_F(XMLPrinterTest_315, PushAttribute_UnsignedInt_315) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("tag", true);
    printer.PushAttribute("val", (unsigned int)100);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val=\"100\""), std::string::npos);
}

TEST_F(XMLPrinterTest_315, PushAttribute_Int64_315) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("tag", true);
    printer.PushAttribute("big", (int64_t)9999999999LL);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("big=\"9999999999\""), std::string::npos);
}

TEST_F(XMLPrinterTest_315, PushAttribute_Uint64_315) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("tag", true);
    printer.PushAttribute("ubig", (uint64_t)12345678901ULL);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("ubig=\"12345678901\""), std::string::npos);
}

TEST_F(XMLPrinterTest_315, PushAttribute_Bool_True_315) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("tag", true);
    printer.PushAttribute("flag", true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("flag=\"true\""), std::string::npos);
}

TEST_F(XMLPrinterTest_315, PushAttribute_Bool_False_315) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("tag", true);
    printer.PushAttribute("flag", false);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("flag=\"false\""), std::string::npos);
}

TEST_F(XMLPrinterTest_315, PushAttribute_Double_315) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("tag", true);
    printer.PushAttribute("pi", 3.14);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("pi=\""), std::string::npos);
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

TEST_F(XMLPrinterTest_315, PushAttribute_MultipleAttributes_315) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("tag", true);
    printer.PushAttribute("a", "1");
    printer.PushAttribute("b", "2");
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("a=\"1\""), std::string::npos);
    EXPECT_NE(result.find("b=\"2\""), std::string::npos);
}

// ============================================================
// PushText Tests
// ============================================================

TEST_F(XMLPrinterTest_315, PushText_String_315) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("p", true);
    printer.PushText("Hello World");
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("Hello World"), std::string::npos);
}

TEST_F(XMLPrinterTest_315, PushText_CDATA_315) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("p", true);
    printer.PushText("data", true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<![CDATA[data]]>"), std::string::npos);
}

TEST_F(XMLPrinterTest_315, PushText_Int_315) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("num", true);
    printer.PushText(42);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("42"), std::string::npos);
}

TEST_F(XMLPrinterTest_315, PushText_NegativeInt_315) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("num", true);
    printer.PushText(-99);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("-99"), std::string::npos);
}

TEST_F(XMLPrinterTest_315, PushText_Unsigned_315) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("num", true);
    printer.PushText((unsigned)500);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("500"), std::string::npos);
}

TEST_F(XMLPrinterTest_315, PushText_Int64_315) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("num", true);
    printer.PushText((int64_t)123456789012345LL);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("123456789012345"), std::string::npos);
}

TEST_F(XMLPrinterTest_315, PushText_Uint64_315) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("num", true);
    printer.PushText((uint64_t)98765432109ULL);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("98765432109"), std::string::npos);
}

TEST_F(XMLPrinterTest_315, PushText_BoolTrue_315) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("val", true);
    printer.PushText(true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("true"), std::string::npos);
}

TEST_F(XMLPrinterTest_315, PushText_BoolFalse_315) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("val", true);
    printer.PushText(false);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("false"), std::string::npos);
}

TEST_F(XMLPrinterTest_315, PushText_Float_315) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("val", true);
    printer.PushText(1.5f);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("1.5"), std::string::npos);
}

TEST_F(XMLPrinterTest_315, PushText_Double_315) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("val", true);
    printer.PushText(2.718);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("2.718"), std::string::npos);
}

// ============================================================
// PushComment Tests
// ============================================================

TEST_F(XMLPrinterTest_315, PushComment_Basic_315) {
    XMLPrinter printer(nullptr, true);
    printer.PushComment("This is a comment");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!--This is a comment-->"), std::string::npos);
}

TEST_F(XMLPrinterTest_315, PushComment_EmptyComment_315) {
    XMLPrinter printer(nullptr, true);
    printer.PushComment("");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!---->"), std::string::npos);
}

// ============================================================
// PushDeclaration Tests
// ============================================================

TEST_F(XMLPrinterTest_315, PushDeclaration_Basic_315) {
    XMLPrinter printer(nullptr, true);
    printer.PushDeclaration("xml version=\"1.0\"");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml version=\"1.0\"?>"), std::string::npos);
}

// ============================================================
// PushHeader Tests
// ============================================================

TEST_F(XMLPrinterTest_315, PushHeader_WithDeclaration_315) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(false, true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml"), std::string::npos);
}

TEST_F(XMLPrinterTest_315, PushHeader_WithBOM_315) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(true, false);
    const char* result = printer.CStr();
    // BOM: 0xEF 0xBB 0xBF
    EXPECT_EQ((unsigned char)result[0], 0xEFu);
    EXPECT_EQ((unsigned char)result[1], 0xBBu);
    EXPECT_EQ((unsigned char)result[2], 0xBFu);
}

TEST_F(XMLPrinterTest_315, PushHeader_NoBOMNoDeclaration_315) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(false, false);
    std::string result = printer.CStr();
    // Nothing should be added
    EXPECT_EQ(result, "");
}

// ============================================================
// Document Visitor Tests
// ============================================================

TEST_F(XMLPrinterTest_315, VisitDocument_RoundTrip_315) {
    const char* xml = "<root><child attr=\"val\">text</child></root>";
    XMLDocument doc;
    doc.Parse(xml);
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);

    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root>"), std::string::npos);
    EXPECT_NE(result.find("<child"), std::string::npos);
    EXPECT_NE(result.find("attr=\"val\""), std::string::npos);
    EXPECT_NE(result.find("text"), std::string::npos);
    EXPECT_NE(result.find("</child>"), std::string::npos);
    EXPECT_NE(result.find("</root>"), std::string::npos);
}

TEST_F(XMLPrinterTest_315, VisitDocument_WithComment_315) {
    const char* xml = "<!-- a comment --><root/>";
    XMLDocument doc;
    doc.Parse(xml);
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);

    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!-- a comment -->"), std::string::npos);
    EXPECT_NE(result.find("<root/>"), std::string::npos);
}

TEST_F(XMLPrinterTest_315, VisitDocument_WithUnknown_315) {
    const char* xml = "<!DOCTYPE html><root/>";
    XMLDocument doc;
    doc.Parse(xml);
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);

    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!DOCTYPE html>"), std::string::npos);
}

TEST_F(XMLPrinterTest_315, VisitDocument_WithDeclaration_315) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    XMLDocument doc;
    doc.Parse(xml);
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);

    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml version=\"1.0\"?>"), std::string::npos);
}

// ============================================================
// Non-compact mode formatting tests
// ============================================================

TEST_F(XMLPrinterTest_315, NonCompactMode_HasNewlines_315) {
    XMLPrinter printer(nullptr, false);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find('\n'), std::string::npos);
}

TEST_F(XMLPrinterTest_315, CompactMode_NoExtraNewlines_315) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.OpenElement("child", true);
    printer.CloseElement(true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    // In compact mode, there should be no newlines
    EXPECT_EQ(result.find('\n'), std::string::npos);
}

// ============================================================
// ClearBuffer and reuse
// ============================================================

TEST_F(XMLPrinterTest_315, ClearBufferAndReuse_315) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("first", true);
    printer.CloseElement(true);
    EXPECT_NE(std::string(printer.CStr()).find("<first/>"), std::string::npos);

    printer.ClearBuffer();
    printer.OpenElement("second", true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_EQ(result.find("<first/>"), std::string::npos);
    EXPECT_NE(result.find("<second/>"), std::string::npos);
}

// ============================================================
// PushUnknown with long/complex values
// ============================================================

TEST_F(XMLPrinterTest_315, PushUnknown_LongValue_315) {
    XMLPrinter printer(nullptr, true);
    std::string longVal(1000, 'x');
    printer.PushUnknown(longVal.c_str());
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!" + longVal + ">"), std::string::npos);
}

TEST_F(XMLPrinterTest_315, PushUnknown_WithAngleBrackets_315) {
    XMLPrinter printer(nullptr, true);
    printer.PushUnknown("ENTITY % stuff SYSTEM \"file.dtd\"");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!ENTITY % stuff SYSTEM \"file.dtd\">"), std::string::npos);
}

// ============================================================
// Interaction: PushUnknown after other operations
// ============================================================

TEST_F(XMLPrinterTest_315, PushUnknown_AfterHeader_315) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(false, true);
    printer.PushUnknown("DOCTYPE root");
    printer.OpenElement("root", true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml"), std::string::npos);
    EXPECT_NE(result.find("<!DOCTYPE root>"), std::string::npos);
    EXPECT_NE(result.find("<root/>"), std::string::npos);
}

// ============================================================
// Multiple unknowns interspersed with elements
// ============================================================

TEST_F(XMLPrinterTest_315, PushUnknown_InterspersedWithElements_315) {
    XMLPrinter printer(nullptr, true);
    printer.PushUnknown("ONE");
    printer.OpenElement("middle", true);
    printer.CloseElement(true);
    printer.PushUnknown("TWO");
    std::string result = printer.CStr();
    size_t posOne = result.find("<!ONE>");
    size_t posMiddle = result.find("<middle/>");
    size_t posTwo = result.find("<!TWO>");
    ASSERT_NE(posOne, std::string::npos);
    ASSERT_NE(posMiddle, std::string::npos);
    ASSERT_NE(posTwo, std::string::npos);
    EXPECT_LT(posOne, posMiddle);
    EXPECT_LT(posMiddle, posTwo);
}

// ============================================================
// Depth parameter test
// ============================================================

TEST_F(XMLPrinterTest_315, ConstructorWithDepth_315) {
    XMLPrinter printer(nullptr, false, 2);
    printer.OpenElement("item");
    printer.CloseElement();
    std::string result = printer.CStr();
    // With depth=2, there should be indentation
    EXPECT_NE(result.find("item"), std::string::npos);
}

// ============================================================
// Element with text content (not self-closing)
// ============================================================

TEST_F(XMLPrinterTest_315, ElementWithTextNotSelfClosing_315) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("tag", true);
    printer.PushText("content");
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<tag>content</tag>"), std::string::npos);
}

// ============================================================
// Empty string in PushText
// ============================================================

TEST_F(XMLPrinterTest_315, PushText_EmptyString_315) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("tag", true);
    printer.PushText("");
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<tag>"), std::string::npos);
    EXPECT_NE(result.find("</tag>"), std::string::npos);
}

// ============================================================
// Special XML entities in text
// ============================================================

TEST_F(XMLPrinterTest_315, PushText_WithEntities_315) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("tag", true);
    printer.PushText("a < b & c > d");
    printer.CloseElement(true);
    std::string result = printer.CStr();
    // Should have entity escaping
    EXPECT_NE(result.find("&lt;"), std::string::npos);
    EXPECT_NE(result.find("&amp;"), std::string::npos);
    EXPECT_NE(result.find("&gt;"), std::string::npos);
}

// ============================================================
// PushAttribute with entities in value
// ============================================================

TEST_F(XMLPrinterTest_315, PushAttribute_WithEntities_315) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("tag", true);
    printer.PushAttribute("val", "a&b<c>d\"e");
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("&amp;"), std::string::npos);
    EXPECT_NE(result.find("&lt;"), std::string::npos);
    EXPECT_NE(result.find("&gt;"), std::string::npos);
    EXPECT_NE(result.find("&quot;"), std::string::npos);
}
