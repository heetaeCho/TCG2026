// TEST_ID: 54
#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class XMLNodeLastChildTest_54 : public ::testing::Test {
protected:
    XMLDocument doc;

    XMLElement* MakeRoot() {
        auto* root = doc.NewElement("root");
        // Attach to document so normal TinyXML2 ownership/lifetime rules apply.
        doc.InsertFirstChild(root);
        return root;
    }
};

TEST_F(XMLNodeLastChildTest_54, LastChildReturnsNullptrWhenNoChildren_54) {
    XMLElement* root = MakeRoot();
    const XMLNode* croot = root;

    EXPECT_EQ(croot->LastChild(), nullptr);
}

TEST_F(XMLNodeLastChildTest_54, LastChildReturnsOnlyChildAfterLinkEndChild_54) {
    XMLElement* root = MakeRoot();
    XMLElement* child1 = doc.NewElement("child1");

    ASSERT_NE(root->LinkEndChild(child1), nullptr);

    const XMLNode* croot = root;
    EXPECT_EQ(croot->LastChild(), child1);
}

TEST_F(XMLNodeLastChildTest_54, LastChildReturnsMostRecentlyAppendedChild_54) {
    XMLElement* root = MakeRoot();
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");

    ASSERT_NE(root->LinkEndChild(child1), nullptr);
    EXPECT_EQ(root->LastChild(), child1);

    ASSERT_NE(root->LinkEndChild(child2), nullptr);
    EXPECT_EQ(root->LastChild(), child2);
}

TEST_F(XMLNodeLastChildTest_54, LastChildTracksMixedNodeTypes_54) {
    XMLElement* root = MakeRoot();
    XMLElement* elem = doc.NewElement("elem");
    XMLText* text = doc.NewText("hello");

    ASSERT_NE(root->LinkEndChild(elem), nullptr);
    EXPECT_EQ(root->LastChild(), elem);

    ASSERT_NE(root->LinkEndChild(text), nullptr);
    EXPECT_EQ(root->LastChild(), text);
}

TEST_F(XMLNodeLastChildTest_54, LastChildIsUpdatedAfterDeleteChildren_54) {
    XMLElement* root = MakeRoot();
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");

    ASSERT_NE(root->LinkEndChild(child1), nullptr);
    ASSERT_NE(root->LinkEndChild(child2), nullptr);
    ASSERT_NE(root->LastChild(), nullptr);

    root->DeleteChildren();

    const XMLNode* croot = root;
    EXPECT_EQ(croot->LastChild(), nullptr);
}

TEST_F(XMLNodeLastChildTest_54, LastChildReflectsInsertFirstChildOrdering_54) {
    XMLElement* root = MakeRoot();
    XMLElement* first = doc.NewElement("first");
    XMLElement* insertedAtFront = doc.NewElement("front");

    ASSERT_NE(root->LinkEndChild(first), nullptr);
    EXPECT_EQ(root->LastChild(), first);

    ASSERT_NE(root->InsertFirstChild(insertedAtFront), nullptr);
    // Inserting at the front should not change the "last" child when there was already one at the end.
    EXPECT_EQ(root->LastChild(), first);
}
