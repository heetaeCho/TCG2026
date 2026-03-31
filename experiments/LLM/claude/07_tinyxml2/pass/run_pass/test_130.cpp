#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLHandleTest_130 : public ::testing::Test {
protected:
    void SetUp() override {
        doc = new XMLDocument();
    }

    void TearDown() override {
        delete doc;
    }

    XMLDocument* doc;
};

// Test XMLHandle constructed with a null node
TEST_F(XMLHandleTest_130, NullNodeHandle_ToText_ReturnsNull_130) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    EXPECT_EQ(nullptr, handle.ToText());
}

// Test XMLHandle constructed with a null node returns null for all conversions
TEST_F(XMLHandleTest_130, NullNodeHandle_ToNode_ReturnsNull_130) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    EXPECT_EQ(nullptr, handle.ToNode());
}

TEST_F(XMLHandleTest_130, NullNodeHandle_ToElement_ReturnsNull_130) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    EXPECT_EQ(nullptr, handle.ToElement());
}

TEST_F(XMLHandleTest_130, NullNodeHandle_ToUnknown_ReturnsNull_130) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    EXPECT_EQ(nullptr, handle.ToUnknown());
}

TEST_F(XMLHandleTest_130, NullNodeHandle_ToDeclaration_ReturnsNull_130) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    EXPECT_EQ(nullptr, handle.ToDeclaration());
}

// Test XMLHandle constructed with a valid text node
TEST_F(XMLHandleTest_130, ValidTextNode_ToText_ReturnsNonNull_130) {
    doc->Parse("<root>Hello</root>");
    XMLNode* textNode = doc->FirstChildElement("root")->FirstChild();
    ASSERT_NE(nullptr, textNode);
    ASSERT_NE(nullptr, textNode->ToText());

    XMLHandle handle(textNode);
    EXPECT_NE(nullptr, handle.ToText());
    EXPECT_EQ(textNode->ToText(), handle.ToText());
}

// Test XMLHandle constructed with an element node - ToText should return null
TEST_F(XMLHandleTest_130, ElementNode_ToText_ReturnsNull_130) {
    doc->Parse("<root><child/></root>");
    XMLElement* elem = doc->FirstChildElement("root");
    ASSERT_NE(nullptr, elem);

    XMLHandle handle(elem);
    EXPECT_EQ(nullptr, handle.ToText());
}

// Test XMLHandle ToNode with valid node
TEST_F(XMLHandleTest_130, ValidNode_ToNode_ReturnsNode_130) {
    doc->Parse("<root/>");
    XMLNode* node = doc->FirstChildElement("root");
    ASSERT_NE(nullptr, node);

    XMLHandle handle(node);
    EXPECT_EQ(node, handle.ToNode());
}

// Test XMLHandle ToElement with valid element
TEST_F(XMLHandleTest_130, ValidElement_ToElement_ReturnsElement_130) {
    doc->Parse("<root/>");
    XMLElement* elem = doc->FirstChildElement("root");
    ASSERT_NE(nullptr, elem);

    XMLHandle handle(elem);
    EXPECT_EQ(elem, handle.ToElement());
}

// Test XMLHandle constructed with reference
TEST_F(XMLHandleTest_130, ConstructFromReference_ToNode_130) {
    doc->Parse("<root/>");
    XMLNode* node = doc->FirstChildElement("root");
    ASSERT_NE(nullptr, node);

    XMLHandle handle(*node);
    EXPECT_EQ(node, handle.ToNode());
}

// Test copy constructor
TEST_F(XMLHandleTest_130, CopyConstructor_130) {
    doc->Parse("<root/>");
    XMLNode* node = doc->FirstChildElement("root");
    ASSERT_NE(nullptr, node);

    XMLHandle handle1(node);
    XMLHandle handle2(handle1);
    EXPECT_EQ(handle1.ToNode(), handle2.ToNode());
}

