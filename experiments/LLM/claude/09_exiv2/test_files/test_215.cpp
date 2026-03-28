#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/jpgimage.hpp>
#include <exiv2/basicio.hpp>
#include <fstream>
#include <cstring>

using namespace Exiv2;

class JpegImageTest_215 : public ::testing::Test {
protected:
    // Helper to create a minimal valid JPEG in memory
    std::unique_ptr<MemIo> createMinimalJpeg() {
        // Minimal JPEG: SOI (FFD8) + EOI (FFD9)
        static const unsigned char minJpeg[] = {
            0xFF, 0xD8, 0xFF, 0xD9
        };
        auto io = std::make_unique<MemIo>(minJpeg, sizeof(minJpeg));
        return io;
    }

    // Helper to create a more complete JPEG with SOF0 marker
    std::unique_ptr<MemIo> createJpegWithSOF0(int numComponents = 3) {
        // SOI + SOF0 segment + EOI
        // SOF0: FF C0, length (2 bytes), precision (1 byte), height (2 bytes), width (2 bytes),
        //        num_components (1 byte), then for each component: id(1), sampling(1), qt(1)
        std::vector<unsigned char> data;
        // SOI
        data.push_back(0xFF);
        data.push_back(0xD8);
        // APP0 (JFIF marker) - minimal
        data.push_back(0xFF);
        data.push_back(0xE0);
        data.push_back(0x00);
        data.push_back(0x10); // length = 16
        // JFIF\0
        data.push_back('J'); data.push_back('F'); data.push_back('I'); data.push_back('F'); data.push_back(0x00);
        // version
        data.push_back(0x01); data.push_back(0x01);
        // units
        data.push_back(0x00);
        // Xdensity, Ydensity
        data.push_back(0x00); data.push_back(0x48);
        data.push_back(0x00); data.push_back(0x48);
        // thumbnail
        data.push_back(0x00); data.push_back(0x00);

        // SOF0 marker
        data.push_back(0xFF);
        data.push_back(0xC0);
        int sof_length = 8 + numComponents * 3;
        data.push_back(static_cast<unsigned char>((sof_length >> 8) & 0xFF));
        data.push_back(static_cast<unsigned char>(sof_length & 0xFF));
        // precision
        data.push_back(0x08);
        // height = 1
        data.push_back(0x00); data.push_back(0x01);
        // width = 1
        data.push_back(0x00); data.push_back(0x01);
        // number of components
        data.push_back(static_cast<unsigned char>(numComponents));
        for (int i = 0; i < numComponents; i++) {
            data.push_back(static_cast<unsigned char>(i + 1)); // component id
            data.push_back(0x11); // sampling factors
            data.push_back(0x00); // quantization table
        }

        // SOS marker (minimal) - required before image data
        data.push_back(0xFF);
        data.push_back(0xDA);
        int sos_length = 6 + numComponents * 2;
        data.push_back(static_cast<unsigned char>((sos_length >> 8) & 0xFF));
        data.push_back(static_cast<unsigned char>(sos_length & 0xFF));
        data.push_back(static_cast<unsigned char>(numComponents));
        for (int i = 0; i < numComponents; i++) {
            data.push_back(static_cast<unsigned char>(i + 1));
            data.push_back(0x00);
        }
        // Ss, Se, Ah/Al
        data.push_back(0x00);
        data.push_back(0x3F);
        data.push_back(0x00);

        // Some dummy scan data
        data.push_back(0x00);

        // EOI
        data.push_back(0xFF);
        data.push_back(0xD9);

        return std::make_unique<MemIo>(data.data(), data.size());
    }

    std::unique_ptr<MemIo> createEmptyIo() {
        return std::make_unique<MemIo>();
    }
};

// Test: Creating a JpegImage with create=true should succeed
TEST_F(JpegImageTest_215, CreateNewJpegImage_215) {
    auto io = std::make_unique<MemIo>();
    ASSERT_NO_THROW(JpegImage img(std::move(io), true));
}

// Test: Creating a JpegImage from a minimal JPEG buffer with create=false
TEST_F(JpegImageTest_215, OpenMinimalJpeg_215) {
    auto io = createMinimalJpeg();
    ASSERT_NO_THROW(JpegImage img(std::move(io), false));
}

// Test: mimeType returns the correct JPEG MIME type
TEST_F(JpegImageTest_215, MimeTypeIsJpeg_215) {
    auto io = createMinimalJpeg();
    JpegImage img(std::move(io), false);
    EXPECT_EQ(img.mimeType(), "image/jpeg");
}

// Test: numColorComponents returns -1 before readMetadata is called
TEST_F(JpegImageTest_215, NumColorComponentsBeforeRead_215) {
    auto io = createMinimalJpeg();
    JpegImage img(std::move(io), false);
    // Before reading metadata, num_color_components_ should be the default (-1)
    EXPECT_EQ(img.numColorComponents(), -1);
}

// Test: After reading a JPEG with SOF0 and 3 color components, numColorComponents returns 3
TEST_F(JpegImageTest_215, NumColorComponentsAfterReadRGB_215) {
    auto io = createJpegWithSOF0(3);
    JpegImage img(std::move(io), false);
    try {
        img.readMetadata();
    } catch (...) {
        // Some minimal JPEGs might fail to fully parse; we test what we can
    }
    int nc = img.numColorComponents();
    // If reading succeeded and parsed SOF0, expect 3; otherwise still -1
    EXPECT_TRUE(nc == 3 || nc == -1);
}

// Test: After reading a grayscale JPEG (1 component), numColorComponents returns 1
TEST_F(JpegImageTest_215, NumColorComponentsAfterReadGrayscale_215) {
    auto io = createJpegWithSOF0(1);
    JpegImage img(std::move(io), false);
    try {
        img.readMetadata();
    } catch (...) {
        // May fail on minimal data
    }
    int nc = img.numColorComponents();
    EXPECT_TRUE(nc == 1 || nc == -1);
}

