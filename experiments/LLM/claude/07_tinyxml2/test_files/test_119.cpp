#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLHandleTest_119 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
        const char* xml =
            "<?xml version=\"1.0\"?>"
            "<root>"
            "  <child1 name=\"first\">"
            "    <grandchild1/>"
            "    <grandchild2/>"
            "  </child1>"
            "  <child2 name=\"second\">Some text</child2>"
            "  <child3 name=\"third\"/>"
            "  <!-- a comment -->"
            "  <child2 name=\"duplicate\"/>"
            "</root>";
        doc.Parse(xml);
    }
};

// Test constructing XMLHandle from a null XMLNode pointer
TEST_F(XMLHandleTest_119, ConstructFromNullPointer_119) {
    XMLHandle handle((XMLNode*)nullptr);
    EXPECT_EQ(handle.ToNode(), nullptr);
    EXPECT_EQ(handle.ToElement(), nullptr);
}

// Test constructing XMLHandle from a valid XMLNode pointer
TEST_F(XMLHandleTest_119, ConstructFromValidPointer_119) {
    XMLNode* root = doc.RootElement();
    XMLHandle handle(root);
    EXPECT_EQ(handle.ToNode(), root);
    EXPECT_EQ(handle.ToElement(), root->ToElement());
}

// Test constructing XMLHandle from a XMLNode reference
TEST_F(XMLHandleTest_119, ConstructFromReference_119) {
    XMLNode* root = doc.RootElement();
    XMLHandle handle(*root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test copy constructor
TEST_F(XMLHandleTest_119, CopyConstructor_119) {
    XMLNode* root = doc.RootElement();
    XMLHandle handle1(root);
    XMLHandle handle2(handle1);
    EXPECT_EQ(handle2.ToNode(), root);
}

// Test assignment operator
TEST_F(XMLHandleTest_119, AssignmentOperator_119) {
    XMLNode* root = doc.RootElement();
    XMLHandle handle1(root);
    XMLHandle handle2((XMLNode*)nullptr);
    EXPECT_EQ(handle2.ToNode(), nullptr);
    handle2 = handle1;
    EXPECT_EQ(handle2.ToNode(), root);
}

// Test self-assignment
TEST_F(XMLHandleTest_119, SelfAssignment_119) {
    XMLNode* root = doc.RootElement();
    XMLHandle handle(root);
    handle = handle;
    EXPECT_EQ(handle.ToNode(), root);
}

// Test FirstChild on a valid node with children
TEST_F(XMLHandleTest_119, FirstChildValid_119) {
    XMLHandle handle(doc.RootElement());
    XMLHandle firstChild = handle.FirstChild();
    EXPECT_NE(firstChild.ToNode(), nullptr);
}

// Test FirstChild on a null handle
TEST_F(XMLHandleTest_119, FirstChildNull_119) {
    XMLHandle handle((XMLNode*)nullptr);
    XMLHandle firstChild = handle.FirstChild();
    EXPECT_EQ(firstChild.ToNode(), nullptr);
}

// Test FirstChildElement on a valid node
TEST_F(XMLHandleTest_119, FirstChildElementValid_119) {
    XMLHandle handle(doc.RootElement());
    XMLHandle firstChildElem = handle.FirstChildElement();
    EXPECT_NE(firstChildElem.ToElement(), nullptr);
    EXPECT_STREQ(firstChildElem.ToElement()->Name(), "child1");
}

// Test FirstChildElement with a specific name
TEST_F(XMLHandleTest_119, FirstChildElementByName_119) {
    XMLHandle handle(doc.RootElement());
    XMLHandle child2 = handle.FirstChildElement("child2");
    EXPECT_NE(child2.ToElement(), nullptr);
    EXPECT_STREQ(child2.ToElement()->Name(), "child2");
    EXPECT_STREQ(child2.ToElement()->Attribute("name"), "second");
}

// Test FirstChildElement with a name that doesn't exist
TEST_F(XMLHandleTest_119, FirstChildElementNonExistent_119) {
    XMLHandle handle(doc.RootElement());
    XMLHandle missing = handle.FirstChildElement("nonexistent");
    EXPECT_EQ(missing.ToNode(), nullptr);
    EXPECT_EQ(missing.ToElement(), nullptr);
}

// Test FirstChildElement on a null handle
TEST_F(XMLHandleTest_119, FirstChildElementNull_119) {
    XMLHandle handle((XMLNode*)nullptr);
    XMLHandle result = handle.FirstChildElement();
    EXPECT_EQ(result.ToElement(), nullptr);
}

// Test LastChild on a valid node
TEST_F(XMLHandleTest_119, LastChildValid_119) {
    XMLHandle handle(doc.RootElement());
    XMLHandle lastChild = handle.LastChild();
    EXPECT_NE(lastChild.ToNode(), nullptr);
}

// Test LastChild on a null handle
TEST_F(XMLHandleTest_119, LastChildNull_119) {
    XMLHandle handle((XMLNode*)nullptr);
    XMLHandle lastChild = handle.LastChild();
    EXPECT_EQ(lastChild.ToNode(), nullptr);
}

// Test LastChildElement on a valid node
TEST_F(XMLHandleTest_119, LastChildElementValid_119) {
    XMLHandle handle(doc.RootElement());
    XMLHandle lastChildElem = handle.LastChildElement();
    EXPECT_NE(lastChildElem.ToElement(), nullptr);
}

// Test LastChildElement with a specific name
TEST_F(XMLHandleTest_119, LastChildElementByName_119) {
    XMLHandle handle(doc.RootElement());
    XMLHandle lastChild2 = handle.LastChildElement("child2");
    EXPECT_NE(lastChild2.ToElement(), nullptr);
    EXPECT_STREQ(lastChild2.ToElement()->Name(), "child2");
    // Should find the last child2 which has name="duplicate"
    EXPECT_STREQ(lastChild2.ToElement()->Attribute("name"), "duplicate");
}

// Test LastChildElement on a null handle
TEST_F(XMLHandleTest_119, LastChildElementNull_119) {
    XMLHandle handle((XMLNode*)nullptr);
    XMLHandle result = handle.LastChildElement();
    EXPECT_EQ(result.ToElement(), nullptr);
}

// Test NextSibling
TEST_F(XMLHandleTest_119, NextSiblingValid_119) {
    XMLHandle handle(doc.RootElement());
    XMLHandle firstChild = handle.FirstChildElement("child1");
    XMLHandle nextSib = firstChild.NextSibling();
    EXPECT_NE(nextSib.ToNode(), nullptr);
}

// Test NextSibling on a null handle
TEST_F(XMLHandleTest_119, NextSiblingNull_119) {
    XMLHandle handle((XMLNode*)nullptr);
    XMLHandle result = handle.NextSibling();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test NextSiblingElement
TEST_F(XMLHandleTest_119, NextSiblingElementValid_119) {
    XMLHandle handle(doc.RootElement());
    XMLHandle child1 = handle.FirstChildElement("child1");
    XMLHandle nextElem = child1.NextSiblingElement();
    EXPECT_NE(nextElem.ToElement(), nullptr);
    EXPECT_STREQ(nextElem.ToElement()->Name(), "child2");
}

// Test NextSiblingElement with a specific name
TEST_F(XMLHandleTest_119, NextSiblingElementByName_119) {
    XMLHandle handle(doc.RootElement());
    XMLHandle child1 = handle.FirstChildElement("child1");
    XMLHandle nextChild3 = child1.NextSiblingElement("child3");
    EXPECT_NE(nextChild3.ToElement(), nullptr);
    EXPECT_STREQ(nextChild3.ToElement()->Name(), "child3");
}

// Test NextSiblingElement on a null handle
TEST_F(XMLHandleTest_119, NextSiblingElementNull_119) {
    XMLHandle handle((XMLNode*)nullptr);
    XMLHandle result = handle.NextSiblingElement();
    EXPECT_EQ(result.ToElement(), nullptr);
}

// Test PreviousSibling
TEST_F(XMLHandleTest_119, PreviousSiblingValid_119) {
    XMLHandle handle(doc.RootElement());
    XMLHandle lastChild = handle.LastChildElement();
    XMLHandle prevSib = lastChild.PreviousSibling();
    EXPECT_NE(prevSib.ToNode(), nullptr);
}

// Test PreviousSibling on a null handle
TEST_F(XMLHandleTest_119, PreviousSiblingNull_119) {
    XMLHandle handle((XMLNode*)nullptr);
    XMLHandle result = handle.PreviousSibling();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test PreviousSiblingElement
TEST_F(XMLHandleTest_119, PreviousSiblingElementValid_119) {
    XMLHandle handle(doc.RootElement());
    XMLHandle child3 = handle.FirstChildElement("child3");
    XMLHandle prevElem = child3.PreviousSiblingElement();
    EXPECT_NE(prevElem.ToElement(), nullptr);
    EXPECT_STREQ(prevElem.ToElement()->Name(), "child2");
}

// Test PreviousSiblingElement with a specific name
TEST_F(XMLHandleTest_119, PreviousSiblingElementByName_119) {
    XMLHandle handle(doc.RootElement());
    XMLHandle child3 = handle.FirstChildElement("child3");
    XMLHandle prevChild1 = child3.PreviousSiblingElement("child1");
    EXPECT_NE(prevChild1.ToElement(), nullptr);
    EXPECT_STREQ(prevChild1.ToElement()->Name(), "child1");
}

// Test PreviousSiblingElement on a null handle
TEST_F(XMLHandleTest_119, PreviousSiblingElementNull_119) {
    XMLHandle handle((XMLNode*)nullptr);
    XMLHandle result = handle.PreviousSiblingElement();
    EXPECT_EQ(result.ToElement(), nullptr);
}

// Test ToNode on a valid element
TEST_F(XMLHandleTest_119, ToNodeValid_119) {
    XMLHandle handle(doc.RootElement());
    EXPECT_NE(handle.ToNode(), nullptr);
}

// Test ToNode on null
TEST_F(XMLHandleTest_119, ToNodeNull_119) {
    XMLHandle handle((XMLNode*)nullptr);
    EXPECT_EQ(handle.ToNode(), nullptr);
}

// Test ToElement on a valid element
TEST_F(XMLHandleTest_119, ToElementValid_119) {
    XMLHandle handle(doc.RootElement());
    EXPECT_NE(handle.ToElement(), nullptr);
    EXPECT_STREQ(handle.ToElement()->Name(), "root");
}

// Test ToElement on null
TEST_F(XMLHandleTest_119, ToElementNull_119) {
    XMLHandle handle((XMLNode*)nullptr);
    EXPECT_EQ(handle.ToElement(), nullptr);
}

// Test ToText on a text node
TEST_F(XMLHandleTest_119, ToTextValid_119) {
    XMLHandle handle(doc.RootElement());
    XMLHandle child2 = handle.FirstChildElement("child2");
    XMLHandle textNode = child2.FirstChild();
    EXPECT_NE(textNode.ToNode(), nullptr);
    EXPECT_NE(textNode.ToText(), nullptr);
}

// Test ToText on a non-text node returns null
TEST_F(XMLHandleTest_119, ToTextOnElement_119) {
    XMLHandle handle(doc.RootElement());
    EXPECT_EQ(handle.ToText(), nullptr);
}

// Test ToText on a null handle
TEST_F(XMLHandleTest_119, ToTextNull_119) {
    XMLHandle handle((XMLNode*)nullptr);
    EXPECT_EQ(handle.ToText(), nullptr);
}

// Test ToUnknown on a null handle
TEST_F(XMLHandleTest_119, ToUnknownNull_119) {
    XMLHandle handle((XMLNode*)nullptr);
    EXPECT_EQ(handle.ToUnknown(), nullptr);
}

// Test ToUnknown on a regular element returns null
TEST_F(XMLHandleTest_119, ToUnknownOnElement_119) {
    XMLHandle handle(doc.RootElement());
    EXPECT_EQ(handle.ToUnknown(), nullptr);
}

// Test ToDeclaration on a null handle
TEST_F(XMLHandleTest_119, ToDeclarationNull_119) {
    XMLHandle handle((XMLNode*)nullptr);
    EXPECT_EQ(handle.ToDeclaration(), nullptr);
}

// Test ToDeclaration on a regular element returns null
TEST_F(XMLHandleTest_119, ToDeclarationOnElement_119) {
    XMLHandle handle(doc.RootElement());
    EXPECT_EQ(handle.ToDeclaration(), nullptr);
}

// Test ToDeclaration on the XML declaration
TEST_F(XMLHandleTest_119, ToDeclarationValid_119) {
    XMLHandle docHandle(&doc);
    XMLHandle firstChild = docHandle.FirstChild();
    // The first child of the document should be the XML declaration
    if (firstChild.ToNode() != nullptr && firstChild.ToDeclaration() != nullptr) {
        EXPECT_NE(firstChild.ToDeclaration(), nullptr);
    }
}

// Test chaining: navigate to grandchild
TEST_F(XMLHandleTest_119, ChainingNavigation_119) {
    XMLHandle handle(doc.RootElement());
    XMLElement* grandchild = handle.FirstChildElement("child1")
                                   .FirstChildElement("grandchild1")
                                   .ToElement();
    EXPECT_NE(grandchild, nullptr);
    EXPECT_STREQ(grandchild->Name(), "grandchild1");
}

// Test chaining through a missing path returns null gracefully
TEST_F(XMLHandleTest_119, ChainingThroughMissingPath_119) {
    XMLHandle handle(doc.RootElement());
    XMLElement* result = handle.FirstChildElement("nonexistent")
                               .FirstChildElement("anything")
                               .ToElement();
    EXPECT_EQ(result, nullptr);
}

// Test navigating grandchild siblings
TEST_F(XMLHandleTest_119, GrandchildSiblings_119) {
    XMLHandle handle(doc.RootElement());
    XMLHandle gc1 = handle.FirstChildElement("child1").FirstChildElement("grandchild1");
    EXPECT_NE(gc1.ToElement(), nullptr);

    XMLHandle gc2 = gc1.NextSiblingElement();
    EXPECT_NE(gc2.ToElement(), nullptr);
    EXPECT_STREQ(gc2.ToElement()->Name(), "grandchild2");

    // grandchild2 has no next sibling element
    XMLHandle gc3 = gc2.NextSiblingElement();
    EXPECT_EQ(gc3.ToElement(), nullptr);
}

// Test PreviousSiblingElement from grandchild2 goes back to grandchild1
TEST_F(XMLHandleTest_119, GrandchildPreviousSibling_119) {
    XMLHandle handle(doc.RootElement());
    XMLHandle gc2 = handle.FirstChildElement("child1").LastChildElement("grandchild2");
    EXPECT_NE(gc2.ToElement(), nullptr);

    XMLHandle gc1 = gc2.PreviousSiblingElement();
    EXPECT_NE(gc1.ToElement(), nullptr);
    EXPECT_STREQ(gc1.ToElement()->Name(), "grandchild1");
}

// Test FirstChild on a leaf node (no children)
TEST_F(XMLHandleTest_119, FirstChildOnLeafNode_119) {
    XMLHandle handle(doc.RootElement());
    XMLHandle child3 = handle.FirstChildElement("child3");
    EXPECT_NE(child3.ToElement(), nullptr);

    XMLHandle result = child3.FirstChild();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test LastChild on a leaf node (no children)
TEST_F(XMLHandleTest_119, LastChildOnLeafNode_119) {
    XMLHandle handle(doc.RootElement());
    XMLHandle child3 = handle.FirstChildElement("child3");
    EXPECT_NE(child3.ToElement(), nullptr);

    XMLHandle result = child3.LastChild();
    EXPECT_EQ(result.ToNode(), nullptr);
}

// Test handle with an empty document
TEST_F(XMLHandleTest_119, EmptyDocument_119) {
    XMLDocument emptyDoc;
    XMLHandle handle(&emptyDoc);
    EXPECT_NE(handle.ToNode(), nullptr);
    EXPECT_EQ(handle.FirstChildElement().ToElement(), nullptr);
}

// Test assignment from null to valid and back
TEST_F(XMLHandleTest_119, AssignmentOverwrite_119) {
    XMLNode* root = doc.RootElement();
    XMLHandle handle1(root);
    XMLHandle handle2((XMLNode*)nullptr);

    handle2 = handle1;
    EXPECT_EQ(handle2.ToNode(), root);

    XMLHandle nullHandle((XMLNode*)nullptr);
    handle2 = nullHandle;
    EXPECT_EQ(handle2.ToNode(), nullptr);
}
