#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/CMap.h"

#include <memory>

#include <string>



// Mock class for GfxFont::WritingMode if necessary

namespace GfxFont {

    enum WritingMode { Horizontal = 0, Vertical };

}



class CMapTest : public ::testing::Test {

protected:

    std::shared_ptr<CMap> cMap;

};



TEST_F(CMapTest_1504, GetWMode_DefaultConstruction_1504) {

    auto collectionA = std::make_unique<GooString>("collection");

    auto cMapNameA = std::make_unique<GooString>("cMapName");

    cMap = std::shared_ptr<CMap>(new CMap(std::move(collectionA), std::move(cMapNameA)));

    EXPECT_EQ(cMap->getWMode(), GfxFont::Horizontal);

}



TEST_F(CMapTest_1504, GetWMode_CustomConstruction_1504) {

    auto collectionA = std::make_unique<GooString>("collection");

    auto cMapNameA = std::make_unique<GooString>("cMapName");

    GfxFont::WritingMode wModeA = GfxFont::Vertical;

    cMap = std::shared_ptr<CMap>(new CMap(std::move(collectionA), std::move(cMapNameA), wModeA));

    EXPECT_EQ(cMap->getWMode(), GfxFont::Vertical);

}



TEST_F(CMapTest_1504, GetCollection_DefaultConstruction_1504) {

    auto collectionA = std::make_unique<GooString>("collection");

    auto cMapNameA = std::make_unique<GooString>("cMapName");

    cMap = std::shared_ptr<CMap>(new CMap(std::move(collectionA), std::move(cMapNameA)));

    EXPECT_EQ(cMap->getCollection()->cmpN("collection", 10), 0);

}



TEST_F(CMapTest_1504, GetCMapName_DefaultConstruction_1504) {

    auto collectionA = std::make_unique<GooString>("collection");

    auto cMapNameA = std::make_unique<GooString>("cMapName");

    cMap = std::shared_ptr<CMap>(new CMap(std::move(collectionA), std::move(cMapNameA)));

    EXPECT_EQ(cMap->getCMapName()->cmpN("cMapName", 8), 0);

}



TEST_F(CMapTest_1504, Match_SameCollectionAndCMapName_1504) {

    auto collectionA = std::make_unique<GooString>("collection");

    auto cMapNameA = std::make_unique<GooString>("cMapName");

    cMap = std::shared_ptr<CMap>(new CMap(std::move(collectionA), std::move(cMapNameA)));

    EXPECT_TRUE(cMap->match("collection", "cMapName"));

}



TEST_F(CMapTest_1504, Match_DifferentCollection_1504) {

    auto collectionA = std::make_unique<GooString>("collection");

    auto cMapNameA = std::make_unique<GooString>("cMapName");

    cMap = std::shared_ptr<CMap>(new CMap(std::move(collectionA), std::move(cMapNameA)));

    EXPECT_FALSE(cMap->match("differentCollection", "cMapName"));

}



TEST_F(CMapTest_1504, Match_DifferentCMapName_1504) {

    auto collectionA = std::make_unique<GooString>("collection");

    auto cMapNameA = std::make_unique<GooString>("cMapName");

    cMap = std::shared_ptr<CMap>(new CMap(std::move(collectionA), std::move(cMapNameA)));

    EXPECT_FALSE(cMap->match("collection", "differentCMapName"));

}
