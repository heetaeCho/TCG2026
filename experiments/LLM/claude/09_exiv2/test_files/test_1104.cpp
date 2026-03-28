#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/image_types.hpp>
#include <exiv2/error.hpp>

#include <cstring>
#include <fstream>
#include <vector>

namespace {

// Helper: JPEG file signature
const Exiv2::byte jpegSignature[] = {0xFF, 0xD8, 0xFF, 0xE0};

// Helper: PNG file signature
const Exiv2::byte pngSignature[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};

// Helper: TIFF (little-endian) signature
const Exiv2::byte tiffLESignature[] = {0x49, 0x49, 0x2A, 0x00};

// Helper: TIFF (big-endian) signature
const Exiv2::byte tiffBESignature[] = {0x4D, 0x4D, 0x00, 0x2A};

// Helper: GIF signature
const Exiv2::byte gifSignature[] = {0x47, 0x49, 0x46, 0x38, 0x39, 0x61};

// Helper: BMP signature
const Exiv2::byte bmpSignature[] = {0x42, 0x4D, 0x00, 0x00, 0x00, 0x00};

// Helper: WebP signature
const Exiv2::byte webpSignature[] = {
    0x52, 0x49, 0x46, 0x46,  // "RIFF"
    0x00, 0x00, 0x00, 0x00,  // file size (placeholder)
    0x57, 0x45, 0x42, 0x50   // "WEBP"
};

// Helper: PSD signature
const Exiv2::byte psdSignature[] = {0x38, 0x42, 0x50, 0x53};

// Helper to create a temporary file with given data
class TempFile {
public:
    TempFile(const std::string& name, const Exiv2::byte* data, size_t size)
        : path_(name) {
        std::ofstream ofs(path_, std::ios::binary);
        if (data && size > 0) {
            ofs.write(reinterpret_cast<const char*>(data), size);
        }
        ofs.close();
    }
    ~TempFile() {
        std::remove(path_.c_str());
    }
    const std::string& path() const { return path_; }
private:
    std::string path_;
};

} // anonymous namespace

// Test: getType with JPEG data from memory
TEST(ImageFactoryGetTypeTest_1104, JpegFromMemory_1104) {
    // Minimal JPEG: FF D8 FF E0 ...
    std::vector<Exiv2::byte> data = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10,
                                      0x4A, 0x46, 0x49, 0x46, 0x00, 0x01,
                                      0x01, 0x00, 0x00, 0x01, 0x00, 0x01,
                                      0x00, 0x00};
    Exiv2::ImageType type = Exiv2::ImageFactory::getType(data.data(), data.size());
    EXPECT_EQ(type, Exiv2::ImageType::jpeg);
}

// Test: getType with PNG data from memory
TEST(ImageFactoryGetTypeTest_1104, PngFromMemory_1104) {
    std::vector<Exiv2::byte> data(pngSignature, pngSignature + sizeof(pngSignature));
    // Pad some extra bytes to make it look more like a real file
    data.resize(64, 0);
    Exiv2::ImageType type = Exiv2::ImageFactory::getType(data.data(), data.size());
    EXPECT_EQ(type, Exiv2::ImageType::png);
}

// Test: getType with empty/random data returns none
TEST(ImageFactoryGetTypeTest_1104, RandomDataReturnsNone_1104) {
    std::vector<Exiv2::byte> data = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
    Exiv2::ImageType type = Exiv2::ImageFactory::getType(data.data(), data.size());
    EXPECT_EQ(type, Exiv2::ImageType::none);
}

// Test: getType with zero-length data returns none
TEST(ImageFactoryGetTypeTest_1104, EmptyDataReturnsNone_1104) {
    Exiv2::byte dummy = 0;
    Exiv2::ImageType type = Exiv2::ImageFactory::getType(&dummy, 0);
    EXPECT_EQ(type, Exiv2::ImageType::none);
}

// Test: getType with TIFF LE data from memory
TEST(ImageFactoryGetTypeTest_1104, TiffLittleEndianFromMemory_1104) {
    // TIFF LE with minimal header
    std::vector<Exiv2::byte> data(tiffLESignature, tiffLESignature + sizeof(tiffLESignature));
    // Offset to first IFD (8 bytes from start)
    data.push_back(0x08);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    // Pad
    data.resize(64, 0);
    Exiv2::ImageType type = Exiv2::ImageFactory::getType(data.data(), data.size());
    EXPECT_EQ(type, Exiv2::ImageType::tiff);
}

