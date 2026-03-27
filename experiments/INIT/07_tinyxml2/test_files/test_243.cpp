// File: ./TestProjects/tinyxml2/tests/XMLElementSetTextDoubleTest_243.cpp

#include <gtest/gtest.h>

#include <cmath>
#include <cfloat>
#include <cstring>
#include <limits>

#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLElementSetTextDoubleTest_243 : public ::testing::Test {
protected:
    XMLDocument doc_;
    XMLElement* elem_ = nullptr;

    void SetUp() override {
        elem_ = doc_.NewElement("root");
        ASSERT_NE(elem_, nullptr);
        doc_.InsertFirstChild(elem_);
    }

    static const char* ToExpectedString(double v, char (&buf)[200]) {
        // Use the public utility exactly as the production code does.
        XMLUtil::ToStr(v, buf, static_cast<int>(sizeof(buf)));
        return buf;
    }
};

} // namespace

TEST_F(XMLElementSetTextDoubleTest_243, SetTextFiniteValue_MatchesXMLUtilToStr_243) {
    const double v = 3.141592653589793;
    elem_->SetText(v);

    char expected[200] = {};
    ToExpectedString(v, expected);

    const char* text = elem_->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, expected);
}

TEST_F(XMLElementSetTextDoubleTest_243, SetTextNegativeValue_QueryDoubleTextRoundTrips_243) {
    const double v = -42.125;
    elem_->SetText(v);

    double out = 0.0;
    const XMLError err = elem_->QueryDoubleText(&out);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(out, v);
}

TEST_F(XMLElementSetTextDoubleTest_243, SetTextZero_QueryDoubleTextRoundTrips_243) {
    const double v = 0.0;
    elem_->SetText(v);

    double out = 1.0;
    const XMLError err = elem_->QueryDoubleText(&out);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(out, v);
}

TEST_F(XMLElementSetTextDoubleTest_243, SetTextOverwritesPreviousText_243) {
    elem_->SetText("old");
    ASSERT_NE(elem_->GetText(), nullptr);
    ASSERT_STREQ(elem_->GetText(), "old");

    const double v = 123.5;
    elem_->SetText(v);

    char expected[200] = {};
    ToExpectedString(v, expected);

    const char* text = elem_->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, expected);
    EXPECT_STRNE(text, "old");
}

TEST_F(XMLElementSetTextDoubleTest_243, SetTextLargeMagnitude_DBLEMax_MatchesXMLUtilToStr_243) {
    const double v = DBL_MAX;
    elem_->SetText(v);

    char expected[200] = {};
    ToExpectedString(v, expected);

    const char* text = elem_->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, expected);

    // Also attempt a parse round-trip if supported by the library.
    double out = 0.0;
    const XMLError err = elem_->QueryDoubleText(&out);
    if (err == XML_SUCCESS) {
        EXPECT_DOUBLE_EQ(out, v);
    }
}

TEST_F(XMLElementSetTextDoubleTest_243, SetTextSmallMagnitude_DBLEMinPositive_MatchesXMLUtilToStr_243) {
    const double v = DBL_MIN; // smallest positive *normalized* double
    elem_->SetText(v);

    char expected[200] = {};
    ToExpectedString(v, expected);

    const char* text = elem_->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, expected);

    double out = 0.0;
    const XMLError err = elem_->QueryDoubleText(&out);
    if (err == XML_SUCCESS) {
        EXPECT_DOUBLE_EQ(out, v);
    }
}

TEST_F(XMLElementSetTextDoubleTest_243, SetTextSpecialValue_NaN_DoesNotCrashAndSetsSomeText_243) {
    const double v = std::numeric_limits<double>::quiet_NaN();

    ASSERT_NO_FATAL_FAILURE(elem_->SetText(v));

    const char* text = elem_->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_GT(std::strlen(text), 0u);

    // If the implementation supports parsing "nan", verify it; otherwise just keep it non-fatal.
    double out = 0.0;
    const XMLError err = elem_->QueryDoubleText(&out);
    if (err == XML_SUCCESS) {
        EXPECT_TRUE(std::isnan(out));
    }
}

TEST_F(XMLElementSetTextDoubleTest_243, SetTextSpecialValue_Infinity_DoesNotCrashAndSetsSomeText_243) {
    const double v = std::numeric_limits<double>::infinity();

    ASSERT_NO_FATAL_FAILURE(elem_->SetText(v));

    const char* text = elem_->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_GT(std::strlen(text), 0u);

    // If the implementation supports parsing "inf", verify it; otherwise just keep it non-fatal.
    double out = 0.0;
    const XMLError err = elem_->QueryDoubleText(&out);
    if (err == XML_SUCCESS) {
        EXPECT_TRUE(std::isinf(out));
        EXPECT_GT(out, 0.0);
    }
}
