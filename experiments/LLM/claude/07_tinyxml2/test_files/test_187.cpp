#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLNodeTest_187 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that a newly created document has no children
TEST_F(XMLNodeTest_187, NewDocumentHasNoChildren_187) {
    EXPECT_TRUE(doc.NoChildren());
    EXPECT_EQ(doc.FirstChild(), nullptr);
    EXPECT_EQ(doc.LastChild(), nullptr);
}

// Test DeleteChildren on a document with no children
TEST_F(XMLNodeTest_187, DeleteChildrenOnEmptyDocument_187) {
    doc.DeleteChildren();
    EXPECT_TRUE(doc.NoChildren());
    EXPECT_EQ(doc.FirstChild(), nullptr);
    EXPECT_EQ(doc.LastChild(), nullptr);
}

// Test DeleteChildren removes a single child
TEST_F(XMLNodeTest_187, DeleteChildrenRemovesSingleChild_187) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_FALSE(doc.NoChildren());

    doc.DeleteChildren();
    EXPECT_TRUE(doc.NoChildren());
    EXPECT_EQ(doc.FirstChild(), nullptr);
    EXPECT_EQ(doc.LastChild(), nullptr);
}

// Test DeleteChildren removes multiple children
TEST_F(XMLNodeTest_187, DeleteChildrenRemovesMultipleChildren_187) {
    doc.InsertEndChild(doc.NewElement("child1"));
    doc.InsertEndChild(doc.NewElement("child2"));
    doc.InsertEndChild(doc.NewElement("child3"));
    EXPECT_EQ(doc.ChildElementCount(), 3);

    doc.DeleteChildren();
    EXPECT_TRUE(doc.NoChildren());
    EXPECT_EQ(doc.ChildElementCount(), 0);
}

// Test DeleteChildren removes nested children (deep hierarchy)
TEST_F(XMLNodeTest_187, DeleteChildrenRemovesNestedChildren_187) {
    XMLElement* parent = doc.NewElement("parent");
    XMLElement* child = doc.NewElement("child");
    XMLElement* grandchild = doc.NewElement("grandchild");
    child->InsertEndChild(grandchild);
    parent->InsertEndChild(child);
    doc.InsertEndChild(parent);

    EXPECT_FALSE(doc.NoChildren());

    doc.DeleteChildren();
    EXPECT_TRUE(doc.NoChildren());
    EXPECT_EQ(doc.FirstChild(), nullptr);
}

// Test InsertEndChild adds a child
TEST_F(XMLNodeTest_187, InsertEndChildAddsChild_187) {
    XMLElement* elem = doc.NewElement("test");
    XMLNode* result = doc.InsertEndChild(elem);
    EXPECT_NE(result, nullptr);
    EXPECT_FALSE(doc.NoChildren());
    EXPECT_EQ(doc.FirstChild(), elem);
    EXPECT_EQ(doc.LastChild(), elem);
}

// Test InsertFirstChild adds child at beginning
TEST_F(XMLNodeTest_187, InsertFirstChildAddsAtBeginning_187) {
    XMLElement* elem1 = doc.NewElement("first");
    XMLElement* elem2 = doc.NewElement("second");
    doc.InsertEndChild(elem1);
    doc.InsertFirstChild(elem2);

    EXPECT_EQ(doc.FirstChild(), elem2);
    EXPECT_EQ(doc.LastChild(), elem1);
}

// Test InsertAfterChild inserts in middle
TEST_F(XMLNodeTest_187, InsertAfterChildInsertsInMiddle_187) {
    XMLElement* elem1 = doc.NewElement("first");
    XMLElement* elem2 = doc.NewElement("second");
    XMLElement* elem3 = doc.NewElement("middle");
    doc.InsertEndChild(elem1);
    doc.InsertEndChild(elem2);
    doc.InsertAfterChild(elem1, elem3);

    EXPECT_EQ(doc.FirstChild(), elem1);
    EXPECT_EQ(doc.FirstChild()->NextSibling(), elem3);
    EXPECT_EQ(doc.LastChild(), elem2);
}

