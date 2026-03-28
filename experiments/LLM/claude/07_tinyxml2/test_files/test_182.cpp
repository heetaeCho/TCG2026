#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLNodeTest_182 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test ChildElementCount with no children
TEST_F(XMLNodeTest_182, ChildElementCount_NoChildren_ReturnsZero_182) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    EXPECT_EQ(root->ChildElementCount(), 0);
}

// Test ChildElementCount with no filter (all children)
TEST_F(XMLNodeTest_182, ChildElementCount_MultipleChildren_ReturnsCorrectCount_182) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    root->InsertEndChild(doc.NewElement("child"));
    root->InsertEndChild(doc.NewElement("child"));
    root->InsertEndChild(doc.NewElement("child"));

    EXPECT_EQ(root->ChildElementCount(), 3);
}

// Test ChildElementCount with a specific name filter
TEST_F(XMLNodeTest_182, ChildElementCount_WithNameFilter_ReturnsFilteredCount_182) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    root->InsertEndChild(doc.NewElement("apple"));
    root->InsertEndChild(doc.NewElement("banana"));
    root->InsertEndChild(doc.NewElement("apple"));
    root->InsertEndChild(doc.NewElement("cherry"));
    root->InsertEndChild(doc.NewElement("apple"));

    EXPECT_EQ(root->ChildElementCount("apple"), 3);
    EXPECT_EQ(root->ChildElementCount("banana"), 1);
    EXPECT_EQ(root->ChildElementCount("cherry"), 1);
}

// Test ChildElementCount with a name that matches no children
TEST_F(XMLNodeTest_182, ChildElementCount_NameNotFound_ReturnsZero_182) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    root->InsertEndChild(doc.NewElement("child1"));
    root->InsertEndChild(doc.NewElement("child2"));

    EXPECT_EQ(root->ChildElementCount("nonexistent"), 0);
}

// Test ChildElementCount with nullptr (should count all elements)
TEST_F(XMLNodeTest_182, ChildElementCount_NullName_CountsAll_182) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    root->InsertEndChild(doc.NewElement("a"));
    root->InsertEndChild(doc.NewElement("b"));
    root->InsertEndChild(doc.NewElement("c"));

    EXPECT_EQ(root->ChildElementCount(nullptr), 3);
    EXPECT_EQ(root->ChildElementCount(), 3);
}

// Test ChildElementCount on document node
TEST_F(XMLNodeTest_182, ChildElementCount_OnDocument_182) {
    doc.InsertEndChild(doc.NewElement("root"));
    EXPECT_EQ(doc.ChildElementCount(), 1);
}

// Test ChildElementCount doesn't count text nodes
TEST_F(XMLNodeTest_182, ChildElementCount_IgnoresNonElements_182) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    root->InsertEndChild(doc.NewElement("child"));
    root->InsertEndChild(doc.NewComment("this is a comment"));
    root->InsertEndChild(doc.NewElement("child"));
    root->InsertEndChild(doc.NewText("some text"));
    root->InsertEndChild(doc.NewElement("child"));

    EXPECT_EQ(root->ChildElementCount(), 3);
    EXPECT_EQ(root->ChildElementCount("child"), 3);
}

// Test ChildElementCount with single child
TEST_F(XMLNodeTest_182, ChildElementCount_SingleChild_182) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    root->InsertEndChild(doc.NewElement("only"));

    EXPECT_EQ(root->ChildElementCount(), 1);
    EXPECT_EQ(root->ChildElementCount("only"), 1);
}

// Test ChildElementCount doesn't count grandchildren
TEST_F(XMLNodeTest_182, ChildElementCount_DoesNotCountGrandchildren_182) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);

    child->InsertEndChild(doc.NewElement("grandchild"));
    child->InsertEndChild(doc.NewElement("grandchild"));

    EXPECT_EQ(root->ChildElementCount(), 1);
    EXPECT_EQ(root->ChildElementCount("child"), 1);
    EXPECT_EQ(root->ChildElementCount("grandchild"), 0);
    EXPECT_EQ(child->ChildElementCount("grandchild"), 2);
}

