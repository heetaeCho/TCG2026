// TEST_ID 612
// Unit tests for Exiv2::RemoteIo (black-box) - focusing on observable tell()/seek()/read()/putb() behavior.
//
// File under test (partial): ./TestProjects/exiv2/src/basicio.cpp
// Interface reference: exiv2/basicio.hpp

#include <gtest/gtest.h>

#include <cstdint>
#include <vector>

#include "exiv2/basicio.hpp"

namespace {

class RemoteIoTest_612 : public ::testing::Test {
 protected:
  Exiv2::RemoteIo io_;
};

TEST_F(RemoteIoTest_612, TellIsStableAcrossConsecutiveCalls_612) {
  const size_t t1 = io_.tell();
  const size_t t2 = io_.tell();
  EXPECT_EQ(t1, t2);
}

TEST_F(RemoteIoTest_612, SeekToBeginningSetsTellToZeroIfSeekSucceeds_612) {
  (void)io_.open();  // Some implementations may require open(); do not assert on return.

  const int rc = io_.seek(0, Exiv2::BasicIo::beg);
  if (rc == 0) {
    EXPECT_EQ(0u, io_.tell());
  }
}

TEST_F(RemoteIoTest_612, SeekCurWithZeroOffsetKeepsTellIfSeekSucceeds_612) {
  (void)io_.open();

  const size_t before = io_.tell();
  const int rc = io_.seek(0, Exiv2::BasicIo::cur);
  if (rc == 0) {
    EXPECT_EQ(before, io_.tell());
  }
}

TEST_F(RemoteIoTest_612, SeekBeyondCurrentSizeEitherFailsOrMovesTellToRequested_612) {
  (void)io_.open();

  const size_t before = io_.tell();
  const size_t sz = io_.size();

  // Attempt to seek one past the end (boundary-ish). Behavior is implementation-defined:
  // - it may fail, or
  // - it may allow seeking past end.
  const int rc = io_.seek(static_cast<int64_t>(sz + 1u), Exiv2::BasicIo::beg);
  if (rc == 0) {
    EXPECT_EQ(sz + 1u, io_.tell());
  } else {
    // If it fails, tell() should remain a valid position; conservatively expect it didn't change.
    EXPECT_EQ(before, io_.tell());
  }
}

TEST_F(RemoteIoTest_612, ReadWithNonZeroRequestEitherAdvancesTellByBytesReadOrLeavesItUnchanged_612) {
  // Try to ensure there is something to read.
  io_.populateFakeData();
  (void)io_.open();
  (void)io_.seek(0, Exiv2::BasicIo::beg);

  const size_t before = io_.tell();

  std::vector<Exiv2::byte> buf(8);
  const size_t n = io_.read(buf.data(), buf.size());

  const size_t after = io_.tell();
  if (n > 0) {
    EXPECT_EQ(before + n, after);
  } else {
    EXPECT_EQ(before, after);
  }
}

TEST_F(RemoteIoTest_612, PutbEitherAdvancesTellByOneOnSuccessOrLeavesItUnchangedOnFailure_612) {
  (void)io_.open();

  const size_t before = io_.tell();
  const int rc = io_.putb(static_cast<Exiv2::byte>(0x7F));

  const size_t after = io_.tell();
  if (rc == 0) {
    EXPECT_EQ(before + 1u, after);
  } else {
    EXPECT_EQ(before, after);
  }
}

TEST_F(RemoteIoTest_612, SeekWithInvalidPositionDoesNotCrashAndDoesNotChangeTellOnFailure_612) {
  (void)io_.open();

  const size_t before = io_.tell();
  const auto invalidPos = static_cast<Exiv2::BasicIo::Position>(999);

  // We only assert observable stability: no crash; if it reports failure, tell() unchanged.
  const int rc = io_.seek(0, invalidPos);
  if (rc != 0) {
    EXPECT_EQ(before, io_.tell());
  }
}

}  // namespace