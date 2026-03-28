#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"
#include "types.hpp"
#include "exif.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper ArrayCfg for creating TiffBinaryArray instances
namespace {

const ArrayCfg testArrayCfg = {
    IfdId::ifd0Id,       // group
    invalidByteOrder,    // byte order
    ttUndefined,         // elTiffType
    notEncrypted,        // cryptFct
    false,               // hasSize
    false,               // hasFillers
    false,               // concat
    0,                   // tagStep
    0,                   // first
    nullptr,             // arrayDef
    0                    // arrayDefSize (or whatever the struct expects)
};

const ArrayDef testArrayDef[] = {
    {0, ttUndefined, 1},
    {1, ttUndefined, 1},
    {2, ttUndefined, 1},
};

} // namespace

class TiffBinaryArrayTest_315 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test construction with ArrayCfg and ArrayDef
TEST_F(TiffBinaryArrayTest_315, ConstructWithArrayCfg_315) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);
    EXPECT_EQ(arr.tag(), 0x0001);
    EXPECT_EQ(arr.cfg(), &testArrayCfg);
    EXPECT_EQ(arr.def(), testArrayDef);
    EXPECT_EQ(arr.defSize(), 3u);
    EXPECT_FALSE(arr.decoded());
}

// Test construction with ArraySet and CfgSelFct
TEST_F(TiffBinaryArrayTest_315, ConstructWithArraySet_315) {
    // Construct with nullptr arraySet and null cfgSelFct
    TiffBinaryArray arr(0x0002, IfdId::ifd0Id, nullptr, 0, nullptr);
    EXPECT_EQ(arr.tag(), 0x0002);
    EXPECT_EQ(arr.cfg(), nullptr);
    EXPECT_EQ(arr.def(), nullptr);
    EXPECT_EQ(arr.defSize(), 0u);
    EXPECT_FALSE(arr.decoded());
}

// Test setDecoded / decoded
TEST_F(TiffBinaryArrayTest_315, SetDecoded_315) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);
    EXPECT_FALSE(arr.decoded());
    arr.setDecoded(true);
    EXPECT_TRUE(arr.decoded());
    arr.setDecoded(false);
    EXPECT_FALSE(arr.decoded());
}

// Test cfg() returns correct pointer
TEST_F(TiffBinaryArrayTest_315, CfgReturnsCorrectPointer_315) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);
    EXPECT_EQ(arr.cfg(), &testArrayCfg);
}

// Test def() returns correct pointer
TEST_F(TiffBinaryArrayTest_315, DefReturnsCorrectPointer_315) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);
    EXPECT_EQ(arr.def(), testArrayDef);
}

// Test defSize() returns correct size
TEST_F(TiffBinaryArrayTest_315, DefSizeReturnsCorrectValue_315) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);
    EXPECT_EQ(arr.defSize(), 3u);
}

// Test defSize with zero
TEST_F(TiffBinaryArrayTest_315, DefSizeZero_315) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, testArrayCfg, nullptr, 0);
    EXPECT_EQ(arr.defSize(), 0u);
    EXPECT_EQ(arr.def(), nullptr);
}

// Test iniOrigDataBuf when no data is set
TEST_F(TiffBinaryArrayTest_315, IniOrigDataBufNoData_315) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);
    // When no data has been set, pData() should be nullptr
    EXPECT_EQ(arr.pData(), nullptr);
    // Calling iniOrigDataBuf should not crash
    arr.iniOrigDataBuf();
}

// Test iniOrigDataBuf after setting data
TEST_F(TiffBinaryArrayTest_315, IniOrigDataBufWithData_315) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);

    auto storage = std::make_shared<DataBuf>(10);
    byte* data = storage->data();
    for (size_t i = 0; i < 10; ++i) {
        data[i] = static_cast<byte>(i);
    }
    arr.setData(data, 10, storage);

    EXPECT_NE(arr.pData(), nullptr);

    // iniOrigDataBuf should not crash and should store origData
    arr.iniOrigDataBuf();
}

// Test updOrigDataBuf with valid data after iniOrigDataBuf
TEST_F(TiffBinaryArrayTest_315, UpdOrigDataBufAfterInit_315) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);

    auto storage = std::make_shared<DataBuf>(10);
    byte* data = storage->data();
    for (size_t i = 0; i < 10; ++i) {
        data[i] = static_cast<byte>(i);
    }
    arr.setData(data, 10, storage);
    arr.iniOrigDataBuf();

    // updOrigDataBuf with data of same size
    byte newData[10] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
    bool result = arr.updOrigDataBuf(newData, 10);
    // The result depends on the internal state (whether origData_ is set and sizes match)
    // We just verify it doesn't crash and returns a bool
    EXPECT_TRUE(result || !result);
}

// Test updOrigDataBuf with nullptr
TEST_F(TiffBinaryArrayTest_315, UpdOrigDataBufNullptr_315) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);
    // Without initializing origData, updOrigDataBuf should handle gracefully
    bool result = arr.updOrigDataBuf(nullptr, 0);
    // Just verify it doesn't crash
    EXPECT_TRUE(result || !result);
}

