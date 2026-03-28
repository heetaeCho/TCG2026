#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/metadatum.hpp"
#include "exiv2/exif.hpp"

// Mock class for ExifData to simulate external behavior
class MockExifData : public Exiv2::ExifData {
public:
    MOCK_METHOD(const std::string&, operator[], (const std::string& key), (const, override));
    MOCK_METHOD(void, add, (const Exiv2::ExifKey& key, const Exiv2::Value* pValue), (override));
};

// Test Fixture for Metadatum class
class MetadatumTest_110 : public testing::Test {
protected:
    Exiv2::Metadatum metadatum;
    MockExifData mockExifData;
};

// Normal Operation Test Case
TEST_F(MetadatumTest_110, Print_ReturnsString_110) {
    // Mocking ExifData
    Exiv2::ExifData* pMetadata = &mockExifData;
    
    // Setting up expectations
    EXPECT_CALL(mockExifData, operator[]).WillOnce(testing::ReturnRef(std::string("Mocked ExifData")));

    // Testing the print function
    std::string result = metadatum.print(pMetadata);
    EXPECT_EQ(result, "Mocked ExifData");
}

// Boundary Test Case for Null Metadata
TEST_F(MetadatumTest_110, Print_WithNullMetadata_110) {
    // Testing print with a null pointer
    std::string result = metadatum.print(nullptr);
    EXPECT_EQ(result, "");
}

// Error Handling Test Case: Invalid Metadata Type
TEST_F(MetadatumTest_110, Print_WithInvalidMetadataType_110) {
    // Mocking invalid behavior in metadata
    Exiv2::ExifData* pMetadata = nullptr;
    
    // We expect an empty string when print is called with invalid data
    std::string result = metadatum.print(pMetadata);
    EXPECT_EQ(result, "");
}

// Boundary Test Case: Check for Empty String
TEST_F(MetadatumTest_110, Print_EmptyString_110) {
    Exiv2::ExifData* pMetadata = &mockExifData;
    
    // Setting up the expectation for an empty string
    EXPECT_CALL(mockExifData, operator[]).WillOnce(testing::ReturnRef(std::string("")));
    
    // Testing print with empty metadata content
    std::string result = metadatum.print(pMetadata);
    EXPECT_EQ(result, "");
}

// Exceptional Case: Test for Unsupported Value Type in Metadata
TEST_F(MetadatumTest_110, Print_UnsupportedValueType_110) {
    Exiv2::ExifData* pMetadata = &mockExifData;
    
    // Set up an unsupported type (e.g., unsupported key type)
    EXPECT_CALL(mockExifData, operator[]).WillOnce(testing::Throw(std::invalid_argument("Unsupported key")));
    
    try {
        std::string result = metadatum.print(pMetadata);
        FAIL() << "Expected std::invalid_argument exception";
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ(e.what(), "Unsupported key");
    }
}

// Mock for Metadatum::toUint32
TEST_F(MetadatumTest_110, ToUint32_ValidConversion_110) {
    size_t n = 0;
    uint32_t expectedValue = 42;

    EXPECT_CALL(mockExifData, operator[]).WillOnce(testing::ReturnRef(std::string("42")));
    
    // Testing toUint32 function
    uint32_t result = metadatum.toUint32(n);
    EXPECT_EQ(result, expectedValue);
}

// Boundary Test for Conversion Function
TEST_F(MetadatumTest_110, ToUint32_WithZero_110) {
    size_t n = 0;
    uint32_t expectedValue = 0;
    
    EXPECT_CALL(mockExifData, operator[]).WillOnce(testing::ReturnRef(std::string("0")));
    
    uint32_t result = metadatum.toUint32(n);
    EXPECT_EQ(result, expectedValue);
}

// Boundary Test for Invalid Input (Non-Numeric String)
TEST_F(MetadatumTest_110, ToUint32_InvalidInput_110) {
    size_t n = 0;
    
    EXPECT_CALL(mockExifData, operator[]).WillOnce(testing::ReturnRef(std::string("Invalid")));

    try {
        uint32_t result = metadatum.toUint32(n);
        FAIL() << "Expected std::invalid_argument exception";
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ(e.what(), "Invalid numeric string");
    }
}