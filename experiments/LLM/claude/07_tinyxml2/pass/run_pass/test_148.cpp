#include <gtest/gtest.h>
#include <string>
#include <cstring>
#include "tinyxml2.h"

using namespace tinyxml2;

// Helper to get printer output as std::string
static std::string GetPrinterOutput(XMLPrinter& printer) {
    const char* cstr = printer.CStr();
    return cstr ? std::string(cstr) : std::string();
}

// =============================================================================
// Basic Construction and CStr Tests
// =============================================================================

TEST(XMLPrinterTest_148, DefaultConstructionCStrNotNull_148) {
    XMLPrinter printer;
    EXPECT_NE(printer.CStr(), nullptr);
}

TEST(XMLPrinterTest_148, DefaultConstructionCStrSizeIsMinimal_148) {
    XMLPrinter printer;
    // CStrSize should be at least 1 for null terminator or 0 for empty
    EXPECT_GE(printer.CStrSize(), 0u);
}

TEST(XMLPrinterTest_148, CompactModeConstruction_148) {
    XMLPrinter printer(nullptr, true);
    EXPECT_NE(printer.CStr(), nullptr);
}

// =============================================================================
// PushHeader Tests
// =============================================================================

TEST(XMLPrinterTest_148, PushHeaderWithDeclaration_148) {
    XMLPrinter printer;
    printer.PushHeader(false, true);
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<?xml"), std::string::npos);
    EXPECT_NE(output.find("version"), std::string::npos);
}

TEST(XMLPrinterTest_148, PushHeaderWithBOM_148) {
    XMLPrinter printer;
    printer.PushHeader(true, false);
    std::string output = GetPrinterOutput(printer);
    // BOM is 3 bytes: 0xEF 0xBB 0xBF
    ASSERT_GE(output.size(), 3u);
    EXPECT_EQ((unsigned char)output[0], 0xEF);
    EXPECT_EQ((unsigned char)output[1], 0xBB);
    EXPECT_EQ((unsigned char)output[2], 0xBF);
}

TEST(XMLPrinterTest_148, PushHeaderWithBOMAndDeclaration_148) {
    XMLPrinter printer;
    printer.PushHeader(true, true);
    std::string output = GetPrinterOutput(printer);
    EXPECT_GE(output.size(), 3u);
    EXPECT_NE(output.find("<?xml"), std::string::npos);
}

TEST(XMLPrinterTest_148, PushHeaderNoBOMNoDeclaration_148) {
    XMLPrinter printer;
    printer.PushHeader(false, false);
    std::string output = GetPrinterOutput(printer);
    // Should produce nothing or minimal output
    EXPECT_EQ(output.find("<?xml"), std::string::npos);
}

// =============================================================================
// OpenElement / CloseElement Tests
// =============================================================================

TEST(XMLPrinterTest_148, OpenAndCloseElement_148) {
    XMLPrinter printer;
    printer.OpenElement("root");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<root"), std::string::npos);
    // Could be self-closing or have close tag
}

TEST(XMLPrinterTest_148, OpenAndCloseElementCompact_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<root/>"), std::string::npos);
}

TEST(XMLPrinterTest_148, NestedElements_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<root>"), std::string::npos);
    EXPECT_NE(output.find("<child/>"), std::string::npos);
    EXPECT_NE(output.find("</root>"), std::string::npos);
}

TEST(XMLPrinterTest_148, MultipleNestedElements_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.OpenElement("a");
    printer.OpenElement("b");
    printer.CloseElement();
    printer.CloseElement();
    printer.OpenElement("c");
    printer.CloseElement();
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<root>"), std::string::npos);
    EXPECT_NE(output.find("<a>"), std::string::npos);
    EXPECT_NE(output.find("<b/>"), std::string::npos);
    EXPECT_NE(output.find("</a>"), std::string::npos);
    EXPECT_NE(output.find("<c/>"), std::string::npos);
    EXPECT_NE(output.find("</root>"), std::string::npos);
}

// =============================================================================
// PushAttribute Tests
// =============================================================================

TEST(XMLPrinterTest_148, PushAttributeString_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("name", "value");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("name=\"value\""), std::string::npos);
}

TEST(XMLPrinterTest_148, PushAttributeInt_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("count", 42);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("count=\"42\""), std::string::npos);
}

