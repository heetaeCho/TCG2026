// File: doMergeNameDict_test_2699.cc
#include <gtest/gtest.h>

#include <string>
#include <vector>

// --- Test seam to observe interaction with doMergeNameTree ---
// We treat doMergeNameTree as an external collaborator of doMergeNameDict for testing purposes.
namespace {
struct MergeNameTreeCall_2699 {
  PDFDoc *doc = nullptr;
  XRef *srcXRef = nullptr;
  XRef *countRef = nullptr;
  int oldRefNum = 0;
  int newRefNum = 0;
  Dict *srcTree = nullptr;
  Dict *mergeTree = nullptr;
  int numOffset = 0;
};

static std::vector<MergeNameTreeCall_2699> g_calls_2699;

static void ResetCalls_2699() { g_calls_2699.clear(); }

// Stub that records calls.
void doMergeNameTree_Stub_2699(PDFDoc *doc,
                               XRef *srcXRef,
                               XRef *countRef,
                               int oldRefNum,
                               int newRefNum,
                               Dict *srcNameTree,
                               Dict *mergeNameTree,
                               int numOffset)
{
  MergeNameTreeCall_2699 call;
  call.doc = doc;
  call.srcXRef = srcXRef;
  call.countRef = countRef;
  call.oldRefNum = oldRefNum;
  call.newRefNum = newRefNum;
  call.srcTree = srcNameTree;
  call.mergeTree = mergeNameTree;
  call.numOffset = numOffset;
  g_calls_2699.push_back(call);
}
} // namespace

// Rename internal symbols in the included TU:
// - Avoid linking a "main" from pdfunite.cc (if present).
// - Redirect doMergeNameTree to our stub.
// - Remove "static" so we can call doMergeNameDict from tests.
#define main pdfunite_main_2699
#define doMergeNameTree doMergeNameTree_Stub_2699
#define static

// Include the implementation under test.
#include "utils/pdfunite.cc"

#undef static
#undef doMergeNameTree
#undef main

namespace {

class DoMergeNameDictTest_2699 : public ::testing::Test {
protected:
  void SetUp() override { ResetCalls_2699(); }
  void TearDown() override { ResetCalls_2699(); }

