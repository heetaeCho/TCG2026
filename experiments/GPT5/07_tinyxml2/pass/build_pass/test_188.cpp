// File: ./TestProjects/tinyxml2/tests/xmlnode_deletechild_test_188.cpp

#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLNodeDeleteChildTest_188 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* root = nullptr;

    void SetUp() override {
        root = doc.NewElement("root");
        ASSERT_NE(root, nullptr);
        doc.InsertEndChild(root);
    }

    XMLElement* AddChild(const char* name) {
        XMLElement* e = doc.NewElement(name);
        EXPECT_NE(e, nullptr);
        XMLNode* inserted = root->InsertEndChild(e);
        EXPECT_EQ(inserted, e);
        return e;
    }
};

TEST_F(XMLNodeDeleteChildTest_188, DeleteOnlyChildRemovesIt_188) {
    XMLElement* c1 = AddChild("c1");
    ASSERT_EQ(root->ChildElementCount(), 1);
    ASSERT_FALSE(root->NoChildren());
    ASSERT_EQ(root->FirstChild(), c1);
    ASSERT_EQ(root->LastChild(), c1);

    root->DeleteChild(c1);

    EXPECT_EQ(root->ChildElementCount(), 0);
    EXPECT_TRUE(root->NoChildren());
    EXPECT_EQ(root->FirstChild(), nullptr);
    EXPECT_EQ(root->LastChild(), nullptr);
    EXPECT_EQ(root->FirstChildElement(), nullptr);
    EXPECT_EQ(root->LastChildElement(), nullptr);
}

TEST_F(XMLNodeDeleteChildTest_188, DeleteFirstChildUpdatesFirstChildPointerAndSiblingLinks_188) {
    XMLElement* c1 = AddChild("c1");
    XMLElement* c2 = AddChild("c2");
    XMLElement* c3 = AddChild("c3");

    ASSERT_EQ(root->ChildElementCount(), 3);
    ASSERT_EQ(root->FirstChild(), c1);
    ASSERT_EQ(root->LastChild(), c3);
    ASSERT_EQ(c1->NextSibling(), c2);
    ASSERT_EQ(c2->PreviousSibling(), c1);

    root->DeleteChild(c1);

    EXPECT_EQ(root->ChildElementCount(), 2);
    EXPECT_EQ(root->FirstChild(), c2);
    EXPECT_EQ(root->LastChild(), c3);

    // Remaining sibling links should be consistent.
    EXPECT_EQ(c2->PreviousSibling(), nullptr);
    EXPECT_EQ(c2->NextSibling(), c3);
    EXPECT_EQ(c3->PreviousSibling(), c2);
    EXPECT_EQ(c3->NextSibling(), nullptr);

    // Element navigation still works.
    EXPECT_EQ(root->FirstChildElement(), c2);
    EXPECT_EQ(root->LastChildElement(), c3);
}

TEST_F(XMLNodeDeleteChildTest_188, DeleteLastChildUpdatesLastChildPointerAndSiblingLinks_188) {
    XMLElement* c1 = AddChild("c1");
    XMLElement* c2 = AddChild("c2");
    XMLElement* c3 = AddChild("c3");

    ASSERT_EQ(root->ChildElementCount(), 3);
    ASSERT_EQ(root->FirstChild(), c1);
    ASSERT_EQ(root->LastChild(), c3);
    ASSERT_EQ(c3->PreviousSibling(), c2);

    root->DeleteChild(c3);

    EXPECT_EQ(root->ChildElementCount(), 2);
    EXPECT_EQ(root->FirstChild(), c1);
    EXPECT_EQ(root->LastChild(), c2);

    EXPECT_EQ(c1->PreviousSibling(), nullptr);
    EXPECT_EQ(c1->NextSibling(), c2);
    EXPECT_EQ(c2->PreviousSibling(), c1);
    EXPECT_EQ(c2->NextSibling(), nullptr);

    EXPECT_EQ(root->FirstChildElement(), c1);
    EXPECT_EQ(root->LastChildElement(), c2);
}

