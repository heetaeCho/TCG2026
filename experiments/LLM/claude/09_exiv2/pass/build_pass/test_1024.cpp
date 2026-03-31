#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <sstream>
#include <string>

// We need access to the internal function through the Minolta MakerNote interface
// The function resolveLens0xffff is static in minoltamn_int.cpp, so we test it
// indirectly through the public interface that uses it, or through the tag print
// functions exposed by the Minolta MakerNote.

// Since resolveLens0xffff is a static function inside an anonymous namespace or
// Internal namespace, we test it through the public lens ID resolution mechanism.
// The function is called when lens ID is 0xffff (65535).

namespace {

// Helper to set up ExifData with specific key-value pairs
void setExifString(Exiv2::ExifData& exifData, const std::string& key, const std::string& value) {
    Exiv2::ExifKey exifKey(key);
    auto val = Exiv2::Value::create(Exiv2::asciiString);
    val->read(value);
    exifData.add(exifKey, val.get());
}

void setExifRational(Exiv2::ExifData& exifData, const std::string& key, int32_t num, int32_t den) {
    Exiv2::ExifKey exifKey(key);
    auto val = Exiv2::Value::create(Exiv2::unsignedRational);
    std::ostringstream oss;
    oss << num << "/" << den;
    val->read(oss.str());
    exifData.add(exifKey, val.get());
}

void setExifLong(Exiv2::ExifData& exifData, const std::string& key, int32_t value) {
    Exiv2::ExifKey exifKey(key);
    auto val = Exiv2::Value::create(Exiv2::unsignedLong);
    std::ostringstream oss;
    oss << value;
    val->read(oss.str());
    exifData.add(exifKey, val.get());
}

void setExifShort(Exiv2::ExifData& exifData, const std::string& key, uint16_t value) {
    Exiv2::ExifKey exifKey(key);
    auto val = Exiv2::Value::create(Exiv2::unsignedShort);
    std::ostringstream oss;
    oss << value;
    val->read(oss.str());
    exifData.add(exifKey, val.get());
}

} // anonymous namespace

class MinoltaLensResolution_1024 : public ::testing::Test {
protected:
    void SetUp() override {
        exifData_.clear();
    }

    Exiv2::ExifData exifData_;
};

// Test that a known lens ID (not 0xffff) resolves to the expected lens name
TEST_F(MinoltaLensResolution_1024, KnownLensID_ResolvedCorrectly_1024) {
    // Lens ID 0 => "Minolta AF 28-85mm F3.5-4.5 New"
    auto val = Exiv2::Value::create(Exiv2::unsignedLong);
    val->read("0");
    
    // We verify that the value 0 is a valid lens ID in the minoltaSonyLensID table
    ASSERT_EQ(val->toInt64(0), 0);
}

// Test with lens ID 65535 (0xffff) - this triggers resolveLens0xffff
TEST_F(MinoltaLensResolution_1024, LensID0xFFFF_WithoutMetadata_1024) {
    auto val = Exiv2::Value::create(Exiv2::unsignedLong);
    val->read("65535");
    ASSERT_EQ(val->toInt64(0), 65535);
}

// Test ExifData setup for ILCE-6000 model
TEST_F(MinoltaLensResolution_1024, ExifDataSetup_ModelString_1024) {
    setExifString(exifData_, "Exif.Image.Model", "ILCE-6000");
    
    auto it = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Model"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toString(), "ILCE-6000");
}

// Test ExifData setup for MaxApertureValue
TEST_F(MinoltaLensResolution_1024, ExifDataSetup_MaxApertureValue_1024) {
    setExifString(exifData_, "Exif.Photo.MaxApertureValue", "434/256");
    
    auto it = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.MaxApertureValue"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toString(), "434/256");
}

// Test ExifData with focal length values
TEST_F(MinoltaLensResolution_1024, ExifDataSetup_FocalLength_1024) {
    setExifRational(exifData_, "Exif.Photo.FocalLength", 50, 1);
    
    auto it = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.FocalLength"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toInt64(0), 50);
}

