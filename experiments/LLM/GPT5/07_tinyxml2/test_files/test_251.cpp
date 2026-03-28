// File: ./TestProjects/tinyxml2/test_XMLElement_IntText_251.cpp

#include <climits>
#include <gtest/gtest.h>

#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLElementIntTextTest_251 : public ::testing::Test {
protected:
    static XMLElement* ParseSingleElement(XMLDocument& doc, const char* xml, const char* elementName) {
        doc.Clear();
        const XMLError err = doc.Parse(xml);
        EXPECT_EQ(err, XML_SUCCESS) << "XML parse failed for input: " << (xml ? xml : "(null)");
        XMLElement* elem = doc.FirstChildElement(elementName);
        EXPECT_NE(elem, nullptr) << "Expected element <" << elementName << "> not found.";
        return elem;
    }
};

}  // namespace

TEST_F(XMLElementIntTextTest_251, ReturnsParsedValueWhenTextIsValidInteger_251) {
    XMLDocument doc;
    XMLElement* e = ParseSingleElement(doc, "<root>42</root>", "root");
    ASSERT_NE(e, nullptr);

    EXPECT_EQ(e->IntText(7), 42);
}

TEST_F(XMLElementIntTextTest_251, ReturnsDefaultWhenTextIsNonNumeric_251) {
    XMLDocument doc;
    XMLElement* e = ParseSingleElement(doc, "<root>abc</root>", "root");
    ASSERT_NE(e, nullptr);

    EXPECT_EQ(e->IntText(123), 123);
}

TEST_F(XMLElementIntTextTest_251, ReturnsDefaultWhenElementHasNoText_SelfClosing_251) {
    XMLDocument doc;
    XMLElement* e = ParseSingleElement(doc, "<root/>", "root");
    ASSERT_NE(e, nullptr);

    EXPECT_EQ(e->IntText(99), 99);
}

TEST_F(XMLElementIntTextTest_251, ReturnsDefaultWhenElementHasEmptyText_251) {
    XMLDocument doc;
    XMLElement* e = ParseSingleElement(doc, "<root></root>", "root");
    ASSERT_NE(e, nullptr);

    EXPECT_EQ(e->IntText(-5), -5);
}

TEST_F(XMLElementIntTextTest_251, ParsesWithLeadingAndTrailingWhitespace_251) {
    XMLDocument doc;
    XMLElement* e = ParseSingleElement(doc, "<root>  \n\t -17 \r\n </root>", "root");
    ASSERT_NE(e, nullptr);

    EXPECT_EQ(e->IntText(0), -17);
}

TEST_F(XMLElementIntTextTest_251, ParsesWithExplicitPlusSign_251) {
    XMLDocument doc;
    XMLElement* e = ParseSingleElement(doc, "<root>+5</root>", "root");
    ASSERT_NE(e, nullptr);

    EXPECT_EQ(e->IntText(0), 5);
}

TEST_F(XMLElementIntTextTest_251, ParsesBoundaryValues_IntMinAndIntMax_251) {
    {
        XMLDocument doc;
        XMLElement* e = ParseSingleElement(doc, "<root>-2147483648</root>", "root");
        ASSERT_NE(e, nullptr);
        EXPECT_EQ(e->IntText(1), INT_MIN);
    }
    {
        XMLDocument doc;
        XMLElement* e = ParseSingleElement(doc, "<root>2147483647</root>", "root");
        ASSERT_NE(e, nullptr);
        EXPECT_EQ(e->IntText(1), INT_MAX);
    }
}

TEST_F(XMLElementIntTextTest_251, ReturnsDefaultWhenValueOverflowsInt_251) {
    // If parsing fails due to overflow, IntText should return the provided default
    // (because it initializes the local int with defaultValue before querying).
    XMLDocument doc;
    XMLElement* e = ParseSingleElement(doc, "<root>2147483648</root>", "root");
    ASSERT_NE(e, nullptr);

    EXPECT_EQ(e->IntText(77), 77);
}

TEST_F(XMLElementIntTextTest_251, ReturnsDefaultWhenValueUnderflowsInt_251) {
    XMLDocument doc;
    XMLElement* e = ParseSingleElement(doc, "<root>-2147483649</root>", "root");
    ASSERT_NE(e, nullptr);

    EXPECT_EQ(e->IntText(-77), -77);
}

TEST_F(XMLElementIntTextTest_251, ReturnsProvidedDefaultEvenWhenDefaultIsExtreme_251) {
    XMLDocument doc;
    XMLElement* e = ParseSingleElement(doc, "<root>not_a_number</root>", "root");
    ASSERT_NE(e, nullptr);

    EXPECT_EQ(e->IntText(INT_MIN), INT_MIN);
    EXPECT_EQ(e->IntText(INT_MAX), INT_MAX);
}

TEST_F(XMLElementIntTextTest_251, DoesNotMutateTextObservableViaGetText_251) {
    XMLDocument doc;
    XMLElement* e = ParseSingleElement(doc, "<root>123</root>", "root");
    ASSERT_NE(e, nullptr);

    const char* before = e->GetText();
    ASSERT_NE(before, nullptr);

    (void)e->IntText(0);

    const char* after = e->GetText();
    ASSERT_NE(after, nullptr);

    // Observable contract: IntText is a read operation; the element's text should remain the same.
    EXPECT_STREQ(after, before);
}
