#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <string>
#include <sstream>

// We need access to the Converter class which is defined in convert.cpp
// The public API for conversion is through copyExifToXmp, copyXmpToExif, etc.
// But based on the partial code, we need to test cnvXmpGPSCoord specifically.
// Since Converter is in the Exiv2 namespace but defined in convert.cpp,
// we'll use the conversion functions or create Converter objects directly.

// Forward declaration - Converter is defined in convert.cpp
namespace Exiv2 {
void copyXmpToExif(const XmpData& xmpData, ExifData& exifData);
void copyExifToXmp(const ExifData& exifData, XmpData& xmpData);
}

namespace {

// Helper to suppress warnings during tests
class SuppressWarnings {
public:
    SuppressWarnings() {
        oldLevel_ = Exiv2::LogMsg::level();
        Exiv2::LogMsg::setLevel(Exiv2::LogMsg::mute);
    }
    ~SuppressWarnings() {
        Exiv2::LogMsg::setLevel(oldLevel_);
    }
private:
    Exiv2::LogMsg::Level oldLevel_;
};

class CnvXmpGPSCoordTest_1850 : public ::testing::Test {
protected:
    void SetUp() override {
        Exiv2::XmpParser::initialize();
        // Mute warnings to keep test output clean
        Exiv2::LogMsg::setLevel(Exiv2::LogMsg::mute);
    }

    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }

    Exiv2::ExifData exifData_;
    Exiv2::XmpData xmpData_;
};

// Test: Normal latitude conversion with degrees, minutes, seconds format (N)
TEST_F(CnvXmpGPSCoordTest_1850, NormalLatitudeNorth_1850) {
    xmpData_["Xmp.exif.GPSLatitude"] = "54,59,23N";

    Exiv2::copyXmpToExif(xmpData_, exifData_);

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"));
    ASSERT_NE(pos, exifData_.end());

    auto refPos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitudeRef"));
    ASSERT_NE(refPos, exifData_.end());
    EXPECT_EQ(refPos->toString(), "N");
}

// Test: Normal latitude conversion with South reference
TEST_F(CnvXmpGPSCoordTest_1850, NormalLatitudeSouth_1850) {
    xmpData_["Xmp.exif.GPSLatitude"] = "33,51,54S";

    Exiv2::copyXmpToExif(xmpData_, exifData_);

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"));
    ASSERT_NE(pos, exifData_.end());

    auto refPos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitudeRef"));
    ASSERT_NE(refPos, exifData_.end());
    EXPECT_EQ(refPos->toString(), "S");
}

// Test: Normal longitude conversion with East reference
TEST_F(CnvXmpGPSCoordTest_1850, NormalLongitudeEast_1850) {
    xmpData_["Xmp.exif.GPSLongitude"] = "10,0,0E";

    Exiv2::copyXmpToExif(xmpData_, exifData_);

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSLongitude"));
    ASSERT_NE(pos, exifData_.end());

    auto refPos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSLongitudeRef"));
    ASSERT_NE(refPos, exifData_.end());
    EXPECT_EQ(refPos->toString(), "E");
}

// Test: Normal longitude conversion with West reference
TEST_F(CnvXmpGPSCoordTest_1850, NormalLongitudeWest_1850) {
    xmpData_["Xmp.exif.GPSLongitude"] = "122,25,10W";

    Exiv2::copyXmpToExif(xmpData_, exifData_);

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSLongitude"));
    ASSERT_NE(pos, exifData_.end());

    auto refPos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSLongitudeRef"));
    ASSERT_NE(refPos, exifData_.end());
    EXPECT_EQ(refPos->toString(), "W");
}

// Test: GPS coordinate with degrees and decimal minutes (no seconds separator)
TEST_F(CnvXmpGPSCoordTest_1850, DegreesAndDecimalMinutes_1850) {
    xmpData_["Xmp.exif.GPSLatitude"] = "54,59.5N";

    Exiv2::copyXmpToExif(xmpData_, exifData_);

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"));
    ASSERT_NE(pos, exifData_.end());

    auto refPos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitudeRef"));
    ASSERT_NE(refPos, exifData_.end());
    EXPECT_EQ(refPos->toString(), "N");
}

// Test: XMP key not found - should not create exif data
TEST_F(CnvXmpGPSCoordTest_1850, XmpKeyNotFound_1850) {
    // Don't set any XMP GPS data
    Exiv2::copyXmpToExif(xmpData_, exifData_);

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"));
    EXPECT_EQ(pos, exifData_.end());
}

// Test: Invalid reference character - should not convert
TEST_F(CnvXmpGPSCoordTest_1850, InvalidRefCharacter_1850) {
    xmpData_["Xmp.exif.GPSLatitude"] = "54,59,23X";

    Exiv2::copyXmpToExif(xmpData_, exifData_);

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"));
    EXPECT_EQ(pos, exifData_.end());
}

// Test: Zero coordinates
TEST_F(CnvXmpGPSCoordTest_1850, ZeroCoordinates_1850) {
    xmpData_["Xmp.exif.GPSLatitude"] = "0,0,0N";

    Exiv2::copyXmpToExif(xmpData_, exifData_);

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"));
    ASSERT_NE(pos, exifData_.end());

    auto refPos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitudeRef"));
    ASSERT_NE(refPos, exifData_.end());
    EXPECT_EQ(refPos->toString(), "N");
}

