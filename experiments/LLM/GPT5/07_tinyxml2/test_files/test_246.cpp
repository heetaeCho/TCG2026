// File: test_xml_element_query_int64_text_246.cpp

#include <cstdint>
#include <limits>

#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class QueryInt64TextTest_246 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* elem = nullptr;

    void SetUp() override {
        elem = doc.NewElement("root");
        ASSERT_NE(elem, nullptr);
        doc.InsertEndChild(elem);
    }
};

}  // namespace

TEST_F(QueryInt64TextTest_246, ReturnsSuccessAndParsesWhenTextSetWithInt64_246) {
    const int64_t expected = 1234567890123LL;
    elem->SetText(expected);

    int64_t out = 0;
    const XMLError err = elem->QueryInt64Text(&out);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(out, expected);
}

TEST_F(QueryInt64TextTest_246, ReturnsSuccessAndParsesWhenTextSetWithCStringNumeric_246) {
    elem->SetText("42");

    int64_t out = -1;
    const XMLError err = elem->QueryInt64Text(&out);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(out, 42);
}

TEST_F(QueryInt64TextTest_246, ReturnsSuccessForInt64MinBoundary_246) {
    const int64_t expected = (std::numeric_limits<int64_t>::min)();
    elem->SetText(expected);

    int64_t out = 0;
    const XMLError err = elem->QueryInt64Text(&out);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(out, expected);
}

TEST_F(QueryInt64TextTest_246, ReturnsSuccessForInt64MaxBoundary_246) {
    const int64_t expected = (std::numeric_limits<int64_t>::max)();
    elem->SetText(expected);

    int64_t out = 0;
    const XMLError err = elem->QueryInt64Text(&out);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(out, expected);
}

TEST_F(QueryInt64TextTest_246, ReturnsNoTextNodeWhenElementHasNoChildren_246) {
    int64_t out = 777;  // value should not matter; only return code is asserted
    const XMLError err = elem->QueryInt64Text(&out);

    EXPECT_EQ(err, XML_NO_TEXT_NODE);
}

TEST_F(QueryInt64TextTest_246, ReturnsCanNotConvertTextWhenTextIsNonNumeric_246) {
    elem->SetText("not-a-number");

    int64_t out = 0;
    const XMLError err = elem->QueryInt64Text(&out);

    EXPECT_EQ(err, XML_CAN_NOT_CONVERT_TEXT);
}
