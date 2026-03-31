#include <gtest/gtest.h>
#include "tiffcomposite_int.hpp"

// We need to include necessary headers for the types used
#include "types.hpp"
#include "tags_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Minimal ArrayCfg and ArrayDef setup for testing
// These are needed to construct TiffBinaryArray objects

class TiffBinaryArrayTest_253 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that decoded() returns false by default after construction with ArrayCfg
TEST_F(TiffBinaryArrayTest_253, DecodedDefaultFalseWithArrayCfg_253) {
    // Create a minimal ArrayCfg
    ArrayCfg arrayCfg{
        IfdId::ifd0Id,    // group
        invalidByteOrder, // byteOrder
        ttUndefined,      // elTiffType
        notEncrypted,     // cryptFct
        false,            // hasFillers
        false             // hasSize
    };

    TiffBinaryArray ba(0x0001, IfdId::ifd0Id, arrayCfg, nullptr, 0);
    EXPECT_FALSE(ba.decoded());
}

// Test that decoded() returns false by default after construction with ArraySet
TEST_F(TiffBinaryArrayTest_253, DecodedDefaultFalseWithArraySet_253) {
    // Using nullptr for arraySet and a null cfgSelFct
    TiffBinaryArray ba(0x0001, IfdId::ifd0Id, nullptr, 0, nullptr);
    EXPECT_FALSE(ba.decoded());
}

// Test setDecoded(true) makes decoded() return true
TEST_F(TiffBinaryArrayTest_253, SetDecodedTrue_253) {
    ArrayCfg arrayCfg{
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false
    };

    TiffBinaryArray ba(0x0001, IfdId::ifd0Id, arrayCfg, nullptr, 0);
    ba.setDecoded(true);
    EXPECT_TRUE(ba.decoded());
}

// Test setDecoded(false) makes decoded() return false
TEST_F(TiffBinaryArrayTest_253, SetDecodedFalse_253) {
    ArrayCfg arrayCfg{
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false
    };

    TiffBinaryArray ba(0x0001, IfdId::ifd0Id, arrayCfg, nullptr, 0);
    ba.setDecoded(true);
    EXPECT_TRUE(ba.decoded());
    ba.setDecoded(false);
    EXPECT_FALSE(ba.decoded());
}

// Test cfg() returns the ArrayCfg pointer passed in constructor
TEST_F(TiffBinaryArrayTest_253, CfgReturnsCorrectPointer_253) {
    ArrayCfg arrayCfg{
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false
    };

    TiffBinaryArray ba(0x0001, IfdId::ifd0Id, arrayCfg, nullptr, 0);
    EXPECT_NE(nullptr, ba.cfg());
    EXPECT_EQ(&arrayCfg, ba.cfg());
}

// Test def() returns the ArrayDef pointer passed in constructor
TEST_F(TiffBinaryArrayTest_253, DefReturnsCorrectPointer_253) {
    ArrayCfg arrayCfg{
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false
    };
    ArrayDef arrayDef = {0, ttUnsignedByte, 1};

    TiffBinaryArray ba(0x0001, IfdId::ifd0Id, arrayCfg, &arrayDef, 1);
    EXPECT_EQ(&arrayDef, ba.def());
}

// Test def() returns nullptr when constructed with nullptr
TEST_F(TiffBinaryArrayTest_253, DefReturnsNullptrWhenNone_253) {
    ArrayCfg arrayCfg{
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false
    };

    TiffBinaryArray ba(0x0001, IfdId::ifd0Id, arrayCfg, nullptr, 0);
    EXPECT_EQ(nullptr, ba.def());
}

// Test defSize() returns the size passed in constructor
TEST_F(TiffBinaryArrayTest_253, DefSizeReturnsCorrectValue_253) {
    ArrayCfg arrayCfg{
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false
    };
    ArrayDef arrayDefs[] = {
        {0, ttUnsignedByte, 1},
        {1, ttUnsignedByte, 1},
        {2, ttUnsignedByte, 1}
    };

    TiffBinaryArray ba(0x0001, IfdId::ifd0Id, arrayCfg, arrayDefs, 3);
    EXPECT_EQ(3u, ba.defSize());
}

// Test defSize() returns 0 when constructed with 0
TEST_F(TiffBinaryArrayTest_253, DefSizeReturnsZero_253) {
    ArrayCfg arrayCfg{
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false
    };

    TiffBinaryArray ba(0x0001, IfdId::ifd0Id, arrayCfg, nullptr, 0);
    EXPECT_EQ(0u, ba.defSize());
}

// Test toggle decoded state multiple times
TEST_F(TiffBinaryArrayTest_253, SetDecodedToggleMultipleTimes_253) {
    ArrayCfg arrayCfg{
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false
    };

    TiffBinaryArray ba(0x0001, IfdId::ifd0Id, arrayCfg, nullptr, 0);
    
    for (int i = 0; i < 10; ++i) {
        ba.setDecoded(true);
        EXPECT_TRUE(ba.decoded());
        ba.setDecoded(false);
        EXPECT_FALSE(ba.decoded());
    }
}

// Test initialize with IfdId group
TEST_F(TiffBinaryArrayTest_253, InitializeWithGroup_253) {
    ArrayCfg arrayCfg{
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false
    };

    TiffBinaryArray ba(0x0001, IfdId::ifd0Id, arrayCfg, nullptr, 0);
    // initialize should return a bool; test that it doesn't crash
    bool result = ba.initialize(IfdId::ifd0Id);
    // We can't assert the exact value without knowing internals, but we verify it runs
    (void)result;
}

// Test initialize with TiffComponent pointer (nullptr)
TEST_F(TiffBinaryArrayTest_253, InitializeWithNullRoot_253) {
    ArrayCfg arrayCfg{
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false
    };

    TiffBinaryArray ba(0x0001, IfdId::ifd0Id, arrayCfg, nullptr, 0);
    bool result = ba.initialize(static_cast<TiffComponent*>(nullptr));
    (void)result;
}

// Test updOrigDataBuf with nullptr and zero size
TEST_F(TiffBinaryArrayTest_253, UpdOrigDataBufNullptr_253) {
    ArrayCfg arrayCfg{
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false
    };

    TiffBinaryArray ba(0x0001, IfdId::ifd0Id, arrayCfg, nullptr, 0);
    ba.iniOrigDataBuf();
    bool result = ba.updOrigDataBuf(nullptr, 0);
    (void)result;
}

// Test construction with ArraySet constructor
TEST_F(TiffBinaryArrayTest_253, ConstructWithArraySet_253) {
    TiffBinaryArray ba(0x0002, IfdId::ifd0Id, nullptr, 0, nullptr);
    EXPECT_FALSE(ba.decoded());
    EXPECT_EQ(0u, ba.defSize());
}

// Test cfg() for ArraySet-constructed object returns nullptr (no arrayCfg set)
TEST_F(TiffBinaryArrayTest_253, CfgNullForArraySetConstruction_253) {
    TiffBinaryArray ba(0x0002, IfdId::ifd0Id, nullptr, 0, nullptr);
    EXPECT_EQ(nullptr, ba.cfg());
}
