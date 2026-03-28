// File: ./TestProjects/tinyxml2/tests/test_xmlelement_query_bool_attribute_85.cpp

#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

namespace tinyxml2 {

class QueryBoolAttributeTest_85 : public ::testing::Test {
protected:
    XMLDocument doc_;
    XMLElement* elem_ = nullptr;

    void SetUp() override {
        elem_ = doc_.NewElement("root");
        ASSERT_NE(elem_, nullptr);
        doc_.InsertEndChild(elem_);
    }
};

TEST_F(QueryBoolAttributeTest_85, MissingAttributeReturnsNoAttribute_85) {
    bool out = true;
    const XMLError err = elem_->QueryBoolAttribute("missing", &out);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
}

TEST_F(QueryBoolAttributeTest_85, SetAttributeBoolTrueThenQueryReturnsSuccessAndTrue_85) {
    elem_->SetAttribute("flag", true);

    bool out = false;
    const XMLError err = elem_->QueryBoolAttribute("flag", &out);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(out);
}

TEST_F(QueryBoolAttributeTest_85, SetAttributeBoolFalseThenQueryReturnsSuccessAndFalse_85) {
    elem_->SetAttribute("flag", false);

    bool out = true;
    const XMLError err = elem_->QueryBoolAttribute("flag", &out);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(out);
}

TEST_F(QueryBoolAttributeTest_85, StringTrueIsAccepted_85) {
    elem_->SetAttribute("flag", "true");

    bool out = false;
    const XMLError err = elem_->QueryBoolAttribute("flag", &out);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(out);
}

TEST_F(QueryBoolAttributeTest_85, StringFalseIsAccepted_85) {
    elem_->SetAttribute("flag", "false");

    bool out = true;
    const XMLError err = elem_->QueryBoolAttribute("flag", &out);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(out);
}

TEST_F(QueryBoolAttributeTest_85, NumericOneIsAcceptedAsTrue_85) {
    elem_->SetAttribute("flag", "1");

    bool out = false;
    const XMLError err = elem_->QueryBoolAttribute("flag", &out);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(out);
}

TEST_F(QueryBoolAttributeTest_85, NumericZeroIsAcceptedAsFalse_85) {
    elem_->SetAttribute("flag", "0");

    bool out = true;
    const XMLError err = elem_->QueryBoolAttribute("flag", &out);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(out);
}

TEST_F(QueryBoolAttributeTest_85, NonBooleanStringReturnsWrongAttributeType_85) {
    elem_->SetAttribute("flag", "not_a_bool");

    bool out = false;
    const XMLError err = elem_->QueryBoolAttribute("flag", &out);

    // Treat as a black box: tinyxml2 typically returns XML_WRONG_ATTRIBUTE_TYPE here,
    // but allow XML_CAN_NOT_CONVERT_TEXT as well if implementation maps failures that way.
    EXPECT_TRUE(err == XML_WRONG_ATTRIBUTE_TYPE || err == XML_CAN_NOT_CONVERT_TEXT);
}

TEST_F(QueryBoolAttributeTest_85, OverwritesOutputOnSuccess_85) {
    elem_->SetAttribute("flag", true);

    bool out = false;
    const XMLError err = elem_->QueryBoolAttribute("flag", &out);

    ASSERT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(out);
}

}  // namespace tinyxml2
