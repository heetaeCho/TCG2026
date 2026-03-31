#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// Helper to get printer output as string
static std::string GetPrinterOutput(XMLPrinter& printer) {
    return std::string(printer.CStr());
}

// ==========================
// PushDeclaration Tests
// ==========================

TEST(XMLPrinterPushDeclarationTest_314, BasicDeclaration_314) {
    XMLPrinter printer(nullptr, true);
    printer.PushDeclaration("xml version=\"1.0\"");
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("<?xml version=\"1.0\"?>"), std::string::npos);
}

TEST(XMLPrinterPushDeclarationTest_314, EmptyDeclaration_314) {
    XMLPrinter printer(nullptr, true);
    printer.PushDeclaration("");
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("<??>"), std::string::npos);
}

TEST(XMLPrinterPushDeclarationTest_314, DeclarationWithEncoding_314) {
    XMLPrinter printer(nullptr, true);
    printer.PushDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("<?xml version=\"1.0\" encoding=\"UTF-8\"?>"), std::string::npos);
}

TEST(XMLPrinterPushDeclarationTest_314, MultipleDeclarations_314) {
    XMLPrinter printer(nullptr, true);
    printer.PushDeclaration("xml version=\"1.0\"");
    printer.PushDeclaration("xml-stylesheet type=\"text/xsl\" href=\"style.xsl\"");
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("<?xml version=\"1.0\"?>"), std::string::npos);
    EXPECT_NE(result.find("<?xml-stylesheet type=\"text/xsl\" href=\"style.xsl\"?>"), std::string::npos);
}

TEST(XMLPrinterPushDeclarationTest_314, DeclarationNonCompactMode_314) {
    XMLPrinter printer(nullptr, false);
    printer.PushDeclaration("xml version=\"1.0\"");
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("<?xml version=\"1.0\"?>"), std::string::npos);
}

// ==========================
// OpenElement / CloseElement Tests
// ==========================

TEST(XMLPrinterElementTest_314, SimpleElement_314) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("<root/>"), std::string::npos);
}

TEST(XMLPrinterElementTest_314, ElementWithText_314) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.PushText("hello");
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("<root>hello</root>"), std::string::npos);
}

TEST(XMLPrinterElementTest_314, NestedElements_314) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("<root>"), std::string::npos);
    EXPECT_NE(result.find("<child/>"), std::string::npos);
    EXPECT_NE(result.find("</root>"), std::string::npos);
}

TEST(XMLPrinterElementTest_314, ElementNonCompactMode_314) {
    XMLPrinter printer(nullptr, false);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("<root>"), std::string::npos);
    EXPECT_NE(result.find("<child/>"), std::string::npos);
    EXPECT_NE(result.find("</root>"), std::string::npos);
}

// ==========================
// PushAttribute Tests
// ==========================

TEST(XMLPrinterAttributeTest_314, StringAttribute_314) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("name", "value");
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("name=\"value\""), std::string::npos);
}

TEST(XMLPrinterAttributeTest_314, IntAttribute_314) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("count", 42);
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("count=\"42\""), std::string::npos);
}

TEST(XMLPrinterAttributeTest_314, UnsignedIntAttribute_314) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", (unsigned int)100);
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("val=\"100\""), std::string::npos);
}

TEST(XMLPrinterAttributeTest_314, Int64Attribute_314) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("big", (int64_t)9223372036854775807LL);
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("big=\"9223372036854775807\""), std::string::npos);
}

TEST(XMLPrinterAttributeTest_314, Uint64Attribute_314) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("ubig", (uint64_t)18446744073709551615ULL);
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("ubig=\"18446744073709551615\""), std::string::npos);
}

TEST(XMLPrinterAttributeTest_314, BoolAttributeTrue_314) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("flag", true);
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("flag=\"true\""), std::string::npos);
}

TEST(XMLPrinterAttributeTest_314, BoolAttributeFalse_314) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("flag", false);
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("flag=\"false\""), std::string::npos);
}

TEST(XMLPrinterAttributeTest_314, DoubleAttribute_314) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("pi", 3.14);
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("pi="), std::string::npos);
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

TEST(XMLPrinterAttributeTest_314, MultipleAttributes_314) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("a", "1");
    printer.PushAttribute("b", "2");
    printer.PushAttribute("c", "3");
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("a=\"1\""), std::string::npos);
    EXPECT_NE(result.find("b=\"2\""), std::string::npos);
    EXPECT_NE(result.find("c=\"3\""), std::string::npos);
}

// ==========================
// PushText Tests
// ==========================

