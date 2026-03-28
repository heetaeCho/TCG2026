#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include <cstdio>
#include "tinyxml2.h"

using namespace tinyxml2;

// ============================================================
// Test fixture
// ============================================================
class XMLPrinterTest_152 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ----------------------------------------------------------
// Basic construction / empty buffer
// ----------------------------------------------------------
TEST_F(XMLPrinterTest_152, DefaultConstruction_EmptyBuffer_152) {
    XMLPrinter printer;
    // freshly constructed printer should have an empty (or trivially sized) buffer
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(std::string(result), "");
    // CStrSize includes the null terminator for an empty string
    EXPECT_GE(printer.CStrSize(), 1u);
}

// ----------------------------------------------------------
// PushHeader – BOM + declaration
// ----------------------------------------------------------
TEST_F(XMLPrinterTest_152, PushHeader_WithBOMAndDeclaration_152) {
    XMLPrinter printer;
    printer.PushHeader(true, true);
    std::string out = printer.CStr();
    // BOM is 3-byte UTF-8 sequence \xEF\xBB\xBF
    EXPECT_NE(out.find("\xEF\xBB\xBF"), std::string::npos);
    EXPECT_NE(out.find("<?xml"), std::string::npos);
}

TEST_F(XMLPrinterTest_152, PushHeader_NoBOM_WithDeclaration_152) {
    XMLPrinter printer;
    printer.PushHeader(false, true);
    std::string out = printer.CStr();
    EXPECT_EQ(out.find("\xEF\xBB\xBF"), std::string::npos);
    EXPECT_NE(out.find("<?xml"), std::string::npos);
}

TEST_F(XMLPrinterTest_152, PushHeader_NoBOM_NoDeclaration_152) {
    XMLPrinter printer;
    printer.PushHeader(false, false);
    std::string out = printer.CStr();
    EXPECT_EQ(out.find("<?xml"), std::string::npos);
}

// ----------------------------------------------------------
// OpenElement / CloseElement
// ----------------------------------------------------------
TEST_F(XMLPrinterTest_152, OpenAndCloseElement_152) {
    XMLPrinter printer;
    printer.OpenElement("root");
    printer.CloseElement();
    std::string out = printer.CStr();
    EXPECT_NE(out.find("<root"), std::string::npos);
    EXPECT_NE(out.find("</root>"), std::string::npos);
}

TEST_F(XMLPrinterTest_152, OpenAndCloseElement_Compact_152) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("item", true);
    printer.CloseElement(true);
    std::string out = printer.CStr();
    // Self-closing or close tag, no extra whitespace expected
    EXPECT_NE(out.find("<item"), std::string::npos);
}

TEST_F(XMLPrinterTest_152, SelfClosingElement_NoChildren_152) {
    XMLPrinter printer;
    printer.OpenElement("empty");
    printer.CloseElement();
    std::string out = printer.CStr();
    // tinyxml2 should produce a self-closing tag for empty element: <empty/>
    EXPECT_NE(out.find("<empty/>"), std::string::npos);
}

// ----------------------------------------------------------
// Nested elements
// ----------------------------------------------------------
TEST_F(XMLPrinterTest_152, NestedElements_152) {
    XMLPrinter printer;
    printer.OpenElement("parent");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string out = printer.CStr();
    EXPECT_NE(out.find("<parent"), std::string::npos);
    EXPECT_NE(out.find("<child/>"), std::string::npos);
    EXPECT_NE(out.find("</parent>"), std::string::npos);
}

// ----------------------------------------------------------
// PushAttribute (various types)
// ----------------------------------------------------------
TEST_F(XMLPrinterTest_152, PushAttribute_String_152) {
    XMLPrinter printer;
    printer.OpenElement("tag");
    printer.PushAttribute("name", "value");
    printer.CloseElement();
    std::string out = printer.CStr();
    EXPECT_NE(out.find("name=\"value\""), std::string::npos);
}

