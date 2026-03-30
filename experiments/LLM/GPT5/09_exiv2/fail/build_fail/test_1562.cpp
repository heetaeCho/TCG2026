// ============================================================================
// test_asfvideo_readmetadata_1562.cpp
// Unit tests for Exiv2::AsfVideo::readMetadata (black-box)
// TEST_ID: 1562
// ============================================================================

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

#include "exiv2/asfvideo.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"
#include "exiv2/memio.hpp"     // MemIo (memory-backed BasicIo)
#include "exiv2/xmp_exiv2.hpp" // XmpData / Xmpdatum

using ::testing::_;
using ::testing::Return;
using ::testing::NiceMock;

namespace {

// -----------------------------
// Minimal helpers to build ASF
// -----------------------------
static void appendBytes(std::vector<Exiv2::byte>& out, const void* p, size_t n) {
  const auto* b = static_cast<const Exiv2::byte*>(p);
  out.insert(out.end(), b, b + n);
}

static void appendU16LE(std::vector<Exiv2::byte>& out, uint16_t v) {
  Exiv2::byte b[2] = {static_cast<Exiv2::byte>(v & 0xff),
                      static_cast<Exiv2::byte>((v >> 8) & 0xff)};
  appendBytes(out, b, 2);
}

static void appendU32LE(std::vector<Exiv2::byte>& out, uint32_t v) {
  Exiv2::byte b[4] = {static_cast<Exiv2::byte>(v & 0xff),
                      static_cast<Exiv2::byte>((v >> 8) & 0xff),
                      static_cast<Exiv2::byte>((v >> 16) & 0xff),
                      static_cast<Exiv2::byte>((v >> 24) & 0xff)};
  appendBytes(out, b, 4);
}

static void appendU64LE(std::vector<Exiv2::byte>& out, uint64_t v) {
  Exiv2::byte b[8] = {static_cast<Exiv2::byte>(v & 0xff),
                      static_cast<Exiv2::byte>((v >> 8) & 0xff),
                      static_cast<Exiv2::byte>((v >> 16) & 0xff),
                      static_cast<Exiv2::byte>((v >> 24) & 0xff),
                      static_cast<Exiv2::byte>((v >> 32) & 0xff),
                      static_cast<Exiv2::byte>((v >> 40) & 0xff),
                      static_cast<Exiv2::byte>((v >> 48) & 0xff),
                      static_cast<Exiv2::byte>((v >> 56) & 0xff)};
  appendBytes(out, b, 8);
}

// ASF GUID bytes as stored in ASF files (little-endian layout for first 3 fields).
static void appendGuidLE(std::vector<Exiv2::byte>& out, const Exiv2::byte guid[16]) {
  appendBytes(out, guid, 16);
}

// Build a tiny ASF with:
// - Header Object
//   - File Properties Object
//   - Stream Properties Object (minimal, with zero type-specific data)
// - Data Object (minimal, no payload)
// This is meant to be "just enough" to allow Exiv2::AsfVideo::readMetadata()
// to proceed through decodeBlock() in typical implementations.
static std::vector<Exiv2::byte> makeMinimalAsfBytes() {
  // Known ASF GUIDs (file storage byte order)
  static const Exiv2::byte kHeaderObjectGuid[16] = {
      0x30, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11, 0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C};
  static const Exiv2::byte kFilePropsGuid[16] = {
      0xA1, 0xDC, 0xAB, 0x8C, 0x47, 0xA9, 0xCF, 0x11, 0x8E, 0xE4, 0x00, 0xC0, 0x0C, 0x20, 0x53, 0x65};
  static const Exiv2::byte kStreamPropsGuid[16] = {
      0x91, 0x07, 0xDC, 0xB7, 0xB7, 0xA9, 0xCF, 0x11, 0x8E, 0xE6, 0x00, 0xC0, 0x0C, 0x20, 0x53, 0x65};
  static const Exiv2::byte kDataObjectGuid[16] = {
      0x36, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11, 0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C};

  // Stream type GUID (Video Media) (common ASF GUID)
  static const Exiv2::byte kVideoMediaGuid[16] = {
      0xC0, 0xEF, 0x19, 0xBC, 0x4D, 0x5B, 0xCF, 0x11, 0xA8, 0xFD, 0x00, 0x80, 0x5F, 0x5C, 0x44, 0x2B};

  // All-zero GUID used as a conservative "none/unknown" for error correction type in minimal files.
  static const Exiv2::byte kZeroGuid[16] = {0};

  // We’ll fill object sizes once we know all pieces.
  std::vector<Exiv2::byte> headerObject;
  std::vector<Exiv2::byte> filePropsObject;
  std::vector<Exiv2::byte> streamPropsObject;
  std::vector<Exiv2::byte> dataObject;

  // -------------------------
  // File Properties Object
  // -------------------------
  appendGuidLE(filePropsObject, kFilePropsGuid);
  appendU64LE(filePropsObject, 0 /* placeholder: object size */);

  // File ID GUID (arbitrary, non-zero)
  const Exiv2::byte fileIdGuid[16] = {
      0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
      0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10};
  appendBytes(filePropsObject, fileIdGuid, 16);

  // Fields (values are placeholders; consistency matters more than realism for a minimal header)
  appendU64LE(filePropsObject, 0 /* File Size placeholder */);
  appendU64LE(filePropsObject, 0 /* Creation Date */);
  appendU64LE(filePropsObject, 0 /* Data Packets Count */);
  appendU64LE(filePropsObject, 0 /* Play Duration */);
  appendU64LE(filePropsObject, 0 /* Send Duration */);
  appendU64LE(filePropsObject, 0 /* Preroll */);
  appendU32LE(filePropsObject, 0 /* Flags */);
  appendU32LE(filePropsObject, 1024 /* Min Packet Size */);
  appendU32LE(filePropsObject, 1024 /* Max Packet Size */);
  appendU32LE(filePropsObject, 0 /* Max Bitrate */);

  // Patch object size (should be total bytes of this object)
  const uint64_t filePropsSize = static_cast<uint64_t>(filePropsObject.size());
  std::memcpy(&filePropsObject[16], &filePropsSize, sizeof(filePropsSize)); // overwrites placeholder (little-endian host assumed)
  // If host endianness differs, tests would fail on exotic platforms; acceptable for typical CI.

  // -------------------------
  // Stream Properties Object
  // -------------------------
  appendGuidLE(streamPropsObject, kStreamPropsGuid);
  appendU64LE(streamPropsObject, 0 /* placeholder: object size */);

  appendGuidLE(streamPropsObject, kVideoMediaGuid); // Stream Type
  appendGuidLE(streamPropsObject, kZeroGuid);       // Error Correction Type
  appendU64LE(streamPropsObject, 0 /* Time Offset */);
  appendU32LE(streamPropsObject, 0 /* Type-Specific Data Length */);
  appendU32LE(streamPropsObject, 0 /* Error Correction Data Length */);
  appendU16LE(streamPropsObject, 1 /* Flags: Stream Number = 1 */);
  appendU32LE(streamPropsObject, 0 /* Reserved */);

  const uint64_t streamPropsSize = static_cast<uint64_t>(streamPropsObject.size());
  std::memcpy(&streamPropsObject[16], &streamPropsSize, sizeof(streamPropsSize));

  // -------------------------
  // Header Object
  // -------------------------
  appendGuidLE(headerObject, kHeaderObjectGuid);
  appendU64LE(headerObject, 0 /* placeholder: header object size */);

  appendU32LE(headerObject, 2 /* Number of Header Objects */);
  headerObject.push_back(1 /* Reserved1 */);
  headerObject.push_back(2 /* Reserved2 */);

  // Append header sub-objects
  appendBytes(headerObject, filePropsObject.data(), filePropsObject.size());
  appendBytes(headerObject, streamPropsObject.data(), streamPropsObject.size());

  const uint64_t headerSize = static_cast<uint64_t>(headerObject.size());
  std::memcpy(&headerObject[16], &headerSize, sizeof(headerSize));

  // -------------------------
  // Data Object (minimal)
  // -------------------------
  appendGuidLE(dataObject, kDataObjectGuid);
  appendU64LE(dataObject, 0 /* placeholder: data object size */);
  appendBytes(dataObject, fileIdGuid, 16);       // File ID
  appendU64LE(dataObject, 0 /* Total Data Packets */);
  appendU16LE(dataObject, 0 /* Reserved */);

  const uint64_t dataSize = static_cast<uint64_t>(dataObject.size());
  std::memcpy(&dataObject[16], &dataSize, sizeof(dataSize));

  // -------------------------
  // Full file
  // -------------------------
  std::vector<Exiv2::byte> full;
  appendBytes(full, headerObject.data(), headerObject.size());
  appendBytes(full, dataObject.data(), dataObject.size());

  // Patch File Size field inside File Properties object to match actual full file size.
  // File Size field offset inside File Properties object:
  // [GUID 16][SIZE 8][FileID 16] => next is FileSize QWORD (8)
  const size_t filePropsStartInHeader =
      16 /*Header GUID*/ + 8 /*Header size*/ + 4 /*num*/ + 1 + 1;
  const size_t filePropsFileSizeOffsetInFile =
      filePropsStartInHeader + 16 + 8 + 16; // to FileSize field

  const uint64_t fullSize = static_cast<uint64_t>(full.size());
  std::memcpy(&full[filePropsFileSizeOffsetInFile], &fullSize, sizeof(fullSize));

  return full;
}

// -----------------------------
// Mock BasicIo for open-failure
// -----------------------------
class MockBasicIo : public Exiv2::BasicIo {
public:
  MOCK_METHOD(int, open, (), (override));
  MOCK_METHOD(int, close, (), (override));
  MOCK_METHOD(size_t, write, (const Exiv2::byte*, size_t), (override));
  MOCK_METHOD(size_t, write, (Exiv2::BasicIo&), (override));
  MOCK_METHOD(int, putb, (Exiv2::byte), (override));
  MOCK_METHOD(Exiv2::DataBuf, read, (size_t), (override));
  MOCK_METHOD(size_t, read, (Exiv2::byte*, size_t), (override));
  MOCK_METHOD(int, getb, (), (override));
  MOCK_METHOD(void, transfer, (Exiv2::BasicIo&), (override));
  MOCK_METHOD(int, seek, (int64_t, Exiv2::BasicIo::Position), (override));
  MOCK_METHOD(Exiv2::byte*, mmap, (bool), (override));
  MOCK_METHOD(int, munmap, (), (override));
  MOCK_METHOD(const size_t, tell, (), (override));
  MOCK_METHOD(const size_t, size, (), (override));
  MOCK_METHOD(const bool, isopen, (), (override));
  MOCK_METHOD(const int, error, (), (override));
  MOCK_METHOD(const bool, eof, (), (override));
  MOCK_METHOD(const std::string&, path, (), (override));
  MOCK_METHOD(void, populateFakeData, (), (override));
};

class AsfVideoReadMetadataTest_1562 : public ::testing::Test {};

} // namespace

