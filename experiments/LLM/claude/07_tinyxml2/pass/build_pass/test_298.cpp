#include <gtest/gtest.h>
#include <string>
#include <cstring>
#include <climits>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLPrinterTest_298 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test PushAttribute with unsigned int value 0
TEST_F(XMLPrinterTest_298, PushAttributeUnsignedZero_298) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("attr", (unsigned int)0);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("attr=\"0\""), std::string::npos);
}

// Test PushAttribute with unsigned int value 1
TEST_F(XMLPrinterTest_298, PushAttributeUnsignedOne_298) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("attr", (unsigned int)1);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("attr=\"1\""), std::string::npos);
}

// Test PushAttribute with unsigned int max value
TEST_F(XMLPrinterTest_298, PushAttributeUnsignedMax_298) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("maxval", UINT_MAX);
    printer.CloseElement();
    std::string result = printer.CStr();
    // UINT_MAX is 4294967295
    EXPECT_NE(result.find("maxval=\"4294967295\""), std::string::npos);
}

// Test PushAttribute with unsigned int typical value
TEST_F(XMLPrinterTest_298, PushAttributeUnsignedTypical_298) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("item");
    printer.PushAttribute("count", (unsigned int)42);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("count=\"42\""), std::string::npos);
}

// Test PushAttribute with unsigned int large value
TEST_F(XMLPrinterTest_298, PushAttributeUnsignedLargeValue_298) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("data");
    printer.PushAttribute("size", (unsigned int)1000000000);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("size=\"1000000000\""), std::string::npos);
}

// Test PushAttribute with int value (positive)
TEST_F(XMLPrinterTest_298, PushAttributeIntPositive_298) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", 123);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val=\"123\""), std::string::npos);
}

// Test PushAttribute with int value (negative)
TEST_F(XMLPrinterTest_298, PushAttributeIntNegative_298) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", -456);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val=\"-456\""), std::string::npos);
}

// Test PushAttribute with bool value true
TEST_F(XMLPrinterTest_298, PushAttributeBoolTrue_298) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("flag", true);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("flag=\"true\""), std::string::npos);
}

// Test PushAttribute with bool value false
TEST_F(XMLPrinterTest_298, PushAttributeBoolFalse_298) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("flag", false);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("flag=\"false\""), std::string::npos);
}

// Test PushAttribute with double value
TEST_F(XMLPrinterTest_298, PushAttributeDouble_298) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("pi", 3.14);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("pi="), std::string::npos);
}

// Test PushAttribute with string value
TEST_F(XMLPrinterTest_298, PushAttributeString_298) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("name", "hello");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("name=\"hello\""), std::string::npos);
}

// Test PushAttribute with int64_t value
TEST_F(XMLPrinterTest_298, PushAttributeInt64_298) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("big", (int64_t)9223372036854775807LL);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("big=\"9223372036854775807\""), std::string::npos);
}

// Test PushAttribute with uint64_t value
TEST_F(XMLPrinterTest_298, PushAttributeUint64_298) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("ubig", (uint64_t)18446744073709551615ULL);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("ubig=\"18446744073709551615\""), std::string::npos);
}

// Test multiple unsigned attributes on the same element
TEST_F(XMLPrinterTest_298, PushMultipleUnsignedAttributes_298) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("a", (unsigned int)10);
    printer.PushAttribute("b", (unsigned int)20);
    printer.PushAttribute("c", (unsigned int)30);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("a=\"10\""), std::string::npos);
    EXPECT_NE(result.find("b=\"20\""), std::string::npos);
    EXPECT_NE(result.find("c=\"30\""), std::string::npos);
}

// Test output structure with element and unsigned attribute
TEST_F(XMLPrinterTest_298, ElementWithUnsignedAttributeStructure_298) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root");
    printer.PushAttribute("version", (unsigned int)2);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root"), std::string::npos);
    EXPECT_NE(result.find("version=\"2\""), std::string::npos);
    EXPECT_NE(result.find("/>"), std::string::npos);
}

// Test CStr returns valid string after PushAttribute unsigned
TEST_F(XMLPrinterTest_298, CStrReturnsNonNull_298) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test");
    printer.PushAttribute("num", (unsigned int)999);
    printer.CloseElement();
    EXPECT_NE(printer.CStr(), nullptr);
    EXPECT_GT(printer.CStrSize(), (size_t)0);
}

// Test ClearBuffer resets content after unsigned attribute
TEST_F(XMLPrinterTest_298, ClearBufferAfterUnsignedAttribute_298) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", (unsigned int)100);
    printer.CloseElement();
    size_t sizeBeforeClear = printer.CStrSize();
    EXPECT_GT(sizeBeforeClear, (size_t)1);
    printer.ClearBuffer();
    // After clearing, buffer should be essentially empty (just null terminator)
    EXPECT_LE(printer.CStrSize(), (size_t)1);
}

