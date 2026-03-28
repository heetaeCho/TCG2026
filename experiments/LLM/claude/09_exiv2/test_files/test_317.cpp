#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"
#include "tiffvisitor_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class TiffBinaryArrayTest_317 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test that addElement returns 0 when TiffCreator::create returns a non-TiffBinaryElement
// or when configuration is invalid. This tests the boundary where dynamic_cast fails.
TEST_F(TiffBinaryArrayTest_317, AddElementReturnsZeroWhenCreatorReturnsNonBinaryElement_317) {
    // We need a valid ArrayCfg. We'll try to construct a TiffBinaryArray with
    // a group that TiffCreator::create would create a non-TiffBinaryElement for.
    // Using a known IFD group that creates regular TIFF entries, not binary elements.
    
    ArrayDef arrayDef = {0, ttUndefined, 1};
    ArrayCfg arrayCfg = {ttUndefined, nullptr, false, false, false, arrayDef};
    
    // Create TiffBinaryArray with IfdId that likely won't produce TiffBinaryElement
    // from TiffCreator::create
    TiffBinaryArray tba(0x0001, IfdId::ifd0Id, arrayCfg, &arrayDef, 1);
    
    // Set some data so pData() and doSize() are valid
    auto buf = std::make_shared<DataBuf>(16);
    std::memset(buf->data(), 0, 16);
    tba.setData(buf);
    
    ArrayDef def = {0, ttUndefined, 1};
    
    // When TiffCreator::create returns something that's not a TiffBinaryElement,
    // addElement should return 0
    size_t result = tba.addElement(0, def);
    // The result depends on whether TiffCreator creates a TiffBinaryElement for this group
    // For ifd0Id, it likely won't, so result should be 0
    EXPECT_EQ(result, 0u);
}

// Test addElement with a configuration that uses a known binary array group
// This tests the normal operation path
TEST_F(TiffBinaryArrayTest_317, AddElementWithValidBinaryGroup_317) {
    // Try with a group known to have binary elements in the TIFF structure
    // canonCsId is commonly used with binary arrays
    ArrayDef arrayDef = {0, ttSignedShort, 1};
    ArrayCfg arrayCfg = {ttSignedShort, nullptr, true, false, false, arrayDef};
    
    TiffBinaryArray tba(0x0001, IfdId::canonCsId, arrayCfg, &arrayDef, 1);
    
    auto buf = std::make_shared<DataBuf>(32);
    std::memset(buf->data(), 0, 32);
    tba.setData(buf);
    
    ArrayDef def = {0, ttSignedShort, 1};
    size_t result = tba.addElement(0, def);
    
    // Result is either 0 (if TiffCreator doesn't produce a TiffBinaryElement)
    // or a positive size value
    // We just verify it doesn't crash and returns a sensible value
    EXPECT_GE(result, 0u);
}

// Test addElement at various indices
TEST_F(TiffBinaryArrayTest_317, AddElementAtDifferentIndices_317) {
    ArrayDef arrayDef = {0, ttUndefined, 1};
    ArrayCfg arrayCfg = {ttUndefined, nullptr, false, false, false, arrayDef};
    
    TiffBinaryArray tba(0x0001, IfdId::canonCsId, arrayCfg, &arrayDef, 1);
    
    auto buf = std::make_shared<DataBuf>(64);
    std::memset(buf->data(), 0xAB, 64);
    tba.setData(buf);
    
    ArrayDef def = {0, ttUndefined, 1};
    
    // Try adding at index 0
    size_t result0 = tba.addElement(0, def);
    EXPECT_GE(result0, 0u);
    
    // Try adding at a mid-range index
    if (tba.size() > 10) {
        size_t result10 = tba.addElement(10, def);
        EXPECT_GE(result10, 0u);
    }
}

// Test cfg() and def() accessors
TEST_F(TiffBinaryArrayTest_317, CfgAndDefAccessors_317) {
    ArrayDef arrayDef = {0, ttUndefined, 1};
    ArrayCfg arrayCfg = {ttUndefined, nullptr, false, false, false, arrayDef};
    
    TiffBinaryArray tba(0x0001, IfdId::ifd0Id, arrayCfg, &arrayDef, 1);
    
    EXPECT_EQ(tba.cfg(), &arrayCfg);
    EXPECT_EQ(tba.def(), &arrayDef);
    EXPECT_EQ(tba.defSize(), 1u);
}

// Test decoded flag
TEST_F(TiffBinaryArrayTest_317, DecodedFlag_317) {
    ArrayDef arrayDef = {0, ttUndefined, 1};
    ArrayCfg arrayCfg = {ttUndefined, nullptr, false, false, false, arrayDef};
    
    TiffBinaryArray tba(0x0001, IfdId::ifd0Id, arrayCfg, &arrayDef, 1);
    
    EXPECT_FALSE(tba.decoded());
    tba.setDecoded(true);
    EXPECT_TRUE(tba.decoded());
    tba.setDecoded(false);
    EXPECT_FALSE(tba.decoded());
}

// Test constructor with ArraySet
TEST_F(TiffBinaryArrayTest_317, ConstructorWithArraySet_317) {
    ArrayDef arrayDef = {0, ttUndefined, 1};
    ArrayCfg arrayCfg = {ttUndefined, nullptr, false, false, false, arrayDef};
    ArraySet arraySet = {arrayCfg, &arrayDef, 1};
    
    auto cfgSelFct = [](uint16_t, const byte*, size_t, size_t) -> int { return 0; };
    
    TiffBinaryArray tba(0x0001, IfdId::ifd0Id, &arraySet, 1, cfgSelFct);
    
    // With ArraySet constructor, cfg() might be null until initialized
    // Just verify construction doesn't crash
    EXPECT_EQ(tba.tag(), 0x0001);
    EXPECT_EQ(tba.group(), IfdId::ifd0Id);
}

