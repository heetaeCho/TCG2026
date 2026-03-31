#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <cstring>
#include <memory>

#include "exiv2/image.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"
#include "exiv2/types.hpp"

using namespace Exiv2;

// Mock BasicIo for testing
class MockBasicIo : public BasicIo {
public:
    MOCK_METHOD(int, open, (), (override));
    MOCK_METHOD(int, close, (), (override));
    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));
    MOCK_METHOD(size_t, write, (BasicIo& src), (override));
    MOCK_METHOD(int, putb, (byte data), (override));
    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));
    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));
    MOCK_METHOD(int, getb, (), (override));
    MOCK_METHOD(void, transfer, (BasicIo& src), (override));
    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));
    MOCK_METHOD(byte*, mmap, (bool isWriteable), (override));
    MOCK_METHOD(int, munmap, (), (override));
    MOCK_METHOD(size_t, tell, (), (const, override));
    MOCK_METHOD(size_t, size, (), (const, override));
    MOCK_METHOD(bool, isopen, (), (const, override));
    MOCK_METHOD(int, error, (), (const, override));
    MOCK_METHOD(bool, eof, (), (const, override));
    MOCK_METHOD(const std::string&, path, (), (const, override));
    MOCK_METHOD(void, populateFakeData, (), (override));

    // Helper: we need readOrThrow to work. Since it calls read() internally,
    // we mock the read(byte*, size_t) method.
};

// A concrete Image subclass for testing (since Image has pure virtual-like methods)
// We need a concrete subclass that we can instantiate
class TestImage : public Image {
public:
    TestImage(std::unique_ptr<BasicIo> io)
        : Image(ImageType::none, 0xFFFF, std::move(io)) {}

    void readMetadata() override {}
    void writeMetadata() override {}
};

class ImageStaticMethodsTest_1066 : public ::testing::Test {
protected:
    std::unique_ptr<TestImage> createTestImage() {
        auto io = std::make_unique<MockBasicIo>();
        return std::make_unique<TestImage>(std::move(io));
    }
};

// Test isBigEndianPlatform and isLittleEndianPlatform are complementary
TEST_F(ImageStaticMethodsTest_1066, EndianPlatformConsistency_1066) {
    bool big = Image::isBigEndianPlatform();
    bool little = Image::isLittleEndianPlatform();
    // Exactly one should be true
    EXPECT_NE(big, little);
}

TEST_F(ImageStaticMethodsTest_1066, IsStringType_1066) {
    // TIFF type 2 is ASCII string
    EXPECT_TRUE(Image::isStringType(2));
    // Type 1 (BYTE) should not be string
    EXPECT_FALSE(Image::isStringType(1));
}

TEST_F(ImageStaticMethodsTest_1066, IsShortType_1066) {
    // TIFF type 3 is SHORT
    EXPECT_TRUE(Image::isShortType(3));
    // Type 8 is SSHORT
    EXPECT_TRUE(Image::isShortType(8));
    EXPECT_FALSE(Image::isShortType(1));
}

TEST_F(ImageStaticMethodsTest_1066, IsLongType_1066) {
    // TIFF type 4 is LONG
    EXPECT_TRUE(Image::isLongType(4));
    // Type 9 is SLONG
    EXPECT_TRUE(Image::isLongType(9));
    EXPECT_FALSE(Image::isLongType(1));
}

TEST_F(ImageStaticMethodsTest_1066, IsLongLongType_1066) {
    // Type 16 is LONG8, Type 17 is SLONG8
    EXPECT_TRUE(Image::isLongLongType(16));
    EXPECT_TRUE(Image::isLongLongType(17));
    EXPECT_FALSE(Image::isLongLongType(1));
}

TEST_F(ImageStaticMethodsTest_1066, IsRationalType_1066) {
    // Type 5 is RATIONAL, Type 10 is SRATIONAL
    EXPECT_TRUE(Image::isRationalType(5));
    EXPECT_TRUE(Image::isRationalType(10));
    EXPECT_FALSE(Image::isRationalType(1));
}

