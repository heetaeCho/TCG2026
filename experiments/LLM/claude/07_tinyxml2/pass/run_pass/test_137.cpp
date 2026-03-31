#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLConstHandleLastChildElementTest_137 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test LastChildElement on a null node returns a handle with null ToElement
TEST_F(XMLConstHandleLastChildElementTest_137, NullNode_ReturnsNullHandle_137) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.LastChildElement();
    EXPECT_EQ(nullptr, result.ToElement());
    EXPECT_EQ(nullptr, result.ToNode());
}

// Test LastChildElement with a name on a null node returns a handle with null ToElement
TEST_F(XMLConstHandleLastChildElementTest_137, NullNodeWithName_ReturnsNullHandle_137) {
    XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    XMLConstHandle result = handle.LastChildElement("child");
    EXPECT_EQ(nullptr, result.ToElement());
    EXPECT_EQ(nullptr, result.ToNode());
}

// Test LastChildElement on a valid node with no children returns null handle
TEST_F(XMLConstHandleLastChildElementTest_137, ValidNodeNoChildren_ReturnsNullHandle_137) {
    XMLDocument doc;
    doc.Parse("<root/>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);

    XMLConstHandle handle(root);
    XMLConstHandle result = handle.LastChildElement();
    EXPECT_EQ(nullptr, result.ToElement());
}

// Test LastChildElement on a valid node with one child element (no name filter)
TEST_F(XMLConstHandleLastChildElementTest_137, ValidNodeOneChild_ReturnsChild_137) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);

    XMLConstHandle handle(root);
    XMLConstHandle result = handle.LastChildElement();
    ASSERT_NE(nullptr, result.ToElement());
    EXPECT_STREQ("child", result.ToElement()->Name());
}

