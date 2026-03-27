// File: remoteio_seek_test_609.cpp
// TEST_ID: 609
//
// Unit tests for Exiv2::RemoteIo::seek(int64_t, Position)
//
// Constraints respected:
// - Treat RemoteIo as a black box: only use public interface (open/close/populateFakeData/seek/tell/size/eof).
// - No access to private state.
// - No re-implementation beyond what is observable via the interface.

#include <gtest/gtest.h>

#include "exiv2/basicio.hpp"

namespace {

using Exiv2::RemoteIo;
using Exiv2::BasicIo::beg;
using Exiv2::BasicIo::cur;
using Exiv2::BasicIo::end;

class RemoteIoSeekTest_609 : public ::testing::Test {
 protected:
  RemoteIo io_;

  void SetUp() override {
    // If RemoteIo requires open(), attempt it; if it fails, skip tests rather than assume behavior.
    const int rc = io_.open();
    if (rc != 0) {
      GTEST_SKIP() << "RemoteIo::open() failed with rc=" << rc;
    }

    // Populate backing data so size() is meaningful (if implementation provides it).
    io_.populateFakeData();
  }

  void TearDown() override {
    // Best-effort close; do not assert to avoid assuming close semantics.
    (void)io_.close();
  }
};

TEST_F(RemoteIoSeekTest_609, SeekAlwaysReturnsZero_609) {
  // Normal operation: seek should return an int; provided implementation returns 0.
  EXPECT_EQ(0, io_.seek(0, beg));
  EXPECT_EQ(0, io_.seek(0, cur));
  EXPECT_EQ(0, io_.seek(0, end));
}

TEST_F(RemoteIoSeekTest_609, SeekBegZeroSetsTellToZero_609) {
  // Boundary/normal: seeking to beginning with offset 0 should land at 0.
  ASSERT_EQ(0, io_.seek(0, beg));
  EXPECT_EQ(static_cast<size_t>(0), io_.tell());

  // eof() should be observable; do not hard-require true/false beyond what follows from tell/size.
  // Here, at position 0, eof should not be forced true by "past end" seeking.
  EXPECT_FALSE(io_.eof());
}

TEST_F(RemoteIoSeekTest_609, SeekEndZeroSetsTellToSizeAndNotEof_609) {
  // Normal: seek to end with offset 0 should land on size().
  const size_t sz = io_.size();
  ASSERT_EQ(0, io_.seek(0, end));
  EXPECT_EQ(sz, io_.tell());

  // Past-end is defined as strictly greater than size, so at exactly size, eof should be false.
  EXPECT_FALSE(io_.eof());
}

TEST_F(RemoteIoSeekTest_609, SeekBegPastEndClampsTellToSizeAndSetsEof_609) {
  // Boundary/error-like: seeking beyond end should clamp tell() to size() and set eof().
  const size_t sz = io_.size();

  // Use a large positive offset. Avoid overflow risk by staying well within int64_t.
  const int64_t big = static_cast<int64_t>(sz) + 1024;
  ASSERT_EQ(0, io_.seek(big, beg));

  EXPECT_EQ(sz, io_.tell());
  EXPECT_TRUE(io_.eof());
}

TEST_F(RemoteIoSeekTest_609, SeekEndPositiveOffsetClampsTellToSizeAndSetsEof_609) {
  // Boundary/error-like: seek from end with positive offset goes past end -> clamp and eof true.
  const size_t sz = io_.size();
  ASSERT_EQ(0, io_.seek(10, end));

  EXPECT_EQ(sz, io_.tell());
  EXPECT_TRUE(io_.eof());
}

TEST_F(RemoteIoSeekTest_609, SeekCurForwardThenBackwardWithinRange_609) {
  // Normal: move to a mid position (if possible), then seek relative to current.
  const size_t sz = io_.size();
  if (sz < 4) {
    GTEST_SKIP() << "Not enough data (size=" << sz << ") to validate relative seeks meaningfully.";
  }

  // Go to position 2 from beginning.
  ASSERT_EQ(0, io_.seek(2, beg));
  EXPECT_EQ(static_cast<size_t>(2), io_.tell());
  EXPECT_FALSE(io_.eof());

  // Move forward by 1 from current.
  ASSERT_EQ(0, io_.seek(1, cur));
  EXPECT_EQ(static_cast<size_t>(3), io_.tell());
  EXPECT_FALSE(io_.eof());

  // Move backward by 2 from current => should return to position 1.
  ASSERT_EQ(0, io_.seek(-2, cur));
  EXPECT_EQ(static_cast<size_t>(1), io_.tell());
  EXPECT_FALSE(io_.eof());
}

TEST_F(RemoteIoSeekTest_609, SeekBegNegativeOffsetClampsTellToSizeAndDoesNotSetEof_609) {
  // Boundary: negative offset at beg is observable. The provided implementation:
  // - computes newIdx = offset (negative)
  // - assigns idx_ = static_cast<size_t>(newIdx) then clamps idx_ to <= size
  // - sets eof_ based on (newIdx > size), which is false for negative newIdx
  //
  // Therefore: tell() becomes size() (due to clamp), eof() remains false.
  const size_t sz = io_.size();

  ASSERT_EQ(0, io_.seek(-1, beg));
  EXPECT_EQ(sz, io_.tell());
  EXPECT_FALSE(io_.eof());
}

TEST_F(RemoteIoSeekTest_609, SeekCurLargePositiveOffsetClampsTellToSizeAndSetsEof_609) {
  // Boundary/error-like: seeking far forward from current should clamp to size and set eof.
  const size_t sz = io_.size();

  // Ensure current is at 0 to make the intent clear.
  ASSERT_EQ(0, io_.seek(0, beg));
  ASSERT_EQ(static_cast<size_t>(0), io_.tell());

  const int64_t big = static_cast<int64_t>(sz) + 5000;
  ASSERT_EQ(0, io_.seek(big, cur));

  EXPECT_EQ(sz, io_.tell());
  EXPECT_TRUE(io_.eof());
}

}  // namespace