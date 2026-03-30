// SPDX-License-Identifier: GPL-2.0-or-later
// Test ID: 587
//
// Unit tests for Exiv2::MemIo::isopen() based strictly on the public interface.
// We treat MemIo as a black box and only verify observable behavior.

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>

#include "exiv2/basicio.hpp"

namespace {

class MemIoTest_587 : public ::testing::Test {
 protected:
  // Small helper buffer for constructor coverage.
  static constexpr Exiv2::byte kData[4] = {0x00, 0x11, 0x22, 0x33};
};

constexpr Exiv2::byte MemIoTest_587::kData[4];

TEST_F(MemIoTest_587, DefaultConstructed_IsOpenTrue_587) {
  Exiv2::MemIo io;
  EXPECT_TRUE(io.isopen());
}

TEST_F(MemIoTest_587, ConstReference_IsOpenTrue_587) {
  Exiv2::MemIo io;
  const Exiv2::MemIo& cio = io;
  EXPECT_TRUE(cio.isopen());
}

TEST_F(MemIoTest_587, RepeatedCalls_AreConsistentlyTrue_587) {
  Exiv2::MemIo io;
  EXPECT_TRUE(io.isopen());
  EXPECT_TRUE(io.isopen());
  EXPECT_TRUE(io.isopen());
}

TEST_F(MemIoTest_587, ConstructWithNullDataAndZeroSize_IsOpenTrue_587) {
  // Boundary: nullptr with size 0.
  Exiv2::MemIo io(nullptr, 0);
  EXPECT_TRUE(io.isopen());
}

TEST_F(MemIoTest_587, ConstructWithNonEmptyData_IsOpenTrue_587) {
  Exiv2::MemIo io(kData, sizeof(kData));
  EXPECT_TRUE(io.isopen());
}

TEST_F(MemIoTest_587, AfterOpenCall_IsOpenTrue_587) {
  Exiv2::MemIo io;

  // We don't infer open()'s semantics beyond "callable and returns int".
  (void)io.open();

  EXPECT_TRUE(io.isopen());
}

TEST_F(MemIoTest_587, AfterCloseCall_IsOpenTrue_587) {
  Exiv2::MemIo io;

  // Close is part of the public interface; we only observe isopen().
  (void)io.close();

  EXPECT_TRUE(io.isopen());
}

}  // namespace