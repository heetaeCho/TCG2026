#include <gtest/gtest.h>
#include "tiffcomposite_int.hpp"
#include "types.hpp"

// Include necessary headers for the project
#include <cstdint>

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper function to create a basic ArrayCfg for testing
namespace {

// We need to set up valid ArrayCfg and ArrayDef structures for testing.
// These are typically defined in the Exiv2 internal headers.

static const ArrayCfg testArrayCfg = {
    IfdId::ifd0Id,       // group
    invalidByteOrder,    // byte order
    ttUndefined,         // elTiffType
    notEncrypted,        // cryptFct
    false,               // hasSize
    false,               // hasFillers
    false                // concat
};

static const ArrayDef testArrayDef[] = {
    {0, ttUndefined, 1},
    {1, ttUndefined, 1},
    {2, ttUndefined, 2}
};

static const ArrayCfg testArrayCfg2 = {
    IfdId::exifId,
    invalidByteOrder,
    ttUnsignedByte,
    notEncrypted,
    false,
    false,
    false
};

} // anonymous namespace

class TiffBinaryArrayTest_250 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test construction with ArrayCfg and ArrayDef
TEST_F(TiffBinaryArrayTest_250, ConstructWithArrayCfgAndDef_250) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);
    EXPECT_NE(arr.cfg(), nullptr);
    EXPECT_EQ(arr.cfg(), &testArrayCfg);
    EXPECT_NE(arr.def(), nullptr);
    EXPECT_EQ(arr.def(), testArrayDef);
    EXPECT_EQ(arr.defSize(), 3u);
}

// Test that cfg() returns the correct pointer
TEST_F(TiffBinaryArrayTest_250, CfgReturnsCorrectPointer_250) {
    TiffBinaryArray arr(0x0002, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);
    const ArrayCfg* cfg = arr.cfg();
    ASSERT_NE(cfg, nullptr);
    EXPECT_EQ(cfg, &testArrayCfg);
}

// Test that def() returns the correct pointer
TEST_F(TiffBinaryArrayTest_250, DefReturnsCorrectPointer_250) {
    TiffBinaryArray arr(0x0003, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);
    const ArrayDef* def = arr.def();
    ASSERT_NE(def, nullptr);
    EXPECT_EQ(def, testArrayDef);
}

// Test defSize returns correct size
TEST_F(TiffBinaryArrayTest_250, DefSizeReturnsCorrectSize_250) {
    TiffBinaryArray arr(0x0004, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);
    EXPECT_EQ(arr.defSize(), 3u);
}

// Test defSize with zero
TEST_F(TiffBinaryArrayTest_250, DefSizeZero_250) {
    TiffBinaryArray arr(0x0005, IfdId::ifd0Id, testArrayCfg, nullptr, 0);
    EXPECT_EQ(arr.defSize(), 0u);
    EXPECT_EQ(arr.def(), nullptr);
}

// Test decoded default is false
TEST_F(TiffBinaryArrayTest_250, DecodedDefaultIsFalse_250) {
    TiffBinaryArray arr(0x0006, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);
    EXPECT_FALSE(arr.decoded());
}

// Test setDecoded to true
TEST_F(TiffBinaryArrayTest_250, SetDecodedTrue_250) {
    TiffBinaryArray arr(0x0007, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);
    arr.setDecoded(true);
    EXPECT_TRUE(arr.decoded());
}

// Test setDecoded toggle
TEST_F(TiffBinaryArrayTest_250, SetDecodedToggle_250) {
    TiffBinaryArray arr(0x0008, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);
    arr.setDecoded(true);
    EXPECT_TRUE(arr.decoded());
    arr.setDecoded(false);
    EXPECT_FALSE(arr.decoded());
}

