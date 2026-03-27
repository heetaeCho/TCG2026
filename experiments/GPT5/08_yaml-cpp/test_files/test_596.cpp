// File: yaml-cpp/node/convert_string_decode_test_596.cpp

#include <gtest/gtest.h>

#include <string>

#include "yaml-cpp/node/convert.h"
#include "yaml-cpp/node/node.h"

namespace {

class DecodeStringTest_596 : public ::testing::Test {};

TEST_F(DecodeStringTest_596, ScalarNodeCopiesScalarAndReturnsTrue_596) {
  const YAML::Node node(std::string("hello"));
  std::string out = "sentinel";

  const bool ok = YAML::decode(node, out);

  EXPECT_TRUE(ok);
  EXPECT_EQ(out, "hello");
}

TEST_F(DecodeStringTest_596, ScalarNodeAllowsEmptyString_596) {
  const YAML::Node node(std::string(""));
  std::string out = "sentinel";

  const bool ok = YAML::decode(node, out);

  EXPECT_TRUE(ok);
  EXPECT_EQ(out, "");
}

TEST_F(DecodeStringTest_596, ScalarNodePreservesWhitespaceAndUtf8_596) {
  const std::string kValue = "  spaced\tvalue  ✓";
  const YAML::Node node(kValue);
  std::string out;

  const bool ok = YAML::decode(node, out);

  EXPECT_TRUE(ok);
  EXPECT_EQ(out, kValue);
}

TEST_F(DecodeStringTest_596, ScalarNodeHandlesLargeString_596) {
  const std::string kLarge(64 * 1024, 'x');  // 64KB
  const YAML::Node node(kLarge);
  std::string out = "sentinel";

  const bool ok = YAML::decode(node, out);

  EXPECT_TRUE(ok);
  EXPECT_EQ(out.size(), kLarge.size());
  EXPECT_EQ(out, kLarge);
}

TEST_F(DecodeStringTest_596, NonScalarNullNodeReturnsFalseAndDoesNotModifyOutput_596) {
  const YAML::Node node;  // default-constructed; should not be a scalar
  std::string out = "sentinel";

  const bool ok = YAML::decode(node, out);

  EXPECT_FALSE(ok);
  EXPECT_EQ(out, "sentinel");
}

TEST_F(DecodeStringTest_596, NonScalarSequenceNodeReturnsFalseAndDoesNotModifyOutput_596) {
  YAML::Node node;
  node.push_back(1);  // make it a sequence
  ASSERT_TRUE(node.IsSequence());

  std::string out = "sentinel";

  const bool ok = YAML::decode(node, out);

  EXPECT_FALSE(ok);
  EXPECT_EQ(out, "sentinel");
}

TEST_F(DecodeStringTest_596, NonScalarMapNodeReturnsFalseAndDoesNotModifyOutput_596) {
  YAML::Node node;
  node.force_insert("k", "v");  // make it a map
  ASSERT_TRUE(node.IsMap());

  std::string out = "sentinel";

  const bool ok = YAML::decode(node, out);

  EXPECT_FALSE(ok);
  EXPECT_EQ(out, "sentinel");
}

TEST_F(DecodeStringTest_596, NonScalarSequenceDoesNotThrow_596) {
  YAML::Node node;
  node.push_back("x");
  ASSERT_TRUE(node.IsSequence());

  std::string out = "sentinel";

  EXPECT_NO_THROW({
    const bool ok = YAML::decode(node, out);
    EXPECT_FALSE(ok);
  });
  EXPECT_EQ(out, "sentinel");
}

}  // namespace