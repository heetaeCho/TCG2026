#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLConstHandlePreviousSiblingTest_138 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }
};

// Test PreviousSibling on a null node handle returns a handle with null node
TEST_F(XMLConstHandlePreviousSiblingTest_138, NullNodeReturnsNullHandle_138) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle prev = handle.PreviousSibling();
    EXPECT_EQ(prev.ToNode(), nullptr);
}

// Test PreviousSibling on the first child (no previous sibling) returns null handle
TEST_F(XMLConstHandlePreviousSiblingTest_138, FirstChildHasNoPreviousSibling_138) {
    doc.Parse("<root><child1/><child2/><child3/></root>");
    ASSERT_FALSE(doc.Error());

    const XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const XMLNode* firstChild = root->FirstChild();
    ASSERT_NE(firstChild, nullptr);

    XMLConstHandle handle(firstChild);
    XMLConstHandle prev = handle.PreviousSibling();
    EXPECT_EQ(prev.ToNode(), nullptr);
}

// Test PreviousSibling on the second child returns the first child
TEST_F(XMLConstHandlePreviousSiblingTest_138, SecondChildPreviousSiblingIsFirstChild_138) {
    doc.Parse("<root><child1/><child2/><child3/></root>");
    ASSERT_FALSE(doc.Error());

    const XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const XMLNode* firstChild = root->FirstChild();
    ASSERT_NE(firstChild, nullptr);
    const XMLNode* secondChild = firstChild->NextSibling();
    ASSERT_NE(secondChild, nullptr);

    XMLConstHandle handle(secondChild);
    XMLConstHandle prev = handle.PreviousSibling();
    EXPECT_EQ(prev.ToNode(), firstChild);
}

// Test PreviousSibling on the third child returns the second child
TEST_F(XMLConstHandlePreviousSiblingTest_138, ThirdChildPreviousSiblingIsSecondChild_138) {
    doc.Parse("<root><child1/><child2/><child3/></root>");
    ASSERT_FALSE(doc.Error());

    const XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const XMLNode* firstChild = root->FirstChild();
    ASSERT_NE(firstChild, nullptr);
    const XMLNode* secondChild = firstChild->NextSibling();
    ASSERT_NE(secondChild, nullptr);
    const XMLNode* thirdChild = secondChild->NextSibling();
    ASSERT_NE(thirdChild, nullptr);

    XMLConstHandle handle(thirdChild);
    XMLConstHandle prev = handle.PreviousSibling();
    EXPECT_EQ(prev.ToNode(), secondChild);
}

// Test PreviousSibling on a single child returns null handle
TEST_F(XMLConstHandlePreviousSiblingTest_138, SingleChildHasNoPreviousSibling_138) {
    doc.Parse("<root><only/></root>");
    ASSERT_FALSE(doc.Error());

    const XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const XMLNode* onlyChild = root->FirstChild();
    ASSERT_NE(onlyChild, nullptr);

    XMLConstHandle handle(onlyChild);
    XMLConstHandle prev = handle.PreviousSibling();
    EXPECT_EQ(prev.ToNode(), nullptr);
}

// Test chaining PreviousSibling calls to traverse backwards
TEST_F(XMLConstHandlePreviousSiblingTest_138, ChainingPreviousSiblingTraversesBackward_138) {
    doc.Parse("<root><a/><b/><c/><d/></root>");
    ASSERT_FALSE(doc.Error());

    const XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const XMLNode* lastChild = root->LastChild();
    ASSERT_NE(lastChild, nullptr);

    XMLConstHandle handle(lastChild);
    // d -> c
    XMLConstHandle prevC = handle.PreviousSibling();
    EXPECT_NE(prevC.ToNode(), nullptr);
    // c -> b
    XMLConstHandle prevB = prevC.PreviousSibling();
    EXPECT_NE(prevB.ToNode(), nullptr);
    // b -> a
    XMLConstHandle prevA = prevB.PreviousSibling();
    EXPECT_NE(prevA.ToNode(), nullptr);
    // a -> null
    XMLConstHandle prevNull = prevA.PreviousSibling();
    EXPECT_EQ(prevNull.ToNode(), nullptr);
}

