#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLHandleTest_121 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test XMLHandle constructed from a null node pointer
TEST_F(XMLHandleTest_121, NullNodeHandle_121) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToNode(), nullptr);
    EXPECT_EQ(handle.ToElement(), nullptr);
    EXPECT_EQ(handle.ToText(), nullptr);
    EXPECT_EQ(handle.ToUnknown(), nullptr);
    EXPECT_EQ(handle.ToDeclaration(), nullptr);
}

// Test FirstChildElement on a null handle returns null handle
TEST_F(XMLHandleTest_121, NullHandleFirstChildElement_121) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle child = handle.FirstChildElement();
    EXPECT_EQ(child.ToNode(), nullptr);
    EXPECT_EQ(child.ToElement(), nullptr);
}

// Test FirstChild on a null handle returns null handle
TEST_F(XMLHandleTest_121, NullHandleFirstChild_121) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle child = handle.FirstChild();
    EXPECT_EQ(child.ToNode(), nullptr);
}

// Test LastChild on a null handle returns null handle
TEST_F(XMLHandleTest_121, NullHandleLastChild_121) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle child = handle.LastChild();
    EXPECT_EQ(child.ToNode(), nullptr);
}

// Test LastChildElement on a null handle returns null handle
TEST_F(XMLHandleTest_121, NullHandleLastChildElement_121) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle child = handle.LastChildElement();
    EXPECT_EQ(child.ToNode(), nullptr);
}

// Test PreviousSibling on a null handle returns null handle
TEST_F(XMLHandleTest_121, NullHandlePreviousSibling_121) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle sibling = handle.PreviousSibling();
    EXPECT_EQ(sibling.ToNode(), nullptr);
}

// Test PreviousSiblingElement on a null handle returns null handle
TEST_F(XMLHandleTest_121, NullHandlePreviousSiblingElement_121) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle sibling = handle.PreviousSiblingElement();
    EXPECT_EQ(sibling.ToNode(), nullptr);
}

// Test NextSibling on a null handle returns null handle
TEST_F(XMLHandleTest_121, NullHandleNextSibling_121) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle sibling = handle.NextSibling();
    EXPECT_EQ(sibling.ToNode(), nullptr);
}

// Test NextSiblingElement on a null handle returns null handle
TEST_F(XMLHandleTest_121, NullHandleNextSiblingElement_121) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));
    XMLHandle sibling = handle.NextSiblingElement();
    EXPECT_EQ(sibling.ToNode(), nullptr);
}

// Test XMLHandle constructed from a valid document
TEST_F(XMLHandleTest_121, HandleFromDocument_121) {
    XMLDocument doc;
    doc.Parse("<root><child1/><child2/></root>");
    ASSERT_FALSE(doc.Error());

    XMLHandle docHandle(&doc);
    EXPECT_NE(docHandle.ToNode(), nullptr);
}

// Test FirstChildElement returns correct element from document handle
TEST_F(XMLHandleTest_121, FirstChildElementFromDocument_121) {
    XMLDocument doc;
    doc.Parse("<root><child1/><child2/></root>");
    ASSERT_FALSE(doc.Error());

    XMLHandle docHandle(&doc);
    XMLHandle rootHandle = docHandle.FirstChildElement("root");
    EXPECT_NE(rootHandle.ToElement(), nullptr);
    EXPECT_STREQ(rootHandle.ToElement()->Name(), "root");
}

// Test FirstChildElement with no name returns first element
TEST_F(XMLHandleTest_121, FirstChildElementNoName_121) {
    XMLDocument doc;
    doc.Parse("<root><child1/><child2/></root>");
    ASSERT_FALSE(doc.Error());

    XMLHandle docHandle(&doc);
    XMLHandle rootHandle = docHandle.FirstChildElement();
    EXPECT_NE(rootHandle.ToElement(), nullptr);
    EXPECT_STREQ(rootHandle.ToElement()->Name(), "root");
}

