#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class XMLElementQueryDoubleAttributeTest_86 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* elem = nullptr;

    void SetUp() override {
        elem = doc.NewElement("root");
        ASSERT_NE(elem, nullptr);
        doc.InsertEndChild(elem);
    }
};

TEST_F(XMLElementQueryDoubleAttributeTest_86, ReturnsSuccessAndWritesValue_WhenAttributeIsDouble_86) {
    elem->SetAttribute("pi", 3.141592653589793);

    double v = 0.0;
    const XMLError err = elem->QueryDoubleAttribute("pi", &v);

    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_DOUBLE_EQ(3.141592653589793, v);
}

TEST_F(XMLElementQueryDoubleAttributeTest_86, ReturnsSuccess_WhenAttributeIsNumericString_86) {
    elem->SetAttribute("num", "2.5");

    double v = 0.0;
    const XMLError err = elem->QueryDoubleAttribute("num", &v);

    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_DOUBLE_EQ(2.5, v);
}

TEST_F(XMLElementQueryDoubleAttributeTest_86, ReturnsNoAttribute_WhenAttributeIsMissing_86) {
    double v = 123.0;  // value content is not part of this test's contract
    const XMLError err = elem->QueryDoubleAttribute("missing", &v);

    EXPECT_EQ(XML_NO_ATTRIBUTE, err);
}

TEST_F(XMLElementQueryDoubleAttributeTest_86, ReturnsWrongType_WhenAttributeIsNotConvertibleToDouble_86) {
    elem->SetAttribute("bad", "not-a-number");

    double v = 0.0;
    const XMLError err = elem->QueryDoubleAttribute("bad", &v);

    EXPECT_EQ(XML_WRONG_ATTRIBUTE_TYPE, err);
}

TEST_F(XMLElementQueryDoubleAttributeTest_86, ReturnsLatestValue_WhenAttributeIsOverwritten_86) {
    elem->SetAttribute("x", 1.0);
    elem->SetAttribute("x", 2.0);

    double v = 0.0;
    const XMLError err = elem->QueryDoubleAttribute("x", &v);

    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_DOUBLE_EQ(2.0, v);
}

TEST_F(XMLElementQueryDoubleAttributeTest_86, HandlesLargeMagnitudeValues_86) {
    const double large = 1e308;
    elem->SetAttribute("large", large);

    double v = 0.0;
    const XMLError err = elem->QueryDoubleAttribute("large", &v);

    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_DOUBLE_EQ(large, v);
}
