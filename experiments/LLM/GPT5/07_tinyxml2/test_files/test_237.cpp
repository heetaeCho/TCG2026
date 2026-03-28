// File: ./TestProjects/tinyxml2/tests/xmlelement_settext_int_test_237.cpp

#include <climits>
#include <cstring>

#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementSetTextIntTest_237 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* elem = nullptr;

    void SetUp() override {
        // XMLElement ctor is private; create via XMLDocument factory.
        elem = doc.NewElement("root");
        ASSERT_NE(elem, nullptr);
        doc.InsertFirstChild(elem);
    }
};

TEST_F(XMLElementSetTextIntTest_237, SetTextZero_QueryIntTextReturnsZero_237) {
    ASSERT_NE(elem, nullptr);

    elem->SetText(0);

    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);

    int out = 12345;
    const XMLError err = elem->QueryIntText(&out);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(out, 0);
}

TEST_F(XMLElementSetTextIntTest_237, SetTextPositive_QueryIntTextRoundTrips_237) {
    ASSERT_NE(elem, nullptr);

    elem->SetText(42);

    int out = 0;
    const XMLError err = elem->QueryIntText(&out);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(out, 42);
}

TEST_F(XMLElementSetTextIntTest_237, SetTextNegative_QueryIntTextRoundTrips_237) {
    ASSERT_NE(elem, nullptr);

    elem->SetText(-17);

    int out = 0;
    const XMLError err = elem->QueryIntText(&out);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(out, -17);
}

TEST_F(XMLElementSetTextIntTest_237, SetTextIntMax_QueryIntTextRoundTrips_237) {
    ASSERT_NE(elem, nullptr);

    elem->SetText(INT_MAX);

    int out = 0;
    const XMLError err = elem->QueryIntText(&out);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(out, INT_MAX);
}

TEST_F(XMLElementSetTextIntTest_237, SetTextIntMin_QueryIntTextRoundTrips_237) {
    ASSERT_NE(elem, nullptr);

    elem->SetText(INT_MIN);

    int out = 0;
    const XMLError err = elem->QueryIntText(&out);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(out, INT_MIN);
}

TEST_F(XMLElementSetTextIntTest_237, SetTextOverwritesPreviousText_237) {
    ASSERT_NE(elem, nullptr);

    elem->SetText(1);
    int out1 = 0;
    ASSERT_EQ(elem->QueryIntText(&out1), XML_SUCCESS);
    ASSERT_EQ(out1, 1);

    elem->SetText(999);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);

    int out2 = 0;
    const XMLError err2 = elem->QueryIntText(&out2);
    EXPECT_EQ(err2, XML_SUCCESS);
    EXPECT_EQ(out2, 999);

    // Ensure we didn't keep the old value.
    EXPECT_NE(out2, out1);
}

TEST_F(XMLElementSetTextIntTest_237, SetTextAfterStringText_UpdatesToIntValue_237) {
    ASSERT_NE(elem, nullptr);

    elem->SetText("123");
    int out_before = 0;
    ASSERT_EQ(elem->QueryIntText(&out_before), XML_SUCCESS);
    ASSERT_EQ(out_before, 123);

    elem->SetText(-456);
    int out_after = 0;
    const XMLError err = elem->QueryIntText(&out_after);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(out_after, -456);
}

TEST_F(XMLElementSetTextIntTest_237, GetTextNotNullAfterSetText_237) {
    ASSERT_NE(elem, nullptr);

    elem->SetText(7);

    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    // Don't assert a specific string formatting beyond being non-empty.
    EXPECT_GT(std::strlen(text), 0u);
}

TEST_F(XMLElementSetTextIntTest_237, IntTextReturnsSetValue_237) {
    ASSERT_NE(elem, nullptr);

    elem->SetText(314);

    // IntText is an observable public API for retrieving parsed int value.
    EXPECT_EQ(elem->IntText(-1), 314);
}

TEST_F(XMLElementSetTextIntTest_237, QueryIntTextWithNullOutParam_ReturnsError_237) {
    ASSERT_NE(elem, nullptr);

    elem->SetText(10);

    // Error behavior is observable via return code.
    const XMLError err = elem->QueryIntText(nullptr);
    EXPECT_NE(err, XML_SUCCESS);
}

TEST_F(XMLElementSetTextIntTest_237, SetTextDoesNotThrowOnTypicalValues_237) {
    ASSERT_NE(elem, nullptr);

    EXPECT_NO_THROW(elem->SetText(0));
    EXPECT_NO_THROW(elem->SetText(123));
    EXPECT_NO_THROW(elem->SetText(-123));
    EXPECT_NO_THROW(elem->SetText(INT_MAX));
    EXPECT_NO_THROW(elem->SetText(INT_MIN));
}
