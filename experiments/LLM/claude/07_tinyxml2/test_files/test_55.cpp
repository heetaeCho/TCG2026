#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class LastChildElementTest_55 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that LastChildElement returns nullptr when the document has no children
TEST_F(LastChildElementTest_55, ReturnsNullWhenNoChildren_55) {
    XMLElement* result = doc.LastChildElement();
    // A fresh document with no elements should return nullptr
    // (unless there's a root element by default, but for an empty doc it should be null)
    XMLDocument emptyDoc;
    EXPECT_EQ(emptyDoc.LastChildElement(), nullptr);
}

// Test that LastChildElement returns the last child element when there is one element
TEST_F(LastChildElementTest_55, ReturnsSingleChildElement_55) {
    doc.InsertEndChild(doc.NewElement("Root"));
    XMLElement* last = doc.LastChildElement();
    ASSERT_NE(last, nullptr);
    EXPECT_STREQ(last->Name(), "Root");
}

// Test that LastChildElement returns the last element among multiple children
TEST_F(LastChildElementTest_55, ReturnsLastAmongMultipleChildren_55) {
    doc.InsertEndChild(doc.NewElement("First"));
    doc.InsertEndChild(doc.NewElement("Second"));
    doc.InsertEndChild(doc.NewElement("Third"));

    XMLElement* last = doc.LastChildElement();
    ASSERT_NE(last, nullptr);
    EXPECT_STREQ(last->Name(), "Third");
}

// Test that LastChildElement with a name filter returns the last matching element
TEST_F(LastChildElementTest_55, ReturnsLastMatchingElementByName_55) {
    doc.InsertEndChild(doc.NewElement("Alpha"));
    doc.InsertEndChild(doc.NewElement("Beta"));
    doc.InsertEndChild(doc.NewElement("Alpha"));
    doc.InsertEndChild(doc.NewElement("Gamma"));

    XMLElement* last = doc.LastChildElement("Alpha");
    ASSERT_NE(last, nullptr);
    EXPECT_STREQ(last->Name(), "Alpha");

    // Verify it's the second Alpha, not the first
    // The second Alpha should have "Gamma" as next sibling
    XMLElement* nextSibling = last->NextSiblingElement();
    ASSERT_NE(nextSibling, nullptr);
    EXPECT_STREQ(nextSibling->Name(), "Gamma");
}

// Test that LastChildElement with a name filter returns nullptr when no match
TEST_F(LastChildElementTest_55, ReturnsNullWhenNameDoesNotMatch_55) {
    doc.InsertEndChild(doc.NewElement("Alpha"));
    doc.InsertEndChild(doc.NewElement("Beta"));

    XMLElement* last = doc.LastChildElement("NonExistent");
    EXPECT_EQ(last, nullptr);
}

// Test LastChildElement on an XMLElement node (not document root)
TEST_F(LastChildElementTest_55, WorksOnElementNode_55) {
    XMLElement* root = doc.NewElement("Root");
    doc.InsertEndChild(root);

    root->InsertEndChild(doc.NewElement("Child1"));
    root->InsertEndChild(doc.NewElement("Child2"));
    root->InsertEndChild(doc.NewElement("Child3"));

    XMLElement* last = root->LastChildElement();
    ASSERT_NE(last, nullptr);
    EXPECT_STREQ(last->Name(), "Child3");
}

// Test LastChildElement with name filter on an XMLElement node
TEST_F(LastChildElementTest_55, WorksOnElementNodeWithNameFilter_55) {
    XMLElement* root = doc.NewElement("Root");
    doc.InsertEndChild(root);

    root->InsertEndChild(doc.NewElement("Item"));
    root->InsertEndChild(doc.NewElement("Other"));
    root->InsertEndChild(doc.NewElement("Item"));
    root->InsertEndChild(doc.NewElement("Final"));

    XMLElement* last = root->LastChildElement("Item");
    ASSERT_NE(last, nullptr);
    EXPECT_STREQ(last->Name(), "Item");

    // Ensure it's the last "Item" (not the first one)
    XMLElement* next = last->NextSiblingElement();
    ASSERT_NE(next, nullptr);
    EXPECT_STREQ(next->Name(), "Final");
}

// Test that LastChildElement with nullptr name returns last child element (same as no arg)
TEST_F(LastChildElementTest_55, NullptrNameReturnsSameAsNoArg_55) {
    XMLElement* root = doc.NewElement("Root");
    doc.InsertEndChild(root);

    root->InsertEndChild(doc.NewElement("A"));
    root->InsertEndChild(doc.NewElement("B"));

    XMLElement* lastNoArg = root->LastChildElement();
    XMLElement* lastNullptr = root->LastChildElement(nullptr);

    EXPECT_EQ(lastNoArg, lastNullptr);
}

// Test LastChildElement when children include non-element nodes (comments, text)
TEST_F(LastChildElementTest_55, SkipsNonElementNodes_55) {
    XMLElement* root = doc.NewElement("Root");
    doc.InsertEndChild(root);

    root->InsertEndChild(doc.NewElement("Elem1"));
    root->InsertEndChild(doc.NewComment("This is a comment"));
    root->InsertEndChild(doc.NewElement("Elem2"));
    root->InsertEndChild(doc.NewComment("Another comment"));

    XMLElement* last = root->LastChildElement();
    ASSERT_NE(last, nullptr);
    EXPECT_STREQ(last->Name(), "Elem2");
}

