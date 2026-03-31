#include <gtest/gtest.h>
#include "makernote_int.hpp"

using namespace Exiv2::Internal;

class OMSystemMnHeaderTest_1449 : public ::testing::Test {
protected:
    OMSystemMnHeader header;
};

// Test that ifdOffset returns sizeOfSignature
TEST_F(OMSystemMnHeaderTest_1449, IfdOffsetEqualsSizeOfSignature_1449) {
    EXPECT_EQ(header.ifdOffset(), OMSystemMnHeader::sizeOfSignature());
}

// Test that ifdOffset returns a consistent value across multiple calls
TEST_F(OMSystemMnHeaderTest_1449, IfdOffsetIsConsistent_1449) {
    size_t first = header.ifdOffset();
    size_t second = header.ifdOffset();
    EXPECT_EQ(first, second);
}

// Test that sizeOfSignature returns a non-zero value (signature must have some length)
TEST_F(OMSystemMnHeaderTest_1449, SizeOfSignatureIsNonZero_1449) {
    EXPECT_GT(OMSystemMnHeader::sizeOfSignature(), 0u);
}

// Test that ifdOffset is non-zero since sizeOfSignature should be non-zero
TEST_F(OMSystemMnHeaderTest_1449, IfdOffsetIsNonZero_1449) {
    EXPECT_GT(header.ifdOffset(), 0u);
}

// Test that size() returns a value >= sizeOfSignature (size should encompass at least the signature)
TEST_F(OMSystemMnHeaderTest_1449, SizeIsAtLeastSizeOfSignature_1449) {
    EXPECT_GE(header.size(), OMSystemMnHeader::sizeOfSignature());
}

// Test default constructed header - read with nullptr and zero size should fail
TEST_F(OMSystemMnHeaderTest_1449, ReadWithNullptrAndZeroSizeFails_1449) {
    bool result = header.read(nullptr, 0, Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

// Test read with insufficient data size
TEST_F(OMSystemMnHeaderTest_1449, ReadWithInsufficientSizeFails_1449) {
    Exiv2::byte data[1] = {0};
    bool result = header.read(data, 1, Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

// Test read with valid OM SYSTEM signature
TEST_F(OMSystemMnHeaderTest_1449, ReadWithValidOMSystemSignature_1449) {
    // OM SYSTEM maker note signature is typically "OLYMPUS\0II\x03\0"
    // but for OM System it may differ. We test with a buffer large enough.
    const size_t sigSize = OMSystemMnHeader::sizeOfSignature();
    std::vector<Exiv2::byte> data(sigSize + 100, 0);
    
    // Attempt to read - result depends on actual signature content
    // This tests the interface without assuming internal logic
    bool result = header.read(data.data(), data.size(), Exiv2::littleEndian);
    // We just verify it doesn't crash; result may be true or false depending on signature match
    (void)result;
}

// Test baseOffset with zero mnOffset
TEST_F(OMSystemMnHeaderTest_1449, BaseOffsetWithZeroMnOffset_1449) {
    size_t baseOff = header.baseOffset(0);
    // baseOffset should return some value; verify it doesn't throw
    EXPECT_GE(baseOff, 0u);
}

// Test baseOffset with non-zero mnOffset
TEST_F(OMSystemMnHeaderTest_1449, BaseOffsetWithNonZeroMnOffset_1449) {
    size_t baseOff = header.baseOffset(100);
    // Just ensure it returns without crashing
    EXPECT_GE(baseOff, 0u);
}

// Test that multiple instances return same ifdOffset
TEST(OMSystemMnHeaderMultiInstanceTest_1449, MultipleInstancesSameIfdOffset_1449) {
    OMSystemMnHeader h1;
    OMSystemMnHeader h2;
    EXPECT_EQ(h1.ifdOffset(), h2.ifdOffset());
}

// Test that multiple instances return same size
TEST(OMSystemMnHeaderMultiInstanceTest_1449, MultipleInstancesSameSize_1449) {
    OMSystemMnHeader h1;
    OMSystemMnHeader h2;
    EXPECT_EQ(h1.size(), h2.size());
}

// Test that sizeOfSignature is a static method returning consistent value
TEST(OMSystemMnHeaderStaticTest_1449, SizeOfSignatureIsStatic_1449) {
    size_t s1 = OMSystemMnHeader::sizeOfSignature();
    size_t s2 = OMSystemMnHeader::sizeOfSignature();
    EXPECT_EQ(s1, s2);
}
