// TEST_ID: 209
#include <gtest/gtest.h>

#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLAttributeTest_209 : public ::testing::Test {
protected:
    XMLDocument doc_;
};

}  // namespace

TEST_F(XMLAttributeTest_209, NameReturnsParsedAttributeName_209) {
    const char* xml = "<root a='1'/>";
    ASSERT_EQ(XML_SUCCESS, doc_.Parse(xml));

    XMLElement* root = doc_.FirstChildElement("root");
    ASSERT_NE(nullptr, root);

    const XMLAttribute* attr = root->FirstAttribute();
    ASSERT_NE(nullptr, attr);

    EXPECT_STREQ("a", attr->Name());
}

TEST_F(XMLAttributeTest_209, NameReturnsExpectedNamesWhenIteratingAttributes_209) {
    const char* xml = "<root first='1' second='2' third='3'/>";
    ASSERT_EQ(XML_SUCCESS, doc_.Parse(xml));

    XMLElement* root = doc_.FirstChildElement("root");
    ASSERT_NE(nullptr, root);

    const XMLAttribute* a1 = root->FirstAttribute();
    ASSERT_NE(nullptr, a1);
    EXPECT_STREQ("first", a1->Name());

    const XMLAttribute* a2 = a1->Next();
    ASSERT_NE(nullptr, a2);
    EXPECT_STREQ("second", a2->Name());

    const XMLAttribute* a3 = a2->Next();
    ASSERT_NE(nullptr, a3);
    EXPECT_STREQ("third", a3->Name());

    EXPECT_EQ(nullptr, a3->Next());
}

TEST_F(XMLAttributeTest_209, NameIsConsistentAcrossMultipleCalls_209) {
    const char* xml = "<root a='1'/>";
    ASSERT_EQ(XML_SUCCESS, doc_.Parse(xml));

    XMLElement* root = doc_.FirstChildElement("root");
    ASSERT_NE(nullptr, root);

    const XMLAttribute* attr = root->FirstAttribute();
    ASSERT_NE(nullptr, attr);

    const char* n1 = attr->Name();
    const char* n2 = attr->Name();

    ASSERT_NE(nullptr, n1);
    ASSERT_NE(nullptr, n2);
    EXPECT_STREQ(n1, n2);
}

TEST_F(XMLAttributeTest_209, NameHandlesNonTrivialValidXmlNameCharacters_209) {
    // Use a name that is commonly accepted in XML name rules (letters, underscore, dash, dot, colon).
    const char* xml = "<root _a-b.c:ns='1'/>";
    ASSERT_EQ(XML_SUCCESS, doc_.Parse(xml));

    XMLElement* root = doc_.FirstChildElement("root");
    ASSERT_NE(nullptr, root);

    const XMLAttribute* attr = root->FirstAttribute();
    ASSERT_NE(nullptr, attr);

    EXPECT_STREQ("_a-b.c:ns", attr->Name());
}

TEST_F(XMLAttributeTest_209, NameSupportsLongAttributeNames_209) {
    // Boundary-style case: long attribute name.
    const char* xml =
        "<root "
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"
        "='1'/>";

    ASSERT_EQ(XML_SUCCESS, doc_.Parse(xml));

    XMLElement* root = doc_.FirstChildElement("root");
    ASSERT_NE(nullptr, root);

    const XMLAttribute* attr = root->FirstAttribute();
    ASSERT_NE(nullptr, attr);

    EXPECT_STREQ(
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
        attr->Name());
}

TEST_F(XMLAttributeTest_209, NoAttributeMeansNoXMLAttributeObjectToQuery_209) {
    const char* xml = "<root></root>";
    ASSERT_EQ(XML_SUCCESS, doc_.Parse(xml));

    XMLElement* root = doc_.FirstChildElement("root");
    ASSERT_NE(nullptr, root);

    // Error/boundary observable through interface: no attributes => FirstAttribute is null.
    EXPECT_EQ(nullptr, root->FirstAttribute());
}

TEST_F(XMLAttributeTest_209, ParseErrorDoesNotProduceAttributeToQuery_209) {
    // Exceptional/error case (observable): malformed XML fails to parse; no root/attributes.
    const char* badXml = "<root a='1'>";  // missing closing tag
    EXPECT_NE(XML_SUCCESS, doc_.Parse(badXml));

    // When parsing fails, it's observable that we don't have the expected element/attributes.
    EXPECT_EQ(nullptr, doc_.FirstChildElement("root"));
}
