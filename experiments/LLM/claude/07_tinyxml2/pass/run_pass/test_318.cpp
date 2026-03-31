#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for XMLPrinter VisitExit tests
class XMLPrinterVisitExitTest_318 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that VisitExit returns true for a simple element
TEST_F(XMLPrinterVisitExitTest_318, VisitExitReturnsTrue_318) {
    XMLDocument doc;
    doc.Parse("<root/>");
    const XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);

    XMLPrinter printer(nullptr, false);
    printer.OpenElement("root");
    bool result = printer.VisitExit(*element);
    EXPECT_TRUE(result);
}

// Test VisitExit with compact mode element
TEST_F(XMLPrinterVisitExitTest_318, VisitExitCompactMode_318) {
    XMLDocument doc;
    doc.Parse("<root/>");
    const XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);

    XMLPrinter printer(nullptr, true);
    printer.OpenElement("root", true);
    bool result = printer.VisitExit(*element);
    EXPECT_TRUE(result);
}

// Test VisitExit closes the element properly (verified through CStr)
TEST_F(XMLPrinterVisitExitTest_318, VisitExitClosesElement_318) {
    XMLDocument doc;
    doc.Parse("<root><child>text</child></root>");
    const XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    XMLPrinter printer(nullptr, true);
    // Print the document through Accept which uses VisitEnter/VisitExit
    doc.Accept(&printer);
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);

    // The output should contain proper closing tags
    std::string outputStr(output);
    EXPECT_NE(outputStr.find("</root>"), std::string::npos);
    EXPECT_NE(outputStr.find("</child>"), std::string::npos);
}

// Test VisitExit with nested elements
TEST_F(XMLPrinterVisitExitTest_318, VisitExitNestedElements_318) {
    XMLDocument doc;
    doc.Parse("<a><b><c/></b></a>");
    
    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);

    std::string outputStr(output);
    EXPECT_NE(outputStr.find("</a>"), std::string::npos);
    EXPECT_NE(outputStr.find("</b>"), std::string::npos);
}

// Test VisitExit with self-closing element
TEST_F(XMLPrinterVisitExitTest_318, VisitExitSelfClosingElement_318) {
    XMLDocument doc;
    doc.Parse("<root><empty/></root>");
    
    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);

    // Self-closing elements should produce "/>"
    std::string outputStr(output);
    EXPECT_NE(outputStr.find("/>"), std::string::npos);
}

// Test VisitExit with element containing attributes
TEST_F(XMLPrinterVisitExitTest_318, VisitExitElementWithAttributes_318) {
    XMLDocument doc;
    doc.Parse("<root attr=\"value\">content</root>");
    const XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);

    std::string outputStr(output);
    EXPECT_NE(outputStr.find("</root>"), std::string::npos);
    EXPECT_NE(outputStr.find("attr=\"value\""), std::string::npos);
}

// Test VisitExit with non-compact mode (pretty printing)
TEST_F(XMLPrinterVisitExitTest_318, VisitExitNonCompactMode_318) {
    XMLDocument doc;
    doc.Parse("<root><child>text</child></root>");
    
    XMLPrinter printer(nullptr, false);
    doc.Accept(&printer);
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);

    std::string outputStr(output);
    // In non-compact mode, output should contain newlines
    EXPECT_NE(outputStr.find("\n"), std::string::npos);
    EXPECT_NE(outputStr.find("</root>"), std::string::npos);
}

// Test VisitExit always returns true
TEST_F(XMLPrinterVisitExitTest_318, VisitExitAlwaysReturnsTrue_318) {
    XMLDocument doc;
    doc.Parse("<a><b/><c/><d><e/></d></a>");

    // We'll verify by checking that Accept completes successfully
    // (it would stop if VisitExit returned false)
    XMLPrinter printer(nullptr, true);
    bool accepted = doc.Accept(&printer);
    EXPECT_TRUE(accepted);

    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    // Verify the entire document was printed (all elements visited)
    std::string outputStr(output);
    EXPECT_NE(outputStr.find("</a>"), std::string::npos);
}

// Test VisitExit with element that has text content
TEST_F(XMLPrinterVisitExitTest_318, VisitExitElementWithTextContent_318) {
    XMLDocument doc;
    doc.Parse("<msg>Hello World</msg>");
    const XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);

    std::string outputStr(output);
    EXPECT_NE(outputStr.find("Hello World"), std::string::npos);
    EXPECT_NE(outputStr.find("</msg>"), std::string::npos);
}

// Test VisitExit with deeply nested elements
TEST_F(XMLPrinterVisitExitTest_318, VisitExitDeeplyNested_318) {
    XMLDocument doc;
    doc.Parse("<a><b><c><d><e>deep</e></d></c></b></a>");

    XMLPrinter printer(nullptr, false);
    doc.Accept(&printer);
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);

    std::string outputStr(output);
    EXPECT_NE(outputStr.find("</a>"), std::string::npos);
    EXPECT_NE(outputStr.find("</b>"), std::string::npos);
    EXPECT_NE(outputStr.find("</c>"), std::string::npos);
    EXPECT_NE(outputStr.find("</d>"), std::string::npos);
    EXPECT_NE(outputStr.find("</e>"), std::string::npos);
    EXPECT_NE(outputStr.find("deep"), std::string::npos);
}

// Test VisitExit with multiple sibling elements
TEST_F(XMLPrinterVisitExitTest_318, VisitExitMultipleSiblings_318) {
    XMLDocument doc;
    doc.Parse("<root><a/><b/><c/></root>");

    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);

    std::string outputStr(output);
    EXPECT_NE(outputStr.find("</root>"), std::string::npos);
}

// Test VisitExit with empty root element
TEST_F(XMLPrinterVisitExitTest_318, VisitExitEmptyElement_318) {
    XMLDocument doc;
    doc.Parse("<root></root>");

    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);

    std::string outputStr(output);
    // Empty element may be self-closing or have close tag
    EXPECT_TRUE(outputStr.find("/>") != std::string::npos || 
                outputStr.find("</root>") != std::string::npos);
}

// Test that using printer directly with OpenElement and then calling VisitExit works
TEST_F(XMLPrinterVisitExitTest_318, DirectPrinterUsageWithVisitExit_318) {
    XMLDocument doc;
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);

    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test", true);
    bool result = printer.VisitExit(*elem);
    EXPECT_TRUE(result);

    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    std::string outputStr(output);
    // Should have closing for the element
    EXPECT_TRUE(outputStr.find("test") != std::string::npos);
}

// Test VisitExit with element having special characters in name
TEST_F(XMLPrinterVisitExitTest_318, VisitExitSpecialElementName_318) {
    XMLDocument doc;
    doc.Parse("<my-element_1>data</my-element_1>");

    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);

    std::string outputStr(output);
    EXPECT_NE(outputStr.find("</my-element_1>"), std::string::npos);
}
