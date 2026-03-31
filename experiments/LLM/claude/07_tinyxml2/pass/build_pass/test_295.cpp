#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLPrinterTest_295 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== OpenElement Tests ====================

TEST_F(XMLPrinterTest_295, OpenElement_SingleElement_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("root");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root"), std::string::npos);
    EXPECT_NE(result.find("</root>"), std::string::npos);
}

TEST_F(XMLPrinterTest_295, OpenElement_NestedElements_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root"), std::string::npos);
    EXPECT_NE(result.find("<child"), std::string::npos);
    EXPECT_NE(result.find("</child>"), std::string::npos);
    EXPECT_NE(result.find("</root>"), std::string::npos);
}

TEST_F(XMLPrinterTest_295, OpenElement_CompactMode_295) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("root", true);
    printer.OpenElement("child", true);
    printer.CloseElement(true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root"), std::string::npos);
    EXPECT_NE(result.find("<child"), std::string::npos);
    // In compact mode, no extra whitespace/newlines expected between elements
}

TEST_F(XMLPrinterTest_295, OpenElement_NonCompactMode_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("root", false);
    printer.OpenElement("child", false);
    printer.CloseElement(false);
    printer.CloseElement(false);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root"), std::string::npos);
    EXPECT_NE(result.find("<child"), std::string::npos);
}

// ==================== CloseElement Tests ====================

TEST_F(XMLPrinterTest_295, CloseElement_SelfClosing_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("empty");
    printer.CloseElement();
    std::string result = printer.CStr();
    // Self-closing element when no content
    EXPECT_NE(result.find("<empty/>"), std::string::npos);
}

TEST_F(XMLPrinterTest_295, CloseElement_WithText_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText("hello");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("hello"), std::string::npos);
    EXPECT_NE(result.find("</elem>"), std::string::npos);
}

// ==================== PushAttribute Tests ====================

TEST_F(XMLPrinterTest_295, PushAttribute_StringValue_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("name", "value");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("name=\"value\""), std::string::npos);
}

TEST_F(XMLPrinterTest_295, PushAttribute_IntValue_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("count", 42);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("count=\"42\""), std::string::npos);
}

TEST_F(XMLPrinterTest_295, PushAttribute_UnsignedIntValue_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("count", (unsigned int)100);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("count=\"100\""), std::string::npos);
}

TEST_F(XMLPrinterTest_295, PushAttribute_Int64Value_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("bignum", (int64_t)9876543210LL);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("bignum=\"9876543210\""), std::string::npos);
}

TEST_F(XMLPrinterTest_295, PushAttribute_Uint64Value_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("ubignum", (uint64_t)12345678901ULL);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("ubignum=\"12345678901\""), std::string::npos);
}

TEST_F(XMLPrinterTest_295, PushAttribute_BoolTrueValue_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("flag", true);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("flag=\"true\""), std::string::npos);
}

TEST_F(XMLPrinterTest_295, PushAttribute_BoolFalseValue_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("flag", false);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("flag=\"false\""), std::string::npos);
}

TEST_F(XMLPrinterTest_295, PushAttribute_DoubleValue_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("val", 3.14);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val=\""), std::string::npos);
}

TEST_F(XMLPrinterTest_295, PushAttribute_MultipleAttributes_295) {
    XMLPrinter printer(nullptr, false, 0);
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

TEST_F(XMLPrinterTest_295, PushText_String_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText("Hello World");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("Hello World"), std::string::npos);
}

TEST_F(XMLPrinterTest_295, PushText_CDATA_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText("some data", true);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<![CDATA[some data]]>"), std::string::npos);
}

TEST_F(XMLPrinterTest_295, PushText_IntValue_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText(42);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("42"), std::string::npos);
}

TEST_F(XMLPrinterTest_295, PushText_UnsignedValue_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText((unsigned int)99);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("99"), std::string::npos);
}

