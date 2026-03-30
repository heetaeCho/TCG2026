// File: ./TestProjects/yaml-cpp/test/collectionstack_test_65.cpp

#include <gtest/gtest.h>

#include "collectionstack.h"

namespace {

using YAML::CollectionStack;
using YAML::CollectionType;

TEST(CollectionStackTest_65, DefaultCtor_CurrentTypeIsAValidEnumValue_65) {
  CollectionStack stack;

  const auto cur = stack.GetCurCollectionType();
  EXPECT_TRUE(cur == CollectionType::NoType || cur == CollectionType::Sequence ||
              cur == CollectionType::Map);
}

TEST(CollectionStackTest_65, PushThenGetCurCollectionType_ReturnsPushedType_65) {
  CollectionStack stack;

  stack.PushCollectionType(CollectionType::Sequence);
  EXPECT_EQ(stack.GetCurCollectionType(), CollectionType::Sequence);

  stack.PushCollectionType(CollectionType::Map);
  EXPECT_EQ(stack.GetCurCollectionType(), CollectionType::Map);
}

TEST(CollectionStackTest_65, PushTwoThenPop_RestoresPreviousType_65) {
  CollectionStack stack;

  stack.PushCollectionType(CollectionType::Sequence);
  stack.PushCollectionType(CollectionType::Map);

  stack.PopCollectionType(CollectionType::Map);
  EXPECT_EQ(stack.GetCurCollectionType(), CollectionType::Sequence);
}

TEST(CollectionStackTest_65, PopWithMatchingType_DoesNotCrash_65) {
  CollectionStack stack;

  stack.PushCollectionType(CollectionType::Sequence);
  EXPECT_NO_FATAL_FAILURE(stack.PopCollectionType(CollectionType::Sequence));
}

#if GTEST_HAS_DEATH_TEST
#ifndef NDEBUG
TEST(CollectionStackTest_65, PopWithMismatchedType_TriggersAssertDeath_65) {
  CollectionStack stack;

  stack.PushCollectionType(CollectionType::Sequence);

  // PopCollectionType asserts that the provided type matches the current type.
  ASSERT_DEATH(stack.PopCollectionType(CollectionType::Map), "");
}
#endif  // !NDEBUG
#endif  // GTEST_HAS_DEATH_TEST

}  // namespace