  // Helpers to build Dict/Object structures with minimal dependencies.
  Object MakeDictObject_2699(XRef *xref) {
    return Object(new Dict(xref));
  }
};

TEST_F(DoMergeNameDictTest_2699, EmptyMergeDictDoesNothing_2699)
{
  XRef xref;
  Dict srcNameDict(&xref);
  Dict mergeNameDict(&xref);

  PDFDoc *doc = nullptr;
  XRef *srcXRef = &xref;
  XRef *countRef = &xref;

  ASSERT_EQ(srcNameDict.getLength(), 0);
  ASSERT_EQ(mergeNameDict.getLength(), 0);

  doMergeNameDict(doc, srcXRef, countRef, /*oldRefNum=*/1, /*newRefNum=*/2,
                  &srcNameDict, &mergeNameDict, /*numOffset=*/0);

  EXPECT_TRUE(g_calls_2699.empty());
  EXPECT_EQ(srcNameDict.getLength(), 0);
}

TEST_F(DoMergeNameDictTest_2699, NonDictMergeEntryDoesNotTriggerMerge_2699)
{
  XRef xref;
  Dict srcNameDict(&xref);
  Dict mergeNameDict(&xref);

  // mergeNameDict["Dests"] = "not-a-dict"
  mergeNameDict.add("Dests", Object(std::string("not-a-dict")));

  PDFDoc *doc = nullptr;
  XRef *srcXRef = &xref;
  XRef *countRef = &xref;

  // Key doesn't exist in src -> lookup should be null, but merge is not dict, so no merge.
  ASSERT_TRUE(srcNameDict.lookup("Dests", /*recursion=*/0).isNull());

  doMergeNameDict(doc, srcXRef, countRef, /*oldRefNum=*/10, /*newRefNum=*/20,
                  &srcNameDict, &mergeNameDict, /*numOffset=*/5);

  EXPECT_TRUE(g_calls_2699.empty());
  // Still missing
  EXPECT_TRUE(srcNameDict.lookup("Dests", /*recursion=*/0).isNull());
}

TEST_F(DoMergeNameDictTest_2699, DictInBothSrcAndMergeCallsDoMergeNameTree_2699)
{
  XRef xref;
  Dict srcNameDict(&xref);
  Dict mergeNameDict(&xref);

  // srcNameDict["Dests"] = dict
  Object srcTreeObj = MakeDictObject_2699(&xref);
  Dict *srcTreePtr = srcTreeObj.getDict();
  ASSERT_NE(srcTreePtr, nullptr);
  srcNameDict.add("Dests", std::move(srcTreeObj));

  // mergeNameDict["Dests"] = dict
  Object mergeTreeObj = MakeDictObject_2699(&xref);
  Dict *mergeTreePtr = mergeTreeObj.getDict();
  ASSERT_NE(mergeTreePtr, nullptr);
  mergeNameDict.add("Dests", std::move(mergeTreeObj));

  PDFDoc *doc = nullptr;
  XRef *srcXRef = &xref;
  XRef *countRef = &xref;

  doMergeNameDict(doc, srcXRef, countRef, /*oldRefNum=*/3, /*newRefNum=*/4,
                  &srcNameDict, &mergeNameDict, /*numOffset=*/7);

  ASSERT_EQ(g_calls_2699.size(), 1u);
  EXPECT_EQ(g_calls_2699[0].doc, doc);
  EXPECT_EQ(g_calls_2699[0].srcXRef, srcXRef);
  EXPECT_EQ(g_calls_2699[0].countRef, countRef);
  EXPECT_EQ(g_calls_2699[0].oldRefNum, 3);
  EXPECT_EQ(g_calls_2699[0].newRefNum, 4);
  EXPECT_EQ(g_calls_2699[0].srcTree, srcTreePtr);
  EXPECT_EQ(g_calls_2699[0].mergeTree, mergeTreePtr);
  EXPECT_EQ(g_calls_2699[0].numOffset, 7);

  // The key should still exist and be a dict.
  Object after = srcNameDict.lookup("Dests", /*recursion=*/0);
  EXPECT_TRUE(after.isDict());
}

TEST_F(DoMergeNameDictTest_2699, MissingSrcKeyAndDictInMergeCreatesNewDictAndCallsMerge_2699)
{
  XRef xref;
  Dict srcNameDict(&xref);
  Dict mergeNameDict(&xref);

  // mergeNameDict["EmbeddedFiles"] = dict
  Object mergeTreeObj = MakeDictObject_2699(&xref);
  Dict *mergeTreePtr = mergeTreeObj.getDict();
  ASSERT_NE(mergeTreePtr, nullptr);
  mergeNameDict.add("EmbeddedFiles", std::move(mergeTreeObj));

  // srcNameDict does not have "EmbeddedFiles"
  ASSERT_TRUE(srcNameDict.lookup("EmbeddedFiles", /*recursion=*/0).isNull());

  PDFDoc *doc = nullptr;
  XRef *srcXRef = &xref;
  XRef *countRef = &xref;

  doMergeNameDict(doc, srcXRef, countRef, /*oldRefNum=*/100, /*newRefNum=*/200,
                  &srcNameDict, &mergeNameDict, /*numOffset=*/9);

  // It should have called the collaborator once.
  ASSERT_EQ(g_calls_2699.size(), 1u);
  EXPECT_EQ(g_calls_2699[0].oldRefNum, 100);
  EXPECT_EQ(g_calls_2699[0].newRefNum, 200);
  EXPECT_EQ(g_calls_2699[0].mergeTree, mergeTreePtr);
  EXPECT_EQ(g_calls_2699[0].numOffset, 9);

  // And srcNameDict should now have the key with a dict value.
  Object after = srcNameDict.lookup("EmbeddedFiles", /*recursion=*/0);
  ASSERT_TRUE(after.isDict());
  Dict *newlyCreatedSrcTree = after.getDict();
  ASSERT_NE(newlyCreatedSrcTree, nullptr);

  // The call should have been made with the newly created dict from srcNameDict.
  EXPECT_EQ(g_calls_2699[0].srcTree, newlyCreatedSrcTree);
}

TEST_F(DoMergeNameDictTest_2699, MultipleKeysOnlyDictEntriesAreMerged_2699)
{
  XRef xref;
  Dict srcNameDict(&xref);
  Dict mergeNameDict(&xref);

  // merge has:
  //  - "Dests" => dict (should merge; src missing so should create + call)
  //  - "JavaScript" => string (should NOT merge)
  //  - "Pages" => dict (should merge; src already dict so call)
  Object mergeDestsObj = MakeDictObject_2699(&xref);
  Dict *mergeDestsPtr = mergeDestsObj.getDict();
  ASSERT_NE(mergeDestsPtr, nullptr);
  mergeNameDict.add("Dests", std::move(mergeDestsObj));

  mergeNameDict.add("JavaScript", Object(std::string("noop")));

  Object mergePagesObj = MakeDictObject_2699(&xref);
  Dict *mergePagesPtr = mergePagesObj.getDict();
  ASSERT_NE(mergePagesPtr, nullptr);
  mergeNameDict.add("Pages", std::move(mergePagesObj));

  Object srcPagesObj = MakeDictObject_2699(&xref);
  Dict *srcPagesPtr = srcPagesObj.getDict();
  ASSERT_NE(srcPagesPtr, nullptr);
  srcNameDict.add("Pages", std::move(srcPagesObj));

  PDFDoc *doc = nullptr;
  XRef *srcXRef = &xref;
  XRef *countRef = &xref;

  doMergeNameDict(doc, srcXRef, countRef, /*oldRefNum=*/11, /*newRefNum=*/12,
                  &srcNameDict, &mergeNameDict, /*numOffset=*/13);

  // Expected merges: "Dests" and "Pages" => 2 calls.
  ASSERT_EQ(g_calls_2699.size(), 2u);

  // Verify we got one call for "Pages" using existing src dict.
  bool sawPages = false;
  bool sawDests = false;
  for (const auto &c : g_calls_2699) {
    if (c.mergeTree == mergePagesPtr) {
      sawPages = true;
      EXPECT_EQ(c.srcTree, srcPagesPtr);
      EXPECT_EQ(c.oldRefNum, 11);
      EXPECT_EQ(c.newRefNum, 12);
      EXPECT_EQ(c.numOffset, 13);
    }
    if (c.mergeTree == mergeDestsPtr) {
      sawDests = true;
      // For Dests, src was missing; it should now exist as dict in srcNameDict.
      Object afterDests = srcNameDict.lookup("Dests", /*recursion=*/0);
      ASSERT_TRUE(afterDests.isDict());
      EXPECT_EQ(c.srcTree, afterDests.getDict());
    }
  }
  EXPECT_TRUE(sawPages);
  EXPECT_TRUE(sawDests);

  // "JavaScript" should not have been added to srcNameDict by doMergeNameDict.
  EXPECT_TRUE(srcNameDict.lookup("JavaScript", /*recursion=*/0).isNull());
}

} // namespace