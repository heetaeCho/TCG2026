#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLNodePreviousSiblingTest_56 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// Test that PreviousSibling returns nullptr for the root element (no sibling)
TEST_F(XMLNodePreviousSiblingTest_56, RootElementHasNoPreviousSibling_56) {
    doc.Parse("<root/>");
    const XMLNode* root = doc.FirstChild();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->PreviousSibling(), nullptr);
}

// Test that PreviousSibling returns nullptr for the first child
TEST_F(XMLNodePreviousSiblingTest_56, FirstChildHasNoPreviousSibling_56) {
    doc.Parse("<root><a/><b/><c/></root>");
    const XMLNode* root = doc.FirstChild();
    ASSERT_NE(root, nullptr);
    const XMLNode* firstChild = root->FirstChild();
    ASSERT_NE(firstChild, nullptr);
    EXPECT_EQ(firstChild->PreviousSibling(), nullptr);
}

// Test that PreviousSibling returns the correct previous node for the second child
TEST_F(XMLNodePreviousSiblingTest_56, SecondChildPreviousSiblingIsFirstChild_56) {
    doc.Parse("<root><a/><b/><c/></root>");
    const XMLNode* root = doc.FirstChild();
    ASSERT_NE(root, nullptr);
    const XMLNode* firstChild = root->FirstChild();
    ASSERT_NE(firstChild, nullptr);
    const XMLNode* secondChild = firstChild->NextSibling();
    ASSERT_NE(secondChild, nullptr);
    EXPECT_EQ(secondChild->PreviousSibling(), firstChild);
}

// Test that PreviousSibling returns the correct previous node for the third child
TEST_F(XMLNodePreviousSiblingTest_56, ThirdChildPreviousSiblingIsSecondChild_56) {
    doc.Parse("<root><a/><b/><c/></root>");
    const XMLNode* root = doc.FirstChild();
    ASSERT_NE(root, nullptr);
    const XMLNode* firstChild = root->FirstChild();
    ASSERT_NE(firstChild, nullptr);
    const XMLNode* secondChild = firstChild->NextSibling();
    ASSERT_NE(secondChild, nullptr);
    const XMLNode* thirdChild = secondChild->NextSibling();
    ASSERT_NE(thirdChild, nullptr);
    EXPECT_EQ(thirdChild->PreviousSibling(), secondChild);
}

// Test that PreviousSibling is consistent with NextSibling (round trip)
TEST_F(XMLNodePreviousSiblingTest_56, PreviousSiblingNextSiblingRoundTrip_56) {
    doc.Parse("<root><a/><b/></root>");
    const XMLNode* root = doc.FirstChild();
    ASSERT_NE(root, nullptr);
    const XMLNode* firstChild = root->FirstChild();
    ASSERT_NE(firstChild, nullptr);
    const XMLNode* secondChild = firstChild->NextSibling();
    ASSERT_NE(secondChild, nullptr);
    // Going forward then backward should return to the same node
    EXPECT_EQ(secondChild->PreviousSibling(), firstChild);
    EXPECT_EQ(firstChild->NextSibling(), secondChild);
}

// Test PreviousSibling with a single child (no siblings)
TEST_F(XMLNodePreviousSiblingTest_56, SingleChildHasNoPreviousSibling_56) {
    doc.Parse("<root><only/></root>");
    const XMLNode* root = doc.FirstChild();
    ASSERT_NE(root, nullptr);
    const XMLNode* only = root->FirstChild();
    ASSERT_NE(only, nullptr);
    EXPECT_EQ(only->PreviousSibling(), nullptr);
}

// Test PreviousSibling after inserting children dynamically
TEST_F(XMLNodePreviousSiblingTest_56, DynamicallyInsertedChildPreviousSibling_56) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);

    XMLElement* a = doc.NewElement("a");
    root->InsertEndChild(a);

    XMLElement* b = doc.NewElement("b");
    root->InsertEndChild(b);

    EXPECT_EQ(a->PreviousSibling(), nullptr);
    EXPECT_EQ(b->PreviousSibling(), a);
}

