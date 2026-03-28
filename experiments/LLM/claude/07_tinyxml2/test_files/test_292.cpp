#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>
#include <string>
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for XMLPrinter tests
class XMLPrinterTest_292 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// === Putc Tests ===

TEST_F(XMLPrinterTest_292, PutcSingleCharToBuffer_292) {
    XMLPrinter printer(nullptr, false, 0);
    printer.ClearBuffer();
    printer.Putc('A');
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result[0], 'A');
    EXPECT_EQ(result[1], '\0');
}

TEST_F(XMLPrinterTest_292, PutcMultipleCharsToBuffer_292) {
    XMLPrinter printer(nullptr, false, 0);
    printer.ClearBuffer();
    printer.Putc('H');
    printer.Putc('i');
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Hi");
}

TEST_F(XMLPrinterTest_292, PutcNullCharToBuffer_292) {
    XMLPrinter printer(nullptr, false, 0);
    printer.ClearBuffer();
    printer.Putc('A');
    printer.Putc('\0');
    // After putting 'A' and then '\0', the CStr should return "A" 
    // because the null terminator from Putc('\0') would end the string
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result[0], 'A');
}

TEST_F(XMLPrinterTest_292, PutcSpecialCharsToBuffer_292) {
    XMLPrinter printer(nullptr, false, 0);
    printer.ClearBuffer();
    printer.Putc('\n');
    printer.Putc('\t');
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result[0], '\n');
    EXPECT_EQ(result[1], '\t');
    EXPECT_EQ(result[2], '\0');
}

TEST_F(XMLPrinterTest_292, PutcToFile_292) {
    FILE* fp = tmpfile();
    ASSERT_NE(fp, nullptr);
    {
        XMLPrinter printer(fp, false, 0);
        printer.Putc('X');
        printer.Putc('Y');
    }
    fflush(fp);
    rewind(fp);
    char buf[10] = {};
    size_t read = fread(buf, 1, sizeof(buf) - 1, fp);
    fclose(fp);
    EXPECT_GE(read, 2u);
    // The file output includes the default XML header potentially; 
    // but Putc directly writes 'X' and 'Y'
    std::string content(buf, read);
    EXPECT_NE(content.find('X'), std::string::npos);
    EXPECT_NE(content.find('Y'), std::string::npos);
}

// === CStr and CStrSize Tests ===

TEST_F(XMLPrinterTest_292, CStrReturnsEmptyOnFreshPrinter_292) {
    XMLPrinter printer(nullptr, false, 0);
    printer.ClearBuffer();
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

TEST_F(XMLPrinterTest_292, CStrSizeAfterClearBuffer_292) {
    XMLPrinter printer(nullptr, false, 0);
    printer.ClearBuffer();
    // Size should be at least 1 for the null terminator
    EXPECT_GE(printer.CStrSize(), 1u);
}

// === ClearBuffer Tests ===

TEST_F(XMLPrinterTest_292, ClearBufferResetsContent_292) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("test");
    printer.CloseElement();
    const char* before = printer.CStr();
    ASSERT_NE(before, nullptr);
    EXPECT_GT(strlen(before), 0u);

    printer.ClearBuffer();
    const char* after = printer.CStr();
    ASSERT_NE(after, nullptr);
    EXPECT_STREQ(after, "");
}

// === OpenElement / CloseElement Tests ===

TEST_F(XMLPrinterTest_292, OpenAndCloseElement_292) {
    XMLPrinter printer(nullptr, false, 0);
    printer.ClearBuffer();
    printer.OpenElement("root");
    printer.CloseElement();
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    std::string s(result);
    EXPECT_NE(s.find("<root"), std::string::npos);
    EXPECT_NE(s.find("</root>"), std::string::npos);
}

TEST_F(XMLPrinterTest_292, OpenAndCloseElementCompact_292) {
    XMLPrinter printer(nullptr, true, 0);
    printer.ClearBuffer();
    printer.OpenElement("item", true);
    printer.CloseElement(true);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    std::string s(result);
    EXPECT_NE(s.find("<item"), std::string::npos);
}

