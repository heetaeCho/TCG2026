// File: ./TestProjects/tinyxml2/tests/XMLElementShallowEqualTest_266.cpp

#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementShallowEqualTest_266 : public ::testing::Test {
protected:
    XMLDocument doc1_;
    XMLDocument doc2_;
};

TEST_F(XMLElementShallowEqualTest_266, SameElementPointerIsEqual_266) {
    XMLElement* e = doc1_.NewElement("root");
    ASSERT_NE(e, nullptr);

    EXPECT_TRUE(e->ShallowEqual(e));
}

TEST_F(XMLElementShallowEqualTest_266, SameNameNoAttributesIsEqual_266) {
    XMLElement* a = doc1_.NewElement("root");
    XMLElement* b = doc2_.NewElement("root");
    ASSERT_NE(a, nullptr);
    ASSERT_NE(b, nullptr);

    EXPECT_TRUE(a->ShallowEqual(b));
    EXPECT_TRUE(b->ShallowEqual(a));
}

TEST_F(XMLElementShallowEqualTest_266, DifferentNameIsNotEqual_266) {
    XMLElement* a = doc1_.NewElement("root");
    XMLElement* b = doc2_.NewElement("other");
    ASSERT_NE(a, nullptr);
    ASSERT_NE(b, nullptr);

    EXPECT_FALSE(a->ShallowEqual(b));
    EXPECT_FALSE(b->ShallowEqual(a));
}

TEST_F(XMLElementShallowEqualTest_266, SameNameSameSingleAttributeValueIsEqual_266) {
    XMLElement* a = doc1_.NewElement("root");
    XMLElement* b = doc2_.NewElement("root");
    ASSERT_NE(a, nullptr);
    ASSERT_NE(b, nullptr);

    a->SetAttribute("id", "123");
    b->SetAttribute("id", "123");

    EXPECT_TRUE(a->ShallowEqual(b));
    EXPECT_TRUE(b->ShallowEqual(a));
}

TEST_F(XMLElementShallowEqualTest_266, SameNameDifferentAttributeValueIsNotEqual_266) {
    XMLElement* a = doc1_.NewElement("root");
    XMLElement* b = doc2_.NewElement("root");
    ASSERT_NE(a, nullptr);
    ASSERT_NE(b, nullptr);

    a->SetAttribute("id", "123");
    b->SetAttribute("id", "124");

    EXPECT_FALSE(a->ShallowEqual(b));
    EXPECT_FALSE(b->ShallowEqual(a));
}

TEST_F(XMLElementShallowEqualTest_266, SameNameDifferentAttributeCountIsNotEqual_266) {
    XMLElement* a = doc1_.NewElement("root");
    XMLElement* b = doc2_.NewElement("root");
    ASSERT_NE(a, nullptr);
    ASSERT_NE(b, nullptr);

    a->SetAttribute("a", "1");
    a->SetAttribute("b", "2");
    b->SetAttribute("a", "1");

    EXPECT_FALSE(a->ShallowEqual(b));
    EXPECT_FALSE(b->ShallowEqual(a));
}

TEST_F(XMLElementShallowEqualTest_266, SameNameSameValuesDifferentOrderIsNotEqual_266) {
    XMLElement* a = doc1_.NewElement("root");
    XMLElement* b = doc2_.NewElement("root");
    ASSERT_NE(a, nullptr);
    ASSERT_NE(b, nullptr);

    // Insert in one order.
    a->SetAttribute("first", "1");
    a->SetAttribute("second", "2");

    // Insert in the opposite order.
    b->SetAttribute("second", "2");
    b->SetAttribute("first", "1");

    EXPECT_FALSE(a->ShallowEqual(b));
    EXPECT_FALSE(b->ShallowEqual(a));
}

TEST_F(XMLElementShallowEqualTest_266, SameNameDifferentAttributeNamesButSameValuesIsEqual_266) {
    XMLElement* a = doc1_.NewElement("root");
    XMLElement* b = doc2_.NewElement("root");
    ASSERT_NE(a, nullptr);
    ASSERT_NE(b, nullptr);

    // Values match in sequence, but names differ.
    a->SetAttribute("id", "123");
    b->SetAttribute("differentName", "123");

    EXPECT_TRUE(a->ShallowEqual(b));
    EXPECT_TRUE(b->ShallowEqual(a));
}

TEST_F(XMLElementShallowEqualTest_266, CompareAgainstNonElementNodeIsNotEqual_266) {
    XMLElement* a = doc1_.NewElement("root");
    XMLText* t = doc2_.NewText("hello");
    ASSERT_NE(a, nullptr);
    ASSERT_NE(t, nullptr);

    EXPECT_FALSE(a->ShallowEqual(t));
}

#if defined(GTEST_HAS_DEATH_TEST) && GTEST_HAS_DEATH_TEST
// TIXMLASSERT(compare) is expected to fire in debug builds.
// In release builds, the assertion may be compiled out; this test is guarded accordingly.
#ifndef NDEBUG
TEST_F(XMLElementShallowEqualTest_266, NullCompareTriggersAssert_266) {
    XMLElement* a = doc1_.NewElement("root");
    ASSERT_NE(a, nullptr);

    EXPECT_DEATH({ (void)a->ShallowEqual(nullptr); }, "");
}
#endif  // !NDEBUG
#endif  // death tests
