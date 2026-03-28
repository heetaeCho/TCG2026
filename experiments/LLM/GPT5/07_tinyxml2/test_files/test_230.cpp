// File: ./TestProjects/tinyxml2/test_xmlelement_int64attribute_230.cpp

#include <cstdint>
#include <limits>
#include <string>

#include "gtest/gtest.h"

#include "tinyxml2.h"

using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;

namespace {

class Int64AttributeTest_230 : public ::testing::Test {
protected:
    static XMLElement* ParseSingleElement(XMLDocument& doc, const char* xml, const char* elementName) {
        const auto err = doc.Parse(xml);
        EXPECT_EQ(err, tinyxml2::XML_SUCCESS) << "XML parse failed for input: " << xml;
        XMLElement* elem = doc.FirstChildElement(elementName);
        EXPECT_NE(elem, nullptr) << "Expected element <" << elementName << "> not found.";
        return elem;
    }
};

TEST_F(Int64AttributeTest_230, ReturnsParsedValueWhenAttributeExists_230) {
    XMLDocument doc;
    XMLElement* elem = ParseSingleElement(doc, "<root a=\"123\"/>", "root");
    ASSERT_NE(elem, nullptr);

    const int64_t result = elem->Int64Attribute("a", /*defaultValue*/ -7);
    EXPECT_EQ(result, 123);
}

TEST_F(Int64AttributeTest_230, ReturnsDefaultWhenAttributeMissing_230) {
    XMLDocument doc;
    XMLElement* elem = ParseSingleElement(doc, "<root/>", "root");
    ASSERT_NE(elem, nullptr);

    const int64_t def = 42;
    const int64_t result = elem->Int64Attribute("missing", def);
    EXPECT_EQ(result, def);
}

TEST_F(Int64AttributeTest_230, ReturnsDefaultWhenAttributeIsNonNumeric_230) {
    XMLDocument doc;
    XMLElement* elem = ParseSingleElement(doc, "<root a=\"not_a_number\"/>", "root");
    ASSERT_NE(elem, nullptr);

    const int64_t def = 99;
    const int64_t result = elem->Int64Attribute("a", def);
    EXPECT_EQ(result, def);
}

TEST_F(Int64AttributeTest_230, ParsesNegativeValue_230) {
    XMLDocument doc;
    XMLElement* elem = ParseSingleElement(doc, "<root a=\"-456\"/>", "root");
    ASSERT_NE(elem, nullptr);

    const int64_t result = elem->Int64Attribute("a", /*defaultValue*/ 0);
    EXPECT_EQ(result, -456);
}

TEST_F(Int64AttributeTest_230, ParsesInt64MaxBoundary_230) {
    XMLDocument doc;
    const std::string xml =
        std::string("<root a=\"") + std::to_string(std::numeric_limits<int64_t>::max()) + "\"/>";
    XMLElement* elem = ParseSingleElement(doc, xml.c_str(), "root");
    ASSERT_NE(elem, nullptr);

    const int64_t result = elem->Int64Attribute("a", /*defaultValue*/ 0);
    EXPECT_EQ(result, std::numeric_limits<int64_t>::max());
}

TEST_F(Int64AttributeTest_230, ParsesInt64MinBoundary_230) {
    XMLDocument doc;
    const std::string xml =
        std::string("<root a=\"") + std::to_string(std::numeric_limits<int64_t>::min()) + "\"/>";
    XMLElement* elem = ParseSingleElement(doc, xml.c_str(), "root");
    ASSERT_NE(elem, nullptr);

    const int64_t result = elem->Int64Attribute("a", /*defaultValue*/ 0);
    EXPECT_EQ(result, std::numeric_limits<int64_t>::min());
}

TEST_F(Int64AttributeTest_230, ReturnsDefaultWhenValueOverflowsInt64_230) {
    // A value larger than int64_t max should not be representable.
    // Observable behavior expected through the wrapper: the default remains returned if parsing fails.
    XMLDocument doc;
    XMLElement* elem = ParseSingleElement(doc, "<root a=\"9223372036854775808\"/>", "root");
    ASSERT_NE(elem, nullptr);

    const int64_t def = -1234;
    const int64_t result = elem->Int64Attribute("a", def);
    EXPECT_EQ(result, def);
}

TEST_F(Int64AttributeTest_230, DefaultValueIsReturnedUnmodifiedAcrossMultipleCalls_230) {
    XMLDocument doc;
    XMLElement* elem = ParseSingleElement(doc, "<root a=\"10\"/>", "root");
    ASSERT_NE(elem, nullptr);

    EXPECT_EQ(elem->Int64Attribute("a", 1), 10);
    EXPECT_EQ(elem->Int64Attribute("missing", 1), 1);
    EXPECT_EQ(elem->Int64Attribute("missing", -500), -500);
}

}  // namespace