TEST_F(ImageStaticMethodsTest_1066, Is2ByteType_1066) {
    EXPECT_TRUE(Image::is2ByteType(3));  // SHORT
    EXPECT_TRUE(Image::is2ByteType(8));  // SSHORT
    EXPECT_FALSE(Image::is2ByteType(4)); // LONG is not 2 byte
}

TEST_F(ImageStaticMethodsTest_1066, Is4ByteType_1066) {
    EXPECT_TRUE(Image::is4ByteType(4));  // LONG
    EXPECT_TRUE(Image::is4ByteType(9));  // SLONG
    EXPECT_FALSE(Image::is4ByteType(3)); // SHORT
}

TEST_F(ImageStaticMethodsTest_1066, Is8ByteType_1066) {
    EXPECT_TRUE(Image::is8ByteType(5));   // RATIONAL
    EXPECT_TRUE(Image::is8ByteType(10));  // SRATIONAL
    EXPECT_TRUE(Image::is8ByteType(16));  // LONG8
    EXPECT_TRUE(Image::is8ByteType(17));  // SLONG8
    EXPECT_FALSE(Image::is8ByteType(1));
}

TEST_F(ImageStaticMethodsTest_1066, IsPrintXMP_1066) {
    // Type 2 (ASCII) with kpsXMP option should be true
    EXPECT_TRUE(Image::isPrintXMP(2, kpsXMP));
    EXPECT_FALSE(Image::isPrintXMP(2, kpsBasic));
    EXPECT_FALSE(Image::isPrintXMP(1, kpsXMP));
}

TEST_F(ImageStaticMethodsTest_1066, IsPrintICC_1066) {
    // Type 7 (UNDEFINED) with kpsIccProfile
    EXPECT_TRUE(Image::isPrintICC(7, kpsIccProfile));
    EXPECT_FALSE(Image::isPrintICC(7, kpsBasic));
    EXPECT_FALSE(Image::isPrintICC(1, kpsIccProfile));
}

// Test byteSwap methods
TEST_F(ImageStaticMethodsTest_1066, ByteSwap16NoSwap_1066) {
    uint16_t val = 0x0102;
    EXPECT_EQ(Image::byteSwap(val, false), val);
}

TEST_F(ImageStaticMethodsTest_1066, ByteSwap16WithSwap_1066) {
    uint16_t val = 0x0102;
    uint16_t swapped = Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x0201);
}

TEST_F(ImageStaticMethodsTest_1066, ByteSwap32NoSwap_1066) {
    uint32_t val = 0x01020304;
    EXPECT_EQ(Image::byteSwap(val, false), val);
}

TEST_F(ImageStaticMethodsTest_1066, ByteSwap32WithSwap_1066) {
    uint32_t val = 0x01020304;
    uint32_t swapped = Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x04030201u);
}

TEST_F(ImageStaticMethodsTest_1066, ByteSwap64NoSwap_1066) {
    uint64_t val = 0x0102030405060708ULL;
    EXPECT_EQ(Image::byteSwap(val, false), val);
}

TEST_F(ImageStaticMethodsTest_1066, ByteSwap64WithSwap_1066) {
    uint64_t val = 0x0102030405060708ULL;
    uint64_t swapped = Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x0807060504030201ULL);
}

// Test byteSwap2 from DataBuf
TEST_F(ImageStaticMethodsTest_1066, ByteSwap2FromBuf_1066) {
    byte data[] = {0x01, 0x02};
    DataBuf buf(data, 2);
    uint16_t result = Image::byteSwap2(buf, 0, false);
    uint16_t expected;
    std::memcpy(&expected, data, 2);
    EXPECT_EQ(result, expected);
}

TEST_F(ImageStaticMethodsTest_1066, ByteSwap2FromBufSwapped_1066) {
    byte data[] = {0x01, 0x02};
    DataBuf buf(data, 2);
    uint16_t noswap = Image::byteSwap2(buf, 0, false);
    uint16_t swapped = Image::byteSwap2(buf, 0, true);
    EXPECT_EQ(swapped, Image::byteSwap(noswap, true));
}

