// File: ./TestProjects/tinyxml2/tests/xmlelement_insert_new_comment_test_260.cpp

#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

#include <cstring>
#include <string>

using namespace tinyxml2;

class XMLElementInsertNewCommentTest_260 : public ::testing::Test {
protected:
    // Use explicit ctor args to avoid relying on default ctor availability.
    XMLDocument doc{true, Whitespace::PRESERVE_WHITESPACE};
    XMLElement* root = nullptr;

    void SetUp() override {
        root = doc.NewElement("root");
        ASSERT_NE(root, nullptr);
        // Attach root to the document so sibling/child navigation is meaningful.
        ASSERT_NE(doc.InsertEndChild(root), nullptr);
    }
};

TEST_F(XMLElementInsertNewCommentTest_260, ReturnsCommentNodeWithExpectedValue_260) {
    const char* text = "hello comment";
    XMLComment* c = root->InsertNewComment(text);

    ASSERT_NE(c, nullptr);
    EXPECT_NE(c->ToComment(), nullptr);

    const char* v = c->Value();
    ASSERT_NE(v, nullptr);
    EXPECT_STREQ(v, text);
}

TEST_F(XMLElementInsertNewCommentTest_260, InsertsAsLastChildAndPreservesOrder_260) {
    XMLComment* c1 = root->InsertNewComment("first");
    ASSERT_NE(c1, nullptr);

    XMLComment* c2 = root->InsertNewComment("second");
    ASSERT_NE(c2, nullptr);

    // Verify "end child" semantics using public navigation.
    EXPECT_EQ(root->LastChild(), c2);
    EXPECT_EQ(c1->NextSibling(), c2);
    EXPECT_EQ(c2->PreviousSibling(), c1);
}

TEST_F(XMLElementInsertNewCommentTest_260, AcceptsEmptyStringComment_260) {
    XMLComment* c = root->InsertNewComment("");
    ASSERT_NE(c, nullptr);

    const char* v = c->Value();
    ASSERT_NE(v, nullptr);
    EXPECT_STREQ(v, "");
}

TEST_F(XMLElementInsertNewCommentTest_260, HandlesLongCommentText_260) {
    std::string longText(10000, 'x');
    XMLComment* c = root->InsertNewComment(longText.c_str());

    ASSERT_NE(c, nullptr);
    const char* v = c->Value();
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(std::strlen(v), longText.size());
    EXPECT_STREQ(v, longText.c_str());
}

TEST_F(XMLElementInsertNewCommentTest_260, WorksOnOrphanElementNotAttachedToDocumentTree_260) {
    XMLElement* orphan = doc.NewElement("orphan");
    ASSERT_NE(orphan, nullptr);

    XMLComment* c = orphan->InsertNewComment("inside orphan");
    ASSERT_NE(c, nullptr);

    // Verify it became a child of the orphan element.
    const XMLNode* first = orphan->FirstChild();
    ASSERT_NE(first, nullptr);
    EXPECT_EQ(first, c);
    EXPECT_NE(first->ToComment(), nullptr);

    const char* v = c->Value();
    ASSERT_NE(v, nullptr);
    EXPECT_STREQ(v, "inside orphan");
}
