#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class PrintFlashMasterDataFl7Test_490 : public ::testing::Test {
protected:
  std::ostringstream os;
};

// Test: null metadata pointer should output "(value)"
TEST_F(PrintFlashMasterDataFl7Test_490, NullMetadata_490) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  
  Nikon3MakerNote::printFlashMasterDataFl7(os, *value, nullptr);
  
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: value count != 1 should output "(value)"
TEST_F(PrintFlashMasterDataFl7Test_490, ValueCountNotOne_490) {
  auto value = Value::create(unsignedByte);
  value->read("0 1");  // two values
  
  ExifData metadata;
  
  Nikon3MakerNote::printFlashMasterDataFl7(os, *value, &metadata);
  
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: value typeId != unsignedByte should output "(value)"
TEST_F(PrintFlashMasterDataFl7Test_490, WrongTypeId_490) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  
  ExifData metadata;
  
  Nikon3MakerNote::printFlashMasterDataFl7(os, *value, &metadata);
  
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: ExternalFlashData2 key not found in metadata should output "(value)"
TEST_F(PrintFlashMasterDataFl7Test_490, ExternalFlashData2NotFound_490) {
  auto value = Value::create(unsignedByte);
  value->read("10");
  
  ExifData metadata;
  // Don't add ExternalFlashData2 key
  
  Nikon3MakerNote::printFlashMasterDataFl7(os, *value, &metadata);
  
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: ExternalFlashData2 exists but with wrong type should output "(value)"
TEST_F(PrintFlashMasterDataFl7Test_490, ExternalFlashData2WrongType_490) {
  auto value = Value::create(unsignedByte);
  value->read("10");
  
  ExifData metadata;
  // Add ExternalFlashData2 with wrong type (unsignedShort instead of unsignedByte)
  auto flashValue = Value::create(unsignedShort);
  flashValue->read("5");
  metadata.add(ExifKey("Exif.NikonFl7.ExternalFlashData2"), flashValue.get());
  
  Nikon3MakerNote::printFlashMasterDataFl7(os, *value, &metadata);
  
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: ExternalFlashData2 exists but with count != 1 should output "(value)"
TEST_F(PrintFlashMasterDataFl7Test_490, ExternalFlashData2CountNotOne_490) {
  auto value = Value::create(unsignedByte);
  value->read("10");
  
  ExifData metadata;
  auto flashValue = Value::create(unsignedByte);
  flashValue->read("5 6");  // count == 2
  metadata.add(ExifKey("Exif.NikonFl7.ExternalFlashData2"), flashValue.get());
  
  Nikon3MakerNote::printFlashMasterDataFl7(os, *value, &metadata);
  
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: ExternalFlashData2 mode (lower nibble) == 0 should output "n/a"
TEST_F(PrintFlashMasterDataFl7Test_490, ModeZeroReturnsNA_490) {
  auto value = Value::create(unsignedByte);
  value->read("10");
  
  ExifData metadata;
  // Lower nibble is 0 (0x00 & 0x0F == 0)
  auto flashValue = Value::create(unsignedByte);
  flashValue->read("0");
  metadata.add(ExifKey("Exif.NikonFl7.ExternalFlashData2"), flashValue.get());
  
  Nikon3MakerNote::printFlashMasterDataFl7(os, *value, &metadata);
  
  std::string result = os.str();
  EXPECT_TRUE(result.find("n/a") != std::string::npos);
}

// Test: ExternalFlashData2 mode (lower nibble) == 0 with upper nibble set should still output "n/a"
TEST_F(PrintFlashMasterDataFl7Test_490, ModeZeroWithUpperNibbleReturnsNA_490) {
  auto value = Value::create(unsignedByte);
  value->read("10");
  
  ExifData metadata;
  // 0xF0 & 0x0F == 0, so mode == 0
  auto flashValue = Value::create(unsignedByte);
  flashValue->read("240");  // 0xF0
  metadata.add(ExifKey("Exif.NikonFl7.ExternalFlashData2"), flashValue.get());
  
  Nikon3MakerNote::printFlashMasterDataFl7(os, *value, &metadata);
  
  std::string result = os.str();
  EXPECT_TRUE(result.find("n/a") != std::string::npos);
}

// Test: ExternalFlashData2 mode != 0 should print flash compensation value (non-"n/a" output)
TEST_F(PrintFlashMasterDataFl7Test_490, ModeNonZeroPrintsFlashCompensation_490) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  
  ExifData metadata;
  // Lower nibble is 1 (mode != 0), so it should call printFlashCompensationValue
  auto flashValue = Value::create(unsignedByte);
  flashValue->read("1");
  metadata.add(ExifKey("Exif.NikonFl7.ExternalFlashData2"), flashValue.get());
  
  Nikon3MakerNote::printFlashMasterDataFl7(os, *value, &metadata);
  
  std::string result = os.str();
  // Should not contain "n/a" nor be wrapped in parentheses
  EXPECT_TRUE(result.find("n/a") == std::string::npos);
  // The output should not be empty
  EXPECT_FALSE(result.empty());
}

// Test: ExternalFlashData2 mode = 3 with value = 0 (flash compensation)
TEST_F(PrintFlashMasterDataFl7Test_490, ModeThreeWithValueZero_490) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  
  ExifData metadata;
  auto flashValue = Value::create(unsignedByte);
  flashValue->read("3");  // mode = 3
  metadata.add(ExifKey("Exif.NikonFl7.ExternalFlashData2"), flashValue.get());
  
  Nikon3MakerNote::printFlashMasterDataFl7(os, *value, &metadata);
  
  std::string result = os.str();
  EXPECT_TRUE(result.find("n/a") == std::string::npos);
  EXPECT_FALSE(result.empty());
}

// Test: returns reference to the same ostream
TEST_F(PrintFlashMasterDataFl7Test_490, ReturnsOstreamReference_490) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  
  std::ostream& ret = Nikon3MakerNote::printFlashMasterDataFl7(os, *value, nullptr);
  
  EXPECT_EQ(&ret, &os);
}

// Test: returns reference to the same ostream when mode is zero (n/a path)
TEST_F(PrintFlashMasterDataFl7Test_490, ReturnsOstreamReferenceNA_490) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  
  ExifData metadata;
  auto flashValue = Value::create(unsignedByte);
  flashValue->read("0");  // mode = 0
  metadata.add(ExifKey("Exif.NikonFl7.ExternalFlashData2"), flashValue.get());
  
  std::ostream& ret = Nikon3MakerNote::printFlashMasterDataFl7(os, *value, &metadata);
  
  EXPECT_EQ(&ret, &os);
}

