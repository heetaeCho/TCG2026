// File: ./TestProjects/tinyxml2/test_xmlnode_insertfirstchild_190.cpp

#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLNodeInsertFirstChildTest_190 : public ::testing::Test {
protected:
    XMLDocument doc;
};

TEST_F(XMLNodeInsertFirstChildTest_190, InsertIntoEmptyParent_SetsFirstLastAndParentLinks_190) {
    XMLElement* root = doc.NewElement("root");
    ASSERT_NE(root, nullptr);
    ASSERT_NE(doc.InsertFirstChild(root), nullptr);

    ASSERT_TRUE(root->NoChildren());

    XMLElement* child = doc.NewElement("child");
    ASSERT_NE(child, nullptr);

    XMLNode* inserted = root->InsertFirstChild(child);
    ASSERT_EQ(inserted, child);

    EXPECT_FALSE(root->NoChildren());
    EXPECT_EQ(root->FirstChild(), child);
    EXPECT_EQ(root->LastChild(), child);

    EXPECT_EQ(child->Parent(), root);
    EXPECT_EQ(child->PreviousSibling(), nullptr);
    EXPECT_EQ(child->NextSibling(), nullptr);
}

TEST_F(XMLNodeInsertFirstChildTest_190, InsertWhenExistingChild_NewBecomesFirstAndSiblingLinksUpdate_190) {
    XMLElement* root = doc.NewElement("root");
    ASSERT_NE(root, nullptr);
    ASSERT_NE(doc.InsertFirstChild(root), nullptr);

    XMLElement* first = doc.NewElement("first");
    XMLElement* second = doc.NewElement("second");
    ASSERT_NE(first, nullptr);
    ASSERT_NE(second, nullptr);

    ASSERT_EQ(root->InsertEndChild(first), first);
    ASSERT_EQ(root->InsertFirstChild(second), second);

    // Order should now be: second, first
    EXPECT_EQ(root->FirstChild(), second);
    EXPECT_EQ(root->LastChild(), first);

    EXPECT_EQ(second->Parent(), root);
    EXPECT_EQ(first->Parent(), root);

    EXPECT_EQ(second->PreviousSibling(), nullptr);
    EXPECT_EQ(second->NextSibling(), first);

    EXPECT_EQ(first->PreviousSibling(), second);
    EXPECT_EQ(first->NextSibling(), nullptr);
}

TEST_F(XMLNodeInsertFirstChildTest_190, InsertFirstChildMultipleTimes_MaintainsFrontInsertionOrder_190) {
    XMLElement* root = doc.NewElement("root");
    ASSERT_NE(root, nullptr);
    ASSERT_NE(doc.InsertFirstChild(root), nullptr);

    XMLElement* a = doc.NewElement("a");
    XMLElement* b = doc.NewElement("b");
    XMLElement* c = doc.NewElement("c");
    ASSERT_NE(a, nullptr);
    ASSERT_NE(b, nullptr);
    ASSERT_NE(c, nullptr);

    ASSERT_EQ(root->InsertFirstChild(a), a); // [a]
    ASSERT_EQ(root->InsertFirstChild(b), b); // [b, a]
    ASSERT_EQ(root->InsertFirstChild(c), c); // [c, b, a]

    const XMLNode* n0 = root->FirstChild();
    ASSERT_NE(n0, nullptr);
    EXPECT_STREQ(n0->Value(), "c");

    const XMLNode* n1 = n0->NextSibling();
    ASSERT_NE(n1, nullptr);
    EXPECT_STREQ(n1->Value(), "b");

    const XMLNode* n2 = n1->NextSibling();
    ASSERT_NE(n2, nullptr);
    EXPECT_STREQ(n2->Value(), "a");

    EXPECT_EQ(n2->NextSibling(), nullptr);
    EXPECT_EQ(root->LastChild(), n2);
}

TEST_F(XMLNodeInsertFirstChildTest_190, InsertFromDifferentDocument_ErrorOrDeathDependingOnAsserts_190) {
    XMLElement* root = doc.NewElement("root");
    ASSERT_NE(root, nullptr);
    ASSERT_NE(doc.InsertFirstChild(root), nullptr);

    XMLDocument otherDoc;
    XMLElement* foreign = otherDoc.NewElement("foreign");
    ASSERT_NE(foreign, nullptr);

#ifndef NDEBUG
    // With assertions enabled, tinyxml2 uses TIXMLASSERT which typically aborts.
    EXPECT_DEATH_IF_SUPPORTED(root->InsertFirstChild(foreign), "");
#else
    // With assertions disabled, observable behavior is a null return.
    EXPECT_EQ(root->InsertFirstChild(foreign), nullptr);
#endif
}

TEST_F(XMLNodeInsertFirstChildTest_190, InsertNullptr_ErrorOrSkipDependingOnAsserts_190) {
#ifndef NDEBUG
    XMLElement* root = doc.NewElement("root");
    ASSERT_NE(root, nullptr);
    ASSERT_NE(doc.InsertFirstChild(root), nullptr);

    EXPECT_DEATH_IF_SUPPORTED(root->InsertFirstChild(nullptr), "");
#else
    GTEST_SKIP() << "InsertFirstChild(nullptr) would violate the interface precondition when asserts are disabled.";
#endif
}
