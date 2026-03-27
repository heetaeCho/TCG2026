#include <gtest/gtest.h>

#include "exiv2/iptc.hpp"



using namespace Exiv2;



class IptcDataTest_48 : public ::testing::Test {

protected:

    IptcData iptcData;

};



TEST_F(IptcDataTest_48, CountInitiallyZero_48) {

    EXPECT_EQ(iptcData.count(), 0);

}



TEST_F(IptcDataTest_48, AddIncreasesCount_48) {

    // Assuming add function returns a success code (e.g., 0)

    iptcData.add(IptcKey("Iptc.Application2.Caption"), new Value);

    EXPECT_EQ(iptcData.count(), 1);

}



TEST_F(IptcDataTest_48, AddMultipleIncreasesCount_48) {

    iptcData.add(IptcKey("Iptc.Application2.Caption"), new Value);

    iptcData.add(IptcKey("Iptc.Application2.Byline"), new Value);

    EXPECT_EQ(iptcData.count(), 2);

}



TEST_F(IptcDataTest_48, ClearResetsCount_48) {

    iptcData.add(IptcKey("Iptc.Application2.Caption"), new Value);

    iptcData.clear();

    EXPECT_EQ(iptcData.count(), 0);

}



TEST_F(IptcDataTest_48, EmptyInitiallyTrue_48) {

    EXPECT_TRUE(iptcData.empty());

}



TEST_F(IptcDataTest_48, AddMakesEmptyFalse_48) {

    iptcData.add(IptcKey("Iptc.Application2.Caption"), new Value);

    EXPECT_FALSE(iptcData.empty());

}



TEST_F(IptcDataTest_48, ClearMakesEmptyTrue_48) {

    iptcData.add(IptcKey("Iptc.Application2.Caption"), new Value);

    iptcData.clear();

    EXPECT_TRUE(iptcData.empty());

}



TEST_F(IptcDataTest_48, FindKeyReturnsValidIterator_48) {

    iptcData.add(IptcKey("Iptc.Application2.Caption"), new Value);

    auto it = iptcData.findKey(IptcKey("Iptc.Application2.Caption"));

    EXPECT_NE(it, iptcData.end());

}



TEST_F(IptcDataTest_48, FindNonExistentKeyReturnsEnd_48) {

    auto it = iptcData.findKey(IptcKey("Iptc.Application2.Caption"));

    EXPECT_EQ(it, iptcData.end());

}



TEST_F(IptcDataTest_48, SortByKeyDoesNotChangeCount_48) {

    iptcData.add(IptcKey("Iptc.Application2.Byline"), new Value);

    iptcData.add(IptcKey("Iptc.Application2.Caption"), new Value);

    size_t initialCount = iptcData.count();

    iptcData.sortByKey();

    EXPECT_EQ(iptcData.count(), initialCount);

}



TEST_F(IptcDataTest_48, SortByTagDoesNotChangeCount_48) {

    iptcData.add(IptcKey("Iptc.Application2.Byline"), new Value);

    iptcData.add(IptcKey("Iptc.Application2.Caption"), new Value);

    size_t initialCount = iptcData.count();

    iptcData.sortByTag();

    EXPECT_EQ(iptcData.count(), initialCount);

}



TEST_F(IptcDataTest_48, EraseReducesCount_48) {

    iptcData.add(IptcKey("Iptc.Application2.Caption"), new Value);

    auto it = iptcData.begin();

    iptcData.erase(it);

    EXPECT_EQ(iptcData.count(), 0);

}



TEST_F(IptcDataTest_48, EraseInvalidIteratorDoesNotChangeCount_48) {

    size_t initialCount = iptcData.count();

    iptcData.erase(iptcData.end());

    EXPECT_EQ(iptcData.count(), initialCount);

}
