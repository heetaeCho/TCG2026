#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tinyxml2.h"

using namespace tinyxml2;
using ::testing::Return;
using ::testing::_;

// Minimal stub for XMLAttribute to allow linking a chain
class MockXMLAttribute : public XMLAttribute {
public:
    MockXMLAttribute(const char* n, const char* v, MockXMLAttribute* next = nullptr)
        : _nameStr(n), _valueStr(v), _nextAttr(next) {}

    const char* Name() const override { return _nameStr; }
    const char* Value() const override { return _valueStr; }
    const XMLAttribute* Next() const override { return _nextAttr; }

private:
    const char* _nameStr;
    const char* _valueStr;
    MockXMLAttribute* _nextAttr;
};

// Minimal stub for XMLElement to allow Parent() and Name()
class MockXMLElement : public XMLElement {
public:
    MockXMLElement(const char* name, XMLElement* parent = nullptr)
        : _name(name), _parent(parent) {}

    XMLElement* Parent() const override { return _parent; }
    const char* Name() const override { return _name; }

private:
    const char* _name;
    XMLElement* _parent;
};

// Test fixture for XMLPrinter
class XMLPrinterTest_317 : public ::testing::Test {
protected:
    void SetUp() override {
        // Using nullptr FILE* and compact mode true for simplicity
        printer = new XMLPrinter(nullptr, true, 0, XMLPrinter::EscapeAposCharsInAttributes::NO);
    }

    void TearDown() override {
        delete printer;
    }

    XMLPrinter* printer;
};

// Test normal operation: single element, no attributes
TEST_F(XMLPrinterTest_317, VisitEnter_SingleElementNoAttributes_317) {
    MockXMLElement elem("Root");
    
    bool result = printer->VisitEnter(elem, nullptr);

    EXPECT_TRUE(result);
    // We can only check observable effect via VisitEnter return value
}

// Test single element with single attribute
TEST_F(XMLPrinterTest_317, VisitEnter_SingleElementSingleAttribute_317) {
    MockXMLElement elem("Root");
    MockXMLAttribute attr("id", "123");

    bool result = printer->VisitEnter(elem, &attr);

    EXPECT_TRUE(result);
    // Only observable: returns true
}

// Test single element with multiple chained attributes
TEST_F(XMLPrinterTest_317, VisitEnter_SingleElementMultipleAttributes_317) {
    MockXMLAttribute attr3("attr3", "val3");
    MockXMLAttribute attr2("attr2", "val2", &attr3);
    MockXMLAttribute attr1("attr1", "val1", &attr2);

    MockXMLElement elem("Root");

    bool result = printer->VisitEnter(elem, &attr1);

    EXPECT_TRUE(result);
}

// Test element with a parent (to check compactMode selection path)
TEST_F(XMLPrinterTest_317, VisitEnter_ElementWithParent_317) {
    MockXMLElement parent("Parent");
    MockXMLElement elem("Child", &parent);

    bool result = printer->VisitEnter(elem, nullptr);

    EXPECT_TRUE(result);
}

// Test VisitEnter with nullptr element name (edge case, observable via no crash)
TEST_F(XMLPrinterTest_317, VisitEnter_ElementWithNullName_317) {
    MockXMLElement elem(nullptr);

    bool result = printer->VisitEnter(elem, nullptr);

    EXPECT_TRUE(result);
}

// Test VisitEnter with nullptr attribute in chain (should safely handle)
TEST_F(XMLPrinterTest_317, VisitEnter_ElementWithNullAttributeNext_317) {
    MockXMLAttribute attr("id", "123", nullptr);
    MockXMLElement elem("Root");

    bool result = printer->VisitEnter(elem, &attr);

    EXPECT_TRUE(result);
}
