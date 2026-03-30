// File: ./TestProjects/tinyxml2/test_XMLNode_DeleteChildren_187.cpp

#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLNodeDeleteChildrenTest_187 : public ::testing::Test {
protected:
    XMLDocument doc_;
    XMLElement* root_ = nullptr;

    void SetUp() override {
        root_ = doc_.NewElement("root");
        ASSERT_NE(root_, nullptr);
        doc_.InsertEndChild(root_);
    }

    // Helper that adds a few different node types as children of root_.
    void AddMixedChildren() {
        XMLElement* a = doc_.NewElement("a");
        XMLElement* b = doc_.NewElement("b");
        XMLComment* cmt = doc_.NewComment("comment");
        XMLText* txt = doc_.NewText("text");

        ASSERT_NE(a, nullptr);
        ASSERT_NE(b, nullptr);
        ASSERT_NE(cmt, nullptr);
        ASSERT_NE(txt, nullptr);

        root_->InsertEndChild(a);
        root_->InsertEndChild(cmt);
        root_->InsertEndChild(b);
        root_->InsertEndChild(txt);

        // Add a nested subtree under <a> to ensure subtree deletion is safe/complete.
        XMLElement* a_child = doc_.NewElement("a_child");
        ASSERT_NE(a_child, nullptr);
        a->InsertEndChild(a_child);
    }
};

}  // namespace

TEST_F(XMLNodeDeleteChildrenTest_187, DeleteChildrenOnEmptyNodeKeepsNoChildren_187) {
    ASSERT_TRUE(root_->NoChildren());
    ASSERT_EQ(root_->FirstChild(), nullptr);
    ASSERT_EQ(root_->LastChild(), nullptr);
    EXPECT_EQ(root_->ChildElementCount(), 0);

    // Should be safe and keep the node empty.
    root_->DeleteChildren();

    EXPECT_TRUE(root_->NoChildren());
    EXPECT_EQ(root_->FirstChild(), nullptr);
    EXPECT_EQ(root_->LastChild(), nullptr);
    EXPECT_EQ(root_->ChildElementCount(), 0);
}

TEST_F(XMLNodeDeleteChildrenTest_187, DeleteChildrenRemovesSingleElementChild_187) {
    XMLElement* child = doc_.NewElement("child");
    ASSERT_NE(child, nullptr);
    ASSERT_NE(root_->InsertEndChild(child), nullptr);

    ASSERT_FALSE(root_->NoChildren());
    ASSERT_NE(root_->FirstChild(), nullptr);
    ASSERT_NE(root_->LastChild(), nullptr);
    ASSERT_EQ(root_->ChildElementCount(), 1);

    root_->DeleteChildren();

    EXPECT_TRUE(root_->NoChildren());
    EXPECT_EQ(root_->FirstChild(), nullptr);
    EXPECT_EQ(root_->LastChild(), nullptr);
    EXPECT_EQ(root_->ChildElementCount(), 0);
    EXPECT_EQ(root_->FirstChildElement(), nullptr);
    EXPECT_EQ(root_->LastChildElement(), nullptr);
}

TEST_F(XMLNodeDeleteChildrenTest_187, DeleteChildrenRemovesMultipleMixedChildren_187) {
    AddMixedChildren();

    ASSERT_FALSE(root_->NoChildren());
    ASSERT_NE(root_->FirstChild(), nullptr);
    ASSERT_NE(root_->LastChild(), nullptr);

    // We inserted <a>, comment, <b>, text => 2 element children.
    ASSERT_EQ(root_->ChildElementCount(), 2);
    ASSERT_NE(root_->FirstChildElement("a"), nullptr);
    ASSERT_NE(root_->FirstChildElement("b"), nullptr);

    root_->DeleteChildren();

    EXPECT_TRUE(root_->NoChildren());
    EXPECT_EQ(root_->FirstChild(), nullptr);
    EXPECT_EQ(root_->LastChild(), nullptr);
    EXPECT_EQ(root_->ChildElementCount(), 0);
    EXPECT_EQ(root_->FirstChildElement(), nullptr);
    EXPECT_EQ(root_->LastChildElement(), nullptr);
}

TEST_F(XMLNodeDeleteChildrenTest_187, DeleteChildrenClearsSiblingNavigation_187) {
    XMLElement* c1 = doc_.NewElement("c1");
    XMLElement* c2 = doc_.NewElement("c2");
    XMLElement* c3 = doc_.NewElement("c3");
    ASSERT_NE(c1, nullptr);
    ASSERT_NE(c2, nullptr);
    ASSERT_NE(c3, nullptr);

    root_->InsertEndChild(c1);
    root_->InsertEndChild(c2);
    root_->InsertEndChild(c3);

    ASSERT_EQ(root_->ChildElementCount(), 3);

    // Before deletion, sibling traversal should work.
    ASSERT_NE(c1->NextSiblingElement(), nullptr);
    ASSERT_NE(c2->PreviousSiblingElement(), nullptr);
    ASSERT_EQ(c1->NextSiblingElement()->Value() != nullptr, true);

    root_->DeleteChildren();

    // After deletion, parent has no children; sibling navigation from parent is empty.
    EXPECT_EQ(root_->FirstChildElement(), nullptr);
    EXPECT_EQ(root_->LastChildElement(), nullptr);
    EXPECT_EQ(root_->ChildElementCount(), 0);
    EXPECT_TRUE(root_->NoChildren());
}

TEST_F(XMLNodeDeleteChildrenTest_187, DeleteChildrenAllowsReinsertionAfterClear_187) {
    AddMixedChildren();
    ASSERT_FALSE(root_->NoChildren());
    ASSERT_GT(root_->ChildElementCount(), 0);

    root_->DeleteChildren();
    ASSERT_TRUE(root_->NoChildren());
    ASSERT_EQ(root_->ChildElementCount(), 0);

    // Re-insert new children and ensure the node behaves normally afterwards.
    XMLElement* again = doc_.NewElement("again");
    ASSERT_NE(again, nullptr);
    ASSERT_NE(root_->InsertEndChild(again), nullptr);

    EXPECT_FALSE(root_->NoChildren());
    EXPECT_EQ(root_->ChildElementCount(), 1);
    EXPECT_NE(root_->FirstChildElement("again"), nullptr);
    EXPECT_EQ(root_->LastChildElement("again"), root_->FirstChildElement("again"));
}

TEST_F(XMLNodeDeleteChildrenTest_187, DeleteChildrenOnDocumentRemovesTopLevelChildren_187) {
    XMLDocument doc2;
    XMLElement* r = doc2.NewElement("r");
    XMLElement* s = doc2.NewElement("s");
    ASSERT_NE(r, nullptr);
    ASSERT_NE(s, nullptr);

    doc2.InsertEndChild(r);
    doc2.InsertEndChild(s);

    ASSERT_FALSE(doc2.NoChildren());
    ASSERT_NE(doc2.FirstChild(), nullptr);
    ASSERT_NE(doc2.LastChild(), nullptr);

    doc2.DeleteChildren();

    EXPECT_TRUE(doc2.NoChildren());
    EXPECT_EQ(doc2.FirstChild(), nullptr);
    EXPECT_EQ(doc2.LastChild(), nullptr);
    EXPECT_EQ(doc2.FirstChildElement(), nullptr);
    EXPECT_EQ(doc2.LastChildElement(), nullptr);
}
