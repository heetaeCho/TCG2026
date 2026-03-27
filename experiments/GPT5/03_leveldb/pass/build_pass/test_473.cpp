// status_copy_constructor_test.cc
#include <gtest/gtest.h>
#include "leveldb/status.h"

using leveldb::Status;

class StatusCopyConstructorTest_473 : public ::testing::Test {};

// Copies of a default-constructed Status remain OK
TEST_F(StatusCopyConstructorTest_473, CopyFromDefaultIsOK_473) {
  Status s1;                 // default-constructed
  ASSERT_TRUE(s1.ok());

  Status s2(s1);             // copy-construct
  EXPECT_TRUE(s2.ok());
  EXPECT_EQ(s1.ToString(), s2.ToString());
}

// Copy-constructing from Status::OK() yields OK with identical string
TEST_F(StatusCopyConstructorTest_473, CopyFromOKYieldsOK_473) {
  Status ok1 = Status::OK();
  ASSERT_TRUE(ok1.ok());

  Status ok2(ok1);
  EXPECT_TRUE(ok2.ok());
  EXPECT_EQ(ok1.ToString(), ok2.ToString());
}

// Copy-constructing from an error Status preserves its observable properties
TEST_F(StatusCopyConstructorTest_473, CopyFromNotFoundPreservesState_473) {
  Status s1 = Status::NotFound("missing-key");
  ASSERT_TRUE(s1.IsNotFound());
  const std::string before = s1.ToString();

  Status s2(s1);  // copy-construct

  EXPECT_TRUE(s2.IsNotFound());
  EXPECT_EQ(before, s2.ToString());  // identical observable string
}

// Copy is independent of later changes to the source object (deep-copy behavior, by observation)
TEST_F(StatusCopyConstructorTest_473, CopyUnaffectedBySourceReassignment_473) {
  Status s1 = Status::Corruption("bad-block");
  const std::string original_str = s1.ToString();

  Status s2(s1);  // make a copy
  // Reassign the source to a different status
  s1 = Status::IOError("disk-failure");

  // The copy must still reflect the original observable state
  EXPECT_EQ(original_str, s2.ToString());
  EXPECT_TRUE(s2.IsCorruption());
  // And the reassigned source shows the new observable state
  EXPECT_TRUE(s1.IsIOError());
}

// The copy remains valid even if the source is moved-from afterward
TEST_F(StatusCopyConstructorTest_473, CopySurvivesSourceMove_473) {
  Status src = Status::InvalidArgument("bad-arg");
  const std::string snapshot = src.ToString();

  Status copy(src);              // make the copy first
  Status moved(std::move(src));  // move the source

  // The copy should remain identical to the pre-move snapshot
  EXPECT_EQ(snapshot, copy.ToString());
  EXPECT_TRUE(copy.IsInvalidArgument());
  // We do not assert anything about 'src' after move (valid but unspecified).
}

// Copy-construct directly from a temporary error Status
TEST_F(StatusCopyConstructorTest_473, CopyFromTemporaryStatus_473) {
  Status s2(Status::NotSupported("feature-x", " not enabled"));
  EXPECT_TRUE(s2.IsNotSupportedError());
  // ToString should be stable and non-empty for error states
  EXPECT_FALSE(s2.ToString().empty());
}

// Multiple levels of copy preserve observable behavior
TEST_F(StatusCopyConstructorTest_473, MultipleCopyLevelsPreserveBehavior_473) {
  Status base = Status::IOError("io");
  Status c1(base);
  Status c2(c1);

  EXPECT_TRUE(base.IsIOError());
  EXPECT_TRUE(c1.IsIOError());
  EXPECT_TRUE(c2.IsIOError());
  EXPECT_EQ(base.ToString(), c1.ToString());
  EXPECT_EQ(c1.ToString(), c2.ToString());
}
