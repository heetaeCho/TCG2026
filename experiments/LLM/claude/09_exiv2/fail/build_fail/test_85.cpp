#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/jp2image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/types.hpp>
#include <exiv2/image.hpp>

#include <cstring>
#include <fstream>
#include <memory>
#include <vector>
#include <algorithm>

namespace {

// Helper to write big-endian uint32_t into a buffer
void writeUint32BE(std::vector<uint8_t>& buf, size_t offset, uint32_t val) {
  buf[offset + 0] = static_cast<uint8_t>((val >> 24) & 0xFF);
  buf[offset + 1] = static_cast<uint8_t>((val >> 16) & 0xFF);
  buf[offset + 2] = static_cast<uint8_t>((val >> 8) & 0xFF);
  buf[offset + 3] = static_cast<uint8_t>(val & 0xFF);
}

void writeUint16BE(std::vector<uint8_t>& buf, size_t offset, uint16_t val) {
  buf[offset + 0] = static_cast<uint8_t>((val >> 8) & 0xFF);
  buf[offset + 1] = static_cast<uint8_t>(val & 0xFF);
}

// JP2 box types (big-endian values)
constexpr uint32_t kSignature = 0x6A502020;   // 'jP  '
constexpr uint32_t kFileTypeBox = 0x66747970;  // 'ftyp'
constexpr uint32_t kHeader = 0x6A703268;       // 'jp2h'
constexpr uint32_t kImageHeader = 0x69686472;  // 'ihdr'
constexpr uint32_t kColorSpec = 0x636F6C72;    // 'colr'
constexpr uint32_t kUuid = 0x75756964;         // 'uuid'

// JP2 signature content: 0x0D0A870A
const uint8_t jp2SignatureContent[] = {0x0D, 0x0A, 0x87, 0x0A};

// Build a minimal valid JP2 Signature box
void appendSignatureBox(std::vector<uint8_t>& data) {
  size_t start = data.size();
  data.resize(data.size() + 12);
  writeUint32BE(data, start, 12);       // length = 12
  writeUint32BE(data, start + 4, kSignature); // type
  // Signature content
  data[start + 8] = 0x0D;
  data[start + 9] = 0x0A;
  data[start + 10] = 0x87;
  data[start + 11] = 0x0A;
}

// Build a minimal valid FileType box
// brand = 'jp2 ' (0x6A703220), minor_version = 0, compatibility = 'jp2 '
void appendFileTypeBox(std::vector<uint8_t>& data) {
  // ftyp box: length(4) + type(4) + brand(4) + minor_version(4) + compat(4) = 20
  size_t start = data.size();
  data.resize(data.size() + 20);
  writeUint32BE(data, start, 20);
  writeUint32BE(data, start + 4, kFileTypeBox);
  writeUint32BE(data, start + 8, 0x6A703220);  // brand = 'jp2 '
  writeUint32BE(data, start + 12, 0);           // minor version
  writeUint32BE(data, start + 16, 0x6A703220);  // compatibility list: 'jp2 '
}

// Build a Header box with ImageHeader sub-box
void appendHeaderBoxWithImageHeader(std::vector<uint8_t>& data, uint32_t width, uint32_t height, uint16_t components) {
  // ImageHeader sub-box: length(4) + type(4) + ihdr data (14 bytes from struct) = 22
  // ihdr data: height(4) + width(4) + componentCount(2) + bpc(1) + c(1) + unkC(1) + ipr(1) = 14
  const uint32_t ihdrBoxLen = 22;
  const uint32_t headerBoxLen = 8 + ihdrBoxLen; // Header box = header(8) + ihdr sub-box

  size_t start = data.size();
  data.resize(data.size() + headerBoxLen);

  // Header box
  writeUint32BE(data, start, headerBoxLen);
  writeUint32BE(data, start + 4, kHeader);

  // ImageHeader sub-box
  size_t ihdrStart = start + 8;
  writeUint32BE(data, ihdrStart, ihdrBoxLen);
  writeUint32BE(data, ihdrStart + 4, kImageHeader);
  writeUint32BE(data, ihdrStart + 8, height);
  writeUint32BE(data, ihdrStart + 12, width);
  writeUint16BE(data, ihdrStart + 16, components);
  data[ihdrStart + 18] = 8;   // bpc
  data[ihdrStart + 19] = 7;   // c = 7 (required by enforce)
  data[ihdrStart + 20] = 0;   // unkC
  data[ihdrStart + 21] = 0;   // ipr
}

// Build a minimal valid JP2 file in memory
std::vector<uint8_t> buildMinimalJp2(uint32_t width = 100, uint32_t height = 200) {
  std::vector<uint8_t> data;
  appendSignatureBox(data);
  appendFileTypeBox(data);
  appendHeaderBoxWithImageHeader(data, width, height, 3);
  return data;
}

// Helper to create a Jp2Image from in-memory data
std::unique_ptr<Exiv2::Jp2Image> createJp2ImageFromData(const std::vector<uint8_t>& data) {
  auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
  return std::make_unique<Exiv2::Jp2Image>(std::move(io), false);
}

} // anonymous namespace

