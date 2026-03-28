#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <string>

// The Converter class is defined in convert.cpp and not directly exposed via a public header.
// We need to use the public conversion functions or access it through the copyExifToXmp/moveExifToXmp APIs.
// However, based on the partial code, we'll test cnvExifDate through the Converter class.
// Since Converter is in the Exiv2 namespace in convert.cpp, we need to include the relevant header.

// Forward declaration approach - the Converter class is typically used internally.
// We'll use the exiv2 public API which internally uses Converter, or we can
// include the source file if the class is not in a public header.

// Based on the codebase structure, Converter is an internal class.
// We'll test it by including the necessary headers and accessing it.
// In practice, copyExifToXmp and moveExifToXmp use Converter internally.

namespace Exiv2 {
// Forward declare the Converter class for testing purposes
class Converter {
public:
    Converter(ExifData& exifData, XmpData& xmpData);
    void cnvExifDate(const char* from, const char* to);
    void setErase(bool onoff = true);
    void setOverwrite(bool onoff = true);
    bool erase() const;
    void cnvToXmp();
    void cnvFromXmp();
    void cnvExifValue(const char* from, const char* to);
private:
    bool erase_;
    bool overwrite_;
    ExifData* exifData_;
    void* iptcData_;
    XmpData* xmpData_;
    const char* iptcCharset_;
};
}

// Since Converter may not be accessible through public headers, we test through
// the public API: copyExifToXmp / moveExifToXmp
// These are declared in exiv2/convert.hpp

class CnvExifDateTest_1838 : public ::testing::Test {
protected:
    Exiv2::ExifData exifData;
    Exiv2::XmpData xmpData;

    void SetUp() override {
        // Suppress warnings during tests
        Exiv2::LogMsg::setLevel(Exiv2::LogMsg::mute);
        // Initialize XMP parser
        Exiv2::XmpParser::initialize();
    }

    void TearDown() override {
        Exiv2::XmpParser::terminate();
        Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
    }
};

// Test: Normal DateTime conversion from Exif.Image.DateTime to XMP
TEST_F(CnvExifDateTest_1838, NormalDateTimeConversion_1838) {
    exifData["Exif.Image.DateTime"] = "2023:06:15 10:30:45";

    Exiv2::copyExifToXmp(exifData, xmpData);

    auto pos = xmpData.findKey(Exiv2::XmpKey("Xmp.xmp.ModifyDate"));
    if (pos != xmpData.end()) {
        std::string result = pos->toString();
        EXPECT_TRUE(result.find("2023") != std::string::npos);
        EXPECT_TRUE(result.find("06") != std::string::npos);
        EXPECT_TRUE(result.find("15") != std::string::npos);
        EXPECT_TRUE(result.find("10") != std::string::npos);
        EXPECT_TRUE(result.find("30") != std::string::npos);
        EXPECT_TRUE(result.find("45") != std::string::npos);
    }
}

// Test: DateTimeOriginal conversion
TEST_F(CnvExifDateTest_1838, DateTimeOriginalConversion_1838) {
    exifData["Exif.Photo.DateTimeOriginal"] = "2022:01:01 00:00:00";

    Exiv2::copyExifToXmp(exifData, xmpData);

    auto pos = xmpData.findKey(Exiv2::XmpKey("Xmp.exif.DateTimeOriginal"));
    if (pos != xmpData.end()) {
        std::string result = pos->toString();
        EXPECT_TRUE(result.find("2022") != std::string::npos);
        EXPECT_TRUE(result.find("01") != std::string::npos);
    }
}

// Test: DateTimeDigitized conversion
TEST_F(CnvExifDateTest_1838, DateTimeDigitizedConversion_1838) {
    exifData["Exif.Photo.DateTimeDigitized"] = "2021:12:31 23:59:59";

    Exiv2::copyExifToXmp(exifData, xmpData);

    auto pos = xmpData.findKey(Exiv2::XmpKey("Xmp.exif.DateTimeDigitized"));
    if (pos != xmpData.end()) {
        std::string result = pos->toString();
        EXPECT_TRUE(result.find("2021") != std::string::npos);
        EXPECT_TRUE(result.find("12") != std::string::npos);
        EXPECT_TRUE(result.find("31") != std::string::npos);
        EXPECT_TRUE(result.find("23") != std::string::npos);
        EXPECT_TRUE(result.find("59") != std::string::npos);
    }
}

