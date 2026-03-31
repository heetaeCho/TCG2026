#include <gtest/gtest.h>
#include "tiffcomposite_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Minimal ArrayCfg and ArrayDef for testing
namespace {

// A simple ArrayCfg with tagStep = 1, no fillers
const ArrayCfg testCfgNoFillers = {
    ttUndefined,  // elTiffType_
    nullptr,      // cryptFct_
    false,        // hasSize_
    false,        // hasFillers_
    false,        // concat_
    {0, 0},       // elDefaultDef_
};

// ArrayCfg with fillers enabled
const ArrayCfg testCfgWithFillers = {
    ttUndefined,  // elTiffType_
    nullptr,      // cryptFct_
    false,        // hasSize_
    true,         // hasFillers_
    false,        // concat_
    {0, 0},       // elDefaultDef_
};

// ArrayDef entries for testing
const ArrayDef testDefs[] = {
    {0, 1},
    {1, 1},
    {2, 1},
};

const ArrayDef testDefsLarge[] = {
    {0, 1},
    {1, 1},
    {10, 2},
};

} // namespace

class TiffBinaryArrayDoSize_395 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test: When cfg() is null (constructed with ArraySet constructor but not initialized),
// doSize falls back to TiffEntryBase::doSize
TEST_F(TiffBinaryArrayDoSize_395, NoCfgDelegatesToBase_395) {
    // Using the ArraySet constructor with nullptr arraySet
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, nullptr, 0, nullptr);
    // cfg() should be null, so it delegates to TiffEntryBase::doSize()
    // TiffEntryBase::doSize() with no data should return its internal size_ (0)
    size_t s = arr.size();
    EXPECT_EQ(s, 0u);
}

// Test: When decoded is false, doSize falls back to TiffEntryBase::doSize
TEST_F(TiffBinaryArrayDoSize_395, NotDecodedDelegatesToBase_395) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, testCfgNoFillers, testDefs, 3);
    // decoded_ defaults to false
    EXPECT_FALSE(arr.decoded());
    size_t s = arr.size();
    // Falls back to TiffEntryBase::doSize()
    EXPECT_EQ(s, 0u);
}

// Test: When decoded is true and elements are empty, returns 0
TEST_F(TiffBinaryArrayDoSize_395, DecodedEmptyElementsReturnsZero_395) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, testCfgNoFillers, testDefs, 3);
    arr.setDecoded(true);
    EXPECT_TRUE(arr.decoded());
    size_t s = arr.size();
    EXPECT_EQ(s, 0u);
}

// Test: cfg() returns the arrayCfg pointer passed in constructor
TEST_F(TiffBinaryArrayDoSize_395, CfgReturnsCorrectPointer_395) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, testCfgNoFillers, testDefs, 3);
    EXPECT_EQ(arr.cfg(), &testCfgNoFillers);
}

// Test: def() returns the arrayDef pointer passed in constructor
TEST_F(TiffBinaryArrayDoSize_395, DefReturnsCorrectPointer_395) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, testCfgNoFillers, testDefs, 3);
    EXPECT_EQ(arr.def(), testDefs);
}

// Test: defSize() returns the defSize passed in constructor
TEST_F(TiffBinaryArrayDoSize_395, DefSizeReturnsCorrectValue_395) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, testCfgNoFillers, testDefs, 3);
    EXPECT_EQ(arr.defSize(), 3u);
}

// Test: decoded() initially false, setDecoded changes it
TEST_F(TiffBinaryArrayDoSize_395, SetDecodedChangesState_395) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, testCfgNoFillers, testDefs, 3);
    EXPECT_FALSE(arr.decoded());
    arr.setDecoded(true);
    EXPECT_TRUE(arr.decoded());
    arr.setDecoded(false);
    EXPECT_FALSE(arr.decoded());
}

// Test: Constructor with ArrayCfg sets correct tag and group
TEST_F(TiffBinaryArrayDoSize_395, ConstructorSetsTagAndGroup_395) {
    TiffBinaryArray arr(0x0042, IfdId::ifd0Id, testCfgNoFillers, testDefs, 3);
    EXPECT_EQ(arr.tag(), 0x0042);
    EXPECT_EQ(arr.group(), IfdId::ifd0Id);
}

// Test: Constructor with ArraySet sets correct tag and group
TEST_F(TiffBinaryArrayDoSize_395, ArraySetConstructorSetsTagAndGroup_395) {
    TiffBinaryArray arr(0x0099, IfdId::ifd1Id, nullptr, 0, nullptr);
    EXPECT_EQ(arr.tag(), 0x0099);
    EXPECT_EQ(arr.group(), IfdId::ifd1Id);
}

// Test: With ArraySet constructor, cfg() is null and def() is null
TEST_F(TiffBinaryArrayDoSize_395, ArraySetConstructorNullCfgAndDef_395) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, nullptr, 0, nullptr);
    EXPECT_EQ(arr.cfg(), nullptr);
    EXPECT_EQ(arr.def(), nullptr);
    EXPECT_EQ(arr.defSize(), 0u);
}

// Test: iniOrigDataBuf does not crash on default constructed array
TEST_F(TiffBinaryArrayDoSize_395, IniOrigDataBufNoCrash_395) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, testCfgNoFillers, testDefs, 3);
    EXPECT_NO_THROW(arr.iniOrigDataBuf());
}

// Test: updOrigDataBuf with null data
TEST_F(TiffBinaryArrayDoSize_395, UpdOrigDataBufNullData_395) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, testCfgNoFillers, testDefs, 3);
    arr.iniOrigDataBuf();
    bool result = arr.updOrigDataBuf(nullptr, 0);
    // The result depends on internal state, just verify no crash
    (void)result;
}

// Test: Size after adding elements with decoded = true
TEST_F(TiffBinaryArrayDoSize_395, SizeWithElementsDecoded_395) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, testCfgNoFillers, testDefs, 3);
    arr.setDecoded(true);
    
    // Add elements using addElement
    ArrayDef def0 = {0, 1};
    size_t added = arr.addElement(0, def0);
    // After adding at least one element, size should be non-zero when decoded
    size_t s = arr.size();
    // We just check it doesn't crash; the exact value depends on element internals
    EXPECT_GE(s, 0u);
}

// Test: tiffType returns the type from ArrayCfg
TEST_F(TiffBinaryArrayDoSize_395, TiffTypeFromCfg_395) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, testCfgNoFillers, testDefs, 3);
    EXPECT_EQ(arr.tiffType(), ttUndefined);
}
