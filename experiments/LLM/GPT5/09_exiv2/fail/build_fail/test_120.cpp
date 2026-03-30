#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/helper_functions.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"
#include "exiv2/types.hpp"

using namespace Exiv2;
using ::testing::Return;
using ::testing::Throw;

namespace {
    // Mock class for BasicIo to simulate external interactions
    class MockBasicIo : public BasicIo {
    public:
        MOCK_METHOD(int, open, (), (override));
        MOCK_METHOD(int, close, (), (override));
        MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));
        MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));
        MOCK_METHOD(void, readOrThrow, (byte* buf, size_t rcount, ErrorCode err), (override));
        MOCK_METHOD(size_t, tell, (), (const, override));
        MOCK_METHOD(size_t, size, (), (const, override));
        MOCK_METHOD(bool, isopen, (), (const, override));
    };

    // Test Fixture for readStringTag
    class ReadStringTagTest_120 : public ::testing::Test {
    protected:
        MockBasicIo mockIo;
    };

    // Normal operation test
    TEST_F(ReadStringTagTest_120, NormalOperation_120) {
        // Arrange
        size_t length = 5;
        std::string expected = "Hello";
        byte data[] = { 'H', 'e', 'l', 'l', 'o' };
        EXPECT_CALL(mockIo, read(_, length)).WillOnce([data](byte* buf, size_t rcount) {
            std::memcpy(buf, data, rcount);
            return rcount;
        });
        EXPECT_CALL(mockIo, size()).WillOnce(Return(10));
        EXPECT_CALL(mockIo, tell()).WillOnce(Return(0));

        // Act
        std::string result = readStringTag(mockIo, length);

        // Assert
        EXPECT_EQ(result, expected);
    }

    // Boundary condition test: reading an empty string (length = 0)
    TEST_F(ReadStringTagTest_120, ReadEmptyString_120) {
        // Arrange
        size_t length = 0;
        std::string expected = "";
        EXPECT_CALL(mockIo, read(_, length)).WillOnce([](byte* buf, size_t rcount) {
            return 0;
        });
        EXPECT_CALL(mockIo, size()).WillOnce(Return(10));
        EXPECT_CALL(mockIo, tell()).WillOnce(Return(0));

        // Act
        std::string result = readStringTag(mockIo, length);

        // Assert
        EXPECT_EQ(result, expected);
    }

    // Boundary condition test: reading beyond available size
    TEST_F(ReadStringTagTest_120, ReadBeyondAvailableSize_120) {
        // Arrange
        size_t length = 20;
        EXPECT_CALL(mockIo, size()).WillOnce(Return(10));
        EXPECT_CALL(mockIo, tell()).WillOnce(Return(0));

        // Act & Assert
        EXPECT_THROW(readStringTag(mockIo, length), std::out_of_range);
    }

    // Exception case: readOrThrow throws an exception
    TEST_F(ReadStringTagTest_120, ReadThrowsException_120) {
        // Arrange
        size_t length = 5;
        EXPECT_CALL(mockIo, readOrThrow(_, length, ErrorCode::kerFailedToReadImageData))
            .WillOnce(Throw(std::runtime_error("Failed to read data")));

        // Act & Assert
        EXPECT_THROW(readStringTag(mockIo, length), std::runtime_error);
    }

    // Test verification of the interaction with external dependencies
    TEST_F(ReadStringTagTest_120, VerifyReadInteraction_120) {
        // Arrange
        size_t length = 5;
        byte data[] = { 'T', 'e', 's', 't', ' ' };
        EXPECT_CALL(mockIo, read(_, length)).WillOnce([data](byte* buf, size_t rcount) {
            std::memcpy(buf, data, rcount);
            return rcount;
        });
        EXPECT_CALL(mockIo, size()).WillOnce(Return(10));
        EXPECT_CALL(mockIo, tell()).WillOnce(Return(0));

        // Act
        std::string result = readStringTag(mockIo, length);

        // Assert
        EXPECT_EQ(result, "Test ");
        // Ensure interaction with the mock was as expected
        testing::Mock::VerifyAndClearExpectations(&mockIo);
    }
}