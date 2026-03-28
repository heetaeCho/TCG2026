// SPDX-License-Identifier: GPL-2.0-or-later
// File: memio_read_bytebuf_test_590.cpp

#include <gtest/gtest.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "exiv2/basicio.hpp"

namespace {

using Exiv2::byte;
using Exiv2::MemIo;

class MemIoReadTest_590 : public ::testing::Test {};

TEST_F(MemIoReadTest_590, ReadZeroBytesReturnsZeroAndDoesNotMove_590) {
  const std::array<byte, 4> kData{{0x10, 0x20, 0x30, 0x40}};
  MemIo io(kData.data(), kData.size());

  ASSERT_EQ(0, io.open());

  std::array<byte, 4> out{{0xAA, 0xAA, 0xAA, 0xAA}};
  const auto before = io.tell();

  EXPECT_EQ(0u, io.read(out.data(), 0u));
  EXPECT_EQ(before, io.tell());
  EXPECT_FALSE(io.eof());

  ASSERT_EQ(0, io.close());
}

TEST_F(MemIoReadTest_590, ReadLessThanAvailableCopiesAndAdvances_590) {
  const std::array<byte, 6> kData{{0x01, 0x02, 0x03, 0x04, 0x05, 0x06}};
  MemIo io(kData.data(), kData.size());

  ASSERT_EQ(0, io.open());

  std::array<byte, 4> out{{0, 0, 0, 0}};
  EXPECT_EQ(3u, io.read(out.data(), 3u));
  EXPECT_EQ(3u, io.tell());
  EXPECT_FALSE(io.eof());

  EXPECT_EQ(0x01, out[0]);
  EXPECT_EQ(0x02, out[1]);
  EXPECT_EQ(0x03, out[2]);

  ASSERT_EQ(0, io.close());
}

TEST_F(MemIoReadTest_590, ReadExactlyAvailableAtBeginningDoesNotSetEof_590) {
  const std::array<byte, 3> kData{{0xA1, 0xB2, 0xC3}};
  MemIo io(kData.data(), kData.size());

  ASSERT_EQ(0, io.open());

  std::array<byte, 3> out{{0, 0, 0}};
  EXPECT_EQ(kData.size(), io.read(out.data(), kData.size()));
  EXPECT_EQ(kData.size(), io.tell());

  // Observable contract per implementation: eof is set only when requesting more than available.
  EXPECT_FALSE(io.eof());

  EXPECT_EQ(kData[0], out[0]);
  EXPECT_EQ(kData[1], out[1]);
  EXPECT_EQ(kData[2], out[2]);

  ASSERT_EQ(0, io.close());
}

TEST_F(MemIoReadTest_590, ReadMoreThanAvailableReturnsRemainingAndSetsEof_590) {
  const std::array<byte, 5> kData{{0x11, 0x22, 0x33, 0x44, 0x55}};
  MemIo io(kData.data(), kData.size());

  ASSERT_EQ(0, io.open());

  std::array<byte, 10> out{};
  const auto n = io.read(out.data(), out.size());

  EXPECT_EQ(kData.size(), n);
  EXPECT_EQ(kData.size(), io.tell());
  EXPECT_TRUE(io.eof());

  for (size_t i = 0; i < kData.size(); ++i) {
    EXPECT_EQ(kData[i], out[i]);
  }

  ASSERT_EQ(0, io.close());
}

TEST_F(MemIoReadTest_590, ConsecutiveReadsConsumeDataInOrder_590) {
  const std::array<byte, 8> kData{{0, 1, 2, 3, 4, 5, 6, 7}};
  MemIo io(kData.data(), kData.size());

  ASSERT_EQ(0, io.open());

  std::array<byte, 3> a{{0xFF, 0xFF, 0xFF}};
  std::array<byte, 3> b{{0xFF, 0xFF, 0xFF}};
  std::array<byte, 3> c{{0xFF, 0xFF, 0xFF}};

  EXPECT_EQ(3u, io.read(a.data(), a.size()));
  EXPECT_EQ(3u, io.tell());
  EXPECT_FALSE(io.eof());

  EXPECT_EQ(3u, io.read(b.data(), b.size()));
  EXPECT_EQ(6u, io.tell());
  EXPECT_FALSE(io.eof());

  // Request more than remaining (2 remaining); should read remaining and set eof.
  EXPECT_EQ(2u, io.read(c.data(), c.size()));
  EXPECT_EQ(8u, io.tell());
  EXPECT_TRUE(io.eof());

  EXPECT_EQ(0u, a[0]);
  EXPECT_EQ(1u, a[1]);
  EXPECT_EQ(2u, a[2]);

  EXPECT_EQ(3u, b[0]);
  EXPECT_EQ(4u, b[1]);
  EXPECT_EQ(5u, b[2]);

  EXPECT_EQ(6u, c[0]);
  EXPECT_EQ(7u, c[1]);

  ASSERT_EQ(0, io.close());
}

TEST_F(MemIoReadTest_590, ReadFromEmptyBufferReturnsZeroAndSetsEofWhenRequestingMoreThanZero_590) {
  const std::array<byte, 1> kDummy{{0x00}};
  MemIo io(/*data*/ kDummy.data(), /*size*/ 0u);

  ASSERT_EQ(0, io.open());

  std::array<byte, 4> out{{0xAA, 0xAA, 0xAA, 0xAA}};
  EXPECT_EQ(0u, io.read(out.data(), out.size()));
  EXPECT_EQ(0u, io.tell());
  EXPECT_TRUE(io.eof());

  // Further reads should continue returning 0.
  EXPECT_EQ(0u, io.read(out.data(), 1u));
  EXPECT_EQ(0u, io.tell());
  EXPECT_TRUE(io.eof());

  ASSERT_EQ(0, io.close());
}

}  // namespace