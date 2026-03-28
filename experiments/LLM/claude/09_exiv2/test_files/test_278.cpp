#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// A minimal TiffHeader for testing purposes
class TestTiffHeader : public TiffHeaderBase {
public:
    TestTiffHeader(ByteOrder byteOrder = littleEndian)
        : TiffHeaderBase(42, 8, byteOrder, 0) {}

    ~TestTiffHeader() override = default;

    bool read(const byte* pData, size_t size) override { return true; }
    DataBuf write() const override { return DataBuf(); }
};

// Helper to find encoder (no-op for testing)
static const TiffMappingInfo* testFindEncoderFct(const std::string& make,
                                                   int tag,
                                                   IfdId group) {
    return nullptr;
}

class TiffEncoderTest_278 : public ::testing::Test {
protected:
    void SetUp() override {
        header_ = std::make_unique<TestTiffHeader>(littleEndian);
        // Create a minimal TiffDirectory as root
        root_ = new TiffDirectory(0x0000, IfdId::ifd0Id);
        primaryGroups_ = std::make_shared<PrimaryGroups::element_type>();
    }

    void TearDown() override {
        // root_ is owned by tests or encoder
        delete root_;
    }

    std::unique_ptr<TestTiffHeader> header_;
    TiffComponent* root_;
    PrimaryGroups primaryGroups_;

    std::unique_ptr<TiffEncoder> createEncoder(
        ExifData exifData = ExifData(),
        const IptcData& iptcData = IptcData(),
        const XmpData& xmpData = XmpData(),
        bool isNewImage = false,
        ByteOrder bo = littleEndian) {
        auto hdr = std::make_unique<TestTiffHeader>(bo);
        auto* rootDir = new TiffDirectory(0x0000, IfdId::ifd0Id);
        auto pg = std::make_shared<PrimaryGroups::element_type>();
        auto encoder = std::make_unique<TiffEncoder>(
            std::move(exifData), iptcData, xmpData,
            rootDir, isNewImage, pg, hdr.get(), testFindEncoderFct);
        // Store header and root so they outlive the encoder in these tests
        headers_.push_back(std::move(hdr));
        roots_.push_back(rootDir);
        return encoder;
    }

    std::vector<std::unique_ptr<TestTiffHeader>> headers_;
    std::vector<TiffComponent*> roots_;

    void cleanupRoots() {
        for (auto* r : roots_) {
            delete r;
        }
        roots_.clear();
    }

    ~TiffEncoderTest_278() override {
        cleanupRoots();
    }
};

// Test that default writeMethod is wmNonIntrusive
TEST_F(TiffEncoderTest_278, DefaultWriteMethodIsNonIntrusive_278) {
    auto encoder = createEncoder();
    EXPECT_EQ(encoder->writeMethod(), wmNonIntrusive);
}

// Test that byteOrder returns the header's byte order (little endian)
TEST_F(TiffEncoderTest_278, ByteOrderLittleEndian_278) {
    auto encoder = createEncoder(ExifData(), IptcData(), XmpData(), false, littleEndian);
    EXPECT_EQ(encoder->byteOrder(), littleEndian);
}

// Test that byteOrder returns the header's byte order (big endian)
TEST_F(TiffEncoderTest_278, ByteOrderBigEndian_278) {
    auto encoder = createEncoder(ExifData(), IptcData(), XmpData(), false, bigEndian);
    EXPECT_EQ(encoder->byteOrder(), bigEndian);
}

// Test that dirty() initially returns false
TEST_F(TiffEncoderTest_278, InitialDirtyIsFalse_278) {
    auto encoder = createEncoder();
    EXPECT_FALSE(encoder->dirty());
}

// Test that setDirty(true) makes dirty() return true
TEST_F(TiffEncoderTest_278, SetDirtyTrue_278) {
    auto encoder = createEncoder();
    encoder->setDirty(true);
    EXPECT_TRUE(encoder->dirty());
}

// Test that setDirty(false) makes dirty() return false
TEST_F(TiffEncoderTest_278, SetDirtyFalse_278) {
    auto encoder = createEncoder();
    encoder->setDirty(true);
    EXPECT_TRUE(encoder->dirty());
    encoder->setDirty(false);
    EXPECT_FALSE(encoder->dirty());
}

// Test toggling dirty flag multiple times
TEST_F(TiffEncoderTest_278, SetDirtyToggle_278) {
    auto encoder = createEncoder();
    EXPECT_FALSE(encoder->dirty());
    encoder->setDirty(true);
    EXPECT_TRUE(encoder->dirty());
    encoder->setDirty(true);
    EXPECT_TRUE(encoder->dirty());
    encoder->setDirty(false);
    EXPECT_FALSE(encoder->dirty());
    encoder->setDirty(false);
    EXPECT_FALSE(encoder->dirty());
}

// Test that writeMethod remains consistent after setDirty
TEST_F(TiffEncoderTest_278, WriteMethodUnchangedAfterSetDirty_278) {
    auto encoder = createEncoder();
    EXPECT_EQ(encoder->writeMethod(), wmNonIntrusive);
    encoder->setDirty(true);
    // writeMethod should still be wmNonIntrusive unless visitor methods change it
    EXPECT_EQ(encoder->writeMethod(), wmNonIntrusive);
}

// Test construction with new image flag true
TEST_F(TiffEncoderTest_278, ConstructWithNewImageTrue_278) {
    auto encoder = createEncoder(ExifData(), IptcData(), XmpData(), true, littleEndian);
    // Even with isNewImage=true, default writeMethod and dirty should remain default
    EXPECT_EQ(encoder->writeMethod(), wmNonIntrusive);
    EXPECT_FALSE(encoder->dirty());
}

// Test construction with non-empty ExifData
TEST_F(TiffEncoderTest_278, ConstructWithExifData_278) {
    ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    auto encoder = createEncoder(std::move(exifData));
    // Encoder should be constructible with exif data; basic state remains valid
    EXPECT_EQ(encoder->writeMethod(), wmNonIntrusive);
}

// Test construction with non-empty IptcData
TEST_F(TiffEncoderTest_278, ConstructWithIptcData_278) {
    IptcData iptcData;
    Iptcdatum datum(IptcKey("Iptc.Application2.Caption"));
    datum.setValue("Test caption");
    iptcData.add(datum);
    auto encoder = createEncoder(ExifData(), iptcData);
    EXPECT_FALSE(encoder->dirty());
}

// Test that multiple encoders can be created independently
TEST_F(TiffEncoderTest_278, MultipleEncodersIndependent_278) {
    auto encoder1 = createEncoder();
    auto encoder2 = createEncoder();
    encoder1->setDirty(true);
    EXPECT_TRUE(encoder1->dirty());
    EXPECT_FALSE(encoder2->dirty());
}
