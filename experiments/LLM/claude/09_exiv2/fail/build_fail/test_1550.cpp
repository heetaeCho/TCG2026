#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <memory>
#include <cstring>

#include "exiv2/orfimage.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"
#include "exiv2/image_types.hpp"

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

private:
    std::string mockPath_ = "mock_path.orf";
};

class OrfImageTest_1550 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that OrfImage can be created with a valid BasicIo
TEST_F(OrfImageTest_1550, Construction_1550) {
    auto io = std::make_unique<MockBasicIo>();
    EXPECT_CALL(*io, open()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, close()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, size()).WillRepeatedly(testing::Return(0));

    // OrfImage constructor should not throw
    EXPECT_NO_THROW(OrfImage img(std::move(io), false));
}

// Test mimeType returns correct value for ORF
TEST_F(OrfImageTest_1550, MimeTypeReturnsCorrectValue_1550) {
    auto io = std::make_unique<MockBasicIo>();
    EXPECT_CALL(*io, open()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, close()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, size()).WillRepeatedly(testing::Return(0));

    OrfImage img(std::move(io), false);
    std::string mime = img.mimeType();
    // ORF files are Olympus Raw Format
    EXPECT_FALSE(mime.empty());
}

// Test setComment throws or is unsupported for ORF
TEST_F(OrfImageTest_1550, SetCommentBehavior_1550) {
    auto io = std::make_unique<MockBasicIo>();
    EXPECT_CALL(*io, open()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, close()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, size()).WillRepeatedly(testing::Return(0));

    OrfImage img(std::move(io), false);
    // setComment for ORF should throw (unsupported)
    EXPECT_THROW(img.setComment("test comment"), Error);
}

// Test printStructure outputs ORF IMAGE header
TEST_F(OrfImageTest_1550, PrintStructureOutputsHeader_1550) {
    auto io = std::make_unique<MockBasicIo>();
    std::string mockPath = "test.orf";

    EXPECT_CALL(*io, open()).WillOnce(testing::Return(1)); // open fails
    EXPECT_CALL(*io, path()).WillRepeatedly(testing::ReturnRef(mockPath));
    EXPECT_CALL(*io, close()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, size()).WillRepeatedly(testing::Return(0));

    OrfImage img(std::move(io), false);
    std::ostringstream oss;

    // open() returns non-zero, should throw kerDataSourceOpenFailed
    EXPECT_THROW(img.printStructure(oss, PrintStructureOption::kpsNone, 0), Error);

    // But "ORF IMAGE" should have been written before the throw
    EXPECT_NE(oss.str().find("ORF IMAGE"), std::string::npos);
}

// Test printStructure throws when io open fails
TEST_F(OrfImageTest_1550, PrintStructureThrowsOnOpenFailure_1550) {
    auto io = std::make_unique<MockBasicIo>();
    std::string mockPath = "nonexistent.orf";

    EXPECT_CALL(*io, open()).WillOnce(testing::Return(1));
    EXPECT_CALL(*io, path()).WillRepeatedly(testing::ReturnRef(mockPath));
    EXPECT_CALL(*io, close()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, size()).WillRepeatedly(testing::Return(0));

    OrfImage img(std::move(io), false);
    std::ostringstream oss;

    try {
        img.printStructure(oss, PrintStructureOption::kpsNone, 0);
        FAIL() << "Expected Error to be thrown";
    } catch (const Error& e) {
        EXPECT_EQ(e.code(), ErrorCode::kerDataSourceOpenFailed);
    }
}

// Test pixelWidth and pixelHeight default values
TEST_F(OrfImageTest_1550, PixelDimensionsDefault_1550) {
    auto io = std::make_unique<MockBasicIo>();
    EXPECT_CALL(*io, open()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, close()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, size()).WillRepeatedly(testing::Return(0));

    OrfImage img(std::move(io), false);
    // Without reading metadata, dimensions should be 0
    EXPECT_EQ(img.pixelWidth(), 0u);
    EXPECT_EQ(img.pixelHeight(), 0u);
}

// Test that creating OrfImage with create=true works
TEST_F(OrfImageTest_1550, CreateNewOrfImage_1550) {
    auto io = std::make_unique<MockBasicIo>();
    EXPECT_CALL(*io, open()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, close()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, size()).WillRepeatedly(testing::Return(0));

    EXPECT_NO_THROW(OrfImage img(std::move(io), true));
}

// Test readMetadata with invalid/empty io throws
TEST_F(OrfImageTest_1550, ReadMetadataWithEmptyIoThrows_1550) {
    auto io = std::make_unique<MockBasicIo>();
    std::string mockPath = "empty.orf";

    EXPECT_CALL(*io, open()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, close()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, size()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, path()).WillRepeatedly(testing::ReturnRef(mockPath));
    EXPECT_CALL(*io, isopen()).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*io, error()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, eof()).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*io, seek(testing::_, testing::_)).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, tell()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, read(testing::A<byte*>(), testing::_)).WillRepeatedly(testing::Return(0));

    OrfImage img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Error);
}

// Test writeMetadata with empty io throws
TEST_F(OrfImageTest_1550, WriteMetadataWithEmptyIoThrows_1550) {
    auto io = std::make_unique<MockBasicIo>();
    std::string mockPath = "empty.orf";

    EXPECT_CALL(*io, open()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, close()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, size()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, path()).WillRepeatedly(testing::ReturnRef(mockPath));
    EXPECT_CALL(*io, isopen()).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*io, error()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, eof()).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*io, seek(testing::_, testing::_)).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, tell()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, read(testing::A<byte*>(), testing::_)).WillRepeatedly(testing::Return(0));

    OrfImage img(std::move(io), false);
    EXPECT_THROW(img.writeMetadata(), Error);
}

