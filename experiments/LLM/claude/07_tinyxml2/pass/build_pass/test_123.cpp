#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLHandleLastChildElementTest_123 : public ::testing::Test {
protected:
    void SetUp() override {
        doc = new XMLDocument();
    }

    void TearDown() override {
        delete doc;
    }

    XMLDocument* doc;
};

// Test LastChildElement on an empty document (no children)
TEST_F(XMLHandleLastChildElementTest_123, EmptyDocument_ReturnsNullHandle_123) {
    XMLHandle handle(doc);
    XMLHandle result = handle.LastChildElement();
    EXPECT_EQ(result.ToElement(), nullptr);
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test LastChildElement with no name filter returns the last child element
TEST_F(XMLHandleLastChildElementTest_123, SingleChildElement_ReturnsIt_123) {
    doc->InsertEndChild(doc->NewElement("root"));
    XMLHandle handle(doc);
    XMLHandle result = handle.LastChildElement();
    ASSERT_NE(result.ToElement(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "root");
}

// Test LastChildElement returns the last element when multiple children exist
TEST_F(XMLHandleLastChildElementTest_123, MultipleChildren_ReturnsLastElement_123) {
    doc->InsertEndChild(doc->NewElement("first"));
    doc->InsertEndChild(doc->NewElement("second"));
    doc->InsertEndChild(doc->NewElement("third"));
    XMLHandle handle(doc);
    XMLHandle result = handle.LastChildElement();
    ASSERT_NE(result.ToElement(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "third");
}

// Test LastChildElement with a specific name filter
TEST_F(XMLHandleLastChildElementTest_123, WithNameFilter_ReturnsLastMatchingElement_123) {
    doc->InsertEndChild(doc->NewElement("alpha"));
    doc->InsertEndChild(doc->NewElement("beta"));
    doc->InsertEndChild(doc->NewElement("alpha"));
    doc->InsertEndChild(doc->NewElement("gamma"));
    XMLHandle handle(doc);
    XMLHandle result = handle.LastChildElement("alpha");
    ASSERT_NE(result.ToElement(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "alpha");
    // Verify it's the last "alpha" (not the first) by checking it's different from first
    XMLHandle firstAlpha = handle.FirstChildElement("alpha");
    ASSERT_NE(firstAlpha.ToElement(), nullptr);
    EXPECT_NE(result.ToElement(), firstAlpha.ToElement());
}

// Test LastChildElement with name filter that doesn't match any child
TEST_F(XMLHandleLastChildElementTest_123, WithNameFilter_NoMatch_ReturnsNullHandle_123) {
    doc->InsertEndChild(doc->NewElement("alpha"));
    doc->InsertEndChild(doc->NewElement("beta"));
    XMLHandle handle(doc);
    XMLHandle result = handle.LastChildElement("nonexistent");
    EXPECT_EQ(result.ToElement(), nullptr);
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test LastChildElement on a null XMLHandle (constructed with null node)
TEST_F(XMLHandleLastChildElementTest_123, NullNode_ReturnsNullHandle_123) {
    XMLHandle handle((XMLNode*)nullptr);
    XMLHandle result = handle.LastChildElement();
    EXPECT_EQ(result.ToElement(), nullptr);
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test LastChildElement with name filter on a null XMLHandle
TEST_F(XMLHandleLastChildElementTest_123, NullNode_WithNameFilter_ReturnsNullHandle_123) {
    XMLHandle handle((XMLNode*)nullptr);
    XMLHandle result = handle.LastChildElement("anything");
    EXPECT_EQ(result.ToElement(), nullptr);
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test LastChildElement on a nested structure
TEST_F(XMLHandleLastChildElementTest_123, NestedElements_ReturnsLastChildOfParent_123) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    root->InsertEndChild(doc->NewElement("child1"));
    root->InsertEndChild(doc->NewElement("child2"));
    root->InsertEndChild(doc->NewElement("child3"));

    XMLHandle handle(root);
    XMLHandle result = handle.LastChildElement();
    ASSERT_NE(result.ToElement(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "child3");
}

// Test chaining: LastChildElement followed by LastChildElement
TEST_F(XMLHandleLastChildElementTest_123, ChainingLastChildElement_123) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLElement* child = doc->NewElement("child");
    root->InsertEndChild(child);
    child->InsertEndChild(doc->NewElement("grandchild1"));
    child->InsertEndChild(doc->NewElement("grandchild2"));

    XMLHandle handle(doc);
    XMLHandle result = handle.LastChildElement("root").LastChildElement("child").LastChildElement();
    ASSERT_NE(result.ToElement(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "grandchild2");
}

// Test that result of LastChildElement on empty parent returns null
TEST_F(XMLHandleLastChildElementTest_123, ElementWithNoChildren_ReturnsNull_123) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLHandle handle(root);
    XMLHandle result = handle.LastChildElement();
    EXPECT_EQ(result.ToElement(), nullptr);
}

// Test LastChildElement with nullptr name (should behave like no filter)
TEST_F(XMLHandleLastChildElementTest_123, NullptrName_ReturnsLastElement_123) {
    doc->InsertEndChild(doc->NewElement("first"));
    doc->InsertEndChild(doc->NewElement("second"));
    XMLHandle handle(doc);
    XMLHandle result = handle.LastChildElement(nullptr);
    ASSERT_NE(result.ToElement(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "second");
}

// Test LastChildElement when result is used to further navigate
TEST_F(XMLHandleLastChildElementTest_123, ResultCanBeUsedForFurtherNavigation_123) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);

    XMLElement* a = doc->NewElement("section");
    root->InsertEndChild(a);
    a->InsertEndChild(doc->NewElement("item_a"));

    XMLElement* b = doc->NewElement("section");
    root->InsertEndChild(b);
    b->InsertEndChild(doc->NewElement("item_b"));

    XMLHandle handle(root);
    XMLHandle lastSection = handle.LastChildElement("section");
    ASSERT_NE(lastSection.ToElement(), nullptr);

    XMLHandle itemInLastSection = lastSection.FirstChildElement();
    ASSERT_NE(itemInLastSection.ToElement(), nullptr);
    EXPECT_STREQ(itemInLastSection.ToElement()->Name(), "item_b");
}

// Test using XMLHandle constructed from reference
TEST_F(XMLHandleLastChildElementTest_123, ConstructedFromReference_LastChildElement_123) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    root->InsertEndChild(doc->NewElement("child1"));
    root->InsertEndChild(doc->NewElement("child2"));

    XMLHandle handle(*root);
    XMLHandle result = handle.LastChildElement();
    ASSERT_NE(result.ToElement(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "child2");
}

// Test copy constructor preserves handle, and LastChildElement works on copy
TEST_F(XMLHandleLastChildElementTest_123, CopiedHandle_LastChildElement_123) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    root->InsertEndChild(doc->NewElement("child"));

    XMLHandle original(root);
    XMLHandle copy(original);
    XMLHandle result = copy.LastChildElement();
    ASSERT_NE(result.ToElement(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "child");
}

// Test assignment operator preserves handle, and LastChildElement works after assignment
TEST_F(XMLHandleLastChildElementTest_123, AssignedHandle_LastChildElement_123) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    root->InsertEndChild(doc->NewElement("elem"));

    XMLHandle original(root);
    XMLHandle assigned((XMLNode*)nullptr);
    assigned = original;
    XMLHandle result = assigned.LastChildElement();
    ASSERT_NE(result.ToElement(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "elem");
}

// Test with mixed node types (comment + elements), LastChildElement should skip non-elements
TEST_F(XMLHandleLastChildElementTest_123, MixedNodeTypes_SkipsNonElements_123) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    root->InsertEndChild(doc->NewElement("elem1"));
    root->InsertEndChild(doc->NewComment("a comment"));
    root->InsertEndChild(doc->NewElement("elem2"));
    root->InsertEndChild(doc->NewComment("another comment"));

    XMLHandle handle(root);
    XMLHandle result = handle.LastChildElement();
    ASSERT_NE(result.ToElement(), nullptr);
    EXPECT_STREQ(result.ToElement()->Name(), "elem2");
}
