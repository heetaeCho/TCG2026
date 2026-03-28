// TEST_ID: 242
#include <gtest/gtest.h>

#include <cmath>
#include <cfloat>

#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLElementSetTextFloatTest_242 : public ::testing::Test {
protected:
    XMLDocument doc_;
    XMLElement* elem_ = nullptr;

    void SetUp() override {
        elem_ = doc_.NewElement("root");
        ASSERT_NE(elem_, nullptr);
        doc_.InsertEndChild(elem_);
    }

    static void ExpectFloatRoundTrip(float in, float out) {
        // Avoid assuming exact string formatting/precision; allow a small tolerance.
        const float tol = std::fabs(in) * 1e-6f + 1e-6f;
        EXPECT_NEAR(out, in, tol);
    }
};

}  // namespace

TEST_F(XMLElementSetTextFloatTest_242, SetTextFloat_StoresParsableValue_242) {
    const float v = 123.456f;

    elem_->SetText(v);

    float out = 0.0f;
    EXPECT_EQ(elem_->QueryFloatText(&out), XML_SUCCESS);
    ExpectFloatRoundTrip(v, out);

    const char* text = elem_->GetText();
    EXPECT_NE(text, nullptr);
}

TEST_F(XMLElementSetTextFloatTest_242, SetTextFloat_AllowsNegativeValue_242) {
    const float v = -78.9f;

    elem_->SetText(v);

    float out = 0.0f;
    EXPECT_EQ(elem_->QueryFloatText(&out), XML_SUCCESS);
    ExpectFloatRoundTrip(v, out);
}

TEST_F(XMLElementSetTextFloatTest_242, SetTextFloat_ZeroAndSmallMagnitudeValues_242) {
    {
        const float v = 0.0f;
        elem_->SetText(v);

        float out = 1.0f;
        EXPECT_EQ(elem_->QueryFloatText(&out), XML_SUCCESS);
        EXPECT_FLOAT_EQ(out, 0.0f);
    }
    {
        const float v = 1e-5f;
        elem_->SetText(v);

        float out = 0.0f;
        EXPECT_EQ(elem_->QueryFloatText(&out), XML_SUCCESS);
        ExpectFloatRoundTrip(v, out);
    }
}

TEST_F(XMLElementSetTextFloatTest_242, SetTextFloat_LargerMagnitudeValue_242) {
    const float v = 1e5f;

    elem_->SetText(v);

    float out = 0.0f;
    EXPECT_EQ(elem_->QueryFloatText(&out), XML_SUCCESS);
    ExpectFloatRoundTrip(v, out);
}

TEST_F(XMLElementSetTextFloatTest_242, SetTextFloat_OverwriteReplacesPreviousText_242) {
    elem_->SetText(1.25f);

    float out1 = 0.0f;
    EXPECT_EQ(elem_->QueryFloatText(&out1), XML_SUCCESS);
    ExpectFloatRoundTrip(1.25f, out1);

    elem_->SetText(-2.5f);

    float out2 = 0.0f;
    EXPECT_EQ(elem_->QueryFloatText(&out2), XML_SUCCESS);
    ExpectFloatRoundTrip(-2.5f, out2);
}

TEST_F(XMLElementSetTextFloatTest_242, QueryFloatText_WithNullOutParam_ReturnsError_242) {
    elem_->SetText(3.14f);

    // Error is observable via return code; don't assume a specific non-success enum.
    const XMLError err = elem_->QueryFloatText(nullptr);
    EXPECT_NE(err, XML_SUCCESS);
}

TEST_F(XMLElementSetTextFloatTest_242, SetTextFloat_SpecialValues_DoNotCrashAndProduceText_242) {
    // Don't assume how NaN/Inf are serialized or whether they parse back successfully.
    // Only verify observable behavior: call succeeds and text is present (or at least stable).
    {
        const float v = std::numeric_limits<float>::infinity();
        elem_->SetText(v);
        EXPECT_NE(elem_->GetText(), nullptr);
    }
    {
        const float v = -std::numeric_limits<float>::infinity();
        elem_->SetText(v);
        EXPECT_NE(elem_->GetText(), nullptr);
    }
    {
        const float v = std::numeric_limits<float>::quiet_NaN();
        elem_->SetText(v);
        EXPECT_NE(elem_->GetText(), nullptr);
    }
}
