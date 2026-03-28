#include <gtest/gtest.h>
#include "tiffcomposite_int.hpp"
#include "types.hpp"
#include "tags_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper to create a basic ArrayCfg for testing
namespace {

// We need to define minimal ArrayCfg and ArrayDef structures for construction
// These are existing types in the Exiv2 codebase

ArrayCfg makeTestArrayCfg() {
    ArrayCfg cfg{
        IfdId::ifd0Id,      // group
        invalidByteOrder,   // byteOrder
        ttUndefined,        // elTiffType
        notEncrypted,       // cryptFct
        false,              // hasSize
        false,              // hasFillers
        false               // concat
    };
    return cfg;
}

ArrayDef makeTestArrayDef(size_t idx, size_t count, TiffType tiffType) {
    ArrayDef def{static_cast<uint32_t>(idx), static_cast<uint32_t>(count), tiffType};
    return def;
}

} // anonymous namespace

class TiffBinaryArrayTest_252 : public ::testing::Test {
protected:
    void SetUp() override {
        arrayCfg_ = makeTestArrayCfg();
    }

    ArrayCfg arrayCfg_;
};

// Test that defSize returns the value passed during construction with ArrayCfg constructor
TEST_F(TiffBinaryArrayTest_252, DefSizeReturnsConstructedValue_252) {
    ArrayDef defs[] = {makeTestArrayDef(0, 1, ttUndefined)};
    size_t defSize = 1;
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, arrayCfg_, defs, defSize);
    EXPECT_EQ(arr.defSize(), defSize);
}

// Test defSize with zero
TEST_F(TiffBinaryArrayTest_252, DefSizeZero_252) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, arrayCfg_, nullptr, 0);
    EXPECT_EQ(arr.defSize(), 0u);
}

// Test defSize with larger value
TEST_F(TiffBinaryArrayTest_252, DefSizeLargerValue_252) {
    ArrayDef defs[] = {
        makeTestArrayDef(0, 1, ttUndefined),
        makeTestArrayDef(1, 1, ttUndefined),
        makeTestArrayDef(2, 1, ttUndefined),
        makeTestArrayDef(3, 1, ttUndefined),
        makeTestArrayDef(4, 1, ttUndefined)
    };
    size_t defSize = 5;
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, arrayCfg_, defs, defSize);
    EXPECT_EQ(arr.defSize(), 5u);
}

// Test that cfg() returns the arrayCfg passed during construction
TEST_F(TiffBinaryArrayTest_252, CfgReturnsPassedArrayCfg_252) {
    ArrayDef defs[] = {makeTestArrayDef(0, 1, ttUndefined)};
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, arrayCfg_, defs, 1);
    EXPECT_EQ(arr.cfg(), &arrayCfg_);
}

// Test that def() returns the arrayDef passed during construction
TEST_F(TiffBinaryArrayTest_252, DefReturnsPassedArrayDef_252) {
    ArrayDef defs[] = {makeTestArrayDef(0, 1, ttUndefined)};
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, arrayCfg_, defs, 1);
    EXPECT_EQ(arr.def(), defs);
}

// Test that def() returns nullptr when nullptr is passed
TEST_F(TiffBinaryArrayTest_252, DefReturnsNullWhenNullPassed_252) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, arrayCfg_, nullptr, 0);
    EXPECT_EQ(arr.def(), nullptr);
}

// Test decoded() default is false
TEST_F(TiffBinaryArrayTest_252, DecodedDefaultIsFalse_252) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, arrayCfg_, nullptr, 0);
    EXPECT_FALSE(arr.decoded());
}

// Test setDecoded changes decoded state to true
TEST_F(TiffBinaryArrayTest_252, SetDecodedTrue_252) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, arrayCfg_, nullptr, 0);
    arr.setDecoded(true);
    EXPECT_TRUE(arr.decoded());
}

// Test setDecoded can set back to false
TEST_F(TiffBinaryArrayTest_252, SetDecodedFalseAfterTrue_252) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, arrayCfg_, nullptr, 0);
    arr.setDecoded(true);
    EXPECT_TRUE(arr.decoded());
    arr.setDecoded(false);
    EXPECT_FALSE(arr.decoded());
}

// Test construction with ArraySet constructor (second constructor)
TEST_F(TiffBinaryArrayTest_252, ArraySetConstructorDefSizeIsZero_252) {
    // When constructed with ArraySet constructor, defSize_ should be default (0)
    auto cfgSelFct = [](uint16_t, const byte*, size_t, size_t) -> int { return 0; };
    ArraySet arraySet[] = {
        {arrayCfg_, nullptr, 0}
    };
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, arraySet, 1, cfgSelFct);
    EXPECT_EQ(arr.defSize(), 0u);
}

// Test updOrigDataBuf with nullptr and zero size
TEST_F(TiffBinaryArrayTest_252, UpdOrigDataBufNullData_252) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, arrayCfg_, nullptr, 0);
    arr.iniOrigDataBuf();
    bool result = arr.updOrigDataBuf(nullptr, 0);
    // Just verify it doesn't crash and returns a value
    (void)result;
}

// Test initialize with pRoot nullptr
TEST_F(TiffBinaryArrayTest_252, InitializeWithNullRoot_252) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, arrayCfg_, nullptr, 0);
    bool result = arr.initialize(static_cast<TiffComponent*>(nullptr));
    // Verify it doesn't crash
    (void)result;
}

// Test boundary: maximum defSize
TEST_F(TiffBinaryArrayTest_252, DefSizeMaxBoundary_252) {
    size_t largeDefSize = 10000;
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, arrayCfg_, nullptr, largeDefSize);
    EXPECT_EQ(arr.defSize(), largeDefSize);
}
