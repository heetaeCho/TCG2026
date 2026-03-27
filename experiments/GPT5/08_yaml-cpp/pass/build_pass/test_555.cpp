// TEST_ID: 555
#include <gtest/gtest.h>

#include <string>

// Prefer the umbrella header if available in the codebase; it typically brings in Node + exceptions.
#include "yaml-cpp/yaml.h"

namespace {

class NodeAsTest_555 : public ::testing::Test {};

TEST_F(NodeAsTest_555, ValidScalarStringRoundTrips_555) {
  YAML::Node n(std::string("hello"));
  EXPECT_NO_THROW({
    const auto s = n.as<std::string>();
    EXPECT_EQ(s, "hello");
  });
}

TEST_F(NodeAsTest_555, ValidScalarEmptyStringRoundTrips_555) {
  YAML::Node n(std::string{});
  EXPECT_NO_THROW({
    const auto s = n.as<std::string>();
    EXPECT_TRUE(s.empty());
  });
}

TEST_F(NodeAsTest_555, InvalidNodeThrowsInvalidNodeException_555) {
  // Obtain an invalid node through public API: accessing a missing key.
  YAML::Node map(YAML::NodeType::Map);
  const YAML::Node missing = map["missing_key_555"];

  // Observable precondition via public API.
  EXPECT_FALSE(missing.IsDefined());

  // From impl.h: as<T>() throws InvalidNode if the node is not valid.
  EXPECT_THROW((void)missing.as<std::string>(), YAML::InvalidNode);
}

TEST_F(NodeAsTest_555, InvalidNodeThrowsForDifferentRequestedTypes_555) {
  YAML::Node map(YAML::NodeType::Map);
  const YAML::Node missing = map["missing_key_for_int_555"];

  EXPECT_FALSE(missing.IsDefined());

  // The validity check happens before any conversion attempt.
  EXPECT_THROW((void)missing.as<int>(), YAML::InvalidNode);
}

}  // nam