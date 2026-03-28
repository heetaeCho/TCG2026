#include <gtest/gtest.h>
#include "tiffcomposite_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper to create a minimal ArrayCfg for testing
namespace {

// We need to define minimal test fixtures based on available types
// ArrayCfg and ArrayDef are structures used by TiffBinaryArray

class TiffBinaryArrayTest_251 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

} // anonymous namespace

// Test: Constructor with ArrayCfg stores the arrayDef pointer correctly
TEST_F(TiffBinaryArrayTest_251, ConstructorWithArrayCfgStoresDefPointer_251) {
    ArrayCfg arrayCfg{
        IfdId::ifd0Id,    // group
        invalidByteOrder, // byteOrder
        ttUndefined,      // elTiffType
        notEncrypted,     // cryptFct
        false,            // hasFillers
        false             // hasSize
    };
    
    ArrayDef arrayDef[] = {
        {0, ttUnsignedByte, 1}
    };
    
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, arrayCfg, arrayDef, 1);
    
    EXPECT_EQ(arr.def(), arrayDef);
}

// Test: Constructor with ArrayCfg and nullptr arrayDef
TEST_F(TiffBinaryArrayTest_251, ConstructorWithNullArrayDef_251) {
    ArrayCfg arrayCfg{
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false
    };
    
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, arrayCfg, nullptr, 0);
    
    EXPECT_EQ(arr.def(), nullptr);
}

// Test: cfg() returns the arrayCfg pointer from first constructor
TEST_F(TiffBinaryArrayTest_251, CfgReturnsArrayCfgPointer_251) {
    ArrayCfg arrayCfg{
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false
    };
    
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, arrayCfg, nullptr, 0);
    
    EXPECT_EQ(arr.cfg(), &arrayCfg);
}

// Test: defSize() returns the size passed to constructor
TEST_F(TiffBinaryArrayTest_251, DefSizeReturnsCorrectValue_251) {
    ArrayCfg arrayCfg{
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false
    };
    
    ArrayDef arrayDef[] = {
        {0, ttUnsignedByte, 1},
        {1, ttUnsignedByte, 1},
        {2, ttUnsignedByte, 1}
    };
    
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, arrayCfg, arrayDef, 3);
    
    EXPECT_EQ(arr.defSize(), 3u);
}

// Test: defSize() returns zero when constructed with zero
TEST_F(TiffBinaryArrayTest_251, DefSizeZero_251) {
    ArrayCfg arrayCfg{
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false
    };
    
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, arrayCfg, nullptr, 0);
    
    EXPECT_EQ(arr.defSize(), 0u);
}

// Test: decoded() returns false by default
TEST_F(TiffBinaryArrayTest_251, DecodedDefaultFalse_251) {
    ArrayCfg arrayCfg{
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false
    };
    
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, arrayCfg, nullptr, 0);
    
    EXPECT_FALSE(arr.decoded());
}

// Test: setDecoded(true) changes decoded() to true
TEST_F(TiffBinaryArrayTest_251, SetDecodedTrue_251) {
    ArrayCfg arrayCfg{
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false
    };
    
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, arrayCfg, nullptr, 0);
    arr.setDecoded(true);
    
    EXPECT_TRUE(arr.decoded());
}

// Test: setDecoded(false) after setting true reverts decoded()
TEST_F(TiffBinaryArrayTest_251, SetDecodedFalseAfterTrue_251) {
    ArrayCfg arrayCfg{
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false
    };
    
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, arrayCfg, nullptr, 0);
    arr.setDecoded(true);
    EXPECT_TRUE(arr.decoded());
    arr.setDecoded(false);
    EXPECT_FALSE(arr.decoded());
}

// Test: updOrigDataBuf with nullptr and zero size
TEST_F(TiffBinaryArrayTest_251, UpdOrigDataBufNullptr_251) {
    ArrayCfg arrayCfg{
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false
    };
    
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, arrayCfg, nullptr, 0);
    arr.iniOrigDataBuf();
    
    // updOrigDataBuf with null data and 0 size — should not crash
    bool result = arr.updOrigDataBuf(nullptr, 0);
    // Result depends on implementation, but should not crash
    (void)result;
}

// Test: Constructor with ArraySet stores cfg as nullptr initially
TEST_F(TiffBinaryArrayTest_251, ConstructorWithArraySetCfgInitiallyNull_251) {
    // When using the ArraySet constructor, arrayCfg_ is not set directly
    // It should be nullptr until initialize() is called
    ArrayCfg arrayCfg{
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false
    };
    
    ArrayDef arrayDef[] = {
        {0, ttUnsignedByte, 1}
    };
    
    ArraySet arraySet[] = {
        {arrayCfg, arrayDef, 1}
    };
    
    auto cfgSelFct = [](uint16_t, const byte*, size_t, size_t) -> int { return 0; };
    
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, arraySet, 1, cfgSelFct);
    
    // Before initialization, cfg() and def() may be nullptr
    EXPECT_EQ(arr.cfg(), nullptr);
    EXPECT_EQ(arr.def(), nullptr);
}

// Test: initialize with IfdId group
TEST_F(TiffBinaryArrayTest_251, InitializeWithGroup_251) {
    ArrayCfg arrayCfg{
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false
    };
    
    ArrayDef arrayDef[] = {
        {0, ttUnsignedByte, 1}
    };
    
    ArraySet arraySet[] = {
        {arrayCfg, arrayDef, 1}
    };
    
    auto cfgSelFct = [](uint16_t, const byte*, size_t, size_t) -> int { return 0; };
    
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, arraySet, 1, cfgSelFct);
    
    // initialize should select configuration based on group
    bool result = arr.initialize(IfdId::ifd0Id);
    // After initialization, cfg and def should be set
    if (result) {
        EXPECT_NE(arr.cfg(), nullptr);
        EXPECT_NE(arr.def(), nullptr);
    }
}

// Test: Multiple setDecoded calls
TEST_F(TiffBinaryArrayTest_251, MultipleSetDecodedCalls_251) {
    ArrayCfg arrayCfg{
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false
    };
    
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, arrayCfg, nullptr, 0);
    
    arr.setDecoded(true);
    arr.setDecoded(true);
    EXPECT_TRUE(arr.decoded());
    
    arr.setDecoded(false);
    arr.setDecoded(false);
    EXPECT_FALSE(arr.decoded());
}

// Test: def() consistency - same pointer returned on multiple calls
TEST_F(TiffBinaryArrayTest_251, DefConsistentAcrossMultipleCalls_251) {
    ArrayCfg arrayCfg{
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false
    };
    
    ArrayDef arrayDef[] = {
        {0, ttUnsignedByte, 1}
    };
    
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, arrayCfg, arrayDef, 1);
    
    const ArrayDef* first = arr.def();
    const ArrayDef* second = arr.def();
    
    EXPECT_EQ(first, second);
    EXPECT_EQ(first, arrayDef);
}

// Test: cfg() consistency
TEST_F(TiffBinaryArrayTest_251, CfgConsistentAcrossMultipleCalls_251) {
    ArrayCfg arrayCfg{
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false
    };
    
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, arrayCfg, nullptr, 0);
    
    const ArrayCfg* first = arr.cfg();
    const ArrayCfg* second = arr.cfg();
    
    EXPECT_EQ(first, second);
    EXPECT_EQ(first, &arrayCfg);
}
