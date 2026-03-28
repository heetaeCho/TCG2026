#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <string>
#include <sstream>

// Test fixture for Converter tests focusing on cnvXmpDate
class ConverterCnvXmpDateTest_1846 : public ::testing::Test {
protected:
    Exiv2::ExifData exifData_;
    Exiv2::XmpData xmpData_;

    void SetUp() override {
        // Suppress warnings to keep test output clean
        Exiv2::LogMsg::setLevel(Exiv2::LogMsg::mute);
    }

    void TearDown() override {
        Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
    }
};

// Test: When XMP key does not exist, nothing should happen
TEST_F(ConverterCnvXmpDateTest_1846, XmpKeyNotFound_DoesNothing_1846) {
    Exiv2::Converter converter(exifData_, xmpData_);

    // xmpData_ is empty, so "Xmp.xmp.CreateDate" won't be found
    converter.cnvXmpDate("Xmp.xmp.CreateDate", "Exif.Image.DateTime");

    // exifData_ should remain empty
    EXPECT_TRUE(exifData_.empty());
}

// Test: Convert a valid XMP date to Exif.Image.DateTime
TEST_F(ConverterCnvXmpDateTest_1846, ValidDate_ConvertToExifDateTime_1846) {
    Exiv2::Converter converter(exifData_, xmpData_);

    xmpData_["Xmp.xmp.CreateDate"] = "2023-06-15T10:30:45";

    converter.cnvXmpDate("Xmp.xmp.CreateDate", "Exif.Image.DateTime");

#ifdef EXV_HAVE_XMP_TOOLKIT
    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Image.DateTime"));
    EXPECT_NE(pos, exifData_.end());
    if (pos != exifData_.end()) {
        std::string val = pos->toString();
        // Should contain year 2023, month 06, day 15
        EXPECT_NE(val.find("2023"), std::string::npos);
    }
#else
    // Without XMP toolkit, conversion should not happen
    EXPECT_TRUE(exifData_.empty());
#endif
}

// Test: Convert a valid XMP date to Exif.Photo.DateTimeOriginal
TEST_F(ConverterCnvXmpDateTest_1846, ValidDate_ConvertToDateTimeOriginal_1846) {
    Exiv2::Converter converter(exifData_, xmpData_);

    xmpData_["Xmp.xmp.CreateDate"] = "2023-06-15T10:30:45";

    converter.cnvXmpDate("Xmp.xmp.CreateDate", "Exif.Photo.DateTimeOriginal");

#ifdef EXV_HAVE_XMP_TOOLKIT
    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.DateTimeOriginal"));
    EXPECT_NE(pos, exifData_.end());
#else
    EXPECT_TRUE(exifData_.empty());
#endif
}

// Test: Convert a valid XMP date to Exif.Photo.DateTimeDigitized
TEST_F(ConverterCnvXmpDateTest_1846, ValidDate_ConvertToDateTimeDigitized_1846) {
    Exiv2::Converter converter(exifData_, xmpData_);

    xmpData_["Xmp.xmp.CreateDate"] = "2023-06-15T10:30:45";

    converter.cnvXmpDate("Xmp.xmp.CreateDate", "Exif.Photo.DateTimeDigitized");

#ifdef EXV_HAVE_XMP_TOOLKIT
    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.DateTimeDigitized"));
    EXPECT_NE(pos, exifData_.end());
#else
    EXPECT_TRUE(exifData_.empty());
#endif
}

// Test: Convert a valid XMP date to Exif.GPSInfo.GPSTimeStamp
TEST_F(ConverterCnvXmpDateTest_1846, ValidDate_ConvertToGPSTimeStamp_1846) {
    Exiv2::Converter converter(exifData_, xmpData_);

    xmpData_["Xmp.xmp.CreateDate"] = "2023-06-15T10:30:45+00:00";

    converter.cnvXmpDate("Xmp.xmp.CreateDate", "Exif.GPSInfo.GPSTimeStamp");

#ifdef EXV_HAVE_XMP_TOOLKIT
    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSTimeStamp"));
    EXPECT_NE(pos, exifData_.end());

    // GPSDateStamp should also be set
    auto datePos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSDateStamp"));
    EXPECT_NE(datePos, exifData_.end());
#else
    EXPECT_TRUE(exifData_.empty());
#endif
}

