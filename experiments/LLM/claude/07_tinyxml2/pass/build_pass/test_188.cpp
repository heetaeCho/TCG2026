#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLNodeDeleteChildTest_188 : public ::testing::Test {
protected:
    void SetUp() override {
        doc = new XMLDocument();
    }

    void TearDown() override {
        delete doc;
    }

    XMLDocument* doc;
};

// Test deleting a single child element
TEST_F(XMLNodeDeleteChildTest_188, DeleteSingleChild_188) {
    doc->Parse("<root><child/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);

    root->DeleteChild(child);
    EXPECT_TRUE(root->NoChildren());
    EXPECT_EQ(root->FirstChild(), nullptr);
}

// Test deleting one child among multiple children
TEST_F(XMLNodeDeleteChildTest_188, DeleteMiddleChild_188) {
    doc->Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLElement* b = root->FirstChildElement("b");
    ASSERT_NE(b, nullptr);

    root->DeleteChild(b);

    EXPECT_EQ(root->ChildElementCount(), 2);
    XMLElement* first = root->FirstChildElement();
    ASSERT_NE(first, nullptr);
    EXPECT_STREQ(first->Value(), "a");

    XMLElement* last = root->LastChildElement();
    ASSERT_NE(last, nullptr);
    EXPECT_STREQ(last->Value(), "c");

    // Verify a's next sibling is c
    XMLElement* aNext = first->NextSiblingElement();
    ASSERT_NE(aNext, nullptr);
    EXPECT_STREQ(aNext->Value(), "c");

    // Verify c's previous sibling is a
    XMLElement* cPrev = last->PreviousSiblingElement();
    ASSERT_NE(cPrev, nullptr);
    EXPECT_STREQ(cPrev->Value(), "a");
}

// Test deleting the first child among multiple children
TEST_F(XMLNodeDeleteChildTest_188, DeleteFirstChild_188) {
    doc->Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);

    root->DeleteChild(a);

    EXPECT_EQ(root->ChildElementCount(), 2);
    XMLElement* first = root->FirstChildElement();
    ASSERT_NE(first, nullptr);
    EXPECT_STREQ(first->Value(), "b");
}

// Test deleting the last child among multiple children
TEST_F(XMLNodeDeleteChildTest_188, DeleteLastChild_188) {
    doc->Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLElement* c = root->FirstChildElement("c");
    ASSERT_NE(c, nullptr);

    root->DeleteChild(c);

    EXPECT_EQ(root->ChildElementCount(), 2);
    XMLElement* last = root->LastChildElement();
    ASSERT_NE(last, nullptr);
    EXPECT_STREQ(last->Value(), "b");
}

// Test deleting all children one by one
TEST_F(XMLNodeDeleteChildTest_188, DeleteAllChildrenOneByOne_188) {
    doc->Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    while (XMLNode* child = root->FirstChild()) {
        root->DeleteChild(child);
    }

    EXPECT_TRUE(root->NoChildren());
    EXPECT_EQ(root->ChildElementCount(), 0);
}