// Test DeleteChild removes specific child
TEST_F(XMLNodeTest_187, DeleteChildRemovesSpecificChild_187) {
    XMLElement* elem1 = doc.NewElement("child1");
    XMLElement* elem2 = doc.NewElement("child2");
    XMLElement* elem3 = doc.NewElement("child3");
    doc.InsertEndChild(elem1);
    doc.InsertEndChild(elem2);
    doc.InsertEndChild(elem3);

    doc.DeleteChild(elem2);
    EXPECT_EQ(doc.ChildElementCount(), 2);
    EXPECT_EQ(doc.FirstChildElement("child2"), nullptr);
}

// Test ChildElementCount returns correct count
TEST_F(XMLNodeTest_187, ChildElementCountReturnsCorrectCount_187) {
    EXPECT_EQ(doc.ChildElementCount(), 0);

    doc.InsertEndChild(doc.NewElement("a"));
    EXPECT_EQ(doc.ChildElementCount(), 1);

    doc.InsertEndChild(doc.NewElement("b"));
    EXPECT_EQ(doc.ChildElementCount(), 2);

    doc.InsertEndChild(doc.NewElement("c"));
    EXPECT_EQ(doc.ChildElementCount(), 3);
}

// Test ChildElementCount with name filter
TEST_F(XMLNodeTest_187, ChildElementCountWithNameFilter_187) {
    doc.InsertEndChild(doc.NewElement("apple"));
    doc.InsertEndChild(doc.NewElement("banana"));
    doc.InsertEndChild(doc.NewElement("apple"));

    EXPECT_EQ(doc.ChildElementCount("apple"), 2);
    EXPECT_EQ(doc.ChildElementCount("banana"), 1);
    EXPECT_EQ(doc.ChildElementCount("cherry"), 0);
}

// Test NoChildren returns true when empty
TEST_F(XMLNodeTest_187, NoChildrenReturnsTrueWhenEmpty_187) {
    EXPECT_TRUE(doc.NoChildren());
}

// Test NoChildren returns false when has children
TEST_F(XMLNodeTest_187, NoChildrenReturnsFalseWhenHasChildren_187) {
    doc.InsertEndChild(doc.NewElement("child"));
    EXPECT_FALSE(doc.NoChildren());
}

// Test FirstChildElement with name
TEST_F(XMLNodeTest_187, FirstChildElementWithName_187) {
    doc.InsertEndChild(doc.NewElement("alpha"));
    doc.InsertEndChild(doc.NewElement("beta"));
    doc.InsertEndChild(doc.NewElement("alpha"));

    XMLElement* found = doc.FirstChildElement("beta");
    ASSERT_NE(found, nullptr);
    EXPECT_STREQ(found->Value(), "beta");
}

// Test FirstChildElement returns nullptr when not found
TEST_F(XMLNodeTest_187, FirstChildElementReturnsNullWhenNotFound_187) {
    doc.InsertEndChild(doc.NewElement("alpha"));
    EXPECT_EQ(doc.FirstChildElement("nonexistent"), nullptr);
}

// Test LastChildElement with name
TEST_F(XMLNodeTest_187, LastChildElementWithName_187) {
    XMLElement* e1 = doc.NewElement("item");
    XMLElement* e2 = doc.NewElement("other");
    XMLElement* e3 = doc.NewElement("item");
    doc.InsertEndChild(e1);
    doc.InsertEndChild(e2);
    doc.InsertEndChild(e3);

    const XMLElement* last = doc.LastChildElement("item");
    ASSERT_NE(last, nullptr);
    EXPECT_EQ(last, e3);
}

// Test NextSiblingElement
TEST_F(XMLNodeTest_187, NextSiblingElement_187) {
    XMLElement* e1 = doc.NewElement("a");
    XMLElement* e2 = doc.NewElement("b");
    XMLElement* e3 = doc.NewElement("c");
    doc.InsertEndChild(e1);
    doc.InsertEndChild(e2);
    doc.InsertEndChild(e3);

    EXPECT_EQ(e1->NextSiblingElement(), e2);
    EXPECT_EQ(e2->NextSiblingElement(), e3);
    EXPECT_EQ(e3->NextSiblingElement(), nullptr);
}

