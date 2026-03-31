#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLHandleLastChildTest_122 : public ::testing::Test {
protected:
    void SetUp() override {
        doc = new XMLDocument();
    }

    void TearDown() override {
        delete doc;
    }

    XMLDocument* doc;
};

// Test that LastChild on a null handle returns a null handle
TEST_F(XMLHandleLastChildTest_122, NullHandleReturnsNullHandle_122) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle result = handle.LastChild();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test that LastChild on an empty document (no children) returns null handle
TEST_F(XMLHandleLastChildTest_122, EmptyDocumentReturnsNullHandle_122) {
    XMLHandle handle(doc);
    XMLHandle result = handle.LastChild();
    // An empty document has no children
    // Actually XMLDocument may have a declaration, let's just check it doesn't crash
    // For a truly empty document:
    doc->DeleteChildren();
    XMLHandle handle2(doc);
    XMLHandle result2 = handle2.LastChild();
    EXPECT_EQ(result2.ToNode(), nullptr);
}

// Test that LastChild returns the last child when there is exactly one child
TEST_F(XMLHandleLastChildTest_122, SingleChildReturnsLastChild_122) {
    doc->Parse("<root/>");
    XMLHandle handle(doc);
    XMLHandle result = handle.LastChild();
    ASSERT_NE(result.ToNode(), nullptr);
    EXPECT_EQ(result.ToNode(), doc->LastChild());
}

// Test that LastChild returns the last child when there are multiple children
TEST_F(XMLHandleLastChildTest_122, MultipleChildrenReturnsLastChild_122) {
    doc->Parse("<root><a/><b/><c/></root>");
    XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLHandle handle(root);
    XMLHandle result = handle.LastChild();
    ASSERT_NE(result.ToNode(), nullptr);
    EXPECT_EQ(result.ToNode(), root->LastChild());

    // The last child element should be "c"
    XMLElement* elem = result.ToElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "c");
}

// Test that LastChild returns the actual last child (which may be text, not element)
TEST_F(XMLHandleLastChildTest_122, LastChildCanBeTextNode_122) {
    doc->Parse("<root><a/>some text</root>");
    XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLHandle handle(root);
    XMLHandle result = handle.LastChild();
    ASSERT_NE(result.ToNode(), nullptr);
    // The last child should be the text node, not element "a"
    EXPECT_NE(result.ToText(), nullptr);
    EXPECT_EQ(result.ToElement(), nullptr);
}

// Test that LastChild on a node with no children returns null handle
TEST_F(XMLHandleLastChildTest_122, LeafNodeReturnsNullHandle_122) {
    doc->Parse("<root><leaf/></root>");
    XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLNode* leaf = root->FirstChildElement("leaf");
    ASSERT_NE(leaf, nullptr);

    XMLHandle handle(leaf);
    XMLHandle result = handle.LastChild();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test that chaining LastChild works correctly
TEST_F(XMLHandleLastChildTest_122, ChainingLastChild_122) {
    doc->Parse("<root><a><x/></a><b><y/><z/></b></root>");
    XMLHandle handle(doc);
    // doc -> LastChild() = root, root -> LastChild() = b, b -> LastChild() = z
    XMLHandle result = handle.LastChild().LastChild().LastChild();
    ASSERT_NE(result.ToNode(), nullptr);
    XMLElement* elem = result.ToElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "z");
}

// Test that LastChild after chaining through a dead-end returns null
TEST_F(XMLHandleLastChildTest_122, ChainingThroughDeadEndReturnsNull_122) {
    doc->Parse("<root><a/></root>");
    XMLHandle handle(doc);
    // doc -> LastChild = root, root -> LastChild = a, a -> LastChild = null, null -> LastChild = null
    XMLHandle result = handle.LastChild().LastChild().LastChild().LastChild();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test XMLHandle constructed from reference
TEST_F(XMLHandleLastChildTest_122, HandleFromReferenceLastChild_122) {
    doc->Parse("<root><first/><second/></root>");
    XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLHandle handle(*root);
    XMLHandle result = handle.LastChild();
    ASSERT_NE(result.ToNode(), nullptr);
    XMLElement* elem = result.ToElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "second");
}

// Test copy-constructed handle preserves behavior
TEST_F(XMLHandleLastChildTest_122, CopyConstructedHandleLastChild_122) {
    doc->Parse("<root><child/></root>");
    XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLHandle original(root);
    XMLHandle copy(original);
    XMLHandle result = copy.LastChild();
    ASSERT_NE(result.ToNode(), nullptr);
    XMLElement* elem = result.ToElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "child");
}

// Test assignment operator preserves behavior for LastChild
TEST_F(XMLHandleLastChildTest_122, AssignedHandleLastChild_122) {
    doc->Parse("<root><a/><b/></root>");
    XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLHandle handle1(static_cast<XMLNode*>(nullptr));
    XMLHandle handle2(root);
    handle1 = handle2;
    XMLHandle result = handle1.LastChild();
    ASSERT_NE(result.ToNode(), nullptr);
    XMLElement* elem = result.ToElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "b");
}

// Test LastChild with mixed node types (element, comment, text)
TEST_F(XMLHandleLastChildTest_122, MixedNodeTypesLastChild_122) {
    doc->Parse("<root><elem/><!-- comment --></root>");
    XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLHandle handle(root);
    XMLHandle result = handle.LastChild();
    ASSERT_NE(result.ToNode(), nullptr);
    // Last child should be the comment
    EXPECT_NE(result.ToNode()->ToComment(), nullptr);
}

// Test that LastChild result is consistent with XMLNode::LastChild
TEST_F(XMLHandleLastChildTest_122, ConsistentWithNodeLastChild_122) {
    doc->Parse("<root><a/><b/><c/><d/><e/></root>");
    XMLNode* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLHandle handle(root);
    XMLHandle result = handle.LastChild();
    EXPECT_EQ(result.ToNode(), root->LastChild());
}
