#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

// ============================================================
// Test fixture
// ============================================================
class XMLNodeDeepCloneTest_186 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLDocument targetDoc;

    void SetUp() override {
        doc.Clear();
        targetDoc.Clear();
    }
};

// ------------------------------------------------------------
// Normal operation tests
// ------------------------------------------------------------

TEST_F(XMLNodeDeepCloneTest_186, DeepCloneSingleElement_186) {
    doc.Parse("<root/>");
    ASSERT_FALSE(doc.Error());

    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    XMLNode* clone = root->DeepClone(&targetDoc);
    ASSERT_NE(clone, nullptr);

    targetDoc.InsertEndChild(clone);
    XMLElement* clonedRoot = targetDoc.RootElement();
    ASSERT_NE(clonedRoot, nullptr);
    EXPECT_STREQ(clonedRoot->Name(), "root");
}

TEST_F(XMLNodeDeepCloneTest_186, DeepCloneElementWithChildren_186) {
    doc.Parse("<root><child1/><child2/></root>");
    ASSERT_FALSE(doc.Error());

    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    XMLNode* clone = root->DeepClone(&targetDoc);
    ASSERT_NE(clone, nullptr);

    targetDoc.InsertEndChild(clone);
    XMLElement* clonedRoot = targetDoc.RootElement();
    ASSERT_NE(clonedRoot, nullptr);
    EXPECT_STREQ(clonedRoot->Name(), "root");

    EXPECT_EQ(clonedRoot->ChildElementCount(), 2);

    XMLElement* c1 = clonedRoot->FirstChildElement("child1");
    ASSERT_NE(c1, nullptr);
    XMLElement* c2 = clonedRoot->FirstChildElement("child2");
    ASSERT_NE(c2, nullptr);
}

TEST_F(XMLNodeDeepCloneTest_186, DeepCloneNestedChildren_186) {
    doc.Parse("<root><a><b><c/></b></a></root>");
    ASSERT_FALSE(doc.Error());

    XMLElement* root = doc.RootElement();
    XMLNode* clone = root->DeepClone(&targetDoc);
    ASSERT_NE(clone, nullptr);

    targetDoc.InsertEndChild(clone);
    XMLElement* clonedRoot = targetDoc.RootElement();
    ASSERT_NE(clonedRoot, nullptr);

    XMLElement* a = clonedRoot->FirstChildElement("a");
    ASSERT_NE(a, nullptr);
    XMLElement* b = a->FirstChildElement("b");
    ASSERT_NE(b, nullptr);
    XMLElement* c = b->FirstChildElement("c");
    ASSERT_NE(c, nullptr);
    EXPECT_TRUE(c->NoChildren());
}

TEST_F(XMLNodeDeepCloneTest_186, DeepClonePreservesAttributes_186) {
    doc.Parse("<root attr1=\"val1\" attr2=\"val2\"/>");
    ASSERT_FALSE(doc.Error());

    XMLElement* root = doc.RootElement();
    XMLNode* clone = root->DeepClone(&targetDoc);
    ASSERT_NE(clone, nullptr);

    targetDoc.InsertEndChild(clone);
    XMLElement* clonedRoot = targetDoc.RootElement();
    ASSERT_NE(clonedRoot, nullptr);

    EXPECT_STREQ(clonedRoot->Attribute("attr1"), "val1");
    EXPECT_STREQ(clonedRoot->Attribute("attr2"), "val2");
}

TEST_F(XMLNodeDeepCloneTest_186, DeepClonePreservesTextContent_186) {
    doc.Parse("<root>Hello World</root>");
    ASSERT_FALSE(doc.Error());

    XMLElement* root = doc.RootElement();
    XMLNode* clone = root->DeepClone(&targetDoc);
    ASSERT_NE(clone, nullptr);

    targetDoc.InsertEndChild(clone);
    XMLElement* clonedRoot = targetDoc.RootElement();
    ASSERT_NE(clonedRoot, nullptr);

    EXPECT_STREQ(clonedRoot->GetText(), "Hello World");
}

