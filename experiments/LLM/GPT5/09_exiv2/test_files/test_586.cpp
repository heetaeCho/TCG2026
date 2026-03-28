// File: test_memio_open_586.cpp
#include <gtest/gtest.h>

#include <cstdint>
#include <vector>

#include "exiv2/basicio.hpp"

namespace {

// Focused fixture for MemIo::open() observable behavior.
class MemIoOpenTest_586 : public ::testing::Test {};

TEST_F(MemIoOpenTest_586, OpenReturnsZeroAndResetsTellAndEof_586) {
  Exiv2::MemIo io;

  // Move away from the initial position if possible (do not assert on seek result).
  (void)io.seek(10, Exiv2::BasicIo::beg);

  const int rc = io.open();
  EXPECT_EQ(0, rc);

  // Observable effects (do not access private state):
  EXPECT_EQ(0u, io.tell());
  EXPECT_FALSE(io.eof());
}

TEST_F(MemIoOpenTest_586, OpenResetsPositionAfterReads_586) {
  const Exiv2::byte data[] = {0x01, 0x02, 0x03, 0x04};
  Exiv2::MemIo io(data, sizeof(data));

  ASSERT_EQ(0, io.open());
  ASSERT_EQ(0u, io.tell());

  // Perform a read to advance position (avoid assuming exact bytes returned).
  (void)io.read(2);
  EXPECT_NE(0u, io.tell());

  // open() should reset position back to 0.
  EXPECT_EQ(0, io.open());
  EXPECT_EQ(0u, io.tell());
  EXPECT_FALSE(io.eof());
}

TEST_F(MemIoOpenTest_586, OpenClearsEofAfterReadingPastEnd_586) {
  const Exiv2::byte data[] = {0xAA, 0xBB, 0xCC};
  Exiv2::MemIo io(data, sizeof(data));

  ASSERT_EQ(0, io.open());
  EXPECT_FALSE(io.eof());

  // Try to read more than available to (likely) reach EOF.
  (void)io.read(sizeof(data) + 10);
  // EOF should become observable after an over-read attempt in typical BasicIo behavior.
  // If implementation differs, this assertion may fail and should be adjusted to the real behavior.
  EXPECT_TRUE(io.eof());

  // open() should clear EOF and reset position.
  EXPECT_EQ(0, io.open());
  EXPECT_FALSE(io.eof());
  EXPECT_EQ(0u, io.tell());
}

TEST_F(MemIoOpenTest_586, OpenIsIdempotentWhenCalledRepeatedly_586) {
  const Exiv2::byte data[] = {0x10, 0x20};
  Exiv2::MemIo io(data, sizeof(data));

  EXPECT_EQ(0, io.open());
  EXPECT_EQ(0u, io.tell());
  EXPECT_FALSE(io.eof());

  // Disturb state a bit.
  (void)io.read(1);
  EXPECT_NE(0u, io.tell());

  // Repeated opens should consistently succeed and reset observable state.
  EXPECT_EQ(0, io.open());
  EXPECT_EQ(0u, io.tell());
  EXPECT_FALSE(io.eof());

  EXPECT_EQ(0, io.open());
  EXPECT_EQ(0u, io.tell());
  EXPECT_FALSE(io.eof());
}

TEST_F(MemIoOpenTest_586, OpenOnEmptyBufferKeepsTellAtZeroAndEofFalse_586) {
  // Construct with no data.
  Exiv2::MemIo io(nullptr, 0);

  EXPECT_EQ(0, io.open());
  EXPECT_EQ(0u, io.tell());
  EXPECT_FALSE(io.eof());

  // Boundary: reading zero bytes should not change position or set eof.
  (void)io.read(static_cast<size_t>(0));
  EXPECT_EQ(0u, io.tell());
  EXPECT_FALSE(io.eof());
}

}  // namespace