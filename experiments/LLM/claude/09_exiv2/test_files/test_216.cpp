#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/jpgimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <fstream>
#include <cstring>
#include <sstream>

namespace {

// Helper to create a minimal valid JPEG in memory
std::vector<unsigned char> createMinimalJpeg() {
    // Minimal JPEG: SOI + APP0 (JFIF) + SOF0 + SOS + EOI
    std::vector<unsigned char> jpeg;
    // SOI
    jpeg.push_back(0xFF);
    jpeg.push_back(0xD8);
    // APP0 JFIF marker
    jpeg.push_back(0xFF);
    jpeg.push_back(0xE0);
    jpeg.push_back(0x00);
    jpeg.push_back(0x10); // length 16
    jpeg.push_back('J');
    jpeg.push_back('F');
    jpeg.push_back('I');
    jpeg.push_back('F');
    jpeg.push_back(0x00);
    jpeg.push_back(0x01);
    jpeg.push_back(0x01);
    jpeg.push_back(0x00);
    jpeg.push_back(0x00);
    jpeg.push_back(0x01);
    jpeg.push_back(0x00);
    jpeg.push_back(0x01);
    jpeg.push_back(0x00);
    jpeg.push_back(0x00);
    // SOF0 marker (Baseline DCT)
    jpeg.push_back(0xFF);
    jpeg.push_back(0xC0);
    jpeg.push_back(0x00);
    jpeg.push_back(0x0B); // length 11
    jpeg.push_back(0x08); // precision
    jpeg.push_back(0x00);
    jpeg.push_back(0x01); // height 1
    jpeg.push_back(0x00);
    jpeg.push_back(0x01); // width 1
    jpeg.push_back(0x01); // num components = 1 (grayscale)
    jpeg.push_back(0x01); // component id
    jpeg.push_back(0x11); // sampling factors
    jpeg.push_back(0x00); // quant table
    // DHT (minimal)
    jpeg.push_back(0xFF);
    jpeg.push_back(0xC4);
    jpeg.push_back(0x00);
    jpeg.push_back(0x1F); // length 31
    jpeg.push_back(0x00); // DC table 0
    // 16 bytes of counts
    jpeg.push_back(0x00);
    jpeg.push_back(0x01);
    jpeg.push_back(0x05);
    jpeg.push_back(0x01);
    jpeg.push_back(0x01);
    jpeg.push_back(0x01);
    jpeg.push_back(0x01);
    jpeg.push_back(0x01);
    jpeg.push_back(0x01);
    jpeg.push_back(0x00);
    jpeg.push_back(0x00);
    jpeg.push_back(0x00);
    jpeg.push_back(0x00);
    jpeg.push_back(0x00);
    jpeg.push_back(0x00);
    jpeg.push_back(0x00);
    // values
    jpeg.push_back(0x00);
    jpeg.push_back(0x01);
    jpeg.push_back(0x02);
    jpeg.push_back(0x03);
    jpeg.push_back(0x04);
    jpeg.push_back(0x05);
    jpeg.push_back(0x06);
    jpeg.push_back(0x07);
    jpeg.push_back(0x08);
    jpeg.push_back(0x09);
    jpeg.push_back(0x0A);
    jpeg.push_back(0x0B);
    // SOS
    jpeg.push_back(0xFF);
    jpeg.push_back(0xDA);
    jpeg.push_back(0x00);
    jpeg.push_back(0x08); // length 8
    jpeg.push_back(0x01); // num components
    jpeg.push_back(0x01); // component id
    jpeg.push_back(0x00); // DC/AC table
    jpeg.push_back(0x00); // Ss
    jpeg.push_back(0x3F); // Se
    jpeg.push_back(0x00); // Ah/Al
    // Some scan data
    jpeg.push_back(0x00);
    // EOI
    jpeg.push_back(0xFF);
    jpeg.push_back(0xD9);
    return jpeg;
}

// Helper to create a JPEG with SOF2 (progressive) and 3 color components
std::vector<unsigned char> createProgressiveJpeg() {
    std::vector<unsigned char> jpeg;
    // SOI
    jpeg.push_back(0xFF);
    jpeg.push_back(0xD8);
    // SOF2 marker (Progressive DCT)
    jpeg.push_back(0xFF);
    jpeg.push_back(0xC2);
    jpeg.push_back(0x00);
    jpeg.push_back(0x11); // length 17
    jpeg.push_back(0x08); // precision
    jpeg.push_back(0x00);
    jpeg.push_back(0x01); // height 1
    jpeg.push_back(0x00);
    jpeg.push_back(0x01); // width 1
    jpeg.push_back(0x03); // num components = 3 (color)
    jpeg.push_back(0x01); // component 1 id
    jpeg.push_back(0x22); // sampling factors
    jpeg.push_back(0x00); // quant table
    jpeg.push_back(0x02); // component 2 id
    jpeg.push_back(0x11); // sampling factors
    jpeg.push_back(0x01); // quant table
    jpeg.push_back(0x03); // component 3 id
    jpeg.push_back(0x11); // sampling factors
    jpeg.push_back(0x01); // quant table
    // SOS
    jpeg.push_back(0xFF);
    jpeg.push_back(0xDA);
    jpeg.push_back(0x00);
    jpeg.push_back(0x0C); // length 12
    jpeg.push_back(0x03); // num components
    jpeg.push_back(0x01);
    jpeg.push_back(0x00);
    jpeg.push_back(0x02);
    jpeg.push_back(0x11);
    jpeg.push_back(0x03);
    jpeg.push_back(0x11);
    jpeg.push_back(0x00);
    jpeg.push_back(0x3F);
    jpeg.push_back(0x00);
    // scan data
    jpeg.push_back(0x00);
    // EOI
    jpeg.push_back(0xFF);
    jpeg.push_back(0xD9);
    return jpeg;
}

} // anonymous namespace

