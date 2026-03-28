#include <cstdlib>
#include <cstring>
#include <string>

#include "gtest/gtest.h"
#include "leveldb/status.h"

// We need to declare SaveError since it's a static function in db/c.cc
// For testing purposes, we replicate its signature and include it.
// In practice, you'd need to make it accessible for testing.

static bool SaveError(char** errptr, const leveldb::Status& s) {
  assert(errptr != nullptr);
  if (s.ok()) {
    return false;
  } else if (*errptr == nullptr) {
    *errptr = strdup(s.ToString().c_str());
  } else {
    std::free(*errptr);
    *errptr = strdup(s.ToString().c_str());
  }
  return true;
}

class SaveErrorTest_218 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Clean up any allocated error strings
    if (errptr_ != nullptr) {
      std::free(errptr_);
      errptr_ = nullptr;
    }
  }

  char* errptr_ = nullptr;
};

// Test that an OK status returns false and does not set errptr
TEST_F(SaveErrorTest_218, OkStatusReturnsFalseAndDoesNotSetError_218) {
  leveldb::Status s = leveldb::Status::OK();
  bool result = SaveError(&errptr_, s);
  EXPECT_FALSE(result);
  EXPECT_EQ(errptr_, nullptr);
}

// Test that a NotFound error returns true and sets errptr when it was nullptr
TEST_F(SaveErrorTest_218, NotFoundErrorSetsErrorWhenNull_218) {
  leveldb::Status s = leveldb::Status::NotFound("key not found");
  bool result = SaveError(&errptr_, s);
  EXPECT_TRUE(result);
  EXPECT_NE(errptr_, nullptr);
  std::string err_str(errptr_);
  EXPECT_NE(err_str.find("not found"), std::string::npos);
}

// Test that a Corruption error returns true and sets errptr
TEST_F(SaveErrorTest_218, CorruptionErrorSetsError_218) {
  leveldb::Status s = leveldb::Status::Corruption("data corruption");
  bool result = SaveError(&errptr_, s);
  EXPECT_TRUE(result);
  EXPECT_NE(errptr_, nullptr);
  std::string err_str(errptr_);
  EXPECT_NE(err_str.find("Corruption"), std::string::npos);
}

// Test that an IOError returns true and sets errptr
TEST_F(SaveErrorTest_218, IOErrorSetsError_218) {
  leveldb::Status s = leveldb::Status::IOError("disk failure");
  bool result = SaveError(&errptr_, s);
  EXPECT_TRUE(result);
  EXPECT_NE(errptr_, nullptr);
  std::string err_str(errptr_);
  EXPECT_NE(err_str.find("IO error"), std::string::npos);
}

// Test that a NotSupported error returns true and sets errptr
TEST_F(SaveErrorTest_218, NotSupportedErrorSetsError_218) {
  leveldb::Status s = leveldb::Status::NotSupported("not supported op");
  bool result = SaveError(&errptr_, s);
  EXPECT_TRUE(result);
  EXPECT_NE(errptr_, nullptr);
  std::string err_str(errptr_);
  EXPECT_NE(err_str.find("Not implemented"), std::string::npos);
}

// Test that an InvalidArgument error returns true and sets errptr
TEST_F(SaveErrorTest_218, InvalidArgumentErrorSetsError_218) {
  leveldb::Status s = leveldb::Status::InvalidArgument("bad argument");
  bool result = SaveError(&errptr_, s);
  EXPECT_TRUE(result);
  EXPECT_NE(errptr_, nullptr);
  std::string err_str(errptr_);
  EXPECT_NE(err_str.find("Invalid argument"), std::string::npos);
}

// Test that calling SaveError with an error when errptr already has a value
// replaces the old value
TEST_F(SaveErrorTest_218, ErrorReplacesExistingError_218) {
  // Set an initial error
  leveldb::Status s1 = leveldb::Status::NotFound("first error");
  bool result1 = SaveError(&errptr_, s1);
  EXPECT_TRUE(result1);
  EXPECT_NE(errptr_, nullptr);
  std::string first_err(errptr_);

  // Now set a different error
  leveldb::Status s2 = leveldb::Status::IOError("second error");
  bool result2 = SaveError(&errptr_, s2);
  EXPECT_TRUE(result2);
  EXPECT_NE(errptr_, nullptr);
  std::string second_err(errptr_);

  // The error string should have changed
  EXPECT_NE(first_err, second_err);
  EXPECT_NE(second_err.find("IO error"), std::string::npos);
}

// Test that an OK status after an error does not clear the existing error
TEST_F(SaveErrorTest_218, OkStatusDoesNotClearExistingError_218) {
  // Set an initial error
  leveldb::Status s1 = leveldb::Status::Corruption("some corruption");
  SaveError(&errptr_, s1);
  EXPECT_NE(errptr_, nullptr);
  std::string err_before(errptr_);

  // Now pass OK status
  leveldb::Status s2 = leveldb::Status::OK();
  bool result = SaveError(&errptr_, s2);
  EXPECT_FALSE(result);
  // errptr_ should still have the old error (SaveError doesn't clear on OK)
  EXPECT_NE(errptr_, nullptr);
  std::string err_after(errptr_);
  EXPECT_EQ(err_before, err_after);
}

// Test with error that has two message parts
TEST_F(SaveErrorTest_218, ErrorWithTwoMessageParts_218) {
  leveldb::Status s = leveldb::Status::NotFound("primary msg", "secondary msg");
  bool result = SaveError(&errptr_, s);
  EXPECT_TRUE(result);
  EXPECT_NE(errptr_, nullptr);
  std::string err_str(errptr_);
  // The string should contain both parts of the message
  EXPECT_NE(err_str.find("primary msg"), std::string::npos);
}

// Test multiple consecutive OK statuses don't affect errptr
TEST_F(SaveErrorTest_218, MultipleOkStatusesKeepNullptr_218) {
  for (int i = 0; i < 5; i++) {
    leveldb::Status s = leveldb::Status::OK();
    bool result = SaveError(&errptr_, s);
    EXPECT_FALSE(result);
    EXPECT_EQ(errptr_, nullptr);
  }
}

// Test multiple consecutive errors replace each other properly
TEST_F(SaveErrorTest_218, MultipleConsecutiveErrorsReplaceCorrectly_218) {
  leveldb::Status s1 = leveldb::Status::NotFound("error1");
  SaveError(&errptr_, s1);
  EXPECT_NE(errptr_, nullptr);

  leveldb::Status s2 = leveldb::Status::Corruption("error2");
  SaveError(&errptr_, s2);
  EXPECT_NE(errptr_, nullptr);
  std::string err2(errptr_);
  EXPECT_NE(err2.find("Corruption"), std::string::npos);

  leveldb::Status s3 = leveldb::Status::IOError("error3");
  SaveError(&errptr_, s3);
  EXPECT_NE(errptr_, nullptr);
  std::string err3(errptr_);
  EXPECT_NE(err3.find("IO error"), std::string::npos);
}

// Test that the return value correctly distinguishes OK from error
TEST_F(SaveErrorTest_218, ReturnValueDistinguishesOkFromError_218) {
  leveldb::Status ok = leveldb::Status::OK();
  EXPECT_FALSE(SaveError(&errptr_, ok));

  leveldb::Status err = leveldb::Status::InvalidArgument("test");
  EXPECT_TRUE(SaveError(&errptr_, err));
}