TEST(XMLPrinterTextTest_314, TextString_314) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText("Hello World");
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("Hello World"), std::string::npos);
}

TEST(XMLPrinterTextTest_314, TextCDATA_314) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText("Some data", true);
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("<![CDATA[Some data]]>"), std::string::npos);
}

TEST(XMLPrinterTextTest_314, TextInt_314) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText(42);
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("42"), std::string::npos);
}

TEST(XMLPrinterTextTest_314, TextNegativeInt_314) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText(-100);
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("-100"), std::string::npos);
}

TEST(XMLPrinterTextTest_314, TextUnsignedInt_314) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText((unsigned int)999);
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("999"), std::string::npos);
}

TEST(XMLPrinterTextTest_314, TextInt64_314) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText((int64_t)123456789012345LL);
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("123456789012345"), std::string::npos);
}

TEST(XMLPrinterTextTest_314, TextUint64_314) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText((uint64_t)987654321098765ULL);
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("987654321098765"), std::string::npos);
}

TEST(XMLPrinterTextTest_314, TextBoolTrue_314) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText(true);
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("true"), std::string::npos);
}

TEST(XMLPrinterTextTest_314, TextBoolFalse_314) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText(false);
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("false"), std::string::npos);
}

TEST(XMLPrinterTextTest_314, TextFloat_314) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText(1.5f);
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("1.5"), std::string::npos);
}

TEST(XMLPrinterTextTest_314, TextDouble_314) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText(2.718281828);
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("2.71828"), std::string::npos);
}

// ==========================
// PushComment Tests
// ==========================

TEST(XMLPrinterCommentTest_314, SimpleComment_314) {
    XMLPrinter printer(nullptr, true);
    printer.PushComment("This is a comment");
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("<!--This is a comment-->"), std::string::npos);
}

TEST(XMLPrinterCommentTest_314, EmptyComment_314) {
    XMLPrinter printer(nullptr, true);
    printer.PushComment("");
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("<!---->"), std::string::npos);
}

// ==========================
// PushUnknown Tests
// ==========================

TEST(XMLPrinterUnknownTest_314, SimpleUnknown_314) {
    XMLPrinter printer(nullptr, true);
    printer.PushUnknown("!DOCTYPE html");
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("<!DOCTYPE html>"), std::string::npos);
}

TEST(XMLPrinterUnknownTest_314, EmptyUnknown_314) {
    XMLPrinter printer(nullptr, true);
    printer.PushUnknown("");
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("<!>"), std::string::npos);
}

// ==========================
// PushHeader Tests
// ==========================

TEST(XMLPrinterHeaderTest_314, HeaderWithDeclaration_314) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(false, true);
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("<?xml"), std::string::npos);
    EXPECT_NE(result.find("?>"), std::string::npos);
}

TEST(XMLPrinterHeaderTest_314, HeaderWithBOM_314) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(true, false);
    std::string result = GetPrinterOutput(printer);
    // BOM is 0xEF 0xBB 0xBF
    EXPECT_GE(printer.CStrSize(), 3u);
    const char* raw = printer.CStr();
    EXPECT_EQ((unsigned char)raw[0], 0xEF);
    EXPECT_EQ((unsigned char)raw[1], 0xBB);
    EXPECT_EQ((unsigned char)raw[2], 0xBF);
}

TEST(XMLPrinterHeaderTest_314, HeaderWithBOMAndDeclaration_314) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(true, true);
    std::string result = GetPrinterOutput(printer);
    const char* raw = printer.CStr();
    EXPECT_EQ((unsigned char)raw[0], 0xEF);
    EXPECT_EQ((unsigned char)raw[1], 0xBB);
    EXPECT_EQ((unsigned char)raw[2], 0xBF);
    EXPECT_NE(result.find("<?xml"), std::string::npos);
}

TEST(XMLPrinterHeaderTest_314, HeaderNoWriteBOMNoDeclaration_314) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(false, false);
    std::string result = GetPrinterOutput(printer);
    // Should produce no output
    EXPECT_EQ(result.find("<?xml"), std::string::npos);
}

// ==========================
// CStr / CStrSize / ClearBuffer Tests
// ==========================

TEST(XMLPrinterBufferTest_314, InitialCStrIsEmpty_314) {
    XMLPrinter printer(nullptr, true);
    EXPECT_NE(printer.CStr(), nullptr);
    // CStrSize includes the null terminator
    EXPECT_GE(printer.CStrSize(), 1u);
}

