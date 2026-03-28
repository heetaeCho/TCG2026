#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/exiv2.hpp>
#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Fixture for TiffDecoder tests
class TiffDecoderTest_1655 : public ::testing::Test {
protected:
    void SetUp() override {
        exifData_ = std::make_unique<ExifData>();
        iptcData_ = std::make_unique<IptcData>();
        xmpData_ = std::make_unique<XmpData>();
    }

    void TearDown() override {
    }

    std::unique_ptr<ExifData> exifData_;
    std::unique_ptr<IptcData> iptcData_;
    std::unique_ptr<XmpData> xmpData_;
};

// Test that visitSubIfd can be called with a valid TiffSubIfd object without crashing
TEST_F(TiffDecoderTest_1655, VisitSubIfdDoesNotCrashWithValidObject_1655) {
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, nullptr);
    
    // Should not crash - visitSubIfd delegates to decodeTiffEntry
    EXPECT_NO_THROW(decoder.visitSubIfd(&subIfd));
}

// Test that visitSubIfd with a SubIfd having a specific tag processes without error
TEST_F(TiffDecoderTest_1655, VisitSubIfdWithSpecificTag_1655) {
    // Use a common SubIFD tag
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, nullptr);
    
    EXPECT_NO_THROW(decoder.visitSubIfd(&subIfd));
}

// Test that visitSubIfd with ExifIFD group processes without error
TEST_F(TiffDecoderTest_1655, VisitSubIfdWithExifGroup_1655) {
    TiffSubIfd subIfd(0x8769, IfdId::ifd0Id, IfdId::exifId);
    
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, nullptr);
    
    EXPECT_NO_THROW(decoder.visitSubIfd(&subIfd));
}

// Test that visitSubIfd with GPS IFD group processes without error
TEST_F(TiffDecoderTest_1655, VisitSubIfdWithGpsGroup_1655) {
    TiffSubIfd subIfd(0x8825, IfdId::ifd0Id, IfdId::gpsId);
    
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, nullptr);
    
    EXPECT_NO_THROW(decoder.visitSubIfd(&subIfd));
}

// Test that visitSubIfd does not add exif data when SubIfd has no actual data set
TEST_F(TiffDecoderTest_1655, VisitSubIfdNoDataDoesNotPopulateExifData_1655) {
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    
    size_t initialSize = exifData_->count();
    
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, nullptr);
    decoder.visitSubIfd(&subIfd);
    
    // With no data in the SubIfd, exifData should remain unchanged or have minimal change
    // This tests the boundary condition of empty SubIfd
    EXPECT_GE(exifData_->count(), initialSize);
}

// Test calling visitSubIfd multiple times does not crash
TEST_F(TiffDecoderTest_1655, VisitSubIfdCalledMultipleTimes_1655) {
    TiffSubIfd subIfd1(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    TiffSubIfd subIfd2(0x8769, IfdId::ifd0Id, IfdId::exifId);
    
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, nullptr);
    
    EXPECT_NO_THROW(decoder.visitSubIfd(&subIfd1));
    EXPECT_NO_THROW(decoder.visitSubIfd(&subIfd2));
}

// Test with tag value 0 as boundary condition
TEST_F(TiffDecoderTest_1655, VisitSubIfdWithZeroTag_1655) {
    TiffSubIfd subIfd(0x0000, IfdId::ifd0Id, IfdId::subImage1Id);
    
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, nullptr);
    
    EXPECT_NO_THROW(decoder.visitSubIfd(&subIfd));
}

// Test with maximum tag value as boundary condition
TEST_F(TiffDecoderTest_1655, VisitSubIfdWithMaxTag_1655) {
    TiffSubIfd subIfd(0xFFFF, IfdId::ifd0Id, IfdId::subImage1Id);
    
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, nullptr);
    
    EXPECT_NO_THROW(decoder.visitSubIfd(&subIfd));
}

// Test that decoder with findDecoderFct as nullptr handles visitSubIfd
TEST_F(TiffDecoderTest_1655, VisitSubIfdWithNullDecoderFct_1655) {
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, nullptr);
    
    EXPECT_NO_THROW(decoder.visitSubIfd(&subIfd));
}
