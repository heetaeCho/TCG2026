#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/easyaccess.hpp>

using namespace Exiv2;

class IsoSpeedTest_511 : public ::testing::Test {
protected:
    ExifData ed;
};

// Test: Empty ExifData returns end iterator
TEST_F(IsoSpeedTest_511, EmptyExifDataReturnsEnd_511) {
    auto result = isoSpeed(ed);
    EXPECT_EQ(result, ed.end());
}

// Test: Standard ISOSpeedRatings key is found
TEST_F(IsoSpeedTest_511, StandardISOSpeedRatingsFound_511) {
    ed["Exif.Photo.ISOSpeedRatings"] = uint16_t(200);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.Photo.ISOSpeedRatings");
}

// Test: Image ISOSpeedRatings key is found when Photo is absent
TEST_F(IsoSpeedTest_511, ImageISOSpeedRatingsFound_511) {
    ed["Exif.Image.ISOSpeedRatings"] = uint16_t(400);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.Image.ISOSpeedRatings");
}

// Test: Canon ISOSpeed key is found
TEST_F(IsoSpeedTest_511, CanonSiISOSpeedFound_511) {
    ed["Exif.CanonSi.ISOSpeed"] = uint16_t(800);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.CanonSi.ISOSpeed");
}

// Test: CanonCs ISOSpeed key is found
TEST_F(IsoSpeedTest_511, CanonCsISOSpeedFound_511) {
    ed["Exif.CanonCs.ISOSpeed"] = uint16_t(1600);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.CanonCs.ISOSpeed");
}

// Test: Nikon1 ISOSpeed key is found
TEST_F(IsoSpeedTest_511, Nikon1ISOSpeedFound_511) {
    ed["Exif.Nikon1.ISOSpeed"] = uint16_t(100);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.Nikon1.ISOSpeed");
}

// Test: Nikon2 ISOSpeed key is found
TEST_F(IsoSpeedTest_511, Nikon2ISOSpeedFound_511) {
    ed["Exif.Nikon2.ISOSpeed"] = uint16_t(100);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.Nikon2.ISOSpeed");
}

// Test: Nikon3 ISOSettings key is found
TEST_F(IsoSpeedTest_511, Nikon3ISOSettingsFound_511) {
    ed["Exif.Nikon3.ISOSettings"] = uint16_t(320);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.Nikon3.ISOSettings");
}

// Test: Nikon3 ISOSpeed key is found
TEST_F(IsoSpeedTest_511, Nikon3ISOSpeedFound_511) {
    ed["Exif.Nikon3.ISOSpeed"] = uint16_t(640);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.Nikon3.ISOSpeed");
}

// Test: NikonIi ISO key is found
TEST_F(IsoSpeedTest_511, NikonIiISOFound_511) {
    ed["Exif.NikonIi.ISO"] = uint16_t(500);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.NikonIi.ISO");
}

// Test: Pentax ISO key is found
TEST_F(IsoSpeedTest_511, PentaxISOFound_511) {
    ed["Exif.Pentax.ISO"] = uint16_t(200);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.Pentax.ISO");
}

// Test: PentaxDng ISO key is found
TEST_F(IsoSpeedTest_511, PentaxDngISOFound_511) {
    ed["Exif.PentaxDng.ISO"] = uint16_t(200);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.PentaxDng.ISO");
}

// Test: Olympus ISOSpeed key is found
TEST_F(IsoSpeedTest_511, OlympusISOSpeedFound_511) {
    ed["Exif.Olympus.ISOSpeed"] = uint16_t(1600);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.Olympus.ISOSpeed");
}

// Test: Samsung2 ISO key is found
TEST_F(IsoSpeedTest_511, Samsung2ISOFound_511) {
    ed["Exif.Samsung2.ISO"] = uint16_t(100);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.Samsung2.ISO");
}

// Test: Casio ISO key is found
TEST_F(IsoSpeedTest_511, CasioISOFound_511) {
    ed["Exif.Casio.ISO"] = uint16_t(200);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.Casio.ISO");
}

// Test: Casio2 ISO key is found
TEST_F(IsoSpeedTest_511, Casio2ISOFound_511) {
    ed["Exif.Casio2.ISO"] = uint16_t(400);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.Casio2.ISO");
}