// Test deleting a child that itself has children (deep structure)
TEST_F(XMLNodeDeleteChildTest_188, DeleteChildWithNestedChildren_188) {
    doc->Parse("<root><parent><child1/><child2/></parent></root>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLElement* parent = root->FirstChildElement("parent");
    ASSERT_NE(parent, nullptr);

    root->DeleteChild(parent);
    EXPECT_TRUE(root->NoChildren());
}

// Test that after deletion, the node count is correct
TEST_F(XMLNodeDeleteChildTest_188, ChildElementCountAfterDelete_188) {
    doc->Parse("<root><a/><b/><c/><d/><e/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->ChildElementCount(), 5);

    XMLElement* c = root->FirstChildElement("c");
    ASSERT_NE(c, nullptr);
    root->DeleteChild(c);

    EXPECT_EQ(root->ChildElementCount(), 4);
}

// Test DeleteChildren (delete all at once)
TEST_F(XMLNodeDeleteChildTest_188, DeleteChildrenRemovesAll_188) {
    doc->Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_FALSE(root->NoChildren());

    root->DeleteChildren();

    EXPECT_TRUE(root->NoChildren());
    EXPECT_EQ(root->FirstChild(), nullptr);
    EXPECT_EQ(root->LastChild(), nullptr);
    EXPECT_EQ(root->ChildElementCount(), 0);
}

// Test deleting a child with text content
TEST_F(XMLNodeDeleteChildTest_188, DeleteChildWithTextContent_188) {
    doc->Parse("<root><item>Hello</item><item>World</item></root>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLElement* firstItem = root->FirstChildElement("item");
    ASSERT_NE(firstItem, nullptr);

    root->DeleteChild(firstItem);

    EXPECT_EQ(root->ChildElementCount(), 1);
    XMLElement* remaining = root->FirstChildElement("item");
    ASSERT_NE(remaining, nullptr);
    EXPECT_STREQ(remaining->GetText(), "World");
}

// Test InsertEndChild followed by DeleteChild
TEST_F(XMLNodeDeleteChildTest_188, InsertThenDelete_188) {
    doc->Parse("<root/>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLElement* newChild = doc->NewElement("newChild");
    root->InsertEndChild(newChild);
    EXPECT_EQ(root->ChildElementCount(), 1);

    root->DeleteChild(newChild);
    EXPECT_TRUE(root->NoChildren());
}

// Test deleting from document level
TEST_F(XMLNodeDeleteChildTest_188, DeleteChildFromDocument_188) {
    doc->Parse("<root/>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    doc->DeleteChild(root);
    EXPECT_EQ(doc->FirstChildElement("root"), nullptr);
    EXPECT_TRUE(doc->NoChildren());
}

// Test sibling links are properly updated after deletion
TEST_F(XMLNodeDeleteChildTest_188, SiblingLinksUpdatedAfterDelete_188) {
    doc->Parse("<root><a/><b/><c/><d/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLElement* b = root->FirstChildElement("b");
    XMLElement* c = root->FirstChildElement("c");
    ASSERT_NE(b, nullptr);
    ASSERT_NE(c, nullptr);

    // Delete b, then a->next should be c
    root->DeleteChild(b);

    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);
    XMLElement* aNext = a->NextSiblingElement();
    ASSERT_NE(aNext, nullptr);
    EXPECT_STREQ(aNext->Value(), "c");

    // c's prev sibling should be a
    XMLElement* cPrev = aNext->PreviousSiblingElement();
    ASSERT_NE(cPrev, nullptr);
    EXPECT_STREQ(cPrev->Value(), "a");
}

// Test deleting the only child of a node that was itself inserted
TEST_F(XMLNodeDeleteChildTest_188, DeleteOnlyChildOfInsertedNode_188) {
    doc->Parse("<root/>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLElement* parent = doc->NewElement("parent");
    XMLElement* child = doc->NewElement("child");
    root->InsertEndChild(parent);
    parent->InsertEndChild(child);

    EXPECT_EQ(parent->ChildElementCount(), 1);

    parent->DeleteChild(child);
    EXPECT_TRUE(parent->NoChildren());
    EXPECT_EQ(root->ChildElementCount(), 1); // parent still exists
}

// Test deleting children preserves non-deleted siblings' order
TEST_F(XMLNodeDeleteChildTest_188, PreservesOrderAfterMultipleDeletes_188) {
    doc->Parse("<root><a/><b/><c/><d/><e/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    // Delete b and d
    XMLElement* b = root->FirstChildElement("b");
    root->DeleteChild(b);
    XMLElement* d = root->FirstChildElement("d");
    root->DeleteChild(d);

    EXPECT_EQ(root->ChildElementCount(), 3);

    XMLElement* elem = root->FirstChildElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Value(), "a");

    elem = elem->NextSiblingElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Value(), "c");

    elem = elem->NextSiblingElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Value(), "e");

    elem = elem->NextSiblingElement();
    EXPECT_EQ(elem, nullptr);
}

// Test DeleteChildren on an already empty node
TEST_F(XMLNodeDeleteChildTest_188, DeleteChildrenOnEmptyNode_188) {
    doc->Parse("<root/>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_TRUE(root->NoChildren());

    // Should not crash
    root->DeleteChildren();
    EXPECT_TRUE(root->NoChildren());
}

// Test that FirstChild and LastChild are updated when the only child is deleted
TEST_F(XMLNodeDeleteChildTest_188, FirstLastChildUpdatedOnSingleDelete_188) {
    doc->Parse("<root><only/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    EXPECT_NE(root->FirstChild(), nullptr);
    EXPECT_NE(root->LastChild(), nullptr);

    XMLElement* only = root->FirstChildElement("only");
    root->DeleteChild(only);

    EXPECT_EQ(root->FirstChild(), nullptr);
    EXPECT_EQ(root->LastChild(), nullptr);
}

// Test that FirstChild and LastChild are correct after deleting first child
TEST_F(XMLNodeDeleteChildTest_188, FirstChildUpdatedAfterDeletingFirst_188) {
    doc->Parse("<root><a/><b/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLElement* a = root->FirstChildElement("a");
    root->DeleteChild(a);

    const XMLNode* first = root->FirstChild();
    ASSERT_NE(first, nullptr);
    EXPECT_STREQ(first->Value(), "b");

    const XMLNode* last = root->LastChild();
    ASSERT_NE(last, nullptr);
    EXPECT_STREQ(last->Value(), "b");
}

// Test that FirstChild and LastChild are correct after deleting last child
TEST_F(XMLNodeDeleteChildTest_188, LastChildUpdatedAfterDeletingLast_188) {
    doc->Parse("<root><a/><b/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLElement* b = root->FirstChildElement("b");
    root->DeleteChild(b);

    const XMLNode* first = root->FirstChild();
    ASSERT_NE(first, nullptr);
    EXPECT_STREQ(first->Value(), "a");

    const XMLNode* last = root->LastChild();
    ASSERT_NE(last, nullptr);
    EXPECT_STREQ(last->Value(), "a");
}
