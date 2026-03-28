// SPDX-License-Identifier: MIT
// File: test_remoteio_614.cpp

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>

namespace {

class RemoteIoTest_614 : public ::testing::Test {
 protected:
  Exiv2::RemoteIo io_;
};

TEST_F(RemoteIoTest_614, DefaultConstructed_IsNotOpen_614) {
  // Observable behavior: isopen() should reflect whether the object is open.
  EXPECT_FALSE(io_.isopen());
}

TEST_F(RemoteIoTest_614, IsOpen_IsConstCallable_614) {
  // Compile-time / interface check: const object can call isopen().
  const Exiv2::RemoteIo& cio = io_;
  (void)cio.isopen();
  SUCCEED();
}

TEST_F(RemoteIoTest_614, OpenThenClose_TogglesIsOpen_614) {
  EXPECT_FALSE(io_.isopen());

  const int open_rc = io_.open();
  (void)open_rc;  // Return value semantics are not assumed here.
  EXPECT_TRUE(io_.isopen());

  const int close_rc = io_.close();
  (void)close_rc;
  EXPECT_FALSE(io_.isopen());
}

TEST_F(RemoteIoTest_614, CloseWhenNotOpen_LeavesIsOpenFalse_614) {
  EXPECT_FALSE(io_.isopen());

  const int close_rc = io_.close();
  (void)close_rc;

  EXPECT_FALSE(io_.isopen());
}

TEST_F(RemoteIoTest_614, OpenTwice_IsStillOpen_614) {
  EXPECT_FALSE(io_.isopen());

  const int rc1 = io_.open();
  (void)rc1;
  EXPECT_TRUE(io_.isopen());

  // Boundary-ish scenario: opening again should not make it "not open".
  const int rc2 = io_.open();
  (void)rc2;
  EXPECT_TRUE(io_.isopen());

  (void)io_.close();
  EXPECT_FALSE(io_.isopen());
}

TEST_F(RemoteIoTest_614, CloseTwice_IsStillClosed_614) {
  (void)io_.open();
  EXPECT_TRUE(io_.isopen());

  (void)io_.close();
  EXPECT_FALSE(io_.isopen());

  // Boundary-ish scenario: closing again should keep it closed.
  (void)io_.close();
  EXPECT_FALSE(io_.isopen());
}

TEST_F(RemoteIoTest_614, PopulateFakeData_MakesIsOpenTrue_614) {
  // Observable behavior expectation based on provided interface name:
  // populateFakeData() should prepare the object for use. We only assert what
  // we can observe: it becomes "open" afterwards.
  EXPECT_FALSE(io_.isopen());

  io_.populateFakeData();
  EXPECT_TRUE(io_.isopen());

  (void)io_.close();
  EXPECT_FALSE(io_.isopen());
}

}  // namespace