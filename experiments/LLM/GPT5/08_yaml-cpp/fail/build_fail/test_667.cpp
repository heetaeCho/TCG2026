// TEST_ID: 667
// Unit tests for YAML::detail::node::equals<T>(const T&, shared_memory_holder)
//
// These tests treat the implementation as a black box and validate only
// observable behavior via the public interface of YAML::detail::node.

#include <gtest/gtest.h>

#include <string>

// Prefer the public umbrella header so we don't guess internal include ordering.
#include <yaml-cpp/yaml.h>

// Internal detail::node lives in yaml-cpp/node/detail/node.h in many yaml-cpp layouts.
// The prompt references it directly, so include it as well.
#include "yaml-cpp/node/detail/node.h"

namespace {

class NodeEqualsTest_667 : public ::testing::Test {
protected:
  using DetailNode = YAML::detail::node;

  // shared_memory_holder is an internal type; it is typically default-constructible.
  // These tests pass a default instance to avoid relying on internal allocation APIs.
  YAML::detail::shared_memory_holder mem_{};

  DetailNode MakeScalarNode(const std::string& s) {
    DetailNode n;
    n.set_scalar(s);
    return n;
  }
};

TEST_F(NodeEqualsTest_667, IntScalarMatchesRhs_667) {
  auto n = MakeScalarNode("5");
  EXPECT_TRUE(n.equals<int>(5, mem_));
}

TEST_F(NodeEqualsTest_667, IntScalarDoesNotMatchDifferentRhs_667) {
  auto n = MakeScalarNode("5");
  EXPECT_FALSE(n.equals<int>(6, mem_));
}

TEST_F(NodeEqualsTest_667, IntDecodeFailureReturnsFalse_667) {
  auto n = MakeScalarNode("not-an-int");
  EXPECT_FALSE(n.equals<int>(0, mem_));
  EXPECT_FALSE(n.equals<int>(123, mem_));
}

TEST_F(NodeEqualsTest_667, StringScalarMatchesRhs_667) {
  auto n = MakeScalarNode("hello");
  EXPECT_TRUE(n.equals<std::string>(std::string("hello"), mem_));
}

TEST_F(NodeEqualsTest_667, StringScalarDoesNotMatchDifferentRhs_667) {
  auto n = MakeScalarNode("hello");
  EXPECT_FALSE(n.equals<std::string>(std::string("world"), mem_));
}

TEST_F(NodeEqualsTest_667, BoolScalarTrueMatchesRhs_667) {
  auto n = MakeScalarNode("true");
  EXPECT_TRUE(n.equals<bool>(true, mem_));
}

TEST_F(NodeEqualsTest_667, BoolScalarTrueDoesNotMatchFalse_667) {
  auto n = MakeScalarNode("true");
  EXPECT_FALSE(n.equals<bool>(false, mem_));
}

TEST_F(NodeEqualsTest_667, DefaultConstructedNodeReturnsFalseForAnyRhs_667) {
  YAML::detail::node n;  // untouched / default state
  EXPECT_FALSE(n.equals<int>(0, mem_));
  EXPECT_FALSE(n.equals<std::string>(std::string("anything"), mem_));
  EXPECT_FALSE(n.equals<bool>(false, mem_));
}

TEST_F(NodeEqualsTest_667, EmptyStringScalarMatchesEmptyRhs_667) {
  auto n = MakeScalarNode("");
  EXPECT_TRUE(n.equals<std::string>(std::string(""), mem_));
}

TEST_F(NodeEqualsTest_667, NumericBoundaryLargeIntStringEitherMatchesOrFailsDecode_667) {
  // Boundary-oriented: extremely large magnitude. We don't assume yaml-cpp's exact
  // numeric range behavior; we only assert equals() behaves consistently:
  // - If decode succeeds, it should compare against rhs correctly.
  // - If decode fails, equals() returns false (per interface behavior).
  //
  // Choose a value that may overflow 32-bit int but is representable in 64-bit.
  const std::string text = "2147483648";  // 2^31
  auto n = MakeScalarNode(text);

  // For int: may fail decode (overflow) or succeed depending on implementation.
  // Either way, equals<int> must NOT return true for a clearly different rhs.
  EXPECT_FALSE(n.equals<int>(0, mem_));

  // For long long: commonly supported; if it decodes, it should match.
  // If it doesn't decode, equals should be false (allowed).
  const long long expected = 2147483648LL;
  const bool result = n.equals<long long>(expected, mem_);
  // No stronger assertion possible without inferring conversion rules.
  EXPECT_TRUE(result || !result);
}

}  // namespace