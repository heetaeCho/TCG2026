#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "exiv2/exif.hpp"
#include "exiv2/tags.hpp"
#include "exiv2/types.hpp"
#include "exiv2/value.hpp"

// Include the internal header for CanonMakerNote
// Based on the provided code structure
namespace Exiv2 {
namespace Internal {
class CanonMakerNote;
}
}

// We need access to the printFocalLength static method
#include "canonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_942 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test: When metadata is nullptr, should just print the value as-is
TEST_F(CanonMakerNoteTest_942, PrintFocalLength_NullMetadata_942) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  value->read("100 200 300 400");
  
  CanonMakerNote::printFocalLength(os, *value, nullptr);
  
  // When metadata is null, it should fall through to `os << value`
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test: When value count is less than 4, should just print the value
TEST_F(CanonMakerNoteTest_942, PrintFocalLength_ValueCountLessThan4_942) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  value->read("100 200 300");  // Only 3 values, need at least 4
  
  ExifData metadata;
  CanonMakerNote::printFocalLength(os, *value, &metadata);
  
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test: When value type is not unsignedShort, should just print the value
TEST_F(CanonMakerNoteTest_942, PrintFocalLength_WrongTypeId_942) {
  std::ostringstream os;
  auto value = Value::create(unsignedLong);
  value->read("100 200 300 400");
  
  ExifData metadata;
  CanonMakerNote::printFocalLength(os, *value, &metadata);
  
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test: When Exif.CanonCs.Lens key is not found in metadata, should print raw value
TEST_F(CanonMakerNoteTest_942, PrintFocalLength_NoLensKeyInMetadata_942) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  value->read("0 200 300 400");
  
  ExifData metadata;
  // Don't add Exif.CanonCs.Lens
  
  CanonMakerNote::printFocalLength(os, *value, &metadata);
  
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test: When Exif.CanonCs.Lens exists but has fewer than 3 values
TEST_F(CanonMakerNoteTest_942, PrintFocalLength_LensKeyTooFewValues_942) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  value->read("0 200 300 400");
  
  ExifData metadata;
  ExifKey lensKey("Exif.CanonCs.Lens");
  auto lensValue = Value::create(unsignedShort);
  lensValue->read("100 200");  // Only 2 values, need at least 3
  metadata.add(lensKey, lensValue.get());
  
  CanonMakerNote::printFocalLength(os, *value, &metadata);
  
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test: When Exif.CanonCs.Lens exists with 3+ values and fu != 0, should compute focal length
TEST_F(CanonMakerNoteTest_942, PrintFocalLength_ValidComputation_942) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  value->read("0 100 0 0");  // value[1] = 100 (focal length numerator)
  
  ExifData metadata;
  ExifKey lensKey("Exif.CanonCs.Lens");
  auto lensValue = Value::create(unsignedShort);
  lensValue->read("200 100 2");  // lensValue[2] = 2 (focal unit)
  metadata.add(lensKey, lensValue.get());
  
  CanonMakerNote::printFocalLength(os, *value, &metadata);
  
  std::string result = os.str();
  // 100 / 2 = 50.0 mm
  EXPECT_NE(result.find("50.0"), std::string::npos);
  EXPECT_NE(result.find("mm"), std::string::npos);
}

// Test: When fu (focal unit) is 0, should fall through to print raw value
TEST_F(CanonMakerNoteTest_942, PrintFocalLength_FocalUnitZero_942) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  value->read("0 100 0 0");
  
  ExifData metadata;
  ExifKey lensKey("Exif.CanonCs.Lens");
  auto lensValue = Value::create(unsignedShort);
  lensValue->read("200 100 0");  // lensValue[2] = 0 (focal unit is zero)
  metadata.add(lensKey, lensValue.get());
  
  CanonMakerNote::printFocalLength(os, *value, &metadata);
  
  std::string result = os.str();
  // Should not contain "mm" since fu == 0, falls through to raw value
  EXPECT_EQ(result.find("mm"), std::string::npos);
}

