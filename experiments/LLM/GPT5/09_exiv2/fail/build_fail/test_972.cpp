// SPDX-License-Identifier: GPL-2.0-or-later
// Test ID: 972
//
// Unit tests for Exiv2::PngImage::printStructure
// File under test: ./TestProjects/exiv2/src/pngimage.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/pngimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/image.hpp>
#include <exiv2/types.hpp>

#include <cstdint>
#include <cstring>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

using namespace Exiv2;

namespace {

std::vector<byte> be32(uint32_t v) {
  return std::vector<byte>{
      static_cast<byte>((v >> 24) & 0xff),
      static_cast<byte>((v >> 16) & 0xff),
      static_cast<byte>((v >> 8) & 0xff),
      static_cast<byte>(v & 0xff),
  };
}

void append(std::vector<byte>& dst, const std::vector<byte>& src) {
  dst.insert(dst.end(), src.begin(), src.end());
}

void appendBytes(std::vector<byte>& dst, const byte* p, size_t n) {
  dst.insert(dst.end(), p, p + n);
}

void appendAscii4(std::vector<byte>& dst, const char type4[4]) {
  dst.push_back(static_cast<byte>(type4[0]));
  dst.push_back(static_cast<byte>(type4[1]));
  dst.push_back(static_cast<byte>(type4[2]));
  dst.push_back(static_cast<byte>(type4[3]));
}

std::vector<byte> buildChunk(const char type4[4],
                             const std::vector<byte>& data,
                             const std::vector<byte>& crc4 = std::vector<byte>{0x01, 0x02, 0x03, 0x04}) {
  std::vector<byte> out;
  append(out, be32(static_cast<uint32_t>(data.size())));
  appendAscii4(out, type4);
  append(out, data);
  // CRC is not validated by printStructure (it is read/printed); any 4 bytes are fine.
  if (crc4.size() == 4) {
    append(out, crc4);
  } else {
    out.push_back(0);
    out.push_back(0);
    out.push_back(0);
    out.push_back(0);
  }
  return out;
}

std::vector<byte> buildMinimalValidPng_IHDR_IEND() {
  std::vector<byte> png;

  // PNG signature: 89 50 4E 47 0D 0A 1A 0A
  const byte sig[8] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
  appendBytes(png, sig, sizeof(sig));

  // IHDR data must be 13 bytes in real PNG, but printStructure does not validate IHDR semantics.
  std::vector<byte> ihdrData(13, 0);
  append(png, buildChunk("IHDR", ihdrData, {0xAA, 0xBB, 0xCC, 0xDD}));

  // IEND has zero-length data.
  std::vector<byte> iendData;
  append(png, buildChunk("IEND", iendData, {0x11, 0x22, 0x33, 0x44}));

  return png;
}

class MockBasicIo : public BasicIo {
public:
  MOCK_METHOD(int, open, (), (override));
  MOCK_METHOD(int, close, (), (override));
  MOCK_METHOD(size_t, write, (const byte*, size_t), (override));
  MOCK_METHOD(size_t, write, (BasicIo&), (override));
  MOCK_METHOD(int, putb, (byte), (override));
  MOCK_METHOD(DataBuf, read, (size_t), (override));
  MOCK_METHOD(size_t, read, (byte*, size_t), (override));
  MOCK_METHOD(int, getb, (), (override));
  MOCK_METHOD(void, transfer, (BasicIo&), (override));
  MOCK_METHOD(int, seek, (int64_t, Position), (override));
  MOCK_METHOD(byte*, mmap, (bool), (override));
  MOCK_METHOD(int, munmap, (), (override));
  MOCK_METHOD(const size_t, tell, (), (override));
  MOCK_METHOD(const size_t, size, (), (override));
  MOCK_METHOD(const bool, isopen, (), (override));
  MOCK_METHOD(const int, error, (), (override));
  MOCK_METHOD(const bool, eof, (), (override));
  MOCK_METHOD(const std::string&, path, (), (override));
  MOCK_METHOD(void, populateFakeData, (), (override));
};

class PngImageTest_972 : public ::testing::Test {};

}  // namespace

TEST_F(PngImageTest_972, PrintStructureBasic_PrintsHeaderAndChunks_972) {
  const auto bytes = buildMinimalValidPng_IHDR_IEND();
  auto io = std::make_unique<MemIo>(bytes.data(), bytes.size());
  PngImage img(std::move(io), /*create=*/false);

  std::ostringstream out;
  EXPECT_NO_THROW(img.printStructure(out, kpsBasic, /*depth=*/0));

  const std::string s = out.str();
  EXPECT_NE(s.find("STRUCTURE OF PNG FILE:"), std::string::npos);
  EXPECT_NE(s.find("address | chunk | length | data | checksum"), std::string::npos);

  // Should list both chunks and their lengths.
  EXPECT_NE(s.find("IHDR"), std::string::npos);
  EXPECT_NE(s.find("IEND"), std::string::npos);
  EXPECT_NE(s.find("|      13 |"), std::string::npos);  // IHDR length 13
  EXPECT_NE(s.find("|       0 |"), std::string::npos);  // IEND length 0

  // CRC bytes should be printed in hex format; we don't assert exact spacing/formatting, only presence.
  EXPECT_NE(s.find("0xaabbccdd"), std::string::npos);
  EXPECT_NE(s.find("0x11223344"), std::string::npos);
}

