#include <gtest/gtest.h>
#include <string>
#include <cstring>
#include <climits>
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for XMLPrinter tests
class XMLPrinterTest_309 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== PushText(unsigned) Tests ====================

TEST_F(XMLPrinterTest_309, PushTextUnsigned_Zero_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText((unsigned)0);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("0"), std::string::npos);
}

TEST_F(XMLPrinterTest_309, PushTextUnsigned_One_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText((unsigned)1);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("1"), std::string::npos);
}

TEST_F(XMLPrinterTest_309, PushTextUnsigned_LargeValue_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText((unsigned)4294967295u); // UINT_MAX
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("4294967295"), std::string::npos);
}

TEST_F(XMLPrinterTest_309, PushTextUnsigned_TypicalValue_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem", true);
    printer.PushText((unsigned)42);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("42"), std::string::npos);
}

TEST_F(XMLPrinterTest_309, PushTextUnsigned_InElement_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("number", true);
    printer.PushText((unsigned)12345);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<number>"), std::string::npos);
    EXPECT_NE(result.find("12345"), std::string::npos);
    EXPECT_NE(result.find("</number>"), std::string::npos);
}

// ==================== PushText(int) Tests ====================

TEST_F(XMLPrinterTest_309, PushTextInt_Positive_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText((int)100);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("100"), std::string::npos);
}

TEST_F(XMLPrinterTest_309, PushTextInt_Negative_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText((int)-100);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("-100"), std::string::npos);
}

TEST_F(XMLPrinterTest_309, PushTextInt_Zero_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText((int)0);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("0"), std::string::npos);
}

// ==================== PushText(int64_t) Tests ====================

TEST_F(XMLPrinterTest_309, PushTextInt64_LargeValue_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText((int64_t)9223372036854775807LL);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("9223372036854775807"), std::string::npos);
}

TEST_F(XMLPrinterTest_309, PushTextInt64_NegativeValue_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText((int64_t)-9223372036854775807LL);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("-9223372036854775807"), std::string::npos);
}

// ==================== PushText(uint64_t) Tests ====================

TEST_F(XMLPrinterTest_309, PushTextUint64_LargeValue_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText((uint64_t)18446744073709551615ULL);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("18446744073709551615"), std::string::npos);
}

// ==================== PushText(bool) Tests ====================

TEST_F(XMLPrinterTest_309, PushTextBool_True_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("true"), std::string::npos);
}

TEST_F(XMLPrinterTest_309, PushTextBool_False_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(false);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("false"), std::string::npos);
}

// ==================== PushText(float) Tests ====================

TEST_F(XMLPrinterTest_309, PushTextFloat_PositiveValue_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(3.14f);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

TEST_F(XMLPrinterTest_309, PushTextFloat_Zero_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(0.0f);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("0"), std::string::npos);
}

// ==================== PushText(double) Tests ====================

TEST_F(XMLPrinterTest_309, PushTextDouble_PositiveValue_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(2.718281828);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("2.718"), std::string::npos);
}

// ==================== PushText(const char*) Tests ====================

TEST_F(XMLPrinterTest_309, PushTextString_Normal_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText("hello", false);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("hello"), std::string::npos);
}

TEST_F(XMLPrinterTest_309, PushTextString_CDATA_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText("hello", true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<![CDATA[hello]]>"), std::string::npos);
}

TEST_F(XMLPrinterTest_309, PushTextString_SpecialChars_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText("<>&\"", false);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    // The special characters should be escaped
    EXPECT_NE(result.find("&lt;"), std::string::npos);
    EXPECT_NE(result.find("&gt;"), std::string::npos);
    EXPECT_NE(result.find("&amp;"), std::string::npos);
}

// ==================== OpenElement / CloseElement Tests ====================

TEST_F(XMLPrinterTest_309, OpenCloseElement_Simple_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test", true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<test/>"), std::string::npos);
}

TEST_F(XMLPrinterTest_309, OpenCloseElement_WithContent_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test", true);
    printer.PushText("content", false);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<test>"), std::string::npos);
    EXPECT_NE(result.find("content"), std::string::npos);
    EXPECT_NE(result.find("</test>"), std::string::npos);
}

TEST_F(XMLPrinterTest_309, NestedElements_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("outer", true);
    printer.OpenElement("inner", true);
    printer.CloseElement(true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<outer>"), std::string::npos);
    EXPECT_NE(result.find("<inner/>"), std::string::npos);
    EXPECT_NE(result.find("</outer>"), std::string::npos);
}

// ==================== PushAttribute Tests ====================

TEST_F(XMLPrinterTest_309, PushAttribute_String_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushAttribute("name", "value");
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("name=\"value\""), std::string::npos);
}

TEST_F(XMLPrinterTest_309, PushAttribute_Int_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushAttribute("count", 42);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("count=\"42\""), std::string::npos);
}

TEST_F(XMLPrinterTest_309, PushAttribute_Unsigned_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushAttribute("count", (unsigned)100);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("count=\"100\""), std::string::npos);
}

TEST_F(XMLPrinterTest_309, PushAttribute_Bool_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushAttribute("flag", true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("flag=\"true\""), std::string::npos);
}

TEST_F(XMLPrinterTest_309, PushAttribute_Double_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushAttribute("val", 3.14);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val=\""), std::string::npos);
}

TEST_F(XMLPrinterTest_309, PushAttribute_Int64_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushAttribute("big", (int64_t)9223372036854775807LL);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("big=\"9223372036854775807\""), std::string::npos);
}

TEST_F(XMLPrinterTest_309, PushAttribute_Uint64_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushAttribute("ubig", (uint64_t)18446744073709551615ULL);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("ubig=\"18446744073709551615\""), std::string::npos);
}

