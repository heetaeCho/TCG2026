#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/epsimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/image.hpp>

#include <cstring>
#include <memory>
#include <sstream>

using namespace Exiv2;

// Helper: create a MemIo with blank EPS content
static std::unique_ptr<BasicIo> makeBlankEpsIo() {
    const std::string epsBlank = "%!PS-Adobe-3.0 EPSF-3.0\n%%BoundingBox: 0 0 0 0\n";
    auto io = std::make_unique<MemIo>(reinterpret_cast<const byte*>(epsBlank.data()), epsBlank.size());
    return io;
}

// Helper: create an empty MemIo
static std::unique_ptr<BasicIo> makeEmptyIo() {
    return std::make_unique<MemIo>();
}

class EpsImageTest_2205 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Construction with create=false and valid EPS data should succeed
TEST_F(EpsImageTest_2205, ConstructWithCreateFalse_2205) {
    auto io = makeBlankEpsIo();
    ASSERT_NO_THROW(EpsImage img(std::move(io), false));
}

// Test: Construction with create=true on empty MemIo should write blank EPS
TEST_F(EpsImageTest_2205, ConstructWithCreateTrue_WritesBlankEps_2205) {
    auto io = std::make_unique<MemIo>();
    ASSERT_NO_THROW(EpsImage img(std::move(io), true));
}

// Test: Construction with create=true produces a valid io with expected size
TEST_F(EpsImageTest_2205, ConstructWithCreateTrue_IoHasContent_2205) {
    auto io = std::make_unique<MemIo>();
    EpsImage img(std::move(io), true);
    const std::string epsBlank = "%!PS-Adobe-3.0 EPSF-3.0\n%%BoundingBox: 0 0 0 0\n";
    EXPECT_EQ(img.io().size(), epsBlank.size());
}

// Test: mimeType returns expected EPS MIME type
TEST_F(EpsImageTest_2205, MimeType_ReturnsEpsMimeType_2205) {
    auto io = makeBlankEpsIo();
    EpsImage img(std::move(io), false);
    std::string mime = img.mimeType();
    // EPS mime type is typically "application/postscript"
    EXPECT_FALSE(mime.empty());
    EXPECT_TRUE(mime == "application/postscript" || mime == "image/x-eps");
}

// Test: setComment should throw or be unsupported for EPS images
TEST_F(EpsImageTest_2205, SetComment_ThrowsOrNoOp_2205) {
    auto io = makeBlankEpsIo();
    EpsImage img(std::move(io), false);
    // EPS typically doesn't support comments via setComment
    EXPECT_THROW(img.setComment("test comment"), Exiv2::Error);
}

// Test: good() should return true after proper construction with create=true
TEST_F(EpsImageTest_2205, Good_AfterCreateTrue_2205) {
    auto io = std::make_unique<MemIo>();
    EpsImage img(std::move(io), true);
    EXPECT_TRUE(img.good());
}

// Test: good() should return true after construction with valid EPS and create=false
TEST_F(EpsImageTest_2205, Good_AfterCreateFalseWithValidEps_2205) {
    auto io = makeBlankEpsIo();
    EpsImage img(std::move(io), false);
    EXPECT_TRUE(img.good());
}

// Test: readMetadata on blank EPS image (minimal content)
TEST_F(EpsImageTest_2205, ReadMetadata_BlankEps_2205) {
    auto io = std::make_unique<MemIo>();
    EpsImage img(std::move(io), true);
    // Reading metadata on a blank EPS should not crash
    // It may throw if the format is not complete enough, but should not segfault
    try {
        img.readMetadata();
    } catch (const Exiv2::Error&) {
        // Acceptable - blank EPS may not have full metadata
    }
}

// Test: writeMetadata on blank EPS image
TEST_F(EpsImageTest_2205, WriteMetadata_BlankEps_2205) {
    auto io = std::make_unique<MemIo>();
    EpsImage img(std::move(io), true);
    // Writing metadata on a blank EPS
    try {
        img.writeMetadata();
    } catch (const Exiv2::Error&) {
        // Acceptable
    }
}

// Test: Construction with create=false and empty IO
TEST_F(EpsImageTest_2205, ConstructWithCreateFalse_EmptyIo_2205) {
    auto io = std::make_unique<MemIo>();
    ASSERT_NO_THROW(EpsImage img(std::move(io), false));
}

