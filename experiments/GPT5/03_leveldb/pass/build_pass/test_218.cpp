// save_error_test_218.cc
#include <gtest/gtest.h>
#include <string>
#include <cstring>

// Pull in the static function's TU so we can exercise it without changing production code.
// IMPORTANT: Ensure db/c.cc is NOT also compiled separately into the test binary.
#include "db/c.cc"

#include "leveldb/status.h"

using leveldb::Status;

class SaveErrorTest_218 : public ::testing::Test {
protected:
  char* err_{nullptr};

  void TearDown() override {
    // Free any allocated buffer to avoid leaks across tests
    if (err_ != nullptr) {
      std::free(err_);
      err_ = nullptr;
    }
  }
};

// Normal operation: OK status -> returns false and does NOT modify *errptr when it is nullptr.
TEST_F(SaveErrorTest_218, OkStatus_NoChangeAndFalse_218) {
  ASSERT_EQ(err_, nullptr);

  Status ok = Status::OK();
  bool changed = SaveError(&err_, ok);

  EXPECT_FALSE(changed);
  EXPECT_EQ(err_, nullptr) << "errptr should remain nullptr for OK status";
}

// Normal operation: OK status -> returns false and does NOT overwrite existing error buffer.
TEST_F(SaveErrorTest_218, OkStatus_ExistingErr_NotOverwritten_218) {
  err_ = strdup("previous error text");
  ASSERT_NE(err_, nullptr);
  char* prev_ptr = err_;
  std::string prev_str = err_;

  Status ok = Status::OK();
  bool changed = SaveError(&err_, ok);

  EXPECT_FALSE(changed);
  EXPECT_EQ(err_, prev_ptr) << "Pointer should remain the same for OK status";
  EXPECT_STREQ(err_, prev_str.c_str()) << "Content should remain unchanged for OK status";
}

// Error case: *errptr == nullptr -> allocates and writes Status::ToString(), returns true.
TEST_F(SaveErrorTest_218, ErrorStatus_NullErrPtr_AllocatesAndTrue_218) {
  ASSERT_EQ(err_, nullptr);

  Status s = Status::IOError("disk exploded");
  std::string expected = s.ToString();

  bool changed = SaveError(&err_, s);

  ASSERT_TRUE(changed);
  ASSERT_NE(err_, nullptr);
  EXPECT_STREQ(err_, expected.c_str());
}

// Error case: *errptr already set -> replaces existing buffer with new message, returns true.
TEST_F(SaveErrorTest_218, ErrorStatus_ReplacesExistingBuffer_218) {
  err_ = strdup("old message");
  ASSERT_NE(err_, nullptr);

  Status s = Status::NotFound("missing key");
  std::string expected = s.ToString();

  bool changed = SaveError(&err_, s);

  ASSERT_TRUE(changed);
  ASSERT_NE(err_, nullptr);
  EXPECT_STREQ(err_, expected.c_str());
}

// Defensive behavior: passing a nullptr for errptr should trigger the assert in debug builds.
// Use a death test so it doesn't crash the whole suite if asserts are enabled.
#if GTEST_HAS_DEATH_TEST
TEST_F(SaveErrorTest_218, NullErrptr_Asserts_218) {
  Status s = Status::Corruption("bad data");
  // Expect the assertion on errptr != nullptr to fail.
  EXPECT_DEATH({ SaveError(nullptr, s); }, "");
}
#endif