// Test: getType with TIFF BE data from memory
TEST(ImageFactoryGetTypeTest_1104, TiffBigEndianFromMemory_1104) {
    std::vector<Exiv2::byte> data(tiffBESignature, tiffBESignature + sizeof(tiffBESignature));
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x08);
    data.resize(64, 0);
    Exiv2::ImageType type = Exiv2::ImageFactory::getType(data.data(), data.size());
    EXPECT_EQ(type, Exiv2::ImageType::tiff);
}

// Test: getType with GIF data from memory
TEST(ImageFactoryGetTypeTest_1104, GifFromMemory_1104) {
    std::vector<Exiv2::byte> data(gifSignature, gifSignature + sizeof(gifSignature));
    data.resize(64, 0);
    Exiv2::ImageType type = Exiv2::ImageFactory::getType(data.data(), data.size());
    EXPECT_EQ(type, Exiv2::ImageType::gif);
}

// Test: getType with BMP data from memory
TEST(ImageFactoryGetTypeTest_1104, BmpFromMemory_1104) {
    std::vector<Exiv2::byte> data(bmpSignature, bmpSignature + sizeof(bmpSignature));
    data.resize(64, 0);
    Exiv2::ImageType type = Exiv2::ImageFactory::getType(data.data(), data.size());
    EXPECT_EQ(type, Exiv2::ImageType::bmp);
}

// Test: getType with WebP data from memory
TEST(ImageFactoryGetTypeTest_1104, WebPFromMemory_1104) {
    std::vector<Exiv2::byte> data(webpSignature, webpSignature + sizeof(webpSignature));
    data.resize(64, 0);
    Exiv2::ImageType type = Exiv2::ImageFactory::getType(data.data(), data.size());
    EXPECT_EQ(type, Exiv2::ImageType::webp);
}

// Test: getType with PSD data from memory
TEST(ImageFactoryGetTypeTest_1104, PsdFromMemory_1104) {
    std::vector<Exiv2::byte> data(psdSignature, psdSignature + sizeof(psdSignature));
    data.resize(64, 0);
    Exiv2::ImageType type = Exiv2::ImageFactory::getType(data.data(), data.size());
    EXPECT_EQ(type, Exiv2::ImageType::psd);
}

// Test: open with JPEG data from memory returns non-null
TEST(ImageFactoryOpenTest_1104, OpenJpegFromMemory_1104) {
    // Minimal JPEG data
    std::vector<Exiv2::byte> data = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10,
                                      0x4A, 0x46, 0x49, 0x46, 0x00, 0x01,
                                      0x01, 0x00, 0x00, 0x01, 0x00, 0x01,
                                      0x00, 0x00, 0xFF, 0xD9};
    auto image = Exiv2::ImageFactory::open(data.data(), data.size());
    ASSERT_NE(image, nullptr);
}

// Test: open with unrecognized data throws
TEST(ImageFactoryOpenTest_1104, OpenUnrecognizedDataThrows_1104) {
    std::vector<Exiv2::byte> data = {0x00, 0x01, 0x02, 0x03};
    EXPECT_THROW(Exiv2::ImageFactory::open(data.data(), data.size()), Exiv2::Error);
}

// Test: open with nonexistent file path throws
TEST(ImageFactoryOpenTest_1104, OpenNonexistentFileThrows_1104) {
    EXPECT_THROW(Exiv2::ImageFactory::open("/nonexistent/path/to/file.jpg", false), Exiv2::Error);
}

// Test: getType with nonexistent file path
TEST(ImageFactoryGetTypeTest_1104, NonexistentFileReturnsNone_1104) {
    Exiv2::ImageType type = Exiv2::ImageFactory::getType("/nonexistent/path/to/file.xyz");
    EXPECT_EQ(type, Exiv2::ImageType::none);
}

// Test: checkMode for JPEG with Exif
TEST(ImageFactoryCheckModeTest_1104, JpegExifReadWrite_1104) {
    Exiv2::AccessMode mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::jpeg, Exiv2::MetadataId::mdExif);
    EXPECT_EQ(mode, Exiv2::amReadWrite);
}