// Test PreviousSibling after InsertFirstChild (new first child should have no prev)
TEST_F(XMLNodePreviousSiblingTest_56, InsertFirstChildUpdatesPreviousSibling_56) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);

    XMLElement* b = doc.NewElement("b");
    root->InsertEndChild(b);

    XMLElement* a = doc.NewElement("a");
    root->InsertFirstChild(a);

    EXPECT_EQ(a->PreviousSibling(), nullptr);
    EXPECT_EQ(b->PreviousSibling(), a);
}

// Test PreviousSibling after InsertAfterChild
TEST_F(XMLNodePreviousSiblingTest_56, InsertAfterChildUpdatesPreviousSibling_56) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);

    XMLElement* a = doc.NewElement("a");
    root->InsertEndChild(a);

    XMLElement* c = doc.NewElement("c");
    root->InsertEndChild(c);

    XMLElement* b = doc.NewElement("b");
    root->InsertAfterChild(a, b);

    EXPECT_EQ(a->PreviousSibling(), nullptr);
    EXPECT_EQ(b->PreviousSibling(), a);
    EXPECT_EQ(c->PreviousSibling(), b);
}

// Test PreviousSibling after deleting a child
TEST_F(XMLNodePreviousSiblingTest_56, DeleteChildUpdatesPreviousSibling_56) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLElement* a = root->FirstChildElement("a");
    XMLElement* b = root->FirstChildElement("b");
    XMLElement* c = root->FirstChildElement("c");
    ASSERT_NE(a, nullptr);
    ASSERT_NE(b, nullptr);
    ASSERT_NE(c, nullptr);

    // Delete middle child 'b'
    root->DeleteChild(b);

    // Now 'c' previous sibling should be 'a'
    EXPECT_EQ(c->PreviousSibling(), a);
    EXPECT_EQ(a->PreviousSibling(), nullptr);
}

// Test PreviousSibling with mixed node types (elements and text)
TEST_F(XMLNodePreviousSiblingTest_56, MixedNodeTypesPreviousSibling_56) {
    doc.Parse("<root>text<a/></root>");
    const XMLNode* root = doc.FirstChild();
    ASSERT_NE(root, nullptr);
    const XMLNode* textNode = root->FirstChild();
    ASSERT_NE(textNode, nullptr);
    const XMLNode* elemNode = textNode->NextSibling();
    ASSERT_NE(elemNode, nullptr);

    EXPECT_EQ(textNode->PreviousSibling(), nullptr);
    EXPECT_EQ(elemNode->PreviousSibling(), textNode);
}

// Test PreviousSibling on document node itself
TEST_F(XMLNodePreviousSiblingTest_56, DocumentNodeHasNoPreviousSibling_56) {
    doc.Parse("<root/>");
    // The document itself should have no previous sibling
    EXPECT_EQ(doc.PreviousSibling(), nullptr);
}

// Test that LastChild's PreviousSibling chain walks back to FirstChild
TEST_F(XMLNodePreviousSiblingTest_56, WalkBackFromLastChildToFirstChild_56) {
    doc.Parse("<root><a/><b/><c/><d/></root>");
    const XMLNode* root = doc.FirstChild();
    ASSERT_NE(root, nullptr);

    const XMLNode* last = root->LastChild();
    ASSERT_NE(last, nullptr);

    // Walk backwards
    const XMLNode* current = last;
    int count = 1;
    while (current->PreviousSibling() != nullptr) {
        current = current->PreviousSibling();
        count++;
    }
    // Should have traversed 4 nodes
    EXPECT_EQ(count, 4);
    // current should now be the first child
    EXPECT_EQ(current, root->FirstChild());
}

// Test PreviousSibling with deeply cloned nodes
TEST_F(XMLNodePreviousSiblingTest_56, DeepClonedNodesPreviousSibling_56) {
    doc.Parse("<root><a/><b/></root>");
    XMLDocument targetDoc;
    const XMLNode* root = doc.FirstChild();
    ASSERT_NE(root, nullptr);

    XMLNode* cloned = root->DeepClone(&targetDoc);
    targetDoc.InsertFirstChild(cloned);

    const XMLNode* clonedFirst = cloned->FirstChild();
    ASSERT_NE(clonedFirst, nullptr);
    const XMLNode* clonedSecond = clonedFirst->NextSibling();
    ASSERT_NE(clonedSecond, nullptr);

    EXPECT_EQ(clonedFirst->PreviousSibling(), nullptr);
    EXPECT_EQ(clonedSecond->PreviousSibling(), clonedFirst);
}
