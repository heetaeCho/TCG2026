#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include "sonymn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMakerNoteTest_1619 : public ::testing::Test {
protected:
    std::ostringstream os;

    // Helper to set the model in ExifData
    void setModel(ExifData& metadata, const std::string& model) {
        metadata["Exif.Image.Model"] = model;
    }

    // Helper to create an unsignedLong value with a single entry
    std::unique_ptr<Value> makeUnsignedLongValue(uint32_t val) {
        auto v = Value::create(unsignedLong);
        v->read(std::to_string(val));
        return v;
    }

    // Helper to create an unsignedShort value with a single entry
    std::unique_ptr<Value> makeUnsignedShortValue(uint16_t val) {
        auto v = Value::create(unsignedShort);
        v->read(std::to_string(val));
        return v;
    }

    // Helper to create a signedLong value
    std::unique_ptr<Value> makeSignedLongValue(int32_t val) {
        auto v = Value::create(signedLong);
        v->read(std::to_string(val));
        return v;
    }
};

// Test: null metadata pointer should output value in parentheses
TEST_F(SonyMakerNoteTest_1619, ShotNumberSincePowerUp_NullMetadata_1619) {
    auto value = makeUnsignedLongValue(42);
    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result, "(42)");
}

// Test: wrong type (unsignedShort instead of unsignedLong) should output value in parentheses
TEST_F(SonyMakerNoteTest_1619, ShotNumberSincePowerUp_WrongType_1619) {
    auto value = makeUnsignedShortValue(42);
    ExifData metadata;
    setModel(metadata, "ILCE-7");
    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_EQ(result, "(42)");
}

// Test: known model ILCE-7 should output the numeric value directly
TEST_F(SonyMakerNoteTest_1619, ShotNumberSincePowerUp_KnownModel_ILCE7_1619) {
    auto value = makeUnsignedLongValue(100);
    ExifData metadata;
    setModel(metadata, "ILCE-7");
    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_EQ(result, "100");
}

// Test: known model DSC-RX100M3 should output numeric value
TEST_F(SonyMakerNoteTest_1619, ShotNumberSincePowerUp_KnownModel_DSCRX100M3_1619) {
    auto value = makeUnsignedLongValue(500);
    ExifData metadata;
    setModel(metadata, "DSC-RX100M3");
    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_EQ(result, "500");
}

// Test: known model ILCA-68 should output numeric value
TEST_F(SonyMakerNoteTest_1619, ShotNumberSincePowerUp_KnownModel_ILCA68_1619) {
    auto value = makeUnsignedLongValue(1);
    ExifData metadata;
    setModel(metadata, "ILCA-68");
    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_EQ(result, "1");
}

// Test: known model DSC-WX500 (last in the list) should output numeric value
TEST_F(SonyMakerNoteTest_1619, ShotNumberSincePowerUp_KnownModel_DSCWX500_1619) {
    auto value = makeUnsignedLongValue(999);
    ExifData metadata;
    setModel(metadata, "DSC-WX500");
    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_EQ(result, "999");
}

// Test: unknown model should output "n/a"
TEST_F(SonyMakerNoteTest_1619, ShotNumberSincePowerUp_UnknownModel_1619) {
    auto value = makeUnsignedLongValue(42);
    ExifData metadata;
    setModel(metadata, "ILCE-9");
    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, *value, &metadata);
    std::string result = os.str();
    // Should contain "n/a" (possibly translated)
    EXPECT_NE(result.find("n/a"), std::string::npos);
}

// Test: another unknown model
TEST_F(SonyMakerNoteTest_1619, ShotNumberSincePowerUp_UnknownModelCanon_1619) {
    auto value = makeUnsignedLongValue(42);
    ExifData metadata;
    setModel(metadata, "Canon EOS 5D");
    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_NE(result.find("n/a"), std::string::npos);
}

// Test: value of 0 with known model
TEST_F(SonyMakerNoteTest_1619, ShotNumberSincePowerUp_ZeroValue_KnownModel_1619) {
    auto value = makeUnsignedLongValue(0);
    ExifData metadata;
    setModel(metadata, "ILCE-7RM2");
    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_EQ(result, "0");
}

// Test: large value with known model
TEST_F(SonyMakerNoteTest_1619, ShotNumberSincePowerUp_LargeValue_KnownModel_1619) {
    auto value = makeUnsignedLongValue(4294967295u);
    ExifData metadata;
    setModel(metadata, "DSC-RX0");
    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, *value, &metadata);
    std::string result = os.str();
    // Should output the numeric value
    EXPECT_FALSE(result.empty());
    // Should not be in parentheses or n/a
    EXPECT_EQ(result.find("("), std::string::npos);
    EXPECT_EQ(result.find("n/a"), std::string::npos);
}

// Test: metadata without model key should output value in parentheses
TEST_F(SonyMakerNoteTest_1619, ShotNumberSincePowerUp_NoModelInMetadata_1619) {
    auto value = makeUnsignedLongValue(42);
    ExifData metadata;
    // Don't set model
    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_EQ(result, "(42)");
}