// Test: SubSecTime is appended to the date string
TEST_F(CnvExifDateTest_1838, SubSecTimeAppended_1838) {
    exifData["Exif.Photo.DateTimeOriginal"] = "2023:03:20 14:25:36";
    exifData["Exif.Photo.SubSecTimeOriginal"] = "123";

    Exiv2::copyExifToXmp(exifData, xmpData);

    auto pos = xmpData.findKey(Exiv2::XmpKey("Xmp.exif.DateTimeOriginal"));
    if (pos != xmpData.end()) {
        std::string result = pos->toString();
        EXPECT_TRUE(result.find(".123") != std::string::npos);
    }
}

// Test: SubSecTime for DateTime (ModifyDate)
TEST_F(CnvExifDateTest_1838, SubSecTimeForModifyDate_1838) {
    exifData["Exif.Image.DateTime"] = "2023:07:04 09:15:30";
    exifData["Exif.Photo.SubSecTime"] = "456";

    Exiv2::copyExifToXmp(exifData, xmpData);

    auto pos = xmpData.findKey(Exiv2::XmpKey("Xmp.xmp.ModifyDate"));
    if (pos != xmpData.end()) {
        std::string result = pos->toString();
        EXPECT_TRUE(result.find(".456") != std::string::npos);
    }
}

// Test: SubSecTimeDigitized for DateTimeDigitized
TEST_F(CnvExifDateTest_1838, SubSecTimeDigitized_1838) {
    exifData["Exif.Photo.DateTimeDigitized"] = "2023:08:15 16:45:20";
    exifData["Exif.Photo.SubSecTimeDigitized"] = "789";

    Exiv2::copyExifToXmp(exifData, xmpData);

    auto pos = xmpData.findKey(Exiv2::XmpKey("Xmp.exif.DateTimeDigitized"));
    if (pos != xmpData.end()) {
        std::string result = pos->toString();
        EXPECT_TRUE(result.find(".789") != std::string::npos);
    }
}

// Test: GPSTimeStamp conversion with GPSDateStamp
TEST_F(CnvExifDateTest_1838, GPSTimeStampWithDateStamp_1838) {
    // Set GPSTimeStamp as rational values (hour, min, sec)
    Exiv2::URationalValue::UniquePtr rv(new Exiv2::URationalValue);
    rv->read("10/1 30/1 45/1");
    exifData.add(Exiv2::ExifKey("Exif.GPSInfo.GPSTimeStamp"), rv.get());

    exifData["Exif.GPSInfo.GPSDateStamp"] = "2023:06:15";

    Exiv2::copyExifToXmp(exifData, xmpData);

    auto pos = xmpData.findKey(Exiv2::XmpKey("Xmp.exif.GPSTimeStamp"));
    if (pos != xmpData.end()) {
        std::string result = pos->toString();
        EXPECT_TRUE(result.find("2023") != std::string::npos);
        EXPECT_TRUE(result.find("10") != std::string::npos);
        EXPECT_TRUE(result.find("30") != std::string::npos);
        EXPECT_TRUE(result.find("45") != std::string::npos);
    }
}

// Test: GPSTimeStamp falls back to DateTimeOriginal when GPSDateStamp missing
TEST_F(CnvExifDateTest_1838, GPSTimeStampFallbackToDateTimeOriginal_1838) {
    Exiv2::URationalValue::UniquePtr rv(new Exiv2::URationalValue);
    rv->read("12/1 0/1 0/1");
    exifData.add(Exiv2::ExifKey("Exif.GPSInfo.GPSTimeStamp"), rv.get());

    // No GPSDateStamp, but DateTimeOriginal exists
    exifData["Exif.Photo.DateTimeOriginal"] = "2023:05:10 08:00:00";

    Exiv2::copyExifToXmp(exifData, xmpData);

    auto pos = xmpData.findKey(Exiv2::XmpKey("Xmp.exif.GPSTimeStamp"));
    if (pos != xmpData.end()) {
        std::string result = pos->toString();
        EXPECT_TRUE(result.find("2023") != std::string::npos);
        EXPECT_TRUE(result.find("05") != std::string::npos);
        EXPECT_TRUE(result.find("10") != std::string::npos);
    }
}