// ----------------------------------------------------------------------------
// TEST_ID 1562: open() failure -> kerDataSourceOpenFailed (observable exception)
// ----------------------------------------------------------------------------
TEST_F(AsfVideoReadMetadataTest_1562, ThrowsOnOpenFailure_1562) {
  auto io = std::make_unique<NiceMock<MockBasicIo>>();
  // Ensure open fails; readMetadata should throw before any format checks.
  EXPECT_CALL(*io, open()).WillOnce(Return(1));
  // Provide a stable path() for error construction (if queried).
  static const std::string kPath = "mock.asf";
  EXPECT_CALL(*io, path()).WillRepeatedly(Return(std::ref(kPath)));

  Exiv2::AsfVideo video(std::move(io));

  try {
    video.readMetadata();
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerDataSourceOpenFailed);
  }
}

// ----------------------------------------------------------------------------
// TEST_ID 1562: Non-ASF input should throw kerNotAnImage (observable exception)
// ----------------------------------------------------------------------------
TEST_F(AsfVideoReadMetadataTest_1562, NonAsfThrowsNotAnImage_1562) {
  // A small non-ASF buffer; isAsfType should reject it.
  const Exiv2::byte bytes[] = {0x00, 0x11, 0x22, 0x33, 0x44};
  auto memIo = std::make_unique<Exiv2::MemIo>(bytes, sizeof(bytes));

  Exiv2::AsfVideo video(std::move(memIo));

  try {
    video.readMetadata();
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    // Per provided implementation: when !isAsfType and no io error/eof => kerNotAnImage("ASF")
    EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerNotAnImage);
  }
}

