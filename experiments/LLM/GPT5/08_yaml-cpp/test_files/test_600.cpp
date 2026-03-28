// File: yaml_cpp_encode_string_view_test_600.cpp

#include <gtest/gtest.h>

#include <string>
#include <string_view>
#include <vector>

#include <yaml-cpp/yaml.h>  // Provides YAML::Node

namespace {

class EncodeStringViewTest_600 : public ::testing::Test {
protected:
  static std::string NodeToString(const YAML::Node& n) {
    // Observable behavior via public API: convert node to std::string.
    return n.as<std::string>();
  }
};

TEST_F(EncodeStringViewTest_600, EncodesSimpleAsciiString_600) {
  std::string_view sv = "hello";
  YAML::Node n = YAML::encode(sv);

  EXPECT_EQ(NodeToString(n), "hello");
}

TEST_F(EncodeStringViewTest_600, EncodesEmptyString_600) {
  std::string_view sv = "";
  YAML::Node n = YAML::encode(sv);

  EXPECT_EQ(NodeToString(n), "");
}

TEST_F(EncodeStringViewTest_600, EncodesStringWithSpacesAndPunctuation_600) {
  std::string_view sv = " a b\tc\n!@# ";
  YAML::Node n = YAML::encode(sv);

  EXPECT_EQ(NodeToString(n), std::string(sv));
}

TEST_F(EncodeStringViewTest_600, CopiesFromMutableBufferSoLaterMutationDoesNotAffectNode_600) {
  std::string backing = "original";
  std::string_view sv(backing);

  YAML::Node n = YAML::encode(sv);

  // Mutate the original backing after encoding.
  backing[0] = 'X';
  backing.append("_changed");

  // Node should still reflect what was encoded.
  EXPECT_EQ(NodeToString(n), "original");
}

TEST_F(EncodeStringViewTest_600, EncodesStringViewWithEmbeddedNullByte_600) {
  // string_view can reference binary data (including '\0').
  const char raw[] = {'a', '\0', 'b', 'c'};
  std::string_view sv(raw, sizeof(raw));

  YAML::Node n = YAML::encode(sv);
  std::string out = NodeToString(n);

  ASSERT_EQ(out.size(), sizeof(raw));
  EXPECT_EQ(out[0], 'a');
  EXPECT_EQ(out[1], '\0');
  EXPECT_EQ(out[2], 'b');
  EXPECT_EQ(out[3], 'c');
}

TEST_F(EncodeStringViewTest_600, EncodesLargeString_600) {
  const size_t kSize = 1 << 20;  // 1 MiB
  std::string big(kSize, 'x');
  std::string_view sv(big);

  YAML::Node n = YAML::encode(sv);
  std::string out = NodeToString(n);

  ASSERT_EQ(out.size(), kSize);
  EXPECT_EQ(out.front(), 'x');
  EXPECT_EQ(out.back(), 'x');
}

}  // namespace