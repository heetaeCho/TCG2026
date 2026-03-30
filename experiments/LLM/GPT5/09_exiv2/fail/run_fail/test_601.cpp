// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_remoteio_close_601.cpp

#include <gtest/gtest.h>

#include "exiv2/basicio.hpp"

namespace {

class RemoteIoCloseTest_601 : public ::testing::Test {
 protected:
  Exiv2::RemoteIo io_;
};

TEST_F(RemoteIoCloseTest_601, CloseReturnsZeroWhenBigBlockNull_601) {
  io_.bigBlock_ = nullptr;

  EXPECT_NO_THROW({
    const int rc = io_.close();
    EXPECT_EQ(0, rc);
  });

  // Observable via public member from BasicIo.
  EXPECT_EQ(nullptr, io_.bigBlock_);
}

TEST_F(RemoteIoCloseTest_601, CloseDeletesAndNullsBigBlock_601) {
  // Allocate a buffer to simulate an active bigBlock_.
  io_.bigBlock_ = new Exiv2::byte[16]{};

  EXPECT_NE(nullptr, io_.bigBlock_);

  EXPECT_NO_THROW({
    const int rc = io_.close();
    EXPECT_EQ(0, rc);
  });

  // Observable effect: bigBlock_ becomes nullptr after close().
  EXPECT_EQ(nullptr, io_.bigBlock_);
}

TEST_F(RemoteIoCloseTest_601, CloseIsIdempotentWithBigBlockAllocated_601) {
  io_.bigBlock_ = new Exiv2::byte[8]{};

  EXPECT_NO_THROW({
    EXPECT_EQ(0, io_.close());
  });
  EXPECT_EQ(nullptr, io_.bigBlock_);

  // Calling close again should still succeed and keep state consistent.
  EXPECT_NO_THROW({
    EXPECT_EQ(0, io_.close());
  });
  EXPECT_EQ(nullptr, io_.bigBlock_);
}

TEST_F(RemoteIoCloseTest_601, CloseWorksWithZeroLengthAllocation_601) {
  // Boundary: new[] with zero length is allowed; it may return non-null.
  io_.bigBlock_ = new Exiv2::byte[0];

  EXPECT_NO_THROW({
    EXPECT_EQ(0, io_.close());
  });

  EXPECT_EQ(nullptr, io_.bigBlock_);
}

TEST_F(RemoteIoCloseTest_601, CloseViaBasePointerNullsBigBlock_601) {
  io_.bigBlock_ = new Exiv2::byte[4]{};

  Exiv2::BasicIo* base = &io_;
  EXPECT_NO_THROW({
    EXPECT_EQ(0, base->close());
  });

  EXPECT_EQ(nullptr, io_.bigBlock_);
}

}  // namespace