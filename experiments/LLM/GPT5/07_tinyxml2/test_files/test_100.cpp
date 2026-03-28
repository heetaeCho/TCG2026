#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

// Fixture for XMLElement tests
class XMLElementSetAttributeInt64Test_100 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* element;

    void SetUp() override {
        element = doc.NewElement("TestElement");
        doc.InsertEndChild(element);
    }
};

// Test normal operation: set and retrieve int64 attribute
TEST_F(XMLElementSetAttributeInt64Test_100, SetAndQueryAttribute_100) {
    const char* attrName = "attr";
    int64_t value = 1234567890123LL;

    element->SetAttribute(attrName, value);

    int64_t queriedValue = 0;
    XMLError err = element->QueryAttribute(attrName, &queriedValue);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(queriedValue, value);
}

// Test boundary values: INT64_MAX
TEST_F(XMLElementSetAttributeInt64Test_100, SetMaxInt64_100) {
    const char* attrName = "maxAttr";
    int64_t maxValue = INT64_MAX;

    element->SetAttribute(attrName, maxValue);

    int64_t queriedValue = 0;
    XMLError err = element->QueryAttribute(attrName, &queriedValue);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(queriedValue, maxValue);
}

// Test boundary values: INT64_MIN
TEST_F(XMLElementSetAttributeInt64Test_100, SetMinInt64_100) {
    const char* attrName = "minAttr";
    int64_t minValue = INT64_MIN;

    element->SetAttribute(attrName, minValue);

    int64_t queriedValue = 0;
    XMLError err = element->QueryAttribute(attrName, &queriedValue);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(queriedValue, minValue);
}

// Test overwriting an existing attribute
TEST_F(XMLElementSetAttributeInt64Test_100, OverwriteAttribute_100) {
    const char* attrName = "attr";
    int64_t firstValue = 100;
    int64_t secondValue = 200;

    element->SetAttribute(attrName, firstValue);
    element->SetAttribute(attrName, secondValue);

    int64_t queriedValue = 0;
    XMLError err = element->QueryAttribute(attrName, &queriedValue);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(queriedValue, secondValue);
}

// Test setting multiple attributes
TEST_F(XMLElementSetAttributeInt64Test_100, SetMultipleAttributes_100) {
    element->SetAttribute("attr1", 1LL);
    element->SetAttribute("attr2", 2LL);
    element->SetAttribute("attr3", 3LL);

    int64_t val1, val2, val3;
    EXPECT_EQ(element->QueryAttribute("attr1", &val1), XML_SUCCESS);
    EXPECT_EQ(val1, 1LL);
    EXPECT_EQ(element->QueryAttribute("attr2", &val2), XML_SUCCESS);
    EXPECT_EQ(val2, 2LL);
    EXPECT_EQ(element->QueryAttribute("attr3", &val3), XML_SUCCESS);
    EXPECT_EQ(val3, 3LL);
}

// Test querying a non-existent attribute
TEST_F(XMLElementSetAttributeInt64Test_100, QueryNonExistentAttribute_100) {
    int64_t value = 0;
    XMLError err = element->QueryAttribute("nonexistent", &value);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
}

// Test using a null attribute name (should not crash)
TEST_F(XMLElementSetAttributeInt64Test_100, NullAttributeName_100) {
    // Behavior undefined; we can only test that it does not crash
    EXPECT_NO_THROW(element->SetAttribute(nullptr, 123LL));
}

// Test setting attribute to zero
TEST_F(XMLElementSetAttributeInt64Test_100, SetZeroValue_100) {
    const char* attrName = "zeroAttr";
    element->SetAttribute(attrName, 0LL);

    int64_t queriedValue = -1;
    EXPECT_EQ(element->QueryAttribute(attrName, &queriedValue), XML_SUCCESS);
    EXPECT_EQ(queriedValue, 0LL);
}
