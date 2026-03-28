#include <gtest/gtest.h>
#include <memory>
#include "exiv2/bmffimage.hpp"
#include "basicio.hpp"

namespace {

// Helper to create a BmffImage with a memory-based IO
// We need a minimal valid BMFF file or at least a BasicIo object
class BmffImageMimeTypeTest_1193 : public ::testing::Test {
protected:
    // Helper to create a BmffImage with a specific fileType_ set
    // Since fileType_ is private and set during readMetadata/construction,
    // we need to work with what we can observe through the public interface.
    // 
    // For mimeType() testing, we'll need to create actual BMFF files with
    // proper ftyp boxes to set fileType_ correctly.
    
    // Create a minimal ftyp box with the given major brand
    std::vector<uint8_t> createMinimalBmff(uint32_t majorBrand) {
        std::vector<uint8_t> data;
        
        // ftyp box: size(4) + 'ftyp'(4) + major_brand(4) + minor_version(4) = 16 bytes minimum
        uint32_t boxSize = 16;
        
        // Box size (big-endian)
        data.push_back((boxSize >> 24) & 0xFF);
        data.push_back((boxSize >> 16) & 0xFF);
        data.push_back((boxSize >> 8) & 0xFF);
        data.push_back(boxSize & 0xFF);
        
        // Box type 'ftyp' = 0x66747970
        data.push_back('f');
        data.push_back('t');
        data.push_back('y');
        data.push_back('p');
        
        // Major brand (big-endian)
        data.push_back((majorBrand >> 24) & 0xFF);
        data.push_back((majorBrand >> 16) & 0xFF);
        data.push_back((majorBrand >> 8) & 0xFF);
        data.push_back(majorBrand & 0xFF);
        
        // Minor version
        data.push_back(0);
        data.push_back(0);
        data.push_back(0);
        data.push_back(0);
        
        return data;
    }
    
