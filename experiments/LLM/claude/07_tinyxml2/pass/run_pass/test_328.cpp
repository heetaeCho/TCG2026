#include <gtest/gtest.h>
#include "tinyxml2.h"
#include <cstring>
#include <string>
#include <cstdio>

using namespace tinyxml2;

// Helper to get printer output as string
class XMLPrinterTest_328 : public ::testing::Test {
protected:
    // Utility: create a printer writing to internal buffer (no file)
    // and return CStr() after operations
};

// =============================================================================
// Constructor tests
// =============================================================================

TEST_F(XMLPrinterTest_328, DefaultConstructor_NullFile_328) {
    XMLPrinter printer(nullptr, false, 0);
    // Should produce an empty buffer (just null terminator)
    ASSERT_NE(printer.CStr(), nullptr);
    EXPECT_STREQ(printer.CStr(), "");
    EXPECT_EQ(printer.CStrSize(), 1u); // null terminator
}

TEST_F(XMLPrinterTest_328, ConstructorCompactMode_328) {
    XMLPrinter printer(nullptr, true, 0);
    ASSERT_NE(printer.CStr(), nullptr);
    EXPECT_STREQ(printer.CStr(), "");
}

TEST_F(XMLPrinterTest_328, ConstructorWithDepth_328) {
    XMLPrinter printer(nullptr, false, 5);
    printer.OpenElement("test");
    printer.CloseElement();
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    // Should have indentation based on depth=5
    EXPECT_TRUE(std::string(result).find("test") != std::string::npos);
}

// =============================================================================
// OpenElement / CloseElement tests
// =============================================================================

TEST_F(XMLPrinterTest_328, OpenAndCloseElement_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("root");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("<root/>") != std::string::npos ||
                result.find("<root />") != std::string::npos);
}

TEST_F(XMLPrinterTest_328, NestedElements_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("parent");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("<parent>") != std::string::npos);
    EXPECT_TRUE(result.find("<child/>") != std::string::npos ||
                result.find("<child />") != std::string::npos);
    EXPECT_TRUE(result.find("</parent>") != std::string::npos);
}

TEST_F(XMLPrinterTest_328, NestedElementsCompactMode_328) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("parent", true);
    printer.OpenElement("child", true);
    printer.CloseElement(true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    // In compact mode, no extra whitespace
    EXPECT_TRUE(result.find("<parent>") != std::string::npos);
    EXPECT_TRUE(result.find("</parent>") != std::string::npos);
}

TEST_F(XMLPrinterTest_328, MultipleTopLevelElements_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("first");
    printer.CloseElement();
    printer.OpenElement("second");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("first") != std::string::npos);
    EXPECT_TRUE(result.find("second") != std::string::npos);
}

// =============================================================================
// PushAttribute tests
// =============================================================================

TEST_F(XMLPrinterTest_328, PushAttributeString_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("name", "value");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("name=\"value\"") != std::string::npos);
}

TEST_F(XMLPrinterTest_328, PushAttributeInt_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("count", 42);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("count=\"42\"") != std::string::npos);
}

TEST_F(XMLPrinterTest_328, PushAttributeUnsignedInt_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("val", (unsigned)100);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("val=\"100\"") != std::string::npos);
}

TEST_F(XMLPrinterTest_328, PushAttributeInt64_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("bignum", (int64_t)1234567890123LL);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("bignum=\"1234567890123\"") != std::string::npos);
}

TEST_F(XMLPrinterTest_328, PushAttributeUint64_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("ubignum", (uint64_t)9876543210ULL);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("ubignum=\"9876543210\"") != std::string::npos);
}

TEST_F(XMLPrinterTest_328, PushAttributeBoolTrue_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("flag", true);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("flag=\"true\"") != std::string::npos);
}

TEST_F(XMLPrinterTest_328, PushAttributeBoolFalse_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("flag", false);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("flag=\"false\"") != std::string::npos);
}

TEST_F(XMLPrinterTest_328, PushAttributeDouble_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("pi", 3.14);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("pi=") != std::string::npos);
    EXPECT_TRUE(result.find("3.14") != std::string::npos);
}

