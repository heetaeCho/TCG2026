#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Internal header for the function under test
#include "minoltamn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class PrintMinoltaSonyTeleconverterModelTest_1036 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test: Value 0 should print "None"
TEST_F(PrintMinoltaSonyTeleconverterModelTest_1036, ValueZero_PrintsNone_1036) {
    Value::UniquePtr value = Value::create(unsignedLong);
    value->read("0");
    printMinoltaSonyTeleconverterModel(os, *value, nullptr);
    EXPECT_EQ(os.str(), "None");
}

// Test: Value 4 should print the corresponding teleconverter model
TEST_F(PrintMinoltaSonyTeleconverterModelTest_1036, Value4_PrintsAF14xAPO_D_04_1036) {
    Value::UniquePtr value = Value::create(unsignedLong);
    value->read("4");
    printMinoltaSonyTeleconverterModel(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Minolta/Sony AF 1.4x APO (D) (0x04)");
}

// Test: Value 5 should print "Minolta/Sony AF 2x APO (D) (0x05)"
TEST_F(PrintMinoltaSonyTeleconverterModelTest_1036, Value5_PrintsAF2xAPO_D_05_1036) {
    Value::UniquePtr value = Value::create(unsignedLong);
    value->read("5");
    printMinoltaSonyTeleconverterModel(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Minolta/Sony AF 2x APO (D) (0x05)");
}

// Test: Value 72 should print "Minolta/Sony AF 2x APO (D)"
TEST_F(PrintMinoltaSonyTeleconverterModelTest_1036, Value72_PrintsAF2xAPO_D_1036) {
    Value::UniquePtr value = Value::create(unsignedLong);
    value->read("72");
    printMinoltaSonyTeleconverterModel(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Minolta/Sony AF 2x APO (D)");
}

// Test: Value 80 should print "Minolta AF 2x APO II"
TEST_F(PrintMinoltaSonyTeleconverterModelTest_1036, Value80_PrintsAF2xAPOII_1036) {
    Value::UniquePtr value = Value::create(unsignedLong);
    value->read("80");
    printMinoltaSonyTeleconverterModel(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Minolta AF 2x APO II");
}

// Test: Value 96 should print "Minolta AF 2x APO"
TEST_F(PrintMinoltaSonyTeleconverterModelTest_1036, Value96_PrintsAF2xAPO_1036) {
    Value::UniquePtr value = Value::create(unsignedLong);
    value->read("96");
    printMinoltaSonyTeleconverterModel(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Minolta AF 2x APO");
}

// Test: Value 136 should print "Minolta/Sony AF 1.4x APO (D)"
TEST_F(PrintMinoltaSonyTeleconverterModelTest_1036, Value136_PrintsAF14xAPO_D_1036) {
    Value::UniquePtr value = Value::create(unsignedLong);
    value->read("136");
    printMinoltaSonyTeleconverterModel(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Minolta/Sony AF 1.4x APO (D)");
}

// Test: Value 144 should print "Minolta AF 1.4x APO II"
TEST_F(PrintMinoltaSonyTeleconverterModelTest_1036, Value144_PrintsAF14xAPOII_1036) {
    Value::UniquePtr value = Value::create(unsignedLong);
    value->read("144");
    printMinoltaSonyTeleconverterModel(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Minolta AF 1.4x APO II");
}

// Test: Value 160 should print "Minolta AF 1.4x APO"
TEST_F(PrintMinoltaSonyTeleconverterModelTest_1036, Value160_PrintsAF14xAPO_1036) {
    Value::UniquePtr value = Value::create(unsignedLong);
    value->read("160");
    printMinoltaSonyTeleconverterModel(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Minolta AF 1.4x APO");
}

// Test: Unknown value (not in the table) should print the numeric value or "(n)"
TEST_F(PrintMinoltaSonyTeleconverterModelTest_1036, UnknownValue1_PrintsUnknown_1036) {
    Value::UniquePtr value = Value::create(unsignedLong);
    value->read("1");
    printMinoltaSonyTeleconverterModel(os, *value, nullptr);
    std::string result = os.str();
    // Unknown values typically print "(1)" or just "1"
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "None");
}

// Test: Unknown value 999 should not match any known tag
TEST_F(PrintMinoltaSonyTeleconverterModelTest_1036, UnknownValue999_PrintsUnknown_1036) {
    Value::UniquePtr value = Value::create(unsignedLong);
    value->read("999");
    printMinoltaSonyTeleconverterModel(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    // Should not match any of the known model strings
    EXPECT_TRUE(result.find("Minolta") == std::string::npos);
    EXPECT_NE(result, "None");
}

// Test: Function returns the same ostream reference
TEST_F(PrintMinoltaSonyTeleconverterModelTest_1036, ReturnsOstreamReference_1036) {
    Value::UniquePtr value = Value::create(unsignedLong);
    value->read("0");
    std::ostream& returned = printMinoltaSonyTeleconverterModel(os, *value, nullptr);
    EXPECT_EQ(&returned, &os);
}

// Test: With ExifData passed as metadata (non-null)
TEST_F(PrintMinoltaSonyTeleconverterModelTest_1036, WithExifDataMetadata_1036) {
    ExifData exifData;
    Value::UniquePtr value = Value::create(unsignedLong);
    value->read("4");
    printMinoltaSonyTeleconverterModel(os, *value, &exifData);
    EXPECT_EQ(os.str(), "Minolta/Sony AF 1.4x APO (D) (0x04)");
}

// Test: Boundary - value just below a known tag (71, before 72)
TEST_F(PrintMinoltaSonyTeleconverterModelTest_1036, BoundaryValue71_1036) {
    Value::UniquePtr value = Value::create(unsignedLong);
    value->read("71");
    printMinoltaSonyTeleconverterModel(os, *value, nullptr);
    std::string result = os.str();
    // 71 is not a known value, should not match "Minolta/Sony AF 2x APO (D)"
    EXPECT_NE(result, "Minolta/Sony AF 2x APO (D)");
}

// Test: Boundary - value just above a known tag (73, after 72)
TEST_F(PrintMinoltaSonyTeleconverterModelTest_1036, BoundaryValue73_1036) {
    Value::UniquePtr value = Value::create(unsignedLong);
    value->read("73");
    printMinoltaSonyTeleconverterModel(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result, "Minolta/Sony AF 2x APO (D)");
}

// Test: Using unsignedShort type value
TEST_F(PrintMinoltaSonyTeleconverterModelTest_1036, UnsignedShortValue_1036) {
    Value::UniquePtr value = Value::create(unsignedShort);
    value->read("0");
    printMinoltaSonyTeleconverterModel(os, *value, nullptr);
    EXPECT_EQ(os.str(), "None");
}

// Test: Large unknown value
TEST_F(PrintMinoltaSonyTeleconverterModelTest_1036, LargeUnknownValue_1036) {
    Value::UniquePtr value = Value::create(unsignedLong);
    value->read("65535");
    printMinoltaSonyTeleconverterModel(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    // Should not match any known model
    EXPECT_TRUE(result.find("Minolta") == std::string::npos);
    EXPECT_NE(result, "None");
}
