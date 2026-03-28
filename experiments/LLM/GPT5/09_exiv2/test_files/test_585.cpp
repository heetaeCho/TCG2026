// SPDX-License-Identifier: GPL-2.0-or-later
// Test file for Exiv2::MemIo::size() const
// TEST_ID: 585

#include <gtest/gtest.h>

#include <cstddef>
#include <vector>

#include "exiv2/basicio.hpp"

namespace {

class MemIoSizeTest_585 : public ::testing::Test {};

TEST_F(MemIoSizeTest_585, DefaultConstructed_SizeIsStableAcrossCalls_585) {
  Exiv2::MemIo io;

  const size_t s1 = io.size();
  const size_t s2 = io.size();
  const size_t s3 = static_cast<const Exiv2::MemIo&>(io).size();

  EXPECT_EQ(s1, s2);
  EXPECT_EQ(s2, s3);
}

TEST_F(MemIoSizeTest_585, ConstructWithData_SizeMatchesProvidedSize_585) {
  const std::vector<Exiv2::byte> data = {0x01, 0x02, 0x03, 0x04, 0x05};

  Exiv2::MemIo io(data.data(), data.size());

  EXPECT_EQ(io.size(), data.size());
  EXPECT_EQ(static_cast<const Exiv2::MemIo&>(io).size(), data.size());
}

TEST_F(MemIoSizeTest_585, OpenAndClose_DoNotChangeSize_585) {
  const std::vector<Exiv2::byte> data = {0x10, 0x20, 0x30};

  Exiv2::MemIo io(data.data(), data.size());
  const size_t before = io.size();

  // We don't assume specific return codes; we only verify that size is unaffected.
  (void)io.open();
  (void)io.close();

  EXPECT_EQ(io.size(), before);
}

TEST_F(MemIoSizeTest_585, Reads_DoNotChangeSize_585) {
  const std::vector<Exiv2::byte> data = {0xAA, 0xBB, 0xCC, 0xDD};

  Exiv2::MemIo io(data.data(), data.size());
  const size_t before = io.size();

  (void)io.open();

  // Read via DataBuf-returning overload
  {
    Exiv2::DataBuf buf = io.read(2);
    (void)buf;
    EXPECT_EQ(io.size(), before);
  }

  // Read via buffer overload
  {
    Exiv2::byte out[8] = {};
    const size_t nread = io.read(out, 3);
    (void)nread;
    EXPECT_EQ(io.size(), before);
  }

  (void)io.close();
  EXPECT_EQ(io.size(), before);
}

}  // namespace