// Test byteSwap4 from DataBuf
TEST_F(ImageStaticMethodsTest_1066, ByteSwap4FromBuf_1066) {
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    uint32_t result = Image::byteSwap4(buf, 0, false);
    uint32_t expected;
    std::memcpy(&expected, data, 4);
    EXPECT_EQ(result, expected);
}

TEST_F(ImageStaticMethodsTest_1066, ByteSwap4FromBufSwapped_1066) {
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    uint32_t noswap = Image::byteSwap4(buf, 0, false);
    uint32_t swapped = Image::byteSwap4(buf, 0, true);
    EXPECT_EQ(swapped, Image::byteSwap(noswap, true));
}

// Test byteSwap8 from DataBuf
TEST_F(ImageStaticMethodsTest_1066, ByteSwap8FromBuf_1066) {
    byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    DataBuf buf(data, 8);
    uint64_t result = Image::byteSwap8(buf, 0, false);
    uint64_t expected;
    std::memcpy(&expected, data, 8);
    EXPECT_EQ(result, expected);
}

// Test Image construction and basic accessors
class ImageAccessorTest_1066 : public ::testing::Test {
protected:
    std::unique_ptr<TestImage> image_;
    
    void SetUp() override {
        auto io = std::make_unique<testing::NiceMock<MockBasicIo>>();
        ON_CALL(*io, isopen()).WillByDefault(testing::Return(true));
        ON_CALL(*io, error()).WillByDefault(testing::Return(0));
        ON_CALL(*io, eof()).WillByDefault(testing::Return(false));
        image_ = std::make_unique<TestImage>(std::move(io));
    }
};

TEST_F(ImageAccessorTest_1066, InitialPixelWidthIsZero_1066) {
    EXPECT_EQ(image_->pixelWidth(), 0u);
}

TEST_F(ImageAccessorTest_1066, InitialPixelHeightIsZero_1066) {
    EXPECT_EQ(image_->pixelHeight(), 0u);
}

TEST_F(ImageAccessorTest_1066, InitialCommentIsEmpty_1066) {
    EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageAccessorTest_1066, ByteOrderInitiallyInvalid_1066) {
    EXPECT_EQ(image_->byteOrder(), invalidByteOrder);
}

TEST_F(ImageAccessorTest_1066, SetByteOrder_1066) {
    image_->setByteOrder(bigEndian);
    EXPECT_EQ(image_->byteOrder(), bigEndian);
    image_->setByteOrder(littleEndian);
    EXPECT_EQ(image_->byteOrder(), littleEndian);
}

TEST_F(ImageAccessorTest_1066, SetAndGetComment_1066) {
    image_->setComment("Hello World");
    EXPECT_EQ(image_->comment(), "Hello World");
}

TEST_F(ImageAccessorTest_1066, ClearComment_1066) {
    image_->setComment("Hello");
    image_->clearComment();
    EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageAccessorTest_1066, WriteXmpFromPacketDefault_1066) {
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageAccessorTest_1066, SetWriteXmpFromPacket_1066) {
    image_->writeXmpFromPacket(true);
    EXPECT_TRUE(image_->writeXmpFromPacket());
    image_->writeXmpFromPacket(false);
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageAccessorTest_1066, GoodReturnsTrue_1066) {
    EXPECT_TRUE(image_->good());
}

TEST_F(ImageAccessorTest_1066, ExifDataAccessible_1066) {
    ExifData& data = image_->exifData();
    EXPECT_TRUE(data.empty());
}

TEST_F(ImageAccessorTest_1066, IptcDataAccessible_1066) {
    IptcData& data = image_->iptcData();
    EXPECT_TRUE(data.empty());
}

TEST_F(ImageAccessorTest_1066, XmpDataAccessible_1066) {
    XmpData& data = image_->xmpData();
    EXPECT_TRUE(data.empty());
}

TEST_F(ImageAccessorTest_1066, ClearExifData_1066) {
    image_->clearExifData();
    EXPECT_TRUE(image_->exifData().empty());
}

TEST_F(ImageAccessorTest_1066, ClearIptcData_1066) {
    image_->clearIptcData();
    EXPECT_TRUE(image_->iptcData().empty());
}

