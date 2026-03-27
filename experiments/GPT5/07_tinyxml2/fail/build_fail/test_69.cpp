// TEST_ID: 69
#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLAttributeGetLineNumTest_69 : public ::testing::Test {
protected:
    static XMLDocument ParseDocOrFail(const char* xml) {
        XMLDocument doc;
        const XMLError err = doc.Parse(xml);
        ASSERT_EQ(err, XML_SUCCESS) << "Parse failed with error code: " << err;
        return doc; // NRVO/move
    }

    static const XMLAttribute* FirstAttrOrFail(const XMLElement* elem) {
        ASSERT_NE(elem, nullptr);
        const XMLAttribute* a = elem->FirstAttribute();
        ASSERT_NE(a, nullptr);
        return a;
    }
};

}  // namespace

TEST_F(XMLAttributeGetLineNumTest_69, ReturnsOneForSingleLineDocument_69) {
    XMLDocument doc = ParseDocOrFail("<root a='1'/>");

    const XMLElement* root = doc.RootElement();
    const XMLAttribute* attr = FirstAttrOrFail(root);

    EXPECT_EQ(attr->GetLineNum(), 1);
}

TEST_F(XMLAttributeGetLineNumTest_69, TracksLineNumberInMultilineDocument_69) {
    const char* xml =
        "<root>\n"
        "  <child a='1'/>\n"
        "</root>\n";

    XMLDocument doc = ParseDocOrFail(xml);

    const XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);

    const XMLAttribute* attr = FirstAttrOrFail(child);
    EXPECT_EQ(attr->GetLineNum(), 2);
}

TEST_F(XMLAttributeGetLineNumTest_69, DistinguishesAttributesOnDifferentLines_69) {
    const char* xml =
        "<root>\n"
        "  <c1 a='1'/>\n"
        "  <c2 b='2'/>\n"
        "</root>\n";

    XMLDocument doc = ParseDocOrFail(xml);

    const XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const XMLElement* c1 = root->FirstChildElement("c1");
    ASSERT_NE(c1, nullptr);
    const XMLAttribute* a1 = FirstAttrOrFail(c1);

    const XMLElement* c2 = root->FirstChildElement("c2");
    ASSERT_NE(c2, nullptr);
    const XMLAttribute* a2 = FirstAttrOrFail(c2);

    EXPECT_EQ(a1->GetLineNum(), 2);
    EXPECT_EQ(a2->GetLineNum(), 3);
    EXPECT_LT(a1->GetLineNum(), a2->GetLineNum());
}

TEST_F(XMLAttributeGetLineNumTest_69, HandlesWindowsNewlinesCRLF_69) {
    const char* xml =
        "<root>\r\n"
        "  <child a='1'/>\r\n"
        "</root>\r\n";

    XMLDocument doc = ParseDocOrFail(xml);

    const XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);

    const XMLAttribute* attr = FirstAttrOrFail(child);
    EXPECT_EQ(attr->GetLineNum(), 2);
}

TEST_F(XMLAttributeGetLineNumTest_69, CountsLeadingBlankLines_69) {
    const char* xml =
        "\n"
        "\n"
        "<root a='1'/>\n";

    XMLDocument doc = ParseDocOrFail(xml);

    const XMLElement* root = doc.RootElement();
    const XMLAttribute* attr = FirstAttrOrFail(root);

    EXPECT_EQ(attr->GetLineNum(), 3);
}