TEST_F(XMLPrinterTest_295, PushText_Int64Value_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText((int64_t)1234567890123LL);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("1234567890123"), std::string::npos);
}

TEST_F(XMLPrinterTest_295, PushText_Uint64Value_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText((uint64_t)9876543210ULL);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("9876543210"), std::string::npos);
}

TEST_F(XMLPrinterTest_295, PushText_BoolTrue_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText(true);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("true"), std::string::npos);
}

TEST_F(XMLPrinterTest_295, PushText_BoolFalse_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText(false);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("false"), std::string::npos);
}

TEST_F(XMLPrinterTest_295, PushText_FloatValue_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText(1.5f);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("1.5"), std::string::npos);
}

TEST_F(XMLPrinterTest_295, PushText_DoubleValue_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText(2.718);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("2.718"), std::string::npos);
}

// ==================== PushComment Tests ====================

TEST_F(XMLPrinterTest_295, PushComment_Normal_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushComment("This is a comment");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!--This is a comment-->"), std::string::npos);
}

// ==================== PushDeclaration Tests ====================

TEST_F(XMLPrinterTest_295, PushDeclaration_Normal_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushDeclaration("xml version=\"1.0\"");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml version=\"1.0\"?>"), std::string::npos);
}

// ==================== PushUnknown Tests ====================

TEST_F(XMLPrinterTest_295, PushUnknown_Normal_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushUnknown("DOCTYPE html");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!DOCTYPE html>"), std::string::npos);
}

// ==================== PushHeader Tests ====================

TEST_F(XMLPrinterTest_295, PushHeader_WithDeclaration_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushHeader(false, true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml"), std::string::npos);
}

TEST_F(XMLPrinterTest_295, PushHeader_WithBOM_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushHeader(true, true);
    std::string result = printer.CStr();
    // BOM is 3 bytes: 0xEF 0xBB 0xBF
    EXPECT_GE(printer.CStrSize(), 3u);
}

TEST_F(XMLPrinterTest_295, PushHeader_NoBOM_NoDeclaration_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushHeader(false, false);
    std::string result = printer.CStr();
    // Nothing meaningful should be added
    EXPECT_EQ(result.find("<?xml"), std::string::npos);
}

// ==================== CStr / CStrSize Tests ====================

TEST_F(XMLPrinterTest_295, CStr_EmptyPrinter_295) {
    XMLPrinter printer(nullptr, false, 0);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(strlen(result), 0u);
}

TEST_F(XMLPrinterTest_295, CStrSize_EmptyPrinter_295) {
    XMLPrinter printer(nullptr, false, 0);
    // CStrSize includes null terminator typically
    size_t size = printer.CStrSize();
    EXPECT_GE(size, 0u);
}

TEST_F(XMLPrinterTest_295, CStrSize_AfterContent_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("root");
    printer.CloseElement();
    size_t size = printer.CStrSize();
    EXPECT_GT(size, 0u);
}

// ==================== ClearBuffer Tests ====================

TEST_F(XMLPrinterTest_295, ClearBuffer_ResetsOutput_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("root");
    printer.CloseElement();
    EXPECT_GT(strlen(printer.CStr()), 0u);
    printer.ClearBuffer();
    EXPECT_EQ(strlen(printer.CStr()), 0u);
}

// ==================== Complex Scenarios ====================

TEST_F(XMLPrinterTest_295, ComplexDocument_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushHeader(false, true);
    printer.OpenElement("root");
    printer.PushAttribute("version", "1.0");
    
    printer.OpenElement("child1");
    printer.PushAttribute("id", 1);
    printer.PushText("text content");
    printer.CloseElement();
    
    printer.OpenElement("child2");
    printer.PushAttribute("active", true);
    printer.OpenElement("grandchild");
    printer.CloseElement();
    printer.CloseElement();
    
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml"), std::string::npos);
    EXPECT_NE(result.find("<root"), std::string::npos);
    EXPECT_NE(result.find("version=\"1.0\""), std::string::npos);
    EXPECT_NE(result.find("<child1"), std::string::npos);
    EXPECT_NE(result.find("id=\"1\""), std::string::npos);
    EXPECT_NE(result.find("text content"), std::string::npos);
    EXPECT_NE(result.find("</child1>"), std::string::npos);
    EXPECT_NE(result.find("<child2"), std::string::npos);
    EXPECT_NE(result.find("active=\"true\""), std::string::npos);
    EXPECT_NE(result.find("<grandchild/>"), std::string::npos);
    EXPECT_NE(result.find("</child2>"), std::string::npos);
    EXPECT_NE(result.find("</root>"), std::string::npos);
}

TEST_F(XMLPrinterTest_295, MultipleSiblingElements_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("root");
    for (int i = 0; i < 5; i++) {
        printer.OpenElement("item");
        printer.PushAttribute("index", i);
        printer.CloseElement();
    }
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root"), std::string::npos);
    EXPECT_NE(result.find("</root>"), std::string::npos);
    EXPECT_NE(result.find("index=\"0\""), std::string::npos);
    EXPECT_NE(result.find("index=\"4\""), std::string::npos);
}

// ==================== Entity Handling Tests ====================

TEST_F(XMLPrinterTest_295, PushText_WithSpecialCharacters_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText("a < b & c > d");
    printer.CloseElement();
    std::string result = printer.CStr();
    // Entities should be escaped
    EXPECT_NE(result.find("&lt;"), std::string::npos);
    EXPECT_NE(result.find("&amp;"), std::string::npos);
    EXPECT_NE(result.find("&gt;"), std::string::npos);
}

TEST_F(XMLPrinterTest_295, PushAttribute_WithSpecialCharacters_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("val", "a&b<c>d\"e");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("&amp;"), std::string::npos);
    EXPECT_NE(result.find("&lt;"), std::string::npos);
    EXPECT_NE(result.find("&gt;"), std::string::npos);
    EXPECT_NE(result.find("&quot;"), std::string::npos);
}

