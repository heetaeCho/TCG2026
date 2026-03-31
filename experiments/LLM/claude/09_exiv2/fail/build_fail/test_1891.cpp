#include <gtest/gtest.h>

// Include necessary headers
#include "XMP_Const.h"

// We need to declare the function under test and the exception mechanism
// Based on the XMP SDK, XMP_Throw typically throws an XMP_Error
#include "XMPCore_Impl.hpp"

// If the above headers don't work directly, we may need these definitions:
#ifndef XMP_StringPtr
typedef const char* XMP_StringPtr;
#endif

#ifndef XMP_OptionBits
typedef unsigned int XMP_OptionBits;
#endif

// Forward declaration of the function under test
extern XMP_OptionBits VerifySetOptions(XMP_OptionBits options, XMP_StringPtr propValue);

// Define kXMP_AllSetOptionsMask if not already defined
#ifndef kXMP_AllSetOptionsMask
enum { kXMP_AllSetOptionsMask = 536878850 };
#endif

class VerifySetOptionsTest_1891 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// =============================================================================
// Normal operation tests
// =============================================================================

TEST_F(VerifySetOptionsTest_1891, ZeroOptionsNullValue_ReturnsZero_1891) {
    XMP_OptionBits result = VerifySetOptions(0, nullptr);
    EXPECT_EQ(result, 0u);
}

TEST_F(VerifySetOptionsTest_1891, ZeroOptionsEmptyString_ReturnsZero_1891) {
    XMP_OptionBits result = VerifySetOptions(0, "");
    EXPECT_EQ(result, 0u);
}

TEST_F(VerifySetOptionsTest_1891, ZeroOptionsWithStringValue_ReturnsZero_1891) {
    XMP_OptionBits result = VerifySetOptions(0, "some value");
    EXPECT_EQ(result, 0u);
}

TEST_F(VerifySetOptionsTest_1891, PropValueIsURI_WithNullValue_1891) {
    XMP_OptionBits result = VerifySetOptions(kXMP_PropValueIsURI, nullptr);
    EXPECT_EQ(result, static_cast<XMP_OptionBits>(kXMP_PropValueIsURI));
}

TEST_F(VerifySetOptionsTest_1891, PropValueIsURI_WithStringValue_1891) {
    XMP_OptionBits result = VerifySetOptions(kXMP_PropValueIsURI, "test");
    EXPECT_EQ(result, static_cast<XMP_OptionBits>(kXMP_PropValueIsURI));
}

// =============================================================================
// Flag propagation tests (cascading of array options)
// =============================================================================

TEST_F(VerifySetOptionsTest_1891, AltTextSetsAlternateAndOrderedAndArray_1891) {
    XMP_OptionBits result = VerifySetOptions(kXMP_PropArrayIsAltText, nullptr);
    EXPECT_TRUE(result & kXMP_PropArrayIsAltText);
    EXPECT_TRUE(result & kXMP_PropArrayIsAlternate);
    EXPECT_TRUE(result & kXMP_PropArrayIsOrdered);
    EXPECT_TRUE(result & kXMP_PropValueIsArray);
}

TEST_F(VerifySetOptionsTest_1891, AlternateSetsOrderedAndArray_1891) {
    XMP_OptionBits result = VerifySetOptions(kXMP_PropArrayIsAlternate, nullptr);
    EXPECT_TRUE(result & kXMP_PropArrayIsAlternate);
    EXPECT_TRUE(result & kXMP_PropArrayIsOrdered);
    EXPECT_TRUE(result & kXMP_PropValueIsArray);
}

TEST_F(VerifySetOptionsTest_1891, OrderedSetsArray_1891) {
    XMP_OptionBits result = VerifySetOptions(kXMP_PropArrayIsOrdered, nullptr);
    EXPECT_TRUE(result & kXMP_PropArrayIsOrdered);
    EXPECT_TRUE(result & kXMP_PropValueIsArray);
}

TEST_F(VerifySetOptionsTest_1891, ArrayAloneStaysArray_1891) {
    XMP_OptionBits result = VerifySetOptions(kXMP_PropValueIsArray, nullptr);
    EXPECT_TRUE(result & kXMP_PropValueIsArray);
    EXPECT_FALSE(result & kXMP_PropArrayIsOrdered);
    EXPECT_FALSE(result & kXMP_PropArrayIsAlternate);
    EXPECT_FALSE(result & kXMP_PropArrayIsAltText);
}

// =============================================================================
// Struct with null value is OK
// =============================================================================

