// TEST_ID: 213
#include <gtest/gtest.h>

#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLAttributeQueryInt64ValueTest_213 : public ::testing::Test {
protected:
    // Parses a tiny XML snippet and returns the requested attribute pointer.
    // Keeps the XMLDocument alive via outDoc for the lifetime of the attribute pointer.
    static const XMLAttribute* GetAttr(XMLDocument& outDoc,
                                       const char* xml,
                                       const char* elementName,
                                       const char* attrName) {
        EXPECT_NE(xml, nullptr);
        EXPECT_NE(elementName, nullptr);
        EXPECT_NE(attrName, nullptr);

        const XMLError parseErr = outDoc.Parse(xml);
        EXPECT_EQ(parseErr, XML_SUCCESS);

        const XMLElement* elem = outDoc.FirstChildElement(elementName);
        EXPECT_NE(elem, nullptr);

        const XMLAttribute* attr = elem->FindAttribute(attrName);
        EXPECT_NE(attr, nullptr);

        return attr;
    }
};

}  // namespace

TEST_F(XMLAttributeQueryInt64ValueTest_213, ParsesZero_213) {
    XMLDocument doc;
    const XMLAttribute* attr =
        GetAttr(doc, "<root a='0'/>", "root", "a");

    int64_t out = 123;  // sentinel
    const XMLError err = attr->QueryInt64Value(&out);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(out, static_cast<int64_t>(0));
}

TEST_F(XMLAttributeQueryInt64ValueTest_213, ParsesNegativeValue_213) {
    XMLDocument doc;
    const XMLAttribute* attr =
        GetAttr(doc, "<root a='-42'/>", "root", "a");

    int64_t out = 0;
    const XMLError err = attr->QueryInt64Value(&out);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(out, static_cast<int64_t>(-42));
}

TEST_F(XMLAttributeQueryInt64ValueTest_213, ParsesInt64Max_213) {
    XMLDocument doc;
    const XMLAttribute* attr =
        GetAttr(doc, "<root a='9223372036854775807'/>", "root", "a");

    int64_t out = 0;
    const XMLError err = attr->QueryInt64Value(&out);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(out, static_cast<int64_t>(9223372036854775807LL));
}

TEST_F(XMLAttributeQueryInt64ValueTest_213, ParsesInt64Min_213) {
    XMLDocument doc;
    // Int64 minimum value as text.
    const XMLAttribute* attr =
        GetAttr(doc, "<root a='-9223372036854775808'/>", "root", "a");

    int64_t out = 0;
    const XMLError err = attr->QueryInt64Value(&out);

    EXPECT_EQ(err, XML_SUCCESS);
    // Use the constant to avoid relying on compiler parsing quirks.
    EXPECT_EQ(out, static_cast<int64_t>(INT64_MIN));
}

TEST_F(XMLAttributeQueryInt64ValueTest_213, ReturnsWrongTypeForNonNumeric_213) {
    XMLDocument doc;
    const XMLAttribute* attr =
        GetAttr(doc, "<root a='not_a_number'/>", "root", "a");

    int64_t out = 777;  // sentinel; behavior on failure is not specified, so don't assert on out.
    const XMLError err = attr->QueryInt64Value(&out);

    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

TEST_F(XMLAttributeQueryInt64ValueTest_213, ReturnsWrongTypeForOutOfRange_213) {
    XMLDocument doc;
    // One above INT64_MAX.
    const XMLAttribute* attr =
        GetAttr(doc, "<root a='9223372036854775808'/>", "root", "a");

    int64_t out = 0;
    const XMLError err = attr->QueryInt64Value(&out);

    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(XMLAttributeQueryInt64ValueTest_213, DeathOnNullOutputPointer_213) {
    XMLDocument doc;
    const XMLAttribute* attr =
        GetAttr(doc, "<root a='123'/>", "root", "a");

    // If the implementation dereferences the pointer, this will crash; death tests
    // document/guard that behavior without relying on internal details.
    ASSERT_DEATH(
        {
            (void)attr->QueryInt64Value(nullptr);
        },
        "");
}
#endif
