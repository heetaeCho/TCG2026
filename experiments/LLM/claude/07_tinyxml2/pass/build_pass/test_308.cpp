#include <gtest/gtest.h>
#include "tinyxml2.h"
#include <string>
#include <cstring>
#include <climits>

using namespace tinyxml2;

class XMLPrinterTest_308 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test PushText with a positive integer value
TEST_F(XMLPrinterTest_308, PushTextInt_PositiveValue_308) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(42);
    printer.CloseElement(true);
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("42"), std::string::npos);
}

// Test PushText with zero
TEST_F(XMLPrinterTest_308, PushTextInt_ZeroValue_308) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(0);
    printer.CloseElement(true);
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("0"), std::string::npos);
}

// Test PushText with a negative integer value
TEST_F(XMLPrinterTest_308, PushTextInt_NegativeValue_308) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(-123);
    printer.CloseElement(true);
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("-123"), std::string::npos);
}

// Test PushText with INT_MAX
TEST_F(XMLPrinterTest_308, PushTextInt_MaxInt_308) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(INT_MAX);
    printer.CloseElement(true);
    
    std::string result = printer.CStr();
    std::string expected = std::to_string(INT_MAX);
    EXPECT_NE(result.find(expected), std::string::npos);
}

// Test PushText with INT_MIN
TEST_F(XMLPrinterTest_308, PushTextInt_MinInt_308) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(INT_MIN);
    printer.CloseElement(true);
    
    std::string result = printer.CStr();
    std::string expected = std::to_string(INT_MIN);
    EXPECT_NE(result.find(expected), std::string::npos);
}

// Test PushText with int value 1
TEST_F(XMLPrinterTest_308, PushTextInt_One_308) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(1);
    printer.CloseElement(true);
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("1"), std::string::npos);
}

// Test PushText with int value -1
TEST_F(XMLPrinterTest_308, PushTextInt_NegativeOne_308) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(-1);
    printer.CloseElement(true);
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("-1"), std::string::npos);
}

// Test PushText int generates proper XML within an element
TEST_F(XMLPrinterTest_308, PushTextInt_InsideElement_308) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("value", true);
    printer.PushText(999);
    printer.CloseElement(true);
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<value>"), std::string::npos);
    EXPECT_NE(result.find("999"), std::string::npos);
    EXPECT_NE(result.find("</value>"), std::string::npos);
}

// Test PushText with multiple int values sequentially
TEST_F(XMLPrinterTest_308, PushTextInt_MultipleValues_308) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("a", true);
    printer.PushText(10);
    printer.CloseElement(true);
    printer.OpenElement("b", true);
    printer.PushText(20);
    printer.CloseElement(true);
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("10"), std::string::npos);
    EXPECT_NE(result.find("20"), std::string::npos);
}

// Test PushText with large positive number
TEST_F(XMLPrinterTest_308, PushTextInt_LargePositive_308) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("num", true);
    printer.PushText(1000000);
    printer.CloseElement(true);
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("1000000"), std::string::npos);
}

// Test PushText unsigned int
TEST_F(XMLPrinterTest_308, PushTextUnsignedInt_308) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText((unsigned int)42);
    printer.CloseElement(true);
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("42"), std::string::npos);
}

// Test PushText bool true
TEST_F(XMLPrinterTest_308, PushTextBool_True_308) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(true);
    printer.CloseElement(true);
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("true"), std::string::npos);
}

// Test PushText bool false
TEST_F(XMLPrinterTest_308, PushTextBool_False_308) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(false);
    printer.CloseElement(true);
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("false"), std::string::npos);
}

// Test PushText float
TEST_F(XMLPrinterTest_308, PushTextFloat_308) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(3.14f);
    printer.CloseElement(true);
    
    std::string result = printer.CStr();
    // Should contain some representation of 3.14
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

// Test PushText double
TEST_F(XMLPrinterTest_308, PushTextDouble_308) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(2.71828);
    printer.CloseElement(true);
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("2.71828"), std::string::npos);
}

// Test PushText int64_t
TEST_F(XMLPrinterTest_308, PushTextInt64_308) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText((int64_t)1234567890123LL);
    printer.CloseElement(true);
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("1234567890123"), std::string::npos);
}

