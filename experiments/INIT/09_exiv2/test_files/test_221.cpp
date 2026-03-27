#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/rafimage.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"

using namespace Exiv2;

class MockBasicIo : public BasicIo {
public:
    MOCK_METHOD(int, open, (), (override));
    MOCK_METHOD(int, close, (), (override));
    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));
    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));
    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));
    MOCK_METHOD(int, error, (), (const, override));
    MOCK_METHOD(bool, eof, (), (const, override));
    MOCK_METHOD(const std::string&, path, (), (const, override));
    MOCK_METHOD(size_t, size, (), (const, override));
};

// Test Fixture for RafImage Tests
class RafImageTest : public ::testing::Test {
protected:
    MockBasicIo* mockIo;
    std::unique_ptr<RafImage> rafImage;

    void SetUp() override {
        mockIo = new MockBasicIo();
        rafImage = std::make_unique<RafImage>(std::unique_ptr<BasicIo>(mockIo), true);
    }

    void TearDown() override {
        rafImage.reset();
    }
};

// TEST 1: Normal operation of reading metadata
TEST_F(RafImageTest, ReadMetadata_221) {
    EXPECT_CALL(*mockIo, open()).WillOnce(testing::Return(0));
    EXPECT_CALL(*mockIo, seek(testing::Eq(84), testing::_)).WillOnce(testing::Return(0));
    EXPECT_CALL(*mockIo, read(testing::_, testing::_)).WillOnce(testing::Return(4));
    EXPECT_CALL(*mockIo, read(testing::_, testing::_)).WillOnce(testing::Return(4));
    EXPECT_CALL(*mockIo, seek(testing::Eq(100), testing::_)).WillOnce(testing::Return(0));
    EXPECT_CALL(*mockIo, read(testing::_, testing::_)).WillOnce(testing::Return(4));
    EXPECT_CALL(*mockIo, read(testing::_, testing::_)).WillOnce(testing::Return(4));

    try {
        rafImage->readMetadata();
        SUCCEED();
    } catch (...) {
        FAIL() << "Expected no exception to be thrown.";
    }
}

// TEST 2: Fail case due to seek error
TEST_F(RafImageTest, ReadMetadata_SeekFail_221) {
    EXPECT_CALL(*mockIo, open()).WillOnce(testing::Return(0));
    EXPECT_CALL(*mockIo, seek(testing::Eq(84), testing::_)).WillOnce(testing::Return(-1)); // simulate seek failure

    EXPECT_THROW(rafImage->readMetadata(), Error);
}

// TEST 3: Fail case due to read error (4-byte read failure)
TEST_F(RafImageTest, ReadMetadata_ReadFail_221) {
    EXPECT_CALL(*mockIo, open()).WillOnce(testing::Return(0));
    EXPECT_CALL(*mockIo, seek(testing::Eq(84), testing::_)).WillOnce(testing::Return(0));
    EXPECT_CALL(*mockIo, read(testing::_, testing::_)).WillOnce(testing::Return(4));
    EXPECT_CALL(*mockIo, read(testing::_, testing::_)).WillOnce(testing::Return(0)); // simulate read failure

    EXPECT_THROW(rafImage->readMetadata(), Error);
}

// TEST 4: Fail case due to corrupted metadata (tiff offset and length mismatch)
TEST_F(RafImageTest, ReadMetadata_CorruptedMetadata_221) {
    EXPECT_CALL(*mockIo, open()).WillOnce(testing::Return(0));
    EXPECT_CALL(*mockIo, seek(testing::Eq(84), testing::_)).WillOnce(testing::Return(0));
    EXPECT_CALL(*mockIo, read(testing::_, testing::_)).WillOnce(testing::Return(4));
    EXPECT_CALL(*mockIo, read(testing::_, testing::_)).WillOnce(testing::Return(4));
    EXPECT_CALL(*mockIo, seek(testing::Eq(100), testing::_)).WillOnce(testing::Return(0));
    EXPECT_CALL(*mockIo, read(testing::_, testing::_)).WillOnce(testing::Return(4));
    EXPECT_CALL(*mockIo, read(testing::_, testing::_)).WillOnce(testing::Return(4));

    // Simulate corrupted metadata by setting invalid values
    EXPECT_CALL(*mockIo, read(testing::_, testing::_)).WillOnce(testing::Return(4));
    EXPECT_CALL(*mockIo, size()).WillOnce(testing::Return(0));

    EXPECT_THROW(rafImage->readMetadata(), Error);
}

// TEST 5: Verify if xmpData is set correctly when metadata is read
TEST_F(RafImageTest, VerifyXmpData_221) {
    EXPECT_CALL(*mockIo, open()).WillOnce(testing::Return(0));
    EXPECT_CALL(*mockIo, seek(testing::Eq(84), testing::_)).WillOnce(testing::Return(0));
    EXPECT_CALL(*mockIo, read(testing::_, testing::_)).WillOnce(testing::Return(4));
    EXPECT_CALL(*mockIo, read(testing::_, testing::_)).WillOnce(testing::Return(4));
    EXPECT_CALL(*mockIo, seek(testing::Eq(100), testing::_)).WillOnce(testing::Return(0));
    EXPECT_CALL(*mockIo, read(testing::_, testing::_)).WillOnce(testing::Return(4));
    EXPECT_CALL(*mockIo, read(testing::_, testing::_)).WillOnce(testing::Return(4));

    // Simulating successful reading of metadata
    EXPECT_CALL(*mockIo, read(testing::_, testing::_)).WillOnce(testing::Return(4));
    EXPECT_CALL(*mockIo, size()).WillOnce(testing::Return(10));

    try {
        rafImage->readMetadata();
        ASSERT_FALSE(rafImage->xmpData().empty());
    } catch (...) {
        FAIL() << "Expected no exception to be thrown.";
    }
}