// TEST_ID: 89
#include <gtest/gtest.h>

#include <limits>
#include <string>

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class XMLElementQueryAttributeIntTest_89 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* root = nullptr;

    void SetUp() override {
        // Include: valid ints, negative, non-int, and int boundary values.
        const char* xml =
            "<root a='42' b='-7' bad='abc' "
            "imax='2147483647' imin='-2147483648' />";
        ASSERT_EQ(doc.Parse(xml), XML_SUCCESS);
        root = doc.FirstChildElement("root");
        ASSERT_NE(root, nullptr);
    }
};

TEST_F(XMLElementQueryAttributeIntTest_89, ReadsValidIntAttribute_89) {
    int value = 0;
    const XMLError err = root->QueryAttribute("a", &value);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 42);
}

TEST_F(XMLElementQueryAttributeIntTest_89, MatchesQueryIntAttributeOnSuccess_89) {
    int via_query_attribute = 123;
    int via_query_int_attr  = 456;

    const XMLError e1 = root->QueryAttribute("b", &via_query_attribute);
    const XMLError e2 = root->QueryIntAttribute("b", &via_query_int_attr);

    EXPECT_EQ(e1, e2);
    EXPECT_EQ(via_query_attribute, via_query_int_attr);
    if (e1 == XML_SUCCESS) {
        EXPECT_EQ(via_query_attribute, -7);
    }
}

TEST_F(XMLElementQueryAttributeIntTest_89, MissingAttributeMatchesQueryIntAttribute_89) {
    int v1 = 111;
    int v2 = 111;

    const XMLError e1 = root->QueryAttribute("does_not_exist", &v1);
    const XMLError e2 = root->QueryIntAttribute("does_not_exist", &v2);

    EXPECT_EQ(e1, e2);
    // Black-box friendly: verify both APIs affect the output identically.
    EXPECT_EQ(v1, v2);
}

TEST_F(XMLElementQueryAttributeIntTest_89, NonIntegerAttributeMatchesQueryIntAttribute_89) {
    int v1 = 222;
    int v2 = 222;

    const XMLError e1 = root->QueryAttribute("bad", &v1);
    const XMLError e2 = root->QueryIntAttribute("bad", &v2);

    EXPECT_EQ(e1, e2);
    EXPECT_EQ(v1, v2);
}

TEST_F(XMLElementQueryAttributeIntTest_89, BoundaryValuesMatchQueryIntAttribute_89) {
    // INT_MAX
    {
        int v1 = 0, v2 = 0;
        const XMLError e1 = root->QueryAttribute("imax", &v1);
        const XMLError e2 = root->QueryIntAttribute("imax", &v2);

        EXPECT_EQ(e1, e2);
        EXPECT_EQ(v1, v2);
        if (e1 == XML_SUCCESS) {
            EXPECT_EQ(v1, std::numeric_limits<int>::max());
        }
    }

    // INT_MIN
    {
        int v1 = 0, v2 = 0;
        const XMLError e1 = root->QueryAttribute("imin", &v1);
        const XMLError e2 = root->QueryIntAttribute("imin", &v2);

        EXPECT_EQ(e1, e2);
        EXPECT_EQ(v1, v2);
        if (e1 == XML_SUCCESS) {
            EXPECT_EQ(v1, std::numeric_limits<int>::min());
        }
    }
}
