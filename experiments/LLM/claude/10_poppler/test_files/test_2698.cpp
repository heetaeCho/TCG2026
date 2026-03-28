#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary poppler headers
#include "Object.h"
#include "Array.h"
#include "Dict.h"
#include "XRef.h"
#include "PDFDoc.h"
#include "GooString.h"

// Since doMergeNameTree is a static function in pdfunite.cc, we need to include it
// to make it available for testing. We wrap it to avoid main() conflicts.
#define main pdfunite_main
#include "pdfunite.cc"
#undef main

class DoMergeNameTreeTest_2698 : public ::testing::Test {
protected:
    void SetUp() override {
        xref = new XRef();
        countRef = new XRef();
    }

    void TearDown() override {
        delete xref;
        delete countRef;
    }

    XRef *xref;
    XRef *countRef;

    // Helper to create a PDFDoc for testing
    // We use a minimal approach - create from a minimal PDF stream
    std::unique_ptr<PDFDoc> createMinimalDoc() {
        auto doc = std::unique_ptr<PDFDoc>(new PDFDoc());
        return doc;
    }

    // Helper: create a name array with string-ref pairs
    Array* createNameArray(XRef* xr, const std::vector<std::pair<std::string, Ref>>& entries) {
        Array* arr = new Array(xr);
        for (const auto& e : entries) {
            arr->add(Object(std::make_unique<GooString>(e.first.c_str())));
            arr->add(Object(e.second));
        }
        return arr;
    }
};

// Test: Both src and merge have Names arrays - merge entries are interleaved properly
TEST_F(DoMergeNameTreeTest_2698, BothHaveNamesArrays_MergeInterleaved_2698) {
    // Create source name tree dict
    Dict* srcNameTree = new Dict(xref);
    Array* srcArr = new Array(xref);
    srcArr->add(Object(std::make_unique<GooString>("b")));
    srcArr->add(Object(Ref{.num = 1, .gen = 0}));
    srcArr->add(Object(std::make_unique<GooString>("d")));
    srcArr->add(Object(Ref{.num = 2, .gen = 0}));
    srcNameTree->add("Names", Object(srcArr));

    // Create merge name tree dict
    Dict* mergeNameTree = new Dict(xref);
    Array* mergeArr = new Array(xref);
    mergeArr->add(Object(std::make_unique<GooString>("a")));
    mergeArr->add(Object(Ref{.num = 10, .gen = 0}));
    mergeArr->add(Object(std::make_unique<GooString>("c")));
    mergeArr->add(Object(Ref{.num = 11, .gen = 0}));
    mergeArr->add(Object(std::make_unique<GooString>("e")));
    mergeArr->add(Object(Ref{.num = 12, .gen = 0}));
    mergeNameTree->add("Names", Object(mergeArr));

    int numOffset = 100;
    PDFDoc doc;

    doMergeNameTree(&doc, xref, countRef, 0, 1, srcNameTree, mergeNameTree, numOffset);

    // Check the result: srcNameTree should now have a merged "Names" array
    Object namesObj = srcNameTree->lookup("Names");
    ASSERT_TRUE(namesObj.isArray());
    
    // Expected order: a(110), b(1), c(111), d(2), e(112)
    // Total 10 entries (5 pairs)
    EXPECT_EQ(namesObj.arrayGetLength(), 10);

    // Check ordering: keys should be a, b, c, d, e
    if (namesObj.arrayGetLength() >= 10) {
        const Object& k0 = namesObj.arrayGetNF(0);
        EXPECT_TRUE(k0.isString());
        if (k0.isString()) EXPECT_EQ(k0.getString()->toStr(), "a");

        const Object& v0 = namesObj.arrayGetNF(1);
        EXPECT_TRUE(v0.isRef());
        if (v0.isRef()) EXPECT_EQ(v0.getRef().num, 10 + numOffset);

        const Object& k1 = namesObj.arrayGetNF(2);
        EXPECT_TRUE(k1.isString());
        if (k1.isString()) EXPECT_EQ(k1.getString()->toStr(), "b");

        const Object& v1 = namesObj.arrayGetNF(3);
        EXPECT_TRUE(v1.isRef());
        if (v1.isRef()) EXPECT_EQ(v1.getRef().num, 1);

        const Object& k2 = namesObj.arrayGetNF(4);
        EXPECT_TRUE(k2.isString());
        if (k2.isString()) EXPECT_EQ(k2.getString()->toStr(), "c");

        const Object& v2 = namesObj.arrayGetNF(5);
        EXPECT_TRUE(v2.isRef());
        if (v2.isRef()) EXPECT_EQ(v2.getRef().num, 11 + numOffset);

        const Object& k3 = namesObj.arrayGetNF(6);
        EXPECT_TRUE(k3.isString());
        if (k3.isString()) EXPECT_EQ(k3.getString()->toStr(), "d");

        const Object& v3 = namesObj.arrayGetNF(7);
        EXPECT_TRUE(v3.isRef());
        if (v3.isRef()) EXPECT_EQ(v3.getRef().num, 2);

        const Object& k4 = namesObj.arrayGetNF(8);
        EXPECT_TRUE(k4.isString());
        if (k4.isString()) EXPECT_EQ(k4.getString()->toStr(), "e");

        const Object& v4 = namesObj.arrayGetNF(9);
        EXPECT_TRUE(v4.isRef());
        if (v4.isRef()) EXPECT_EQ(v4.getRef().num, 12 + numOffset);
    }

    delete srcNameTree;
    delete mergeNameTree;
}