// Test: checkMode for JPEG with IPTC
TEST(ImageFactoryCheckModeTest_1104, JpegIptcReadWrite_1104) {
    Exiv2::AccessMode mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::jpeg, Exiv2::MetadataId::mdIptc);
    EXPECT_EQ(mode, Exiv2::amReadWrite);
}

// Test: checkMode for JPEG with XMP
TEST(ImageFactoryCheckModeTest_1104, JpegXmpReadWrite_1104) {
    Exiv2::AccessMode mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::jpeg, Exiv2::MetadataId::mdXmp);
    EXPECT_EQ(mode, Exiv2::amReadWrite);
}

// Test: checkMode for JPEG with Comment
TEST(ImageFactoryCheckModeTest_1104, JpegCommentReadWrite_1104) {
    Exiv2::AccessMode mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::jpeg, Exiv2::MetadataId::mdComment);
    EXPECT_EQ(mode, Exiv2::amReadWrite);
}

// Test: checkMode for GIF (no metadata support)
TEST(ImageFactoryCheckModeTest_1104, GifExifNone_1104) {
    Exiv2::AccessMode mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::gif, Exiv2::MetadataId::mdExif);
    EXPECT_EQ(mode, Exiv2::amNone);
}

// Test: checkMode for GIF IPTC none
TEST(ImageFactoryCheckModeTest_1104, GifIptcNone_1104) {
    Exiv2::AccessMode mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::gif, Exiv2::MetadataId::mdIptc);
    EXPECT_EQ(mode, Exiv2::amNone);
}

// Test: checkMode for unknown type returns none
TEST(ImageFactoryCheckModeTest_1104, NoneTypeReturnsNone_1104) {
    Exiv2::AccessMode mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::none, Exiv2::MetadataId::mdExif);
    EXPECT_EQ(mode, Exiv2::amNone);
}

// Test: checkMode for MRW (read-only Exif)
TEST(ImageFactoryCheckModeTest_1104, MrwExifReadOnly_1104) {
    Exiv2::AccessMode mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::mrw, Exiv2::MetadataId::mdExif);
    EXPECT_EQ(mode, Exiv2::amRead);
}

// Test: checkMode for CRW comment support
TEST(ImageFactoryCheckModeTest_1104, CrwCommentReadWrite_1104) {
    Exiv2::AccessMode mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::crw, Exiv2::MetadataId::mdComment);
    EXPECT_EQ(mode, Exiv2::amReadWrite);
}

// Test: checkMode for CRW IPTC (none)
TEST(ImageFactoryCheckModeTest_1104, CrwIptcNone_1104) {
    Exiv2::AccessMode mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::crw, Exiv2::MetadataId::mdIptc);
    EXPECT_EQ(mode, Exiv2::amNone);
}

// Test: checkMode for EPS Exif (none)
TEST(ImageFactoryCheckModeTest_1104, EpsExifNone_1104) {
    Exiv2::AccessMode mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::eps, Exiv2::MetadataId::mdExif);
    EXPECT_EQ(mode, Exiv2::amNone);
}

// Test: checkMode for EPS XMP (readwrite)
TEST(ImageFactoryCheckModeTest_1104, EpsXmpReadWrite_1104) {
    Exiv2::AccessMode mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::eps, Exiv2::MetadataId::mdXmp);
    EXPECT_EQ(mode, Exiv2::amReadWrite);
}

// Test: checkMode for TIFF comment (none)
TEST(ImageFactoryCheckModeTest_1104, TiffCommentNone_1104) {
    Exiv2::AccessMode mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::tiff, Exiv2::MetadataId::mdComment);
    EXPECT_EQ(mode, Exiv2::amNone);
}

// Test: checkMode for PNG with all metadata
TEST(ImageFactoryCheckModeTest_1104, PngExifReadWrite_1104) {
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::png, Exiv2::MetadataId::mdExif), Exiv2::amReadWrite);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::png, Exiv2::MetadataId::mdIptc), Exiv2::amReadWrite);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::png, Exiv2::MetadataId::mdXmp), Exiv2::amReadWrite);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::png, Exiv2::MetadataId::mdComment), Exiv2::amReadWrite);
}

