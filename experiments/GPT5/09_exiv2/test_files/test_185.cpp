#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include <sstream>

// Mock class to simulate the Value and ExifData types used in the original function
class MockValue {
public:
    MOCK_METHOD(int, count, (), (const));
    MOCK_METHOD(uint32_t, toUint32, (size_t index), (const));
};

class MockExifData {};

// Test fixture for testing printTagBitlistAllLE
class PrintTagBitlistAllLETest_185 : public ::testing::Test {
protected:
    // This will be used to capture the output of the function
    std::stringstream outputStream;

    // This will represent the mock value object
    MockValue mockValue;
    
    // TagDetailsBitlistSorted array to be used in the test
    static constexpr std::pair<uint32_t, const char*> tagDetails[] = {
        {0, "Tag0"},
        {1, "Tag1"},
        {2, "Tag2"},
    };

    // Method to call the function under test
    void callPrintTagBitlistAllLE(const MockValue& value) {
        Exiv2::Internal::printTagBitlistAllLE(outputStream, value, nullptr);
    }
};

// Test case for normal operation: Testing the case where some tags are processed
TEST_F(PrintTagBitlistAllLETest_185, NormalOperation_185) {
    // Set up mock behavior
    EXPECT_CALL(mockValue, count()).WillOnce(testing::Return(2));
    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(testing::Return(0b00000001)); // Only first bit set
    EXPECT_CALL(mockValue, toUint32(1)).WillOnce(testing::Return(0b00000010)); // Only second bit set

    // Call the function
    callPrintTagBitlistAllLE(mockValue);

    // Check the output
    EXPECT_EQ(outputStream.str(), "Tag0, Tag1");
}

// Test case for boundary condition: Testing the case with no tags set
TEST_F(PrintTagBitlistAllLETest_185, NoTagsSet_185) {
    // Set up mock behavior
    EXPECT_CALL(mockValue, count()).WillOnce(testing::Return(1));
    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(testing::Return(0));

    // Call the function
    callPrintTagBitlistAllLE(mockValue);

    // Check the output
    EXPECT_EQ(outputStream.str(), "None");
}

// Test case for boundary condition: Testing the case where tags exceed the array bitlist
TEST_F(PrintTagBitlistAllLETest_185, TagsExceedBitlist_185) {
    // Set up mock behavior
    EXPECT_CALL(mockValue, count()).WillOnce(testing::Return(1));
    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(testing::Return(0b10000000)); // Tag beyond max bit

    // Call the function
    callPrintTagBitlistAllLE(mockValue);

    // Check the output
    EXPECT_EQ(outputStream.str(), ", [8]");
}

// Test case for exceptional behavior: Testing the case with zero length array
TEST_F(PrintTagBitlistAllLETest_185, ZeroLengthArray_185) {
    // Test the static_assert failure if N == 0 (compilation should fail)
    constexpr std::pair<uint32_t, const char*> emptyTagDetails[] = {};

    // This should cause a compile-time error due to static_assert
    // Exiv2::Internal::printTagBitlistAllLE(outputStream, mockValue, nullptr); // Uncomment to trigger compile-time error
    SUCCEED();  // If compilation passes, this will succeed
}

// Test case for boundary condition: Testing when `vN` is exactly zero for all bits
TEST_F(PrintTagBitlistAllLETest_185, AllBitsZero_185) {
    // Set up mock behavior
    EXPECT_CALL(mockValue, count()).WillOnce(testing::Return(1));
    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(testing::Return(0));

    // Call the function
    callPrintTagBitlistAllLE(mockValue);

    // Check the output
    EXPECT_EQ(outputStream.str(), "None");
}