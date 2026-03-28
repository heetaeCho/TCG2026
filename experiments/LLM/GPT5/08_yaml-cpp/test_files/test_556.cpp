// TEST_ID: 556
#include <gtest/gtest.h>

#include <limits>
#include <string>

#include "yaml-cpp/node/node.h"

namespace {

class NodeAsWithFallbackTest_556 : public ::testing::Test {};

TEST_F(NodeAsWithFallbackTest_556, ConvertibleScalarToIntReturnsConverted_556) {
  const YAML::Node n(std::string("10"));

  const int value = n.as<int>(-1);

  EXPECT_EQ(value, 10);
}

TEST_F(NodeAsWithFallbackTest_556, NonConvertibleScalarToIntReturnsFallback_556) {
  const YAML::Node n(std::string("not-a-number"));

  EXPECT_NO_THROW({
    const int value = n.as<int>(123);
    EXPECT_EQ(value, 123);
  });
}

TEST_F(NodeAsWithFallbackTest_556, EmptyStringScalarToIntReturnsFallback_556) {
  const YAML::Node n(std::string(""));

  EXPECT_NO_THROW({
    const int value = n.as<int>(7);
    EXPECT_EQ(value, 7);
  });
}

TEST_F(NodeAsWithFallbackTest_556, NodeConstructedFromIntReturnsSameInt_556) {
  const YAML::Node n(42);

  const int value = n.as<int>(-1);

  EXPECT_EQ(value, 42);
}

TEST_F(NodeAsWithFallbackTest_556, NodeConstructedFromMaxLongLongReturnsSame_556) {
  const long long kMax = (std::numeric_limits<long long>::max)();
  const YAML::Node n(kMax);

  const long long value = n.as<long long>(0LL);

  EXPECT_EQ(value, kMax);
}

TEST_F(NodeAsWithFallbackTest_556, FallbackTypeCanDifferFromTargetTypeForString_556) {
  const YAML::Node n(std::string("hello"));

  const std::string value = n.as<std::string>("fallback");

  EXPECT_EQ(value, "hello");
}

TEST_F(NodeAsWithFallbackTest_556, InvalidNodeFromMissingMapKeyReturnsFallback_556) {
  YAML::Node map(YAML::NodeType::Map);
  map.force_insert(std::string("a"), 1);

  const YAML::Node missing = map[std::string("b")];

  // Observable precondition: missing key should not be "defined" in typical usage.
  // Regardless, as(fallback) should be safe to call.
  EXPECT_NO_THROW({
    const int value = missing.as<int>(999);
    EXPECT_EQ(value, 999);
  });
}

}  // namespace