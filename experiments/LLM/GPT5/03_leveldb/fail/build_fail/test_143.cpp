// File: level_file_num_iterator_status_test_143.cc

#include <gtest/gtest.h>
#include "leveldb/status.h"

// Pull in the implementation so the nested iterator type is visible.
// (We are NOT re-implementing anything; just using the provided interface.)
#include "db/version_set.cc"

namespace leveldb {

// Test suite name must include TEST_ID per requirements.
class LevelFileNumIteratorTest_143 : public ::testing::Test {};

TEST_F(LevelFileNumIteratorTest_143, StatusIsOk_143) {
  // Arrange
  Version::LevelFileNumIterator it;

  // Act
  Status s = it.status();

  // Assert: observable behavior — status reports OK
  EXPECT_TRUE(s.ok());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST_F(LevelFileNumIteratorTest_143, StatusRemainsOkOnRepeatedCalls_143) {
  // Arrange
  Version::LevelFileNumIterator it;

  // Act & Assert: multiple calls should consistently return OK
  for (int i = 0; i < 5; ++i) {
    Status s = it.status();
    EXPECT_TRUE(s.ok()) << "status() call #" << i << " should remain OK";
  }
}

}  // namespace leveldb