// Test: Convert XMP date with nanoseconds to Exif.Image.DateTime should also set SubSecTime
TEST_F(ConverterCnvXmpDateTest_1846, DateWithNanoseconds_SetsSubSecTime_1846) {
    Exiv2::Converter converter(exifData_, xmpData_);

    xmpData_["Xmp.xmp.CreateDate"] = "2023-06-15T10:30:45.123456789";

    converter.cnvXmpDate("Xmp.xmp.CreateDate", "Exif.Image.DateTime");

#ifdef EXV_HAVE_XMP_TOOLKIT
    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Image.DateTime"));
    EXPECT_NE(pos, exifData_.end());

    // SubSecTime should be set when nanoseconds are present
    auto subPos = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.SubSecTime"));
    EXPECT_NE(subPos, exifData_.end());
#else
    EXPECT_TRUE(exifData_.empty());
#endif
}

// Test: Convert XMP date with nanoseconds to Exif.Photo.DateTimeOriginal sets SubSecTimeOriginal
TEST_F(ConverterCnvXmpDateTest_1846, DateWithNanoseconds_SetsSubSecTimeOriginal_1846) {
    Exiv2::Converter converter(exifData_, xmpData_);

    xmpData_["Xmp.xmp.CreateDate"] = "2023-06-15T10:30:45.123456789";

    converter.cnvXmpDate("Xmp.xmp.CreateDate", "Exif.Photo.DateTimeOriginal");

#ifdef EXV_HAVE_XMP_TOOLKIT
    auto subPos = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.SubSecTimeOriginal"));
    EXPECT_NE(subPos, exifData_.end());
#else
    EXPECT_TRUE(exifData_.empty());
#endif
}

// Test: Convert XMP date with nanoseconds to Exif.Photo.DateTimeDigitized sets SubSecTimeDigitized
TEST_F(ConverterCnvXmpDateTest_1846, DateWithNanoseconds_SetsSubSecTimeDigitized_1846) {
    Exiv2::Converter converter(exifData_, xmpData_);

    xmpData_["Xmp.xmp.CreateDate"] = "2023-06-15T10:30:45.123456789";

    converter.cnvXmpDate("Xmp.xmp.CreateDate", "Exif.Photo.DateTimeDigitized");

#ifdef EXV_HAVE_XMP_TOOLKIT
    auto subPos = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.SubSecTimeDigitized"));
    EXPECT_NE(subPos, exifData_.end());
#else
    EXPECT_TRUE(exifData_.empty());
#endif
}

// Test: Erase mode - XMP data should be erased after conversion
TEST_F(ConverterCnvXmpDateTest_1846, EraseMode_ErasesXmpAfterConversion_1846) {
    Exiv2::Converter converter(exifData_, xmpData_);
    converter.setErase(true);

    xmpData_["Xmp.xmp.CreateDate"] = "2023-06-15T10:30:45";

    converter.cnvXmpDate("Xmp.xmp.CreateDate", "Exif.Image.DateTime");

#ifdef EXV_HAVE_XMP_TOOLKIT
    auto xmpPos = xmpData_.findKey(Exiv2::XmpKey("Xmp.xmp.CreateDate"));
    EXPECT_EQ(xmpPos, xmpData_.end());
#endif
}