// Test LastChildElement on a node with only non-element children
TEST_F(LastChildElementTest_55, ReturnsNullWhenOnlyNonElementChildren_55) {
    XMLElement* root = doc.NewElement("Root");
    doc.InsertEndChild(root);

    root->InsertEndChild(doc.NewComment("comment1"));
    root->InsertEndChild(doc.NewComment("comment2"));

    XMLElement* last = root->LastChildElement();
    EXPECT_EQ(last, nullptr);
}

// Test LastChildElement after deleting the last child
TEST_F(LastChildElementTest_55, ReturnsCorrectAfterDeletingLastChild_55) {
    XMLElement* root = doc.NewElement("Root");
    doc.InsertEndChild(root);

    root->InsertEndChild(doc.NewElement("A"));
    XMLElement* b = doc.NewElement("B");
    root->InsertEndChild(b);

    // Before deletion
    ASSERT_NE(root->LastChildElement(), nullptr);
    EXPECT_STREQ(root->LastChildElement()->Name(), "B");

    // Delete B
    root->DeleteChild(b);

    XMLElement* last = root->LastChildElement();
    ASSERT_NE(last, nullptr);
    EXPECT_STREQ(last->Name(), "A");
}

// Test LastChildElement after deleting all children
TEST_F(LastChildElementTest_55, ReturnsNullAfterDeletingAllChildren_55) {
    XMLElement* root = doc.NewElement("Root");
    doc.InsertEndChild(root);

    root->InsertEndChild(doc.NewElement("X"));
    root->InsertEndChild(doc.NewElement("Y"));

    root->DeleteChildren();

    EXPECT_EQ(root->LastChildElement(), nullptr);
}

// Test const correctness: calling on const XMLNode should also work
TEST_F(LastChildElementTest_55, ConstVersionWorksCorrectly_55) {
    XMLElement* root = doc.NewElement("Root");
    doc.InsertEndChild(root);

    root->InsertEndChild(doc.NewElement("Child"));

    const XMLNode* constRoot = root;
    const XMLElement* last = constRoot->LastChildElement();
    ASSERT_NE(last, nullptr);
    EXPECT_STREQ(last->Name(), "Child");
}

// Test LastChildElement with name filter on const node
TEST_F(LastChildElementTest_55, ConstVersionWithNameFilter_55) {
    XMLElement* root = doc.NewElement("Root");
    doc.InsertEndChild(root);

    root->InsertEndChild(doc.NewElement("Foo"));
    root->InsertEndChild(doc.NewElement("Bar"));
    root->InsertEndChild(doc.NewElement("Foo"));

    const XMLNode* constRoot = root;
    const XMLElement* last = constRoot->LastChildElement("Foo");
    ASSERT_NE(last, nullptr);
    EXPECT_STREQ(last->Name(), "Foo");

    // Verify it's the second Foo
    const XMLElement* nextSib = last->NextSiblingElement();
    EXPECT_EQ(nextSib, nullptr);
}

// Test LastChildElement with a single matching child among many
TEST_F(LastChildElementTest_55, SingleMatchAmongMany_55) {
    XMLElement* root = doc.NewElement("Root");
    doc.InsertEndChild(root);

    root->InsertEndChild(doc.NewElement("A"));
    root->InsertEndChild(doc.NewElement("B"));
    root->InsertEndChild(doc.NewElement("C"));

    XMLElement* last = root->LastChildElement("A");
    ASSERT_NE(last, nullptr);
    EXPECT_STREQ(last->Name(), "A");

    // A is the first child, but also the only match, so it should be returned
    XMLElement* prevSib = last->PreviousSiblingElement();
    EXPECT_EQ(prevSib, nullptr);
}

// Test LastChildElement when all children have the same name
TEST_F(LastChildElementTest_55, AllChildrenSameName_55) {
    XMLElement* root = doc.NewElement("Root");
    doc.InsertEndChild(root);

    root->InsertEndChild(doc.NewElement("Same"));
    root->InsertEndChild(doc.NewElement("Same"));
    root->InsertEndChild(doc.NewElement("Same"));

    XMLElement* last = root->LastChildElement("Same");
    ASSERT_NE(last, nullptr);
    EXPECT_STREQ(last->Name(), "Same");

    // The last "Same" should have no next sibling element
    EXPECT_EQ(last->NextSiblingElement(), nullptr);
}

// Test with parsed XML
TEST_F(LastChildElementTest_55, WorksWithParsedXML_55) {
    const char* xml = "<root><a/><b/><c/><a/></root>";
    doc.Parse(xml);
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);

    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    XMLElement* lastA = root->LastChildElement("a");
    ASSERT_NE(lastA, nullptr);
    EXPECT_STREQ(lastA->Name(), "a");

    // The last "a" should have no next sibling
    EXPECT_EQ(lastA->NextSiblingElement(), nullptr);
}

// Test with deeply nested structure
TEST_F(LastChildElementTest_55, DeepNesting_55) {
    const char* xml = "<root><level1><level2><deep1/><deep2/></level2></level1></root>";
    doc.Parse(xml);
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);

    XMLElement* root = doc.RootElement();
    XMLElement* level1 = root->FirstChildElement("level1");
    ASSERT_NE(level1, nullptr);
    XMLElement* level2 = level1->FirstChildElement("level2");
    ASSERT_NE(level2, nullptr);

    XMLElement* lastDeep = level2->LastChildElement();
    ASSERT_NE(lastDeep, nullptr);
    EXPECT_STREQ(lastDeep->Name(), "deep2");
}
