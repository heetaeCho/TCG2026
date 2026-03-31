#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class PreviousSiblingElementTest_57 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST_F(PreviousSiblingElementTest_57, NoPreviousSiblingElement_ReturnsNull_57) {
    const char* xml = "<root><child1/></root>";
    doc.Parse(xml);
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* child1 = root->FirstChildElement("child1");
    ASSERT_NE(child1, nullptr);

    XMLElement* prev = child1->PreviousSiblingElement();
    EXPECT_EQ(prev, nullptr);
}

TEST_F(PreviousSiblingElementTest_57, HasPreviousSiblingElement_ReturnsIt_57) {
    const char* xml = "<root><child1/><child2/></root>";
    doc.Parse(xml);
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* child2 = root->FirstChildElement("child1")->NextSiblingElement("child2");
    ASSERT_NE(child2, nullptr);

    XMLElement* prev = child2->PreviousSiblingElement();
    ASSERT_NE(prev, nullptr);
    EXPECT_STREQ(prev->Name(), "child1");
}

TEST_F(PreviousSiblingElementTest_57, PreviousSiblingElementByName_Found_57) {
    const char* xml = "<root><alpha/><beta/><gamma/></root>";
    doc.Parse(xml);
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* gamma = root->LastChildElement("gamma");
    ASSERT_NE(gamma, nullptr);

    XMLElement* prev = gamma->PreviousSiblingElement("alpha");
    ASSERT_NE(prev, nullptr);
    EXPECT_STREQ(prev->Name(), "alpha");
}

TEST_F(PreviousSiblingElementTest_57, PreviousSiblingElementByName_NotFound_57) {
    const char* xml = "<root><alpha/><beta/><gamma/></root>";
    doc.Parse(xml);
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* gamma = root->LastChildElement("gamma");
    ASSERT_NE(gamma, nullptr);

    XMLElement* prev = gamma->PreviousSiblingElement("nonexistent");
    EXPECT_EQ(prev, nullptr);
}

TEST_F(PreviousSiblingElementTest_57, PreviousSiblingElementByName_SkipsNonMatching_57) {
    const char* xml = "<root><target/><other1/><other2/><last/></root>";
    doc.Parse(xml);
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* last = root->LastChildElement("last");
    ASSERT_NE(last, nullptr);

    XMLElement* prev = last->PreviousSiblingElement("target");
    ASSERT_NE(prev, nullptr);
    EXPECT_STREQ(prev->Name(), "target");
}

TEST_F(PreviousSiblingElementTest_57, PreviousSiblingElement_NullName_ReturnsImmediatePrevious_57) {
    const char* xml = "<root><a/><b/><c/></root>";
    doc.Parse(xml);
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* c = root->LastChildElement("c");
    ASSERT_NE(c, nullptr);

    XMLElement* prev = c->PreviousSiblingElement(nullptr);
    ASSERT_NE(prev, nullptr);
    EXPECT_STREQ(prev->Name(), "b");
}

TEST_F(PreviousSiblingElementTest_57, PreviousSiblingElement_MultipleSameName_57) {
    const char* xml = "<root><item/><item/><item/></root>";
    doc.Parse(xml);
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* last = root->LastChildElement("item");
    ASSERT_NE(last, nullptr);

    XMLElement* prev = last->PreviousSiblingElement("item");
    ASSERT_NE(prev, nullptr);
    EXPECT_STREQ(prev->Name(), "item");
    // The previous sibling should not be the same as the last one
    EXPECT_NE(prev, last);

    // Go one more back
    XMLElement* prevPrev = prev->PreviousSiblingElement("item");
    ASSERT_NE(prevPrev, nullptr);
    EXPECT_STREQ(prevPrev->Name(), "item");
    EXPECT_NE(prevPrev, prev);

    // No more previous
    XMLElement* noPrev = prevPrev->PreviousSiblingElement("item");
    EXPECT_EQ(noPrev, nullptr);
}