TEST_F(XMLNodeDeleteChildTest_188, DeleteMiddleChildBridgesNeighbors_188) {
    XMLElement* c1 = AddChild("c1");
    XMLElement* c2 = AddChild("c2");
    XMLElement* c3 = AddChild("c3");

    ASSERT_EQ(root->ChildElementCount(), 3);
    ASSERT_EQ(c1->NextSibling(), c2);
    ASSERT_EQ(c2->NextSibling(), c3);
    ASSERT_EQ(c3->PreviousSibling(), c2);

    root->DeleteChild(c2);

    EXPECT_EQ(root->ChildElementCount(), 2);
    EXPECT_EQ(root->FirstChild(), c1);
    EXPECT_EQ(root->LastChild(), c3);

    // Neighbors should now point to each other.
    EXPECT_EQ(c1->NextSibling(), c3);
    EXPECT_EQ(c3->PreviousSibling(), c1);

    // And ends are still ends.
    EXPECT_EQ(c1->PreviousSibling(), nullptr);
    EXPECT_EQ(c3->NextSibling(), nullptr);
}

TEST_F(XMLNodeDeleteChildTest_188, DeleteChildDoesNotAffectOtherBranches_188) {
    // root -> a, b ; b -> b1, b2
    XMLElement* a = AddChild("a");
    XMLElement* b = AddChild("b");
    ASSERT_EQ(root->ChildElementCount(), 2);

    XMLElement* b1 = doc.NewElement("b1");
    XMLElement* b2 = doc.NewElement("b2");
    ASSERT_NE(b1, nullptr);
    ASSERT_NE(b2, nullptr);
    ASSERT_EQ(b->InsertEndChild(b1), b1);
    ASSERT_EQ(b->InsertEndChild(b2), b2);

    ASSERT_EQ(b->ChildElementCount(), 2);
    ASSERT_EQ(b->FirstChildElement(), b1);
    ASSERT_EQ(b->LastChildElement(), b2);

    root->DeleteChild(a);

    EXPECT_EQ(root->ChildElementCount(), 1);
    EXPECT_EQ(root->FirstChildElement(), b);
    EXPECT_EQ(root->LastChildElement(), b);

    // b's children remain intact and navigable.
    EXPECT_EQ(b->ChildElementCount(), 2);
    EXPECT_EQ(b->FirstChildElement(), b1);
    EXPECT_EQ(b->LastChildElement(), b2);
    EXPECT_EQ(b1->NextSibling(), b2);
    EXPECT_EQ(b2->PreviousSibling(), b1);
}

#ifndef NDEBUG
// The implementation uses TIXMLASSERT, which is typically active in debug builds.
// These death tests validate observable error handling through the public interface.

TEST_F(XMLNodeDeleteChildTest_188, DeleteChildWithNullptrDiesInDebug_188) {
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";
    EXPECT_DEATH({ root->DeleteChild(nullptr); }, "");
}

TEST_F(XMLNodeDeleteChildTest_188, DeleteChildFromDifferentParentDiesInDebug_188) {
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";

    XMLElement* c1 = AddChild("c1");
    (void)c1;

    XMLElement* otherParent = doc.NewElement("other");
    ASSERT_NE(otherParent, nullptr);
    root->InsertEndChild(otherParent);

    XMLElement* otherChild = doc.NewElement("otherChild");
    ASSERT_NE(otherChild, nullptr);
    ASSERT_EQ(otherParent->InsertEndChild(otherChild), otherChild);

    // otherChild's parent is otherParent, not root -> should assert.
    EXPECT_DEATH({ root->DeleteChild(otherChild); }, "");
}

TEST_F(XMLNodeDeleteChildTest_188, DeleteChildFromDifferentDocumentDiesInDebug_188) {
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";

    XMLDocument doc2;
    XMLElement* doc2Root = doc2.NewElement("r2");
    ASSERT_NE(doc2Root, nullptr);
    doc2.InsertEndChild(doc2Root);

    XMLElement* foreign = doc2.NewElement("foreign");
    ASSERT_NE(foreign, nullptr);
    ASSERT_EQ(doc2Root->InsertEndChild(foreign), foreign);

    // foreign belongs to doc2, but we're calling root->DeleteChild(foreign) in doc1 -> should assert.
    EXPECT_DEATH({ root->DeleteChild(foreign); }, "");
}
#endif
