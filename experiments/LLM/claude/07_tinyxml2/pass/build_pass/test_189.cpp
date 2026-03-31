#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLNodeInsertEndChildTest_189 : public ::testing::Test {
protected:
    void SetUp() override {
        doc = new XMLDocument();
    }

    void TearDown() override {
        delete doc;
    }

    XMLDocument* doc;
};

// Test inserting a single element as end child
TEST_F(XMLNodeInsertEndChildTest_189, InsertSingleChild_189) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);

    XMLElement* child = doc->NewElement("child");
    XMLNode* result = root->InsertEndChild(child);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, child);
    EXPECT_FALSE(root->NoChildren());
    EXPECT_EQ(root->FirstChild(), child);
    EXPECT_EQ(root->LastChild(), child);
}

// Test inserting multiple children - order should be preserved
TEST_F(XMLNodeInsertEndChildTest_189, InsertMultipleChildren_189) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);

    XMLElement* child1 = doc->NewElement("child1");
    XMLElement* child2 = doc->NewElement("child2");
    XMLElement* child3 = doc->NewElement("child3");

    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    root->InsertEndChild(child3);

    EXPECT_EQ(root->FirstChild(), child1);
    EXPECT_EQ(root->LastChild(), child3);

    // Check ordering via sibling traversal
    EXPECT_EQ(child1->NextSibling(), child2);
    EXPECT_EQ(child2->NextSibling(), child3);
    EXPECT_EQ(child3->NextSibling(), nullptr);

    // Check reverse ordering
    EXPECT_EQ(child3->PreviousSibling(), child2);
    EXPECT_EQ(child2->PreviousSibling(), child1);
    EXPECT_EQ(child1->PreviousSibling(), nullptr);
}

// Test that parent is set correctly after InsertEndChild
TEST_F(XMLNodeInsertEndChildTest_189, ParentIsSetCorrectly_189) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);

    XMLElement* child = doc->NewElement("child");
    root->InsertEndChild(child);

    EXPECT_EQ(child->Parent(), root);
}

// Test inserting a child from a different document returns null
TEST_F(XMLNodeInsertEndChildTest_189, InsertChildFromDifferentDocumentReturnsNull_189) {
    XMLDocument doc2;
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);

    XMLElement* foreignChild = doc2.NewElement("foreign");

    // Inserting a node from a different document should fail
    // According to the code, it returns 0 if documents don't match
    XMLNode* result = root->InsertEndChild(foreignChild);
    EXPECT_EQ(result, nullptr);

    // Clean up the foreign child since it wasn't inserted
    doc2.InsertEndChild(foreignChild);
}

// Test that InsertEndChild returns the inserted node
TEST_F(XMLNodeInsertEndChildTest_189, ReturnsInsertedNode_189) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);

    XMLElement* child = doc->NewElement("child");
    XMLNode* result = root->InsertEndChild(child);

    EXPECT_EQ(result, child);
}

// Test inserting a text node as end child
TEST_F(XMLNodeInsertEndChildTest_189, InsertTextNode_189) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);

    XMLText* text = doc->NewText("Hello World");
    XMLNode* result = root->InsertEndChild(text);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(root->FirstChild(), text);
    EXPECT_EQ(root->LastChild(), text);
}

// Test inserting a comment node as end child
TEST_F(XMLNodeInsertEndChildTest_189, InsertCommentNode_189) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);

    XMLComment* comment = doc->NewComment("This is a comment");
    XMLNode* result = root->InsertEndChild(comment);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(root->FirstChild(), comment);
}

// Test ChildElementCount after multiple InsertEndChild calls
TEST_F(XMLNodeInsertEndChildTest_189, ChildElementCountAfterInsertions_189) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);

    EXPECT_EQ(root->ChildElementCount(), 0);

    root->InsertEndChild(doc->NewElement("a"));
    EXPECT_EQ(root->ChildElementCount(), 1);

    root->InsertEndChild(doc->NewElement("b"));
    EXPECT_EQ(root->ChildElementCount(), 2);

    root->InsertEndChild(doc->NewElement("c"));
    EXPECT_EQ(root->ChildElementCount(), 3);
}

// Test NoChildren before and after InsertEndChild
TEST_F(XMLNodeInsertEndChildTest_189, NoChildrenBeforeAndAfterInsert_189) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);

    EXPECT_TRUE(root->NoChildren());

    root->InsertEndChild(doc->NewElement("child"));
    EXPECT_FALSE(root->NoChildren());
}

