// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_asfvideo_headerreader_1045.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <vector>

#include <exiv2/asfvideo.hpp>
#include <exiv2/basicio.hpp>

namespace {

// ASF Header Object GUID: 75B22630-668E-11CF-A6D9-00AA0062CE6C
// Common on-disk byte order used by ASF (little-endian for first 3 fields).
static constexpr Exiv2::byte kAsfHeaderGuid[16] = {
    0x30, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11,
    0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C,
};

static void appendU64Le(std::vector<Exiv2::byte>& out, uint64_t v) {
  for (int i = 0; i < 8; ++i) {
    out.push_back(static_cast<Exiv2::byte>((v >> (8 * i)) & 0xFFu));
  }
}

static std::vector<Exiv2::byte> makeAsfObjectBytes(uint64_t objectSize, size_t payloadFill = 0) {
  std::vector<Exiv2::byte> bytes;
  bytes.insert(bytes.end(), std::begin(kAsfHeaderGuid), std::end(kAsfHeaderGuid));
  appendU64Le(bytes, objectSize);
  bytes.insert(bytes.end(), payloadFill, static_cast<Exiv2::byte>(0x00));
  return bytes;
}

static Exiv2::BasicIo::UniquePtr makeMemIo(const std::vector<Exiv2::byte>& bytes) {
  // MemIo takes a raw buffer and size. Keep backing storage alive by copying into MemIo.
  // Exiv2::MemIo provides ownership of its own internal buffer.
  return Exiv2::BasicIo::UniquePtr(new Exiv2::MemIo(bytes.data(), static_cast<long>(bytes.size())));
}

}  // namespace

// TEST_ID = 1045

TEST(AsfVideoHeaderReaderTest_1045, GetRemainingSize_IsStableAcrossRepeatedCalls_1045) {
  // Arrange: a minimally well-formed ASF-like object: 16-byte GUID + 8-byte size + payload.
  // We do not assume exact parsing rules; we only verify observable invariants.
  const uint64_t objectSize = 64;
  const size_t payloadSize = static_cast<size_t>(objectSize >= 24 ? (objectSize - 24) : 0);
  auto bytes = makeAsfObjectBytes(objectSize, payloadSize);
  auto io = makeMemIo(bytes);

  // Act
  Exiv2::AsfVideo::HeaderReader reader(io);
  const uint64_t r1 = reader.getRemainingSize();
  const uint64_t r2 = reader.getRemainingSize();

  // Assert
  EXPECT_EQ(r1, r2);
}

TEST(AsfVideoHeaderReaderTest_1045, GetRemainingSize_IsWithinReasonableBoundsForWellFormedInput_1045) {
  // Arrange
  const uint64_t objectSize = 128;
  const size_t payloadSize = static_cast<size_t>(objectSize >= 24 ? (objectSize - 24) : 0);
  auto bytes = makeAsfObjectBytes(objectSize, payloadSize);
  auto io = makeMemIo(bytes);

  // Act
  Exiv2::AsfVideo::HeaderReader reader(io);
  const uint64_t remaining = reader.getRemainingSize();

  // Assert (black-box, non-prescriptive): remaining is a uint64_t and should not exceed the object size.
  EXPECT_LE(remaining, objectSize);
}

TEST(AsfVideoHeaderReaderTest_1045, GetRemainingSize_BoundarySizeEqualsHeaderBytes_DoesNotExceedSize_1045) {
  // Arrange: object size set to exactly 24 bytes (GUID + size field, no payload).
  const uint64_t objectSize = 24;
  auto bytes = makeAsfObjectBytes(objectSize, /*payloadFill=*/0);
  auto io = makeMemIo(bytes);

  // Act
  Exiv2::AsfVideo::HeaderReader reader(io);
  const uint64_t remaining = reader.getRemainingSize();

  // Assert: remaining must not exceed reported/encoded object size.
  EXPECT_LE(remaining, objectSize);
}

TEST(AsfVideoHeaderReaderTest_1045, ConstructorOrGetter_ThrowsOnTruncatedHeader_1045) {
  // Arrange: truncated buffer (< 24 bytes total), likely insufficient to read required fields.
  std::vector<Exiv2::byte> bytes(10, static_cast<Exiv2::byte>(0x00));
  auto io = makeMemIo(bytes);

  // Act + Assert: either construction or subsequent access may throw; both are acceptable and observable.
  EXPECT_ANY_THROW({
    Exiv2::AsfVideo::HeaderReader reader(io);
    (void)reader.getRemainingSize();
  });
}

TEST(AsfVideoHeaderReaderTest_1045, ConstructorOrGetter_ThrowsOnObjectSizeSmallerThanHeader_1045) {
  // Arrange: declares an object size smaller than the minimum header (24 bytes).
  // This is an error case observable via exception behavior.
  const uint64_t objectSize = 8;  // invalid boundary
  auto bytes = makeAsfObjectBytes(objectSize, /*payloadFill=*/0);
  auto io = makeMemIo(bytes);

  // Act + Assert
  EXPECT_ANY_THROW({
    Exiv2::AsfVideo::HeaderReader reader(io);
    (void)reader.getRemainingSize();
  });
}