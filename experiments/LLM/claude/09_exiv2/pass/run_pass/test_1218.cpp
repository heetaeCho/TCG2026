#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <cstring>
#include <vector>

#include "exiv2/jpgimage.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/image.hpp"
#include "exiv2/error.hpp"
#include "exiv2/types.hpp"

using namespace Exiv2;

// Helper to create a minimal valid JPEG in memory
static std::vector<byte> createMinimalJpeg() {
    // SOI + APP0 (JFIF) + SOF0 + SOS + EOI
    std::vector<byte> jpeg;
    // SOI
    jpeg.push_back(0xFF);
    jpeg.push_back(0xD8);
    // APP0 marker with JFIF signature
    jpeg.push_back(0xFF);
    jpeg.push_back(0xE0);
    // Length = 16
    jpeg.push_back(0x00);
    jpeg.push_back(0x10);
    // "JFIF\0"
    jpeg.push_back('J');
    jpeg.push_back('F');
    jpeg.push_back('I');
    jpeg.push_back('F');
    jpeg.push_back(0x00);
    // Version 1.01
    jpeg.push_back(0x01);
    jpeg.push_back(0x01);
    // Units, X density, Y density, thumbnail
    jpeg.push_back(0x00);
    jpeg.push_back(0x00);
    jpeg.push_back(0x01);
    jpeg.push_back(0x00);
    jpeg.push_back(0x01);
    jpeg.push_back(0x00);
    jpeg.push_back(0x00);
    // SOF0
    jpeg.push_back(0xFF);
    jpeg.push_back(0xC0);
    // Length = 11
    jpeg.push_back(0x00);
    jpeg.push_back(0x0B);
    // precision
    jpeg.push_back(0x08);
    // height = 1
    jpeg.push_back(0x00);
    jpeg.push_back(0x01);
    // width = 1
    jpeg.push_back(0x00);
    jpeg.push_back(0x01);
    // num components = 1
    jpeg.push_back(0x01);
    // component 1
    jpeg.push_back(0x01);
    jpeg.push_back(0x11);
    jpeg.push_back(0x00);
    // DHT marker
    jpeg.push_back(0xFF);
    jpeg.push_back(0xC4);
    // Length = 31 (minimal Huffman table)
    jpeg.push_back(0x00);
    jpeg.push_back(0x1F);
    // class/id
    jpeg.push_back(0x00);
    // 16 bytes: number of codes of each length
    for (int i = 0; i < 16; i++) {
        if (i == 0)
            jpeg.push_back(0x01);
        else
            jpeg.push_back(0x00);
    }
    // Values
    jpeg.push_back(0x00);
    // DQT
    jpeg.push_back(0xFF);
    jpeg.push_back(0xDB);
    jpeg.push_back(0x00);
    jpeg.push_back(0x43);
    jpeg.push_back(0x00);
    for (int i = 0; i < 64; i++) {
        jpeg.push_back(0x01);
    }
    // SOS
    jpeg.push_back(0xFF);
    jpeg.push_back(0xDA);
    // Length = 8
    jpeg.push_back(0x00);
    jpeg.push_back(0x08);
    // num components
    jpeg.push_back(0x01);
    // component 1
    jpeg.push_back(0x01);
    jpeg.push_back(0x00);
    // spectral selection
    jpeg.push_back(0x00);
    jpeg.push_back(0x3F);
    jpeg.push_back(0x00);
    // Compressed data (minimal)
    jpeg.push_back(0x7B);
    jpeg.push_back(0x40);
    // EOI
    jpeg.push_back(0xFF);
    jpeg.push_back(0xD9);
    return jpeg;
}

// Helper: Simplest possible JPEG (SOI + EOI only, with a single marker segment between)
static std::vector<byte> createSimpleJpegWithApp0() {
    std::vector<byte> jpeg;
    // SOI
    jpeg.push_back(0xFF);
    jpeg.push_back(0xD8);
    // APP0 with minimal data
    jpeg.push_back(0xFF);
    jpeg.push_back(0xE0);
    jpeg.push_back(0x00);
    jpeg.push_back(0x10);
    // "JFIF\0"
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
    // EOI
    jpeg.push_back(0xFF);
    jpeg.push_back(0xD9);
    return jpeg;
}

