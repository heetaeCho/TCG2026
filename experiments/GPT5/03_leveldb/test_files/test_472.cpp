// File: status_move_constructor_test_472.cc
#include "leveldb/status.h"
#include <gtest/gtest.h>

using leveldb::Status;

namespace {

// Basic sanity: moving an OK status keeps the value OK, and leaves the source OK.
TEST(StatusMoveTest_472, MoveConstructFromOK_472) {
  Status s1 = Status::OK();
  const std::string before = s1.ToString();

  Status s2 = std::move(s1);

  // Destination remains OK with the same string representation.
  EXPECT_TRUE(s2.ok());
  EXPECT_EQ(before, s2.ToString());

  // Source becomes OK after move (observable via ok()).
  EXPECT_TRUE(s1.ok());
}

// Moving a non-OK status transfers the error and message; source becomes OK.
TEST(StatusMoveTest_472, MoveConstructFromNotFound_TransfersState_472) {
  Status s1 = Status::NotFound("missing key", "in db");
  ASSERT_FALSE(s1.ok());
  const std::string before = s1.ToString();

  Status s2 = std::move(s1);

  // Destination preserves the status semantics and message.
  EXPECT_FALSE(s2.ok());
  EXPECT_TRUE(s2.IsNotFound());
  EXPECT_EQ(before, s2.ToString());

  // Source is cleared to OK.
  EXPECT_TRUE(s1.ok());
}

// Moving an IOError status with a single message works similarly.
TEST(StatusMoveTest_472, MoveConstructFromIOError_TransfersState_472) {
  Status s1 = Status::IOError("disk full");
  ASSERT_FALSE(s1.ok());
  const std::string before = s1.ToString();

  Status s2 = std::move(s1);

  EXPECT_FALSE(s2.ok());
  EXPECT_TRUE(s2.IsIOError());
  EXPECT_EQ(before, s2.ToString());

  EXPECT_TRUE(s1.ok());
}

// Chained moves are safe: final object holds the original state; intermediates are OK.
TEST(StatusMoveTest_472, ChainedMoveConstructors_PreserveEndState_472) {
  Status original = Status::Corruption("bad block", "seg#7");
  ASSERT_FALSE(original.ok());
  const std::string before = original.ToString();

  Status mid = std::move(original);
  EXPECT_TRUE(original.ok());   // moved-from -> OK

  Status final = std::move(mid);
  EXPECT_TRUE(mid.ok());        // moved-from -> OK
  EXPECT_FALSE(final.ok());
  EXPECT_TRUE(final.IsCorruption());
  EXPECT_EQ(before, final.ToString());
}

// Compile-time guarantee: move constructor is noexcept.
TEST(StatusMoveTest_472, MoveConstructorIsNoexcept_472) {
  static_assert(noexcept(Status(std::declval<Status&&>())), "Status move ctor must be noexcept");
  SUCCEED(); // Reaching here means the static_assert passed at compile time.
}

}  // namespace