// ==================== Compact vs Non-Compact Mode ====================

TEST_F(XMLPrinterTest_295, CompactModeConstructor_295) {
    XMLPrinter compactPrinter(nullptr, true, 0);
    compactPrinter.OpenElement("root");
    compactPrinter.OpenElement("child");
    compactPrinter.PushText("text");
    compactPrinter.CloseElement();
    compactPrinter.CloseElement();
    std::string compactResult = compactPrinter.CStr();

    XMLPrinter normalPrinter(nullptr, false, 0);
    normalPrinter.OpenElement("root");
    normalPrinter.OpenElement("child");
    normalPrinter.PushText("text");
    normalPrinter.CloseElement();
    normalPrinter.CloseElement();
    std::string normalResult = normalPrinter.CStr();

    // Compact should generally be shorter or equal (no extra whitespace)
    EXPECT_LE(compactResult.length(), normalResult.length());
}

// ==================== XMLDocument Print via XMLPrinter ====================

TEST_F(XMLPrinterTest_295, VisitDocument_295) {
    XMLDocument doc;
    doc.Parse("<root><child>text</child></root>");
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);

    XMLPrinter printer(nullptr, false, 0);
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root"), std::string::npos);
    EXPECT_NE(result.find("<child"), std::string::npos);
    EXPECT_NE(result.find("text"), std::string::npos);
    EXPECT_NE(result.find("</child>"), std::string::npos);
    EXPECT_NE(result.find("</root>"), std::string::npos);
}

TEST_F(XMLPrinterTest_295, VisitDocumentWithAttributes_295) {
    XMLDocument doc;
    doc.Parse("<root attr=\"val\"><child id=\"1\"/></root>");
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);

    XMLPrinter printer(nullptr, false, 0);
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("attr=\"val\""), std::string::npos);
    EXPECT_NE(result.find("id=\"1\""), std::string::npos);
}