// Test: Casio2 ISOSpeed key is found
TEST_F(IsoSpeedTest_511, Casio2ISOSpeedFound_511) {
    ed["Exif.Casio2.ISOSpeed"] = uint16_t(800);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.Casio2.ISOSpeed");
}

// Test: Priority order - Photo.ISOSpeedRatings takes precedence over Image.ISOSpeedRatings
TEST_F(IsoSpeedTest_511, PhotoISOSpeedRatingsTakesPrecedence_511) {
    ed["Exif.Photo.ISOSpeedRatings"] = uint16_t(100);
    ed["Exif.Image.ISOSpeedRatings"] = uint16_t(200);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.Photo.ISOSpeedRatings");
}

// Test: ISO value of 0 should be skipped
TEST_F(IsoSpeedTest_511, ZeroISOValueSkipped_511) {
    ed["Exif.Photo.ISOSpeedRatings"] = uint16_t(0);
    ed["Exif.Image.ISOSpeedRatings"] = uint16_t(400);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.Image.ISOSpeedRatings");
}

// Test: SensitivityType fallback when ISO is 65535
TEST_F(IsoSpeedTest_511, SensitivityTypeFallbackForISO65535_511) {
    ed["Exif.Photo.ISOSpeedRatings"] = uint16_t(65535);
    ed["Exif.Photo.SensitivityType"] = uint16_t(3);  // ISOSpeed
    ed["Exif.Photo.ISOSpeed"] = uint32_t(102400);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.Photo.ISOSpeed");
}

// Test: SensitivityType = 1 -> StandardOutputSensitivity
TEST_F(IsoSpeedTest_511, SensitivityType1StandardOutputSensitivity_511) {
    ed["Exif.Photo.ISOSpeedRatings"] = uint16_t(65535);
    ed["Exif.Photo.SensitivityType"] = uint16_t(1);
    ed["Exif.Photo.StandardOutputSensitivity"] = uint32_t(51200);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.Photo.StandardOutputSensitivity");
}

// Test: SensitivityType = 2 -> RecommendedExposureIndex
TEST_F(IsoSpeedTest_511, SensitivityType2RecommendedExposureIndex_511) {
    ed["Exif.Photo.ISOSpeedRatings"] = uint16_t(65535);
    ed["Exif.Photo.SensitivityType"] = uint16_t(2);
    ed["Exif.Photo.RecommendedExposureIndex"] = uint32_t(25600);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.Photo.RecommendedExposureIndex");
}

// Test: SensitivityType = 3 -> ISOSpeed
TEST_F(IsoSpeedTest_511, SensitivityType3ISOSpeed_511) {
    ed["Exif.Photo.ISOSpeedRatings"] = uint16_t(65535);
    ed["Exif.Photo.SensitivityType"] = uint16_t(3);
    ed["Exif.Photo.ISOSpeed"] = uint32_t(12800);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.Photo.ISOSpeed");
}

// Test: SensitivityType out of range (0) - no fallback
TEST_F(IsoSpeedTest_511, SensitivityTypeZeroNoFallback_511) {
    ed["Exif.Photo.ISOSpeedRatings"] = uint16_t(65535);
    ed["Exif.Photo.SensitivityType"] = uint16_t(0);
    ed["Exif.Photo.ISOSpeed"] = uint32_t(12800);
    auto result = isoSpeed(ed);
    // SensitivityType 0 is out of range, so it should return the original match (65535 match)
    // or end(). The original ISOSpeedRatings with value 65535 was found, and the fallback
    // didn't produce a valid replacement.
    if (result != ed.end()) {
        EXPECT_EQ(result->key(), "Exif.Photo.ISOSpeedRatings");
    }
}

// Test: SensitivityType out of range (8) - no fallback
TEST_F(IsoSpeedTest_511, SensitivityType8NoFallback_511) {
    ed["Exif.Photo.ISOSpeedRatings"] = uint16_t(65535);
    ed["Exif.Photo.SensitivityType"] = uint16_t(8);
    ed["Exif.Photo.ISOSpeed"] = uint32_t(12800);
    auto result = isoSpeed(ed);
    // SensitivityType 8 is out of range
    if (result != ed.end()) {
        EXPECT_EQ(result->key(), "Exif.Photo.ISOSpeedRatings");
    }
}

