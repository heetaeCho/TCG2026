// TEST_ID: 215
#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

namespace {

const XMLAttribute* GetAttrOrFail_215(XMLDocument& doc, const char* xml, const char* elemName,
                                     const char* attrName) {
    doc.Clear();
    doc.Parse(xml);
    EXPECT_EQ(XML_SUCCESS, doc.ErrorID()) << "XML parse failed for: " << xml;

    XMLElement* elem = doc.FirstChildElement(elemName);
    EXPECT_NE(nullptr, elem) << "Element not found: " << (elemName ? elemName : "(null)");

    const XMLAttribute* attr = elem ? elem->FindAttribute(attrName) : nullptr;
    EXPECT_NE(nullptr, attr) << "Attribute not found: " << (attrName ? attrName : "(null)");
    return attr;
}

}  // namespace

class XMLAttributeQueryBoolValueTest_215 : public ::testing::Test {
protected:
    XMLDocument doc_;
};

TEST_F(XMLAttributeQueryBoolValueTest_215, ParsesTrueLiteral_ReturnsSuccessAndSetsTrue_215) {
    const XMLAttribute* attr =
        GetAttrOrFail_215(doc_, "<root a='true'/>", "root", "a");
    ASSERT_NE(nullptr, attr);

    bool value = false;
    XMLError err = attr->QueryBoolValue(&value);

    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_TRUE(value);
}

TEST_F(XMLAttributeQueryBoolValueTest_215, ParsesFalseLiteral_ReturnsSuccessAndSetsFalse_215) {
    const XMLAttribute* attr =
        GetAttrOrFail_215(doc_, "<root a='false'/>", "root", "a");
    ASSERT_NE(nullptr, attr);

    bool value = true;
    XMLError err = attr->QueryBoolValue(&value);

    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FALSE(value);
}

TEST_F(XMLAttributeQueryBoolValueTest_215, ParsesOne_ReturnsSuccessAndSetsTrue_215) {
    const XMLAttribute* attr =
        GetAttrOrFail_215(doc_, "<root a='1'/>", "root", "a");
    ASSERT_NE(nullptr, attr);

    bool value = false;
    XMLError err = attr->QueryBoolValue(&value);

    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_TRUE(value);
}

TEST_F(XMLAttributeQueryBoolValueTest_215, ParsesZero_ReturnsSuccessAndSetsFalse_215) {
    const XMLAttribute* attr =
        GetAttrOrFail_215(doc_, "<root a='0'/>", "root", "a");
    ASSERT_NE(nullptr, attr);

    bool value = true;
    XMLError err = attr->QueryBoolValue(&value);

    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FALSE(value);
}

TEST_F(XMLAttributeQueryBoolValueTest_215, NonBooleanString_ReturnsWrongAttributeType_215) {
    const XMLAttribute* attr =
        GetAttrOrFail_215(doc_, "<root a='notabool'/>", "root", "a");
    ASSERT_NE(nullptr, attr);

    bool value = false;  // value content is not asserted on failure
    XMLError err = attr->QueryBoolValue(&value);

    EXPECT_EQ(XML_WRONG_ATTRIBUTE_TYPE, err);
}

TEST_F(XMLAttributeQueryBoolValueTest_215, EmptyString_ReturnsWrongAttributeType_215) {
    const XMLAttribute* attr =
        GetAttrOrFail_215(doc_, "<root a=''/>", "root", "a");
    ASSERT_NE(nullptr, attr);

    bool value = false;
    XMLError err = attr->QueryBoolValue(&value);

    EXPECT_EQ(XML_WRONG_ATTRIBUTE_TYPE, err);
}