TEST(XMLPrinterBufferTest_314, ClearBufferResetsContent_314) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.CloseElement();
    EXPECT_GT(printer.CStrSize(), 1u);
    printer.ClearBuffer();
    // After clear, the buffer should be empty or minimal
    std::string result = GetPrinterOutput(printer);
    EXPECT_TRUE(result.empty() || printer.CStrSize() == 1u);
}

TEST(XMLPrinterBufferTest_314, CStrSizeMatchesStringLength_314) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test");
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    // CStrSize should be strlen + 1 (for null terminator)
    EXPECT_EQ(printer.CStrSize(), result.size() + 1);
}

// ==========================
// Complex Document Tests
// ==========================

TEST(XMLPrinterComplexTest_314, FullDocumentCompact_314) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(false, true);
    printer.OpenElement("root");
    printer.PushAttribute("version", "1.0");
    printer.OpenElement("child");
    printer.PushText("content");
    printer.CloseElement();
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("<?xml"), std::string::npos);
    EXPECT_NE(result.find("<root"), std::string::npos);
    EXPECT_NE(result.find("version=\"1.0\""), std::string::npos);
    EXPECT_NE(result.find("<child>content</child>"), std::string::npos);
    EXPECT_NE(result.find("</root>"), std::string::npos);
}

TEST(XMLPrinterComplexTest_314, FullDocumentNonCompact_314) {
    XMLPrinter printer(nullptr, false);
    printer.PushHeader(false, true);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.PushText("text");
    printer.CloseElement();
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("<?xml"), std::string::npos);
    EXPECT_NE(result.find("<root>"), std::string::npos);
    EXPECT_NE(result.find("<child>"), std::string::npos);
    EXPECT_NE(result.find("text"), std::string::npos);
    // Non-compact mode should have newlines
    EXPECT_NE(result.find("\n"), std::string::npos);
}

TEST(XMLPrinterComplexTest_314, DeclarationBeforeElement_314) {
    XMLPrinter printer(nullptr, true);
    printer.PushDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
    printer.OpenElement("root");
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    size_t declPos = result.find("<?xml");
    size_t elemPos = result.find("<root");
    EXPECT_LT(declPos, elemPos);
}

TEST(XMLPrinterComplexTest_314, CommentInsideElement_314) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.PushComment("a comment");
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("<root>"), std::string::npos);
    EXPECT_NE(result.find("<!--a comment-->"), std::string::npos);
    EXPECT_NE(result.find("</root>"), std::string::npos);
}

TEST(XMLPrinterComplexTest_314, EmptyElementSelfClosing_314) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("empty");
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("<empty/>"), std::string::npos);
}

TEST(XMLPrinterComplexTest_314, ElementWithAttributeAndNoContent_314) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("key", "val");
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("key=\"val\""), std::string::npos);
    EXPECT_NE(result.find("/>"), std::string::npos);
}

// ==========================
// Visit via XMLDocument Tests
// ==========================

TEST(XMLPrinterVisitorTest_314, PrintDocumentViaVisitor_314) {
    XMLDocument doc;
    doc.Parse("<root><child>text</child></root>");
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);

    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("<root>"), std::string::npos);
    EXPECT_NE(result.find("<child>text</child>"), std::string::npos);
    EXPECT_NE(result.find("</root>"), std::string::npos);
}

TEST(XMLPrinterVisitorTest_314, PrintDocumentWithDeclaration_314) {
    XMLDocument doc;
    doc.Parse("<?xml version=\"1.0\"?><root/>");
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);

    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("<?xml version=\"1.0\"?>"), std::string::npos);
    EXPECT_NE(result.find("<root/>"), std::string::npos);
}

TEST(XMLPrinterVisitorTest_314, PrintDocumentWithComment_314) {
    XMLDocument doc;
    doc.Parse("<root><!--comment--></root>");
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);

    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("<!--comment-->"), std::string::npos);
}

TEST(XMLPrinterVisitorTest_314, PrintDocumentWithAttributes_314) {
    XMLDocument doc;
    doc.Parse("<root a=\"1\" b=\"2\"/>");
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);

    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("a=\"1\""), std::string::npos);
    EXPECT_NE(result.find("b=\"2\""), std::string::npos);
}

// ==========================
// Boundary / Edge Cases
// ==========================

TEST(XMLPrinterEdgeCaseTest_314, DeeplyNestedElements_314) {
    XMLPrinter printer(nullptr, true);
    const int depth = 50;
    for (int i = 0; i < depth; ++i) {
        printer.OpenElement("level");
    }
    for (int i = 0; i < depth; ++i) {
        printer.CloseElement();
    }
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("<level>"), std::string::npos);
    EXPECT_NE(result.find("</level>"), std::string::npos);
}

