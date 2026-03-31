#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/asfvideo.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/types.hpp>

#include <cstring>
#include <memory>
#include <vector>

// We use MemIo to create controlled in-memory streams for testing
#include <exiv2/basicio.hpp>

namespace {

// Helper to write a uint32_t in little-endian format into a byte buffer
void writeLE32(std::vector<uint8_t>& buf, uint32_t value) {
  buf.push_back(static_cast<uint8_t>(value & 0xFF));
  buf.push_back(static_cast<uint8_t>((value >> 8) & 0xFF));
  buf.push_back(static_cast<uint8_t>((value >> 16) & 0xFF));
  buf.push_back(static_cast<uint8_t>((value >> 24) & 0xFF));
}

// Helper to write a uint64_t in little-endian format into a byte buffer
void writeLE64(std::vector<uint8_t>& buf, uint64_t value) {
  for (int i = 0; i < 8; i++) {
    buf.push_back(static_cast<uint8_t>((value >> (i * 8)) & 0xFF));
  }
}

// Helper to write a GUID (16 bytes) into a byte buffer
void writeGUID(std::vector<uint8_t>& buf, const uint8_t guid[16]) {
  for (int i = 0; i < 16; i++) {
    buf.push_back(guid[i]);
  }
}

// ASF Header Object GUID: 30 26 B2 75 8E 66 CF 11 A6 D9 00 AA 00 62 CE 6C
const uint8_t ASF_HEADER_GUID[16] = {0x30, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11,
                                      0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C};

// ASF File Properties Object GUID: A1 DC AB 8C 47 A9 CF 11 8E E4 00 C0 0C 20 53 65
const uint8_t ASF_FILE_PROPERTIES_GUID[16] = {0xA1, 0xDC, 0xAB, 0x8C, 0x47, 0xA9, 0xCF, 0x11,
                                                0x8E, 0xE4, 0x00, 0xC0, 0x0C, 0x20, 0x53, 0x65};

// A dummy/unknown GUID for blocks that shouldn't match any known handler
const uint8_t UNKNOWN_GUID[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

class AsfVideoTest_1564 : public ::testing::Test {
 protected:
  // Build a minimal valid ASF file that starts with the ASF header object
  // containing zero sub-headers (so decodeHeader iterates 0 times)
  std::vector<uint8_t> buildMinimalAsfFile(uint32_t nb_headers) {
    std::vector<uint8_t> data;

    // ASF Header Object GUID (16 bytes)
    writeGUID(data, ASF_HEADER_GUID);

    // Object Size (8 bytes, little-endian) - we'll fill a reasonable size
    // Size = 16 (GUID) + 8 (size) + 4 (nb_headers) + 2 (reserved) = 30 + block data
    uint64_t headerObjSize = 30;
    // For each sub-header block, we need at minimum: 16 (GUID) + 8 (size) = 24 bytes
    // The block size field says the total size including GUID+size fields
    uint64_t blockSize = 24;  // minimal block: GUID(16) + Size(8) with size=24 (no payload)
    headerObjSize += nb_headers * blockSize;
    writeLE64(data, headerObjSize);

    // Number of Header Objects (4 bytes, little-endian)
    writeLE32(data, nb_headers);

    // Reserved1 (1 byte) and Reserved2 (1 byte) - the 2 bytes skipped by seekOrThrow
    data.push_back(0x01);
    data.push_back(0x02);

    // Now write nb_headers minimal blocks
    for (uint32_t i = 0; i < nb_headers; i++) {
      // Unknown GUID (16 bytes) so decodeBlock just skips
      writeGUID(data, UNKNOWN_GUID);
      // Block size (8 bytes) = 24 (just the GUID + size, no additional data)
      writeLE64(data, blockSize);
    }

    return data;
  }
};

// Test that readMetadata works on a minimal valid ASF file with 0 sub-headers
TEST_F(AsfVideoTest_1564, ReadMetadata_ZeroHeaders_1564) {
  auto data = buildMinimalAsfFile(0);
  auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
  Exiv2::AsfVideo asf(std::move(io));
  EXPECT_NO_THROW(asf.readMetadata());
}

// Test that readMetadata works on a minimal valid ASF file with 1 sub-header
TEST_F(AsfVideoTest_1564, ReadMetadata_OneHeader_1564) {
  auto data = buildMinimalAsfFile(1);
  auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
  Exiv2::AsfVideo asf(std::move(io));
  EXPECT_NO_THROW(asf.readMetadata());
}

// Test that readMetadata works on a minimal valid ASF file with multiple sub-headers
TEST_F(AsfVideoTest_1564, ReadMetadata_MultipleHeaders_1564) {
  auto data = buildMinimalAsfFile(5);
  auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
  Exiv2::AsfVideo asf(std::move(io));
  EXPECT_NO_THROW(asf.readMetadata());
}

// Test that readMetadata throws on empty data (no valid ASF header)
TEST_F(AsfVideoTest_1564, ReadMetadata_EmptyData_Throws_1564) {
  std::vector<uint8_t> data;
  auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
  Exiv2::AsfVideo asf(std::move(io));
  EXPECT_THROW(asf.readMetadata(), Exiv2::Error);
}

// Test that readMetadata throws when data is too short to read the header
TEST_F(AsfVideoTest_1564, ReadMetadata_TruncatedHeader_Throws_1564) {
  // Only write the GUID, but not the rest
  std::vector<uint8_t> data;
  writeGUID(data, ASF_HEADER_GUID);
  // Only partial size field
  data.push_back(0x1E);
  data.push_back(0x00);
  // Truncated here

  auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
  Exiv2::AsfVideo asf(std::move(io));
  EXPECT_THROW(asf.readMetadata(), Exiv2::Error);
}

// Test that readMetadata throws when nb_headers is max uint32 (overflow protection)
TEST_F(AsfVideoTest_1564, ReadMetadata_MaxHeaders_Throws_1564) {
  std::vector<uint8_t> data;

  // ASF Header Object GUID
  writeGUID(data, ASF_HEADER_GUID);

  // Object Size (arbitrary large value)
  writeLE64(data, 30);

  // Number of Header Objects = UINT32_MAX (should trigger enforce failure)
  writeLE32(data, std::numeric_limits<uint32_t>::max());

  // Reserved bytes
  data.push_back(0x01);
  data.push_back(0x02);

  auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
  Exiv2::AsfVideo asf(std::move(io));
  EXPECT_THROW(asf.readMetadata(), Exiv2::Error);
}

// Test that readMetadata throws when data is truncated in the middle of blocks
TEST_F(AsfVideoTest_1564, ReadMetadata_TruncatedBlock_Throws_1564) {
  std::vector<uint8_t> data;

  // ASF Header Object GUID
  writeGUID(data, ASF_HEADER_GUID);

  // Object Size
  writeLE64(data, 54);  // 30 + 24 for one block

  // Number of Header Objects = 2 (but we only provide data for ~1 block)
  writeLE32(data, 2);

  // Reserved bytes
  data.push_back(0x01);
  data.push_back(0x02);

  // Write one complete minimal block
  writeGUID(data, UNKNOWN_GUID);
  writeLE64(data, 24);

  // Second block is truncated (only partial GUID)
  data.push_back(0x00);
  data.push_back(0x00);

  auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
  Exiv2::AsfVideo asf(std::move(io));
  EXPECT_THROW(asf.readMetadata(), Exiv2::Error);
}

// Test mimeType returns expected value
TEST_F(AsfVideoTest_1564, MimeType_ReturnsExpected_1564) {
  auto data = buildMinimalAsfFile(0);
  auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
  Exiv2::AsfVideo asf(std::move(io));
  std::string mime = asf.mimeType();
  EXPECT_FALSE(mime.empty());
  // ASF mime type is typically "video/x-ms-asf"
  EXPECT_EQ(mime, "video/x-ms-asf");
}

// Test writeMetadata throws (ASF writing is typically unsupported)
TEST_F(AsfVideoTest_1564, WriteMetadata_Throws_1564) {
  auto data = buildMinimalAsfFile(0);
  auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
  Exiv2::AsfVideo asf(std::move(io));
  EXPECT_THROW(asf.writeMetadata(), Exiv2::Error);
}

// Test that the AsfVideo constructor creates a valid object
TEST_F(AsfVideoTest_1564, Constructor_CreatesValidObject_1564) {
  auto data = buildMinimalAsfFile(0);
  auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
  Exiv2::AsfVideo asf(std::move(io));
  EXPECT_TRUE(asf.good());
}

// Test readMetadata with missing reserved bytes (truncated after nb_headers)
TEST_F(AsfVideoTest_1564, ReadMetadata_MissingReservedBytes_Throws_1564) {
  std::vector<uint8_t> data;

  // ASF Header Object GUID
  writeGUID(data, ASF_HEADER_GUID);

  // Object Size
  writeLE64(data, 28);

  // Number of Header Objects = 0
  writeLE32(data, 0);

  // No reserved bytes - truncated here

  auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
  Exiv2::AsfVideo asf(std::move(io));
  EXPECT_THROW(asf.readMetadata(), Exiv2::Error);
}

// Test that reading a very small number of headers (boundary: 1) works
TEST_F(AsfVideoTest_1564, ReadMetadata_BoundaryOneHeader_1564) {
  auto data = buildMinimalAsfFile(1);
  auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
  Exiv2::AsfVideo asf(std::move(io));
  EXPECT_NO_THROW(asf.readMetadata());
}

// Test with corrupted nb_headers field (data too short to read DWORD)
TEST_F(AsfVideoTest_1564, ReadMetadata_CorruptedNbHeaders_Throws_1564) {
  std::vector<uint8_t> data;

  // ASF Header Object GUID
  writeGUID(data, ASF_HEADER_GUID);

  // Object Size (8 bytes)
  writeLE64(data, 26);

  // Only 2 bytes of nb_headers instead of 4
  data.push_back(0x00);
  data.push_back(0x00);

  auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
  Exiv2::AsfVideo asf(std::move(io));
  EXPECT_THROW(asf.readMetadata(), Exiv2::Error);
}

}  // namespace
