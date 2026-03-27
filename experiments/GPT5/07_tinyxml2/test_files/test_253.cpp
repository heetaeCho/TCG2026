// File: TestProjects/tinyxml2/tests/XMLElementInt64TextTest_253.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <string>

#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementInt64TextTest_253 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* elem = nullptr;

    void SetUp() override {
        elem = doc.NewElement("e");
        ASSERT_NE(elem, nullptr);
        doc.InsertFirstChild(elem);
    }
};

TEST_F(XMLElementInt64TextTest_253, ReturnsValueSetBySetTextInt64_253) {
    const int64_t v = 1234567890123LL;
    elem->SetText(v);

    EXPECT_EQ(elem->Int64Text(0), v);
    EXPECT_EQ(elem->Int64Text(42), v);
    EXPECT_EQ(elem->Int64Text(std::numeric_limits<int64_t>::min()), v);
}

TEST_F(XMLElementInt64TextTest_253, ReturnsValueForNegativeAndZero_253) {
    elem->SetText(int64_t{0});
    EXPECT_EQ(elem->Int64Text(-7), int64_t{0});

    elem->SetText(int64_t{-1});
    EXPECT_EQ(elem->Int64Text(999), int64_t{-1});

    elem->SetText(int64_t{-9876543210LL});
    EXPECT_EQ(elem->Int64Text(0), int64_t{-9876543210LL});
}

TEST_F(XMLElementInt64TextTest_253, HandlesInt64MinAndMaxBoundaries_253) {
    const int64_t kMin = std::numeric_limits<int64_t>::min();
    const int64_t kMax = std::numeric_limits<int64_t>::max();

    elem->SetText(kMin);
    EXPECT_EQ(elem->Int64Text(0), kMin);

    elem->SetText(kMax);
    EXPECT_EQ(elem->Int64Text(0), kMax);
}

TEST_F(XMLElementInt64TextTest_253, EmptyElementReturnsDefault_253) {
    // No text set at all.
    const int64_t def1 = 111;
    const int64_t def2 = -222;

    EXPECT_EQ(elem->Int64Text(def1), def1);
    EXPECT_EQ(elem->Int64Text(def2), def2);
}

TEST_F(XMLElementInt64TextTest_253, NonNumericTextReturnsDefault_253) {
    elem->SetText("not-a-number");

    EXPECT_EQ(elem->Int64Text(0), int64_t{0});
    EXPECT_EQ(elem->Int64Text(77), int64_t{77});
    EXPECT_EQ(elem->Int64Text(std::numeric_limits<int64_t>::min()),
              std::numeric_limits<int64_t>::min());
}

TEST_F(XMLElementInt64TextTest_253, OverflowTextReturnsDefault_253) {
    // One above int64 max: 9223372036854775808
    elem->SetText("9223372036854775808");

    const int64_t def = 3141592653LL;
    EXPECT_EQ(elem->Int64Text(def), def);
}

TEST_F(XMLElementInt64TextTest_253, UnderflowTextReturnsDefault_253) {
    // One below int64 min: -9223372036854775809
    elem->SetText("-9223372036854775809");

    const int64_t def = -2718281828LL;
    EXPECT_EQ(elem->Int64Text(def), def);
}

TEST_F(XMLElementInt64TextTest_253, RepeatedCallsAreStable_253) {
    const int64_t v = -444444444444LL;
    elem->SetText(v);

    EXPECT_EQ(elem->Int64Text(1), v);
    EXPECT_EQ(elem->Int64Text(2), v);
    EXPECT_EQ(elem->Int64Text(3), v);
}

TEST_F(XMLElementInt64TextTest_253, ParsedFromXmlTextReturnsValue_253) {
    XMLDocument d;
    ASSERT_EQ(d.Parse("<root><e>12345</e></root>"), XML_SUCCESS);

    XMLElement* e = d.FirstChildElement("root")->FirstChildElement("e");
    ASSERT_NE(e, nullptr);

    EXPECT_EQ(e->Int64Text(-1), int64_t{12345});
}
