// File: ./TestProjects/tinyxml2/tests/XMLElementQueryUnsignedAttribute_test_82.cpp

#include <gtest/gtest.h>

#include <limits>

#include "tinyxml2.h"

namespace {

class QueryUnsignedAttributeTest_82 : public ::testing::Test {
protected:
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement* elem = nullptr;

    void SetUp() override {
        elem = doc.NewElement("root");
        ASSERT_NE(elem, nullptr);
        doc.InsertEndChild(elem);
    }
};

TEST_F(QueryUnsignedAttributeTest_82, MissingAttributeReturnsNoAttribute_82) {
    unsigned int value = 123u;
    const tinyxml2::XMLError err = elem->QueryUnsignedAttribute("missing", &value);
    EXPECT_EQ(tinyxml2::XML_NO_ATTRIBUTE, err);
}

TEST_F(QueryUnsignedAttributeTest_82, ExistingUnsignedAttributeReturnsSuccessAndValue_82) {
    elem->SetAttribute("u", 42u);

    unsigned int value = 0u;
    const tinyxml2::XMLError err = elem->QueryUnsignedAttribute("u", &value);

    EXPECT_EQ(tinyxml2::XML_SUCCESS, err);
    EXPECT_EQ(42u, value);
}

TEST_F(QueryUnsignedAttributeTest_82, ZeroValueParsesSuccessfully_82) {
    elem->SetAttribute("u", 0u);

    unsigned int value = 999u;
    const tinyxml2::XMLError err = elem->QueryUnsignedAttribute("u", &value);

    EXPECT_EQ(tinyxml2::XML_SUCCESS, err);
    EXPECT_EQ(0u, value);
}

TEST_F(QueryUnsignedAttributeTest_82, MaxUnsignedValueParsesSuccessfully_82) {
    const unsigned int kMax = (std::numeric_limits<unsigned int>::max)();
    elem->SetAttribute("u", kMax);

    unsigned int value = 0u;
    const tinyxml2::XMLError err = elem->QueryUnsignedAttribute("u", &value);

    EXPECT_EQ(tinyxml2::XML_SUCCESS, err);
    EXPECT_EQ(kMax, value);
}

TEST_F(QueryUnsignedAttributeTest_82, NonNumericValueReturnsWrongAttributeType_82) {
    elem->SetAttribute("u", "not_a_number");

    unsigned int value = 7u;
    const tinyxml2::XMLError err = elem->QueryUnsignedAttribute("u", &value);

    EXPECT_EQ(tinyxml2::XML_WRONG_ATTRIBUTE_TYPE, err);
}

TEST_F(QueryUnsignedAttributeTest_82, NegativeNumericStringReturnsWrongAttributeType_82) {
    // Stored as a string attribute; querying as unsigned should fail.
    elem->SetAttribute("u", "-1");

    unsigned int value = 7u;
    const tinyxml2::XMLError err = elem->QueryUnsignedAttribute("u", &value);

    EXPECT_EQ(tinyxml2::XML_WRONG_ATTRIBUTE_TYPE, err);
}

TEST_F(QueryUnsignedAttributeTest_82, AfterDeleteAttributeReturnsNoAttribute_82) {
    elem->SetAttribute("u", 10u);
    elem->DeleteAttribute("u");

    unsigned int value = 0u;
    const tinyxml2::XMLError err = elem->QueryUnsignedAttribute("u", &value);

    EXPECT_EQ(tinyxml2::XML_NO_ATTRIBUTE, err);
}

}  // namespace
