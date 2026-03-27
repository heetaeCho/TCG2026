// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_nikon2_mn_header_write_1464.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <vector>

#include "basicio.hpp"
#include "makernote_int.hpp"
#include "types.hpp"

namespace {

using Exiv2::ByteOrder;
using Exiv2::Internal::IoWrapper;
using Exiv2::Internal::Nikon2MnHeader;

static std::vector<uint8_t> ReadAll(Exiv2::BasicIo& io) {
  const long sz = io.size();
  if (sz <= 0) return {};
  std::vector<uint8_t> out(static_cast<size_t>(sz));
  io.seek(0, Exiv2::BasicIo::beg);
  const long r = io.read(out.data(), static_cast<long>(out.size()));
  out.resize(r > 0 ? static_cast<size_t>(r) : 0);
  return out;
}

TEST(Nikon2MnHeaderTest_1464, WriteReturnsAndMatchesTargetSize_1464) {
  Nikon2MnHeader hdr;

  Exiv2::MemIo mem;
  IoWrapper w;
  w.setTarget(&mem);

  const size_t n = hdr.write(w, ByteOrder::littleEndian);

  EXPECT_EQ(static_cast<long>(n), mem.size());
  EXPECT_GT(n, 0u);

  const auto bytes = ReadAll(mem);
  EXPECT_EQ(bytes.size(), n);
}

TEST(Nikon2MnHeaderTest_1464, WriteAppendsDeterministicallyOnRepeatedCalls_1464) {
  Nikon2MnHeader hdr;

  Exiv2::MemIo mem;
  IoWrapper w;
  w.setTarget(&mem);

  const size_t n1 = hdr.write(w, ByteOrder::littleEndian);
  const auto first = ReadAll(mem);

  const size_t n2 = hdr.write(w, ByteOrder::littleEndian);
  const auto second = ReadAll(mem);

  ASSERT_EQ(n1, n2);
  ASSERT_EQ(second.size(), n1 + n2);
  ASSERT_EQ(first.size(), n1);

  // Second buffer should be two identical consecutive chunks.
  EXPECT_TRUE(std::equal(second.begin(), second.begin() + static_cast<long>(n1), second.begin() + static_cast<long>(n1)));
  EXPECT_TRUE(std::equal(first.begin(), first.end(), second.begin()));
  EXPECT_TRUE(std::equal(first.begin(), first.end(), second.begin() + static_cast<long>(n1)));
}

TEST(Nikon2MnHeaderTest_1464, ByteOrderDoesNotChangeWrittenBytesOrSize_1464) {
  Nikon2MnHeader hdr;

  Exiv2::MemIo memLE;
  IoWrapper wLE;
  wLE.setTarget(&memLE);

  Exiv2::MemIo memBE;
  IoWrapper wBE;
  wBE.setTarget(&memBE);

  const size_t nLE = hdr.write(wLE, ByteOrder::littleEndian);
  const size_t nBE = hdr.write(wBE, ByteOrder::bigEndian);

  EXPECT_EQ(nLE, nBE);
  EXPECT_EQ(memLE.size(), memBE.size());

  const auto le = ReadAll(memLE);
  const auto be = ReadAll(memBE);
  EXPECT_EQ(le, be);
}

TEST(Nikon2MnHeaderTest_1464, WritePreservesExistingPrefixWhenAppendingAtEnd_1464) {
  Nikon2MnHeader hdr;

  Exiv2::MemIo mem;
  IoWrapper w;
  w.setTarget(&mem);

  const std::vector<uint8_t> prefix = {0x01, 0x02, 0x03, 0xFE, 0xFF};
  ASSERT_EQ(static_cast<long>(prefix.size()), mem.write(prefix.data(), static_cast<long>(prefix.size())));
  ASSERT_EQ(static_cast<long>(prefix.size()), mem.size());

  mem.seek(0, Exiv2::BasicIo::end);
  const size_t n = hdr.write(w, ByteOrder::littleEndian);

  ASSERT_EQ(static_cast<long>(prefix.size() + n), mem.size());

  const auto all = ReadAll(mem);
  ASSERT_GE(all.size(), prefix.size());
  EXPECT_TRUE(std::equal(prefix.begin(), prefix.end(), all.begin()));
}

TEST(Nikon2MnHeaderTest_1464, WriteThrowsWhenIoWrapperHasNoTarget_1464) {
  Nikon2MnHeader hdr;

  IoWrapper w;
  // Intentionally do not set a target. If IoWrapper requires a target, this should be observable.
  EXPECT_ANY_THROW((void)hdr.write(w, ByteOrder::littleEndian));
}

}  // namespace