// Test: getType via BasicIo with JPEG data
TEST(ImageFactoryGetTypeViaIoTest_1104, JpegViaMemIo_1104) {
    std::vector<Exiv2::byte> data = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10,
                                      0x4A, 0x46, 0x49, 0x46, 0x00, 0x01,
                                      0x01, 0x00, 0x00, 0x01, 0x00, 0x01,
                                      0x00, 0x00};
    Exiv2::MemIo memIo(data.data(), data.size());
    Exiv2::ImageType type = Exiv2::ImageFactory::getType(memIo);
    EXPECT_EQ(type, Exiv2::ImageType::jpeg);
}

// Test: getType via BasicIo with empty data
TEST(ImageFactoryGetTypeViaIoTest_1104, EmptyMemIoReturnsNone_1104) {
    Exiv2::MemIo memIo;
    Exiv2::ImageType type = Exiv2::ImageFactory::getType(memIo);
    EXPECT_EQ(type, Exiv2::ImageType::none);
}

// Test: getType via BasicIo with random data
TEST(ImageFactoryGetTypeViaIoTest_1104, RandomDataMemIoReturnsNone_1104) {
    std::vector<Exiv2::byte> data = {0x12, 0x34, 0x56, 0x78};
    Exiv2::MemIo memIo(data.data(), data.size());
    Exiv2::ImageType type = Exiv2::ImageFactory::getType(memIo);
    EXPECT_EQ(type, Exiv2::ImageType::none);
}

// Test: create with ImageType::jpeg
TEST(ImageFactoryCreateTest_1104, CreateJpeg_1104) {
    auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::jpeg);
    ASSERT_NE(image, nullptr);
}

// Test: create with unsupported/none type throws
TEST(ImageFactoryCreateTest_1104, CreateNoneThrows_1104) {
    EXPECT_THROW(Exiv2::ImageFactory::create(Exiv2::ImageType::none), Exiv2::Error);
}

// Test: checkMode for WebP metadata
TEST(ImageFactoryCheckModeTest_1104, WebPMetadata_1104) {
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::webp, Exiv2::MetadataId::mdExif), Exiv2::amReadWrite);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::webp, Exiv2::MetadataId::mdIptc), Exiv2::amNone);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::webp, Exiv2::MetadataId::mdXmp), Exiv2::amReadWrite);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::webp, Exiv2::MetadataId::mdComment), Exiv2::amNone);
}

// Test: checkMode for RAF (read-only)
TEST(ImageFactoryCheckModeTest_1104, RafReadOnly_1104) {
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::raf, Exiv2::MetadataId::mdExif), Exiv2::amRead);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::raf, Exiv2::MetadataId::mdIptc), Exiv2::amRead);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::raf, Exiv2::MetadataId::mdXmp), Exiv2::amRead);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::raf, Exiv2::MetadataId::mdComment), Exiv2::amNone);
}

// Test: checkMode for BMP (no metadata)
TEST(ImageFactoryCheckModeTest_1104, BmpNoMetadata_1104) {
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::bmp, Exiv2::MetadataId::mdExif), Exiv2::amNone);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::bmp, Exiv2::MetadataId::mdIptc), Exiv2::amNone);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::bmp, Exiv2::MetadataId::mdXmp), Exiv2::amNone);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::bmp, Exiv2::MetadataId::mdComment), Exiv2::amNone);
}

// Test: checkMode for TGA (no metadata)
TEST(ImageFactoryCheckModeTest_1104, TgaNoMetadata_1104) {
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::tga, Exiv2::MetadataId::mdExif), Exiv2::amNone);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::tga, Exiv2::MetadataId::mdIptc), Exiv2::amNone);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::tga, Exiv2::MetadataId::mdXmp), Exiv2::amNone);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::tga, Exiv2::MetadataId::mdComment), Exiv2::amNone);
}

// Test: checkMode for PGF (full support)
TEST(ImageFactoryCheckModeTest_1104, PgfFullSupport_1104) {
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::pgf, Exiv2::MetadataId::mdExif), Exiv2::amReadWrite);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::pgf, Exiv2::MetadataId::mdIptc), Exiv2::amReadWrite);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::pgf, Exiv2::MetadataId::mdXmp), Exiv2::amReadWrite);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::pgf, Exiv2::MetadataId::mdComment), Exiv2::amReadWrite);
}

