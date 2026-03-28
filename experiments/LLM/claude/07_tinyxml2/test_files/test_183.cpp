#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLNodeTest_183 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// Test ChildElementCount on empty document/node
TEST_F(XMLNodeTest_183, ChildElementCount_EmptyNode_ReturnsZero_183) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    EXPECT_EQ(0, root->ChildElementCount());
}

// Test ChildElementCount with one child element
TEST_F(XMLNodeTest_183, ChildElementCount_OneChild_ReturnsOne_183) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);
    
    EXPECT_EQ(1, root->ChildElementCount());
}

// Test ChildElementCount with multiple child elements
TEST_F(XMLNodeTest_183, ChildElementCount_MultipleChildren_ReturnsCorrectCount_183) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    for (int i = 0; i < 5; i++) {
        XMLElement* child = doc.NewElement("child");
        root->InsertEndChild(child);
    }
    
    EXPECT_EQ(5, root->ChildElementCount());
}

// Test ChildElementCount ignores non-element children (text nodes, comments)
TEST_F(XMLNodeTest_183, ChildElementCount_MixedChildren_CountsOnlyElements_183) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* child1 = doc.NewElement("child1");
    root->InsertEndChild(child1);
    
    XMLComment* comment = doc.NewComment("this is a comment");
    root->InsertEndChild(comment);
    
    XMLElement* child2 = doc.NewElement("child2");
    root->InsertEndChild(child2);
    
    XMLText* text = doc.NewText("some text");
    root->InsertEndChild(text);
    
    EXPECT_EQ(2, root->ChildElementCount());
}

// Test ChildElementCount with named filter
TEST_F(XMLNodeTest_183, ChildElementCount_WithNameFilter_CountsMatchingOnly_183) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* a1 = doc.NewElement("apple");
    root->InsertEndChild(a1);
    
    XMLElement* b1 = doc.NewElement("banana");
    root->InsertEndChild(b1);
    
    XMLElement* a2 = doc.NewElement("apple");
    root->InsertEndChild(a2);
    
    XMLElement* c1 = doc.NewElement("cherry");
    root->InsertEndChild(c1);
    
    EXPECT_EQ(4, root->ChildElementCount());
    EXPECT_EQ(2, root->ChildElementCount("apple"));
    EXPECT_EQ(1, root->ChildElementCount("banana"));
    EXPECT_EQ(1, root->ChildElementCount("cherry"));
}

// Test ChildElementCount with named filter that matches no children
TEST_F(XMLNodeTest_183, ChildElementCount_WithNameFilter_NoMatch_ReturnsZero_183) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);
    
    EXPECT_EQ(0, root->ChildElementCount("nonexistent"));
}

// Test ChildElementCount on document node
TEST_F(XMLNodeTest_183, ChildElementCount_OnDocument_183) {
    doc.Parse("<root><a/><b/><c/></root>");
    EXPECT_EQ(1, doc.ChildElementCount());
}

// Test ChildElementCount does not count grandchildren
TEST_F(XMLNodeTest_183, ChildElementCount_DoesNotCountGrandchildren_183) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);
    
    XMLElement* grandchild1 = doc.NewElement("grandchild");
    child->InsertEndChild(grandchild1);
    
    XMLElement* grandchild2 = doc.NewElement("grandchild");
    child->InsertEndChild(grandchild2);
    
    EXPECT_EQ(1, root->ChildElementCount());
    EXPECT_EQ(2, child->ChildElementCount());
}

// Test InsertEndChild and ChildElementCount consistency
TEST_F(XMLNodeTest_183, InsertEndChild_IncreasesChildElementCount_183) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    EXPECT_EQ(0, root->ChildElementCount());
    
    XMLElement* c1 = doc.NewElement("c1");
    root->InsertEndChild(c1);
    EXPECT_EQ(1, root->ChildElementCount());
    
    XMLElement* c2 = doc.NewElement("c2");
    root->InsertEndChild(c2);
    EXPECT_EQ(2, root->ChildElementCount());
}