TEST_F(XMLPrinterTest_292, SelfClosingElement_292) {
    XMLPrinter printer(nullptr, true, 0);
    printer.ClearBuffer();
    printer.OpenElement("empty", true);
    printer.CloseElement(true);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    std::string s(result);
    // Should be self-closing since no children/text added
    EXPECT_NE(s.find("/>"), std::string::npos);
}

// === PushAttribute Tests ===

TEST_F(XMLPrinterTest_292, PushAttributeString_292) {
    XMLPrinter printer(nullptr, true, 0);
    printer.ClearBuffer();
    printer.OpenElement("elem", true);
    printer.PushAttribute("name", "value");
    printer.CloseElement(true);
    const char* result = printer.CStr();
    std::string s(result);
    EXPECT_NE(s.find("name=\"value\""), std::string::npos);
}

TEST_F(XMLPrinterTest_292, PushAttributeInt_292) {
    XMLPrinter printer(nullptr, true, 0);
    printer.ClearBuffer();
    printer.OpenElement("elem", true);
    printer.PushAttribute("count", 42);
    printer.CloseElement(true);
    const char* result = printer.CStr();
    std::string s(result);
    EXPECT_NE(s.find("count=\"42\""), std::string::npos);
}

TEST_F(XMLPrinterTest_292, PushAttributeUnsignedInt_292) {
    XMLPrinter printer(nullptr, true, 0);
    printer.ClearBuffer();
    printer.OpenElement("elem", true);
    printer.PushAttribute("val", (unsigned int)100);
    printer.CloseElement(true);
    const char* result = printer.CStr();
    std::string s(result);
    EXPECT_NE(s.find("val=\"100\""), std::string::npos);
}

TEST_F(XMLPrinterTest_292, PushAttributeInt64_292) {
    XMLPrinter printer(nullptr, true, 0);
    printer.ClearBuffer();
    printer.OpenElement("elem", true);
    printer.PushAttribute("big", (int64_t)1234567890123LL);
    printer.CloseElement(true);
    const char* result = printer.CStr();
    std::string s(result);
    EXPECT_NE(s.find("big=\"1234567890123\""), std::string::npos);
}

TEST_F(XMLPrinterTest_292, PushAttributeUInt64_292) {
    XMLPrinter printer(nullptr, true, 0);
    printer.ClearBuffer();
    printer.OpenElement("elem", true);
    printer.PushAttribute("ubig", (uint64_t)9876543210ULL);
    printer.CloseElement(true);
    const char* result = printer.CStr();
    std::string s(result);
    EXPECT_NE(s.find("ubig=\"9876543210\""), std::string::npos);
}

TEST_F(XMLPrinterTest_292, PushAttributeBool_292) {
    XMLPrinter printer(nullptr, true, 0);
    printer.ClearBuffer();
    printer.OpenElement("elem", true);
    printer.PushAttribute("flag", true);
    printer.CloseElement(true);
    const char* result = printer.CStr();
    std::string s(result);
    EXPECT_NE(s.find("flag=\"true\""), std::string::npos);
}

TEST_F(XMLPrinterTest_292, PushAttributeBoolFalse_292) {
    XMLPrinter printer(nullptr, true, 0);
    printer.ClearBuffer();
    printer.OpenElement("elem", true);
    printer.PushAttribute("flag", false);
    printer.CloseElement(true);
    const char* result = printer.CStr();
    std::string s(result);
    EXPECT_NE(s.find("flag=\"false\""), std::string::npos);
}

TEST_F(XMLPrinterTest_292, PushAttributeDouble_292) {
    XMLPrinter printer(nullptr, true, 0);
    printer.ClearBuffer();
    printer.OpenElement("elem", true);
    printer.PushAttribute("pi", 3.14);
    printer.CloseElement(true);
    const char* result = printer.CStr();
    std::string s(result);
    EXPECT_NE(s.find("pi="), std::string::npos);
    EXPECT_NE(s.find("3.14"), std::string::npos);
}

