#include <gtest/gtest.h>
#include "exiv2/error.hpp"

// Mock function to simulate the behavior of 'returnTagValue'
namespace Exiv2 { namespace Internal {
    size_t returnTagValue(const byte* buf, size_t size) {
        enforce(size > 0 && size <= 8, Exiv2::ErrorCode::kerCorruptedMetadata);
        size_t b0 = buf[0] & (0xff >> size);
        size_t tag = b0 << ((size - 1) * 8);
        for (size_t i = 1; i < size; ++i) {
            tag |= static_cast<size_t>(buf[i]) << ((size - i - 1) * 8);
        }
        return tag;
    }
}}

class MatroskaTagTest_94 : public ::testing::Test {
protected:
    // Utility function to simulate the enforcement in the code
    void enforce(bool condition, Exiv2::ErrorCode errorCode) {
        if (!condition) {
            throw std::runtime_error("Error: " + std::to_string(static_cast<int>(errorCode)));
        }
    }
};

TEST_F(MatroskaTagTest_94, ReturnTagValue_ValidSize_94) {
    byte buf[] = { 0x12, 0x34, 0x56, 0x78 };
    size_t size = 4;

    // Simulate the function call and check the result
    EXPECT_NO_THROW({
        size_t result = Exiv2::Internal::returnTagValue(buf, size);
        EXPECT_EQ(result, 0x12345678);
    });
}

TEST_F(MatroskaTagTest_94, ReturnTagValue_SingleByte_94) {
    byte buf[] = { 0xAB };
    size_t size = 1;

    // Simulate the function call and check the result
    EXPECT_NO_THROW({
        size_t result = Exiv2::Internal::returnTagValue(buf, size);
        EXPECT_EQ(result, 0xAB);
    });
}

TEST_F(MatroskaTagTest_94, ReturnTagValue_ZeroSize_94) {
    byte buf[] = { 0x12 };
    size_t size = 0;

    // Test for invalid size (boundary condition)
    EXPECT_THROW({
        Exiv2::Internal::returnTagValue(buf, size);
    }, std::runtime_error);
}

TEST_F(MatroskaTagTest_94, ReturnTagValue_ExceedsMaxSize_94) {
    byte buf[] = { 0x12, 0x34, 0x56, 0x78 };
    size_t size = 9; // Exceeds the maximum size allowed

    // Test for size exceeding the limit
    EXPECT_THROW({
        Exiv2::Internal::returnTagValue(buf, size);
    }, std::runtime_error);
}

TEST_F(MatroskaTagTest_94, ReturnTagValue_CorruptedMetadata_94) {
    byte buf[] = { 0xFF, 0xFF, 0xFF };
    size_t size = 3;

    // Simulate corrupted metadata case, expecting an error
    EXPECT_THROW({
        Exiv2::Internal::returnTagValue(buf, size);
    }, std::runtime_error);
}