// Test assignment operator
TEST_F(XMLHandleTest_130, AssignmentOperator_130) {
    doc->Parse("<root><child/></root>");
    XMLNode* root = doc->FirstChildElement("root");
    XMLNode* child = root->FirstChildElement("child");
    ASSERT_NE(nullptr, root);
    ASSERT_NE(nullptr, child);

    XMLHandle handle1(root);
    XMLHandle handle2(child);
    handle2 = handle1;
    EXPECT_EQ(root, handle2.ToNode());
}

// Test FirstChild
TEST_F(XMLHandleTest_130, FirstChild_ValidNode_130) {
    doc->Parse("<root><child1/><child2/></root>");
    XMLHandle handle(doc->FirstChildElement("root"));
    XMLHandle firstChild = handle.FirstChild();
    EXPECT_NE(nullptr, firstChild.ToNode());
    EXPECT_STREQ("child1", firstChild.ToElement()->Name());
}

// Test FirstChild on null handle
TEST_F(XMLHandleTest_130, FirstChild_NullHandle_ReturnsNullHandle_130) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle firstChild = handle.FirstChild();
    EXPECT_EQ(nullptr, firstChild.ToNode());
}

// Test FirstChildElement
TEST_F(XMLHandleTest_130, FirstChildElement_ByName_130) {
    doc->Parse("<root><a/><b/><c/></root>");
    XMLHandle handle(doc->FirstChildElement("root"));
    XMLHandle child = handle.FirstChildElement("b");
    ASSERT_NE(nullptr, child.ToElement());
    EXPECT_STREQ("b", child.ToElement()->Name());
}

// Test FirstChildElement with no name (default)
TEST_F(XMLHandleTest_130, FirstChildElement_NoName_130) {
    doc->Parse("<root><a/><b/></root>");
    XMLHandle handle(doc->FirstChildElement("root"));
    XMLHandle child = handle.FirstChildElement();
    ASSERT_NE(nullptr, child.ToElement());
    EXPECT_STREQ("a", child.ToElement()->Name());
}

// Test FirstChildElement on null handle
TEST_F(XMLHandleTest_130, FirstChildElement_NullHandle_130) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle child = handle.FirstChildElement("anything");
    EXPECT_EQ(nullptr, child.ToElement());
}

// Test LastChild
TEST_F(XMLHandleTest_130, LastChild_ValidNode_130) {
    doc->Parse("<root><child1/><child2/></root>");
    XMLHandle handle(doc->FirstChildElement("root"));
    XMLHandle lastChild = handle.LastChild();
    ASSERT_NE(nullptr, lastChild.ToNode());
    EXPECT_STREQ("child2", lastChild.ToElement()->Name());
}

// Test LastChild on null handle
TEST_F(XMLHandleTest_130, LastChild_NullHandle_130) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle lastChild = handle.LastChild();
    EXPECT_EQ(nullptr, lastChild.ToNode());
}

// Test LastChildElement
TEST_F(XMLHandleTest_130, LastChildElement_ByName_130) {
    doc->Parse("<root><a/><b/><a id='2'/></root>");
    XMLHandle handle(doc->FirstChildElement("root"));
    XMLHandle child = handle.LastChildElement("a");
    ASSERT_NE(nullptr, child.ToElement());
    EXPECT_STREQ("a", child.ToElement()->Name());
    EXPECT_STREQ("2", child.ToElement()->Attribute("id"));
}

// Test LastChildElement on null handle
TEST_F(XMLHandleTest_130, LastChildElement_NullHandle_130) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle child = handle.LastChildElement();
    EXPECT_EQ(nullptr, child.ToElement());
}

// Test PreviousSibling
TEST_F(XMLHandleTest_130, PreviousSibling_ValidNode_130) {
    doc->Parse("<root><a/><b/><c/></root>");
    XMLElement* b = doc->FirstChildElement("root")->FirstChildElement("b");
    ASSERT_NE(nullptr, b);

    XMLHandle handle(b);
    XMLHandle prev = handle.PreviousSibling();
    ASSERT_NE(nullptr, prev.ToNode());
    EXPECT_STREQ("a", prev.ToElement()->Name());
}