// === PushText Tests ===

TEST_F(XMLPrinterTest_292, PushTextString_292) {
    XMLPrinter printer(nullptr, true, 0);
    printer.ClearBuffer();
    printer.OpenElement("msg", true);
    printer.PushText("Hello World");
    printer.CloseElement(true);
    const char* result = printer.CStr();
    std::string s(result);
    EXPECT_NE(s.find("Hello World"), std::string::npos);
}

TEST_F(XMLPrinterTest_292, PushTextCDATA_292) {
    XMLPrinter printer(nullptr, true, 0);
    printer.ClearBuffer();
    printer.OpenElement("data", true);
    printer.PushText("some <data>", true);
    printer.CloseElement(true);
    const char* result = printer.CStr();
    std::string s(result);
    EXPECT_NE(s.find("<![CDATA["), std::string::npos);
    EXPECT_NE(s.find("]]>"), std::string::npos);
}

TEST_F(XMLPrinterTest_292, PushTextInt_292) {
    XMLPrinter printer(nullptr, true, 0);
    printer.ClearBuffer();
    printer.OpenElement("num", true);
    printer.PushText(99);
    printer.CloseElement(true);
    const char* result = printer.CStr();
    std::string s(result);
    EXPECT_NE(s.find("99"), std::string::npos);
}

TEST_F(XMLPrinterTest_292, PushTextUnsigned_292) {
    XMLPrinter printer(nullptr, true, 0);
    printer.ClearBuffer();
    printer.OpenElement("num", true);
    printer.PushText((unsigned)200);
    printer.CloseElement(true);
    const char* result = printer.CStr();
    std::string s(result);
    EXPECT_NE(s.find("200"), std::string::npos);
}

TEST_F(XMLPrinterTest_292, PushTextInt64_292) {
    XMLPrinter printer(nullptr, true, 0);
    printer.ClearBuffer();
    printer.OpenElement("num", true);
    printer.PushText((int64_t)123456789012LL);
    printer.CloseElement(true);
    const char* result = printer.CStr();
    std::string s(result);
    EXPECT_NE(s.find("123456789012"), std::string::npos);
}

TEST_F(XMLPrinterTest_292, PushTextUInt64_292) {
    XMLPrinter printer(nullptr, true, 0);
    printer.ClearBuffer();
    printer.OpenElement("num", true);
    printer.PushText((uint64_t)999999999999ULL);
    printer.CloseElement(true);
    const char* result = printer.CStr();
    std::string s(result);
    EXPECT_NE(s.find("999999999999"), std::string::npos);
}

TEST_F(XMLPrinterTest_292, PushTextBoolTrue_292) {
    XMLPrinter printer(nullptr, true, 0);
    printer.ClearBuffer();
    printer.OpenElement("b", true);
    printer.PushText(true);
    printer.CloseElement(true);
    const char* result = printer.CStr();
    std::string s(result);
    EXPECT_NE(s.find("true"), std::string::npos);
}

TEST_F(XMLPrinterTest_292, PushTextBoolFalse_292) {
    XMLPrinter printer(nullptr, true, 0);
    printer.ClearBuffer();
    printer.OpenElement("b", true);
    printer.PushText(false);
    printer.CloseElement(true);
    const char* result = printer.CStr();
    std::string s(result);
    EXPECT_NE(s.find("false"), std::string::npos);
}

TEST_F(XMLPrinterTest_292, PushTextFloat_292) {
    XMLPrinter printer(nullptr, true, 0);
    printer.ClearBuffer();
    printer.OpenElement("f", true);
    printer.PushText(1.5f);
    printer.CloseElement(true);
    const char* result = printer.CStr();
    std::string s(result);
    EXPECT_NE(s.find("1.5"), std::string::npos);
}

TEST_F(XMLPrinterTest_292, PushTextDouble_292) {
    XMLPrinter printer(nullptr, true, 0);
    printer.ClearBuffer();
    printer.OpenElement("d", true);
    printer.PushText(2.718);
    printer.CloseElement(true);
    const char* result = printer.CStr();
    std::string s(result);
    EXPECT_NE(s.find("2.718"), std::string::npos);
}