// Test FirstChildElement returns correct element
TEST_F(XMLNodeTest_182, FirstChildElement_ReturnsFirstMatch_182) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* first = doc.NewElement("item");
    first->SetAttribute("id", 1);
    root->InsertEndChild(first);

    XMLElement* second = doc.NewElement("item");
    second->SetAttribute("id", 2);
    root->InsertEndChild(second);

    const XMLElement* found = root->FirstChildElement("item");
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->IntAttribute("id"), 1);
}

// Test LastChildElement returns correct element
TEST_F(XMLNodeTest_182, LastChildElement_ReturnsLastMatch_182) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* first = doc.NewElement("item");
    first->SetAttribute("id", 1);
    root->InsertEndChild(first);

    XMLElement* second = doc.NewElement("item");
    second->SetAttribute("id", 2);
    root->InsertEndChild(second);

    const XMLElement* found = root->LastChildElement("item");
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->IntAttribute("id"), 2);
}

// Test NextSiblingElement
TEST_F(XMLNodeTest_182, NextSiblingElement_TraverseSiblings_182) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    root->InsertEndChild(doc.NewElement("a"));
    root->InsertEndChild(doc.NewElement("b"));
    root->InsertEndChild(doc.NewElement("c"));

    const XMLElement* e = root->FirstChildElement();
    ASSERT_NE(e, nullptr);
    EXPECT_STREQ(e->Value(), "a");

    e = e->NextSiblingElement();
    ASSERT_NE(e, nullptr);
    EXPECT_STREQ(e->Value(), "b");

    e = e->NextSiblingElement();
    ASSERT_NE(e, nullptr);
    EXPECT_STREQ(e->Value(), "c");

    e = e->NextSiblingElement();
    EXPECT_EQ(e, nullptr);
}

// Test PreviousSiblingElement
TEST_F(XMLNodeTest_182, PreviousSiblingElement_TraverseBackwards_182) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    root->InsertEndChild(doc.NewElement("a"));
    root->InsertEndChild(doc.NewElement("b"));
    root->InsertEndChild(doc.NewElement("c"));

    const XMLElement* e = root->LastChildElement();
    ASSERT_NE(e, nullptr);
    EXPECT_STREQ(e->Value(), "c");

    e = e->PreviousSiblingElement();
    ASSERT_NE(e, nullptr);
    EXPECT_STREQ(e->Value(), "b");

    e = e->PreviousSiblingElement();
    ASSERT_NE(e, nullptr);
    EXPECT_STREQ(e->Value(), "a");

    e = e->PreviousSiblingElement();
    EXPECT_EQ(e, nullptr);
}

// Test InsertEndChild
TEST_F(XMLNodeTest_182, InsertEndChild_AppendsChild_182) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child1 = doc.NewElement("first");
    XMLElement* child2 = doc.NewElement("second");

    root->InsertEndChild(child1);
    root->InsertEndChild(child2);

    EXPECT_STREQ(root->FirstChildElement()->Value(), "first");
    EXPECT_STREQ(root->LastChildElement()->Value(), "second");
}

// Test InsertFirstChild
TEST_F(XMLNodeTest_182, InsertFirstChild_PrependsChild_182) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child1 = doc.NewElement("first");
    XMLElement* child2 = doc.NewElement("second");

    root->InsertEndChild(child1);
    root->InsertFirstChild(child2);

    EXPECT_STREQ(root->FirstChildElement()->Value(), "second");
    EXPECT_STREQ(root->LastChildElement()->Value(), "first");
}

// Test InsertAfterChild
TEST_F(XMLNodeTest_182, InsertAfterChild_InsertsInCorrectPosition_182) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child1 = doc.NewElement("first");
    XMLElement* child3 = doc.NewElement("third");
    root->InsertEndChild(child1);
    root->InsertEndChild(child3);

    XMLElement* child2 = doc.NewElement("second");
    root->InsertAfterChild(child1, child2);

    const XMLElement* e = root->FirstChildElement();
    ASSERT_NE(e, nullptr);
    EXPECT_STREQ(e->Value(), "first");
    e = e->NextSiblingElement();
    ASSERT_NE(e, nullptr);
    EXPECT_STREQ(e->Value(), "second");
    e = e->NextSiblingElement();
    ASSERT_NE(e, nullptr);
    EXPECT_STREQ(e->Value(), "third");
}