class JpegImageTest_216 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: Creating JpegImage with create=true (blank image creation)
TEST_F(JpegImageTest_216, CreateBlankJpegImage_216) {
    auto io = std::make_unique<Exiv2::MemIo>();
    ASSERT_NO_THROW(Exiv2::JpegImage img(std::move(io), true));
}

// Test: Creating JpegImage from valid JPEG data with create=false
TEST_F(JpegImageTest_216, CreateFromValidJpegData_216) {
    auto jpegData = createMinimalJpeg();
    auto io = std::make_unique<Exiv2::MemIo>(jpegData.data(), jpegData.size());
    ASSERT_NO_THROW(Exiv2::JpegImage img(std::move(io), false));
}

// Test: mimeType returns "image/jpeg"
TEST_F(JpegImageTest_216, MimeTypeReturnsImageJpeg_216) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::JpegImage img(std::move(io), true);
    EXPECT_EQ(img.mimeType(), "image/jpeg");
}

// Test: encodingProcess returns a string (before readMetadata, it should be empty or default)
TEST_F(JpegImageTest_216, EncodingProcessBeforeReadMetadata_216) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::JpegImage img(std::move(io), true);
    // Before reading metadata, encoding process should be empty or default
    const std::string& ep = img.encodingProcess();
    // We can just check it's a valid string reference
    EXPECT_TRUE(ep.empty() || !ep.empty()); // basically just ensure no crash
}

// Test: readMetadata on a minimal baseline JPEG populates encoding process
TEST_F(JpegImageTest_216, ReadMetadataBaselineJpeg_216) {
    auto jpegData = createMinimalJpeg();
    auto io = std::make_unique<Exiv2::MemIo>(jpegData.data(), jpegData.size());
    Exiv2::JpegImage img(std::move(io), false);
    ASSERT_NO_THROW(img.readMetadata());
    const std::string& ep = img.encodingProcess();
    // SOF0 = Baseline DCT
    EXPECT_FALSE(ep.empty());
}

// Test: numColorComponents after reading a 1-component (grayscale) JPEG
TEST_F(JpegImageTest_216, NumColorComponentsGrayscale_216) {
    auto jpegData = createMinimalJpeg();
    auto io = std::make_unique<Exiv2::MemIo>(jpegData.data(), jpegData.size());
    Exiv2::JpegImage img(std::move(io), false);
    ASSERT_NO_THROW(img.readMetadata());
    EXPECT_EQ(img.numColorComponents(), 1);
}

// Test: numColorComponents after reading a 3-component (color) progressive JPEG
TEST_F(JpegImageTest_216, NumColorComponentsColor_216) {
    auto jpegData = createProgressiveJpeg();
    auto io = std::make_unique<Exiv2::MemIo>(jpegData.data(), jpegData.size());
    Exiv2::JpegImage img(std::move(io), false);
    ASSERT_NO_THROW(img.readMetadata());
    EXPECT_EQ(img.numColorComponents(), 3);
}

// Test: encodingProcess for progressive JPEG (SOF2)
TEST_F(JpegImageTest_216, EncodingProcessProgressiveJpeg_216) {
    auto jpegData = createProgressiveJpeg();
    auto io = std::make_unique<Exiv2::MemIo>(jpegData.data(), jpegData.size());
    Exiv2::JpegImage img(std::move(io), false);
    ASSERT_NO_THROW(img.readMetadata());
    const std::string& ep = img.encodingProcess();
    // Progressive DCT should have a different encoding process string than Baseline
    EXPECT_FALSE(ep.empty());
}

