// File: test_tinyxml2_xmlelement_query_unsigned64_text_247.cpp

#include <cstdint>
#include <limits>

#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class QueryUnsigned64TextTest_247 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* elem = nullptr;

    void SetUp() override {
        elem = doc.NewElement("root");
        ASSERT_NE(elem, nullptr);
        doc.InsertEndChild(elem);
    }
};

TEST_F(QueryUnsigned64TextTest_247, ReturnsNoTextNodeWhenElementHasNoChildren_247) {
    uint64_t out = 123;
    const XMLError err = elem->QueryUnsigned64Text(&out);
    EXPECT_EQ(err, XML_NO_TEXT_NODE);
}

TEST_F(QueryUnsigned64TextTest_247, ReturnsNoTextNodeWhenFirstChildIsElement_247) {
    ASSERT_NE(elem->InsertNewChildElement("child"), nullptr);

    uint64_t out = 0;
    const XMLError err = elem->QueryUnsigned64Text(&out);
    EXPECT_EQ(err, XML_NO_TEXT_NODE);
}

TEST_F(QueryUnsigned64TextTest_247, ReturnsNoTextNodeWhenFirstChildIsComment_247) {
    ASSERT_NE(elem->InsertNewComment("comment"), nullptr);

    uint64_t out = 0;
    const XMLError err = elem->QueryUnsigned64Text(&out);
    EXPECT_EQ(err, XML_NO_TEXT_NODE);
}

TEST_F(QueryUnsigned64TextTest_247, SucceedsAndParsesZero_247) {
    elem->SetText(static_cast<uint64_t>(0));

    uint64_t out = 999;
    const XMLError err = elem->QueryUnsigned64Text(&out);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(out, 0u);
}

TEST_F(QueryUnsigned64TextTest_247, SucceedsAndParsesMaxUint64_247) {
    const uint64_t maxv = (std::numeric_limits<uint64_t>::max)();
    elem->SetText(maxv);

    uint64_t out = 0;
    const XMLError err = elem->QueryUnsigned64Text(&out);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(out, maxv);
}

TEST_F(QueryUnsigned64TextTest_247, ReturnsCanNotConvertTextForNonNumericText_247) {
    elem->SetText("not_a_number");

    uint64_t out = 0;
    const XMLError err = elem->QueryUnsigned64Text(&out);
    EXPECT_EQ(err, XML_CAN_NOT_CONVERT_TEXT);
}

TEST_F(QueryUnsigned64TextTest_247, ReturnsCanNotConvertTextForNegativeText_247) {
    elem->SetText("-1");

    uint64_t out = 0;
    const XMLError err = elem->QueryUnsigned64Text(&out);
    EXPECT_EQ(err, XML_CAN_NOT_CONVERT_TEXT);
}

TEST_F(QueryUnsigned64TextTest_247, ReturnsCanNotConvertTextForOverflowText_247) {
    // One above uint64_t max: 18446744073709551615 + 1
    elem->SetText("18446744073709551616");

    uint64_t out = 0;
    const XMLError err = elem->QueryUnsigned64Text(&out);
    EXPECT_EQ(err, XML_CAN_NOT_CONVERT_TEXT);
}