TEST_F(XMLNodeDeepCloneTest_186, DeepCloneToSameDocument_186) {
    doc.Parse("<root><child/></root>");
    ASSERT_FALSE(doc.Error());

    XMLElement* root = doc.RootElement();
    XMLNode* clone = root->DeepClone(&doc);
    ASSERT_NE(clone, nullptr);

    // Insert the clone as a sibling
    doc.InsertEndChild(clone);

    // Now there should be two root-level elements
    int count = 0;
    for (const XMLNode* node = doc.FirstChild(); node; node = node->NextSibling()) {
        count++;
    }
    EXPECT_GE(count, 2);
}

TEST_F(XMLNodeDeepCloneTest_186, DeepCloneComment_186) {
    doc.Parse("<root><!-- a comment --></root>");
    ASSERT_FALSE(doc.Error());

    XMLElement* root = doc.RootElement();
    XMLNode* clone = root->DeepClone(&targetDoc);
    ASSERT_NE(clone, nullptr);

    targetDoc.InsertEndChild(clone);
    XMLElement* clonedRoot = targetDoc.RootElement();
    ASSERT_NE(clonedRoot, nullptr);

    const XMLNode* child = clonedRoot->FirstChild();
    ASSERT_NE(child, nullptr);
    const XMLComment* comment = child->ToComment();
    ASSERT_NE(comment, nullptr);
    EXPECT_STREQ(comment->Value(), " a comment ");
}

TEST_F(XMLNodeDeepCloneTest_186, DeepCloneElementWithNoChildren_186) {
    doc.Parse("<empty/>");
    ASSERT_FALSE(doc.Error());

    XMLElement* root = doc.RootElement();
    XMLNode* clone = root->DeepClone(&targetDoc);
    ASSERT_NE(clone, nullptr);

    targetDoc.InsertEndChild(clone);
    XMLElement* clonedRoot = targetDoc.RootElement();
    ASSERT_NE(clonedRoot, nullptr);
    EXPECT_TRUE(clonedRoot->NoChildren());
    EXPECT_STREQ(clonedRoot->Name(), "empty");
}

TEST_F(XMLNodeDeepCloneTest_186, DeepCloneMultipleSiblings_186) {
    doc.Parse("<root><a/><b/><c/><d/><e/></root>");
    ASSERT_FALSE(doc.Error());

    XMLElement* root = doc.RootElement();
    XMLNode* clone = root->DeepClone(&targetDoc);
    ASSERT_NE(clone, nullptr);

    targetDoc.InsertEndChild(clone);
    XMLElement* clonedRoot = targetDoc.RootElement();
    ASSERT_NE(clonedRoot, nullptr);
    EXPECT_EQ(clonedRoot->ChildElementCount(), 5);
}

TEST_F(XMLNodeDeepCloneTest_186, DeepCloneIsIndependentOfSource_186) {
    doc.Parse("<root><child val=\"1\"/></root>");
    ASSERT_FALSE(doc.Error());

    XMLElement* root = doc.RootElement();
    XMLNode* clone = root->DeepClone(&targetDoc);
    ASSERT_NE(clone, nullptr);
    targetDoc.InsertEndChild(clone);

    // Modify the source document
    doc.RootElement()->FirstChildElement("child")->SetAttribute("val", "2");

    // Clone should not be affected
    XMLElement* clonedRoot = targetDoc.RootElement();
    ASSERT_NE(clonedRoot, nullptr);
    XMLElement* clonedChild = clonedRoot->FirstChildElement("child");
    ASSERT_NE(clonedChild, nullptr);
    EXPECT_STREQ(clonedChild->Attribute("val"), "1");
}

TEST_F(XMLNodeDeepCloneTest_186, DeepCloneComplexTree_186) {
    const char* xml =
        "<root>"
        "  <level1 a=\"1\">"
        "    <level2>text</level2>"
        "    <level2b/>"
        "  </level1>"
        "  <level1b>"
        "    <!-- comment -->"
        "  </level1b>"
        "</root>";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());

    XMLElement* root = doc.RootElement();
    XMLNode* clone = root->DeepClone(&targetDoc);
    ASSERT_NE(clone, nullptr);
    targetDoc.InsertEndChild(clone);

    XMLElement* clonedRoot = targetDoc.RootElement();
    ASSERT_NE(clonedRoot, nullptr);

    XMLElement* level1 = clonedRoot->FirstChildElement("level1");
    ASSERT_NE(level1, nullptr);
    EXPECT_STREQ(level1->Attribute("a"), "1");

    XMLElement* level2 = level1->FirstChildElement("level2");
    ASSERT_NE(level2, nullptr);
    EXPECT_STREQ(level2->GetText(), "text");

    XMLElement* level2b = level1->FirstChildElement("level2b");
    ASSERT_NE(level2b, nullptr);

    XMLElement* level1b = clonedRoot->FirstChildElement("level1b");
    ASSERT_NE(level1b, nullptr);

    const XMLNode* commentNode = level1b->FirstChild();
    ASSERT_NE(commentNode, nullptr);
    ASSERT_NE(commentNode->ToComment(), nullptr);
}