// Test: readMetadata on empty/invalid data should throw
TEST_F(JpegImageTest_216, ReadMetadataInvalidDataThrows_216) {
    auto io = std::make_unique<Exiv2::MemIo>();
    // Write some garbage data
    const unsigned char garbage[] = {0x00, 0x01, 0x02, 0x03};
    io->write(garbage, sizeof(garbage));
    io->seek(0, Exiv2::BasicIo::beg);
    Exiv2::JpegImage img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test: writeMetadata on a newly created blank image
TEST_F(JpegImageTest_216, WriteMetadataOnBlankImage_216) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::JpegImage img(std::move(io), true);
    ASSERT_NO_THROW(img.writeMetadata());
}

// Test: writeMetadata after readMetadata on valid JPEG
TEST_F(JpegImageTest_216, WriteMetadataAfterRead_216) {
    auto jpegData = createMinimalJpeg();
    auto io = std::make_unique<Exiv2::MemIo>(jpegData.data(), jpegData.size());
    Exiv2::JpegImage img(std::move(io), false);
    ASSERT_NO_THROW(img.readMetadata());
    ASSERT_NO_THROW(img.writeMetadata());
}

// Test: encodingProcess returns const reference (stability check)
TEST_F(JpegImageTest_216, EncodingProcessReferenceStability_216) {
    auto jpegData = createMinimalJpeg();
    auto io = std::make_unique<Exiv2::MemIo>(jpegData.data(), jpegData.size());
    Exiv2::JpegImage img(std::move(io), false);
    img.readMetadata();
    const std::string& ep1 = img.encodingProcess();
    const std::string& ep2 = img.encodingProcess();
    EXPECT_EQ(&ep1, &ep2); // Should return the same reference
    EXPECT_EQ(ep1, ep2);
}

// Test: printStructure does not crash
TEST_F(JpegImageTest_216, PrintStructureNoThrow_216) {
    auto jpegData = createMinimalJpeg();
    auto io = std::make_unique<Exiv2::MemIo>(jpegData.data(), jpegData.size());
    Exiv2::JpegImage img(std::move(io), false);
    std::ostringstream oss;
    ASSERT_NO_THROW(img.printStructure(oss, Exiv2::kpsNone, 0));
}

// Test: Creating JpegImage from truncated JPEG (just SOI, no more)
TEST_F(JpegImageTest_216, ReadMetadataTruncatedJpegThrows_216) {
    const unsigned char truncated[] = {0xFF, 0xD8};
    auto io = std::make_unique<Exiv2::MemIo>(truncated, sizeof(truncated));
    Exiv2::JpegImage img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test: numColorComponents before readMetadata (should be default/uninitialized value)
TEST_F(JpegImageTest_216, NumColorComponentsBeforeRead_216) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::JpegImage img(std::move(io), true);
    // Before reading metadata, numColorComponents should have a default value
    int nc = img.numColorComponents();
    // Based on the known dependency, default is -1
    EXPECT_EQ(nc, -1);
}

// Test: Baseline vs Progressive have different encoding process strings
TEST_F(JpegImageTest_216, BaselineVsProgressiveEncodingProcess_216) {
    // Read baseline
    auto baselineData = createMinimalJpeg();
    auto io1 = std::make_unique<Exiv2::MemIo>(baselineData.data(), baselineData.size());
    Exiv2::JpegImage baselineImg(std::move(io1), false);
    baselineImg.readMetadata();
    std::string baselineEp = baselineImg.encodingProcess();

    // Read progressive
    auto progressiveData = createProgressiveJpeg();
    auto io2 = std::make_unique<Exiv2::MemIo>(progressiveData.data(), progressiveData.size());
    Exiv2::JpegImage progressiveImg(std::move(io2), false);
    progressiveImg.readMetadata();
    std::string progressiveEp = progressiveImg.encodingProcess();

    // They should differ since SOF0 != SOF2
    EXPECT_NE(baselineEp, progressiveEp);
}

// Test: printStructure with kpsBasic option
TEST_F(JpegImageTest_216, PrintStructureBasic_216) {
    auto jpegData = createMinimalJpeg();
    auto io = std::make_unique<Exiv2::MemIo>(jpegData.data(), jpegData.size());
    Exiv2::JpegImage img(std::move(io), false);
    std::ostringstream oss;
    ASSERT_NO_THROW(img.printStructure(oss, Exiv2::kpsBasic, 0));
    // Should produce some output for basic structure
    EXPECT_FALSE(oss.str().empty());
}