// Test DeleteChildren
TEST_F(XMLNodeTest_182, DeleteChildren_RemovesAllChildren_182) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    root->InsertEndChild(doc.NewElement("a"));
    root->InsertEndChild(doc.NewElement("b"));
    root->InsertEndChild(doc.NewElement("c"));

    EXPECT_EQ(root->ChildElementCount(), 3);

    root->DeleteChildren();

    EXPECT_EQ(root->ChildElementCount(), 0);
    EXPECT_TRUE(root->NoChildren());
}

// Test DeleteChild
TEST_F(XMLNodeTest_182, DeleteChild_RemovesSpecificChild_182) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child1 = doc.NewElement("a");
    XMLElement* child2 = doc.NewElement("b");
    XMLElement* child3 = doc.NewElement("c");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    root->InsertEndChild(child3);

    root->DeleteChild(child2);

    EXPECT_EQ(root->ChildElementCount(), 2);
    EXPECT_STREQ(root->FirstChildElement()->Value(), "a");
    EXPECT_STREQ(root->LastChildElement()->Value(), "c");
}

// Test NoChildren
TEST_F(XMLNodeTest_182, NoChildren_ReturnsTrueWhenEmpty_182) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    EXPECT_TRUE(root->NoChildren());

    root->InsertEndChild(doc.NewElement("child"));
    EXPECT_FALSE(root->NoChildren());
}

// Test Value and SetValue
TEST_F(XMLNodeTest_182, Value_ReturnsNodeValue_182) {
    XMLElement* root = doc.NewElement("myRoot");
    doc.InsertEndChild(root);

    EXPECT_STREQ(root->Value(), "myRoot");
}

// Test Parent
TEST_F(XMLNodeTest_182, Parent_ReturnsParentNode_182) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);

    EXPECT_EQ(child->Parent(), root);
    EXPECT_EQ(root->Parent(), &doc);
}

// Test DeepClone
TEST_F(XMLNodeTest_182, DeepClone_ClonesEntireSubtree_182) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child = doc.NewElement("child");
    child->SetAttribute("attr", "value");
    root->InsertEndChild(child);

    XMLElement* grandchild = doc.NewElement("grandchild");
    child->InsertEndChild(grandchild);

    XMLDocument targetDoc;
    XMLNode* cloned = root->DeepClone(&targetDoc);
    targetDoc.InsertEndChild(cloned);

    ASSERT_NE(cloned, nullptr);
    EXPECT_STREQ(cloned->Value(), "root");

    const XMLElement* clonedChild = cloned->FirstChildElement("child");
    ASSERT_NE(clonedChild, nullptr);
    EXPECT_STREQ(clonedChild->Attribute("attr"), "value");

    const XMLElement* clonedGrandchild = clonedChild->FirstChildElement("grandchild");
    ASSERT_NE(clonedGrandchild, nullptr);
}

// Test GetDocument
TEST_F(XMLNodeTest_182, GetDocument_ReturnsOwningDocument_182) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    EXPECT_EQ(root->GetDocument(), &doc);
}

// Test UserData
TEST_F(XMLNodeTest_182, UserData_SetAndGet_182) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    int data = 42;
    root->SetUserData(&data);
    EXPECT_EQ(root->GetUserData(), &data);
}

// Test UserData default is null
TEST_F(XMLNodeTest_182, UserData_DefaultNull_182) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    EXPECT_EQ(root->GetUserData(), nullptr);
}

// Test ChildElementCount with empty string filter
TEST_F(XMLNodeTest_182, ChildElementCount_EmptyStringFilter_182) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    root->InsertEndChild(doc.NewElement("child"));
    root->InsertEndChild(doc.NewElement("child"));

    // Empty string should not match "child"
    EXPECT_EQ(root->ChildElementCount(""), 0);
}

