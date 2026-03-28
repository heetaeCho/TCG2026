// TEST_ID: 550
#include <gtest/gtest.h>

#include <yaml-cpp/exceptions.h>
#include <yaml-cpp/node/node.h>

namespace {

class TypeTest_550 : public ::testing::Test {};

TEST_F(TypeTest_550, DefaultConstructedNodeTypeIsNull_550) {
  const YAML::Node n;
  EXPECT_NO_THROW({
    const YAML::NodeType::value t = n.Type();
    EXPECT_EQ(t, YAML::NodeType::Null);
  });
}

TEST_F(TypeTest_550, ExplicitNullNodeTypeIsNull_550) {
  const YAML::Node n(YAML::NodeType::Null);
  EXPECT_NO_THROW(EXPECT_EQ(n.Type(), YAML::NodeType::Null));
}

TEST_F(TypeTest_550, ConstructedWithConcreteTypesReportsSameType_550) {
  // Validate observable behavior for the public constructor taking NodeType::value.
  // (Skip Undefined here to avoid relying on any special-casing in the implementation.)
  const YAML::NodeType::value kTypes[] = {
      YAML::NodeType::Null,
      YAML::NodeType::Scalar,
      YAML::NodeType::Sequence,
      YAML::NodeType::Map,
  };

  for (const auto type : kTypes) {
    const YAML::Node n(type);
    EXPECT_NO_THROW(EXPECT_EQ(n.Type(), type));
    // Repeat call: should remain stable and not throw.
    EXPECT_NO_THROW(EXPECT_EQ(n.Type(), type));
  }
}

TEST_F(TypeTest_550, TypeOnMissingKeyFromMapThrowsInvalidNode_550) {
  const YAML::Node m(YAML::NodeType::Map);

  // Accessing a missing key should produce a node that, when queried for Type(),
  // signals invalidity via InvalidNode (observable behavior).
  const YAML::Node missing = m["definitely_missing_key_550"];

  EXPECT_THROW({ (void)missing.Type(); }, YAML::InvalidNode);
}

TEST_F(TypeTest_550, TypeOnMissingIndexFromSequenceThrowsInvalidNode_550) {
  const YAML::Node s(YAML::NodeType::Sequence);

  // Accessing an out-of-range index should produce a node that throws InvalidNode on Type().
  const YAML::Node missing = s[0];

  EXPECT_THROW({ (void)missing.Type(); }, YAML::InvalidNode);
}

TEST_F(TypeTest_550, TypeOnExistingSequenceElementMatchesInsertedNodeType_550) {
  YAML::Node s(YAML::NodeType::Sequence);

  // Insert a node with a known, explicit type so we can validate Type() deterministically.
  const YAML::Node inserted(YAML::NodeType::Map);
  ASSERT_NO_THROW(s.push_back(inserted));

  const YAML::Node elem0 = s[0];
  EXPECT_NO_THROW(EXPECT_EQ(elem0.Type(), YAML::NodeType::Map));
}

}  // namespace