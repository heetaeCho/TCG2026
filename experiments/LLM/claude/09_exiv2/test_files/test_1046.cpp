#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/asfvideo.hpp>
#include <exiv2/basicio.hpp>
#include <cstring>
#include <fstream>
#include <sstream>

// Helper to create a temporary file with specific content
class TempFile {
 public:
  explicit TempFile(const std::string& name, const std::vector<uint8_t>& data)
      : filename_(name) {
    std::ofstream ofs(filename_, std::ios::binary);
    ofs.write(reinterpret_cast<const char*>(data.data()), data.size());
    ofs.close();
  }
  ~TempFile() { std::remove(filename_.c_str()); }
  const std::string& path() const { return filename_; }

 private:
  std::string filename_;
};

// ASF Header GUID: 30 26 B2 75 8E 66 CF 11 A6 D9 00 AA 00 62 CE 6C
// Followed by 8-byte little-endian size

class AsfVideoHeaderReaderTest_1046 : public ::testing::Test {
 protected:
  // Create a minimal valid ASF-like data buffer
  // GUID (16 bytes) + size (8 bytes) = 24 bytes minimum for HeaderReader
  std::vector<uint8_t> createValidAsfHeader(uint64_t size) {
    std::vector<uint8_t> data;
    // ASF Header Object GUID
    uint8_t guid[] = {0x30, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11,
                      0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C};
    data.insert(data.end(), guid, guid + 16);
    // Size as 8-byte little-endian
    for (int i = 0; i < 8; i++) {
      data.push_back(static_cast<uint8_t>((size >> (i * 8)) & 0xFF));
    }
    // Pad with zeros to satisfy the size
    if (size > 24) {
      data.resize(size, 0);
    }
    return data;
  }

  std::vector<uint8_t> createArbitraryGuidHeader(const uint8_t guid[16], uint64_t size) {
    std::vector<uint8_t> data;
    data.insert(data.end(), guid, guid + 16);
    for (int i = 0; i < 8; i++) {
      data.push_back(static_cast<uint8_t>((size >> (i * 8)) & 0xFF));
    }
    if (size > 24) {
      data.resize(size, 0);
    }
    return data;
  }
};

TEST_F(AsfVideoHeaderReaderTest_1046, GetIdReturnsNonEmptyBuffer_1046) {
  // Create a valid ASF header with minimum size (24 bytes = GUID + size field)
  auto data = createValidAsfHeader(24);
  TempFile tmp("test_getid_1046.asf", data);

  auto io = std::make_unique<Exiv2::FileIo>(tmp.path());
  ASSERT_EQ(io->open(), 0);

  Exiv2::AsfVideo::HeaderReader reader(io);
  auto& id = reader.getId();
  // GUID is 16 bytes
  EXPECT_EQ(id.size(), 16u);
}

TEST_F(AsfVideoHeaderReaderTest_1046, GetIdMatchesExpectedGuid_1046) {
  uint8_t expectedGuid[] = {0x30, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11,
                            0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C};
  auto data = createValidAsfHeader(24);
  TempFile tmp("test_guid_match_1046.asf", data);

  auto io = std::make_unique<Exiv2::FileIo>(tmp.path());
  ASSERT_EQ(io->open(), 0);

  Exiv2::AsfVideo::HeaderReader reader(io);
  auto& id = reader.getId();
  EXPECT_EQ(id.size(), 16u);
  EXPECT_EQ(std::memcmp(id.data(), expectedGuid, 16), 0);
}

TEST_F(AsfVideoHeaderReaderTest_1046, GetSizeReturnsCorrectValue_1046) {
  uint64_t expectedSize = 48;
  auto data = createValidAsfHeader(expectedSize);
  TempFile tmp("test_getsize_1046.asf", data);

  auto io = std::make_unique<Exiv2::FileIo>(tmp.path());
  ASSERT_EQ(io->open(), 0);

  Exiv2::AsfVideo::HeaderReader reader(io);
  EXPECT_EQ(reader.getSize(), expectedSize);
}

TEST_F(AsfVideoHeaderReaderTest_1046, GetRemainingSizeIsConsistentWithGetSize_1046) {
  uint64_t totalSize = 48;
  auto data = createValidAsfHeader(totalSize);
  TempFile tmp("test_remaining_1046.asf", data);

  auto io = std::make_unique<Exiv2::FileIo>(tmp.path());
  ASSERT_EQ(io->open(), 0);

  Exiv2::AsfVideo::HeaderReader reader(io);
  // remaining_size should be size minus the header (GUID + size field = 24 bytes)
  uint64_t remaining = reader.getRemainingSize();
  uint64_t size = reader.getSize();
  // remaining_size = size - 24 (the 16-byte GUID + 8-byte size field)
  EXPECT_EQ(remaining, size - 24);
}