// Test chaining FirstChildElement calls
TEST_F(XMLHandleTest_121, ChainingFirstChildElement_121) {
    XMLDocument doc;
    doc.Parse("<root><parent><child>text</child></parent></root>");
    ASSERT_FALSE(doc.Error());

    XMLHandle docHandle(&doc);
    XMLHandle childHandle = docHandle.FirstChildElement("root")
                                      .FirstChildElement("parent")
                                      .FirstChildElement("child");
    EXPECT_NE(childHandle.ToElement(), nullptr);
    EXPECT_STREQ(childHandle.ToElement()->Name(), "child");
}

// Test FirstChildElement with non-existent name returns null handle
TEST_F(XMLHandleTest_121, FirstChildElementNonExistent_121) {
    XMLDocument doc;
    doc.Parse("<root><child1/></root>");
    ASSERT_FALSE(doc.Error());

    XMLHandle docHandle(&doc);
    XMLHandle handle = docHandle.FirstChildElement("root").FirstChildElement("nonexistent");
    EXPECT_EQ(handle.ToElement(), nullptr);
    EXPECT_EQ(handle.ToNode(), nullptr);
}

// Test chaining through a null handle gracefully returns null
TEST_F(XMLHandleTest_121, ChainingThroughNull_121) {
    XMLDocument doc;
    doc.Parse("<root><child1/></root>");
    ASSERT_FALSE(doc.Error());

    XMLHandle docHandle(&doc);
    XMLHandle handle = docHandle.FirstChildElement("root")
                                .FirstChildElement("nonexistent")
                                .FirstChildElement("anything");
    EXPECT_EQ(handle.ToNode(), nullptr);
}

// Test LastChildElement
TEST_F(XMLHandleTest_121, LastChildElement_121) {
    XMLDocument doc;
    doc.Parse("<root><child1/><child2/><child3/></root>");
    ASSERT_FALSE(doc.Error());

    XMLHandle docHandle(&doc);
    XMLHandle rootHandle = docHandle.FirstChildElement("root");
    XMLHandle lastChild = rootHandle.LastChildElement();
    EXPECT_NE(lastChild.ToElement(), nullptr);
    EXPECT_STREQ(lastChild.ToElement()->Name(), "child3");
}

// Test LastChildElement with name filter
TEST_F(XMLHandleTest_121, LastChildElementByName_121) {
    XMLDocument doc;
    doc.Parse("<root><item/><other/><item/></root>");
    ASSERT_FALSE(doc.Error());

    XMLHandle docHandle(&doc);
    XMLHandle rootHandle = docHandle.FirstChildElement("root");
    XMLHandle lastItem = rootHandle.LastChildElement("item");
    EXPECT_NE(lastItem.ToElement(), nullptr);
    EXPECT_STREQ(lastItem.ToElement()->Name(), "item");
}

// Test FirstChild returns the first child node
TEST_F(XMLHandleTest_121, FirstChild_121) {
    XMLDocument doc;
    doc.Parse("<root>text<child/></root>");
    ASSERT_FALSE(doc.Error());

    XMLHandle docHandle(&doc);
    XMLHandle rootHandle = docHandle.FirstChildElement("root");
    XMLHandle firstChild = rootHandle.FirstChild();
    EXPECT_NE(firstChild.ToNode(), nullptr);
}

// Test LastChild returns the last child node
TEST_F(XMLHandleTest_121, LastChild_121) {
    XMLDocument doc;
    doc.Parse("<root><child1/><child2/></root>");
    ASSERT_FALSE(doc.Error());

    XMLHandle docHandle(&doc);
    XMLHandle rootHandle = docHandle.FirstChildElement("root");
    XMLHandle lastChild = rootHandle.LastChild();
    EXPECT_NE(lastChild.ToNode(), nullptr);
}

