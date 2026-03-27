// TEST_ID: 210
#include <gtest/gtest.h>

#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLAttributeValueTest_210 : public ::testing::Test {
protected:
    static XMLElement* ParseSingleElement(XMLDocument& doc, const char* xml) {
        const XMLError err = doc.Parse(xml);
        EXPECT_EQ(err, XML_SUCCESS) << "XML parsing failed with error: " << err;
        return doc.RootElement();
    }

    static const XMLAttribute* GetAttrOrFail(XMLElement* elem, const char* name) {
        ASSERT_NE(elem, nullptr);
        const XMLAttribute* attr = elem->FindAttribute(name);
        ASSERT_NE(attr, nullptr) << "Expected attribute '" << name << "' to exist.";
        return attr;
    }
};

TEST_F(XMLAttributeValueTest_210, ReturnsSameAsElementAttributeApi_210) {
    XMLDocument doc;
    XMLElement* root = ParseSingleElement(doc, "<root a='hello'/>");
    ASSERT_NE(root, nullptr);

    const XMLAttribute* attr = GetAttrOrFail(root, "a");

    // Verify observable consistency with another public API, without assuming internal parsing rules.
    const char* elemApiValue = root->Attribute("a");
    ASSERT_NE(elemApiValue, nullptr);

    ASSERT_NE(attr->Value(), nullptr);
    EXPECT_STREQ(attr->Value(), elemApiValue);
}

TEST_F(XMLAttributeValueTest_210, EmptyStringValueIsReturnedAsEmptyCStr_210) {
    XMLDocument doc;
    XMLElement* root = ParseSingleElement(doc, "<root empty=''/>");
    ASSERT_NE(root, nullptr);

    const XMLAttribute* attr = GetAttrOrFail(root, "empty");
    ASSERT_NE(attr->Value(), nullptr);
    EXPECT_STREQ(attr->Value(), "");
}

TEST_F(XMLAttributeValueTest_210, ValueContentIsConsistentAcrossMultipleCalls_210) {
    XMLDocument doc;
    XMLElement* root = ParseSingleElement(doc, "<root a='repeat'/>");
    ASSERT_NE(root, nullptr);

    const XMLAttribute* attr = GetAttrOrFail(root, "a");

    const char* v1 = attr->Value();
    const char* v2 = attr->Value();
    ASSERT_NE(v1, nullptr);
    ASSERT_NE(v2, nullptr);

    // Don't assume pointer stability; verify observable content.
    EXPECT_STREQ(v1, "repeat");
    EXPECT_STREQ(v2, "repeat");
}

TEST_F(XMLAttributeValueTest_210, ReflectsUpdatedValueAfterElementSetAttribute_210) {
    XMLDocument doc;
    XMLElement* root = ParseSingleElement(doc, "<root a='old'/>");
    ASSERT_NE(root, nullptr);

    // Update through public element API (doesn't require constructing XMLAttribute directly).
    root->SetAttribute("a", "new");

    const XMLAttribute* attr = GetAttrOrFail(root, "a");
    ASSERT_NE(attr->Value(), nullptr);
    EXPECT_STREQ(attr->Value(), "new");

    // Also verify consistency with element Attribute() API after update.
    const char* elemApiValue = root->Attribute("a");
    ASSERT_NE(elemApiValue, nullptr);
    EXPECT_STREQ(attr->Value(), elemApiValue);
}

TEST_F(XMLAttributeValueTest_210, HandlesLargeAttributeValue_210) {
    std::string big(4096, 'x');
    std::string xml = "<root big='";
    xml += big;
    xml += "'/>";

    XMLDocument doc;
    XMLElement* root = ParseSingleElement(doc, xml.c_str());
    ASSERT_NE(root, nullptr);

    const XMLAttribute* attr = GetAttrOrFail(root, "big");
    ASSERT_NE(attr->Value(), nullptr);

    // Verify length/content without assuming allocation details.
    EXPECT_EQ(std::string(attr->Value()), big);
}

TEST_F(XMLAttributeValueTest_210, InvalidXmlProducesNoAttributeToRead_210) {
    XMLDocument doc;
    // Malformed XML: missing closing quote.
    const XMLError err = doc.Parse("<root a='oops/>");
    EXPECT_NE(err, XML_SUCCESS);

    // RootElement should be null on parse failure in typical usage; regardless,
    // we should not have an attribute accessible via public API.
    XMLElement* root = doc.RootElement();
    if (root) {
        EXPECT_EQ(root->FindAttribute("a"), nullptr);
    } else {
        SUCCEED();
    }
}

}  // namespace