// Test PreviousSibling on null handle
TEST_F(XMLHandleTest_130, PreviousSibling_NullHandle_130) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle prev = handle.PreviousSibling();
    EXPECT_EQ(nullptr, prev.ToNode());
}

// Test PreviousSiblingElement
TEST_F(XMLHandleTest_130, PreviousSiblingElement_ByName_130) {
    doc->Parse("<root><x/><a/><b/><c/></root>");
    XMLElement* c = doc->FirstChildElement("root")->LastChildElement("c");
    ASSERT_NE(nullptr, c);

    XMLHandle handle(c);
    XMLHandle prev = handle.PreviousSiblingElement("a");
    ASSERT_NE(nullptr, prev.ToElement());
    EXPECT_STREQ("a", prev.ToElement()->Name());
}

// Test PreviousSiblingElement on null handle
TEST_F(XMLHandleTest_130, PreviousSiblingElement_NullHandle_130) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle prev = handle.PreviousSiblingElement();
    EXPECT_EQ(nullptr, prev.ToElement());
}

// Test NextSibling
TEST_F(XMLHandleTest_130, NextSibling_ValidNode_130) {
    doc->Parse("<root><a/><b/><c/></root>");
    XMLElement* a = doc->FirstChildElement("root")->FirstChildElement("a");
    ASSERT_NE(nullptr, a);

    XMLHandle handle(a);
    XMLHandle next = handle.NextSibling();
    ASSERT_NE(nullptr, next.ToNode());
    EXPECT_STREQ("b", next.ToElement()->Name());
}

// Test NextSibling on null handle
TEST_F(XMLHandleTest_130, NextSibling_NullHandle_130) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle next = handle.NextSibling();
    EXPECT_EQ(nullptr, next.ToNode());
}

// Test NextSiblingElement
TEST_F(XMLHandleTest_130, NextSiblingElement_ByName_130) {
    doc->Parse("<root><a/><b/><c/></root>");
    XMLElement* a = doc->FirstChildElement("root")->FirstChildElement("a");
    ASSERT_NE(nullptr, a);

    XMLHandle handle(a);
    XMLHandle next = handle.NextSiblingElement("c");
    ASSERT_NE(nullptr, next.ToElement());
    EXPECT_STREQ("c", next.ToElement()->Name());
}

// Test NextSiblingElement on null handle
TEST_F(XMLHandleTest_130, NextSiblingElement_NullHandle_130) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle next = handle.NextSiblingElement();
    EXPECT_EQ(nullptr, next.ToElement());
}

// Test chaining: navigate deep into a tree
TEST_F(XMLHandleTest_130, Chaining_DeepNavigation_130) {
    doc->Parse("<root><a><b><c>text</c></b></a></root>");
    XMLHandle handle(doc);
    XMLHandle result = handle.FirstChildElement("root")
                             .FirstChildElement("a")
                             .FirstChildElement("b")
                             .FirstChildElement("c")
                             .FirstChild();
    ASSERT_NE(nullptr, result.ToText());
    EXPECT_STREQ("text", result.ToText()->Value());
}

// Test chaining that falls off at some point returns null
TEST_F(XMLHandleTest_130, Chaining_FallsOff_ReturnsNull_130) {
    doc->Parse("<root><a/></root>");
    XMLHandle handle(doc);
    XMLHandle result = handle.FirstChildElement("root")
                             .FirstChildElement("nonexistent")
                             .FirstChild();
    EXPECT_EQ(nullptr, result.ToNode());
}

// Test ToText on a non-text child
TEST_F(XMLHandleTest_130, ToText_OnComment_ReturnsNull_130) {
    doc->Parse("<root><!-- comment --></root>");
    XMLNode* comment = doc->FirstChildElement("root")->FirstChild();
    ASSERT_NE(nullptr, comment);
    ASSERT_NE(nullptr, comment->ToComment());

    XMLHandle handle(comment);
    EXPECT_EQ(nullptr, handle.ToText());
}

