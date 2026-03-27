#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"



using namespace testing;



class GfxIndexedColorSpaceTest_474 : public Test {

protected:

    std::unique_ptr<GfxColorSpace> base;

    int indexHigh = 255;

    std::vector<std::unique_ptr<GfxSeparationColorSpace>> separationList;

    size_t maxSepComps = 0;



    void SetUp() override {

        base = std::make_unique<GfxColorSpace>();

    }

};



TEST_F(GfxIndexedColorSpaceTest_474, CreateMappingWithEmptySeparationList_474) {

    GfxIndexedColorSpace indexedColorSpace(std::move(base), indexHigh);

    EXPECT_NO_THROW(indexedColorSpace.createMapping(&separationList, maxSepComps));

}



TEST_F(GfxIndexedColorSpaceTest_474, CreateMappingWithNonEmptySeparationList_474) {

    separationList.push_back(std::make_unique<GfxSeparationColorSpace>());

    GfxIndexedColorSpace indexedColorSpace(std::move(base), indexHigh);

    EXPECT_NO_THROW(indexedColorSpace.createMapping(&separationList, maxSepComps));

}



TEST_F(GfxIndexedColorSpaceTest_474, CreateMappingWithMaxSepCompsZero_474) {

    GfxIndexedColorSpace indexedColorSpace(std::move(base), indexHigh);

    EXPECT_NO_THROW(indexedColorSpace.createMapping(&separationList, maxSepComps));

}



TEST_F(GfxIndexedColorSpaceTest_474, CreateMappingWithMaxSepCompsNonZero_474) {

    maxSepComps = 1;

    separationList.push_back(std::make_unique<GfxSeparationColorSpace>());

    GfxIndexedColorSpace indexedColorSpace(std::move(base), indexHigh);

    EXPECT_NO_THROW(indexedColorSpace.createMapping(&separationList, maxSepComps));

}



TEST_F(GfxIndexedColorSpaceTest_474, CreateMappingBoundaryCondition_474) {

    separationList.push_back(std::make_unique<GfxSeparationColorSpace>());

    GfxIndexedColorSpace indexedColorSpace(std::move(base), indexHigh);

    EXPECT_NO_THROW(indexedColorSpace.createMapping(&separationList, 0));

}
