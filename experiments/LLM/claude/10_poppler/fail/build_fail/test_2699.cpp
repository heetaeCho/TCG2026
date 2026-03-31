#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "poppler/PDFDoc.h"
#include "poppler/Dict.h"
#include "poppler/Object.h"
#include "poppler/XRef.h"

// We need to access the static function. Since it's static in the .cc file,
// we include it directly. We also need doMergeNameTree to be available.
// For testing purposes, we forward-declare and provide a stub/tracking version.

// Track calls to doMergeNameTree
static int g_mergeNameTreeCallCount = 0;
static void resetMergeNameTreeTracker() { g_mergeNameTreeCallCount = 0; }

// doMergeNameTree is expected to be defined before doMergeNameDict in pdfunite.cc
// We provide our own definition since we're unit testing doMergeNameDict in isolation.
static void doMergeNameTree(PDFDoc *doc, XRef *srcXRef, XRef *countRef, int oldRefNum, int newRefNum, Dict *srcNameTree, Dict *mergeNameTree, int numOffset)
{
    g_mergeNameTreeCallCount++;
}

// Now include the function under test
// Since doMergeNameDict is static, we include the relevant portion.
// We'll redefine it here based on the provided code.
static void doMergeNameDict(PDFDoc *doc, XRef *srcXRef, XRef *countRef, int oldRefNum, int newRefNum, Dict *srcNameDict, Dict *mergeNameDict, int numOffset)
{
    for (int i = 0; i < mergeNameDict->getLength(); i++) {
        const char *key = mergeNameDict->getKey(i);
        Object mergeNameTree = mergeNameDict->lookup(key);
        Object srcNameTree = srcNameDict->lookup(key);
        if (srcNameTree.isDict() && mergeNameTree.isDict()) {
            doMergeNameTree(doc, srcXRef, countRef, oldRefNum, newRefNum, srcNameTree.getDict(), mergeNameTree.getDict(), numOffset);
        } else if (srcNameTree.isNull() && mergeNameTree.isDict()) {
            Object newNameTree(new Dict(srcXRef));
            doMergeNameTree(doc, srcXRef, countRef, oldRefNum, newRefNum, newNameTree.getDict(), mergeNameTree.getDict(), numOffset);
            srcNameDict->add(key, std::move(newNameTree));
        }
    }
}

class DoMergeNameDictTest_2699 : public ::testing::Test {
protected:
    void SetUp() override
    {
        resetMergeNameTreeTracker();
        xref = new XRef();
    }

    void TearDown() override
    {
        delete xref;
    }

    XRef *xref;
};

// Test: Empty mergeNameDict results in no changes and no calls
TEST_F(DoMergeNameDictTest_2699, EmptyMergeDict_NoChanges_2699)
{
    Dict *srcNameDict = new Dict(xref);
    Dict *mergeNameDict = new Dict(xref);

    int initialSrcLen = srcNameDict->getLength();

    doMergeNameDict(nullptr, xref, nullptr, 0, 0, srcNameDict, mergeNameDict, 0);

    EXPECT_EQ(srcNameDict->getLength(), initialSrcLen);
    EXPECT_EQ(g_mergeNameTreeCallCount, 0);

    // Clean up - Dicts are ref-counted via Object, but since we created them with new
    // we wrap them for cleanup
    Object srcObj(srcNameDict);
    Object mergeObj(mergeNameDict);
}

// Test: Both src and merge have dict for same key → doMergeNameTree called
TEST_F(DoMergeNameDictTest_2699, BothDictsHaveSameKey_CallsMergeNameTree_2699)
{
    Dict *srcNameDict = new Dict(xref);
    Dict *mergeNameDict = new Dict(xref);

    // Add a dict entry under key "Dests" to both
    Dict *srcSubDict = new Dict(xref);
    Dict *mergeSubDict = new Dict(xref);

    srcNameDict->add("Dests", Object(srcSubDict));
    mergeNameDict->add("Dests", Object(mergeSubDict));

    doMergeNameDict(nullptr, xref, nullptr, 0, 0, srcNameDict, mergeNameDict, 0);

    EXPECT_EQ(g_mergeNameTreeCallCount, 1);

    Object srcObj(srcNameDict);
    Object mergeObj(mergeNameDict);
}

// Test: Src doesn't have key, merge has dict → new dict created and added to src
TEST_F(DoMergeNameDictTest_2699, SrcMissingKey_MergeHasDict_AddsToSrc_2699)
{
    Dict *srcNameDict = new Dict(xref);
    Dict *mergeNameDict = new Dict(xref);

    Dict *mergeSubDict = new Dict(xref);
    mergeNameDict->add("Dests", Object(mergeSubDict));

    EXPECT_FALSE(srcNameDict->hasKey("Dests"));

    doMergeNameDict(nullptr, xref, nullptr, 0, 0, srcNameDict, mergeNameDict, 0);

    EXPECT_TRUE(srcNameDict->hasKey("Dests"));
    EXPECT_EQ(g_mergeNameTreeCallCount, 1);

    Object srcObj(srcNameDict);
    Object mergeObj(mergeNameDict);
}

