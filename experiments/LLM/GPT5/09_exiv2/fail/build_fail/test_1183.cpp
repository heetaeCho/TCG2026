// File: test_offsetwriter_settarget_1183.cpp
#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <cstdint>
#include <vector>

#include "tiffimage_int.hpp"
#include "basicio.hpp"

namespace {

using Exiv2::BasicIo;
using Exiv2::ByteOrder;
using Exiv2::MemIo;
using Exiv2::byte;

using Exiv2::Internal::OffsetId;
using Exiv2::Internal::OffsetWriter;

static std::array<byte, 4> EncodeU32(uint32_t v, ByteOrder bo) {
  std::array<byte, 4> out{};
  if (bo == Exiv2::littleEndian) {
    out[0] = static_cast<byte>(v & 0xFF);
    out[1] = static_cast<byte>((v >> 8) & 0xFF);
    out[2] = static_cast<byte>((v >> 16) & 0xFF);
    out[3] = static_cast<byte>((v >> 24) & 0xFF);
  } else {
    out[3] = static_cast<byte>(v & 0xFF);
    out[2] = static_cast<byte>((v >> 8) & 0xFF);
    out[1] = static_cast<byte>((v >> 16) & 0xFF);
    out[0] = static_cast<byte>((v >> 24) & 0xFF);
  }
  return out;
}

static std::array<byte, 4> Read4(BasicIo& io, uint32_t pos) {
  ASSERT_EQ(0, io.seek(pos, BasicIo::beg));
  std::array<byte, 4> buf{};
  const long n = io.read(buf.data(), static_cast<long>(buf.size()));
  EXPECT_EQ(static_cast<long>(buf.size()), n);
  return buf;
}

static void WritePattern(BasicIo& io, uint32_t size, byte pattern) {
  std::vector<byte> data(size, pattern);
  ASSERT_EQ(0, io.seek(0, BasicIo::beg));
  ASSERT_EQ(static_cast<long>(size), io.write(data.data(), static_cast<long>(size)));
  ASSERT_EQ(0, io.seek(0, BasicIo::beg));
}

class OffsetWriterTest_1183 : public ::testing::Test {
 protected:
  static OffsetId MakeId(int v) {
    return static_cast<OffsetId>(v);
  }
};

}  // namespace

TEST_F(OffsetWriterTest_1183, SetTargetUpdatesWrittenOffset_LittleEndian_1183) {
  OffsetWriter writer;
  const OffsetId id = MakeId(1);
  const uint32_t origin = 8;
  const uint32_t target = 0x11223344u;

  MemIo io;
  WritePattern(io, 32, static_cast<byte>(0xAA));

  writer.setOrigin(id, origin, Exiv2::littleEndian);
  writer.setTarget(id, target);
  writer.writeOffsets(io);

  const auto got = Read4(io, origin);
  const auto expected = EncodeU32(target, Exiv2::littleEndian);
  EXPECT_EQ(expected, got);
}

TEST_F(OffsetWriterTest_1183, SetTargetUpdatesWrittenOffset_BigEndian_1183) {
  OffsetWriter writer;
  const OffsetId id = MakeId(2);
  const uint32_t origin = 4;
  const uint32_t target = 0xA1B2C3D4u;

  MemIo io;
  WritePattern(io, 24, static_cast<byte>(0x55));

  writer.setOrigin(id, origin, Exiv2::bigEndian);
  writer.setTarget(id, target);
  writer.writeOffsets(io);

  const auto got = Read4(io, origin);
  const auto expected = EncodeU32(target, Exiv2::bigEndian);
  EXPECT_EQ(expected, got);
}

TEST_F(OffsetWriterTest_1183, SetTargetForUnknownIdDoesNotModifyIo_1183) {
  OffsetWriter writer;
  const OffsetId known = MakeId(10);
  const OffsetId unknown = MakeId(11);
  const uint32_t origin = 12;

  MemIo io;
  WritePattern(io, 32, static_cast<byte>(0xCC));

  // Only "known" is registered via setOrigin.
  writer.setOrigin(known, origin, Exiv2::littleEndian);

  // Attempt to set target for an ID that was never registered.
  writer.setTarget(unknown, 0x01020304u);

  // Writing offsets should not change bytes at origin for the known entry (since we never set its target),
  // and should not introduce changes for the unknown entry.
  writer.writeOffsets(io);

  const auto got = Read4(io, origin);
  const std::array<byte, 4> unchanged{static_cast<byte>(0xCC), static_cast<byte>(0xCC),
                                      static_cast<byte>(0xCC), static_cast<byte>(0xCC)};
  EXPECT_EQ(unchanged, got);
}

TEST_F(OffsetWriterTest_1183, SetTargetWithoutOriginDoesNotModifyIo_1183) {
  OffsetWriter writer;
  const OffsetId id = MakeId(20);

  MemIo io;
  WritePattern(io, 16, static_cast<byte>(0x7E));

  // No setOrigin call: ID is not registered in writer.
  writer.setTarget(id, 0xDEADBEEFu);

  // Should be safe and should not change the IO buffer.
  writer.writeOffsets(io);

  const auto got0 = Read4(io, 0);
  const std::array<byte, 4> unchanged{static_cast<byte>(0x7E), static_cast<byte>(0x7E),
                                      static_cast<byte>(0x7E), static_cast<byte>(0x7E)};
  EXPECT_EQ(unchanged, got0);
}

TEST_F(OffsetWriterTest_1183, SetTargetOverwritesPreviousTargetForSameId_1183) {
  OffsetWriter writer;
  const OffsetId id = MakeId(30);
  const uint32_t origin = 0;

  MemIo io;
  WritePattern(io, 16, static_cast<byte>(0x00));

  writer.setOrigin(id, origin, Exiv2::littleEndian);

  writer.setTarget(id, 0x00000001u);
  writer.setTarget(id, 0xFFFFFFFFu);
  writer.writeOffsets(io);

  const auto got = Read4(io, origin);
  const auto expected = EncodeU32(0xFFFFFFFFu, Exiv2::littleEndian);
  EXPECT_EQ(expected, got);
}

TEST_F(OffsetWriterTest_1183, BoundaryOriginAtEndMinus4WritesWithinBuffer_1183) {
  OffsetWriter writer;
  const OffsetId id = MakeId(40);
  const uint32_t bufSize = 64;
  const uint32_t origin = bufSize - 4;
  const uint32_t target = 0x01020304u;

  MemIo io;
  WritePattern(io, bufSize, static_cast<byte>(0x99));

  writer.setOrigin(id, origin, Exiv2::bigEndian);
  writer.setTarget(id, target);

  // Should write exactly within the last 4 bytes.
  writer.writeOffsets(io);

  const auto got = Read4(io, origin);
  const auto expected = EncodeU32(target, Exiv2::bigEndian);
  EXPECT_EQ(expected, got);

  // And a byte just before origin remains unchanged (sanity boundary check).
  ASSERT_EQ(0, io.seek(origin - 1, BasicIo::beg));
  byte b = 0;
  EXPECT_EQ(1, io.read(&b, 1));
  EXPECT_EQ(static_cast<byte>(0x99), b);
}