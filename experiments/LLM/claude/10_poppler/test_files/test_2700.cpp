#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Object.h"
#include "Dict.h"
#include "Array.h"
#include "Error.h"

// Include the source file to get access to the static function
#include "pdfunite.cc"

class DoMergeFormDictTest_2700 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: Both Fields are arrays with valid Ref entries
TEST_F(DoMergeFormDictTest_2700, MergeValidRefFields_2700) {
    XRef *xref = nullptr;

    Dict *srcFormDict = new Dict(xref);
    Dict *mergeFormDict = new Dict(xref);

    Array *srcArray = new Array(xref);
    Array *mergeArray = new Array(xref);

    // Add a Ref to mergeArray
    Ref ref1 = { .num = 10, .gen = 0 };
    mergeArray->add(Object(ref1));

    Ref ref2 = { .num = 20, .gen = 1 };
    mergeArray->add(Object(ref2));

    srcFormDict->add("Fields", Object(srcArray));
    mergeFormDict->add("Fields", Object(mergeArray));

    int numOffset = 5;
    bool result = doMergeFormDict(srcFormDict, mergeFormDict, numOffset);

    EXPECT_TRUE(result);

    // Check that srcFields now has the merged entries
    Object srcFields = srcFormDict->lookup("Fields");
    ASSERT_TRUE(srcFields.isArray());
    EXPECT_EQ(srcFields.arrayGetLength(), 2);

    // Check the first merged ref
    const Object &entry0 = srcFields.arrayGetNF(0);
    ASSERT_TRUE(entry0.isRef());
    EXPECT_EQ(entry0.getRef().num, 10 + numOffset);
    EXPECT_EQ(entry0.getRef().gen, 0);

    // Check the second merged ref
    const Object &entry1 = srcFields.arrayGetNF(1);
    ASSERT_TRUE(entry1.isRef());
    EXPECT_EQ(entry1.getRef().num, 20 + numOffset);
    EXPECT_EQ(entry1.getRef().gen, 1);

    delete srcFormDict;
    delete mergeFormDict;
}

// Test: Merge fields contain a non-Ref entry, should return false
TEST_F(DoMergeFormDictTest_2700, MergeNonRefFieldReturnsFalse_2700) {
    XRef *xref = nullptr;

    Dict *srcFormDict = new Dict(xref);
    Dict *mergeFormDict = new Dict(xref);

    Array *srcArray = new Array(xref);
    Array *mergeArray = new Array(xref);

    // Add a non-Ref object (an integer) to mergeArray
    mergeArray->add(Object(42));

    srcFormDict->add("Fields", Object(srcArray));
    mergeFormDict->add("Fields", Object(mergeArray));

    int numOffset = 5;
    bool result = doMergeFormDict(srcFormDict, mergeFormDict, numOffset);

    EXPECT_FALSE(result);

    delete srcFormDict;
    delete mergeFormDict;
}

// Test: Source Fields is not an array — should return true without merging
TEST_F(DoMergeFormDictTest_2700, SrcFieldsNotArray_2700) {
    XRef *xref = nullptr;

    Dict *srcFormDict = new Dict(xref);
    Dict *mergeFormDict = new Dict(xref);

    Array *mergeArray = new Array(xref);
    Ref ref1 = { .num = 10, .gen = 0 };
    mergeArray->add(Object(ref1));

    // srcFormDict has no "Fields" key, so lookup returns null/none
    mergeFormDict->add("Fields", Object(mergeArray));

    int numOffset = 5;
    bool result = doMergeFormDict(srcFormDict, mergeFormDict, numOffset);

    EXPECT_TRUE(result);

    delete srcFormDict;
    delete mergeFormDict;
}

// Test: Merge Fields is not an array — should return true without merging
TEST_F(DoMergeFormDictTest_2700, MergeFieldsNotArray_2700) {
    XRef *xref = nullptr;

    Dict *srcFormDict = new Dict(xref);
    Dict *mergeFormDict = new Dict(xref);

    Array *srcArray = new Array(xref);
    srcFormDict->add("Fields", Object(srcArray));
    // mergeFormDict has no "Fields" key

    int numOffset = 5;
    bool result = doMergeFormDict(srcFormDict, mergeFormDict, numOffset);

    EXPECT_TRUE(result);

    delete srcFormDict;
    delete mergeFormDict;
}