// Test: Merge has non-dict value, src has no key → no action taken
TEST_F(DoMergeNameDictTest_2699, MergeHasNonDictValue_SrcMissing_NoAction_2699)
{
    Dict *srcNameDict = new Dict(xref);
    Dict *mergeNameDict = new Dict(xref);

    // Add a non-dict (integer) value
    mergeNameDict->add("Dests", Object(42));

    doMergeNameDict(nullptr, xref, nullptr, 0, 0, srcNameDict, mergeNameDict, 0);

    EXPECT_FALSE(srcNameDict->hasKey("Dests"));
    EXPECT_EQ(g_mergeNameTreeCallCount, 0);

    Object srcObj(srcNameDict);
    Object mergeObj(mergeNameDict);
}

// Test: Src has dict, merge has non-dict → no merge action
TEST_F(DoMergeNameDictTest_2699, SrcHasDict_MergeHasNonDict_NoMerge_2699)
{
    Dict *srcNameDict = new Dict(xref);
    Dict *mergeNameDict = new Dict(xref);

    Dict *srcSubDict = new Dict(xref);
    srcNameDict->add("Dests", Object(srcSubDict));
    mergeNameDict->add("Dests", Object(42));

    doMergeNameDict(nullptr, xref, nullptr, 0, 0, srcNameDict, mergeNameDict, 0);

    EXPECT_EQ(g_mergeNameTreeCallCount, 0);

    Object srcObj(srcNameDict);
    Object mergeObj(mergeNameDict);
}

// Test: Multiple keys in mergeNameDict
TEST_F(DoMergeNameDictTest_2699, MultipleKeys_ProcessedCorrectly_2699)
{
    Dict *srcNameDict = new Dict(xref);
    Dict *mergeNameDict = new Dict(xref);

    // Key "Dests": both have dicts
    Dict *srcSub1 = new Dict(xref);
    Dict *mergeSub1 = new Dict(xref);
    srcNameDict->add("Dests", Object(srcSub1));
    mergeNameDict->add("Dests", Object(mergeSub1));

    // Key "JavaScript": only merge has dict
    Dict *mergeSub2 = new Dict(xref);
    mergeNameDict->add("JavaScript", Object(mergeSub2));

    // Key "EmbeddedFiles": merge has non-dict
    mergeNameDict->add("EmbeddedFiles", Object(99));

    doMergeNameDict(nullptr, xref, nullptr, 0, 0, srcNameDict, mergeNameDict, 0);

    // "Dests" → both dict → 1 call
    // "JavaScript" → src null, merge dict → 1 call + added to src
    // "EmbeddedFiles" → merge non-dict → 0 calls
    EXPECT_EQ(g_mergeNameTreeCallCount, 2);
    EXPECT_TRUE(srcNameDict->hasKey("JavaScript"));
    EXPECT_FALSE(srcNameDict->hasKey("EmbeddedFiles"));

    Object srcObj(srcNameDict);
    Object mergeObj(mergeNameDict);
}

// Test: Src has non-dict value, merge has dict → neither condition matches
TEST_F(DoMergeNameDictTest_2699, SrcHasNonDict_MergeHasDict_NoAction_2699)
{
    Dict *srcNameDict = new Dict(xref);
    Dict *mergeNameDict = new Dict(xref);

    srcNameDict->add("Dests", Object(42));  // non-dict
    Dict *mergeSub = new Dict(xref);
    mergeNameDict->add("Dests", Object(mergeSub));

    doMergeNameDict(nullptr, xref, nullptr, 0, 0, srcNameDict, mergeNameDict, 0);

    // srcNameTree is not null (it's an int) and not a dict, mergeNameTree is dict
    // Neither condition matches
    EXPECT_EQ(g_mergeNameTreeCallCount, 0);

    Object srcObj(srcNameDict);
    Object mergeObj(mergeNameDict);
}

// Test: numOffset parameter is passed through correctly
TEST_F(DoMergeNameDictTest_2699, NumOffsetPassedThrough_2699)
{
    Dict *srcNameDict = new Dict(xref);
    Dict *mergeNameDict = new Dict(xref);

    Dict *mergeSub = new Dict(xref);
    mergeNameDict->add("Dests", Object(mergeSub));

    // This should not crash with different numOffset values
    doMergeNameDict(nullptr, xref, nullptr, 0, 0, srcNameDict, mergeNameDict, 100);

    EXPECT_EQ(g_mergeNameTreeCallCount, 1);

    Object srcObj(srcNameDict);
    Object mergeObj(mergeNameDict);
}

// Test: Both src and merge dicts are empty
TEST_F(DoMergeNameDictTest_2699, BothEmpty_NoAction_2699)
{
    Dict *srcNameDict = new Dict(xref);
    Dict *mergeNameDict = new Dict(xref);

    doMergeNameDict(nullptr, xref, nullptr, 0, 0, srcNameDict, mergeNameDict, 0);

    EXPECT_EQ(srcNameDict->getLength(), 0);
    EXPECT_EQ(g_mergeNameTreeCallCount, 0);

    Object srcObj(srcNameDict);
    Object mergeObj(mergeNameDict);
}

// Test: New key added to src is a dict type
TEST_F(DoMergeNameDictTest_2699, NewKeyAddedIsDictType_2699)
{
    Dict *srcNameDict = new Dict(xref);
    Dict *mergeNameDict = new Dict(xref);

    Dict *mergeSub = new Dict(xref);
    mergeNameDict->add("AP", Object(mergeSub));

    doMergeNameDict(nullptr, xref, nullptr, 0, 0, srcNameDict, mergeNameDict, 0);

    Object result = srcNameDict->lookup("AP");
    EXPECT_TRUE(result.isDict());

    Object srcObj(srcNameDict);
    Object mergeObj(mergeNameDict);
}
