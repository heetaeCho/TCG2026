#include "gtest/gtest.h"
#include "tinyxml2.h"
#include <string>
#include <cstring>

using namespace tinyxml2;

class XMLPrinterCloseElementTest_303 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Basic open and close element in non-compact mode
TEST_F(XMLPrinterCloseElementTest_303, BasicOpenCloseElement_303) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("root");
    printer.CloseElement(false);
    std::string result = printer.CStr();
    // Should produce a self-closing tag since no content was added
    // <root/>\n
    EXPECT_NE(result.find("<root/>"), std::string::npos);
}

// Test: Self-closing element in compact mode
TEST_F(XMLPrinterCloseElementTest_303, SelfClosingCompactMode_303) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("item", true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<item/>"), std::string::npos);
    // In compact mode, no trailing newline after root-level close
}

// Test: Element with text content and close in non-compact mode
TEST_F(XMLPrinterCloseElementTest_303, ElementWithTextCloseNonCompact_303) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("name");
    printer.PushText("Hello");
    printer.CloseElement(false);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<name>Hello</name>"), std::string::npos);
}

// Test: Element with text content and close in compact mode
TEST_F(XMLPrinterCloseElementTest_303, ElementWithTextCloseCompact_303) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("name", true);
    printer.PushText("Hello");
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<name>Hello</name>"), std::string::npos);
}

// Test: Nested elements close properly in non-compact mode
TEST_F(XMLPrinterCloseElementTest_303, NestedElementsNonCompact_303) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.CloseElement(false);
    printer.CloseElement(false);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root>"), std::string::npos);
    EXPECT_NE(result.find("<child/>"), std::string::npos);
    EXPECT_NE(result.find("</root>"), std::string::npos);
}

// Test: Nested elements close properly in compact mode
TEST_F(XMLPrinterCloseElementTest_303, NestedElementsCompact_303) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("root", true);
    printer.OpenElement("child", true);
    printer.CloseElement(true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root>"), std::string::npos);
    EXPECT_NE(result.find("<child/>"), std::string::npos);
    EXPECT_NE(result.find("</root>"), std::string::npos);
}

// Test: Close element after adding attribute (self-closing)
TEST_F(XMLPrinterCloseElementTest_303, CloseElementWithAttribute_303) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("item");
    printer.PushAttribute("id", "42");
    printer.CloseElement(false);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("id=\"42\""), std::string::npos);
    EXPECT_NE(result.find("/>"), std::string::npos);
}

// Test: Close element with children that have text
TEST_F(XMLPrinterCloseElementTest_303, CloseElementWithChildText_303) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.PushText("data");
    printer.CloseElement(false);
    printer.CloseElement(false);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<child>data</child>"), std::string::npos);
    EXPECT_NE(result.find("</root>"), std::string::npos);
}

// Test: Multiple sibling elements
TEST_F(XMLPrinterCloseElementTest_303, MultipleSiblingElements_303) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("root");
    printer.OpenElement("a");
    printer.CloseElement(false);
    printer.OpenElement("b");
    printer.CloseElement(false);
    printer.OpenElement("c");
    printer.CloseElement(false);
    printer.CloseElement(false);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<a/>"), std::string::npos);
    EXPECT_NE(result.find("<b/>"), std::string::npos);
    EXPECT_NE(result.find("<c/>"), std::string::npos);
    EXPECT_NE(result.find("</root>"), std::string::npos);
}

// Test: Deeply nested elements
TEST_F(XMLPrinterCloseElementTest_303, DeeplyNestedElements_303) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("a");
    printer.OpenElement("b");
    printer.OpenElement("c");
    printer.OpenElement("d");
    printer.CloseElement(false);
    printer.CloseElement(false);
    printer.CloseElement(false);
    printer.CloseElement(false);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("</a>"), std::string::npos);
    EXPECT_NE(result.find("</b>"), std::string::npos);
    EXPECT_NE(result.find("</c>"), std::string::npos);
    EXPECT_NE(result.find("<d/>"), std::string::npos);
}

// Test: Close element with compact=true on non-compact printer
TEST_F(XMLPrinterCloseElementTest_303, CompactCloseOnNonCompactPrinter_303) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("root");
    printer.OpenElement("child");
    printer.PushText("text");
    printer.CloseElement(true);  // close child in compact mode
    printer.CloseElement(false); // close root in non-compact mode
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<child>text</child>"), std::string::npos);
    EXPECT_NE(result.find("</root>"), std::string::npos);
}

// Test: Close element with compact=false on compact printer
TEST_F(XMLPrinterCloseElementTest_303, NonCompactCloseOnCompactPrinter_303) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("root", true);
    printer.OpenElement("child", true);
    printer.PushText("text");
    printer.CloseElement(false); // close child in non-compact mode
    printer.CloseElement(true);  // close root in compact mode
    std::string result = printer.CStr();
    EXPECT_NE(result.find("</child>"), std::string::npos);
    EXPECT_NE(result.find("</root>"), std::string::npos);
}