TEST_F(VerifySetOptionsTest_1891, StructWithNullValue_Succeeds_1891) {
    XMP_OptionBits result = VerifySetOptions(kXMP_PropValueIsStruct, nullptr);
    EXPECT_EQ(result, static_cast<XMP_OptionBits>(kXMP_PropValueIsStruct));
}

// =============================================================================
// Error / Exception tests
// =============================================================================

TEST_F(VerifySetOptionsTest_1891, UnrecognizedOptionFlags_Throws_1891) {
    // Use a bit that is not in kXMP_AllSetOptionsMask (536878850)
    // kXMP_AllSetOptionsMask = 0x20001F02
    // Pick a bit outside this mask, e.g., bit 0 (value 1)
    XMP_OptionBits badOptions = 1u; // bit 0 is not in the mask
    EXPECT_ANY_THROW(VerifySetOptions(badOptions, nullptr));
}

TEST_F(VerifySetOptionsTest_1891, StructAndArrayMutuallyExclusive_Throws_1891) {
    XMP_OptionBits options = kXMP_PropValueIsStruct | kXMP_PropValueIsArray;
    EXPECT_ANY_THROW(VerifySetOptions(options, nullptr));
}

TEST_F(VerifySetOptionsTest_1891, StructAndOrderedArray_MutuallyExclusive_Throws_1891) {
    // kXMP_PropArrayIsOrdered will cascade to set kXMP_PropValueIsArray
    // Then both struct and array will be set
    XMP_OptionBits options = kXMP_PropValueIsStruct | kXMP_PropArrayIsOrdered;
    EXPECT_ANY_THROW(VerifySetOptions(options, nullptr));
}

TEST_F(VerifySetOptionsTest_1891, StructAndAlternateArray_MutuallyExclusive_Throws_1891) {
    XMP_OptionBits options = kXMP_PropValueIsStruct | kXMP_PropArrayIsAlternate;
    EXPECT_ANY_THROW(VerifySetOptions(options, nullptr));
}

TEST_F(VerifySetOptionsTest_1891, StructAndAltText_MutuallyExclusive_Throws_1891) {
    XMP_OptionBits options = kXMP_PropValueIsStruct | kXMP_PropArrayIsAltText;
    EXPECT_ANY_THROW(VerifySetOptions(options, nullptr));
}

TEST_F(VerifySetOptionsTest_1891, ValueOptionsWithStruct_Throws_1891) {
    // kXMP_PropValueOptionsMask = 2 (which is kXMP_PropValueIsURI)
    // kXMP_PropCompositeMask = 7936 (0x1F00) includes struct and array bits
    XMP_OptionBits options = kXMP_PropValueIsURI | kXMP_PropValueIsStruct;
    EXPECT_ANY_THROW(VerifySetOptions(options, nullptr));
}

TEST_F(VerifySetOptionsTest_1891, ValueOptionsWithArray_Throws_1891) {
    XMP_OptionBits options = kXMP_PropValueIsURI | kXMP_PropValueIsArray;
    EXPECT_ANY_THROW(VerifySetOptions(options, nullptr));
}

TEST_F(VerifySetOptionsTest_1891, StructWithStringValue_Throws_1891) {
    // Structs can't have string values
    EXPECT_ANY_THROW(VerifySetOptions(kXMP_PropValueIsStruct, "some string"));
}

TEST_F(VerifySetOptionsTest_1891, ArrayWithStringValue_Throws_1891) {
    // Arrays can't have string values
    EXPECT_ANY_THROW(VerifySetOptions(kXMP_PropValueIsArray, "some string"));
}

TEST_F(VerifySetOptionsTest_1891, OrderedArrayWithStringValue_Throws_1891) {
    EXPECT_ANY_THROW(VerifySetOptions(kXMP_PropArrayIsOrdered, "some string"));
}

TEST_F(VerifySetOptionsTest_1891, AlternateArrayWithStringValue_Throws_1891) {
    EXPECT_ANY_THROW(VerifySetOptions(kXMP_PropArrayIsAlternate, "some string"));
}

TEST_F(VerifySetOptionsTest_1891, AltTextWithStringValue_Throws_1891) {
    EXPECT_ANY_THROW(VerifySetOptions(kXMP_PropArrayIsAltText, "some string"));
}

// =============================================================================
// Boundary tests with high bits
// =============================================================================

