// SPDX-License-Identifier: GPL-2.0-or-later
// Test file for Exiv2::RemoteIo::write(BasicIo&)
// TEST_ID: 603

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "exiv2/basicio.hpp"

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <vector>

namespace {

using ::testing::_;
using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Invoke;
using ::testing::Return;
using ::testing::SetArrayArgument;

class MockBasicIo : public Exiv2::BasicIo {
 public:
  // Only mock methods that are observable collaborators for RemoteIo::write(BasicIo&).
  MOCK_METHOD(bool, isopen, (), (const, override));
  MOCK_METHOD(bool, eof, (), (const, override));
  MOCK_METHOD(size_t, size, (), (const, override));
  MOCK_METHOD(int, seek, (int64_t offset, Exiv2::BasicIo::Position pos), (override));
  MOCK_METHOD(size_t, read, (Exiv2::byte* buf, size_t rcount), (override));
};

class RemoteIoWriteTest_603 : public ::testing::Test {
 protected:
  Exiv2::RemoteIo remote_;

  void SetUp() override {
    // Ensure RemoteIo has any internal state it may require, without assuming internals.
    // populateFakeData() is part of the public interface.
    remote_.populateFakeData();
  }
};

TEST_F(RemoteIoWriteTest_603, ReturnsZeroWhenSrcNotOpen_603) {
  MockBasicIo src;

  EXPECT_CALL(src, isopen()).WillOnce(Return(false));
  // Should short-circuit and not interact further.
  EXPECT_CALL(src, seek(_, _)).Times(0);
  EXPECT_CALL(src, read(_, _)).Times(0);
  EXPECT_CALL(src, size()).Times(0);
  EXPECT_CALL(src, eof()).Times(0);

  EXPECT_EQ(remote_.write(src), 0u);
}

TEST_F(RemoteIoWriteTest_603, SeeksToBeginningOnOpenSourceEvenIfEmpty_603) {
  MockBasicIo src;

  EXPECT_CALL(src, isopen()).WillOnce(Return(true));

  // RemoteIo::write() seeks to beginning before comparing.
  EXPECT_CALL(src, seek(0, Exiv2::BasicIo::beg)).WillOnce(Return(0));

  // Make the source appear empty and at EOF to avoid additional reads/seeks.
  EXPECT_CALL(src, eof()).WillRepeatedly(Return(true));
  EXPECT_CALL(src, size()).WillRepeatedly(Return(0u));

  EXPECT_CALL(src, read(_, _)).Times(0);

  EXPECT_EQ(remote_.write(src), 0u);
}

TEST_F(RemoteIoWriteTest_603, ReturnsSrcSizeForOpenSource_603) {
  MockBasicIo src;

  constexpr size_t kSize = 7;

  EXPECT_CALL(src, isopen()).WillOnce(Return(true));

  // It should at least seek to the start.
  EXPECT_CALL(src, seek(0, Exiv2::BasicIo::beg)).WillOnce(Return(0));

  // Keep early diff-scan loop minimal.
  EXPECT_CALL(src, eof()).WillRepeatedly(Return(true));

  // Return a stable size. The implementation returns src.size() at the end.
  EXPECT_CALL(src, size()).WillRepeatedly(Return(kSize));

  // If it decides to submit a diff, it will read some bytes; allow it.
  EXPECT_CALL(src, read(_, _))
      .Times(AtLeast(0))
      .WillRepeatedly(Invoke([](Exiv2::byte* buf, size_t n) -> size_t {
        if (buf && n > 0) std::memset(buf, 0, n);
        return n;
      }));

  EXPECT_EQ(remote_.write(src), kSize);
}

TEST_F(RemoteIoWriteTest_603, ReadsFromLeftOffsetWhenThereIsDataToSend_603) {
  MockBasicIo src;

  constexpr size_t kSize = 4;

  EXPECT_CALL(src, isopen()).WillOnce(Return(true));

  // Initial seek to the beginning is required.
  EXPECT_CALL(src, seek(0, Exiv2::BasicIo::beg)).WillOnce(Return(0));

  // Skip the forward scan by reporting EOF immediately.
  EXPECT_CALL(src, eof()).WillRepeatedly(Return(true));

  // Make size non-zero so dataSize may become non-zero and trigger a read from the left offset.
  EXPECT_CALL(src, size()).WillRepeatedly(Return(kSize));

  // If RemoteIo decides to send data, it should seek to 'left' from beg (commonly 0 in this setup).
  // We don't assume exact left/right computation; just that a beg seek can occur again for reading.
  EXPECT_CALL(src, seek(_, Exiv2::BasicIo::beg)).Times(AtLeast(1)).WillRepeatedly(Return(0));

  // If the implementation attempts right-side scanning, it may call seek from end; allow it.
  EXPECT_CALL(src, seek(_, Exiv2::BasicIo::end)).Times(AtLeast(0)).WillRepeatedly(Return(1));

  // Allow reads; fill buffer with deterministic bytes.
  EXPECT_CALL(src, read(_, _))
      .Times(AtLeast(1))
      .WillRepeatedly(Invoke([](Exiv2::byte* buf, size_t n) -> size_t {
        if (buf && n > 0) {
          for (size_t i = 0; i < n; ++i) buf[i] = static_cast<Exiv2::byte>(0xAB);
        }
        return n;
      }));

  EXPECT_EQ(remote_.write(src), kSize);
}

}  // namespace