// === PushComment Tests ===

TEST_F(XMLPrinterTest_292, PushComment_292) {
    XMLPrinter printer(nullptr, true, 0);
    printer.ClearBuffer();
    printer.PushComment("This is a comment");
    const char* result = printer.CStr();
    std::string s(result);
    EXPECT_NE(s.find("<!--"), std::string::npos);
    EXPECT_NE(s.find("This is a comment"), std::string::npos);
    EXPECT_NE(s.find("-->"), std::string::npos);
}

// === PushDeclaration Tests ===

TEST_F(XMLPrinterTest_292, PushDeclaration_292) {
    XMLPrinter printer(nullptr, true, 0);
    printer.ClearBuffer();
    printer.PushDeclaration("xml version=\"1.0\"");
    const char* result = printer.CStr();
    std::string s(result);
    EXPECT_NE(s.find("<?"), std::string::npos);
    EXPECT_NE(s.find("?>"), std::string::npos);
    EXPECT_NE(s.find("xml version=\"1.0\""), std::string::npos);
}

// === PushUnknown Tests ===

TEST_F(XMLPrinterTest_292, PushUnknown_292) {
    XMLPrinter printer(nullptr, true, 0);
    printer.ClearBuffer();
    printer.PushUnknown("DOCTYPE html");
    const char* result = printer.CStr();
    std::string s(result);
    EXPECT_NE(s.find("<!"), std::string::npos);
    EXPECT_NE(s.find("DOCTYPE html"), std::string::npos);
    EXPECT_NE(s.find(">"), std::string::npos);
}

// === PushHeader Tests ===

TEST_F(XMLPrinterTest_292, PushHeaderWithDeclaration_292) {
    XMLPrinter printer(nullptr, true, 0);
    printer.ClearBuffer();
    printer.PushHeader(false, true);
    const char* result = printer.CStr();
    std::string s(result);
    EXPECT_NE(s.find("<?xml"), std::string::npos);
}

TEST_F(XMLPrinterTest_292, PushHeaderWithBOM_292) {
    XMLPrinter printer(nullptr, true, 0);
    printer.ClearBuffer();
    printer.PushHeader(true, false);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    // BOM is 0xEF, 0xBB, 0xBF
    EXPECT_EQ((unsigned char)result[0], 0xEF);
    EXPECT_EQ((unsigned char)result[1], 0xBB);
    EXPECT_EQ((unsigned char)result[2], 0xBF);
}

TEST_F(XMLPrinterTest_292, PushHeaderNoDeclarationNoBOM_292) {
    XMLPrinter printer(nullptr, true, 0);
    printer.ClearBuffer();
    printer.PushHeader(false, false);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

// === Nested Elements Tests ===

TEST_F(XMLPrinterTest_292, NestedElements_292) {
    XMLPrinter printer(nullptr, true, 0);
    printer.ClearBuffer();
    printer.OpenElement("parent", true);
    printer.OpenElement("child", true);
    printer.PushText("text");
    printer.CloseElement(true);
    printer.CloseElement(true);
    const char* result = printer.CStr();
    std::string s(result);
    EXPECT_NE(s.find("<parent>"), std::string::npos);
    EXPECT_NE(s.find("<child>"), std::string::npos);
    EXPECT_NE(s.find("text"), std::string::npos);
    EXPECT_NE(s.find("</child>"), std::string::npos);
    EXPECT_NE(s.find("</parent>"), std::string::npos);
}

// === XMLDocument Printing through Visitor ===

TEST_F(XMLPrinterTest_292, VisitDocumentRoundTrip_292) {
    const char* xml = "<root><child attr=\"val\">Hello</child></root>";
    XMLDocument doc;
    doc.Parse(xml);
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);

    XMLPrinter printer(nullptr, true, 0);
    doc.Accept(&printer);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    std::string s(result);
    EXPECT_NE(s.find("<root>"), std::string::npos);
    EXPECT_NE(s.find("<child"), std::string::npos);
    EXPECT_NE(s.find("attr=\"val\""), std::string::npos);
    EXPECT_NE(s.find("Hello"), std::string::npos);
    EXPECT_NE(s.find("</child>"), std::string::npos);
    EXPECT_NE(s.find("</root>"), std::string::npos);
}

