// File: doMergeNameTree_test_2698.cc
#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "poppler/Array.h"
#include "poppler/Dict.h"
#include "poppler/Object.h"
#include "poppler/PDFDoc.h"
#include "poppler/XRef.h"
#include "goo/GooString.h"

// pdfunite.cc is a utility with (typically) its own main(). Rename it away so we can include it.
#define main pdfunite_main_disabled_2698
#include "utils/pdfunite.cc"
#undef main

namespace {

class DoMergeNameTreeTest_2698 : public ::testing::Test {
protected:
    static Object MakeStringObj(const char *s)
    {
        return Object(std::make_unique<GooString>(s));
    }

    static Object MakeRefObj(int num, int gen)
    {
        return Object(Ref{ num, gen });
    }

    static Array *MakeNamesArray(XRef *xref, const std::vector<std::pair<std::string, Ref>> &pairs)
    {
        auto *arr = new Array(xref);
        for (const auto &kv : pairs) {
            arr->add(Object(std::make_unique<GooString>(kv.first)));
            arr->add(Object(Ref{ kv.second.num, kv.second.gen }));
        }
        return arr;
    }

    static std::vector<std::pair<std::string, Ref>> ReadNamesArray(Dict *tree)
    {
        std::vector<std::pair<std::string, Ref>> out;

        Object namesObj = tree->lookup("Names", 0);
        if (!namesObj.isArray()) {
            return out;
        }

        Array *arr = namesObj.getArray();
        const int len = arr->getLength();
        for (int i = 0; i + 1 < len; i += 2) {
            const Object &k = arr->getNF(i);
            const Object &v = arr->getNF(i + 1);
            if (k.isString() && v.isRef()) {
                out.emplace_back(k.getString()->toStr(), v.getRef());
            }
        }
        return out;
    }

    static void ExpectPairsEq(const std::vector<std::pair<std::string, Ref>> &actual,
                             const std::vector<std::pair<std::string, Ref>> &expected)
    {
        ASSERT_EQ(actual.size(), expected.size());
        for (size_t i = 0; i < expected.size(); ++i) {
            EXPECT_EQ(actual[i].first, expected[i].first) << "index=" << i;
            EXPECT_EQ(actual[i].second.num, expected[i].second.num) << "index=" << i;
            EXPECT_EQ(actual[i].second.gen, expected[i].second.gen) << "index=" << i;
        }
    }
};

TEST_F(DoMergeNameTreeTest_2698, MergesAndSortsAndOffsetsMergeRefs_DedupsSameKey_2698)
{
    XRef srcXRef;
    XRef countRef;

    // src: B->(10,0), D->(11,0)
    Dict srcNameTree(&srcXRef);
    srcNameTree.set(
        "Names",
        Object(MakeNamesArray(&srcXRef,
                              { { "B", Ref{ 10, 0 } }, { "D", Ref{ 11, 0 } } })));

    // merge: A->(1,0), C->(2,0), D->(3,0), E->(4,0)
    Dict mergeNameTree(&srcXRef);
    mergeNameTree.set(
        "Names",
        Object(MakeNamesArray(&srcXRef,
                              { { "A", Ref{ 1, 0 } },
                                { "C", Ref{ 2, 0 } },
                                { "D", Ref{ 3, 0 } }, // should be deduped against src "D"
                                { "E", Ref{ 4, 0 } } })));

    // Snapshot merge tree "Names" to ensure it's not modified by this helper.
    const auto mergeBefore = ReadNamesArray(&mergeNameTree);

    // Use an ErrorPDFDoc to avoid needing a real PDF file.
    auto doc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("dummy.pdf"));
    ASSERT_TRUE(doc);

    const int oldRefNum = 1;
    const int newRefNum = 2;
    const int numOffset = 100;

    doMergeNameTree(doc.get(), &srcXRef, &countRef, oldRefNum, newRefNum,
                    &srcNameTree, &mergeNameTree, numOffset);

    // Expect merged keys are ordered and merge refs are offset by numOffset.
    // Duplicate key "D" should come from src (ref 11,0) and merge's D should be skipped.
    const auto actual = ReadNamesArray(&srcNameTree);
    ExpectPairsEq(actual,
                  { { "A", Ref{ 101, 0 } },
                    { "B", Ref{ 10, 0 } },
                    { "C", Ref{ 102, 0 } },
                    { "D", Ref{ 11, 0 } },
                    { "E", Ref{ 104, 0 } } });

    // mergeNameTree should remain unchanged from the perspective of its "Names" content.
    const auto mergeAfter = ReadNamesArray(&mergeNameTree);
    ExpectPairsEq(mergeAfter, mergeBefore);
}

