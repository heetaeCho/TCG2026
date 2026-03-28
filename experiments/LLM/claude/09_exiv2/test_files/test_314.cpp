#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "types.hpp"
#include "tags_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// ============================================================================
// Test fixture for TiffBinaryArray::initialize(TiffComponent* pRoot)
// ============================================================================

class TiffBinaryArrayInitializeTest_314 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Helper: a CfgSelFct that always returns -1 (failure)
static int cfgSelFctAlwaysFail(uint16_t /*tag*/, const byte* /*pData*/, size_t /*size*/, TiffComponent* /*pRoot*/) {
    return -1;
}

// Helper: a CfgSelFct that always returns 0 (selects first element)
static int cfgSelFctAlwaysZero(uint16_t /*tag*/, const byte* /*pData*/, size_t /*size*/, TiffComponent* /*pRoot*/) {
    return 0;
}

// Helper: a CfgSelFct that always returns 1 (selects second element)
static int cfgSelFctAlwaysOne(uint16_t /*tag*/, const byte* /*pData*/, size_t /*size*/, TiffComponent* /*pRoot*/) {
    return 1;
}

// Test: When cfgSelFct_ is nullptr (simple array constructor), initialize returns true
TEST_F(TiffBinaryArrayInitializeTest_314, NoCfgSelFctReturnsTrue_314) {
    // Use the simple constructor that doesn't set cfgSelFct_
    ArrayCfg cfg = {IfdId::ifd0Id, ttUndefined, ttUndefined, notEncrypted, false, false};
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);

    bool result = arr.initialize(nullptr);
    EXPECT_TRUE(result);
}

// Test: When cfgSelFct returns -1, initialize returns false
TEST_F(TiffBinaryArrayInitializeTest_314, CfgSelFctReturnsNegativeOne_314) {
    ArrayCfg cfg0 = {IfdId::ifd0Id, ttUndefined, ttUndefined, notEncrypted, false, false};
    ArraySet arraySet[] = {
        {cfg0, nullptr, 0}
    };

    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, arraySet, 1, cfgSelFctAlwaysFail);

    bool result = arr.initialize(nullptr);
    EXPECT_FALSE(result);
}

// Test: When cfgSelFct returns 0 (valid index), initialize returns true and sets cfg
TEST_F(TiffBinaryArrayInitializeTest_314, CfgSelFctReturnsValidIndex_314) {
    ArrayCfg cfg0 = {IfdId::ifd0Id, ttUndefined, ttUndefined, notEncrypted, false, false};
    ArraySet arraySet[] = {
        {cfg0, nullptr, 0}
    };

    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, arraySet, 1, cfgSelFctAlwaysZero);

    bool result = arr.initialize(nullptr);
    EXPECT_TRUE(result);
    // After successful initialization, cfg() should point to the selected config
    EXPECT_NE(arr.cfg(), nullptr);
    EXPECT_EQ(arr.def(), nullptr);
    EXPECT_EQ(arr.defSize(), 0u);
}

// Test: When cfgSelFct returns index 1, the second array set is selected
TEST_F(TiffBinaryArrayInitializeTest_314, CfgSelFctReturnsSecondIndex_314) {
    ArrayCfg cfg0 = {IfdId::ifd0Id, ttUndefined, ttUndefined, notEncrypted, false, false};
    ArrayCfg cfg1 = {IfdId::exifId, ttUndefined, ttUndefined, notEncrypted, false, false};
    ArrayDef defs[] = {{0, ttUndefined, 1}};
    ArraySet arraySet[] = {
        {cfg0, nullptr, 0},
        {cfg1, defs, 1}
    };

    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, arraySet, 2, cfgSelFctAlwaysOne);

    bool result = arr.initialize(nullptr);
    EXPECT_TRUE(result);
    EXPECT_NE(arr.cfg(), nullptr);
    EXPECT_EQ(arr.def(), defs);
    EXPECT_EQ(arr.defSize(), 1u);
}

// ============================================================================
// Test fixture for TiffBinaryArray general functionality
// ============================================================================

class TiffBinaryArrayGeneralTest_314 : public ::testing::Test {
protected:
};

// Test: Simple constructor sets cfg, def, and defSize correctly
TEST_F(TiffBinaryArrayGeneralTest_314, SimpleConstructorSetsFields_314) {
    ArrayCfg cfg = {IfdId::ifd0Id, ttUndefined, ttUndefined, notEncrypted, false, false};
    ArrayDef defs[] = {{0, ttUndefined, 2}, {2, ttUndefined, 3}};

    TiffBinaryArray arr(0x0010, IfdId::ifd0Id, cfg, defs, 2);

    EXPECT_EQ(arr.cfg(), &cfg);
    EXPECT_EQ(arr.def(), defs);
    EXPECT_EQ(arr.defSize(), 2u);
    EXPECT_EQ(arr.tag(), 0x0010);
    EXPECT_FALSE(arr.decoded());
}

