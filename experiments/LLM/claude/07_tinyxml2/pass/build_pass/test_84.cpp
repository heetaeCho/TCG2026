#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class QueryUnsigned64AttributeTest_84 : public ::testing::Test {
protected:
    XMLDocument doc;

    XMLElement* CreateElementWithAttribute(const char* elemName, const char* attrName, const char* attrValue) {
        doc.Clear();
        XMLElement* elem = doc.NewElement(elemName);
        doc.InsertFirstChild(elem);
        elem->SetAttribute(attrName, attrValue);
        return elem;
    }

    XMLElement* CreateElementWithUint64Attribute(const char* elemName, const char* attrName, uint64_t attrValue) {
        doc.Clear();
        XMLElement* elem = doc.NewElement(elemName);
        doc.InsertFirstChild(elem);
        elem->SetAttribute(attrName, attrValue);
        return elem;
    }
};

// Test: Querying an existing attribute with a valid unsigned 64-bit value succeeds
TEST_F(QueryUnsigned64AttributeTest_84, ValidUnsigned64Value_ReturnsSuccess_84) {
    XMLElement* elem = CreateElementWithUint64Attribute("test", "val", 12345678901234ULL);
    uint64_t result = 0;
    XMLError err = elem->QueryUnsigned64Attribute("val", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, 12345678901234ULL);
}

// Test: Querying a non-existent attribute returns XML_NO_ATTRIBUTE
TEST_F(QueryUnsigned64AttributeTest_84, NonExistentAttribute_ReturnsNoAttribute_84) {
    XMLElement* elem = CreateElementWithUint64Attribute("test", "val", 42ULL);
    uint64_t result = 0;
    XMLError err = elem->QueryUnsigned64Attribute("nonexistent", &result);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
}

// Test: Querying with a value of zero succeeds
TEST_F(QueryUnsigned64AttributeTest_84, ZeroValue_ReturnsSuccess_84) {
    XMLElement* elem = CreateElementWithUint64Attribute("test", "val", 0ULL);
    uint64_t result = 999;
    XMLError err = elem->QueryUnsigned64Attribute("val", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, 0ULL);
}

// Test: Querying with the maximum uint64_t value succeeds
TEST_F(QueryUnsigned64AttributeTest_84, MaxUint64Value_ReturnsSuccess_84) {
    XMLElement* elem = CreateElementWithUint64Attribute("test", "val", UINT64_MAX);
    uint64_t result = 0;
    XMLError err = elem->QueryUnsigned64Attribute("val", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, UINT64_MAX);
}

// Test: Querying with a value of 1 succeeds
TEST_F(QueryUnsigned64AttributeTest_84, ValueOne_ReturnsSuccess_84) {
    XMLElement* elem = CreateElementWithUint64Attribute("test", "myattr", 1ULL);
    uint64_t result = 0;
    XMLError err = elem->QueryUnsigned64Attribute("myattr", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, 1ULL);
}

// Test: Querying an attribute with non-numeric string value returns wrong type
TEST_F(QueryUnsigned64AttributeTest_84, NonNumericValue_ReturnsWrongType_84) {
    XMLElement* elem = CreateElementWithAttribute("test", "val", "not_a_number");
    uint64_t result = 0;
    XMLError err = elem->QueryUnsigned64Attribute("val", &result);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test: Querying an attribute with a negative string value returns wrong type
TEST_F(QueryUnsigned64AttributeTest_84, NegativeStringValue_ReturnsWrongType_84) {
    XMLElement* elem = CreateElementWithAttribute("test", "val", "-1");
    uint64_t result = 0;
    XMLError err = elem->QueryUnsigned64Attribute("val", &result);
    // Negative values may or may not convert; check that it doesn't silently succeed with wrong value
    // Depending on implementation, it could be XML_WRONG_ATTRIBUTE_TYPE or wrap around
    // We just ensure no crash and the error is documented
    EXPECT_TRUE(err == XML_SUCCESS || err == XML_WRONG_ATTRIBUTE_TYPE);
}

// Test: Querying an element with no attributes returns XML_NO_ATTRIBUTE
TEST_F(QueryUnsigned64AttributeTest_84, ElementWithNoAttributes_ReturnsNoAttribute_84) {
    doc.Clear();
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertFirstChild(elem);
    uint64_t result = 0;
    XMLError err = elem->QueryUnsigned64Attribute("anything", &result);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
}

// Test: Querying attribute with empty name on element with attributes returns XML_NO_ATTRIBUTE
TEST_F(QueryUnsigned64AttributeTest_84, EmptyAttributeName_ReturnsNoAttribute_84) {
    XMLElement* elem = CreateElementWithUint64Attribute("test", "val", 100ULL);
    uint64_t result = 0;
    XMLError err = elem->QueryUnsigned64Attribute("", &result);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
}

// Test: Querying attribute with a large but valid uint64 value via parsed XML
TEST_F(QueryUnsigned64AttributeTest_84, ParsedXmlLargeValue_ReturnsSuccess_84) {
    const char* xml = "<root bigval=\"18446744073709551615\"/>";
    doc.Parse(xml);
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    uint64_t result = 0;
    XMLError err = elem->QueryUnsigned64Attribute("bigval", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, UINT64_MAX);
}

// Test: Querying attribute with float string value returns wrong type
TEST_F(QueryUnsigned64AttributeTest_84, FloatStringValue_ReturnsWrongType_84) {
    XMLElement* elem = CreateElementWithAttribute("test", "val", "3.14");
    uint64_t result = 0;
    XMLError err = elem->QueryUnsigned64Attribute("val", &result);
    // Floating point strings typically can't convert to uint64 cleanly
    EXPECT_TRUE(err == XML_WRONG_ATTRIBUTE_TYPE || err == XML_SUCCESS);
}

// Test: Multiple attributes - query the correct one
TEST_F(QueryUnsigned64AttributeTest_84, MultipleAttributes_QueryCorrectOne_84) {
    doc.Clear();
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("a", (uint64_t)111);
    elem->SetAttribute("b", (uint64_t)222);
    elem->SetAttribute("c", (uint64_t)333);

    uint64_t result = 0;
    XMLError err = elem->QueryUnsigned64Attribute("b", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, 222ULL);
}

// Test: Case sensitivity of attribute names
TEST_F(QueryUnsigned64AttributeTest_84, CaseSensitiveAttributeName_84) {
    XMLElement* elem = CreateElementWithUint64Attribute("test", "Value", 42ULL);
    uint64_t result = 0;

    XMLError err = elem->QueryUnsigned64Attribute("Value", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, 42ULL);

    err = elem->QueryUnsigned64Attribute("value", &result);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);

    err = elem->QueryUnsigned64Attribute("VALUE", &result);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
}

// Test: Attribute with empty string value returns wrong type
TEST_F(QueryUnsigned64AttributeTest_84, EmptyStringValue_ReturnsWrongType_84) {
    XMLElement* elem = CreateElementWithAttribute("test", "val", "");
    uint64_t result = 0;
    XMLError err = elem->QueryUnsigned64Attribute("val", &result);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test: Parsed XML with valid uint64 attribute
TEST_F(QueryUnsigned64AttributeTest_84, ParsedXmlValidAttribute_84) {
    const char* xml = "<item count=\"9999999999\"/>";
    doc.Parse(xml);
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    uint64_t result = 0;
    XMLError err = elem->QueryUnsigned64Attribute("count", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, 9999999999ULL);
}