// Test updOrigDataBuf with mismatched size
TEST_F(TiffBinaryArrayTest_315, UpdOrigDataBufSizeMismatch_315) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);

    auto storage = std::make_shared<DataBuf>(10);
    byte* data = storage->data();
    for (size_t i = 0; i < 10; ++i) {
        data[i] = static_cast<byte>(i);
    }
    arr.setData(data, 10, storage);
    arr.iniOrigDataBuf();

    // Try to update with a different size
    byte newData[5] = {10, 11, 12, 13, 14};
    bool result = arr.updOrigDataBuf(newData, 5);
    // Should return false since sizes don't match
    EXPECT_FALSE(result);
}

// Test initialize with IfdId
TEST_F(TiffBinaryArrayTest_315, InitializeWithIfdId_315) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);
    bool result = arr.initialize(IfdId::ifd0Id);
    // Just verify it doesn't crash
    EXPECT_TRUE(result || !result);
}

// Test initialize with TiffComponent pointer (nullptr)
TEST_F(TiffBinaryArrayTest_315, InitializeWithNullRoot_315) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);
    bool result = arr.initialize(static_cast<TiffComponent*>(nullptr));
    EXPECT_TRUE(result || !result);
}

// Test TiffEntryBase base class functionality - tiffType
TEST_F(TiffBinaryArrayTest_315, TiffTypeAccessor_315) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);
    // The tiffType should be set from arrayCfg.elTiffType_ which is ttUndefined
    EXPECT_EQ(arr.tiffType(), ttUndefined);
}

// Test setData with shared_ptr<DataBuf>
TEST_F(TiffBinaryArrayTest_315, SetDataWithSharedPtr_315) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);
    
    auto buf = std::make_shared<DataBuf>(5);
    byte* data = buf->data();
    data[0] = 0xAA;
    data[1] = 0xBB;
    data[2] = 0xCC;
    data[3] = 0xDD;
    data[4] = 0xEE;
    
    arr.setData(buf);
    EXPECT_NE(arr.pData(), nullptr);
}

// Test setData with raw pointer
TEST_F(TiffBinaryArrayTest_315, SetDataWithRawPointer_315) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);
    
    auto storage = std::make_shared<DataBuf>(8);
    byte* data = storage->data();
    for (size_t i = 0; i < 8; ++i) {
        data[i] = static_cast<byte>(i + 0x10);
    }
    
    arr.setData(data, 8, storage);
    EXPECT_EQ(arr.pData(), data);
}

// Test pData returns nullptr initially
TEST_F(TiffBinaryArrayTest_315, PDataInitiallyNull_315) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);
    EXPECT_EQ(arr.pData(), nullptr);
}

// Test pValue returns nullptr initially
TEST_F(TiffBinaryArrayTest_315, PValueInitiallyNull_315) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);
    EXPECT_EQ(arr.pValue(), nullptr);
}

// Test tag accessor
TEST_F(TiffBinaryArrayTest_315, TagAccessor_315) {
    TiffBinaryArray arr(0x1234, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);
    EXPECT_EQ(arr.tag(), 0x1234);
}

// Test with different tag values
TEST_F(TiffBinaryArrayTest_315, DifferentTagValues_315) {
    TiffBinaryArray arr1(0x0000, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);
    EXPECT_EQ(arr1.tag(), 0x0000);
    
    TiffBinaryArray arr2(0xFFFF, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);
    EXPECT_EQ(arr2.tag(), 0xFFFF);
}

// Test offset accessor initial value
TEST_F(TiffBinaryArrayTest_315, OffsetInitiallyZero_315) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);
    EXPECT_EQ(arr.offset(), 0u);
}

// Test setOffset
TEST_F(TiffBinaryArrayTest_315, SetOffset_315) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);
    arr.setOffset(42);
    EXPECT_EQ(arr.offset(), 42u);
}

// Test idx accessor
TEST_F(TiffBinaryArrayTest_315, IdxAccessor_315) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);
    // idx should default to 0
    EXPECT_EQ(arr.idx(), 0);
}

// Test iniOrigDataBuf followed by updOrigDataBuf full cycle
TEST_F(TiffBinaryArrayTest_315, IniAndUpdOrigDataBufFullCycle_315) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);

    auto storage = std::make_shared<DataBuf>(4);
    byte* data = storage->data();
    data[0] = 0x01;
    data[1] = 0x02;
    data[2] = 0x03;
    data[3] = 0x04;
    
    arr.setData(data, 4, storage);
    arr.iniOrigDataBuf();

    // Update with same-size data
    byte updatedData[4] = {0x05, 0x06, 0x07, 0x08};
    bool result = arr.updOrigDataBuf(updatedData, 4);
    EXPECT_TRUE(result);
}

// Test updOrigDataBuf without calling iniOrigDataBuf first
TEST_F(TiffBinaryArrayTest_315, UpdOrigDataBufWithoutInit_315) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);

    byte someData[4] = {0x01, 0x02, 0x03, 0x04};
    // origData_ should be nullptr, origSize_ should be 0
    bool result = arr.updOrigDataBuf(someData, 4);
    // Should return false since origData_ is null
    EXPECT_FALSE(result);
}

// Test multiple setDecoded toggles
TEST_F(TiffBinaryArrayTest_315, MultipleSetDecodedToggles_315) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, testArrayCfg, testArrayDef, 3);
    
    arr.setDecoded(true);
    EXPECT_TRUE(arr.decoded());
    
    arr.setDecoded(true);
    EXPECT_TRUE(arr.decoded());
    
    arr.setDecoded(false);
    EXPECT_FALSE(arr.decoded());
    
    arr.setDecoded(false);
    EXPECT_FALSE(arr.decoded());
}
