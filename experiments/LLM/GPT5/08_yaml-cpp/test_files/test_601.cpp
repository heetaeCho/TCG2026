// File: yaml-cpp/node/convert_test.cpp

#include <gtest/gtest.h>

#include <string>
#include <string_view>
#include <vector>

#include "yaml-cpp/node/convert.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/type.h"

namespace {

class ConvertDecodeStringViewTest_601 : public ::testing::Test {};

TEST_F(ConvertDecodeStringViewTest_601, ScalarNodeDecodesToStringView_601) {
  YAML::Node node("hello");

  std::string_view out = "sentinel";
  const bool ok = YAML::decode(node, out);

  EXPECT_TRUE(ok);
  EXPECT_EQ(out, "hello");
}

TEST_F(ConvertDecodeStringViewTest_601, EmptyScalarDecodesToEmptyView_601) {
  YAML::Node node(std::string(""));

  std::string_view out = "sentinel";
  const bool ok = YAML::decode(node, out);

  EXPECT_TRUE(ok);
  EXPECT_TRUE(out.empty());
}

TEST_F(ConvertDecodeStringViewTest_601, SequenceNodeReturnsFalseAndDoesNotChangeRhs_601) {
  YAML::Node node(YAML::NodeType::Sequence);

  std::string_view out = "keep-me";
  const bool ok = YAML::decode(node, out);

  EXPECT_FALSE(ok);
  EXPECT_EQ(out, "keep-me");
}

TEST_F(ConvertDecodeStringViewTest_601, MapNodeReturnsFalseAndDoesNotChangeRhs_601) {
  YAML::Node node(YAML::NodeType::Map);

  std::string_view out = "keep-me";
  const bool ok = YAML::decode(node, out);

  EXPECT_FALSE(ok);
  EXPECT_EQ(out, "keep-me");
}

TEST_F(ConvertDecodeStringViewTest_601, NullNodeReturnsFalseAndDoesNotChangeRhs_601) {
  YAML::Node node(YAML::NodeType::Null);

  std::string_view out = "keep-me";
  const bool ok = YAML::decode(node, out);

  EXPECT_FALSE(ok);
  EXPECT_EQ(out, "keep-me");
}

TEST_F(ConvertDecodeStringViewTest_601, EmbeddedNullBytesArePreservedInViewSize_601) {
  const std::string with_nulls(std::string("a\0b\0c", 5));
  YAML::Node node(with_nulls);

  std::string_view out;
  const bool ok = YAML::decode(node, out);

  EXPECT_TRUE(ok);
  ASSERT_EQ(out.size(), with_nulls.size());
  EXPECT_EQ(std::string(out.data(), out.size()), with_nulls);
}

TEST_F(ConvertDecodeStringViewTest_601, LargeScalarDecodes_601) {
  std::string large(1 << 20, 'x');  // 1 MiB
  YAML::Node node(large);

  std::string_view out;
  const bool ok = YAML::decode(node, out);

  EXPECT_TRUE(ok);
  ASSERT_EQ(out.size(), large.size());
  EXPECT_EQ(out.front(), 'x');
  EXPECT_EQ(out.back(), 'x');
}

TEST_F(ConvertDecodeStringViewTest_601, SuccessiveCallsUpdateOutputView_601) {
  YAML::Node n1("first");
  YAML::Node n2("second");

  std::string_view out = "sentinel";

  ASSERT_TRUE(YAML::decode(n1, out));
  EXPECT_EQ(out, "first");

  ASSERT_TRUE(YAML::decode(n2, out));
  EXPECT_EQ(out, "second");
}

}  // namespace