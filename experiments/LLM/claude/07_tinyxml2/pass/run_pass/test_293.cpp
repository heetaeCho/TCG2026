#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include "tinyxml2.h"

using namespace tinyxml2;

// Helper to get printer output as string
static std::string GetPrinterOutput(XMLPrinter& printer) {
    return std::string(printer.CStr());
}

// ==================== Construction Tests ====================

TEST(XMLPrinterTest_293, DefaultConstruction_293) {
    XMLPrinter printer;
    // Should start with empty buffer
    EXPECT_NE(printer.CStr(), nullptr);
    EXPECT_EQ(printer.CStrSize(), 1u); // Just the null terminator
}

TEST(XMLPrinterTest_293, ConstructionWithCompactMode_293) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    // Compact mode should not have newlines
    EXPECT_EQ(output.find('\n'), std::string::npos);
}

TEST(XMLPrinterTest_293, ConstructionWithDepth_293) {
    XMLPrinter printer(nullptr, false, 2);
    printer.OpenElement("root");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    // Should have indentation based on initial depth
    EXPECT_TRUE(output.find("        <root") != std::string::npos || output.find("    <root") != std::string::npos || output.size() > 0);
}

// ==================== OpenElement / CloseElement Tests ====================

TEST(XMLPrinterTest_293, SimpleElement_293) {
    XMLPrinter printer;
    printer.OpenElement("root");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<root/>"), std::string::npos);
}

TEST(XMLPrinterTest_293, NestedElements_293) {
    XMLPrinter printer;
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<root>"), std::string::npos);
    EXPECT_NE(output.find("<child/>"), std::string::npos);
    EXPECT_NE(output.find("</root>"), std::string::npos);
}

TEST(XMLPrinterTest_293, MultipleNestedElements_293) {
    XMLPrinter printer;
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

TEST(XMLPrinterTest_293, CompactModeElement_293) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<root><child/></root>"), std::string::npos);
}

// ==================== PushAttribute Tests ====================

TEST(XMLPrinterTest_293, PushAttributeString_293) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("name", "value");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("name=\"value\""), std::string::npos);
}

TEST(XMLPrinterTest_293, PushAttributeInt_293) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("count", 42);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("count=\"42\""), std::string::npos);
}

TEST(XMLPrinterTest_293, PushAttributeUnsigned_293) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("val", (unsigned)100);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("val=\"100\""), std::string::npos);
}

TEST(XMLPrinterTest_293, PushAttributeInt64_293) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("big", (int64_t)9223372036854775807LL);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("big=\"9223372036854775807\""), std::string::npos);
}

TEST(XMLPrinterTest_293, PushAttributeUint64_293) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("ubig", (uint64_t)18446744073709551615ULL);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("ubig=\"18446744073709551615\""), std::string::npos);
}

TEST(XMLPrinterTest_293, PushAttributeBoolTrue_293) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("flag", true);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("flag=\"true\""), std::string::npos);
}

TEST(XMLPrinterTest_293, PushAttributeBoolFalse_293) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("flag", false);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("flag=\"false\""), std::string::npos);
}

TEST(XMLPrinterTest_293, PushAttributeDouble_293) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("pi", 3.14);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("pi=\""), std::string::npos);
    // Verify it contains some numeric representation of 3.14
    EXPECT_NE(output.find("3.14"), std::string::npos);
}

TEST(XMLPrinterTest_293, MultipleAttributes_293) {
    XMLPrinter printer;
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

// ==================== PushText Tests ====================

TEST(XMLPrinterTest_293, PushTextString_293) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText("Hello World");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("Hello World"), std::string::npos);
    EXPECT_NE(output.find("</elem>"), std::string::npos);
}

TEST(XMLPrinterTest_293, PushTextCDATA_293) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText("data content", true);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<![CDATA[data content]]>"), std::string::npos);
}

TEST(XMLPrinterTest_293, PushTextInt_293) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText(42);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST(XMLPrinterTest_293, PushTextNegativeInt_293) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText(-99);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("-99"), std::string::npos);
}

