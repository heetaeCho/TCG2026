// File: ./TestProjects/tinyxml2/tests/test_xmlelement_unsigned64text_254.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLElementUnsigned64TextTest_254 : public ::testing::Test {
protected:
    static XMLElement* ParseSingleElement(XMLDocument& doc, const char* xml, const char* name) {
        ASSERT_NE(xml, nullptr);
        ASSERT_NE(name, nullptr);

        const XMLError err = doc.Parse(xml);
        ASSERT_EQ(err, XML_SUCCESS);

        XMLElement* elem = doc.FirstChildElement(name);
        ASSERT_NE(elem, nullptr);
        return elem;
    }
};

TEST_F(XMLElementUnsigned64TextTest_254, ReturnsParsedValueForValidNumber_254) {
    XMLDocument doc;
    XMLElement* elem = ParseSingleElement(doc, "<root>42</root>", "root");

    const uint64_t result = elem->Unsigned64Text(/*defaultValue=*/999);
    EXPECT_EQ(result, 42u);
}

TEST_F(XMLElementUnsigned64TextTest_254, ReturnsDefaultWhenElementHasNoText_254) {
    XMLDocument doc;
    XMLElement* elem = ParseSingleElement(doc, "<root/>", "root");

    const uint64_t defaultValue = 123456789u;
    const uint64_t result = elem->Unsigned64Text(defaultValue);
    EXPECT_EQ(result, defaultValue);
}

TEST_F(XMLElementUnsigned64TextTest_254, ReturnsDefaultWhenTextIsNonNumeric_254) {
    XMLDocument doc;
    XMLElement* elem = ParseSingleElement(doc, "<root>not_a_number</root>", "root");

    const uint64_t defaultValue = 77u;
    const uint64_t result = elem->Unsigned64Text(defaultValue);
    EXPECT_EQ(result, defaultValue);
}

TEST_F(XMLElementUnsigned64TextTest_254, ParsesWithLeadingAndTrailingWhitespace_254) {
    XMLDocument doc;
    XMLElement* elem = ParseSingleElement(doc, "<root>   12345 \n</root>", "root");

    const uint64_t result = elem->Unsigned64Text(/*defaultValue=*/0);
    EXPECT_EQ(result, 12345u);
}

TEST_F(XMLElementUnsigned64TextTest_254, ParsesZeroCorrectly_254) {
    XMLDocument doc;
    XMLElement* elem = ParseSingleElement(doc, "<root>0</root>", "root");

    const uint64_t result = elem->Unsigned64Text(/*defaultValue=*/999);
    EXPECT_EQ(result, 0u);
}

TEST_F(XMLElementUnsigned64TextTest_254, ParsesUint64MaxCorrectly_254) {
    XMLDocument doc;
    // UINT64_MAX = 18446744073709551615
    XMLElement* elem = ParseSingleElement(doc, "<root>18446744073709551615</root>", "root");

    const uint64_t result = elem->Unsigned64Text(/*defaultValue=*/0);
    EXPECT_EQ(result, std::numeric_limits<uint64_t>::max());
}

TEST_F(XMLElementUnsigned64TextTest_254, ReturnsDefaultOnOverflow_254) {
    XMLDocument doc;
    // UINT64_MAX + 1
    XMLElement* elem = ParseSingleElement(doc, "<root>18446744073709551616</root>", "root");

    const uint64_t defaultValue = 555u;
    const uint64_t result = elem->Unsigned64Text(defaultValue);
    EXPECT_EQ(result, defaultValue);
}

TEST_F(XMLElementUnsigned64TextTest_254, ReturnsDefaultForNegativeText_254) {
    XMLDocument doc;
    XMLElement* elem = ParseSingleElement(doc, "<root>-1</root>", "root");

    const uint64_t defaultValue = 9999u;
    const uint64_t result = elem->Unsigned64Text(defaultValue);
    EXPECT_EQ(result, defaultValue);
}

TEST_F(XMLElementUnsigned64TextTest_254, ReturnsDefaultForEmptyStringText_254) {
    XMLDocument doc;
    XMLElement* elem = ParseSingleElement(doc, "<root></root>", "root");

    const uint64_t defaultValue = 4242u;
    const uint64_t result = elem->Unsigned64Text(defaultValue);
    EXPECT_EQ(result, defaultValue);
}

TEST_F(XMLElementUnsigned64TextTest_254, CanBeCalledRepeatedlyAndIsStable_254) {
    XMLDocument doc;
    XMLElement* elem = ParseSingleElement(doc, "<root>9001</root>", "root");

    const uint64_t first = elem->Unsigned64Text(/*defaultValue=*/0);
    const uint64_t second = elem->Unsigned64Text(/*defaultValue=*/123);
    EXPECT_EQ(first, 9001u);
    EXPECT_EQ(second, 9001u);
}

}  // namespace
