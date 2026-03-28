// TEST_ID: 83
#include <cstdint>
#include <limits>

#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class QueryInt64AttributeTest_83 : public ::testing::Test {
protected:
    static XMLElement* ParseRoot(XMLDocument& doc, const char* xml) {
        EXPECT_EQ(XML_SUCCESS, doc.Parse(xml));
        XMLElement* root = doc.RootElement();
        EXPECT_NE(nullptr, root);
        return root;
    }
};

TEST_F(QueryInt64AttributeTest_83, ReturnsNoAttributeWhenMissing_83) {
    XMLDocument doc;
    XMLElement* root = ParseRoot(doc, "<root/>");

    int64_t value = 0;
    EXPECT_EQ(XML_NO_ATTRIBUTE, root->QueryInt64Attribute("missing", &value));
}

TEST_F(QueryInt64AttributeTest_83, ReturnsSuccessAndWritesValueForValidInt64_83) {
    XMLDocument doc;
    XMLElement* root = ParseRoot(doc, "<root a=\"123\"/>");

    int64_t value = 0;
    EXPECT_EQ(XML_SUCCESS, root->QueryInt64Attribute("a", &value));
    EXPECT_EQ(static_cast<int64_t>(123), value);
}

TEST_F(QueryInt64AttributeTest_83, ReturnsWrongTypeForNonNumericValue_83) {
    XMLDocument doc;
    XMLElement* root = ParseRoot(doc, "<root a=\"not_a_number\"/>");

    int64_t value = 0;
    EXPECT_EQ(XML_WRONG_ATTRIBUTE_TYPE, root->QueryInt64Attribute("a", &value));
}

TEST_F(QueryInt64AttributeTest_83, ParsesInt64Max_83) {
    XMLDocument doc;
    // 9223372036854775807
    XMLElement* root = ParseRoot(doc, "<root a=\"9223372036854775807\"/>");

    int64_t value = 0;
    EXPECT_EQ(XML_SUCCESS, root->QueryInt64Attribute("a", &value));
    EXPECT_EQ(std::numeric_limits<int64_t>::max(), value);
}

TEST_F(QueryInt64AttributeTest_83, ParsesInt64Min_83) {
    XMLDocument doc;
    // -9223372036854775808
    XMLElement* root = ParseRoot(doc, "<root a=\"-9223372036854775808\"/>");

    int64_t value = 0;
    EXPECT_EQ(XML_SUCCESS, root->QueryInt64Attribute("a", &value));
    EXPECT_EQ(std::numeric_limits<int64_t>::min(), value);
}

TEST_F(QueryInt64AttributeTest_83, ReturnsWrongTypeForOutOfRangeValue_83) {
    XMLDocument doc;
    // One more than INT64_MAX
    XMLElement* root = ParseRoot(doc, "<root a=\"9223372036854775808\"/>");

    int64_t value = 0;
    EXPECT_EQ(XML_WRONG_ATTRIBUTE_TYPE, root->QueryInt64Attribute("a", &value));
}

TEST_F(QueryInt64AttributeTest_83, ReturnsNoAttributeForEmptyName_83) {
    XMLDocument doc;
    XMLElement* root = ParseRoot(doc, "<root a=\"1\"/>");

    int64_t value = 0;
    EXPECT_EQ(XML_NO_ATTRIBUTE, root->QueryInt64Attribute("", &value));
}
