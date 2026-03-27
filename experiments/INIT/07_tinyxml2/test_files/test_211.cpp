// File: ./TestProjects/tinyxml2/xmlattribute_queryintvalue_test_211.cpp

#include <climits>
#include <string>

#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLAttributeQueryIntValueTest_211 : public ::testing::Test {
protected:
    // Parses a minimal XML with a single attribute a="...".
    // Returns the XMLAttribute* for attribute "a" on the root element.
    const XMLAttribute* ParseAndGetAttrA(const char* valueLiteral) {
        doc_.Clear();

        // Build: <root a="VALUE"/>
        std::string xml = "<root a=\"";
        if (valueLiteral) {
            xml += valueLiteral;
        }
        xml += "\"/>";

        ASSERT_EQ(doc_.Parse(xml.c_str()), XML_SUCCESS) << "XML parse failed for: " << xml;

        const XMLElement* root = doc_.RootElement();
        ASSERT_NE(root, nullptr);

        const XMLAttribute* attr = root->FindAttribute("a");
        ASSERT_NE(attr, nullptr);

        // Sanity: it should be the same value string we provided (observable via Value()).
        ASSERT_NE(attr->Value(), nullptr);

        return attr;
    }

    XMLDocument doc_;
};

TEST_F(XMLAttributeQueryIntValueTest_211, ReturnsSuccessAndWritesValue_ForZero_211) {
    const XMLAttribute* attr = ParseAndGetAttrA("0");
    int out = 12345;

    const XMLError err = attr->QueryIntValue(&out);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(out, 0);
}

TEST_F(XMLAttributeQueryIntValueTest_211, ReturnsSuccessAndWritesValue_ForPositiveInteger_211) {
    const XMLAttribute* attr = ParseAndGetAttrA("42");
    int out = 0;

    const XMLError err = attr->QueryIntValue(&out);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(out, 42);
}

TEST_F(XMLAttributeQueryIntValueTest_211, ReturnsSuccessAndWritesValue_ForNegativeInteger_211) {
    const XMLAttribute* attr = ParseAndGetAttrA("-17");
    int out = 0;

    const XMLError err = attr->QueryIntValue(&out);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(out, -17);
}

TEST_F(XMLAttributeQueryIntValueTest_211, ReturnsSuccessAndWritesValue_ForIntMax_211) {
    const std::string s = std::to_string(INT_MAX);
    const XMLAttribute* attr = ParseAndGetAttrA(s.c_str());
    int out = 0;

    const XMLError err = attr->QueryIntValue(&out);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(out, INT_MAX);
}

TEST_F(XMLAttributeQueryIntValueTest_211, ReturnsSuccessAndWritesValue_ForIntMin_211) {
    const std::string s = std::to_string(INT_MIN);
    const XMLAttribute* attr = ParseAndGetAttrA(s.c_str());
    int out = 0;

    const XMLError err = attr->QueryIntValue(&out);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(out, INT_MIN);
}

TEST_F(XMLAttributeQueryIntValueTest_211, ReturnsWrongAttributeType_ForNonNumericText_211) {
    const XMLAttribute* attr = ParseAndGetAttrA("abc");
    int out = 999;

    const XMLError err = attr->QueryIntValue(&out);

    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
    // Do not assume whether 'out' changes on failure; only verify the error code.
}

TEST_F(XMLAttributeQueryIntValueTest_211, ReturnsWrongAttributeType_ForEmptyString_211) {
    const XMLAttribute* attr = ParseAndGetAttrA("");
    int out = 999;

    const XMLError err = attr->QueryIntValue(&out);

    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

TEST_F(XMLAttributeQueryIntValueTest_211, ReturnsWrongAttributeType_ForFloatingPointText_211) {
    const XMLAttribute* attr = ParseAndGetAttrA("1.25");
    int out = 999;

    const XMLError err = attr->QueryIntValue(&out);

    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

TEST_F(XMLAttributeQueryIntValueTest_211, ReturnsWrongAttributeType_ForOutOfRangePositive_211) {
    // One above INT_MAX (for 32-bit int). This is a boundary/error case observable through return value.
    // If int is wider on some platform, this may still be in-range; in that case, the test adapts by
    // constructing a clearly-too-large value for the platform's INT_MAX.
    const long long tooLarge = static_cast<long long>(INT_MAX) + 1LL;
    const std::string s = std::to_string(tooLarge);

    const XMLAttribute* attr = ParseAndGetAttrA(s.c_str());
    int out = 0;

    const XMLError err = attr->QueryIntValue(&out);

    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

TEST_F(XMLAttributeQueryIntValueTest_211, ReturnsWrongAttributeType_ForOutOfRangeNegative_211) {
    const long long tooSmall = static_cast<long long>(INT_MIN) - 1LL;
    const std::string s = std::to_string(tooSmall);

    const XMLAttribute* attr = ParseAndGetAttrA(s.c_str());
    int out = 0;

    const XMLError err = attr->QueryIntValue(&out);

    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

}  // namespace