// Test: No erase mode - XMP data should remain after conversion
TEST_F(ConverterCnvXmpDateTest_1846, NoEraseMode_KeepsXmpAfterConversion_1846) {
    Exiv2::Converter converter(exifData_, xmpData_);
    converter.setErase(false);

    xmpData_["Xmp.xmp.CreateDate"] = "2023-06-15T10:30:45";

    converter.cnvXmpDate("Xmp.xmp.CreateDate", "Exif.Image.DateTime");

    auto xmpPos = xmpData_.findKey(Exiv2::XmpKey("Xmp.xmp.CreateDate"));
    EXPECT_NE(xmpPos, xmpData_.end());
}

// Test: When target already exists and overwrite is false, conversion should not overwrite
TEST_F(ConverterCnvXmpDateTest_1846, OverwriteFalse_DoesNotOverwriteExistingExif_1846) {
    Exiv2::Converter converter(exifData_, xmpData_);
    converter.setOverwrite(false);

    // Pre-populate exif target
    exifData_["Exif.Image.DateTime"] = "2020:01:01 00:00:00";

    xmpData_["Xmp.xmp.CreateDate"] = "2023-06-15T10:30:45";

    converter.cnvXmpDate("Xmp.xmp.CreateDate", "Exif.Image.DateTime");

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Image.DateTime"));
    ASSERT_NE(pos, exifData_.end());
    // Should still be the original value since overwrite is false
    EXPECT_EQ(pos->toString(), "2020:01:01 00:00:00");
}

// Test: When target already exists and overwrite is true, conversion should overwrite
TEST_F(ConverterCnvXmpDateTest_1846, OverwriteTrue_OverwritesExistingExif_1846) {
    Exiv2::Converter converter(exifData_, xmpData_);
    converter.setOverwrite(true);

    // Pre-populate exif target
    exifData_["Exif.Image.DateTime"] = "2020:01:01 00:00:00";

    xmpData_["Xmp.xmp.CreateDate"] = "2023-06-15T10:30:45";

    converter.cnvXmpDate("Xmp.xmp.CreateDate", "Exif.Image.DateTime");

#ifdef EXV_HAVE_XMP_TOOLKIT
    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Image.DateTime"));
    ASSERT_NE(pos, exifData_.end());
    std::string val = pos->toString();
    // Value should have been overwritten - should contain 2023
    EXPECT_NE(val.find("2023"), std::string::npos);
#endif
}

// Test: Invalid date string should not crash and should not add exif data
TEST_F(ConverterCnvXmpDateTest_1846, InvalidDateString_NoCrash_1846) {
    Exiv2::Converter converter(exifData_, xmpData_);

    xmpData_["Xmp.xmp.CreateDate"] = "not-a-valid-date";

    // Should not throw
    EXPECT_NO_THROW(converter.cnvXmpDate("Xmp.xmp.CreateDate", "Exif.Image.DateTime"));
}

// Test: Empty date string should not crash
TEST_F(ConverterCnvXmpDateTest_1846, EmptyDateString_NoCrash_1846) {
    Exiv2::Converter converter(exifData_, xmpData_);

    xmpData_["Xmp.xmp.CreateDate"] = "";

    EXPECT_NO_THROW(converter.cnvXmpDate("Xmp.xmp.CreateDate", "Exif.Image.DateTime"));
}

// Test: Date-only XMP value (no time component)
TEST_F(ConverterCnvXmpDateTest_1846, DateOnly_NoTimeComponent_1846) {
    Exiv2::Converter converter(exifData_, xmpData_);

    xmpData_["Xmp.xmp.CreateDate"] = "2023-06-15";

    EXPECT_NO_THROW(converter.cnvXmpDate("Xmp.xmp.CreateDate", "Exif.Image.DateTime"));

#ifdef EXV_HAVE_XMP_TOOLKIT
    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Image.DateTime"));
    EXPECT_NE(pos, exifData_.end());
#endif
}

