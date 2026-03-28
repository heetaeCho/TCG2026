// File: yaml-cpp/node/convert_vector_decode_test_612.cpp

#include <gtest/gtest.h>

#include <vector>
#include <string>

#include "yaml-cpp/exceptions.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/type.h"

// Under test: YAML::decode(const Node&, std::vector<T, A>&)
// (Defined in yaml-cpp/node/convert.h in the codebase)
#include "yaml-cpp/node/convert.h"

namespace {

class ConvertVectorDecodeTest_612 : public ::testing::Test {};

TEST_F(ConvertVectorDecodeTest_612, ReturnsFalseWhenNodeIsNotSequenceAndDoesNotModifyRhs_612) {
  YAML::Node node(YAML::NodeType::Scalar);
  node = "abc";

  std::vector<int> rhs = {1, 2, 3};

  const bool ok = YAML::decode(node, rhs);

  EXPECT_FALSE(ok);
  EXPECT_EQ(rhs, (std::vector<int>{1, 2, 3})) << "rhs must remain unchanged on failure";
}

TEST_F(ConvertVectorDecodeTest_612, ClearsAndFillsVectorForIntSequence_612) {
  YAML::Node node(YAML::NodeType::Sequence);
  node.push_back(10);
  node.push_back(20);
  node.push_back(30);

  std::vector<int> rhs = {999, 888};  // should be cleared on success

  const bool ok = YAML::decode(node, rhs);

  ASSERT_TRUE(ok);
  EXPECT_EQ(rhs, (std::vector<int>{10, 20, 30}));
}

TEST_F(ConvertVectorDecodeTest_612, HandlesEmptySequenceByClearingVector_612) {
  YAML::Node node(YAML::NodeType::Sequence);  // empty

  std::vector<std::string> rhs = {"will", "be", "cleared"};

  const bool ok = YAML::decode(node, rhs);

  ASSERT_TRUE(ok);
  EXPECT_TRUE(rhs.empty());
}

TEST_F(ConvertVectorDecodeTest_612, PreservesOrderOfElements_612) {
  YAML::Node node(YAML::NodeType::Sequence);
  node.push_back("first");
  node.push_back("second");
  node.push_back("third");

  std::vector<std::string> rhs;

  const bool ok = YAML::decode(node, rhs);

  ASSERT_TRUE(ok);
  ASSERT_EQ(rhs.size(), 3u);
  EXPECT_EQ(rhs[0], "first");
  EXPECT_EQ(rhs[1], "second");
  EXPECT_EQ(rhs[2], "third");
}

TEST_F(ConvertVectorDecodeTest_612, ThrowsWhenElementCannotBeConvertedToTargetType_612) {
  YAML::Node node(YAML::NodeType::Sequence);
  node.push_back("not_an_int");
  node.push_back("123");  // even if later would convert, first should already fail

  std::vector<int> rhs = {7, 8, 9};

  // decode() does not document catching conversion errors; verify exception is observable.
  EXPECT_THROW({ (void)YAML::decode(node, rhs); }, YAML::BadConversion);
}

TEST_F(ConvertVectorDecodeTest_612, MayPartiallyModifyRhsBeforeThrowingButDoesNotCrash_612) {
  YAML::Node node(YAML::NodeType::Sequence);
  node.push_back(1);
  node.push_back("bad");
  node.push_back(3);

  std::vector<int> rhs = {42};

  // We only assert that an exception is thrown and the call is safe.
  // We intentionally do NOT assert the final contents of rhs here because
  // partial modification is an implementation detail.
  EXPECT_THROW({ (void)YAML::decode(node, rhs); }, YAML::BadConversion);
}

}  // namespace