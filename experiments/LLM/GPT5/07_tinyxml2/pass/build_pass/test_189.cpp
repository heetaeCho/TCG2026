// TEST_ID: 189
#include <gtest/gtest.h>

#include "tinyxml2.h"

using namespace tinyxml2;

class InsertEndChildTest_189 : public ::testing::Test {
protected:
    XMLDocument doc;
};

TEST_F(InsertEndChildTest_189, InsertIntoEmptyParent_SetsParentAndFirstLast_189) {
    XMLElement* parent = doc.NewElement("parent");
    ASSERT_NE(parent, nullptr);
    doc.InsertEndChild(parent);

    XMLElement* child = doc.NewElement("child");
    ASSERT_NE(child, nullptr);

    XMLNode* ret = parent->InsertEndChild(child);
    ASSERT_EQ(ret, child);

    ASSERT_EQ(child->Parent(), parent);
    ASSERT_EQ(parent->FirstChild(), child);
    ASSERT_EQ(parent->LastChild(), child);

    ASSERT_EQ(child->PreviousSibling(), nullptr);
    ASSERT_EQ(child->NextSibling(), nullptr);
    ASSERT_FALSE(parent->NoChildren());
}

TEST_F(InsertEndChildTest_189, InsertAppendsAfterExistingLastChild_SiblingLinksAndLastUpdated_189) {
    XMLElement* parent = doc.NewElement("parent");
    ASSERT_NE(parent, nullptr);
    doc.InsertEndChild(parent);

    XMLElement* c1 = doc.NewElement("c1");
    XMLElement* c2 = doc.NewElement("c2");
    ASSERT_NE(c1, nullptr);
    ASSERT_NE(c2, nullptr);

    ASSERT_EQ(parent->InsertEndChild(c1), c1);
    ASSERT_EQ(parent->InsertEndChild(c2), c2);

    ASSERT_EQ(parent->FirstChild(), c1);
    ASSERT_EQ(parent->LastChild(), c2);

    ASSERT_EQ(c1->Parent(), parent);
    ASSERT_EQ(c2->Parent(), parent);

    ASSERT_EQ(c1->PreviousSibling(), nullptr);
    ASSERT_EQ(c1->NextSibling(), c2);

    ASSERT_EQ(c2->PreviousSibling(), c1);
    ASSERT_EQ(c2->NextSibling(), nullptr);
}

TEST_F(InsertEndChildTest_189, InsertMultipleChildren_PreservesInsertionOrderThroughNextSibling_189) {
    XMLElement* parent = doc.NewElement("parent");
    ASSERT_NE(parent, nullptr);
    doc.InsertEndChild(parent);

    XMLElement* a = doc.NewElement("a");
    XMLElement* b = doc.NewElement("b");
    XMLElement* c = doc.NewElement("c");
    ASSERT_NE(a, nullptr);
    ASSERT_NE(b, nullptr);
    ASSERT_NE(c, nullptr);

    ASSERT_EQ(parent->InsertEndChild(a), a);
    ASSERT_EQ(parent->InsertEndChild(b), b);
    ASSERT_EQ(parent->InsertEndChild(c), c);

    const XMLNode* first = parent->FirstChild();
    ASSERT_EQ(first, a);
    ASSERT_EQ(first->NextSibling(), b);
    ASSERT_EQ(first->NextSibling()->NextSibling(), c);
    ASSERT_EQ(first->NextSibling()->NextSibling()->NextSibling(), nullptr);

    ASSERT_EQ(parent->LastChild(), c);
    ASSERT_EQ(parent->ChildElementCount(), 3);
}

TEST_F(InsertEndChildTest_189, InsertNodeFromDifferentDocument_ReturnsNullAndDoesNotModifyParent_189) {
    XMLElement* parent = doc.NewElement("parent");
    ASSERT_NE(parent, nullptr);
    doc.InsertEndChild(parent);
    ASSERT_TRUE(parent->NoChildren());

    XMLDocument otherDoc;
    XMLElement* foreignChild = otherDoc.NewElement("foreign");
    ASSERT_NE(foreignChild, nullptr);

    XMLNode* ret = parent->InsertEndChild(foreignChild);
    ASSERT_EQ(ret, nullptr);

    // Parent should remain unchanged (observable via public API).
    ASSERT_TRUE(parent->NoChildren());
    ASSERT_EQ(parent->FirstChild(), nullptr);
    ASSERT_EQ(parent->LastChild(), nullptr);

    // And the foreign node should not have been adopted.
    ASSERT_EQ(foreignChild->Parent(), nullptr);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(InsertEndChildTest_189, InsertNullChild_Death_189) {
    XMLElement* parent = doc.NewElement("parent");
    ASSERT_NE(parent, nullptr);
    doc.InsertEndChild(parent);

    // Contract: passing null triggers an assertion (or a hard failure) in typical builds.
    EXPECT_DEATH(
        {
            parent->InsertEndChild(nullptr);
        },
        ""
    );
}
#endif