TEST_F(XMLPrinterTest_152, PushAttribute_Int_152) {
    XMLPrinter printer;
    printer.OpenElement("tag");
    printer.PushAttribute("count", 42);
    printer.CloseElement();
    std::string out = printer.CStr();
    EXPECT_NE(out.find("count=\"42\""), std::string::npos);
}

TEST_F(XMLPrinterTest_152, PushAttribute_UnsignedInt_152) {
    XMLPrinter printer;
    printer.OpenElement("tag");
    printer.PushAttribute("val", (unsigned int)100);
    printer.CloseElement();
    std::string out = printer.CStr();
    EXPECT_NE(out.find("val=\"100\""), std::string::npos);
}

TEST_F(XMLPrinterTest_152, PushAttribute_Int64_152) {
    XMLPrinter printer;
    printer.OpenElement("tag");
    printer.PushAttribute("big", (int64_t)1234567890123LL);
    printer.CloseElement();
    std::string out = printer.CStr();
    EXPECT_NE(out.find("big=\"1234567890123\""), std::string::npos);
}

TEST_F(XMLPrinterTest_152, PushAttribute_UInt64_152) {
    XMLPrinter printer;
    printer.OpenElement("tag");
    printer.PushAttribute("ubig", (uint64_t)9876543210ULL);
    printer.CloseElement();
    std::string out = printer.CStr();
    EXPECT_NE(out.find("ubig=\"9876543210\""), std::string::npos);
}

TEST_F(XMLPrinterTest_152, PushAttribute_Bool_True_152) {
    XMLPrinter printer;
    printer.OpenElement("tag");
    printer.PushAttribute("flag", true);
    printer.CloseElement();
    std::string out = printer.CStr();
    EXPECT_NE(out.find("flag=\"true\""), std::string::npos);
}

TEST_F(XMLPrinterTest_152, PushAttribute_Bool_False_152) {
    XMLPrinter printer;
    printer.OpenElement("tag");
    printer.PushAttribute("flag", false);
    printer.CloseElement();
    std::string out = printer.CStr();
    EXPECT_NE(out.find("flag=\"false\""), std::string::npos);
}

TEST_F(XMLPrinterTest_152, PushAttribute_Double_152) {
    XMLPrinter printer;
    printer.OpenElement("tag");
    printer.PushAttribute("pi", 3.14);
    printer.CloseElement();
    std::string out = printer.CStr();
    EXPECT_NE(out.find("pi=\""), std::string::npos);
    // The value should contain "3.14" (possibly with more digits)
    EXPECT_NE(out.find("3.14"), std::string::npos);
}

// ----------------------------------------------------------
// Multiple attributes
// ----------------------------------------------------------
TEST_F(XMLPrinterTest_152, MultipleAttributes_152) {
    XMLPrinter printer;
    printer.OpenElement("tag");
    printer.PushAttribute("a", "1");
    printer.PushAttribute("b", "2");
    printer.CloseElement();
    std::string out = printer.CStr();
    EXPECT_NE(out.find("a=\"1\""), std::string::npos);
    EXPECT_NE(out.find("b=\"2\""), std::string::npos);
}

// ----------------------------------------------------------
// PushText (various types)
// ----------------------------------------------------------
TEST_F(XMLPrinterTest_152, PushText_String_152) {
    XMLPrinter printer;
    printer.OpenElement("msg");
    printer.PushText("hello");
    printer.CloseElement();
    std::string out = printer.CStr();
    EXPECT_NE(out.find("hello"), std::string::npos);
    EXPECT_NE(out.find("</msg>"), std::string::npos);
}

TEST_F(XMLPrinterTest_152, PushText_CDATA_152) {
    XMLPrinter printer;
    printer.OpenElement("msg");
    printer.PushText("data", true);
    printer.CloseElement();
    std::string out = printer.CStr();
    EXPECT_NE(out.find("<![CDATA[data]]>"), std::string::npos);
}

TEST_F(XMLPrinterTest_152, PushText_Int_152) {
    XMLPrinter printer;
    printer.OpenElement("num");
    printer.PushText(99);
    printer.CloseElement();
    std::string out = printer.CStr();
    EXPECT_NE(out.find("99"), std::string::npos);
}

