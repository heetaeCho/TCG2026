// TEST_ID: 554
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

#include <yaml-cpp/node/node.h>
#include <yaml-cpp/exceptions.h>

namespace {

using ::testing::HasSubstr;

class AsIfStringOperatorNoFallbackTest_554 : public ::testing::Test {};

TEST_F(AsIfStringOperatorNoFallbackTest_554, UndefinedNodeThrowsInvalidNode_554) {
  const YAML::Node n(YAML::NodeType::Undefined);
  EXPECT_THROW((void)n.as<std::string>(), YAML::InvalidNode);
}

TEST_F(AsIfStringOperatorNoFallbackTest_554, NullNodeReturnsLiteralNull_554) {
  const YAML::Node n(YAML::NodeType::Null);
  EXPECT_EQ(n.as<std::string>(), "null");
}

TEST_F(AsIfStringOperatorNoFallbackTest_554, ScalarNodeReturnsScalarValue_554) {
  const YAML::Node n(std::string("hello"));
  EXPECT_EQ(n.as<std::string>(), "hello");
}

TEST_F(AsIfStringOperatorNoFallbackTest_554, ScalarEmptyStringIsReturned_554) {
  const YAML::Node n(std::string(""));
  EXPECT_EQ(n.as<std::string>(), "");
}

TEST_F(AsIfStringOperatorNoFallbackTest_554, ScalarWithTextNullIsNotTreatedAsNull_554) {
  const YAML::Node n(std::string("null"));
  EXPECT_EQ(n.as<std::string>(), "null");
}

TEST_F(AsIfStringOperatorNoFallbackTest_554, SequenceNodeThrowsTypedBadConversion_554) {
  const YAML::Node n(YAML::NodeType::Sequence);
  EXPECT_THROW((void)n.as<std::string>(), YAML::TypedBadConversion<std::string>);
}

TEST_F(AsIfStringOperatorNoFallbackTest_554, MapNodeThrowsTypedBadConversion_554) {
  const YAML::Node n(YAML::NodeType::Map);
  EXPECT_THROW((void)n.as<std::string>(), YAML::TypedBadConversion<std::string>);
}

TEST_F(AsIfStringOperatorNoFallbackTest_554, MissingKeyNodeThrowsInvalidNodeAndMentionsKey_554) {
  YAML::Node map(YAML::NodeType::Map);

  const YAML::Node missing = map["missing_key"];
  try {
    (void)missing.as<std::string>();
    FAIL() << "Expected YAML::InvalidNode to be thrown";
  } catch (const YAML::InvalidNode& e) {
    EXPECT_THAT(std::string(e.what()), HasSubstr("missing_key"));
  } catch (...) {
    FAIL() << "Expected YAML::InvalidNode, but caught a different exception type";
  }
}

}  // namespac