TEST_F(XMLPrinterTest_292, VisitDocumentWithComment_292) {
    const char* xml = "<!-- comment --><root/>";
    XMLDocument doc;
    doc.Parse(xml);
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);

    XMLPrinter printer(nullptr, true, 0);
    doc.Accept(&printer);
    const char* result = printer.CStr();
    std::string s(result);
    EXPECT_NE(s.find("<!-- comment -->"), std::string::npos);
    EXPECT_NE(s.find("<root/>"), std::string::npos);
}

TEST_F(XMLPrinterTest_292, VisitDocumentWithDeclaration_292) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    XMLDocument doc;
    doc.Parse(xml);
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);

    XMLPrinter printer(nullptr, true, 0);
    doc.Accept(&printer);
    const char* result = printer.CStr();
    std::string s(result);
    EXPECT_NE(s.find("<?xml"), std::string::npos);
    EXPECT_NE(s.find("<root/>"), std::string::npos);
}

// === File Output Tests ===

TEST_F(XMLPrinterTest_292, PrintToFile_292) {
    FILE* fp = tmpfile();
    ASSERT_NE(fp, nullptr);
    {
        XMLPrinter printer(fp, true, 0);
        printer.OpenElement("test", true);
        printer.PushText("data");
        printer.CloseElement(true);
    }
    fflush(fp);
    rewind(fp);
    char buf[256] = {};
    size_t read = fread(buf, 1, sizeof(buf) - 1, fp);
    fclose(fp);
    EXPECT_GT(read, 0u);
    std::string s(buf, read);
    EXPECT_NE(s.find("<test>"), std::string::npos);
    EXPECT_NE(s.find("data"), std::string::npos);
    EXPECT_NE(s.find("</test>"), std::string::npos);
}

// === CStr with file printer should return null or empty ===

TEST_F(XMLPrinterTest_292, CStrWithFileReturnsNullOrEmpty_292) {
    FILE* fp = tmpfile();
    ASSERT_NE(fp, nullptr);
    XMLPrinter printer(fp, true, 0);
    printer.OpenElement("x", true);
    printer.CloseElement(true);
    // When writing to file, CStr should not contain the output
    // (it goes to file, not buffer)
    const char* result = printer.CStr();
    if (result != nullptr) {
        EXPECT_EQ(strlen(result), 0u);
    }
    fclose(fp);
}

// === Multiple elements at same level ===

TEST_F(XMLPrinterTest_292, MultipleElementsSameLevel_292) {
    XMLPrinter printer(nullptr, true, 0);
    printer.ClearBuffer();
    printer.OpenElement("a", true);
    printer.CloseElement(true);
    printer.OpenElement("b", true);
    printer.CloseElement(true);
    const char* result = printer.CStr();
    std::string s(result);
    EXPECT_NE(s.find("<a/>"), std::string::npos);
    EXPECT_NE(s.find("<b/>"), std::string::npos);
}

// === Element with multiple attributes ===

TEST_F(XMLPrinterTest_292, ElementWithMultipleAttributes_292) {
    XMLPrinter printer(nullptr, true, 0);
    printer.ClearBuffer();
    printer.OpenElement("e", true);
    printer.PushAttribute("a", "1");
    printer.PushAttribute("b", "2");
    printer.PushAttribute("c", "3");
    printer.CloseElement(true);
    const char* result = printer.CStr();
    std::string s(result);
    EXPECT_NE(s.find("a=\"1\""), std::string::npos);
    EXPECT_NE(s.find("b=\"2\""), std::string::npos);
    EXPECT_NE(s.find("c=\"3\""), std::string::npos);
}

// === Boundary: empty element name ===