TEST_F(XMLPrinterTest_328, MultipleAttributes_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("a", "1");
    printer.PushAttribute("b", "2");
    printer.PushAttribute("c", "3");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("a=\"1\"") != std::string::npos);
    EXPECT_TRUE(result.find("b=\"2\"") != std::string::npos);
    EXPECT_TRUE(result.find("c=\"3\"") != std::string::npos);
}

// =============================================================================
// PushText tests
// =============================================================================

TEST_F(XMLPrinterTest_328, PushTextString_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText("Hello World");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("Hello World") != std::string::npos);
    EXPECT_TRUE(result.find("</elem>") != std::string::npos);
}

TEST_F(XMLPrinterTest_328, PushTextCData_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText("some data", true);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("<![CDATA[some data]]>") != std::string::npos);
}

TEST_F(XMLPrinterTest_328, PushTextInt_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText(42);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("42") != std::string::npos);
}

TEST_F(XMLPrinterTest_328, PushTextUnsigned_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText((unsigned)99);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("99") != std::string::npos);
}

TEST_F(XMLPrinterTest_328, PushTextInt64_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText((int64_t)123456789012345LL);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("123456789012345") != std::string::npos);
}

TEST_F(XMLPrinterTest_328, PushTextUint64_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText((uint64_t)9876543210ULL);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("9876543210") != std::string::npos);
}

TEST_F(XMLPrinterTest_328, PushTextBoolTrue_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText(true);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("true") != std::string::npos);
}

TEST_F(XMLPrinterTest_328, PushTextBoolFalse_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText(false);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("false") != std::string::npos);
}

TEST_F(XMLPrinterTest_328, PushTextFloat_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText(1.5f);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("1.5") != std::string::npos);
}

TEST_F(XMLPrinterTest_328, PushTextDouble_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText(2.718);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("2.718") != std::string::npos);
}

// =============================================================================
// PushComment tests
// =============================================================================

TEST_F(XMLPrinterTest_328, PushComment_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushComment("This is a comment");
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("<!--This is a comment-->") != std::string::npos);
}

TEST_F(XMLPrinterTest_328, PushCommentInsideElement_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("root");
    printer.PushComment("inner comment");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("<!--inner comment-->") != std::string::npos);
    EXPECT_TRUE(result.find("</root>") != std::string::npos);
}

// =============================================================================
// PushDeclaration tests
// =============================================================================

TEST_F(XMLPrinterTest_328, PushDeclaration_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushDeclaration("xml version=\"1.0\"");
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("<?xml version=\"1.0\"?>") != std::string::npos);
}

// =============================================================================
// PushUnknown tests
// =============================================================================

TEST_F(XMLPrinterTest_328, PushUnknown_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushUnknown("DOCTYPE html");
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("<!DOCTYPE html>") != std::string::npos);
}

// =============================================================================
// PushHeader tests
// =============================================================================

TEST_F(XMLPrinterTest_328, PushHeaderWithBOMAndDeclaration_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushHeader(true, true);
    std::string result = printer.CStr();
    // BOM: EF BB BF
    EXPECT_TRUE(result.size() >= 3);
    EXPECT_EQ((unsigned char)result[0], 0xEF);
    EXPECT_EQ((unsigned char)result[1], 0xBB);
    EXPECT_EQ((unsigned char)result[2], 0xBF);
    EXPECT_TRUE(result.find("<?xml") != std::string::npos);
}

TEST_F(XMLPrinterTest_328, PushHeaderNoBOMWithDeclaration_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushHeader(false, true);
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("<?xml") != std::string::npos);
    // No BOM
    if (result.size() >= 3) {
        bool hasBOM = ((unsigned char)result[0] == 0xEF &&
                       (unsigned char)result[1] == 0xBB &&
                       (unsigned char)result[2] == 0xBF);
        EXPECT_FALSE(hasBOM);
    }
}

TEST_F(XMLPrinterTest_328, PushHeaderNoBOMNoDeclaration_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushHeader(false, false);
    std::string result = printer.CStr();
    EXPECT_STREQ(result.c_str(), "");
}

// =============================================================================
// CStr / CStrSize tests
// =============================================================================

