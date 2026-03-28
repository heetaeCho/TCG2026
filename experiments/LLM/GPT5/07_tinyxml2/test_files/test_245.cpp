// File: test_xmlelement_queryunsignedtext_245.cpp

#include <gtest/gtest.h>

#include <limits>
#include <string>

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLElementQueryUnsignedTextTest_245 : public ::testing::Test {
protected:
    // Parse XML and return the first element with given name (or nullptr on failure).
    static XMLElement* ParseAndGet(XMLDocument& doc, const char* xml, const char* elemName) {
        EXPECT_NE(xml, nullptr);
        EXPECT_NE(elemName, nullptr);

        const XMLError parseErr = doc.Parse(xml);
        EXPECT_EQ(parseErr, XML_SUCCESS);

        XMLElement* elem = doc.FirstChildElement(elemName);
        return elem;
    }
};

}  // namespace

TEST_F(XMLElementQueryUnsignedTextTest_245, ReturnsSuccessAndParsesZero_245) {
    XMLDocument doc;
    XMLElement* elem = ParseAndGet(doc, "<root>0</root>", "root");
    ASSERT_NE(elem, nullptr);

    unsigned value = 123u;
    const XMLError err = elem->QueryUnsignedText(&value);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 0u);
}

TEST_F(XMLElementQueryUnsignedTextTest_245, ReturnsSuccessAndParsesMaxUnsigned_245) {
    XMLDocument doc;

    const unsigned maxU = std::numeric_limits<unsigned>::max();
    const std::string xml = std::string("<root>") + std::to_string(maxU) + "</root>";

    XMLElement* elem = ParseAndGet(doc, xml.c_str(), "root");
    ASSERT_NE(elem, nullptr);

    unsigned value = 0u;
    const XMLError err = elem->QueryUnsignedText(&value);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, maxU);
}

TEST_F(XMLElementQueryUnsignedTextTest_245, ReturnsNoTextNodeWhenElementHasNoChildren_245) {
    XMLDocument doc;
    XMLElement* elem = ParseAndGet(doc, "<root/>", "root");
    ASSERT_NE(elem, nullptr);

    unsigned value = 777u;
    const XMLError err = elem->QueryUnsignedText(&value);

    EXPECT_EQ(err, XML_NO_TEXT_NODE);
    // Value is unspecified on failure; just ensure call didn't succeed.
}

TEST_F(XMLElementQueryUnsignedTextTest_245, ReturnsNoTextNodeWhenFirstChildIsElementNotText_245) {
    XMLDocument doc;
    XMLElement* elem = ParseAndGet(doc, "<root><child/></root>", "root");
    ASSERT_NE(elem, nullptr);

    unsigned value = 1u;
    const XMLError err = elem->QueryUnsignedText(&value);

    EXPECT_EQ(err, XML_NO_TEXT_NODE);
}

TEST_F(XMLElementQueryUnsignedTextTest_245, ReturnsCannotConvertTextForNonNumericText_245) {
    XMLDocument doc;
    XMLElement* elem = ParseAndGet(doc, "<root>abc</root>", "root");
    ASSERT_NE(elem, nullptr);

    unsigned value = 0u;
    const XMLError err = elem->QueryUnsignedText(&value);

    EXPECT_EQ(err, XML_CAN_NOT_CONVERT_TEXT);
}

TEST_F(XMLElementQueryUnsignedTextTest_245, ReturnsCannotConvertTextForNegativeNumberText_245) {
    XMLDocument doc;
    XMLElement* elem = ParseAndGet(doc, "<root>-1</root>", "root");
    ASSERT_NE(elem, nullptr);

    unsigned value = 0u;
    const XMLError err = elem->QueryUnsignedText(&value);

    EXPECT_EQ(err, XML_CAN_NOT_CONVERT_TEXT);
}

TEST_F(XMLElementQueryUnsignedTextTest_245, ReturnsCannotConvertTextWhenOutOfRange_245) {
    XMLDocument doc;

    // One more than max unsigned.
    const unsigned maxU = std::numeric_limits<unsigned>::max();
    const std::string xml = std::string("<root>") + std::to_string(static_cast<unsigned long long>(maxU) + 1ULL) +
                            "</root>";

    XMLElement* elem = ParseAndGet(doc, xml.c_str(), "root");
    ASSERT_NE(elem, nullptr);

    unsigned value = 0u;
    const XMLError err = elem->QueryUnsignedText(&value);

    EXPECT_EQ(err, XML_CAN_NOT_CONVERT_TEXT);
}

TEST_F(XMLElementQueryUnsignedTextTest_245, ReturnsCannotConvertTextForEmptyString_245) {
    XMLDocument doc;
    XMLElement* elem = ParseAndGet(doc, "<root></root>", "root");
    ASSERT_NE(elem, nullptr);

    unsigned value = 42u;
    const XMLError err = elem->QueryUnsignedText(&value);

    EXPECT_EQ(err, XML_CAN_NOT_CONVERT_TEXT);
}
