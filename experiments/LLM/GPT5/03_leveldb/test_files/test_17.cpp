// status_corruption_test_17.cc
#include <gtest/gtest.h>
#include "leveldb/status.h"
#include "leveldb/slice.h"

namespace leveldb {

class StatusCorruptionTest_17 : public ::testing::Test {};

TEST_F(StatusCorruptionTest_17, IsCorruptionAndNotOk_17) {
  Status s = Status::Corruption(Slice("primary message"));
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());

  // ToString should be callable and return something (format is not asserted).
  const std::string str = s.ToString();
  EXPECT_FALSE(str.empty());
}

TEST_F(StatusCorruptionTest_17, DefaultSecondMessage_17) {
  // When msg2 is omitted, behavior should still be Corruption and ok() should be false.
  Status s = Status::Corruption(Slice("only one msg"));
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_FALSE(s.ok());

  // The primary message should appear in the string representation.
  const std::string str = s.ToString();
  EXPECT_NE(str.find("only one msg"), std::string::npos);
}

TEST_F(StatusCorruptionTest_17, TwoMessagesAppearInToString_17) {
  Status s = Status::Corruption(Slice("first"), Slice("second"));
  ASSERT_TRUE(s.IsCorruption());
  const std::string str = s.ToString();
  EXPECT_NE(str.find("first"), std::string::npos);
  EXPECT_NE(str.find("second"), std::string::npos);
}

TEST_F(StatusCorruptionTest_17, CopyConstructorPreservesState_17) {
  Status original = Status::Corruption(Slice("copy-ctor test"), Slice("extra"));
  Status copy(original);

  EXPECT_TRUE(copy.IsCorruption());
  EXPECT_FALSE(copy.ok());

  // Observable text should match.
  EXPECT_EQ(original.ToString(), copy.ToString());
}

TEST_F(StatusCorruptionTest_17, CopyAssignmentPreservesState_17) {
  Status src = Status::Corruption(Slice("copy-assign test"), Slice("extra"));
  Status dst = Status::OK();  // Start with a different state to observe change.
  dst = src;

  EXPECT_TRUE(dst.IsCorruption());
  EXPECT_FALSE(dst.ok());
  EXPECT_EQ(src.ToString(), dst.ToString());
}

TEST_F(StatusCorruptionTest_17, MoveConstructorTransfersState_17) {
  Status temp = Status::Corruption(Slice("move-ctor test"), Slice("x"));
  const std::string expected = temp.ToString();

  Status moved(std::move(temp));
  EXPECT_TRUE(moved.IsCorruption());
  EXPECT_FALSE(moved.ok());
  EXPECT_EQ(expected, moved.ToString());

  // We make no assertions about the moved-from object's predicates, as its
  // state is not specified by the interface.
}

TEST_F(StatusCorruptionTest_17, MoveAssignmentTransfersState_17) {
  Status temp = Status::Corruption(Slice("move-assign test"), Slice("y"));
  const std::string expected = temp.ToString();

  Status target = Status::OK();  // Different initial state
  target = std::move(temp);

  EXPECT_TRUE(target.IsCorruption());
  EXPECT_FALSE(target.ok());
  EXPECT_EQ(expected, target.ToString());
}

TEST_F(StatusCorruptionTest_17, PredicateExclusivity_17) {
  Status s = Status::Corruption(Slice("predicates"));
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST_F(StatusCorruptionTest_17, HandlesEmptyMessages_17) {
  // Exercise boundary with empty msg and empty msg2.
  Status s = Status::Corruption(Slice(), Slice());
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_FALSE(s.ok());

  // ToString should still be usable and non-empty (not asserting format).
  const std::string str = s.ToString();
  EXPECT_FALSE(str.empty());
}

}  // namespace leveldb