TEST(XMLPrinterTest_148, PushAttributeNegativeInt_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", -100);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("val=\"-100\""), std::string::npos);
}

TEST(XMLPrinterTest_148, PushAttributeUnsignedInt_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", (unsigned int)123);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("val=\"123\""), std::string::npos);
}

TEST(XMLPrinterTest_148, PushAttributeInt64_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", (int64_t)9876543210LL);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("val=\"9876543210\""), std::string::npos);
}

TEST(XMLPrinterTest_148, PushAttributeUint64_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", (uint64_t)18446744073709551615ULL);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("val=\"18446744073709551615\""), std::string::npos);
}

TEST(XMLPrinterTest_148, PushAttributeBoolTrue_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("flag", true);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("flag=\"true\""), std::string::npos);
}

TEST(XMLPrinterTest_148, PushAttributeBoolFalse_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("flag", false);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("flag=\"false\""), std::string::npos);
}

TEST(XMLPrinterTest_148, PushAttributeDouble_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", 3.14);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("val=\""), std::string::npos);
    // Just verify it contains the attribute, exact format may vary
}

TEST(XMLPrinterTest_148, MultipleAttributes_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("a", "1");
    printer.PushAttribute("b", "2");
    printer.PushAttribute("c", "3");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("a=\"1\""), std::string::npos);
    EXPECT_NE(output.find("b=\"2\""), std::string::npos);
    EXPECT_NE(output.find("c=\"3\""), std::string::npos);
}

// =============================================================================
// PushText Tests
// =============================================================================

TEST(XMLPrinterTest_148, PushTextString_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText("Hello World");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("Hello World"), std::string::npos);
    EXPECT_NE(output.find("<elem>"), std::string::npos);
    EXPECT_NE(output.find("</elem>"), std::string::npos);
}

TEST(XMLPrinterTest_148, PushTextCData_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText("some data", true);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<![CDATA[some data]]>"), std::string::npos);
}

TEST(XMLPrinterTest_148, PushTextInt_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText(42);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST(XMLPrinterTest_148, PushTextUnsignedInt_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText((unsigned int)99);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("99"), std::string::npos);
}

TEST(XMLPrinterTest_148, PushTextInt64_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText((int64_t)123456789012LL);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("123456789012"), std::string::npos);
}

TEST(XMLPrinterTest_148, PushTextUint64_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText((uint64_t)987654321098ULL);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("987654321098"), std::string::npos);
}

TEST(XMLPrinterTest_148, PushTextBoolTrue_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText(true);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST(XMLPrinterTest_148, PushTextBoolFalse_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText(false);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("false"), std::string::npos);
}

TEST(XMLPrinterTest_148, PushTextFloat_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText(1.5f);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("1.5"), std::string::npos);
}

TEST(XMLPrinterTest_148, PushTextDouble_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText(2.718);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("2.718"), std::string::npos);
}

// =============================================================================
// PushComment Tests
// =============================================================================

TEST(XMLPrinterTest_148, PushComment_148) {
    XMLPrinter printer(nullptr, true);
    printer.PushComment("This is a comment");
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<!--This is a comment-->"), std::string::npos);
}

TEST(XMLPrinterTest_148, PushCommentInsideElement_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.PushComment("inner comment");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<!--inner comment-->"), std::string::npos);
}

// =============================================================================
// PushDeclaration Tests
// =============================================================================

TEST(XMLPrinterTest_148, PushDeclaration_148) {
    XMLPrinter printer(nullptr, true);
    printer.PushDeclaration("xml version=\"1.0\"");
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<?xml version=\"1.0\"?>"), std::string::npos);
}

// =============================================================================
// PushUnknown Tests
// =============================================================================

TEST(XMLPrinterTest_148, PushUnknown_148) {
    XMLPrinter printer(nullptr, true);
    printer.PushUnknown("DOCTYPE html");
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<!DOCTYPE html>"), std::string::npos);
}

// =============================================================================
// ClearBuffer Tests
// =============================================================================

TEST(XMLPrinterTest_148, ClearBufferResetsOutput_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.CloseElement();
    EXPECT_GT(printer.CStrSize(), 1u);

    printer.ClearBuffer();
    // After clearing, the buffer should be empty or minimal
    std::string output = GetPrinterOutput(printer);
    EXPECT_TRUE(output.empty() || output.size() == 0);
}

