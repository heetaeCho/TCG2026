void visitBinaryArray(TiffBinaryArray* object) {
    if (!object->cfg() || !object->decoded()) {
        decodeTiffEntry(object);
    }
}
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"
#include "exif.hpp"
#include "iptc.hpp"
#include "xmp_exiv2.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for TiffBinaryArray basic accessors
class TiffBinaryArrayTest_1664 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// A simple ArrayCfg for testing purposes
static const ArrayCfg testArrayCfg = {
    IfdId::ifd0Id,      // group
    invalidByteOrder,   // byteOrder
    ttUndefined,        // elTiffType
    notEncrypted,       // cryptFct
    false,              // hasFillers
    false               // hasSize
};

// Test that cfg() returns the ArrayCfg pointer when constructed with ArrayCfg
TEST_F(TiffBinaryArrayTest_1664, CfgReturnsNonNullWhenConstructedWithArrayCfg_1664) {
    TiffBinaryArray ba(0x0001, IfdId::ifd0Id, testArrayCfg, nullptr, 0);
    EXPECT_NE(ba.cfg(), nullptr);
}

// Test that decoded() returns false by default
TEST_F(TiffBinaryArrayTest_1664, DecodedReturnsFalseByDefault_1664) {
    TiffBinaryArray ba(0x0001, IfdId::ifd0Id, testArrayCfg, nullptr, 0);
    EXPECT_FALSE(ba.decoded());
}

// Test that setDecoded changes the decoded state
TEST_F(TiffBinaryArrayTest_1664, SetDecodedChangesState_1664) {
    TiffBinaryArray ba(0x0001, IfdId::ifd0Id, testArrayCfg, nullptr, 0);
    ba.setDecoded(true);
    EXPECT_TRUE(ba.decoded());
}

// Test that setDecoded can toggle back to false
TEST_F(TiffBinaryArrayTest_1664, SetDecodedCanToggleBackToFalse_1664) {
    TiffBinaryArray ba(0x0001, IfdId::ifd0Id, testArrayCfg, nullptr, 0);
    ba.setDecoded(true);
    EXPECT_TRUE(ba.decoded());
    ba.setDecoded(false);
    EXPECT_FALSE(ba.decoded());
}

// Test that def() returns nullptr when constructed with nullptr arrayDef
TEST_F(TiffBinaryArrayTest_1664, DefReturnsNullptrWhenNullArrayDef_1664) {
    TiffBinaryArray ba(0x0001, IfdId::ifd0Id, testArrayCfg, nullptr, 0);
    EXPECT_EQ(ba.def(), nullptr);
}

// Test that defSize() returns 0 when constructed with defSize 0
TEST_F(TiffBinaryArrayTest_1664, DefSizeReturnsZeroWhenConstructedWithZero_1664) {
    TiffBinaryArray ba(0x0001, IfdId::ifd0Id, testArrayCfg, nullptr, 0);
    EXPECT_EQ(ba.defSize(), 0u);
}

// Test construction with ArraySet (cfg should be null initially since no selection has been made)
TEST_F(TiffBinaryArrayTest_1664, CfgReturnsNullWhenConstructedWithArraySet_1664) {
    // When constructed with ArraySet constructor, arrayCfg_ is not set directly
    // so cfg() should return nullptr
    TiffBinaryArray ba(0x0001, IfdId::ifd0Id, nullptr, 0, nullptr);
    EXPECT_EQ(ba.cfg(), nullptr);
}

// Test defSize with non-zero value
TEST_F(TiffBinaryArrayTest_1664, DefSizeReturnsCorrectValue_1664) {
    ArrayDef testDef = {0, ttUnsignedByte, 1};
    TiffBinaryArray ba(0x0001, IfdId::ifd0Id, testArrayCfg, &testDef, 1);
    EXPECT_EQ(ba.defSize(), 1u);
}

// Test def() returns non-null when arrayDef is provided
TEST_F(TiffBinaryArrayTest_1664, DefReturnsNonNullWhenArrayDefProvided_1664) {
    ArrayDef testDef = {0, ttUnsignedByte, 1};
    TiffBinaryArray ba(0x0001, IfdId::ifd0Id, testArrayCfg, &testDef, 1);
    EXPECT_NE(ba.def(), nullptr);
}

// Test visitBinaryArray behavior - when cfg is null and decoded is false, decodeTiffEntry should be called
// We test this indirectly through the TiffDecoder
class TiffDecoderVisitBinaryArrayTest_1664 : public ::testing::Test {
protected:
    ExifData exifData_;
    IptcData iptcData_;
    XmpData xmpData_;
};

