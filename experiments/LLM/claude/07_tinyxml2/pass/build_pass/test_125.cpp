#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLHandlePreviousSiblingElementTest_125 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test PreviousSiblingElement on a null handle returns null handle
TEST_F(XMLHandlePreviousSiblingElementTest_125, NullHandle_ReturnsNull_125) {
    XMLHandle nullHandle(static_cast<XMLNode*>(nullptr));
    XMLHandle result = nullHandle.PreviousSiblingElement();
    EXPECT_EQ(nullptr, result.ToElement());
    EXPECT_EQ(nullptr, result.ToNode());
}

// Test PreviousSiblingElement with a name on a null handle returns null handle
TEST_F(XMLHandlePreviousSiblingElementTest_125, NullHandleWithName_ReturnsNull_125) {
    XMLHandle nullHandle(static_cast<XMLNode*>(nullptr));
    XMLHandle result = nullHandle.PreviousSiblingElement("foo");
    EXPECT_EQ(nullptr, result.ToElement());
    EXPECT_EQ(nullptr, result.ToNode());
}

// Test PreviousSiblingElement when there is no previous sibling element
TEST_F(XMLHandlePreviousSiblingElementTest_125, NoPreviousSibling_ReturnsNull_125) {
    doc.Parse("<root><first/><second/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    XMLElement* first = root->FirstChildElement("first");
    ASSERT_NE(nullptr, first);

    XMLHandle handle(first);
    XMLHandle result = handle.PreviousSiblingElement();
    EXPECT_EQ(nullptr, result.ToElement());
}

// Test PreviousSiblingElement when there is a previous sibling element
TEST_F(XMLHandlePreviousSiblingElementTest_125, HasPreviousSibling_ReturnsPreviousElement_125) {
    doc.Parse("<root><first/><second/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    XMLElement* second = root->FirstChildElement("second");
    ASSERT_NE(nullptr, second);

    XMLHandle handle(second);
    XMLHandle result = handle.PreviousSiblingElement();
    ASSERT_NE(nullptr, result.ToElement());
    EXPECT_STREQ("first", result.ToElement()->Name());
}

// Test PreviousSiblingElement with a specific name that matches
TEST_F(XMLHandlePreviousSiblingElementTest_125, WithMatchingName_ReturnsMatchingElement_125) {
    doc.Parse("<root><alpha/><beta/><gamma/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    XMLElement* gamma = root->FirstChildElement("gamma");
    ASSERT_NE(nullptr, gamma);

    XMLHandle handle(gamma);
    XMLHandle result = handle.PreviousSiblingElement("alpha");
    ASSERT_NE(nullptr, result.ToElement());
    EXPECT_STREQ("alpha", result.ToElement()->Name());
}

// Test PreviousSiblingElement with a specific name that does not match
TEST_F(XMLHandlePreviousSiblingElementTest_125, WithNonMatchingName_ReturnsNull_125) {
    doc.Parse("<root><alpha/><beta/><gamma/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    XMLElement* gamma = root->FirstChildElement("gamma");
    ASSERT_NE(nullptr, gamma);

    XMLHandle handle(gamma);
    XMLHandle result = handle.PreviousSiblingElement("nonexistent");
    EXPECT_EQ(nullptr, result.ToElement());
}

// Test PreviousSiblingElement with default (null) name parameter returns immediate previous element
TEST_F(XMLHandlePreviousSiblingElementTest_125, DefaultName_ReturnsImmediatePreviousElement_125) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    XMLElement* c = root->FirstChildElement("c");
    ASSERT_NE(nullptr, c);

    XMLHandle handle(c);
    XMLHandle result = handle.PreviousSiblingElement();
    ASSERT_NE(nullptr, result.ToElement());
    EXPECT_STREQ("b", result.ToElement()->Name());
}

// Test PreviousSiblingElement with name skipping non-matching siblings
TEST_F(XMLHandlePreviousSiblingElementTest_125, WithNameSkipsNonMatching_125) {
    doc.Parse("<root><target/><skip1/><skip2/><current/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    XMLElement* current = root->FirstChildElement("current");
    ASSERT_NE(nullptr, current);

    XMLHandle handle(current);
    XMLHandle result = handle.PreviousSiblingElement("target");
    ASSERT_NE(nullptr, result.ToElement());
    EXPECT_STREQ("target", result.ToElement()->Name());
}

// Test PreviousSiblingElement on root element (no parent siblings)
TEST_F(XMLHandlePreviousSiblingElementTest_125, RootElement_ReturnsNull_125) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);

    XMLHandle handle(root);
    XMLHandle result = handle.PreviousSiblingElement();
    EXPECT_EQ(nullptr, result.ToElement());
}

// Test chaining: PreviousSiblingElement returns a handle that can be further queried
TEST_F(XMLHandlePreviousSiblingElementTest_125, ChainingWithOtherHandleMethods_125) {
    doc.Parse("<root><prev><child/></prev><current/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    XMLElement* current = root->FirstChildElement("current");
    ASSERT_NE(nullptr, current);

    XMLHandle handle(current);
    XMLHandle prevHandle = handle.PreviousSiblingElement("prev");
    ASSERT_NE(nullptr, prevHandle.ToElement());

    XMLHandle childHandle = prevHandle.FirstChildElement("child");
    ASSERT_NE(nullptr, childHandle.ToElement());
    EXPECT_STREQ("child", childHandle.ToElement()->Name());
}

// Test PreviousSiblingElement when previous sibling is a text node, not an element
TEST_F(XMLHandlePreviousSiblingElementTest_125, PreviousSiblingIsText_SkipsToElement_125) {
    doc.Parse("<root><elem/>Some text<current/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    XMLElement* current = root->FirstChildElement("current");
    ASSERT_NE(nullptr, current);

    XMLHandle handle(current);
    XMLHandle result = handle.PreviousSiblingElement();
    ASSERT_NE(nullptr, result.ToElement());
    EXPECT_STREQ("elem", result.ToElement()->Name());
}

// Test PreviousSiblingElement with multiple same-named siblings returns the nearest one
TEST_F(XMLHandlePreviousSiblingElementTest_125, MultipleSameNamedSiblings_ReturnsNearest_125) {
    doc.Parse("<root><item/><item/><item id='last'/><current/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    XMLElement* current = root->FirstChildElement("current");
    ASSERT_NE(nullptr, current);

    XMLHandle handle(current);
    XMLHandle result = handle.PreviousSiblingElement("item");
    ASSERT_NE(nullptr, result.ToElement());
    // The nearest previous "item" should have the "id" attribute
    EXPECT_STREQ("last", result.ToElement()->Attribute("id"));
}

// Test that the result of PreviousSiblingElement on null handle can be chained safely
TEST_F(XMLHandlePreviousSiblingElementTest_125, NullHandleChaining_125) {
    XMLHandle nullHandle(static_cast<XMLNode*>(nullptr));
    XMLHandle result = nullHandle.PreviousSiblingElement().PreviousSiblingElement("test");
    EXPECT_EQ(nullptr, result.ToNode());
    EXPECT_EQ(nullptr, result.ToElement());
}

// Test PreviousSiblingElement with empty string name
TEST_F(XMLHandlePreviousSiblingElementTest_125, EmptyStringName_125) {
    doc.Parse("<root><a/><b/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    XMLElement* b = root->FirstChildElement("b");
    ASSERT_NE(nullptr, b);

    XMLHandle handle(b);
    // Empty string name - behavior depends on implementation, but should not crash
    XMLHandle result = handle.PreviousSiblingElement("");
    // An empty string likely won't match element names like "a"
    // Just verifying it doesn't crash; the result may be null
    (void)result.ToElement();
}
