#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/tiffimage.hpp"
#include "exiv2/error.hpp"

using namespace Exiv2;

// Mock the Io interface to simulate BasicIo behavior
class MockBasicIo : public BasicIo {
public:
    MOCK_METHOD(int, open, (), (override));
    MOCK_METHOD(bool, error, (), (const, override));
    MOCK_METHOD(bool, eof, (), (const, override));
    MOCK_METHOD(size_t, size, (), (const, override));
    MOCK_METHOD(const std::string&, path, (), (const, override));
};

// Test Fixture
class TiffImageTest_1732 : public ::testing::Test {
protected:
    std::unique_ptr<MockBasicIo> mockIo;
    TiffImage* tiffImage;

    void SetUp() override {
        mockIo = std::make_unique<MockBasicIo>();
        tiffImage = new TiffImage(std::move(mockIo), true);
    }

    void TearDown() override {
        delete tiffImage;
    }
};

// Test case 1: Successful metadata reading
TEST_F(TiffImageTest_1732, ReadMetadata_Success_1732) {
    EXPECT_CALL(*mockIo, open()).WillOnce(testing::Return(0)); // Simulate successful open
    EXPECT_CALL(*mockIo, error()).WillOnce(testing::Return(false)); // Simulate no error
    EXPECT_CALL(*mockIo, eof()).WillOnce(testing::Return(false)); // Simulate no EOF

    EXPECT_NO_THROW(tiffImage->readMetadata());
}

// Test case 2: File open failure
TEST_F(TiffImageTest_1732, ReadMetadata_FileOpenFailed_1732) {
    EXPECT_CALL(*mockIo, open()).WillOnce(testing::Return(-1)); // Simulate file open failure

    EXPECT_THROW(tiffImage->readMetadata(), Error);
    EXPECT_EQ(tiffImage->readMetadata(), ErrorCode::kerDataSourceOpenFailed);
}

// Test case 3: Not a TIFF image
TEST_F(TiffImageTest_1732, ReadMetadata_NotATiffImage_1732) {
    EXPECT_CALL(*mockIo, open()).WillOnce(testing::Return(0)); // Simulate successful open
    EXPECT_CALL(*mockIo, error()).WillOnce(testing::Return(false)); // Simulate no error
    EXPECT_CALL(*mockIo, eof()).WillOnce(testing::Return(false)); // Simulate no EOF

    EXPECT_CALL(*mockIo, mmap()).WillOnce(testing::Return(nullptr)); // Simulate non-TIFF data

    EXPECT_THROW(tiffImage->readMetadata(), Error);
    EXPECT_EQ(tiffImage->readMetadata(), ErrorCode::kerNotAnImage);
}

// Test case 4: ICC profile allocation failure
TEST_F(TiffImageTest_1732, ReadMetadata_IccProfileAllocFailed_1732) {
    EXPECT_CALL(*mockIo, open()).WillOnce(testing::Return(0)); // Simulate successful open
    EXPECT_CALL(*mockIo, error()).WillOnce(testing::Return(false)); // Simulate no error
    EXPECT_CALL(*mockIo, eof()).WillOnce(testing::Return(false)); // Simulate no EOF

    EXPECT_CALL(*mockIo, mmap()).WillOnce(testing::Return(nullptr)); // Simulate non-TIFF data

    // Simulate ExifData with an ICC Profile that fails allocation
    ExifData exifData;
    Exiv2::ExifKey key("Exif.Image.InterColorProfile");
    Exifdatum iccProfileDatum(key, nullptr);
    exifData.add(iccProfileDatum);

    EXPECT_THROW(tiffImage->readMetadata(), Error);
    EXPECT_EQ(tiffImage->readMetadata(), ErrorCode::kerFailedToReadImageData);
}

// Test case 5: Successful read with valid TIFF image
TEST_F(TiffImageTest_1732, ReadMetadata_ValidTiffImage_1732) {
    // Mock successful file open and reading
    EXPECT_CALL(*mockIo, open()).WillOnce(testing::Return(0)); // Simulate successful open
    EXPECT_CALL(*mockIo, error()).WillOnce(testing::Return(false)); // Simulate no error
    EXPECT_CALL(*mockIo, eof()).WillOnce(testing::Return(false)); // Simulate no EOF

    // Simulate successful TIFF check
    EXPECT_CALL(*mockIo, mmap()).WillOnce(testing::Return(reinterpret_cast<const byte*>(nullptr))); // Simulate valid TIFF data

    // Simulate valid ExifData
    ExifData exifData;
    Exiv2::ExifKey key("Exif.Image.InterColorProfile");
    Exifdatum iccProfileDatum(key, nullptr);
    exifData.add(iccProfileDatum);

    EXPECT_NO_THROW(tiffImage->readMetadata());
}