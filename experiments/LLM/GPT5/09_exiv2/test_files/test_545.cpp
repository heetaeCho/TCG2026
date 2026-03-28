// SPDX-License-Identifier: GPL-2.0-or-later
// File: basicio_seekOrThrow_test.cpp
//
// Unit tests for Exiv2::BasicIo::seekOrThrow
// TEST_ID: 545

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"

// Some Exiv2 builds expose ErrorCode via error.hpp; include when available.
#if __has_include("exiv2/error.hpp")
#include "exiv2/error.hpp"
#endif

using ::testing::Return;
using ::testing::StrictMock;

namespace {

// Mock only the external collaborator (virtual seek()).
class MockBasicIo final : public Exiv2::BasicIo {
public:
  MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));
};

// Helper to avoid depending on any specific ErrorCode enumerator name.
static Exiv2::ErrorCode AnyErrorCode(int v = 1) {
  return static_cast<Exiv2::ErrorCode>(v);
}

class BasicIoSeekOrThrowTest_545 : public ::testing::Test {};

TEST_F(BasicIoSeekOrThrowTest_545, SeekCalledWithArgsAndNoThrowOnSuccess_545) {
  StrictMock<MockBasicIo> io;

  const int64_t offset = 123;
  const auto pos = Exiv2::BasicIo::beg;

  EXPECT_CALL(io, seek(offset, pos)).WillOnce(Return(0));

  EXPECT_NO_THROW(io.seekOrThrow(offset, pos, AnyErrorCode()));
}

TEST_F(BasicIoSeekOrThrowTest_545, ThrowsWhenSeekFails_545) {
  StrictMock<MockBasicIo> io;

  const int64_t offset = 7;
  const auto pos = Exiv2::BasicIo::cur;

  EXPECT_CALL(io, seek(offset, pos)).WillOnce(Return(1));

  // We only assert that an exception is observable; type is an implementation detail.
  EXPECT_THROW(io.seekOrThrow(offset, pos, AnyErrorCode(2)), std::exception);
}

TEST_F(BasicIoSeekOrThrowTest_545, BoundaryOffsetZeroPropagatesToSeek_545) {
  StrictMock<MockBasicIo> io;

  const int64_t offset = 0;
  const auto pos = Exiv2::BasicIo::end;

  EXPECT_CALL(io, seek(offset, pos)).WillOnce(Return(0));

  EXPECT_NO_THROW(io.seekOrThrow(offset, pos, AnyErrorCode()));
}

TEST_F(BasicIoSeekOrThrowTest_545, BoundaryNegativeOffsetStillCallsSeekAndMayThrow_545) {
  StrictMock<MockBasicIo> io;

  const int64_t offset = -1;
  const auto pos = Exiv2::BasicIo::beg;

  EXPECT_CALL(io, seek(offset, pos)).WillOnce(Return(-1));

  EXPECT_THROW(io.seekOrThrow(offset, pos, AnyErrorCode(3)), std::exception);
}

}  // namespace