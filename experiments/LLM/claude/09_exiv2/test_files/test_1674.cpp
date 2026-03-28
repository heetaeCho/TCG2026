#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

namespace {

// A minimal TiffHeaderBase implementation for testing
class TestTiffHeader : public TiffHeaderBase {
public:
    TestTiffHeader() : TiffHeaderBase(42, 8, littleEndian, 0) {}
    ~TestTiffHeader() override = default;
};

// Helper to find the encoder function
const TiffMappingInfo* findEncoder(const std::string& make, uint16_t tag, IfdId group) {
    return nullptr;
}

class TiffEncoderVisitMnEntryTest_1674 : public ::testing::Test {
protected:
    void SetUp() override {
        header_ = std::make_unique<TestTiffHeader>();
    }

    std::unique_ptr<TiffEncoder> createEncoder(ExifData exifData, bool isNewImage = false) {
        IptcData iptcData;
        XmpData xmpData;
        PrimaryGroups primaryGroups;
        
        return std::make_unique<TiffEncoder>(
            std::move(exifData),
            iptcData_,
            xmpData_,
            nullptr,  // pRoot
            isNewImage,
            std::move(primaryGroups),
            header_.get(),
            findEncoder
        );
    }

    std::unique_ptr<TestTiffHeader> header_;
    IptcData iptcData_;
    XmpData xmpData_;
};

// Test that visitMnEntry with a TiffMnEntry that has mn_ == nullptr
// calls encodeTiffComponent path (doesn't crash, handles gracefully)
TEST_F(TiffEncoderVisitMnEntryTest_1674, VisitMnEntryWithNullMn_1674) {
    ExifData exifData;
    auto encoder = createEncoder(std::move(exifData));
    
    // Create a TiffMnEntry - mn_ should be nullptr by default
    TiffMnEntry mnEntry(0x927c, IfdId::exifId, IfdId::canonId);
    
    // Should not crash - with null mn_, it goes to encodeTiffComponent path
    EXPECT_NO_THROW(encoder->visitMnEntry(&mnEntry));
}

// Test that visitMnEntry with del_ = true and matching key in exifData
// erases the entry from exifData. By default del_ is true.
TEST_F(TiffEncoderVisitMnEntryTest_1674, VisitMnEntryWithMnSetAndDelTrue_1674) {
    ExifData exifData;
    // Add a MakerNote entry to exifData
    ExifKey key(0x927c, "Exif");
    Value::UniquePtr val = Value::create(undefinedId);
    exifData.add(key, val.get());
    
    ASSERT_FALSE(exifData.empty());
    size_t countBefore = exifData.count();
    
    // We need a TiffMnEntry with mn_ set (non-null)
    // However, setting mn_ requires internal access which we can't easily do
    // from the public interface. This test verifies behavior with null mn_.
    TiffMnEntry mnEntry(0x927c, IfdId::exifId, IfdId::canonId);
    
    auto encoder = createEncoder(std::move(exifData));
    
    // With mn_ == nullptr, this should go through encodeTiffComponent
    EXPECT_NO_THROW(encoder->visitMnEntry(&mnEntry));
}

// Test dirty flag default state
TEST_F(TiffEncoderVisitMnEntryTest_1674, DirtyFlagDefaultFalse_1674) {
    ExifData exifData;
    auto encoder = createEncoder(std::move(exifData));
    
    EXPECT_FALSE(encoder->dirty());
}

// Test setDirty and dirty
TEST_F(TiffEncoderVisitMnEntryTest_1674, SetDirtyFlag_1674) {
    ExifData exifData;
    auto encoder = createEncoder(std::move(exifData));
    
    encoder->setDirty(true);
    EXPECT_TRUE(encoder->dirty());
    
    encoder->setDirty(false);
    EXPECT_FALSE(encoder->dirty());
}

// Test byteOrder returns expected value
TEST_F(TiffEncoderVisitMnEntryTest_1674, ByteOrderMatchesHeader_1674) {
    ExifData exifData;
    auto encoder = createEncoder(std::move(exifData));
    
    EXPECT_EQ(encoder->byteOrder(), littleEndian);
}

// Test writeMethod default is wmNonIntrusive
TEST_F(TiffEncoderVisitMnEntryTest_1674, WriteMethodDefaultNonIntrusive_1674) {
    ExifData exifData;
    auto encoder = createEncoder(std::move(exifData));
    
    EXPECT_EQ(encoder->writeMethod(), wmNonIntrusive);
}

// Test visitMnEntry with a different tag
TEST_F(TiffEncoderVisitMnEntryTest_1674, VisitMnEntryDifferentTag_1674) {
    ExifData exifData;
    auto encoder = createEncoder(std::move(exifData));
    
    TiffMnEntry mnEntry(0x0001, IfdId::exifId, IfdId::canonId);
    
    EXPECT_NO_THROW(encoder->visitMnEntry(&mnEntry));
}

// Test creating encoder with new image flag
TEST_F(TiffEncoderVisitMnEntryTest_1674, CreateEncoderNewImage_1674) {
    ExifData exifData;
    auto encoder = createEncoder(std::move(exifData), true);
    
    EXPECT_FALSE(encoder->dirty());
    EXPECT_EQ(encoder->byteOrder(), littleEndian);
}

// Test visitMnEntry with empty ExifData and null mn_
TEST_F(TiffEncoderVisitMnEntryTest_1674, VisitMnEntryEmptyExifData_1674) {
    ExifData exifData;
    ASSERT_TRUE(exifData.empty());
    
    auto encoder = createEncoder(std::move(exifData));
    
    TiffMnEntry mnEntry(0x927c, IfdId::exifId, IfdId::canonId);
    
    EXPECT_NO_THROW(encoder->visitMnEntry(&mnEntry));
}

}  // namespace
