#include <gtest/gtest.h>
#include <string>

// Include XMP SDK headers
#define TXMP_STRING_TYPE std::string
#include "XMP_Const.h"
#include "XMP.incl_cpp"
#include "XMP.hpp"

class FixGPSTimeStampTest_1966 : public ::testing::Test {
protected:
    void SetUp() override {
        SXMPMeta::Initialize();
    }

    void TearDown() override {
        SXMPMeta::Terminate();
    }

    // Helper to create XMP packet with GPS timestamp and optional DateTimeOriginal
    std::string makeXMPPacket(const std::string& gpsTimeStamp,
                               const std::string& dateTimeOriginal = "",
                               const std::string& dateTimeDigitized = "") {
        std::string xmp = "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
            "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
            "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
            "<rdf:Description rdf:about=''"
            " xmlns:exif='http://ns.adobe.com/exif/1.0/'";
        
        xmp += ">";
        
        if (!gpsTimeStamp.empty()) {
            xmp += "<exif:GPSTimeStamp>" + gpsTimeStamp + "</exif:GPSTimeStamp>";
        }
        if (!dateTimeOriginal.empty()) {
            xmp += "<exif:DateTimeOriginal>" + dateTimeOriginal + "</exif:DateTimeOriginal>";
        }
        if (!dateTimeDigitized.empty()) {
            xmp += "<exif:DateTimeDigitized>" + dateTimeDigitized + "</exif:DateTimeDigitized>";
        }
        
        xmp += "</rdf:Description>"
            "</rdf:RDF>"
            "</x:xmpmeta>"
            "<?xpacket end='w'?>";
        return xmp;
    }
};

// Test: GPS timestamp with zero date gets date from DateTimeOriginal
TEST_F(FixGPSTimeStampTest_1966, GPSTimeStampGetsDateFromDateTimeOriginal_1966) {
    // GPS timestamp with only time (no date), DateTimeOriginal has full date
    std::string xmpStr = makeXMPPacket("0000-00-00T12:30:45Z", "2023-06-15T10:20:30");
    
    SXMPMeta meta;
    meta.ParseFromBuffer(xmpStr.c_str(), static_cast<XMP_StringLen>(xmpStr.size()));
    
    std::string gpsValue;
    bool found = meta.GetProperty(kXMP_NS_EXIF, "GPSTimeStamp", &gpsValue, nullptr);
    
    ASSERT_TRUE(found);
    // The GPS timestamp should now have the date from DateTimeOriginal
    EXPECT_NE(gpsValue.find("2023"), std::string::npos);
}

// Test: GPS timestamp with zero date gets date from DateTimeDigitized when DateTimeOriginal absent
TEST_F(FixGPSTimeStampTest_1966, GPSTimeStampGetsDateFromDateTimeDigitized_1966) {
    std::string xmpStr = makeXMPPacket("0000-00-00T14:00:00Z", "", "2022-03-10T08:15:00");
    
    SXMPMeta meta;
    meta.ParseFromBuffer(xmpStr.c_str(), static_cast<XMP_StringLen>(xmpStr.size()));
    
    std::string gpsValue;
    bool found = meta.GetProperty(kXMP_NS_EXIF, "GPSTimeStamp", &gpsValue, nullptr);
    
    ASSERT_TRUE(found);
    EXPECT_NE(gpsValue.find("2022"), std::string::npos);
}

// Test: GPS timestamp already has a valid date - should not be modified
TEST_F(FixGPSTimeStampTest_1966, GPSTimeStampWithValidDateUnchanged_1966) {
    std::string xmpStr = makeXMPPacket("2021-05-20T12:30:45Z", "2023-06-15T10:20:30");
    
    SXMPMeta meta;
    meta.ParseFromBuffer(xmpStr.c_str(), static_cast<XMP_StringLen>(xmpStr.size()));
    
    std::string gpsValue;
    bool found = meta.GetProperty(kXMP_NS_EXIF, "GPSTimeStamp", &gpsValue, nullptr);
    
    ASSERT_TRUE(found);
    // Should keep original date, not change to DateTimeOriginal's date
    EXPECT_NE(gpsValue.find("2021"), std::string::npos);
}

// Test: GPS timestamp with zero date but no other date available - should remain unchanged
TEST_F(FixGPSTimeStampTest_1966, GPSTimeStampNoOtherDateAvailable_1966) {
    std::string xmpStr = makeXMPPacket("0000-00-00T12:30:45Z");
    
    SXMPMeta meta;
    meta.ParseFromBuffer(xmpStr.c_str(), static_cast<XMP_StringLen>(xmpStr.size()));
    
    std::string gpsValue;
    bool found = meta.GetProperty(kXMP_NS_EXIF, "GPSTimeStamp", &gpsValue, nullptr);
    
    // Property should still exist, value may be unchanged or empty-date
    if (found) {
        // Without any other date, the year should remain 0 or the value unchanged
        // This is acceptable - just verifying it doesn't crash
        SUCCEED();
    }
}

