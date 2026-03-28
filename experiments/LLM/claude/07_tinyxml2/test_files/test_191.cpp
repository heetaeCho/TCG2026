#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class InsertAfterChildTest_191 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test inserting a node after the first child
TEST_F(InsertAfterChildTest_191, InsertAfterFirstChild_191) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    XMLElement* child3 = doc.NewElement("child3");

    root->InsertEndChild(child1);
    root->InsertEndChild(child3);

    XMLNode* result = root->InsertAfterChild(child1, child2);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, child2);

    // Verify order: child1 -> child2 -> child3
    EXPECT_EQ(root->FirstChild(), child1);
    EXPECT_EQ(child1->NextSibling(), child2);
    EXPECT_EQ(child2->NextSibling(), child3);
    EXPECT_EQ(child3->NextSibling(), nullptr);

    // Verify reverse links
    EXPECT_EQ(child3->PreviousSibling(), child2);
    EXPECT_EQ(child2->PreviousSibling(), child1);
    EXPECT_EQ(child1->PreviousSibling(), nullptr);
}

// Test inserting after the last child (should behave like InsertEndChild)
TEST_F(InsertAfterChildTest_191, InsertAfterLastChild_191) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");

    root->InsertEndChild(child1);

    XMLNode* result = root->InsertAfterChild(child1, child2);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, child2);

    // child1 is last, so inserting after it appends
    EXPECT_EQ(root->FirstChild(), child1);
    EXPECT_EQ(root->LastChild(), child2);
    EXPECT_EQ(child1->NextSibling(), child2);
    EXPECT_EQ(child2->PreviousSibling(), child1);
    EXPECT_EQ(child2->NextSibling(), nullptr);
}

// Test inserting the same node as afterThis (addThis == afterThis)
TEST_F(InsertAfterChildTest_191, InsertSameNodeAsAfterThis_191) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child1 = doc.NewElement("child1");
    root->InsertEndChild(child1);

    XMLNode* result = root->InsertAfterChild(child1, child1);

    // When afterThis == addThis, should return addThis directly
    EXPECT_EQ(result, child1);
    EXPECT_EQ(root->FirstChild(), child1);
    EXPECT_EQ(root->LastChild(), child1);
}

// Test that parent of the inserted node is set correctly
TEST_F(InsertAfterChildTest_191, InsertedNodeHasCorrectParent_191) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");

    root->InsertEndChild(child1);
    root->InsertAfterChild(child1, child2);

    EXPECT_EQ(child2->Parent(), root);
}

// Test inserting after a middle child among three children
TEST_F(InsertAfterChildTest_191, InsertAfterMiddleChild_191) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    XMLElement* child3 = doc.NewElement("child3");
    XMLElement* child4 = doc.NewElement("child4");

    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    root->InsertEndChild(child3);

    XMLNode* result = root->InsertAfterChild(child2, child4);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, child4);

    // Verify order: child1 -> child2 -> child4 -> child3
    EXPECT_EQ(child1->NextSibling(), child2);
    EXPECT_EQ(child2->NextSibling(), child4);
    EXPECT_EQ(child4->NextSibling(), child3);
    EXPECT_EQ(child3->NextSibling(), nullptr);

    // Verify reverse
    EXPECT_EQ(child3->PreviousSibling(), child4);
    EXPECT_EQ(child4->PreviousSibling(), child2);
    EXPECT_EQ(child2->PreviousSibling(), child1);
}

// Test inserting a node from the same document that is already a child elsewhere (re-parenting)
TEST_F(InsertAfterChildTest_191, ReParentNodeFromAnotherParent_191) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* parent1 = doc.NewElement("parent1");
    XMLElement* parent2 = doc.NewElement("parent2");
    root->InsertEndChild(parent1);
    root->InsertEndChild(parent2);

    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    XMLElement* movable = doc.NewElement("movable");

    parent1->InsertEndChild(child1);
    parent1->InsertEndChild(movable);

    parent2->InsertEndChild(child2);

    // Move 'movable' from parent1 to parent2, after child2
    XMLNode* result = parent2->InsertAfterChild(child2, movable);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, movable);
    EXPECT_EQ(movable->Parent(), parent2);

    // parent1 should no longer have movable
    EXPECT_EQ(parent1->FirstChild(), child1);
    EXPECT_EQ(parent1->LastChild(), child1);

    // parent2 should have child2 -> movable
    EXPECT_EQ(parent2->FirstChild(), child2);
    EXPECT_EQ(parent2->LastChild(), movable);
    EXPECT_EQ(child2->NextSibling(), movable);
}