// Test: Source has no Names, merge has Names -> Names added to src
TEST_F(DoMergeNameTreeTest_2698, SrcNullMergeHasNames_2698) {
    Dict* srcNameTree = new Dict(xref);
    // No "Names" key in src

    Dict* mergeNameTree = new Dict(xref);
    Array* mergeArr = new Array(xref);
    mergeArr->add(Object(std::make_unique<GooString>("alpha")));
    mergeArr->add(Object(Ref{.num = 5, .gen = 0}));
    mergeArr->add(Object(std::make_unique<GooString>("beta")));
    mergeArr->add(Object(Ref{.num = 6, .gen = 0}));
    mergeNameTree->add("Names", Object(mergeArr));

    int numOffset = 50;
    PDFDoc doc;

    doMergeNameTree(&doc, xref, countRef, 0, 1, srcNameTree, mergeNameTree, numOffset);

    Object namesObj = srcNameTree->lookup("Names");
    ASSERT_TRUE(namesObj.isArray());
    EXPECT_EQ(namesObj.arrayGetLength(), 4);

    if (namesObj.arrayGetLength() >= 4) {
        const Object& k0 = namesObj.arrayGetNF(0);
        EXPECT_TRUE(k0.isString());
        if (k0.isString()) EXPECT_EQ(k0.getString()->toStr(), "alpha");

        const Object& v0 = namesObj.arrayGetNF(1);
        EXPECT_TRUE(v0.isRef());
        if (v0.isRef()) EXPECT_EQ(v0.getRef().num, 5 + numOffset);

        const Object& k1 = namesObj.arrayGetNF(2);
        EXPECT_TRUE(k1.isString());
        if (k1.isString()) EXPECT_EQ(k1.getString()->toStr(), "beta");

        const Object& v1 = namesObj.arrayGetNF(3);
        EXPECT_TRUE(v1.isRef());
        if (v1.isRef()) EXPECT_EQ(v1.getRef().num, 6 + numOffset);
    }

    delete srcNameTree;
    delete mergeNameTree;
}

// Test: Both have Names but merge is empty array
TEST_F(DoMergeNameTreeTest_2698, BothHaveNamesButMergeEmpty_2698) {
    Dict* srcNameTree = new Dict(xref);
    Array* srcArr = new Array(xref);
    srcArr->add(Object(std::make_unique<GooString>("key1")));
    srcArr->add(Object(Ref{.num = 1, .gen = 0}));
    srcNameTree->add("Names", Object(srcArr));

    Dict* mergeNameTree = new Dict(xref);
    Array* mergeArr = new Array(xref);
    // Empty merge array
    mergeNameTree->add("Names", Object(mergeArr));

    PDFDoc doc;
    doMergeNameTree(&doc, xref, countRef, 0, 1, srcNameTree, mergeNameTree, 0);

    Object namesObj = srcNameTree->lookup("Names");
    ASSERT_TRUE(namesObj.isArray());
    // Should contain original entries
    EXPECT_EQ(namesObj.arrayGetLength(), 2);

    delete srcNameTree;
    delete mergeNameTree;
}