// Test that inserting a node that is already a child of another parent moves it
TEST_F(XMLNodeInsertEndChildTest_189, MovingChildFromOneParentToAnother_189) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);

    XMLElement* parent1 = doc->NewElement("parent1");
    XMLElement* parent2 = doc->NewElement("parent2");
    root->InsertEndChild(parent1);
    root->InsertEndChild(parent2);

    XMLElement* child = doc->NewElement("child");
    parent1->InsertEndChild(child);

    EXPECT_EQ(child->Parent(), parent1);
    EXPECT_FALSE(parent1->NoChildren());

    // Now move child to parent2
    parent2->InsertEndChild(child);

    EXPECT_EQ(child->Parent(), parent2);
    EXPECT_TRUE(parent1->NoChildren());
    EXPECT_FALSE(parent2->NoChildren());
}

// Test inserting into document itself
TEST_F(XMLNodeInsertEndChildTest_189, InsertIntoDocument_189) {
    XMLElement* root = doc->NewElement("root");
    XMLNode* result = doc->InsertEndChild(root);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, root);
    EXPECT_FALSE(doc->NoChildren());
}

// Test mixed node types as children
TEST_F(XMLNodeInsertEndChildTest_189, MixedNodeTypes_189) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);

    XMLElement* elem = doc->NewElement("elem");
    XMLText* text = doc->NewText("text");
    XMLComment* comment = doc->NewComment("comment");

    root->InsertEndChild(elem);
    root->InsertEndChild(text);
    root->InsertEndChild(comment);

    EXPECT_EQ(root->FirstChild(), elem);
    EXPECT_EQ(root->LastChild(), comment);
    EXPECT_EQ(elem->NextSibling(), text);
    EXPECT_EQ(text->NextSibling(), comment);
}

// Test that FirstChildElement and LastChildElement work correctly after InsertEndChild
TEST_F(XMLNodeInsertEndChildTest_189, FirstAndLastChildElement_189) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);

    XMLElement* alpha = doc->NewElement("alpha");
    XMLElement* beta = doc->NewElement("beta");
    XMLElement* gamma = doc->NewElement("gamma");

    root->InsertEndChild(alpha);
    root->InsertEndChild(beta);
    root->InsertEndChild(gamma);

    EXPECT_EQ(root->FirstChildElement(), alpha);
    EXPECT_EQ(root->LastChildElement(), gamma);
    EXPECT_EQ(root->FirstChildElement("beta"), beta);
    EXPECT_EQ(root->LastChildElement("alpha"), alpha);
}

// Test deeply nested InsertEndChild
TEST_F(XMLNodeInsertEndChildTest_189, DeepNesting_189) {
    XMLElement* current = doc->NewElement("level0");
    doc->InsertEndChild(current);

    for (int i = 1; i <= 10; i++) {
        std::string name = "level" + std::to_string(i);
        XMLElement* child = doc->NewElement(name.c_str());
        current->InsertEndChild(child);
        current = child;
    }

    // Traverse down to verify
    const XMLNode* node = doc->FirstChild();
    for (int i = 0; i <= 10; i++) {
        ASSERT_NE(node, nullptr);
        if (i < 10) {
            EXPECT_FALSE(node->NoChildren());
            node = node->FirstChild();
        }
    }
    // The deepest node should have no children
    EXPECT_TRUE(node->NoChildren());
}

// Test InsertEndChild after DeleteChildren
TEST_F(XMLNodeInsertEndChildTest_189, InsertAfterDeleteChildren_189) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);

    root->InsertEndChild(doc->NewElement("a"));
    root->InsertEndChild(doc->NewElement("b"));
    EXPECT_EQ(root->ChildElementCount(), 2);

    root->DeleteChildren();
    EXPECT_TRUE(root->NoChildren());
    EXPECT_EQ(root->ChildElementCount(), 0);

    XMLElement* newChild = doc->NewElement("new");
    root->InsertEndChild(newChild);
    EXPECT_EQ(root->ChildElementCount(), 1);
    EXPECT_EQ(root->FirstChild(), newChild);
    EXPECT_EQ(root->LastChild(), newChild);
}

// Test that the prev pointer of the first child is null
TEST_F(XMLNodeInsertEndChildTest_189, FirstChildPrevIsNull_189) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);

    XMLElement* child1 = doc->NewElement("child1");
    XMLElement* child2 = doc->NewElement("child2");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);

    EXPECT_EQ(child1->PreviousSibling(), nullptr);
}

// Test that the next pointer of the last child is null
TEST_F(XMLNodeInsertEndChildTest_189, LastChildNextIsNull_189) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);

    XMLElement* child1 = doc->NewElement("child1");
    XMLElement* child2 = doc->NewElement("child2");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);

    EXPECT_EQ(child2->NextSibling(), nullptr);
}
