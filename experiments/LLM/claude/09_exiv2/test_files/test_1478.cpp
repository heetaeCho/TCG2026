#include <gtest/gtest.h>
#include "makernote_int.hpp"

using namespace Exiv2::Internal;

class PentaxDngMnHeaderTest_1478 : public ::testing::Test {
protected:
    PentaxDngMnHeader header_;
};

TEST_F(PentaxDngMnHeaderTest_1478, SizeOfSignatureReturnsNonZero_1478) {
    size_t sigSize = header_.sizeOfSignature();
    EXPECT_GT(sigSize, 0u);
}

TEST_F(PentaxDngMnHeaderTest_1478, SizeOfSignatureIsConsistent_1478) {
    size_t sigSize1 = header_.sizeOfSignature();
    size_t sigSize2 = header_.sizeOfSignature();
    EXPECT_EQ(sigSize1, sigSize2);
}

TEST_F(PentaxDngMnHeaderTest_1478, SizeReturnsExpectedValue_1478) {
    size_t sz = header_.size();
    EXPECT_GT(sz, 0u);
}

TEST_F(PentaxDngMnHeaderTest_1478, SizeIsAtLeastSignatureSize_1478) {
    size_t sz = header_.size();
    size_t sigSize = header_.sizeOfSignature();
    EXPECT_GE(sz, sigSize);
}

TEST_F(PentaxDngMnHeaderTest_1478, IfdOffsetReturnsValue_1478) {
    size_t offset = header_.ifdOffset();
    // ifdOffset should be a reasonable value (at least 0)
    EXPECT_GE(offset, 0u);
}

TEST_F(PentaxDngMnHeaderTest_1478, BaseOffsetReturnsValue_1478) {
    size_t mnOffset = 100;
    size_t baseOff = header_.baseOffset(mnOffset);
    EXPECT_GE(baseOff, 0u);
}

TEST_F(PentaxDngMnHeaderTest_1478, BaseOffsetWithZeroMnOffset_1478) {
    size_t baseOff = header_.baseOffset(0);
    EXPECT_GE(baseOff, 0u);
}

TEST_F(PentaxDngMnHeaderTest_1478, ReadWithNullptrReturnsFalse_1478) {
    bool result = header_.read(nullptr, 0, Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

TEST_F(PentaxDngMnHeaderTest_1478, ReadWithInsufficientSizeReturnsFalse_1478) {
    Exiv2::byte data[] = {0x00};
    bool result = header_.read(data, 1, Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

TEST_F(PentaxDngMnHeaderTest_1478, ReadWithZeroSizeReturnsFalse_1478) {
    Exiv2::byte data[] = {0x00, 0x01, 0x02, 0x03};
    bool result = header_.read(data, 0, Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

TEST_F(PentaxDngMnHeaderTest_1478, ReadWithValidPentaxDngSignature_1478) {
    // The Pentax DNG maker note signature is "PENTAX \0" or similar
    // Construct a buffer that matches the expected signature
    const size_t sigSize = header_.sizeOfSignature();
    const size_t bufSize = header_.size() + 100;
    std::vector<Exiv2::byte> data(bufSize, 0);
    
    // Try with "PENTAX \0" signature (known Pentax DNG MN header)
    const char pentaxSig[] = "PENTAX \0MM";
    if (sigSize <= sizeof(pentaxSig)) {
        std::memcpy(data.data(), pentaxSig, std::min(sizeof(pentaxSig), bufSize));
    }
    
    // We just test it doesn't crash; result depends on signature match
    bool result = header_.read(data.data(), data.size(), Exiv2::bigEndian);
    // Result could be true or false depending on exact expected signature
    (void)result;
}

TEST_F(PentaxDngMnHeaderTest_1478, ReadWithWrongSignatureReturnsFalse_1478) {
    const size_t bufSize = header_.size() + 100;
    std::vector<Exiv2::byte> data(bufSize, 0xFF);
    bool result = header_.read(data.data(), data.size(), Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

TEST_F(PentaxDngMnHeaderTest_1478, SizeOfSignatureMultipleInstances_1478) {
    PentaxDngMnHeader header2;
    EXPECT_EQ(header_.sizeOfSignature(), header2.sizeOfSignature());
}

TEST_F(PentaxDngMnHeaderTest_1478, SizeMultipleInstances_1478) {
    PentaxDngMnHeader header2;
    EXPECT_EQ(header_.size(), header2.size());
}

TEST_F(PentaxDngMnHeaderTest_1478, IfdOffsetMultipleInstances_1478) {
    PentaxDngMnHeader header2;
    EXPECT_EQ(header_.ifdOffset(), header2.ifdOffset());
}

TEST_F(PentaxDngMnHeaderTest_1478, BaseOffsetWithLargeOffset_1478) {
    size_t largeOffset = 1000000;
    size_t baseOff = header_.baseOffset(largeOffset);
    EXPECT_GE(baseOff, 0u);
}

TEST_F(PentaxDngMnHeaderTest_1478, ReadWithExactSignatureSize_1478) {
    size_t sigSize = header_.sizeOfSignature();
    std::vector<Exiv2::byte> data(sigSize, 0);
    // Likely too small if header needs more than just signature
    bool result = header_.read(data.data(), data.size(), Exiv2::littleEndian);
    // Just verify it doesn't crash
    (void)result;
}
