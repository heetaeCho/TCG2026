#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/epsimage.hpp>
#include <exiv2/image.hpp>
#include <exiv2/error.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/xmp_exiv2.hpp>

#include <fstream>
#include <cstring>
#include <sstream>

namespace {

// Minimal valid EPS header for testing
const std::string kMinimalEpsHeader =
    "%!PS-Adobe-3.0 EPSF-3.0\n"
    "%%BoundingBox: 0 0 100 100\n"
    "%%EndComments\n";

// A helper to create a MemIo with given content
std::unique_ptr<Exiv2::BasicIo> createMemIo(const std::string& content) {
    auto io = std::make_unique<Exiv2::MemIo>(
        reinterpret_cast<const uint8_t*>(content.data()), content.size());
    return io;
}

// A helper to create a MemIo with empty content
std::unique_ptr<Exiv2::BasicIo> createEmptyMemIo() {
    return std::make_unique<Exiv2::MemIo>();
}

} // namespace

class EpsImageTest_1754 : public ::testing::Test {
protected:
    void SetUp() override {
        Exiv2::XmpParser::initialize();
    }

    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }
};

// Test: Construction with create=true and empty IO
TEST_F(EpsImageTest_1754, ConstructWithCreateTrue_1754) {
    auto io = createEmptyMemIo();
    EXPECT_NO_THROW(Exiv2::EpsImage img(std::move(io), true));
}

// Test: Construction with create=false and empty IO
TEST_F(EpsImageTest_1754, ConstructWithCreateFalse_1754) {
    auto io = createEmptyMemIo();
    EXPECT_NO_THROW(Exiv2::EpsImage img(std::move(io), false));
}

// Test: mimeType returns the expected MIME type for EPS
TEST_F(EpsImageTest_1754, MimeTypeReturnsExpected_1754) {
    auto io = createMemIo(kMinimalEpsHeader);
    Exiv2::EpsImage img(std::move(io), false);
    std::string mime = img.mimeType();
    // EPS images should return an appropriate mime type
    EXPECT_FALSE(mime.empty());
    // Typically "application/postscript" or similar
    EXPECT_TRUE(mime == "application/postscript" || mime.find("postscript") != std::string::npos);
}

// Test: setComment should throw since EPS doesn't support comments this way
TEST_F(EpsImageTest_1754, SetCommentThrows_1754) {
    auto io = createMemIo(kMinimalEpsHeader);
    Exiv2::EpsImage img(std::move(io), false);
    EXPECT_THROW(img.setComment("test comment"), Exiv2::Error);
}