// Test that exifData, iptcData, xmpData are accessible
TEST_F(OrfImageTest_1550, MetadataAccessors_1550) {
    auto io = std::make_unique<MockBasicIo>();
    EXPECT_CALL(*io, open()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, close()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, size()).WillRepeatedly(testing::Return(0));

    OrfImage img(std::move(io), false);

    // These should be accessible and initially empty
    EXPECT_TRUE(img.exifData().empty());
    EXPECT_TRUE(img.iptcData().empty());
    EXPECT_TRUE(img.xmpData().empty());
}

// Test good() on freshly created OrfImage
TEST_F(OrfImageTest_1550, GoodOnFreshImage_1550) {
    auto io = std::make_unique<MockBasicIo>();
    EXPECT_CALL(*io, open()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, close()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, size()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, isopen()).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*io, error()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, eof()).WillRepeatedly(testing::Return(false));

    OrfImage img(std::move(io), false);
    // good() checks the io state
    EXPECT_TRUE(img.good());
}

// Test printStructure with different depth values
TEST_F(OrfImageTest_1550, PrintStructureWithVariousDepths_1550) {
    // Depth 0
    {
        auto io = std::make_unique<MockBasicIo>();
        std::string mockPath = "test.orf";
        EXPECT_CALL(*io, open()).WillOnce(testing::Return(1));
        EXPECT_CALL(*io, path()).WillRepeatedly(testing::ReturnRef(mockPath));
        EXPECT_CALL(*io, close()).WillRepeatedly(testing::Return(0));
        EXPECT_CALL(*io, size()).WillRepeatedly(testing::Return(0));

        OrfImage img(std::move(io), false);
        std::ostringstream oss;
        EXPECT_THROW(img.printStructure(oss, PrintStructureOption::kpsNone, 0), Error);
    }

    // Depth 10
    {
        auto io = std::make_unique<MockBasicIo>();
        std::string mockPath = "test.orf";
        EXPECT_CALL(*io, open()).WillOnce(testing::Return(1));
        EXPECT_CALL(*io, path()).WillRepeatedly(testing::ReturnRef(mockPath));
        EXPECT_CALL(*io, close()).WillRepeatedly(testing::Return(0));
        EXPECT_CALL(*io, size()).WillRepeatedly(testing::Return(0));

        OrfImage img(std::move(io), false);
        std::ostringstream oss;
        EXPECT_THROW(img.printStructure(oss, PrintStructureOption::kpsNone, 10), Error);
    }
}

// Test clearMetadata
TEST_F(OrfImageTest_1550, ClearMetadata_1550) {
    auto io = std::make_unique<MockBasicIo>();
    EXPECT_CALL(*io, open()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, close()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, size()).WillRepeatedly(testing::Return(0));

    OrfImage img(std::move(io), false);
    EXPECT_NO_THROW(img.clearMetadata());
    EXPECT_TRUE(img.exifData().empty());
    EXPECT_TRUE(img.iptcData().empty());
    EXPECT_TRUE(img.xmpData().empty());
}

// Test clearExifData
TEST_F(OrfImageTest_1550, ClearExifData_1550) {
    auto io = std::make_unique<MockBasicIo>();
    EXPECT_CALL(*io, open()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, close()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, size()).WillRepeatedly(testing::Return(0));

    OrfImage img(std::move(io), false);
    EXPECT_NO_THROW(img.clearExifData());
    EXPECT_TRUE(img.exifData().empty());
}

// Test clearIptcData
TEST_F(OrfImageTest_1550, ClearIptcData_1550) {
    auto io = std::make_unique<MockBasicIo>();
    EXPECT_CALL(*io, open()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, close()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, size()).WillRepeatedly(testing::Return(0));

    OrfImage img(std::move(io), false);
    EXPECT_NO_THROW(img.clearIptcData());
    EXPECT_TRUE(img.iptcData().empty());
}

// Test clearXmpData
TEST_F(OrfImageTest_1550, ClearXmpData_1550) {
    auto io = std::make_unique<MockBasicIo>();
    EXPECT_CALL(*io, open()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, close()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, size()).WillRepeatedly(testing::Return(0));

    OrfImage img(std::move(io), false);
    EXPECT_NO_THROW(img.clearXmpData());
    EXPECT_TRUE(img.xmpData().empty());
}

// Test printStructure writes ORF IMAGE to output before any failure
TEST_F(OrfImageTest_1550, PrintStructureWritesHeaderBeforeError_1550) {
    auto io = std::make_unique<MockBasicIo>();
    std::string mockPath = "header_test.orf";

    EXPECT_CALL(*io, open()).WillOnce(testing::Return(1)); // fail open
    EXPECT_CALL(*io, path()).WillRepeatedly(testing::ReturnRef(mockPath));
    EXPECT_CALL(*io, close()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, size()).WillRepeatedly(testing::Return(0));

    OrfImage img(std::move(io), false);
    std::ostringstream oss;

    try {
        img.printStructure(oss, PrintStructureOption::kpsNone, 0);
    } catch (const Error&) {
        // Expected
    }

    std::string output = oss.str();
    EXPECT_THAT(output, testing::HasSubstr("ORF IMAGE"));
}

// Test io() accessor returns reference to the underlying io
TEST_F(OrfImageTest_1550, IoAccessor_1550) {
    auto io = std::make_unique<MockBasicIo>();
    auto ioPtr = io.get();
    EXPECT_CALL(*io, open()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, close()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*io, size()).WillRepeatedly(testing::Return(0));

    OrfImage img(std::move(io), false);
    // io() should return a reference to the same object
    EXPECT_EQ(&img.io(), ioPtr);
}
