// TEST_ID: 181
// File: tinyxml2_xmlnode_dtor_unittest_181.cpp

#include <gtest/gtest.h>
#include "tinyxml2.h"

namespace {

class TestXMLNode_181 : public tinyxml2::XMLNode {
public:
    static int dtorCount;

    explicit TestXMLNode_181(tinyxml2::XMLDocument* doc) : tinyxml2::XMLNode(doc) {}
    ~TestXMLNode_181() override { ++dtorCount; }

    // Expose only the public/protected API needed for black-box verification.
    using tinyxml2::XMLNode::DeleteChild;
    using tinyxml2::XMLNode::DeleteChildren;
    using tinyxml2::XMLNode::InsertAfterChild;
    using tinyxml2::XMLNode::InsertEndChild;
    using tinyxml2::XMLNode::InsertFirstChild;

    using tinyxml2::XMLNode::FirstChild;
    using tinyxml2::XMLNode::LastChild;
    using tinyxml2::XMLNode::NextSibling;
    using tinyxml2::XMLNode::NoChildren;
    using tinyxml2::XMLNode::Parent;
    using tinyxml2::XMLNode::PreviousSibling;
};

int TestXMLNode_181::dtorCount = 0;

class XMLNodeDestructorTest_181 : public ::testing::Test {
protected:
    void SetUp() override { TestXMLNode_181::dtorCount = 0; }
};

TEST_F(XMLNodeDestructorTest_181, DeletingChildUnlinksFromParent_181) {
    tinyxml2::XMLDocument doc;

    auto* parent = new TestXMLNode_181(&doc);
    auto* child = new TestXMLNode_181(&doc);

    ASSERT_EQ(parent->FirstChild(), nullptr);
    ASSERT_TRUE(parent->NoChildren());

    ASSERT_EQ(parent->InsertEndChild(child), child);
    ASSERT_EQ(parent->FirstChild(), child);
    ASSERT_FALSE(parent->NoChildren());

    // Deleting the child should (via XMLNode::~XMLNode) unlink it from its parent.
    delete child;

    EXPECT_EQ(parent->FirstChild(), nullptr);
    EXPECT_EQ(parent->LastChild(), nullptr);
    EXPECT_TRUE(parent->NoChildren());

    delete parent;
}

TEST_F(XMLNodeDestructorTest_181, DeletingMiddleChildUpdatesSiblingLinks_181) {
    tinyxml2::XMLDocument doc;

    auto* parent = new TestXMLNode_181(&doc);
    auto* c1 = new TestXMLNode_181(&doc);
    auto* c2 = new TestXMLNode_181(&doc);
    auto* c3 = new TestXMLNode_181(&doc);

    ASSERT_EQ(parent->InsertEndChild(c1), c1);
    ASSERT_EQ(parent->InsertEndChild(c2), c2);
    ASSERT_EQ(parent->InsertEndChild(c3), c3);

    ASSERT_EQ(parent->FirstChild(), c1);
    ASSERT_EQ(parent->LastChild(), c3);
    ASSERT_EQ(c1->NextSibling(), c2);
    ASSERT_EQ(c2->PreviousSibling(), c1);
    ASSERT_EQ(c2->NextSibling(), c3);
    ASSERT_EQ(c3->PreviousSibling(), c2);

    // Trigger unlinking through destructor.
    delete c2;

    EXPECT_EQ(parent->FirstChild(), c1);
    EXPECT_EQ(parent->LastChild(), c3);
    EXPECT_EQ(c1->NextSibling(), c3);
    EXPECT_EQ(c3->PreviousSibling(), c1);

    delete parent; // cleans up c1 and c3
}

TEST_F(XMLNodeDestructorTest_181, ParentDestructorDeletesChildren_181) {
    tinyxml2::XMLDocument doc;

    auto* parent = new TestXMLNode_181(&doc);
    auto* c1 = new TestXMLNode_181(&doc);
    auto* c2 = new TestXMLNode_181(&doc);

    ASSERT_EQ(parent->InsertEndChild(c1), c1);
    ASSERT_EQ(parent->InsertEndChild(c2), c2);

    // Deleting parent should delete its children first (observable via derived destructor count).
    delete parent;

    // parent + 2 children
    EXPECT_EQ(TestXMLNode_181::dtorCount, 3);
}

TEST_F(XMLNodeDestructorTest_181, DeleteChildrenOnEmptyIsNoOp_181) {
    tinyxml2::XMLDocument doc;
    auto* parent = new TestXMLNode_181(&doc);

    ASSERT_TRUE(parent->NoChildren());
    ASSERT_EQ(parent->FirstChild(), nullptr);

    // Should not crash, and should not change observable state.
    parent->DeleteChildren();

    EXPECT_TRUE(parent->NoChildren());
    EXPECT_EQ(parent->FirstChild(), nullptr);
    EXPECT_EQ(parent->LastChild(), nullptr);

    delete parent;
}

TEST_F(XMLNodeDestructorTest_181, DeleteChildWithNullPointerDoesNotModifyTree_181) {
    tinyxml2::XMLDocument doc;

    auto* parent = new TestXMLNode_181(&doc);
    auto* child = new TestXMLNode_181(&doc);

    ASSERT_EQ(parent->InsertEndChild(child), child);
    ASSERT_EQ(parent->FirstChild(), child);
    ASSERT_EQ(parent->LastChild(), child);

    // Error/edge case: deleting a null child pointer should be a safe no-op (observable: tree unchanged).
    parent->DeleteChild(nullptr);

    EXPECT_EQ(parent->FirstChild(), child);
    EXPECT_EQ(parent->LastChild(), child);
    EXPECT_FALSE(parent->NoChildren());

    delete parent; // cleans up child
}

}  // namespace