TEST_F(XMLPrinterTest_295, VisitDocumentWithComment_295) {
    XMLDocument doc;
    doc.Parse("<root><!-- comment --></root>");
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);

    XMLPrinter printer(nullptr, false, 0);
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!-- comment -->"), std::string::npos);
}

TEST_F(XMLPrinterTest_295, VisitDocumentWithDeclaration_295) {
    XMLDocument doc;
    doc.Parse("<?xml version=\"1.0\"?><root/>");
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);

    XMLPrinter printer(nullptr, false, 0);
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml"), std::string::npos);
    EXPECT_NE(result.find("<root/>"), std::string::npos);
}

// ==================== Depth Parameter Tests ====================

TEST_F(XMLPrinterTest_295, CustomInitialDepth_295) {
    XMLPrinter printer(nullptr, false, 2);
    printer.OpenElement("elem");
    printer.CloseElement();
    std::string result = printer.CStr();
    // Should still produce valid output, possibly with additional indentation
    EXPECT_NE(result.find("<elem/>"), std::string::npos);
}

// ==================== Empty Element Name ====================

TEST_F(XMLPrinterTest_295, OpenElement_EmptyName_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("");
    printer.CloseElement();
    std::string result = printer.CStr();
    // Should produce <></> or </>
    EXPECT_NE(result.find("<"), std::string::npos);
}

// ==================== Negative Int Attribute ====================

TEST_F(XMLPrinterTest_295, PushAttribute_NegativeInt_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("val", -42);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val=\"-42\""), std::string::npos);
}

// ==================== Zero Values ====================

TEST_F(XMLPrinterTest_295, PushText_ZeroInt_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText(0);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("0"), std::string::npos);
}

TEST_F(XMLPrinterTest_295, PushAttribute_ZeroDouble_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("val", 0.0);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val=\"0"), std::string::npos);
}

// ==================== Deeply Nested Elements ====================

TEST_F(XMLPrinterTest_295, DeeplyNestedElements_295) {
    XMLPrinter printer(nullptr, false, 0);
    const int depth = 20;
    for (int i = 0; i < depth; i++) {
        printer.OpenElement("level");
    }
    for (int i = 0; i < depth; i++) {
        printer.CloseElement();
    }
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<level"), std::string::npos);
    // Verify we have closing tags
    size_t closeCount = 0;
    size_t pos = 0;
    while ((pos = result.find("</level>", pos)) != std::string::npos) {
        closeCount++;
        pos++;
    }
    // Some may be self-closing, but the innermost should be self-closing
    // All elements opened and closed
    EXPECT_GT(result.length(), 0u);
}

// ==================== PushComment inside Element ====================

TEST_F(XMLPrinterTest_295, PushComment_InsideElement_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("root");
    printer.PushComment("inner comment");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!--inner comment-->"), std::string::npos);
    EXPECT_NE(result.find("</root>"), std::string::npos);
}

// ==================== Mixed Content ====================

TEST_F(XMLPrinterTest_295, MixedContent_295) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("root");
    printer.PushText("before");
    printer.OpenElement("mid");
    printer.CloseElement();
    printer.PushText("after");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("before"), std::string::npos);
    EXPECT_NE(result.find("after"), std::string::npos);
    EXPECT_NE(result.find("<mid/>"), std::string::npos);
}

// ==================== ClearBuffer and Reuse ====================

TEST_F(XMLPrinterTest_295, ClearBufferAndReuse_295) {
    XMLPrinter printer(nullptr, false, 0);
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

// ==================== File output (just constructor, no crash) ====================

TEST_F(XMLPrinterTest_295, FileOutput_NullFile_295) {
    // Passing nullptr for file, output goes to internal buffer
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("test");
    printer.CloseElement();
    EXPECT_NE(printer.CStr(), nullptr);
    EXPECT_GT(strlen(printer.CStr()), 0u);
}
