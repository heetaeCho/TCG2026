// TEST_ID: 49
#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class XMLNodeGetLineNumTest_49 : public ::testing::Test {
protected:
    XMLDocument doc_;
};

TEST_F(XMLNodeGetLineNumTest_49, NewElementHasZeroLineNum_49) {
    XMLElement* e = doc_.NewElement("a");
    ASSERT_NE(e, nullptr);

    // A newly created (not parsed) node should report the default line number.
    EXPECT_EQ(e->GetLineNum(), 0);
}

TEST_F(XMLNodeGetLineNumTest_49, ParsedRootHasNonZeroLineNum_49) {
    const char* xml = "<root/>";

    ASSERT_EQ(doc_.Parse(xml), XML_SUCCESS);
    const XMLElement* root = doc_.RootElement();
    ASSERT_NE(root, nullptr);

    // After parsing, line numbers should be populated (non-zero).
    EXPECT_NE(root->GetLineNum(), 0);
}

TEST_F(XMLNodeGetLineNumTest_49, LineNumberIncreasesWhenElementMovedDown_49) {
    XMLDocument docA;
    XMLDocument docB;

    const char* xmlA = "<root><child/></root>";
    const char* xmlB =
        "<root>\n"
        "<child/>\n"
        "</root>";

    ASSERT_EQ(docA.Parse(xmlA), XML_SUCCESS);
    ASSERT_EQ(docB.Parse(xmlB), XML_SUCCESS);

    const XMLElement* childA = docA.RootElement()->FirstChildElement("child");
    const XMLElement* childB = docB.RootElement()->FirstChildElement("child");
    ASSERT_NE(childA, nullptr);
    ASSERT_NE(childB, nullptr);

    // Moving the same element to a later line should increase its reported line number.
    EXPECT_GT(childB->GetLineNum(), childA->GetLineNum());
}

TEST_F(XMLNodeGetLineNumTest_49, SiblingLineNumbersRespectOrder_49) {
    const char* xml =
        "<root>\n"
        "<first/>\n"
        "\n"
        "<second/>\n"
        "</root>";

    ASSERT_EQ(doc_.Parse(xml), XML_SUCCESS);

    const XMLElement* root = doc_.RootElement();
    ASSERT_NE(root, nullptr);

    const XMLElement* first = root->FirstChildElement("first");
    const XMLElement* second = root->FirstChildElement("second");
    ASSERT_NE(first, nullptr);
    ASSERT_NE(second, nullptr);

    // Later sibling placed after extra newline(s) should have a greater line number.
    EXPECT_GT(second->GetLineNum(), first->GetLineNum());
}