// Test: signedLong type instead of unsignedLong should output in parentheses
TEST_F(SonyMakerNoteTest_1619, ShotNumberSincePowerUp_SignedLongType_1619) {
    auto value = makeSignedLongValue(42);
    ExifData metadata;
    setModel(metadata, "ILCE-7");
    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_EQ(result, "(42)");
}

// Test: known model ILCE-7SM5 should output numeric value
TEST_F(SonyMakerNoteTest_1619, ShotNumberSincePowerUp_KnownModel_ILCE7SM5_1619) {
    auto value = makeUnsignedLongValue(77);
    ExifData metadata;
    setModel(metadata, "ILCE-7SM5");
    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_EQ(result, "77");
}

// Test: known model DSC-HX350
TEST_F(SonyMakerNoteTest_1619, ShotNumberSincePowerUp_KnownModel_DSCHX350_1619) {
    auto value = makeUnsignedLongValue(200);
    ExifData metadata;
    setModel(metadata, "DSC-HX350");
    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_EQ(result, "200");
}

// Test: known model ILCE-QX1
TEST_F(SonyMakerNoteTest_1619, ShotNumberSincePowerUp_KnownModel_ILCEQX1_1619) {
    auto value = makeUnsignedLongValue(10);
    ExifData metadata;
    setModel(metadata, "ILCE-QX1");
    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_EQ(result, "10");
}

// Test: known model DSC-RX1RM2
TEST_F(SonyMakerNoteTest_1619, ShotNumberSincePowerUp_KnownModel_DSCRX1RM2_1619) {
    auto value = makeUnsignedLongValue(55);
    ExifData metadata;
    setModel(metadata, "DSC-RX1RM2");
    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_EQ(result, "55");
}

// Test: known model DSC-QX30
TEST_F(SonyMakerNoteTest_1619, ShotNumberSincePowerUp_KnownModel_DSCQX30_1619) {
    auto value = makeUnsignedLongValue(300);
    ExifData metadata;
    setModel(metadata, "DSC-QX30");
    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_EQ(result, "300");
}

// Test: empty model string should trigger n/a or parenthesized output
TEST_F(SonyMakerNoteTest_1619, ShotNumberSincePowerUp_EmptyModel_1619) {
    auto value = makeUnsignedLongValue(42);
    ExifData metadata;
    setModel(metadata, "");
    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, *value, &metadata);
    std::string result = os.str();
    // Empty model is not in the known list, so should be n/a
    EXPECT_NE(result.find("n/a"), std::string::npos);
}

// Test: model with extra whitespace should not match
TEST_F(SonyMakerNoteTest_1619, ShotNumberSincePowerUp_ModelWithWhitespace_1619) {
    auto value = makeUnsignedLongValue(42);
    ExifData metadata;
    setModel(metadata, " ILCE-7 ");
    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, *value, &metadata);
    std::string result = os.str();
    // With extra whitespace, likely won't match
    EXPECT_NE(result.find("n/a"), std::string::npos);
}

// Test: all known models output numeric values (spot check a few more)
TEST_F(SonyMakerNoteTest_1619, ShotNumberSincePowerUp_KnownModel_ILCA99M2_1619) {
    auto value = makeUnsignedLongValue(123);
    ExifData metadata;
    setModel(metadata, "ILCA-99M2");
    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, *value, &metadata);
    EXPECT_EQ(os.str(), "123");
}

TEST_F(SonyMakerNoteTest_1619, ShotNumberSincePowerUp_KnownModel_ILCE6500_1619) {
    auto value = makeUnsignedLongValue(456);
    ExifData metadata;
    setModel(metadata, "ILCE-6500");
    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, *value, &metadata);
    EXPECT_EQ(os.str(), "456");
}

TEST_F(SonyMakerNoteTest_1619, ShotNumberSincePowerUp_KnownModel_DSCHX400V_1619) {
    auto value = makeUnsignedLongValue(789);
    ExifData metadata;
    setModel(metadata, "DSC-HX400V");
    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, *value, &metadata);
    EXPECT_EQ(os.str(), "789");
}

TEST_F(SonyMakerNoteTest_1619, ShotNumberSincePowerUp_KnownModel_DSCRX10M3_1619) {
    auto value = makeUnsignedLongValue(321);
    ExifData metadata;
    setModel(metadata, "DSC-RX10M3");
    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, *value, &metadata);
    EXPECT_EQ(os.str(), "321");
}

TEST_F(SonyMakerNoteTest_1619, ShotNumberSincePowerUp_KnownModel_DSCRX100M5_1619) {
    auto value = makeUnsignedLongValue(654);
    ExifData metadata;
    setModel(metadata, "DSC-RX100M5");
    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, *value, &metadata);
    EXPECT_EQ(os.str(), "654");
}

TEST_F(SonyMakerNoteTest_1619, ShotNumberSincePowerUp_KnownModel_DSCWX220_1619) {
    auto value = makeUnsignedLongValue(111);
    ExifData metadata;
    setModel(metadata, "DSC-WX220");
    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, *value, &metadata);
    EXPECT_EQ(os.str(), "111");
}
