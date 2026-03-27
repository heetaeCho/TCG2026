#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Exiv2/jp2image.hpp>
#include <Exiv2/basicio.hpp>
#include <Exiv2/error.hpp>
#include <Exiv2/io.hpp>

namespace Exiv2 {
    class MockBasicIo : public BasicIo {
    public:
        MOCK_METHOD(int, open, (), (override));
        MOCK_METHOD(int, close, (), (override));
        MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));
        MOCK_METHOD(void, transfer, (BasicIo& src), (override));
        MOCK_METHOD(int, error, (), (const, override));
        MOCK_METHOD(const std::string&, path, (), (const, override));
    };

    class Jp2ImageTest_87 : public testing::Test {
    protected:
        std::unique_ptr<MockBasicIo> mockIo;
        std::unique_ptr<Jp2Image> jp2Image;

        void SetUp() override {
            mockIo = std::make_unique<MockBasicIo>();
            jp2Image = std::make_unique<Jp2Image>(std::move(mockIo), true);
        }
    };

    TEST_F(Jp2ImageTest_87, WriteMetadataSucceeds_87) {
        // Setup expectations
        EXPECT_CALL(*mockIo, open()).WillOnce(testing::Return(0));  // simulating successful open
        EXPECT_CALL(*mockIo, close()).WillOnce(testing::Return(0)); // simulating successful close
        EXPECT_CALL(*mockIo, transfer(testing::_));  // transfer should be called

        // Act
        EXPECT_NO_THROW(jp2Image->writeMetadata());  // No exception should be thrown
    }

    TEST_F(Jp2ImageTest_87, WriteMetadataFailsOnOpen_87) {
        // Setup expectations for failure during open
        EXPECT_CALL(*mockIo, open()).WillOnce(testing::Return(1));  // simulating failed open

        // Act & Assert
        EXPECT_THROW(jp2Image->writeMetadata(), Error);  // Should throw an error due to failed open
    }

    TEST_F(Jp2ImageTest_87, WriteMetadataFailsOnTransfer_87) {
        // Setup expectations
        EXPECT_CALL(*mockIo, open()).WillOnce(testing::Return(0));  // simulating successful open
        EXPECT_CALL(*mockIo, close()).WillOnce(testing::Return(0)); // simulating successful close
        EXPECT_CALL(*mockIo, transfer(testing::_)).WillOnce(testing::Throw(std::runtime_error("Transfer failed"))); // transfer throws exception

        // Act & Assert
        EXPECT_THROW(jp2Image->writeMetadata(), std::runtime_error);  // Should throw a transfer error
    }

    TEST_F(Jp2ImageTest_87, WriteMetadataWithErrorCode_87) {
        // Setup expectations
        EXPECT_CALL(*mockIo, open()).WillOnce(testing::Return(0));  // simulating successful open
        EXPECT_CALL(*mockIo, close()).WillOnce(testing::Return(0)); // simulating successful close
        EXPECT_CALL(*mockIo, transfer(testing::_));  // transfer should be called

        // Simulate error code during write
        EXPECT_CALL(*mockIo, error()).WillOnce(testing::Return(1)); // simulate an error code

        // Act & Assert
        EXPECT_THROW(jp2Image->writeMetadata(), Error);  // Should throw an error due to error code
    }
}