// Test: Focal length calculation with fu = 1 (identity)
TEST_F(CanonMakerNoteTest_942, PrintFocalLength_FocalUnitOne_942) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  value->read("0 50 0 0");  // value[1] = 50
  
  ExifData metadata;
  ExifKey lensKey("Exif.CanonCs.Lens");
  auto lensValue = Value::create(unsignedShort);
  lensValue->read("200 100 1");  // fu = 1
  metadata.add(lensKey, lensValue.get());
  
  CanonMakerNote::printFocalLength(os, *value, &metadata);
  
  std::string result = os.str();
  // 50 / 1 = 50.0 mm
  EXPECT_NE(result.find("50.0"), std::string::npos);
  EXPECT_NE(result.find("mm"), std::string::npos);
}

// Test: When Exif.CanonCs.Lens type is not unsignedShort
TEST_F(CanonMakerNoteTest_942, PrintFocalLength_LensWrongType_942) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  value->read("0 100 0 0");
  
  ExifData metadata;
  ExifKey lensKey("Exif.CanonCs.Lens");
  auto lensValue = Value::create(unsignedLong);
  lensValue->read("200 100 2");
  metadata.add(lensKey, lensValue.get());
  
  CanonMakerNote::printFocalLength(os, *value, &metadata);
  
  std::string result = os.str();
  // Should not compute focal length since lens value type is wrong
  EXPECT_EQ(result.find("mm"), std::string::npos);
}

// Test: Value with exactly 4 elements (boundary for count >= 4)
TEST_F(CanonMakerNoteTest_942, PrintFocalLength_ExactlyFourValues_942) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  value->read("1 200 3 4");  // Exactly 4 values
  
  ExifData metadata;
  ExifKey lensKey("Exif.CanonCs.Lens");
  auto lensValue = Value::create(unsignedShort);
  lensValue->read("300 150 4");  // fu = 4
  metadata.add(lensKey, lensValue.get());
  
  CanonMakerNote::printFocalLength(os, *value, &metadata);
  
  std::string result = os.str();
  // 200 / 4 = 50.0 mm
  EXPECT_NE(result.find("50.0"), std::string::npos);
  EXPECT_NE(result.find("mm"), std::string::npos);
}

// Test: Empty value (count = 0)
TEST_F(CanonMakerNoteTest_942, PrintFocalLength_EmptyValue_942) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  // Don't read any data, count should be 0
  
  ExifData metadata;
  CanonMakerNote::printFocalLength(os, *value, &metadata);
  
  // Should just print the value since count < 4
  std::string result = os.str();
  // Result might be empty string representation of empty value, but shouldn't crash
}

// Test: Lens value with exactly 3 elements (boundary for count >= 3)
TEST_F(CanonMakerNoteTest_942, PrintFocalLength_LensExactlyThreeValues_942) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  value->read("0 300 0 0");
  
  ExifData metadata;
  ExifKey lensKey("Exif.CanonCs.Lens");
  auto lensValue = Value::create(unsignedShort);
  lensValue->read("200 100 3");  // Exactly 3 values, fu = 3
  metadata.add(lensKey, lensValue.get());
  
  CanonMakerNote::printFocalLength(os, *value, &metadata);
  
  std::string result = os.str();
  // 300 / 3 = 100.0 mm
  EXPECT_NE(result.find("100.0"), std::string::npos);
  EXPECT_NE(result.find("mm"), std::string::npos);
}

// Test: Return value is reference to the same ostream
TEST_F(CanonMakerNoteTest_942, PrintFocalLength_ReturnsOstream_942) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  value->read("0 100 0 0");
  
  std::ostream& result = CanonMakerNote::printFocalLength(os, *value, nullptr);
  
  EXPECT_EQ(&result, &os);
}

// Test: Large focal length value
TEST_F(CanonMakerNoteTest_942, PrintFocalLength_LargeFocalLength_942) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  value->read("0 10000 0 0");  // value[1] = 10000
  
  ExifData metadata;
  ExifKey lensKey("Exif.CanonCs.Lens");
  auto lensValue = Value::create(unsignedShort);
  lensValue->read("200 100 1");  // fu = 1
  metadata.add(lensKey, lensValue.get());
  
  CanonMakerNote::printFocalLength(os, *value, &metadata);
  
  std::string result = os.str();
  // 10000 / 1 = 10000.0 mm
  EXPECT_NE(result.find("10000.0"), std::string::npos);
  EXPECT_NE(result.find("mm"), std::string::npos);
}
