#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "exiv2/exiv2.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper function type for FindDecoderFct
static DecoderFct findStdDecoder(const std::string& make,
                                  uint32_t tag,
                                  IfdId group) {
    return nullptr;
}

class TiffDecoderVisitSizeEntryTest_1654 : public ::testing::Test {
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

// Test that visitSizeEntry can be called with a valid TiffSizeEntry without crashing
TEST_F(TiffDecoderVisitSizeEntryTest_1654, VisitSizeEntryDoesNotCrash_1654) {
    TiffSizeEntry sizeEntry(0x0100, IfdId::ifd0Id, 0x0101, IfdId::ifd0Id);
    
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, findStdDecoder);
    
    // Should not crash - visitSizeEntry delegates to decodeTiffEntry
    EXPECT_NO_THROW(decoder.visitSizeEntry(&sizeEntry));
}

// Test visitSizeEntry with different tag/group combinations
TEST_F(TiffDecoderVisitSizeEntryTest_1654, VisitSizeEntryDifferentTags_1654) {
    TiffSizeEntry sizeEntry(0x0202, IfdId::ifd1Id, 0x0201, IfdId::ifd1Id);
    
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, findStdDecoder);
    
    EXPECT_NO_THROW(decoder.visitSizeEntry(&sizeEntry));
}

// Test that TiffSizeEntry correctly returns dtTag and dtGroup
TEST_F(TiffDecoderVisitSizeEntryTest_1654, SizeEntryAccessors_1654) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::ifd0Id;
    uint16_t dtTag = 0x0101;
    IfdId dtGroup = IfdId::ifd1Id;
    
    TiffSizeEntry sizeEntry(tag, group, dtTag, dtGroup);
    
    EXPECT_EQ(sizeEntry.dtTag(), dtTag);
    EXPECT_EQ(sizeEntry.dtGroup(), dtGroup);
}

// Test visitSizeEntry with a TiffSizeEntry having zero tags
TEST_F(TiffDecoderVisitSizeEntryTest_1654, VisitSizeEntryZeroTags_1654) {
    TiffSizeEntry sizeEntry(0x0000, IfdId::ifd0Id, 0x0000, IfdId::ifd0Id);
    
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, findStdDecoder);
    
    EXPECT_NO_THROW(decoder.visitSizeEntry(&sizeEntry));
}

// Test that visitSizeEntry with a custom findDecoderFct works
static DecoderFct customFindDecoder(const std::string& make,
                                     uint32_t tag,
                                     IfdId group) {
    // Return a specific decoder function or nullptr
    return nullptr;
}

TEST_F(TiffDecoderVisitSizeEntryTest_1654, VisitSizeEntryCustomDecoder_1654) {
    TiffSizeEntry sizeEntry(0x0100, IfdId::ifd0Id, 0x0101, IfdId::ifd0Id);
    
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, customFindDecoder);
    
    EXPECT_NO_THROW(decoder.visitSizeEntry(&sizeEntry));
}

// Test that visitSizeEntry with maximum uint16_t tag values
TEST_F(TiffDecoderVisitSizeEntryTest_1654, VisitSizeEntryMaxTagValues_1654) {
    TiffSizeEntry sizeEntry(0xFFFF, IfdId::ifd0Id, 0xFFFF, IfdId::ifd0Id);
    
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, findStdDecoder);
    
    EXPECT_NO_THROW(decoder.visitSizeEntry(&sizeEntry));
}

// Test multiple calls to visitSizeEntry
TEST_F(TiffDecoderVisitSizeEntryTest_1654, VisitSizeEntryMultipleCalls_1654) {
    TiffSizeEntry sizeEntry1(0x0100, IfdId::ifd0Id, 0x0101, IfdId::ifd0Id);
    TiffSizeEntry sizeEntry2(0x0200, IfdId::ifd1Id, 0x0201, IfdId::ifd1Id);
    
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, findStdDecoder);
    
    EXPECT_NO_THROW(decoder.visitSizeEntry(&sizeEntry1));
    EXPECT_NO_THROW(decoder.visitSizeEntry(&sizeEntry2));
}

// Test that TiffSizeEntry constructed with exifIfd tags works with visitSizeEntry
TEST_F(TiffDecoderVisitSizeEntryTest_1654, VisitSizeEntryExifIfd_1654) {
    TiffSizeEntry sizeEntry(0x9201, IfdId::exifId, 0x9202, IfdId::exifId);
    
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, findStdDecoder);
    
    EXPECT_NO_THROW(decoder.visitSizeEntry(&sizeEntry));
}

// Test that visitEntry also works (related visit method)
TEST_F(TiffDecoderVisitSizeEntryTest_1654, VisitEntryDoesNotCrash_1654) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, findStdDecoder);
    
    EXPECT_NO_THROW(decoder.visitEntry(&entry));
}

// Test SizeEntry dtTag and dtGroup with various IfdId values
TEST_F(TiffDecoderVisitSizeEntryTest_1654, SizeEntryDifferentGroups_1654) {
    TiffSizeEntry sizeEntry(0x0100, IfdId::exifId, 0x0201, IfdId::gpsId);
    
    EXPECT_EQ(sizeEntry.dtTag(), 0x0201);
    EXPECT_EQ(sizeEntry.dtGroup(), IfdId::gpsId);
}