// Test: readMetadata on empty IO should throw
TEST_F(EpsImageTest_2205, ReadMetadata_EmptyIo_Throws_2205) {
    auto io = std::make_unique<MemIo>();
    EpsImage img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test: writeMetadata on empty IO should throw
TEST_F(EpsImageTest_2205, WriteMetadata_EmptyIo_Throws_2205) {
    auto io = std::make_unique<MemIo>();
    EpsImage img(std::move(io), false);
    EXPECT_THROW(img.writeMetadata(), Exiv2::Error);
}

// Test: readMetadata on invalid (non-EPS) data should throw
TEST_F(EpsImageTest_2205, ReadMetadata_InvalidData_Throws_2205) {
    const std::string invalidData = "This is not an EPS file at all.";
    auto io = std::make_unique<MemIo>(reinterpret_cast<const byte*>(invalidData.data()), invalidData.size());
    EpsImage img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test: xmpData should be accessible (EPS supports XMP)
TEST_F(EpsImageTest_2205, XmpDataAccessible_2205) {
    auto io = std::make_unique<MemIo>();
    EpsImage img(std::move(io), true);
    EXPECT_NO_THROW(img.xmpData());
}

// Test: supportsMetadata for XMP should return true
TEST_F(EpsImageTest_2205, SupportsMetadata_Xmp_2205) {
    auto io = std::make_unique<MemIo>();
    EpsImage img(std::move(io), true);
    // mdXmp is supported as per constructor
    EXPECT_TRUE(img.supportsMetadata(MetadataId::mdXmp));
}

// Test: pixelWidth and pixelHeight default to 0
TEST_F(EpsImageTest_2205, DefaultPixelDimensions_2205) {
    auto io = std::make_unique<MemIo>();
    EpsImage img(std::move(io), true);
    EXPECT_EQ(img.pixelWidth(), 0u);
    EXPECT_EQ(img.pixelHeight(), 0u);
}

// Test: io() returns a reference to the underlying IO
TEST_F(EpsImageTest_2205, IoReference_2205) {
    auto io = std::make_unique<MemIo>();
    EpsImage img(std::move(io), true);
    EXPECT_NO_THROW(img.io());
}

// Test: clearXmpData on EPS image
TEST_F(EpsImageTest_2205, ClearXmpData_2205) {
    auto io = std::make_unique<MemIo>();
    EpsImage img(std::move(io), true);
    EXPECT_NO_THROW(img.clearXmpData());
    EXPECT_TRUE(img.xmpData().empty());
}

// Test: setXmpData on EPS image
TEST_F(EpsImageTest_2205, SetXmpData_2205) {
    auto io = std::make_unique<MemIo>();
    EpsImage img(std::move(io), true);
    XmpData xmp;
    EXPECT_NO_THROW(img.setXmpData(xmp));
}

// Test: imageType returns eps
TEST_F(EpsImageTest_2205, ImageType_IsEps_2205) {
    auto io = std::make_unique<MemIo>();
    EpsImage img(std::move(io), true);
    EXPECT_EQ(img.imageType(), ImageType::eps);
}

// Test: Multiple create=true constructions
TEST_F(EpsImageTest_2205, MultipleCreations_2205) {
    for (int i = 0; i < 5; ++i) {
        auto io = std::make_unique<MemIo>();
        ASSERT_NO_THROW(EpsImage img(std::move(io), true));
    }
}

// Test: readMetadata after create=true with proper EPS content
TEST_F(EpsImageTest_2205, ReadMetadata_AfterCreate_2205) {
    auto io = std::make_unique<MemIo>();
    EpsImage img(std::move(io), true);
    // The blank EPS should be readable
    try {
        img.readMetadata();
        // If successful, xmpData should be accessible
        EXPECT_NO_THROW(img.xmpData());
    } catch (const Exiv2::Error&) {
        // Some implementations may not fully support reading the minimal blank
    }
}

// Test: Large non-EPS data
TEST_F(EpsImageTest_2205, ReadMetadata_LargeInvalidData_Throws_2205) {
    std::string largeData(100000, 'A');
    auto io = std::make_unique<MemIo>(reinterpret_cast<const byte*>(largeData.data()), largeData.size());
    EpsImage img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test: comment() returns empty for default EPS
TEST_F(EpsImageTest_2205, Comment_DefaultEmpty_2205) {
    auto io = std::make_unique<MemIo>();
    EpsImage img(std::move(io), true);
    EXPECT_TRUE(img.comment().empty());
}
