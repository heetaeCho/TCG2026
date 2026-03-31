#include <gtest/gtest.h>
#include <cstdarg>
#include <cstdio>
#include <climits>
#include <string>

// We need to test TIXML_VSCPRINTF which is a static inline function.
// Since it's defined as static inline in tinyxml2.cpp, we need to include or
// redefine it for testing purposes. We'll include the header and test through
// the public interface of tinyxml2, or we can test the function behavior
// through a wrapper.

// Include tinyxml2 header for the public API
#include "tinyxml2.h"

using namespace tinyxml2;

// Helper function that calls the equivalent of TIXML_VSCPRINTF behavior
// through the public API. Since TIXML_VSCPRINTF is a static helper used
// internally, we test its effects through XMLPrinter which uses it.

class TinyXML2_VSCPRINTF_Test_153 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that XMLPrinter can handle simple formatted output (exercises TIXML_VSCPRINTF internally)
TEST_F(TinyXML2_VSCPRINTF_Test_153, PrinterHandlesSimpleText_153) {
    XMLPrinter printer;
    printer.PushHeader(false, false);
    printer.OpenElement("root");
    printer.PushText("Hello World");
    printer.CloseElement();
    
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    EXPECT_NE(std::string(result).find("Hello World"), std::string::npos);
}

// Test that XMLPrinter handles empty strings
TEST_F(TinyXML2_VSCPRINTF_Test_153, PrinterHandlesEmptyText_153) {
    XMLPrinter printer;
    printer.OpenElement("root");
    printer.PushText("");
    printer.CloseElement();
    
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    EXPECT_NE(std::string(result).find("root"), std::string::npos);
}

// Test that XMLPrinter handles long text (exercises buffer growth via TIXML_VSCPRINTF)
TEST_F(TinyXML2_VSCPRINTF_Test_153, PrinterHandlesLongText_153) {
    XMLPrinter printer;
    printer.OpenElement("root");
    
    std::string longText(1000, 'A');
    printer.PushText(longText.c_str());
    printer.CloseElement();
    
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    EXPECT_NE(std::string(result).find(longText), std::string::npos);
}

// Test that XMLPrinter handles integer attributes (formatted output)
TEST_F(TinyXML2_VSCPRINTF_Test_153, PrinterHandlesIntAttribute_153) {
    XMLPrinter printer;
    printer.OpenElement("root");
    printer.PushAttribute("value", 42);
    printer.CloseElement();
    
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    std::string str(result);
    EXPECT_NE(str.find("42"), std::string::npos);
}

// Test that XMLPrinter handles double attributes (formatted output)
TEST_F(TinyXML2_VSCPRINTF_Test_153, PrinterHandlesDoubleAttribute_153) {
    XMLPrinter printer;
    printer.OpenElement("root");
    printer.PushAttribute("value", 3.14);
    printer.CloseElement();
    
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    std::string str(result);
    EXPECT_NE(str.find("3.14"), std::string::npos);
}

// Test that XMLPrinter handles boolean attributes
TEST_F(TinyXML2_VSCPRINTF_Test_153, PrinterHandlesBoolAttribute_153) {
    XMLPrinter printer;
    printer.OpenElement("root");
    printer.PushAttribute("flag", true);
    printer.CloseElement();
    
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    std::string str(result);
    EXPECT_NE(str.find("true"), std::string::npos);
}

// Test that XMLPrinter handles special characters in text
TEST_F(TinyXML2_VSCPRINTF_Test_153, PrinterHandlesSpecialChars_153) {
    XMLPrinter printer;
    printer.OpenElement("root");
    printer.PushText("a < b & c > d");
    printer.CloseElement();
    
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    std::string str(result);
    // Special chars should be escaped
    EXPECT_NE(str.find("&lt;"), std::string::npos);
    EXPECT_NE(str.find("&amp;"), std::string::npos);
    EXPECT_NE(str.find("&gt;"), std::string::npos);
}

// Test that XMLPrinter handles nested elements
TEST_F(TinyXML2_VSCPRINTF_Test_153, PrinterHandlesNestedElements_153) {
    XMLPrinter printer;
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.OpenElement("grandchild");
    printer.PushText("deep");
    printer.CloseElement();
    printer.CloseElement();
    printer.CloseElement();
    
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    std::string str(result);
    EXPECT_NE(str.find("root"), std::string::npos);
    EXPECT_NE(str.find("child"), std::string::npos);
    EXPECT_NE(str.find("grandchild"), std::string::npos);
    EXPECT_NE(str.find("deep"), std::string::npos);
}

