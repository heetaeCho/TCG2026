#include <gtest/gtest.h>

#include <limits>
#include <string>

#include "tinyxml2.h"

using namespace tinyxml2;

class XMLAttributeSetAttributeUnsignedTest_220 : public ::testing::Test {
protected:
    static XMLAttribute* GetMutableAttr(XMLElement* elem, const char* name) {
        // tinyxml2 exposes attributes via const XMLAttribute* even for non-const elements.
        // The underlying object is still owned by the (mutable) document; for the purpose
        // of testing XMLAttribute's public non-const API, we cast away constness here.
        const XMLAttribute* a = elem->FindAttribute(name);
        return const_cast<XMLAttribute*>(a);
    }

    static XMLElement* ParseSingleAttrDoc(XMLDocument& doc,
                                         const char* xml,
                                         const char* elemName = "root") {
        ASSERT_EQ(XML_SUCCESS, doc.Parse(xml));
        XMLElement* root = doc.FirstChildElement(elemName);
        ASSERT_NE(nullptr, root);
        return root;
    }
};

TEST_F(XMLAttributeSetAttributeUnsignedTest_220, SetsZeroAsDecimalString_220) {
    XMLDocument doc;
    XMLElement* root = ParseSingleAttrDoc(doc, "<root a='123'/>");

    XMLAttribute* attr = GetMutableAttr(root, "a");
    ASSERT_NE(nullptr, attr);

    attr->SetAttribute(static_cast<unsigned>(0));

    ASSERT_NE(nullptr, attr->Value());
    EXPECT_STREQ("0", attr->Value());

    unsigned out = 999u;
    EXPECT_EQ(XML_SUCCESS, attr->QueryUnsignedValue(&out));
    EXPECT_EQ(0u, out);
    EXPECT_EQ(0u, attr->UnsignedValue());
}

TEST_F(XMLAttributeSetAttributeUnsignedTest_220, SetsOneAsDecimalString_220) {
    XMLDocument doc;
    XMLElement* root = ParseSingleAttrDoc(doc, "<root a='0'/>");

    XMLAttribute* attr = GetMutableAttr(root, "a");
    ASSERT_NE(nullptr, attr);

    attr->SetAttribute(static_cast<unsigned>(1));

    EXPECT_STREQ("1", attr->Value());

    unsigned out = 0u;
    EXPECT_EQ(XML_SUCCESS, attr->QueryUnsignedValue(&out));
    EXPECT_EQ(1u, out);
    EXPECT_EQ(1u, attr->UnsignedValue());
}

TEST_F(XMLAttributeSetAttributeUnsignedTest_220, SetsMaxUnsignedAsDecimalString_220) {
    XMLDocument doc;
    XMLElement* root = ParseSingleAttrDoc(doc, "<root a='7'/>");

    XMLAttribute* attr = GetMutableAttr(root, "a");
    ASSERT_NE(nullptr, attr);

    const unsigned maxU = (std::numeric_limits<unsigned>::max)();
    attr->SetAttribute(maxU);

    // Verify the stored string matches what the public API reports via parsing back.
    unsigned out = 0u;
    EXPECT_EQ(XML_SUCCESS, attr->QueryUnsignedValue(&out));
    EXPECT_EQ(maxU, out);
    EXPECT_EQ(maxU, attr->UnsignedValue());

    // Also ensure Value() is a non-empty decimal representation.
    ASSERT_NE(nullptr, attr->Value());
    EXPECT_GT(std::string(attr->Value()).size(), 0u);
    // Leading '-' would be invalid for an unsigned representation.
    EXPECT_EQ(std::string::npos, std::string(attr->Value()).find('-'));
}

TEST_F(XMLAttributeSetAttributeUnsignedTest_220, OverwritesPreviousValue_220) {
    XMLDocument doc;
    XMLElement* root = ParseSingleAttrDoc(doc, "<root a='999'/>");

    XMLAttribute* attr = GetMutableAttr(root, "a");
    ASSERT_NE(nullptr, attr);

    ASSERT_STREQ("a", attr->Name());
    EXPECT_STREQ("999", attr->Value());

    attr->SetAttribute(static_cast<unsigned>(42));

    EXPECT_STREQ("a", attr->Name());           // name unchanged
    EXPECT_STREQ("42", attr->Value());         // value replaced
    EXPECT_EQ(42u, attr->UnsignedValue());     // numeric view matches
}

TEST_F(XMLAttributeSetAttributeUnsignedTest_220, MultipleCallsKeepLatestValue_220) {
    XMLDocument doc;
    XMLElement* root = ParseSingleAttrDoc(doc, "<root a='1'/>");

    XMLAttribute* attr = GetMutableAttr(root, "a");
    ASSERT_NE(nullptr, attr);

    attr->SetAttribute(static_cast<unsigned>(10));
    EXPECT_STREQ("10", attr->Value());
    EXPECT_EQ(10u, attr->UnsignedValue());

    attr->SetAttribute(static_cast<unsigned>(0));
    EXPECT_STREQ("0", attr->Value());
    EXPECT_EQ(0u, attr->UnsignedValue());

    attr->SetAttribute(static_cast<unsigned>(123456));
    EXPECT_STREQ("123456", attr->Value());
    EXPECT_EQ(123456u, attr->UnsignedValue());
}
