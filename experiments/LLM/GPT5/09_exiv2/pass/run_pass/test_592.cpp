// TEST_ID 592
// File: memio_error_test_592.cpp

#include <gtest/gtest.h>

#include "exiv2/basicio.hpp"

namespace {

class MemIoTest_592 : public ::testing::Test {
 protected:
  static Exiv2::byte kData[4];
};

Exiv2::byte MemIoTest_592::kData[4] = {0x00, 0x11, 0x22, 0x33};

TEST_F(MemIoTest_592, ErrorReturnsZeroOnDefaultConstructed_592) {
  Exiv2::MemIo io;
  EXPECT_EQ(0, io.error());
}

TEST_F(MemIoTest_592, ErrorReturnsZeroOnConstructedWithData_592) {
  Exiv2::MemIo io(kData, sizeof(kData));
  EXPECT_EQ(0, io.error());
}

TEST_F(MemIoTest_592, ErrorCallableOnConstObjectAndReturnsZero_592) {
  const Exiv2::MemIo io;
  EXPECT_EQ(0, io.error());
}

TEST_F(MemIoTest_592, ErrorIsStableAcrossMultipleCalls_592) {
  Exiv2::MemIo io;
  const int first = io.error();
  const int second = io.error();
  const int third = io.error();

  EXPECT_EQ(0, first);
  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(MemIoTest_592, ErrorReturnsIntTypeValueZero_592) {
  Exiv2::MemIo io;
  // This test is intentionally simple and only checks observable behavior.
  int err = io.error();
  EXPECT_EQ(0, err);
}

}  // namespace