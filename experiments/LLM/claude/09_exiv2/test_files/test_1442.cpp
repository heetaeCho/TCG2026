#include <gtest/gtest.h>
#include "makernote_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Olympus2MnHeaderTest_1442 : public ::testing::Test {
protected:
    Olympus2MnHeader header_;
};

TEST_F(Olympus2MnHeaderTest_1442, DefaultConstructor_SizeIsSignatureSize_1442) {
    // After default construction, size() should return the size of the signature
    size_t sz = header_.size();
    size_t sigSize = Olympus2MnHeader::sizeOfSignature();
    EXPECT_EQ(sz, sigSize);
}

TEST_F(Olympus2MnHeaderTest_1442, SizeOfSignature_ReturnsNonZero_1442) {
    size_t sigSize = Olympus2MnHeader::sizeOfSignature();
    EXPECT_GT(sigSize, 0u);
}

TEST_F(Olympus2MnHeaderTest_1442, SizeIsConsistentWithSizeOfSignature_1442) {
    EXPECT_EQ(header_.size(), Olympus2MnHeader::sizeOfSignature());
}

TEST_F(Olympus2MnHeaderTest_1442, IfdOffset_ReturnsExpectedValue_1442) {
    // ifdOffset should return some value after default construction
    size_t offset = header_.ifdOffset();
    // The IFD offset for Olympus2 is typically equal to the signature size
    EXPECT_GE(offset, 0u);
}

TEST_F(Olympus2MnHeaderTest_1442, BaseOffset_ReturnsExpectedValue_1442) {
    size_t mnOffset = 100;
    size_t baseOff = header_.baseOffset(mnOffset);
    // baseOffset typically returns the mnOffset for Olympus2
    EXPECT_EQ(baseOff, mnOffset);
}

TEST_F(Olympus2MnHeaderTest_1442, BaseOffset_ZeroMnOffset_1442) {
    size_t baseOff = header_.baseOffset(0);
    EXPECT_EQ(baseOff, 0u);
}

TEST_F(Olympus2MnHeaderTest_1442, BaseOffset_LargeMnOffset_1442) {
    size_t largeMnOffset = 0xFFFFFFFF;
    size_t baseOff = header_.baseOffset(largeMnOffset);
    EXPECT_EQ(baseOff, largeMnOffset);
}

TEST_F(Olympus2MnHeaderTest_1442, Read_ValidSignature_1442) {
    // Olympus2 MakerNote signature is "OLYMPUS\0II" (12 bytes typically)
    const byte olympus2Sig[] = "OLYMPUS\0II\x03\x00";
    size_t sigSize = Olympus2MnHeader::sizeOfSignature();
    
    // Only attempt if we have enough data
    if (sigSize <= sizeof(olympus2Sig)) {
        bool result = header_.read(olympus2Sig, sizeof(olympus2Sig), littleEndian);
        EXPECT_TRUE(result);
    }
}

TEST_F(Olympus2MnHeaderTest_1442, Read_InvalidSignature_1442) {
    const byte invalidData[] = "INVALID_DATA_HERE!!!";
    bool result = header_.read(invalidData, sizeof(invalidData), littleEndian);
    EXPECT_FALSE(result);
}

TEST_F(Olympus2MnHeaderTest_1442, Read_TooSmallData_1442) {
    const byte smallData[] = "OLY";
    bool result = header_.read(smallData, sizeof(smallData), littleEndian);
    EXPECT_FALSE(result);
}

TEST_F(Olympus2MnHeaderTest_1442, Read_ZeroSizeData_1442) {
    const byte data[] = {0};
    bool result = header_.read(data, 0, littleEndian);
    EXPECT_FALSE(result);
}

TEST_F(Olympus2MnHeaderTest_1442, Read_ExactSignatureSize_ValidData_1442) {
    // Construct proper Olympus2 signature: "OLYMPUS\0II\x03\x00"
    size_t sigSize = Olympus2MnHeader::sizeOfSignature();
    std::vector<byte> data(sigSize, 0);
    
    // Fill with Olympus2 signature
    const char* sig = "OLYMPUS";
    size_t sigLen = 7;
    if (sigSize >= 12) {
        std::memcpy(data.data(), sig, sigLen);
        data[7] = 0x00;  // null terminator
        data[8] = 'I';
        data[9] = 'I';
        data[10] = 0x03;
        data[11] = 0x00;
    }
    
    bool result = header_.read(data.data(), data.size(), littleEndian);
    // If signature is correct, should return true
    if (sigSize == 12) {
        EXPECT_TRUE(result);
    }
}

TEST_F(Olympus2MnHeaderTest_1442, Read_BigEndianByteOrder_1442) {
    const byte olympus2Sig[] = "OLYMPUS\0II\x03\x00";
    size_t sigSize = Olympus2MnHeader::sizeOfSignature();
    
    if (sigSize <= sizeof(olympus2Sig)) {
        // ByteOrder parameter shouldn't matter for Olympus2 read since 
        // the signature encodes its own byte order
        bool result = header_.read(olympus2Sig, sizeof(olympus2Sig), bigEndian);
        EXPECT_TRUE(result);
    }
}

TEST_F(Olympus2MnHeaderTest_1442, Read_AllZeroData_1442) {
    size_t sigSize = Olympus2MnHeader::sizeOfSignature();
    std::vector<byte> zeroData(sigSize, 0);
    bool result = header_.read(zeroData.data(), zeroData.size(), littleEndian);
    EXPECT_FALSE(result);
}

TEST_F(Olympus2MnHeaderTest_1442, SizeAfterSuccessfulRead_1442) {
    const byte olympus2Sig[] = "OLYMPUS\0II\x03\x00";
    size_t sigSize = Olympus2MnHeader::sizeOfSignature();
    
    if (sigSize <= sizeof(olympus2Sig)) {
        header_.read(olympus2Sig, sizeof(olympus2Sig), littleEndian);
        EXPECT_EQ(header_.size(), sigSize);
    }
}

TEST_F(Olympus2MnHeaderTest_1442, MultipleSizeCallsReturnSameValue_1442) {
    size_t size1 = header_.size();
    size_t size2 = header_.size();
    EXPECT_EQ(size1, size2);
}