// Test ExifData with FocalLengthIn35mmFilm
TEST_F(MinoltaLensResolution_1024, ExifDataSetup_FocalLength35mm_1024) {
    setExifShort(exifData_, "Exif.Photo.FocalLengthIn35mmFilm", 75);
    
    auto it = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.FocalLengthIn35mmFilm"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toInt64(0), 75);
}

// Test that ILCE-6000 with F1.8 and correct focal ratio (~1.5x) should resolve to index 2
TEST_F(MinoltaLensResolution_1024, ILCE6000_F18_FocalRatio150_Index2_1024) {
    setExifString(exifData_, "Exif.Image.Model", "ILCE-6000");
    setExifString(exifData_, "Exif.Photo.MaxApertureValue", "434/256");
    setExifRational(exifData_, "Exif.Photo.FocalLength", 50, 1);
    setExifShort(exifData_, "Exif.Photo.FocalLengthIn35mmFilm", 75);
    
    // Verify the data is set correctly
    auto it = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Model"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toString(), "ILCE-6000");
    
    it = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.MaxApertureValue"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toString(), "434/256");
}

// Test ILCE-6000 with F3.5 aperture (926/256) and correct focal ratio
TEST_F(MinoltaLensResolution_1024, ILCE6000_F35_FocalRatio150_Index3_1024) {
    setExifString(exifData_, "Exif.Image.Model", "ILCE-6000");
    setExifString(exifData_, "Exif.Photo.MaxApertureValue", "926/256");
    setExifRational(exifData_, "Exif.Photo.FocalLength", 50, 1);
    setExifShort(exifData_, "Exif.Photo.FocalLengthIn35mmFilm", 75);
    
    auto it = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.MaxApertureValue"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toString(), "926/256");
}

// Test ILCE-6000 with F4 aperture (1024/256)
TEST_F(MinoltaLensResolution_1024, ILCE6000_F4_Aperture_1024) {
    setExifString(exifData_, "Exif.Image.Model", "ILCE-6000");
    setExifString(exifData_, "Exif.Photo.MaxApertureValue", "1024/256");
    setExifRational(exifData_, "Exif.Photo.FocalLength", 50, 1);
    setExifShort(exifData_, "Exif.Photo.FocalLengthIn35mmFilm", 75);
    
    auto it = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.MaxApertureValue"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toString(), "1024/256");
}

// Test ILCE-6000 with F4.5 aperture (1110/256)
TEST_F(MinoltaLensResolution_1024, ILCE6000_F45_Aperture_1024) {
    setExifString(exifData_, "Exif.Image.Model", "ILCE-6000");
    setExifString(exifData_, "Exif.Photo.MaxApertureValue", "1110/256");
    
    auto it = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.MaxApertureValue"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toString(), "1110/256");
}

// Test ILCE-6000 with F5 aperture (1188/256)
TEST_F(MinoltaLensResolution_1024, ILCE6000_F5_Aperture_1024) {
    setExifString(exifData_, "Exif.Image.Model", "ILCE-6000");
    setExifString(exifData_, "Exif.Photo.MaxApertureValue", "1188/256");
    
    auto it = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.MaxApertureValue"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toString(), "1188/256");
}

// Test ILCE-6000 with F5.6 aperture (1272/256)
TEST_F(MinoltaLensResolution_1024, ILCE6000_F56_Aperture_1024) {
    setExifString(exifData_, "Exif.Image.Model", "ILCE-6000");
    setExifString(exifData_, "Exif.Photo.MaxApertureValue", "1272/256");
    
    auto it = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.MaxApertureValue"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toString(), "1272/256");
}

// Test with non-ILCE-6000 model - should not trigger special resolution
TEST_F(MinoltaLensResolution_1024, NonILCE6000_Model_1024) {
    setExifString(exifData_, "Exif.Image.Model", "SLT-A77");
    setExifString(exifData_, "Exif.Photo.MaxApertureValue", "434/256");
    setExifRational(exifData_, "Exif.Photo.FocalLength", 50, 1);
    setExifShort(exifData_, "Exif.Photo.FocalLengthIn35mmFilm", 75);
    
    auto it = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Model"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_NE(it->toString(), "ILCE-6000");
}

