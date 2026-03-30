#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/iptc.hpp"

#include <string>



using namespace Exiv2;

using testing::ElementsAre;



class IptcDataTest_700 : public ::testing::Test {

protected:

    IptcData iptcData;

};



TEST_F(IptcDataTest_700, EraseSingleElement_700) {

    // Arrange

    IptcKey key("Iptc.Application2.Caption");

    Value* value = new StringValue("Sample Caption");

    iptcData.add(key, value);



    auto it = iptcData.begin();



    // Act

    auto resultIt = iptcData.erase(it);



    // Assert

    EXPECT_EQ(resultIt, iptcData.end());

    EXPECT_TRUE(iptcData.empty());



    delete value;

}



TEST_F(IptcDataTest_700, EraseMultipleElements_700) {

    // Arrange

    IptcKey key1("Iptc.Application2.Caption");

    Value* value1 = new StringValue("Sample Caption 1");

    iptcData.add(key1, value1);



    IptcKey key2("Iptc.Application2.Headline");

    Value* value2 = new StringValue("Sample Headline");

    iptcData.add(key2, value2);



    auto it = iptcData.findKey(key1);



    // Act

    auto resultIt = iptcData.erase(it);

    size_t newSize = iptcData.size();



    // Assert

    EXPECT_EQ(resultIt->key(), key2);

    EXPECT_EQ(newSize, 1u);



    delete value1;

    delete value2;

}



TEST_F(IptcDataTest_700, EraseEndIterator_700) {

    // Arrange

    auto it = iptcData.end();



    // Act & Assert

    EXPECT_THROW(iptcData.erase(it), std::out_of_range);

}



TEST_F(IptcDataTest_700, EraseFromEmptyContainer_700) {

    // Arrange

    auto it = iptcData.begin();



    // Act & Assert

    EXPECT_THROW(iptcData.erase(it), std::out_of_range);

}