// Test: Trailing newline at depth 0 in non-compact mode
TEST_F(XMLPrinterCloseElementTest_303, TrailingNewlineAtDepthZero_303) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("root");
    printer.CloseElement(false);
    std::string result = printer.CStr();
    // Should end with newline in non-compact mode at depth 0
    ASSERT_FALSE(result.empty());
    EXPECT_EQ(result.back(), '\n');
}

// Test: No trailing newline at depth 0 in compact mode
TEST_F(XMLPrinterCloseElementTest_303, NoTrailingNewlineCompact_303) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("root", true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    ASSERT_FALSE(result.empty());
    EXPECT_NE(result.back(), '\n');
}

// Test: ClearBuffer and reuse after CloseElement
TEST_F(XMLPrinterCloseElementTest_303, ClearBufferAfterCloseElement_303) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("first");
    printer.CloseElement(false);
    std::string first_result = printer.CStr();
    EXPECT_NE(first_result.find("<first/>"), std::string::npos);
    
    printer.ClearBuffer();
    printer.OpenElement("second");
    printer.CloseElement(false);
    std::string second_result = printer.CStr();
    EXPECT_NE(second_result.find("<second/>"), std::string::npos);
    EXPECT_EQ(second_result.find("<first/>"), std::string::npos);
}

// Test: Element with attribute and child text
TEST_F(XMLPrinterCloseElementTest_303, ElementWithAttributeAndChildText_303) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("item");
    printer.PushAttribute("key", "value");
    printer.PushText("content");
    printer.CloseElement(false);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("key=\"value\""), std::string::npos);
    EXPECT_NE(result.find(">content</item>"), std::string::npos);
}

// Test: Using XMLDocument to print and verify CloseElement behavior
TEST_F(XMLPrinterCloseElementTest_303, DocumentRoundTrip_303) {
    XMLDocument doc;
    doc.Parse("<root><child>text</child></root>");
    ASSERT_FALSE(doc.Error());
    
    XMLPrinter printer(nullptr, true, 0);
    doc.Accept(&printer);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<root>"), std::string::npos);
    EXPECT_NE(result.find("</root>"), std::string::npos);
    EXPECT_NE(result.find("<child>text</child>"), std::string::npos);
}

// Test: Empty element name
TEST_F(XMLPrinterCloseElementTest_303, EmptyElementName_303) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("", true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    // Should still produce valid output with empty element name
    EXPECT_NE(result.find("/>"), std::string::npos);
}

// Test: Multiple root-level elements
TEST_F(XMLPrinterCloseElementTest_303, MultipleRootLevelElements_303) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("first");
    printer.CloseElement(false);
    printer.OpenElement("second");
    printer.CloseElement(false);
    std::string result = printer.CStr();
    EXPECT_NE(result.find("<first/>"), std::string::npos);
    EXPECT_NE(result.find("<second/>"), std::string::npos);
}

// Test: CloseElement self-closing preserves correct tag format
TEST_F(XMLPrinterCloseElementTest_303, SelfClosingFormat_303) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("selfclose");
    printer.CloseElement(false);
    std::string result = printer.CStr();
    // Self-closing should use "/>" not "</selfclose>"
    EXPECT_NE(result.find("<selfclose/>"), std::string::npos);
    EXPECT_EQ(result.find("</selfclose>"), std::string::npos);
}

// Test: Non-self-closing when content exists
TEST_F(XMLPrinterCloseElementTest_303, NonSelfClosingWithContent_303) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("parent");
    printer.OpenElement("child");
    printer.CloseElement(false);
    printer.CloseElement(false);
    std::string result = printer.CStr();
    // parent has content (child), so should use </parent>
    EXPECT_NE(result.find("</parent>"), std::string::npos);
}

// Test: CStrSize after CloseElement
TEST_F(XMLPrinterCloseElementTest_303, CStrSizeAfterCloseElement_303) {
    XMLPrinter printer(nullptr, true, 0);
    printer.OpenElement("test", true);
    printer.CloseElement(true);
    std::string result = printer.CStr();
    // CStrSize includes the null terminator
    EXPECT_EQ(printer.CStrSize(), result.size() + 1);
}

// Test: Indentation in non-compact nested elements
TEST_F(XMLPrinterCloseElementTest_303, IndentationNonCompact_303) {
    XMLPrinter printer(nullptr, false, 0);
    printer.OpenElement("root");
    printer.OpenElement("level1");
    printer.OpenElement("level2");
    printer.CloseElement(false);
    printer.CloseElement(false);
    printer.CloseElement(false);
    std::string result = printer.CStr();
    // Verify proper structure
    EXPECT_NE(result.find("<root>"), std::string::npos);
    EXPECT_NE(result.find("<level1>"), std::string::npos);
    EXPECT_NE(result.find("<level2/>"), std::string::npos);
    EXPECT_NE(result.find("</level1>"), std::string::npos);
    EXPECT_NE(result.find("</root>"), std::string::npos);
}
