// TEST_ID: 570
#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "yaml-cpp/node/node.h"

namespace {

class NodePushBackTest_570 : public ::testing::Test {
 protected:
  YAML::Node MakeSeq() { return YAML::Node(YAML::NodeType::Sequence); }
  YAML::Node MakeScalar(const std::string& s) { return YAML::Node(s); }
};

TEST_F(NodePushBackTest_570, PushBackSingleScalarIncreasesSizeAndStoresValue_570) {
  YAML::Node seq = MakeSeq();
  ASSERT_EQ(seq.size(), 0u);

  YAML::Node rhs = MakeScalar("hello");

  ASSERT_NO_THROW(seq.push_back(rhs));
  EXPECT_EQ(seq.size(), 1u);

  // Verify observable content via public interface.
  EXPECT_EQ(seq[0].as<std::string>(), "hello");
}

TEST_F(NodePushBackTest_570, PushBackMultipleScalarsPreservesOrder_570) {
  YAML::Node seq = MakeSeq();

  std::vector<std::string> values = {"a", "b", "c", "d"};
  for (const auto& v : values) {
    ASSERT_NO_THROW(seq.push_back(MakeScalar(v)));
  }

  ASSERT_EQ(seq.size(), values.size());
  for (std::size_t i = 0; i < values.size(); ++i) {
    EXPECT_EQ(seq[i].as<std::string>(), values[i]);
  }
}

TEST_F(NodePushBackTest_570, PushBackDoesNotModifyRhsNode_570) {
  YAML::Node seq = MakeSeq();

  YAML::Node rhs = MakeScalar("keep-me");
  // Capture observable state of rhs before push_back.
  const bool rhs_defined_before = rhs.IsDefined();
  const auto rhs_type_before = rhs.Type();
  const std::string rhs_scalar_before = rhs.IsScalar() ? rhs.Scalar() : std::string();

  ASSERT_NO_THROW(seq.push_back(rhs));
  ASSERT_EQ(seq.size(), 1u);
  EXPECT_EQ(seq[0].as<std::string>(), "keep-me");

  // Verify rhs observable properties remain the same after being appended.
  EXPECT_EQ(rhs.IsDefined(), rhs_defined_before);
  EXPECT_EQ(rhs.Type(), rhs_type_before);
  if (rhs.IsScalar()) {
    EXPECT_EQ(rhs.Scalar(), rhs_scalar_before);
  }
}

TEST_F(NodePushBackTest_570, PushBackAppendsCopyNotAliasOfScalarValue_570) {
  YAML::Node seq = MakeSeq();

  YAML::Node rhs = MakeScalar("first");
  ASSERT_NO_THROW(seq.push_back(rhs));
  ASSERT_EQ(seq.size(), 1u);
  EXPECT_EQ(seq[0].as<std::string>(), "first");

  // Reassign rhs to a different scalar; appended element should remain unchanged.
  rhs = MakeScalar("second");
  EXPECT_EQ(rhs.as<std::string>(), "second");
  EXPECT_EQ(seq[0].as<std::string>(), "first");
}

TEST_F(NodePushBackTest_570, PushBackManyElementsMaintainsCorrectSize_570) {
  YAML::Node seq = MakeSeq();
  constexpr std::size_t kCount = 100;

  for (std::size_t i = 0; i < kCount; ++i) {
    ASSERT_NO_THROW(seq.push_back(MakeScalar(std::to_string(i))));
  }

  ASSERT_EQ(seq.size(), kCount);
  // Spot-check a few indices for correct observable values.
  EXPECT_EQ(seq[0].as<std::string>(), "0");
  EXPECT_EQ(seq[1].as<std::string>(), "1");
  EXPECT_EQ(seq[42].as<std::string>(), "42");
  EXPECT_EQ(seq[99].as<std::string>(), "99");
}

TEST_F(NodePushBackTest_570, PushBackDefaultConstructedNodeIntoSequenceDoesNotThrow_570) {
  YAML::Node seq = MakeSeq();
  YAML::Node rhs;  // Default constructed node.

  ASSERT_NO_THROW(seq.push_back(rhs));
  EXPECT_EQ(seq.size(), 1u);

  // Only assert properties that are observable without assuming internal semantics.
  // The appended node should be accessible and queryable.
  EXPECT_NO_THROW((void)seq[0].IsDefined());
  EXPECT_NO_THROW((void)seq[0].Type());
}

}  // namespace