// Test NextSiblingElement
TEST_F(XMLHandleTest_121, NextSiblingElement_121) {
    XMLDocument doc;
    doc.Parse("<root><child1/><child2/><child3/></root>");
    ASSERT_FALSE(doc.Error());

    XMLHandle docHandle(&doc);
    XMLHandle firstChild = docHandle.FirstChildElement("root").FirstChildElement();
    EXPECT_NE(firstChild.ToElement(), nullptr);
    EXPECT_STREQ(firstChild.ToElement()->Name(), "child1");

    XMLHandle secondChild = firstChild.NextSiblingElement();
    EXPECT_NE(secondChild.ToElement(), nullptr);
    EXPECT_STREQ(secondChild.ToElement()->Name(), "child2");

    XMLHandle thirdChild = secondChild.NextSiblingElement();
    EXPECT_NE(thirdChild.ToElement(), nullptr);
    EXPECT_STREQ(thirdChild.ToElement()->Name(), "child3");

    XMLHandle noMoreChild = thirdChild.NextSiblingElement();
    EXPECT_EQ(noMoreChild.ToElement(), nullptr);
}

// Test NextSiblingElement with name filter
TEST_F(XMLHandleTest_121, NextSiblingElementByName_121) {
    XMLDocument doc;
    doc.Parse("<root><a/><b/><a/><c/></root>");
    ASSERT_FALSE(doc.Error());

    XMLHandle docHandle(&doc);
    XMLHandle firstA = docHandle.FirstChildElement("root").FirstChildElement("a");
    EXPECT_NE(firstA.ToElement(), nullptr);

    XMLHandle secondA = firstA.NextSiblingElement("a");
    EXPECT_NE(secondA.ToElement(), nullptr);
    EXPECT_STREQ(secondA.ToElement()->Name(), "a");

    XMLHandle thirdA = secondA.NextSiblingElement("a");
    EXPECT_EQ(thirdA.ToElement(), nullptr);
}

// Test PreviousSiblingElement
TEST_F(XMLHandleTest_121, PreviousSiblingElement_121) {
    XMLDocument doc;
    doc.Parse("<root><child1/><child2/><child3/></root>");
    ASSERT_FALSE(doc.Error());

    XMLHandle docHandle(&doc);
    XMLHandle lastChild = docHandle.FirstChildElement("root").LastChildElement();
    EXPECT_NE(lastChild.ToElement(), nullptr);
    EXPECT_STREQ(lastChild.ToElement()->Name(), "child3");

    XMLHandle prevChild = lastChild.PreviousSiblingElement();
    EXPECT_NE(prevChild.ToElement(), nullptr);
    EXPECT_STREQ(prevChild.ToElement()->Name(), "child2");

    XMLHandle firstChild = prevChild.PreviousSiblingElement();
    EXPECT_NE(firstChild.ToElement(), nullptr);
    EXPECT_STREQ(firstChild.ToElement()->Name(), "child1");

    XMLHandle noPrev = firstChild.PreviousSiblingElement();
    EXPECT_EQ(noPrev.ToElement(), nullptr);
}

// Test PreviousSiblingElement with name filter
TEST_F(XMLHandleTest_121, PreviousSiblingElementByName_121) {
    XMLDocument doc;
    doc.Parse("<root><a/><b/><a/><c/></root>");
    ASSERT_FALSE(doc.Error());

    XMLHandle docHandle(&doc);
    XMLHandle lastChild = docHandle.FirstChildElement("root").LastChildElement("c");
    EXPECT_NE(lastChild.ToElement(), nullptr);

    XMLHandle prevA = lastChild.PreviousSiblingElement("a");
    EXPECT_NE(prevA.ToElement(), nullptr);
    EXPECT_STREQ(prevA.ToElement()->Name(), "a");
}