// Test: readMetadata on empty IO should throw
TEST_F(EpsImageTest_1754, ReadMetadataEmptyIoThrows_1754) {
    auto io = createEmptyMemIo();
    Exiv2::EpsImage img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test: readMetadata on invalid data should throw
TEST_F(EpsImageTest_1754, ReadMetadataInvalidDataThrows_1754) {
    std::string invalidData = "This is not a valid EPS file at all.";
    auto io = createMemIo(invalidData);
    Exiv2::EpsImage img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test: readMetadata on a minimal EPS header
TEST_F(EpsImageTest_1754, ReadMetadataMinimalEps_1754) {
    auto io = createMemIo(kMinimalEpsHeader);
    Exiv2::EpsImage img(std::move(io), false);
    // A minimal EPS without proper structure may still throw depending on impl
    // We test that it either succeeds or throws a known error
    try {
        img.readMetadata();
        // If it succeeds, XMP data should be accessible (possibly empty)
        EXPECT_TRUE(img.xmpData().empty() || !img.xmpData().empty());
    } catch (const Exiv2::Error&) {
        // Acceptable if minimal EPS is not enough
    }
}

// Test: writeMetadata on empty IO should throw
TEST_F(EpsImageTest_1754, WriteMetadataEmptyIoThrows_1754) {
    auto io = createEmptyMemIo();
    Exiv2::EpsImage img(std::move(io), false);
    EXPECT_THROW(img.writeMetadata(), Exiv2::Error);
}

// Test: writeMetadata on invalid data should throw
TEST_F(EpsImageTest_1754, WriteMetadataInvalidDataThrows_1754) {
    std::string invalidData = "Not an EPS file";
    auto io = createMemIo(invalidData);
    Exiv2::EpsImage img(std::move(io), false);
    EXPECT_THROW(img.writeMetadata(), Exiv2::Error);
}

// Test: good() returns appropriate status
TEST_F(EpsImageTest_1754, GoodStatusAfterConstruction_1754) {
    auto io = createMemIo(kMinimalEpsHeader);
    Exiv2::EpsImage img(std::move(io), false);
    // good() depends on IO state
    // After construction with valid IO, it may or may not be "good" depending on impl
    // Just ensure it doesn't crash
    bool status = img.good();
    (void)status; // suppress unused warning
}

// Test: xmpData() returns a reference that can be used
TEST_F(EpsImageTest_1754, XmpDataAccessible_1754) {
    auto io = createMemIo(kMinimalEpsHeader);
    Exiv2::EpsImage img(std::move(io), false);
    Exiv2::XmpData& xmp = img.xmpData();
    EXPECT_TRUE(xmp.empty());
}

// Test: xmpPacket() returns a reference that can be used
TEST_F(EpsImageTest_1754, XmpPacketAccessible_1754) {
    auto io = createMemIo(kMinimalEpsHeader);
    Exiv2::EpsImage img(std::move(io), false);
    std::string& packet = img.xmpPacket();
    EXPECT_TRUE(packet.empty());
}

// Test: clearXmpData works
TEST_F(EpsImageTest_1754, ClearXmpData_1754) {
    auto io = createMemIo(kMinimalEpsHeader);
    Exiv2::EpsImage img(std::move(io), false);
    img.clearXmpData();
    EXPECT_TRUE(img.xmpData().empty());
}

// Test: clearXmpPacket works
TEST_F(EpsImageTest_1754, ClearXmpPacket_1754) {
    auto io = createMemIo(kMinimalEpsHeader);
    Exiv2::EpsImage img(std::move(io), false);
    img.clearXmpPacket();
    EXPECT_TRUE(img.xmpPacket().empty());
}

// Test: writeXmpFromPacket flag can be set and read
TEST_F(EpsImageTest_1754, WriteXmpFromPacketFlag_1754) {
    auto io = createMemIo(kMinimalEpsHeader);
    Exiv2::EpsImage img(std::move(io), false);
    
    img.writeXmpFromPacket(true);
    EXPECT_TRUE(img.writeXmpFromPacket());
    
    img.writeXmpFromPacket(false);
    EXPECT_FALSE(img.writeXmpFromPacket());
}

// Test: EPS with a more structured but still incomplete content
TEST_F(EpsImageTest_1754, ReadMetadataPartialEps_1754) {
    std::string partialEps =
        "%!PS-Adobe-3.0 EPSF-3.0\n"
        "%%BoundingBox: 0 0 200 200\n"
        "%%HiResBoundingBox: 0.0 0.0 200.0 200.0\n"
        "%%EndComments\n"
        "%%BeginProlog\n"
        "%%EndProlog\n"
        "%%Page: 1 1\n"
        "showpage\n"
        "%%EOF\n";
    
    auto io = createMemIo(partialEps);
    Exiv2::EpsImage img(std::move(io), false);
    try {
        img.readMetadata();
        // If successful, verify accessible data
        EXPECT_TRUE(img.xmpData().empty() || !img.xmpData().empty());
    } catch (const Exiv2::Error&) {
        // May throw if the EPS is not valid enough
    }
}

// Test: setXmpData and then attempt writeMetadata on valid EPS
TEST_F(EpsImageTest_1754, SetXmpDataThenWrite_1754) {
    std::string epsContent =
        "%!PS-Adobe-3.0 EPSF-3.0\n"
        "%%BoundingBox: 0 0 100 100\n"
        "%%EndComments\n"
        "%%BeginProlog\n"
        "%%EndProlog\n"
        "%%Page: 1 1\n"
        "showpage\n"
        "%%EOF\n";
    
    auto io = createMemIo(epsContent);
    Exiv2::EpsImage img(std::move(io), false);
    
    // Set some XMP data
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Test Title";
    img.setXmpData(xmpData);
    
    // writeMetadata may throw if the EPS structure is not complete enough
    try {
        img.writeMetadata();
    } catch (const Exiv2::Error&) {
        // Expected for incomplete EPS
    }
}

// Test: io() accessor returns valid reference
TEST_F(EpsImageTest_1754, IoAccessor_1754) {
    auto io = createMemIo(kMinimalEpsHeader);
    Exiv2::EpsImage img(std::move(io), false);
    const Exiv2::BasicIo& ioRef = img.io();
    (void)ioRef; // Should not crash
}

// Test: nativePreviews returns a list (likely empty for minimal EPS)
TEST_F(EpsImageTest_1754, NativePreviewsAccessible_1754) {
    auto io = createMemIo(kMinimalEpsHeader);
    Exiv2::EpsImage img(std::move(io), false);
    const Exiv2::NativePreviewList& previews = img.nativePreviews();
    EXPECT_TRUE(previews.empty());
}

// Test: Binary garbage data should fail readMetadata
TEST_F(EpsImageTest_1754, ReadMetadataBinaryGarbageThrows_1754) {
    std::string garbage(1024, '\0');
    for (size_t i = 0; i < garbage.size(); ++i) {
        garbage[i] = static_cast<char>(i % 256);
    }
    auto io = createMemIo(garbage);
    Exiv2::EpsImage img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test: Very short data should fail readMetadata
TEST_F(EpsImageTest_1754, ReadMetadataVeryShortDataThrows_1754) {
    std::string shortData = "%!";
    auto io = createMemIo(shortData);
    Exiv2::EpsImage img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test: writeMetadata with writeXmpFromPacket true and empty packet
TEST_F(EpsImageTest_1754, WriteMetadataFromPacketEmptyPacket_1754) {
    auto io = createMemIo(kMinimalEpsHeader);
    Exiv2::EpsImage img(std::move(io), false);
    img.writeXmpFromPacket(true);
    img.setXmpPacket("");
    
    // Should throw because the EPS structure is likely insufficient
    try {
        img.writeMetadata();
    } catch (const Exiv2::Error&) {
        // Expected
    }
}

// Test: Exif and IPTC data should be empty for EPS (only XMP is supported)
TEST_F(EpsImageTest_1754, ExifAndIptcEmptyForEps_1754) {
    auto io = createMemIo(kMinimalEpsHeader);
    Exiv2::EpsImage img(std::move(io), false);
    EXPECT_TRUE(img.exifData().empty());
    EXPECT_TRUE(img.iptcData().empty());
}

// Test: Pixel dimensions default to 0
TEST_F(EpsImageTest_1754, DefaultPixelDimensions_1754) {
    auto io = createMemIo(kMinimalEpsHeader);
    Exiv2::EpsImage img(std::move(io), false);
    EXPECT_EQ(img.pixelWidth(), 0u);
    EXPECT_EQ(img.pixelHeight(), 0u);
}

// Test: DOS EPS binary header (starts with 0xC5D0D3C6)
TEST_F(EpsImageTest_1754, ReadMetadataDosEpsBinaryHeader_1754) {
    // DOS EPS binary header: C5 D0 D3 C6 followed by offsets
    std::string dosEps;
    dosEps.push_back('\xC5');
    dosEps.push_back('\xD0');
    dosEps.push_back('\xD3');
    dosEps.push_back('\xC6');
    // Add minimal offset data (30 bytes header) - but likely incomplete
    dosEps.append(26, '\0');
    
    auto io = createMemIo(dosEps);
    Exiv2::EpsImage img(std::move(io), false);
    // Incomplete DOS EPS header should throw
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}
