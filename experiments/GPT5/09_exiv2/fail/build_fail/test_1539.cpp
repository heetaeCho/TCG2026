// ============================================================================
// TEST_ID: 1539
// File: test_sony2010eSelector_1539.cpp
// Target: Exiv2::Internal::sony2010eSelector (makernote_int.cpp)
// ============================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

#include "makernote_int.hpp"     // Exiv2::Internal::sony2010eSelector
#include "tiffparser_int.hpp"    // Exiv2::Internal::TiffParser (to build a TiffComponent tree)
#include "types.hpp"             // Exiv2::byte, Exiv2::ByteOrder, Exiv2::littleEndian

namespace {

using Exiv2::byte;

static void appendLE16(std::vector<byte>& v, uint16_t x) {
  v.push_back(static_cast<byte>(x & 0xff));
  v.push_back(static_cast<byte>((x >> 8) & 0xff));
}

static void appendLE32(std::vector<byte>& v, uint32_t x) {
  v.push_back(static_cast<byte>(x & 0xff));
  v.push_back(static_cast<byte>((x >> 8) & 0xff));
  v.push_back(static_cast<byte>((x >> 16) & 0xff));
  v.push_back(static_cast<byte>((x >> 24) & 0xff));
}

// Build a minimal TIFF (little-endian) containing a single IFD0 entry: Model (0x0110) as ASCII.
// This is used only to create a TiffComponent* root for getExifModel(pRoot) to read from.
static std::vector<byte> makeMinimalTiffWithModel(const std::string& model) {
  // TIFF header: "II" 42, IFD0 offset = 8
  std::vector<byte> buf;
  buf.reserve(64 + model.size());

  buf.push_back(static_cast<byte>('I'));
  buf.push_back(static_cast<byte>('I'));
  appendLE16(buf, 42);
  appendLE32(buf, 8);

  // IFD0 at offset 8:
  // numEntries (2 bytes) = 1
  // entry (12 bytes)
  // nextIFDOffset (4 bytes) = 0
  const uint32_t ifd0Offset = 8;
  (void)ifd0Offset;

  appendLE16(buf, 1);  // one entry

  // Entry:
  // Tag = 0x0110 (Model)
  // Type = 2 (ASCII)
  // Count = model.size() + 1
  // ValueOffset = offset to the string data (placed after IFD)
  const uint16_t tagModel = 0x0110;
  const uint16_t typeAscii = 2;
  const uint32_t count = static_cast<uint32_t>(model.size() + 1);

  // Calculate where the string will live:
  // header (8) + numEntries(2) + entry(12) + nextIFD(4) = 26 bytes total.
  // So string offset = 8 + 2 + 12 + 4 = 26.
  const uint32_t valueOffset = 8 + 2 + 12 + 4;

  appendLE16(buf, tagModel);
  appendLE16(buf, typeAscii);
  appendLE32(buf, count);
  appendLE32(buf, valueOffset);

  appendLE32(buf, 0);  // next IFD offset

  // String data at valueOffset: model + '\0'
  // Ensure buffer size matches valueOffset.
  while (buf.size() < valueOffset) buf.push_back(0);

  buf.insert(buf.end(), model.begin(), model.end());
  buf.push_back(0);

  return buf;
}

static auto decodeTiffRoot(const std::vector<byte>& tiffBytes) {
  // Common Exiv2 internal API: TiffParser::decode(data, size, byteOrder)
  return Exiv2::Internal::TiffParser::decode(tiffBytes.data(), tiffBytes.size(), Exiv2::littleEndian);
}

class Sony2010eSelectorTest_1539 : public ::testing::Test {};

}  // namespace

TEST_F(Sony2010eSelectorTest_1539, NullRootReturnsMinus1_1539) {
  const uint16_t anyTag = 0;
  const byte* anyData = nullptr;
  const size_t anySize = 0;
  Exiv2::Internal::TiffComponent* root = nullptr;

  const int rc = Exiv2::Internal::sony2010eSelector(anyTag, anyData, anySize, root);
  EXPECT_EQ(-1, rc);
}

TEST_F(Sony2010eSelectorTest_1539, IgnoresTagDataAndSizeWhenRootNull_1539) {
  Exiv2::Internal::TiffComponent* root = nullptr;

  const byte dummy[4] = {0xde, 0xad, 0xbe, 0xef};

  const int rc1 = Exiv2::Internal::sony2010eSelector(0x0000, nullptr, 0, root);
  const int rc2 = Exiv2::Internal::sony2010eSelector(0xffff, dummy, 0, root);
  const int rc3 = Exiv2::Internal::sony2010eSelector(0x1234, dummy, sizeof(dummy), root);

  EXPECT_EQ(rc1, rc2);
  EXPECT_EQ(rc2, rc3);
  EXPECT_EQ(-1, rc1);
}

TEST_F(Sony2010eSelectorTest_1539, KnownModelsReturnZero_1539) {
  const char* const knownModels[] = {
      "SLT-A58",
      "ILCE-3000",
      "NEX-6",
      "DSC-RX1R",
      "DSC-WX300",
  };

  for (const char* model : knownModels) {
    const auto tiff = makeMinimalTiffWithModel(model);
    auto rootOwner = decodeTiffRoot(tiff);
    ASSERT_TRUE(static_cast<bool>(rootOwner)) << "Failed to decode TIFF root for model: " << model;

    Exiv2::Internal::TiffComponent* root = rootOwner.get();
    const int rc = Exiv2::Internal::sony2010eSelector(/*tag*/ 0, /*pData*/ nullptr, /*size*/ 0, root);
    EXPECT_EQ(0, rc) << "Expected selector to accept model: " << model;
  }
}

TEST_F(Sony2010eSelectorTest_1539, UnknownModelReturnsMinus1_1539) {
  const auto tiff = makeMinimalTiffWithModel("TOTALLY-NOT-A-SONY-MODEL");
  auto rootOwner = decodeTiffRoot(tiff);
  ASSERT_TRUE(static_cast<bool>(rootOwner));

  Exiv2::Internal::TiffComponent* root = rootOwner.get();
  const int rc = Exiv2::Internal::sony2010eSelector(/*tag*/ 0, /*pData*/ nullptr, /*size*/ 0, root);
  EXPECT_EQ(-1, rc);
}

TEST_F(Sony2010eSelectorTest_1539, CaseSensitivityBoundaryReturnsMinus1_1539) {
  // Boundary: same characters but different case.
  const auto tiff = makeMinimalTiffWithModel("slt-a58");
  auto rootOwner = decodeTiffRoot(tiff);
  ASSERT_TRUE(static_cast<bool>(rootOwner));

  Exiv2::Internal::TiffComponent* root = rootOwner.get();
  const int rc = Exiv2::Internal::sony2010eSelector(/*tag*/ 0, /*pData*/ nullptr, /*size*/ 0, root);
  EXPECT_EQ(-1, rc);
}

TEST_F(Sony2010eSelectorTest_1539, EmptyModelBoundaryReturnsMinus1_1539) {
  const auto tiff = makeMinimalTiffWithModel(std::string());
  auto rootOwner = decodeTiffRoot(tiff);
  ASSERT_TRUE(static_cast<bool>(rootOwner));

  Exiv2::Internal::TiffComponent* root = rootOwner.get();
  const int rc = Exiv2::Internal::sony2010eSelector(/*tag*/ 0, /*pData*/ nullptr, /*size*/ 0, root);
  EXPECT_EQ(-1, rc);
}