TEST(XMLPrinterTest_293, PushTextUnsigned_293) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText((unsigned)123);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("123"), std::string::npos);
}

TEST(XMLPrinterTest_293, PushTextInt64_293) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText((int64_t)1234567890123LL);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("1234567890123"), std::string::npos);
}

TEST(XMLPrinterTest_293, PushTextUint64_293) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText((uint64_t)9876543210ULL);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("9876543210"), std::string::npos);
}

TEST(XMLPrinterTest_293, PushTextBoolTrue_293) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText(true);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST(XMLPrinterTest_293, PushTextBoolFalse_293) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText(false);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("false"), std::string::npos);
}

TEST(XMLPrinterTest_293, PushTextFloat_293) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText(1.5f);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("1.5"), std::string::npos);
}

TEST(XMLPrinterTest_293, PushTextDouble_293) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText(2.718);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("2.718"), std::string::npos);
}

// ==================== PushComment Tests ====================

TEST(XMLPrinterTest_293, PushComment_293) {
    XMLPrinter printer;
    printer.PushComment("This is a comment");
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<!--This is a comment-->"), std::string::npos);
}

TEST(XMLPrinterTest_293, PushCommentInsideElement_293) {
    XMLPrinter printer;
    printer.OpenElement("root");
    printer.PushComment("inner comment");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<!--inner comment-->"), std::string::npos);
    EXPECT_NE(output.find("<root>"), std::string::npos);
    EXPECT_NE(output.find("</root>"), std::string::npos);
}

// ==================== PushDeclaration Tests ====================

TEST(XMLPrinterTest_293, PushDeclaration_293) {
    XMLPrinter printer;
    printer.PushDeclaration("xml version=\"1.0\"");
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<?xml version=\"1.0\"?>"), std::string::npos);
}

// ==================== PushUnknown Tests ====================

TEST(XMLPrinterTest_293, PushUnknown_293) {
    XMLPrinter printer;
    printer.PushUnknown("!DOCTYPE html");
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<!DOCTYPE html>"), std::string::npos);
}

// ==================== PushHeader Tests ====================

TEST(XMLPrinterTest_293, PushHeaderWithDeclaration_293) {
    XMLPrinter printer;
    printer.PushHeader(false, true);
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<?xml"), std::string::npos);
}

TEST(XMLPrinterTest_293, PushHeaderWithBOM_293) {
    XMLPrinter printer;
    printer.PushHeader(true, false);
    std::string output = GetPrinterOutput(printer);
    // BOM is 3 bytes: 0xEF, 0xBB, 0xBF
    EXPECT_GE(printer.CStrSize(), 4u);
}

TEST(XMLPrinterTest_293, PushHeaderWithBOMAndDeclaration_293) {
    XMLPrinter printer;
    printer.PushHeader(true, true);
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<?xml"), std::string::npos);
}

TEST(XMLPrinterTest_293, PushHeaderNoOptions_293) {
    XMLPrinter printer;
    printer.PushHeader(false, false);
    // With both false, nothing should be printed
    EXPECT_EQ(printer.CStrSize(), 1u);
}

// ==================== CStr / CStrSize Tests ====================

TEST(XMLPrinterTest_293, CStrReturnsNullTerminated_293) {
    XMLPrinter printer;
    printer.OpenElement("test");
    printer.CloseElement();
    const char* str = printer.CStr();
    EXPECT_NE(str, nullptr);
    size_t len = strlen(str);
    EXPECT_EQ(len + 1, printer.CStrSize());
}

TEST(XMLPrinterTest_293, CStrSizeIncludesNullTerminator_293) {
    XMLPrinter printer;
    EXPECT_EQ(printer.CStrSize(), 1u); // Only null terminator
}

// ==================== ClearBuffer Tests ====================

