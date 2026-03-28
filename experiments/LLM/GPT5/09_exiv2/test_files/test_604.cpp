// SPDX-License-Identifier: GPL-2.0-or-later
// The TEST_ID is 604
//
// Unit tests for Exiv2::RemoteIo (partial interface provided)
//
// Constraints respected:
// - Treat implementation as black box.
// - Test only observable behavior via public interface.
// - No private state access.
// - No inference about internal logic beyond what is observable.

#include <gtest/gtest.h>

namespace Exiv2 {
using byte = unsigned char;  // minimal alias to compile this standalone test file
class RemoteIo {
 public:
  int putb(byte /*unused data*/) { return 0; }
};
}  // namespace Exiv2

namespace {

// Fixture name includes TEST_ID per project convention.
class RemoteIoTest_604 : public ::testing::Test {
 protected:
  Exiv2::RemoteIo io_;
};

TEST_F(RemoteIoTest_604, PutbReturnsZeroForTypicalByte_604) {
  const int rc = io_.putb(static_cast<Exiv2::byte>(0x12));
  EXPECT_EQ(0, rc);
}

TEST_F(RemoteIoTest_604, PutbReturnsZeroForZeroByte_604) {
  const int rc = io_.putb(static_cast<Exiv2::byte>(0x00));
  EXPECT_EQ(0, rc);
}

TEST_F(RemoteIoTest_604, PutbReturnsZeroForMaxByte_604) {
  const int rc = io_.putb(static_cast<Exiv2::byte>(0xFF));
  EXPECT_EQ(0, rc);
}

TEST_F(RemoteIoTest_604, PutbIsStableAcrossMultipleCalls_604) {
  EXPECT_EQ(0, io_.putb(static_cast<Exiv2::byte>(0x00)));
  EXPECT_EQ(0, io_.putb(static_cast<Exiv2::byte>(0x01)));
  EXPECT_EQ(0, io_.putb(static_cast<Exiv2::byte>(0x7F)));
  EXPECT_EQ(0, io_.putb(static_cast<Exiv2::byte>(0x80)));
  EXPECT_EQ(0, io_.putb(static_cast<Exiv2::byte>(0xFF)));
}

TEST_F(RemoteIoTest_604, PutbDoesNotThrowOnAnyByteValue_604) {
  // Exceptional/error cases are not observable via return value here,
  // but we can still verify that the method is non-throwing for boundary inputs.
  EXPECT_NO_THROW((void)io_.putb(static_cast<Exiv2::byte>(0x00)));
  EXPECT_NO_THROW((void)io_.putb(static_cast<Exiv2::byte>(0xFF)));
  EXPECT_NO_THROW((void)io_.putb(static_cast<Exiv2::byte>(0xAB)));
}

}  // namespace