// Test: No matching keys and no sensitivity type returns end
TEST_F(IsoSpeedTest_511, NoMatchingKeysReturnsEnd_511) {
    ed["Exif.Photo.ExposureTime"] = std::string("1/125");
    auto result = isoSpeed(ed);
    EXPECT_EQ(result, ed.end());
}

// Test: SensitivityType = 7 with all three keys
TEST_F(IsoSpeedTest_511, SensitivityType7AllThreeKeys_511) {
    ed["Exif.Photo.ISOSpeedRatings"] = uint16_t(65535);
    ed["Exif.Photo.SensitivityType"] = uint16_t(7);
    ed["Exif.Photo.ISOSpeed"] = uint32_t(204800);
    ed["Exif.Photo.RecommendedExposureIndex"] = uint32_t(204800);
    ed["Exif.Photo.StandardOutputSensitivity"] = uint32_t(204800);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    // SensitivityType 7 checks ISOSpeed first
    EXPECT_EQ(result->key(), "Exif.Photo.ISOSpeed");
}

// Test: When no standard keys found, SensitivityType alone triggers lookup
TEST_F(IsoSpeedTest_511, NoStandardKeysButSensitivityTypePresent_511) {
    ed["Exif.Photo.SensitivityType"] = uint16_t(3);
    ed["Exif.Photo.ISOSpeed"] = uint32_t(3200);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.Photo.ISOSpeed");
}

// Test: MinoltaCsNew ISOSetting key is found
TEST_F(IsoSpeedTest_511, MinoltaCsNewISOSettingFound_511) {
    ed["Exif.MinoltaCsNew.ISOSetting"] = uint16_t(100);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.MinoltaCsNew.ISOSetting");
}

// Test: MinoltaCsOld ISOSetting key is found
TEST_F(IsoSpeedTest_511, MinoltaCsOldISOSettingFound_511) {
    ed["Exif.MinoltaCsOld.ISOSetting"] = uint16_t(200);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.MinoltaCsOld.ISOSetting");
}

// Test: MinoltaCs5D ISOSpeed key is found
TEST_F(IsoSpeedTest_511, MinoltaCs5DISOSpeedFound_511) {
    ed["Exif.MinoltaCs5D.ISOSpeed"] = uint16_t(400);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.MinoltaCs5D.ISOSpeed");
}

// Test: MinoltaCs7D ISOSpeed key is found
TEST_F(IsoSpeedTest_511, MinoltaCs7DISOSpeedFound_511) {
    ed["Exif.MinoltaCs7D.ISOSpeed"] = uint16_t(800);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.MinoltaCs7D.ISOSpeed");
}

// Test: Sony1Cs ISOSetting key is found
TEST_F(IsoSpeedTest_511, Sony1CsISOSettingFound_511) {
    ed["Exif.Sony1Cs.ISOSetting"] = uint16_t(3200);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.Sony1Cs.ISOSetting");
}

// Test: Sony2Cs ISOSetting key is found
TEST_F(IsoSpeedTest_511, Sony2CsISOSettingFound_511) {
    ed["Exif.Sony2Cs.ISOSetting"] = uint16_t(6400);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.Sony2Cs.ISOSetting");
}

// Test: SensitivityType = 4 -> REI and SOS
TEST_F(IsoSpeedTest_511, SensitivityType4REIAndSOS_511) {
    ed["Exif.Photo.ISOSpeedRatings"] = uint16_t(65535);
    ed["Exif.Photo.SensitivityType"] = uint16_t(4);
    ed["Exif.Photo.RecommendedExposureIndex"] = uint32_t(51200);
    ed["Exif.Photo.StandardOutputSensitivity"] = uint32_t(51200);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    // Type 4: REI, SOS - should find REI first
    EXPECT_EQ(result->key(), "Exif.Photo.RecommendedExposureIndex");
}