// Test PreviousSiblingElement
TEST_F(XMLNodeTest_187, PreviousSiblingElement_187) {
    XMLElement* e1 = doc.NewElement("a");
    XMLElement* e2 = doc.NewElement("b");
    XMLElement* e3 = doc.NewElement("c");
    doc.InsertEndChild(e1);
    doc.InsertEndChild(e2);
    doc.InsertEndChild(e3);

    EXPECT_EQ(e3->PreviousSiblingElement(), e2);
    EXPECT_EQ(e2->PreviousSiblingElement(), e1);
    EXPECT_EQ(e1->PreviousSiblingElement(), nullptr);
}

// Test SetValue and Value
TEST_F(XMLNodeTest_187, SetValueAndValue_187) {
    XMLElement* elem = doc.NewElement("original");
    doc.InsertEndChild(elem);
    EXPECT_STREQ(elem->Value(), "original");

    elem->SetValue("modified", false);
    EXPECT_STREQ(elem->Value(), "modified");
}

// Test UserData
TEST_F(XMLNodeTest_187, UserData_187) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);

    EXPECT_EQ(elem->GetUserData(), nullptr);

    int data = 42;
    elem->SetUserData(&data);
    EXPECT_EQ(elem->GetUserData(), &data);
}

// Test DeepClone
TEST_F(XMLNodeTest_187, DeepClone_187) {
    XMLElement* parent = doc.NewElement("parent");
    XMLElement* child = doc.NewElement("child");
    parent->InsertEndChild(child);
    doc.InsertEndChild(parent);

    XMLDocument targetDoc;
    XMLNode* cloned = parent->DeepClone(&targetDoc);
    ASSERT_NE(cloned, nullptr);
    targetDoc.InsertEndChild(cloned);

    EXPECT_STREQ(cloned->Value(), "parent");
    EXPECT_FALSE(cloned->NoChildren());
    EXPECT_STREQ(cloned->FirstChildElement()->Value(), "child");
}

// Test DeleteChildren called multiple times
TEST_F(XMLNodeTest_187, DeleteChildrenCalledMultipleTimes_187) {
    doc.InsertEndChild(doc.NewElement("a"));
    doc.InsertEndChild(doc.NewElement("b"));

    doc.DeleteChildren();
    EXPECT_TRUE(doc.NoChildren());

    // Calling again should be safe
    doc.DeleteChildren();
    EXPECT_TRUE(doc.NoChildren());
}

// Test DeleteChildren on element with mixed content
TEST_F(XMLNodeTest_187, DeleteChildrenOnElementWithMixedContent_187) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    root->InsertEndChild(doc.NewElement("elem1"));
    root->InsertEndChild(doc.NewComment("a comment"));
    root->InsertEndChild(doc.NewElement("elem2"));
    root->InsertEndChild(doc.NewText("some text"));

    EXPECT_FALSE(root->NoChildren());

    root->DeleteChildren();
    EXPECT_TRUE(root->NoChildren());
    EXPECT_EQ(root->FirstChild(), nullptr);
    EXPECT_EQ(root->LastChild(), nullptr);
}

// Test that after DeleteChildren, parent still exists in document
TEST_F(XMLNodeTest_187, DeleteChildrenParentStillExists_187) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    root->InsertEndChild(doc.NewElement("child1"));
    root->InsertEndChild(doc.NewElement("child2"));

    root->DeleteChildren();
    EXPECT_TRUE(root->NoChildren());

    // root should still be a child of doc
    EXPECT_EQ(doc.FirstChild(), root);
    EXPECT_FALSE(doc.NoChildren());
}

// Test LinkEndChild (alias for InsertEndChild)
TEST_F(XMLNodeTest_187, LinkEndChild_187) {
    XMLElement* elem = doc.NewElement("linked");
    XMLNode* result = doc.LinkEndChild(elem);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(doc.FirstChild(), elem);
}

// Test GetDocument returns the owning document
TEST_F(XMLNodeTest_187, GetDocumentReturnsOwningDocument_187) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_EQ(elem->GetDocument(), &doc);
}