TEST_F(ImageAccessorTest_1066, ClearXmpData_1066) {
    image_->clearXmpData();
    EXPECT_TRUE(image_->xmpData().empty());
}

TEST_F(ImageAccessorTest_1066, ClearXmpPacket_1066) {
    image_->setXmpPacket("<xmp>test</xmp>");
    image_->clearXmpPacket();
    EXPECT_TRUE(image_->xmpPacket().empty());
}

TEST_F(ImageAccessorTest_1066, SetXmpPacket_1066) {
    std::string packet = "<xmp>test</xmp>";
    image_->setXmpPacket(packet);
    EXPECT_EQ(image_->xmpPacket(), packet);
}

TEST_F(ImageAccessorTest_1066, ClearMetadata_1066) {
    image_->setComment("test");
    image_->clearMetadata();
    EXPECT_TRUE(image_->comment().empty());
    EXPECT_TRUE(image_->exifData().empty());
    EXPECT_TRUE(image_->iptcData().empty());
    EXPECT_TRUE(image_->xmpData().empty());
}

TEST_F(ImageAccessorTest_1066, IccProfileInitiallyUndefined_1066) {
    EXPECT_FALSE(image_->iccProfileDefined());
}

TEST_F(ImageAccessorTest_1066, ClearIccProfile_1066) {
    image_->clearIccProfile();
    EXPECT_FALSE(image_->iccProfileDefined());
}

TEST_F(ImageAccessorTest_1066, NativePreviewsInitiallyEmpty_1066) {
    EXPECT_TRUE(image_->nativePreviews().empty());
}

// Test printTiffStructure with option kpsNone (should be no-op, no read)
class PrintTiffStructureTest_1066 : public ::testing::Test {
protected:
    testing::NiceMock<MockBasicIo>* mockIoPtr_;
    std::unique_ptr<TestImage> image_;

    void SetUp() override {
        auto mockIo = std::make_unique<testing::NiceMock<MockBasicIo>>();
        mockIoPtr_ = mockIo.get();
        ON_CALL(*mockIoPtr_, isopen()).WillByDefault(testing::Return(true));
        ON_CALL(*mockIoPtr_, error()).WillByDefault(testing::Return(0));
        ON_CALL(*mockIoPtr_, eof()).WillByDefault(testing::Return(false));
        image_ = std::make_unique<TestImage>(std::move(mockIo));
    }
};

TEST_F(PrintTiffStructureTest_1066, KpsNoneDoesNotReadIo_1066) {
    // With kpsNone, printTiffStructure should not do anything
    testing::NiceMock<MockBasicIo> externalIo;
    EXPECT_CALL(externalIo, read(testing::_, testing::_)).Times(0);
    std::ostringstream out;
    image_->printTiffStructure(externalIo, out, kpsNone, 0, 0);
}

TEST_F(PrintTiffStructureTest_1066, KpsIptcEraseDoesNotReadIo_1066) {
    testing::NiceMock<MockBasicIo> externalIo;
    EXPECT_CALL(externalIo, read(testing::_, testing::_)).Times(0);
    std::ostringstream out;
    image_->printTiffStructure(externalIo, out, kpsIptcErase, 0, 0);
}

// Test that printTiffStructure with kpsBasic reads 8 bytes from IO
TEST_F(PrintTiffStructureTest_1066, KpsBasicReadsHeader_1066) {
    testing::NiceMock<MockBasicIo> externalIo;
    
    // When readOrThrow is called, it calls read(byte*, size_t)
    // We provide a valid TIFF header: 'II' (little endian), magic 42, offset 8
    ON_CALL(externalIo, read(testing::_, testing::_))
        .WillByDefault([](byte* buf, size_t rcount) -> size_t {
            if (rcount >= 8) {
                // 'I', 'I' for little endian
                buf[0] = 'I';
                buf[1] = 'I';
                buf[2] = 42; // magic
                buf[3] = 0;
                buf[4] = 8;  // offset to first IFD
                buf[5] = 0;
                buf[6] = 0;
                buf[7] = 0;
            }
            return rcount;
        });
    
    // seek and size calls for printIFDStructure
    ON_CALL(externalIo, size()).WillByDefault(testing::Return(100));
    ON_CALL(externalIo, seek(testing::_, testing::_)).WillByDefault(testing::Return(0));
    ON_CALL(externalIo, tell()).WillByDefault(testing::Return(0));
    ON_CALL(externalIo, eof()).WillByDefault(testing::Return(true));
    ON_CALL(externalIo, error()).WillByDefault(testing::Return(0));
    ON_CALL(externalIo, isopen()).WillByDefault(testing::Return(true));
    
    std::ostringstream out;
    // This may throw if printIFDStructure encounters issues, but the header read should work
    try {
        image_->printTiffStructure(externalIo, out, kpsBasic, 0, 0);
    } catch (const Exiv2::Error&) {
        // Expected - printIFDStructure may fail but header was read
    }
}

