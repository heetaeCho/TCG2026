#include <gtest/gtest.h>

#include "CMap.h"



// Assuming GooString and other dependencies are properly included and linked



class CMapTest : public ::testing::Test {

protected:

    std::unique_ptr<GooString> collectionName = std::make_unique<GooString>("SampleCollection");

    std::shared_ptr<CMap> cmap;



    void SetUp() override {

        cmap = CMap::parse(collectionName->getCString(), nullptr);

    }

};



TEST_F(CMapTest_1502, GetCollection_ReturnsCorrectCollection_1502) {

    EXPECT_EQ(cmap->getCollection()->getCString(), "SampleCollection");

}



TEST_F(CMapTest_1502, Match_ReturnsTrueForMatchingNames_1502) {

    EXPECT_TRUE(cmap->match("SampleCollection", ""));

}



TEST_F(CMapTest_1502, Match_ReturnsFalseForNonMatchingNames_1502) {

    EXPECT_FALSE(cmap->match("DifferentCollection", "SomeCMapName"));

}



// Assuming getCMapName and getWMode are similar to getCollection, we can add tests for them as well

TEST_F(CMapTest_1502, GetCMapName_ReturnsCorrectCMapName_1502) {

    // Since the CMapName is not initialized in the setup, we cannot assert a specific value.

    // This test assumes that getCMapName returns a non-null pointer if the CMap was constructed correctly.

    EXPECT_NE(cmap->getCMapName(), nullptr);

}



TEST_F(CMapTest_1502, GetWMode_ReturnsDefaultWritingMode_1502) {

    // Assuming default WritingMode is 0 (Horizontal)

    EXPECT_EQ(static_cast<int>(cmap->getWMode()), 0);

}
