#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

namespace {

class LinkEndChildTest_60 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* root = nullptr;

    void SetUp() override {
        root = doc.NewElement("root");
        ASSERT_NE(root, nullptr);
        ASSERT_NE(doc.InsertEndChild(root), nullptr);
    }
};

static void ExpectSingleChildChain(XMLNode* parent, XMLNode* onlyChild) {
    ASSERT_NE(parent, nullptr);
    ASSERT_NE(onlyChild, nullptr);

    EXPECT_EQ(parent->FirstChild(), onlyChild);
    EXPECT_EQ(parent->LastChild(), onlyChild);
    EXPECT_EQ(onlyChild->Parent(), parent);
    EXPECT_EQ(onlyChild->PreviousSibling(), nullptr);
    EXPECT_EQ(onlyChild->NextSibling(), nullptr);
}

}  // namespace

TEST_F(LinkEndChildTest_60, LinkEndChild_AppendsFirstChild_60) {
    ASSERT_TRUE(root->NoChildren());

    XMLElement* child = doc.NewElement("child");
    ASSERT_NE(child, nullptr);

    XMLNode* ret = root->LinkEndChild(child);

    // Observable behavior through the public interface:
    // - return value
    // - tree navigation (parent/children/siblings)
    EXPECT_EQ(ret, child);
    EXPECT_FALSE(root->NoChildren());
    ExpectSingleChildChain(root, child);
}

TEST_F(LinkEndChildTest_60, LinkEndChild_AppendsAfterExistingLastChild_60) {
    XMLElement* first = doc.NewElement("first");
    XMLElement* second = doc.NewElement("second");
    ASSERT_NE(first, nullptr);
    ASSERT_NE(second, nullptr);

    ASSERT_EQ(root->InsertEndChild(first), first);
    ASSERT_EQ(root->LastChild(), first);

    XMLNode* ret = root->LinkEndChild(second);

    EXPECT_EQ(ret, second);
    EXPECT_EQ(root->FirstChild(), first);
    EXPECT_EQ(root->LastChild(), second);

    EXPECT_EQ(first->Parent(), root);
    EXPECT_EQ(second->Parent(), root);

    EXPECT_EQ(first->NextSibling(), second);
    EXPECT_EQ(second->PreviousSibling(), first);
    EXPECT_EQ(second->NextSibling(), nullptr);
}

TEST_F(LinkEndChildTest_60, LinkEndChild_MatchesInsertEndChildForSameInput_60) {
    // Build two separate documents with the same starting structure.
    XMLDocument docA;
    XMLDocument docB;

    XMLElement* rootA = docA.NewElement("root");
    XMLElement* rootB = docB.NewElement("root");
    ASSERT_NE(rootA, nullptr);
    ASSERT_NE(rootB, nullptr);
    ASSERT_NE(docA.InsertEndChild(rootA), nullptr);
    ASSERT_NE(docB.InsertEndChild(rootB), nullptr);

    XMLElement* childA = docA.NewElement("child");
    XMLElement* childB = docB.NewElement("child");
    ASSERT_NE(childA, nullptr);
    ASSERT_NE(childB, nullptr);

    XMLNode* retInsert = rootA->InsertEndChild(childA);
    XMLNode* retLink = rootB->LinkEndChild(childB);

    // Compare observable results (return + structure), without inferring internals.
    EXPECT_EQ(retInsert, childA);
    EXPECT_EQ(retLink, childB);

    ExpectSingleChildChain(rootA, childA);
    ExpectSingleChildChain(rootB, childB);

    // Also compare a simple observable count, if available.
    EXPECT_EQ(rootA->ChildElementCount(), 1);
    EXPECT_EQ(rootB->ChildElementCount(), 1);
}

TEST_F(LinkEndChildTest_60, LinkEndChild_NullptrBehaviorMatchesInsertEndChild_60) {
    // We don't assume what "should" happen; we only assert LinkEndChild matches InsertEndChild.
    XMLDocument docA;
    XMLDocument docB;

    XMLElement* rootA = docA.NewElement("root");
    XMLElement* rootB = docB.NewElement("root");
    ASSERT_NE(rootA, nullptr);
    ASSERT_NE(rootB, nullptr);
    ASSERT_NE(docA.InsertEndChild(rootA), nullptr);
    ASSERT_NE(docB.InsertEndChild(rootB), nullptr);

    ASSERT_TRUE(rootA->NoChildren());
    ASSERT_TRUE(rootB->NoChildren());

    XMLNode* retInsert = rootA->InsertEndChild(nullptr);
    XMLNode* retLink = rootB->LinkEndChild(nullptr);

    EXPECT_EQ(retLink, retInsert);

    // Structural invariants should match between the two after the operation.
    EXPECT_EQ(rootB->NoChildren(), rootA->NoChildren());
    EXPECT_EQ(rootB->FirstChild() == nullptr, rootA->FirstChild() == nullptr);
    EXPECT_EQ(rootB->LastChild() == nullptr, rootA->LastChild() == nullptr);
    EXPECT_EQ(rootB->ChildElementCount(), rootA->ChildElementCount());
}