// Test: Both have Names but src is empty array
TEST_F(DoMergeNameTreeTest_2698, BothHaveNamesButSrcEmpty_2698) {
    Dict* srcNameTree = new Dict(xref);
    Array* srcArr = new Array(xref);
    // Empty src array
    srcNameTree->add("Names", Object(srcArr));

    Dict* mergeNameTree = new Dict(xref);
    Array* mergeArr = new Array(xref);
    mergeArr->add(Object(std::make_unique<GooString>("x")));
    mergeArr->add(Object(Ref{.num = 7, .gen = 0}));
    mergeNameTree->add("Names", Object(mergeArr));

    int numOffset = 20;
    PDFDoc doc;

    doMergeNameTree(&doc, xref, countRef, 0, 1, srcNameTree, mergeNameTree, numOffset);

    Object namesObj = srcNameTree->lookup("Names");
    ASSERT_TRUE(namesObj.isArray());
    EXPECT_EQ(namesObj.arrayGetLength(), 2);

    if (namesObj.arrayGetLength() >= 2) {
        const Object& k = namesObj.arrayGetNF(0);
        EXPECT_TRUE(k.isString());
        if (k.isString()) EXPECT_EQ(k.getString()->toStr(), "x");

        const Object& v = namesObj.arrayGetNF(1);
        EXPECT_TRUE(v.isRef());
        if (v.isRef()) EXPECT_EQ(v.getRef().num, 7 + numOffset);
    }

    delete srcNameTree;
    delete mergeNameTree;
}

// Test: Duplicate keys - merge key same as src key, merge entry should be skipped
TEST_F(DoMergeNameTreeTest_2698, DuplicateKeysSkipsMergeEntry_2698) {
    Dict* srcNameTree = new Dict(xref);
    Array* srcArr = new Array(xref);
    srcArr->add(Object(std::make_unique<GooString>("dup")));
    srcArr->add(Object(Ref{.num = 1, .gen = 0}));
    srcNameTree->add("Names", Object(srcArr));

    Dict* mergeNameTree = new Dict(xref);
    Array* mergeArr = new Array(xref);
    mergeArr->add(Object(std::make_unique<GooString>("dup")));
    mergeArr->add(Object(Ref{.num = 99, .gen = 0}));
    mergeNameTree->add("Names", Object(mergeArr));

    int numOffset = 10;
    PDFDoc doc;

    doMergeNameTree(&doc, xref, countRef, 0, 1, srcNameTree, mergeNameTree, numOffset);

    Object namesObj = srcNameTree->lookup("Names");
    ASSERT_TRUE(namesObj.isArray());
    // Should have only 1 pair (2 entries) - src wins, merge duplicate skipped
    EXPECT_EQ(namesObj.arrayGetLength(), 2);

    if (namesObj.arrayGetLength() >= 2) {
        const Object& v = namesObj.arrayGetNF(1);
        EXPECT_TRUE(v.isRef());
        if (v.isRef()) EXPECT_EQ(v.getRef().num, 1); // src ref, not merge ref
    }

    delete srcNameTree;
    delete mergeNameTree;
}

// Test: Neither has Names array - nothing happens
TEST_F(DoMergeNameTreeTest_2698, NeitherHasNames_2698) {
    Dict* srcNameTree = new Dict(xref);
    Dict* mergeNameTree = new Dict(xref);

    PDFDoc doc;

    // Should not crash
    doMergeNameTree(&doc, xref, countRef, 0, 1, srcNameTree, mergeNameTree, 0);

    // src should still not have Names
    Object namesObj = srcNameTree->lookup("Names");
    EXPECT_TRUE(namesObj.isNull());

    delete srcNameTree;
    delete mergeNameTree;
}

// Test: Src has Names but merge does not
TEST_F(DoMergeNameTreeTest_2698, SrcHasNamesMergeDoesNot_2698) {
    Dict* srcNameTree = new Dict(xref);
    Array* srcArr = new Array(xref);
    srcArr->add(Object(std::make_unique<GooString>("existing")));
    srcArr->add(Object(Ref{.num = 3, .gen = 0}));
    srcNameTree->add("Names", Object(srcArr));

    Dict* mergeNameTree = new Dict(xref);
    // No "Names" in merge

    PDFDoc doc;

    doMergeNameTree(&doc, xref, countRef, 0, 1, srcNameTree, mergeNameTree, 0);

    // Original Names should remain unchanged
    Object namesObj = srcNameTree->lookup("Names");
    ASSERT_TRUE(namesObj.isArray());
    EXPECT_EQ(namesObj.arrayGetLength(), 2);

    delete srcNameTree;
    delete mergeNameTree;
}