// ------------------------------------------------------------
// DeepCopy on XMLDocument
// ------------------------------------------------------------

TEST_F(XMLNodeDeepCloneTest_186, DocumentDeepCopy_186) {
    doc.Parse("<root><a/><b/></root>");
    ASSERT_FALSE(doc.Error());

    doc.DeepCopy(&targetDoc);

    XMLElement* clonedRoot = targetDoc.RootElement();
    ASSERT_NE(clonedRoot, nullptr);
    EXPECT_STREQ(clonedRoot->Name(), "root");
    EXPECT_EQ(clonedRoot->ChildElementCount(), 2);
}

TEST_F(XMLNodeDeepCloneTest_186, DocumentDeepCopyOverwritesTarget_186) {
    targetDoc.Parse("<old>data</old>");
    ASSERT_FALSE(targetDoc.Error());

    doc.Parse("<new>stuff</new>");
    ASSERT_FALSE(doc.Error());

    doc.DeepCopy(&targetDoc);

    XMLElement* clonedRoot = targetDoc.RootElement();
    ASSERT_NE(clonedRoot, nullptr);
    EXPECT_STREQ(clonedRoot->Name(), "new");
    EXPECT_STREQ(clonedRoot->GetText(), "stuff");
}

// ------------------------------------------------------------
// Boundary conditions
// ------------------------------------------------------------

TEST_F(XMLNodeDeepCloneTest_186, DeepCloneEmptyDocument_186) {
    // Empty document deep copy
    doc.Clear();
    doc.DeepCopy(&targetDoc);

    EXPECT_EQ(targetDoc.RootElement(), nullptr);
}

TEST_F(XMLNodeDeepCloneTest_186, DeepCloneDocumentShallowCloneReturnsNull_186) {
    // XMLDocument::ShallowClone returns nullptr
    XMLNode* clone = doc.ShallowClone(&targetDoc);
    EXPECT_EQ(clone, nullptr);
}

TEST_F(XMLNodeDeepCloneTest_186, DeepClonePreservesChildOrder_186) {
    doc.Parse("<root><z/><a/><m/><b/></root>");
    ASSERT_FALSE(doc.Error());

    XMLNode* clone = doc.RootElement()->DeepClone(&targetDoc);
    targetDoc.InsertEndChild(clone);

    XMLElement* clonedRoot = targetDoc.RootElement();
    ASSERT_NE(clonedRoot, nullptr);

    const char* expectedOrder[] = {"z", "a", "m", "b"};
    int i = 0;
    for (XMLElement* e = clonedRoot->FirstChildElement(); e; e = e->NextSiblingElement()) {
        ASSERT_LT(i, 4);
        EXPECT_STREQ(e->Name(), expectedOrder[i]);
        i++;
    }
    EXPECT_EQ(i, 4);
}

TEST_F(XMLNodeDeepCloneTest_186, DeepCloneTextNode_186) {
    doc.Parse("<root>Some text here</root>");
    ASSERT_FALSE(doc.Error());

    XMLNode* textNode = doc.RootElement()->FirstChild();
    ASSERT_NE(textNode, nullptr);
    ASSERT_NE(textNode->ToText(), nullptr);

    XMLNode* clone = textNode->DeepClone(&targetDoc);
    ASSERT_NE(clone, nullptr);

    XMLElement* wrapper = targetDoc.NewElement("wrapper");
    targetDoc.InsertEndChild(wrapper);
    wrapper->InsertEndChild(clone);

    EXPECT_STREQ(wrapper->GetText(), "Some text here");
}