// Test cfg returns correct config with different ArrayCfg
TEST_F(TiffBinaryArrayTest_250, CfgReturnsDifferentConfig_250) {
    TiffBinaryArray arr1(0x0009, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);
    TiffBinaryArray arr2(0x000A, IfdId::exifId, testArrayCfg2, testArrayDef, 2);
    EXPECT_EQ(arr1.cfg(), &testArrayCfg);
    EXPECT_EQ(arr2.cfg(), &testArrayCfg2);
    EXPECT_NE(arr1.cfg(), arr2.cfg());
}

// Test construction with null ArrayDef
TEST_F(TiffBinaryArrayTest_250, ConstructWithNullArrayDef_250) {
    TiffBinaryArray arr(0x000B, IfdId::ifd0Id, testArrayCfg, nullptr, 0);
    EXPECT_EQ(arr.cfg(), &testArrayCfg);
    EXPECT_EQ(arr.def(), nullptr);
    EXPECT_EQ(arr.defSize(), 0u);
}

// Test initialize with IfdId group
TEST_F(TiffBinaryArrayTest_250, InitializeWithGroup_250) {
    // Use ArraySet-based constructor for this test if possible
    // For the ArrayCfg constructor, initialize should work based on the cfg
    TiffBinaryArray arr(0x000C, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);
    // initialize with a group - behavior depends on cfgSelFct_ being null
    bool result = arr.initialize(IfdId::ifd0Id);
    // With the ArrayCfg constructor, cfgSelFct_ is default (null), so initialize
    // may return false since there's no selection function
    // We just verify it doesn't crash and returns a bool
    (void)result;
}

// Test initialize with TiffComponent pointer (null)
TEST_F(TiffBinaryArrayTest_250, InitializeWithNullRoot_250) {
    TiffBinaryArray arr(0x000D, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);
    bool result = arr.initialize(nullptr);
    // Just verify it doesn't crash
    (void)result;
}

// Test iniOrigDataBuf
TEST_F(TiffBinaryArrayTest_250, IniOrigDataBuf_250) {
    TiffBinaryArray arr(0x000E, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);
    // Should not crash even when no data is set
    arr.iniOrigDataBuf();
}

// Test updOrigDataBuf with null data
TEST_F(TiffBinaryArrayTest_250, UpdOrigDataBufWithNull_250) {
    TiffBinaryArray arr(0x000F, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);
    bool result = arr.updOrigDataBuf(nullptr, 0);
    // Verify it doesn't crash; result depends on internal state
    (void)result;
}

// Test updOrigDataBuf with valid data
TEST_F(TiffBinaryArrayTest_250, UpdOrigDataBufWithData_250) {
    TiffBinaryArray arr(0x0010, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);
    arr.iniOrigDataBuf();
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    bool result = arr.updOrigDataBuf(data, sizeof(data));
    (void)result;
}

// Test multiple setDecoded calls
TEST_F(TiffBinaryArrayTest_250, MultipleSetDecodedCalls_250) {
    TiffBinaryArray arr(0x0011, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);
    arr.setDecoded(true);
    arr.setDecoded(true);
    EXPECT_TRUE(arr.decoded());
    arr.setDecoded(false);
    arr.setDecoded(false);
    EXPECT_FALSE(arr.decoded());
}

// Test cfg consistency after operations
TEST_F(TiffBinaryArrayTest_250, CfgConsistencyAfterOperations_250) {
    TiffBinaryArray arr(0x0012, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);
    arr.setDecoded(true);
    arr.iniOrigDataBuf();
    // cfg should still be the same
    EXPECT_EQ(arr.cfg(), &testArrayCfg);
    EXPECT_EQ(arr.def(), testArrayDef);
    EXPECT_EQ(arr.defSize(), 3u);
}

// Test with large defSize
TEST_F(TiffBinaryArrayTest_250, LargeDefSize_250) {
    static const ArrayDef largeDef[] = {
        {0, ttUndefined, 1},
    };
    TiffBinaryArray arr(0x0013, IfdId::ifd0Id, testArrayCfg, largeDef, 1);
    EXPECT_EQ(arr.defSize(), 1u);
    EXPECT_EQ(arr.def(), largeDef);
}
