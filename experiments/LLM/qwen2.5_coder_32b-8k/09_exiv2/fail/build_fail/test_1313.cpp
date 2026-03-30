#include <gtest/gtest.h>

#include "exiv2/xmp_exiv2.hpp"



using namespace Exiv2;



class XmpDataTest_1313 : public ::testing::Test {

protected:

    void SetUp() override {

        xmpData = std::make_unique<XmpData>();

        // Adding sample data for testing

        xmpData->add(XmpKey("Xmp.dc.title"), new Value(1));

        xmpData->add(XmpKey("Xmp.dc.description"), new Value(2));

        xmpData->add(XmpKey("Xmp.xmpMM.History"), new Value(3));

        xmpData->add(XmpKey("Xmp.xmpMM.HistoryItem[1]"), new Value(4));

        xmpData->add(XmpKey("Xmp.xmpMM.HistoryItem[2]"), new Value(5));

    }



    void TearDown() override {

        xmpData.reset();

    }



    std::unique_ptr<XmpData> xmpData;

};



TEST_F(XmpDataTest_1313, EraseFamilyRemovesAllMatchingKeys_1313) {

    auto it = xmpData->findKey(XmpKey("Xmp.xmpMM.History"));

    size_t initialCount = xmpData->count();

    xmpData->eraseFamily(it);

    EXPECT_EQ(xmpData->count(), initialCount - 3); // 3 items in the family

}



TEST_F(XmpDataTest_1313, EraseFamilyDoesNothingForNonExistingKey_1313) {

    auto it = xmpData->end();

    size_t initialCount = xmpData->count();

    xmpData->eraseFamily(it);

    EXPECT_EQ(xmpData->count(), initialCount);

}



TEST_F(XmpDataTest_1313, EraseFamilyHandlesSingleElementFamily_1313) {

    auto it = xmpData->findKey(XmpKey("Xmp.dc.title"));

    size_t initialCount = xmpData->count();

    xmpData->eraseFamily(it);

    EXPECT_EQ(xmpData->count(), initialCount - 1); // Only one item in the family

}



TEST_F(XmpDataTest_1313, EraseFamilyBoundaryConditionFirstElement_1313) {

    auto it = xmpData->begin();

    size_t initialCount = xmpData->count();

    xmpData->eraseFamily(it);

    EXPECT_EQ(xmpData->count(), initialCount - 3); // Xmp.dc.title and description are removed

}



TEST_F(XmpDataTest_1313, EraseFamilyBoundaryConditionLastElement_1313) {

    auto it = xmpData->findKey(XmpKey("Xmp.xmpMM.HistoryItem[2]"));

    size_t initialCount = xmpData->count();

    xmpData->eraseFamily(it);

    EXPECT_EQ(xmpData->count(), initialCount - 3); // All history items are removed

}
