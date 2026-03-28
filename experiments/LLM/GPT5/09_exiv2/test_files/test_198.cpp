#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include "pentaxmn_int.cpp"  // Include your partial code here

using ::testing::AtLeast;

namespace Exiv2 {
namespace Internal {

// Mock classes if necessary (not required for the provided code)

class Value {
public:
    virtual int64_t toInt64() const = 0;
};

class ExifData {};

class MockValue : public Value {
public:
    MOCK_CONST_METHOD0(toInt64, int64_t());
};

// Unit Test Class
class PentaxMakerNoteTest_198 : public ::testing::Test {
protected:
    PentaxMakerNote pentaxMakerNote;  // Object under test
};

TEST_F(PentaxMakerNoteTest_198, PrintFlashCompensation_NormalOperation_198) {
    // Arrange
    MockValue value;
    ExifData exifData;
    std::ostringstream os;

    // Set up mock behavior
    EXPECT_CALL(value, toInt64())
        .WillOnce(testing::Return(512));  // Example value: 512
    
    // Act
    pentaxMakerNote.printFlashCompensation(os, value, &exifData);

    // Assert
    EXPECT_EQ(os.str(), "2 EV");  // Expected output: 512 / 256 = 2
}

TEST_F(PentaxMakerNoteTest_198, PrintFlashCompensation_BoundaryCondition_Max_198) {
    // Arrange
    MockValue value;
    ExifData exifData;
    std::ostringstream os;

    // Set up mock behavior for a large value
    EXPECT_CALL(value, toInt64())
        .WillOnce(testing::Return(std::numeric_limits<int64_t>::max()));  // Max value

    // Act
    pentaxMakerNote.printFlashCompensation(os, value, &exifData);

    // Assert
    // Test that the output is formatted correctly (this could be extremely large EV)
    EXPECT_EQ(os.str(), "{:.2g} EV");  // Format of max value should be tested
}

TEST_F(PentaxMakerNoteTest_198, PrintFlashCompensation_ZeroValue_198) {
    // Arrange
    MockValue value;
    ExifData exifData;
    std::ostringstream os;

    // Set up mock behavior for a zero value
    EXPECT_CALL(value, toInt64())
        .WillOnce(testing::Return(0));  // Zero value

    // Act
    pentaxMakerNote.printFlashCompensation(os, value, &exifData);

    // Assert
    EXPECT_EQ(os.str(), "0 EV");  // Expected output: 0 / 256 = 0
}

TEST_F(PentaxMakerNoteTest_198, PrintFlashCompensation_NegativeValue_198) {
    // Arrange
    MockValue value;
    ExifData exifData;
    std::ostringstream os;

    // Set up mock behavior for a negative value
    EXPECT_CALL(value, toInt64())
        .WillOnce(testing::Return(-256));  // Negative value

    // Act
    pentaxMakerNote.printFlashCompensation(os, value, &exifData);

    // Assert
    EXPECT_EQ(os.str(), "-1 EV");  // Expected output: -256 / 256 = -1
}

}  // namespace Internal
}  // namespace Exiv2