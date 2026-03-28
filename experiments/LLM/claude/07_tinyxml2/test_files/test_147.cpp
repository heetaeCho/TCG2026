#include <gtest/gtest.h>
#include "tinyxml2.h"
#include <cstring>
#include <string>

using namespace tinyxml2;

class XMLPrinterTest_147 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that XMLPrinter can be default constructed
TEST_F(XMLPrinterTest_147, DefaultConstruction_147) {
    XMLPrinter printer;
    // Should be constructible without errors
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
}

// Test that VisitExit with XMLDocument returns true
TEST_F(XMLPrinterTest_147, VisitExitReturnsTrue_147) {
    XMLDocument doc;
    XMLPrinter printer;
    bool result = printer.VisitExit(doc);
    EXPECT_TRUE(result);
}

// Test printing an empty document
TEST_F(XMLPrinterTest_147, PrintEmptyDocument_147) {
    XMLDocument doc;
    XMLPrinter printer;
    doc.Print(&printer);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
}

// Test printing a document with a single element
TEST_F(XMLPrinterTest_147, PrintSingleElement_147) {
    XMLDocument doc;
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLPrinter printer;
    doc.Print(&printer);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    EXPECT_NE(std::string(result).find("root"), std::string::npos);
}

// Test printing a document with nested elements
TEST_F(XMLPrinterTest_147, PrintNestedElements_147) {
    XMLDocument doc;
    XMLElement* root = doc.NewElement("root");
    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);
    doc.InsertEndChild(root);
    XMLPrinter printer;
    doc.Print(&printer);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    std::string output(result);
    EXPECT_NE(output.find("root"), std::string::npos);
    EXPECT_NE(output.find("child"), std::string::npos);
}

// Test printing a document with text content
TEST_F(XMLPrinterTest_147, PrintTextContent_147) {
    XMLDocument doc;
    XMLElement* root = doc.NewElement("message");
    root->SetText("Hello World");
    doc.InsertEndChild(root);
    XMLPrinter printer;
    doc.Print(&printer);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    std::string output(result);
    EXPECT_NE(output.find("Hello World"), std::string::npos);
}

// Test printing with attributes
TEST_F(XMLPrinterTest_147, PrintElementWithAttributes_147) {
    XMLDocument doc;
    XMLElement* root = doc.NewElement("item");
    root->SetAttribute("id", 42);
    root->SetAttribute("name", "test");
    doc.InsertEndChild(root);
    XMLPrinter printer;
    doc.Print(&printer);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    std::string output(result);
    EXPECT_NE(output.find("id"), std::string::npos);
    EXPECT_NE(output.find("42"), std::string::npos);
    EXPECT_NE(output.find("name"), std::string::npos);
    EXPECT_NE(output.find("test"), std::string::npos);
}

// Test CStrSize returns non-zero for non-empty document
TEST_F(XMLPrinterTest_147, CStrSizeNonEmpty_147) {
    XMLDocument doc;
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLPrinter printer;
    doc.Print(&printer);
    EXPECT_GT(printer.CStrSize(), 0);
}

// Test printing to file (with nullptr uses internal buffer)
TEST_F(XMLPrinterTest_147, PrintToInternalBuffer_147) {
    XMLPrinter printer(nullptr, false);
    XMLDocument doc;
    doc.Parse("<root><child>text</child></root>");
    doc.Print(&printer);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    EXPECT_GT(printer.CStrSize(), 0);
}

// Test compact mode printer
TEST_F(XMLPrinterTest_147, CompactModePrinter_147) {
    XMLPrinter compact(nullptr, true);
    XMLDocument doc;
    doc.Parse("<root>\n  <child>text</child>\n</root>");
    doc.Print(&compact);
    const char* result = compact.CStr();
    ASSERT_NE(result, nullptr);
}

// Test VisitExit on parsed document
TEST_F(XMLPrinterTest_147, VisitExitOnParsedDocument_147) {
    XMLDocument doc;
    doc.Parse("<root><a/><b/></root>");
    ASSERT_FALSE(doc.Error());
    XMLPrinter printer;
    bool result = printer.VisitExit(doc);
    EXPECT_TRUE(result);
}

// Test Accept with printer
TEST_F(XMLPrinterTest_147, AcceptWithPrinter_147) {
    XMLDocument doc;
    doc.Parse("<root attr=\"value\"><child>content</child></root>");
    ASSERT_FALSE(doc.Error());
    XMLPrinter printer;
    doc.Accept(&printer);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    std::string output(result);
    EXPECT_NE(output.find("root"), std::string::npos);
    EXPECT_NE(output.find("attr"), std::string::npos);
    EXPECT_NE(output.find("value"), std::string::npos);
    EXPECT_NE(output.find("child"), std::string::npos);
    EXPECT_NE(output.find("content"), std::string::npos);
}

// Test printing XML declaration
TEST_F(XMLPrinterTest_147, PrintXMLDeclaration_147) {
    XMLDocument doc;
    doc.Parse("<?xml version=\"1.0\"?><root/>");
    ASSERT_FALSE(doc.Error());
    XMLPrinter printer;
    doc.Accept(&printer);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    std::string output(result);
    EXPECT_NE(output.find("xml"), std::string::npos);
}

// Test printing comment
TEST_F(XMLPrinterTest_147, PrintComment_147) {
    XMLDocument doc;
    doc.Parse("<root><!-- a comment --></root>");
    ASSERT_FALSE(doc.Error());
    XMLPrinter printer;
    doc.Accept(&printer);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    std::string output(result);
    EXPECT_NE(output.find("a comment"), std::string::npos);
}

// Test multiple VisitExit calls
TEST_F(XMLPrinterTest_147, MultipleVisitExitCalls_147) {
    XMLDocument doc1;
    XMLDocument doc2;
    XMLPrinter printer;
    EXPECT_TRUE(printer.VisitExit(doc1));
    EXPECT_TRUE(printer.VisitExit(doc2));
}

// Test printing deeply nested structure
TEST_F(XMLPrinterTest_147, PrintDeeplyNestedStructure_147) {
    XMLDocument doc;
    doc.Parse("<a><b><c><d><e>deep</e></d></c></b></a>");
    ASSERT_FALSE(doc.Error());
    XMLPrinter printer;
    doc.Accept(&printer);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    std::string output(result);
    EXPECT_NE(output.find("deep"), std::string::npos);
}

// Test printing multiple siblings
TEST_F(XMLPrinterTest_147, PrintMultipleSiblings_147) {
    XMLDocument doc;
    doc.Parse("<root><a/><b/><c/><d/></root>");
    ASSERT_FALSE(doc.Error());
    XMLPrinter printer;
    doc.Accept(&printer);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    std::string output(result);
    EXPECT_NE(output.find("<a/>"), std::string::npos);
    EXPECT_NE(output.find("<b/>"), std::string::npos);
    EXPECT_NE(output.find("<c/>"), std::string::npos);
    EXPECT_NE(output.find("<d/>"), std::string::npos);
}