// Test: checkMode for XMP sidecar
TEST(ImageFactoryCheckModeTest_1104, XmpMetadata_1104) {
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::xmp, Exiv2::MetadataId::mdExif), Exiv2::amReadWrite);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::xmp, Exiv2::MetadataId::mdIptc), Exiv2::amReadWrite);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::xmp, Exiv2::MetadataId::mdXmp), Exiv2::amReadWrite);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::xmp, Exiv2::MetadataId::mdComment), Exiv2::amNone);
}

// Test: checkMode for CR2
TEST(ImageFactoryCheckModeTest_1104, Cr2Metadata_1104) {
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::cr2, Exiv2::MetadataId::mdExif), Exiv2::amReadWrite);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::cr2, Exiv2::MetadataId::mdIptc), Exiv2::amReadWrite);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::cr2, Exiv2::MetadataId::mdXmp), Exiv2::amReadWrite);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::cr2, Exiv2::MetadataId::mdComment), Exiv2::amNone);
}

// Test: checkMode for ARW (read-only)
TEST(ImageFactoryCheckModeTest_1104, ArwReadOnly_1104) {
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::arw, Exiv2::MetadataId::mdExif), Exiv2::amRead);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::arw, Exiv2::MetadataId::mdIptc), Exiv2::amRead);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::arw, Exiv2::MetadataId::mdXmp), Exiv2::amRead);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::arw, Exiv2::MetadataId::mdComment), Exiv2::amNone);
}

// Test: single byte data should return none
TEST(ImageFactoryGetTypeTest_1104, SingleByteReturnsNone_1104) {
    Exiv2::byte data = 0xFF;
    Exiv2::ImageType type = Exiv2::ImageFactory::getType(&data, 1);
    EXPECT_EQ(type, Exiv2::ImageType::none);
}

// Test: two bytes of JPEG header but incomplete
TEST(ImageFactoryGetTypeTest_1104, IncompleteJpegReturnsNoneOrJpeg_1104) {
    Exiv2::byte data[] = {0xFF, 0xD8};
    Exiv2::ImageType type = Exiv2::ImageFactory::getType(data, 2);
    // With only 2 bytes, it might or might not be recognized as JPEG
    // We just verify it doesn't crash and returns a valid enum
    EXPECT_TRUE(type == Exiv2::ImageType::jpeg || type == Exiv2::ImageType::none);
}

// Test: createIo returns valid BasicIo for a valid path concept
TEST(ImageFactoryCreateIoTest_1104, CreateIoForFilePath_1104) {
    auto io = Exiv2::ImageFactory::createIo("/tmp/test_imagefactory_1104.tmp", false);
    ASSERT_NE(io, nullptr);
}

// Test: checkMode for BMFF
TEST(ImageFactoryCheckModeTest_1104, BmffMetadata_1104) {
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::bmff, Exiv2::MetadataId::mdExif), Exiv2::amRead);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::bmff, Exiv2::MetadataId::mdIptc), Exiv2::amRead);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::bmff, Exiv2::MetadataId::mdXmp), Exiv2::amRead);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::bmff, Exiv2::MetadataId::mdComment), Exiv2::amNone);
}

// Test: checkMode for RW2 (read-only)
TEST(ImageFactoryCheckModeTest_1104, Rw2ReadOnly_1104) {
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::rw2, Exiv2::MetadataId::mdExif), Exiv2::amRead);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::rw2, Exiv2::MetadataId::mdIptc), Exiv2::amRead);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::rw2, Exiv2::MetadataId::mdXmp), Exiv2::amRead);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::rw2, Exiv2::MetadataId::mdComment), Exiv2::amNone);
}

// Test: checkMode for ORF
TEST(ImageFactoryCheckModeTest_1104, OrfMetadata_1104) {
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::orf, Exiv2::MetadataId::mdExif), Exiv2::amReadWrite);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::orf, Exiv2::MetadataId::mdIptc), Exiv2::amReadWrite);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::orf, Exiv2::MetadataId::mdXmp), Exiv2::amReadWrite);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::orf, Exiv2::MetadataId::mdComment), Exiv2::amNone);
}