TEST_F(XMLPrinterTest_292, EmptyTextPush_292) {
    XMLPrinter printer(nullptr, true, 0);
    printer.ClearBuffer();
    printer.OpenElement("e", true);
    printer.PushText("");
    printer.CloseElement(true);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    std::string s(result);
    EXPECT_NE(s.find("<e>"), std::string::npos);
    EXPECT_NE(s.find("</e>"), std::string::npos);
}

// === Putc with many characters (boundary: exceed initial buffer) ===

TEST_F(XMLPrinterTest_292, PutcManyCharsExceedsInitialBuffer_292) {
    XMLPrinter printer(nullptr, false, 0);
    printer.ClearBuffer();
    const int count = 100;
    for (int i = 0; i < count; ++i) {
        printer.Putc('A');
    }
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(strlen(result), (size_t)count);
    for (int i = 0; i < count; ++i) {
        EXPECT_EQ(result[i], 'A');
    }
}

// === Non-compact mode with depth ===

TEST_F(XMLPrinterTest_292, NonCompactModeProducesWhitespace_292) {
    XMLPrinter printer(nullptr, false, 0);
    printer.ClearBuffer();
    printer.OpenElement("parent");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    const char* result = printer.CStr();
    std::string s(result);
    // In non-compact mode, there should be newlines or indentation
    EXPECT_NE(s.find("\n"), std::string::npos);
}

// === Negative int text ===

TEST_F(XMLPrinterTest_292, PushTextNegativeInt_292) {
    XMLPrinter printer(nullptr, true, 0);
    printer.ClearBuffer();
    printer.OpenElement("n", true);
    printer.PushText(-42);
    printer.CloseElement(true);
    const char* result = printer.CStr();
    std::string s(result);
    EXPECT_NE(s.find("-42"), std::string::npos);
}

// === Zero values ===

TEST_F(XMLPrinterTest_292, PushTextZeroInt_292) {
    XMLPrinter printer(nullptr, true, 0);
    printer.ClearBuffer();
    printer.OpenElement("z", true);
    printer.PushText(0);
    printer.CloseElement(true);
    const char* result = printer.CStr();
    std::string s(result);
    EXPECT_NE(s.find(">0<"), std::string::npos);
}

// === Special XML characters in text ===

TEST_F(XMLPrinterTest_292, PushTextWithSpecialXMLChars_292) {
    XMLPrinter printer(nullptr, true, 0);
    printer.ClearBuffer();
    printer.OpenElement("e", true);
    printer.PushText("a < b & c > d");
    printer.CloseElement(true);
    const char* result = printer.CStr();
    std::string s(result);
    // Should have entity-escaped the special characters
    EXPECT_NE(s.find("&lt;"), std::string::npos);
    EXPECT_NE(s.find("&amp;"), std::string::npos);
    EXPECT_NE(s.find("&gt;"), std::string::npos);
}

// === PushAttribute with special characters ===

TEST_F(XMLPrinterTest_292, PushAttributeWithSpecialChars_292) {
    XMLPrinter printer(nullptr, true, 0);
    printer.ClearBuffer();
    printer.OpenElement("e", true);
    printer.PushAttribute("val", "a&b<c>d\"e");
    printer.CloseElement(true);
    const char* result = printer.CStr();
    std::string s(result);
    EXPECT_NE(s.find("&amp;"), std::string::npos);
    EXPECT_NE(s.find("&lt;"), std::string::npos);
    EXPECT_NE(s.find("&gt;"), std::string::npos);
    EXPECT_NE(s.find("&quot;"), std::string::npos);
}

// === CStrSize reflects content ===

TEST_F(XMLPrinterTest_292, CStrSizeReflectsContent_292) {
    XMLPrinter printer(nullptr, true, 0);
    printer.ClearBuffer();
    printer.OpenElement("root", true);
    printer.CloseElement(true);
    const char* result = printer.CStr();
    size_t len = strlen(result);
    // CStrSize includes null terminator
    EXPECT_EQ(printer.CStrSize(), len + 1);
}
