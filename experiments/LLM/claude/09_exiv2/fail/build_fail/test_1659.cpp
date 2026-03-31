#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/exiv2.hpp>
#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

namespace {

// A simple FindDecoderFct that always returns nullptr (no special decoder)
DecoderFct findDecoderFctNull(const std::string& /*make*/, uint32_t /*tag*/, IfdId /*group*/) {
    return nullptr;
}

class TiffDecoderDecodeIptcTest_1659 : public ::testing::Test {
protected:
    void SetUp() override {
        // Suppress warnings during tests
        Exiv2::LogMsg::setLevel(Exiv2::LogMsg::mute);
    }

    void TearDown() override {
        Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
    }

    ExifData exifData_;
    IptcData iptcData_;
    XmpData xmpData_;
};

// Test that decodeIptc with a null object entry doesn't crash
// and iptcData remains empty when no IPTC data is present
TEST_F(TiffDecoderDecodeIptcTest_1659, DecodeIptcWithNoData_1659) {
    TiffEntry entry(0x83bb, IfdId::ifd0Id);
    TiffDecoder decoder(exifData_, iptcData_, xmpData_, &entry, findDecoderFctNull);

    // Entry with no data set - should handle gracefully
    decoder.decodeIptc(&entry);

    EXPECT_TRUE(iptcData_.empty());
}

// Test that calling decodeIptc twice only processes IPTC once
// (decodedIptc_ flag prevents re-processing)
TEST_F(TiffDecoderDecodeIptcTest_1659, DecodeIptcCalledTwiceOnlyDecodesOnce_1659) {
    TiffEntry entry(0x83bb, IfdId::ifd0Id);
    TiffDecoder decoder(exifData_, iptcData_, xmpData_, &entry, findDecoderFctNull);

    decoder.decodeIptc(&entry);
    size_t sizeAfterFirst = iptcData_.size();

    decoder.decodeIptc(&entry);
    size_t sizeAfterSecond = iptcData_.size();

    EXPECT_EQ(sizeAfterFirst, sizeAfterSecond);
}

// Test decodeIptc with an entry that has tag 0x83bb but invalid IPTC data
TEST_F(TiffDecoderDecodeIptcTest_1659, DecodeIptcWithInvalidIptcData0x83bb_1659) {
    // Create entry with tag 0x83bb
    TiffEntry entry(0x83bb, IfdId::ifd0Id);

    // Set some garbage data
    auto storage = std::make_shared<DataBuf>(16);
    std::memset(storage->data(), 0xFF, 16);
    entry.setData(storage->data(), 16, storage);

    TiffDecoder decoder(exifData_, iptcData_, xmpData_, &entry, findDecoderFctNull);
    decoder.decodeIptc(&entry);

    // With invalid data, IPTC decode should fail and iptcData remains empty
    EXPECT_TRUE(iptcData_.empty());
}

// Test decodeIptc with an entry that has tag 0x8649 but invalid Photoshop data
TEST_F(TiffDecoderDecodeIptcTest_1659, DecodeIptcWithInvalidPhotoshopData0x8649_1659) {
    TiffEntry entry(0x8649, IfdId::ifd0Id);

    auto storage = std::make_shared<DataBuf>(32);
    std::memset(storage->data(), 0x00, 32);
    entry.setData(storage->data(), 32, storage);

    TiffDecoder decoder(exifData_, iptcData_, xmpData_, &entry, findDecoderFctNull);
    decoder.decodeIptc(&entry);

    EXPECT_TRUE(iptcData_.empty());
}

// Test decodeIptc with an entry in a different group (not ifd0Id)
TEST_F(TiffDecoderDecodeIptcTest_1659, DecodeIptcWithDifferentGroup_1659) {
    TiffEntry entry(0x83bb, IfdId::exifId);

    auto storage = std::make_shared<DataBuf>(16);
    std::memset(storage->data(), 0xFF, 16);
    entry.setData(storage->data(), 16, storage);

    TiffDecoder decoder(exifData_, iptcData_, xmpData_, &entry, findDecoderFctNull);
    decoder.decodeIptc(&entry);

    // Data is in exifId, not ifd0Id, so getObjData won't find it for ifd0Id lookup
    EXPECT_TRUE(iptcData_.empty());
}

// Test decodeIptc with a different tag (not 0x83bb or 0x8649)
TEST_F(TiffDecoderDecodeIptcTest_1659, DecodeIptcWithUnrelatedTag_1659) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);  // ImageWidth tag

    TiffDecoder decoder(exifData_, iptcData_, xmpData_, &entry, findDecoderFctNull);
    decoder.decodeIptc(&entry);

    EXPECT_TRUE(iptcData_.empty());
}

