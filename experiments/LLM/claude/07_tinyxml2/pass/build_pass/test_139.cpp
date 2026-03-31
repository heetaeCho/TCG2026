#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLConstHandlePreviousSiblingElementTest_139 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }
};

// Test PreviousSiblingElement on a null node handle returns a handle with null node
TEST_F(XMLConstHandlePreviousSiblingElementTest_139, NullNode_ReturnsNullHandle_139) {
    XMLConstHandle nullHandle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = nullHandle.PreviousSiblingElement();
    EXPECT_EQ(nullptr, result.ToElement());
    EXPECT_EQ(nullptr, result.ToNode());
}

// Test PreviousSiblingElement with a name on a null node handle returns a handle with null node
TEST_F(XMLConstHandlePreviousSiblingElementTest_139, NullNodeWithName_ReturnsNullHandle_139) {
    XMLConstHandle nullHandle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = nullHandle.PreviousSiblingElement("something");
    EXPECT_EQ(nullptr, result.ToElement());
    EXPECT_EQ(nullptr, result.ToNode());
}

// Test PreviousSiblingElement when there is no previous sibling element
TEST_F(XMLConstHandlePreviousSiblingElementTest_139, NoPreviousSibling_ReturnsNullHandle_139) {
    doc.Parse("<root><child1/></root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    const XMLElement* child1 = root->FirstChildElement("child1");
    ASSERT_NE(nullptr, child1);

    XMLConstHandle handle(child1);
    XMLConstHandle result = handle.PreviousSiblingElement();
    EXPECT_EQ(nullptr, result.ToElement());
}

// Test PreviousSiblingElement returns the correct previous sibling element
TEST_F(XMLConstHandlePreviousSiblingElementTest_139, HasPreviousSibling_ReturnsPreviousElement_139) {
    doc.Parse("<root><child1/><child2/><child3/></root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    const XMLElement* child3 = root->LastChildElement("child3");
    ASSERT_NE(nullptr, child3);

    XMLConstHandle handle(child3);
    XMLConstHandle result = handle.PreviousSiblingElement();
    ASSERT_NE(nullptr, result.ToElement());
    EXPECT_STREQ("child2", result.ToElement()->Name());
}

// Test PreviousSiblingElement with a specific name filter
TEST_F(XMLConstHandlePreviousSiblingElementTest_139, WithNameFilter_ReturnsMatchingPreviousElement_139) {
    doc.Parse("<root><alpha/><beta/><gamma/></root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    const XMLElement* gamma = root->LastChildElement("gamma");
    ASSERT_NE(nullptr, gamma);

    XMLConstHandle handle(gamma);
    XMLConstHandle result = handle.PreviousSiblingElement("alpha");
    ASSERT_NE(nullptr, result.ToElement());
    EXPECT_STREQ("alpha", result.ToElement()->Name());
}

// Test PreviousSiblingElement with a name filter that doesn't match any previous sibling
TEST_F(XMLConstHandlePreviousSiblingElementTest_139, WithNameFilter_NoMatch_ReturnsNullHandle_139) {
    doc.Parse("<root><alpha/><beta/><gamma/></root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    const XMLElement* gamma = root->LastChildElement("gamma");
    ASSERT_NE(nullptr, gamma);

    XMLConstHandle handle(gamma);
    XMLConstHandle result = handle.PreviousSiblingElement("nonexistent");
    EXPECT_EQ(nullptr, result.ToElement());
}

// Test PreviousSiblingElement with name filter skipping non-matching siblings
TEST_F(XMLConstHandlePreviousSiblingElementTest_139, WithNameFilter_SkipsNonMatching_139) {
    doc.Parse("<root><target/><skip1/><skip2/><current/></root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    const XMLElement* current = root->LastChildElement("current");
    ASSERT_NE(nullptr, current);

    XMLConstHandle handle(current);
    XMLConstHandle result = handle.PreviousSiblingElement("target");
    ASSERT_NE(nullptr, result.ToElement());
    EXPECT_STREQ("target", result.ToElement()->Name());
}

// Test PreviousSiblingElement on the first child with no default name
TEST_F(XMLConstHandlePreviousSiblingElementTest_139, FirstChild_NoPrevious_139) {
    doc.Parse("<root><only/></root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    const XMLElement* only = root->FirstChildElement("only");
    ASSERT_NE(nullptr, only);

    XMLConstHandle handle(only);
    XMLConstHandle result = handle.PreviousSiblingElement();
    EXPECT_EQ(nullptr, result.ToElement());
}

// Test chaining PreviousSiblingElement calls
TEST_F(XMLConstHandlePreviousSiblingElementTest_139, Chaining_ReturnsPreviousOfPrevious_139) {
    doc.Parse("<root><a/><b/><c/></root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    const XMLElement* c = root->LastChildElement("c");
    ASSERT_NE(nullptr, c);

    XMLConstHandle handle(c);
    XMLConstHandle resultB = handle.PreviousSiblingElement();
    ASSERT_NE(nullptr, resultB.ToElement());
    EXPECT_STREQ("b", resultB.ToElement()->Name());

    XMLConstHandle resultA = resultB.PreviousSiblingElement();
    ASSERT_NE(nullptr, resultA.ToElement());
    EXPECT_STREQ("a", resultA.ToElement()->Name());

    XMLConstHandle resultNull = resultA.PreviousSiblingElement();
    EXPECT_EQ(nullptr, resultNull.ToElement());
}

// Test PreviousSiblingElement with mixed content (text and elements)
TEST_F(XMLConstHandlePreviousSiblingElementTest_139, MixedContent_SkipsTextNodes_139) {
    doc.Parse("<root><elem1/>text<elem2/></root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    const XMLElement* elem2 = root->LastChildElement("elem2");
    ASSERT_NE(nullptr, elem2);

    XMLConstHandle handle(elem2);
    XMLConstHandle result = handle.PreviousSiblingElement();
    ASSERT_NE(nullptr, result.ToElement());
    EXPECT_STREQ("elem1", result.ToElement()->Name());
}

// Test PreviousSiblingElement with duplicate element names
TEST_F(XMLConstHandlePreviousSiblingElementTest_139, DuplicateNames_ReturnsNearestMatch_139) {
    doc.Parse("<root><item/><item/><item/></root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    const XMLElement* last = root->LastChildElement("item");
    ASSERT_NE(nullptr, last);

    XMLConstHandle handle(last);
    XMLConstHandle result = handle.PreviousSiblingElement("item");
    ASSERT_NE(nullptr, result.ToElement());
    // The result should be the second item (the one right before the last)
    // Verify it's not the same as the last
    EXPECT_NE(last, result.ToElement());
    EXPECT_STREQ("item", result.ToElement()->Name());
}

// Test PreviousSiblingElement constructed from a node reference
TEST_F(XMLConstHandlePreviousSiblingElementTest_139, ConstructedFromReference_Works_139) {
    doc.Parse("<root><a/><b/></root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    const XMLElement* b = root->LastChildElement("b");
    ASSERT_NE(nullptr, b);

    XMLConstHandle handle(*b);
    XMLConstHandle result = handle.PreviousSiblingElement();
    ASSERT_NE(nullptr, result.ToElement());
    EXPECT_STREQ("a", result.ToElement()->Name());
}

// Test that the result of PreviousSiblingElement can be used with ToNode
TEST_F(XMLConstHandlePreviousSiblingElementTest_139, ResultToNode_ReturnsValidNode_139) {
    doc.Parse("<root><a/><b/></root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    const XMLElement* b = root->LastChildElement("b");
    ASSERT_NE(nullptr, b);

    XMLConstHandle handle(b);
    XMLConstHandle result = handle.PreviousSiblingElement();
    ASSERT_NE(nullptr, result.ToNode());
    EXPECT_STREQ("a", result.ToNode()->Value());
}

// Test PreviousSiblingElement with empty name string
TEST_F(XMLConstHandlePreviousSiblingElementTest_139, EmptyNameString_139) {
    doc.Parse("<root><a/><b/></root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    const XMLElement* b = root->LastChildElement("b");
    ASSERT_NE(nullptr, b);

    // Passing empty string as name - should look for element with empty name
    // which typically won't match any element
    XMLConstHandle handle(b);
    XMLConstHandle result = handle.PreviousSiblingElement("");
    // Behavior depends on implementation - empty string may or may not match
    // This just tests it doesn't crash
}

// Test copy construction preserves behavior
TEST_F(XMLConstHandlePreviousSiblingElementTest_139, CopyConstruction_PreservesBehavior_139) {
    doc.Parse("<root><a/><b/></root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    const XMLElement* b = root->LastChildElement("b");
    ASSERT_NE(nullptr, b);

    XMLConstHandle original(b);
    XMLConstHandle copy(original);
    XMLConstHandle result = copy.PreviousSiblingElement();
    ASSERT_NE(nullptr, result.ToElement());
    EXPECT_STREQ("a", result.ToElement()->Name());
}
