#include "gtest/gtest.h"
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class XMLHandleNextSiblingElementTest_127 : public ::testing::Test {
protected:
    void SetUp() override {
        doc = new XMLDocument();
    }

    void TearDown() override {
        delete doc;
    }

    XMLDocument* doc;
};

// Test NextSiblingElement on a handle wrapping a null node
TEST_F(XMLHandleNextSiblingElementTest_127, NullNode_ReturnsNullHandle_127) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle result = handle.NextSiblingElement();
    EXPECT_EQ(nullptr, result.ToNode());
    EXPECT_EQ(nullptr, result.ToElement());
}

// Test NextSiblingElement with no name filter when there is a next sibling element
TEST_F(XMLHandleNextSiblingElementTest_127, HasNextSiblingElement_ReturnsIt_127) {
    doc->Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(nullptr, root);

    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(nullptr, a);

    XMLHandle handleA(a);
    XMLHandle result = handleA.NextSiblingElement();
    ASSERT_NE(nullptr, result.ToElement());
    EXPECT_STREQ("b", result.ToElement()->Name());
}

// Test NextSiblingElement with a specific name filter
TEST_F(XMLHandleNextSiblingElementTest_127, WithNameFilter_ReturnsMatchingElement_127) {
    doc->Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(nullptr, root);

    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(nullptr, a);

    XMLHandle handleA(a);
    XMLHandle result = handleA.NextSiblingElement("c");
    ASSERT_NE(nullptr, result.ToElement());
    EXPECT_STREQ("c", result.ToElement()->Name());
}

// Test NextSiblingElement with a name filter that doesn't match any sibling
TEST_F(XMLHandleNextSiblingElementTest_127, WithNameFilter_NoMatch_ReturnsNullHandle_127) {
    doc->Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(nullptr, root);

    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(nullptr, a);

    XMLHandle handleA(a);
    XMLHandle result = handleA.NextSiblingElement("z");
    EXPECT_EQ(nullptr, result.ToNode());
    EXPECT_EQ(nullptr, result.ToElement());
}

// Test NextSiblingElement when the current element is the last one
TEST_F(XMLHandleNextSiblingElementTest_127, LastElement_ReturnsNullHandle_127) {
    doc->Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(nullptr, root);

    XMLElement* c = root->FirstChildElement("c");
    ASSERT_NE(nullptr, c);

    XMLHandle handleC(c);
    XMLHandle result = handleC.NextSiblingElement();
    EXPECT_EQ(nullptr, result.ToNode());
    EXPECT_EQ(nullptr, result.ToElement());
}

// Test chaining NextSiblingElement calls
TEST_F(XMLHandleNextSiblingElementTest_127, ChainingCalls_127) {
    doc->Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(nullptr, root);

    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(nullptr, a);

    XMLHandle handleA(a);
    XMLHandle result = handleA.NextSiblingElement().NextSiblingElement();
    ASSERT_NE(nullptr, result.ToElement());
    EXPECT_STREQ("c", result.ToElement()->Name());
}

// Test chaining NextSiblingElement calls past the end returns null
TEST_F(XMLHandleNextSiblingElementTest_127, ChainingPastEnd_ReturnsNull_127) {
    doc->Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(nullptr, root);

    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(nullptr, a);

    XMLHandle handleA(a);
    XMLHandle result = handleA.NextSiblingElement().NextSiblingElement().NextSiblingElement();
    EXPECT_EQ(nullptr, result.ToNode());
    EXPECT_EQ(nullptr, result.ToElement());
}

// Test NextSiblingElement with a null name (should behave like no filter)
TEST_F(XMLHandleNextSiblingElementTest_127, NullNameFilter_BehavesLikeNoFilter_127) {
    doc->Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(nullptr, root);

    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(nullptr, a);

    XMLHandle handleA(a);
    XMLHandle result = handleA.NextSiblingElement(nullptr);
    ASSERT_NE(nullptr, result.ToElement());
    EXPECT_STREQ("b", result.ToElement()->Name());
}

// Test NextSiblingElement when there are duplicate named siblings
TEST_F(XMLHandleNextSiblingElementTest_127, DuplicateNamedSiblings_ReturnsFirst_127) {
    doc->Parse("<root><item id='1'/><other/><item id='2'/><item id='3'/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(nullptr, root);

    XMLElement* first = root->FirstChildElement("item");
    ASSERT_NE(nullptr, first);

    XMLHandle handle(first);
    XMLHandle result = handle.NextSiblingElement("item");
    ASSERT_NE(nullptr, result.ToElement());
    EXPECT_STREQ("2", result.ToElement()->Attribute("id"));
}

// Test NextSiblingElement on a single child element (no siblings)
TEST_F(XMLHandleNextSiblingElementTest_127, SingleChild_ReturnsNull_127) {
    doc->Parse("<root><only/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(nullptr, root);

    XMLElement* only = root->FirstChildElement("only");
    ASSERT_NE(nullptr, only);

    XMLHandle handle(only);
    XMLHandle result = handle.NextSiblingElement();
    EXPECT_EQ(nullptr, result.ToElement());
}

// Test NextSiblingElement called on a null handle returned from another operation
TEST_F(XMLHandleNextSiblingElementTest_127, NullHandleFromChain_ReturnsNull_127) {
    doc->Parse("<root><a/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(nullptr, root);

    // FirstChildElement("nonexistent") should return null handle
    XMLHandle handle(root);
    XMLHandle nullHandle = handle.FirstChildElement("nonexistent");
    EXPECT_EQ(nullptr, nullHandle.ToElement());

    XMLHandle result = nullHandle.NextSiblingElement();
    EXPECT_EQ(nullptr, result.ToElement());
}

// Test that NextSiblingElement result ToNode returns non-null for valid element
TEST_F(XMLHandleNextSiblingElementTest_127, ValidResult_ToNodeIsNonNull_127) {
    doc->Parse("<root><a/><b/></root>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(nullptr, root);

    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(nullptr, a);

    XMLHandle handle(a);
    XMLHandle result = handle.NextSiblingElement();
    EXPECT_NE(nullptr, result.ToNode());
    EXPECT_NE(nullptr, result.ToElement());
}