// Test that child element count is correct after insertion
TEST_F(InsertAfterChildTest_191, ChildElementCountAfterInsert_191) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    XMLElement* child3 = doc.NewElement("child3");

    root->InsertEndChild(child1);
    root->InsertEndChild(child3);

    EXPECT_EQ(root->ChildElementCount(), 2);

    root->InsertAfterChild(child1, child2);

    EXPECT_EQ(root->ChildElementCount(), 3);
}

// Test inserting a text node after an element child
TEST_F(InsertAfterChildTest_191, InsertTextNodeAfterElement_191) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child1 = doc.NewElement("child1");
    root->InsertEndChild(child1);

    XMLText* textNode = doc.NewText("hello");
    XMLNode* result = root->InsertAfterChild(child1, textNode);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, textNode);
    EXPECT_EQ(root->LastChild(), textNode);
    EXPECT_EQ(child1->NextSibling(), textNode);
}

// Test inserting a comment node after an element
TEST_F(InsertAfterChildTest_191, InsertCommentAfterElement_191) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child1 = doc.NewElement("child1");
    root->InsertEndChild(child1);

    XMLComment* comment = doc.NewComment("this is a comment");
    XMLNode* result = root->InsertAfterChild(child1, comment);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, comment);
    EXPECT_EQ(child1->NextSibling(), comment);
}

// Test inserting after child with a node from a different document returns 0
TEST_F(InsertAfterChildTest_191, InsertNodeFromDifferentDocumentReturnsNull_191) {
    XMLDocument doc2;

    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child1 = doc.NewElement("child1");
    root->InsertEndChild(child1);

    XMLElement* foreignChild = doc2.NewElement("foreign");

    // addThis belongs to a different document
    XMLNode* result = root->InsertAfterChild(child1, foreignChild);

    EXPECT_EQ(result, nullptr);
}

// Test multiple sequential insertions after the same node
TEST_F(InsertAfterChildTest_191, MultipleInsertionsAfterSameNode_191) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* anchor = doc.NewElement("anchor");
    root->InsertEndChild(anchor);

    XMLElement* insert1 = doc.NewElement("insert1");
    XMLElement* insert2 = doc.NewElement("insert2");
    XMLElement* insert3 = doc.NewElement("insert3");

    // Insert after anchor: anchor -> insert1
    root->InsertAfterChild(anchor, insert1);
    // Insert after anchor again: anchor -> insert2 -> insert1
    root->InsertAfterChild(anchor, insert2);
    // Insert after anchor again: anchor -> insert3 -> insert2 -> insert1
    root->InsertAfterChild(anchor, insert3);

    EXPECT_EQ(anchor->NextSibling(), insert3);
    EXPECT_EQ(insert3->NextSibling(), insert2);
    EXPECT_EQ(insert2->NextSibling(), insert1);
    EXPECT_EQ(insert1->NextSibling(), nullptr);
    EXPECT_EQ(root->LastChild(), insert1);
}

// Test inserting preserves existing sibling links properly
TEST_F(InsertAfterChildTest_191, PreservesExistingSiblingLinks_191) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* a = doc.NewElement("a");
    XMLElement* b = doc.NewElement("b");
    XMLElement* c = doc.NewElement("c");
    XMLElement* d = doc.NewElement("d");

    root->InsertEndChild(a);
    root->InsertEndChild(b);
    root->InsertEndChild(d);

    // Insert c between b and d
    root->InsertAfterChild(b, c);

    // Full chain: a -> b -> c -> d
    EXPECT_EQ(a->NextSibling(), b);
    EXPECT_EQ(b->NextSibling(), c);
    EXPECT_EQ(c->NextSibling(), d);
    EXPECT_EQ(d->NextSibling(), nullptr);

    EXPECT_EQ(d->PreviousSibling(), c);
    EXPECT_EQ(c->PreviousSibling(), b);
    EXPECT_EQ(b->PreviousSibling(), a);
    EXPECT_EQ(a->PreviousSibling(), nullptr);

    EXPECT_EQ(root->FirstChild(), a);
    EXPECT_EQ(root->LastChild(), d);
}

// Test NoChildren returns false after insertion
TEST_F(InsertAfterChildTest_191, NoChildrenReturnsFalseAfterInsert_191) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    EXPECT_TRUE(root->NoChildren());

    XMLElement* child1 = doc.NewElement("child1");
    root->InsertEndChild(child1);

    EXPECT_FALSE(root->NoChildren());

    XMLElement* child2 = doc.NewElement("child2");
    root->InsertAfterChild(child1, child2);

    EXPECT_FALSE(root->NoChildren());
    EXPECT_EQ(root->ChildElementCount(), 2);
}