TEST_F(VerifySetOptionsTest_1891, DeleteExistingOptionAlone_Succeeds_1891) {
    // kXMP_DeleteExisting = 536870912 = 0x20000000, should be in the mask
    XMP_OptionBits result = VerifySetOptions(kXMP_DeleteExisting, nullptr);
    EXPECT_EQ(result, static_cast<XMP_OptionBits>(kXMP_DeleteExisting));
}

TEST_F(VerifySetOptionsTest_1891, DeleteExistingWithStringValue_Succeeds_1891) {
    XMP_OptionBits result = VerifySetOptions(kXMP_DeleteExisting, "value");
    EXPECT_EQ(result, static_cast<XMP_OptionBits>(kXMP_DeleteExisting));
}

TEST_F(VerifySetOptionsTest_1891, ImplReservedMaskBits_AreUnrecognized_Throws_1891) {
    // kXMP_ImplReservedMask = 1879048192 = 0x70000000
    // Some of these bits may not be in kXMP_AllSetOptionsMask
    // kXMP_AllSetOptionsMask = 536878850 = 0x20001F02
    // 0x70000000 & ~0x20001F02 has many bits set, so should throw
    XMP_OptionBits badOptions = 0x40000000u; // bit 30, not in mask
    EXPECT_ANY_THROW(VerifySetOptions(badOptions, nullptr));
}

TEST_F(VerifySetOptionsTest_1891, MultipleFlagPropagation_AltTextFullCascade_1891) {
    // Start with just AltText, verify the full cascade
    XMP_OptionBits result = VerifySetOptions(kXMP_PropArrayIsAltText, nullptr);
    XMP_OptionBits expected = kXMP_PropArrayIsAltText | kXMP_PropArrayIsAlternate | 
                              kXMP_PropArrayIsOrdered | kXMP_PropValueIsArray;
    EXPECT_EQ(result, expected);
}

TEST_F(VerifySetOptionsTest_1891, InsertBeforeItem_WithNullValue_1891) {
    // kXMP_InsertBeforeItem = 16384 = 0x4000
    // Check if it's in the AllSetOptionsMask: 0x20001F02
    // 0x4000 & ~0x20001F02 = 0x4000 (not zero) => should throw
    EXPECT_ANY_THROW(VerifySetOptions(kXMP_InsertBeforeItem, nullptr));
}

TEST_F(VerifySetOptionsTest_1891, InsertAfterItem_WithNullValue_1891) {
    // kXMP_InsertAfterItem = 32768 = 0x8000
    // 0x8000 & ~0x20001F02 = 0x8000 (not zero) => should throw
    EXPECT_ANY_THROW(VerifySetOptions(kXMP_InsertAfterItem, nullptr));
}

// =============================================================================
// Verify that HasQualifiers and similar qualifier flags work with null value
// =============================================================================

TEST_F(VerifySetOptionsTest_1891, HasQualifiers_WithNullValue_Succeeds_1891) {
    // kXMP_PropHasQualifiers = 16 = 0x10
    // 0x10 & ~0x20001F02 = 0x10 (not zero), so this might throw
    // Actually let's check: kXMP_AllSetOptionsMask = 0x20001F02
    // 0x10 is not in 0x20001F02, so it should throw
    EXPECT_ANY_THROW(VerifySetOptions(kXMP_PropHasQualifiers, nullptr));
}

TEST_F(VerifySetOptionsTest_1891, PropHasLang_Throws_Unrecognized_1891) {
    // kXMP_PropHasLang = 64 = 0x40, not in mask 0x20001F02
    EXPECT_ANY_THROW(VerifySetOptions(kXMP_PropHasLang, nullptr));
}

TEST_F(VerifySetOptionsTest_1891, PropHasType_Throws_Unrecognized_1891) {
    // kXMP_PropHasType = 128 = 0x80, not in mask 0x20001F02
    EXPECT_ANY_THROW(VerifySetOptions(kXMP_PropHasType, nullptr));
}

// =============================================================================
// Test that the composite mask options with string value throws
// =============================================================================

TEST_F(VerifySetOptionsTest_1891, StructWithEmptyStringValue_Throws_1891) {
    // propValue is "" which is not null (propValue != 0)
    // But "" is a valid pointer, so the check (propValue != 0) is true
    EXPECT_ANY_THROW(VerifySetOptions(kXMP_PropValueIsStruct, ""));
}

TEST_F(VerifySetOptionsTest_1891, ArrayWithEmptyStringValue_Throws_1891) {
    EXPECT_ANY_THROW(VerifySetOptions(kXMP_PropValueIsArray, ""));
}
