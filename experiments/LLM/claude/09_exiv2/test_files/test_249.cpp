#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class TiffBinaryArrayTest_249 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test setDecoded and decoded getter - set to true
TEST_F(TiffBinaryArrayTest_249, SetDecodedTrue_249) {
    // We need a minimal ArrayCfg to construct TiffBinaryArray
    ArrayCfg cfg = {
        IfdId::ifd0Id,     // group
        invalidByteOrder,  // byteOrder
        ttUndefined,       // elTiffType
        notEncrypted,      // cryptFct
        false,              // hasSize
        false,              // hasFillers
        false               // concat
    };

    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);
    arr.setDecoded(true);
    EXPECT_TRUE(arr.decoded());
}

// Test setDecoded and decoded getter - set to false
TEST_F(TiffBinaryArrayTest_249, SetDecodedFalse_249) {
    ArrayCfg cfg = {
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false,
        false
    };

    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);
    arr.setDecoded(false);
    EXPECT_FALSE(arr.decoded());
}

// Test default decoded state is false
TEST_F(TiffBinaryArrayTest_249, DefaultDecodedIsFalse_249) {
    ArrayCfg cfg = {
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false,
        false
    };

    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);
    EXPECT_FALSE(arr.decoded());
}

// Test toggle decoded state
TEST_F(TiffBinaryArrayTest_249, ToggleDecoded_249) {
    ArrayCfg cfg = {
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false,
        false
    };

    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);
    arr.setDecoded(true);
    EXPECT_TRUE(arr.decoded());
    arr.setDecoded(false);
    EXPECT_FALSE(arr.decoded());
}

// Test cfg() returns the ArrayCfg pointer passed in constructor
TEST_F(TiffBinaryArrayTest_249, CfgReturnsCorrectPointer_249) {
    ArrayCfg cfg = {
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false,
        false
    };

    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);
    EXPECT_NE(arr.cfg(), nullptr);
}

// Test def() returns the ArrayDef pointer passed in constructor (nullptr case)
TEST_F(TiffBinaryArrayTest_249, DefReturnsNullptrWhenNoneProvided_249) {
    ArrayCfg cfg = {
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false,
        false
    };

    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);
    EXPECT_EQ(arr.def(), nullptr);
}

// Test defSize() returns correct size when no defs provided
TEST_F(TiffBinaryArrayTest_249, DefSizeZeroWhenNoDefs_249) {
    ArrayCfg cfg = {
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false,
        false
    };

    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);
    EXPECT_EQ(arr.defSize(), 0u);
}

// Test def() and defSize() with actual ArrayDef
TEST_F(TiffBinaryArrayTest_249, DefAndDefSizeWithArrayDef_249) {
    ArrayCfg cfg = {
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false,
        false
    };

    ArrayDef defs[] = {
        {0, ttUnsignedByte, 1},
        {1, ttUnsignedByte, 1},
        {2, ttUnsignedByte, 1}
    };

    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, cfg, defs, 3);
    EXPECT_NE(arr.def(), nullptr);
    EXPECT_EQ(arr.defSize(), 3u);
}

// Test constructor with ArraySet (second constructor variant)
TEST_F(TiffBinaryArrayTest_249, ConstructWithArraySet_249) {
    // Using a simple CfgSelFct that returns 0
    auto selFct = [](uint16_t, const byte*, size_t, size_t) -> int {
        return 0;
    };

    ArrayCfg cfg = {
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false,
        false
    };

    ArraySet sets[] = {
        {cfg, nullptr, 0}
    };

    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, sets, 1, selFct);
    // The object should be constructed; decoded should be false by default
    EXPECT_FALSE(arr.decoded());
}

// Test initialize with nullptr pRoot
TEST_F(TiffBinaryArrayTest_249, InitializeWithNullptrRoot_249) {
    ArrayCfg cfg = {
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false,
        false
    };

    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);
    // Initialize with nullptr - should handle gracefully
    bool result = arr.initialize(static_cast<TiffComponent*>(nullptr));
    // We just check it doesn't crash; the result depends on implementation
    (void)result;
}

// Test updOrigDataBuf with nullptr data
TEST_F(TiffBinaryArrayTest_249, UpdOrigDataBufWithNullptr_249) {
    ArrayCfg cfg = {
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false,
        false
    };

    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);
    arr.iniOrigDataBuf();
    bool result = arr.updOrigDataBuf(nullptr, 0);
    // Just verify it doesn't crash
    (void)result;
}

// Test updOrigDataBuf with valid data
TEST_F(TiffBinaryArrayTest_249, UpdOrigDataBufWithValidData_249) {
    ArrayCfg cfg = {
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false,
        false
    };

    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);
    arr.iniOrigDataBuf();

    byte data[] = {0x01, 0x02, 0x03, 0x04};
    bool result = arr.updOrigDataBuf(data, sizeof(data));
    (void)result;
}

// Test setDecoded multiple times with same value
TEST_F(TiffBinaryArrayTest_249, SetDecodedMultipleTimes_249) {
    ArrayCfg cfg = {
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false,
        false
    };

    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);
    arr.setDecoded(true);
    arr.setDecoded(true);
    EXPECT_TRUE(arr.decoded());
    arr.setDecoded(false);
    arr.setDecoded(false);
    EXPECT_FALSE(arr.decoded());
}
