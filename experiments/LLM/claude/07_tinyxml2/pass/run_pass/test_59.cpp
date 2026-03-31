#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class NextSiblingElementTest_59 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST_F(NextSiblingElementTest_59, ReturnsNullWhenNoSiblings_59) {
    doc.Parse("<root><child/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    XMLElement* next = child->NextSiblingElement();
    EXPECT_EQ(next, nullptr);
}

TEST_F(NextSiblingElementTest_59, ReturnsNextSiblingElementWithoutName_59) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);
    XMLElement* b = a->NextSiblingElement();
    ASSERT_NE(b, nullptr);
    EXPECT_STREQ(b->Name(), "b");
    XMLElement* c = b->NextSiblingElement();
    ASSERT_NE(c, nullptr);
    EXPECT_STREQ(c->Name(), "c");
    XMLElement* none = c->NextSiblingElement();
    EXPECT_EQ(none, nullptr);
}

TEST_F(NextSiblingElementTest_59, ReturnsNextSiblingElementByName_59) {
    doc.Parse("<root><a/><b/><c/><b/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);
    XMLElement* firstB = a->NextSiblingElement("b");
    ASSERT_NE(firstB, nullptr);
    EXPECT_STREQ(firstB->Name(), "b");
    XMLElement* secondB = firstB->NextSiblingElement("b");
    ASSERT_NE(secondB, nullptr);
    EXPECT_STREQ(secondB->Name(), "b");
    // The second b should be different from the first
    EXPECT_NE(firstB, secondB);
    XMLElement* thirdB = secondB->NextSiblingElement("b");
    EXPECT_EQ(thirdB, nullptr);
}

TEST_F(NextSiblingElementTest_59, ReturnsNullWhenNameNotFound_59) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);
    XMLElement* result = a->NextSiblingElement("nonexistent");
    EXPECT_EQ(result, nullptr);
}

