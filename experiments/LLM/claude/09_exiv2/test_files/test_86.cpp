#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <cstring>
#include <vector>
#include <array>

#include "exiv2/jp2image.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"
#include "exiv2/image.hpp"
#include "exiv2/types.hpp"

using namespace Exiv2;

namespace {

// Helper to write a uint32_t in big-endian format
void writeBE32(std::vector<uint8_t>& buf, uint32_t val) {
  buf.push_back(static_cast<uint8_t>((val >> 24) & 0xFF));
  buf.push_back(static_cast<uint8_t>((val >> 16) & 0xFF));
  buf.push_back(static_cast<uint8_t>((val >> 8) & 0xFF));
  buf.push_back(static_cast<uint8_t>(val & 0xFF));
}

// Helper to write a uint32_t in big-endian at a specific position
void writeBE32At(std::vector<uint8_t>& buf, size_t pos, uint32_t val) {
  buf[pos + 0] = static_cast<uint8_t>((val >> 24) & 0xFF);
  buf[pos + 1] = static_cast<uint8_t>((val >> 16) & 0xFF);
  buf[pos + 2] = static_cast<uint8_t>((val >> 8) & 0xFF);
  buf[pos + 3] = static_cast<uint8_t>(val & 0xFF);
}

// JP2 box type constants (big-endian encoded values)
const uint32_t kSignature = 0x6A502020;   // 'jP  '
const uint32_t kFileTypeBox = 0x66747970; // 'ftyp'
const uint32_t kHeader = 0x6A703268;      // 'jp2h'
const uint32_t kImageHeader = 0x69686472; // 'ihdr'
const uint32_t kColorSpec = 0x636F6C72;   // 'colr'
const uint32_t kUuid = 0x75756964;        // 'uuid'
const uint32_t kClose = 0x6A703263;       // 'jp2c'

// JP2 signature data (0x0D0A870A)
const std::array<uint8_t, 4> kJp2SignatureData = {0x0D, 0x0A, 0x87, 0x0A};

// Build a minimal valid JP2 file in memory
std::vector<uint8_t> buildMinimalJp2() {
  std::vector<uint8_t> data;

  // Signature box: length=12, type='jP  ', data=0x0D0A870A
  writeBE32(data, 12);
  writeBE32(data, kSignature);
  data.insert(data.end(), kJp2SignatureData.begin(), kJp2SignatureData.end());

  // File Type box: length=20, type='ftyp', brand='jp2 ', minorVersion=0, cl='jp2 '
  writeBE32(data, 20);
  writeBE32(data, kFileTypeBox);
  // brand = 'jp2 '
  data.push_back('j'); data.push_back('p'); data.push_back('2'); data.push_back(' ');
  // minor version = 0
  writeBE32(data, 0);
  // compatibility list: 'jp2 '
  data.push_back('j'); data.push_back('p'); data.push_back('2'); data.push_back(' ');

  // Header box with ImageHeader and ColorSpec sub-boxes
  // ImageHeader sub-box: length=22, type='ihdr'
  // Data: height(4) + width(4) + numComponents(2) + bpc(1) + compressionType(1) + unkC(1) + ipr(1) = 14 bytes
  std::vector<uint8_t> ihdrData;
  writeBE32(ihdrData, 22);       // sub-box length
  writeBE32(ihdrData, kImageHeader); // sub-box type
  writeBE32(ihdrData, 100);      // height
  writeBE32(ihdrData, 200);      // width
  ihdrData.push_back(0); ihdrData.push_back(3); // numComponents = 3
  ihdrData.push_back(8);         // bpc
  ihdrData.push_back(7);         // compressionType = 7 (required)
  ihdrData.push_back(0);         // unkC (0 or 1)
  ihdrData.push_back(0);         // ipr (0 or 1)

  // ColorSpec sub-box: length=15, type='colr'
  // Data: METH(1) + PREC(1) + APPROX(1) + enumCS(4) = 7 bytes
  std::vector<uint8_t> colrData;
  writeBE32(colrData, 15);       // sub-box length
  writeBE32(colrData, kColorSpec); // sub-box type
  colrData.push_back(1);         // METH = 1 (Enumerated)
  colrData.push_back(0);         // PREC
  colrData.push_back(0);         // APPROX
  writeBE32(colrData, 16);       // enumCS = 16 (sRGB)

  // Header box: length = 8 + ihdrData.size() + colrData.size()
  size_t headerLen = 8 + ihdrData.size() + colrData.size();
  writeBE32(data, static_cast<uint32_t>(headerLen));
  writeBE32(data, kHeader);
  data.insert(data.end(), ihdrData.begin(), ihdrData.end());
  data.insert(data.end(), colrData.begin(), colrData.end());

  // Close box (jp2c): length=8, type='jp2c'
  writeBE32(data, 8);
  writeBE32(data, kClose);

  return data;
}

// Build a JP2 file with only a signature box but no valid JP2 signature data
std::vector<uint8_t> buildInvalidJp2() {
  std::vector<uint8_t> data;
  // Just random data, not a valid JP2
  data.resize(100, 0);
  return data;
}

// Build JP2 with duplicate signature boxes
std::vector<uint8_t> buildDuplicateSignatureJp2() {
  std::vector<uint8_t> data;

  // First Signature box
  writeBE32(data, 12);
  writeBE32(data, kSignature);
  data.insert(data.end(), kJp2SignatureData.begin(), kJp2SignatureData.end());

  // File Type box
  writeBE32(data, 20);
  writeBE32(data, kFileTypeBox);
  data.push_back('j'); data.push_back('p'); data.push_back('2'); data.push_back(' ');
  writeBE32(data, 0);
  data.push_back('j'); data.push_back('p'); data.push_back('2'); data.push_back(' ');

  // Second Signature box (should cause error)
  writeBE32(data, 12);
  writeBE32(data, kSignature);
  data.insert(data.end(), kJp2SignatureData.begin(), kJp2SignatureData.end());

  // Close box
  writeBE32(data, 8);
  writeBE32(data, kClose);

  return data;
}

// Build JP2 with a UUID box containing XMP data
std::vector<uint8_t> buildJp2WithXmpUuid() {
  std::vector<uint8_t> data;

  // Signature box
  writeBE32(data, 12);
  writeBE32(data, kSignature);
  data.insert(data.end(), kJp2SignatureData.begin(), kJp2SignatureData.end());

  // File Type box
  writeBE32(data, 20);
  writeBE32(data, kFileTypeBox);
  data.push_back('j'); data.push_back('p'); data.push_back('2'); data.push_back(' ');
  writeBE32(data, 0);
  data.push_back('j'); data.push_back('p'); data.push_back('2'); data.push_back(' ');

  // Header box with ihdr and colr
  std::vector<uint8_t> ihdrData;
  writeBE32(ihdrData, 22);
  writeBE32(ihdrData, kImageHeader);
  writeBE32(ihdrData, 100);
  writeBE32(ihdrData, 200);
  ihdrData.push_back(0); ihdrData.push_back(3);
  ihdrData.push_back(8);
  ihdrData.push_back(7);
  ihdrData.push_back(0);
  ihdrData.push_back(0);

  std::vector<uint8_t> colrData;
  writeBE32(colrData, 15);
  writeBE32(colrData, kColorSpec);
  colrData.push_back(1);
  colrData.push_back(0);
  colrData.push_back(0);
  writeBE32(colrData, 16);

  size_t headerLen = 8 + ihdrData.size() + colrData.size();
  writeBE32(data, static_cast<uint32_t>(headerLen));
  writeBE32(data, kHeader);
  data.insert(data.end(), ihdrData.begin(), ihdrData.end());
  data.insert(data.end(), colrData.begin(), colrData.end());

  // UUID box with XMP UUID
  const std::array<uint8_t, 16> kJp2UuidXmp = {0xBE, 0x7A, 0xCF, 0xCB, 0x97, 0xA9, 0x42, 0xE8,
                                                  0x9C, 0x71, 0x99, 0x94, 0x91, 0xE3, 0xAF, 0xAC};
  std::string xmpPayload = "<xmp>test xmp data</xmp>";
  uint32_t uuidBoxLen = 8 + 16 + static_cast<uint32_t>(xmpPayload.size());
  writeBE32(data, uuidBoxLen);
  writeBE32(data, kUuid);
  data.insert(data.end(), kJp2UuidXmp.begin(), kJp2UuidXmp.end());
  data.insert(data.end(), xmpPayload.begin(), xmpPayload.end());

  // Close box
  writeBE32(data, 8);
  writeBE32(data, kClose);

  return data;
}

// Build JP2 with an ImageHeader that has invalid compression type
std::vector<uint8_t> buildJp2WithBadImageHeader() {
  std::vector<uint8_t> data;

  // Signature box
  writeBE32(data, 12);
  writeBE32(data, kSignature);
  data.insert(data.end(), kJp2SignatureData.begin(), kJp2SignatureData.end());

  // File Type box
  writeBE32(data, 20);
  writeBE32(data, kFileTypeBox);
  data.push_back('j'); data.push_back('p'); data.push_back('2'); data.push_back(' ');
  writeBE32(data, 0);
  data.push_back('j'); data.push_back('p'); data.push_back('2'); data.push_back(' ');

  // Header with bad ImageHeader (compressionType != 7)
  std::vector<uint8_t> ihdrData;
  writeBE32(ihdrData, 22);
  writeBE32(ihdrData, kImageHeader);
  writeBE32(ihdrData, 100);
  writeBE32(ihdrData, 200);
  ihdrData.push_back(0); ihdrData.push_back(3);
  ihdrData.push_back(8);
  ihdrData.push_back(5);   // compressionType = 5 (invalid, should be 7)
  ihdrData.push_back(0);
  ihdrData.push_back(0);

  size_t headerLen = 8 + ihdrData.size();
  writeBE32(data, static_cast<uint32_t>(headerLen));
  writeBE32(data, kHeader);
  data.insert(data.end(), ihdrData.begin(), ihdrData.end());

  // Close box
  writeBE32(data, 8);
  writeBE32(data, kClose);

  return data;
}

// Build JP2 with ColorSpec having enumCS != 16 and != 17 with METH=1
std::vector<uint8_t> buildJp2WithBadColorSpec() {
  std::vector<uint8_t> data;

  // Signature box
  writeBE32(data, 12);
  writeBE32(data, kSignature);
  data.insert(data.end(), kJp2SignatureData.begin(), kJp2SignatureData.end());

  // File Type box
  writeBE32(data, 20);
  writeBE32(data, kFileTypeBox);
  data.push_back('j'); data.push_back('p'); data.push_back('2'); data.push_back(' ');
  writeBE32(data, 0);
  data.push_back('j'); data.push_back('p'); data.push_back('2'); data.push_back(' ');

  // Header with valid ImageHeader but bad ColorSpec
  std::vector<uint8_t> ihdrData;
  writeBE32(ihdrData, 22);
  writeBE32(ihdrData, kImageHeader);
  writeBE32(ihdrData, 100);
  writeBE32(ihdrData, 200);
  ihdrData.push_back(0); ihdrData.push_back(3);
  ihdrData.push_back(8);
  ihdrData.push_back(7);
  ihdrData.push_back(0);
  ihdrData.push_back(0);

  std::vector<uint8_t> colrData;
  writeBE32(colrData, 15);
  writeBE32(colrData, kColorSpec);
  colrData.push_back(1);         // METH = 1
  colrData.push_back(0);
  colrData.push_back(0);
  writeBE32(colrData, 99);       // enumCS = 99 (invalid)

  size_t headerLen = 8 + ihdrData.size() + colrData.size();
  writeBE32(data, static_cast<uint32_t>(headerLen));
  writeBE32(data, kHeader);
  data.insert(data.end(), ihdrData.begin(), ihdrData.end());
  data.insert(data.end(), colrData.begin(), colrData.end());

  // Close box
  writeBE32(data, 8);
  writeBE32(data, kClose);

  return data;
}

} // anonymous namespace

