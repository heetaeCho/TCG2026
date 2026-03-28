#include <gtest/gtest.h>
#include "tiffcomposite_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper function for CfgSelFct - a simple selector that returns 0
static int testCfgSelFct(TiffComponent* /*unused*/, IfdId /*unused*/, IfdId /*unused*/, int /*unused*/) {
    return 0;
}

class TiffBinaryArrayTest_313 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test: Constructor with ArrayCfg sets cfg, def, and defSize correctly
TEST_F(TiffBinaryArrayTest_313, ConstructorWithArrayCfg_SetsMembers_313) {
    ArrayDef arrayDef = {0, ttUndefined, 1};
    ArrayCfg arrayCfg = {IfdId::ifdIdNotSet, ttUndefined, nullptr, false, false, false, {0, ttUndefined, 0}};
    
    TiffBinaryArray tba(0x0001, IfdId::ifdIdNotSet, arrayCfg, &arrayDef, 1);
    
    EXPECT_NE(tba.cfg(), nullptr);
    EXPECT_EQ(tba.def(), &arrayDef);
    EXPECT_EQ(tba.defSize(), 1u);
}

// Test: Constructor with ArraySet leaves arrayCfg_ as nullptr initially
TEST_F(TiffBinaryArrayTest_313, ConstructorWithArraySet_CfgIsNull_313) {
    ArrayCfg cfg1 = {IfdId::canonCsId, ttUndefined, nullptr, false, false, false, {0, ttUndefined, 0}};
    ArrayDef def1 = {0, ttUndefined, 1};
    ArraySet arraySet[] = {{cfg1, &def1, 1}};
    
    TiffBinaryArray tba(0x0001, IfdId::ifdIdNotSet, arraySet, 1, testCfgSelFct);
    
    // Before initialization, cfg should be nullptr since constructor with ArraySet doesn't set arrayCfg_
    EXPECT_EQ(tba.cfg(), nullptr);
    EXPECT_EQ(tba.def(), nullptr);
    EXPECT_EQ(tba.defSize(), 0u);
}

// Test: initialize(group) returns true when group matches an entry in arraySet
TEST_F(TiffBinaryArrayTest_313, InitializeWithMatchingGroup_ReturnsTrue_313) {
    ArrayCfg cfg1 = {IfdId::canonCsId, ttUndefined, nullptr, false, false, false, {0, ttUndefined, 0}};
    ArrayDef def1 = {0, ttUndefined, 1};
    ArraySet arraySet[] = {{cfg1, &def1, 1}};
    
    TiffBinaryArray tba(0x0001, IfdId::ifdIdNotSet, arraySet, 1, testCfgSelFct);
    
    bool result = tba.initialize(IfdId::canonCsId);
    EXPECT_TRUE(result);
    EXPECT_NE(tba.cfg(), nullptr);
    EXPECT_EQ(tba.def(), &def1);
    EXPECT_EQ(tba.defSize(), 1u);
}

// Test: initialize(group) returns false when group does not match any entry
TEST_F(TiffBinaryArrayTest_313, InitializeWithNonMatchingGroup_ReturnsFalse_313) {
    ArrayCfg cfg1 = {IfdId::canonCsId, ttUndefined, nullptr, false, false, false, {0, ttUndefined, 0}};
    ArrayDef def1 = {0, ttUndefined, 1};
    ArraySet arraySet[] = {{cfg1, &def1, 1}};
    
    TiffBinaryArray tba(0x0001, IfdId::ifdIdNotSet, arraySet, 1, testCfgSelFct);
    
    bool result = tba.initialize(IfdId::canonSiId);
    EXPECT_FALSE(result);
    EXPECT_EQ(tba.cfg(), nullptr);
}

// Test: initialize(group) returns true immediately if arrayCfg_ is already set
TEST_F(TiffBinaryArrayTest_313, InitializeWhenAlreadyInitialized_ReturnsTrueImmediately_313) {
    ArrayDef arrayDef = {0, ttUndefined, 1};
    ArrayCfg arrayCfg = {IfdId::ifdIdNotSet, ttUndefined, nullptr, false, false, false, {0, ttUndefined, 0}};
    
    // This constructor sets arrayCfg_ directly
    TiffBinaryArray tba(0x0001, IfdId::ifdIdNotSet, arrayCfg, &arrayDef, 1);
    
    // Should return true immediately since arrayCfg_ is already set
    bool result = tba.initialize(IfdId::canonCsId);
    EXPECT_TRUE(result);
}

// Test: initialize with empty arraySet (setSize_ == 0) returns false
TEST_F(TiffBinaryArrayTest_313, InitializeWithEmptyArraySet_ReturnsFalse_313) {
    TiffBinaryArray tba(0x0001, IfdId::ifdIdNotSet, nullptr, 0, testCfgSelFct);
    
    bool result = tba.initialize(IfdId::canonCsId);
    EXPECT_FALSE(result);
}