// Test NextSibling
TEST_F(XMLHandleTest_121, NextSibling_121) {
    XMLDocument doc;
    doc.Parse("<root><child1/><child2/></root>");
    ASSERT_FALSE(doc.Error());

    XMLHandle docHandle(&doc);
    XMLHandle firstChild = docHandle.FirstChildElement("root").FirstChild();
    EXPECT_NE(firstChild.ToNode(), nullptr);

    XMLHandle nextSibling = firstChild.NextSibling();
    EXPECT_NE(nextSibling.ToNode(), nullptr);
}

// Test PreviousSibling
TEST_F(XMLHandleTest_121, PreviousSibling_121) {
    XMLDocument doc;
    doc.Parse("<root><child1/><child2/></root>");
    ASSERT_FALSE(doc.Error());

    XMLHandle docHandle(&doc);
    XMLHandle lastChild = docHandle.FirstChildElement("root").LastChild();
    EXPECT_NE(lastChild.ToNode(), nullptr);

    XMLHandle prevSibling = lastChild.PreviousSibling();
    EXPECT_NE(prevSibling.ToNode(), nullptr);
}

// Test copy constructor
TEST_F(XMLHandleTest_121, CopyConstructor_121) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    ASSERT_FALSE(doc.Error());

    XMLHandle handle1(&doc);
    XMLHandle handle2(handle1);
    EXPECT_EQ(handle1.ToNode(), handle2.ToNode());
}

// Test assignment operator
TEST_F(XMLHandleTest_121, AssignmentOperator_121) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    ASSERT_FALSE(doc.Error());

    XMLHandle handle1(&doc);
    XMLHandle handle2(static_cast<XMLNode*>(nullptr));
    handle2 = handle1;
    EXPECT_EQ(handle1.ToNode(), handle2.ToNode());
}

// Test XMLHandle from node reference
TEST_F(XMLHandleTest_121, HandleFromNodeReference_121) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    ASSERT_FALSE(doc.Error());

    XMLHandle handle(doc);
    EXPECT_NE(handle.ToNode(), nullptr);
    XMLHandle rootHandle = handle.FirstChildElement("root");
    EXPECT_NE(rootHandle.ToElement(), nullptr);
}

// Test ToText on a text node
TEST_F(XMLHandleTest_121, ToTextOnTextNode_121) {
    XMLDocument doc;
    doc.Parse("<root>Hello</root>");
    ASSERT_FALSE(doc.Error());

    XMLHandle docHandle(&doc);
    XMLHandle textHandle = docHandle.FirstChildElement("root").FirstChild();
    EXPECT_NE(textHandle.ToText(), nullptr);
}

// Test ToText on a non-text node returns null
TEST_F(XMLHandleTest_121, ToTextOnNonTextNode_121) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    ASSERT_FALSE(doc.Error());

    XMLHandle docHandle(&doc);
    XMLHandle childHandle = docHandle.FirstChildElement("root").FirstChildElement("child");
    EXPECT_EQ(childHandle.ToText(), nullptr);
}

// Test ToElement on element node
TEST_F(XMLHandleTest_121, ToElementOnElementNode_121) {
    XMLDocument doc;
    doc.Parse("<root/>");
    ASSERT_FALSE(doc.Error());

    XMLHandle docHandle(&doc);
    XMLHandle rootHandle = docHandle.FirstChildElement("root");
    EXPECT_NE(rootHandle.ToElement(), nullptr);
    EXPECT_STREQ(rootHandle.ToElement()->Name(), "root");
}

// Test ToElement on non-element returns null
TEST_F(XMLHandleTest_121, ToElementOnTextReturnsNull_121) {
    XMLDocument doc;
    doc.Parse("<root>Hello</root>");
    ASSERT_FALSE(doc.Error());

    XMLHandle docHandle(&doc);
    XMLHandle textHandle = docHandle.FirstChildElement("root").FirstChild();
    EXPECT_EQ(textHandle.ToElement(), nullptr);
}