// Test: returns reference to the same ostream when mode is non-zero (compensation path)
TEST_F(PrintFlashMasterDataFl7Test_490, ReturnsOstreamReferenceCompensation_490) {
  auto value = Value::create(unsignedByte);
  value->read("6");
  
  ExifData metadata;
  auto flashValue = Value::create(unsignedByte);
  flashValue->read("2");  // mode = 2
  metadata.add(ExifKey("Exif.NikonFl7.ExternalFlashData2"), flashValue.get());
  
  std::ostream& ret = Nikon3MakerNote::printFlashMasterDataFl7(os, *value, &metadata);
  
  EXPECT_EQ(&ret, &os);
}

// Test: different mode values in lower nibble (0x01 through 0x0F)
TEST_F(PrintFlashMasterDataFl7Test_490, VariousNonZeroModes_490) {
  for (int mode = 1; mode <= 15; ++mode) {
    std::ostringstream localOs;
    auto value = Value::create(unsignedByte);
    value->read("12");
    
    ExifData metadata;
    auto flashValue = Value::create(unsignedByte);
    flashValue->read(std::to_string(mode));
    metadata.add(ExifKey("Exif.NikonFl7.ExternalFlashData2"), flashValue.get());
    
    Nikon3MakerNote::printFlashMasterDataFl7(localOs, *value, &metadata);
    
    std::string result = localOs.str();
    // For all non-zero modes, should not output "n/a"
    EXPECT_TRUE(result.find("n/a") == std::string::npos) 
        << "Failed for mode=" << mode << ", output=" << result;
    EXPECT_FALSE(result.empty()) << "Failed for mode=" << mode;
  }
}

// Test: value with unsignedByte type but representing boundary value 255
TEST_F(PrintFlashMasterDataFl7Test_490, BoundaryValue255_490) {
  auto value = Value::create(unsignedByte);
  value->read("255");
  
  ExifData metadata;
  auto flashValue = Value::create(unsignedByte);
  flashValue->read("1");  // mode = 1
  metadata.add(ExifKey("Exif.NikonFl7.ExternalFlashData2"), flashValue.get());
  
  Nikon3MakerNote::printFlashMasterDataFl7(os, *value, &metadata);
  
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
  EXPECT_TRUE(result.find("n/a") == std::string::npos);
}

// Test: value with unsignedByte type representing boundary value 0 with mode 0 -> n/a
TEST_F(PrintFlashMasterDataFl7Test_490, BoundaryValueZeroModeZero_490) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  
  ExifData metadata;
  auto flashValue = Value::create(unsignedByte);
  flashValue->read("16");  // 0x10 & 0x0F == 0, mode == 0
  metadata.add(ExifKey("Exif.NikonFl7.ExternalFlashData2"), flashValue.get());
  
  Nikon3MakerNote::printFlashMasterDataFl7(os, *value, &metadata);
  
  std::string result = os.str();
  EXPECT_TRUE(result.find("n/a") != std::string::npos);
}
