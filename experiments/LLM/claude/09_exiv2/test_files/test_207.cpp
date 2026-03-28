#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <exiv2/exiv2.hpp>

// We need access to the internal function we're testing
namespace Exiv2 {
namespace Internal {
// Forward declaration of the function under test
std::ostream& resolveLens0x319(std::ostream& os, const Value& value, const ExifData* metadata);
}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class ResolveLens0x319Test_207 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}

  // Helper: create ExifData with a given model string
  void setModel(ExifData& exifData, const std::string& model) {
    exifData["Exif.Image.Model"] = model;
  }

  // Helper: create a Value with given count of uint16 elements
  std::unique_ptr<Value> createUShortValue(const std::vector<uint16_t>& values) {
    auto v = Value::create(unsignedShort);
    for (const auto& val : values) {
      std::ostringstream oss;
      oss << val;
      if (&val == &values[0]) {
        v->read(oss.str());
      } else {
        // For multi-value, we need to build a space-separated string
        // Actually, let's rebuild:
      }
    }
    // Better approach: build space-separated string
    std::ostringstream oss;
    for (size_t i = 0; i < values.size(); ++i) {
      if (i > 0) oss << " ";
      oss << values[i];
    }
    auto v2 = Value::create(unsignedShort);
    v2->read(oss.str());
    return v2;
  }

  // Helper: set lens info with specific byte values
  void setLensInfo(ExifData& exifData, const std::vector<uint8_t>& data) {
    auto v = Value::create(unsignedByte);
    std::ostringstream oss;
    for (size_t i = 0; i < data.size(); ++i) {
      if (i > 0) oss << " ";
      oss << static_cast<int>(data[i]);
    }
    v->read(oss.str());
    exifData.add(ExifKey("Exif.Pentax.LensInfo"), v.get());
  }

  void setLensInfoMakernoteII(ExifData& exifData, const std::vector<uint8_t>& data) {
    auto v = Value::create(unsignedByte);
    std::ostringstream oss;
    for (size_t i = 0; i < data.size(); ++i) {
      if (i > 0) oss << " ";
      oss << static_cast<int>(data[i]);
    }
    v->read(oss.str());
    exifData.add(ExifKey("Exif.PentaxDng.LensInfo"), v.get());
  }
};

