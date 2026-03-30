// TEST_ID: 552
#include <gtest/gtest.h>

#include <string>

#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/impl.h"

namespace {

class AsIfStringTest_552 : public ::testing::Test {
 protected:
  static std::string AsStringWithFallbackStd_552(const YAML::Node& n,
                                                const std::string& fallback) {
    YAML::as_if<std::string, std::string> conv(n);
    return conv(fallback);
  }

  static std::string AsStringWithFallbackCStr_552(const YAML::Node& n,
                                                  const char* fallback) {
    YAML::as_if<std::string, const char*> conv(n);
    return conv(fallback);
  }
};

TEST_F(AsIfStringTest_552, ReturnsLiteralNullWhenNodeIsNull_552) {
  const YAML::Node n(YAML::NodeType::Null);

  const std::string out1 = AsStringWithFallbackStd_552(n, "fallback");
  EXPECT_EQ(out1, "null");

  const std::string out2 = AsStringWithFallbackCStr_552(n, "fallback");
  EXPECT_EQ(out2, "null");
}

TEST_F(AsIfStringTest_552, IgnoresFallbackEvenIfEmptyWhenNodeIsNull_552) {
  const YAML::Node n(YAML::NodeType::Null);

  const std::string out1 = AsStringWithFallbackStd_552(n, "");
  EXPECT_EQ(out1, "null");

  const std::string out2 = AsStringWithFallbackCStr_552(n, "");
  EXPECT_EQ(out2, "null");
}

TEST_F(AsIfStringTest_552, ReturnsScalarValueWhenNodeIsScalar_552) {
  const YAML::Node n(std::string("hello"));

  const std::string out1 = AsStringWithFallbackStd_552(n, "fallback");
  EXPECT_EQ(out1, "hello");

  const std::string out2 = AsStringWithFallbackCStr_552(n, "fallback");
  EXPECT_EQ(out2, "hello");
}

TEST_F(AsIfStringTest_552, ReturnsEmptyStringWhenScalarIsEmpty_552) {
  const YAML::Node n(std::string(""));

  const std::string out = AsStringWithFallbackStd_552(n, "fallback");
  EXPECT_EQ(out, "");
}

TEST_F(AsIfStringTest_552, PreservesScalarWithWhitespaceAndSymbols_552) {
  const std::string scalar = "  a:b #c\t\n";
  const YAML::Node n(scalar);

  const std::string out = AsStringWithFallbackStd_552(n, "fallback");
  EXPECT_EQ(out, scalar);
}

TEST_F(AsIfStringTest_552, ReturnsFallbackWhenNodeIsSequence_552) {
  const YAML::Node n(YAML::NodeType::Sequence);

  const std::string out1 = AsStringWithFallbackStd_552(n, "fallback");
  EXPECT_EQ(out1, "fallback");

  const std::string out2 = AsStringWithFallbackCStr_552(n, "fallback");
  EXPECT_EQ(out2, "fallback");
}

TEST_F(AsIfStringTest_552, ReturnsFallbackWhenNodeIsMap_552) {
  const YAML::Node n(YAML::NodeType::Map);

  const std::string out1 = AsStringWithFallbackStd_552(n, "fallback");
  EXPECT_EQ(out1, "fallback");

  const std::string out2 = AsStringWithFallbackCStr_552(n, "fallback");
  EXPECT_EQ(out2, "fallback");
}

TEST_F(AsIfStringTest_552, ReturnsFallbackForNonScalarNonNullWithDistinctFallback_552) {
  const YAML::Node n(YAML::NodeType::Sequence);

  const std::string fallback = "distinct_fallback_value";
  const std::string out = AsStringWithFallbackStd_552(n, fallback);
  EXPECT_EQ(out, fallback);
}

TEST_F(AsIfStringTest_552, DoesNotThrowForSupportedNodeTypes_552) {
  const YAML::Node nullNode(YAML::NodeType::Null);
  const YAML::Node scalarNode(std::string("x"));
  const YAML::Node seqNode(YAML::NodeType::Sequence);
  const YAML::Node mapNode(YAML::NodeType::Map);

  EXPECT_NO_THROW((void)AsStringWithFallbackStd_552(nullNode, "fb"));
  EXPECT_NO_THROW((void)AsStringWithFallbackStd_552(scalarNode, "fb"));
  EXPECT_NO_THROW((void)AsStringWithFallbackStd_552(seqNode, "fb"));
  EXPECT_NO_THROW((void)AsStringWithFallbackStd_552(mapNode, "fb"));
}

}  // namespace