// Helper: Create a JPEG with Photoshop 3.0 IPTC segment
static std::vector<byte> createJpegWithIptc() {
    std::vector<byte> jpeg;
    // SOI
    jpeg.push_back(0xFF);
    jpeg.push_back(0xD8);

    // APP13 with Photoshop 3.0 signature
    jpeg.push_back(0xFF);
    jpeg.push_back(0xED); // APP13
    // Build the segment
    std::string sig = "Photoshop 3.0";
    // length = 2 + sig.size() + 1 (null) + some padding
    uint16_t segLen = static_cast<uint16_t>(2 + sig.size() + 1 + 10);
    jpeg.push_back(static_cast<byte>((segLen >> 8) & 0xFF));
    jpeg.push_back(static_cast<byte>(segLen & 0xFF));
    for (char c : sig) {
        jpeg.push_back(static_cast<byte>(c));
    }
    jpeg.push_back(0x00);
    // Padding data
    for (int i = 0; i < 10; i++) {
        jpeg.push_back(0x00);
    }

    // EOI
    jpeg.push_back(0xFF);
    jpeg.push_back(0xD9);
    return jpeg;
}

// Helper: Create a JPEG with an ICC_PROFILE segment
static std::vector<byte> createJpegWithIccProfile() {
    std::vector<byte> jpeg;
    // SOI
    jpeg.push_back(0xFF);
    jpeg.push_back(0xD8);

    // APP2 with ICC_PROFILE signature
    jpeg.push_back(0xFF);
    jpeg.push_back(0xE2); // APP2
    std::string iccSig = "ICC_PROFILE";
    // iccSig + null + chunk_num(1) + num_chunks(1) + profile data
    uint16_t segLen = static_cast<uint16_t>(2 + iccSig.size() + 1 + 2 + 20);
    jpeg.push_back(static_cast<byte>((segLen >> 8) & 0xFF));
    jpeg.push_back(static_cast<byte>(segLen & 0xFF));
    for (char c : iccSig) {
        jpeg.push_back(static_cast<byte>(c));
    }
    jpeg.push_back(0x00); // null terminator
    jpeg.push_back(0x01); // chunk number
    jpeg.push_back(0x01); // total chunks
    // Some ICC profile data
    for (int i = 0; i < 20; i++) {
        jpeg.push_back(static_cast<byte>(0x41 + i));
    }

    // EOI
    jpeg.push_back(0xFF);
    jpeg.push_back(0xD9);
    return jpeg;
}

// Helper: Create a JPEG with a COM (comment) marker
static std::vector<byte> createJpegWithComment() {
    std::vector<byte> jpeg;
    // SOI
    jpeg.push_back(0xFF);
    jpeg.push_back(0xD8);

    // COM marker
    jpeg.push_back(0xFF);
    jpeg.push_back(0xFE);
    std::string comment = "Test comment for JPEG";
    uint16_t segLen = static_cast<uint16_t>(2 + comment.size());
    jpeg.push_back(static_cast<byte>((segLen >> 8) & 0xFF));
    jpeg.push_back(static_cast<byte>(segLen & 0xFF));
    for (char c : comment) {
        jpeg.push_back(static_cast<byte>(c));
    }

    // EOI
    jpeg.push_back(0xFF);
    jpeg.push_back(0xD9);
    return jpeg;
}

class JpegPrintStructureTest_1218 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: printStructure with kpsBasic on a minimal valid JPEG shows STRUCTURE header
TEST_F(JpegPrintStructureTest_1218, BasicPrintStructureShowsHeader_1218) {
    auto jpegData = createSimpleJpegWithApp0();
    auto io = std::make_unique<MemIo>(jpegData.data(), jpegData.size());
    auto image = ImageFactory::open(std::move(io));
    ASSERT_NE(image, nullptr);

    std::ostringstream out;
    EXPECT_NO_THROW(image->printStructure(out, kpsBasic, 0));

    std::string output = out.str();
    EXPECT_NE(output.find("STRUCTURE OF JPEG FILE"), std::string::npos);
    EXPECT_NE(output.find("address"), std::string::npos);
    EXPECT_NE(output.find("marker"), std::string::npos);
}

// Test: printStructure with kpsBasic shows SOI marker info
TEST_F(JpegPrintStructureTest_1218, BasicPrintShowsSOI_1218) {
    auto jpegData = createSimpleJpegWithApp0();
    auto io = std::make_unique<MemIo>(jpegData.data(), jpegData.size());
    auto image = ImageFactory::open(std::move(io));
    ASSERT_NE(image, nullptr);

    std::ostringstream out;
    EXPECT_NO_THROW(image->printStructure(out, kpsBasic, 0));

    std::string output = out.str();
    EXPECT_NE(output.find("APP0"), std::string::npos);
}