// Test InsertFirstChild and ChildElementCount
TEST_F(XMLNodeTest_183, InsertFirstChild_IncreasesChildElementCount_183) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* c1 = doc.NewElement("c1");
    root->InsertFirstChild(c1);
    EXPECT_EQ(1, root->ChildElementCount());
    
    XMLElement* c2 = doc.NewElement("c2");
    root->InsertFirstChild(c2);
    EXPECT_EQ(2, root->ChildElementCount());
}

// Test DeleteChildren reduces ChildElementCount to zero
TEST_F(XMLNodeTest_183, DeleteChildren_ReducesCountToZero_183) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    for (int i = 0; i < 3; i++) {
        XMLElement* child = doc.NewElement("child");
        root->InsertEndChild(child);
    }
    
    EXPECT_EQ(3, root->ChildElementCount());
    root->DeleteChildren();
    EXPECT_EQ(0, root->ChildElementCount());
}

// Test DeleteChild reduces ChildElementCount by one
TEST_F(XMLNodeTest_183, DeleteChild_ReducesCountByOne_183) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* c1 = doc.NewElement("c1");
    root->InsertEndChild(c1);
    XMLElement* c2 = doc.NewElement("c2");
    root->InsertEndChild(c2);
    
    EXPECT_EQ(2, root->ChildElementCount());
    root->DeleteChild(c1);
    EXPECT_EQ(1, root->ChildElementCount());
}

// Test NoChildren is consistent with ChildElementCount
TEST_F(XMLNodeTest_183, NoChildren_ConsistentWithChildElementCount_183) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    EXPECT_TRUE(root->NoChildren());
    EXPECT_EQ(0, root->ChildElementCount());
    
    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);
    
    EXPECT_FALSE(root->NoChildren());
    EXPECT_EQ(1, root->ChildElementCount());
}

// Test FirstChildElement and LastChildElement with ChildElementCount
TEST_F(XMLNodeTest_183, FirstAndLastChildElement_183) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    EXPECT_EQ(nullptr, root->FirstChildElement());
    EXPECT_EQ(nullptr, root->LastChildElement());
    
    XMLElement* c1 = doc.NewElement("first");
    root->InsertEndChild(c1);
    XMLElement* c2 = doc.NewElement("middle");
    root->InsertEndChild(c2);
    XMLElement* c3 = doc.NewElement("last");
    root->InsertEndChild(c3);
    
    EXPECT_EQ(3, root->ChildElementCount());
    EXPECT_STREQ("first", root->FirstChildElement()->Value());
    EXPECT_STREQ("last", root->LastChildElement()->Value());
}

// Test FirstChildElement with name filter
TEST_F(XMLNodeTest_183, FirstChildElement_WithNameFilter_183) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* c1 = doc.NewElement("alpha");
    root->InsertEndChild(c1);
    XMLElement* c2 = doc.NewElement("beta");
    root->InsertEndChild(c2);
    XMLElement* c3 = doc.NewElement("alpha");
    root->InsertEndChild(c3);
    
    EXPECT_STREQ("alpha", root->FirstChildElement("alpha")->Value());
    EXPECT_STREQ("beta", root->FirstChildElement("beta")->Value());
    EXPECT_EQ(nullptr, root->FirstChildElement("gamma"));
}

// Test Value and SetValue
TEST_F(XMLNodeTest_183, Value_SetValue_183) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    EXPECT_STREQ("root", root->Value());
    
    root->SetValue("newroot", false);
    EXPECT_STREQ("newroot", root->Value());
}

// Test InsertAfterChild
TEST_F(XMLNodeTest_183, InsertAfterChild_183) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* c1 = doc.NewElement("c1");
    root->InsertEndChild(c1);
    XMLElement* c3 = doc.NewElement("c3");
    root->InsertEndChild(c3);
    
    XMLElement* c2 = doc.NewElement("c2");
    root->InsertAfterChild(c1, c2);
    
    EXPECT_EQ(3, root->ChildElementCount());
    
    // Verify order: c1, c2, c3
    XMLElement* e = root->FirstChildElement();
    EXPECT_STREQ("c1", e->Value());
    e = e->NextSiblingElement();
    EXPECT_STREQ("c2", e->Value());
    e = e->NextSiblingElement();
    EXPECT_STREQ("c3", e->Value());
    EXPECT_EQ(nullptr, e->NextSiblingElement());
}