// Test: numOffset is zero
TEST_F(DoMergeNameTreeTest_2698, NumOffsetZero_2698) {
    Dict* srcNameTree = new Dict(xref);
    // No Names in src (null case)

    Dict* mergeNameTree = new Dict(xref);
    Array* mergeArr = new Array(xref);
    mergeArr->add(Object(std::make_unique<GooString>("item")));
    mergeArr->add(Object(Ref{.num = 42, .gen = 3}));
    mergeNameTree->add("Names", Object(mergeArr));

    PDFDoc doc;

    doMergeNameTree(&doc, xref, countRef, 0, 1, srcNameTree, mergeNameTree, 0);

    Object namesObj = srcNameTree->lookup("Names");
    ASSERT_TRUE(namesObj.isArray());
    EXPECT_EQ(namesObj.arrayGetLength(), 2);

    if (namesObj.arrayGetLength() >= 2) {
        const Object& v = namesObj.arrayGetNF(1);
        EXPECT_TRUE(v.isRef());
        if (v.isRef()) {
            EXPECT_EQ(v.getRef().num, 42); // 42 + 0
            EXPECT_EQ(v.getRef().gen, 3);
        }
    }

    delete srcNameTree;
    delete mergeNameTree;
}

// Test: Large numOffset
TEST_F(DoMergeNameTreeTest_2698, LargeNumOffset_2698) {
    Dict* srcNameTree = new Dict(xref);

    Dict* mergeNameTree = new Dict(xref);
    Array* mergeArr = new Array(xref);
    mergeArr->add(Object(std::make_unique<GooString>("test")));
    mergeArr->add(Object(Ref{.num = 1, .gen = 0}));
    mergeNameTree->add("Names", Object(mergeArr));

    int numOffset = 1000000;
    PDFDoc doc;

    doMergeNameTree(&doc, xref, countRef, 0, 1, srcNameTree, mergeNameTree, numOffset);

    Object namesObj = srcNameTree->lookup("Names");
    ASSERT_TRUE(namesObj.isArray());

    if (namesObj.arrayGetLength() >= 2) {
        const Object& v = namesObj.arrayGetNF(1);
        EXPECT_TRUE(v.isRef());
        if (v.isRef()) EXPECT_EQ(v.getRef().num, 1 + numOffset);
    }

    delete srcNameTree;
    delete mergeNameTree;
}

// Test: Multiple entries all from merge come after all src entries
TEST_F(DoMergeNameTreeTest_2698, AllMergeAfterSrc_2698) {
    Dict* srcNameTree = new Dict(xref);
    Array* srcArr = new Array(xref);
    srcArr->add(Object(std::make_unique<GooString>("a")));
    srcArr->add(Object(Ref{.num = 1, .gen = 0}));
    srcArr->add(Object(std::make_unique<GooString>("b")));
    srcArr->add(Object(Ref{.num = 2, .gen = 0}));
    srcNameTree->add("Names", Object(srcArr));

    Dict* mergeNameTree = new Dict(xref);
    Array* mergeArr = new Array(xref);
    mergeArr->add(Object(std::make_unique<GooString>("x")));
    mergeArr->add(Object(Ref{.num = 10, .gen = 0}));
    mergeArr->add(Object(std::make_unique<GooString>("y")));
    mergeArr->add(Object(Ref{.num = 11, .gen = 0}));
    mergeNameTree->add("Names", Object(mergeArr));

    int numOffset = 5;
    PDFDoc doc;

    doMergeNameTree(&doc, xref, countRef, 0, 1, srcNameTree, mergeNameTree, numOffset);

    Object namesObj = srcNameTree->lookup("Names");
    ASSERT_TRUE(namesObj.isArray());
    // a, b from src, then x, y from merge = 4 pairs = 8 entries
    EXPECT_EQ(namesObj.arrayGetLength(), 8);

    // Verify order: a, b, x, y
    if (namesObj.arrayGetLength() >= 8) {
        const Object& k0 = namesObj.arrayGetNF(0);
        if (k0.isString()) EXPECT_EQ(k0.getString()->toStr(), "a");
        const Object& k1 = namesObj.arrayGetNF(2);
        if (k1.isString()) EXPECT_EQ(k1.getString()->toStr(), "b");
        const Object& k2 = namesObj.arrayGetNF(4);
        if (k2.isString()) EXPECT_EQ(k2.getString()->toStr(), "x");
        const Object& k3 = namesObj.arrayGetNF(6);
        if (k3.isString()) EXPECT_EQ(k3.getString()->toStr(), "y");

        // Verify merge refs have offset applied
        const Object& v2 = namesObj.arrayGetNF(5);
        if (v2.isRef()) EXPECT_EQ(v2.getRef().num, 10 + numOffset);
        const Object& v3 = namesObj.arrayGetNF(7);
        if (v3.isRef()) EXPECT_EQ(v3.getRef().num, 11 + numOffset);
    }

    delete srcNameTree;
    delete mergeNameTree;
}

