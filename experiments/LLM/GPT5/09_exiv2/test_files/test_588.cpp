// SPDX-License-Identifier: MIT
// File: test_memio_close_588.cpp

#include <gtest/gtest.h>

#include <type_traits>

namespace Exiv2 {
// The class is implemented in the codebase (basicio.cpp). We only rely on the
// public interface visible at link-time: Exiv2::MemIo with close().
class MemIo;
}  // namespace Exiv2

class MemIoTest_588 : public ::testing::Test {};

TEST_F(MemIoTest_588, CloseReturnsZero_588) {
  Exiv2::MemIo io;
  EXPECT_EQ(0, io.close());
}

TEST_F(MemIoTest_588, CloseIsIdempotent_ReturnsZeroOnRepeatedCalls_588) {
  Exiv2::MemIo io;
  EXPECT_EQ(0, io.close());
  EXPECT_EQ(0, io.close());
  EXPECT_EQ(0, io.close());
}

TEST_F(MemIoTest_588, CloseDoesNotThrow_588) {
  Exiv2::MemIo io;
  EXPECT_NO_THROW({
    const int rc = io.close();
    (void)rc;
  });
}

TEST_F(MemIoTest_588, CloseOnMultipleInstances_ReturnsZeroEach_588) {
  Exiv2::MemIo io1;
  Exiv2::MemIo io2;

  EXPECT_EQ(0, io1.close());
  EXPECT_EQ(0, io2.close());

  // Boundary-ish: close again after already closed.
  EXPECT_EQ(0, io1.close());
  EXPECT_EQ(0, io2.close());
}