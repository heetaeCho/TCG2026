#include <gtest/gtest.h>
#include <string>
#include <cstring>
#include <climits>
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for XMLPrinter tests
class XMLPrinterTest_297 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test PushAttribute with a positive integer value
TEST_F(XMLPrinterTest_297, PushAttributeIntPositive_297) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    printer.PushAttribute("count", 42);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("count=\"42\""), std::string::npos);
}

// Test PushAttribute with zero integer value
TEST_F(XMLPrinterTest_297, PushAttributeIntZero_297) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    printer.PushAttribute("value", 0);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("value=\"0\""), std::string::npos);
}

// Test PushAttribute with a negative integer value
TEST_F(XMLPrinterTest_297, PushAttributeIntNegative_297) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    printer.PushAttribute("value", -100);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("value=\"-100\""), std::string::npos);
}

// Test PushAttribute with INT_MAX
TEST_F(XMLPrinterTest_297, PushAttributeIntMax_297) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    printer.PushAttribute("max", INT_MAX);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    std::string expected = std::to_string(INT_MAX);
    EXPECT_NE(result.find(std::string("max=\"") + expected + "\""), std::string::npos);
}

// Test PushAttribute with INT_MIN
TEST_F(XMLPrinterTest_297, PushAttributeIntMin_297) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    printer.PushAttribute("min", INT_MIN);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    std::string expected = std::to_string(INT_MIN);
    EXPECT_NE(result.find(std::string("min=\"") + expected + "\""), std::string::npos);
}

// Test PushAttribute with multiple integer attributes
TEST_F(XMLPrinterTest_297, PushAttributeMultipleInts_297) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    printer.PushAttribute("a", 1);
    printer.PushAttribute("b", 2);
    printer.PushAttribute("c", 3);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("a=\"1\""), std::string::npos);
    EXPECT_NE(result.find("b=\"2\""), std::string::npos);
    EXPECT_NE(result.find("c=\"3\""), std::string::npos);
}

// Test PushAttribute with string value
TEST_F(XMLPrinterTest_297, PushAttributeString_297) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    printer.PushAttribute("name", "hello");
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("name=\"hello\""), std::string::npos);
}

// Test PushAttribute with unsigned int value
TEST_F(XMLPrinterTest_297, PushAttributeUnsigned_297) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    printer.PushAttribute("val", (unsigned int)12345);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val=\"12345\""), std::string::npos);
}

// Test PushAttribute with bool value true
TEST_F(XMLPrinterTest_297, PushAttributeBoolTrue_297) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    printer.PushAttribute("flag", true);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("flag=\"true\""), std::string::npos);
}

// Test PushAttribute with bool value false
TEST_F(XMLPrinterTest_297, PushAttributeBoolFalse_297) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    printer.PushAttribute("flag", false);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("flag=\"false\""), std::string::npos);
}

// Test PushAttribute with double value
TEST_F(XMLPrinterTest_297, PushAttributeDouble_297) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    printer.PushAttribute("pi", 3.14);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("pi=\""), std::string::npos);
}

// Test PushAttribute with int64_t value
TEST_F(XMLPrinterTest_297, PushAttributeInt64_297) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    printer.PushAttribute("big", (int64_t)9223372036854775807LL);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("big=\"9223372036854775807\""), std::string::npos);
}

// Test PushAttribute with uint64_t value
TEST_F(XMLPrinterTest_297, PushAttributeUint64_297) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("element");
    printer.PushAttribute("ubig", (uint64_t)18446744073709551615ULL);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("ubig=\"18446744073709551615\""), std::string::npos);
}

// Test CStr returns non-null after operations
TEST_F(XMLPrinterTest_297, CStrReturnsNonNull_297) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test");
    printer.PushAttribute("x", 10);
    printer.CloseElement();
    
    EXPECT_NE(printer.CStr(), nullptr);
}

// Test CStrSize returns positive value after operations
TEST_F(XMLPrinterTest_297, CStrSizePositive_297) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test");
    printer.PushAttribute("x", 10);
    printer.CloseElement();
    
    EXPECT_GT(printer.CStrSize(), (size_t)0);
}

