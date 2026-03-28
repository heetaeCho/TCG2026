#include "tinyxml2.h"
#include "gtest/gtest.h"

using namespace tinyxml2;

class XMLElementSetAttributeUint64Test_101 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* element;

    void SetUp() override {
        element = doc.NewElement("TestElement");
        doc.InsertEndChild(element);
    }

    void TearDown() override {
        doc.Clear();
    }
};

// Test normal operation: set and retrieve a uint64_t attribute
TEST_F(XMLElementSetAttributeUint64Test_101, SetAndGetAttribute_101) {
    const char* attrName = "attr";
    uint64_t value = 123456789012345ULL;

    element->SetAttribute(attrName, value);

    uint64_t queriedValue = 0;
    XMLError err = element->QueryUnsigned64Attribute(attrName, &queriedValue);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(queriedValue, value);
}

// Test boundary case: set attribute to 0
TEST_F(XMLElementSetAttributeUint64Test_101, SetAttributeZero_101) {
    const char* attrName = "zeroAttr";
    uint64_t value = 0;

    element->SetAttribute(attrName, value);

    uint64_t queriedValue = 1; // initialize differently
    XMLError err = element->QueryUnsigned64Attribute(attrName, &queriedValue);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(queriedValue, value);
}

// Test boundary case: set attribute to maximum uint64_t
TEST_F(XMLElementSetAttributeUint64Test_101, SetAttributeMaxUint64_101) {
    const char* attrName = "maxAttr";
    uint64_t value = std::numeric_limits<uint64_t>::max();

    element->SetAttribute(attrName, value);

    uint64_t queriedValue = 0;
    XMLError err = element->QueryUnsigned64Attribute(attrName, &queriedValue);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(queriedValue, value);
}

// Test overwriting an existing attribute
TEST_F(XMLElementSetAttributeUint64Test_101, OverwriteAttribute_101) {
    const char* attrName = "attr";
    uint64_t initialValue = 10;
    uint64_t newValue = 20;

    element->SetAttribute(attrName, initialValue);
    element->SetAttribute(attrName, newValue);

    uint64_t queriedValue = 0;
    XMLError err = element->QueryUnsigned64Attribute(attrName, &queriedValue);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(queriedValue, newValue);
}

// Test error case: querying a non-existent attribute
TEST_F(XMLElementSetAttributeUint64Test_101, QueryNonExistentAttribute_101) {
    const char* attrName = "nonexistent";

    uint64_t queriedValue = 0;
    XMLError err = element->QueryUnsigned64Attribute(attrName, &queriedValue);

    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
}

// Test multiple attributes to ensure no interference
TEST_F(XMLElementSetAttributeUint64Test_101, MultipleAttributes_101) {
    element->SetAttribute("attr1", 111ULL);
    element->SetAttribute("attr2", 222ULL);
    element->SetAttribute("attr3", 333ULL);

    uint64_t value = 0;

    EXPECT_EQ(element->QueryUnsigned64Attribute("attr1", &value), XML_SUCCESS);
    EXPECT_EQ(value, 111ULL);

    EXPECT_EQ(element->QueryUnsigned64Attribute("attr2", &value), XML_SUCCESS);
    EXPECT_EQ(value, 222ULL);

    EXPECT_EQ(element->QueryUnsigned64Attribute("attr3", &value), XML_SUCCESS);
    EXPECT_EQ(value, 333ULL);
}