class Jp2ImagePrintStructureTest_86 : public ::testing::Test {
protected:
  std::unique_ptr<Jp2Image> createJp2Image(const std::vector<uint8_t>& data) {
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    return std::make_unique<Jp2Image>(std::move(io), false);
  }
};

// Test: printStructure with kpsBasic on a valid minimal JP2 file
TEST_F(Jp2ImagePrintStructureTest_86, PrintBasicStructure_ValidJp2_86) {
  auto data = buildMinimalJp2();
  auto img = createJp2Image(data);
  std::ostringstream oss;

  ASSERT_NO_THROW(img->printStructure(oss, kpsBasic, 0));

  std::string output = oss.str();
  EXPECT_TRUE(output.find("STRUCTURE OF JPEG2000 FILE") != std::string::npos);
  EXPECT_TRUE(output.find("address") != std::string::npos);
  EXPECT_TRUE(output.find("length") != std::string::npos);
}

// Test: printStructure throws on non-JP2 data
TEST_F(Jp2ImagePrintStructureTest_86, PrintStructure_InvalidData_ThrowsNotAJpeg_86) {
  auto data = buildInvalidJp2();
  auto img = createJp2Image(data);
  std::ostringstream oss;

  EXPECT_THROW(img->printStructure(oss, kpsBasic, 0), Error);
}