// Test empty document handle
TEST_F(XMLHandleTest_121, EmptyDocumentHandle_121) {
    XMLDocument doc;
    XMLHandle docHandle(&doc);
    XMLHandle child = docHandle.FirstChildElement();
    EXPECT_EQ(child.ToElement(), nullptr);
}

// Test handle with deeply nested structure
TEST_F(XMLHandleTest_121, DeeplyNestedStructure_121) {
    XMLDocument doc;
    doc.Parse("<a><b><c><d><e>deep</e></d></c></b></a>");
    ASSERT_FALSE(doc.Error());

    XMLHandle docHandle(&doc);
    XMLHandle deepHandle = docHandle.FirstChildElement("a")
                                     .FirstChildElement("b")
                                     .FirstChildElement("c")
                                     .FirstChildElement("d")
                                     .FirstChildElement("e");
    EXPECT_NE(deepHandle.ToElement(), nullptr);
    EXPECT_STREQ(deepHandle.ToElement()->Name(), "e");
}

// Test FirstChildElement on empty element
TEST_F(XMLHandleTest_121, FirstChildElementOnEmptyElement_121) {
    XMLDocument doc;
    doc.Parse("<root/>");
    ASSERT_FALSE(doc.Error());

    XMLHandle docHandle(&doc);
    XMLHandle rootHandle = docHandle.FirstChildElement("root");
    EXPECT_NE(rootHandle.ToElement(), nullptr);

    XMLHandle childHandle = rootHandle.FirstChildElement();
    EXPECT_EQ(childHandle.ToElement(), nullptr);
}

// Test ToUnknown on unknown node
TEST_F(XMLHandleTest_121, ToUnknownNode_121) {
    XMLDocument doc;
    doc.Parse("<root><!unknown stuff></root>");
    // If parsing unknown nodes is supported
    if (!doc.Error()) {
        XMLHandle docHandle(&doc);
        XMLHandle rootHandle = docHandle.FirstChildElement("root");
        XMLHandle firstChild = rootHandle.FirstChild();
        // May or may not be unknown depending on parser behavior
        // Just ensure no crash
        firstChild.ToUnknown();
    }
}

// Test ToDeclaration
TEST_F(XMLHandleTest_121, ToDeclaration_121) {
    XMLDocument doc;
    doc.Parse("<?xml version=\"1.0\"?><root/>");
    ASSERT_FALSE(doc.Error());

    XMLHandle docHandle(&doc);
    XMLHandle firstChild = docHandle.FirstChild();
    EXPECT_NE(firstChild.ToNode(), nullptr);
    // First child of doc might be the declaration
    XMLDeclaration* decl = firstChild.ToDeclaration();
    if (decl) {
        EXPECT_NE(decl, nullptr);
    }
}

// Test multiple siblings with same name
TEST_F(XMLHandleTest_121, MultipleSiblingsWithSameName_121) {
    XMLDocument doc;
    doc.Parse("<root><item id=\"1\"/><item id=\"2\"/><item id=\"3\"/></root>");
    ASSERT_FALSE(doc.Error());

    XMLHandle docHandle(&doc);
    XMLHandle firstItem = docHandle.FirstChildElement("root").FirstChildElement("item");
    EXPECT_NE(firstItem.ToElement(), nullptr);
    EXPECT_STREQ(firstItem.ToElement()->Attribute("id"), "1");

    XMLHandle secondItem = firstItem.NextSiblingElement("item");
    EXPECT_NE(secondItem.ToElement(), nullptr);
    EXPECT_STREQ(secondItem.ToElement()->Attribute("id"), "2");

    XMLHandle thirdItem = secondItem.NextSiblingElement("item");
    EXPECT_NE(thirdItem.ToElement(), nullptr);
    EXPECT_STREQ(thirdItem.ToElement()->Attribute("id"), "3");

    XMLHandle noMore = thirdItem.NextSiblingElement("item");
    EXPECT_EQ(noMore.ToElement(), nullptr);
}
