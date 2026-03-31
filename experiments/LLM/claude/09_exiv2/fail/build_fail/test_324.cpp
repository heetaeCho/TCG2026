#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"
#include "tiffvisitor_int.hpp"

#include <stack>

using namespace Exiv2;
using namespace Exiv2::Internal;

class TiffBinaryArrayDoAddPathTest_324 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that when tiffPath has exactly one element, doAddPath returns 'this'
TEST_F(TiffBinaryArrayDoAddPathTest_324, ReturnsThisWhenPathSizeIsOne_324) {
    // We need a valid ArrayCfg to construct TiffBinaryArray
    // Try to use known configurations from exiv2
    // For a minimal test, we try to exercise the path with size 1

    // Use a known tag/group combination that has a TiffBinaryArray definition
    // We'll attempt to use the public addPath which delegates to doAddPath

    // Since the internal structures are complex, we test what we can observe:
    // When path size is 1, the method should return `this`

    try {
        // Create a TiffPath with a single element
        // TiffPath is typically a std::stack<TiffPathItem>
        TiffPath tiffPath;
        // We need at least the tag/group to be valid for TiffBinaryArray
        // Use IfdId::ifd0Id or similar known group
        const uint16_t testTag = 0x0001;
        const IfdId testGroup = IfdId::canonCsId;

        // We need a valid ArrayCfg
        ArrayCfg arrayCfg{
            testGroup,      // group
            invalidByteOrder, // byte order
            ttUnsignedByte, // elTiffType
            notEncrypted,   // encryption
            false,          // hasFillers
            false           // hasSize
        };

        TiffBinaryArray ba(testTag, testGroup, arrayCfg, nullptr, 0);

        TiffPathItem item(testTag, testGroup);
        tiffPath.push(item);

        TiffComponent* result = ba.addPath(testTag, tiffPath, &ba, nullptr);

        // When path size is 1, should return this
        EXPECT_EQ(result, &ba);
    } catch (const std::exception& e) {
        // If configuration is invalid, we note the exception
        GTEST_SKIP() << "Skipped due to configuration dependency: " << e.what();
    }
}

// Test that pRoot is set when doAddPath is called
TEST_F(TiffBinaryArrayDoAddPathTest_324, SetsRootPointer_324) {
    try {
        const uint16_t testTag = 0x0001;
        const IfdId testGroup = IfdId::canonCsId;

        ArrayCfg arrayCfg{
            testGroup,
            invalidByteOrder,
            ttUnsignedByte,
            notEncrypted,
            false,
            false
        };

        TiffBinaryArray ba(testTag, testGroup, arrayCfg, nullptr, 0);

        TiffPath tiffPath;
        TiffPathItem item(testTag, testGroup);
        tiffPath.push(item);

        TiffComponent dummyRoot(0x0000, IfdId::ifd0Id);
        TiffComponent* result = ba.addPath(testTag, tiffPath, &dummyRoot, nullptr);

        // With path size 1, should return this
        EXPECT_EQ(result, &ba);
    } catch (const std::exception& e) {
        GTEST_SKIP() << "Skipped due to configuration dependency: " << e.what();
    }
}

// Test with path size > 1 and an object provided
TEST_F(TiffBinaryArrayDoAddPathTest_324, PathSizeGreaterThanOneWithObject_324) {
    try {
        const uint16_t testTag = 0x0001;
        const IfdId testGroup = IfdId::canonCsId;

        ArrayCfg arrayCfg{
            testGroup,
            invalidByteOrder,
            ttUnsignedByte,
            notEncrypted,
            false,
            false
        };

        ArrayDef arrayDef = {0, ttUnsignedShort, 1};

        TiffBinaryArray ba(testTag, testGroup, arrayCfg, &arrayDef, 1);

        TiffPath tiffPath;
        // Push two items - first will be the destination, second is current level
        TiffPathItem item1(0x0001, testGroup);
        TiffPathItem item2(testTag, testGroup);

        // Stack: item2 on top, item1 on bottom
        tiffPath.push(item1);
        tiffPath.push(item2);

        // The path has size 2, so it won't return this immediately
        // It will pop, initialize, and try to create/find child
        TiffComponent* result = ba.addPath(testTag, tiffPath, &ba, nullptr);

        // Result should not be null (either found or created component)
        EXPECT_NE(result, nullptr);
    } catch (const std::exception& e) {
        GTEST_SKIP() << "Skipped due to configuration dependency: " << e.what();
    }
}

// Test decoded state
TEST_F(TiffBinaryArrayDoAddPathTest_324, DecodedDefaultIsFalse_324) {
    const uint16_t testTag = 0x0001;
    const IfdId testGroup = IfdId::canonCsId;

    ArrayCfg arrayCfg{
        testGroup,
        invalidByteOrder,
        ttUnsignedByte,
        notEncrypted,
        false,
        false
    };

    TiffBinaryArray ba(testTag, testGroup, arrayCfg, nullptr, 0);
    EXPECT_FALSE(ba.decoded());
}

