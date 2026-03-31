#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLPrinterVisitEnterTest_317 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test VisitEnter with a simple element with no attributes
TEST_F(XMLPrinterVisitEnterTest_317, SimpleElementNoAttributes_317) {
    XMLDocument doc;
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    XMLPrinter printer(nullptr, false);
    bool result = printer.VisitEnter(*root, nullptr);
    EXPECT_TRUE(result);

    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    // Should contain the element name "root"
    EXPECT_NE(std::string(output).find("root"), std::string::npos);
}

// Test VisitEnter returns true
TEST_F(XMLPrinterVisitEnterTest_317, ReturnsTrue_317) {
    XMLDocument doc;
    doc.Parse("<element/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLPrinter printer(nullptr, false);
    bool result = printer.VisitEnter(*elem, nullptr);
    EXPECT_TRUE(result);
}

// Test VisitEnter with element having a single attribute
TEST_F(XMLPrinterVisitEnterTest_317, ElementWithSingleAttribute_317) {
    XMLDocument doc;
    doc.Parse("<item key=\"value\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);

    XMLPrinter printer(nullptr, false);
    bool result = printer.VisitEnter(*elem, attr);
    EXPECT_TRUE(result);

    std::string output(printer.CStr());
    EXPECT_NE(output.find("key"), std::string::npos);
    EXPECT_NE(output.find("value"), std::string::npos);
}

// Test VisitEnter with element having multiple attributes
TEST_F(XMLPrinterVisitEnterTest_317, ElementWithMultipleAttributes_317) {
    XMLDocument doc;
    doc.Parse("<item a=\"1\" b=\"2\" c=\"3\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);

    XMLPrinter printer(nullptr, false);
    bool result = printer.VisitEnter(*elem, attr);
    EXPECT_TRUE(result);

    std::string output(printer.CStr());
    EXPECT_NE(output.find("a="), std::string::npos);
    EXPECT_NE(output.find("b="), std::string::npos);
    EXPECT_NE(output.find("c="), std::string::npos);
    EXPECT_NE(output.find("\"1\""), std::string::npos);
    EXPECT_NE(output.find("\"2\""), std::string::npos);
    EXPECT_NE(output.find("\"3\""), std::string::npos);
}

// Test VisitEnter with a child element (parent is an element)
TEST_F(XMLPrinterVisitEnterTest_317, ChildElementWithParent_317) {
    XMLDocument doc;
    doc.Parse("<parent><child/></parent>");
    XMLElement* parent = doc.RootElement();
    ASSERT_NE(parent, nullptr);
    XMLElement* child = parent->FirstChildElement("child");
    ASSERT_NE(child, nullptr);

    XMLPrinter printer(nullptr, false);
    // First visit parent
    printer.VisitEnter(*parent, nullptr);
    // Then visit child
    bool result = printer.VisitEnter(*child, nullptr);
    EXPECT_TRUE(result);

    std::string output(printer.CStr());
    EXPECT_NE(output.find("parent"), std::string::npos);
    EXPECT_NE(output.find("child"), std::string::npos);
}

// Test VisitEnter in compact mode
TEST_F(XMLPrinterVisitEnterTest_317, CompactModePrinter_317) {
    XMLDocument doc;
    doc.Parse("<root><child attr=\"val\"/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    XMLPrinter printer(nullptr, true); // compact mode
    bool result = printer.VisitEnter(*root, nullptr);
    EXPECT_TRUE(result);

    std::string output(printer.CStr());
    EXPECT_NE(output.find("<root"), std::string::npos);
}

// Test VisitEnter with element that has no parent element (root-level)
TEST_F(XMLPrinterVisitEnterTest_317, RootElementNoParentElement_317) {
    XMLDocument doc;
    doc.Parse("<standalone/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    // The parent is XMLDocument, not XMLElement
    ASSERT_NE(elem->Parent(), nullptr);
    EXPECT_EQ(elem->Parent()->ToElement(), nullptr);

    XMLPrinter printer(nullptr, false);
    bool result = printer.VisitEnter(*elem, nullptr);
    EXPECT_TRUE(result);

    std::string output(printer.CStr());
    EXPECT_NE(output.find("standalone"), std::string::npos);
}

// Test VisitEnter with element having attributes with special characters
TEST_F(XMLPrinterVisitEnterTest_317, AttributesWithSpecialChars_317) {
    XMLDocument doc;
    doc.Parse("<item desc=\"a &amp; b\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);

    XMLPrinter printer(nullptr, false);
    bool result = printer.VisitEnter(*elem, attr);
    EXPECT_TRUE(result);

    std::string output(printer.CStr());
    EXPECT_NE(output.find("desc"), std::string::npos);
}

// Test full document printing via Accept which internally uses VisitEnter
TEST_F(XMLPrinterVisitEnterTest_317, FullDocumentAccept_317) {
    XMLDocument doc;
    doc.Parse("<root attr1=\"hello\" attr2=\"world\"><child>text</child></root>");
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer(nullptr, false);
    doc.Accept(&printer);

    std::string output(printer.CStr());
    EXPECT_NE(output.find("<root"), std::string::npos);
    EXPECT_NE(output.find("attr1="), std::string::npos);
    EXPECT_NE(output.find("attr2="), std::string::npos);
    EXPECT_NE(output.find("<child"), std::string::npos);
    EXPECT_NE(output.find("text"), std::string::npos);
    EXPECT_NE(output.find("</root>"), std::string::npos);
}

// Test VisitEnter with element that has an empty name attribute value
TEST_F(XMLPrinterVisitEnterTest_317, ElementWithEmptyAttributeValue_317) {
    XMLDocument doc;
    doc.Parse("<item name=\"\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);

    XMLPrinter printer(nullptr, false);
    bool result = printer.VisitEnter(*elem, attr);
    EXPECT_TRUE(result);

    std::string output(printer.CStr());
    EXPECT_NE(output.find("name=\"\""), std::string::npos);
}

// Test VisitEnter with deeply nested elements
TEST_F(XMLPrinterVisitEnterTest_317, DeeplyNestedElements_317) {
    XMLDocument doc;
    doc.Parse("<a><b><c><d/></c></b></a>");
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer(nullptr, false);
    doc.Accept(&printer);

    std::string output(printer.CStr());
    EXPECT_NE(output.find("<a"), std::string::npos);
    EXPECT_NE(output.find("<b"), std::string::npos);
    EXPECT_NE(output.find("<c"), std::string::npos);
    EXPECT_NE(output.find("<d"), std::string::npos);
}

// Test VisitEnter compact mode with nested child elements
TEST_F(XMLPrinterVisitEnterTest_317, CompactModeNestedElements_317) {
    XMLDocument doc;
    doc.Parse("<root><child1/><child2/></root>");
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer(nullptr, true); // compact
    doc.Accept(&printer);

    std::string output(printer.CStr());
    // In compact mode, there should be no extra whitespace/newlines
    EXPECT_NE(output.find("<root>"), std::string::npos);
    EXPECT_NE(output.find("</root>"), std::string::npos);
}

// Test CStr and CStrSize after VisitEnter
TEST_F(XMLPrinterVisitEnterTest_317, CStrSizeAfterVisitEnter_317) {
    XMLDocument doc;
    doc.Parse("<elem/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLPrinter printer(nullptr, false);
    printer.VisitEnter(*elem, nullptr);

    const char* str = printer.CStr();
    ASSERT_NE(str, nullptr);
    size_t size = printer.CStrSize();
    // CStrSize includes the null terminator
    EXPECT_EQ(size, strlen(str) + 1);
}

// Test VisitEnter skipping some attributes (passing second attribute as start)
TEST_F(XMLPrinterVisitEnterTest_317, SkipFirstAttribute_317) {
    XMLDocument doc;
    doc.Parse("<item a=\"1\" b=\"2\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    const XMLAttribute* firstAttr = elem->FirstAttribute();
    ASSERT_NE(firstAttr, nullptr);
    const XMLAttribute* secondAttr = firstAttr->Next();
    ASSERT_NE(secondAttr, nullptr);

    XMLPrinter printer(nullptr, false);
    // Pass second attribute, skipping the first
    bool result = printer.VisitEnter(*elem, secondAttr);
    EXPECT_TRUE(result);

    std::string output(printer.CStr());
    // Should contain second attribute but not the first
    EXPECT_NE(output.find("b="), std::string::npos);
    EXPECT_EQ(output.find("a="), std::string::npos);
}

// Test ClearBuffer and re-use printer
TEST_F(XMLPrinterVisitEnterTest_317, ClearBufferAndReuse_317) {
    XMLDocument doc;
    doc.Parse("<first/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLPrinter printer(nullptr, false);
    printer.VisitEnter(*elem, nullptr);
    
    std::string firstOutput(printer.CStr());
    EXPECT_NE(firstOutput.find("first"), std::string::npos);

    printer.ClearBuffer();

    XMLDocument doc2;
    doc2.Parse("<second/>");
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem2, nullptr);

    printer.VisitEnter(*elem2, nullptr);
    std::string secondOutput(printer.CStr());
    EXPECT_NE(secondOutput.find("second"), std::string::npos);
}