TEST_F(XMLNodeDeepCloneTest_186, DeepCloneDeclaration_186) {
    doc.Parse("<?xml version=\"1.0\"?><root/>");
    ASSERT_FALSE(doc.Error());

    // First child should be the declaration
    const XMLNode* firstChild = doc.FirstChild();
    ASSERT_NE(firstChild, nullptr);

    if (firstChild->ToDeclaration()) {
        XMLNode* clone = firstChild->DeepClone(&targetDoc);
        ASSERT_NE(clone, nullptr);
        targetDoc.InsertFirstChild(clone);

        const XMLNode* targetFirst = targetDoc.FirstChild();
        ASSERT_NE(targetFirst, nullptr);
        ASSERT_NE(targetFirst->ToDeclaration(), nullptr);
    }
}

TEST_F(XMLNodeDeepCloneTest_186, DeepCloneDeeplyNestedTree_186) {
    // Build a deeply nested tree
    const char* xml =
        "<l1><l2><l3><l4><l5><l6><l7><l8>deep</l8></l7></l6></l5></l4></l3></l2></l1>";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());

    XMLNode* clone = doc.RootElement()->DeepClone(&targetDoc);
    ASSERT_NE(clone, nullptr);
    targetDoc.InsertEndChild(clone);

    // Navigate down to l8
    XMLElement* e = targetDoc.RootElement();
    const char* levels[] = {"l2", "l3", "l4", "l5", "l6", "l7", "l8"};
    for (const char* name : levels) {
        ASSERT_NE(e, nullptr);
        e = e->FirstChildElement(name);
    }
    ASSERT_NE(e, nullptr);
    EXPECT_STREQ(e->GetText(), "deep");
}

TEST_F(XMLNodeDeepCloneTest_186, DeepCloneWithMixedContent_186) {
    doc.Parse("<root>text1<child/>text2</root>");
    ASSERT_FALSE(doc.Error());

    XMLNode* clone = doc.RootElement()->DeepClone(&targetDoc);
    ASSERT_NE(clone, nullptr);
    targetDoc.InsertEndChild(clone);

    XMLElement* clonedRoot = targetDoc.RootElement();
    ASSERT_NE(clonedRoot, nullptr);

    // Should have 3 children: text, element, text
    int childCount = 0;
    for (const XMLNode* n = clonedRoot->FirstChild(); n; n = n->NextSibling()) {
        childCount++;
    }
    EXPECT_EQ(childCount, 3);
}

TEST_F(XMLNodeDeepCloneTest_186, DeepCloneNewElementFromDocument_186) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);

    XMLNode* clone = elem->DeepClone(&targetDoc);
    ASSERT_NE(clone, nullptr);
    targetDoc.InsertEndChild(clone);

    XMLElement* cloned = targetDoc.RootElement();
    ASSERT_NE(cloned, nullptr);
    EXPECT_STREQ(cloned->Name(), "test");
    EXPECT_TRUE(cloned->NoChildren());
}

TEST_F(XMLNodeDeepCloneTest_186, DeepCloneUnknownNode_186) {
    doc.Parse("<root><!ENTITY test></root>");
    // Even if parsing produces unknown nodes, let's try with NewUnknown
    XMLUnknown* unk = doc.NewUnknown("something");
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    root->InsertEndChild(unk);

    XMLNode* clone = root->DeepClone(&targetDoc);
    ASSERT_NE(clone, nullptr);
    targetDoc.InsertEndChild(clone);

    XMLElement* clonedRoot = targetDoc.RootElement();
    ASSERT_NE(clonedRoot, nullptr);
    const XMLNode* child = clonedRoot->FirstChild();
    ASSERT_NE(child, nullptr);
    EXPECT_NE(child->ToUnknown(), nullptr);
}

TEST_F(XMLNodeDeepCloneTest_186, DeepClonedNodeBelongsToTargetDocument_186) {
    doc.Parse("<root><child/></root>");
    ASSERT_FALSE(doc.Error());

    XMLNode* clone = doc.RootElement()->DeepClone(&targetDoc);
    ASSERT_NE(clone, nullptr);
    targetDoc.InsertEndChild(clone);

    // The cloned node's document should be the target document
    EXPECT_EQ(clone->GetDocument(), &targetDoc);
}
