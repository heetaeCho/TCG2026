// File: iterator_base_test_200.cpp

#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

namespace {

class IteratorBaseTest_200 : public ::testing::Test {};

TEST_F(IteratorBaseTest_200, PostIncrementReturnsPreviousPosition_200) {
  const YAML::Node seq = YAML::Load("[a, b, c]");
  ASSERT_TRUE(seq.IsSequence());
  ASSERT_GE(seq.size(), 2u);

  auto it = seq.begin();
  const auto begin_it = seq.begin();

  // Post-increment should return the iterator state *before* increment.
  auto prev = it++;

  EXPECT_EQ(prev, begin_it);
  ASSERT_NE(it, seq.end());
  ASSERT_NE(prev, seq.end());

  EXPECT_EQ(prev->as<std::string>(), "a");
  EXPECT_EQ(it->as<std::string>(), "b");
}

TEST_F(IteratorBaseTest_200, PostIncrementAdvancesSameAsPreIncrement_200) {
  const YAML::Node seq = YAML::Load("[x, y, z]");
  ASSERT_TRUE(seq.IsSequence());
  ASSERT_GE(seq.size(), 2u);

  auto it_post = seq.begin();
  auto it_pre = seq.begin();

  // After these operations, both iterators should point to the same element.
  (void)it_post++;
  ++it_pre;

  EXPECT_EQ(it_post, it_pre);
  ASSERT_NE(it_post, seq.end());
  EXPECT_EQ(it_post->as<std::string>(), "y");
}

TEST_F(IteratorBaseTest_200, PostIncrementFromLastElementReachesEnd_200) {
  const YAML::Node seq = YAML::Load("[one, two]");
  ASSERT_TRUE(seq.IsSequence());
  ASSERT_EQ(seq.size(), 2u);

  auto it = seq.begin();
  ++it;  // now at last element ("two")
  ASSERT_NE(it, seq.end());
  EXPECT_EQ(it->as<std::string>(), "two");

  // Post-increment from the last element should yield end().
  auto prev = it++;
  ASSERT_NE(prev, seq.end());
  EXPECT_EQ(prev->as<std::string>(), "two");
  EXPECT_EQ(it, seq.end());
}

TEST_F(IteratorBaseTest_200, PostIncrementOnBeginDoesNotModifyReturnedCopy_200) {
  const YAML::Node seq = YAML::Load("[p, q]");
  ASSERT_TRUE(seq.IsSequence());
  ASSERT_EQ(seq.size(), 2u);

  auto it = seq.begin();
  auto prev = it++;

  // The returned iterator is a copy of the pre-increment state; it should still
  // refer to the first element even after the original iterator advances.
  ASSERT_NE(prev, seq.end());
  EXPECT_EQ(prev->as<std::string>(), "p");

  ASSERT_NE(it, seq.end());
  EXPECT_EQ(it->as<std::string>(), "q");
}

}  // namespace