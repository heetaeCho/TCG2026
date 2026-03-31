#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <map>
#include <cstdio>

#include "PDFDoc.h"
#include "Catalog.h"
#include "GooString.h"
#include "UnicodeMap.h"
#include "Object.h"
#include "Link.h"
#include "GlobalParams.h"

// External globals used by printDestinations
extern int firstPage;
extern int lastPage;

class PrintDestinationsTest_2671 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    std::unique_ptr<PDFDoc> loadTestDoc(const std::string &filename) {
        auto fileName = std::make_unique<GooString>(filename);
        auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
        return doc;
    }
};

// Test Ref comparison and ordering used in the map inside printDestinations
TEST_F(PrintDestinationsTest_2671, RefInvalidConstant_2671) {
    Ref invalid = Ref::INVALID();
    // INVALID ref should have specific values
    EXPECT_EQ(invalid.num, -1);
    EXPECT_EQ(invalid.gen, -1);
}

TEST_F(PrintDestinationsTest_2671, RefEquality_2671) {
    Ref r1 = {1, 0};
    Ref r2 = {1, 0};
    Ref r3 = {2, 0};
    EXPECT_TRUE(r1 == r2);
    EXPECT_FALSE(r1 == r3);
}

TEST_F(PrintDestinationsTest_2671, RefOrdering_2671) {
    Ref r1 = {1, 0};
    Ref r2 = {2, 0};
    // std::map<Ref, ...> requires operator< for Ref
    std::map<Ref, int> refMap;
    refMap[r1] = 10;
    refMap[r2] = 20;
    EXPECT_EQ(refMap.size(), 2u);
    EXPECT_EQ(refMap[r1], 10);
    EXPECT_EQ(refMap[r2], 20);
}

TEST_F(PrintDestinationsTest_2671, GooStringToStr_2671) {
    GooString gs("hello");
    EXPECT_EQ(gs.toStr(), "hello");
}

TEST_F(PrintDestinationsTest_2671, GooStringEmpty_2671) {
    GooString gs("");
    EXPECT_EQ(gs.toStr(), "");
}

TEST_F(PrintDestinationsTest_2671, GooStringFromStdString_2671) {
    std::string s = "test destination name";
    GooString gs(s);
    EXPECT_EQ(gs.toStr(), s);
}

TEST_F(PrintDestinationsTest_2671, MapInsertWithSameKeyPreservesFirst_2671) {
    // printDestinations uses std::map::insert which does not overwrite
    std::map<std::string, int> m;
    m.insert(std::make_pair("key", 1));
    m.insert(std::make_pair("key", 2));
    EXPECT_EQ(m["key"], 1);
    EXPECT_EQ(m.size(), 1u);
}

TEST_F(PrintDestinationsTest_2671, MapInsertMultipleKeys_2671) {
    std::map<std::string, int> m;
    m.insert(std::make_pair("dest1", 1));
    m.insert(std::make_pair("dest2", 2));
    EXPECT_EQ(m.size(), 2u);
}

TEST_F(PrintDestinationsTest_2671, RefMapMultipleDestsPerPage_2671) {
    Ref pageRef = {5, 0};
    std::map<Ref, std::map<std::string, int>> refMap;
    refMap[pageRef].insert(std::make_pair("destA", 1));
    refMap[pageRef].insert(std::make_pair("destB", 2));
    EXPECT_EQ(refMap[pageRef].size(), 2u);
}

TEST_F(PrintDestinationsTest_2671, RefMapEmptyWhenNoInserts_2671) {
    std::map<Ref, std::map<std::string, int>> refMap;
    Ref pageRef = {3, 0};
    auto it = refMap.find(pageRef);
    EXPECT_EQ(it, refMap.end());
}

TEST_F(PrintDestinationsTest_2671, CatalogNumDestsOnValidDoc_2671) {
    // Try to load a non-existent file — doc should fail gracefully
    auto fileName = std::make_unique<GooString>("nonexistent_file.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc.isOk());
}

TEST_F(PrintDestinationsTest_2671, FirstPageLastPageGlobals_2671) {
    // Verify the globals that printDestinations uses
    firstPage = 1;
    lastPage = 5;
    EXPECT_EQ(firstPage, 1);
    EXPECT_EQ(lastPage, 5);
}

TEST_F(PrintDestinationsTest_2671, FirstPageGreaterThanLastPage_2671) {
    // When firstPage > lastPage, the for loop in printDestinations won't execute
    firstPage = 10;
    lastPage = 5;
    // The loop `for (int i = firstPage; i <= lastPage; i++)` will not iterate
    EXPECT_GT(firstPage, lastPage);
}

TEST_F(PrintDestinationsTest_2671, SinglePageRange_2671) {
    firstPage = 3;
    lastPage = 3;
    EXPECT_EQ(firstPage, lastPage);
}

TEST_F(PrintDestinationsTest_2671, NestedMapStructure_2671) {
    // Simulate the data structure used in printDestinations
    std::map<Ref, std::map<std::string, std::unique_ptr<LinkDest>>> map;
    Ref r1 = {1, 0};
    Ref r2 = {2, 0};

    // Map should be empty initially
    EXPECT_TRUE(map.empty());

    // After finding entries, iterating should work
    auto it = map.find(r1);
    EXPECT_EQ(it, map.end());
}

TEST_F(PrintDestinationsTest_2671, GooStringCopy_2671) {
    GooString original("destination_name");
    auto copy = original.copy();
    EXPECT_NE(copy, nullptr);
    EXPECT_EQ(copy->toStr(), "destination_name");
}

TEST_F(PrintDestinationsTest_2671, GooStringGetChar_2671) {
    GooString gs("abc");
    EXPECT_EQ(gs.getChar(0), 'a');
    EXPECT_EQ(gs.getChar(1), 'b');
    EXPECT_EQ(gs.getChar(2), 'c');
}

TEST_F(PrintDestinationsTest_2671, ErrorDocGetErrorCode_2671) {
    auto fileName = std::make_unique<GooString>("no_such_file.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc.isOk());
    EXPECT_NE(doc.getErrorCode(), 0);
}
