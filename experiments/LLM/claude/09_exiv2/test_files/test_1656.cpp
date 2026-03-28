#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "exiv2/exiv2.hpp"
#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

namespace {

// A simple FindDecoderFct that returns nullptr (use standard decoding)
DecoderFct findDecoderFctNull(const std::string& /*make*/,
                               uint32_t /*tag*/,
                               IfdId /*group*/) {
    return nullptr;
}

// A FindDecoderFct that returns a specific decoder
DecoderFct findDecoderFctStd(const std::string& /*make*/,
                              uint32_t /*tag*/,
                              IfdId /*group*/) {
    return &TiffDecoder::decodeStdTiffEntry;
}

class TiffDecoderTest_1656 : public ::testing::Test {
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

// Test that TiffDecoder can be constructed with valid parameters
TEST_F(TiffDecoderTest_1656, ConstructorWithValidParams_1656) {
    EXPECT_NO_THROW({
        TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, findDecoderFctNull);
    });
}

// Test visitMnEntry with a TiffMnEntry object - should not crash with nullptr root
TEST_F(TiffDecoderTest_1656, VisitMnEntryWithValidEntry_1656) {
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, findDecoderFctNull);
    TiffMnEntry mnEntry(0x927c, IfdId::exifId, IfdId::canonId);
    
    // visitMnEntry calls decodeTiffEntry internally; with no data set, 
    // it should handle gracefully without crashing
    EXPECT_NO_THROW(decoder.visitMnEntry(&mnEntry));
}

// Test visitMnEntry with standard decoder function
TEST_F(TiffDecoderTest_1656, VisitMnEntryWithStdDecoder_1656) {
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, findDecoderFctStd);
    TiffMnEntry mnEntry(0x927c, IfdId::exifId, IfdId::canonId);
    
    EXPECT_NO_THROW(decoder.visitMnEntry(&mnEntry));
}

// Test visitDirectory with nullptr - should handle gracefully (it's documented as /* object */)
TEST_F(TiffDecoderTest_1656, VisitDirectoryDoesNothing_1656) {
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, findDecoderFctNull);
    
    // visitDirectory is essentially a no-op based on the /* object */ comment
    EXPECT_NO_THROW(decoder.visitDirectory(nullptr));
}

// Test visitEntry with a TiffEntry that has no data
TEST_F(TiffDecoderTest_1656, VisitEntryWithEmptyEntry_1656) {
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, findDecoderFctNull);
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    
    EXPECT_NO_THROW(decoder.visitEntry(&entry));
}

// Test that after visiting entries, ExifData may be populated
TEST_F(TiffDecoderTest_1656, ExifDataInitiallyEmpty_1656) {
    EXPECT_TRUE(exifData_->empty());
    
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, findDecoderFctNull);
    
    // After construction but before visiting, ExifData should still be empty
    EXPECT_TRUE(exifData_->empty());
}

// Test visitMnEntry with different tag values
TEST_F(TiffDecoderTest_1656, VisitMnEntryWithDifferentTags_1656) {
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, findDecoderFctNull);
    
    TiffMnEntry mnEntry1(0x927c, IfdId::exifId, IfdId::nikonId);
    EXPECT_NO_THROW(decoder.visitMnEntry(&mnEntry1));
    
    TiffMnEntry mnEntry2(0x927c, IfdId::exifId, IfdId::sonyId);
    EXPECT_NO_THROW(decoder.visitMnEntry(&mnEntry2));
}

// Test that IptcData and XmpData remain empty when visiting MnEntry with no relevant data
TEST_F(TiffDecoderTest_1656, IptcAndXmpDataUnchangedAfterMnEntry_1656) {
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, findDecoderFctNull);
    TiffMnEntry mnEntry(0x927c, IfdId::exifId, IfdId::canonId);
    
    decoder.visitMnEntry(&mnEntry);
    
    EXPECT_TRUE(iptcData_->empty());
    EXPECT_TRUE(xmpData_->empty());
}

// Test visitBinaryArray with a valid object
TEST_F(TiffDecoderTest_1656, VisitBinaryArrayNoData_1656) {
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, findDecoderFctNull);
    
    // Create a minimal binary array - should not crash with empty data
    TiffBinaryArray binaryArray(0x0001, IfdId::ifd0Id, IfdId::ifd0Id, 0);
    EXPECT_NO_THROW(decoder.visitBinaryArray(&binaryArray));
}

// Test multiple visit calls in sequence
TEST_F(TiffDecoderTest_1656, MultipleVisitCallsInSequence_1656) {
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, findDecoderFctNull);
    
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    TiffMnEntry mnEntry(0x927c, IfdId::exifId, IfdId::canonId);
    
    EXPECT_NO_THROW({
        decoder.visitEntry(&entry);
        decoder.visitMnEntry(&mnEntry);
        decoder.visitDirectory(nullptr);
    });
}

// Test with zero tag value for MnEntry
TEST_F(TiffDecoderTest_1656, VisitMnEntryWithZeroTag_1656) {
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, findDecoderFctNull);
    TiffMnEntry mnEntry(0x0000, IfdId::ifd0Id, IfdId::ifd0Id);
    
    EXPECT_NO_THROW(decoder.visitMnEntry(&mnEntry));
}

// Test with max tag value for MnEntry
TEST_F(TiffDecoderTest_1656, VisitMnEntryWithMaxTag_1656) {
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, findDecoderFctNull);
    TiffMnEntry mnEntry(0xFFFF, IfdId::ifd0Id, IfdId::ifd0Id);
    
    EXPECT_NO_THROW(decoder.visitMnEntry(&mnEntry));
}

} // namespace
