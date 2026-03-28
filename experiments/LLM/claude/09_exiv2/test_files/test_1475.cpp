#include <gtest/gtest.h>
#include "makernote_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class PanasonicMnHeaderTest_1475 : public ::testing::Test {
protected:
    PanasonicMnHeader header_;
};

// Test that a default-constructed PanasonicMnHeader returns a known ifdOffset
TEST_F(PanasonicMnHeaderTest_1475, DefaultIfdOffset_1475) {
    size_t offset = header_.ifdOffset();
    // The ifdOffset should be a well-defined value after default construction.
    // Typically for Panasonic, the IFD offset equals the signature size (12 bytes).
    EXPECT_EQ(offset, header_.sizeOfSignature());
}

// Test that size() returns a non-zero value for the header
TEST_F(PanasonicMnHeaderTest_1475, SizeIsNonZero_1475) {
    size_t sz = header_.size();
    EXPECT_GT(sz, 0u);
}

// Test that sizeOfSignature() returns a positive value
TEST_F(PanasonicMnHeaderTest_1475, SizeOfSignaturePositive_1475) {
    size_t sigSize = PanasonicMnHeader::sizeOfSignature();
    EXPECT_GT(sigSize, 0u);
}

// Test that size() and sizeOfSignature() are consistent
TEST_F(PanasonicMnHeaderTest_1475, SizeConsistentWithSignature_1475) {
    // The header size should be at least as large as the signature
    EXPECT_GE(header_.size(), PanasonicMnHeader::sizeOfSignature());
}

// Test read with nullptr data returns false
TEST_F(PanasonicMnHeaderTest_1475, ReadNullDataReturnsFalse_1475) {
    bool result = header_.read(nullptr, 0, littleEndian);
    EXPECT_FALSE(result);
}

// Test read with insufficient data size returns false
TEST_F(PanasonicMnHeaderTest_1475, ReadInsufficientSizeReturnsFalse_1475) {
    byte data[4] = {0};
    bool result = header_.read(data, 4, littleEndian);
    EXPECT_FALSE(result);
}

// Test read with valid Panasonic signature
TEST_F(PanasonicMnHeaderTest_1475, ReadValidSignature_1475) {
    // Panasonic maker note signature: "Panasonic\0\0\0"
    const byte panasonicSig[] = "Panasonic\0\0\0";
    size_t sigSize = PanasonicMnHeader::sizeOfSignature();
    
    // Create buffer large enough
    std::vector<byte> data(sigSize + 100, 0);
    std::memcpy(data.data(), panasonicSig, std::min(sizeof(panasonicSig), sigSize));
    
    bool result = header_.read(data.data(), data.size(), littleEndian);
    EXPECT_TRUE(result);
}

// Test that ifdOffset matches sizeOfSignature after successful read
TEST_F(PanasonicMnHeaderTest_1475, IfdOffsetAfterValidRead_1475) {
    const byte panasonicSig[] = "Panasonic\0\0\0";
    size_t sigSize = PanasonicMnHeader::sizeOfSignature();
    
    std::vector<byte> data(sigSize + 100, 0);
    std::memcpy(data.data(), panasonicSig, std::min(sizeof(panasonicSig), sigSize));
    
    bool result = header_.read(data.data(), data.size(), littleEndian);
    if (result) {
        EXPECT_EQ(header_.ifdOffset(), sigSize);
    }
}

// Test read with invalid signature returns false
TEST_F(PanasonicMnHeaderTest_1475, ReadInvalidSignature_1475) {
    size_t sigSize = PanasonicMnHeader::sizeOfSignature();
    std::vector<byte> data(sigSize + 100, 0xFF);
    
    bool result = header_.read(data.data(), data.size(), littleEndian);
    EXPECT_FALSE(result);
}

// Test read with big endian byte order
TEST_F(PanasonicMnHeaderTest_1475, ReadValidSignatureBigEndian_1475) {
    const byte panasonicSig[] = "Panasonic\0\0\0";
    size_t sigSize = PanasonicMnHeader::sizeOfSignature();
    
    std::vector<byte> data(sigSize + 100, 0);
    std::memcpy(data.data(), panasonicSig, std::min(sizeof(panasonicSig), sigSize));
    
    bool result = header_.read(data.data(), data.size(), bigEndian);
    EXPECT_TRUE(result);
}

// Test read with exact minimum size
TEST_F(PanasonicMnHeaderTest_1475, ReadExactMinimumSize_1475) {
    const byte panasonicSig[] = "Panasonic\0\0\0";
    size_t sigSize = PanasonicMnHeader::sizeOfSignature();
    
    std::vector<byte> data(sigSize, 0);
    std::memcpy(data.data(), panasonicSig, std::min(sizeof(panasonicSig), sigSize));
    
    bool result = header_.read(data.data(), sigSize, littleEndian);
    // With exactly sigSize bytes, it should succeed if the signature matches
    EXPECT_TRUE(result);
}

// Test read with size just below minimum
TEST_F(PanasonicMnHeaderTest_1475, ReadSizeBelowMinimum_1475) {
    const byte panasonicSig[] = "Panasonic\0\0\0";
    size_t sigSize = PanasonicMnHeader::sizeOfSignature();
    
    if (sigSize > 0) {
        std::vector<byte> data(sigSize - 1, 0);
        std::memcpy(data.data(), panasonicSig, std::min(sizeof(panasonicSig), sigSize - 1));
        
        bool result = header_.read(data.data(), sigSize - 1, littleEndian);
        EXPECT_FALSE(result);
    }
}

// Test that multiple PanasonicMnHeader instances have consistent sizeOfSignature
TEST_F(PanasonicMnHeaderTest_1475, ConsistentSizeOfSignature_1475) {
    PanasonicMnHeader header2;
    EXPECT_EQ(header_.sizeOfSignature(), header2.sizeOfSignature());
}

// Test that multiple instances have same default ifdOffset
TEST_F(PanasonicMnHeaderTest_1475, ConsistentDefaultIfdOffset_1475) {
    PanasonicMnHeader header2;
    EXPECT_EQ(header_.ifdOffset(), header2.ifdOffset());
}