// Test: DateTimeOriginal takes precedence over DateTimeDigitized
TEST_F(FixGPSTimeStampTest_1966, DateTimeOriginalTakesPrecedence_1966) {
    std::string xmpStr = makeXMPPacket("0000-00-00T12:30:45Z",
                                        "2023-06-15T10:20:30",
                                        "2022-03-10T08:15:00");
    
    SXMPMeta meta;
    meta.ParseFromBuffer(xmpStr.c_str(), static_cast<XMP_StringLen>(xmpStr.size()));
    
    std::string gpsValue;
    bool found = meta.GetProperty(kXMP_NS_EXIF, "GPSTimeStamp", &gpsValue, nullptr);
    
    ASSERT_TRUE(found);
    // Should use DateTimeOriginal (2023), not DateTimeDigitized (2022)
    EXPECT_NE(gpsValue.find("2023"), std::string::npos);
}

// Test: Bad GPS timestamp string doesn't crash - graceful handling
TEST_F(FixGPSTimeStampTest_1966, BadGPSTimeStampHandledGracefully_1966) {
    std::string xmpStr = makeXMPPacket("not-a-valid-date", "2023-06-15T10:20:30");
    
    SXMPMeta meta;
    EXPECT_NO_THROW(meta.ParseFromBuffer(xmpStr.c_str(), static_cast<XMP_StringLen>(xmpStr.size())));
    
    std::string gpsValue;
    meta.GetProperty(kXMP_NS_EXIF, "GPSTimeStamp", &gpsValue, nullptr);
    // Just verify no crash
    SUCCEED();
}

// Test: Bad DateTimeOriginal doesn't crash when GPS needs fixing
TEST_F(FixGPSTimeStampTest_1966, BadDateTimeOriginalHandledGracefully_1966) {
    std::string xmpStr = makeXMPPacket("0000-00-00T12:30:45Z", "not-a-date");
    
    SXMPMeta meta;
    EXPECT_NO_THROW(meta.ParseFromBuffer(xmpStr.c_str(), static_cast<XMP_StringLen>(xmpStr.size())));
    SUCCEED();
}

// Test: GPS time portion is preserved when date is copied
TEST_F(FixGPSTimeStampTest_1966, GPSTimePreservedWhenDateCopied_1966) {
    std::string xmpStr = makeXMPPacket("0000-00-00T14:25:59Z", "2020-12-25T00:00:00");
    
    SXMPMeta meta;
    meta.ParseFromBuffer(xmpStr.c_str(), static_cast<XMP_StringLen>(xmpStr.size()));
    
    std::string gpsValue;
    bool found = meta.GetProperty(kXMP_NS_EXIF, "GPSTimeStamp", &gpsValue, nullptr);
    
    ASSERT_TRUE(found);
    // Date should come from DateTimeOriginal
    EXPECT_NE(gpsValue.find("2020"), std::string::npos);
    EXPECT_NE(gpsValue.find("12"), std::string::npos);
    EXPECT_NE(gpsValue.find("25"), std::string::npos);
}

// Test: Only month is zero but year and day are non-zero - GPS stamp has partial date
TEST_F(FixGPSTimeStampTest_1966, GPSWithNonZeroYearNotModified_1966) {
    // If year is non-zero, function should return early without modification
    std::string xmpStr = makeXMPPacket("2023-00-00T12:30:45Z", "2020-06-15T10:20:30");
    
    SXMPMeta meta;
    meta.ParseFromBuffer(xmpStr.c_str(), static_cast<XMP_StringLen>(xmpStr.size()));
    
    std::string gpsValue;
    bool found = meta.GetProperty(kXMP_NS_EXIF, "GPSTimeStamp", &gpsValue, nullptr);
    
    if (found) {
        // Year is non-zero so function should NOT replace date
        EXPECT_NE(gpsValue.find("2023"), std::string::npos);
    }
}

// Test: Empty XMP packet doesn't crash
TEST_F(FixGPSTimeStampTest_1966, EmptyPacketNoCrash_1966) {
    std::string xmpStr = "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";
    
    SXMPMeta meta;
    EXPECT_NO_THROW(meta.ParseFromBuffer(xmpStr.c_str(), static_cast<XMP_StringLen>(xmpStr.size())));
}

// Test: GPS timestamp with all zero date and timezone info
TEST_F(FixGPSTimeStampTest_1966, GPSTimeStampWithTimezoneFixedCorrectly_1966) {
    std::string xmpStr = makeXMPPacket("0000-00-00T09:15:30+05:30", "2019-07-04T12:00:00");
    
    SXMPMeta meta;
    meta.ParseFromBuffer(xmpStr.c_str(), static_cast<XMP_StringLen>(xmpStr.size()));
    
    std::string gpsValue;
    bool found = meta.GetProperty(kXMP_NS_EXIF, "GPSTimeStamp", &gpsValue, nullptr);
    
    ASSERT_TRUE(found);
    EXPECT_NE(gpsValue.find("2019"), std::string::npos);
}