// Test PreviousSibling on root element of document (no previous sibling at doc level)
TEST_F(XMLConstHandlePreviousSiblingTest_138, RootElementNoPreviousSibling_138) {
    doc.Parse("<root/>");
    ASSERT_FALSE(doc.Error());

    const XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle prev = handle.PreviousSibling();
    // Root might or might not have a previous sibling (e.g., XML declaration).
    // Without a declaration, it should be null.
    // This tests the observable behavior.
    // With just "<root/>", no declaration precedes it.
    EXPECT_EQ(prev.ToNode(), nullptr);
}

// Test PreviousSibling when XML declaration precedes root element
TEST_F(XMLConstHandlePreviousSiblingTest_138, RootElementWithDeclarationHasPreviousSibling_138) {
    doc.Parse("<?xml version=\"1.0\"?><root/>");
    ASSERT_FALSE(doc.Error());

    const XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    XMLConstHandle prev = handle.PreviousSibling();
    EXPECT_NE(prev.ToNode(), nullptr);
    // The previous sibling should be the declaration
    EXPECT_NE(prev.ToDeclaration(), nullptr);
}

// Test PreviousSibling with mixed node types (text, elements, comments)
TEST_F(XMLConstHandlePreviousSiblingTest_138, MixedNodeTypesPreviousSibling_138) {
    doc.Parse("<root>text<!-- comment --><elem/></root>");
    ASSERT_FALSE(doc.Error());

    const XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const XMLNode* lastChild = root->LastChild();
    ASSERT_NE(lastChild, nullptr);
    // lastChild should be <elem/>

    XMLConstHandle handle(lastChild);
    XMLConstHandle prev = handle.PreviousSibling();
    EXPECT_NE(prev.ToNode(), nullptr);
    // Previous sibling should be the comment node

    XMLConstHandle prevPrev = prev.PreviousSibling();
    EXPECT_NE(prevPrev.ToNode(), nullptr);
    // Previous of comment should be the text node
    EXPECT_NE(prevPrev.ToText(), nullptr);
}

// Test that PreviousSibling result from null handle can be chained without crashing
TEST_F(XMLConstHandlePreviousSiblingTest_138, ChainingOnNullHandleDoesNotCrash_138) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle prev1 = handle.PreviousSibling();
    XMLConstHandle prev2 = prev1.PreviousSibling();
    XMLConstHandle prev3 = prev2.PreviousSibling();
    EXPECT_EQ(prev3.ToNode(), nullptr);
}

// Test constructing XMLConstHandle from reference and using PreviousSibling
TEST_F(XMLConstHandlePreviousSiblingTest_138, ConstructFromReferenceAndPreviousSibling_138) {
    doc.Parse("<root><a/><b/></root>");
    ASSERT_FALSE(doc.Error());

    const XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const XMLNode* secondChild = root->FirstChild()->NextSibling();
    ASSERT_NE(secondChild, nullptr);

    XMLConstHandle handle(*secondChild);
    XMLConstHandle prev = handle.PreviousSibling();
    EXPECT_NE(prev.ToNode(), nullptr);
    EXPECT_EQ(prev.ToNode(), root->FirstChild());
}

// Test copy constructor preserves behavior of PreviousSibling
TEST_F(XMLConstHandlePreviousSiblingTest_138, CopyConstructorPreservesBehavior_138) {
    doc.Parse("<root><a/><b/></root>");
    ASSERT_FALSE(doc.Error());

    const XMLElement* root = doc.RootElement();
    const XMLNode* secondChild = root->FirstChild()->NextSibling();

    XMLConstHandle original(secondChild);
    XMLConstHandle copy(original);

    XMLConstHandle prevOriginal = original.PreviousSibling();
    XMLConstHandle prevCopy = copy.PreviousSibling();

    EXPECT_EQ(prevOriginal.ToNode(), prevCopy.ToNode());
}

// Test assignment operator preserves behavior of PreviousSibling
TEST_F(XMLConstHandlePreviousSiblingTest_138, AssignmentOperatorPreservesBehavior_138) {
    doc.Parse("<root><a/><b/></root>");
    ASSERT_FALSE(doc.Error());

    const XMLElement* root = doc.RootElement();
    const XMLNode* secondChild = root->FirstChild()->NextSibling();

    XMLConstHandle original(secondChild);
    XMLConstHandle assigned(static_cast<const XMLNode*>(nullptr));
    assigned = original;

    XMLConstHandle prevOriginal = original.PreviousSibling();
    XMLConstHandle prevAssigned = assigned.PreviousSibling();

    EXPECT_EQ(prevOriginal.ToNode(), prevAssigned.ToNode());
}