class Jp2ImageTest_85 : public ::testing::Test {
protected:
  void SetUp() override {
    Exiv2::XmpParser::initialize();
  }
  void TearDown() override {
  }
};

// Test that readMetadata succeeds on a minimal valid JP2 file
TEST_F(Jp2ImageTest_85, ReadMetadataMinimalValidFile_85) {
  auto data = buildMinimalJp2(640, 480);
  auto image = createJp2ImageFromData(data);
  ASSERT_NO_THROW(image->readMetadata());
  EXPECT_EQ(image->pixelWidth(), 640u);
  EXPECT_EQ(image->pixelHeight(), 480u);
}

// Test that readMetadata throws on empty data
TEST_F(Jp2ImageTest_85, ReadMetadataEmptyFile_85) {
  std::vector<uint8_t> data;
  auto image = createJp2ImageFromData(data);
  EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test that readMetadata throws on non-JP2 data
TEST_F(Jp2ImageTest_85, ReadMetadataNotAJp2Image_85) {
  std::vector<uint8_t> data = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                                0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
  auto image = createJp2ImageFromData(data);
  EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test that readMetadata correctly reads pixel dimensions
TEST_F(Jp2ImageTest_85, ReadMetadataPixelDimensions_85) {
  auto data = buildMinimalJp2(1920, 1080);
  auto image = createJp2ImageFromData(data);
  ASSERT_NO_THROW(image->readMetadata());
  EXPECT_EQ(image->pixelWidth(), 1920u);
  EXPECT_EQ(image->pixelHeight(), 1080u);
}

// Test with minimum pixel dimensions (1x1)
TEST_F(Jp2ImageTest_85, ReadMetadataMinimumDimensions_85) {
  auto data = buildMinimalJp2(1, 1);
  auto image = createJp2ImageFromData(data);
  ASSERT_NO_THROW(image->readMetadata());
  EXPECT_EQ(image->pixelWidth(), 1u);
  EXPECT_EQ(image->pixelHeight(), 1u);
}

// Test that duplicate Signature boxes cause an error
TEST_F(Jp2ImageTest_85, ReadMetadataDuplicateSignatureBox_85) {
  std::vector<uint8_t> data;
  appendSignatureBox(data);
  appendSignatureBox(data); // duplicate
  appendFileTypeBox(data);
  auto image = createJp2ImageFromData(data);
  EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test that FileType box before Signature box causes an error
TEST_F(Jp2ImageTest_85, ReadMetadataFileTypeBeforeSignature_85) {
  std::vector<uint8_t> data;
  appendFileTypeBox(data);
  appendSignatureBox(data);
  auto image = createJp2ImageFromData(data);
  EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test that duplicate FileType boxes cause an error
TEST_F(Jp2ImageTest_85, ReadMetadataDuplicateFileTypeBox_85) {
  std::vector<uint8_t> data;
  appendSignatureBox(data);
  appendFileTypeBox(data);
  appendFileTypeBox(data); // duplicate
  auto image = createJp2ImageFromData(data);
  EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test that exifData is empty for a minimal JP2 without UUID-Exif box
TEST_F(Jp2ImageTest_85, ReadMetadataNoExifData_85) {
  auto data = buildMinimalJp2();
  auto image = createJp2ImageFromData(data);
  ASSERT_NO_THROW(image->readMetadata());
  EXPECT_TRUE(image->exifData().empty());
}

// Test that iptcData is empty for a minimal JP2 without UUID-IPTC box
TEST_F(Jp2ImageTest_85, ReadMetadataNoIptcData_85) {
  auto data = buildMinimalJp2();
  auto image = createJp2ImageFromData(data);
  ASSERT_NO_THROW(image->readMetadata());
  EXPECT_TRUE(image->iptcData().empty());
}

// Test that xmpData is empty for a minimal JP2 without UUID-XMP box
TEST_F(Jp2ImageTest_85, ReadMetadataNoXmpData_85) {
  auto data = buildMinimalJp2();
  auto image = createJp2ImageFromData(data);
  ASSERT_NO_THROW(image->readMetadata());
  EXPECT_TRUE(image->xmpData().empty());
}

// Test that xmpPacket is empty for a minimal JP2
TEST_F(Jp2ImageTest_85, ReadMetadataNoXmpPacket_85) {
  auto data = buildMinimalJp2();
  auto image = createJp2ImageFromData(data);
  ASSERT_NO_THROW(image->readMetadata());
  EXPECT_TRUE(image->xmpPacket().empty());
}

// Test mimeType returns correct MIME type
TEST_F(Jp2ImageTest_85, MimeType_85) {
  auto data = buildMinimalJp2();
  auto image = createJp2ImageFromData(data);
  std::string mime = image->mimeType();
  EXPECT_EQ(mime, "image/jp2");
}

// Test setComment does nothing (JP2 doesn't support comments per the override)
TEST_F(Jp2ImageTest_85, SetCommentNoOp_85) {
  auto data = buildMinimalJp2();
  auto image = createJp2ImageFromData(data);
  ASSERT_NO_THROW(image->setComment("test comment"));
  // Comment should remain empty since Jp2Image::setComment is a no-op
  EXPECT_TRUE(image->comment().empty());
}

// Test that a truncated file causes an error
TEST_F(Jp2ImageTest_85, ReadMetadataTruncatedFile_85) {
  auto data = buildMinimalJp2();
  // Truncate the data to cut off the header box
  data.resize(data.size() / 2);
  auto image = createJp2ImageFromData(data);
  EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test with a box that has zero length (should return gracefully)
TEST_F(Jp2ImageTest_85, ReadMetadataZeroLengthBoxStopsProcessing_85) {
  std::vector<uint8_t> data;
  appendSignatureBox(data);
  appendFileTypeBox(data);

  // Add a box with length = 0 (should cause readMetadata to return)
  size_t start = data.size();
  data.resize(data.size() + 8);
  writeUint32BE(data, start, 0);  // length = 0
  writeUint32BE(data, start + 4, 0x00000000); // some type

  auto image = createJp2ImageFromData(data);
  ASSERT_NO_THROW(image->readMetadata());
  // No image header was read, so dimensions should be 0
  EXPECT_EQ(image->pixelWidth(), 0u);
  EXPECT_EQ(image->pixelHeight(), 0u);
}

// Test that a corrupted box length (too large) throws
TEST_F(Jp2ImageTest_85, ReadMetadataCorruptedBoxLength_85) {
  std::vector<uint8_t> data;
  appendSignatureBox(data);
  appendFileTypeBox(data);

  // Add a box with absurdly large length
  size_t start = data.size();
  data.resize(data.size() + 8);
  writeUint32BE(data, start, 0xFFFFFFFF);  // very large length
  writeUint32BE(data, start + 4, kHeader);

  auto image = createJp2ImageFromData(data);
  EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test that ImageHeader with wrong 'c' value (not 7) throws
TEST_F(Jp2ImageTest_85, ReadMetadataInvalidImageHeaderC_85) {
  std::vector<uint8_t> data;
  appendSignatureBox(data);
  appendFileTypeBox(data);

  // Build header with ihdr where c != 7
  const uint32_t ihdrBoxLen = 22;
  const uint32_t headerBoxLen = 8 + ihdrBoxLen;

  size_t start = data.size();
  data.resize(data.size() + headerBoxLen);
  writeUint32BE(data, start, headerBoxLen);
  writeUint32BE(data, start + 4, kHeader);

  size_t ihdrStart = start + 8;
  writeUint32BE(data, ihdrStart, ihdrBoxLen);
  writeUint32BE(data, ihdrStart + 4, kImageHeader);
  writeUint32BE(data, ihdrStart + 8, 100);  // height
  writeUint32BE(data, ihdrStart + 12, 200); // width
  writeUint16BE(data, ihdrStart + 16, 3);   // components
  data[ihdrStart + 18] = 8;   // bpc
  data[ihdrStart + 19] = 5;   // c = 5 (invalid, should be 7)
  data[ihdrStart + 20] = 0;
  data[ihdrStart + 21] = 0;

  auto image = createJp2ImageFromData(data);
  EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test with XMP UUID box containing simple XMP data
TEST_F(Jp2ImageTest_85, ReadMetadataWithXmpUuidBox_85) {
  auto data = buildMinimalJp2(320, 240);

  // XMP UUID: BE7ACF CB 97A9 42E8 9C71 99949 1E3AF AC
  const uint8_t xmpUuid[16] = {0xBE, 0x7A, 0xCF, 0xCB, 0x97, 0xA9, 0x42, 0xE8,
                                 0x9C, 0x71, 0x99, 0x94, 0x91, 0xE3, 0xAF, 0xAC};

  std::string xmpPacket = R"(<?xpacket begin="" id="W5M0MpCehiHzreSzNTczkc9d"?>
<x:xmpmeta xmlns:x="adobe:ns:meta/">
  <rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  </rdf:RDF>
</x:xmpmeta>
<?xpacket end="w"?>)";

  uint32_t uuidBoxLen = 8 + 16 + static_cast<uint32_t>(xmpPacket.size());
  size_t start = data.size();
  data.resize(data.size() + uuidBoxLen);
  writeUint32BE(data, start, uuidBoxLen);
  writeUint32BE(data, start + 4, kUuid);
  std::memcpy(data.data() + start + 8, xmpUuid, 16);
  std::memcpy(data.data() + start + 24, xmpPacket.data(), xmpPacket.size());

  auto image = createJp2ImageFromData(data);
  ASSERT_NO_THROW(image->readMetadata());
  EXPECT_FALSE(image->xmpPacket().empty());
}

// Test that good() returns true for a valid JP2 file after construction
TEST_F(Jp2ImageTest_85, GoodReturnsTrueForValidFile_85) {
  auto data = buildMinimalJp2();
  auto image = createJp2ImageFromData(data);
  EXPECT_TRUE(image->good());
}

// Test that iccProfile is not defined for minimal JP2 without color spec
TEST_F(Jp2ImageTest_85, ReadMetadataNoIccProfile_85) {
  auto data = buildMinimalJp2();
  auto image = createJp2ImageFromData(data);
  ASSERT_NO_THROW(image->readMetadata());
  EXPECT_FALSE(image->iccProfileDefined());
}

// Test with large pixel dimensions
TEST_F(Jp2ImageTest_85, ReadMetadataLargeDimensions_85) {
  auto data = buildMinimalJp2(4096, 4096);
  auto image = createJp2ImageFromData(data);
  ASSERT_NO_THROW(image->readMetadata());
  EXPECT_EQ(image->pixelWidth(), 4096u);
  EXPECT_EQ(image->pixelHeight(), 4096u);
}

// Test that only the Signature box without FileType causes an error if we try FileType first
TEST_F(Jp2ImageTest_85, ReadMetadataOnlySignatureBox_85) {
  std::vector<uint8_t> data;
  appendSignatureBox(data);
  // No FileType box, no more data - should just finish reading without error
  // (the loop just ends when it can't read more box headers)
  auto image = createJp2ImageFromData(data);
  ASSERT_NO_THROW(image->readMetadata());
}

// Test corrupted FileType box content
TEST_F(Jp2ImageTest_85, ReadMetadataInvalidFileTypeContent_85) {
  std::vector<uint8_t> data;
  appendSignatureBox(data);

  // Build a FileType box with invalid brand
  size_t start = data.size();
  data.resize(data.size() + 20);
  writeUint32BE(data, start, 20);
  writeUint32BE(data, start + 4, kFileTypeBox);
  writeUint32BE(data, start + 8, 0x00000000);  // invalid brand
  writeUint32BE(data, start + 12, 0);
  writeUint32BE(data, start + 16, 0x00000000);  // invalid compatibility

  auto image = createJp2ImageFromData(data);
  EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test that clearMetadata works after reading
TEST_F(Jp2ImageTest_85, ClearMetadataAfterRead_85) {
  auto data = buildMinimalJp2(800, 600);
  auto image = createJp2ImageFromData(data);
  ASSERT_NO_THROW(image->readMetadata());
  image->clearMetadata();
  EXPECT_TRUE(image->exifData().empty());
  EXPECT_TRUE(image->iptcData().empty());
  EXPECT_TRUE(image->xmpData().empty());
}

// Test that the Jp2Image constructor with create=true doesn't crash
TEST_F(Jp2ImageTest_85, ConstructorCreateTrue_85) {
  auto io = std::make_unique<Exiv2::MemIo>();
  ASSERT_NO_THROW(Exiv2::Jp2Image(std::move(io), true));
}

// Test that the Jp2Image constructor with create=false doesn't crash
TEST_F(Jp2ImageTest_85, ConstructorCreateFalse_85) {
  auto io = std::make_unique<Exiv2::MemIo>();
  ASSERT_NO_THROW(Exiv2::Jp2Image(std::move(io), false));
}

// Test reading metadata with IPTC UUID box
TEST_F(Jp2ImageTest_85, ReadMetadataWithIptcUuidBox_85) {
  auto data = buildMinimalJp2(320, 240);

  const uint8_t iptcUuid[16] = {0x33, 0xC7, 0xA4, 0xD2, 0xB8, 0x1D, 0x47, 0x23,
                                  0xA0, 0xBA, 0xF1, 0xA3, 0xE0, 0x97, 0xAD, 0x38};

  // Empty IPTC data (just the UUID, no actual IPTC records)
  uint32_t uuidBoxLen = 8 + 16;
  size_t start = data.size();
  data.resize(data.size() + uuidBoxLen);
  writeUint32BE(data, start, uuidBoxLen);
  writeUint32BE(data, start + 4, kUuid);
  std::memcpy(data.data() + start + 8, iptcUuid, 16);

  auto image = createJp2ImageFromData(data);
  ASSERT_NO_THROW(image->readMetadata());
  EXPECT_TRUE(image->iptcData().empty());
}

// Test reading metadata with Exif UUID box containing minimal valid TIFF data
TEST_F(Jp2ImageTest_85, ReadMetadataWithExifUuidBox_85) {
  auto data = buildMinimalJp2(320, 240);

  const uint8_t exifUuid[16] = {0x4A, 0x70, 0x67, 0x54, 0x69, 0x66, 0x66, 0x45,
                                  0x78, 0x69, 0x66, 0x2D, 0x3E, 0x4A, 0x50, 0x32};

  // Minimal TIFF header (little-endian): "II" + 0x002A + offset to IFD0 = 8 + 0 entries
  std::vector<uint8_t> tiffData = {
    'I', 'I',                       // byte order: little-endian
    0x2A, 0x00,                     // TIFF magic
    0x08, 0x00, 0x00, 0x00,        // offset to IFD0
    0x00, 0x00                      // 0 entries in IFD0
  };

  uint32_t uuidBoxLen = 8 + 16 + static_cast<uint32_t>(tiffData.size());
  size_t start = data.size();
  data.resize(data.size() + uuidBoxLen);
  writeUint32BE(data, start, uuidBoxLen);
  writeUint32BE(data, start + 4, kUuid);
  std::memcpy(data.data() + start + 8, exifUuid, 16);
  std::memcpy(data.data() + start + 24, tiffData.data(), tiffData.size());

  auto image = createJp2ImageFromData(data);
  ASSERT_NO_THROW(image->readMetadata());
}

// Test that a JP2 file with just random bytes after signature and ftyp
// is handled gracefully (unknown box types are skipped)
TEST_F(Jp2ImageTest_85, ReadMetadataUnknownBoxTypesSkipped_85) {
  std::vector<uint8_t> data;
  appendSignatureBox(data);
  appendFileTypeBox(data);

  // Add an unknown box type
  size_t start = data.size();
  data.resize(data.size() + 16);
  writeUint32BE(data, start, 16);
  writeUint32BE(data, start + 4, 0x12345678);  // unknown type
  // 8 bytes of padding
  std::fill(data.begin() + start + 8, data.begin() + start + 16, 0);

  appendHeaderBoxWithImageHeader(data, 512, 512);

  auto image = createJp2ImageFromData(data);
  ASSERT_NO_THROW(image->readMetadata());
  EXPECT_EQ(image->pixelWidth(), 512u);
  EXPECT_EQ(image->pixelHeight(), 512u);
}

// Test printing structure doesn't crash for a valid JP2
TEST_F(Jp2ImageTest_85, PrintStructureNoThrow_85) {
  auto data = buildMinimalJp2();
  auto image = createJp2ImageFromData(data);
  std::ostringstream oss;
  ASSERT_NO_THROW(image->printStructure(oss, Exiv2::kpsBasic, 0));
}

// Test that multiple reads of metadata produce consistent results
TEST_F(Jp2ImageTest_85, ReadMetadataMultipleTimes_85) {
  auto data = buildMinimalJp2(1024, 768);
  auto image = createJp2ImageFromData(data);
  ASSERT_NO_THROW(image->readMetadata());
  EXPECT_EQ(image->pixelWidth(), 1024u);
  EXPECT_EQ(image->pixelHeight(), 768u);

  // Read again
  ASSERT_NO_THROW(image->readMetadata());
  EXPECT_EQ(image->pixelWidth(), 1024u);
  EXPECT_EQ(image->pixelHeight(), 768u);
}
