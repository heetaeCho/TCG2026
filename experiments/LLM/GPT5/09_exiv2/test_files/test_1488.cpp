// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_pentaxmnheader_write_1488.cpp
//
// Unit tests for Exiv2::Internal::PentaxMnHeader::write
//
// Constraints honored:
// - Treat implementation as a black box
// - Verify only observable behavior (return value + bytes written through public I/O)
// - No access to private/internal state

#include <gtest/gtest.h>

#include <vector>
#include <algorithm>

#include "basicio.hpp"
#include "makernote_int.hpp"

namespace {

class PentaxMnHeaderTest_1488 : public ::testing::Test {
protected:
  static std::vector<Exiv2::byte> readAll(Exiv2::BasicIo& io) {
    const auto sz = static_cast<size_t>(io.size());
    std::vector<Exiv2::byte> data(sz);

    io.seek(0, Exiv2::BasicIo::beg);
    if (sz != 0) {
      const long r = io.read(data.data(), static_cast<long>(data.size()));
      data.resize(r < 0 ? 0U : static_cast<size_t>(r));
    }
    return data;
  }
};

TEST_F(PentaxMnHeaderTest_1488, WriteReturnsPositiveSizeAndWritesSameAmount_1488) {
  Exiv2::Internal::PentaxMnHeader header;
  Exiv2::MemIo mem;
  Exiv2::Internal::IoWrapper ioWrapper(mem);

  const size_t n = header.write(ioWrapper, Exiv2::littleEndian);

  EXPECT_GT(n, 0U);
  EXPECT_EQ(static_cast<size_t>(mem.size()), n);

  const auto bytes = readAll(mem);
  EXPECT_EQ(bytes.size(), n);
}

TEST_F(PentaxMnHeaderTest_1488, WriteIsDeterministicAcrossRunsSameByteOrder_1488) {
  Exiv2::Internal::PentaxMnHeader header;

  Exiv2::MemIo mem1;
  Exiv2::Internal::IoWrapper w1(mem1);
  const size_t n1 = header.write(w1, Exiv2::littleEndian);
  const auto b1 = readAll(mem1);

  Exiv2::MemIo mem2;
  Exiv2::Internal::IoWrapper w2(mem2);
  const size_t n2 = header.write(w2, Exiv2::littleEndian);
  const auto b2 = readAll(mem2);

  EXPECT_EQ(n1, n2);
  EXPECT_EQ(b1.size(), b2.size());
  EXPECT_EQ(b1, b2);
}

TEST_F(PentaxMnHeaderTest_1488, WriteResultAndBytesDoNotDependOnByteOrderParam_1488) {
  Exiv2::Internal::PentaxMnHeader header;

  Exiv2::MemIo memLE;
  Exiv2::Internal::IoWrapper wLE(memLE);
  const size_t nLE = header.write(wLE, Exiv2::littleEndian);
  const auto bLE = readAll(memLE);

  Exiv2::MemIo memBE;
  Exiv2::Internal::IoWrapper wBE(memBE);
  const size_t nBE = header.write(wBE, Exiv2::bigEndian);
  const auto bBE = readAll(memBE);

  EXPECT_EQ(nLE, nBE);
  EXPECT_EQ(bLE.size(), bBE.size());
  EXPECT_EQ(bLE, bBE);
}

TEST_F(PentaxMnHeaderTest_1488, MultipleWritesAppendSameSignatureEachTime_1488) {
  Exiv2::Internal::PentaxMnHeader header;
  Exiv2::MemIo mem;
  Exiv2::Internal::IoWrapper ioWrapper(mem);

  const size_t n1 = header.write(ioWrapper, Exiv2::littleEndian);
  const auto after1 = readAll(mem);

  const size_t n2 = header.write(ioWrapper, Exiv2::littleEndian);
  const auto after2 = readAll(mem);

  ASSERT_GT(n1, 0U);
  EXPECT_EQ(n1, n2);

  ASSERT_EQ(after1.size(), n1);
  ASSERT_EQ(after2.size(), n1 + n2);

  // Verify the second write appended an identical block.
  const bool prefix_ok = std::equal(after1.begin(), after1.end(), after2.begin());
  const bool suffix_ok = std::equal(after1.begin(), after1.end(), after2.begin() + static_cast<std::ptrdiff_t>(n1));
  EXPECT_TRUE(prefix_ok);
  EXPECT_TRUE(suffix_ok);
}

}  // namespace