// Test LastChildElement on a valid node with multiple children returns the last one
TEST_F(XMLConstHandleLastChildElementTest_137, ValidNodeMultipleChildren_ReturnsLastChild_137) {
    XMLDocument doc;
    doc.Parse("<root><first/><second/><third/></root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);

    XMLConstHandle handle(root);
    XMLConstHandle result = handle.LastChildElement();
    ASSERT_NE(nullptr, result.ToElement());
    EXPECT_STREQ("third", result.ToElement()->Name());
}

// Test LastChildElement with a specific name filter
TEST_F(XMLConstHandleLastChildElementTest_137, ValidNodeWithNameFilter_ReturnsLastMatchingChild_137) {
    XMLDocument doc;
    doc.Parse("<root><item>1</item><other/><item>2</item><extra/></root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);

    XMLConstHandle handle(root);
    XMLConstHandle result = handle.LastChildElement("item");
    ASSERT_NE(nullptr, result.ToElement());
    EXPECT_STREQ("item", result.ToElement()->Name());
    EXPECT_STREQ("2", result.ToElement()->GetText());
}

// Test LastChildElement with a name that doesn't match any child
TEST_F(XMLConstHandleLastChildElementTest_137, ValidNodeWithNonMatchingName_ReturnsNullHandle_137) {
    XMLDocument doc;
    doc.Parse("<root><child1/><child2/></root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);

    XMLConstHandle handle(root);
    XMLConstHandle result = handle.LastChildElement("nonexistent");
    EXPECT_EQ(nullptr, result.ToElement());
}

// Test LastChildElement with name filter where only one child matches
TEST_F(XMLConstHandleLastChildElementTest_137, ValidNodeSingleMatchingChild_ReturnsThatChild_137) {
    XMLDocument doc;
    doc.Parse("<root><alpha/><beta/><gamma/></root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);

    XMLConstHandle handle(root);
    XMLConstHandle result = handle.LastChildElement("beta");
    ASSERT_NE(nullptr, result.ToElement());
    EXPECT_STREQ("beta", result.ToElement()->Name());
}

// Test LastChildElement called on an XMLDocument node
TEST_F(XMLConstHandleLastChildElementTest_137, DocumentNode_ReturnsLastChildElement_137) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");

    XMLConstHandle handle(static_cast<const XMLNode*>(&doc));
    XMLConstHandle result = handle.LastChildElement("root");
    ASSERT_NE(nullptr, result.ToElement());
    EXPECT_STREQ("root", result.ToElement()->Name());
}

// Test LastChildElement with nullptr name (default) behaves the same as no argument
TEST_F(XMLConstHandleLastChildElementTest_137, ExplicitNullptrName_ReturnsLastChild_137) {
    XMLDocument doc;
    doc.Parse("<root><a/><b/><c/></root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);

    XMLConstHandle handle(root);
    XMLConstHandle result = handle.LastChildElement(nullptr);
    ASSERT_NE(nullptr, result.ToElement());
    EXPECT_STREQ("c", result.ToElement()->Name());
}

// Test chaining: LastChildElement on a result of LastChildElement
TEST_F(XMLConstHandleLastChildElementTest_137, Chaining_LastChildElementOnResult_137) {
    XMLDocument doc;
    doc.Parse("<root><parent><inner1/><inner2/></parent></root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);

    XMLConstHandle handle(root);
    XMLConstHandle result = handle.LastChildElement("parent").LastChildElement("inner2");
    ASSERT_NE(nullptr, result.ToElement());
    EXPECT_STREQ("inner2", result.ToElement()->Name());
}

// Test chaining where intermediate result is null
TEST_F(XMLConstHandleLastChildElementTest_137, ChainingNullIntermediate_ReturnsNull_137) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);

    XMLConstHandle handle(root);
    XMLConstHandle result = handle.LastChildElement("nonexistent").LastChildElement("anything");
    EXPECT_EQ(nullptr, result.ToElement());
    EXPECT_EQ(nullptr, result.ToNode());
}

// Test LastChildElement with empty string name
TEST_F(XMLConstHandleLastChildElementTest_137, EmptyStringName_ReturnsNullOrNoMatch_137) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);

    XMLConstHandle handle(root);
    XMLConstHandle result = handle.LastChildElement("");
    // An empty string name should not match "child"
    EXPECT_EQ(nullptr, result.ToElement());
}

// Test that ToNode on the result of LastChildElement also works
TEST_F(XMLConstHandleLastChildElementTest_137, ResultToNode_IsNotNull_137) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);

    XMLConstHandle handle(root);
    XMLConstHandle result = handle.LastChildElement();
    EXPECT_NE(nullptr, result.ToNode());
    EXPECT_NE(nullptr, result.ToElement());
}

// Test LastChildElement on a node with mixed content (text + elements)
TEST_F(XMLConstHandleLastChildElementTest_137, MixedContent_ReturnsLastElement_137) {
    XMLDocument doc;
    doc.Parse("<root>Some text<elem1/>More text<elem2/></root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);

    XMLConstHandle handle(root);
    XMLConstHandle result = handle.LastChildElement();
    ASSERT_NE(nullptr, result.ToElement());
    EXPECT_STREQ("elem2", result.ToElement()->Name());
}

// Test copy constructor preserves the handle state for LastChildElement
TEST_F(XMLConstHandleLastChildElementTest_137, CopyConstructor_PreservesState_137) {
    XMLDocument doc;
    doc.Parse("<root><a/><b/></root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);

    XMLConstHandle handle1(root);
    XMLConstHandle handle2(handle1);
    XMLConstHandle result = handle2.LastChildElement();
    ASSERT_NE(nullptr, result.ToElement());
    EXPECT_STREQ("b", result.ToElement()->Name());
}

// Test assignment operator preserves the handle state for LastChildElement
TEST_F(XMLConstHandleLastChildElementTest_137, AssignmentOperator_PreservesState_137) {
    XMLDocument doc;
    doc.Parse("<root><x/><y/></root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);

    XMLConstHandle handle1(root);
    XMLConstHandle handle2(static_cast<const XMLNode*>(nullptr));
    handle2 = handle1;
    XMLConstHandle result = handle2.LastChildElement();
    ASSERT_NE(nullptr, result.ToElement());
    EXPECT_STREQ("y", result.ToElement()->Name());
}