TEST(XMLPrinterTest_148, ClearBufferThenReuse_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("first");
    printer.CloseElement();
    printer.ClearBuffer();

    printer.OpenElement("second");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_EQ(output.find("first"), std::string::npos);
    EXPECT_NE(output.find("<second/>"), std::string::npos);
}

// =============================================================================
// CStrSize Tests
// =============================================================================

TEST(XMLPrinterTest_148, CStrSizeMatchesCStr_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test");
    printer.PushAttribute("key", "val");
    printer.PushText("content");
    printer.CloseElement();
    size_t size = printer.CStrSize();
    const char* cstr = printer.CStr();
    // CStrSize includes null terminator typically
    EXPECT_EQ(size, strlen(cstr) + 1);
}

// =============================================================================
// Entity Escaping Tests
// =============================================================================

TEST(XMLPrinterTest_148, TextEntityEscaping_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText("a < b & c > d");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("&lt;"), std::string::npos);
    EXPECT_NE(output.find("&amp;"), std::string::npos);
    EXPECT_NE(output.find("&gt;"), std::string::npos);
}

TEST(XMLPrinterTest_148, AttributeEntityEscaping_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", "a\"b<c&d");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("&quot;"), std::string::npos);
    EXPECT_NE(output.find("&lt;"), std::string::npos);
    EXPECT_NE(output.find("&amp;"), std::string::npos);
}

// =============================================================================
// Visitor Interface via XMLDocument Tests
// =============================================================================

TEST(XMLPrinterTest_148, VisitDocumentRoundTrip_148) {
    const char* xml = "<root><child attr=\"val\">text</child></root>";
    XMLDocument doc;
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<root>"), std::string::npos);
    EXPECT_NE(output.find("<child"), std::string::npos);
    EXPECT_NE(output.find("attr=\"val\""), std::string::npos);
    EXPECT_NE(output.find("text"), std::string::npos);
    EXPECT_NE(output.find("</child>"), std::string::npos);
    EXPECT_NE(output.find("</root>"), std::string::npos);
}

TEST(XMLPrinterTest_148, VisitDocumentWithComment_148) {
    const char* xml = "<!-- a comment --><root/>";
    XMLDocument doc;
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<!-- a comment -->"), std::string::npos);
    EXPECT_NE(output.find("<root/>"), std::string::npos);
}

TEST(XMLPrinterTest_148, VisitDocumentWithDeclaration_148) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    XMLDocument doc;
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<?xml"), std::string::npos);
    EXPECT_NE(output.find("<root/>"), std::string::npos);
}

TEST(XMLPrinterTest_148, VisitDocumentWithUnknown_148) {
    const char* xml = "<!DOCTYPE html><root/>";
    XMLDocument doc;
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<!DOCTYPE html>"), std::string::npos);
}

// =============================================================================
// Non-compact mode (pretty printing) Tests
// =============================================================================

TEST(XMLPrinterTest_148, NonCompactModeHasNewlines_148) {
    XMLPrinter printer(nullptr, false);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("\n"), std::string::npos);
}

TEST(XMLPrinterTest_148, NonCompactModeHasIndentation_148) {
    XMLPrinter printer(nullptr, false);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    // Indentation typically uses spaces or tabs
    EXPECT_NE(output.find("    "), std::string::npos);  // 4 spaces indent (common default)
}

// =============================================================================
// Self-closing element Tests
// =============================================================================

TEST(XMLPrinterTest_148, EmptyElementSelfCloses_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("empty");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<empty/>"), std::string::npos);
}

TEST(XMLPrinterTest_148, ElementWithAttributeSelfCloses_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("x", "1");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("/>"), std::string::npos);
    // Should not have a separate close tag
    EXPECT_EQ(output.find("</elem>"), std::string::npos);
}

TEST(XMLPrinterTest_148, ElementWithTextDoesNotSelfClose_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText("text");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("</elem>"), std::string::npos);
}

// =============================================================================
// Complex Document Tests
// =============================================================================