// Test ClearBuffer resets the printer
TEST_F(XMLPrinterTest_297, ClearBufferResets_297) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test");
    printer.PushAttribute("x", 10);
    printer.CloseElement();
    
    size_t sizeBefore = printer.CStrSize();
    printer.ClearBuffer();
    
    // After clearing, size should be smaller or equal to 1 (null terminator)
    EXPECT_LE(printer.CStrSize(), sizeBefore);
}

// Test compact mode vs non-compact mode output
TEST_F(XMLPrinterTest_297, CompactModeOutput_297) {
    XMLPrinter compactPrinter(nullptr, true);
    compactPrinter.OpenElement("root");
    compactPrinter.PushAttribute("val", 5);
    compactPrinter.OpenElement("child");
    compactPrinter.CloseElement();
    compactPrinter.CloseElement();
    
    XMLPrinter normalPrinter(nullptr, false);
    normalPrinter.OpenElement("root");
    normalPrinter.PushAttribute("val", 5);
    normalPrinter.OpenElement("child");
    normalPrinter.CloseElement();
    normalPrinter.CloseElement();
    
    std::string compact = compactPrinter.CStr();
    std::string normal = normalPrinter.CStr();
    
    // Both should contain the attribute
    EXPECT_NE(compact.find("val=\"5\""), std::string::npos);
    EXPECT_NE(normal.find("val=\"5\""), std::string::npos);
}

// Test PushText with int
TEST_F(XMLPrinterTest_297, PushTextInt_297) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("num");
    printer.PushText(42);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("42"), std::string::npos);
}

// Test PushHeader
TEST_F(XMLPrinterTest_297, PushHeaderDeclaration_297) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(false, true);
    printer.OpenElement("root");
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml"), std::string::npos);
}

// Test PushComment
TEST_F(XMLPrinterTest_297, PushComment_297) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.PushComment("this is a comment");
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!--this is a comment-->"), std::string::npos);
}

// Test OpenElement and CloseElement produce valid XML structure
TEST_F(XMLPrinterTest_297, OpenCloseElement_297) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root"), std::string::npos);
    EXPECT_NE(result.find("/>"), std::string::npos);
}

// Test nested elements with int attributes
TEST_F(XMLPrinterTest_297, NestedElementsWithIntAttributes_297) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("parent");
    printer.PushAttribute("id", 1);
    printer.OpenElement("child");
    printer.PushAttribute("id", 2);
    printer.CloseElement();
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("id=\"1\""), std::string::npos);
    EXPECT_NE(result.find("id=\"2\""), std::string::npos);
}

// Test PushAttribute with value 1 (small positive)
TEST_F(XMLPrinterTest_297, PushAttributeIntOne_297) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("e");
    printer.PushAttribute("v", 1);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("v=\"1\""), std::string::npos);
}

// Test PushAttribute with value -1 (small negative)
TEST_F(XMLPrinterTest_297, PushAttributeIntNegOne_297) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("e");
    printer.PushAttribute("v", -1);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("v=\"-1\""), std::string::npos);
}

// Test PushDeclaration
TEST_F(XMLPrinterTest_297, PushDeclaration_297) {
    XMLPrinter printer(nullptr, true);
    printer.PushDeclaration("xml version=\"1.0\"");
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml version=\"1.0\"?>"), std::string::npos);
}

// Test PushUnknown
TEST_F(XMLPrinterTest_297, PushUnknown_297) {
    XMLPrinter printer(nullptr, true);
    printer.PushUnknown("something");
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!something>"), std::string::npos);
}

// Test XMLDocument round-trip with printer
TEST_F(XMLPrinterTest_297, DocumentRoundTrip_297) {
    XMLDocument doc;
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    root->SetAttribute("count", 99);
    
    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("count=\"99\""), std::string::npos);
    EXPECT_NE(result.find("<root"), std::string::npos);
}

// Test PushText with cdata
TEST_F(XMLPrinterTest_297, PushTextCData_297) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("data");
    printer.PushText("content", true);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<![CDATA[content]]>"), std::string::npos);
}

// Test large integer value
TEST_F(XMLPrinterTest_297, PushAttributeLargeInt_297) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("e");
    printer.PushAttribute("v", 999999999);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("v=\"999999999\""), std::string::npos);
}
