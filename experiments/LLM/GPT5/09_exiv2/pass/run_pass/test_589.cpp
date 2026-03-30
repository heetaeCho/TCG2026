// SPDX-License-Identifier: GPL-2.0-or-later
// Tests for Exiv2::MemIo::read(size_t) DataBuf wrapper
//
// File: test_memio_read_databuf_589.cpp

#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "exiv2/basicio.hpp"
#include "exiv2/types.hpp"

namespace {

using Exiv2::byte;

static std::vector<byte> ToBytes(const char* s) {
  std::vector<byte> out;
  for (const char* p = s; *p != '\0'; ++p) out.push_back(static_cast<byte>(*p));
  return out;
}

static void ExpectBufEquals(const Exiv2::DataBuf& buf, const std::vector<byte>& expected) {
  ASSERT_EQ(buf.size(), expected.size());
  if (expected.empty()) return;
  EXPECT_EQ(0, buf.cmpBytes(/*offset=*/0, expected.data(), expected.size()));
}

class MemIoReadDataBufTest_589 : public ::testing::Test {
 protected:
  // Keep tests resilient: don't assume open() is strictly required; just call it and proceed.
  static void TryOpen(Exiv2::MemIo& io) { (void)io.open(); }
  static void TryClose(Exiv2::MemIo& io) { (void)io.close(); }
};

}  // namespace

TEST_F(MemIoReadDataBufTest_589, ReadExactCountReturnsSameBytes_589) {
  const auto data = ToBytes("ABCDE");
  Exiv2::MemIo io(data.data(), data.size());
  TryOpen(io);

  const auto before = io.tell();
  Exiv2::DataBuf buf = io.read(/*rcount=*/data.size());

  EXPECT_EQ(buf.size(), data.size());
  ExpectBufEquals(buf, data);
  EXPECT_EQ(io.tell(), before + data.size());
}

TEST_F(MemIoReadDataBufTest_589, ReadSmallerThanAvailableReturnsPrefixAndAdvances_589) {
  const auto data = ToBytes("ABCDE");
  Exiv2::MemIo io(data.data(), data.size());
  TryOpen(io);

  Exiv2::DataBuf buf = io.read(/*rcount=*/2);

  ExpectBufEquals(buf, std::vector<byte>({static_cast<byte>('A'), static_cast<byte>('B')}));
  EXPECT_EQ(io.tell(), static_cast<size_t>(2));

  // Next read should continue from the new position.
  Exiv2::DataBuf buf2 = io.read(/*rcount=*/2);
  ExpectBufEquals(buf2, std::vector<byte>({static_cast<byte>('C'), static_cast<byte>('D')}));
  EXPECT_EQ(io.tell(), static_cast<size_t>(4));
}

TEST_F(MemIoReadDataBufTest_589, ReadLargerThanAvailableReturnsAtMostAvailable_589) {
  const auto data = ToBytes("ABC");
  Exiv2::MemIo io(data.data(), data.size());
  TryOpen(io);

  Exiv2::DataBuf buf = io.read(/*rcount=*/10);

  // Observable contract for wrapper: returned size cannot exceed requested count.
  EXPECT_LE(buf.size(), static_cast<size_t>(10));
  // And when reading from a finite in-memory source, it should not exceed total size.
  EXPECT_LE(buf.size(), data.size());

  // We can also validate that whatever was returned matches the beginning of the data,
  // since this is the first read from the start.
  std::vector<byte> expected(data.begin(), data.begin() + buf.size());
  ExpectBufEquals(buf, expected);

  EXPECT_EQ(io.tell(), buf.size());
}

TEST_F(MemIoReadDataBufTest_589, ReadZeroReturnsEmptyAndDoesNotAdvance_589) {
  const auto data = ToBytes("ABCDE");
  Exiv2::MemIo io(data.data(), data.size());
  TryOpen(io);

  const auto before = io.tell();
  Exiv2::DataBuf buf = io.read(/*rcount=*/0);

  EXPECT_EQ(buf.size(), static_cast<size_t>(0));
  EXPECT_EQ(io.tell(), before);
}

TEST_F(MemIoReadDataBufTest_589, ReadFromEmptyMemIoReturnsEmpty_589) {
  Exiv2::MemIo io;  // default constructed: no initial data specified
  TryOpen(io);

  Exiv2::DataBuf buf = io.read(/*rcount=*/5);

  EXPECT_LE(buf.size(), static_cast<size_t>(5));
  EXPECT_EQ(buf.size(), static_cast<size_t>(0));
  EXPECT_EQ(io.tell(), static_cast<size_t>(0));
}

TEST_F(MemIoReadDataBufTest_589, ReadConsumesAllThenFurtherReadReturnsEmpty_589) {
  const auto data = ToBytes("AB");
  Exiv2::MemIo io(data.data(), data.size());
  TryOpen(io);

  Exiv2::DataBuf first = io.read(/*rcount=*/2);
  ExpectBufEquals(first, data);
  EXPECT_EQ(io.tell(), static_cast<size_t>(2));

  Exiv2::DataBuf second = io.read(/*rcount=*/1);
  EXPECT_LE(second.size(), static_cast<size_t>(1));
  EXPECT_EQ(second.size(), static_cast<size_t>(0));
  EXPECT_EQ(io.tell(), static_cast<size_t>(2));
}

TEST_F(MemIoReadDataBufTest_589, ReadAfterSeekReadsFromNewPosition_589) {
  const auto data = ToBytes("ABCDE");
  Exiv2::MemIo io(data.data(), data.size());
  TryOpen(io);

  // Seek to offset 2 from beginning and read 2 bytes -> "CD"
  (void)io.seek(/*offset=*/2, Exiv2::BasicIo::beg);
  EXPECT_EQ(io.tell(), static_cast<size_t>(2));

  Exiv2::DataBuf buf = io.read(/*rcount=*/2);
  ExpectBufEquals(buf, std::vector<byte>({static_cast<byte>('C'), static_cast<byte>('D')}));
  EXPECT_EQ(io.tell(), static_cast<size_t>(4));
}

TEST_F(MemIoReadDataBufTest_589, ReadWhenClosedDoesNotReturnMoreThanRequestedAndDoesNotCrash_589) {
  const auto data = ToBytes("ABCDE");
  Exiv2::MemIo io(data.data(), data.size());

  // Ensure it's closed (whether open is required or not).
  TryOpen(io);
  TryClose(io);

  // Black-box safety: should not crash; returned buffer size must not exceed requested.
  ASSERT_NO_THROW({
    Exiv2::DataBuf buf = io.read(/*rcount=*/3);
    EXPECT_LE(buf.size(), static_cast<size_t>(3));
  });
}