#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"
#include "exiv2/exif.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for TiffBinaryArray
class TiffBinaryArrayTest_350 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test that decoded flag defaults to false and can be set
TEST_F(TiffBinaryArrayTest_350, SetDecodedDefault_350) {
    // Create a minimal ArrayCfg for construction
    ArrayCfg cfg{IfdId::ifd0Id, ttUndefined, ttUndefined, notEncrypted, false, false, {0, ttUndefined, 1}};
    ArrayDef def{0, ttUndefined, 1};

    TiffBinaryArray array(0x0001, IfdId::ifd0Id, cfg, &def, 1);
    EXPECT_FALSE(array.decoded());
}

TEST_F(TiffBinaryArrayTest_350, SetDecodedTrue_350) {
    ArrayCfg cfg{IfdId::ifd0Id, ttUndefined, ttUndefined, notEncrypted, false, false, {0, ttUndefined, 1}};
    ArrayDef def{0, ttUndefined, 1};

    TiffBinaryArray array(0x0001, IfdId::ifd0Id, cfg, &def, 1);
    array.setDecoded(true);
    EXPECT_TRUE(array.decoded());
}

TEST_F(TiffBinaryArrayTest_350, SetDecodedFalseAfterTrue_350) {
    ArrayCfg cfg{IfdId::ifd0Id, ttUndefined, ttUndefined, notEncrypted, false, false, {0, ttUndefined, 1}};
    ArrayDef def{0, ttUndefined, 1};

    TiffBinaryArray array(0x0001, IfdId::ifd0Id, cfg, &def, 1);
    array.setDecoded(true);
    array.setDecoded(false);
    EXPECT_FALSE(array.decoded());
}

// Test cfg() returns the configuration passed in constructor
TEST_F(TiffBinaryArrayTest_350, CfgReturnsArrayCfg_350) {
    ArrayCfg cfg{IfdId::ifd0Id, ttUndefined, ttUndefined, notEncrypted, false, false, {0, ttUndefined, 1}};
    ArrayDef def{0, ttUndefined, 1};

    TiffBinaryArray array(0x0001, IfdId::ifd0Id, cfg, &def, 1);
    EXPECT_NE(nullptr, array.cfg());
}

// Test def() returns the definition passed in constructor
TEST_F(TiffBinaryArrayTest_350, DefReturnsArrayDef_350) {
    ArrayCfg cfg{IfdId::ifd0Id, ttUndefined, ttUndefined, notEncrypted, false, false, {0, ttUndefined, 1}};
    ArrayDef def{0, ttUndefined, 1};

    TiffBinaryArray array(0x0001, IfdId::ifd0Id, cfg, &def, 1);
    EXPECT_NE(nullptr, array.def());
}

// Test defSize() returns the size passed in constructor
TEST_F(TiffBinaryArrayTest_350, DefSizeReturnsCorrectSize_350) {
    ArrayCfg cfg{IfdId::ifd0Id, ttUndefined, ttUndefined, notEncrypted, false, false, {0, ttUndefined, 1}};
    ArrayDef def{0, ttUndefined, 1};

    TiffBinaryArray array(0x0001, IfdId::ifd0Id, cfg, &def, 3);
    EXPECT_EQ(3u, array.defSize());
}

// Test construction with ArraySet
TEST_F(TiffBinaryArrayTest_350, ConstructWithArraySet_350) {
    ArrayCfg cfg{IfdId::ifd0Id, ttUndefined, ttUndefined, notEncrypted, false, false, {0, ttUndefined, 1}};
    ArrayDef def{0, ttUndefined, 1};
    ArraySet set{cfg, &def, 1};

    TiffBinaryArray array(0x0001, IfdId::ifd0Id, &set, 1, nullptr);
    // With ArraySet constructor, cfg() may be null initially
    EXPECT_EQ(nullptr, array.cfg());
}

// Test updOrigDataBuf with null data
TEST_F(TiffBinaryArrayTest_350, UpdOrigDataBufNullData_350) {
    ArrayCfg cfg{IfdId::ifd0Id, ttUndefined, ttUndefined, notEncrypted, false, false, {0, ttUndefined, 1}};
    ArrayDef def{0, ttUndefined, 1};

    TiffBinaryArray array(0x0001, IfdId::ifd0Id, cfg, &def, 1);
    bool result = array.updOrigDataBuf(nullptr, 0);
    // Should handle null gracefully
    EXPECT_FALSE(result);
}

// Test defSize zero
TEST_F(TiffBinaryArrayTest_350, DefSizeZero_350) {
    ArrayCfg cfg{IfdId::ifd0Id, ttUndefined, ttUndefined, notEncrypted, false, false, {0, ttUndefined, 1}};

    TiffBinaryArray array(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);
    EXPECT_EQ(0u, array.defSize());
    EXPECT_EQ(nullptr, array.def());
}
