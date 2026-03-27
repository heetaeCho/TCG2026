// ***************************************************************** -*- C++ -*-
// Unit tests for Exiv2::MemIo::getb
//
// File: ./TestProjects/exiv2/src/basicio.cpp (partial)
// Interface: exiv2/basicio.hpp
//
// TEST_ID: 591
// *****************************************************************

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>

#include <array>
#include <cstddef>

namespace {

// Fixture kept minimal: MemIo is tested as a black box via public API only.
class MemIoGetbTest_591 : public ::testing::Test {};

TEST_F(MemIoGetbTest_591, ReadsBytesSequentially_591) {
  const std::array<Exiv2::byte, 4> data{{0x00, 0x7f, 0x80, 0xff}};
  Exiv2::MemIo io(data.data(), data.size());

  // Read exactly size() bytes; each getb() should yield the next byte value.
  for (std::size_t i = 0; i < data.size(); ++i) {
    const int v = io.getb();
    ASSERT_NE(v, EOF) << "Unexpected EOF while reading within bounds at index " << i;
    EXPECT_EQ(v, static_cast<int>(data[i])) << "Byte mismatch at index " << i;
    EXPECT_FALSE(io.eof()) << "eof() should remain false while reading within bounds";
  }
}

TEST_F(MemIoGetbTest_591, ReturnsEOFAndSetsEofAfterEnd_591) {
  const std::array<Exiv2::byte, 2> data{{0x12, 0x34}};
  Exiv2::MemIo io(data.data(), data.size());

  // Consume all bytes.
  EXPECT_EQ(io.getb(), static_cast<int>(data[0]));
  EXPECT_FALSE(io.eof());
  EXPECT_EQ(io.getb(), static_cast<int>(data[1]));
  EXPECT_FALSE(io.eof());

  // One more read should hit EOF and make eof() observable as true.
  EXPECT_EQ(io.getb(), EOF);
  EXPECT_TRUE(io.eof());
}

TEST_F(MemIoGetbTest_591, EmptyBufferImmediatelyEOFAndEofTrue_591) {
  // Construct with a null pointer and zero size (common convention).
  Exiv2::MemIo io(nullptr, 0);

  EXPECT_EQ(io.getb(), EOF);
  EXPECT_TRUE(io.eof());
}

TEST_F(MemIoGetbTest_591, RepeatedReadsPastEndStayEOFAndEofStaysTrue_591) {
  const std::array<Exiv2::byte, 1> data{{0xab}};
  Exiv2::MemIo io(data.data(), data.size());

  EXPECT_EQ(io.getb(), static_cast<int>(data[0]));
  EXPECT_FALSE(io.eof());

  // Past end: EOF and eof() true.
  EXPECT_EQ(io.getb(), EOF);
  EXPECT_TRUE(io.eof());

  // Repeated calls should continue to report EOF, and eof() should remain true.
  EXPECT_EQ(io.getb(), EOF);
  EXPECT_TRUE(io.eof());
  EXPECT_EQ(io.getb(), EOF);
  EXPECT_TRUE(io.eof());
}

}  // namespace