// Test nested elements with unsigned attributes
TEST_F(XMLPrinterTest_298, NestedElementsWithUnsignedAttributes_298) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("parent");
    printer.PushAttribute("id", (unsigned int)1);
    printer.OpenElement("child");
    printer.PushAttribute("id", (unsigned int)2);
    printer.CloseElement();
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("parent"), std::string::npos);
    EXPECT_NE(result.find("child"), std::string::npos);
}

// Test PushText with unsigned int
TEST_F(XMLPrinterTest_298, PushTextUnsigned_298) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("num");
    printer.PushText((unsigned int)555);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("555"), std::string::npos);
}

// Test PushHeader
TEST_F(XMLPrinterTest_298, PushHeaderDeclaration_298) {
    XMLPrinter printer(nullptr, true);
    printer.PushHeader(false, true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?xml"), std::string::npos);
}

// Test PushComment
TEST_F(XMLPrinterTest_298, PushComment_298) {
    XMLPrinter printer(nullptr, true);
    printer.PushComment("This is a comment");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!--"), std::string::npos);
    EXPECT_NE(result.find("This is a comment"), std::string::npos);
    EXPECT_NE(result.find("-->"), std::string::npos);
}

// Test PushDeclaration
TEST_F(XMLPrinterTest_298, PushDeclaration_298) {
    XMLPrinter printer(nullptr, true);
    printer.PushDeclaration("xml version=\"1.0\"");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<?"), std::string::npos);
    EXPECT_NE(result.find("?>"), std::string::npos);
}

// Test PushUnknown
TEST_F(XMLPrinterTest_298, PushUnknown_298) {
    XMLPrinter printer(nullptr, true);
    printer.PushUnknown("UNKNOWN_STUFF");
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<!"), std::string::npos);
    EXPECT_NE(result.find("UNKNOWN_STUFF"), std::string::npos);
}

// Test XMLDocument with XMLPrinter visitor
TEST_F(XMLPrinterTest_298, DocumentAcceptWithPrinter_298) {
    XMLDocument doc;
    doc.Parse("<root attr=\"5\"><child/></root>");
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);

    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("root"), std::string::npos);
    EXPECT_NE(result.find("child"), std::string::npos);
}

// Test compact vs non-compact mode
TEST_F(XMLPrinterTest_298, CompactModeOutput_298) {
    XMLPrinter compactPrinter(nullptr, true);
    compactPrinter.OpenElement("a");
    compactPrinter.PushAttribute("x", (unsigned int)7);
    compactPrinter.CloseElement();

    XMLPrinter normalPrinter(nullptr, false);
    normalPrinter.OpenElement("a");
    normalPrinter.PushAttribute("x", (unsigned int)7);
    normalPrinter.CloseElement();

    std::string compactResult = compactPrinter.CStr();
    std::string normalResult = normalPrinter.CStr();

    // Both should contain the attribute
    EXPECT_NE(compactResult.find("x=\"7\""), std::string::npos);
    EXPECT_NE(normalResult.find("x=\"7\""), std::string::npos);
}

// Test PushAttribute unsigned with mixed attribute types
TEST_F(XMLPrinterTest_298, MixedAttributeTypes_298) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("mixed");
    printer.PushAttribute("str", "text");
    printer.PushAttribute("num", (unsigned int)42);
    printer.PushAttribute("flag", true);
    printer.PushAttribute("neg", -1);
    printer.PushAttribute("dbl", 2.5);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("str=\"text\""), std::string::npos);
    EXPECT_NE(result.find("num=\"42\""), std::string::npos);
    EXPECT_NE(result.find("flag=\"true\""), std::string::npos);
    EXPECT_NE(result.find("neg=\"-1\""), std::string::npos);
}

// Test PushText with various types inside element
TEST_F(XMLPrinterTest_298, PushTextInt_298) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("val");
    printer.PushText(42);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("42"), std::string::npos);
}

// Test PushText with string
TEST_F(XMLPrinterTest_298, PushTextString_298) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("msg");
    printer.PushText("Hello World", false);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("Hello World"), std::string::npos);
}

// Test PushText with CDATA
TEST_F(XMLPrinterTest_298, PushTextCData_298) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("data");
    printer.PushText("some <data>", true);
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<![CDATA["), std::string::npos);
    EXPECT_NE(result.find("some <data>"), std::string::npos);
}

// Test self-closing element with unsigned attribute
TEST_F(XMLPrinterTest_298, SelfClosingElementWithUnsigned_298) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("br");
    printer.PushAttribute("count", (unsigned int)0);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<br"), std::string::npos);
    EXPECT_NE(result.find("/>"), std::string::npos);
}