TEST_F(NextSiblingElementTest_59, ReturnsNullForSingleChild_59) {
    doc.Parse("<root><only/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* only = root->FirstChildElement("only");
    ASSERT_NE(only, nullptr);
    EXPECT_EQ(only->NextSiblingElement(), nullptr);
    EXPECT_EQ(only->NextSiblingElement("only"), nullptr);
}

TEST_F(NextSiblingElementTest_59, SkipsNonElementSiblings_59) {
    doc.Parse("<root><a/><!-- comment -->text<b/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);
    // NextSiblingElement should skip comment and text nodes
    XMLElement* b = a->NextSiblingElement();
    ASSERT_NE(b, nullptr);
    EXPECT_STREQ(b->Name(), "b");
}

TEST_F(NextSiblingElementTest_59, SkipsNonElementSiblingsWithName_59) {
    doc.Parse("<root><a/><!-- comment -->text<b/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);
    XMLElement* b = a->NextSiblingElement("b");
    ASSERT_NE(b, nullptr);
    EXPECT_STREQ(b->Name(), "b");
}

TEST_F(NextSiblingElementTest_59, NullNameBehavesLikeNoArgument_59) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);
    XMLElement* withNull = a->NextSiblingElement(nullptr);
    XMLElement* withDefault = a->NextSiblingElement();
    EXPECT_EQ(withNull, withDefault);
}

TEST_F(NextSiblingElementTest_59, WorksWithMultipleSameName_59) {
    doc.Parse("<root><item id='1'/><item id='2'/><item id='3'/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* item1 = root->FirstChildElement("item");
    ASSERT_NE(item1, nullptr);
    EXPECT_STREQ(item1->Attribute("id"), "1");

    XMLElement* item2 = item1->NextSiblingElement("item");
    ASSERT_NE(item2, nullptr);
    EXPECT_STREQ(item2->Attribute("id"), "2");

    XMLElement* item3 = item2->NextSiblingElement("item");
    ASSERT_NE(item3, nullptr);
    EXPECT_STREQ(item3->Attribute("id"), "3");

    XMLElement* item4 = item3->NextSiblingElement("item");
    EXPECT_EQ(item4, nullptr);
}

TEST_F(NextSiblingElementTest_59, ConstVersionReturnsCorrectElement_59) {
    doc.Parse("<root><a/><b/><c/></root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);
    const XMLElement* b = a->NextSiblingElement();
    ASSERT_NE(b, nullptr);
    EXPECT_STREQ(b->Name(), "b");
}

TEST_F(NextSiblingElementTest_59, ConstVersionWithNameReturnsCorrectElement_59) {
    doc.Parse("<root><a/><b/><c/></root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);
    const XMLElement* c = a->NextSiblingElement("c");
    ASSERT_NE(c, nullptr);
    EXPECT_STREQ(c->Name(), "c");
}

TEST_F(NextSiblingElementTest_59, WorksAfterInsertEndChild_59) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* a = doc.NewElement("a");
    XMLElement* b = doc.NewElement("b");
    XMLElement* c = doc.NewElement("c");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    root->InsertEndChild(c);

    XMLElement* next = a->NextSiblingElement();
    ASSERT_NE(next, nullptr);
    EXPECT_STREQ(next->Name(), "b");

    next = next->NextSiblingElement();
    ASSERT_NE(next, nullptr);
    EXPECT_STREQ(next->Name(), "c");

    next = next->NextSiblingElement();
    EXPECT_EQ(next, nullptr);
}

TEST_F(NextSiblingElementTest_59, WorksAfterInsertFirstChild_59) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* a = doc.NewElement("a");
    XMLElement* b = doc.NewElement("b");
    root->InsertEndChild(a);
    root->InsertFirstChild(b);

    // Order should be: b, a
    XMLElement* first = root->FirstChildElement();
    ASSERT_NE(first, nullptr);
    EXPECT_STREQ(first->Name(), "b");

    XMLElement* second = first->NextSiblingElement();
    ASSERT_NE(second, nullptr);
    EXPECT_STREQ(second->Name(), "a");

    EXPECT_EQ(second->NextSiblingElement(), nullptr);
}

TEST_F(NextSiblingElementTest_59, WorksAfterDeletingChild_59) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* b = root->FirstChildElement("b");
    ASSERT_NE(b, nullptr);
    root->DeleteChild(b);

    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);
    XMLElement* next = a->NextSiblingElement();
    ASSERT_NE(next, nullptr);
    EXPECT_STREQ(next->Name(), "c");
    EXPECT_EQ(next->NextSiblingElement(), nullptr);
}

TEST_F(NextSiblingElementTest_59, EmptyNameStringBehavior_59) {
    doc.Parse("<root><a/><b/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);
    // Empty string should not match any element name (unless an element has empty name)
    XMLElement* result = a->NextSiblingElement("");
    EXPECT_EQ(result, nullptr);
}

TEST_F(NextSiblingElementTest_59, RootElementHasNoNextSibling_59) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->NextSiblingElement(), nullptr);
}

TEST_F(NextSiblingElementTest_59, DeepNestedNextSibling_59) {
    doc.Parse("<root><parent><child1/><child2/></parent></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* parent = root->FirstChildElement("parent");
    ASSERT_NE(parent, nullptr);
    XMLElement* child1 = parent->FirstChildElement("child1");
    ASSERT_NE(child1, nullptr);
    XMLElement* child2 = child1->NextSiblingElement("child2");
    ASSERT_NE(child2, nullptr);
    EXPECT_STREQ(child2->Name(), "child2");
}

TEST_F(NextSiblingElementTest_59, InsertAfterChildUpdatesNextSibling_59) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* a = doc.NewElement("a");
    XMLElement* c = doc.NewElement("c");
    root->InsertEndChild(a);
    root->InsertEndChild(c);

    XMLElement* b = doc.NewElement("b");
    root->InsertAfterChild(a, b);

    // Order: a, b, c
    XMLElement* next = a->NextSiblingElement();
    ASSERT_NE(next, nullptr);
    EXPECT_STREQ(next->Name(), "b");
    next = next->NextSiblingElement();
    ASSERT_NE(next, nullptr);
    EXPECT_STREQ(next->Name(), "c");
    EXPECT_EQ(next->NextSiblingElement(), nullptr);
}