TEST_F(XMLPrinterTest_152, PushText_UnsignedInt_152) {
    XMLPrinter printer;
    printer.OpenElement("num");
    printer.PushText((unsigned int)200);
    printer.CloseElement();
    std::string out = printer.CStr();
    EXPECT_NE(out.find("200"), std::string::npos);
}

TEST_F(XMLPrinterTest_152, PushText_Int64_152) {
    XMLPrinter printer;
    printer.OpenElement("num");
    printer.PushText((int64_t)-999999999999LL);
    printer.CloseElement();
    std::string out = printer.CStr();
    EXPECT_NE(out.find("-999999999999"), std::string::npos);
}

TEST_F(XMLPrinterTest_152, PushText_UInt64_152) {
    XMLPrinter printer;
    printer.OpenElement("num");
    printer.PushText((uint64_t)18446744073709551ULL);
    printer.CloseElement();
    std::string out = printer.CStr();
    EXPECT_NE(out.find("18446744073709551"), std::string::npos);
}

TEST_F(XMLPrinterTest_152, PushText_Bool_152) {
    XMLPrinter printer;
    printer.OpenElement("b");
    printer.PushText(true);
    printer.CloseElement();
    std::string out = printer.CStr();
    EXPECT_NE(out.find("true"), std::string::npos);
}

TEST_F(XMLPrinterTest_152, PushText_Float_152) {
    XMLPrinter printer;
    printer.OpenElement("f");
    printer.PushText(1.5f);
    printer.CloseElement();
    std::string out = printer.CStr();
    EXPECT_NE(out.find("1.5"), std::string::npos);
}

TEST_F(XMLPrinterTest_152, PushText_Double_152) {
    XMLPrinter printer;
    printer.OpenElement("d");
    printer.PushText(2.718);
    printer.CloseElement();
    std::string out = printer.CStr();
    EXPECT_NE(out.find("2.718"), std::string::npos);
}

// ----------------------------------------------------------
// PushComment
// ----------------------------------------------------------
TEST_F(XMLPrinterTest_152, PushComment_152) {
    XMLPrinter printer;
    printer.PushComment("this is a comment");
    std::string out = printer.CStr();
    EXPECT_NE(out.find("<!--this is a comment-->"), std::string::npos);
}

// ----------------------------------------------------------
// PushDeclaration
// ----------------------------------------------------------
TEST_F(XMLPrinterTest_152, PushDeclaration_152) {
    XMLPrinter printer;
    printer.PushDeclaration("xml version=\"1.0\"");
    std::string out = printer.CStr();
    EXPECT_NE(out.find("<?xml version=\"1.0\"?>"), std::string::npos);
}

// ----------------------------------------------------------
// PushUnknown
// ----------------------------------------------------------
TEST_F(XMLPrinterTest_152, PushUnknown_152) {
    XMLPrinter printer;
    printer.PushUnknown("!DOCTYPE html");
    std::string out = printer.CStr();
    EXPECT_NE(out.find("<!DOCTYPE html>"), std::string::npos);
}

// ----------------------------------------------------------
// ClearBuffer
// ----------------------------------------------------------
TEST_F(XMLPrinterTest_152, ClearBuffer_ResetsOutput_152) {
    XMLPrinter printer;
    printer.OpenElement("a");
    printer.CloseElement();
    EXPECT_GT(printer.CStrSize(), 1u);

    printer.ClearBuffer();
    std::string out = printer.CStr();
    EXPECT_EQ(out, "");
}

TEST_F(XMLPrinterTest_152, ClearBuffer_AllowsReuse_152) {
    XMLPrinter printer;
    printer.OpenElement("first");
    printer.CloseElement();
    printer.ClearBuffer();

    printer.OpenElement("second");
    printer.CloseElement();
    std::string out = printer.CStr();
    EXPECT_NE(out.find("<second/>"), std::string::npos);
    EXPECT_EQ(out.find("first"), std::string::npos);
}

