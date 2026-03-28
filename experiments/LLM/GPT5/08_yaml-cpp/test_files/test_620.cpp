// TEST_ID: 620
#include <gtest/gtest.h>

#include <utility>
#include <string>

// yaml-cpp public include (common in yaml-cpp projects)
#include <yaml-cpp/yaml.h>

namespace {

class ConvertPairDecodeTest_620 : public ::testing::Test {};

TEST_F(ConvertPairDecodeTest_620, DecodeSucceedsForTwoElementIntSequence_620) {
  YAML::Node node(YAML::NodeType::Sequence);
  node.push_back(1);
  node.push_back(2);

  std::pair<int, int> out{-1, -1};
  const bool ok = YAML::convert<std::pair<int, int>>::decode(node, out);

  EXPECT_TRUE(ok);
  EXPECT_EQ(out.first, 1);
  EXPECT_EQ(out.second, 2);
}

TEST_F(ConvertPairDecodeTest_620, DecodeSucceedsForMixedTypes_620) {
  YAML::Node node(YAML::NodeType::Sequence);
  node.push_back(std::string("hello"));
  node.push_back(42);

  std::pair<std::string, int> out{"", 0};
  const bool ok = YAML::convert<std::pair<std::string, int>>::decode(node, out);

  EXPECT_TRUE(ok);
  EXPECT_EQ(out.first, "hello");
  EXPECT_EQ(out.second, 42);
}

TEST_F(ConvertPairDecodeTest_620, DecodeFailsWhenNodeIsNotASequence_620) {
  YAML::Node node(123);  // scalar node

  std::pair<int, int> out{7, 9};
  const bool ok = YAML::convert<std::pair<int, int>>::decode(node, out);

  EXPECT_FALSE(ok);
}

TEST_F(ConvertPairDecodeTest_620, DecodeFailsWhenSequenceSizeIsZero_620) {
  YAML::Node node(YAML::NodeType::Sequence);

  std::pair<int, int> out{0, 0};
  const bool ok = YAML::convert<std::pair<int, int>>::decode(node, out);

  EXPECT_FALSE(ok);
}

TEST_F(ConvertPairDecodeTest_620, DecodeFailsWhenSequenceSizeIsOne_620) {
  YAML::Node node(YAML::NodeType::Sequence);
  node.push_back(1);

  std::pair<int, int> out{0, 0};
  const bool ok = YAML::convert<std::pair<int, int>>::decode(node, out);

  EXPECT_FALSE(ok);
}

TEST_F(ConvertPairDecodeTest_620, DecodeFailsWhenSequenceSizeIsThree_620) {
  YAML::Node node(YAML::NodeType::Sequence);
  node.push_back(1);
  node.push_back(2);
  node.push_back(3);

  std::pair<int, int> out{0, 0};
  const bool ok = YAML::convert<std::pair<int, int>>::decode(node, out);

  EXPECT_FALSE(ok);
}

TEST_F(ConvertPairDecodeTest_620, DecodeThrowsWhenElementConversionFails_620) {
  YAML::Node node(YAML::NodeType::Sequence);
  node.push_back(std::string("not_an_int"));
  node.push_back(2);

  std::pair<int, int> out{0, 0};

  // decode() calls Node::as<T>() for elements; invalid conversions are observable as exceptions.
  EXPECT_ANY_THROW((void)YAML::convert<std::pair<int, int>>::decode(node, out));
}

TEST_F(ConvertPairDecodeTest_620, DecodeThrowsWhenSecondElementConversionFails_620) {
  YAML::Node node(YAML::NodeType::Sequence);
  node.push_back(1);
  node.push_back(std::string("not_an_int"));

  std::pair<int, int> out{0, 0};
  EXPECT_ANY_THROW((void)YAML::convert<std::pair<int, int>>::decode(node, out));
}

}  // namespace