#include "tinyxml2.h"
#include <gtest/gtest.h>

using namespace tinyxml2;

class XMLPrinterTest_151 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that default XMLPrinter (non-compact mode) returns false for CompactMode
TEST_F(XMLPrinterTest_151, DefaultPrinterCompactModeIsFalse_151) {
    XMLPrinter printer;
    
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    const XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);
    
    // Default printer should not be in compact mode
    bool result = printer.CompactMode(*element);
    EXPECT_FALSE(result);
}

// Test that XMLPrinter created with compact=true returns true for CompactMode
TEST_F(XMLPrinterTest_151, CompactPrinterCompactModeIsTrue_151) {
    XMLPrinter printer(nullptr, true); // compact = true
    
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    const XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);
    
    bool result = printer.CompactMode(*element);
    EXPECT_TRUE(result);
}

// Test CompactMode with a more complex element
TEST_F(XMLPrinterTest_151, CompactModeWithNestedElement_151) {
    XMLPrinter printer(nullptr, false);
    
    XMLDocument doc;
    doc.Parse("<root><parent><child attr=\"value\">text</child></parent></root>");
    const XMLElement* element = doc.RootElement()->FirstChildElement("parent");
    ASSERT_NE(element, nullptr);
    
    bool result = printer.CompactMode(*element);
    EXPECT_FALSE(result);
}

// Test CompactMode with compact printer on nested element
TEST_F(XMLPrinterTest_151, CompactModeWithNestedElementCompact_151) {
    XMLPrinter printer(nullptr, true);
    
    XMLDocument doc;
    doc.Parse("<root><parent><child attr=\"value\">text</child></parent></root>");
    const XMLElement* element = doc.RootElement()->FirstChildElement("parent");
    ASSERT_NE(element, nullptr);
    
    bool result = printer.CompactMode(*element);
    EXPECT_TRUE(result);
}

// Test CompactMode with an element that has attributes
TEST_F(XMLPrinterTest_151, CompactModeWithElementHavingAttributes_151) {
    XMLPrinter printer;
    
    XMLDocument doc;
    doc.Parse("<root attr1=\"val1\" attr2=\"val2\"/>");
    const XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);
    
    bool result = printer.CompactMode(*element);
    EXPECT_FALSE(result);
}

// Test CompactMode with empty element
TEST_F(XMLPrinterTest_151, CompactModeWithEmptyElement_151) {
    XMLPrinter printer;
    
    XMLDocument doc;
    doc.Parse("<empty/>");
    const XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);
    
    bool result = printer.CompactMode(*element);
    EXPECT_FALSE(result);
}

// Test CompactMode consistency - calling multiple times returns same result
TEST_F(XMLPrinterTest_151, CompactModeConsistentResults_151) {
    XMLPrinter printer(nullptr, true);
    
    XMLDocument doc;
    doc.Parse("<root>text</root>");
    const XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);
    
    bool result1 = printer.CompactMode(*element);
    bool result2 = printer.CompactMode(*element);
    EXPECT_EQ(result1, result2);
    EXPECT_TRUE(result1);
}

// Test CompactMode with different elements returns same mode
TEST_F(XMLPrinterTest_151, CompactModeSameForDifferentElements_151) {
    XMLPrinter printer(nullptr, false);
    
    XMLDocument doc;
    doc.Parse("<root><a/><b/></root>");
    const XMLElement* elemA = doc.RootElement()->FirstChildElement("a");
    const XMLElement* elemB = doc.RootElement()->FirstChildElement("b");
    ASSERT_NE(elemA, nullptr);
    ASSERT_NE(elemB, nullptr);
    
    EXPECT_EQ(printer.CompactMode(*elemA), printer.CompactMode(*elemB));
    EXPECT_FALSE(printer.CompactMode(*elemA));
}
