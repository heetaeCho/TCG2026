// File: test_filestream_unfilteredrewind_154.cpp
// The TEST_ID is 154

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "poppler/Stream.h"

using ::testing::Return;
using ::testing::StrictMock;

namespace {

// We only verify observable forwarding behavior: FileStream::unfilteredRewind()
// calls rewind() and returns its result (black-box via the public/virtual interface).
class MockFileStream final : public FileStream {
public:
  using FileStream::FileStream; // inherit constructors

  MOCK_METHOD(bool, rewind, (), (override));
};

class FileStreamTest_154 : public ::testing::Test {
protected:
  // Construct without relying on destructor behavior (avoid touching unknown internals).
  // This keeps the test focused on unfilteredRewind() -> rewind() forwarding.
  template <typename T, typename... Args>
  static T *placementNewNoDtor(Args &&...args) {
    alignas(T) static unsigned char storage[sizeof(T)];
    return new (storage) T(std::forward<Args>(args)...);
  }
};

} // namespace

TEST_F(FileStreamTest_154, UnfilteredRewindForwardsAndReturnsTrue_154) {
  // Arrange
  auto *fs = placementNewNoDtor<StrictMock<MockFileStream>>(
      /*fileA=*/nullptr,
      /*startA=*/0,
      /*limitedA=*/false,
      /*lengthA=*/0,
      /*dictA=*/Object());

  EXPECT_CALL(*fs, rewind()).Times(1).WillOnce(Return(true));

  // Act / Assert
  EXPECT_TRUE(fs->unfilteredRewind());
}

TEST_F(FileStreamTest_154, UnfilteredRewindForwardsAndReturnsFalse_154) {
  // Arrange
  auto *fs = placementNewNoDtor<StrictMock<MockFileStream>>(
      /*fileA=*/nullptr,
      /*startA=*/0,
      /*limitedA=*/false,
      /*lengthA=*/0,
      /*dictA=*/Object());

  EXPECT_CALL(*fs, rewind()).Times(1).WillOnce(Return(false));

  // Act / Assert
  EXPECT_FALSE(fs->unfilteredRewind());
}

TEST_F(FileStreamTest_154, UnfilteredRewindCallsRewindEachTime_154) {
  // Arrange
  auto *fs = placementNewNoDtor<StrictMock<MockFileStream>>(
      /*fileA=*/nullptr,
      /*startA=*/0,
      /*limitedA=*/false,
      /*lengthA=*/0,
      /*dictA=*/Object());

  EXPECT_CALL(*fs, rewind())
      .Times(3)
      .WillOnce(Return(true))
      .WillOnce(Return(false))
      .WillOnce(Return(true));

  // Act / Assert
  EXPECT_TRUE(fs->unfilteredRewind());
  EXPECT_FALSE(fs->unfilteredRewind());
  EXPECT_TRUE(fs->unfilteredRewind());
}

TEST_F(FileStreamTest_154, UnfilteredRewindViaBaseStreamPointerForwards_154) {
  // Arrange
  auto *fs = placementNewNoDtor<StrictMock<MockFileStream>>(
      /*fileA=*/nullptr,
      /*startA=*/0,
      /*limitedA=*/false,
      /*lengthA=*/0,
      /*dictA=*/Object());

  BaseStream *base = fs;

  EXPECT_CALL(*fs, rewind()).Times(1).WillOnce(Return(true));

  // Act / Assert
  EXPECT_TRUE(base->unfilteredRewind());
}