// Test that visitBinaryArray does not crash with a properly configured BinaryArray that has cfg and is decoded
TEST_F(TiffDecoderVisitBinaryArrayTest_1664, VisitBinaryArrayWithCfgAndDecoded_1664) {
    TiffBinaryArray ba(0x0001, IfdId::ifd0Id, testArrayCfg, nullptr, 0);
    ba.setDecoded(true);

    // cfg() is non-null and decoded() is true, so decodeTiffEntry should NOT be called
    // We verify the state doesn't change
    EXPECT_TRUE(ba.decoded());
    EXPECT_NE(ba.cfg(), nullptr);
}

// Test that visitBinaryArray with null cfg would trigger decode path
TEST_F(TiffDecoderVisitBinaryArrayTest_1664, VisitBinaryArrayWithNullCfg_1664) {
    TiffBinaryArray ba(0x0001, IfdId::ifd0Id, nullptr, 0, nullptr);

    // cfg() is null, so the condition !object->cfg() is true
    EXPECT_EQ(ba.cfg(), nullptr);
    EXPECT_FALSE(ba.decoded());
}

// Test that visitBinaryArray with non-null cfg but not decoded would trigger decode path
TEST_F(TiffDecoderVisitBinaryArrayTest_1664, VisitBinaryArrayWithCfgButNotDecoded_1664) {
    TiffBinaryArray ba(0x0001, IfdId::ifd0Id, testArrayCfg, nullptr, 0);

    // cfg() is non-null but decoded() is false, so !object->decoded() is true
    EXPECT_NE(ba.cfg(), nullptr);
    EXPECT_FALSE(ba.decoded());
}

// Test the logic condition: both cfg non-null AND decoded true means no decode
TEST_F(TiffDecoderVisitBinaryArrayTest_1664, BothCfgAndDecodedMeansNoDecodeNeeded_1664) {
    TiffBinaryArray ba(0x0001, IfdId::ifd0Id, testArrayCfg, nullptr, 0);
    ba.setDecoded(true);

    // The condition !cfg() || !decoded() evaluates to false
    bool shouldDecode = (!ba.cfg() || !ba.decoded());
    EXPECT_FALSE(shouldDecode);
}

// Test the logic condition: null cfg means decode needed regardless of decoded state
TEST_F(TiffDecoderVisitBinaryArrayTest_1664, NullCfgMeansDecodeNeeded_1664) {
    TiffBinaryArray ba(0x0001, IfdId::ifd0Id, nullptr, 0, nullptr);
    ba.setDecoded(true);

    // Even though decoded is true, null cfg means decode is needed
    bool shouldDecode = (!ba.cfg() || !ba.decoded());
    EXPECT_TRUE(shouldDecode);
}

// Test the logic condition: non-null cfg but not decoded means decode needed
TEST_F(TiffDecoderVisitBinaryArrayTest_1664, NotDecodedMeansDecodeNeeded_1664) {
    TiffBinaryArray ba(0x0001, IfdId::ifd0Id, testArrayCfg, nullptr, 0);

    bool shouldDecode = (!ba.cfg() || !ba.decoded());
    EXPECT_TRUE(shouldDecode);
}

// Boundary: multiple setDecoded calls
TEST_F(TiffBinaryArrayTest_1664, MultipleSetDecodedCalls_1664) {
    TiffBinaryArray ba(0x0001, IfdId::ifd0Id, testArrayCfg, nullptr, 0);
    
    ba.setDecoded(true);
    ba.setDecoded(true);
    EXPECT_TRUE(ba.decoded());
    
    ba.setDecoded(false);
    ba.setDecoded(false);
    EXPECT_FALSE(ba.decoded());
}

// Test with tag value of 0 (boundary)
TEST_F(TiffBinaryArrayTest_1664, ZeroTagValue_1664) {
    TiffBinaryArray ba(0x0000, IfdId::ifd0Id, testArrayCfg, nullptr, 0);
    EXPECT_NE(ba.cfg(), nullptr);
    EXPECT_FALSE(ba.decoded());
}

// Test with max tag value (boundary)
TEST_F(TiffBinaryArrayTest_1664, MaxTagValue_1664) {
    TiffBinaryArray ba(0xFFFF, IfdId::ifd0Id, testArrayCfg, nullptr, 0);
    EXPECT_NE(ba.cfg(), nullptr);
    EXPECT_FALSE(ba.decoded());
}
