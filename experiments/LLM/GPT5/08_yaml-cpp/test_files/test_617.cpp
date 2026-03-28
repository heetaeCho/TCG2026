// TEST_ID: 617
#include <gtest/gtest.h>

#include <valarray>
#include <cstddef>

#include <yaml-cpp/node/convert.h>
#include <yaml-cpp/node/node.h>

namespace {

TEST(ValarrayEncodeTest_617, EncodesEmptyValarrayAsEmptySequence_617) {
  const std::valarray<int> input;  // empty
  const YAML::Node node = YAML::convert<std::valarray<int>>::encode(input);

  EXPECT_TRUE(node.IsDefined());
  EXPECT_TRUE(node.IsSequence());
  EXPECT_EQ(node.size(), 0u);
}

TEST(ValarrayEncodeTest_617, EncodesSingleElementValarrayPreservingValue_617) {
  const std::valarray<int> input{42};
  const YAML::Node node = YAML::convert<std::valarray<int>>::encode(input);

  ASSERT_TRUE(node.IsSequence());
  ASSERT_EQ(node.size(), 1u);
  EXPECT_EQ(node[0].as<int>(), 42);
}

TEST(ValarrayEncodeTest_617, EncodesMultipleElementsPreservingOrder_617) {
  const std::valarray<int> input{3, -1, 0, 99, 7};
  const YAML::Node node = YAML::convert<std::valarray<int>>::encode(input);

  ASSERT_TRUE(node.IsSequence());
  ASSERT_EQ(node.size(), static_cast<std::size_t>(input.size()));

  for (std::size_t i = 0; i < static_cast<std::size_t>(input.size()); ++i) {
    EXPECT_EQ(node[i].as<int>(), input[static_cast<std::valarray<int>::size_type>(i)]);
  }
}

TEST(ValarrayEncodeTest_617, EncodesFloatingPointValues_617) {
  const std::valarray<double> input{0.5, -2.25, 3.125};
  const YAML::Node node = YAML::convert<std::valarray<double>>::encode(input);

  ASSERT_TRUE(node.IsSequence());
  ASSERT_EQ(node.size(), static_cast<std::size_t>(input.size()));

  for (std::size_t i = 0; i < static_cast<std::size_t>(input.size()); ++i) {
    EXPECT_DOUBLE_EQ(node[i].as<double>(),
                     input[static_cast<std::valarray<double>::size_type>(i)]);
  }
}

TEST(ValarrayEncodeTest_617, EncodesLargerValarrayWithCorrectSizeAndEndpoints_617) {
  constexpr std::size_t kN = 1024;

  // Build via raw array to avoid relying on valarray slicing semantics.
  double values[kN];
  for (std::size_t i = 0; i < kN; ++i) values[i] = static_cast<double>(i) * 0.25;

  const std::valarray<double> input(values, static_cast<std::valarray<double>::size_type>(kN));
  const YAML::Node node = YAML::convert<std::valarray<double>>::encode(input);

  ASSERT_TRUE(node.IsSequence());
  ASSERT_EQ(node.size(), kN);

  // Spot-check a few positions (including boundaries).
  EXPECT_DOUBLE_EQ(node[0].as<double>(), values[0]);
  EXPECT_DOUBLE_EQ(node[kN / 2].as<double>(), values[kN / 2]);
  EXPECT_DOUBLE_EQ(node[kN - 1].as<double>(), values[kN - 1]);
}

}  // namespace