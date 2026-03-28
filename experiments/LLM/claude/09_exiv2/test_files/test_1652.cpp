#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "exiv2/exiv2.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

namespace {

// A finder function that returns nullptr (no special decoder)
DecoderFct findDecoderFctNone(const std::string& /*make*/,
                               uint32_t /*tag*/,
                               IfdId /*group*/) {
    return nullptr;
}

// A finder function that returns decodeStdTiffEntry
DecoderFct findDecoderFctStd(const std::string& /*make*/,
                              uint32_t /*tag*/,
                              IfdId /*group*/) {
    return &TiffDecoder::decodeStdTiffEntry;
}

class TiffDecoderTest_1652 : public ::testing::Test {
protected:
    void SetUp() override {
        exifData_ = std::make_unique<ExifData>();
        iptcData_ = std::make_unique<IptcData>();
        xmpData_ = std::make_unique<XmpData>();
    }

    std::unique_ptr<ExifData> exifData_;
    std::unique_ptr<IptcData> iptcData_;
    std::unique_ptr<XmpData> xmpData_;
};

// Test that visitDataEntry with a null TiffDataEntry doesn't crash when object has no data
TEST_F(TiffDecoderTest_1652, VisitDataEntryWithNullRoot_1652) {
    // Create decoder with nullptr root - this tests basic construction
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, findDecoderFctNone);

    // Create a TiffDataEntry with some tag and group
    TiffDataEntry entry(0x0111, IfdId::ifd0Id);

    // visitDataEntry should handle an entry that has no data set
    // This should not crash - it calls decodeTiffEntry internally
    decoder.visitDataEntry(&entry);

    // After visiting an empty entry, exifData should remain empty or have minimal content
    // We're treating this as black-box, so we just verify no crash
    SUCCEED();
}

// Test visitDataEntry with a valid TiffDataEntry that has been properly initialized
TEST_F(TiffDecoderTest_1652, VisitDataEntryDecodesEntry_1652) {
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, findDecoderFctStd);

    TiffDataEntry entry(0x0111, IfdId::ifd0Id);

    // Visit the entry - this should invoke decodeTiffEntry -> decodeStdTiffEntry
    decoder.visitDataEntry(&entry);

    // The test verifies the call doesn't crash and the decoder processes the entry
    SUCCEED();
}

// Test that visitDataEntry with findDecoderFct returning nullptr still works
TEST_F(TiffDecoderTest_1652, VisitDataEntryWithNullFinderResult_1652) {
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, findDecoderFctNone);

    TiffDataEntry entry(0x0100, IfdId::ifd0Id);

    decoder.visitDataEntry(&entry);

    // Should not crash
    SUCCEED();
}

// Test visitEntry to verify similar behavior to visitDataEntry
TEST_F(TiffDecoderTest_1652, VisitEntryDoesNotCrash_1652) {
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, findDecoderFctNone);

    TiffEntry entry(0x0100, IfdId::ifd0Id);

    decoder.visitEntry(&entry);
    SUCCEED();
}

// Test visitDirectory does not crash
TEST_F(TiffDecoderTest_1652, VisitDirectoryDoesNotCrash_1652) {
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, findDecoderFctNone);

    TiffDirectory dir(0x0000, IfdId::ifd0Id);
    decoder.visitDirectory(&dir);
    SUCCEED();
}

// Test multiple calls to visitDataEntry
TEST_F(TiffDecoderTest_1652, MultipleVisitDataEntryCalls_1652) {
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, findDecoderFctNone);

    TiffDataEntry entry1(0x0111, IfdId::ifd0Id);
    TiffDataEntry entry2(0x0112, IfdId::ifd0Id);
    TiffDataEntry entry3(0x0100, IfdId::exifId);

    decoder.visitDataEntry(&entry1);
    decoder.visitDataEntry(&entry2);
    decoder.visitDataEntry(&entry3);

    // Multiple visits should not cause issues
    SUCCEED();
}

// Test with different IfdId groups
TEST_F(TiffDecoderTest_1652, VisitDataEntryDifferentGroups_1652) {
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, findDecoderFctStd);

    TiffDataEntry entryIfd0(0x0111, IfdId::ifd0Id);
    TiffDataEntry entryExif(0x0111, IfdId::exifId);

    decoder.visitDataEntry(&entryIfd0);
    decoder.visitDataEntry(&entryExif);

    SUCCEED();
}

} // namespace