// Test PushText uint64_t
TEST_F(XMLPrinterTest_308, PushTextUint64_308) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText((uint64_t)9876543210ULL);
    printer.CloseElement(true);
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("9876543210"), std::string::npos);
}

// Test PushText string (cdata false)
TEST_F(XMLPrinterTest_308, PushTextString_308) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText("hello world", false);
    printer.CloseElement(true);
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("hello world"), std::string::npos);
}

// Test PushText string (cdata true)
TEST_F(XMLPrinterTest_308, PushTextStringCData_308) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText("hello world", true);
    printer.CloseElement(true);
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("CDATA"), std::string::npos);
    EXPECT_NE(result.find("hello world"), std::string::npos);
}

// Test CStr returns non-null
TEST_F(XMLPrinterTest_308, CStr_ReturnsNonNull_308) {
    XMLPrinter printer(nullptr, true);
    EXPECT_NE(printer.CStr(), nullptr);
}

// Test CStrSize returns valid size
TEST_F(XMLPrinterTest_308, CStrSize_InitialSize_308) {
    XMLPrinter printer(nullptr, true);
    // Even empty printer should have some size (at least null terminator)
    EXPECT_GE(printer.CStrSize(), (size_t)0);
}

// Test CStrSize increases after content
TEST_F(XMLPrinterTest_308, CStrSize_IncreasesAfterContent_308) {
    XMLPrinter printer(nullptr, true);
    size_t initialSize = printer.CStrSize();
    printer.OpenElement("root", true);
    printer.PushText(42);
    printer.CloseElement(true);
    EXPECT_GT(printer.CStrSize(), initialSize);
}

// Test ClearBuffer resets buffer
TEST_F(XMLPrinterTest_308, ClearBuffer_ResetsBuffer_308) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushText(42);
    printer.CloseElement(true);
    size_t sizeBeforeClear = printer.CStrSize();
    EXPECT_GT(sizeBeforeClear, (size_t)1);
    
    printer.ClearBuffer();
    size_t sizeAfterClear = printer.CStrSize();
    EXPECT_LT(sizeAfterClear, sizeBeforeClear);
}

// Test OpenElement and CloseElement basic
TEST_F(XMLPrinterTest_308, OpenCloseElement_Basic_308) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test", true);
    printer.CloseElement(true);
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<test"), std::string::npos);
}

// Test PushAttribute with string value
TEST_F(XMLPrinterTest_308, PushAttribute_String_308) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushAttribute("name", "value");
    printer.CloseElement(true);
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("name="), std::string::npos);
    EXPECT_NE(result.find("value"), std::string::npos);
}

// Test PushAttribute with int value
TEST_F(XMLPrinterTest_308, PushAttribute_Int_308) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushAttribute("count", 5);
    printer.CloseElement(true);
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("count="), std::string::npos);
    EXPECT_NE(result.find("5"), std::string::npos);
}

// Test PushAttribute with bool value
TEST_F(XMLPrinterTest_308, PushAttribute_Bool_308) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushAttribute("flag", true);
    printer.CloseElement(true);
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("flag="), std::string::npos);
    EXPECT_NE(result.find("true"), std::string::npos);
}

// Test PushAttribute with double value
TEST_F(XMLPrinterTest_308, PushAttribute_Double_308) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushAttribute("pi", 3.14159);
    printer.CloseElement(true);
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("pi="), std::string::npos);
    EXPECT_NE(result.find("3.14159"), std::string::npos);
}

// Test PushComment
TEST_F(XMLPrinterTest_308, PushComment_308) {
    XMLPrinter printer(nullptr, true);
    printer.PushComment("this is a comment");
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!--"), std::string::npos);
    EXPECT_NE(result.find("this is a comment"), std::string::npos);
    EXPECT_NE(result.find("-->"), std::string::npos);
}

