#include <gtest/gtest.h>
#include <cmath>
#include <limits>
#include <string>
#include "tinyxml2.h"

using namespace tinyxml2;

// Since XMLAttribute has a private constructor and destructor, we need to create
// attributes through the XMLDocument/XMLElement API.

class XMLAttributeSetAttributeFloatTest_225 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* elem;

    void SetUp() override {
        elem = doc.NewElement("test");
        doc.InsertFirstChild(elem);
        // Set an initial attribute so we can work with it
        elem->SetAttribute("attr", "initial");
    }
};

// Test: Setting a positive float value
TEST_F(XMLAttributeSetAttributeFloatTest_225, SetPositiveFloat_225) {
    elem->SetAttribute("attr", 3.14f);
    float result = 0.0f;
    XMLError err = elem->QueryFloatAttribute("attr", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(result, 3.14f);
}

// Test: Setting zero float value
TEST_F(XMLAttributeSetAttributeFloatTest_225, SetZeroFloat_225) {
    elem->SetAttribute("attr", 0.0f);
    float result = 1.0f;
    XMLError err = elem->QueryFloatAttribute("attr", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(result, 0.0f);
}

// Test: Setting negative float value
TEST_F(XMLAttributeSetAttributeFloatTest_225, SetNegativeFloat_225) {
    elem->SetAttribute("attr", -2.5f);
    float result = 0.0f;
    XMLError err = elem->QueryFloatAttribute("attr", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(result, -2.5f);
}

// Test: Setting a very small positive float value
TEST_F(XMLAttributeSetAttributeFloatTest_225, SetVerySmallPositiveFloat_225) {
    float tiny = 1.0e-30f;
    elem->SetAttribute("attr", tiny);
    float result = 0.0f;
    XMLError err = elem->QueryFloatAttribute("attr", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(result, tiny);
}

// Test: Setting a very large positive float value
TEST_F(XMLAttributeSetAttributeFloatTest_225, SetVeryLargePositiveFloat_225) {
    float large = 1.0e30f;
    elem->SetAttribute("attr", large);
    float result = 0.0f;
    XMLError err = elem->QueryFloatAttribute("attr", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(result, large);
}

// Test: Setting a very large negative float value
TEST_F(XMLAttributeSetAttributeFloatTest_225, SetVeryLargeNegativeFloat_225) {
    float large = -1.0e30f;
    elem->SetAttribute("attr", large);
    float result = 0.0f;
    XMLError err = elem->QueryFloatAttribute("attr", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(result, large);
}

// Test: Setting float max value
TEST_F(XMLAttributeSetAttributeFloatTest_225, SetFloatMax_225) {
    float maxVal = std::numeric_limits<float>::max();
    elem->SetAttribute("attr", maxVal);
    float result = 0.0f;
    XMLError err = elem->QueryFloatAttribute("attr", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(result, maxVal);
}

// Test: Setting float min (smallest positive normal) value
TEST_F(XMLAttributeSetAttributeFloatTest_225, SetFloatMinPositiveNormal_225) {
    float minVal = std::numeric_limits<float>::min();
    elem->SetAttribute("attr", minVal);
    float result = 0.0f;
    XMLError err = elem->QueryFloatAttribute("attr", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(result, minVal);
}

// Test: Setting negative zero
TEST_F(XMLAttributeSetAttributeFloatTest_225, SetNegativeZeroFloat_225) {
    float negZero = -0.0f;
    elem->SetAttribute("attr", negZero);
    float result = 1.0f;
    XMLError err = elem->QueryFloatAttribute("attr", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    // -0.0 and 0.0 compare equal
    EXPECT_FLOAT_EQ(result, 0.0f);
}

// Test: Setting float value of 1.0
TEST_F(XMLAttributeSetAttributeFloatTest_225, SetFloatOne_225) {
    elem->SetAttribute("attr", 1.0f);
    float result = 0.0f;
    XMLError err = elem->QueryFloatAttribute("attr", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(result, 1.0f);
}

// Test: Setting float value of -1.0
TEST_F(XMLAttributeSetAttributeFloatTest_225, SetFloatNegativeOne_225) {
    elem->SetAttribute("attr", -1.0f);
    float result = 0.0f;
    XMLError err = elem->QueryFloatAttribute("attr", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(result, -1.0f);
}

// Test: Setting float and verifying the Value() string is not empty
TEST_F(XMLAttributeSetAttributeFloatTest_225, SetFloatValueStringNotEmpty_225) {
    elem->SetAttribute("attr", 42.5f);
    const char* val = elem->FindAttribute("attr")->Value();
    ASSERT_NE(val, nullptr);
    EXPECT_GT(strlen(val), 0u);
}

// Test: Overwriting an existing attribute with a float
TEST_F(XMLAttributeSetAttributeFloatTest_225, OverwriteExistingAttributeWithFloat_225) {
    elem->SetAttribute("attr", "hello");
    const char* val1 = elem->FindAttribute("attr")->Value();
    EXPECT_STREQ(val1, "hello");

    elem->SetAttribute("attr", 99.9f);
    float result = 0.0f;
    XMLError err = elem->QueryFloatAttribute("attr", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(result, 99.9f);
}

// Test: Setting float on multiple attributes
TEST_F(XMLAttributeSetAttributeFloatTest_225, SetFloatOnMultipleAttributes_225) {
    elem->SetAttribute("a", 1.1f);
    elem->SetAttribute("b", 2.2f);
    elem->SetAttribute("c", 3.3f);

    float ra = 0, rb = 0, rc = 0;
    EXPECT_EQ(elem->QueryFloatAttribute("a", &ra), XML_SUCCESS);
    EXPECT_EQ(elem->QueryFloatAttribute("b", &rb), XML_SUCCESS);
    EXPECT_EQ(elem->QueryFloatAttribute("c", &rc), XML_SUCCESS);

    EXPECT_FLOAT_EQ(ra, 1.1f);
    EXPECT_FLOAT_EQ(rb, 2.2f);
    EXPECT_FLOAT_EQ(rc, 3.3f);
}

// Test: FloatValue() convenience method returns the correct value
TEST_F(XMLAttributeSetAttributeFloatTest_225, FloatValueConvenience_225) {
    elem->SetAttribute("attr", 7.77f);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_FLOAT_EQ(attr->FloatValue(), 7.77f);
}

// Test: Setting float and reading as double should be close
TEST_F(XMLAttributeSetAttributeFloatTest_225, SetFloatReadAsDouble_225) {
    elem->SetAttribute("attr", 1.5f);
    double result = 0.0;
    XMLError err = elem->QueryDoubleAttribute("attr", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(result, 1.5, 1e-6);
}

// Test: Setting float and verifying via document print/parse roundtrip
TEST_F(XMLAttributeSetAttributeFloatTest_225, FloatRoundtripViaPrintParse_225) {
    elem->SetAttribute("attr", 123.456f);

    XMLPrinter printer;
    doc.Print(&printer);
    const char* xml = printer.CStr();

    XMLDocument doc2;
    XMLError err = doc2.Parse(xml);
    EXPECT_EQ(err, XML_SUCCESS);

    XMLElement* elem2 = doc2.FirstChildElement("test");
    ASSERT_NE(elem2, nullptr);

    float result = 0.0f;
    err = elem2->QueryFloatAttribute("attr", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(result, 123.456f);
}

// Test: Setting float then overwriting with int, then back to float
TEST_F(XMLAttributeSetAttributeFloatTest_225, SetFloatThenIntThenFloat_225) {
    elem->SetAttribute("attr", 1.5f);
    EXPECT_FLOAT_EQ(elem->FindAttribute("attr")->FloatValue(), 1.5f);

    elem->SetAttribute("attr", 42);
    EXPECT_EQ(elem->FindAttribute("attr")->IntValue(), 42);

    elem->SetAttribute("attr", -0.001f);
    float result = 0.0f;
    XMLError err = elem->QueryFloatAttribute("attr", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(result, -0.001f);
}

// Test: Setting denormalized float
TEST_F(XMLAttributeSetAttributeFloatTest_225, SetDenormalizedFloat_225) {
    float denorm = std::numeric_limits<float>::denorm_min();
    elem->SetAttribute("attr", denorm);
    float result = 0.0f;
    XMLError err = elem->QueryFloatAttribute("attr", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    // The denormalized value should survive the roundtrip
    EXPECT_GT(result, 0.0f);
}

// Test: Setting float value of 0.5
TEST_F(XMLAttributeSetAttributeFloatTest_225, SetFloatHalf_225) {
    elem->SetAttribute("attr", 0.5f);
    float result = 0.0f;
    XMLError err = elem->QueryFloatAttribute("attr", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(result, 0.5f);
}
