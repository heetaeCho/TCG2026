// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_memio_mmap_582.cpp
//
// Unit tests for Exiv2::MemIo::mmap(bool)
// TEST_ID: 582

#include <gtest/gtest.h>

#include <cstring>
#include <vector>

#include "exiv2/basicio.hpp"

namespace {

class MemIoMmapTest_582 : public ::testing::Test {};

TEST_F(MemIoMmapTest_582, MmapReturnsStablePointerForSameMode_582) {
  Exiv2::MemIo io;

  const Exiv2::byte kData[] = {0x10, 0x20, 0x30, 0x40};
  ASSERT_EQ(static_cast<long>(sizeof(kData)), io.write(kData, static_cast<long>(sizeof(kData))));

  Exiv2::byte* p1 = io.mmap(false);
  Exiv2::byte* p2 = io.mmap(false);

  // Observable behavior: repeated mmap() calls should be stable.
  EXPECT_EQ(p1, p2);

  // After writing data, mapping is expected to point to some buffer.
  EXPECT_NE(p1, nullptr);
}

TEST_F(MemIoMmapTest_582, MmapIgnoresIsWriteableFlag_582) {
  Exiv2::MemIo io;

  const Exiv2::byte kData[] = {0xAA, 0xBB, 0xCC};
  ASSERT_EQ(static_cast<long>(sizeof(kData)), io.write(kData, static_cast<long>(sizeof(kData))));

  Exiv2::byte* pr = io.mmap(false);
  Exiv2::byte* pw = io.mmap(true);

  // Interface-visible behavior for this implementation: both calls expose the same mapped base.
  EXPECT_EQ(pr, pw);
}

TEST_F(MemIoMmapTest_582, MappedBufferContainsWrittenBytes_582) {
  Exiv2::MemIo io;

  const Exiv2::byte kData[] = {0x01, 0x02, 0xFE, 0xFF, 0x7F};
  const long kSize = static_cast<long>(sizeof(kData));
  ASSERT_EQ(kSize, io.write(kData, kSize));

  Exiv2::byte* p = io.mmap(false);
  ASSERT_NE(p, nullptr);

  EXPECT_EQ(0, std::memcmp(p, kData, static_cast<size_t>(kSize)));
}

TEST_F(MemIoMmapTest_582, ModifyingMappedBufferIsObservableViaRead_582) {
  Exiv2::MemIo io;

  const Exiv2::byte kData[] = {0x11, 0x22, 0x33};
  const long kSize = static_cast<long>(sizeof(kData));
  ASSERT_EQ(kSize, io.write(kData, kSize));

  Exiv2::byte* p = io.mmap(true);
  ASSERT_NE(p, nullptr);

  // Modify mapped bytes.
  p[0] = static_cast<Exiv2::byte>(p[0] ^ 0xFF);
  p[2] = static_cast<Exiv2::byte>(p[2] + 1);

  // Read back through the public interface.
  ASSERT_EQ(0L, io.seek(0L, Exiv2::BasicIo::beg));

  std::vector<Exiv2::byte> out(static_cast<size_t>(kSize));
  ASSERT_EQ(kSize, io.read(out.data(), kSize));

  EXPECT_EQ(out[0], p[0]);
  EXPECT_EQ(out[1], p[1]);
  EXPECT_EQ(out[2], p[2]);
}

TEST_F(MemIoMmapTest_582, MmapOnEmptyInstanceIsStable_582) {
  Exiv2::MemIo io;

  Exiv2::byte* p1 = io.mmap(false);
  Exiv2::byte* p2 = io.mmap(false);
  Exiv2::byte* p3 = io.mmap(true);

  // Don’t assume null vs non-null; only that the returned base pointer is stable/consistent.
  EXPECT_EQ(p1, p2);
  EXPECT_EQ(p1, p3);
}

}  // namespace