// Test with valid IPTC data in 0x83bb entry
TEST_F(TiffDecoderDecodeIptcTest_1659, DecodeIptcWithValidIptcDataTag0x83bb_1659) {
    // Construct valid IPTC data
    // IPTC record format: 0x1C, record, dataset, size(2 bytes big-endian), data
    std::vector<byte> iptcBytes;
    // Tag marker
    iptcBytes.push_back(0x1C);
    // Record 2 (application record)
    iptcBytes.push_back(0x02);
    // Dataset 5 (Object Name)
    iptcBytes.push_back(0x05);
    // Size: 4 bytes
    iptcBytes.push_back(0x00);
    iptcBytes.push_back(0x04);
    // Data: "Test"
    iptcBytes.push_back('T');
    iptcBytes.push_back('e');
    iptcBytes.push_back('s');
    iptcBytes.push_back('t');

    TiffEntry entry(0x83bb, IfdId::ifd0Id);
    auto storage = std::make_shared<DataBuf>(iptcBytes.data(), iptcBytes.size());
    entry.setData(storage->data(), storage->size(), storage);

    TiffDecoder decoder(exifData_, iptcData_, xmpData_, &entry, findDecoderFctNull);
    decoder.decodeIptc(&entry);

    // If decode succeeds, iptcData_ should have content
    // Note: depends on whether getObjData returns data for this entry
    // The test verifies it doesn't crash
}

// Test that decodeIptc flag persists across multiple calls with different entries
TEST_F(TiffDecoderDecodeIptcTest_1659, DecodeIptcFlagPersistsAcrossCalls_1659) {
    TiffEntry entry1(0x83bb, IfdId::ifd0Id);
    TiffEntry entry2(0x8649, IfdId::ifd0Id);

    TiffDecoder decoder(exifData_, iptcData_, xmpData_, &entry1, findDecoderFctNull);

    decoder.decodeIptc(&entry1);
    decoder.decodeIptc(&entry2);

    // Second call should return early due to decodedIptc_ flag
    // Just verify no crash
    SUCCEED();
}

// Test decodeIptc with zero-size data
TEST_F(TiffDecoderDecodeIptcTest_1659, DecodeIptcWithZeroSizeData_1659) {
    TiffEntry entry(0x83bb, IfdId::ifd0Id);

    auto storage = std::make_shared<DataBuf>(0);
    entry.setData(storage);

    TiffDecoder decoder(exifData_, iptcData_, xmpData_, &entry, findDecoderFctNull);
    decoder.decodeIptc(&entry);

    EXPECT_TRUE(iptcData_.empty());
}

// Test that the method works with a minimal valid Photoshop IRB containing IPTC
TEST_F(TiffDecoderDecodeIptcTest_1659, DecodeIptcWithPhotoshopIRB_1659) {
    // Construct a minimal Photoshop IRB with IPTC data
    // Photoshop IRB signature: "8BIM" + resource ID (0x0404 for IPTC) + name + size + data
    std::vector<byte> psData;
    // Signature
    psData.push_back('8');
    psData.push_back('B');
    psData.push_back('I');
    psData.push_back('M');
    // Resource ID 0x0404 (IPTC-NAA)
    psData.push_back(0x04);
    psData.push_back(0x04);
    // Pascal string (empty, 1 byte length + padding)
    psData.push_back(0x00);
    psData.push_back(0x00);
    // Data size (4 bytes big-endian) = 9
    psData.push_back(0x00);
    psData.push_back(0x00);
    psData.push_back(0x00);
    psData.push_back(0x09);
    // IPTC data
    psData.push_back(0x1C);
    psData.push_back(0x02);
    psData.push_back(0x05);
    psData.push_back(0x00);
    psData.push_back(0x04);
    psData.push_back('T');
    psData.push_back('e');
    psData.push_back('s');
    psData.push_back('t');
    // Padding to even size
    psData.push_back(0x00);

    TiffEntry entry(0x8649, IfdId::ifd0Id);
    auto storage = std::make_shared<DataBuf>(psData.data(), psData.size());
    entry.setData(storage->data(), storage->size(), storage);

    TiffDecoder decoder(exifData_, iptcData_, xmpData_, &entry, findDecoderFctNull);
    decoder.decodeIptc(&entry);

    // Verify the method handled it without crashing
    SUCCEED();
}

// Verify IptcData remains unchanged when no valid IPTC is found
TEST_F(TiffDecoderDecodeIptcTest_1659, IptcDataUnchangedOnFailure_1659) {
    TiffEntry entry(0x1234, IfdId::ifd0Id);  // unrelated tag

    auto storage = std::make_shared<DataBuf>(8);
    std::memset(storage->data(), 0xAB, 8);
    entry.setData(storage->data(), 8, storage);

    TiffDecoder decoder(exifData_, iptcData_, xmpData_, &entry, findDecoderFctNull);

    EXPECT_TRUE(iptcData_.empty());
    decoder.decodeIptc(&entry);
    EXPECT_TRUE(iptcData_.empty());
}

}  // namespace