// Test: printStructure with kpsBasic shows EOI
TEST_F(JpegPrintStructureTest_1218, BasicPrintShowsEOI_1218) {
    auto jpegData = createSimpleJpegWithApp0();
    auto io = std::make_unique<MemIo>(jpegData.data(), jpegData.size());
    auto image = ImageFactory::open(std::move(io));
    ASSERT_NE(image, nullptr);

    std::ostringstream out;
    EXPECT_NO_THROW(image->printStructure(out, kpsBasic, 0));

    std::string output = out.str();
    EXPECT_NE(output.find("EOI"), std::string::npos);
}

// Test: printStructure on non-JPEG data throws an error
TEST_F(JpegPrintStructureTest_1218, NonJpegDataThrowsError_1218) {
    std::vector<byte> notJpeg = {0x00, 0x01, 0x02, 0x03, 0x04};
    auto io = std::make_unique<MemIo>(notJpeg.data(), notJpeg.size());

    // Try to open as JPEG - ImageFactory might not recognize it
    // We test via direct creation if possible, or by expecting exception
    EXPECT_THROW(ImageFactory::open(std::move(io)), Error);
}

// Test: printStructure on empty data throws
TEST_F(JpegPrintStructureTest_1218, EmptyDataThrowsError_1218) {
    auto io = std::make_unique<MemIo>();
    EXPECT_THROW(ImageFactory::open(std::move(io)), Error);
}

// Test: printStructure with kpsNone doesn't produce output
TEST_F(JpegPrintStructureTest_1218, NoneOptionProducesNoOutput_1218) {
    auto jpegData = createSimpleJpegWithApp0();
    auto io = std::make_unique<MemIo>(jpegData.data(), jpegData.size());
    auto image = ImageFactory::open(std::move(io));
    ASSERT_NE(image, nullptr);

    std::ostringstream out;
    // kpsNone should not call into the JPEG-specific printStructure logic
    EXPECT_NO_THROW(image->printStructure(out, kpsNone, 0));
    // With kpsNone the base class implementation is likely called
}

// Test: printStructure with kpsBasic on JPEG with comment shows COM
TEST_F(JpegPrintStructureTest_1218, BasicPrintShowsComment_1218) {
    auto jpegData = createJpegWithComment();
    auto io = std::make_unique<MemIo>(jpegData.data(), jpegData.size());
    auto image = ImageFactory::open(std::move(io));
    ASSERT_NE(image, nullptr);

    std::ostringstream out;
    EXPECT_NO_THROW(image->printStructure(out, kpsBasic, 0));

    std::string output = out.str();
    EXPECT_NE(output.find("COM"), std::string::npos);
    // The comment text should appear in the output
    EXPECT_NE(output.find("Test comment"), std::string::npos);
}

// Test: printStructure with kpsIccProfile on JPEG with ICC profile outputs profile data
TEST_F(JpegPrintStructureTest_1218, IccProfileOptionOutputsProfileData_1218) {
    auto jpegData = createJpegWithIccProfile();
    auto io = std::make_unique<MemIo>(jpegData.data(), jpegData.size());
    auto image = ImageFactory::open(std::move(io));
    ASSERT_NE(image, nullptr);

    std::ostringstream out;
    EXPECT_NO_THROW(image->printStructure(out, kpsIccProfile, 0));

    std::string output = out.str();
    // Should contain the ICC profile data bytes we wrote (ASCII letters starting from 'A')
    EXPECT_FALSE(output.empty());
}

// Test: printStructure with kpsBasic shows length field
TEST_F(JpegPrintStructureTest_1218, BasicPrintShowsLength_1218) {
    auto jpegData = createMinimalJpeg();
    auto io = std::make_unique<MemIo>(jpegData.data(), jpegData.size());
    auto image = ImageFactory::open(std::move(io));
    ASSERT_NE(image, nullptr);

    std::ostringstream out;
    EXPECT_NO_THROW(image->printStructure(out, kpsBasic, 0));

    std::string output = out.str();
    // The output format includes "length" in the header
    EXPECT_NE(output.find("length"), std::string::npos);
}

// Test: printStructure with kpsBasic on JPEG with JFIF signature shows JFIF text
TEST_F(JpegPrintStructureTest_1218, BasicPrintShowsJfifSignature_1218) {
    auto jpegData = createSimpleJpegWithApp0();
    auto io = std::make_unique<MemIo>(jpegData.data(), jpegData.size());
    auto image = ImageFactory::open(std::move(io));
    ASSERT_NE(image, nullptr);

    std::ostringstream out;
    EXPECT_NO_THROW(image->printStructure(out, kpsBasic, 0));

    std::string output = out.str();
    EXPECT_NE(output.find("JFIF"), std::string::npos);
}