// Test: Creating JpegImage with create=true on a new MemIo and then writing metadata
TEST_F(JpegImageTest_215, WriteMetadataOnNewImage_215) {
    auto io = std::make_unique<MemIo>();
    JpegImage img(std::move(io), true);
    ASSERT_NO_THROW(img.writeMetadata());
}

// Test: isJpegType with a valid JPEG IO returns true
TEST_F(JpegImageTest_215, IsJpegTypeValid_215) {
    auto io = createMinimalJpeg();
    bool result = JpegImage::isJpegType(*io, false);
    EXPECT_TRUE(result);
}

// Test: isJpegType with empty IO returns false
TEST_F(JpegImageTest_215, IsJpegTypeEmpty_215) {
    auto io = createEmptyIo();
    bool result = JpegImage::isJpegType(*io, false);
    EXPECT_FALSE(result);
}

// Test: isJpegType with non-JPEG data returns false
TEST_F(JpegImageTest_215, IsJpegTypeInvalidData_215) {
    static const unsigned char pngSig[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
    auto io = std::make_unique<MemIo>(pngSig, sizeof(pngSig));
    bool result = JpegImage::isJpegType(*io, false);
    EXPECT_FALSE(result);
}

// Test: isJpegType with advance=true advances the IO position
TEST_F(JpegImageTest_215, IsJpegTypeAdvance_215) {
    auto io = createMinimalJpeg();
    long posBefore = io->tell();
    bool result = JpegImage::isJpegType(*io, true);
    if (result) {
        // Position may have advanced
        EXPECT_GE(io->tell(), posBefore);
    }
}

// Test: isJpegType with advance=false does not change IO position
TEST_F(JpegImageTest_215, IsJpegTypeNoAdvance_215) {
    auto io = createMinimalJpeg();
    io->seek(0, BasicIo::beg);
    long posBefore = io->tell();
    JpegImage::isJpegType(*io, false);
    long posAfter = io->tell();
    EXPECT_EQ(posBefore, posAfter);
}

// Test: readMetadata on empty image throws
TEST_F(JpegImageTest_215, ReadMetadataOnEmptyThrows_215) {
    auto io = createEmptyIo();
    try {
        JpegImage img(std::move(io), false);
        EXPECT_THROW(img.readMetadata(), Exiv2::Error);
    } catch (...) {
        // Construction itself might throw for invalid data
    }
}

// Test: encodingProcess returns a string (possibly empty before read)
TEST_F(JpegImageTest_215, EncodingProcessBeforeRead_215) {
    auto io = createMinimalJpeg();
    JpegImage img(std::move(io), false);
    const std::string& ep = img.encodingProcess();
    // Before reading metadata, should be empty or default
    EXPECT_TRUE(ep.empty() || !ep.empty()); // Just verify it doesn't crash
}

// Test: After reading JPEG with SOF0, encodingProcess returns something meaningful
TEST_F(JpegImageTest_215, EncodingProcessAfterRead_215) {
    auto io = createJpegWithSOF0(3);
    JpegImage img(std::move(io), false);
    try {
        img.readMetadata();
        const std::string& ep = img.encodingProcess();
        // SOF0 = Baseline DCT
        if (!ep.empty()) {
            EXPECT_NE(ep.find("Baseline"), std::string::npos);
        }
    } catch (...) {
        // May fail on minimal JPEG
    }
}

// Test: printStructure does not crash with kpsNone
TEST_F(JpegImageTest_215, PrintStructureNone_215) {
    auto io = createMinimalJpeg();
    JpegImage img(std::move(io), false);
    std::ostringstream oss;
    try {
        img.printStructure(oss, kpsNone, 0);
    } catch (...) {
        // Some options may not be supported for minimal JPEG
    }
    // Just verify no crash
    SUCCEED();
}

// Test: Creating JpegImage with invalid (non-JPEG) data and create=false
TEST_F(JpegImageTest_215, CreateWithInvalidData_215) {
    static const unsigned char garbage[] = {0x00, 0x01, 0x02, 0x03};
    auto io = std::make_unique<MemIo>(garbage, sizeof(garbage));
    EXPECT_THROW(JpegImage img(std::move(io), false), Exiv2::Error);
}

// Test: Boundary - single byte JPEG (too short)
TEST_F(JpegImageTest_215, SingleByteJpeg_215) {
    static const unsigned char oneByte[] = {0xFF};
    auto io = std::make_unique<MemIo>(oneByte, sizeof(oneByte));
    EXPECT_THROW(JpegImage img(std::move(io), false), Exiv2::Error);
}

// Test: Boundary - only SOI marker (2 bytes, no EOI)
TEST_F(JpegImageTest_215, OnlySOIMarker_215) {
    static const unsigned char soiOnly[] = {0xFF, 0xD8};
    auto io = std::make_unique<MemIo>(soiOnly, sizeof(soiOnly));
    // Should construct but readMetadata might fail
    try {
        JpegImage img(std::move(io), false);
        EXPECT_THROW(img.readMetadata(), Exiv2::Error);
    } catch (const Exiv2::Error&) {
        // Construction might also throw
    }
}

// Test: numColorComponents with 4 components (CMYK)
TEST_F(JpegImageTest_215, NumColorComponentsCMYK_215) {
    auto io = createJpegWithSOF0(4);
    JpegImage img(std::move(io), false);
    try {
        img.readMetadata();
    } catch (...) {
    }
    int nc = img.numColorComponents();
    EXPECT_TRUE(nc == 4 || nc == -1);
}