// ----------------------------------------------------------------------------
// TEST_ID 1562: Empty input likely triggers eof/error during type check -> kerFailedToReadImageData
// ----------------------------------------------------------------------------
TEST_F(AsfVideoReadMetadataTest_1562, EmptyInputThrowsFailedToReadImageData_1562) {
  // Empty file content.
  auto memIo = std::make_unique<Exiv2::MemIo>(nullptr, 0);
  Exiv2::AsfVideo video(std::move(memIo));

  try {
    video.readMetadata();
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    // If isAsfType triggers eof/error as it attempts to read header, implementation throws kerFailedToReadImageData.
    EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerFailedToReadImageData);
  }
}

// ----------------------------------------------------------------------------
// TEST_ID 1562: Normal operation: readMetadata succeeds on a minimal ASF and populates XMP keys
// ----------------------------------------------------------------------------
TEST_F(AsfVideoReadMetadataTest_1562, MinimalAsfPopulatesXmpKeys_1562) {
  const auto asf = makeMinimalAsfBytes();
  auto memIo = std::make_unique<Exiv2::MemIo>(asf.data(), asf.size());

  Exiv2::AsfVideo video(std::move(memIo));

  // Put a "stale" key to verify clearMetadata() removes prior metadata observably.
  video.xmpData()["Xmp.test.StaleKey"] = std::string("stale");

  ASSERT_NO_THROW(video.readMetadata());

  // Required observable effects from the provided readMetadata() body:
  // - xmpData()["Xmp.video.FileSize"] set to io_->size()/1048576.
  // - xmpData()["Xmp.video.MimeType"] set to mimeType()
  // - xmpData_["Xmp.video.AspectRatio"] set after decodeBlock()

  // Stale key should be cleared by clearMetadata().
  EXPECT_TRUE(video.xmpData().findKey(Exiv2::XmpKey("Xmp.test.StaleKey")) == video.xmpData().end());

  // FileSize
  auto itFileSize = video.xmpData().findKey(Exiv2::XmpKey("Xmp.video.FileSize"));
  ASSERT_TRUE(itFileSize != video.xmpData().end());
  const double expectedMB = static_cast<double>(asf.size()) / 1048576.0;
  // XMP numeric values are typically exposed via toFloat(0) / toString();
  // toFloat(0) is an observable API, so we prefer it.
  EXPECT_NEAR(itFileSize->toFloat(0), static_cast<float>(expectedMB), 1e-3f);

  // MimeType should match video.mimeType() (do not hardcode string).
  auto itMime = video.xmpData().findKey(Exiv2::XmpKey("Xmp.video.MimeType"));
  ASSERT_TRUE(itMime != video.xmpData().end());
  EXPECT_EQ(itMime->toString(), video.mimeType());

  // AspectRatio should exist (value format is implementation-defined; we only check presence + non-empty).
  auto itAR = video.xmpData().findKey(Exiv2::XmpKey("Xmp.video.AspectRatio"));
  ASSERT_TRUE(itAR != video.xmpData().end());
  EXPECT_FALSE(itAR->toString().empty());
}