// Test: printStructure with empty data
TEST_F(Jp2ImagePrintStructureTest_86, PrintStructure_EmptyData_Throws_86) {
  std::vector<uint8_t> emptyData;
  auto io = std::make_unique<MemIo>();
  auto img = std::make_unique<Jp2Image>(std::move(io), false);
  std::ostringstream oss;

  EXPECT_THROW(img->printStructure(oss, kpsBasic, 0), Error);
}

// Test: printStructure with kpsNone should not print anything
TEST_F(Jp2ImagePrintStructureTest_86, PrintStructure_KpsNone_NoOutput_86) {
  auto data = buildMinimalJp2();
  auto img = createJp2Image(data);
  std::ostringstream oss;

  // kpsNone should result in no output and no processing
  ASSERT_NO_THROW(img->printStructure(oss, kpsNone, 0));
  EXPECT_TRUE(oss.str().empty());
}

// Test: printStructure with duplicate signature boxes should throw
TEST_F(Jp2ImagePrintStructureTest_86, PrintStructure_DuplicateSignature_Throws_86) {
  auto data = buildDuplicateSignatureJp2();
  auto img = createJp2Image(data);
  std::ostringstream oss;

  EXPECT_THROW(img->printStructure(oss, kpsBasic, 0), Error);
}