TEST_F(XMLPrinterTest_328, CStrSizeReflectsContent_328) {
    XMLPrinter printer(nullptr, false, 0);
    EXPECT_EQ(printer.CStrSize(), 1u); // just null terminator
    printer.OpenElement("x");
    printer.CloseElement();
    EXPECT_GT(printer.CStrSize(), 1u);
    // CStrSize should include the null terminator
    EXPECT_EQ(printer.CStrSize(), strlen(printer.CStr()) + 1);
}

// =============================================================================
// ClearBuffer tests
// =============================================================================

TEST_F(XMLPrinterTest_328, ClearBufferResetsContent_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("test");
    printer.CloseElement();
    EXPECT_GT(printer.CStrSize(), 1u);
    printer.ClearBuffer();
    EXPECT_EQ(printer.CStrSize(), 1u);
    EXPECT_STREQ(printer.CStr(), "");
}

TEST_F(XMLPrinterTest_328, ClearBufferAndReuse_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("first");
    printer.CloseElement();
    printer.ClearBuffer();
    printer.OpenElement("second");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("first") == std::string::npos);
    EXPECT_TRUE(result.find("second") != std::string::npos);
}

// =============================================================================
// Entity escaping tests
// =============================================================================

TEST_F(XMLPrinterTest_328, EntityEscapingInText_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText("a < b & c > d");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("&lt;") != std::string::npos);
    EXPECT_TRUE(result.find("&amp;") != std::string::npos);
    EXPECT_TRUE(result.find("&gt;") != std::string::npos);
}

TEST_F(XMLPrinterTest_328, EntityEscapingInAttributeValue_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("attr", "a&b<c>d\"e");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("&amp;") != std::string::npos);
    EXPECT_TRUE(result.find("&lt;") != std::string::npos);
    EXPECT_TRUE(result.find("&gt;") != std::string::npos);
    EXPECT_TRUE(result.find("&quot;") != std::string::npos);
}

// =============================================================================
// EscapeAposCharsInAttributes tests
// =============================================================================

TEST_F(XMLPrinterTest_328, EscapeAposInAttributes_328) {
    XMLPrinter printer(nullptr, false, 0, XMLPrinter::ESCAPE_APOS_CHARS_IN_ATTRIBUTES);
    printer.OpenElement("elem");
    printer.PushAttribute("attr", "it's");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("&apos;") != std::string::npos);
}

TEST_F(XMLPrinterTest_328, DontEscapeAposInAttributes_328) {
    XMLPrinter printer(nullptr, false, 0, XMLPrinter::DONT_ESCAPE_APOS_CHARS_IN_ATTRIBUTES);
    printer.OpenElement("elem");
    printer.PushAttribute("attr", "it's");
    printer.CloseElement();
    std::string result = printer.CStr();
    // Apostrophe should NOT be escaped
    EXPECT_TRUE(result.find("&apos;") == std::string::npos);
    EXPECT_TRUE(result.find("it's") != std::string::npos);
}

// =============================================================================
// XMLDocument integration via Visitor pattern
// =============================================================================

TEST_F(XMLPrinterTest_328, VisitEnterExitDocument_328) {
    XMLDocument doc;
    doc.Parse("<root><child>text</child></root>");
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer(nullptr, false, 0);
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("<root>") != std::string::npos);
    EXPECT_TRUE(result.find("<child>") != std::string::npos);
    EXPECT_TRUE(result.find("text") != std::string::npos);
    EXPECT_TRUE(result.find("</child>") != std::string::npos);
    EXPECT_TRUE(result.find("</root>") != std::string::npos);
}

TEST_F(XMLPrinterTest_328, VisitDocumentWithAttributes_328) {
    XMLDocument doc;
    doc.Parse("<root attr=\"val\"><child id=\"1\"/></root>");
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer(nullptr, false, 0);
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("attr=\"val\"") != std::string::npos);
    EXPECT_TRUE(result.find("id=\"1\"") != std::string::npos);
}

TEST_F(XMLPrinterTest_328, VisitDocumentWithComment_328) {
    XMLDocument doc;
    doc.Parse("<root><!-- a comment --></root>");
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer(nullptr, false, 0);
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("<!-- a comment -->") != std::string::npos ||
                result.find("<!--a comment-->") != std::string::npos);
}