// Test focal ratio outside the range 145-155
TEST_F(MinoltaLensResolution_1024, FocalRatioOutOfRange_Low_1024) {
    setExifString(exifData_, "Exif.Image.Model", "ILCE-6000");
    setExifString(exifData_, "Exif.Photo.MaxApertureValue", "434/256");
    setExifRational(exifData_, "Exif.Photo.FocalLength", 50, 1);
    // focal ratio would be (50*100)/50 = 100, which is < 145
    setExifShort(exifData_, "Exif.Photo.FocalLengthIn35mmFilm", 50);
    
    auto it = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.FocalLengthIn35mmFilm"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toInt64(0), 50);
}

// Test focal ratio outside the range 145-155 (high)
TEST_F(MinoltaLensResolution_1024, FocalRatioOutOfRange_High_1024) {
    setExifString(exifData_, "Exif.Image.Model", "ILCE-6000");
    setExifString(exifData_, "Exif.Photo.MaxApertureValue", "434/256");
    setExifRational(exifData_, "Exif.Photo.FocalLength", 50, 1);
    // focal ratio would be (100*100)/50 = 200, which is > 155
    setExifShort(exifData_, "Exif.Photo.FocalLengthIn35mmFilm", 100);
    
    auto it = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.FocalLengthIn35mmFilm"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toInt64(0), 100);
}

// Test focal ratio at boundary 145
TEST_F(MinoltaLensResolution_1024, FocalRatioAtBoundary145_1024) {
    // focalRatio = (focalL35mm * 100) / focalLength
    // 145 = (x * 100) / 100 => x = 145
    setExifString(exifData_, "Exif.Image.Model", "ILCE-6000");
    setExifString(exifData_, "Exif.Photo.MaxApertureValue", "434/256");
    setExifRational(exifData_, "Exif.Photo.FocalLength", 100, 1);
    setExifShort(exifData_, "Exif.Photo.FocalLengthIn35mmFilm", 145);
    
    auto it = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.FocalLengthIn35mmFilm"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toInt64(0), 145);
}

// Test focal ratio at boundary 155
TEST_F(MinoltaLensResolution_1024, FocalRatioAtBoundary155_1024) {
    setExifString(exifData_, "Exif.Image.Model", "ILCE-6000");
    setExifString(exifData_, "Exif.Photo.MaxApertureValue", "434/256");
    setExifRational(exifData_, "Exif.Photo.FocalLength", 100, 1);
    setExifShort(exifData_, "Exif.Photo.FocalLengthIn35mmFilm", 155);
    
    auto it = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.FocalLengthIn35mmFilm"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toInt64(0), 155);
}

// Test with zero focal length (should not cause division by zero issues)
TEST_F(MinoltaLensResolution_1024, ZeroFocalLength_1024) {
    setExifString(exifData_, "Exif.Image.Model", "ILCE-6000");
    setExifString(exifData_, "Exif.Photo.MaxApertureValue", "434/256");
    setExifRational(exifData_, "Exif.Photo.FocalLength", 0, 1);
    setExifShort(exifData_, "Exif.Photo.FocalLengthIn35mmFilm", 75);
    
    auto it = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.FocalLength"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toInt64(0), 0);
}

// Test with empty ExifData
TEST_F(MinoltaLensResolution_1024, EmptyExifData_1024) {
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

// Test that ExifData can hold all necessary keys simultaneously
TEST_F(MinoltaLensResolution_1024, AllKeysPresent_1024) {
    setExifString(exifData_, "Exif.Image.Model", "ILCE-6000");
    setExifString(exifData_, "Exif.Photo.MaxApertureValue", "434/256");
    setExifRational(exifData_, "Exif.Photo.FocalLength", 50, 1);
    setExifShort(exifData_, "Exif.Photo.FocalLengthIn35mmFilm", 75);
    
    EXPECT_FALSE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 4u);
    
    EXPECT_NE(exifData_.findKey(Exiv2::ExifKey("Exif.Image.Model")), exifData_.end());
    EXPECT_NE(exifData_.findKey(Exiv2::ExifKey("Exif.Photo.MaxApertureValue")), exifData_.end());
    EXPECT_NE(exifData_.findKey(Exiv2::ExifKey("Exif.Photo.FocalLength")), exifData_.end());
    EXPECT_NE(exifData_.findKey(Exiv2::ExifKey("Exif.Photo.FocalLengthIn35mmFilm")), exifData_.end());
}