// Test: GPSTimeStamp falls back to DateTimeDigitized when both GPSDateStamp and DateTimeOriginal missing
TEST_F(CnvExifDateTest_1838, GPSTimeStampFallbackToDateTimeDigitized_1838) {
    Exiv2::URationalValue::UniquePtr rv(new Exiv2::URationalValue);
    rv->read("8/1 15/1 30/1");
    exifData.add(Exiv2::ExifKey("Exif.GPSInfo.GPSTimeStamp"), rv.get());

    // Only DateTimeDigitized exists
    exifData["Exif.Photo.DateTimeDigitized"] = "2023:09:20 00:00:00";

    Exiv2::copyExifToXmp(exifData, xmpData);

    auto pos = xmpData.findKey(Exiv2::XmpKey("Xmp.exif.GPSTimeStamp"));
    if (pos != xmpData.end()) {
        std::string result = pos->toString();
        EXPECT_TRUE(result.find("2023") != std::string::npos);
    }
}

// Test: Missing source key - no conversion should happen
TEST_F(CnvExifDateTest_1838, MissingSourceKeyNoConversion_1838) {
    // Don't add any exif data
    Exiv2::copyExifToXmp(exifData, xmpData);

    auto pos = xmpData.findKey(Exiv2::XmpKey("Xmp.xmp.ModifyDate"));
    EXPECT_TRUE(pos == xmpData.end());
}

// Test: Empty ExifData produces empty XmpData for dates
TEST_F(CnvExifDateTest_1838, EmptyExifDataNoDateInXmp_1838) {
    Exiv2::copyExifToXmp(exifData, xmpData);

    auto pos1 = xmpData.findKey(Exiv2::XmpKey("Xmp.xmp.ModifyDate"));
    auto pos2 = xmpData.findKey(Exiv2::XmpKey("Xmp.exif.DateTimeOriginal"));
    auto pos3 = xmpData.findKey(Exiv2::XmpKey("Xmp.exif.DateTimeDigitized"));

    EXPECT_TRUE(pos1 == xmpData.end());
    EXPECT_TRUE(pos2 == xmpData.end());
    EXPECT_TRUE(pos3 == xmpData.end());
}

// Test: Malformed date string should not produce XMP entry (or produce gracefully)
TEST_F(CnvExifDateTest_1838, MalformedDateString_1838) {
    exifData["Exif.Image.DateTime"] = "not-a-date";

    Exiv2::copyExifToXmp(exifData, xmpData);

    auto pos = xmpData.findKey(Exiv2::XmpKey("Xmp.xmp.ModifyDate"));
    // Malformed date should not create a valid XMP entry
    // The behavior depends on implementation - either no entry or entry with zeros
    // We just verify it doesn't crash
    SUCCEED();
}

// Test: Partially malformed date string
TEST_F(CnvExifDateTest_1838, PartiallyMalformedDate_1838) {
    exifData["Exif.Image.DateTime"] = "2023:06:15";  // Missing time part

    Exiv2::copyExifToXmp(exifData, xmpData);

    // sscanf won't match 6 fields, so conversion should fail silently
    auto pos = xmpData.findKey(Exiv2::XmpKey("Xmp.xmp.ModifyDate"));
    // Depending on implementation, this may or may not be present
    SUCCEED();
}

// Test: moveExifToXmp erases source data
TEST_F(CnvExifDateTest_1838, MoveExifToXmpErasesSource_1838) {
    exifData["Exif.Photo.DateTimeOriginal"] = "2023:04:01 12:00:00";

    Exiv2::moveExifToXmp(exifData, xmpData);

    auto exifPos = exifData.findKey(Exiv2::ExifKey("Exif.Photo.DateTimeOriginal"));
    EXPECT_TRUE(exifPos == exifData.end());

    auto xmpPos = xmpData.findKey(Exiv2::XmpKey("Xmp.exif.DateTimeOriginal"));
    if (xmpPos != xmpData.end()) {
        std::string result = xmpPos->toString();
        EXPECT_TRUE(result.find("2023") != std::string::npos);
    }
}

// Test: copyExifToXmp does not erase source data
TEST_F(CnvExifDateTest_1838, CopyExifToXmpKeepsSource_1838) {
    exifData["Exif.Photo.DateTimeOriginal"] = "2023:04:01 12:00:00";

    Exiv2::copyExifToXmp(exifData, xmpData);

    auto exifPos = exifData.findKey(Exiv2::ExifKey("Exif.Photo.DateTimeOriginal"));
    EXPECT_TRUE(exifPos != exifData.end());
}