TEST_F(DoMergeNameTreeTest_2698, WhenSrcNamesNull_CopiesMergeWithOffset_2698)
{
    XRef srcXRef;
    XRef countRef;

    Dict srcNameTree(&srcXRef); // no "Names" key => treated as null
    Dict mergeNameTree(&srcXRef);
    mergeNameTree.set(
        "Names",
        Object(MakeNamesArray(&srcXRef,
                              { { "K1", Ref{ 7, 1 } }, { "K2", Ref{ 8, 2 } } })));

    auto doc = PDFDoc::ErrorPDFDoc(2, std::make_unique<GooString>("dummy2.pdf"));
    ASSERT_TRUE(doc);

    doMergeNameTree(doc.get(), &srcXRef, &countRef,
                    /*oldRefNum=*/5, /*newRefNum=*/6,
                    &srcNameTree, &mergeNameTree,
                    /*numOffset=*/50);

    const auto actual = ReadNamesArray(&srcNameTree);
    ExpectPairsEq(actual, { { "K1", Ref{ 57, 1 } }, { "K2", Ref{ 58, 2 } } });
}

TEST_F(DoMergeNameTreeTest_2698, SkipsInvalidPairsAndDoesNotCrashOnOddLength_2698)
{
    XRef srcXRef;
    XRef countRef;

    Dict srcNameTree(&srcXRef);
    {
        // Build: ["A", ref(1,0), 123, ref(9,0), "B"]  -> includes invalid key (int) and odd tail.
        auto *arr = new Array(&srcXRef);
        arr->add(MakeStringObj("A"));
        arr->add(MakeRefObj(1, 0));
        arr->add(Object(123));          // invalid key
        arr->add(MakeRefObj(9, 0));     // would be ignored due to invalid key
        arr->add(MakeStringObj("B"));   // odd tail without value; should not crash
        srcNameTree.set("Names", Object(arr));
    }

    Dict mergeNameTree(&srcXRef);
    {
        // Build: ["0", ref(2,0), "C", 3] -> invalid value (int) for "C"
        auto *arr = new Array(&srcXRef);
        arr->add(MakeStringObj("0"));
        arr->add(MakeRefObj(2, 0));
        arr->add(MakeStringObj("C"));
        arr->add(Object(3)); // invalid value
        mergeNameTree.set("Names", Object(arr));
    }

    auto doc = PDFDoc::ErrorPDFDoc(3, std::make_unique<GooString>("dummy3.pdf"));
    ASSERT_TRUE(doc);

    doMergeNameTree(doc.get(), &srcXRef, &countRef,
                    /*oldRefNum=*/0, /*newRefNum=*/0,
                    &srcNameTree, &mergeNameTree,
                    /*numOffset=*/10);

    // Expected behavior observable through interface:
    // - Only valid (string, ref) pairs are preserved/merged.
    // - merge's "0" ref is offset; invalid "C" pair is skipped; invalid/odd entries in src skipped.
    const auto actual = ReadNamesArray(&srcNameTree);
    ExpectPairsEq(actual, { { "0", Ref{ 12, 0 } }, { "A", Ref{ 1, 0 } } });
}

TEST_F(DoMergeNameTreeTest_2698, EmptyMergeArray_KeepsSrcPairs_2698)
{
    XRef srcXRef;
    XRef countRef;

    Dict srcNameTree(&srcXRef);
    srcNameTree.set(
        "Names",
        Object(MakeNamesArray(&srcXRef,
                              { { "X", Ref{ 10, 0 } }, { "Y", Ref{ 11, 0 } } })));

    Dict mergeNameTree(&srcXRef);
    mergeNameTree.set("Names", Object(new Array(&srcXRef))); // empty

    auto doc = PDFDoc::ErrorPDFDoc(4, std::make_unique<GooString>("dummy4.pdf"));
    ASSERT_TRUE(doc);

    doMergeNameTree(doc.get(), &srcXRef, &countRef,
                    /*oldRefNum=*/1, /*newRefNum=*/2,
                    &srcNameTree, &mergeNameTree,
                    /*numOffset=*/999);

    const auto actual = ReadNamesArray(&srcNameTree);
    ExpectPairsEq(actual, { { "X", Ref{ 10, 0 } }, { "Y", Ref{ 11, 0 } } });
}

TEST_F(DoMergeNameTreeTest_2698, NonArrayMergeNames_DoesNotModifySrc_2698)
{
    XRef srcXRef;
    XRef countRef;

    Dict srcNameTree(&srcXRef);
    srcNameTree.set(
        "Names",
        Object(MakeNamesArray(&srcXRef, { { "A", Ref{ 1, 0 } } })));

    Dict mergeNameTree(&srcXRef);
    // Set "Names" to a non-array object.
    mergeNameTree.set("Names", Object(42));

    const auto before = ReadNamesArray(&srcNameTree);

    auto doc = PDFDoc::ErrorPDFDoc(5, std::make_unique<GooString>("dummy5.pdf"));
    ASSERT_TRUE(doc);

    doMergeNameTree(doc.get(), &srcXRef, &countRef,
                    /*oldRefNum=*/0, /*newRefNum=*/0,
                    &srcNameTree, &mergeNameTree,
                    /*numOffset=*/1);

    const auto after = ReadNamesArray(&srcNameTree);
    ExpectPairsEq(after, before);
}

} // namespace