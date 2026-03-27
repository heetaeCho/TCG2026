// File: ./TestProjects/tinyxml2/test_xmlattribute_queryunsignedvalue_212.cpp

#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class XMLAttributeQueryUnsignedValueTest_212 : public ::testing::Test {
protected:
    static const XMLAttribute* GetAttr(const XMLElement* elem, const char* name) {
        ASSERT_NE(elem, nullptr);
#if defined(TINYXML2_MAJOR_VERSION)
        // tinyxml2 provides FindAttribute in its public API.
        return elem->FindAttribute(name);
#else
        // Fallback: walk attributes if FindAttribute isn't available.
        const XMLAttribute* a = elem->FirstAttribute();
        while (a) {
            if (a->Name() && name && std::string(a->Name()) == name) {
                return a;
            }
            a = a->Next();
        }
        return nullptr;
#endif
    }
};

TEST_F(XMLAttributeQueryUnsignedValueTest_212, ReturnsSuccessAndParsesZero_212) {
    XMLDocument doc;
    ASSERT_EQ(doc.Parse("<root a='0'/>"), XML_SUCCESS);

    const XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const XMLAttribute* attr = GetAttr(root, "a");
    ASSERT_NE(attr, nullptr);

    unsigned int out = 123u;
    EXPECT_EQ(attr->QueryUnsignedValue(&out), XML_SUCCESS);
    EXPECT_EQ(out, 0u);
}

TEST_F(XMLAttributeQueryUnsignedValueTest_212, ReturnsSuccessAndParsesPositiveNumber_212) {
    XMLDocument doc;
    ASSERT_EQ(doc.Parse("<root a='42'/>"), XML_SUCCESS);

    const XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const XMLAttribute* attr = GetAttr(root, "a");
    ASSERT_NE(attr, nullptr);

    unsigned int out = 0u;
    EXPECT_EQ(attr->QueryUnsignedValue(&out), XML_SUCCESS);
    EXPECT_EQ(out, 42u);
}

TEST_F(XMLAttributeQueryUnsignedValueTest_212, ReturnsSuccessAndParsesUIntMax_212) {
    XMLDocument doc;
    // Max for 32-bit unsigned int: 4294967295
    ASSERT_EQ(doc.Parse("<root a='4294967295'/>"), XML_SUCCESS);

    const XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const XMLAttribute* attr = GetAttr(root, "a");
    ASSERT_NE(attr, nullptr);

    unsigned int out = 0u;
    EXPECT_EQ(attr->QueryUnsignedValue(&out), XML_SUCCESS);
    EXPECT_EQ(out, 4294967295u);
}

TEST_F(XMLAttributeQueryUnsignedValueTest_212, ReturnsWrongTypeForNegativeNumberString_212) {
    XMLDocument doc;
    ASSERT_EQ(doc.Parse("<root a='-1'/>"), XML_SUCCESS);

    const XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const XMLAttribute* attr = GetAttr(root, "a");
    ASSERT_NE(attr, nullptr);

    unsigned int out = 7u;
    EXPECT_EQ(attr->QueryUnsignedValue(&out), XML_WRONG_ATTRIBUTE_TYPE);
}

TEST_F(XMLAttributeQueryUnsignedValueTest_212, ReturnsWrongTypeForNonNumericString_212) {
    XMLDocument doc;
    ASSERT_EQ(doc.Parse("<root a='abc'/>"), XML_SUCCESS);

    const XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const XMLAttribute* attr = GetAttr(root, "a");
    ASSERT_NE(attr, nullptr);

    unsigned int out = 7u;
    EXPECT_EQ(attr->QueryUnsignedValue(&out), XML_WRONG_ATTRIBUTE_TYPE);
}

TEST_F(XMLAttributeQueryUnsignedValueTest_212, ReturnsWrongTypeForOverflow_212) {
    XMLDocument doc;
    // One more than 32-bit uint max
    ASSERT_EQ(doc.Parse("<root a='4294967296'/>"), XML_SUCCESS);

    const XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const XMLAttribute* attr = GetAttr(root, "a");
    ASSERT_NE(attr, nullptr);

    unsigned int out = 7u;
    EXPECT_EQ(attr->QueryUnsignedValue(&out), XML_WRONG_ATTRIBUTE_TYPE);
}

TEST_F(XMLAttributeQueryUnsignedValueTest_212, ReturnsWrongTypeForEmptyStringValue_212) {
    XMLDocument doc;
    ASSERT_EQ(doc.Parse("<root a=''/>"), XML_SUCCESS);

    const XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const XMLAttribute* attr = GetAttr(root, "a");
    ASSERT_NE(attr, nullptr);

    unsigned int out = 7u;
    EXPECT_EQ(attr->QueryUnsignedValue(&out), XML_WRONG_ATTRIBUTE_TYPE);
}