// Test: Complex constructor initially has null cfg (until initialize is called)
TEST_F(TiffBinaryArrayGeneralTest_314, ComplexConstructorInitialState_314) {
    ArrayCfg cfg0 = {IfdId::ifd0Id, ttUndefined, ttUndefined, notEncrypted, false, false};
    ArraySet arraySet[] = {
        {cfg0, nullptr, 0}
    };

    TiffBinaryArray arr(0x0010, IfdId::ifd0Id, arraySet, 1, cfgSelFctAlwaysFail);

    // Before initialize, cfg should be null for complex arrays
    EXPECT_EQ(arr.cfg(), nullptr);
    EXPECT_EQ(arr.def(), nullptr);
    EXPECT_EQ(arr.defSize(), 0u);
}

// Test: decoded() / setDecoded() work correctly
TEST_F(TiffBinaryArrayGeneralTest_314, SetDecodedFlag_314) {
    ArrayCfg cfg = {IfdId::ifd0Id, ttUndefined, ttUndefined, notEncrypted, false, false};
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);

    EXPECT_FALSE(arr.decoded());
    arr.setDecoded(true);
    EXPECT_TRUE(arr.decoded());
    arr.setDecoded(false);
    EXPECT_FALSE(arr.decoded());
}

// Test: tag() returns the correct tag
TEST_F(TiffBinaryArrayGeneralTest_314, TagReturnsCorrectValue_314) {
    ArrayCfg cfg = {IfdId::ifd0Id, ttUndefined, ttUndefined, notEncrypted, false, false};
    TiffBinaryArray arr(0x1234, IfdId::ifd0Id, cfg, nullptr, 0);

    EXPECT_EQ(arr.tag(), 0x1234);
}

// Test: group() returns the correct group
TEST_F(TiffBinaryArrayGeneralTest_314, GroupReturnsCorrectValue_314) {
    ArrayCfg cfg = {IfdId::exifId, ttUndefined, ttUndefined, notEncrypted, false, false};
    TiffBinaryArray arr(0x0001, IfdId::exifId, cfg, nullptr, 0);

    EXPECT_EQ(arr.group(), IfdId::exifId);
}

// Test: pData() returns nullptr when no data is set
TEST_F(TiffBinaryArrayGeneralTest_314, PDataNullWhenNoDataSet_314) {
    ArrayCfg cfg = {IfdId::ifd0Id, ttUndefined, ttUndefined, notEncrypted, false, false};
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);

    EXPECT_EQ(arr.pData(), nullptr);
}

// Test: After setData, pData returns the data
TEST_F(TiffBinaryArrayGeneralTest_314, SetDataUpdatesPData_314) {
    ArrayCfg cfg = {IfdId::ifd0Id, ttUndefined, ttUndefined, notEncrypted, false, false};
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);

    auto buf = std::make_shared<DataBuf>(10);
    std::memset(buf->data(), 0xAB, 10);
    arr.setData(buf);

    EXPECT_NE(arr.pData(), nullptr);
}

// Test: initialize with pRoot passed to cfgSelFct
TEST_F(TiffBinaryArrayGeneralTest_314, InitializePassesPRootToCfgSelFct_314) {
    // We'll use a static variable to capture what pRoot was passed
    static TiffComponent* capturedRoot = nullptr;
    auto cfgSelCapture = [](uint16_t, const byte*, size_t, TiffComponent* pRoot) -> int {
        capturedRoot = pRoot;
        return 0;
    };

    ArrayCfg cfg0 = {IfdId::ifd0Id, ttUndefined, ttUndefined, notEncrypted, false, false};
    ArraySet arraySet[] = {
        {cfg0, nullptr, 0}
    };

    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, arraySet, 1, cfgSelCapture);

    // Create a dummy TiffComponent to use as root
    ArrayCfg rootCfg = {IfdId::ifd0Id, ttUndefined, ttUndefined, notEncrypted, false, false};
    TiffBinaryArray root(0x0002, IfdId::ifd0Id, rootCfg, nullptr, 0);

    capturedRoot = nullptr;
    bool result = arr.initialize(&root);
    EXPECT_TRUE(result);
    EXPECT_EQ(capturedRoot, &root);
}

// Test: initialize with nullptr as pRoot
TEST_F(TiffBinaryArrayGeneralTest_314, InitializeWithNullptrRoot_314) {
    ArrayCfg cfg0 = {IfdId::ifd0Id, ttUndefined, ttUndefined, notEncrypted, false, false};
    ArraySet arraySet[] = {
        {cfg0, nullptr, 0}
    };

    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, arraySet, 1, cfgSelFctAlwaysZero);

    bool result = arr.initialize(nullptr);
    EXPECT_TRUE(result);
}

// Test: count() returns 0 when no elements
TEST_F(TiffBinaryArrayGeneralTest_314, CountReturnsZeroWhenEmpty_314) {
    ArrayCfg cfg = {IfdId::ifd0Id, ttUndefined, ttUndefined, notEncrypted, false, false};
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);

    EXPECT_EQ(arr.count(), 0u);
}

// Test: size() returns 0 when no data
TEST_F(TiffBinaryArrayGeneralTest_314, SizeReturnsZeroWhenNoData_314) {
    ArrayCfg cfg = {IfdId::ifd0Id, ttUndefined, ttUndefined, notEncrypted, false, false};
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);

    EXPECT_EQ(arr.size(), 0u);
}
