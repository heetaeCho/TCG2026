#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLNodeInsertFirstChildTest_190 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// Test inserting a single child as the first child of an empty parent
TEST_F(XMLNodeInsertFirstChildTest_190, InsertFirstChildIntoEmptyParent_190) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* child = doc.NewElement("child");
    XMLNode* result = parent->InsertFirstChild(child);
    
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, child);
    EXPECT_EQ(parent->FirstChild(), child);
    EXPECT_EQ(parent->LastChild(), child);
    EXPECT_FALSE(parent->NoChildren());
}

// Test inserting a first child when parent already has one child
TEST_F(XMLNodeInsertFirstChildTest_190, InsertFirstChildWhenOneChildExists_190) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* existingChild = doc.NewElement("existing");
    parent->InsertEndChild(existingChild);
    
    XMLElement* newFirst = doc.NewElement("newFirst");
    XMLNode* result = parent->InsertFirstChild(newFirst);
    
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, newFirst);
    EXPECT_EQ(parent->FirstChild(), newFirst);
    EXPECT_EQ(parent->LastChild(), existingChild);
    EXPECT_EQ(newFirst->NextSibling(), existingChild);
    EXPECT_EQ(existingChild->PreviousSibling(), newFirst);
    EXPECT_EQ(newFirst->PreviousSibling(), nullptr);
}

// Test inserting a first child when parent already has multiple children
TEST_F(XMLNodeInsertFirstChildTest_190, InsertFirstChildWhenMultipleChildrenExist_190) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    XMLElement* child3 = doc.NewElement("child3");
    parent->InsertEndChild(child1);
    parent->InsertEndChild(child2);
    parent->InsertEndChild(child3);
    
    XMLElement* newFirst = doc.NewElement("newFirst");
    XMLNode* result = parent->InsertFirstChild(newFirst);
    
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(parent->FirstChild(), newFirst);
    EXPECT_EQ(newFirst->NextSibling(), child1);
    EXPECT_EQ(child1->PreviousSibling(), newFirst);
    EXPECT_EQ(parent->LastChild(), child3);
    EXPECT_EQ(newFirst->PreviousSibling(), nullptr);
}

// Test that the returned node is the same as the added node
TEST_F(XMLNodeInsertFirstChildTest_190, ReturnValueIsAddedNode_190) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* child = doc.NewElement("child");
    XMLNode* result = parent->InsertFirstChild(child);
    
    EXPECT_EQ(result, child);
}

// Test that the parent of the inserted child is correctly set
TEST_F(XMLNodeInsertFirstChildTest_190, InsertedChildHasCorrectParent_190) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* child = doc.NewElement("child");
    parent->InsertFirstChild(child);
    
    EXPECT_EQ(child->Parent(), parent);
}

// Test inserting first child from a different document returns null
TEST_F(XMLNodeInsertFirstChildTest_190, InsertChildFromDifferentDocumentReturnsNull_190) {
    XMLDocument doc2;
    
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* foreignChild = doc2.NewElement("foreign");
    
    // According to the implementation, if addThis->_document != _document, return 0
    XMLNode* result = parent->InsertFirstChild(foreignChild);
    
    EXPECT_EQ(result, nullptr);
}

// Test inserting multiple children via InsertFirstChild maintains correct order
TEST_F(XMLNodeInsertFirstChildTest_190, MultipleInsertFirstChildMaintainsOrder_190) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    XMLElement* child3 = doc.NewElement("child3");
    
    parent->InsertFirstChild(child1); // List: child1
    parent->InsertFirstChild(child2); // List: child2, child1
    parent->InsertFirstChild(child3); // List: child3, child2, child1
    
    EXPECT_EQ(parent->FirstChild(), child3);
    EXPECT_EQ(child3->NextSibling(), child2);
    EXPECT_EQ(child2->NextSibling(), child1);
    EXPECT_EQ(child1->NextSibling(), nullptr);
    EXPECT_EQ(parent->LastChild(), child1);
    
    // Verify backward links
    EXPECT_EQ(child1->PreviousSibling(), child2);
    EXPECT_EQ(child2->PreviousSibling(), child3);
    EXPECT_EQ(child3->PreviousSibling(), nullptr);
}

// Test that NoChildren returns false after InsertFirstChild
TEST_F(XMLNodeInsertFirstChildTest_190, NoChildrenReturnsFalseAfterInsert_190) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    EXPECT_TRUE(parent->NoChildren());
    
    XMLElement* child = doc.NewElement("child");
    parent->InsertFirstChild(child);
    
    EXPECT_FALSE(parent->NoChildren());
}