// Test: printStructure with kpsXMP extracts XMP data
TEST_F(Jp2ImagePrintStructureTest_86, PrintStructure_KpsXMP_ExtractsXmp_86) {
  auto data = buildJp2WithXmpUuid();
  auto img = createJp2Image(data);
  std::ostringstream oss;

  ASSERT_NO_THROW(img->printStructure(oss, kpsXMP, 0));

  std::string output = oss.str();
  EXPECT_TRUE(output.find("<xmp>test xmp data</xmp>") != std::string::npos);
}

// Test: printStructure with kpsRecursive on valid JP2
TEST_F(Jp2ImagePrintStructureTest_86, PrintStructure_KpsRecursive_ValidJp2_86) {
  auto data = buildMinimalJp2();
  auto img = createJp2Image(data);
  std::ostringstream oss;

  ASSERT_NO_THROW(img->printStructure(oss, kpsRecursive, 0));

  std::string output = oss.str();
  EXPECT_TRUE(output.find("STRUCTURE OF JPEG2000 FILE") != std::string::npos);
}

// Test: printStructure with invalid ImageHeader compression type throws
TEST_F(Jp2ImagePrintStructureTest_86, PrintStructure_BadCompressionType_Throws_86) {
  auto data = buildJp2WithBadImageHeader();
  auto img = createJp2Image(data);
  std::ostringstream oss;

  EXPECT_THROW(img->printStructure(oss, kpsBasic, 0), Error);
}

// Test: printStructure with invalid ColorSpec enumCS throws
TEST_F(Jp2ImagePrintStructureTest_86, PrintStructure_BadColorSpec_Throws_86) {
  auto data = buildJp2WithBadColorSpec();
  auto img = createJp2Image(data);
  std::ostringstream oss;

  EXPECT_THROW(img->printStructure(oss, kpsBasic, 0), Error);
}

// Test: printStructure with kpsIptcErase on valid JP2 should not throw
TEST_F(Jp2ImagePrintStructureTest_86, PrintStructure_KpsIptcErase_NoThrow_86) {
  auto data = buildMinimalJp2();
  auto img = createJp2Image(data);
  std::ostringstream oss;

  ASSERT_NO_THROW(img->printStructure(oss, kpsIptcErase, 0));
}

// Test: printStructure basic output contains box type identifiers
TEST_F(Jp2ImagePrintStructureTest_86, PrintStructure_Basic_ContainsBoxInfo_86) {
  auto data = buildMinimalJp2();
  auto img = createJp2Image(data);
  std::ostringstream oss;

  ASSERT_NO_THROW(img->printStructure(oss, kpsBasic, 0));

  std::string output = oss.str();
  // The output should contain sub-box references for the header
  EXPECT_TRUE(output.find("sub:") != std::string::npos);
}