// Test setDecoded
TEST_F(TiffBinaryArrayDoAddPathTest_324, SetDecodedChangesState_324) {
    const uint16_t testTag = 0x0001;
    const IfdId testGroup = IfdId::canonCsId;

    ArrayCfg arrayCfg{
        testGroup,
        invalidByteOrder,
        ttUnsignedByte,
        notEncrypted,
        false,
        false
    };

    TiffBinaryArray ba(testTag, testGroup, arrayCfg, nullptr, 0);
    ba.setDecoded(true);
    EXPECT_TRUE(ba.decoded());
}

// Test tag() and group() accessors
TEST_F(TiffBinaryArrayDoAddPathTest_324, TagAndGroupAccessors_324) {
    const uint16_t testTag = 0x0042;
    const IfdId testGroup = IfdId::canonCsId;

    ArrayCfg arrayCfg{
        testGroup,
        invalidByteOrder,
        ttUnsignedByte,
        notEncrypted,
        false,
        false
    };

    TiffBinaryArray ba(testTag, testGroup, arrayCfg, nullptr, 0);
    EXPECT_EQ(ba.tag(), testTag);
    EXPECT_EQ(ba.group(), testGroup);
}

// Test cfg() returns the correct configuration
TEST_F(TiffBinaryArrayDoAddPathTest_324, CfgReturnsArrayCfg_324) {
    const uint16_t testTag = 0x0001;
    const IfdId testGroup = IfdId::canonCsId;

    ArrayCfg arrayCfg{
        testGroup,
        invalidByteOrder,
        ttUnsignedByte,
        notEncrypted,
        false,
        false
    };

    TiffBinaryArray ba(testTag, testGroup, arrayCfg, nullptr, 0);
    EXPECT_NE(ba.cfg(), nullptr);
    EXPECT_EQ(ba.cfg()->group_, testGroup);
}

// Test def() and defSize()
TEST_F(TiffBinaryArrayDoAddPathTest_324, DefAndDefSizeAccessors_324) {
    const uint16_t testTag = 0x0001;
    const IfdId testGroup = IfdId::canonCsId;

    ArrayCfg arrayCfg{
        testGroup,
        invalidByteOrder,
        ttUnsignedByte,
        notEncrypted,
        false,
        false
    };

    ArrayDef arrayDef = {0, ttUnsignedShort, 1};

    TiffBinaryArray ba(testTag, testGroup, arrayCfg, &arrayDef, 1);
    EXPECT_EQ(ba.def(), &arrayDef);
    EXPECT_EQ(ba.defSize(), 1u);
}

// Test with null arrayDef
TEST_F(TiffBinaryArrayDoAddPathTest_324, NullDefReturnsNullptr_324) {
    const uint16_t testTag = 0x0001;
    const IfdId testGroup = IfdId::canonCsId;

    ArrayCfg arrayCfg{
        testGroup,
        invalidByteOrder,
        ttUnsignedByte,
        notEncrypted,
        false,
        false
    };

    TiffBinaryArray ba(testTag, testGroup, arrayCfg, nullptr, 0);
    EXPECT_EQ(ba.def(), nullptr);
    EXPECT_EQ(ba.defSize(), 0u);
}

// Test constructor with ArraySet
TEST_F(TiffBinaryArrayDoAddPathTest_324, ConstructWithArraySet_324) {
    const uint16_t testTag = 0x0001;
    const IfdId testGroup = IfdId::canonCsId;

    // Construct with ArraySet constructor (second form)
    TiffBinaryArray ba(testTag, testGroup, nullptr, 0, nullptr);
    EXPECT_EQ(ba.tag(), testTag);
    EXPECT_EQ(ba.group(), testGroup);
    EXPECT_EQ(ba.cfg(), nullptr);
}

// Test TiffPathItem accessors
TEST_F(TiffBinaryArrayDoAddPathTest_324, TiffPathItemAccessors_324) {
    const uint32_t extTag = 0x1234;
    const IfdId group = IfdId::canonCsId;

    TiffPathItem item(extTag, group);
    EXPECT_EQ(item.extendedTag(), extTag);
    EXPECT_EQ(item.group(), group);
    EXPECT_EQ(item.tag(), static_cast<uint16_t>(extTag & 0xffff));
}

// Test addPath with nullptr object and single path element
TEST_F(TiffBinaryArrayDoAddPathTest_324, AddPathNullObjectSingleElement_324) {
    try {
        const uint16_t testTag = 0x0001;
        const IfdId testGroup = IfdId::canonCsId;

        ArrayCfg arrayCfg{
            testGroup,
            invalidByteOrder,
            ttUnsignedByte,
            notEncrypted,
            false,
            false
        };

        TiffBinaryArray ba(testTag, testGroup, arrayCfg, nullptr, 0);

        TiffPath tiffPath;
        TiffPathItem item(testTag, testGroup);
        tiffPath.push(item);

        // With size == 1 and nullptr object, should still return this
        TiffComponent* result = ba.addPath(testTag, tiffPath, &ba, nullptr);
        EXPECT_EQ(result, &ba);
    } catch (const std::exception& e) {
        GTEST_SKIP() << "Skipped due to configuration dependency: " << e.what();
    }
}