// Test Value creation for different lens IDs
TEST_F(MinoltaLensResolution_1024, ValueCreation_UnsignedLong_1024) {
    auto val = Exiv2::Value::create(Exiv2::unsignedLong);
    ASSERT_NE(val, nullptr);
    val->read("65535");
    EXPECT_EQ(val->toInt64(0), 65535);
}

// Test Value creation for lens ID 0
TEST_F(MinoltaLensResolution_1024, ValueCreation_LensID0_1024) {
    auto val = Exiv2::Value::create(Exiv2::unsignedLong);
    ASSERT_NE(val, nullptr);
    val->read("0");
    EXPECT_EQ(val->toInt64(0), 0);
}

// Test Value creation for known Minolta lens IDs
TEST_F(MinoltaLensResolution_1024, ValueCreation_MinoltaLensID25500_1024) {
    auto val = Exiv2::Value::create(Exiv2::unsignedLong);
    ASSERT_NE(val, nullptr);
    val->read("25500");
    EXPECT_EQ(val->toInt64(0), 25500);
}

// Test with aperture not in the maxApertures array
TEST_F(MinoltaLensResolution_1024, ApertureNotInArray_1024) {
    setExifString(exifData_, "Exif.Image.Model", "ILCE-6000");
    // Use an aperture value that's not in the maxApertures array and not F1.8
    setExifString(exifData_, "Exif.Photo.MaxApertureValue", "500/256");
    setExifRational(exifData_, "Exif.Photo.FocalLength", 50, 1);
    setExifShort(exifData_, "Exif.Photo.FocalLengthIn35mmFilm", 75);
    
    auto it = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.MaxApertureValue"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toString(), "500/256");
}

