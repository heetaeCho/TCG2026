#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"

// Include necessary headers for ArraySet, CfgSelFct, IfdId, etc.
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// We need to define test fixtures with actual ArraySet data and CfgSelFct

namespace {

// A simple configuration selection function for testing
int testCfgSelFct(uint16_t /*tag*/, const byte* /*pData*/, size_t /*size*/, TiffComponent* const /*pRoot*/) {
    return 0;
}

// Define minimal ArraySet arrays for testing
// We need at least one element to satisfy static_assert
const ArrayCfg testArrayCfg = {
    IfdId::ifd0Id,       // group
    invalidByteOrder,    // byte order
    ttUndefined,         // type
    notEncrypted,        // encryption
    false,               // hasFillers
    false,               // hasSize
};

const ArrayDef testArrayDef[] = {
    {0, ttUndefined, 1},
};

const ArraySet testArraySet1[] = {
    {testArrayCfg, testArrayDef, 1},
};

const ArraySet testArraySet2[] = {
    {testArrayCfg, testArrayDef, 1},
    {testArrayCfg, testArrayDef, 1},
};

} // anonymous namespace

class NewTiffBinaryArray2Test_262 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test that the function returns a non-null unique_ptr with a single element ArraySet
TEST_F(NewTiffBinaryArray2Test_262, ReturnsNonNullWithSingleElementArraySet_262) {
    auto result = newTiffBinaryArray2<1, testArraySet1, testCfgSelFct>(0x0001, IfdId::ifd0Id);
    ASSERT_NE(result, nullptr);
}

// Test that the function returns a non-null unique_ptr with a multi-element ArraySet
TEST_F(NewTiffBinaryArray2Test_262, ReturnsNonNullWithMultiElementArraySet_262) {
    auto result = newTiffBinaryArray2<2, testArraySet2, testCfgSelFct>(0x0002, IfdId::ifd0Id);
    ASSERT_NE(result, nullptr);
}

// Test that the returned component has the correct tag
TEST_F(NewTiffBinaryArray2Test_262, ReturnedComponentHasCorrectTag_262) {
    const uint16_t expectedTag = 0x1234;
    auto result = newTiffBinaryArray2<1, testArraySet1, testCfgSelFct>(expectedTag, IfdId::ifd0Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), expectedTag);
}

// Test with tag value of 0
TEST_F(NewTiffBinaryArray2Test_262, WorksWithZeroTag_262) {
    auto result = newTiffBinaryArray2<1, testArraySet1, testCfgSelFct>(0x0000, IfdId::ifd0Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0x0000);
}

// Test with maximum tag value
TEST_F(NewTiffBinaryArray2Test_262, WorksWithMaxTag_262) {
    auto result = newTiffBinaryArray2<1, testArraySet1, testCfgSelFct>(0xFFFF, IfdId::ifd0Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0xFFFF);
}

// Test that different groups produce valid components
TEST_F(NewTiffBinaryArray2Test_262, WorksWithDifferentGroups_262) {
    auto result1 = newTiffBinaryArray2<1, testArraySet1, testCfgSelFct>(0x0001, IfdId::ifd0Id);
    auto result2 = newTiffBinaryArray2<1, testArraySet1, testCfgSelFct>(0x0001, IfdId::exifId);
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
}

// Test that multiple calls produce independent objects
TEST_F(NewTiffBinaryArray2Test_262, MultipleCallsProduceIndependentObjects_262) {
    auto result1 = newTiffBinaryArray2<1, testArraySet1, testCfgSelFct>(0x0001, IfdId::ifd0Id);
    auto result2 = newTiffBinaryArray2<1, testArraySet1, testCfgSelFct>(0x0001, IfdId::ifd0Id);
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    EXPECT_NE(result1.get(), result2.get());
}