// Test Parent returns correct parent
TEST_F(XMLNodeTest_187, ParentReturnsCorrectParent_187) {
    XMLElement* parent = doc.NewElement("parent");
    XMLElement* child = doc.NewElement("child");
    parent->InsertEndChild(child);
    doc.InsertEndChild(parent);

    EXPECT_EQ(child->Parent(), parent);
    EXPECT_EQ(parent->Parent(), &doc);
}

// Test that deleting the first child updates FirstChild pointer
TEST_F(XMLNodeTest_187, DeleteFirstChildUpdatesFirstChild_187) {
    XMLElement* e1 = doc.NewElement("first");
    XMLElement* e2 = doc.NewElement("second");
    doc.InsertEndChild(e1);
    doc.InsertEndChild(e2);

    doc.DeleteChild(e1);
    EXPECT_EQ(doc.FirstChild(), e2);
    EXPECT_EQ(doc.LastChild(), e2);
}

// Test that deleting the last child updates LastChild pointer
TEST_F(XMLNodeTest_187, DeleteLastChildUpdatesLastChild_187) {
    XMLElement* e1 = doc.NewElement("first");
    XMLElement* e2 = doc.NewElement("second");
    doc.InsertEndChild(e1);
    doc.InsertEndChild(e2);

    doc.DeleteChild(e2);
    EXPECT_EQ(doc.FirstChild(), e1);
    EXPECT_EQ(doc.LastChild(), e1);
}

// Test parsing XML and then DeleteChildren
TEST_F(XMLNodeTest_187, ParseXMLThenDeleteChildren_187) {
    const char* xml = "<root><a/><b/><c/></root>";
    doc.Parse(xml);
    EXPECT_FALSE(doc.Error());

    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->ChildElementCount(), 3);

    root->DeleteChildren();
    EXPECT_TRUE(root->NoChildren());
    EXPECT_EQ(root->ChildElementCount(), 0);
}

// Test DeleteChildren on deeply nested structure
TEST_F(XMLNodeTest_187, DeleteChildrenOnDeeplyNestedStructure_187) {
    XMLElement* level1 = doc.NewElement("l1");
    XMLElement* level2 = doc.NewElement("l2");
    XMLElement* level3 = doc.NewElement("l3");
    XMLElement* level4 = doc.NewElement("l4");

    level3->InsertEndChild(level4);
    level2->InsertEndChild(level3);
    level1->InsertEndChild(level2);
    doc.InsertEndChild(level1);

    level1->DeleteChildren();
    EXPECT_TRUE(level1->NoChildren());
}

// Test ToElement on an element node
TEST_F(XMLNodeTest_187, ToElementOnElement_187) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_NE(elem->ToElement(), nullptr);
    EXPECT_EQ(elem->ToComment(), nullptr);
    EXPECT_EQ(elem->ToText(), nullptr);
    EXPECT_EQ(elem->ToDocument(), nullptr);
    EXPECT_EQ(elem->ToDeclaration(), nullptr);
    EXPECT_EQ(elem->ToUnknown(), nullptr);
}

// Test NextSiblingElement with name filter
TEST_F(XMLNodeTest_187, NextSiblingElementWithNameFilter_187) {
    XMLElement* e1 = doc.NewElement("a");
    XMLElement* e2 = doc.NewElement("b");
    XMLElement* e3 = doc.NewElement("a");
    doc.InsertEndChild(e1);
    doc.InsertEndChild(e2);
    doc.InsertEndChild(e3);

    EXPECT_EQ(e1->NextSiblingElement("a"), e3);
    EXPECT_EQ(e1->NextSiblingElement("b"), e2);
    EXPECT_EQ(e1->NextSiblingElement("c"), nullptr);
}

// Test PreviousSiblingElement with name filter
TEST_F(XMLNodeTest_187, PreviousSiblingElementWithNameFilter_187) {
    XMLElement* e1 = doc.NewElement("a");
    XMLElement* e2 = doc.NewElement("b");
    XMLElement* e3 = doc.NewElement("a");
    doc.InsertEndChild(e1);
    doc.InsertEndChild(e2);
    doc.InsertEndChild(e3);

    EXPECT_EQ(e3->PreviousSiblingElement("a"), e1);
    EXPECT_EQ(e3->PreviousSiblingElement("b"), e2);
    EXPECT_EQ(e3->PreviousSiblingElement("c"), nullptr);
}
