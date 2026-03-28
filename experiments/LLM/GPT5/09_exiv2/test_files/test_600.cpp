// File: test_remoteio_open_600.cpp
#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

#include "exiv2/basicio.hpp"

namespace {

// Spy class to verify that RemoteIo::open() calls close() (virtual dispatch).
class SpyRemoteIo_600 final : public Exiv2::RemoteIo {
 public:
  int close_calls = 0;

  int close() override {
    ++close_calls;
    // Keep it benign: RemoteIo::open() should be able to proceed after a successful close.
    return 0;
  }
};

class RemoteIoOpenTest_600 : public ::testing::Test {};

}  // namespace

TEST_F(RemoteIoOpenTest_600, OpenReturnsZeroAfterPopulateFakeData_600) {
  Exiv2::RemoteIo io;

  // Use only public interface to put the object into a usable state (if needed).
  io.populateFakeData();

  // Normal operation: open should succeed (return 0) without throwing.
  EXPECT_NO_THROW({
    const int rc = io.open();
    EXPECT_EQ(0, rc);
  });
}

TEST_F(RemoteIoOpenTest_600, OpenResetsBigBlockToNullptr_600) {
  Exiv2::RemoteIo io;
  io.populateFakeData();

  // bigBlock_ is publicly visible via BasicIo; ensure open() resets it.
  // Use a non-null sentinel pointer value; it must not be dereferenced.
  io.bigBlock_ = reinterpret_cast<Exiv2::byte*>(static_cast<uintptr_t>(0x1));

  EXPECT_NO_THROW({
    const int rc = io.open();
    EXPECT_EQ(0, rc);
  });

  EXPECT_EQ(nullptr, io.bigBlock_);
}

TEST_F(RemoteIoOpenTest_600, OpenCallsCloseToResetPosition_600) {
  SpyRemoteIo_600 io;

  // Make sure bigBlock_ isn't already null to strengthen the observable effect too.
  io.bigBlock_ = reinterpret_cast<Exiv2::byte*>(static_cast<uintptr_t>(0x1));

  EXPECT_NO_THROW({
    const int rc = io.open();
    EXPECT_EQ(0, rc);
  });

  EXPECT_GE(io.close_calls, 1);
  EXPECT_EQ(nullptr, io.bigBlock_);
}

TEST_F(RemoteIoOpenTest_600, OpenIsRepeatableAndKeepsBigBlockNull_600) {
  Exiv2::RemoteIo io;
  io.populateFakeData();

  ASSERT_NO_THROW({
    const int rc1 = io.open();
    EXPECT_EQ(0, rc1);
  });
  EXPECT_EQ(nullptr, io.bigBlock_);

  // Mutate bigBlock_ between calls to ensure open() re-resets it.
  io.bigBlock_ = reinterpret_cast<Exiv2::byte*>(static_cast<uintptr_t>(0x1));

  ASSERT_NO_THROW({
    const int rc2 = io.open();
    EXPECT_EQ(0, rc2);
  });
  EXPECT_EQ(nullptr, io.bigBlock_);
}