// Test with nullptr metadata - should fall through to default behavior
TEST_F(ResolveLens0x319Test_207, NullMetadata_207) {
  std::ostringstream os;
  auto value = createUShortValue({3, 25});  // 0x319 = 793 in combined form, but value has 2 elements
  // With null metadata, should still produce some output without crashing
  resolveLens0x319(os, *value, nullptr);
  // Just verify it doesn't crash and produces some output
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test with empty ExifData - no model, no lens info
TEST_F(ResolveLens0x319Test_207, EmptyMetadata_207) {
  std::ostringstream os;
  auto value = createUShortValue({3, 25});
  ExifData exifData;
  resolveLens0x319(os, *value, &exifData);
  std::string result = os.str();
  // Should fall through to default EXV_PRINT_COMBITAG_MULTI
  EXPECT_FALSE(result.empty());
}

// Test with value count == 4 and PENTAX K-3 model with matching lens info (128 count, [1]=131, [2]=128)
TEST_F(ResolveLens0x319Test_207, PentaxK3WithMatchingLensInfo128_207) {
  std::ostringstream os;
  auto value = createUShortValue({3, 25, 0, 0});  // count == 4, encodes 0x319
  ExifData exifData;
  setModel(exifData, "PENTAX K-3");

  // Create lens info with 128 bytes, [1]=131, [2]=128
  std::vector<uint8_t> lensData(128, 0);
  lensData[1] = 131;
  lensData[2] = 128;
  setLensInfo(exifData, lensData);

  resolveLens0x319(os, *value, &exifData);
  std::string result = os.str();
  // Should resolve to index 6 of pentaxLensType entries for lensID 0x319
  EXPECT_FALSE(result.empty());
}

// Test with value count == 2 and PENTAX K100D model with lens info count 44
TEST_F(ResolveLens0x319Test_207, PentaxK100DWithLensInfo44_207) {
  std::ostringstream os;
  auto value = createUShortValue({3, 25});  // count == 2, encodes 0x319
  ExifData exifData;
  setModel(exifData, "PENTAX K100D");

  std::vector<uint8_t> lensData(44, 0);
  setLensInfo(exifData, lensData);

  resolveLens0x319(os, *value, &exifData);
  std::string result = os.str();
  // Should resolve to index 6
  EXPECT_FALSE(result.empty());
}

// Test with value count == 2 and PENTAX *ist DL model with lens info count 36
TEST_F(ResolveLens0x319Test_207, PentaxIstDLWithLensInfo36_207) {
  std::ostringstream os;
  auto value = createUShortValue({3, 25});  // count == 2
  ExifData exifData;
  setModel(exifData, "PENTAX *ist DL");

  std::vector<uint8_t> lensData(36, 0);
  setLensInfo(exifData, lensData);

  resolveLens0x319(os, *value, &exifData);
  std::string result = os.str();
  // Should resolve to index 6
  EXPECT_FALSE(result.empty());
}

// Test with value count == 2 but model doesn't match any special case
TEST_F(ResolveLens0x319Test_207, ValueCount2NonMatchingModel_207) {
  std::ostringstream os;
  auto value = createUShortValue({3, 25});
  ExifData exifData;
  setModel(exifData, "PENTAX K-5");

  std::vector<uint8_t> lensData(44, 0);
  setLensInfo(exifData, lensData);

  resolveLens0x319(os, *value, &exifData);
  std::string result = os.str();
  // Should fall through to default EXV_PRINT_COMBITAG_MULTI
  EXPECT_FALSE(result.empty());
}

// Test with value count == 4 but model doesn't start with "PENTAX K-3"
TEST_F(ResolveLens0x319Test_207, ValueCount4NonMatchingModel_207) {
  std::ostringstream os;
  auto value = createUShortValue({3, 25, 0, 0});
  ExifData exifData;
  setModel(exifData, "PENTAX K-5");

  std::vector<uint8_t> lensData(128, 0);
  lensData[1] = 131;
  lensData[2] = 128;
  setLensInfo(exifData, lensData);

  resolveLens0x319(os, *value, &exifData);
  std::string result = os.str();
  // Should fall through to default
  EXPECT_FALSE(result.empty());
}

// Test with value count == 4, PENTAX K-3 model but lens info count != 128
TEST_F(ResolveLens0x319Test_207, PentaxK3LensInfoCountMismatch_207) {
  std::ostringstream os;
  auto value = createUShortValue({3, 25, 0, 0});
  ExifData exifData;
  setModel(exifData, "PENTAX K-3");

  std::vector<uint8_t> lensData(64, 0);  // count = 64, not 128
  lensData[1] = 131;
  lensData[2] = 128;
  setLensInfo(exifData, lensData);

  resolveLens0x319(os, *value, &exifData);
  std::string result = os.str();
  // index stays 0, falls through to default
  EXPECT_FALSE(result.empty());
}

// Test with value count == 4, PENTAX K-3, lens info count 128, but [1] != 131
TEST_F(ResolveLens0x319Test_207, PentaxK3LensInfoByte1Mismatch_207) {
  std::ostringstream os;
  auto value = createUShortValue({3, 25, 0, 0});
  ExifData exifData;
  setModel(exifData, "PENTAX K-3");

  std::vector<uint8_t> lensData(128, 0);
  lensData[1] = 100;  // not 131
  lensData[2] = 128;
  setLensInfo(exifData, lensData);

  resolveLens0x319(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test with value count == 4, PENTAX K-3, lens info count 128, [1]=131 but [2] != 128
TEST_F(ResolveLens0x319Test_207, PentaxK3LensInfoByte2Mismatch_207) {
  std::ostringstream os;
  auto value = createUShortValue({3, 25, 0, 0});
  ExifData exifData;
  setModel(exifData, "PENTAX K-3");

  std::vector<uint8_t> lensData(128, 0);
  lensData[1] = 131;
  lensData[2] = 64;  // not 128
  setLensInfo(exifData, lensData);

  resolveLens0x319(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test with value count == 2, PENTAX K100D but lens info count != 44
TEST_F(ResolveLens0x319Test_207, PentaxK100DLensInfoCountMismatch_207) {
  std::ostringstream os;
  auto value = createUShortValue({3, 25});
  ExifData exifData;
  setModel(exifData, "PENTAX K100D");

  std::vector<uint8_t> lensData(50, 0);  // not 44
  setLensInfo(exifData, lensData);

  resolveLens0x319(os, *value, &exifData);
  std::string result = os.str();
  // Falls through to default
  EXPECT_FALSE(result.empty());
}

// Test with value count == 2, PENTAX *ist DL but lens info count != 36
TEST_F(ResolveLens0x319Test_207, PentaxIstDLLensInfoCountMismatch_207) {
  std::ostringstream os;
  auto value = createUShortValue({3, 25});
  ExifData exifData;
  setModel(exifData, "PENTAX *ist DL");

  std::vector<uint8_t> lensData(44, 0);  // not 36
  setLensInfo(exifData, lensData);

  resolveLens0x319(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test with value count == 1 (neither 2 nor 4 special cases)
TEST_F(ResolveLens0x319Test_207, ValueCount1FallsThrough_207) {
  std::ostringstream os;
  auto value = createUShortValue({25});  // count == 1
  ExifData exifData;
  setModel(exifData, "PENTAX K-3");

  resolveLens0x319(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test with value count == 3 (neither 2 nor 4)
TEST_F(ResolveLens0x319Test_207, ValueCount3FallsThrough_207) {
  std::ostringstream os;
  auto value = createUShortValue({3, 25, 0});
  ExifData exifData;
  setModel(exifData, "PENTAX K-3");

  std::vector<uint8_t> lensData(128, 0);
  lensData[1] = 131;
  lensData[2] = 128;
  setLensInfo(exifData, lensData);

  resolveLens0x319(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test PENTAX K-3 II variant (starts_with "PENTAX K-3")
TEST_F(ResolveLens0x319Test_207, PentaxK3IIWithMatchingLensInfo_207) {
  std::ostringstream os;
  auto value = createUShortValue({3, 25, 0, 0});
  ExifData exifData;
  setModel(exifData, "PENTAX K-3 II");

  std::vector<uint8_t> lensData(128, 0);
  lensData[1] = 131;
  lensData[2] = 128;
  setLensInfo(exifData, lensData);

  resolveLens0x319(os, *value, &exifData);
  std::string result = os.str();
  // Should still match since starts_with "PENTAX K-3"
  EXPECT_FALSE(result.empty());
}

// Test PENTAX K100D Super (starts_with "PENTAX K100D")
TEST_F(ResolveLens0x319Test_207, PentaxK100DSuperWithLensInfo44_207) {
  std::ostringstream os;
  auto value = createUShortValue({3, 25});
  ExifData exifData;
  setModel(exifData, "PENTAX K100D Super");

  std::vector<uint8_t> lensData(44, 0);
  setLensInfo(exifData, lensData);

  resolveLens0x319(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test with no lens info key present in metadata (should trigger exception path)
TEST_F(ResolveLens0x319Test_207, NoLensInfoInMetadata_207) {
  std::ostringstream os;
  auto value = createUShortValue({3, 25, 0, 0});
  ExifData exifData;
  setModel(exifData, "PENTAX K-3");
  // Don't add any lens info

  resolveLens0x319(os, *value, &exifData);
  std::string result = os.str();
  // Should fall through to default after exception is caught
  EXPECT_FALSE(result.empty());
}

// Test that PentaxDng lens info is also found
TEST_F(ResolveLens0x319Test_207, PentaxDngLensInfo_207) {
  std::ostringstream os;
  auto value = createUShortValue({3, 25});
  ExifData exifData;
  setModel(exifData, "PENTAX K100D");

  // Use PentaxDng namespace for lens info
  setLensInfoMakernoteII(exifData, std::vector<uint8_t>(44, 0));

  resolveLens0x319(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test with PENTAX *ist DL2 (starts_with "PENTAX *ist DL")
TEST_F(ResolveLens0x319Test_207, PentaxIstDL2WithLensInfo36_207) {
  std::ostringstream os;
  auto value = createUShortValue({3, 25});
  ExifData exifData;
  setModel(exifData, "PENTAX *ist DL2");

  std::vector<uint8_t> lensData(36, 0);
  setLensInfo(exifData, lensData);

  resolveLens0x319(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}