// Test DeepClone preserves child element count
TEST_F(XMLNodeTest_183, DeepClone_PreservesChildElementCount_183) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* c1 = doc.NewElement("c1");
    root->InsertEndChild(c1);
    XMLElement* c2 = doc.NewElement("c2");
    root->InsertEndChild(c2);
    
    XMLDocument doc2;
    XMLNode* cloned = root->DeepClone(&doc2);
    doc2.InsertEndChild(cloned);
    
    EXPECT_EQ(2, cloned->ChildElementCount());
}

// Test large number of children
TEST_F(XMLNodeTest_183, ChildElementCount_LargeNumberOfChildren_183) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    const int N = 100;
    for (int i = 0; i < N; i++) {
        XMLElement* child = doc.NewElement("child");
        root->InsertEndChild(child);
    }
    
    EXPECT_EQ(N, root->ChildElementCount());
}

// Test ChildElementCount with name filter on empty node
TEST_F(XMLNodeTest_183, ChildElementCount_WithNameFilter_EmptyNode_ReturnsZero_183) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    EXPECT_EQ(0, root->ChildElementCount("anything"));
}

// Test ChildElementCount with nullptr name (should count all)
TEST_F(XMLNodeTest_183, ChildElementCount_WithNullptrName_CountsAll_183) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* c1 = doc.NewElement("a");
    root->InsertEndChild(c1);
    XMLElement* c2 = doc.NewElement("b");
    root->InsertEndChild(c2);
    
    // Passing nullptr should behave like counting all elements
    EXPECT_EQ(2, root->ChildElementCount(nullptr));
    EXPECT_EQ(root->ChildElementCount(), root->ChildElementCount(nullptr));
}

// Test parsed XML ChildElementCount
TEST_F(XMLNodeTest_183, ChildElementCount_ParsedXML_183) {
    const char* xml = "<root><a/><b/><c/><d/></root>";
    doc.Parse(xml);
    
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    EXPECT_EQ(4, root->ChildElementCount());
}

// Test parsed XML with mixed content
TEST_F(XMLNodeTest_183, ChildElementCount_ParsedXML_MixedContent_183) {
    const char* xml = "<root>text1<a/>text2<b/><!-- comment --><c/></root>";
    doc.Parse(xml);
    
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    EXPECT_EQ(3, root->ChildElementCount());
}

// Test NextSiblingElement iteration matches ChildElementCount
TEST_F(XMLNodeTest_183, NextSiblingElement_IterationMatchesCount_183) {
    const char* xml = "<root><a/><b/><c/></root>";
    doc.Parse(xml);
    
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    
    int manualCount = 0;
    const XMLElement* e = root->FirstChildElement();
    while (e) {
        manualCount++;
        e = e->NextSiblingElement();
    }
    
    EXPECT_EQ(root->ChildElementCount(), manualCount);
}

// Test PreviousSiblingElement
TEST_F(XMLNodeTest_183, PreviousSiblingElement_183) {
    const char* xml = "<root><a/><b/><c/></root>";
    doc.Parse(xml);
    
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    
    XMLElement* last = root->LastChildElement();
    ASSERT_NE(nullptr, last);
    EXPECT_STREQ("c", last->Value());
    
    XMLElement* prev = last->PreviousSiblingElement();
    ASSERT_NE(nullptr, prev);
    EXPECT_STREQ("b", prev->Value());
    
    prev = prev->PreviousSiblingElement();
    ASSERT_NE(nullptr, prev);
    EXPECT_STREQ("a", prev->Value());
    
    EXPECT_EQ(nullptr, prev->PreviousSiblingElement());
}

// Test GetDocument
TEST_F(XMLNodeTest_183, GetDocument_ReturnsOwningDocument_183) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    EXPECT_EQ(&doc, root->GetDocument());
}

// Test Parent
TEST_F(XMLNodeTest_183, Parent_183) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);
    
    EXPECT_EQ(root, child->Parent());
}

// Test UserData
TEST_F(XMLNodeTest_183, UserData_SetAndGet_183) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    EXPECT_EQ(nullptr, root->GetUserData());
    
    int data = 42;
    root->SetUserData(&data);
    EXPECT_EQ(&data, root->GetUserData());
}
