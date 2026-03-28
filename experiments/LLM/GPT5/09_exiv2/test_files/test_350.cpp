#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tiffcomposite_int.hpp"  // Ensure this includes the necessary headers

using namespace Exiv2;
using namespace Exiv2::Internal;

// Mock class for Exifdatum
class MockExifdatum : public Exifdatum {
public:
    MOCK_METHOD(void, encode, (TiffEncoder& encoder), (const, override));
};

// Mock class for TiffEncoder
class MockTiffEncoder : public TiffEncoder {
public:
    MOCK_METHOD(void, encodeBinaryArray, (TiffBinaryArray* object, const Exifdatum* datum), (override));
};

// Test Fixture for TiffBinaryArray
class TiffBinaryArrayTest : public ::testing::Test {
protected:
    TiffBinaryArrayTest() : 
        tiffBinaryArray(1234, IfdId::ExifIFD, arrayCfg, arrayDef, 100) {}

    TiffBinaryArray tiffBinaryArray;
    ArrayCfg arrayCfg;
    ArrayDef* arrayDef = nullptr;
};

// Test normal operation of doEncode
TEST_F(TiffBinaryArrayTest, DoEncode_NormalOperation_350) {
    // Arrange
    MockTiffEncoder encoder;
    MockExifdatum datum;

    // Expectation: encodeBinaryArray should be called once with correct arguments
    EXPECT_CALL(encoder, encodeBinaryArray(&tiffBinaryArray, &datum)).Times(1);

    // Act
    tiffBinaryArray.doEncode(encoder, &datum);

    // Assert - Expected behavior is verified with the expectation above
}

// Test when encoder is nullptr (error case)
TEST_F(TiffBinaryArrayTest, DoEncode_NullEncoder_351) {
    // Arrange
    MockExifdatum datum;

    // Act & Assert
    EXPECT_THROW(tiffBinaryArray.doEncode(nullptr, &datum), std::invalid_argument);
}

// Test for boundary condition: Empty datum (testing edge case)
TEST_F(TiffBinaryArrayTest, DoEncode_EmptyDatum_352) {
    // Arrange
    MockTiffEncoder encoder;
    MockExifdatum datum;

    // Expectation: encodeBinaryArray should be called once
    EXPECT_CALL(encoder, encodeBinaryArray(&tiffBinaryArray, &datum)).Times(1);

    // Act
    tiffBinaryArray.doEncode(encoder, &datum);

    // Assert - Expected behavior is verified with the expectation above
}