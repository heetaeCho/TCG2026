// TEST_ID: 259
#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class XMLElementInsertNewChildElementTest_259 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* root = nullptr;

    void SetUp() override {
        // Create a root element and attach it to the document so the tree is well-formed.
        root = doc.NewElement("root");
        ASSERT_NE(root, nullptr);
        ASSERT_NE(doc.InsertEndChild(root), nullptr);
    }
};

TEST_F(XMLElementInsertNewChildElementTest_259, CreatesAndReturnsChildElement_259) {
    XMLElement* child = root->InsertNewChildElement("child");
    ASSERT_NE(child, nullptr);

    // Observable behavior: it should be in the tree under root.
    EXPECT_EQ(child->Parent(), root);
    EXPECT_STREQ(child->Name(), "child");

    // It should be retrievable via element navigation APIs.
    EXPECT_EQ(root->FirstChildElement("child"), child);
    EXPECT_EQ(root->LastChildElement("child"), child);
    EXPECT_EQ(root->ChildElementCount(), 1);
}

TEST_F(XMLElementInsertNewChildElementTest_259, InsertsAtEndWhenOtherChildrenExist_259) {
    XMLElement* first = root->InsertNewChildElement("first");
    ASSERT_NE(first, nullptr);

    XMLElement* second = root->InsertNewChildElement("second");
    ASSERT_NE(second, nullptr);

    // Observable order: second should be the last child element.
    EXPECT_EQ(root->FirstChildElement(), first);
    EXPECT_EQ(root->LastChildElement(), second);

    // And sibling navigation should reflect the append-to-end behavior.
    EXPECT_EQ(first->NextSiblingElement(), second);
    EXPECT_EQ(second->PreviousSiblingElement(), first);
    EXPECT_EQ(root->ChildElementCount(), 2);
}

TEST_F(XMLElementInsertNewChildElementTest_259, AllowsDuplicateNamesAndAppendsNewOne_259) {
    XMLElement* a1 = root->InsertNewChildElement("dup");
    ASSERT_NE(a1, nullptr);

    XMLElement* a2 = root->InsertNewChildElement("dup");
    ASSERT_NE(a2, nullptr);
    EXPECT_NE(a1, a2);

    // The first with that name should be the first inserted; the last should be the most recent.
    EXPECT_EQ(root->FirstChildElement("dup"), a1);
    EXPECT_EQ(root->LastChildElement("dup"), a2);

    // Verify order among duplicates through sibling traversal.
    EXPECT_EQ(a1->NextSiblingElement("dup"), a2);
    EXPECT_EQ(a2->PreviousSiblingElement("dup"), a1);
    EXPECT_EQ(root->ChildElementCount("dup"), 2);
}

TEST_F(XMLElementInsertNewChildElementTest_259, EmptyNameBoundary_259) {
    // Boundary condition: empty string name.
    XMLElement* child = root->InsertNewChildElement("");
    ASSERT_NE(child, nullptr);

    // Name should be observable on the returned element.
    EXPECT_STREQ(child->Name(), "");
    EXPECT_EQ(child->Parent(), root);

    // Should be present as a child element.
    EXPECT_EQ(root->ChildElementCount(), 1);
    EXPECT_EQ(root->FirstChildElement(), child);
    EXPECT_EQ(root->LastChildElement(), child);
}

TEST_F(XMLElementInsertNewChildElementTest_259, VeryLongNameBoundary_259) {
    // Boundary condition: very long element name.
    std::string longName(4096, 'a');

    XMLElement* child = root->InsertNewChildElement(longName.c_str());
    ASSERT_NE(child, nullptr);

    EXPECT_STREQ(child->Name(), longName.c_str());
    EXPECT_EQ(child->Parent(), root);
    EXPECT_EQ(root->LastChildElement(), child);
    EXPECT_EQ(root->ChildElementCount(), 1);
}

TEST_F(XMLElementInsertNewChildElementTest_259, ReturnedPointerMatchesNavigatedPointer_259) {
    XMLElement* child = root->InsertNewChildElement("x");
    ASSERT_NE(child, nullptr);

    // Observable: navigating to the last child element with that name should yield the same pointer.
    XMLElement* found = root->LastChildElement("x");
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found, child);
}
