#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLHandleTest_129 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
        // Build a simple XML tree for testing
        // <root>
        //   <child1>text1</child1>
        //   <child2 attr="val">text2</child2>
        //   <child3/>
        // </root>
        const char* xml = "<root><child1>text1</child1><child2 attr=\"val\">text2</child2><child3/></root>";
        doc.Parse(xml);
    }
};

// Test constructing XMLHandle from a node pointer
TEST_F(XMLHandleTest_129, ConstructFromNodePointer_129) {
    XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLHandle handle(root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test constructing XMLHandle from a node reference
TEST_F(XMLHandleTest_129, ConstructFromNodeReference_129) {
    XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLHandle handle(*root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test constructing XMLHandle from null pointer
TEST_F(XMLHandleTest_129, ConstructFromNullPointer_129) {
    XMLHandle handle((XMLNode*)nullptr);
    EXPECT_EQ(handle.ToNode(), nullptr);
    EXPECT_EQ(handle.ToElement(), nullptr);
    EXPECT_EQ(handle.ToText(), nullptr);
    EXPECT_EQ(handle.ToUnknown(), nullptr);
    EXPECT_EQ(handle.ToDeclaration(), nullptr);
}

// Test copy constructor
TEST_F(XMLHandleTest_129, CopyConstructor_129) {
    XMLNode* root = doc.FirstChildElement("root");
    XMLHandle handle1(root);
    XMLHandle handle2(handle1);
    EXPECT_EQ(handle2.ToNode(), root);
}

// Test assignment operator
TEST_F(XMLHandleTest_129, AssignmentOperator_129) {
    XMLNode* root = doc.FirstChildElement("root");
    XMLHandle handle1(root);
    XMLHandle handle2((XMLNode*)nullptr);
    handle2 = handle1;
    EXPECT_EQ(handle2.ToNode(), root);
}

// Test ToElement returns element when node is an element
TEST_F(XMLHandleTest_129, ToElementReturnsElement_129) {
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLHandle handle(root);
    EXPECT_EQ(handle.ToElement(), root);
}

// Test ToElement returns null when handle is null
TEST_F(XMLHandleTest_129, ToElementReturnsNullWhenNull_129) {
    XMLHandle handle((XMLNode*)nullptr);
    EXPECT_EQ(handle.ToElement(), nullptr);
}

// Test ToNode
TEST_F(XMLHandleTest_129, ToNodeReturnsNode_129) {
    XMLElement* root = doc.FirstChildElement("root");
    XMLHandle handle(root);
    EXPECT_EQ(handle.ToNode(), root);
}

// Test ToText returns text node
TEST_F(XMLHandleTest_129, ToTextReturnsTextNode_129) {
    XMLElement* child1 = doc.FirstChildElement("root")->FirstChildElement("child1");
    ASSERT_NE(child1, nullptr);
    XMLNode* textNode = child1->FirstChild();
    ASSERT_NE(textNode, nullptr);
    XMLHandle handle(textNode);
    EXPECT_NE(handle.ToText(), nullptr);
}

// Test ToText returns null for non-text node
TEST_F(XMLHandleTest_129, ToTextReturnsNullForElement_129) {
    XMLElement* root = doc.FirstChildElement("root");
    XMLHandle handle(root);
    EXPECT_EQ(handle.ToText(), nullptr);
}

// Test FirstChild
TEST_F(XMLHandleTest_129, FirstChild_129) {
    XMLElement* root = doc.FirstChildElement("root");
    XMLHandle handle(root);
    XMLHandle firstChild = handle.FirstChild();
    EXPECT_NE(firstChild.ToNode(), nullptr);
    EXPECT_EQ(firstChild.ToElement(), root->FirstChildElement());
}

// Test FirstChild on null handle
TEST_F(XMLHandleTest_129, FirstChildOnNullHandle_129) {
    XMLHandle handle((XMLNode*)nullptr);
    XMLHandle firstChild = handle.FirstChild();
    EXPECT_EQ(firstChild.ToNode(), nullptr);
}

// Test FirstChildElement
TEST_F(XMLHandleTest_129, FirstChildElement_129) {
    XMLElement* root = doc.FirstChildElement("root");
    XMLHandle handle(root);
    XMLHandle firstElem = handle.FirstChildElement();
    EXPECT_NE(firstElem.ToElement(), nullptr);
    EXPECT_STREQ(firstElem.ToElement()->Name(), "child1");
}

// Test FirstChildElement with name
TEST_F(XMLHandleTest_129, FirstChildElementWithName_129) {
    XMLElement* root = doc.FirstChildElement("root");
    XMLHandle handle(root);
    XMLHandle child2 = handle.FirstChildElement("child2");
    EXPECT_NE(child2.ToElement(), nullptr);
    EXPECT_STREQ(child2.ToElement()->Name(), "child2");
}

// Test FirstChildElement with non-existent name
TEST_F(XMLHandleTest_129, FirstChildElementWithNonExistentName_129) {
    XMLElement* root = doc.FirstChildElement("root");
    XMLHandle handle(root);
    XMLHandle missing = handle.FirstChildElement("nonexistent");
    EXPECT_EQ(missing.ToElement(), nullptr);
    EXPECT_EQ(missing.ToNode(), nullptr);
}

// Test FirstChildElement on null handle
TEST_F(XMLHandleTest_129, FirstChildElementOnNullHandle_129) {
    XMLHandle handle((XMLNode*)nullptr);
    XMLHandle firstElem = handle.FirstChildElement();
    EXPECT_EQ(firstElem.ToElement(), nullptr);
}

// Test LastChild
TEST_F(XMLHandleTest_129, LastChild_129) {
    XMLElement* root = doc.FirstChildElement("root");
    XMLHandle handle(root);
    XMLHandle lastChild = handle.LastChild();
    EXPECT_NE(lastChild.ToNode(), nullptr);
}

// Test LastChild on null handle
TEST_F(XMLHandleTest_129, LastChildOnNullHandle_129) {
    XMLHandle handle((XMLNode*)nullptr);
    XMLHandle lastChild = handle.LastChild();
    EXPECT_EQ(lastChild.ToNode(), nullptr);
}

// Test LastChildElement
TEST_F(XMLHandleTest_129, LastChildElement_129) {
    XMLElement* root = doc.FirstChildElement("root");
    XMLHandle handle(root);
    XMLHandle lastElem = handle.LastChildElement();
    EXPECT_NE(lastElem.ToElement(), nullptr);
    EXPECT_STREQ(lastElem.ToElement()->Name(), "child3");
}

// Test LastChildElement with name
TEST_F(XMLHandleTest_129, LastChildElementWithName_129) {
    XMLElement* root = doc.FirstChildElement("root");
    XMLHandle handle(root);
    XMLHandle child1 = handle.LastChildElement("child1");
    EXPECT_NE(child1.ToElement(), nullptr);
    EXPECT_STREQ(child1.ToElement()->Name(), "child1");
}

// Test LastChildElement on null handle
TEST_F(XMLHandleTest_129, LastChildElementOnNullHandle_129) {
    XMLHandle handle((XMLNode*)nullptr);
    XMLHandle lastElem = handle.LastChildElement();
    EXPECT_EQ(lastElem.ToElement(), nullptr);
}

// Test PreviousSibling
TEST_F(XMLHandleTest_129, PreviousSibling_129) {
    XMLElement* root = doc.FirstChildElement("root");
    XMLElement* child2 = root->FirstChildElement("child2");
    ASSERT_NE(child2, nullptr);
    XMLHandle handle(child2);
    XMLHandle prev = handle.PreviousSibling();
    EXPECT_NE(prev.ToNode(), nullptr);
}

// Test PreviousSibling on null handle
TEST_F(XMLHandleTest_129, PreviousSiblingOnNullHandle_129) {
    XMLHandle handle((XMLNode*)nullptr);
    XMLHandle prev = handle.PreviousSibling();
    EXPECT_EQ(prev.ToNode(), nullptr);
}

// Test PreviousSibling when there is no previous sibling
TEST_F(XMLHandleTest_129, PreviousSiblingNone_129) {
    XMLElement* root = doc.FirstChildElement("root");
    XMLElement* child1 = root->FirstChildElement("child1");
    ASSERT_NE(child1, nullptr);
    XMLHandle handle(child1);
    XMLHandle prev = handle.PreviousSibling();
    EXPECT_EQ(prev.ToNode(), nullptr);
}

// Test PreviousSiblingElement
TEST_F(XMLHandleTest_129, PreviousSiblingElement_129) {
    XMLElement* root = doc.FirstChildElement("root");
    XMLElement* child3 = root->FirstChildElement("child3");
    ASSERT_NE(child3, nullptr);
    XMLHandle handle(child3);
    XMLHandle prevElem = handle.PreviousSiblingElement();
    EXPECT_NE(prevElem.ToElement(), nullptr);
    EXPECT_STREQ(prevElem.ToElement()->Name(), "child2");
}

// Test PreviousSiblingElement with name
TEST_F(XMLHandleTest_129, PreviousSiblingElementWithName_129) {
    XMLElement* root = doc.FirstChildElement("root");
    XMLElement* child3 = root->FirstChildElement("child3");
    ASSERT_NE(child3, nullptr);
    XMLHandle handle(child3);
    XMLHandle prevElem = handle.PreviousSiblingElement("child1");
    EXPECT_NE(prevElem.ToElement(), nullptr);
    EXPECT_STREQ(prevElem.ToElement()->Name(), "child1");
}

// Test PreviousSiblingElement on null handle
TEST_F(XMLHandleTest_129, PreviousSiblingElementOnNullHandle_129) {
    XMLHandle handle((XMLNode*)nullptr);
    XMLHandle prevElem = handle.PreviousSiblingElement();
    EXPECT_EQ(prevElem.ToElement(), nullptr);
}

// Test NextSibling
TEST_F(XMLHandleTest_129, NextSibling_129) {
    XMLElement* root = doc.FirstChildElement("root");
    XMLElement* child1 = root->FirstChildElement("child1");
    ASSERT_NE(child1, nullptr);
    XMLHandle handle(child1);
    XMLHandle next = handle.NextSibling();
    EXPECT_NE(next.ToNode(), nullptr);
}

// Test NextSibling on null handle
TEST_F(XMLHandleTest_129, NextSiblingOnNullHandle_129) {
    XMLHandle handle((XMLNode*)nullptr);
    XMLHandle next = handle.NextSibling();
    EXPECT_EQ(next.ToNode(), nullptr);
}

// Test NextSibling when there is no next sibling
TEST_F(XMLHandleTest_129, NextSiblingNone_129) {
    XMLElement* root = doc.FirstChildElement("root");
    XMLElement* child3 = root->FirstChildElement("child3");
    ASSERT_NE(child3, nullptr);
    XMLHandle handle(child3);
    XMLHandle next = handle.NextSibling();
    EXPECT_EQ(next.ToNode(), nullptr);
}

// Test NextSiblingElement
TEST_F(XMLHandleTest_129, NextSiblingElement_129) {
    XMLElement* root = doc.FirstChildElement("root");
    XMLElement* child1 = root->FirstChildElement("child1");
    ASSERT_NE(child1, nullptr);
    XMLHandle handle(child1);
    XMLHandle nextElem = handle.NextSiblingElement();
    EXPECT_NE(nextElem.ToElement(), nullptr);
    EXPECT_STREQ(nextElem.ToElement()->Name(), "child2");
}

// Test NextSiblingElement with name
TEST_F(XMLHandleTest_129, NextSiblingElementWithName_129) {
    XMLElement* root = doc.FirstChildElement("root");
    XMLElement* child1 = root->FirstChildElement("child1");
    ASSERT_NE(child1, nullptr);
    XMLHandle handle(child1);
    XMLHandle nextElem = handle.NextSiblingElement("child3");
    EXPECT_NE(nextElem.ToElement(), nullptr);
    EXPECT_STREQ(nextElem.ToElement()->Name(), "child3");
}

// Test NextSiblingElement on null handle
TEST_F(XMLHandleTest_129, NextSiblingElementOnNullHandle_129) {
    XMLHandle handle((XMLNode*)nullptr);
    XMLHandle nextElem = handle.NextSiblingElement();
    EXPECT_EQ(nextElem.ToElement(), nullptr);
}

// Test chaining operations
TEST_F(XMLHandleTest_129, ChainingOperations_129) {
    XMLHandle docHandle(&doc);
    XMLElement* child2 = docHandle.FirstChildElement("root").FirstChildElement("child2").ToElement();
    EXPECT_NE(child2, nullptr);
    EXPECT_STREQ(child2->Name(), "child2");
}

// Test chaining with null intermediate
TEST_F(XMLHandleTest_129, ChainingWithNullIntermediate_129) {
    XMLHandle docHandle(&doc);
    XMLElement* result = docHandle.FirstChildElement("nonexistent").FirstChildElement("child1").ToElement();
    EXPECT_EQ(result, nullptr);
}

// Test ToUnknown returns null for element
TEST_F(XMLHandleTest_129, ToUnknownReturnsNullForElement_129) {
    XMLElement* root = doc.FirstChildElement("root");
    XMLHandle handle(root);
    EXPECT_EQ(handle.ToUnknown(), nullptr);
}

// Test ToDeclaration returns null for element
TEST_F(XMLHandleTest_129, ToDeclarationReturnsNullForElement_129) {
    XMLElement* root = doc.FirstChildElement("root");
    XMLHandle handle(root);
    EXPECT_EQ(handle.ToDeclaration(), nullptr);
}

// Test ToDeclaration with declaration node
TEST_F(XMLHandleTest_129, ToDeclarationWithDeclaration_129) {
    XMLDocument declDoc;
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    declDoc.Parse(xml);
    XMLNode* firstChild = declDoc.FirstChild();
    ASSERT_NE(firstChild, nullptr);
    XMLHandle handle(firstChild);
    if (firstChild->ToDeclaration()) {
        EXPECT_NE(handle.ToDeclaration(), nullptr);
    }
}

// Test handle with document node
TEST_F(XMLHandleTest_129, HandleWithDocumentNode_129) {
    XMLHandle handle(&doc);
    EXPECT_EQ(handle.ToNode(), &doc);
    EXPECT_EQ(handle.ToElement(), nullptr); // Document is not an element
}

// Test deep chaining
TEST_F(XMLHandleTest_129, DeepChaining_129) {
    XMLDocument deepDoc;
    const char* xml = "<a><b><c><d>deep</d></c></b></a>";
    deepDoc.Parse(xml);
    XMLHandle handle(&deepDoc);
    XMLElement* d = handle.FirstChildElement("a").FirstChildElement("b").FirstChildElement("c").FirstChildElement("d").ToElement();
    EXPECT_NE(d, nullptr);
    EXPECT_STREQ(d->Name(), "d");
}

// Test null chaining remains null throughout
TEST_F(XMLHandleTest_129, NullChainingRemainsNull_129) {
    XMLHandle handle((XMLNode*)nullptr);
    XMLHandle result = handle.FirstChild().FirstChildElement().LastChild().LastChildElement()
        .NextSibling().NextSiblingElement().PreviousSibling().PreviousSiblingElement();
    EXPECT_EQ(result.ToNode(), nullptr);
    EXPECT_EQ(result.ToElement(), nullptr);
    EXPECT_EQ(result.ToText(), nullptr);
    EXPECT_EQ(result.ToUnknown(), nullptr);
    EXPECT_EQ(result.ToDeclaration(), nullptr);
}

// Test self-assignment
TEST_F(XMLHandleTest_129, SelfAssignment_129) {
    XMLElement* root = doc.FirstChildElement("root");
    XMLHandle handle(root);
    handle = handle;
    EXPECT_EQ(handle.ToNode(), root);
}

// Test with empty document
TEST_F(XMLHandleTest_129, EmptyDocument_129) {
    XMLDocument emptyDoc;
    XMLHandle handle(&emptyDoc);
    EXPECT_EQ(handle.FirstChild().ToNode(), nullptr);
    EXPECT_EQ(handle.FirstChildElement().ToElement(), nullptr);
    EXPECT_EQ(handle.LastChild().ToNode(), nullptr);
    EXPECT_EQ(handle.LastChildElement().ToElement(), nullptr);
}

// Test ToText on null handle
TEST_F(XMLHandleTest_129, ToTextOnNullHandle_129) {
    XMLHandle handle((XMLNode*)nullptr);
    EXPECT_EQ(handle.ToText(), nullptr);
}

// Test ToUnknown on null handle
TEST_F(XMLHandleTest_129, ToUnknownOnNullHandle_129) {
    XMLHandle handle((XMLNode*)nullptr);
    EXPECT_EQ(handle.ToUnknown(), nullptr);
}

// Test ToDeclaration on null handle
TEST_F(XMLHandleTest_129, ToDeclarationOnNullHandle_129) {
    XMLHandle handle((XMLNode*)nullptr);
    EXPECT_EQ(handle.ToDeclaration(), nullptr);
}

// Test ToNode on null handle
TEST_F(XMLHandleTest_129, ToNodeOnNullHandle_129) {
    XMLHandle handle((XMLNode*)nullptr);
    EXPECT_EQ(handle.ToNode(), nullptr);
}
