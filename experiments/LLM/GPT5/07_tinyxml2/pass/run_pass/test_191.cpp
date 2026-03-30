#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class InsertAfterChildTest_191 : public ::testing::Test {
protected:
    XMLDocument doc;

    XMLElement* NewElem(const char* name) {
        return doc.NewElement(name);
    }
};

TEST_F(InsertAfterChildTest_191, InsertInMiddleMaintainsOrder_191) {
    XMLElement* parent = NewElem("parent");
    doc.InsertEndChild(parent);

    XMLElement* a = NewElem("a");
    XMLElement* b = NewElem("b");
    XMLElement* c = NewElem("c");

    ASSERT_EQ(parent->InsertEndChild(a), a);
    ASSERT_EQ(parent->InsertEndChild(c), c);

    // Insert b after a: expected order a -> b -> c
    ASSERT_EQ(parent->InsertAfterChild(a, b), b);

    const XMLNode* first = parent->FirstChild();
    ASSERT_NE(first, nullptr);
    EXPECT_STREQ(first->Value(), "a");

    const XMLNode* second = first->NextSibling();
    ASSERT_NE(second, nullptr);
    EXPECT_STREQ(second->Value(), "b");

    const XMLNode* third = second->NextSibling();
    ASSERT_NE(third, nullptr);
    EXPECT_STREQ(third->Value(), "c");

    EXPECT_EQ(third->NextSibling(), nullptr);
    EXPECT_EQ(parent->LastChild(), third);
}

TEST_F(InsertAfterChildTest_191, InsertAfterLastBehavesLikeInsertEndChild_191) {
    XMLElement* parent = NewElem("parent");
    doc.InsertEndChild(parent);

    XMLElement* a = NewElem("a");
    XMLElement* b = NewElem("b");
    ASSERT_EQ(parent->InsertEndChild(a), a);

    // afterThis is currently the last child; InsertAfterChild should append.
    ASSERT_EQ(parent->InsertAfterChild(a, b), b);

    const XMLNode* last = parent->LastChild();
    ASSERT_NE(last, nullptr);
    EXPECT_STREQ(last->Value(), "b");

    const XMLNode* first = parent->FirstChild();
    ASSERT_NE(first, nullptr);
    EXPECT_STREQ(first->Value(), "a");
    EXPECT_EQ(first->NextSibling(), last);
    EXPECT_EQ(last->PreviousSibling(), first);
    EXPECT_EQ(last->NextSibling(), nullptr);
}

TEST_F(InsertAfterChildTest_191, InsertAfterSelfReturnsNodeAndDoesNotReorder_191) {
    XMLElement* parent = NewElem("parent");
    doc.InsertEndChild(parent);

    XMLElement* a = NewElem("a");
    XMLElement* b = NewElem("b");
    ASSERT_EQ(parent->InsertEndChild(a), a);
    ASSERT_EQ(parent->InsertEndChild(b), b);

    // When afterThis == addThis, function returns addThis.
    ASSERT_EQ(parent->InsertAfterChild(a, a), a);

    // Order should still be a -> b
    const XMLNode* first = parent->FirstChild();
    ASSERT_NE(first, nullptr);
    EXPECT_STREQ(first->Value(), "a");

    const XMLNode* second = first->NextSibling();
    ASSERT_NE(second, nullptr);
    EXPECT_STREQ(second->Value(), "b");
    EXPECT_EQ(second->NextSibling(), nullptr);
}

TEST_F(InsertAfterChildTest_191, InsertFromDifferentDocumentReturnsNull_191) {
    XMLElement* parent = NewElem("parent");
    doc.InsertEndChild(parent);

    XMLElement* a = NewElem("a");
    ASSERT_EQ(parent->InsertEndChild(a), a);

    XMLDocument otherDoc;
    XMLElement* foreign = otherDoc.NewElement("foreign");

    // addThis belongs to a different document -> should fail and return null.
    EXPECT_EQ(parent->InsertAfterChild(a, foreign), nullptr);

    // Existing structure remains intact (a is still the only child).
    const XMLNode* first = parent->FirstChild();
    ASSERT_NE(first, nullptr);
    EXPECT_STREQ(first->Value(), "a");
    EXPECT_EQ(first->NextSibling(), nullptr);
}

TEST_F(InsertAfterChildTest_191, AfterThisNotAChildOfThisReturnsNull_191) {
    XMLElement* parent1 = NewElem("parent1");
    XMLElement* parent2 = NewElem("parent2");
    doc.InsertEndChild(parent1);
    doc.InsertEndChild(parent2);

    XMLElement* a = NewElem("a");
    XMLElement* b = NewElem("b");
    ASSERT_EQ(parent2->InsertEndChild(a), a);

    // Try to insert b into parent1 "after" a, but a is not a child of parent1.
    EXPECT_EQ(parent1->InsertAfterChild(a, b), nullptr);

    // parent1 should still have no children.
    EXPECT_TRUE(parent1->NoChildren());

    // parent2 should still have a as its only child.
    const XMLNode* first2 = parent2->FirstChild();
    ASSERT_NE(first2, nullptr);
    EXPECT_STREQ(first2->Value(), "a");
    EXPECT_EQ(first2->NextSibling(), nullptr);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(InsertAfterChildTest_191, NullAddThisTriggersAssertDeath_191) {
    XMLElement* parent = NewElem("parent");
    doc.InsertEndChild(parent);

    XMLElement* a = NewElem("a");
    ASSERT_EQ(parent->InsertEndChild(a), a);

    // InsertAfterChild begins with TIXMLASSERT(addThis).
    EXPECT_DEATH({ parent->InsertAfterChild(a, nullptr); }, "");
}

TEST_F(InsertAfterChildTest_191, NullAfterThisTriggersAssertDeath_191) {
    XMLElement* parent = NewElem("parent");
    doc.InsertEndChild(parent);

    XMLElement* a = NewElem("a");
    ASSERT_NE(a, nullptr);

    // InsertAfterChild has TIXMLASSERT(afterThis) before use.
    EXPECT_DEATH({ parent->InsertAfterChild(nullptr, a); }, "");
}
#endif