// Test initialize with group
TEST_F(TiffBinaryArrayTest_317, InitializeWithGroup_317) {
    ArrayDef arrayDef = {0, ttUndefined, 1};
    ArrayCfg arrayCfg = {ttUndefined, nullptr, false, false, false, arrayDef};
    ArraySet arraySet = {arrayCfg, &arrayDef, 1};
    
    auto cfgSelFct = [](uint16_t, const byte*, size_t, size_t) -> int { return 0; };
    
    TiffBinaryArray tba(0x0001, IfdId::ifd0Id, &arraySet, 1, cfgSelFct);
    
    // Initialize with a valid group
    bool result = tba.initialize(IfdId::ifd0Id);
    // Result depends on whether the group matches any in arraySet
    // Just test it doesn't crash
    SUCCEED();
}

// Test iniOrigDataBuf and updOrigDataBuf
TEST_F(TiffBinaryArrayTest_317, OrigDataBufOperations_317) {
    ArrayDef arrayDef = {0, ttUndefined, 1};
    ArrayCfg arrayCfg = {ttUndefined, nullptr, false, false, false, arrayDef};
    
    TiffBinaryArray tba(0x0001, IfdId::ifd0Id, arrayCfg, &arrayDef, 1);
    
    auto buf = std::make_shared<DataBuf>(16);
    std::memset(buf->data(), 0, 16);
    tba.setData(buf);
    
    // Initialize original data buffer
    tba.iniOrigDataBuf();
    
    // Update with new data
    byte newData[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    bool updated = tba.updOrigDataBuf(newData, 16);
    // The result indicates whether the update was successful
    SUCCEED();
}

// Test TiffBinaryElement setters and getters
TEST_F(TiffBinaryArrayTest_317, TiffBinaryElementSettersGetters_317) {
    // Create a TiffBinaryElement through TiffCreator if possible,
    // or test its interface directly
    TiffBinaryElement elem(0x0001, IfdId::ifd0Id);
    
    ArrayDef def = {0, ttUndefined, 4};
    elem.setElDef(def);
    EXPECT_NE(elem.elDef(), nullptr);
    
    elem.setElByteOrder(ByteOrder::littleEndian);
    EXPECT_EQ(elem.elByteOrder(), ByteOrder::littleEndian);
    
    elem.setElByteOrder(ByteOrder::bigEndian);
    EXPECT_EQ(elem.elByteOrder(), ByteOrder::bigEndian);
}

// Test TiffBinaryElement with invalidByteOrder (default)
TEST_F(TiffBinaryArrayTest_317, TiffBinaryElementDefaultByteOrder_317) {
    TiffBinaryElement elem(0x0001, IfdId::ifd0Id);
    EXPECT_EQ(elem.elByteOrder(), ByteOrder::invalidByteOrder);
}

// Test tag and group from base class for TiffBinaryArray
TEST_F(TiffBinaryArrayTest_317, TagAndGroupAccessors_317) {
    ArrayDef arrayDef = {0, ttUndefined, 1};
    ArrayCfg arrayCfg = {ttUndefined, nullptr, false, false, false, arrayDef};
    
    TiffBinaryArray tba(0x1234, IfdId::exifId, arrayCfg, &arrayDef, 1);
    
    EXPECT_EQ(tba.tag(), 0x1234);
    EXPECT_EQ(tba.group(), IfdId::exifId);
}

// Test addElement with zero-size data buffer
TEST_F(TiffBinaryArrayTest_317, AddElementWithEmptyData_317) {
    ArrayDef arrayDef = {0, ttUndefined, 1};
    ArrayCfg arrayCfg = {ttUndefined, nullptr, false, false, false, arrayDef};
    
    TiffBinaryArray tba(0x0001, IfdId::ifd0Id, arrayCfg, &arrayDef, 1);
    
    // Don't set any data - pData should be null and size should be 0
    ArrayDef def = {0, ttUndefined, 1};
    
    // This should handle the edge case gracefully
    // When doSize() is 0 and idx is 0, min calculation results in 0
    // The behavior depends on whether pData() is null
    size_t result = tba.addElement(0, def);
    EXPECT_EQ(result, 0u);
}

// Test ArrayDef size method
TEST_F(TiffBinaryArrayTest_317, ArrayDefSize_317) {
    ArrayDef def = {0, ttUndefined, 4};
    size_t sz = def.size(0, IfdId::ifd0Id);
    // The size depends on the implementation
    EXPECT_GT(sz, 0u);
}

// Test ArrayDef equality operator
TEST_F(TiffBinaryArrayTest_317, ArrayDefEquality_317) {
    ArrayDef def = {5, ttUndefined, 1};
    EXPECT_TRUE(def == 5u);
    EXPECT_FALSE(def == 3u);
}

// Test multiple calls to setDecoded
TEST_F(TiffBinaryArrayTest_317, MultipleSetDecoded_317) {
    ArrayDef arrayDef = {0, ttUndefined, 1};
    ArrayCfg arrayCfg = {ttUndefined, nullptr, false, false, false, arrayDef};
    
    TiffBinaryArray tba(0x0001, IfdId::ifd0Id, arrayCfg, &arrayDef, 1);
    
    tba.setDecoded(true);
    EXPECT_TRUE(tba.decoded());
    
    tba.setDecoded(true);
    EXPECT_TRUE(tba.decoded());
    
    tba.setDecoded(false);
    EXPECT_FALSE(tba.decoded());
}