// Test: printStructure with kpsIccProfile on minimal JP2 (no ICC profile)
TEST_F(Jp2ImagePrintStructureTest_86, PrintStructure_KpsIccProfile_NoIcc_86) {
  auto data = buildMinimalJp2();
  auto img = createJp2Image(data);
  std::ostringstream oss;

  // Should not throw; minimal file has METH=1 (enumerated), no ICC
  ASSERT_NO_THROW(img->printStructure(oss, kpsIccProfile, 0));
}

// Test: printStructure with kpsXMP on minimal JP2 without XMP UUID
TEST_F(Jp2ImagePrintStructureTest_86, PrintStructure_KpsXMP_NoXmp_86) {
  auto data = buildMinimalJp2();
  auto img = createJp2Image(data);
  std::ostringstream oss;

  ASSERT_NO_THROW(img->printStructure(oss, kpsXMP, 0));

  // No XMP data in minimal file
  EXPECT_TRUE(oss.str().empty());
}

// Test: JP2 with ColorSpec METH=2 (Restricted ICC Profile) and valid ICC data
TEST_F(Jp2ImagePrintStructureTest_86, PrintStructure_IccProfile_METH2_86) {
  std::vector<uint8_t> data;

  // Signature box
  writeBE32(data, 12);
  writeBE32(data, kSignature);
  data.insert(data.end(), kJp2SignatureData.begin(), kJp2SignatureData.end());

  // File Type box
  writeBE32(data, 20);
  writeBE32(data, kFileTypeBox);
  data.push_back('j'); data.push_back('p'); data.push_back('2'); data.push_back(' ');
  writeBE32(data, 0);
  data.push_back('j'); data.push_back('p'); data.push_back('2'); data.push_back(' ');

  // Header with valid ImageHeader and ColorSpec METH=2
  std::vector<uint8_t> ihdrData;
  writeBE32(ihdrData, 22);
  writeBE32(ihdrData, kImageHeader);
  writeBE32(ihdrData, 100);
  writeBE32(ihdrData, 200);
  ihdrData.push_back(0); ihdrData.push_back(3);
  ihdrData.push_back(8);
  ihdrData.push_back(7);
  ihdrData.push_back(0);
  ihdrData.push_back(0);

  // ColorSpec with METH=2 (ICC profile), pad=3, iccLength, then ICC data
  std::vector<uint8_t> iccProfileData(20, 0xAB); // fake ICC data
  std::vector<uint8_t> colrPayload;
  colrPayload.push_back(2);   // METH = 2
  colrPayload.push_back(0);   // PREC
  colrPayload.push_back(0);   // APPROX
  // pad bytes (3 bytes): iccLength is at offset 3
  writeBE32(colrPayload, static_cast<uint32_t>(iccProfileData.size()));
  colrPayload.insert(colrPayload.end(), iccProfileData.begin(), iccProfileData.end());

  std::vector<uint8_t> colrBox;
  writeBE32(colrBox, static_cast<uint32_t>(8 + colrPayload.size()));
  writeBE32(colrBox, kColorSpec);
  colrBox.insert(colrBox.end(), colrPayload.begin(), colrPayload.end());

  size_t headerLen = 8 + ihdrData.size() + colrBox.size();
  writeBE32(data, static_cast<uint32_t>(headerLen));
  writeBE32(data, kHeader);
  data.insert(data.end(), ihdrData.begin(), ihdrData.end());
  data.insert(data.end(), colrBox.begin(), colrBox.end());

  // Close box
  writeBE32(data, 8);
  writeBE32(data, kClose);

  auto img = createJp2Image(data);
  std::ostringstream oss;

  ASSERT_NO_THROW(img->printStructure(oss, kpsIccProfile, 0));

  // The ICC data should have been written to the output
  std::string output = oss.str();
  EXPECT_EQ(output.size(), iccProfileData.size());
}