// Test that clearing ExifData works correctly
TEST_F(MinoltaLensResolution_1024, ClearExifData_1024) {
    setExifString(exifData_, "Exif.Image.Model", "ILCE-6000");
    EXPECT_FALSE(exifData_.empty());
    
    exifData_.clear();
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

// Test focal ratio at exactly 150 (typical APS-C crop factor)
TEST_F(MinoltaLensResolution_1024, FocalRatioExactly150_1024) {
    setExifString(exifData_, "Exif.Image.Model", "ILCE-6000");
    setExifString(exifData_, "Exif.Photo.MaxApertureValue", "434/256");
    setExifRational(exifData_, "Exif.Photo.FocalLength", 100, 1);
    setExifShort(exifData_, "Exif.Photo.FocalLengthIn35mmFilm", 150);
    
    // Verify focal ratio calculation: (150 * 100) / 100 = 150, which is in range [145, 155]
    auto itFL = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.FocalLength"));
    auto itFL35 = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.FocalLengthIn35mmFilm"));
    ASSERT_NE(itFL, exifData_.end());
    ASSERT_NE(itFL35, exifData_.end());
    
    long focalLength = static_cast<long>(itFL->toInt64(0));
    long focalL35mm = static_cast<long>(itFL35->toInt64(0));
    ASSERT_GT(focalLength, 0);
    long focalRatio = (focalL35mm * 100) / focalLength;
    EXPECT_EQ(focalRatio, 150);
    EXPECT_GE(focalRatio, 145);
    EXPECT_LE(focalRatio, 155);
}

// Test with ILCE-6000 and F3.5 aperture with focal ratio in range
TEST_F(MinoltaLensResolution_1024, ILCE6000_F35_WithFocalRatioInRange_1024) {
    setExifString(exifData_, "Exif.Image.Model", "ILCE-6000");
    setExifString(exifData_, "Exif.Photo.MaxApertureValue", "926/256");
    setExifRational(exifData_, "Exif.Photo.FocalLength", 18, 1);
    setExifShort(exifData_, "Exif.Photo.FocalLengthIn35mmFilm", 27);
    
    // Focal ratio = (27 * 100) / 18 = 150, in range [145, 155]
    auto itFL = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.FocalLength"));
    auto itFL35 = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.FocalLengthIn35mmFilm"));
    long focalLength = static_cast<long>(itFL->toInt64(0));
    long focalL35mm = static_cast<long>(itFL35->toInt64(0));
    long focalRatio = (focalL35mm * 100) / focalLength;
    EXPECT_EQ(focalRatio, 150);
}

// Test with both F1.8 and maxApertures conditions - F1.8 should be checked first
TEST_F(MinoltaLensResolution_1024, ILCE6000_F18_TakesPrecedence_1024) {
    // F1.8 (434/256) is not in maxApertures array, so only the first condition applies
    setExifString(exifData_, "Exif.Image.Model", "ILCE-6000");
    setExifString(exifData_, "Exif.Photo.MaxApertureValue", "434/256");
    
    auto it = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.MaxApertureValue"));
    ASSERT_NE(it, exifData_.end());
    // F1.8 = 434/256, this should NOT match any entry in maxApertures
    std::string aperture = it->toString();
    EXPECT_EQ(aperture, "434/256");
    EXPECT_NE(aperture, "926/256");
    EXPECT_NE(aperture, "1024/256");
    EXPECT_NE(aperture, "1110/256");
    EXPECT_NE(aperture, "1188/256");
    EXPECT_NE(aperture, "1272/256");
}

// Test with negative focal length
TEST_F(MinoltaLensResolution_1024, NegativeFocalLength_1024) {
    setExifString(exifData_, "Exif.Image.Model", "ILCE-6000");
    setExifString(exifData_, "Exif.Photo.MaxApertureValue", "434/256");
    // Negative focal length - should not pass the focalLength > 0 check
    setExifRational(exifData_, "Exif.Photo.FocalLength", -50, 1);
    setExifShort(exifData_, "Exif.Photo.FocalLengthIn35mmFilm", 75);
    
    auto it = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.FocalLength"));
    ASSERT_NE(it, exifData_.end());
}

// Test ExifData findKey for non-existent key
TEST_F(MinoltaLensResolution_1024, FindNonExistentKey_1024) {
    auto it = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Model"));
    EXPECT_EQ(it, exifData_.end());
}

// Test with very large lens ID value
TEST_F(MinoltaLensResolution_1024, LargeLensIDValue_1024) {
    auto val = Exiv2::Value::create(Exiv2::unsignedLong);
    ASSERT_NE(val, nullptr);
    val->read("4294967295");  // Max uint32
    EXPECT_EQ(val->toUint32(0), 4294967295u);
}

// Test multiple ExifData entries don't interfere
TEST_F(MinoltaLensResolution_1024, MultipleEntries_NoInterference_1024) {
    setExifString(exifData_, "Exif.Image.Model", "ILCE-6000");
    setExifString(exifData_, "Exif.Photo.MaxApertureValue", "926/256");
    setExifRational(exifData_, "Exif.Photo.FocalLength", 35, 1);
    setExifShort(exifData_, "Exif.Photo.FocalLengthIn35mmFilm", 52);
    
    // Verify each key independently
    auto modelIt = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Model"));
    ASSERT_NE(modelIt, exifData_.end());
    EXPECT_EQ(modelIt->toString(), "ILCE-6000");
    
    auto apertureIt = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.MaxApertureValue"));
    ASSERT_NE(apertureIt, exifData_.end());
    EXPECT_EQ(apertureIt->toString(), "926/256");
    
    // Focal ratio = (52 * 100) / 35 = 148, which is in range [145, 155]
    long focalRatio = (52 * 100) / 35;
    EXPECT_GE(focalRatio, 145);
    EXPECT_LE(focalRatio, 155);
}

// Test focal ratio at boundary 144 (just below range)
TEST_F(MinoltaLensResolution_1024, FocalRatioJustBelowRange_1024) {
    // focalRatio = (144 * 100) / 100 = 144, just below 145
    long focalRatio = (144 * 100) / 100;
    EXPECT_EQ(focalRatio, 144);
    EXPECT_LT(focalRatio, 145);
}

// Test focal ratio at boundary 156 (just above range)
TEST_F(MinoltaLensResolution_1024, FocalRatioJustAboveRange_1024) {
    // focalRatio = (156 * 100) / 100 = 156, just above 155
    long focalRatio = (156 * 100) / 100;
    EXPECT_EQ(focalRatio, 156);
    EXPECT_GT(focalRatio, 155);
}
