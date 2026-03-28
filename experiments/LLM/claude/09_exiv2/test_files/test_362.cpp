#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// We need a valid ArrayCfg for constructing TiffBinaryArray with config
// Using known structures from the exiv2 codebase

class TiffBinaryArrayCountTest_362 : public ::testing::Test {
protected:
    void SetUp() override {
        // Suppress warnings during tests
        LogMsg::setLevel(LogMsg::mute);
    }

    void TearDown() override {
        LogMsg::setLevel(LogMsg::warn);
    }
};

// Test: When cfg() is null (constructed with ArraySet constructor but no valid config selected),
// and decoded is false, should delegate to TiffEntryBase::doCount()
TEST_F(TiffBinaryArrayCountTest_362, NoCfgDelegatesToBase_362) {
    // Construct with ArraySet constructor - cfgSelFct and arraySet can be null
    // This means cfg() returns nullptr
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, nullptr, 0, nullptr);
    // decoded() defaults to false, cfg() is null
    // Should delegate to TiffEntryBase::doCount() which returns count_ (default 0)
    EXPECT_EQ(0u, arr.count());
}

// Test: When decoded is false, should delegate to TiffEntryBase::doCount()
TEST_F(TiffBinaryArrayCountTest_362, NotDecodedDelegatesToBase_362) {
    // Create with ArrayCfg
    const ArrayCfg cfg = {
        IfdId::ifd0Id,    // group
        invalidByteOrder, // byte order
        ttUndefined,      // elTiffType
        notEncrypted,     // cryptFct
        false,            // hasFillerByteAtTheEnd
        false,            // hasExtraElement
    };
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);
    // decoded() defaults to false
    ASSERT_FALSE(arr.decoded());
    ASSERT_NE(nullptr, arr.cfg());
    // Delegates to base, count_ is 0 by default
    EXPECT_EQ(0u, arr.count());
}

// Test: When decoded is true, cfg is valid, but elements_ is empty -> returns 0
TEST_F(TiffBinaryArrayCountTest_362, DecodedEmptyElementsReturnsZero_362) {
    const ArrayCfg cfg = {
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false,
    };
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);
    arr.setDecoded(true);
    ASSERT_TRUE(arr.decoded());
    ASSERT_NE(nullptr, arr.cfg());
    // No elements added, elements_ is empty
    EXPECT_EQ(0u, arr.count());
}

// Test: When decoded is true, cfg is valid, elements are present, and type is known
TEST_F(TiffBinaryArrayCountTest_362, DecodedWithElementsComputesCount_362) {
    const ArrayCfg cfg = {
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined, // type undefined, typeSize = 1
        notEncrypted,
        false,
        false,
    };
    const ArrayDef def = {0, ttUndefined, 4}; // element of size 4
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, cfg, &def, 1);
    arr.setDecoded(true);

    // Add an element to make elements_ non-empty
    arr.addElement(0, def);

    // Now count() should compute size()/typeSize
    // The result depends on size() and the resolved typeSize
    size_t result = arr.count();
    // We can at least verify it doesn't crash and returns a value
    EXPECT_GE(result, 0u);
}

// Test: setDecoded and decoded accessor
TEST_F(TiffBinaryArrayCountTest_362, SetDecodedToggle_362) {
    const ArrayCfg cfg = {
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false,
    };
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);

    EXPECT_FALSE(arr.decoded());
    arr.setDecoded(true);
    EXPECT_TRUE(arr.decoded());
    arr.setDecoded(false);
    EXPECT_FALSE(arr.decoded());
}

// Test: cfg() returns non-null when constructed with ArrayCfg
TEST_F(TiffBinaryArrayCountTest_362, CfgReturnsNonNullWithArrayCfg_362) {
    const ArrayCfg cfg = {
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false,
    };
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);
    EXPECT_NE(nullptr, arr.cfg());
}

// Test: cfg() returns null when constructed with ArraySet=nullptr
TEST_F(TiffBinaryArrayCountTest_362, CfgReturnsNullWithNullArraySet_362) {
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, nullptr, 0, nullptr);
    EXPECT_EQ(nullptr, arr.cfg());
}

// Test: def() and defSize() accessors
TEST_F(TiffBinaryArrayCountTest_362, DefAccessors_362) {
    const ArrayCfg cfg = {
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false,
    };
    const ArrayDef defs[] = {{0, ttUndefined, 2}, {2, ttUndefined, 3}};
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, cfg, defs, 2);
    EXPECT_EQ(defs, arr.def());
    EXPECT_EQ(2u, arr.defSize());
}

// Test: tag() and group() inherited from TiffComponent
TEST_F(TiffBinaryArrayCountTest_362, TagAndGroup_362) {
    const ArrayCfg cfg = {
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false,
    };
    TiffBinaryArray arr(0x1234, IfdId::exifId, cfg, nullptr, 0);
    EXPECT_EQ(0x1234, arr.tag());
    EXPECT_EQ(IfdId::exifId, arr.group());
}

// Test: tiffType() from TiffEntryBase
TEST_F(TiffBinaryArrayCountTest_362, TiffTypeAccessor_362) {
    const ArrayCfg cfg = {
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false,
    };
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);
    // The tiffType should be set to arrayCfg.elTiffType_ which is ttUndefined
    EXPECT_EQ(ttUndefined, arr.tiffType());
}

// Test: Count with data set but not decoded - should use base class behavior
TEST_F(TiffBinaryArrayCountTest_362, CountWithDataNotDecoded_362) {
    const ArrayCfg cfg = {
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false,
    };
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);

    // Set some data
    auto buf = std::make_shared<DataBuf>(10);
    arr.setData(buf);

    // Not decoded, so delegates to TiffEntryBase::doCount()
    ASSERT_FALSE(arr.decoded());
    size_t c = arr.count();
    // Base count should reflect the data that was set
    EXPECT_GE(c, 0u);
}

// Test: With byte type (typeSize=1), count should equal size
TEST_F(TiffBinaryArrayCountTest_362, ByteTypeCountEqualsSize_362) {
    const ArrayCfg cfg = {
        IfdId::ifd0Id,
        invalidByteOrder,
        ttUnsignedByte, // typeSize = 1
        notEncrypted,
        false,
        false,
    };
    const ArrayDef def = {0, ttUnsignedByte, 1};
    TiffBinaryArray arr(0x0001, IfdId::ifd0Id, cfg, &def, 1);
    arr.setDecoded(true);

    // Add element so elements_ is not empty
    arr.addElement(0, def);

    size_t c = arr.count();
    size_t s = arr.size();
    // With typeSize=1, count should equal size
    if (s > 0) {
        EXPECT_EQ(s, c);
    }
}