// Test: JP2 with only close box (no signature) - should handle gracefully or throw
TEST_F(Jp2ImagePrintStructureTest_86, PrintStructure_OnlyCloseBox_86) {
  std::vector<uint8_t> data;

  // First we need valid JP2 signature for isJp2Type to pass
  writeBE32(data, 12);
  writeBE32(data, kSignature);
  data.insert(data.end(), kJp2SignatureData.begin(), kJp2SignatureData.end());

  // File Type box
  writeBE32(data, 20);
  writeBE32(data, kFileTypeBox);
  data.push_back('j'); data.push_back('p'); data.push_back('2'); data.push_back(' ');
  writeBE32(data, 0);
  data.push_back('j'); data.push_back('p'); data.push_back('2'); data.push_back(' ');

  // Close box immediately
  writeBE32(data, 8);
  writeBE32(data, kClose);

  auto img = createJp2Image(data);
  std::ostringstream oss;

  ASSERT_NO_THROW(img->printStructure(oss, kpsBasic, 0));
}

// Test: Jp2Image mimeType returns correct type
TEST_F(Jp2ImagePrintStructureTest_86, MimeType_ReturnsCorrectType_86) {
  auto data = buildMinimalJp2();
  auto img = createJp2Image(data);

  std::string mime = img->mimeType();
  EXPECT_FALSE(mime.empty());
}

// Test: setComment is a no-op for JP2
TEST_F(Jp2ImagePrintStructureTest_86, SetComment_NoOp_86) {
  auto data = buildMinimalJp2();
  auto img = createJp2Image(data);

  ASSERT_NO_THROW(img->setComment("test comment"));
}

// Test: printStructure with kpsBasic outputs header line
TEST_F(Jp2ImagePrintStructureTest_86, PrintStructure_BasicHeader_86) {
  auto data = buildMinimalJp2();
  auto img = createJp2Image(data);
  std::ostringstream oss;

  img->printStructure(oss, kpsBasic, 0);

  std::string output = oss.str();
  EXPECT_TRUE(output.find("address") != std::string::npos);
  EXPECT_TRUE(output.find("box") != std::string::npos);
  EXPECT_TRUE(output.find("data") != std::string::npos);
}

// Test: ImageHeader with unkC > 1 throws
TEST_F(Jp2ImagePrintStructureTest_86, PrintStructure_BadUnkC_Throws_86) {
  std::vector<uint8_t> data;

  writeBE32(data, 12);
  writeBE32(data, kSignature);
  data.insert(data.end(), kJp2SignatureData.begin(), kJp2SignatureData.end());

  writeBE32(data, 20);
  writeBE32(data, kFileTypeBox);
  data.push_back('j'); data.push_back('p'); data.push_back('2'); data.push_back(' ');
  writeBE32(data, 0);
  data.push_back('j'); data.push_back('p'); data.push_back('2'); data.push_back(' ');

  std::vector<uint8_t> ihdrData;
  writeBE32(ihdrData, 22);
  writeBE32(ihdrData, kImageHeader);
  writeBE32(ihdrData, 100);
  writeBE32(ihdrData, 200);
  ihdrData.push_back(0); ihdrData.push_back(3);
  ihdrData.push_back(8);
  ihdrData.push_back(7);   // compressionType = 7 (valid)
  ihdrData.push_back(2);   // unkC = 2 (invalid, must be 0 or 1)
  ihdrData.push_back(0);

  size_t headerLen = 8 + ihdrData.size();
  writeBE32(data, static_cast<uint32_t>(headerLen));
  writeBE32(data, kHeader);
  data.insert(data.end(), ihdrData.begin(), ihdrData.end());

  writeBE32(data, 8);
  writeBE32(data, kClose);

  auto img = createJp2Image(data);
  std::ostringstream oss;

  EXPECT_THROW(img->printStructure(oss, kpsBasic, 0), Error);
}

// Test: ImageHeader with ipr > 1 throws
TEST_F(Jp2ImagePrintStructureTest_86, PrintStructure_BadIpr_Throws_86) {
  std::vector<uint8_t> data;

  writeBE32(data, 12);
  writeBE32(data, kSignature);
  data.insert(data.end(), kJp2SignatureData.begin(), kJp2SignatureData.end());

  writeBE32(data, 20);
  writeBE32(data, kFileTypeBox);
  data.push_back('j'); data.push_back('p'); data.push_back('2'); data.push_back(' ');
  writeBE32(data, 0);
  data.push_back('j'); data.push_back('p'); data.push_back('2'); data.push_back(' ');

  std::vector<uint8_t> ihdrData;
  writeBE32(ihdrData, 22);
  writeBE32(ihdrData, kImageHeader);
  writeBE32(ihdrData, 100);
  writeBE32(ihdrData, 200);
  ihdrData.push_back(0); ihdrData.push_back(3);
  ihdrData.push_back(8);
  ihdrData.push_back(7);
  ihdrData.push_back(0);
  ihdrData.push_back(2);   // ipr = 2 (invalid)

  size_t headerLen = 8 + ihdrData.size();
  writeBE32(data, static_cast<uint32_t>(headerLen));
  writeBE32(data, kHeader);
  data.insert(data.end(), ihdrData.begin(), ihdrData.end());

  writeBE32(data, 8);
  writeBE32(data, kClose);

  auto img = createJp2Image(data);
  std::ostringstream oss;

  EXPECT_THROW(img->printStructure(oss, kpsBasic, 0), Error);
}

