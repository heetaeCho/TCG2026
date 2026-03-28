#include <gtest/gtest.h>
#include "makernote_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for MnHeader tests
class MnHeaderTest_1434 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that the default byteOrder() returns invalidByteOrder
TEST_F(MnHeaderTest_1434, DefaultByteOrderReturnsInvalid_1434) {
    MnHeader header;
    EXPECT_EQ(header.byteOrder(), invalidByteOrder);
}

// Test that byteOrder() does not return littleEndian by default
TEST_F(MnHeaderTest_1434, DefaultByteOrderIsNotLittleEndian_1434) {
    MnHeader header;
    EXPECT_NE(header.byteOrder(), littleEndian);
}

// Test that byteOrder() does not return bigEndian by default
TEST_F(MnHeaderTest_1434, DefaultByteOrderIsNotBigEndian_1434) {
    MnHeader header;
    EXPECT_NE(header.byteOrder(), bigEndian);
}

// Test that byteOrder() is consistent across multiple calls
TEST_F(MnHeaderTest_1434, ByteOrderIsConsistentAcrossCalls_1434) {
    MnHeader header;
    ByteOrder first = header.byteOrder();
    ByteOrder second = header.byteOrder();
    EXPECT_EQ(first, second);
}

// Test that the default ifdOffset() returns 0
TEST_F(MnHeaderTest_1434, DefaultIfdOffsetReturnsZero_1434) {
    MnHeader header;
    EXPECT_EQ(header.ifdOffset(), 0u);
}

// Test that the default baseOffset() returns 0 regardless of mnOffset
TEST_F(MnHeaderTest_1434, DefaultBaseOffsetReturnsZero_1434) {
    MnHeader header;
    EXPECT_EQ(header.baseOffset(0), 0u);
}

// Test that baseOffset returns 0 for non-zero mnOffset
TEST_F(MnHeaderTest_1434, DefaultBaseOffsetReturnsZeroForNonZeroOffset_1434) {
    MnHeader header;
    EXPECT_EQ(header.baseOffset(100), 0u);
}

// Test that baseOffset returns 0 for large mnOffset
TEST_F(MnHeaderTest_1434, DefaultBaseOffsetReturnsZeroForLargeOffset_1434) {
    MnHeader header;
    EXPECT_EQ(header.baseOffset(999999), 0u);
}

// Test setByteOrder - after setting, verify byteOrder still returns invalidByteOrder
// (base class implementation returns invalidByteOrder regardless)
TEST_F(MnHeaderTest_1434, SetByteOrderBaseClassBehavior_1434) {
    MnHeader header;
    header.setByteOrder(littleEndian);
    // Base class byteOrder() always returns invalidByteOrder
    EXPECT_EQ(header.byteOrder(), invalidByteOrder);
}

// Test setByteOrder with bigEndian
TEST_F(MnHeaderTest_1434, SetByteOrderBigEndianBaseClass_1434) {
    MnHeader header;
    header.setByteOrder(bigEndian);
    // Base class byteOrder() always returns invalidByteOrder
    EXPECT_EQ(header.byteOrder(), invalidByteOrder);
}

// Test setByteOrder with invalidByteOrder
TEST_F(MnHeaderTest_1434, SetByteOrderInvalidBaseClass_1434) {
    MnHeader header;
    header.setByteOrder(invalidByteOrder);
    EXPECT_EQ(header.byteOrder(), invalidByteOrder);
}

// Boundary: baseOffset with max size_t value
TEST_F(MnHeaderTest_1434, BaseOffsetWithMaxSizeT_1434) {
    MnHeader header;
    EXPECT_EQ(header.baseOffset(std::numeric_limits<size_t>::max()), 0u);
}

// Boundary: baseOffset with 1
TEST_F(MnHeaderTest_1434, BaseOffsetWithOne_1434) {
    MnHeader header;
    EXPECT_EQ(header.baseOffset(1), 0u);
}