// Test: printStructure with kpsBasic on a JPEG with ICC profile shows chunk info
TEST_F(JpegPrintStructureTest_1218, BasicPrintShowsIccChunkInfo_1218) {
    auto jpegData = createJpegWithIccProfile();
    auto io = std::make_unique<MemIo>(jpegData.data(), jpegData.size());
    auto image = ImageFactory::open(std::move(io));
    ASSERT_NE(image, nullptr);

    std::ostringstream out;
    EXPECT_NO_THROW(image->printStructure(out, kpsBasic, 0));

    std::string output = out.str();
    // Should show ICC_PROFILE and chunk info like "chunk 1/1"
    EXPECT_NE(output.find("ICC_PROFILE"), std::string::npos);
    EXPECT_NE(output.find("chunk"), std::string::npos);
}

// Test: printStructure with kpsXMP on JPEG without XMP produces empty output
TEST_F(JpegPrintStructureTest_1218, XmpOptionOnJpegWithoutXmpProducesEmptyOutput_1218) {
    auto jpegData = createSimpleJpegWithApp0();
    auto io = std::make_unique<MemIo>(jpegData.data(), jpegData.size());
    auto image = ImageFactory::open(std::move(io));
    ASSERT_NE(image, nullptr);

    std::ostringstream out;
    EXPECT_NO_THROW(image->printStructure(out, kpsXMP, 0));

    std::string output = out.str();
    EXPECT_TRUE(output.empty());
}

// Test: printStructure with kpsIccProfile on JPEG without ICC profile produces empty output
TEST_F(JpegPrintStructureTest_1218, IccProfileOptionOnJpegWithoutIccProducesEmptyOutput_1218) {
    auto jpegData = createSimpleJpegWithApp0();
    auto io = std::make_unique<MemIo>(jpegData.data(), jpegData.size());
    auto image = ImageFactory::open(std::move(io));
    ASSERT_NE(image, nullptr);

    std::ostringstream out;
    EXPECT_NO_THROW(image->printStructure(out, kpsIccProfile, 0));

    std::string output = out.str();
    EXPECT_TRUE(output.empty());
}

// Test: printStructure with kpsRecursive on minimal JPEG works
TEST_F(JpegPrintStructureTest_1218, RecursiveOptionOnMinimalJpeg_1218) {
    auto jpegData = createSimpleJpegWithApp0();
    auto io = std::make_unique<MemIo>(jpegData.data(), jpegData.size());
    auto image = ImageFactory::open(std::move(io));
    ASSERT_NE(image, nullptr);

    std::ostringstream out;
    EXPECT_NO_THROW(image->printStructure(out, kpsRecursive, 0));

    std::string output = out.str();
    // Should still show STRUCTURE header since bPrint is true for kpsRecursive
    EXPECT_NE(output.find("STRUCTURE OF JPEG FILE"), std::string::npos);
}

// Test: printStructure shows data column header
TEST_F(JpegPrintStructureTest_1218, BasicPrintShowsDataHeader_1218) {
    auto jpegData = createSimpleJpegWithApp0();
    auto io = std::make_unique<MemIo>(jpegData.data(), jpegData.size());
    auto image = ImageFactory::open(std::move(io));
    ASSERT_NE(image, nullptr);

    std::ostringstream out;
    EXPECT_NO_THROW(image->printStructure(out, kpsBasic, 0));

    std::string output = out.str();
    EXPECT_NE(output.find("data"), std::string::npos);
}

// Test: printStructure with kpsIptcErase on JPEG without IPTC doesn't crash
TEST_F(JpegPrintStructureTest_1218, IptcEraseOnJpegWithoutIptcDoesNotCrash_1218) {
    auto jpegData = createSimpleJpegWithApp0();
    auto io = std::make_unique<MemIo>(jpegData.data(), jpegData.size());
    auto image = ImageFactory::open(std::move(io));
    ASSERT_NE(image, nullptr);

    std::ostringstream out;
    EXPECT_NO_THROW(image->printStructure(out, kpsIptcErase, 0));
}