// ----------------------------------------------------------
// CStrSize
// ----------------------------------------------------------
TEST_F(XMLPrinterTest_152, CStrSize_MatchesStringLength_152) {
    XMLPrinter printer;
    printer.OpenElement("test");
    printer.CloseElement();
    const char* s = printer.CStr();
    // CStrSize should equal strlen + 1 (null terminator)
    EXPECT_EQ(printer.CStrSize(), strlen(s) + 1);
}

// ----------------------------------------------------------
// Compact mode via constructor
// ----------------------------------------------------------
TEST_F(XMLPrinterTest_152, CompactMode_NoWhitespace_152) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.PushText("text");
    printer.CloseElement();
    printer.CloseElement();
    std::string out = printer.CStr();
    // In compact mode there should be no newlines between tags
    EXPECT_EQ(out.find('\n'), std::string::npos);
}

TEST_F(XMLPrinterTest_152, NonCompactMode_HasFormatting_152) {
    XMLPrinter printer(nullptr, false);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string out = printer.CStr();
    // In non-compact mode we expect newlines
    EXPECT_NE(out.find('\n'), std::string::npos);
}

// ----------------------------------------------------------
// Entity escaping in text
// ----------------------------------------------------------
TEST_F(XMLPrinterTest_152, TextWithSpecialChars_Escaped_152) {
    XMLPrinter printer;
    printer.OpenElement("e");
    printer.PushText("<>&\"");
    printer.CloseElement();
    std::string out = printer.CStr();
    EXPECT_NE(out.find("&lt;"), std::string::npos);
    EXPECT_NE(out.find("&gt;"), std::string::npos);
    EXPECT_NE(out.find("&amp;"), std::string::npos);
}

// ----------------------------------------------------------
// Entity escaping in attribute values
// ----------------------------------------------------------
TEST_F(XMLPrinterTest_152, AttributeWithSpecialChars_Escaped_152) {
    XMLPrinter printer;
    printer.OpenElement("e");
    printer.PushAttribute("val", "<>&\"");
    printer.CloseElement();
    std::string out = printer.CStr();
    EXPECT_NE(out.find("&lt;"), std::string::npos);
    EXPECT_NE(out.find("&amp;"), std::string::npos);
}

// ----------------------------------------------------------
// Visitor interface: parse and print round-trip
// ----------------------------------------------------------
TEST_F(XMLPrinterTest_152, VisitorRoundTrip_152) {
    const char* xml = "<root><child attr=\"1\">text</child></root>";
    XMLDocument doc;
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string out = printer.CStr();
    EXPECT_NE(out.find("<root>"), std::string::npos);
    EXPECT_NE(out.find("<child"), std::string::npos);
    EXPECT_NE(out.find("attr=\"1\""), std::string::npos);
    EXPECT_NE(out.find("text"), std::string::npos);
    EXPECT_NE(out.find("</child>"), std::string::npos);
    EXPECT_NE(out.find("</root>"), std::string::npos);
}

// ----------------------------------------------------------
// Visitor with comment node
// ----------------------------------------------------------
TEST_F(XMLPrinterTest_152, VisitorWithComment_152) {
    const char* xml = "<!--hello--><root/>";
    XMLDocument doc;
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string out = printer.CStr();
    EXPECT_NE(out.find("<!--hello-->"), std::string::npos);
}

// ----------------------------------------------------------
// Visitor with declaration
// ----------------------------------------------------------
TEST_F(XMLPrinterTest_152, VisitorWithDeclaration_152) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    XMLDocument doc;
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string out = printer.CStr();
    EXPECT_NE(out.find("<?xml"), std::string::npos);
}

// ----------------------------------------------------------
// Visitor with unknown
// ----------------------------------------------------------
TEST_F(XMLPrinterTest_152, VisitorWithUnknown_152) {
    const char* xml = "<!DOCTYPE html><root/>";
    XMLDocument doc;
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string out = printer.CStr();
    EXPECT_NE(out.find("<!DOCTYPE html>"), std::string::npos);
}

