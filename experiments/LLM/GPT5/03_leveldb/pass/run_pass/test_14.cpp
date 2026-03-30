// status_destructor_test.cc
#include "leveldb/status.h"
#include "gtest/gtest.h"

namespace {

using leveldb::Status;

class StatusDestructorTest_14 : public ::testing::Test {};

// Verifies that destroying a default-constructed Status does not crash.
TEST_F(StatusDestructorTest_14, Destructor_DefaultConstructed_14) {
  {
    Status s;  // default constructed; state_ is expected to be null internally
  }
  SUCCEED();
}

// Verifies that destroying an OK() status does not crash.
TEST_F(StatusDestructorTest_14, Destructor_OKStatus_14) {
  {
    Status s = Status::OK();
  }
  SUCCEED();
}

// Verifies that destroying copies of OK() status does not crash.
TEST_F(StatusDestructorTest_14, Destructor_CopyOfOK_14) {
  {
    Status s1 = Status::OK();
    Status s2 = s1;   // copy construction
    (void)s2;
  }
  SUCCEED();
}

// Verifies that destroying both original and copy (same lifetime scope) does not crash.
TEST_F(StatusDestructorTest_14, Destructor_OriginalAndCopy_14) {
  {
    Status s1 = Status::OK();
    Status s2 = s1;   // copy construction
    // Both s1 and s2 go out of scope here.
  }
  SUCCEED();
}

// Verifies that destroying a status after move-construction does not crash
// (i.e., moved-from and moved-to objects are both safely destructible).
TEST_F(StatusDestructorTest_14, Destructor_AfterMoveConstruction_14) {
  {
    Status s1 = Status::OK();
    Status s2 = std::move(s1);  // move-construct
    (void)s2;
    // s1 (moved-from) and s2 (moved-to) both get destroyed at scope end.
  }
  SUCCEED();
}

// Verifies that destroying a status after move-assignment does not crash.
TEST_F(StatusDestructorTest_14, Destructor_AfterMoveAssignment_14) {
  {
    Status s1 = Status::OK();
    Status s2;            // default constructed
    s2 = std::move(s1);   // move-assign
    (void)s2;
    // s1 (moved-from) and s2 (moved-to) both get destroyed at scope end.
  }
  SUCCEED();
}

// Verifies that repeated moves and destructions across nested scopes do not crash.
TEST_F(StatusDestructorTest_14, Destructor_ChainedMoves_14) {
  Status s = Status::OK();
  {
    Status a = std::move(s);
    {
      Status b = std::move(a);
      (void)b;
      // b destroyed here
    }
    // a destroyed here (moved-from)
  }
  // s destroyed here (moved-from)
  SUCCEED();
}

}  // namespace
