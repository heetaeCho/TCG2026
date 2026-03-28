// File: yaml_cpp_convert_std_array_decode_test_616.cpp

#include <array>
#include <string>

#include <gtest/gtest.h>

// Prefer the public umbrella include if available in the codebase.
// If your project forbids this, replace with the specific headers you use.
#include <yaml-cpp/yaml.h>

#include "yaml-cpp/node/convert.h"

namespace {

template <typename T>
YAML::Node MakeSequenceNode(const std::initializer_list<T>& values) {
  YAML::Node n(YAML::NodeType::Sequence);
  for (const auto& v : values) {
    n.push_back(v);
  }
  return n;
}

}  // namespace

class ConvertStdArrayDecodeTest_616 : public ::testing::Test {};

TEST_F(ConvertStdArrayDecodeTest_616, DecodeSucceedsForSequenceOfExactSize_616) {
  YAML::Node node = MakeSequenceNode<int>({1, 2, 3});
  std::array<int, 3> out{{0, 0, 0}};

  const bool ok = YAML::convert<std::array<int, 3>>::decode(node, out);

  EXPECT_TRUE(ok);
  EXPECT_EQ(out[0], 1);
  EXPECT_EQ(out[1], 2);
  EXPECT_EQ(out[2], 3);
}

TEST_F(ConvertStdArrayDecodeTest_616, DecodeFailsForNonSequenceNode_616) {
  YAML::Node node(42);  // scalar, not a sequence
  std::array<int, 3> out{{7, 8, 9}};

  const bool ok = YAML::convert<std::array<int, 3>>::decode(node, out);

  EXPECT_FALSE(ok);
}

TEST_F(ConvertStdArrayDecodeTest_616, DecodeFailsWhenSequenceSizeIsSmallerThanArraySize_616) {
  YAML::Node node = MakeSequenceNode<int>({1, 2});  // size 2, expects 3
  std::array<int, 3> out{{0, 0, 0}};

  const bool ok = YAML::convert<std::array<int, 3>>::decode(node, out);

  EXPECT_FALSE(ok);
}

TEST_F(ConvertStdArrayDecodeTest_616, DecodeFailsWhenSequenceSizeIsLargerThanArraySize_616) {
  YAML::Node node = MakeSequenceNode<int>({1, 2, 3, 4});  // size 4, expects 3
  std::array<int, 3> out{{0, 0, 0}};

  const bool ok = YAML::convert<std::array<int, 3>>::decode(node, out);

  EXPECT_FALSE(ok);
}

TEST_F(ConvertStdArrayDecodeTest_616, DecodeSucceedsForStringArray_616) {
  YAML::Node node = MakeSequenceNode<std::string>({"a", "bb", "ccc"});
  std::array<std::string, 3> out{{"", "", ""}};

  const bool ok = YAML::convert<std::array<std::string, 3>>::decode(node, out);

  EXPECT_TRUE(ok);
  EXPECT_EQ(out[0], "a");
  EXPECT_EQ(out[1], "bb");
  EXPECT_EQ(out[2], "ccc");
}

TEST_F(ConvertStdArrayDecodeTest_616, DecodeZeroSizeArraySucceedsForEmptySequence_616) {
  YAML::Node node(YAML::NodeType::Sequence);  // empty sequence
  std::array<int, 0> out{};

  const bool ok = YAML::convert<std::array<int, 0>>::decode(node, out);

  EXPECT_TRUE(ok);
}

TEST_F(ConvertStdArrayDecodeTest_616, DecodeZeroSizeArrayFailsForNonSequence_616) {
  YAML::Node node(0);  // scalar
  std::array<int, 0> out{};

  const bool ok = YAML::convert<std::array<int, 0>>::decode(node, out);

  EXPECT_FALSE(ok);
}