// Test ChildElementCount after deleting children
TEST_F(XMLNodeTest_182, ChildElementCount_AfterDelete_ReturnsUpdatedCount_182) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* c1 = doc.NewElement("item");
    XMLElement* c2 = doc.NewElement("item");
    XMLElement* c3 = doc.NewElement("item");
    root->InsertEndChild(c1);
    root->InsertEndChild(c2);
    root->InsertEndChild(c3);

    EXPECT_EQ(root->ChildElementCount("item"), 3);

    root->DeleteChild(c2);
    EXPECT_EQ(root->ChildElementCount("item"), 2);

    root->DeleteChildren();
    EXPECT_EQ(root->ChildElementCount("item"), 0);
}

// Test ChildElementCount with mixed element names
TEST_F(XMLNodeTest_182, ChildElementCount_MixedNames_182) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    root->InsertEndChild(doc.NewElement("alpha"));
    root->InsertEndChild(doc.NewElement("beta"));
    root->InsertEndChild(doc.NewElement("alpha"));
    root->InsertEndChild(doc.NewElement("gamma"));
    root->InsertEndChild(doc.NewElement("beta"));

    EXPECT_EQ(root->ChildElementCount(), 5);
    EXPECT_EQ(root->ChildElementCount("alpha"), 2);
    EXPECT_EQ(root->ChildElementCount("beta"), 2);
    EXPECT_EQ(root->ChildElementCount("gamma"), 1);
    EXPECT_EQ(root->ChildElementCount("delta"), 0);
}

// Test from XML parsing
TEST_F(XMLNodeTest_182, ChildElementCount_FromParsedXML_182) {
    const char* xml = "<root><item/><item/><other/><item/></root>";
    doc.Parse(xml);
    ASSERT_EQ(doc.ErrorID(), 0);

    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    EXPECT_EQ(root->ChildElementCount(), 4);
    EXPECT_EQ(root->ChildElementCount("item"), 3);
    EXPECT_EQ(root->ChildElementCount("other"), 1);
}

// Test LinkEndChild (alias for InsertEndChild)
TEST_F(XMLNodeTest_182, LinkEndChild_Works_182) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child = doc.NewElement("linked");
    root->LinkEndChild(child);

    EXPECT_EQ(root->ChildElementCount(), 1);
    EXPECT_STREQ(root->FirstChildElement()->Value(), "linked");
}

// Test FirstChild and LastChild
TEST_F(XMLNodeTest_182, FirstChildLastChild_182) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    root->InsertEndChild(doc.NewElement("first"));
    root->InsertEndChild(doc.NewElement("middle"));
    root->InsertEndChild(doc.NewElement("last"));

    ASSERT_NE(root->FirstChild(), nullptr);
    EXPECT_STREQ(root->FirstChild()->Value(), "first");

    ASSERT_NE(root->LastChild(), nullptr);
    EXPECT_STREQ(root->LastChild()->Value(), "last");
}

// Test FirstChildElement and LastChildElement with nullptr
TEST_F(XMLNodeTest_182, FirstLastChildElement_NullReturnsFirstLast_182) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    EXPECT_EQ(root->FirstChildElement(nullptr), nullptr);
    EXPECT_EQ(root->LastChildElement(nullptr), nullptr);

    root->InsertEndChild(doc.NewElement("a"));
    root->InsertEndChild(doc.NewElement("b"));

    EXPECT_STREQ(root->FirstChildElement(nullptr)->Value(), "a");
    EXPECT_STREQ(root->LastChildElement(nullptr)->Value(), "b");
}

// Test that ToElement works
TEST_F(XMLNodeTest_182, ToElement_ReturnsNonNullForElement_182) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    EXPECT_NE(root->ToElement(), nullptr);
    EXPECT_EQ(root->ToText(), nullptr);
    EXPECT_EQ(root->ToComment(), nullptr);
    EXPECT_EQ(root->ToDocument(), nullptr);
}

// Test NextSibling and PreviousSibling
TEST_F(XMLNodeTest_182, NextPreviousSibling_182) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* a = doc.NewElement("a");
    XMLElement* b = doc.NewElement("b");
    root->InsertEndChild(a);
    root->InsertEndChild(b);

    EXPECT_EQ(a->NextSibling(), b);
    EXPECT_EQ(b->PreviousSibling(), a);
    EXPECT_EQ(a->PreviousSibling(), nullptr);
    EXPECT_EQ(b->NextSibling(), nullptr);
}