// Test: SensitivityType = 5 -> ISOSpeed and SOS
TEST_F(IsoSpeedTest_511, SensitivityType5ISOSpeedAndSOS_511) {
    ed["Exif.Photo.ISOSpeedRatings"] = uint16_t(65535);
    ed["Exif.Photo.SensitivityType"] = uint16_t(5);
    ed["Exif.Photo.ISOSpeed"] = uint32_t(25600);
    ed["Exif.Photo.StandardOutputSensitivity"] = uint32_t(25600);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.Photo.ISOSpeed");
}

// Test: SensitivityType = 6 -> ISOSpeed and REI
TEST_F(IsoSpeedTest_511, SensitivityType6ISOSpeedAndREI_511) {
    ed["Exif.Photo.ISOSpeedRatings"] = uint16_t(65535);
    ed["Exif.Photo.SensitivityType"] = uint16_t(6);
    ed["Exif.Photo.ISOSpeed"] = uint32_t(12800);
    ed["Exif.Photo.RecommendedExposureIndex"] = uint32_t(12800);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.Photo.ISOSpeed");
}

// Test: Valid ISO value (not 65535) does not trigger sensitivity type fallback
TEST_F(IsoSpeedTest_511, ValidISODoesNotTriggerFallback_511) {
    ed["Exif.Photo.ISOSpeedRatings"] = uint16_t(400);
    ed["Exif.Photo.SensitivityType"] = uint16_t(3);
    ed["Exif.Photo.ISOSpeed"] = uint32_t(102400);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.Photo.ISOSpeedRatings");
}

// Test: NikonSiD300a ISO key
TEST_F(IsoSpeedTest_511, NikonSiD300aISOFound_511) {
    ed["Exif.NikonSiD300a.ISO"] = uint16_t(1600);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.NikonSiD300a.ISO");
}

// Test: NikonIi ISO2 key
TEST_F(IsoSpeedTest_511, NikonIiISO2Found_511) {
    ed["Exif.NikonIi.ISO2"] = uint16_t(3200);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.NikonIi.ISO2");
}

// Test: Sony1Cs2 ISOSetting key
TEST_F(IsoSpeedTest_511, Sony1Cs2ISOSettingFound_511) {
    ed["Exif.Sony1Cs2.ISOSetting"] = uint16_t(800);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.Sony1Cs2.ISOSetting");
}

// Test: Sony2Cs2 ISOSetting key
TEST_F(IsoSpeedTest_511, Sony2Cs2ISOSettingFound_511) {
    ed["Exif.Sony2Cs2.ISOSetting"] = uint16_t(1600);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.Sony2Cs2.ISOSetting");
}

// Test: Sony1MltCsA100 ISOSetting key
TEST_F(IsoSpeedTest_511, Sony1MltCsA100ISOSettingFound_511) {
    ed["Exif.Sony1MltCsA100.ISOSetting"] = uint16_t(400);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.Sony1MltCsA100.ISOSetting");
}

// Test: SensitivityType present but corresponding sens key missing
TEST_F(IsoSpeedTest_511, SensitivityTypePresentButSensKeyMissing_511) {
    ed["Exif.Photo.SensitivityType"] = uint16_t(3);  // expects ISOSpeed
    // But Exif.Photo.ISOSpeed is NOT present
    auto result = isoSpeed(ed);
    EXPECT_EQ(result, ed.end());
}

// Test: Multiple ISO keys present - first valid one in priority order wins
TEST_F(IsoSpeedTest_511, MultipleKeysFirstValidWins_511) {
    ed["Exif.CanonSi.ISOSpeed"] = uint16_t(800);
    ed["Exif.Nikon1.ISOSpeed"] = uint16_t(400);
    ed["Exif.Pentax.ISO"] = uint16_t(200);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.CanonSi.ISOSpeed");
}

// Test: ISO value of 1 (minimum positive) is valid
TEST_F(IsoSpeedTest_511, ISOValueOneIsValid_511) {
    ed["Exif.Photo.ISOSpeedRatings"] = uint16_t(1);
    auto result = isoSpeed(ed);
    ASSERT_NE(result, ed.end());
    EXPECT_EQ(result->key(), "Exif.Photo.ISOSpeedRatings");
}
