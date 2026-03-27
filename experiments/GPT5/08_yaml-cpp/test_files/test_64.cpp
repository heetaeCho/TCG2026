// File: ./TestProjects/yaml-cpp/test/collectionstack_test_64.cpp

#include <gtest/gtest.h>

#include "collectionstack.h"

namespace {

using YAML::CollectionStack;
using YAML::CollectionType;

// Picks a valid CollectionType value that (ideally) differs from `baseline`.
// This avoids guessing the default current type while still testing observable changes.
static CollectionType::value PickDifferent(CollectionType::value baseline) {
  const CollectionType::value candidates[] = {
      CollectionType::NoType,
      CollectionType::BlockSeq,
      CollectionType::BlockMap,
      CollectionType::FlowSeq,
      CollectionType::FlowMap,
  };

  for (auto v : candidates) {
    if (v != baseline) return v;
  }
  return baseline;  // Fallback: still valid, even if not different.
}

static CollectionType::value PickThirdDifferent(CollectionType::value a,
                                                CollectionType::value b) {
  const CollectionType::value candidates[] = {
      CollectionType::NoType,
      CollectionType::BlockSeq,
      CollectionType::BlockMap,
      CollectionType::FlowSeq,
      CollectionType::FlowMap,
  };

  for (auto v : candidates) {
    if (v != a && v != b) return v;
  }
  return a;  // Fallback: valid.
}

class CollectionStackTest_64 : public ::testing::Test {
 protected:
  CollectionStack stack_;
};

}  // namespace

TEST_F(CollectionStackTest_64, GetCurCollectionTypeIsStableAfterConstruction_64) {
  const auto baseline = stack_.GetCurCollectionType();
  EXPECT_EQ(baseline, stack_.GetCurCollectionType());
  EXPECT_EQ(baseline, stack_.GetCurCollectionType());
}

TEST_F(CollectionStackTest_64, PushThenPopRestoresBaseline_64) {
  const auto baseline = stack_.GetCurCollectionType();
  const auto type = PickDifferent(baseline);

  EXPECT_NO_THROW(stack_.PushCollectionType(type));
  EXPECT_EQ(type, stack_.GetCurCollectionType());

  EXPECT_NO_THROW(stack_.PopCollectionType(type));
  EXPECT_EQ(baseline, stack_.GetCurCollectionType());
}

TEST_F(CollectionStackTest_64, NestedPushPopTracksTopOfStack_64) {
  const auto baseline = stack_.GetCurCollectionType();
  const auto a = PickDifferent(baseline);
  const auto b = PickDifferent(a);

  ASSERT_NO_THROW(stack_.PushCollectionType(a));
  EXPECT_EQ(a, stack_.GetCurCollectionType());

  ASSERT_NO_THROW(stack_.PushCollectionType(b));
  EXPECT_EQ(b, stack_.GetCurCollectionType());

  ASSERT_NO_THROW(stack_.PopCollectionType(b));
  EXPECT_EQ(a, stack_.GetCurCollectionType());

  ASSERT_NO_THROW(stack_.PopCollectionType(a));
  EXPECT_EQ(baseline, stack_.GetCurCollectionType());
}

TEST_F(CollectionStackTest_64, MultiplePushPopRestoresBaseline_64) {
  const auto baseline = stack_.GetCurCollectionType();
  const auto a = PickDifferent(baseline);
  const auto b = PickDifferent(a);
  const auto c = PickThirdDifferent(a, b);

  ASSERT_NO_THROW(stack_.PushCollectionType(a));
  EXPECT_EQ(a, stack_.GetCurCollectionType());

  ASSERT_NO_THROW(stack_.PushCollectionType(b));
  EXPECT_EQ(b, stack_.GetCurCollectionType());

  ASSERT_NO_THROW(stack_.PushCollectionType(c));
  EXPECT_EQ(c, stack_.GetCurCollectionType());

  ASSERT_NO_THROW(stack_.PopCollectionType(c));
  EXPECT_EQ(b, stack_.GetCurCollectionType());

  ASSERT_NO_THROW(stack_.PopCollectionType(b));
  EXPECT_EQ(a, stack_.GetCurCollectionType());

  ASSERT_NO_THROW(stack_.PopCollectionType(a));
  EXPECT_EQ(baseline, stack_.GetCurCollectionType());
}