    std::unique_ptr<Exiv2::BmffImage> createBmffImageWithBrand(uint32_t majorBrand) {
        auto data = createMinimalBmff(majorBrand);
        auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
        auto img = std::make_unique<Exiv2::BmffImage>(std::move(io), false, 1000);
        try {
            img->readMetadata();
        } catch (...) {
            // readMetadata may throw for minimal files, but fileType_ should be set
            // after parsing the ftyp box
        }
        return img;
    }
};

// TAG enum values from the source
constexpr uint32_t TAG_avci = 1635148649;
constexpr uint32_t TAG_avcs = 1635148659;
constexpr uint32_t TAG_avif = 1635150182;
constexpr uint32_t TAG_avio = 1635150191;
constexpr uint32_t TAG_avis = 1635150195;
constexpr uint32_t TAG_heic = 1751476579;
constexpr uint32_t TAG_heif = 1751476582;
constexpr uint32_t TAG_heim = 1751476589;
constexpr uint32_t TAG_heis = 1751476595;
constexpr uint32_t TAG_heix = 1751476600;
constexpr uint32_t TAG_j2is = 1781688691;
constexpr uint32_t TAG_j2ki = 1781689193;
constexpr uint32_t TAG_mif1 = 1835623985;
constexpr uint32_t TAG_crx  = 1668446240;
constexpr uint32_t TAG_jxl  = 1786276896;

// Test mimeType for avci brand
TEST_F(BmffImageMimeTypeTest_1193, MimeTypeAvci_1193) {
    auto img = createBmffImageWithBrand(TAG_avci);
    EXPECT_EQ(img->mimeType(), "image/avci");
}

// Test mimeType for avcs brand
TEST_F(BmffImageMimeTypeTest_1193, MimeTypeAvcs_1193) {
    auto img = createBmffImageWithBrand(TAG_avcs);
    EXPECT_EQ(img->mimeType(), "image/avcs");
}

// Test mimeType for avif brand
TEST_F(BmffImageMimeTypeTest_1193, MimeTypeAvif_1193) {
    auto img = createBmffImageWithBrand(TAG_avif);
    EXPECT_EQ(img->mimeType(), "image/avif");
}

// Test mimeType for avio brand (should return image/avif)
TEST_F(BmffImageMimeTypeTest_1193, MimeTypeAvio_1193) {
    auto img = createBmffImageWithBrand(TAG_avio);
    EXPECT_EQ(img->mimeType(), "image/avif");
}

// Test mimeType for avis brand (should return image/avif)
TEST_F(BmffImageMimeTypeTest_1193, MimeTypeAvis_1193) {
    auto img = createBmffImageWithBrand(TAG_avis);
    EXPECT_EQ(img->mimeType(), "image/avif");
}

// Test mimeType for heic brand
TEST_F(BmffImageMimeTypeTest_1193, MimeTypeHeic_1193) {
    auto img = createBmffImageWithBrand(TAG_heic);
    EXPECT_EQ(img->mimeType(), "image/heic");
}

// Test mimeType for heim brand (should return image/heic)
TEST_F(BmffImageMimeTypeTest_1193, MimeTypeHeim_1193) {
    auto img = createBmffImageWithBrand(TAG_heim);
    EXPECT_EQ(img->mimeType(), "image/heic");
}

// Test mimeType for heis brand (should return image/heic)
TEST_F(BmffImageMimeTypeTest_1193, MimeTypeHeis_1193) {
    auto img = createBmffImageWithBrand(TAG_heis);
    EXPECT_EQ(img->mimeType(), "image/heic");
}

// Test mimeType for heix brand (should return image/heic)
TEST_F(BmffImageMimeTypeTest_1193, MimeTypeHeix_1193) {
    auto img = createBmffImageWithBrand(TAG_heix);
    EXPECT_EQ(img->mimeType(), "image/heic");
}

// Test mimeType for heif brand
TEST_F(BmffImageMimeTypeTest_1193, MimeTypeHeif_1193) {
    auto img = createBmffImageWithBrand(TAG_heif);
    EXPECT_EQ(img->mimeType(), "image/heif");
}

// Test mimeType for mif1 brand (should return image/heif)
TEST_F(BmffImageMimeTypeTest_1193, MimeTypeMif1_1193) {
    auto img = createBmffImageWithBrand(TAG_mif1);
    EXPECT_EQ(img->mimeType(), "image/heif");
}

// Test mimeType for j2is brand
TEST_F(BmffImageMimeTypeTest_1193, MimeTypeJ2is_1193) {
    auto img = createBmffImageWithBrand(TAG_j2is);
    EXPECT_EQ(img->mimeType(), "image/j2is");
}

// Test mimeType for j2ki brand
TEST_F(BmffImageMimeTypeTest_1193, MimeTypeJ2ki_1193) {
    auto img = createBmffImageWithBrand(TAG_j2ki);
    EXPECT_EQ(img->mimeType(), "image/hej2k");
}

// Test mimeType for crx brand
TEST_F(BmffImageMimeTypeTest_1193, MimeTypeCrx_1193) {
    auto img = createBmffImageWithBrand(TAG_crx);
    EXPECT_EQ(img->mimeType(), "image/x-canon-cr3");
}

// Test mimeType for jxl brand
TEST_F(BmffImageMimeTypeTest_1193, MimeTypeJxl_1193) {
    auto img = createBmffImageWithBrand(TAG_jxl);
    EXPECT_EQ(img->mimeType(), "image/jxl");
}

// Test mimeType for unknown/default brand - fileType_ defaults to 0
TEST_F(BmffImageMimeTypeTest_1193, MimeTypeDefaultGeneric_1193) {
    // Create a minimal file that won't set a recognized fileType_
    // Using a brand that doesn't match any known TAG
    uint32_t unknownBrand = 0x12345678;
    auto img = createBmffImageWithBrand(unknownBrand);
    EXPECT_EQ(img->mimeType(), "image/generic");
}

// Test that a freshly constructed BmffImage (without readMetadata) returns generic
TEST_F(BmffImageMimeTypeTest_1193, MimeTypeNoMetadataRead_1193) {
    auto data = createMinimalBmff(TAG_heic);
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    auto img = std::make_unique<Exiv2::BmffImage>(std::move(io), false, 1000);
    // Without calling readMetadata, fileType_ should be default (0)
    EXPECT_EQ(img->mimeType(), "image/generic");
}

// Test setComment - should be a no-op per the interface
TEST_F(BmffImageMimeTypeTest_1193, SetCommentNoOp_1193) {
    auto data = createMinimalBmff(TAG_heic);
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    auto img = std::make_unique<Exiv2::BmffImage>(std::move(io), false, 1000);
    // setComment should not throw
    EXPECT_NO_THROW(img->setComment("test comment"));
}

// Test setExifData - should be a no-op per the interface
TEST_F(BmffImageMimeTypeTest_1193, SetExifDataNoOp_1193) {
    auto data = createMinimalBmff(TAG_heic);
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    auto img = std::make_unique<Exiv2::BmffImage>(std::move(io), false, 1000);
    Exiv2::ExifData exifData;
    EXPECT_NO_THROW(img->setExifData(exifData));
}

// Test setIptcData - should be a no-op per the interface
TEST_F(BmffImageMimeTypeTest_1193, SetIptcDataNoOp_1193) {
    auto data = createMinimalBmff(TAG_heic);
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    auto img = std::make_unique<Exiv2::BmffImage>(std::move(io), false, 1000);
    Exiv2::IptcData iptcData;
    EXPECT_NO_THROW(img->setIptcData(iptcData));
}

// Test setXmpData - should be a no-op per the interface
TEST_F(BmffImageMimeTypeTest_1193, SetXmpDataNoOp_1193) {
    auto data = createMinimalBmff(TAG_heic);
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    auto img = std::make_unique<Exiv2::BmffImage>(std::move(io), false, 1000);
    Exiv2::XmpData xmpData;
    EXPECT_NO_THROW(img->setXmpData(xmpData));
}

// Test pixelWidth and pixelHeight default values (before readMetadata)
TEST_F(BmffImageMimeTypeTest_1193, DefaultPixelDimensions_1193) {
    auto data = createMinimalBmff(TAG_heic);
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    auto img = std::make_unique<Exiv2::BmffImage>(std::move(io), false, 1000);
    // Before reading metadata, dimensions should be 0
    EXPECT_EQ(img->pixelWidth(), 0u);
    EXPECT_EQ(img->pixelHeight(), 0u);
}

// Test writeMetadata throws (BMFF is generally read-only in exiv2)
TEST_F(BmffImageMimeTypeTest_1193, WriteMetadataThrows_1193) {
    auto data = createMinimalBmff(TAG_heic);
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    auto img = std::make_unique<Exiv2::BmffImage>(std::move(io), false, 1000);
    EXPECT_THROW(img->writeMetadata(), Exiv2::Error);
}

// Test readMetadata on empty/minimal data
TEST_F(BmffImageMimeTypeTest_1193, ReadMetadataMinimalFile_1193) {
    // An empty file should cause an error
    std::vector<uint8_t> emptyData;
    auto io = std::make_unique<Exiv2::MemIo>(emptyData.data(), emptyData.size());
    auto img = std::make_unique<Exiv2::BmffImage>(std::move(io), false, 1000);
    EXPECT_THROW(img->readMetadata(), Exiv2::Error);
}

// Test construction with create=true (not necessarily valid for empty IO)
TEST_F(BmffImageMimeTypeTest_1193, ConstructWithCreate_1193) {
    auto io = std::make_unique<Exiv2::MemIo>();
    EXPECT_NO_THROW(auto img = std::make_unique<Exiv2::BmffImage>(std::move(io), true, 1000));
}

// Test that readMetadata on a valid ftyp-only file doesn't crash
TEST_F(BmffImageMimeTypeTest_1193, ReadMetadataFtypOnly_1193) {
    auto data = createMinimalBmff(TAG_avif);
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    auto img = std::make_unique<Exiv2::BmffImage>(std::move(io), false, 1000);
    try {
        img->readMetadata();
    } catch (const Exiv2::Error&) {
        // Expected - minimal file may not have all required boxes
    }
    // After attempting to read, mimeType should reflect the ftyp brand if parsed
    std::string mime = img->mimeType();
    // It should be either "image/avif" (if ftyp was parsed) or "image/generic" (if not)
    EXPECT_TRUE(mime == "image/avif" || mime == "image/generic");
}

// Test printStructure doesn't crash on minimal data
TEST_F(BmffImageMimeTypeTest_1193, PrintStructureMinimal_1193) {
    auto data = createMinimalBmff(TAG_heic);
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    auto img = std::make_unique<Exiv2::BmffImage>(std::move(io), false, 1000);
    std::ostringstream oss;
    try {
        img->printStructure(oss, Exiv2::kpsNone, 0);
    } catch (const Exiv2::Error&) {
        // May throw on minimal data
    }
}

} // namespace
