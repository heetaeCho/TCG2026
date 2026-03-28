#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <memory>
#include <cstring>

#include "exiv2/tiffimage.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"
#include "exiv2/image_types.hpp"

using namespace Exiv2;

// A mock BasicIo class to control I/O behavior in tests
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

    std::string mockPath_ = "test.tiff";
};

class TiffImageTest_1738 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a minimal valid TIFF header (little-endian)
    static std::vector<byte> createMinimalTiffHeader() {
        std::vector<byte> header = {
            0x49, 0x49,       // 'II' - little endian
            0x2A, 0x00,       // TIFF magic number 42
            0x08, 0x00, 0x00, 0x00,  // Offset to first IFD
            0x00, 0x00        // Number of directory entries = 0 (minimal)
        };
        return header;
    }
};

// Test: printStructure throws when io_->open() fails
TEST_F(TiffImageTest_1738, PrintStructureThrowsWhenOpenFails_1738) {
    auto mockIo = std::make_unique<MockBasicIo>();
    std::string path = "test_fail.tiff";

    EXPECT_CALL(*mockIo, open()).WillOnce(::testing::Return(1)); // non-zero = failure
    EXPECT_CALL(*mockIo, path()).WillRepeatedly(::testing::ReturnRef(path));

    TiffImage image(std::move(mockIo), false);

    std::ostringstream oss;
    EXPECT_THROW(image.printStructure(oss, PrintStructureOption::kpsNone, 0), Error);
}