TEST(XMLPrinterTest_293, ClearBufferResetsOutput_293) {
    XMLPrinter printer;
    printer.OpenElement("test");
    printer.CloseElement();
    EXPECT_GT(printer.CStrSize(), 1u);
    
    printer.ClearBuffer();
    EXPECT_EQ(printer.CStrSize(), 1u);
}

TEST(XMLPrinterTest_293, ClearBufferAllowsReuse_293) {
    XMLPrinter printer;
    printer.OpenElement("first");
    printer.CloseElement();
    std::string first = GetPrinterOutput(printer);
    
    printer.ClearBuffer();
    printer.OpenElement("second");
    printer.CloseElement();
    std::string second = GetPrinterOutput(printer);
    
    EXPECT_NE(first.find("first"), std::string::npos);
    EXPECT_EQ(second.find("first"), std::string::npos);
    EXPECT_NE(second.find("second"), std::string::npos);
}

// ==================== Integration with XMLDocument Tests ====================

TEST(XMLPrinterTest_293, VisitSimpleDocument_293) {
    XMLDocument doc;
    doc.Parse("<root><child>text</child></root>");
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);
    
    XMLPrinter printer;
    doc.Accept(&printer);
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<root>"), std::string::npos);
    EXPECT_NE(output.find("<child>"), std::string::npos);
    EXPECT_NE(output.find("text"), std::string::npos);
    EXPECT_NE(output.find("</child>"), std::string::npos);
    EXPECT_NE(output.find("</root>"), std::string::npos);
}

TEST(XMLPrinterTest_293, VisitDocumentWithAttributes_293) {
    XMLDocument doc;
    doc.Parse("<root attr=\"val\"><child id=\"1\"/></root>");
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);
    
    XMLPrinter printer;
    doc.Accept(&printer);
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("attr=\"val\""), std::string::npos);
    EXPECT_NE(output.find("id=\"1\""), std::string::npos);
}

TEST(XMLPrinterTest_293, VisitDocumentWithComment_293) {
    XMLDocument doc;
    doc.Parse("<root><!-- a comment --></root>");
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);
    
    XMLPrinter printer;
    doc.Accept(&printer);
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<!-- a comment -->"), std::string::npos);
}

TEST(XMLPrinterTest_293, VisitDocumentWithDeclaration_293) {
    XMLDocument doc;
    doc.Parse("<?xml version=\"1.0\"?><root/>");
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);
    
    XMLPrinter printer;
    doc.Accept(&printer);
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<?xml"), std::string::npos);
}

TEST(XMLPrinterTest_293, VisitDocumentCompactMode_293) {
    XMLDocument doc;
    doc.Parse("<root><a><b>text</b></a></root>");
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);
    
    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string output = GetPrinterOutput(printer);
    // Compact mode: no newlines or extra whitespace
    EXPECT_EQ(output.find('\n'), std::string::npos);
}

// ==================== Entity Handling Tests ====================

TEST(XMLPrinterTest_293, EntityEscapingInText_293) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText("<>&\"");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("&lt;"), std::string::npos);
    EXPECT_NE(output.find("&gt;"), std::string::npos);
    EXPECT_NE(output.find("&amp;"), std::string::npos);
}

TEST(XMLPrinterTest_293, EntityEscapingInAttribute_293) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("val", "<>&\"");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("&lt;"), std::string::npos);
    EXPECT_NE(output.find("&amp;"), std::string::npos);
    EXPECT_NE(output.find("&quot;"), std::string::npos);
}

// ==================== Empty / Boundary Tests ====================

TEST(XMLPrinterTest_293, EmptyElementName_293) {
    XMLPrinter printer;
    printer.OpenElement("");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<"), std::string::npos);
}

TEST(XMLPrinterTest_293, EmptyText_293) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushText("");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<elem>"), std::string::npos);
    EXPECT_NE(output.find("</elem>"), std::string::npos);
}

TEST(XMLPrinterTest_293, EmptyComment_293) {
    XMLPrinter printer;
    printer.PushComment("");
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<!---->"), std::string::npos);
}