// Test: initialize with multiple entries finds the correct one
TEST_F(TiffBinaryArrayTest_313, InitializeWithMultipleEntries_FindsCorrectOne_313) {
    ArrayCfg cfg1 = {IfdId::canonCsId, ttUndefined, nullptr, false, false, false, {0, ttUndefined, 0}};
    ArrayCfg cfg2 = {IfdId::canonSiId, ttUndefined, nullptr, false, false, false, {0, ttUndefined, 0}};
    ArrayDef def1 = {0, ttUndefined, 1};
    ArrayDef def2 = {0, ttUndefined, 2};
    ArraySet arraySet[] = {
        {cfg1, &def1, 1},
        {cfg2, &def2, 5}
    };
    
    TiffBinaryArray tba(0x0001, IfdId::ifdIdNotSet, arraySet, 2, testCfgSelFct);
    
    bool result = tba.initialize(IfdId::canonSiId);
    EXPECT_TRUE(result);
    EXPECT_EQ(tba.def(), &def2);
    EXPECT_EQ(tba.defSize(), 5u);
}

// Test: initialize finds the first matching entry
TEST_F(TiffBinaryArrayTest_313, InitializeFindsFirstMatchingEntry_313) {
    ArrayCfg cfg1 = {IfdId::canonCsId, ttUndefined, nullptr, false, false, false, {0, ttUndefined, 0}};
    ArrayDef def1 = {0, ttUndefined, 1};
    ArrayDef def2 = {0, ttUndefined, 2};
    ArraySet arraySet[] = {
        {cfg1, &def1, 3},
        {cfg1, &def2, 7}  // Same group, different def
    };
    
    TiffBinaryArray tba(0x0001, IfdId::ifdIdNotSet, arraySet, 2, testCfgSelFct);
    
    bool result = tba.initialize(IfdId::canonCsId);
    EXPECT_TRUE(result);
    // Should find the first match
    EXPECT_EQ(tba.def(), &def1);
    EXPECT_EQ(tba.defSize(), 3u);
}

// Test: setDecoded and decoded work correctly
TEST_F(TiffBinaryArrayTest_313, SetDecodedAndDecoded_313) {
    ArrayDef arrayDef = {0, ttUndefined, 1};
    ArrayCfg arrayCfg = {IfdId::ifdIdNotSet, ttUndefined, nullptr, false, false, false, {0, ttUndefined, 0}};
    
    TiffBinaryArray tba(0x0001, IfdId::ifdIdNotSet, arrayCfg, &arrayDef, 1);
    
    EXPECT_FALSE(tba.decoded());
    
    tba.setDecoded(true);
    EXPECT_TRUE(tba.decoded());
    
    tba.setDecoded(false);
    EXPECT_FALSE(tba.decoded());
}

// Test: cfg() returns correct pointer after ArrayCfg constructor
TEST_F(TiffBinaryArrayTest_313, CfgReturnsCorrectPointer_313) {
    ArrayDef arrayDef = {0, ttUndefined, 1};
    ArrayCfg arrayCfg = {IfdId::ifdIdNotSet, ttUndefined, nullptr, false, false, false, {0, ttUndefined, 0}};
    
    TiffBinaryArray tba(0x0001, IfdId::ifdIdNotSet, arrayCfg, &arrayDef, 1);
    
    EXPECT_EQ(tba.cfg(), &arrayCfg);
}

// Test: Second call to initialize after successful initialization returns true without changing state
TEST_F(TiffBinaryArrayTest_313, InitializeCalledTwice_ReturnsTrue_313) {
    ArrayCfg cfg1 = {IfdId::canonCsId, ttUndefined, nullptr, false, false, false, {0, ttUndefined, 0}};
    ArrayCfg cfg2 = {IfdId::canonSiId, ttUndefined, nullptr, false, false, false, {0, ttUndefined, 0}};
    ArrayDef def1 = {0, ttUndefined, 1};
    ArrayDef def2 = {0, ttUndefined, 2};
    ArraySet arraySet[] = {
        {cfg1, &def1, 3},
        {cfg2, &def2, 7}
    };
    
    TiffBinaryArray tba(0x0001, IfdId::ifdIdNotSet, arraySet, 2, testCfgSelFct);
    
    // First initialization with canonCsId
    EXPECT_TRUE(tba.initialize(IfdId::canonCsId));
    const ArrayCfg* firstCfg = tba.cfg();
    const ArrayDef* firstDef = tba.def();
    size_t firstDefSize = tba.defSize();
    
    // Second call should return true immediately (arrayCfg_ already set)
    EXPECT_TRUE(tba.initialize(IfdId::canonSiId));
    
    // State should not have changed
    EXPECT_EQ(tba.cfg(), firstCfg);
    EXPECT_EQ(tba.def(), firstDef);
    EXPECT_EQ(tba.defSize(), firstDefSize);
}