TEST(XMLPrinterEdgeCaseTest_314, TextWithSpecialCharacters_314) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText("a < b & c > d");
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    // Special characters should be escaped
    EXPECT_NE(result.find("&lt;"), std::string::npos);
    EXPECT_NE(result.find("&amp;"), std::string::npos);
    EXPECT_NE(result.find("&gt;"), std::string::npos);
}

TEST(XMLPrinterEdgeCaseTest_314, AttributeWithSpecialCharacters_314) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", "a\"b<c&d");
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("&quot;"), std::string::npos);
    EXPECT_NE(result.find("&lt;"), std::string::npos);
    EXPECT_NE(result.find("&amp;"), std::string::npos);
}

TEST(XMLPrinterEdgeCaseTest_314, ZeroIntText_314) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText(0);
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("<elem>0</elem>"), std::string::npos);
}

TEST(XMLPrinterEdgeCaseTest_314, NegativeInt64Text_314) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushText((int64_t)-9223372036854775807LL);
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("-9223372036854775807"), std::string::npos);
}

TEST(XMLPrinterEdgeCaseTest_314, EmptyElementName_314) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("");
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    // Should still produce valid XML structure even with empty name
    EXPECT_NE(result.find("<"), std::string::npos);
    EXPECT_NE(result.find(">"), std::string::npos);
}

TEST(XMLPrinterEdgeCaseTest_314, ClearAndReuse_314) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("first");
    printer.CloseElement();
    std::string first = GetPrinterOutput(printer);
    EXPECT_NE(first.find("<first/>"), std::string::npos);

    printer.ClearBuffer();
    printer.OpenElement("second");
    printer.CloseElement();
    std::string second = GetPrinterOutput(printer);
    EXPECT_NE(second.find("<second/>"), std::string::npos);
    EXPECT_EQ(second.find("<first/>"), std::string::npos);
}

TEST(XMLPrinterEdgeCaseTest_314, MixedContentInElement_314) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.PushText("before");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.PushText("after");
    printer.CloseElement();
    std::string result = GetPrinterOutput(printer);
    EXPECT_NE(result.find("before"), std::string::npos);
    EXPECT_NE(result.find("<child/>"), std::string::npos);
    EXPECT_NE(result.find("after"), std::string::npos);
}

TEST(XMLPrinterEdgeCaseTest_314, CompactModeVsNonCompactSiblings_314) {
    XMLPrinter printerCompact(nullptr, true);
    printerCompact.OpenElement("root");
    printerCompact.OpenElement("a");
    printerCompact.CloseElement();
    printerCompact.OpenElement("b");
    printerCompact.CloseElement();
    printerCompact.CloseElement();
    std::string compact = GetPrinterOutput(printerCompact);

    XMLPrinter printerNonCompact(nullptr, false);
    printerNonCompact.OpenElement("root");
    printerNonCompact.OpenElement("a");
    printerNonCompact.CloseElement();
    printerNonCompact.OpenElement("b");
    printerNonCompact.CloseElement();
    printerNonCompact.CloseElement();
    std::string nonCompact = GetPrinterOutput(printerNonCompact);

    // Non-compact should be longer (whitespace/newlines)
    EXPECT_GE(nonCompact.size(), compact.size());
}

// ==========================
// File Output Test (nullptr vs FILE*)
// ==========================

TEST(XMLPrinterFileTest_314, NullFileUsesBuffer_314) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test");
    printer.CloseElement();
    EXPECT_NE(printer.CStr(), nullptr);
    EXPECT_GT(printer.CStrSize(), 1u);
}

TEST(XMLPrinterFileTest_314, WriteToFile_314) {
    const char* filename = "test_output_314.xml";
    FILE* fp = fopen(filename, "w");
    ASSERT_NE(fp, nullptr);

    XMLPrinter printer(fp, true);
    printer.OpenElement("root");
    printer.PushText("content");
    printer.CloseElement();
    fclose(fp);

    // Read the file back and verify
    FILE* readFp = fopen(filename, "r");
    ASSERT_NE(readFp, nullptr);
    char buffer[1024] = {};
    size_t bytesRead = fread(buffer, 1, sizeof(buffer) - 1, readFp);
    fclose(readFp);
    remove(filename);

    std::string result(buffer, bytesRead);
    EXPECT_NE(result.find("<root>content</root>"), std::string::npos);
}