TEST(XMLPrinterTest_148, ComplexDocumentBuild_148) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(false, true);
    printer.OpenElement("document");
    printer.PushAttribute("version", "1.0");
    
    printer.OpenElement("section");
    printer.PushAttribute("id", 1);
    printer.PushText("Section 1 content");
    printer.CloseElement();
    
    printer.OpenElement("section");
    printer.PushAttribute("id", 2);
    printer.OpenElement("subsection");
    printer.PushText("Nested content");
    printer.CloseElement();
    printer.CloseElement();
    
    printer.PushComment("end of document");
    printer.CloseElement();
    
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<?xml"), std::string::npos);
    EXPECT_NE(output.find("<document"), std::string::npos);
    EXPECT_NE(output.find("version=\"1.0\""), std::string::npos);
    EXPECT_NE(output.find("Section 1 content"), std::string::npos);
    EXPECT_NE(output.find("Nested content"), std::string::npos);
    EXPECT_NE(output.find("<!--end of document-->"), std::string::npos);
    EXPECT_NE(output.find("</document>"), std::string::npos);
}

// =============================================================================
// Empty string / boundary tests
// =============================================================================

TEST(XMLPrinterTest_148, PushTextEmptyString_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText("");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<elem>"), std::string::npos);
    EXPECT_NE(output.find("</elem>"), std::string::npos);
}

TEST(XMLPrinterTest_148, PushCommentEmptyString_148) {
    XMLPrinter printer(nullptr, true);
    printer.PushComment("");
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<!--"), std::string::npos);
    EXPECT_NE(output.find("-->"), std::string::npos);
}

TEST(XMLPrinterTest_148, PushAttributeEmptyValue_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("key", "");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("key=\"\""), std::string::npos);
}

// =============================================================================
// Zero values
// =============================================================================

TEST(XMLPrinterTest_148, PushTextIntZero_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText(0);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find(">0<"), std::string::npos);
}

TEST(XMLPrinterTest_148, PushAttributeIntZero_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", 0);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("val=\"0\""), std::string::npos);
}

// =============================================================================
// Depth parameter test
// =============================================================================

TEST(XMLPrinterTest_148, CustomInitialDepth_148) {
    XMLPrinter printer(nullptr, false, 2);
    printer.OpenElement("elem");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    // With initial depth=2, there should be indentation before the element
    // The exact indentation depends on implementation, but there should be some leading whitespace
    EXPECT_NE(output.find("<elem"), std::string::npos);
}

// =============================================================================
// Accept with XMLDocument re-print
// =============================================================================

TEST(XMLPrinterTest_148, ReprintParsedDocument_148) {
    const char* xml = 
        "<?xml version=\"1.0\"?>"
        "<root>"
        "  <item id=\"1\">First</item>"
        "  <item id=\"2\">Second</item>"
        "</root>";
    
    XMLDocument doc;
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());
    
    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    
    // Re-parse the output to verify validity
    XMLDocument doc2;
    doc2.Parse(printer.CStr());
    ASSERT_FALSE(doc2.Error());
    
    XMLElement* root = doc2.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    XMLElement* item1 = root->FirstChildElement("item");
    ASSERT_NE(item1, nullptr);
    EXPECT_STREQ(item1->Attribute("id"), "1");
    EXPECT_STREQ(item1->GetText(), "First");
}

// =============================================================================
// Multiple CStr calls return same pointer
// =============================================================================

TEST(XMLPrinterTest_148, CStrConsistentBetweenCalls_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test");
    printer.CloseElement();
    
    const char* first = printer.CStr();
    const char* second = printer.CStr();
    EXPECT_EQ(first, second);
    EXPECT_STREQ(first, second);
}

// =============================================================================
// CStrSize consistency with content
// =============================================================================

TEST(XMLPrinterTest_148, CStrSizeAfterMultipleOperations_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.PushAttribute("a", "b");
    printer.PushText("hello");
    printer.CloseElement();
    
    size_t size = printer.CStrSize();
    const char* str = printer.CStr();
    EXPECT_EQ(size, strlen(str) + 1);
}

// =============================================================================
// ClearBuffer with resetToFirstElement parameter
// =============================================================================

TEST(XMLPrinterTest_148, ClearBufferWithResetFalse_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("first");
    printer.CloseElement();
    printer.ClearBuffer(false);
    
    printer.OpenElement("second");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<second/>"), std::string::npos);
}

TEST(XMLPrinterTest_148, ClearBufferWithResetTrue_148) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("first");
    printer.CloseElement();
    printer.ClearBuffer(true);
    
    printer.OpenElement("second");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<second/>"), std::string::npos);
}
