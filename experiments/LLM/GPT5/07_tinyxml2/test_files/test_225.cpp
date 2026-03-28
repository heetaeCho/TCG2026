// TEST_ID: 225
// File: xmlattribute_setattribute_float_test_225.cpp

#include <gtest/gtest.h>

#include <cmath>
#include <cfloat>
#include <limits>

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLAttributeSetAttributeFloatTest_225 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* elem = nullptr;

    void SetUp() override {
        elem = doc.NewElement("root");
        ASSERT_NE(elem, nullptr);
        doc.InsertFirstChild(elem);
    }

    const XMLAttribute* FindAttrOrFail(const char* name) {
        ASSERT_NE(elem, nullptr);
        const XMLAttribute* a = elem->FindAttribute(name);
        ASSERT_NE(a, nullptr) << "Expected attribute '" << name << "' to exist.";
        return a;
    }
};

}  // namespace

TEST_F(XMLAttributeSetAttributeFloatTest_225, SetAttributeFloat_StoresValueAndParsesBack_225) {
    const float v = 3.1415926f;

    elem->SetAttribute("f", v);

    const XMLAttribute* a = FindAttrOrFail("f");
    ASSERT_NE(a->Value(), nullptr);

    float out = 0.0f;
    const XMLError e = a->QueryFloatValue(&out);
    EXPECT_EQ(e, XML_SUCCESS);
    EXPECT_NEAR(out, v, 1e-6f);
}

TEST_F(XMLAttributeSetAttributeFloatTest_225, SetAttributeFloat_NegativeValueParsesBack_225) {
    const float v = -123.75f;

    elem->SetAttribute("f", v);

    const XMLAttribute* a = FindAttrOrFail("f");
    float out = 0.0f;
    EXPECT_EQ(a->QueryFloatValue(&out), XML_SUCCESS);
    EXPECT_NEAR(out, v, 1e-6f);
}

TEST_F(XMLAttributeSetAttributeFloatTest_225, SetAttributeFloat_ZeroAndNegativeZeroRoundTrip_225) {
    elem->SetAttribute("pz", 0.0f);
    elem->SetAttribute("nz", -0.0f);

    {
        const XMLAttribute* a = FindAttrOrFail("pz");
        float out = 1.0f;
        EXPECT_EQ(a->QueryFloatValue(&out), XML_SUCCESS);
        EXPECT_EQ(out, 0.0f);
        EXPECT_FALSE(std::signbit(out));
    }
    {
        const XMLAttribute* a = FindAttrOrFail("nz");
        float out = 1.0f;
        EXPECT_EQ(a->QueryFloatValue(&out), XML_SUCCESS);
        // Some serializations may not preserve -0.0 in text; we only require numeric zero.
        EXPECT_EQ(out, 0.0f);
    }
}

TEST_F(XMLAttributeSetAttributeFloatTest_225, SetAttributeFloat_OverwriteUpdatesValue_225) {
    elem->SetAttribute("f", 1.25f);
    elem->SetAttribute("f", 2.5f);

    const XMLAttribute* a = FindAttrOrFail("f");
    float out = 0.0f;
    EXPECT_EQ(a->QueryFloatValue(&out), XML_SUCCESS);
    EXPECT_NEAR(out, 2.5f, 1e-6f);
}

TEST_F(XMLAttributeSetAttributeFloatTest_225, SetAttributeFloat_FloatMaxAndMinRoundTrip_225) {
    const float vmax = std::numeric_limits<float>::max();
    const float vmin = std::numeric_limits<float>::min();  // smallest positive *normalized* value

    elem->SetAttribute("max", vmax);
    elem->SetAttribute("min", vmin);

    {
        const XMLAttribute* a = FindAttrOrFail("max");
        float out = 0.0f;
        const XMLError e = a->QueryFloatValue(&out);
        EXPECT_EQ(e, XML_SUCCESS);
        // Relative tolerance because formatting may round.
        EXPECT_NEAR(out, vmax, vmax * 1e-6f);
    }
    {
        const XMLAttribute* a = FindAttrOrFail("min");
        float out = 0.0f;
        const XMLError e = a->QueryFloatValue(&out);
        EXPECT_EQ(e, XML_SUCCESS);
        EXPECT_NEAR(out, vmin, vmin * 1e-6f);
    }
}

TEST_F(XMLAttributeSetAttributeFloatTest_225, SetAttributeFloat_SpecialValues_DoNotCrashAndProduceAValueString_225) {
    const float nanv = std::numeric_limits<float>::quiet_NaN();
    const float infv = std::numeric_limits<float>::infinity();

    elem->SetAttribute("nan", nanv);
    elem->SetAttribute("inf", infv);

    // We don't assume how XMLUtil::ToStr formats NaN/Inf, or whether QueryFloatValue accepts them.
    // We only verify observable behavior through the interface: attribute exists and Value() is non-null.
    {
        const XMLAttribute* a = FindAttrOrFail("nan");
        EXPECT_NE(a->Value(), nullptr);
        float out = 0.0f;
        (void)a->QueryFloatValue(&out);  // should be safe to call; expectations about result are unspecified
    }
    {
        const XMLAttribute* a = FindAttrOrFail("inf");
        EXPECT_NE(a->Value(), nullptr);
        float out = 0.0f;
        (void)a->QueryFloatValue(&out);
    }
}

TEST_F(XMLAttributeSetAttributeFloatTest_225, QueryFloatValue_ErrorWhenValueIsNotFloat_225) {
    // This is an observable error-path test via the public interface.
    elem->SetAttribute("f", "not-a-float");

    const XMLAttribute* a = FindAttrOrFail("f");
    float out = 0.0f;
    const XMLError e = a->QueryFloatValue(&out);
    EXPECT_NE(e, XML_SUCCESS);
}