// Test: ImageHeader with wrong length (!= 22) throws
TEST_F(Jp2ImagePrintStructureTest_86, PrintStructure_BadImageHeaderLength_Throws_86) {
  std::vector<uint8_t> data;

  writeBE32(data, 12);
  writeBE32(data, kSignature);
  data.insert(data.end(), kJp2SignatureData.begin(), kJp2SignatureData.end());

  writeBE32(data, 20);
  writeBE32(data, kFileTypeBox);
  data.push_back('j'); data.push_back('p'); data.push_back('2'); data.push_back(' ');
  writeBE32(data, 0);
  data.push_back('j'); data.push_back('p'); data.push_back('2'); data.push_back(' ');

  // ImageHeader with wrong length (20 instead of 22)
  std::vector<uint8_t> ihdrData;
  writeBE32(ihdrData, 20);  // Wrong length
  writeBE32(ihdrData, kImageHeader);
  writeBE32(ihdrData, 100);
  writeBE32(ihdrData, 200);
  ihdrData.push_back(0); ihdrData.push_back(3);
  ihdrData.push_back(8);
  ihdrData.push_back(7);

  size_t headerLen = 8 + ihdrData.size();
  writeBE32(data, static_cast<uint32_t>(headerLen));
  writeBE32(data, kHeader);
  data.insert(data.end(), ihdrData.begin(), ihdrData.end());

  writeBE32(data, 8);
  writeBE32(data, kClose);

  auto img = createJp2Image(data);
  std::ostringstream oss;

  EXPECT_THROW(img->printStructure(oss, kpsBasic, 0), Error);
}

// Test: ColorSpec with enumCS=17 (greyscale) is valid
TEST_F(Jp2ImagePrintStructureTest_86, PrintStructure_ColorSpecEnumCS17_Valid_86) {
  std::vector<uint8_t> data;

  writeBE32(data, 12);
  writeBE32(data, kSignature);
  data.insert(data.end(), kJp2SignatureData.begin(), kJp2SignatureData.end());

  writeBE32(data, 20);
  writeBE32(data, kFileTypeBox);
  data.push_back('j'); data.push_back('p'); data.push_back('2'); data.push_back(' ');
  writeBE32(data, 0);
  data.push_back('j'); data.push_back('p'); data.push_back('2'); data.push_back(' ');

  std::vector<uint8_t> ihdrData;
  writeBE32(ihdrData, 22);
  writeBE32(ihdrData, kImageHeader);
  writeBE32(ihdrData, 100);
  writeBE32(ihdrData, 200);
  ihdrData.push_back(0); ihdrData.push_back(3);
  ihdrData.push_back(8);
  ihdrData.push_back(7);
  ihdrData.push_back(0);
  ihdrData.push_back(0);

  std::vector<uint8_t> colrData;
  writeBE32(colrData, 15);
  writeBE32(colrData, kColorSpec);
  colrData.push_back(1);
  colrData.push_back(0);
  colrData.push_back(0);
  writeBE32(colrData, 17);  // enumCS = 17 (greyscale, valid)

  size_t headerLen = 8 + ihdrData.size() + colrData.size();
  writeBE32(data, static_cast<uint32_t>(headerLen));
  writeBE32(data, kHeader);
  data.insert(data.end(), ihdrData.begin(), ihdrData.end());
  data.insert(data.end(), colrData.begin(), colrData.end());

  writeBE32(data, 8);
  writeBE32(data, kClose);

  auto img = createJp2Image(data);
  std::ostringstream oss;

  ASSERT_NO_THROW(img->printStructure(oss, kpsBasic, 0));
}
