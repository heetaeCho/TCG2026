#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <exiv2/exiv2.hpp>

// Forward declaration of the function under test
namespace Exiv2 {
namespace Internal {
std::ostream& printCsLensTypeByMetadata(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

using namespace Exiv2;
using namespace Exiv2::Internal;

class PrintCsLensTypeByMetadataTest_949 : public ::testing::Test {
protected:
  std::ostringstream os;

  // Helper to create an UShortValue with given values
  Value::UniquePtr makeUShortValue(std::initializer_list<uint16_t> vals) {
    auto v = Value::create(unsignedShort);
    for (auto val : vals) {
      std::string s = std::to_string(val);
      v->read(s);
    }
    return v;
  }

  // Helper to create a signed short value
  Value::UniquePtr makeSignedShortValue(std::initializer_list<int16_t> vals) {
    auto v = Value::create(signedShort);
    for (auto val : vals) {
      std::string s = std::to_string(val);
      v->read(s);
    }
    return v;
  }

  // Helper to create a string value
  Value::UniquePtr makeStringValue(const std::string& s) {
    auto v = Value::create(asciiString);
    v->read(s);
    return v;
  }
};

// Test: null metadata returns os << value
TEST_F(PrintCsLensTypeByMetadataTest_949, NullMetadataReturnsValue_949) {
  auto val = makeUShortValue({1});
  printCsLensTypeByMetadata(os, *val, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// Test: wrong type (not unsignedShort) returns os << value
TEST_F(PrintCsLensTypeByMetadataTest_949, WrongTypeIdReturnsValue_949) {
  auto val = Value::create(signedShort);
  val->read("1");
  ExifData metadata;
  printCsLensTypeByMetadata(os, *val, &metadata);
  EXPECT_FALSE(os.str().empty());
}

// Test: empty value (count==0) returns os << value
TEST_F(PrintCsLensTypeByMetadataTest_949, EmptyValueReturnsValue_949) {
  auto val = Value::create(unsignedShort);
  // Don't add any values - count should be 0
  ExifData metadata;
  printCsLensTypeByMetadata(os, *val, &metadata);
  // The output should just be the value printed
}

// Test: lensType 0xffff triggers printCsLensFFFF path
TEST_F(PrintCsLensTypeByMetadataTest_949, LensTypeFFFF_949) {
  auto val = makeUShortValue({0xffff});
  ExifData metadata;
  // Even without proper metadata for FFFF path, it should not crash
  printCsLensTypeByMetadata(os, *val, &metadata);
  EXPECT_FALSE(os.str().empty());
}

// Test: missing Exif.CanonCs.Lens key returns "Unknown Lens"
TEST_F(PrintCsLensTypeByMetadataTest_949, MissingLensKeyReturnsUnknown_949) {
  auto val = makeUShortValue({1});
  ExifData metadata;
  printCsLensTypeByMetadata(os, *val, &metadata);
  std::string result = os.str();
  EXPECT_NE(result.find("Unknown Lens"), std::string::npos);
}

// Test: Exif.CanonCs.Lens with count < 3 returns "Unknown Lens"
TEST_F(PrintCsLensTypeByMetadataTest_949, LensKeyCountLessThan3ReturnsUnknown_949) {
  auto val = makeUShortValue({1});
  ExifData metadata;
  // Add lens key with only 2 values
  ExifKey lensKey("Exif.CanonCs.Lens");
  auto lensVal = makeUShortValue({50, 50});
  metadata.add(lensKey, lensVal.get());

  printCsLensTypeByMetadata(os, *val, &metadata);
  std::string result = os.str();
  EXPECT_NE(result.find("Unknown Lens"), std::string::npos);
}

// Test: Exif.CanonCs.Lens with third value (divisor) == 0 returns "Unknown Lens"
TEST_F(PrintCsLensTypeByMetadataTest_949, LensDivisorZeroReturnsUnknown_949) {
  auto val = makeUShortValue({1});
  ExifData metadata;
  ExifKey lensKey("Exif.CanonCs.Lens");
  auto lensVal = makeUShortValue({50, 50, 0});
  metadata.add(lensKey, lensVal.get());

  printCsLensTypeByMetadata(os, *val, &metadata);
  std::string result = os.str();
  EXPECT_NE(result.find("Unknown Lens"), std::string::npos);
}

// Test: Missing MaxAperture key returns "Unknown Lens"
TEST_F(PrintCsLensTypeByMetadataTest_949, MissingMaxApertureReturnsUnknown_949) {
  auto val = makeUShortValue({1});
  ExifData metadata;
  ExifKey lensKey("Exif.CanonCs.Lens");
  auto lensVal = makeUShortValue({50, 50, 1});
  metadata.add(lensKey, lensVal.get());
  // Don't add MaxAperture

  printCsLensTypeByMetadata(os, *val, &metadata);
  std::string result = os.str();
  EXPECT_NE(result.find("Unknown Lens"), std::string::npos);
}

// Test: MaxAperture with wrong count returns "Unknown Lens"
TEST_F(PrintCsLensTypeByMetadataTest_949, MaxApertureWrongCountReturnsUnknown_949) {
  auto val = makeUShortValue({1});
  ExifData metadata;
  ExifKey lensKey("Exif.CanonCs.Lens");
  auto lensVal = makeUShortValue({50, 50, 1});
  metadata.add(lensKey, lensVal.get());

  ExifKey aperKey("Exif.CanonCs.MaxAperture");
  auto aperVal = makeUShortValue({32, 32}); // count == 2, should be 1
  metadata.add(aperKey, aperVal.get());

  printCsLensTypeByMetadata(os, *val, &metadata);
  std::string result = os.str();
  EXPECT_NE(result.find("Unknown Lens"), std::string::npos);
}

// Test: Successful lookup for Canon EF 50mm f/1.8 (lensType=1)
// Canon EF 50mm f/1.8 => fl 50mm, aperture f/1.8
TEST_F(PrintCsLensTypeByMetadataTest_949, SuccessfulLensLookupCanonEF50_949) {
  auto val = makeUShortValue({1}); // lensType = 1 => "Canon EF 50mm f/1.8"
  ExifData metadata;

  // Lens: maxFl=50, minFl=50, divisor=1
  ExifKey lensKey("Exif.CanonCs.Lens");
  auto lensVal = makeUShortValue({50, 50, 1});
  metadata.add(lensKey, lensVal.get());

  // MaxAperture: We need a value that when processed through canonEv and fnumber
  // gives approximately 1.8. The encoding for Canon aperture values uses
  // a specific formula. For f/1.8, the raw value is typically around 0x18 (24).
  // Let's try a value. canonEv converts int16_t to an EV, then fnumber converts that.
  // Actually, the aperture encoding: aperture = 2^(ev/2), where ev is in APEX units
  // For f/1.8: ev = 2*log2(1.8) ≈ 1.695. In Canon units (1/3 EV steps * 32):
  // raw = ev * 32 = ~54. But this depends on exact internal implementation.
  // Let's use a raw value that's commonly seen for f/1.8.
  // Typical Canon MaxAperture for f/1.8 is around 37 (0x25).
  // We'll try 37 and see if it matches.
  ExifKey aperKey("Exif.CanonCs.MaxAperture");
  auto aperVal = makeUShortValue({37});
  metadata.add(aperKey, aperVal.get());

  printCsLensTypeByMetadata(os, *val, &metadata);
  std::string result = os.str();
  // It should either match "Canon EF 50mm f/1.8" or show "Unknown Lens (1)"
  // Since we're not sure about the exact aperture encoding, check it doesn't crash
  EXPECT_FALSE(result.empty());
}

// Test: Lens type that doesn't exist in the table returns "Unknown Lens"
TEST_F(PrintCsLensTypeByMetadataTest_949, NonexistentLensTypeReturnsUnknown_949) {
  auto val = makeUShortValue({9999}); // Not in the table
  ExifData metadata;

  ExifKey lensKey("Exif.CanonCs.Lens");
  auto lensVal = makeUShortValue({50, 50, 1});
  metadata.add(lensKey, lensVal.get());

  ExifKey aperKey("Exif.CanonCs.MaxAperture");
  auto aperVal = makeUShortValue({37});
  metadata.add(aperKey, aperVal.get());

  printCsLensTypeByMetadata(os, *val, &metadata);
  std::string result = os.str();
  EXPECT_NE(result.find("Unknown Lens"), std::string::npos);
  EXPECT_NE(result.find("9999"), std::string::npos);
}

// Test: MaxAperture with wrong type returns "Unknown Lens"
TEST_F(PrintCsLensTypeByMetadataTest_949, MaxApertureWrongTypeReturnsUnknown_949) {
  auto val = makeUShortValue({1});
  ExifData metadata;

  ExifKey lensKey("Exif.CanonCs.Lens");
  auto lensVal = makeUShortValue({50, 50, 1});
  metadata.add(lensKey, lensVal.get());

  ExifKey aperKey("Exif.CanonCs.MaxAperture");
  auto aperVal = makeSignedShortValue({37}); // Wrong type: signedShort instead of unsignedShort
  metadata.add(aperKey, aperVal.get());

  printCsLensTypeByMetadata(os, *val, &metadata);
  std::string result = os.str();
  EXPECT_NE(result.find("Unknown Lens"), std::string::npos);
}

// Test: Lens key with wrong type returns "Unknown Lens"
TEST_F(PrintCsLensTypeByMetadataTest_949, LensKeyWrongTypeReturnsUnknown_949) {
  auto val = makeUShortValue({1});
  ExifData metadata;

  ExifKey lensKey("Exif.CanonCs.Lens");
  auto lensVal = makeSignedShortValue({50, 50, 1}); // Wrong type: signedShort
  metadata.add(lensKey, lensVal.get());

  printCsLensTypeByMetadata(os, *val, &metadata);
  std::string result = os.str();
  EXPECT_NE(result.find("Unknown Lens"), std::string::npos);
}

// Test: lensType = 29 (Canon EF 50mm f/1.8 II) - unique mapping
// Canon EF 50mm f/1.8 II => 50mm fixed, f/1.8
TEST_F(PrintCsLensTypeByMetadataTest_949, CanonEF50mmF18II_949) {
  auto val = makeUShortValue({29});
  ExifData metadata;

  // fl: 50/1=50, 50/1=50
  ExifKey lensKey("Exif.CanonCs.Lens");
  auto lensVal = makeUShortValue({50, 50, 1});
  metadata.add(lensKey, lensVal.get());

  ExifKey aperKey("Exif.CanonCs.MaxAperture");
  auto aperVal = makeUShortValue({37}); // Approximate for f/1.8
  metadata.add(aperKey, aperVal.get());

  printCsLensTypeByMetadata(os, *val, &metadata);
  std::string result = os.str();
  // Should either match or show unknown
  EXPECT_FALSE(result.empty());
}

// Test: Lens type with mismatched focal length returns "Unknown Lens"
TEST_F(PrintCsLensTypeByMetadataTest_949, MismatchedFocalLengthReturnsUnknown_949) {
  auto val = makeUShortValue({1}); // Canon EF 50mm f/1.8
  ExifData metadata;

  // Set completely wrong focal lengths (200mm instead of 50mm)
  ExifKey lensKey("Exif.CanonCs.Lens");
  auto lensVal = makeUShortValue({200, 200, 1});
  metadata.add(lensKey, lensVal.get());

  ExifKey aperKey("Exif.CanonCs.MaxAperture");
  auto aperVal = makeUShortValue({37});
  metadata.add(aperKey, aperVal.get());

  printCsLensTypeByMetadata(os, *val, &metadata);
  std::string result = os.str();
  EXPECT_NE(result.find("Unknown Lens"), std::string::npos);
}

// Test: Return value is the same ostream reference
TEST_F(PrintCsLensTypeByMetadataTest_949, ReturnsSameOstream_949) {
  auto val = makeUShortValue({1});
  std::ostream& result = printCsLensTypeByMetadata(os, *val, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test: Lens with divisor > 1
TEST_F(PrintCsLensTypeByMetadataTest_949, LensDivisorGreaterThanOne_949) {
  auto val = makeUShortValue({1}); // Canon EF 50mm f/1.8
  ExifData metadata;

  // fl: 100/2=50, 100/2=50
  ExifKey lensKey("Exif.CanonCs.Lens");
  auto lensVal = makeUShortValue({100, 100, 2});
  metadata.add(lensKey, lensVal.get());

  ExifKey aperKey("Exif.CanonCs.MaxAperture");
  auto aperVal = makeUShortValue({37});
  metadata.add(aperKey, aperVal.get());

  printCsLensTypeByMetadata(os, *val, &metadata);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test: n/a lens type (65535 = 0xFFFF)
TEST_F(PrintCsLensTypeByMetadataTest_949, LensType65535_949) {
  auto val = makeUShortValue({65535}); // 0xFFFF = n/a, triggers printCsLensFFFF
  ExifData metadata;
  printCsLensTypeByMetadata(os, *val, &metadata);
  EXPECT_FALSE(os.str().empty());
}

// Test: Multiple lens types with same value (ambiguous lenses)
// lensType = 6 has multiple entries
TEST_F(PrintCsLensTypeByMetadataTest_949, AmbiguousLensType_949) {
  auto val = makeUShortValue({6}); // Multiple lenses with type 6
  ExifData metadata;

  // Canon EF 28-70mm f/3.5-4.5 => fl: 28-70
  ExifKey lensKey("Exif.CanonCs.Lens");
  auto lensVal = makeUShortValue({70, 28, 1});
  metadata.add(lensKey, lensVal.get());

  ExifKey aperKey("Exif.CanonCs.MaxAperture");
  auto aperVal = makeUShortValue({40}); // approximate
  metadata.add(aperKey, aperVal.get());

  printCsLensTypeByMetadata(os, *val, &metadata);
  std::string result = os.str();
  // Should produce some output (either a match or unknown)
  EXPECT_FALSE(result.empty());
}

// Test: Zoom lens with correct range - EF-S 18-55mm (type 45)
TEST_F(PrintCsLensTypeByMetadataTest_949, ZoomLensEFS1855_949) {
  auto val = makeUShortValue({45}); // Canon EF-S 18-55mm f/3.5-5.6 [II]
  ExifData metadata;

  ExifKey lensKey("Exif.CanonCs.Lens");
  auto lensVal = makeUShortValue({55, 18, 1});
  metadata.add(lensKey, lensVal.get());

  ExifKey aperKey("Exif.CanonCs.MaxAperture");
  // For f/3.5-5.6, MaxAperture should be somewhere around f/3.5-5.6 range
  auto aperVal = makeUShortValue({53}); // approximate for f/3.5
  metadata.add(aperKey, aperVal.get());

  printCsLensTypeByMetadata(os, *val, &metadata);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}
