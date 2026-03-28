// File: test_xmlelement_settext_int64_239.cpp

#include <gtest/gtest.h>
#include <limits>
#include <string>

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class XMLElementSetTextInt64Test_239 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* elem = nullptr;

    void SetUp() override {
        elem = doc.NewElement("root");
        ASSERT_NE(elem, nullptr);
        doc.InsertEndChild(elem);
    }
};

TEST_F(XMLElementSetTextInt64Test_239, SetTextZero_239) {
    const int64_t v = 0;
    elem->SetText(v);

    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "0");

    int64_t out = 123;
    const XMLError err = elem->QueryInt64Text(&out);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(out, v);

    EXPECT_EQ(elem->Int64Text(999), v);
}

TEST_F(XMLElementSetTextInt64Test_239, SetTextPositiveValue_239) {
    const int64_t v = 1234567890123LL;
    elem->SetText(v);

    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, std::to_string(v).c_str());

    int64_t out = 0;
    const XMLError err = elem->QueryInt64Text(&out);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(out, v);
}

TEST_F(XMLElementSetTextInt64Test_239, SetTextNegativeValue_239) {
    const int64_t v = -9876543210LL;
    elem->SetText(v);

    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, std::to_string(v).c_str());

    int64_t out = 0;
    const XMLError err = elem->QueryInt64Text(&out);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(out, v);
}

TEST_F(XMLElementSetTextInt64Test_239, SetTextInt64Max_239) {
    const int64_t v = (std::numeric_limits<int64_t>::max)();
    elem->SetText(v);

    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, std::to_string(v).c_str());

    int64_t out = 0;
    const XMLError err = elem->QueryInt64Text(&out);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(out, v);
}

TEST_F(XMLElementSetTextInt64Test_239, SetTextInt64Min_239) {
    const int64_t v = (std::numeric_limits<int64_t>::min)();
    elem->SetText(v);

    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, std::to_string(v).c_str());

    int64_t out = 0;
    const XMLError err = elem->QueryInt64Text(&out);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(out, v);
}

TEST_F(XMLElementSetTextInt64Test_239, OverwritesPreviousText_239) {
    elem->SetText(static_cast<int64_t>(42));
    ASSERT_NE(elem->GetText(), nullptr);
    EXPECT_STREQ(elem->GetText(), "42");

    elem->SetText(static_cast<int64_t>(-7));
    ASSERT_NE(elem->GetText(), nullptr);
    EXPECT_STREQ(elem->GetText(), "-7");

    int64_t out = 0;
    const XMLError err = elem->QueryInt64Text(&out);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(out, static_cast<int64_t>(-7));
}

TEST_F(XMLElementSetTextInt64Test_239, QueryInt64TextFailsOnNonNumericText_239) {
    // Set a non-numeric string through the public interface.
    elem->SetText("not_a_number");

    int64_t out = 0;
    const XMLError err = elem->QueryInt64Text(&out);

    // Error/exceptional case should be observable as a non-success status.
    EXPECT_NE(err, XML_SUCCESS);
}

TEST_F(XMLElementSetTextInt64Test_239, Int64TextReturnsDefaultWhenTextIsNonNumeric_239) {
    elem->SetText("NaN");

    const int64_t def = 314159;
    const int64_t got = elem->Int64Text(def);

    // When conversion is not possible, the observable behavior should be returning the provided default.
    EXPECT_EQ(got, def);
}
