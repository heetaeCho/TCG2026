#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLNodeLastChildTest_54 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// Test that LastChild returns nullptr when the document has no children
TEST_F(XMLNodeLastChildTest_54, LastChildReturnsNullWhenNoChildren_54) {
    XMLDocument emptyDoc;
    // A fresh document with no parsed content should have no children (or only declaration)
    // We'll create an element and check it has no children
    XMLElement* elem = doc.NewElement("parent");
    doc.InsertEndChild(elem);
    // elem has no children
    const XMLNode* lastChild = elem->LastChild();
    EXPECT_EQ(lastChild, nullptr);
}

// Test that LastChild returns the only child when there is exactly one child
TEST_F(XMLNodeLastChildTest_54, LastChildReturnsSingleChild_54) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* child = doc.NewElement("child");
    parent->InsertEndChild(child);

    const XMLNode* lastChild = parent->LastChild();
    ASSERT_NE(lastChild, nullptr);
    EXPECT_EQ(lastChild, child);
}

// Test that LastChild returns the last inserted child when multiple children exist
TEST_F(XMLNodeLastChildTest_54, LastChildReturnsLastOfMultipleChildren_54) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);

    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    XMLElement* child3 = doc.NewElement("child3");
    parent->InsertEndChild(child1);
    parent->InsertEndChild(child2);
    parent->InsertEndChild(child3);

    const XMLNode* lastChild = parent->LastChild();
    ASSERT_NE(lastChild, nullptr);
    EXPECT_EQ(lastChild, child3);
}

// Test that LastChild returns the correct child after inserting via InsertFirstChild
TEST_F(XMLNodeLastChildTest_54, LastChildUnchangedAfterInsertFirstChild_54) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);

    XMLElement* child1 = doc.NewElement("child1");
    parent->InsertEndChild(child1);

    // Insert another child at the beginning
    XMLElement* child0 = doc.NewElement("child0");
    parent->InsertFirstChild(child0);

    // LastChild should still be child1
    const XMLNode* lastChild = parent->LastChild();
    ASSERT_NE(lastChild, nullptr);
    EXPECT_EQ(lastChild, child1);
}

// Test that LastChild updates correctly after deleting the last child
TEST_F(XMLNodeLastChildTest_54, LastChildUpdatesAfterDeletingLastChild_54) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);

    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    parent->InsertEndChild(child1);
    parent->InsertEndChild(child2);

    // Delete the last child
    parent->DeleteChild(child2);

    const XMLNode* lastChild = parent->LastChild();
    ASSERT_NE(lastChild, nullptr);
    EXPECT_EQ(lastChild, child1);
}

// Test that LastChild returns nullptr after all children are deleted
TEST_F(XMLNodeLastChildTest_54, LastChildReturnsNullAfterDeleteChildren_54) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);

    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    parent->InsertEndChild(child1);
    parent->InsertEndChild(child2);

    parent->DeleteChildren();

    const XMLNode* lastChild = parent->LastChild();
    EXPECT_EQ(lastChild, nullptr);
}

// Test that LastChild works on the document node itself
TEST_F(XMLNodeLastChildTest_54, LastChildOnDocumentNode_54) {
    doc.InsertEndChild(doc.NewElement("root"));

    const XMLNode* lastChild = doc.LastChild();
    ASSERT_NE(lastChild, nullptr);
    // The last child should be the root element we added
    EXPECT_NE(lastChild->ToElement(), nullptr);
}

// Test LastChild with mixed node types (elements, text, comments)
TEST_F(XMLNodeLastChildTest_54, LastChildWithMixedNodeTypes_54) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);

    XMLElement* child1 = doc.NewElement("child1");
    parent->InsertEndChild(child1);

    XMLComment* comment = doc.NewComment("a comment");
    parent->InsertEndChild(comment);

    XMLText* text = doc.NewText("some text");
    parent->InsertEndChild(text);

    const XMLNode* lastChild = parent->LastChild();
    ASSERT_NE(lastChild, nullptr);
    // The last child should be the text node
    EXPECT_NE(lastChild->ToText(), nullptr);
}

// Test that FirstChild and LastChild are the same when there is one child
TEST_F(XMLNodeLastChildTest_54, FirstAndLastChildSameWithOneChild_54) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);

    XMLElement* child = doc.NewElement("onlychild");
    parent->InsertEndChild(child);

    EXPECT_EQ(parent->FirstChild(), parent->LastChild());
}

// Test LastChild after InsertAfterChild
TEST_F(XMLNodeLastChildTest_54, LastChildAfterInsertAfterChild_54) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);

    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    parent->InsertEndChild(child1);
    parent->InsertEndChild(child2);

    // Insert a new child after child2 (which is the last child)
    XMLElement* child3 = doc.NewElement("child3");
    parent->InsertAfterChild(child2, child3);

    const XMLNode* lastChild = parent->LastChild();
    ASSERT_NE(lastChild, nullptr);
    EXPECT_EQ(lastChild, child3);
}

// Test LastChild consistency with parsed XML
TEST_F(XMLNodeLastChildTest_54, LastChildWithParsedXML_54) {
    const char* xml = "<root><a/><b/><c/></root>";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());

    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    const XMLNode* lastChild = root->LastChild();
    ASSERT_NE(lastChild, nullptr);
    ASSERT_NE(lastChild->ToElement(), nullptr);
    EXPECT_STREQ(lastChild->ToElement()->Name(), "c");
}

// Test that const and non-const versions are consistent
TEST_F(XMLNodeLastChildTest_54, ConstAndNonConstConsistency_54) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* child = doc.NewElement("child");
    parent->InsertEndChild(child);

    const XMLNode* constParent = parent;
    const XMLNode* constLastChild = constParent->LastChild();

    EXPECT_EQ(constLastChild, child);
}

// Test LastChild on deeply nested structure
TEST_F(XMLNodeLastChildTest_54, LastChildOnDeeplyNestedStructure_54) {
    const char* xml = "<a><b><c><d>text</d></c></b></a>";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());

    const XMLElement* a = doc.FirstChildElement("a");
    ASSERT_NE(a, nullptr);

    const XMLNode* bNode = a->LastChild();
    ASSERT_NE(bNode, nullptr);
    ASSERT_NE(bNode->ToElement(), nullptr);
    EXPECT_STREQ(bNode->ToElement()->Name(), "b");

    const XMLNode* cNode = bNode->LastChild();
    ASSERT_NE(cNode, nullptr);
    ASSERT_NE(cNode->ToElement(), nullptr);
    EXPECT_STREQ(cNode->ToElement()->Name(), "c");

    const XMLNode* dNode = cNode->LastChild();
    ASSERT_NE(dNode, nullptr);
    ASSERT_NE(dNode->ToElement(), nullptr);
    EXPECT_STREQ(dNode->ToElement()->Name(), "d");

    // d's last child should be a text node
    const XMLNode* textNode = dNode->LastChild();
    ASSERT_NE(textNode, nullptr);
    EXPECT_NE(textNode->ToText(), nullptr);
}