// ==================== PushHeader Tests ====================

TEST_F(XMLPrinterTest_309, PushHeader_WithDeclaration_309) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(false, true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml"), std::string::npos);
}

TEST_F(XMLPrinterTest_309, PushHeader_WithBOM_309) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(true, false);
    std::string result = printer.CStr();
    // BOM is 3 bytes: 0xEF, 0xBB, 0xBF
    EXPECT_GE(printer.CStrSize(), 3u);
}

TEST_F(XMLPrinterTest_309, PushHeader_WithBOMAndDeclaration_309) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(true, true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml"), std::string::npos);
}

// ==================== PushComment Tests ====================

TEST_F(XMLPrinterTest_309, PushComment_Simple_309) {
    XMLPrinter printer(nullptr, true);
    printer.PushComment("this is a comment");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!--this is a comment-->"), std::string::npos);
}

// ==================== PushDeclaration Tests ====================

TEST_F(XMLPrinterTest_309, PushDeclaration_Simple_309) {
    XMLPrinter printer(nullptr, true);
    printer.PushDeclaration("xml version=\"1.0\"");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml version=\"1.0\"?>"), std::string::npos);
}

// ==================== PushUnknown Tests ====================

TEST_F(XMLPrinterTest_309, PushUnknown_Simple_309) {
    XMLPrinter printer(nullptr, true);
    printer.PushUnknown("DOCTYPE html");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!DOCTYPE html>"), std::string::npos);
}

// ==================== CStr / CStrSize / ClearBuffer Tests ====================

TEST_F(XMLPrinterTest_309, CStr_EmptyPrinter_309) {
    XMLPrinter printer(nullptr, true);
    const char* str = printer.CStr();
    EXPECT_NE(str, nullptr);
}

TEST_F(XMLPrinterTest_309, CStrSize_EmptyPrinter_309) {
    XMLPrinter printer(nullptr, true);
    size_t size = printer.CStrSize();
    // Should have at least the null terminator size
    EXPECT_GE(size, 0u);
}

TEST_F(XMLPrinterTest_309, CStrSize_AfterContent_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.CloseElement(true);
    size_t size = printer.CStrSize();
    EXPECT_GT(size, 0u);
}

TEST_F(XMLPrinterTest_309, ClearBuffer_ResetsContent_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.CloseElement(true);
    size_t sizeBefore = printer.CStrSize();
    EXPECT_GT(sizeBefore, 0u);

    printer.ClearBuffer();
    // After clearing, CStr should be smaller or effectively empty
    size_t sizeAfter = printer.CStrSize();
    EXPECT_LE(sizeAfter, sizeBefore);
}

// ==================== Non-compact mode Tests ====================

TEST_F(XMLPrinterTest_309, NonCompactMode_Indentation_309) {
    XMLPrinter printer(nullptr, false);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.CloseElement();
    printer.CloseElement();
    std::string result = printer.CStr();
    // In non-compact mode, there should be newlines
    EXPECT_NE(result.find("\n"), std::string::npos);
}

TEST_F(XMLPrinterTest_309, CompactMode_NoIndentation_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.OpenElement("child", true);
    printer.CloseElement(true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root><child/></root>"), std::string::npos);
}

// ==================== Multiple PushText Tests ====================

TEST_F(XMLPrinterTest_309, PushTextUnsigned_MultipleValues_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText((unsigned)10);
    printer.CloseElement(true);

    printer.OpenElement("root2", true);
    printer.PushText((unsigned)20);
    printer.CloseElement(true);

    std::string result = printer.CStr();
    EXPECT_NE(result.find("10"), std::string::npos);
    EXPECT_NE(result.find("20"), std::string::npos);
}

// ==================== XMLDocument integration with XMLPrinter ====================

TEST_F(XMLPrinterTest_309, VisitDocument_309) {
    XMLDocument doc;
    doc.Parse("<root><child>text</child></root>");
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);

    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root>"), std::string::npos);
    EXPECT_NE(result.find("<child>"), std::string::npos);
    EXPECT_NE(result.find("text"), std::string::npos);
    EXPECT_NE(result.find("</child>"), std::string::npos);
    EXPECT_NE(result.find("</root>"), std::string::npos);
}

TEST_F(XMLPrinterTest_309, VisitDocumentWithAttributes_309) {
    XMLDocument doc;
    doc.Parse("<root attr=\"val\"/>");
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);

    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("attr=\"val\""), std::string::npos);
}

// ==================== Boundary: PushText unsigned max ====================

TEST_F(XMLPrinterTest_309, PushTextUnsigned_MaxBoundary_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("val", true);
    printer.PushText(UINT_MAX);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    // UINT_MAX is 4294967295
    EXPECT_NE(result.find("4294967295"), std::string::npos);
}

// ==================== Multiple attributes ====================

TEST_F(XMLPrinterTest_309, MultipleAttributes_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushAttribute("a", "1");
    printer.PushAttribute("b", "2");
    printer.PushAttribute("c", "3");
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("a=\"1\""), std::string::npos);
    EXPECT_NE(result.find("b=\"2\""), std::string::npos);
    EXPECT_NE(result.find("c=\"3\""), std::string::npos);
}

// ==================== Empty element self-closing ====================

TEST_F(XMLPrinterTest_309, EmptyElement_SelfClosing_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("empty", true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<empty/>"), std::string::npos);
}

// ==================== File output (FILE* = nullptr means buffer) ====================

TEST_F(XMLPrinterTest_309, NullFileUsesBuffer_309) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test", true);
    printer.PushText((unsigned)999);
    printer.CloseElement(true);
    const char* cstr = printer.CStr();
    ASSERT_NE(cstr, nullptr);
    EXPECT_GT(printer.CStrSize(), 0u);
}