// Test: Both Fields are arrays but merge array is empty
TEST_F(DoMergeFormDictTest_2700, EmptyMergeFieldsArray_2700) {
    XRef *xref = nullptr;

    Dict *srcFormDict = new Dict(xref);
    Dict *mergeFormDict = new Dict(xref);

    Array *srcArray = new Array(xref);
    Array *mergeArray = new Array(xref);

    srcFormDict->add("Fields", Object(srcArray));
    mergeFormDict->add("Fields", Object(mergeArray));

    int numOffset = 100;
    bool result = doMergeFormDict(srcFormDict, mergeFormDict, numOffset);

    EXPECT_TRUE(result);

    Object srcFields = srcFormDict->lookup("Fields");
    ASSERT_TRUE(srcFields.isArray());
    EXPECT_EQ(srcFields.arrayGetLength(), 0);

    delete srcFormDict;
    delete mergeFormDict;
}

// Test: numOffset is zero
TEST_F(DoMergeFormDictTest_2700, ZeroNumOffset_2700) {
    XRef *xref = nullptr;

    Dict *srcFormDict = new Dict(xref);
    Dict *mergeFormDict = new Dict(xref);

    Array *srcArray = new Array(xref);
    Array *mergeArray = new Array(xref);

    Ref ref1 = { .num = 7, .gen = 2 };
    mergeArray->add(Object(ref1));

    srcFormDict->add("Fields", Object(srcArray));
    mergeFormDict->add("Fields", Object(mergeArray));

    int numOffset = 0;
    bool result = doMergeFormDict(srcFormDict, mergeFormDict, numOffset);

    EXPECT_TRUE(result);

    Object srcFields = srcFormDict->lookup("Fields");
    ASSERT_TRUE(srcFields.isArray());
    EXPECT_EQ(srcFields.arrayGetLength(), 1);

    const Object &entry0 = srcFields.arrayGetNF(0);
    ASSERT_TRUE(entry0.isRef());
    EXPECT_EQ(entry0.getRef().num, 7);
    EXPECT_EQ(entry0.getRef().gen, 2);

    delete srcFormDict;
    delete mergeFormDict;
}

// Test: Source already has existing fields, merge appends
TEST_F(DoMergeFormDictTest_2700, AppendToExistingSrcFields_2700) {
    XRef *xref = nullptr;

    Dict *srcFormDict = new Dict(xref);
    Dict *mergeFormDict = new Dict(xref);

    Array *srcArray = new Array(xref);
    Array *mergeArray = new Array(xref);

    Ref existingRef = { .num = 1, .gen = 0 };
    srcArray->add(Object(existingRef));

    Ref mergeRef = { .num = 10, .gen = 0 };
    mergeArray->add(Object(mergeRef));

    srcFormDict->add("Fields", Object(srcArray));
    mergeFormDict->add("Fields", Object(mergeArray));

    int numOffset = 100;
    bool result = doMergeFormDict(srcFormDict, mergeFormDict, numOffset);

    EXPECT_TRUE(result);

    Object srcFields = srcFormDict->lookup("Fields");
    ASSERT_TRUE(srcFields.isArray());
    EXPECT_EQ(srcFields.arrayGetLength(), 2);

    // Original entry preserved
    const Object &entry0 = srcFields.arrayGetNF(0);
    ASSERT_TRUE(entry0.isRef());
    EXPECT_EQ(entry0.getRef().num, 1);

    // Merged entry with offset
    const Object &entry1 = srcFields.arrayGetNF(1);
    ASSERT_TRUE(entry1.isRef());
    EXPECT_EQ(entry1.getRef().num, 110);
    EXPECT_EQ(entry1.getRef().gen, 0);

    delete srcFormDict;
    delete mergeFormDict;
}