// Test ToDeclaration on a declaration node
TEST_F(XMLHandleTest_130, ToDeclaration_ValidDeclaration_130) {
    doc->Parse("<?xml version='1.0'?><root/>");
    XMLNode* firstChild = doc->FirstChild();
    ASSERT_NE(nullptr, firstChild);

    XMLHandle handle(firstChild);
    if (firstChild->ToDeclaration()) {
        EXPECT_NE(nullptr, handle.ToDeclaration());
    }
}

// Test ToUnknown
TEST_F(XMLHandleTest_130, ToUnknown_OnElement_ReturnsNull_130) {
    doc->Parse("<root/>");
    XMLHandle handle(doc->FirstChildElement("root"));
    EXPECT_EQ(nullptr, handle.ToUnknown());
}

// Test FirstChild on empty element
TEST_F(XMLHandleTest_130, FirstChild_EmptyElement_ReturnsNull_130) {
    doc->Parse("<root/>");
    XMLHandle handle(doc->FirstChildElement("root"));
    XMLHandle child = handle.FirstChild();
    EXPECT_EQ(nullptr, child.ToNode());
}

// Test LastChild on empty element
TEST_F(XMLHandleTest_130, LastChild_EmptyElement_ReturnsNull_130) {
    doc->Parse("<root/>");
    XMLHandle handle(doc->FirstChildElement("root"));
    XMLHandle child = handle.LastChild();
    EXPECT_EQ(nullptr, child.ToNode());
}

// Test FirstChildElement with non-matching name
TEST_F(XMLHandleTest_130, FirstChildElement_NonMatchingName_ReturnsNull_130) {
    doc->Parse("<root><a/><b/></root>");
    XMLHandle handle(doc->FirstChildElement("root"));
    XMLHandle child = handle.FirstChildElement("z");
    EXPECT_EQ(nullptr, child.ToElement());
}

// Test XMLHandle with document node
TEST_F(XMLHandleTest_130, HandleWithDocument_ToNode_130) {
    doc->Parse("<root/>");
    XMLHandle handle(doc);
    EXPECT_EQ(static_cast<XMLNode*>(doc), handle.ToNode());
}

// Test PreviousSibling when there is no previous sibling
TEST_F(XMLHandleTest_130, PreviousSibling_FirstChild_ReturnsNull_130) {
    doc->Parse("<root><a/><b/></root>");
    XMLElement* a = doc->FirstChildElement("root")->FirstChildElement("a");
    ASSERT_NE(nullptr, a);

    XMLHandle handle(a);
    XMLHandle prev = handle.PreviousSibling();
    EXPECT_EQ(nullptr, prev.ToNode());
}

// Test NextSibling when there is no next sibling
TEST_F(XMLHandleTest_130, NextSibling_LastChild_ReturnsNull_130) {
    doc->Parse("<root><a/><b/></root>");
    XMLElement* b = doc->FirstChildElement("root")->LastChildElement("b");
    ASSERT_NE(nullptr, b);

    XMLHandle handle(b);
    XMLHandle next = handle.NextSibling();
    EXPECT_EQ(nullptr, next.ToNode());
}

// Test that ToText returns correct text value
TEST_F(XMLHandleTest_130, ToText_CorrectValue_130) {
    doc->Parse("<root>Sample Text</root>");
    XMLHandle handle(doc);
    XMLText* text = handle.FirstChildElement("root").FirstChild().ToText();
    ASSERT_NE(nullptr, text);
    EXPECT_STREQ("Sample Text", text->Value());
}

// Test multiple children - FirstChildElement vs LastChildElement
TEST_F(XMLHandleTest_130, FirstAndLastChildElement_MultipleChildren_130) {
    doc->Parse("<root><item id='1'/><item id='2'/><item id='3'/></root>");
    XMLHandle handle(doc->FirstChildElement("root"));

    XMLHandle first = handle.FirstChildElement("item");
    XMLHandle last = handle.LastChildElement("item");

    ASSERT_NE(nullptr, first.ToElement());
    ASSERT_NE(nullptr, last.ToElement());
    EXPECT_STREQ("1", first.ToElement()->Attribute("id"));
    EXPECT_STREQ("3", last.ToElement()->Attribute("id"));
}