TEST_F(PngImageTest_972, PrintStructureRecursive_PrintsHeaderAndChunks_972) {
  const auto bytes = buildMinimalValidPng_IHDR_IEND();
  auto io = std::make_unique<MemIo>(bytes.data(), bytes.size());
  PngImage img(std::move(io), /*create=*/false);

  std::ostringstream out;
  EXPECT_NO_THROW(img.printStructure(out, kpsRecursive, /*depth=*/0));

  const std::string s = out.str();
  // For kpsRecursive, bPrint is true (per interface behavior in provided code).
  EXPECT_NE(s.find("STRUCTURE OF PNG FILE:"), std::string::npos);
  EXPECT_NE(s.find("IHDR"), std::string::npos);
  EXPECT_NE(s.find("IEND"), std::string::npos);
}

TEST_F(PngImageTest_972, PrintStructureNone_ProducesNoOutputAndNoThrow_972) {
  const auto bytes = buildMinimalValidPng_IHDR_IEND();
  auto io = std::make_unique<MemIo>(bytes.data(), bytes.size());
  PngImage img(std::move(io), /*create=*/false);

  std::ostringstream out;
  EXPECT_NO_THROW(img.printStructure(out, kpsNone, /*depth=*/0));
  EXPECT_TRUE(out.str().empty());
}

TEST_F(PngImageTest_972, PrintStructureOpenFailure_ThrowsDataSourceOpenFailed_972) {
  using ::testing::Return;
  using ::testing::NiceMock;

  auto mockIo = std::make_unique<NiceMock<MockBasicIo>>();
  // open() non-zero should trigger kerDataSourceOpenFailed.
  EXPECT_CALL(*mockIo, open()).WillOnce(Return(1));

  // Provide a stable path() string reference.
  static const std::string kPath = "mock.png";
  ON_CALL(*mockIo, path()).WillByDefault(::testing::ReturnRef(kPath));

  PngImage img(std::move(mockIo), /*create=*/false);

  std::ostringstream out;
  try {
    img.printStructure(out, kpsBasic, /*depth=*/0);
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    // Verify observable error code (if available in this build).
    EXPECT_EQ(e.code(), ErrorCode::kerDataSourceOpenFailed);
  }
}

TEST_F(PngImageTest_972, PrintStructureNotPng_ThrowsNotAnImage_972) {
  // Wrong signature (not a PNG).
  std::vector<byte> bytes = buildMinimalValidPng_IHDR_IEND();
  bytes[0] = 0x00;

  auto io = std::make_unique<MemIo>(bytes.data(), bytes.size());
  PngImage img(std::move(io), /*create=*/false);

  std::ostringstream out;
  try {
    img.printStructure(out, kpsBasic, /*depth=*/0);
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    EXPECT_EQ(e.code(), ErrorCode::kerNotAnImage);
  }
}

TEST_F(PngImageTest_972, PrintStructureTruncatedChunkHeader_ThrowsInputDataReadFailed_972) {
  // Valid signature, but no full 8-byte chunk header afterwards.
  std::vector<byte> bytes;
  const byte sig[8] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
  appendBytes(bytes, sig, sizeof(sig));
  // Only 4 bytes (half header)
  bytes.push_back(0x00);
  bytes.push_back(0x00);
  bytes.push_back(0x00);
  bytes.push_back(0x00);

  auto io = std::make_unique<MemIo>(bytes.data(), bytes.size());
  PngImage img(std::move(io), /*create=*/false);

  std::ostringstream out;
  try {
    img.printStructure(out, kpsBasic, /*depth=*/0);
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    EXPECT_EQ(e.code(), ErrorCode::kerInputDataReadFailed);
  }
}

TEST_F(PngImageTest_972, PrintStructureChunkLengthBeyondFile_ThrowsFailedToReadImageData_972) {
  // Valid signature + one chunk header claiming a huge length, but file ends immediately.
  std::vector<byte> bytes;
  const byte sig[8] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
  appendBytes(bytes, sig, sizeof(sig));

  // length = 100 (big-endian), type = "IHDR", but no data afterwards => should trip bounds check
  append(bytes, be32(100));
  appendAscii4(bytes, "IHDR");
  // no payload, no crc

  auto io = std::make_unique<MemIo>(bytes.data(), bytes.size());
  PngImage img(std::move(io), /*create=*/false);

  std::ostringstream out;
  try {
    img.printStructure(out, kpsBasic, /*depth=*/0);
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    EXPECT_EQ(e.code(), ErrorCode::kerFailedToReadImageData);
  }
}