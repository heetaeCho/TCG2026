#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLHandlePreviousSiblingTest_124 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }
};

// Test PreviousSibling on a null handle returns a null handle
TEST_F(XMLHandlePreviousSiblingTest_124, NullHandle_ReturnsNullHandle_124) {
    XMLHandle nullHandle(static_cast<XMLNode*>(nullptr));
    XMLHandle result = nullHandle.PreviousSibling();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test PreviousSibling on the first child (no previous sibling) returns null handle
TEST_F(XMLHandlePreviousSiblingTest_124, FirstChild_NoPreviousSibling_ReturnsNull_124) {
    doc.Parse("<root><first/><second/><third/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLNode* firstChild = root->FirstChild();
    ASSERT_NE(firstChild, nullptr);

    XMLHandle handle(firstChild);
    XMLHandle result = handle.PreviousSibling();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test PreviousSibling on the second child returns the first child
TEST_F(XMLHandlePreviousSiblingTest_124, SecondChild_ReturnFirstChild_124) {
    doc.Parse("<root><first/><second/><third/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLElement* secondChild = root->FirstChildElement("second");
    ASSERT_NE(secondChild, nullptr);

    XMLHandle handle(secondChild);
    XMLHandle result = handle.PreviousSibling();
    ASSERT_NE(result.ToNode(), nullptr);

    XMLElement* prevElem = result.ToElement();
    ASSERT_NE(prevElem, nullptr);
    EXPECT_STREQ(prevElem->Name(), "first");
}

// Test PreviousSibling on the third child returns the second child
TEST_F(XMLHandlePreviousSiblingTest_124, ThirdChild_ReturnSecondChild_124) {
    doc.Parse("<root><first/><second/><third/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLElement* thirdChild = root->FirstChildElement("third");
    ASSERT_NE(thirdChild, nullptr);

    XMLHandle handle(thirdChild);
    XMLHandle result = handle.PreviousSibling();
    ASSERT_NE(result.ToNode(), nullptr);

    XMLElement* prevElem = result.ToElement();
    ASSERT_NE(prevElem, nullptr);
    EXPECT_STREQ(prevElem->Name(), "second");
}

// Test PreviousSibling on a single child element returns null handle
TEST_F(XMLHandlePreviousSiblingTest_124, SingleChild_ReturnsNull_124) {
    doc.Parse("<root><only/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLElement* onlyChild = root->FirstChildElement("only");
    ASSERT_NE(onlyChild, nullptr);

    XMLHandle handle(onlyChild);
    XMLHandle result = handle.PreviousSibling();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test PreviousSibling on the root element of the document (no previous sibling at top level)
TEST_F(XMLHandlePreviousSiblingTest_124, RootElement_NoPreviousSibling_124) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLHandle handle(root);
    XMLHandle result = handle.PreviousSibling();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test PreviousSibling with mixed node types (text + elements)
TEST_F(XMLHandlePreviousSiblingTest_124, MixedNodeTypes_TextBeforeElement_124) {
    doc.Parse("<root>Hello<child/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);

    XMLHandle handle(child);
    XMLHandle result = handle.PreviousSibling();
    ASSERT_NE(result.ToNode(), nullptr);

    // The previous sibling should be the text node "Hello"
    XMLText* textNode = result.ToText();
    ASSERT_NE(textNode, nullptr);
    EXPECT_STREQ(textNode->Value(), "Hello");
}

// Test chaining PreviousSibling calls
TEST_F(XMLHandlePreviousSiblingTest_124, ChainingPreviousSibling_124) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLElement* c = root->FirstChildElement("c");
    ASSERT_NE(c, nullptr);

    XMLHandle handle(c);
    XMLHandle bHandle = handle.PreviousSibling();
    ASSERT_NE(bHandle.ToNode(), nullptr);
    EXPECT_STREQ(bHandle.ToElement()->Name(), "b");

    XMLHandle aHandle = bHandle.PreviousSibling();
    ASSERT_NE(aHandle.ToNode(), nullptr);
    EXPECT_STREQ(aHandle.ToElement()->Name(), "a");

    XMLHandle nullHandle = aHandle.PreviousSibling();
    EXPECT_EQ(nullHandle.ToNode(), nullptr);
}

// Test PreviousSibling after chaining from null returns null
TEST_F(XMLHandlePreviousSiblingTest_124, ChainingFromNull_ReturnsNull_124) {
    XMLHandle nullHandle(static_cast<XMLNode*>(nullptr));
    XMLHandle result = nullHandle.PreviousSibling().PreviousSibling();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test PreviousSibling with comment nodes
TEST_F(XMLHandlePreviousSiblingTest_124, CommentBeforeElement_124) {
    doc.Parse("<root><!--comment--><child/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);

    XMLHandle handle(child);
    XMLHandle result = handle.PreviousSibling();
    ASSERT_NE(result.ToNode(), nullptr);

    XMLComment* comment = result.ToNode()->ToComment();
    ASSERT_NE(comment, nullptr);
    EXPECT_STREQ(comment->Value(), "comment");
}

// Test constructing XMLHandle from reference and calling PreviousSibling
TEST_F(XMLHandlePreviousSiblingTest_124, ConstructFromReference_124) {
    doc.Parse("<root><a/><b/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLElement* b = root->FirstChildElement("b");
    ASSERT_NE(b, nullptr);

    XMLHandle handle(*b);
    XMLHandle result = handle.PreviousSibling();
    ASSERT_NE(result.ToNode(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "a");
}

// Test copy constructor preserves behavior of PreviousSibling
TEST_F(XMLHandlePreviousSiblingTest_124, CopyConstructor_124) {
    doc.Parse("<root><a/><b/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLElement* b = root->FirstChildElement("b");
    ASSERT_NE(b, nullptr);

    XMLHandle original(b);
    XMLHandle copy(original);
    XMLHandle result = copy.PreviousSibling();
    ASSERT_NE(result.ToNode(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "a");
}

// Test assignment operator preserves behavior of PreviousSibling
TEST_F(XMLHandlePreviousSiblingTest_124, AssignmentOperator_124) {
    doc.Parse("<root><a/><b/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLElement* b = root->FirstChildElement("b");
    ASSERT_NE(b, nullptr);

    XMLHandle original(b);
    XMLHandle assigned(static_cast<XMLNode*>(nullptr));
    assigned = original;
    XMLHandle result = assigned.PreviousSibling();
    ASSERT_NE(result.ToNode(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "a");
}