// Test: All merge entries come before all src entries
TEST_F(DoMergeNameTreeTest_2698, AllMergeBeforeSrc_2698) {
    Dict* srcNameTree = new Dict(xref);
    Array* srcArr = new Array(xref);
    srcArr->add(Object(std::make_unique<GooString>("x")));
    srcArr->add(Object(Ref{.num = 1, .gen = 0}));
    srcArr->add(Object(std::make_unique<GooString>("y")));
    srcArr->add(Object(Ref{.num = 2, .gen = 0}));
    srcNameTree->add("Names", Object(srcArr));

    Dict* mergeNameTree = new Dict(xref);
    Array* mergeArr = new Array(xref);
    mergeArr->add(Object(std::make_unique<GooString>("a")));
    mergeArr->add(Object(Ref{.num = 10, .gen = 0}));
    mergeArr->add(Object(std::make_unique<GooString>("b")));
    mergeArr->add(Object(Ref{.num = 11, .gen = 0}));
    mergeNameTree->add("Names", Object(mergeArr));

    int numOffset = 5;
    PDFDoc doc;

    doMergeNameTree(&doc, xref, countRef, 0, 1, srcNameTree, mergeNameTree, numOffset);

    Object namesObj = srcNameTree->lookup("Names");
    ASSERT_TRUE(namesObj.isArray());
    EXPECT_EQ(namesObj.arrayGetLength(), 8);

    // Order should be: a, b, x, y
    if (namesObj.arrayGetLength() >= 8) {
        const Object& k0 = namesObj.arrayGetNF(0);
        if (k0.isString()) EXPECT_EQ(k0.getString()->toStr(), "a");
        const Object& k1 = namesObj.arrayGetNF(2);
        if (k1.isString()) EXPECT_EQ(k1.getString()->toStr(), "b");
        const Object& k2 = namesObj.arrayGetNF(4);
        if (k2.isString()) EXPECT_EQ(k2.getString()->toStr(), "x");
        const Object& k3 = namesObj.arrayGetNF(6);
        if (k3.isString()) EXPECT_EQ(k3.getString()->toStr(), "y");
    }

    delete srcNameTree;
    delete mergeNameTree;
}

// Test: Single entry in each
TEST_F(DoMergeNameTreeTest_2698, SingleEntryEach_2698) {
    Dict* srcNameTree = new Dict(xref);
    Array* srcArr = new Array(xref);
    srcArr->add(Object(std::make_unique<GooString>("second")));
    srcArr->add(Object(Ref{.num = 1, .gen = 0}));
    srcNameTree->add("Names", Object(srcArr));

    Dict* mergeNameTree = new Dict(xref);
    Array* mergeArr = new Array(xref);
    mergeArr->add(Object(std::make_unique<GooString>("first")));
    mergeArr->add(Object(Ref{.num = 2, .gen = 0}));
    mergeNameTree->add("Names", Object(mergeArr));

    int numOffset = 10;
    PDFDoc doc;

    doMergeNameTree(&doc, xref, countRef, 0, 1, srcNameTree, mergeNameTree, numOffset);

    Object namesObj = srcNameTree->lookup("Names");
    ASSERT_TRUE(namesObj.isArray());
    EXPECT_EQ(namesObj.arrayGetLength(), 4);

    if (namesObj.arrayGetLength() >= 4) {
        const Object& k0 = namesObj.arrayGetNF(0);
        if (k0.isString()) EXPECT_EQ(k0.getString()->toStr(), "first");
        const Object& k1 = namesObj.arrayGetNF(2);
        if (k1.isString()) EXPECT_EQ(k1.getString()->toStr(), "second");
    }

    delete srcNameTree;
    delete mergeNameTree;
}

// Test: Gen values are preserved from merge
TEST_F(DoMergeNameTreeTest_2698, GenValuesPreserved_2698) {
    Dict* srcNameTree = new Dict(xref);

    Dict* mergeNameTree = new Dict(xref);
    Array* mergeArr = new Array(xref);
    mergeArr->add(Object(std::make_unique<GooString>("key")));
    mergeArr->add(Object(Ref{.num = 5, .gen = 7}));
    mergeNameTree->add("Names", Object(mergeArr));

    int numOffset = 100;
    PDFDoc doc;

    doMergeNameTree(&doc, xref, countRef, 0, 1, srcNameTree, mergeNameTree, numOffset);

    Object namesObj = srcNameTree->lookup("Names");
    ASSERT_TRUE(namesObj.isArray());

    if (namesObj.arrayGetLength() >= 2) {
        const Object& v = namesObj.arrayGetNF(1);
        EXPECT_TRUE(v.isRef());
        if (v.isRef()) {
            EXPECT_EQ(v.getRef().num, 105); // 5 + 100
            EXPECT_EQ(v.getRef().gen, 7);   // gen preserved
        }
    }

    delete srcNameTree;
    delete mergeNameTree;
}