// ----------------------------------------------------------
// Writing to FILE*
// ----------------------------------------------------------
TEST_F(XMLPrinterTest_152, WriteToFile_152) {
    const char* filename = "xmlprinter_test_152.xml";
    FILE* fp = fopen(filename, "w");
    ASSERT_NE(fp, nullptr);

    XMLPrinter printer(fp, true);
    printer.OpenElement("root");
    printer.PushAttribute("id", 1);
    printer.PushText("content");
    printer.CloseElement();
    fclose(fp);

    // Read the file back
    fp = fopen(filename, "r");
    ASSERT_NE(fp, nullptr);
    char buffer[1024] = {};
    size_t n = fread(buffer, 1, sizeof(buffer) - 1, fp);
    fclose(fp);
    remove(filename);

    std::string out(buffer, n);
    EXPECT_NE(out.find("<root"), std::string::npos);
    EXPECT_NE(out.find("id=\"1\""), std::string::npos);
    EXPECT_NE(out.find("content"), std::string::npos);
    EXPECT_NE(out.find("</root>"), std::string::npos);
}

// ----------------------------------------------------------
// PushText negative int
// ----------------------------------------------------------
TEST_F(XMLPrinterTest_152, PushText_NegativeInt_152) {
    XMLPrinter printer;
    printer.OpenElement("n");
    printer.PushText(-42);
    printer.CloseElement();
    std::string out = printer.CStr();
    EXPECT_NE(out.find("-42"), std::string::npos);
}

// ----------------------------------------------------------
// PushAttribute negative int
// ----------------------------------------------------------
TEST_F(XMLPrinterTest_152, PushAttribute_NegativeInt_152) {
    XMLPrinter printer;
    printer.OpenElement("n");
    printer.PushAttribute("val", -7);
    printer.CloseElement();
    std::string out = printer.CStr();
    EXPECT_NE(out.find("val=\"-7\""), std::string::npos);
}

// ----------------------------------------------------------
// Empty element name
// ----------------------------------------------------------
TEST_F(XMLPrinterTest_152, EmptyElementName_152) {
    XMLPrinter printer;
    printer.OpenElement("");
    printer.CloseElement();
    std::string out = printer.CStr();
    // Should still produce well-formed-ish tags
    EXPECT_NE(out.find("<"), std::string::npos);
}

// ----------------------------------------------------------
// Deeply nested elements
// ----------------------------------------------------------
TEST_F(XMLPrinterTest_152, DeeplyNestedElements_152) {
    XMLPrinter printer(nullptr, true);
    const int depth = 50;
    for (int i = 0; i < depth; ++i) {
        printer.OpenElement("level");
    }
    for (int i = 0; i < depth; ++i) {
        printer.CloseElement(true);
    }
    std::string out = printer.CStr();
    // Count occurrences of "<level"
    size_t count = 0;
    size_t pos = 0;
    while ((pos = out.find("<level", pos)) != std::string::npos) {
        ++count;
        pos += 6;
    }
    // Some may be self-closing at inner levels, but we have 50 opens
    // The innermost should be self-closing, the rest need close tags
    EXPECT_GE(count, 1u);
}

// ----------------------------------------------------------
// PushText with empty string
// ----------------------------------------------------------
TEST_F(XMLPrinterTest_152, PushText_EmptyString_152) {
    XMLPrinter printer;
    printer.OpenElement("e");
    printer.PushText("");
    printer.CloseElement();
    std::string out = printer.CStr();
    EXPECT_NE(out.find("<e>"), std::string::npos);
    EXPECT_NE(out.find("</e>"), std::string::npos);
}

// ----------------------------------------------------------
// ClearBuffer then CStrSize
// ----------------------------------------------------------
TEST_F(XMLPrinterTest_152, ClearBuffer_CStrSizeIsMinimal_152) {
    XMLPrinter printer;
    printer.OpenElement("something");
    printer.CloseElement();
    printer.ClearBuffer();
    // After clearing, CStrSize should represent empty string (just null terminator)
    EXPECT_LE(printer.CStrSize(), 1u);
}