TEST_F(AsfVideoHeaderReaderTest_1046, GetSizeMinimumHeader_1046) {
  // Minimum valid: 24 bytes (GUID=16 + size=8)
  uint64_t expectedSize = 24;
  auto data = createValidAsfHeader(expectedSize);
  TempFile tmp("test_minsize_1046.asf", data);

  auto io = std::make_unique<Exiv2::FileIo>(tmp.path());
  ASSERT_EQ(io->open(), 0);

  Exiv2::AsfVideo::HeaderReader reader(io);
  EXPECT_EQ(reader.getSize(), expectedSize);
  EXPECT_EQ(reader.getRemainingSize(), 0u);
}

TEST_F(AsfVideoHeaderReaderTest_1046, DifferentGuidIsReadCorrectly_1046) {
  uint8_t customGuid[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                          0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10};
  auto data = createArbitraryGuidHeader(customGuid, 24);
  TempFile tmp("test_custom_guid_1046.asf", data);

  auto io = std::make_unique<Exiv2::FileIo>(tmp.path());
  ASSERT_EQ(io->open(), 0);

  Exiv2::AsfVideo::HeaderReader reader(io);
  auto& id = reader.getId();
  EXPECT_EQ(id.size(), 16u);
  EXPECT_EQ(std::memcmp(id.data(), customGuid, 16), 0);
}

TEST_F(AsfVideoHeaderReaderTest_1046, LargeSizeValue_1046) {
  // Test with a large size value but only 24 bytes of actual data
  // The HeaderReader should still read the size field correctly
  uint64_t largeSize = 1000000;
  std::vector<uint8_t> data;
  uint8_t guid[] = {0x30, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11,
                    0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C};
  data.insert(data.end(), guid, guid + 16);
  for (int i = 0; i < 8; i++) {
    data.push_back(static_cast<uint8_t>((largeSize >> (i * 8)) & 0xFF));
  }
  TempFile tmp("test_large_size_1046.asf", data);

  auto io = std::make_unique<Exiv2::FileIo>(tmp.path());
  ASSERT_EQ(io->open(), 0);

  Exiv2::AsfVideo::HeaderReader reader(io);
  EXPECT_EQ(reader.getSize(), largeSize);
}

TEST_F(AsfVideoHeaderReaderTest_1046, GetIdReturnsMutableReference_1046) {
  auto data = createValidAsfHeader(24);
  TempFile tmp("test_mutable_id_1046.asf", data);

  auto io = std::make_unique<Exiv2::FileIo>(tmp.path());
  ASSERT_EQ(io->open(), 0);

  Exiv2::AsfVideo::HeaderReader reader(io);
  auto& id1 = reader.getId();
  auto& id2 = reader.getId();
  // Both references should point to the same object
  EXPECT_EQ(&id1, &id2);
}

TEST_F(AsfVideoHeaderReaderTest_1046, ZeroFilledGuid_1046) {
  uint8_t zeroGuid[16] = {};
  auto data = createArbitraryGuidHeader(zeroGuid, 24);
  TempFile tmp("test_zero_guid_1046.asf", data);

  auto io = std::make_unique<Exiv2::FileIo>(tmp.path());
  ASSERT_EQ(io->open(), 0);

  Exiv2::AsfVideo::HeaderReader reader(io);
  auto& id = reader.getId();
  EXPECT_EQ(id.size(), 16u);
  uint8_t expected[16] = {};
  EXPECT_EQ(std::memcmp(id.data(), expected, 16), 0);
}

TEST_F(AsfVideoHeaderReaderTest_1046, GetRemainingSizeForLargerObject_1046) {
  uint64_t totalSize = 1024;
  auto data = createValidAsfHeader(totalSize);
  TempFile tmp("test_remaining_large_1046.asf", data);

  auto io = std::make_unique<Exiv2::FileIo>(tmp.path());
  ASSERT_EQ(io->open(), 0);

  Exiv2::AsfVideo::HeaderReader reader(io);
  EXPECT_EQ(reader.getRemainingSize(), totalSize - 24);
}