// Test that XMLPrinter CStrSize returns correct size
TEST_F(TinyXML2_VSCPRINTF_Test_153, PrinterCStrSizeIsCorrect_153) {
    XMLPrinter printer;
    printer.OpenElement("root");
    printer.CloseElement();
    
    const char* result = printer.CStr();
    int size = printer.CStrSize();
    ASSERT_NE(result, nullptr);
    // CStrSize includes the null terminator
    EXPECT_EQ(size, (int)strlen(result) + 1);
}

// Test that XMLPrinter handles very long formatted attributes
TEST_F(TinyXML2_VSCPRINTF_Test_153, PrinterHandlesVeryLongAttribute_153) {
    XMLPrinter printer;
    printer.OpenElement("root");
    
    std::string longAttrValue(2000, 'X');
    printer.PushAttribute("longattr", longAttrValue.c_str());
    printer.CloseElement();
    
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    std::string str(result);
    EXPECT_NE(str.find(longAttrValue), std::string::npos);
}

// Test that XMLPrinter handles negative integer attributes
TEST_F(TinyXML2_VSCPRINTF_Test_153, PrinterHandlesNegativeInt_153) {
    XMLPrinter printer;
    printer.OpenElement("root");
    printer.PushAttribute("value", -12345);
    printer.CloseElement();
    
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    std::string str(result);
    EXPECT_NE(str.find("-12345"), std::string::npos);
}

// Test that XMLPrinter handles zero value
TEST_F(TinyXML2_VSCPRINTF_Test_153, PrinterHandlesZeroValue_153) {
    XMLPrinter printer;
    printer.OpenElement("root");
    printer.PushAttribute("value", 0);
    printer.CloseElement();
    
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    std::string str(result);
    EXPECT_NE(str.find("\"0\""), std::string::npos);
}

// Test XMLDocument Print which also exercises internal formatting
TEST_F(TinyXML2_VSCPRINTF_Test_153, DocumentPrintExercisesFormatting_153) {
    XMLDocument doc;
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    root->SetAttribute("count", 100);
    root->SetAttribute("name", "test");
    
    XMLPrinter printer;
    doc.Print(&printer);
    
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    std::string str(result);
    EXPECT_NE(str.find("100"), std::string::npos);
    EXPECT_NE(str.find("test"), std::string::npos);
}

// Test that XMLPrinter handles unsigned int attributes
TEST_F(TinyXML2_VSCPRINTF_Test_153, PrinterHandlesUnsignedIntAttribute_153) {
    XMLPrinter printer;
    printer.OpenElement("root");
    printer.PushAttribute("value", (unsigned)4294967295U);
    printer.CloseElement();
    
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    std::string str(result);
    EXPECT_NE(str.find("4294967295"), std::string::npos);
}

// Test printing with XML declaration header
TEST_F(TinyXML2_VSCPRINTF_Test_153, PrinterWithXMLHeader_153) {
    XMLPrinter printer;
    printer.PushHeader(true, true);
    printer.OpenElement("root");
    printer.CloseElement();
    
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    std::string str(result);
    EXPECT_NE(str.find("<?xml"), std::string::npos);
}

// Test multiple text pushes
TEST_F(TinyXML2_VSCPRINTF_Test_153, PrinterMultipleTextPushes_153) {
    XMLPrinter printer;
    printer.OpenElement("root");
    printer.PushText("first");
    printer.PushText("second");
    printer.PushText("third");
    printer.CloseElement();
    
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    std::string str(result);
    EXPECT_NE(str.find("first"), std::string::npos);
    EXPECT_NE(str.find("second"), std::string::npos);
    EXPECT_NE(str.find("third"), std::string::npos);
}

// Test PushComment
TEST_F(TinyXML2_VSCPRINTF_Test_153, PrinterHandlesComment_153) {
    XMLPrinter printer;
    printer.OpenElement("root");
    printer.PushComment("This is a comment");
    printer.CloseElement();
    
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    std::string str(result);
    EXPECT_NE(str.find("<!--"), std::string::npos);
    EXPECT_NE(str.find("This is a comment"), std::string::npos);
    EXPECT_NE(str.find("-->"), std::string::npos);
}

// Test Int64 attribute formatting
TEST_F(TinyXML2_VSCPRINTF_Test_153, PrinterHandlesInt64Attribute_153) {
    XMLPrinter printer;
    printer.OpenElement("root");
    printer.PushAttribute("bigvalue", (int64_t)9223372036854775807LL);
    printer.CloseElement();
    
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    std::string str(result);
    EXPECT_NE(str.find("9223372036854775807"), std::string::npos);
}