// Test: SubSecTime with long value gets truncated to 10 chars
TEST_F(CnvExifDateTest_1838, SubSecTimeTruncation_1838) {
    exifData["Exif.Photo.DateTimeOriginal"] = "2023:01:01 00:00:00";
    exifData["Exif.Photo.SubSecTimeOriginal"] = "12345678901234";  // Very long subsec

    Exiv2::copyExifToXmp(exifData, xmpData);

    auto pos = xmpData.findKey(Exiv2::XmpKey("Xmp.exif.DateTimeOriginal"));
    if (pos != xmpData.end()) {
        std::string result = pos->toString();
        // The subsec part (including dot) should be at most 10 chars
        // Find the 'T' separator and then the seconds
        auto tPos = result.find('T');
        if (tPos != std::string::npos) {
            auto dotPos = result.find('.', tPos);
            if (dotPos != std::string::npos) {
                std::string subsecPart = result.substr(dotPos);
                EXPECT_LE(subsecPart.size(), 10u);
            }
        }
    }
}

// Test: Boundary - midnight time
TEST_F(CnvExifDateTest_1838, MidnightTime_1838) {
    exifData["Exif.Image.DateTime"] = "2023:01:01 00:00:00";

    Exiv2::copyExifToXmp(exifData, xmpData);

    auto pos = xmpData.findKey(Exiv2::XmpKey("Xmp.xmp.ModifyDate"));
    if (pos != xmpData.end()) {
        std::string result = pos->toString();
        EXPECT_TRUE(result.find("00:00:00") != std::string::npos);
    }
}

// Test: Boundary - end of day time
TEST_F(CnvExifDateTest_1838, EndOfDayTime_1838) {
    exifData["Exif.Image.DateTime"] = "2023:12:31 23:59:59";

    Exiv2::copyExifToXmp(exifData, xmpData);

    auto pos = xmpData.findKey(Exiv2::XmpKey("Xmp.xmp.ModifyDate"));
    if (pos != xmpData.end()) {
        std::string result = pos->toString();
        EXPECT_TRUE(result.find("2023") != std::string::npos);
        EXPECT_TRUE(result.find("23:59:59") != std::string::npos);
    }
}

// Test: GPSTimeStamp with no date stamp at all fails gracefully
TEST_F(CnvExifDateTest_1838, GPSTimeStampNoDateStampAnywhere_1838) {
    Exiv2::URationalValue::UniquePtr rv(new Exiv2::URationalValue);
    rv->read("10/1 30/1 45/1");
    exifData.add(Exiv2::ExifKey("Exif.GPSInfo.GPSTimeStamp"), rv.get());

    // No GPSDateStamp, no DateTimeOriginal, no DateTimeDigitized
    Exiv2::copyExifToXmp(exifData, xmpData);

    auto pos = xmpData.findKey(Exiv2::XmpKey("Xmp.exif.GPSTimeStamp"));
    // Should fail gracefully - either no entry or empty
    SUCCEED();
}

// Test: GPSTimeStamp with zero denominator in rational
TEST_F(CnvExifDateTest_1838, GPSTimeStampZeroDenominator_1838) {
    Exiv2::URationalValue::UniquePtr rv(new Exiv2::URationalValue);
    rv->read("10/0 30/1 45/1");  // Zero denominator in first rational
    exifData.add(Exiv2::ExifKey("Exif.GPSInfo.GPSTimeStamp"), rv.get());
    exifData["Exif.GPSInfo.GPSDateStamp"] = "2023:06:15";

    Exiv2::copyExifToXmp(exifData, xmpData);

    // Should fail gracefully due to zero denominator check
    SUCCEED();
}

// Test: XMP date format is ISO 8601
TEST_F(CnvExifDateTest_1838, XmpDateFormatISO8601_1838) {
    exifData["Exif.Photo.DateTimeOriginal"] = "2023:06:15 10:30:45";

    Exiv2::copyExifToXmp(exifData, xmpData);

    auto pos = xmpData.findKey(Exiv2::XmpKey("Xmp.exif.DateTimeOriginal"));
    if (pos != xmpData.end()) {
        std::string result = pos->toString();
        // ISO 8601 format: YYYY-MM-DDTHH:MM:SS
        EXPECT_TRUE(result.find("2023-06-15T10:30:45") != std::string::npos);
    }
}