TEST_F(PreviousSiblingElementTest_57, PreviousSiblingElement_WithTextNodes_57) {
    const char* xml = "<root><a/>Some text<b/></root>";
    doc.Parse(xml);
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* b = root->FirstChildElement("b");
    ASSERT_NE(b, nullptr);

    // PreviousSiblingElement should skip text nodes and find <a/>
    XMLElement* prev = b->PreviousSiblingElement();
    ASSERT_NE(prev, nullptr);
    EXPECT_STREQ(prev->Name(), "a");
}

TEST_F(PreviousSiblingElementTest_57, PreviousSiblingElement_WithComments_57) {
    const char* xml = "<root><a/><!-- comment --><b/></root>";
    doc.Parse(xml);
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* b = root->FirstChildElement("b");
    ASSERT_NE(b, nullptr);

    XMLElement* prev = b->PreviousSiblingElement();
    ASSERT_NE(prev, nullptr);
    EXPECT_STREQ(prev->Name(), "a");
}

TEST_F(PreviousSiblingElementTest_57, PreviousSiblingElement_FirstChild_ReturnsNull_57) {
    const char* xml = "<root><first/><second/><third/></root>";
    doc.Parse(xml);
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* first = root->FirstChildElement("first");
    ASSERT_NE(first, nullptr);

    XMLElement* prev = first->PreviousSiblingElement();
    EXPECT_EQ(prev, nullptr);
}

TEST_F(PreviousSiblingElementTest_57, PreviousSiblingElement_SingleChild_ReturnsNull_57) {
    const char* xml = "<root><only/></root>";
    doc.Parse(xml);
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* only = root->FirstChildElement("only");
    ASSERT_NE(only, nullptr);

    EXPECT_EQ(only->PreviousSiblingElement(), nullptr);
    EXPECT_EQ(only->PreviousSiblingElement("only"), nullptr);
    EXPECT_EQ(only->PreviousSiblingElement("anything"), nullptr);
}

TEST_F(PreviousSiblingElementTest_57, PreviousSiblingElement_ByName_ImmediatePrevious_57) {
    const char* xml = "<root><alpha/><beta/></root>";
    doc.Parse(xml);
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* beta = root->FirstChildElement("beta");
    ASSERT_NE(beta, nullptr);

    XMLElement* prev = beta->PreviousSiblingElement("beta");
    EXPECT_EQ(prev, nullptr);

    prev = beta->PreviousSiblingElement("alpha");
    ASSERT_NE(prev, nullptr);
    EXPECT_STREQ(prev->Name(), "alpha");
}

TEST_F(PreviousSiblingElementTest_57, ConstVersion_PreviousSiblingElement_57) {
    const char* xml = "<root><a/><b/></root>";
    doc.Parse(xml);
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLElement* b = root->LastChildElement("b");
    ASSERT_NE(b, nullptr);

    const XMLElement* prev = b->PreviousSiblingElement();
    ASSERT_NE(prev, nullptr);
    EXPECT_STREQ(prev->Name(), "a");
}

TEST_F(PreviousSiblingElementTest_57, PreviousSiblingElement_DynamicallyInsertedChildren_57) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* e1 = doc.NewElement("e1");
    XMLElement* e2 = doc.NewElement("e2");
    XMLElement* e3 = doc.NewElement("e3");

    root->InsertEndChild(e1);
    root->InsertEndChild(e2);
    root->InsertEndChild(e3);

    EXPECT_EQ(e1->PreviousSiblingElement(), nullptr);
    EXPECT_EQ(e2->PreviousSiblingElement(), e1);
    EXPECT_EQ(e3->PreviousSiblingElement(), e2);
    EXPECT_EQ(e3->PreviousSiblingElement("e1"), e1);
    EXPECT_EQ(e3->PreviousSiblingElement("nonexistent"), nullptr);
}

TEST_F(PreviousSiblingElementTest_57, PreviousSiblingElement_EmptyNameString_57) {
    const char* xml = "<root><a/><b/></root>";
    doc.Parse(xml);
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* b = root->FirstChildElement("b");
    ASSERT_NE(b, nullptr);

    // Empty string name - should not match any element name (names are non-empty)
    XMLElement* prev = b->PreviousSiblingElement("");
    EXPECT_EQ(prev, nullptr);
}
