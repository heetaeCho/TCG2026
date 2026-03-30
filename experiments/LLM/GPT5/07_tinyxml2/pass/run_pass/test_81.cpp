#include <climits>
#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class QueryIntAttributeTest_81 : public ::testing::Test {
protected:
    XMLDocument doc;

    XMLElement* ParseSingleRoot(const char* xml) {
        EXPECT_NE(xml, nullptr);
        const XMLError err = doc.Parse(xml);
        EXPECT_EQ(err, XML_SUCCESS);
        XMLElement* root = doc.RootElement();
        EXPECT_NE(root, nullptr);
        return root;
    }
};

TEST_F(QueryIntAttributeTest_81, ReturnsNoAttributeWhenMissing_81) {
    XMLElement* root = ParseSingleRoot("<root/>");

    int value = 12345;  // sentinel
    const XMLError err = root->QueryIntAttribute("missing", &value);

    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
    // Observable expectation: missing attribute should not be created by a query.
    EXPECT_EQ(root->FirstAttribute(), nullptr);
    // Observable expectation: output should remain unchanged on missing attribute.
    EXPECT_EQ(value, 12345);
}

TEST_F(QueryIntAttributeTest_81, ReturnsSuccessAndParsesPositiveInt_81) {
    XMLElement* root = ParseSingleRoot("<root a='42'/>");

    int value = 0;
    const XMLError err = root->QueryIntAttribute("a", &value);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 42);
}

TEST_F(QueryIntAttributeTest_81, ParsesNegativeInt_81) {
    XMLElement* root = ParseSingleRoot("<root a='-7'/>");

    int value = 0;
    const XMLError err = root->QueryIntAttribute("a", &value);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, -7);
}

TEST_F(QueryIntAttributeTest_81, ParsesZero_81) {
    XMLElement* root = ParseSingleRoot("<root a='0'/>");

    int value = 99;
    const XMLError err = root->QueryIntAttribute("a", &value);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 0);
}

TEST_F(QueryIntAttributeTest_81, ParsesIntMax_81) {
    XMLElement* root = ParseSingleRoot("<root a='2147483647'/>");

    int value = 0;
    const XMLError err = root->QueryIntAttribute("a", &value);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, INT_MAX);
}

TEST_F(QueryIntAttributeTest_81, ReturnsWrongAttributeTypeForNonNumeric_81) {
    XMLElement* root = ParseSingleRoot("<root a='abc'/>");

    int value = 777;  // sentinel
    const XMLError err = root->QueryIntAttribute("a", &value);

    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
    // Observable expectation: value should not be overwritten on type error.
    EXPECT_EQ(value, 777);
}