// ----------------------------------------------------------
// PushComment with empty string
// ----------------------------------------------------------
TEST_F(XMLPrinterTest_152, PushComment_Empty_152) {
    XMLPrinter printer;
    printer.PushComment("");
    std::string out = printer.CStr();
    EXPECT_NE(out.find("<!---->"), std::string::npos);
}

// ----------------------------------------------------------
// Multiple elements at same level
// ----------------------------------------------------------
TEST_F(XMLPrinterTest_152, MultipleSiblingElements_152) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.OpenElement("a");
    printer.CloseElement(true);
    printer.OpenElement("b");
    printer.CloseElement(true);
    printer.OpenElement("c");
    printer.CloseElement(true);
    printer.CloseElement(true);
    std::string out = printer.CStr();
    EXPECT_NE(out.find("<a/>"), std::string::npos);
    EXPECT_NE(out.find("<b/>"), std::string::npos);
    EXPECT_NE(out.find("<c/>"), std::string::npos);
}

// ----------------------------------------------------------
// PushHeader then element
// ----------------------------------------------------------
TEST_F(XMLPrinterTest_152, HeaderThenElement_152) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(false, true);
    printer.OpenElement("root");
    printer.CloseElement(true);
    std::string out = printer.CStr();
    // Declaration should come before the root element
    size_t declPos = out.find("<?xml");
    size_t rootPos = out.find("<root");
    ASSERT_NE(declPos, std::string::npos);
    ASSERT_NE(rootPos, std::string::npos);
    EXPECT_LT(declPos, rootPos);
}

// ----------------------------------------------------------
// Visitor returns correct values
// ----------------------------------------------------------
TEST_F(XMLPrinterTest_152, VisitEnterDocument_ReturnsTrue_152) {
    XMLDocument doc;
    doc.Parse("<r/>");
    XMLPrinter printer;
    EXPECT_TRUE(printer.VisitEnter(doc));
}

TEST_F(XMLPrinterTest_152, VisitExitDocument_ReturnsTrue_152) {
    XMLDocument doc;
    doc.Parse("<r/>");
    XMLPrinter printer;
    EXPECT_TRUE(printer.VisitExit(doc));
}

// ----------------------------------------------------------
// PushText zero values
// ----------------------------------------------------------
TEST_F(XMLPrinterTest_152, PushText_ZeroInt_152) {
    XMLPrinter printer;
    printer.OpenElement("z");
    printer.PushText(0);
    printer.CloseElement();
    std::string out = printer.CStr();
    EXPECT_NE(out.find(">0<"), std::string::npos);
}

TEST_F(XMLPrinterTest_152, PushText_ZeroDouble_152) {
    XMLPrinter printer;
    printer.OpenElement("z");
    printer.PushText(0.0);
    printer.CloseElement();
    std::string out = printer.CStr();
    EXPECT_NE(out.find("0"), std::string::npos);
}

// ----------------------------------------------------------
// Attribute value with single quote (apostrophe)
// ----------------------------------------------------------
TEST_F(XMLPrinterTest_152, AttributeWithApostrophe_152) {
    XMLPrinter printer;
    printer.OpenElement("e");
    printer.PushAttribute("val", "it's");
    printer.CloseElement();
    std::string out = printer.CStr();
    // The attribute should be properly rendered
    EXPECT_NE(out.find("val="), std::string::npos);
}

// ----------------------------------------------------------
// Large text content
// ----------------------------------------------------------
TEST_F(XMLPrinterTest_152, LargeTextContent_152) {
    XMLPrinter printer(nullptr, true);
    std::string largeText(10000, 'A');
    printer.OpenElement("big");
    printer.PushText(largeText.c_str());
    printer.CloseElement(true);
    std::string out = printer.CStr();
    EXPECT_NE(out.find(largeText), std::string::npos);
}
