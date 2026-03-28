// File: ./TestProjects/tinyxml2/tests/test_xmlelement_unsigned64attribute_231.cpp

#include <gtest/gtest.h>

#include "tinyxml2.h"

using namespace tinyxml2;

class Unsigned64AttributeTest_231 : public ::testing::Test {
protected:
    XMLDocument doc;

    XMLElement* ParseSingleElement(const char* xml) {
        EXPECT_EQ(doc.Parse(xml), XML_SUCCESS);
        XMLElement* root = doc.RootElement();
        EXPECT_NE(root, nullptr);
        return root;
    }
};

TEST_F(Unsigned64AttributeTest_231, ReturnsDefaultWhenAttributeMissing_231) {
    XMLElement* e = ParseSingleElement("<root/>");

    const uint64_t def = 123456789ULL;
    const uint64_t out = e->Unsigned64Attribute("missing", def);

    EXPECT_EQ(out, def);
}

TEST_F(Unsigned64AttributeTest_231, ReturnsValueWhenAttributePresent_231) {
    XMLElement* e = ParseSingleElement("<root a=\"42\"/>");

    const uint64_t def = 7ULL;
    const uint64_t out = e->Unsigned64Attribute("a", def);

    EXPECT_EQ(out, 42ULL);
}

TEST_F(Unsigned64AttributeTest_231, BoundaryZeroValue_231) {
    XMLElement* e = ParseSingleElement("<root a=\"0\"/>");

    const uint64_t def = 999ULL;
    const uint64_t out = e->Unsigned64Attribute("a", def);

    EXPECT_EQ(out, 0ULL);
}

TEST_F(Unsigned64AttributeTest_231, BoundaryMaxUint64Value_231) {
    // 2^64 - 1
    XMLElement* e = ParseSingleElement("<root a=\"18446744073709551615\"/>");

    const uint64_t def = 1ULL;
    const uint64_t out = e->Unsigned64Attribute("a", def);

    EXPECT_EQ(out, 18446744073709551615ULL);
}

TEST_F(Unsigned64AttributeTest_231, ReturnsDefaultWhenAttributeIsNotANumber_231) {
    XMLElement* e = ParseSingleElement("<root a=\"not_a_number\"/>");

    const uint64_t def = 3141592653ULL;
    const uint64_t out = e->Unsigned64Attribute("a", def);

    // Observable wrapper behavior: starts from default, calls Query..., returns current value.
    EXPECT_EQ(out, def);
}

TEST_F(Unsigned64AttributeTest_231, ReturnsDefaultWhenAttributeIsEmptyString_231) {
    XMLElement* e = ParseSingleElement("<root a=\"\"/>");

    const uint64_t def = 8080ULL;
    const uint64_t out = e->Unsigned64Attribute("a", def);

    EXPECT_EQ(out, def);
}

TEST_F(Unsigned64AttributeTest_231, AcceptsEmptyAttributeNameAndReturnsDefault_231) {
    // Uses empty attribute name. This is still a valid C-string; behavior should be observable.
    XMLElement* e = ParseSingleElement("<root a=\"1\"/>");

    const uint64_t def = 55ULL;
    const uint64_t out = e->Unsigned64Attribute("", def);

    EXPECT_EQ(out, def);
}
