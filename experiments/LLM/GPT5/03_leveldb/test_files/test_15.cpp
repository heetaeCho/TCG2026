// File: status_ok_test_15.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "leveldb/status.h"

using ::testing::HasSubstr;

namespace leveldb {

class StatusOKTest_15 : public ::testing::Test {};

// Normal operation: OK() yields an OK status.
TEST_F(StatusOKTest_15, OK_YieldsOkTrue_15) {
  Status s = Status::OK();
  EXPECT_TRUE(s.ok());
}

// Normal operation: Error-type predicates are all false for OK.
TEST_F(StatusOKTest_15, OK_ErrorPredicatesAreFalse_15) {
  const Status s = Status::OK();
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

// Observable string behavior: ToString() should indicate OK in a user-visible way.
// (We assert it contains "OK" without relying on a specific full format.)
TEST_F(StatusOKTest_15, OK_ToStringIndicatesOK_15) {
  const Status s = Status::OK();
  EXPECT_THAT(s.ToString(), HasSubstr("OK"));
}

// Boundary: Copy construction preserves OK observable behavior.
TEST_F(StatusOKTest_15, CopyConstruction_PreservesOK_15) {
  const Status original = Status::OK();
  Status copy(original);
  EXPECT_TRUE(copy.ok());
  // Original remains a valid observable state
  EXPECT_TRUE(original.ok());
}

// Boundary: Move construction yields an OK observable state for the destination.
// (No assertions on the moved-from object to avoid relying on unspecified state.)
TEST_F(StatusOKTest_15, MoveConstruction_PreservesOKInTarget_15) {
  Status temp = Status::OK();
  Status moved(std::move(temp));
  EXPECT_TRUE(moved.ok());
}

// Boundary: Copy assignment preserves OK observable behavior.
TEST_F(StatusOKTest_15, CopyAssignment_PreservesOK_15) {
  const Status src = Status::OK();
  Status dst = Status::OK();  // initialize; actual prior state shouldn't matter
  dst = src;
  EXPECT_TRUE(dst.ok());
  EXPECT_TRUE(src.ok());
}

// Boundary: Move assignment yields an OK observable state for the target.
// (Again, we avoid asserting on the moved-from object.)
TEST_F(StatusOKTest_15, MoveAssignment_PreservesOKInTarget_15) {
  Status dst;          // whatever its initial state, after assignment it should be OK
  dst = Status::OK();  // move-assign from a temporary OK
  EXPECT_TRUE(dst.ok());
}

// Idempotence-style check: Multiple OK() creations remain OK and consistent via observable API.
TEST_F(StatusOKTest_15, MultipleOKInstances_AllOK_15) {
  const Status a = Status::OK();
  const Status b = Status::OK();
  EXPECT_TRUE(a.ok());
  EXPECT_TRUE(b.ok());
  // Both should indicate OK in their string forms without assuming exact formatting.
  EXPECT_THAT(a.ToString(), HasSubstr("OK"));
  EXPECT_THAT(b.ToString(), HasSubstr("OK"));
}

} // namespace leveldb