// Test: Mixed Ref and non-Ref in merge array — should fail on first non-Ref
TEST_F(DoMergeFormDictTest_2700, MixedRefAndNonRefFields_2700) {
    XRef *xref = nullptr;

    Dict *srcFormDict = new Dict(xref);
    Dict *mergeFormDict = new Dict(xref);

    Array *srcArray = new Array(xref);
    Array *mergeArray = new Array(xref);

    Ref ref1 = { .num = 5, .gen = 0 };
    mergeArray->add(Object(ref1));
    // Add a non-Ref (integer)
    mergeArray->add(Object(99));

    srcFormDict->add("Fields", Object(srcArray));
    mergeFormDict->add("Fields", Object(mergeArray));

    int numOffset = 10;
    bool result = doMergeFormDict(srcFormDict, mergeFormDict, numOffset);

    // Should return false because the second entry is not a Ref
    EXPECT_FALSE(result);

    // First ref should have been added before the error
    Object srcFields = srcFormDict->lookup("Fields");
    ASSERT_TRUE(srcFields.isArray());
    EXPECT_EQ(srcFields.arrayGetLength(), 1);

    delete srcFormDict;
    delete mergeFormDict;
}

// Test: Negative numOffset
TEST_F(DoMergeFormDictTest_2700, NegativeNumOffset_2700) {
    XRef *xref = nullptr;

    Dict *srcFormDict = new Dict(xref);
    Dict *mergeFormDict = new Dict(xref);

    Array *srcArray = new Array(xref);
    Array *mergeArray = new Array(xref);

    Ref ref1 = { .num = 100, .gen = 0 };
    mergeArray->add(Object(ref1));

    srcFormDict->add("Fields", Object(srcArray));
    mergeFormDict->add("Fields", Object(mergeArray));

    int numOffset = -5;
    bool result = doMergeFormDict(srcFormDict, mergeFormDict, numOffset);

    EXPECT_TRUE(result);

    Object srcFields = srcFormDict->lookup("Fields");
    ASSERT_TRUE(srcFields.isArray());
    EXPECT_EQ(srcFields.arrayGetLength(), 1);

    const Object &entry0 = srcFields.arrayGetNF(0);
    ASSERT_TRUE(entry0.isRef());
    EXPECT_EQ(entry0.getRef().num, 95);
    EXPECT_EQ(entry0.getRef().gen, 0);

    delete srcFormDict;
    delete mergeFormDict;
}

// Test: Neither dict has Fields
TEST_F(DoMergeFormDictTest_2700, NeitherHasFields_2700) {
    XRef *xref = nullptr;

    Dict *srcFormDict = new Dict(xref);
    Dict *mergeFormDict = new Dict(xref);

    int numOffset = 10;
    bool result = doMergeFormDict(srcFormDict, mergeFormDict, numOffset);

    EXPECT_TRUE(result);

    delete srcFormDict;
    delete mergeFormDict;
}

// Test: Gen value is preserved correctly (not offset)
TEST_F(DoMergeFormDictTest_2700, GenValuePreserved_2700) {
    XRef *xref = nullptr;

    Dict *srcFormDict = new Dict(xref);
    Dict *mergeFormDict = new Dict(xref);

    Array *srcArray = new Array(xref);
    Array *mergeArray = new Array(xref);

    Ref ref1 = { .num = 3, .gen = 42 };
    mergeArray->add(Object(ref1));

    srcFormDict->add("Fields", Object(srcArray));
    mergeFormDict->add("Fields", Object(mergeArray));

    int numOffset = 10;
    bool result = doMergeFormDict(srcFormDict, mergeFormDict, numOffset);

    EXPECT_TRUE(result);

    Object srcFields = srcFormDict->lookup("Fields");
    ASSERT_TRUE(srcFields.isArray());

    const Object &entry0 = srcFields.arrayGetNF(0);
    ASSERT_TRUE(entry0.isRef());
    EXPECT_EQ(entry0.getRef().num, 13);
    EXPECT_EQ(entry0.getRef().gen, 42);  // gen should not be offset

    delete srcFormDict;
    delete mergeFormDict;
}
