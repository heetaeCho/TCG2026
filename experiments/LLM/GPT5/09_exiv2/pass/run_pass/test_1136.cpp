// =================================================================================================
// TEST_ID: 1136
// File: test_types_getUShort_ptr_1136.cpp
// Unit tests for: Exiv2::getUShort(const Exiv2::byte* buf, Exiv2::ByteOrder byteOrder)
// =================================================================================================

#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <vector>

// Exiv2 headers: prefer installed-style include, fall back to local project include if needed.
#if __has_include(<exiv2/types.hpp>)
#include <exiv2/types.hpp>
#elif __has_include("types.hpp")
#include "types.hpp"
#else
#include "exiv2/types.hpp"
#endif

namespace {

class GetUShortPtrTest_1136 : public ::testing::Test {};

TEST_F(GetUShortPtrTest_1136, LittleEndianReadsFirstTwoBytes_1136) {
  const std::array<Exiv2::byte, 2> buf{{static_cast<Exiv2::byte>(0x34), static_cast<Exiv2::byte>(0x12)}};

  const uint16_t vLittle = Exiv2::getUShort(buf.data(), Exiv2::littleEndian);
  const uint16_t vBig = Exiv2::getUShort(buf.data(), Exiv2::bigEndian);

  EXPECT_EQ(vLittle, static_cast<uint16_t>(0x1234));
  EXPECT_EQ(vBig, static_cast<uint16_t>(0x3412));
}

TEST_F(GetUShortPtrTest_1136, BigEndianReadsFirstTwoBytes_1136) {
  const std::array<Exiv2::byte, 2> buf{{static_cast<Exiv2::byte>(0x12), static_cast<Exiv2::byte>(0x34)}};

  const uint16_t vBig = Exiv2::getUShort(buf.data(), Exiv2::bigEndian);
  const uint16_t vLittle = Exiv2::getUShort(buf.data(), Exiv2::littleEndian);

  EXPECT_EQ(vBig, static_cast<uint16_t>(0x1234));
  EXPECT_EQ(vLittle, static_cast<uint16_t>(0x3412));
}

TEST_F(GetUShortPtrTest_1136, IgnoresExtraBytesBeyondFirstTwo_1136) {
  const std::array<Exiv2::byte, 4> buf{{static_cast<Exiv2::byte>(0xAA), static_cast<Exiv2::byte>(0xBB),
                                        static_cast<Exiv2::byte>(0xCC), static_cast<Exiv2::byte>(0xDD)}};

  const uint16_t vLittle = Exiv2::getUShort(buf.data(), Exiv2::littleEndian);
  const uint16_t vBig = Exiv2::getUShort(buf.data(), Exiv2::bigEndian);

  EXPECT_EQ(vLittle, static_cast<uint16_t>(0xBBAA));
  EXPECT_EQ(vBig, static_cast<uint16_t>(0xAABB));
}

TEST_F(GetUShortPtrTest_1136, BoundaryValuesZeroAndMax_1136) {
  {
    const std::array<Exiv2::byte, 2> buf{{static_cast<Exiv2::byte>(0x00), static_cast<Exiv2::byte>(0x00)}};
    EXPECT_EQ(Exiv2::getUShort(buf.data(), Exiv2::littleEndian), static_cast<uint16_t>(0x0000));
    EXPECT_EQ(Exiv2::getUShort(buf.data(), Exiv2::bigEndian), static_cast<uint16_t>(0x0000));
  }

  {
    const std::array<Exiv2::byte, 2> buf{{static_cast<Exiv2::byte>(0xFF), static_cast<Exiv2::byte>(0xFF)}};
    EXPECT_EQ(Exiv2::getUShort(buf.data(), Exiv2::littleEndian), static_cast<uint16_t>(0xFFFF));
    EXPECT_EQ(Exiv2::getUShort(buf.data(), Exiv2::bigEndian), static_cast<uint16_t>(0xFFFF));
  }
}

TEST_F(GetUShortPtrTest_1136, WorksWithUnalignedPointer_1136) {
  // Create a buffer where the ushort begins at a non-zero offset.
  // We only validate observable return values for the two bytes at the pointer.
  const std::vector<Exiv2::byte> storage{
      static_cast<Exiv2::byte>(0x00), static_cast<Exiv2::byte>(0x78), static_cast<Exiv2::byte>(0x56),
      static_cast<Exiv2::byte>(0x00)};

  const Exiv2::byte* p = &storage[1];  // points to 0x78, 0x56
  EXPECT_EQ(Exiv2::getUShort(p, Exiv2::littleEndian), static_cast<uint16_t>(0x5678));
  EXPECT_EQ(Exiv2::getUShort(p, Exiv2::bigEndian), static_cast<uint16_t>(0x7856));
}

}  // namespace