// Test: checkMode for JP2
TEST(ImageFactoryCheckModeTest_1104, Jp2Metadata_1104) {
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::jp2, Exiv2::MetadataId::mdExif), Exiv2::amReadWrite);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::jp2, Exiv2::MetadataId::mdIptc), Exiv2::amReadWrite);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::jp2, Exiv2::MetadataId::mdXmp), Exiv2::amReadWrite);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::jp2, Exiv2::MetadataId::mdComment), Exiv2::amNone);
}

// Test: checkMode for PSD
TEST(ImageFactoryCheckModeTest_1104, PsdMetadata_1104) {
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::psd, Exiv2::MetadataId::mdExif), Exiv2::amReadWrite);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::psd, Exiv2::MetadataId::mdIptc), Exiv2::amReadWrite);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::psd, Exiv2::MetadataId::mdXmp), Exiv2::amReadWrite);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::psd, Exiv2::MetadataId::mdComment), Exiv2::amNone);
}

// Test: checkMode for EXV (full metadata like JPEG)
TEST(ImageFactoryCheckModeTest_1104, ExvMetadata_1104) {
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::exv, Exiv2::MetadataId::mdExif), Exiv2::amReadWrite);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::exv, Exiv2::MetadataId::mdIptc), Exiv2::amReadWrite);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::exv, Exiv2::MetadataId::mdXmp), Exiv2::amReadWrite);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::exv, Exiv2::MetadataId::mdComment), Exiv2::amReadWrite);
}

// Test: open with MemIo containing JPEG
TEST(ImageFactoryOpenTest_1104, OpenJpegViaUniqueIo_1104) {
    std::vector<Exiv2::byte> data = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10,
                                      0x4A, 0x46, 0x49, 0x46, 0x00, 0x01,
                                      0x01, 0x00, 0x00, 0x01, 0x00, 0x01,
                                      0x00, 0x00, 0xFF, 0xD9};
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    auto image = Exiv2::ImageFactory::open(std::move(io));
    ASSERT_NE(image, nullptr);
}

// Test: open with MemIo containing unrecognized data throws
TEST(ImageFactoryOpenTest_1104, OpenUnrecognizedViaUniqueIoThrows_1104) {
    std::vector<Exiv2::byte> data = {0x00, 0x01, 0x02, 0x03, 0x04};
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    EXPECT_THROW(Exiv2::ImageFactory::open(std::move(io)), Exiv2::Error);
}

// Test: checkMode for QTime
TEST(ImageFactoryCheckModeTest_1104, QTimeMetadata_1104) {
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::qtime, Exiv2::MetadataId::mdExif), Exiv2::amRead);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::qtime, Exiv2::MetadataId::mdIptc), Exiv2::amNone);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::qtime, Exiv2::MetadataId::mdXmp), Exiv2::amRead);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::qtime, Exiv2::MetadataId::mdComment), Exiv2::amNone);
}

// Test: checkMode for ASF
TEST(ImageFactoryCheckModeTest_1104, AsfMetadata_1104) {
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::asf, Exiv2::MetadataId::mdExif), Exiv2::amRead);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::asf, Exiv2::MetadataId::mdIptc), Exiv2::amNone);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::asf, Exiv2::MetadataId::mdXmp), Exiv2::amRead);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::asf, Exiv2::MetadataId::mdComment), Exiv2::amNone);
}

// Test: checkMode for RIFF
TEST(ImageFactoryCheckModeTest_1104, RiffMetadata_1104) {
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::riff, Exiv2::MetadataId::mdExif), Exiv2::amRead);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::riff, Exiv2::MetadataId::mdIptc), Exiv2::amNone);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::riff, Exiv2::MetadataId::mdXmp), Exiv2::amRead);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::riff, Exiv2::MetadataId::mdComment), Exiv2::amNone);
}

// Test: checkMode for MKV
TEST(ImageFactoryCheckModeTest_1104, MkvMetadata_1104) {
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::mkv, Exiv2::MetadataId::mdExif), Exiv2::amRead);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::mkv, Exiv2::MetadataId::mdIptc), Exiv2::amNone);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::mkv, Exiv2::MetadataId::mdXmp), Exiv2::amRead);
    EXPECT_EQ(Exiv2::ImageFactory::checkMode(Exiv2::ImageType::mkv, Exiv2::MetadataId::mdComment), Exiv2::amNone);
}
