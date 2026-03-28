#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/epsimage.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/types.hpp"

// Mocking BasicIo class to simulate behavior for tests
class MockBasicIo : public Exiv2::BasicIo {
public:
    MOCK_METHOD(Exiv2::DataBuf, read, (size_t), (override));
    MOCK_METHOD(int, error, (), (const, override));
    MOCK_METHOD(int64_t, tell, (), (const, override));
    MOCK_METHOD(void, seek, (int64_t, Exiv2::BasicIo::Position), (override));
    MOCK_METHOD(bool, eof, (), (const, override));
    MOCK_METHOD(size_t, size, (), (const, override));
};

// Test fixture for testing isEpsType function
class EpsImageTest_1756 : public ::testing::Test {
protected:
    MockBasicIo mockIo;

    // Setup function to mock behaviors for different test cases
    void SetUp() override {
        // Default mock behaviors
        ON_CALL(mockIo, error()).WillByDefault(testing::Return(0));
    }
};

// Test case: Normal operation - EPS type with valid first line match
TEST_F(EpsImageTest_1756, ValidEpsTypeMatch_1756) {
    Exiv2::DataBuf validBuf{4};
    validBuf.write_uint8(0, 0x25);  // First byte of EPS signature
    validBuf.write_uint8(1, 0x21);  // Second byte of EPS signature
    validBuf.write_uint8(2, 0x50);  // Third byte of EPS signature
    validBuf.write_uint8(3, 0x53);  // Fourth byte of EPS signature

    EXPECT_CALL(mockIo, read(testing::_))
        .WillOnce(testing::Return(validBuf));
    EXPECT_CALL(mockIo, tell())
        .WillOnce(testing::Return(0));

    bool result = Exiv2::isEpsType(mockIo, true);
    EXPECT_TRUE(result);
}

// Test case: Boundary condition - valid EPS but with a slightly different first line
TEST_F(EpsImageTest_1756, BoundaryConditionEpsTypeMatch_1757) {
    Exiv2::DataBuf boundaryBuf{32}; // Boundary test with a larger buffer size
    boundaryBuf.write_uint8(0, 0x25); // Valid EPS signature start
    boundaryBuf.write_uint8(1, 0x21);
    boundaryBuf.write_uint8(2, 0x50);
    boundaryBuf.write_uint8(3, 0x53);  // Matches "%!PS-Adobe-3.0 EPSF-3.0"

    EXPECT_CALL(mockIo, read(testing::_))
        .WillOnce(testing::Return(boundaryBuf));
    EXPECT_CALL(mockIo, tell())
        .WillOnce(testing::Return(0));

    bool result = Exiv2::isEpsType(mockIo, true);
    EXPECT_TRUE(result);
}

// Test case: Exceptional case - error while reading
TEST_F(EpsImageTest_1756, EpsTypeReadError_1758) {
    Exiv2::DataBuf errorBuf{0}; // Empty buffer simulating read failure

    EXPECT_CALL(mockIo, read(testing::_))
        .WillOnce(testing::Return(errorBuf));
    EXPECT_CALL(mockIo, error())
        .WillOnce(testing::Return(1));  // Simulating an error
    EXPECT_CALL(mockIo, tell())
        .WillOnce(testing::Return(0));

    bool result = Exiv2::isEpsType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test case: Exceptional case - matching failure despite valid buffer
TEST_F(EpsImageTest_1756, EpsTypeMatchFailure_1759) {
    Exiv2::DataBuf invalidBuf{4};
    invalidBuf.write_uint8(0, 0x12); // Invalid EPS signature

    EXPECT_CALL(mockIo, read(testing::_))
        .WillOnce(testing::Return(invalidBuf));
    EXPECT_CALL(mockIo, tell())
        .WillOnce(testing::Return(0));

    bool result = Exiv2::isEpsType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test case: Checking if seek is called correctly when advancing is false
TEST_F(EpsImageTest_1756, SeekCalledWhenNotAdvancing_1760) {
    Exiv2::DataBuf validBuf{4};
    validBuf.write_uint8(0, 0x25);  // First byte of EPS signature

    EXPECT_CALL(mockIo, read(testing::_))
        .WillOnce(testing::Return(validBuf));
    EXPECT_CALL(mockIo, tell())
        .WillOnce(testing::Return(0));
    EXPECT_CALL(mockIo, seek(0, Exiv2::BasicIo::beg)) // Expect seek to be called when advancing is false
        .Times(1);

    bool result = Exiv2::isEpsType(mockIo, false);
    EXPECT_TRUE(result);
}