// Test: GPS timestamp with nanoseconds
TEST_F(ConverterCnvXmpDateTest_1846, GPSTimeStampWithNanoseconds_1846) {
    Exiv2::Converter converter(exifData_, xmpData_);

    xmpData_["Xmp.xmp.CreateDate"] = "2023-06-15T10:30:45.500000000+00:00";

    converter.cnvXmpDate("Xmp.xmp.CreateDate", "Exif.GPSInfo.GPSTimeStamp");

#ifdef EXV_HAVE_XMP_TOOLKIT
    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSTimeStamp"));
    EXPECT_NE(pos, exifData_.end());
    if (pos != exifData_.end()) {
        std::string val = pos->toString();
        // Should contain rational values
        EXPECT_FALSE(val.empty());
    }
#endif
}

// Test: Date with timezone offset
TEST_F(ConverterCnvXmpDateTest_1846, DateWithTimezoneOffset_1846) {
    Exiv2::Converter converter(exifData_, xmpData_);

    xmpData_["Xmp.xmp.CreateDate"] = "2023-06-15T10:30:45+05:30";

    EXPECT_NO_THROW(converter.cnvXmpDate("Xmp.xmp.CreateDate", "Exif.Image.DateTime"));

#ifdef EXV_HAVE_XMP_TOOLKIT
    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Image.DateTime"));
    EXPECT_NE(pos, exifData_.end());
#endif
}

// Test: Date without nanoseconds should not set SubSecTime
TEST_F(ConverterCnvXmpDateTest_1846, DateWithoutNanoseconds_NoSubSecTime_1846) {
    Exiv2::Converter converter(exifData_, xmpData_);

    xmpData_["Xmp.xmp.CreateDate"] = "2023-06-15T10:30:45";

    converter.cnvXmpDate("Xmp.xmp.CreateDate", "Exif.Image.DateTime");

#ifdef EXV_HAVE_XMP_TOOLKIT
    auto subPos = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.SubSecTime"));
    EXPECT_EQ(subPos, exifData_.end());
#endif
}

// Test: erase() getter returns the set value
TEST_F(ConverterCnvXmpDateTest_1846, EraseGetterReturnsSetValue_1846) {
    Exiv2::Converter converter(exifData_, xmpData_);
    
    converter.setErase(true);
    EXPECT_TRUE(converter.erase());
    
    converter.setErase(false);
    EXPECT_FALSE(converter.erase());
}

// Test: GPS timestamp with zero second but nonzero nanoseconds
TEST_F(ConverterCnvXmpDateTest_1846, GPSTimeStampZeroSecondNonZeroNano_1846) {
    Exiv2::Converter converter(exifData_, xmpData_);

    // A date where second=0 but nanoSecond != 0
    xmpData_["Xmp.xmp.CreateDate"] = "2023-06-15T10:30:00.123456789+00:00";

    converter.cnvXmpDate("Xmp.xmp.CreateDate", "Exif.GPSInfo.GPSTimeStamp");

#ifdef EXV_HAVE_XMP_TOOLKIT
    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSTimeStamp"));
    EXPECT_NE(pos, exifData_.end());

    auto datePos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSDateStamp"));
    EXPECT_NE(datePos, exifData_.end());
#endif
}

// Test: Year-only date
TEST_F(ConverterCnvXmpDateTest_1846, YearOnlyDate_1846) {
    Exiv2::Converter converter(exifData_, xmpData_);

    xmpData_["Xmp.xmp.CreateDate"] = "2023";

    EXPECT_NO_THROW(converter.cnvXmpDate("Xmp.xmp.CreateDate", "Exif.Image.DateTime"));
}

// Test: UTC timezone (Z suffix)
TEST_F(ConverterCnvXmpDateTest_1846, UTCTimezone_1846) {
    Exiv2::Converter converter(exifData_, xmpData_);

    xmpData_["Xmp.xmp.CreateDate"] = "2023-06-15T10:30:45Z";

    EXPECT_NO_THROW(converter.cnvXmpDate("Xmp.xmp.CreateDate", "Exif.Image.DateTime"));

#ifdef EXV_HAVE_XMP_TOOLKIT
    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Image.DateTime"));
    EXPECT_NE(pos, exifData_.end());
#endif
}