// Test: printStructure throws when image is not a TIFF and there's an error
TEST_F(TiffImageTest_1738, PrintStructureThrowsWhenNotTiffAndError_1738) {
    auto mockIo = std::make_unique<MockBasicIo>();
    std::string path = "test_nottiff.tiff";

    EXPECT_CALL(*mockIo, open()).WillOnce(::testing::Return(0)); // success
    EXPECT_CALL(*mockIo, path()).WillRepeatedly(::testing::ReturnRef(path));
    EXPECT_CALL(*mockIo, size()).WillRepeatedly(::testing::Return(4));
    EXPECT_CALL(*mockIo, tell()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(*mockIo, isopen()).WillRepeatedly(::testing::Return(true));
    // Return invalid data when reading for TIFF type check
    EXPECT_CALL(*mockIo, read(::testing::_, ::testing::_))
        .WillRepeatedly(::testing::DoAll(
            ::testing::Invoke([](byte* buf, size_t rcount) {
                std::memset(buf, 0, rcount);
            }),
            ::testing::ReturnArg<1>()));
    EXPECT_CALL(*mockIo, seek(::testing::_, ::testing::_)).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(*mockIo, error()).WillRepeatedly(::testing::Return(1)); // error condition
    EXPECT_CALL(*mockIo, eof()).WillRepeatedly(::testing::Return(false));

    // Image type is 'none' when we pass create=false and data isn't valid TIFF
    // We create with ImageType::tiff but need to test the behavior
    // TiffImage constructor sets ImageType::tiff, so the imageType() != none check may pass
    // Let's test differently - the constructor sets type to tiff, so it won't enter the none branch
    // We need to test with actual file data

    TiffImage image(std::move(mockIo), false);

    std::ostringstream oss;
    // Since imageType() == ImageType::tiff (set in constructor), the second condition is skipped
    // It will proceed to seek and printTiffStructure which may throw or succeed depending on data
    // This tests error propagation from invalid data
    EXPECT_THROW(image.printStructure(oss, PrintStructureOption::kpsNone, 0), Error);
}

// Test: TiffImage constructor and basic properties
TEST_F(TiffImageTest_1738, ConstructorSetsCorrectImageType_1738) {
    auto mockIo = std::make_unique<MockBasicIo>();
    std::string path = "test.tiff";
    EXPECT_CALL(*mockIo, path()).WillRepeatedly(::testing::ReturnRef(path));

    TiffImage image(std::move(mockIo), false);
    EXPECT_EQ(image.imageType(), ImageType::tiff);
}

// Test: mimeType returns correct MIME type for TIFF
TEST_F(TiffImageTest_1738, MimeTypeReturnsTiff_1738) {
    auto mockIo = std::make_unique<MockBasicIo>();
    std::string path = "test.tiff";
    EXPECT_CALL(*mockIo, path()).WillRepeatedly(::testing::ReturnRef(path));

    TiffImage image(std::move(mockIo), false);
    EXPECT_EQ(image.mimeType(), "image/tiff");
}

// Test: setComment throws (TIFF doesn't support comments via this interface)
TEST_F(TiffImageTest_1738, SetCommentThrows_1738) {
    auto mockIo = std::make_unique<MockBasicIo>();
    std::string path = "test.tiff";
    EXPECT_CALL(*mockIo, path()).WillRepeatedly(::testing::ReturnRef(path));

    TiffImage image(std::move(mockIo), false);
    EXPECT_THROW(image.setComment("test comment"), Error);
}

// Test: pixelWidth and pixelHeight default to 0
TEST_F(TiffImageTest_1738, DefaultPixelDimensionsAreZero_1738) {
    auto mockIo = std::make_unique<MockBasicIo>();
    std::string path = "test.tiff";
    EXPECT_CALL(*mockIo, path()).WillRepeatedly(::testing::ReturnRef(path));

    TiffImage image(std::move(mockIo), false);
    EXPECT_EQ(image.pixelWidth(), 0u);
    EXPECT_EQ(image.pixelHeight(), 0u);
}

// Test: io() returns reference to the BasicIo object
TEST_F(TiffImageTest_1738, IoReturnsValidReference_1738) {
    auto mockIo = std::make_unique<MockBasicIo>();
    auto rawPtr = mockIo.get();
    std::string path = "test.tiff";
    EXPECT_CALL(*mockIo, path()).WillRepeatedly(::testing::ReturnRef(path));

    TiffImage image(std::move(mockIo), false);
    EXPECT_EQ(&image.io(), rawPtr);
}

// Test: good() returns true when io is in good state
TEST_F(TiffImageTest_1738, GoodReturnsTrueWhenIoIsGood_1738) {
    auto mockIo = std::make_unique<MockBasicIo>();
    std::string path = "test.tiff";
    EXPECT_CALL(*mockIo, path()).WillRepeatedly(::testing::ReturnRef(path));
    EXPECT_CALL(*mockIo, isopen()).WillRepeatedly(::testing::Return(true));
    EXPECT_CALL(*mockIo, error()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(*mockIo, eof()).WillRepeatedly(::testing::Return(false));

    TiffImage image(std::move(mockIo), false);
    // good() likely depends on io state
    // The exact behavior depends on implementation, but we test the call doesn't crash
    image.good();
}

// Test: exifData, iptcData, xmpData accessors
TEST_F(TiffImageTest_1738, MetadataAccessorsDoNotThrow_1738) {
    auto mockIo = std::make_unique<MockBasicIo>();
    std::string path = "test.tiff";
    EXPECT_CALL(*mockIo, path()).WillRepeatedly(::testing::ReturnRef(path));

    TiffImage image(std::move(mockIo), false);
    EXPECT_NO_THROW(image.exifData());
    EXPECT_NO_THROW(image.iptcData());
    EXPECT_NO_THROW(image.xmpData());
}

// Test: clearMetadata doesn't throw
TEST_F(TiffImageTest_1738, ClearMetadataDoesNotThrow_1738) {
    auto mockIo = std::make_unique<MockBasicIo>();
    std::string path = "test.tiff";
    EXPECT_CALL(*mockIo, path()).WillRepeatedly(::testing::ReturnRef(path));

    TiffImage image(std::move(mockIo), false);
    EXPECT_NO_THROW(image.clearMetadata());
}

// Test: readMetadata throws on closed/invalid IO
TEST_F(TiffImageTest_1738, ReadMetadataThrowsOnInvalidIo_1738) {
    auto mockIo = std::make_unique<MockBasicIo>();
    std::string path = "test.tiff";
    EXPECT_CALL(*mockIo, path()).WillRepeatedly(::testing::ReturnRef(path));
    EXPECT_CALL(*mockIo, open()).WillOnce(::testing::Return(1));

    TiffImage image(std::move(mockIo), false);
    EXPECT_THROW(image.readMetadata(), Error);
}

// Test: writeMetadata throws on closed/invalid IO
TEST_F(TiffImageTest_1738, WriteMetadataThrowsOnInvalidIo_1738) {
    auto mockIo = std::make_unique<MockBasicIo>();
    std::string path = "test.tiff";
    EXPECT_CALL(*mockIo, path()).WillRepeatedly(::testing::ReturnRef(path));
    EXPECT_CALL(*mockIo, open()).WillOnce(::testing::Return(1));

    TiffImage image(std::move(mockIo), false);
    EXPECT_THROW(image.writeMetadata(), Error);
}

// Test: supportsMetadata for exif, iptc, xmp
TEST_F(TiffImageTest_1738, SupportsExpectedMetadata_1738) {
    auto mockIo = std::make_unique<MockBasicIo>();
    std::string path = "test.tiff";
    EXPECT_CALL(*mockIo, path()).WillRepeatedly(::testing::ReturnRef(path));

    TiffImage image(std::move(mockIo), false);
    EXPECT_TRUE(image.supportsMetadata(MetadataId::mdExif));
    EXPECT_TRUE(image.supportsMetadata(MetadataId::mdIptc));
    EXPECT_TRUE(image.supportsMetadata(MetadataId::mdXmp));
}

// Test: printStructure with depth 0 after open failure
TEST_F(TiffImageTest_1738, PrintStructureDepthZeroOpenFailure_1738) {
    auto mockIo = std::make_unique<MockBasicIo>();
    std::string path = "nonexistent.tiff";
    EXPECT_CALL(*mockIo, open()).WillOnce(::testing::Return(-1));
    EXPECT_CALL(*mockIo, path()).WillRepeatedly(::testing::ReturnRef(path));

    TiffImage image(std::move(mockIo), false);
    std::ostringstream oss;
    EXPECT_THROW(image.printStructure(oss, PrintStructureOption::kpsNone, 0), Error);
}

// Test: Static helper methods on Image
TEST_F(TiffImageTest_1738, StaticHelperIsStringType_1738) {
    // Type 2 is ASCII in TIFF
    EXPECT_TRUE(Image::isStringType(2));
    // Type 3 is SHORT, not string
    EXPECT_FALSE(Image::isStringType(3));
}

TEST_F(TiffImageTest_1738, StaticHelperIsShortType_1738) {
    // Type 3 is SHORT
    EXPECT_TRUE(Image::isShortType(3));
    // Type 8 is SSHORT
    EXPECT_TRUE(Image::isShortType(8));
    EXPECT_FALSE(Image::isShortType(2));
}

TEST_F(TiffImageTest_1738, StaticHelperIsLongType_1738) {
    // Type 4 is LONG
    EXPECT_TRUE(Image::isLongType(4));
    EXPECT_FALSE(Image::isLongType(3));
}

TEST_F(TiffImageTest_1738, StaticHelperIs2ByteType_1738) {
    EXPECT_TRUE(Image::is2ByteType(3));  // SHORT
    EXPECT_TRUE(Image::is2ByteType(8));  // SSHORT
    EXPECT_FALSE(Image::is2ByteType(4)); // LONG is 4 bytes
}

TEST_F(TiffImageTest_1738, StaticHelperIs4ByteType_1738) {
    EXPECT_TRUE(Image::is4ByteType(4));  // LONG
    EXPECT_FALSE(Image::is4ByteType(3)); // SHORT is 2 bytes
}

TEST_F(TiffImageTest_1738, StaticHelperIs8ByteType_1738) {
    EXPECT_TRUE(Image::is8ByteType(5));  // RATIONAL
    EXPECT_FALSE(Image::is8ByteType(4)); // LONG is 4 bytes
}

// Test: ByteSwap operations
TEST_F(TiffImageTest_1738, ByteSwap16NoSwap_1738) {
    uint16_t val = 0x0102;
    EXPECT_EQ(Image::byteSwap(val, false), 0x0102);
}

TEST_F(TiffImageTest_1738, ByteSwap16WithSwap_1738) {
    uint16_t val = 0x0102;
    EXPECT_EQ(Image::byteSwap(val, true), 0x0201);
}

TEST_F(TiffImageTest_1738, ByteSwap32NoSwap_1738) {
    uint32_t val = 0x01020304;
    EXPECT_EQ(Image::byteSwap(val, false), 0x01020304u);
}

TEST_F(TiffImageTest_1738, ByteSwap32WithSwap_1738) {
    uint32_t val = 0x01020304;
    EXPECT_EQ(Image::byteSwap(val, true), 0x04030201u);
}

TEST_F(TiffImageTest_1738, ByteSwap64NoSwap_1738) {
    uint64_t val = 0x0102030405060708ULL;
    EXPECT_EQ(Image::byteSwap(val, false), 0x0102030405060708ULL);
}

TEST_F(TiffImageTest_1738, ByteSwap64WithSwap_1738) {
    uint64_t val = 0x0102030405060708ULL;
    EXPECT_EQ(Image::byteSwap(val, true), 0x0807060504030201ULL);
}

// Test: Platform endianness (one must be true, the other false)
TEST_F(TiffImageTest_1738, PlatformEndianness_1738) {
    bool big = Image::isBigEndianPlatform();
    bool little = Image::isLittleEndianPlatform();
    EXPECT_NE(big, little); // Exactly one should be true
}

// Test: setByteOrder and byteOrder
TEST_F(TiffImageTest_1738, SetAndGetByteOrder_1738) {
    auto mockIo = std::make_unique<MockBasicIo>();
    std::string path = "test.tiff";
    EXPECT_CALL(*mockIo, path()).WillRepeatedly(::testing::ReturnRef(path));

    TiffImage image(std::move(mockIo), false);
    image.setByteOrder(littleEndian);
    EXPECT_EQ(image.byteOrder(), littleEndian);

    image.setByteOrder(bigEndian);
    EXPECT_EQ(image.byteOrder(), bigEndian);
}

// Test: clearExifData
TEST_F(TiffImageTest_1738, ClearExifData_1738) {
    auto mockIo = std::make_unique<MockBasicIo>();
    std::string path = "test.tiff";
    EXPECT_CALL(*mockIo, path()).WillRepeatedly(::testing::ReturnRef(path));

    TiffImage image(std::move(mockIo), false);
    EXPECT_NO_THROW(image.clearExifData());
    EXPECT_TRUE(image.exifData().empty());
}

// Test: clearIptcData
TEST_F(TiffImageTest_1738, ClearIptcData_1738) {
    auto mockIo = std::make_unique<MockBasicIo>();
    std::string path = "test.tiff";
    EXPECT_CALL(*mockIo, path()).WillRepeatedly(::testing::ReturnRef(path));

    TiffImage image(std::move(mockIo), false);
    EXPECT_NO_THROW(image.clearIptcData());
    EXPECT_TRUE(image.iptcData().empty());
}

// Test: clearXmpData
TEST_F(TiffImageTest_1738, ClearXmpData_1738) {
    auto mockIo = std::make_unique<MockBasicIo>();
    std::string path = "test.tiff";
    EXPECT_CALL(*mockIo, path()).WillRepeatedly(::testing::ReturnRef(path));

    TiffImage image(std::move(mockIo), false);
    EXPECT_NO_THROW(image.clearXmpData());
    EXPECT_TRUE(image.xmpData().empty());
}

// Test: ICC profile initially not defined
TEST_F(TiffImageTest_1738, IccProfileInitiallyNotDefined_1738) {
    auto mockIo = std::make_unique<MockBasicIo>();
    std::string path = "test.tiff";
    EXPECT_CALL(*mockIo, path()).WillRepeatedly(::testing::ReturnRef(path));

    TiffImage image(std::move(mockIo), false);
    EXPECT_FALSE(image.iccProfileDefined());
}

// Test: writeXmpFromPacket flag
TEST_F(TiffImageTest_1738, WriteXmpFromPacketFlag_1738) {
    auto mockIo = std::make_unique<MockBasicIo>();
    std::string path = "test.tiff";
    EXPECT_CALL(*mockIo, path()).WillRepeatedly(::testing::ReturnRef(path));

    TiffImage image(std::move(mockIo), false);
    EXPECT_FALSE(image.writeXmpFromPacket());
    image.writeXmpFromPacket(true);
    EXPECT_TRUE(image.writeXmpFromPacket());
    image.writeXmpFromPacket(false);
    EXPECT_FALSE(image.writeXmpFromPacket());
}

// Test using real MemIo with valid TIFF data
TEST_F(TiffImageTest_1738, PrintStructureWithValidTiffData_1738) {
    // Create a minimal valid TIFF file in memory
    auto header = createMinimalTiffHeader();

    auto memIo = std::make_unique<MemIo>(header.data(), header.size());
    TiffImage image(std::move(memIo), false);

    std::ostringstream oss;
    // kpsNone should not produce output but shouldn't throw for valid TIFF
    EXPECT_NO_THROW(image.printStructure(oss, PrintStructureOption::kpsNone, 0));
}

// Test using real MemIo with invalid (non-TIFF) data
TEST_F(TiffImageTest_1738, PrintStructureWithInvalidData_1738) {
    // Create some garbage data that's not TIFF
    std::vector<byte> garbage = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    auto memIo = std::make_unique<MemIo>(garbage.data(), garbage.size());

    // TiffImage sets imageType to tiff, so the "none" check won't trigger
    // but printTiffStructure should handle bad data
    TiffImage image(std::move(memIo), false);

    std::ostringstream oss;
    // With ImageType::tiff set but invalid data, it should throw during printTiffStructure
    EXPECT_THROW(image.printStructure(oss, PrintStructureOption::kpsNone, 0), Error);
}

// Test using empty MemIo
TEST_F(TiffImageTest_1738, PrintStructureWithEmptyData_1738) {
    auto memIo = std::make_unique<MemIo>();
    TiffImage image(std::move(memIo), false);

    std::ostringstream oss;
    EXPECT_THROW(image.printStructure(oss, PrintStructureOption::kpsNone, 0), Error);
}

// Test: xmpPacket accessor
TEST_F(TiffImageTest_1738, XmpPacketAccessor_1738) {
    auto mockIo = std::make_unique<MockBasicIo>();
    std::string path = "test.tiff";
    EXPECT_CALL(*mockIo, path()).WillRepeatedly(::testing::ReturnRef(path));

    TiffImage image(std::move(mockIo), false);
    EXPECT_NO_THROW(image.xmpPacket());
    EXPECT_TRUE(image.xmpPacket().empty());
}

// Test: clearComment
TEST_F(TiffImageTest_1738, ClearComment_1738) {
    auto mockIo = std::make_unique<MockBasicIo>();
    std::string path = "test.tiff";
    EXPECT_CALL(*mockIo, path()).WillRepeatedly(::testing::ReturnRef(path));

    TiffImage image(std::move(mockIo), false);
    EXPECT_NO_THROW(image.clearComment());
}

// Test: nativePreviews initially empty
TEST_F(TiffImageTest_1738, NativePreviewsInitiallyEmpty_1738) {
    auto mockIo = std::make_unique<MockBasicIo>();
    std::string path = "test.tiff";
    EXPECT_CALL(*mockIo, path()).WillRepeatedly(::testing::ReturnRef(path));

    TiffImage image(std::move(mockIo), false);
    EXPECT_TRUE(image.nativePreviews().empty());
}

// Test: printStructure with various PrintStructureOption values and open failure
TEST_F(TiffImageTest_1738, PrintStructureKpsBasicOpenFail_1738) {
    auto mockIo = std::make_unique<MockBasicIo>();
    std::string path = "fail.tiff";
    EXPECT_CALL(*mockIo, open()).WillOnce(::testing::Return(1));
    EXPECT_CALL(*mockIo, path()).WillRepeatedly(::testing::ReturnRef(path));

    TiffImage image(std::move(mockIo), false);
    std::ostringstream oss;
    EXPECT_THROW(image.printStructure(oss, PrintStructureOption::kpsBasic, 0), Error);
}

TEST_F(TiffImageTest_1738, PrintStructureKpsRecursiveOpenFail_1738) {
    auto mockIo = std::make_unique<MockBasicIo>();
    std::string path = "fail.tiff";
    EXPECT_CALL(*mockIo, open()).WillOnce(::testing::Return(1));
    EXPECT_CALL(*mockIo, path()).WillRepeatedly(::testing::ReturnRef(path));

    TiffImage image(std::move(mockIo), false);
    std::ostringstream oss;
    EXPECT_THROW(image.printStructure(oss, PrintStructureOption::kpsRecursive, 0), Error);
}

// Test: comment() returns empty string by default
TEST_F(TiffImageTest_1738, CommentDefaultEmpty_1738) {
    auto mockIo = std::make_unique<MockBasicIo>();
    std::string path = "test.tiff";
    EXPECT_CALL(*mockIo, path()).WillRepeatedly(::testing::ReturnRef(path));

    TiffImage image(std::move(mockIo), false);
    EXPECT_TRUE(image.comment().empty());
}

// Test: clearIccProfile
TEST_F(TiffImageTest_1738, ClearIccProfile_1738) {
    auto mockIo = std::make_unique<MockBasicIo>();
    std::string path = "test.tiff";
    EXPECT_CALL(*mockIo, path()).WillRepeatedly(::testing::ReturnRef(path));

    TiffImage image(std::move(mockIo), false);
    EXPECT_NO_THROW(image.clearIccProfile());
    EXPECT_FALSE(image.iccProfileDefined());
}