// ----------------------------------------------------------------------------
// TEST_ID 1562: Boundary-ish check: FileSize key reflects current io size (re-run with different buffer size)
// ----------------------------------------------------------------------------
TEST_F(AsfVideoReadMetadataTest_1562, FileSizeReflectsUnderlyingIoSize_1562) {
  // Start with minimal ASF
  auto asf1 = makeMinimalAsfBytes();
  auto io1 = std::make_unique<Exiv2::MemIo>(asf1.data(), asf1.size());
  Exiv2::AsfVideo v1(std::move(io1));
  ASSERT_NO_THROW(v1.readMetadata());

  auto it1 = v1.xmpData().findKey(Exiv2::XmpKey("Xmp.video.FileSize"));
  ASSERT_TRUE(it1 != v1.xmpData().end());
  const float mb1 = it1->toFloat(0);

  // Now a slightly larger ASF by padding extra bytes at the end (data object payload padding).
  auto asf2 = makeMinimalAsfBytes();
  asf2.insert(asf2.end(), 128, 0x00);
  auto io2 = std::make_unique<Exiv2::MemIo>(asf2.data(), asf2.size());
  Exiv2::AsfVideo v2(std::move(io2));
  ASSERT_NO_THROW(v2.readMetadata());

  auto it2 = v2.xmpData().findKey(Exiv2::XmpKey("Xmp.video.FileSize"));
  ASSERT_TRUE(it2 != v2.xmpData().end());
  const float mb2 = it2->toFloat(0);

  EXPECT_GT(mb2, mb1);
}