// Test inserting a text node as first child
TEST_F(XMLNodeInsertFirstChildTest_190, InsertTextNodeAsFirstChild_190) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLText* text = doc.NewText("Hello");
    XMLNode* result = parent->InsertFirstChild(text);
    
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(parent->FirstChild(), text);
    EXPECT_NE(parent->FirstChild()->ToText(), nullptr);
}

// Test inserting a comment node as first child
TEST_F(XMLNodeInsertFirstChildTest_190, InsertCommentNodeAsFirstChild_190) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLComment* comment = doc.NewComment("A comment");
    XMLNode* result = parent->InsertFirstChild(comment);
    
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(parent->FirstChild(), comment);
    EXPECT_NE(parent->FirstChild()->ToComment(), nullptr);
}

// Test moving a child that is already elsewhere in the same document
TEST_F(XMLNodeInsertFirstChildTest_190, MoveExistingChildToFirstPosition_190) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    XMLElement* child3 = doc.NewElement("child3");
    parent->InsertEndChild(child1);
    parent->InsertEndChild(child2);
    parent->InsertEndChild(child3);
    
    // Move child3 to first position
    XMLNode* result = parent->InsertFirstChild(child3);
    
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(parent->FirstChild(), child3);
    EXPECT_EQ(child3->NextSibling(), child1);
    EXPECT_EQ(child1->NextSibling(), child2);
    EXPECT_EQ(child2->NextSibling(), nullptr);
    EXPECT_EQ(parent->LastChild(), child2);
}

// Test ChildElementCount after multiple InsertFirstChild operations
TEST_F(XMLNodeInsertFirstChildTest_190, ChildElementCountAfterInsertFirstChild_190) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    EXPECT_EQ(parent->ChildElementCount(), 0);
    
    XMLElement* child1 = doc.NewElement("child1");
    parent->InsertFirstChild(child1);
    EXPECT_EQ(parent->ChildElementCount(), 1);
    
    XMLElement* child2 = doc.NewElement("child2");
    parent->InsertFirstChild(child2);
    EXPECT_EQ(parent->ChildElementCount(), 2);
    
    XMLElement* child3 = doc.NewElement("child3");
    parent->InsertFirstChild(child3);
    EXPECT_EQ(parent->ChildElementCount(), 3);
}

// Test inserting first child on the document node itself
TEST_F(XMLNodeInsertFirstChildTest_190, InsertFirstChildOnDocumentNode_190) {
    XMLElement* element = doc.NewElement("root");
    XMLNode* result = doc.InsertFirstChild(element);
    
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(doc.FirstChild(), element);
}

// Test that FirstChildElement returns correctly after InsertFirstChild
TEST_F(XMLNodeInsertFirstChildTest_190, FirstChildElementAfterInsertFirstChild_190) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* child1 = doc.NewElement("alpha");
    parent->InsertEndChild(child1);
    
    XMLElement* child2 = doc.NewElement("beta");
    parent->InsertFirstChild(child2);
    
    // FirstChildElement with no name filter should return child2 (the first element)
    XMLElement* firstElem = parent->FirstChildElement();
    EXPECT_EQ(firstElem, child2);
    
    // FirstChildElement with name "alpha" should return child1
    XMLElement* alphaElem = parent->FirstChildElement("alpha");
    EXPECT_EQ(alphaElem, child1);
    
    // FirstChildElement with name "beta" should return child2
    XMLElement* betaElem = parent->FirstChildElement("beta");
    EXPECT_EQ(betaElem, child2);
}

// Test inserting a child that was previously under a different parent in the same document
TEST_F(XMLNodeInsertFirstChildTest_190, MoveChildBetweenParents_190) {
    XMLElement* parent1 = doc.NewElement("parent1");
    XMLElement* parent2 = doc.NewElement("parent2");
    doc.InsertEndChild(parent1);
    doc.InsertEndChild(parent2);
    
    XMLElement* child = doc.NewElement("child");
    parent1->InsertEndChild(child);
    EXPECT_EQ(child->Parent(), parent1);
    
    // Move child to parent2 as first child
    parent2->InsertFirstChild(child);
    EXPECT_EQ(child->Parent(), parent2);
    EXPECT_EQ(parent2->FirstChild(), child);
    EXPECT_TRUE(parent1->NoChildren());
}

// Test that LastChild is correctly maintained when only using InsertFirstChild
TEST_F(XMLNodeInsertFirstChildTest_190, LastChildCorrectWithInsertFirstChild_190) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* child1 = doc.NewElement("child1");
    parent->InsertFirstChild(child1);
    EXPECT_EQ(parent->LastChild(), child1);
    
    XMLElement* child2 = doc.NewElement("child2");
    parent->InsertFirstChild(child2);
    // LastChild should still be child1 since child2 was inserted at the front
    EXPECT_EQ(parent->LastChild(), child1);
    EXPECT_EQ(parent->FirstChild(), child2);
}
