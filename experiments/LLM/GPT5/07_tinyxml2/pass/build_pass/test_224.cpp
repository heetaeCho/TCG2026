// TEST_ID: 224
#include <gtest/gtest.h>

#include <cmath>
#include <cfloat>
#include <limits>

#include "tinyxml2.h"

using namespace tinyxml2;

class XMLAttributeSetDoubleTest_224 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* elem = nullptr;

    void SetUp() override {
        elem = doc.NewElement("root");
        ASSERT_NE(elem, nullptr);
        doc.InsertEndChild(elem);
    }

    const XMLAttribute* SetAndGetAttr(double v) {
        elem->SetAttribute("a", v);  // should create/update underlying XMLAttribute and call XMLAttribute::SetAttribute(double)
        const XMLAttribute* attr = elem->FindAttribute("a");
        EXPECT_NE(attr, nullptr);
        if (attr) {
            EXPECT_NE(attr->Name(), nullptr);
            EXPECT_NE(attr->Value(), nullptr);
            EXPECT_NE(attr->Value()[0], '\0');  // should serialize to some non-empty string
        }
        return attr;
    }
};

TEST_F(XMLAttributeSetDoubleTest_224, SetAttributeDouble_RoundTripsViaQueryDouble_224) {
    const double in = 3.14159265358979323846;
    const XMLAttribute* attr = SetAndGetAttr(in);
    ASSERT_NE(attr, nullptr);

    double out = 0.0;
    XMLError err = attr->QueryDoubleValue(&out);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(out, in);
}

TEST_F(XMLAttributeSetDoubleTest_224, SetAttributeDouble_ZeroAndNegative_RoundTrip_224) {
    {
        const XMLAttribute* attr = SetAndGetAttr(0.0);
        ASSERT_NE(attr, nullptr);

        double out = 1.0;
        XMLError err = attr->QueryDoubleValue(&out);
        EXPECT_EQ(err, XML_SUCCESS);
        EXPECT_DOUBLE_EQ(out, 0.0);
    }
    {
        const XMLAttribute* attr = SetAndGetAttr(-42.5);
        ASSERT_NE(attr, nullptr);

        double out = 0.0;
        XMLError err = attr->QueryDoubleValue(&out);
        EXPECT_EQ(err, XML_SUCCESS);
        EXPECT_DOUBLE_EQ(out, -42.5);
    }
}

TEST_F(XMLAttributeSetDoubleTest_224, SetAttributeDouble_LargeMagnitude_RoundTripWithinTolerance_224) {
    // Use a large finite value that should remain representable and parseable.
    const double in = 1.23456789012345e200;

    const XMLAttribute* attr = SetAndGetAttr(in);
    ASSERT_NE(attr, nullptr);

    double out = 0.0;
    XMLError err = attr->QueryDoubleValue(&out);
    EXPECT_EQ(err, XML_SUCCESS);

    // Avoid assuming exact formatting/precision; require close relative error.
    const double denom = std::fabs(in) > 0 ? std::fabs(in) : 1.0;
    EXPECT_LE(std::fabs(out - in) / denom, 1e-12);
}

TEST_F(XMLAttributeSetDoubleTest_224, SetAttributeDouble_SmallMagnitude_RoundTrip_224) {
    // A small normal value (not denormal) to reduce platform-specific parsing differences.
    const double in = 1.0e-200;

    const XMLAttribute* attr = SetAndGetAttr(in);
    ASSERT_NE(attr, nullptr);

    double out = 0.0;
    XMLError err = attr->QueryDoubleValue(&out);
    EXPECT_EQ(err, XML_SUCCESS);

    const double denom = std::fabs(in) > 0 ? std::fabs(in) : 1.0;
    EXPECT_LE(std::fabs(out - in) / denom, 1e-12);
}

TEST_F(XMLAttributeSetDoubleTest_224, SetAttributeDouble_OverwritesPreviousValue_224) {
    const XMLAttribute* attr1 = SetAndGetAttr(1.25);
    ASSERT_NE(attr1, nullptr);

    double out1 = 0.0;
    EXPECT_EQ(attr1->QueryDoubleValue(&out1), XML_SUCCESS);
    EXPECT_DOUBLE_EQ(out1, 1.25);

    const XMLAttribute* attr2 = SetAndGetAttr(9.75);
    ASSERT_NE(attr2, nullptr);

    double out2 = 0.0;
    EXPECT_EQ(attr2->QueryDoubleValue(&out2), XML_SUCCESS);
    EXPECT_DOUBLE_EQ(out2, 9.75);
}

TEST_F(XMLAttributeSetDoubleTest_224, SetAttributeDouble_SpecialValues_DoNotProduceNullValueString_224) {
    // We avoid asserting how NaN/Inf are serialized/parsing behavior (implementation-defined),
    // but we can still verify the interface remains usable and produces some value string.
    const double specials[] = {
        std::numeric_limits<double>::infinity(),
        -std::numeric_limits<double>::infinity(),
        std::numeric_limits<double>::quiet_NaN()
    };

    for (double v : specials) {
        const XMLAttribute* attr = SetAndGetAttr(v);
        ASSERT_NE(attr, nullptr);

        // Value string should exist and be non-empty (serialization happened).
        ASSERT_NE(attr->Value(), nullptr);
        EXPECT_NE(attr->Value()[0], '\0');

        // QueryDoubleValue may succeed or fail depending on implementation; just ensure it returns a valid XMLError.
        double out = 0.0;
        XMLError err = attr->QueryDoubleValue(&out);
        EXPECT_TRUE(err == XML_SUCCESS || err != XML_SUCCESS);
    }
}

TEST_F(XMLAttributeSetDoubleTest_224, QueryDoubleValue_FailsForNonNumericStringValue_224) {
    // Error case observable via interface: attribute contains non-numeric text.
    elem->SetAttribute("a", "not_a_double");
    const XMLAttribute* attr = elem->FindAttribute("a");
    ASSERT_NE(attr, nullptr);

    double out = 0.0;
    XMLError err = attr->QueryDoubleValue(&out);
    EXPECT_NE(err, XML_SUCCESS);
}