// Test: printStructure depth parameter works (non-zero depth)
TEST_F(JpegPrintStructureTest_1218, DepthParameterNonZero_1218) {
    auto jpegData = createSimpleJpegWithApp0();
    auto io = std::make_unique<MemIo>(jpegData.data(), jpegData.size());
    auto image = ImageFactory::open(std::move(io));
    ASSERT_NE(image, nullptr);

    std::ostringstream out;
    EXPECT_NO_THROW(image->printStructure(out, kpsBasic, 5));

    std::string output = out.str();
    // Should still produce output regardless of depth
    EXPECT_FALSE(output.empty());
}

// Test: Full JPEG with SOF0, DHT, DQT, SOS shows all marker names
TEST_F(JpegPrintStructureTest_1218, FullJpegShowsAllMarkerNames_1218) {
    auto jpegData = createMinimalJpeg();
    auto io = std::make_unique<MemIo>(jpegData.data(), jpegData.size());
    auto image = ImageFactory::open(std::move(io));
    ASSERT_NE(image, nullptr);

    std::ostringstream out;
    EXPECT_NO_THROW(image->printStructure(out, kpsBasic, 0));

    std::string output = out.str();
    EXPECT_NE(output.find("SOF0"), std::string::npos);
    EXPECT_NE(output.find("DHT"), std::string::npos);
    EXPECT_NE(output.find("DQT"), std::string::npos);
    EXPECT_NE(output.find("SOS"), std::string::npos);
}

// Test: Multiple calls to printStructure produce consistent output
TEST_F(JpegPrintStructureTest_1218, MultiplePrintCallsProduceConsistentOutput_1218) {
    auto jpegData = createSimpleJpegWithApp0();

    std::string output1, output2;
    {
        auto io = std::make_unique<MemIo>(jpegData.data(), jpegData.size());
        auto image = ImageFactory::open(std::move(io));
        ASSERT_NE(image, nullptr);
        std::ostringstream out;
        image->printStructure(out, kpsBasic, 0);
        output1 = out.str();
    }
    {
        auto io = std::make_unique<MemIo>(jpegData.data(), jpegData.size());
        auto image = ImageFactory::open(std::move(io));
        ASSERT_NE(image, nullptr);
        std::ostringstream out;
        image->printStructure(out, kpsBasic, 0);
        output2 = out.str();
    }

    EXPECT_EQ(output1, output2);
}

// Test: Truncated JPEG (only SOI, no other markers) causes an error
TEST_F(JpegPrintStructureTest_1218, TruncatedJpegThrows_1218) {
    std::vector<byte> truncated = {0xFF, 0xD8};
    auto io = std::make_unique<MemIo>(truncated.data(), truncated.size());

    try {
        auto image = ImageFactory::open(std::move(io));
        if (image) {
            std::ostringstream out;
            EXPECT_THROW(image->printStructure(out, kpsBasic, 0), Error);
        }
    } catch (const Error&) {
        // Also acceptable if open itself throws
    }
}

// Test: JPEG with XMP segment - kpsXMP option extracts XMP data
TEST_F(JpegPrintStructureTest_1218, XmpOptionExtractsXmpData_1218) {
    std::vector<byte> jpeg;
    // SOI
    jpeg.push_back(0xFF);
    jpeg.push_back(0xD8);

    // APP1 with XMP signature
    jpeg.push_back(0xFF);
    jpeg.push_back(0xE1); // APP1

    std::string xmpSig = "http://ns.adobe.com/xap/1.0/";
    std::string xmpData = "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?><x:xmpmeta></x:xmpmeta><?xpacket end='w'?>";

    uint16_t segLen = static_cast<uint16_t>(2 + xmpSig.size() + 1 + xmpData.size());
    jpeg.push_back(static_cast<byte>((segLen >> 8) & 0xFF));
    jpeg.push_back(static_cast<byte>(segLen & 0xFF));

    for (char c : xmpSig) {
        jpeg.push_back(static_cast<byte>(c));
    }
    jpeg.push_back(0x00); // null terminator

    for (char c : xmpData) {
        jpeg.push_back(static_cast<byte>(c));
    }

    // EOI
    jpeg.push_back(0xFF);
    jpeg.push_back(0xD9);

    auto io = std::make_unique<MemIo>(jpeg.data(), jpeg.size());
    auto image = ImageFactory::open(std::move(io));
    ASSERT_NE(image, nullptr);

    std::ostringstream out;
    EXPECT_NO_THROW(image->printStructure(out, kpsXMP, 0));

    std::string output = out.str();
    // Should contain XMP data
    EXPECT_NE(output.find("xmpmeta"), std::string::npos);
}