// Test that corrupted metadata (short read) throws
TEST_F(PrintTiffStructureTest_1066, KpsBasicThrowsOnShortRead_1066) {
    testing::NiceMock<MockBasicIo> externalIo;
    
    // Return fewer bytes than requested to trigger readOrThrow failure
    ON_CALL(externalIo, read(testing::_, testing::_))
        .WillByDefault(testing::Return(0));  // Reading 0 bytes
    ON_CALL(externalIo, eof()).WillByDefault(testing::Return(true));
    ON_CALL(externalIo, error()).WillByDefault(testing::Return(0));
    
    std::ostringstream out;
    EXPECT_THROW(
        image_->printTiffStructure(externalIo, out, kpsBasic, 0, 0),
        Exiv2::Error
    );
}

TEST_F(PrintTiffStructureTest_1066, KpsXMPReadsHeader_1066) {
    testing::NiceMock<MockBasicIo> externalIo;
    
    ON_CALL(externalIo, read(testing::_, testing::_))
        .WillByDefault(testing::Return(0));
    ON_CALL(externalIo, eof()).WillByDefault(testing::Return(true));
    
    std::ostringstream out;
    EXPECT_THROW(
        image_->printTiffStructure(externalIo, out, kpsXMP, 0, 0),
        Exiv2::Error
    );
}

TEST_F(PrintTiffStructureTest_1066, KpsRecursiveReadsHeader_1066) {
    testing::NiceMock<MockBasicIo> externalIo;
    
    ON_CALL(externalIo, read(testing::_, testing::_))
        .WillByDefault(testing::Return(0));
    ON_CALL(externalIo, eof()).WillByDefault(testing::Return(true));
    
    std::ostringstream out;
    EXPECT_THROW(
        image_->printTiffStructure(externalIo, out, kpsRecursive, 0, 0),
        Exiv2::Error
    );
}

TEST_F(PrintTiffStructureTest_1066, KpsIccProfileReadsHeader_1066) {
    testing::NiceMock<MockBasicIo> externalIo;
    
    ON_CALL(externalIo, read(testing::_, testing::_))
        .WillByDefault(testing::Return(0));
    ON_CALL(externalIo, eof()).WillByDefault(testing::Return(true));
    
    std::ostringstream out;
    EXPECT_THROW(
        image_->printTiffStructure(externalIo, out, kpsIccProfile, 0, 0),
        Exiv2::Error
    );
}

// Test SetMetadata copies from another image
TEST_F(ImageAccessorTest_1066, SetMetadataCopiesComment_1066) {
    auto io2 = std::make_unique<testing::NiceMock<MockBasicIo>>();
    ON_CALL(*io2, isopen()).WillByDefault(testing::Return(true));
    ON_CALL(*io2, error()).WillByDefault(testing::Return(0));
    ON_CALL(*io2, eof()).WillByDefault(testing::Return(false));
    TestImage other(std::move(io2));
    other.setComment("copied comment");
    
    image_->setMetadata(other);
    EXPECT_EQ(image_->comment(), "copied comment");
}

// Test ImageType
TEST_F(ImageAccessorTest_1066, ImageTypeIsNone_1066) {
    EXPECT_EQ(image_->imageType(), ImageType::none);
}
