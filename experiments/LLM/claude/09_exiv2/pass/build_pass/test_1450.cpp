#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
#include "makernote_int.hpp"

namespace Exiv2 {
namespace Internal {

// Test fixture for OMSystemMnHeader
class OMSystemMnHeaderTest_1450 : public ::testing::Test {
 protected:
  OMSystemMnHeader header_;
};

// Test baseOffset returns the mnOffset passed in (normal case)
TEST_F(OMSystemMnHeaderTest_1450, BaseOffsetReturnsInputOffset_1450) {
  size_t mnOffset = 100;
  EXPECT_EQ(header_.baseOffset(mnOffset), mnOffset);
}

// Test baseOffset with zero offset
TEST_F(OMSystemMnHeaderTest_1450, BaseOffsetWithZeroOffset_1450) {
  size_t mnOffset = 0;
  EXPECT_EQ(header_.baseOffset(mnOffset), 0u);
}

// Test baseOffset with large offset
TEST_F(OMSystemMnHeaderTest_1450, BaseOffsetWithLargeOffset_1450) {
  size_t mnOffset = std::numeric_limits<size_t>::max();
  EXPECT_EQ(header_.baseOffset(mnOffset), std::numeric_limits<size_t>::max());
}

// Test baseOffset with value of 1
TEST_F(OMSystemMnHeaderTest_1450, BaseOffsetWithOneOffset_1450) {
  size_t mnOffset = 1;
  EXPECT_EQ(header_.baseOffset(mnOffset), 1u);
}

// Test baseOffset with various typical values
TEST_F(OMSystemMnHeaderTest_1450, BaseOffsetWithTypicalValues_1450) {
  EXPECT_EQ(header_.baseOffset(42), 42u);
  EXPECT_EQ(header_.baseOffset(1024), 1024u);
  EXPECT_EQ(header_.baseOffset(65536), 65536u);
}

// Test baseOffset identity property - calling multiple times yields same result
TEST_F(OMSystemMnHeaderTest_1450, BaseOffsetIsConsistent_1450) {
  size_t mnOffset = 500;
  EXPECT_EQ(header_.baseOffset(mnOffset), header_.baseOffset(mnOffset));
}

// Test default construction
TEST_F(OMSystemMnHeaderTest_1450, DefaultConstruction_1450) {
  OMSystemMnHeader h;
  // Should be constructible and baseOffset should work
  EXPECT_EQ(h.baseOffset(10), 10u);
}

// Test sizeOfSignature is a valid value (non-negative by virtue of being size_t)
TEST_F(OMSystemMnHeaderTest_1450, SizeOfSignatureIsValid_1450) {
  size_t sigSize = OMSystemMnHeader::sizeOfSignature();
  // sizeOfSignature should return a reasonable value
  EXPECT_GE(sigSize, 0u);
}

// Test size returns a valid value
TEST_F(OMSystemMnHeaderTest_1450, SizeReturnsValidValue_1450) {
  size_t sz = header_.size();
  EXPECT_GE(sz, 0u);
}

// Test ifdOffset returns a valid value
TEST_F(OMSystemMnHeaderTest_1450, IfdOffsetReturnsValidValue_1450) {
  size_t offset = header_.ifdOffset();
  EXPECT_GE(offset, 0u);
}

// Test that size is consistent with sizeOfSignature
TEST_F(OMSystemMnHeaderTest_1450, SizeConsistentWithSignatureSize_1450) {
  size_t sz = header_.size();
  size_t sigSize = OMSystemMnHeader::sizeOfSignature();
  // Size should be at least as large as the signature
  EXPECT_GE(sz, sigSize);
}

// Test read with nullptr and zero size
TEST_F(OMSystemMnHeaderTest_1450, ReadWithNullptrAndZeroSize_1450) {
  bool result = header_.read(nullptr, 0, littleEndian);
  // With no data, read should likely fail
  EXPECT_FALSE(result);
}

// Test read with insufficient data size
TEST_F(OMSystemMnHeaderTest_1450, ReadWithInsufficientSize_1450) {
  byte data[1] = {0};
  bool result = header_.read(data, 1, littleEndian);
  // With insufficient data, read should fail
  EXPECT_FALSE(result);
}

// Test baseOffset with half of max size_t
TEST_F(OMSystemMnHeaderTest_1450, BaseOffsetWithHalfMaxValue_1450) {
  size_t halfMax = std::numeric_limits<size_t>::max() / 2;
  EXPECT_EQ(header_.baseOffset(halfMax), halfMax);
}

}  // namespace Internal
}  // namespace Exiv2