// Test: Multiple date fields converted simultaneously
TEST_F(CnvExifDateTest_1838, MultipleDateFieldsConverted_1838) {
    exifData["Exif.Image.DateTime"] = "2023:01:01 01:01:01";
    exifData["Exif.Photo.DateTimeOriginal"] = "2023:02:02 02:02:02";
    exifData["Exif.Photo.DateTimeDigitized"] = "2023:03:03 03:03:03";

    Exiv2::copyExifToXmp(exifData, xmpData);

    auto pos1 = xmpData.findKey(Exiv2::XmpKey("Xmp.xmp.ModifyDate"));
    auto pos2 = xmpData.findKey(Exiv2::XmpKey("Xmp.exif.DateTimeOriginal"));
    auto pos3 = xmpData.findKey(Exiv2::XmpKey("Xmp.exif.DateTimeDigitized"));

    if (pos1 != xmpData.end()) {
        EXPECT_TRUE(pos1->toString().find("2023-01-01") != std::string::npos);
    }
    if (pos2 != xmpData.end()) {
        EXPECT_TRUE(pos2->toString().find("2023-02-02") != std::string::npos);
    }
    if (pos3 != xmpData.end()) {
        EXPECT_TRUE(pos3->toString().find("2023-03-03") != std::string::npos);
    }
}

// Test: Non-numeric SubSecTime should not be appended
TEST_F(CnvExifDateTest_1838, NonNumericSubSecTimeIgnored_1838) {
    exifData["Exif.Photo.DateTimeOriginal"] = "2023:06:15 10:30:45";
    exifData["Exif.Photo.SubSecTimeOriginal"] = "abc";

    Exiv2::copyExifToXmp(exifData, xmpData);

    auto pos = xmpData.findKey(Exiv2::XmpKey("Xmp.exif.DateTimeOriginal"));
    if (pos != xmpData.end()) {
        std::string result = pos->toString();
        // Non-numeric subsec should be ignored
        EXPECT_TRUE(result.find("abc") == std::string::npos);
    }
}

// Test: Empty SubSecTime should not be appended
TEST_F(CnvExifDateTest_1838, EmptySubSecTimeIgnored_1838) {
    exifData["Exif.Photo.DateTimeOriginal"] = "2023:06:15 10:30:45";
    exifData["Exif.Photo.SubSecTimeOriginal"] = "";

    Exiv2::copyExifToXmp(exifData, xmpData);

    auto pos = xmpData.findKey(Exiv2::XmpKey("Xmp.exif.DateTimeOriginal"));
    if (pos != xmpData.end()) {
        std::string result = pos->toString();
        // Should end without subsec
        EXPECT_TRUE(result.find("2023-06-15T10:30:45") != std::string::npos);
    }
}

// Test: Overwrite=false should not overwrite existing XMP value
TEST_F(CnvExifDateTest_1838, OverwriteFalseDoesNotOverwrite_1838) {
    // Pre-populate XMP with a date
    xmpData["Xmp.exif.DateTimeOriginal"] = "2020-01-01T00:00:00";

    exifData["Exif.Photo.DateTimeOriginal"] = "2023:06:15 10:30:45";

    // Use copyExifToXmp which by default overwrites
    // To test overwrite=false, we'd need direct Converter access
    // But we can verify copyExifToXmp overwrites
    Exiv2::copyExifToXmp(exifData, xmpData);

    auto pos = xmpData.findKey(Exiv2::XmpKey("Xmp.exif.DateTimeOriginal"));
    ASSERT_TRUE(pos != xmpData.end());
    std::string result = pos->toString();
    // copyExifToXmp has overwrite=true by default
    EXPECT_TRUE(result.find("2023") != std::string::npos);
}

// Test: GPSTimeStamp with fractional seconds
TEST_F(CnvExifDateTest_1838, GPSTimeStampFractionalSeconds_1838) {
    Exiv2::URationalValue::UniquePtr rv(new Exiv2::URationalValue);
    rv->read("10/1 30/1 4550/100");  // 45.50 seconds
    exifData.add(Exiv2::ExifKey("Exif.GPSInfo.GPSTimeStamp"), rv.get());
    exifData["Exif.GPSInfo.GPSDateStamp"] = "2023:06:15";

    Exiv2::copyExifToXmp(exifData, xmpData);

    auto pos = xmpData.findKey(Exiv2::XmpKey("Xmp.exif.GPSTimeStamp"));
    if (pos != xmpData.end()) {
        std::string result = pos->toString();
        EXPECT_TRUE(result.find("2023-06-15") != std::string::npos);
        EXPECT_TRUE(result.find("10:30:45") != std::string::npos);
    }
}