// Test PushDeclaration
TEST_F(XMLPrinterTest_308, PushDeclaration_308) {
    XMLPrinter printer(nullptr, true);
    printer.PushDeclaration("xml version=\"1.0\"");
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?"), std::string::npos);
    EXPECT_NE(result.find("xml version=\"1.0\""), std::string::npos);
    EXPECT_NE(result.find("?>"), std::string::npos);
}

// Test PushUnknown
TEST_F(XMLPrinterTest_308, PushUnknown_308) {
    XMLPrinter printer(nullptr, true);
    printer.PushUnknown("DOCTYPE html");
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!"), std::string::npos);
    EXPECT_NE(result.find("DOCTYPE html"), std::string::npos);
    EXPECT_NE(result.find(">"), std::string::npos);
}

// Test PushHeader with BOM and declaration
TEST_F(XMLPrinterTest_308, PushHeader_WithBOMAndDecl_308) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(false, true);
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml"), std::string::npos);
}

// Test nested elements
TEST_F(XMLPrinterTest_308, NestedElements_308) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("outer", true);
    printer.OpenElement("inner", true);
    printer.PushText(100);
    printer.CloseElement(true);
    printer.CloseElement(true);
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<outer>"), std::string::npos);
    EXPECT_NE(result.find("<inner>"), std::string::npos);
    EXPECT_NE(result.find("100"), std::string::npos);
    EXPECT_NE(result.find("</inner>"), std::string::npos);
    EXPECT_NE(result.find("</outer>"), std::string::npos);
}

// Test empty element (self-closing)
TEST_F(XMLPrinterTest_308, EmptyElement_SelfClosing_308) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("empty", true);
    printer.CloseElement(true);
    
    std::string result = printer.CStr();
    // Should be self-closing like <empty/>
    EXPECT_NE(result.find("<empty/>"), std::string::npos);
}

// Test compact mode vs non-compact mode
TEST_F(XMLPrinterTest_308, NonCompactMode_308) {
    XMLPrinter printer(nullptr, false);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.PushText(42);
    printer.CloseElement();
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("42"), std::string::npos);
    // Non-compact mode should have newlines
    EXPECT_NE(result.find("\n"), std::string::npos);
}

// Test XMLDocument printing via visitor
TEST_F(XMLPrinterTest_308, VisitDocument_308) {
    XMLDocument doc;
    doc.Parse("<root><child>text</child></root>");
    ASSERT_EQ(doc.Error(), false);
    
    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root>"), std::string::npos);
    EXPECT_NE(result.find("<child>"), std::string::npos);
    EXPECT_NE(result.find("text"), std::string::npos);
}

// Test PushAttribute with unsigned int
TEST_F(XMLPrinterTest_308, PushAttribute_UnsignedInt_308) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushAttribute("val", (unsigned int)100);
    printer.CloseElement(true);
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("100"), std::string::npos);
}

// Test PushAttribute with int64_t
TEST_F(XMLPrinterTest_308, PushAttribute_Int64_308) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushAttribute("big", (int64_t)9999999999LL);
    printer.CloseElement(true);
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("9999999999"), std::string::npos);
}

// Test PushAttribute with uint64_t
TEST_F(XMLPrinterTest_308, PushAttribute_Uint64_308) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    printer.PushAttribute("ubig", (uint64_t)18446744073709551615ULL);
    printer.CloseElement(true);
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("18446744073709551615"), std::string::npos);
}

// Test printing with multiple attributes
TEST_F(XMLPrinterTest_308, MultipleAttributes_308) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem", true);
    printer.PushAttribute("a", "1");
    printer.PushAttribute("b", "2");
    printer.PushAttribute("c", "3");
    printer.CloseElement(true);
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("a="), std::string::npos);
    EXPECT_NE(result.find("b="), std::string::npos);
    EXPECT_NE(result.find("c="), std::string::npos);
}

// Test PushText int after clear buffer
TEST_F(XMLPrinterTest_308, PushTextInt_AfterClearBuffer_308) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("first", true);
    printer.PushText(1);
    printer.CloseElement(true);
    
    printer.ClearBuffer();
    
    printer.OpenElement("second", true);
    printer.PushText(2);
    printer.CloseElement(true);
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("2"), std::string::npos);
    EXPECT_NE(result.find("second"), std::string::npos);
}
