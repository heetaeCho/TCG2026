// File: env_new_appendable_file_test.cc

#include <gtest/gtest.h>
#include "leveldb/env.h"
#include "leveldb/status.h"

namespace leveldb {

class EnvTest_462 : public ::testing::Test {
protected:
  Env env_;
};

// Normal operation-style check: returns NotSupported for a typical filename
TEST_F(EnvTest_462, ReturnsNotSupported_462) {
  WritableFile* out = nullptr;
  Status s = env_.NewAppendableFile("foo/bar.txt", &out);

  EXPECT_FALSE(s.ok());                 // not OK
  EXPECT_TRUE(s.IsNotSupportedError()); // specifically "not supported"
  // Out param should be untouched by the function body we were given.
  EXPECT_EQ(nullptr, out);
}

// Boundary: empty filename should also be NotSupported
TEST_F(EnvTest_462, EmptyFilename_ReturnsNotSupported_462) {
  WritableFile* out = nullptr;
  Status s = env_.NewAppendableFile("", &out);

  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsNotSupportedError());
  EXPECT_EQ(nullptr, out);
}

// Observable error message should mention both the op name and the filename
TEST_F(EnvTest_462, ErrorStringMentionsOpAndFilename_462) {
  WritableFile* out = nullptr;
  const std::string fname = "db/LOG";
  Status s = env_.NewAppendableFile(fname, &out);

  const std::string msg = s.ToString();
  // We avoid asserting exact formatting—only presence of meaningful substrings.
  EXPECT_NE(msg.find("NewAppendableFile"), std::string::npos);
  EXPECT_NE(msg.find(fname), std::string::npos);
}

// Verify the function does not modify a pre-set out param (based on provided body)
TEST_F(EnvTest_462, DoesNotModifyPreSetOutParam_462) {
  // Deliberately use a non-null sentinel pointer value.
  // We are not dereferencing it; just observing whether it changes.
  WritableFile* sentinel = reinterpret_cast<WritableFile*>(0x1);
  WritableFile* out = sentinel;

  Status s = env_.NewAppendableFile("any/file", &out);

  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsNotSupportedError());
  // Given the provided implementation (only returns a Status), out should remain unchanged.
  EXPECT_EQ(sentinel, out);
}

}  // namespace leveldb
