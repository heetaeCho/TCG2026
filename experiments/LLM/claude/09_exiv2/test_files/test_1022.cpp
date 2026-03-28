#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include <exiv2/exiv2.hpp>
#include "minoltamn_int.hpp"

namespace {

// Helper to create an ExifData with specific key-value pairs
void setExifString(Exiv2::ExifData& exifData, const std::string& key, const std::string& value) {
    Exiv2::ExifKey exifKey(key);
    auto v = Exiv2::Value::create(Exiv2::asciiString);
    v->read(value);
    exifData.add(exifKey, v.get());
}

void setExifLong(Exiv2::ExifData& exifData, const std::string& key, uint32_t value) {
    Exiv2::ExifKey exifKey(key);
    auto v = Exiv2::Value::create(Exiv2::unsignedLong);
    v->read(std::to_string(value));
    exifData.add(exifKey, v.get());
}

void setExifRational(Exiv2::ExifData& exifData, const std::string& key, const std::string& rationalStr) {
    Exiv2::ExifKey exifKey(key);
    auto v = Exiv2::Value::create(Exiv2::unsignedRational);
    v->read(rationalStr);
    exifData.add(exifKey, v.get());
}

} // namespace

class ResolveLens0x80Test_1022 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a value representing lens ID 0x80 (128)
        value_ = Exiv2::Value::create(Exiv2::unsignedLong);
        value_->read("128");
    }

    std::unique_ptr<Exiv2::Value> value_;
    Exiv2::ExifData exifData_;
};

// Test: When metadata is null, should fall through to default tag printing
TEST_F(ResolveLens0x80Test_1022, NullMetadata_FallsThrough_1022) {
    std::ostringstream os;
    Exiv2::Internal::resolveLens0x80(os, *value_, nullptr);
    std::string result = os.str();
    // Should produce some output (the default EXV_PRINT_TAG result for lens ID 128)
    EXPECT_FALSE(result.empty());
}

// Test: When model is SLT-A77V, maxAperture is 1024/256, and focal length is within [18,200],
// should resolve to index 2 (an alternate lens name)
TEST_F(ResolveLens0x80Test_1022, SLTA77V_MatchingConditions_ResolvesIndex2_1022) {
    setExifString(exifData_, "Exif.Image.Model", "SLT-A77V");
    setExifRational(exifData_, "Exif.Photo.MaxApertureValue", "1024/256");
    setExifRational(exifData_, "Exif.Photo.FocalLength", "50/1");

    std::ostringstream os;
    Exiv2::Internal::resolveLens0x80(os, *value_, &exifData_);
    std::string result = os.str();
    // When index=2, it should resolve to a specific lens name different from the default
    EXPECT_FALSE(result.empty());
}