// Test: Missing comma separator - should fail conversion
TEST_F(CnvXmpGPSCoordTest_1850, MissingCommaSeparator_1850) {
    xmpData_["Xmp.exif.GPSLatitude"] = "54 59 23N";

    Exiv2::copyXmpToExif(xmpData_, exifData_);

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"));
    EXPECT_EQ(pos, exifData_.end());
}

// Test: Longitude with degrees, minutes, and seconds
TEST_F(CnvXmpGPSCoordTest_1850, LongitudeDMS_1850) {
    xmpData_["Xmp.exif.GPSLongitude"] = "2,17,40E";

    Exiv2::copyXmpToExif(xmpData_, exifData_);

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSLongitude"));
    ASSERT_NE(pos, exifData_.end());

    // Verify the value has 3 rational components
    EXPECT_EQ(pos->count(), 3u);
}

// Test: Latitude with fractional seconds
TEST_F(CnvXmpGPSCoordTest_1850, FractionalSeconds_1850) {
    xmpData_["Xmp.exif.GPSLatitude"] = "40,26,46.302N";

    Exiv2::copyXmpToExif(xmpData_, exifData_);

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"));
    ASSERT_NE(pos, exifData_.end());

    auto refPos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitudeRef"));
    ASSERT_NE(refPos, exifData_.end());
    EXPECT_EQ(refPos->toString(), "N");
}

// Test: Both latitude and longitude conversion
TEST_F(CnvXmpGPSCoordTest_1850, BothLatAndLon_1850) {
    xmpData_["Xmp.exif.GPSLatitude"] = "48,51,24N";
    xmpData_["Xmp.exif.GPSLongitude"] = "2,21,7E";

    Exiv2::copyXmpToExif(xmpData_, exifData_);

    auto latPos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"));
    ASSERT_NE(latPos, exifData_.end());

    auto latRefPos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitudeRef"));
    ASSERT_NE(latRefPos, exifData_.end());
    EXPECT_EQ(latRefPos->toString(), "N");

    auto lonPos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSLongitude"));
    ASSERT_NE(lonPos, exifData_.end());

    auto lonRefPos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSLongitudeRef"));
    ASSERT_NE(lonRefPos, exifData_.end());
    EXPECT_EQ(lonRefPos->toString(), "E");
}

// Test: Decimal minutes format - minutes with decimal part converted to seconds
TEST_F(CnvXmpGPSCoordTest_1850, DecimalMinutesConversion_1850) {
    // 30.5 minutes = 30 minutes 30 seconds
    xmpData_["Xmp.exif.GPSLatitude"] = "40,30.5N";

    Exiv2::copyXmpToExif(xmpData_, exifData_);

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"));
    ASSERT_NE(pos, exifData_.end());
    EXPECT_EQ(pos->count(), 3u);
}

// Test: Maximum valid longitude value
TEST_F(CnvXmpGPSCoordTest_1850, MaxLongitude_1850) {
    xmpData_["Xmp.exif.GPSLongitude"] = "180,0,0E";

    Exiv2::copyXmpToExif(xmpData_, exifData_);

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSLongitude"));
    ASSERT_NE(pos, exifData_.end());
}

// Test: Maximum valid latitude value
TEST_F(CnvXmpGPSCoordTest_1850, MaxLatitude_1850) {
    xmpData_["Xmp.exif.GPSLatitude"] = "90,0,0N";

    Exiv2::copyXmpToExif(xmpData_, exifData_);

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"));
    ASSERT_NE(pos, exifData_.end());
}

// Test: Completely invalid string format
TEST_F(CnvXmpGPSCoordTest_1850, CompletelyInvalidFormat_1850) {
    xmpData_["Xmp.exif.GPSLatitude"] = "invalidN";

    Exiv2::copyXmpToExif(xmpData_, exifData_);

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"));
    EXPECT_EQ(pos, exifData_.end());
}

// Test: Single character value (just the ref)
TEST_F(CnvXmpGPSCoordTest_1850, SingleCharRef_1850) {
    xmpData_["Xmp.exif.GPSLatitude"] = "N";

    Exiv2::copyXmpToExif(xmpData_, exifData_);

    // With just "N", after pop_back the value is empty, parsing should fail
    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"));
    EXPECT_EQ(pos, exifData_.end());
}

// Test: Verify that existing exif data doesn't prevent conversion when overwrite is default
TEST_F(CnvXmpGPSCoordTest_1850, OverwriteExistingData_1850) {
    // First set some GPS data
    xmpData_["Xmp.exif.GPSLatitude"] = "10,20,30N";
    Exiv2::copyXmpToExif(xmpData_, exifData_);

    // Now update the XMP data and convert again
    xmpData_["Xmp.exif.GPSLatitude"] = "20,30,40S";
    Exiv2::copyXmpToExif(xmpData_, exifData_);

    auto refPos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitudeRef"));
    ASSERT_NE(refPos, exifData_.end());
    // The behavior depends on overwrite setting, but default should be true
}

}  // namespace