TEST_F(XMLPrinterTest_328, VisitDocumentWithDeclaration_328) {
    XMLDocument doc;
    doc.Parse("<?xml version=\"1.0\"?><root/>");
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer(nullptr, false, 0);
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("<?xml") != std::string::npos);
    EXPECT_TRUE(result.find("root") != std::string::npos);
}

// =============================================================================
// File output test
// =============================================================================

TEST_F(XMLPrinterTest_328, PrintToFile_328) {
    const char* filename = "test_printer_output_328.xml";
    FILE* fp = fopen(filename, "w");
    ASSERT_NE(fp, nullptr);

    XMLPrinter printer(fp, false, 0);
    printer.OpenElement("root");
    printer.PushAttribute("id", 1);
    printer.PushText("content");
    printer.CloseElement();
    fclose(fp);

    // Read back and verify
    FILE* readFp = fopen(filename, "r");
    ASSERT_NE(readFp, nullptr);
    char buf[1024] = {};
    size_t bytesRead = fread(buf, 1, sizeof(buf) - 1, readFp);
    fclose(readFp);
    remove(filename);

    EXPECT_GT(bytesRead, 0u);
    std::string result(buf);
    EXPECT_TRUE(result.find("<root") != std::string::npos);
    EXPECT_TRUE(result.find("id=\"1\"") != std::string::npos);
    EXPECT_TRUE(result.find("content") != std::string::npos);
    EXPECT_TRUE(result.find("</root>") != std::string::npos);
}

// =============================================================================
// Edge cases
// =============================================================================

TEST_F(XMLPrinterTest_328, EmptyElementName_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("");
    printer.CloseElement();
    std::string result = printer.CStr();
    // Should still produce valid-ish XML tags
    EXPECT_TRUE(result.find("<") != std::string::npos);
    EXPECT_TRUE(result.find(">") != std::string::npos);
}

TEST_F(XMLPrinterTest_328, EmptyText_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText("");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("<elem>") != std::string::npos);
    EXPECT_TRUE(result.find("</elem>") != std::string::npos);
}

TEST_F(XMLPrinterTest_328, EmptyComment_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.PushComment("");
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("<!---->") != std::string::npos);
}

TEST_F(XMLPrinterTest_328, NegativeIntAttribute_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("neg", -42);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("neg=\"-42\"") != std::string::npos);
}

TEST_F(XMLPrinterTest_328, NegativeIntText_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText(-100);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("-100") != std::string::npos);
}

TEST_F(XMLPrinterTest_328, ZeroDepthIndentation_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("<root>") != std::string::npos);
}

TEST_F(XMLPrinterTest_328, DeeplyNestedElements_328) {
    XMLPrinter printer(nullptr, false, 0);
    for (int i = 0; i < 10; ++i) {
        printer.OpenElement("level");
    }
    for (int i = 0; i < 10; ++i) {
        printer.CloseElement();
    }
    std::string result = printer.CStr();
    // Count opening tags
    size_t count = 0;
    size_t pos = 0;
    while ((pos = result.find("<level>", pos)) != std::string::npos) {
        ++count;
        ++pos;
    }
    // The innermost should be self-closing, rest should have opening/closing
    EXPECT_GE(count, 9u); // at least 9 opening <level> tags
}

TEST_F(XMLPrinterTest_328, SelfClosingEmptyElement_328) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("empty", true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    // Should be self-closing since no content
    EXPECT_TRUE(result.find("<empty/>") != std::string::npos ||
                result.find("<empty />") != std::string::npos);
}

TEST_F(XMLPrinterTest_328, RoundTripThroughDocument_328) {
    const char* xml = "<root><a x=\"1\">hello</a><b/></root>";
    XMLDocument doc;
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer(nullptr, true, 0);
    doc.Accept(&printer);

    XMLDocument doc2;
    doc2.Parse(printer.CStr());
    ASSERT_FALSE(doc2.Error());

    XMLPrinter printer2(nullptr, true, 0);
    doc2.Accept(&printer2);

    EXPECT_STREQ(printer.CStr(), printer2.CStr());
}

TEST_F(XMLPrinterTest_328, PushTextZeroValues_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushText(0);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("0") != std::string::npos);
}

TEST_F(XMLPrinterTest_328, PushAttributeEmptyStringValue_328) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("elem");
    printer.PushAttribute("key", "");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("key=\"\"") != std::string::npos);
}