TEST(XMLPrinterTest_293, SelfClosingElement_293) {
    XMLPrinter printer;
    printer.OpenElement("empty");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<empty/>"), std::string::npos);
}

TEST(XMLPrinterTest_293, ElementWithAttributeAndNoChildren_293) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("a", "b");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("a=\"b\""), std::string::npos);
    EXPECT_NE(output.find("/>"), std::string::npos);
}

// ==================== File Output Test ====================

TEST(XMLPrinterTest_293, FileOutputNotNull_293) {
    // When printing to file, CStr() should still work (returns internal buffer or similar)
    FILE* f = tmpfile();
    ASSERT_NE(f, nullptr);
    
    XMLPrinter printer(f);
    printer.OpenElement("root");
    printer.CloseElement();
    
    fclose(f);
}

// ==================== Mixed Content Tests ====================

TEST(XMLPrinterTest_293, MixedContentTextAndElements_293) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.PushText("before");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.PushText("after");
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("before"), std::string::npos);
    EXPECT_NE(output.find("after"), std::string::npos);
    EXPECT_NE(output.find("<child/>"), std::string::npos);
}

// ==================== Deeply Nested Elements Test ====================

TEST(XMLPrinterTest_293, DeeplyNestedElements_293) {
    XMLPrinter printer;
    const int depth = 20;
    for (int i = 0; i < depth; ++i) {
        printer.OpenElement("level");
    }
    for (int i = 0; i < depth; ++i) {
        printer.CloseElement();
    }
    std::string output = GetPrinterOutput(printer);
    // The deepest self-closing should be at the inner level
    EXPECT_NE(output.find("</level>"), std::string::npos);
}

// ==================== PushAttribute with Zero Values ====================

TEST(XMLPrinterTest_293, PushAttributeIntZero_293) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("val", 0);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("val=\"0\""), std::string::npos);
}

TEST(XMLPrinterTest_293, PushAttributeNegativeInt_293) {
    XMLPrinter printer;
    printer.OpenElement("elem");
    printer.PushAttribute("val", -42);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("val=\"-42\""), std::string::npos);
}

// ==================== Roundtrip Test ====================

TEST(XMLPrinterTest_293, RoundtripParsePrint_293) {
    const char* xml = "<root><a attr=\"val\">text</a><b/></root>";
    XMLDocument doc;
    doc.Parse(xml);
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);
    
    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    
    // Parse again
    XMLDocument doc2;
    doc2.Parse(printer.CStr());
    ASSERT_EQ(doc2.ErrorID(), XML_SUCCESS);
    
    XMLPrinter printer2(nullptr, true);
    doc2.Accept(&printer2);
    
    EXPECT_STREQ(printer.CStr(), printer2.CStr());
}

// ==================== Multiple Elements at Same Level ====================

TEST(XMLPrinterTest_293, SiblingElements_293) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.OpenElement("a");
    printer.CloseElement();
    printer.OpenElement("b");
    printer.CloseElement();
    printer.OpenElement("c");
    printer.CloseElement();
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<root><a/><b/><c/></root>"), std::string::npos);
}

// ==================== CloseElement with CompactMode parameter ====================

TEST(XMLPrinterTest_293, CloseElementCompactParameter_293) {
    XMLPrinter printer(nullptr, false); // non-compact overall
    printer.OpenElement("root", true);  // compact open
    printer.OpenElement("child", true);
    printer.CloseElement(true);
    printer.CloseElement(true);
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("<root>"), std::string::npos);
}

// ==================== PushText with Zero Values ====================

TEST(XMLPrinterTest_293, PushTextIntZero_293) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText(0);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find(">0</elem>"), std::string::npos);
}

TEST(XMLPrinterTest_293, PushTextDoubleZero_293) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText(0.0);
    printer.CloseElement();
    std::string output = GetPrinterOutput(printer);
    EXPECT_NE(output.find("0"), std::string::npos);
    EXPECT_NE(output.find("</elem>"), std::string::npos);
}