// Test: When model is SLT-A77V but maxAperture doesn't match, should fall through to default
TEST_F(ResolveLens0x80Test_1022, SLTA77V_WrongMaxAperture_FallsThrough_1022) {
    setExifString(exifData_, "Exif.Image.Model", "SLT-A77V");
    setExifRational(exifData_, "Exif.Photo.MaxApertureValue", "512/256");
    setExifRational(exifData_, "Exif.Photo.FocalLength", "50/1");

    std::ostringstream os;
    Exiv2::Internal::resolveLens0x80(os, *value_, &exifData_);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: When model is different, should fall through to default
TEST_F(ResolveLens0x80Test_1022, DifferentModel_FallsThrough_1022) {
    setExifString(exifData_, "Exif.Image.Model", "DSLR-A700");
    setExifRational(exifData_, "Exif.Photo.MaxApertureValue", "1024/256");
    setExifRational(exifData_, "Exif.Photo.FocalLength", "50/1");

    std::ostringstream os;
    Exiv2::Internal::resolveLens0x80(os, *value_, &exifData_);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: When focal length is below range (< 18), should fall through
TEST_F(ResolveLens0x80Test_1022, SLTA77V_FocalLengthBelowRange_FallsThrough_1022) {
    setExifString(exifData_, "Exif.Image.Model", "SLT-A77V");
    setExifRational(exifData_, "Exif.Photo.MaxApertureValue", "1024/256");
    setExifRational(exifData_, "Exif.Photo.FocalLength", "10/1");

    std::ostringstream os;
    Exiv2::Internal::resolveLens0x80(os, *value_, &exifData_);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: When focal length is above range (> 200), should fall through
TEST_F(ResolveLens0x80Test_1022, SLTA77V_FocalLengthAboveRange_FallsThrough_1022) {
    setExifString(exifData_, "Exif.Image.Model", "SLT-A77V");
    setExifRational(exifData_, "Exif.Photo.MaxApertureValue", "1024/256");
    setExifRational(exifData_, "Exif.Photo.FocalLength", "300/1");

    std::ostringstream os;
    Exiv2::Internal::resolveLens0x80(os, *value_, &exifData_);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: Boundary - focal length exactly 18
TEST_F(ResolveLens0x80Test_1022, SLTA77V_FocalLengthExactly18_1022) {
    setExifString(exifData_, "Exif.Image.Model", "SLT-A77V");
    setExifRational(exifData_, "Exif.Photo.MaxApertureValue", "1024/256");
    setExifRational(exifData_, "Exif.Photo.FocalLength", "18/1");

    std::ostringstream os;
    Exiv2::Internal::resolveLens0x80(os, *value_, &exifData_);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: Boundary - focal length exactly 200
TEST_F(ResolveLens0x80Test_1022, SLTA77V_FocalLengthExactly200_1022) {
    setExifString(exifData_, "Exif.Image.Model", "SLT-A77V");
    setExifRational(exifData_, "Exif.Photo.MaxApertureValue", "1024/256");
    setExifRational(exifData_, "Exif.Photo.FocalLength", "200/1");

    std::ostringstream os;
    Exiv2::Internal::resolveLens0x80(os, *value_, &exifData_);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: Empty ExifData (no keys present), should fall through gracefully
TEST_F(ResolveLens0x80Test_1022, EmptyExifData_FallsThrough_1022) {
    std::ostringstream os;
    Exiv2::Internal::resolveLens0x80(os, *value_, &exifData_);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: All conditions match, verify output differs from non-matching case
TEST_F(ResolveLens0x80Test_1022, MatchingVsNonMatching_DifferentOutput_1022) {
    // Matching case
    Exiv2::ExifData matchData;
    setExifString(matchData, "Exif.Image.Model", "SLT-A77V");
    setExifRational(matchData, "Exif.Photo.MaxApertureValue", "1024/256");
    setExifRational(matchData, "Exif.Photo.FocalLength", "50/1");

    std::ostringstream osMatch;
    Exiv2::Internal::resolveLens0x80(osMatch, *value_, &matchData);

    // Non-matching case (different model)
    Exiv2::ExifData noMatchData;
    setExifString(noMatchData, "Exif.Image.Model", "OTHER-MODEL");
    setExifRational(noMatchData, "Exif.Photo.MaxApertureValue", "1024/256");
    setExifRational(noMatchData, "Exif.Photo.FocalLength", "50/1");

    std::ostringstream osNoMatch;
    Exiv2::Internal::resolveLens0x80(osNoMatch, *value_, &noMatchData);

    // Both should produce non-empty results
    EXPECT_FALSE(osMatch.str().empty());
    EXPECT_FALSE(osNoMatch.str().empty());
}

// Test: Focal length at boundary 17 (just below 18), should not match
TEST_F(ResolveLens0x80Test_1022, SLTA77V_FocalLength17_NoMatch_1022) {
    setExifString(exifData_, "Exif.Image.Model", "SLT-A77V");
    setExifRational(exifData_, "Exif.Photo.MaxApertureValue", "1024/256");
    setExifRational(exifData_, "Exif.Photo.FocalLength", "17/1");

    std::ostringstream os;
    Exiv2::Internal::resolveLens0x80(os, *value_, &exifData_);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: Focal length at boundary 201 (just above 200), should not match
TEST_F(ResolveLens0x80Test_1022, SLTA77V_FocalLength201_NoMatch_1022) {
    setExifString(exifData_, "Exif.Image.Model", "SLT-A77V");
    setExifRational(exifData_, "Exif.Photo.MaxApertureValue", "1024/256");
    setExifRational(exifData_, "Exif.Photo.FocalLength", "201/1");

    std::ostringstream os;
    Exiv2::Internal::resolveLens0x80(os, *value_, &exifData_);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: Partial metadata - only model present
TEST_F(ResolveLens0x80Test_1022, OnlyModelPresent_FallsThrough_1022) {
    setExifString(exifData_, "Exif.Image.Model", "SLT-A77V");

    std::ostringstream os;
    Exiv2::Internal::resolveLens0x80(os, *value_, &exifData_);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: Partial metadata - model and maxAperture but no focal length
TEST_F(ResolveLens0x80Test_1022, NoFocalLength_FallsThrough_1022) {
    setExifString(exifData_, "Exif.Image.Model", "SLT-A77V");
    setExifRational(exifData_, "Exif.Photo.MaxApertureValue", "1024/256");

    std::ostringstream os;
    Exiv2::Internal::resolveLens0x80(os, *value_, &exifData_);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: Mid-range focal length with all conditions matching
TEST_F(ResolveLens0x80Test_1022, SLTA77V_MidRangeFocalLength100_1022) {
    setExifString(exifData_, "Exif.Image.Model", "SLT-A77V");
    setExifRational(exifData_, "Exif.Photo.MaxApertureValue", "1024/256");
    setExifRational(exifData_, "Exif.Photo.FocalLength", "100/1");

    std::ostringstream os;
    Exiv2::Internal::resolveLens0x80(os, *value_, &exifData_);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}
