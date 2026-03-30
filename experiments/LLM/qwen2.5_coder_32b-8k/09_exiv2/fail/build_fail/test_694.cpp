#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/iptc.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;



class IptcDataTest_694 : public ::testing::Test {

protected:

    IptcData iptcData;

};



TEST_F(IptcDataTest_694, AddWithKeyAndValue_ReturnsZero_694) {

    IptcKey key("some_key");

    Value* value = new StringValue("test_value");

    EXPECT_EQ(iptcData.add(key, value), 0);

}



TEST_F(IptcDataTest_694, AddWithSameKeyTwice_ReturnsNonZero_694) {

    IptcKey key("some_key");

    Value* value1 = new StringValue("test_value1");

    Value* value2 = new StringValue("test_value2");



    iptcData.add(key, value1);

    EXPECT_NE(iptcData.add(key, value2), 0);

}



TEST_F(IptcDataTest_694, FindKey_ReturnsIteratorToElement_694) {

    IptcKey key("some_key");

    Value* value = new StringValue("test_value");

    iptcData.add(key, value);



    auto it = iptcData.findKey(key);

    EXPECT_NE(it, iptcData.end());

}



TEST_F(IptcDataTest_694, FindNonExistingKey_ReturnsEndIterator_694) {

    IptcKey key("non_existing_key");

    auto it = iptcData.findKey(key);

    EXPECT_EQ(it, iptcData.end());

}



TEST_F(IptcDataTest_694, SizeReturnsZeroInitially_694) {

    EXPECT_EQ(iptcData.size(), 0);

}



TEST_F(IptcDataTest_694, SizeIncreasesAfterAdd_694) {

    IptcKey key("some_key");

    Value* value = new StringValue("test_value");

    iptcData.add(key, value);



    EXPECT_EQ(iptcData.size(), 1);

}



TEST_F(IptcDataTest_694, ClearRemovesAllElements_694) {

    IptcKey key1("key1");

    Value* value1 = new StringValue("value1");

    iptcData.add(key1, value1);



    IptcKey key2("key2");

    Value* value2 = new StringValue("value2");

    iptcData.add(key2, value2);



    iptcData.clear();

    EXPECT_EQ(iptcData.size(), 0);

}



TEST_F(IptcDataTest_694, EraseRemovesElement_694) {

    IptcKey key("some_key");

    Value* value = new StringValue("test_value");

    auto it = iptcData.add(key, value);



    EXPECT_EQ(iptcData.size(), 1);

    iptcData.erase(it);

    EXPECT_EQ(iptcData.size(), 0);

}



TEST_F(IptcDataTest_694, SortByKeyDoesNotThrow_694) {

    IptcKey key1("key1");

    Value* value1 = new StringValue("value1");

    iptcData.add(key1, value1);



    IptcKey key2("key2");

    Value* value2 = new StringValue("value2");

    iptcData.add(key2, value2);



    EXPECT_NO_THROW(iptcData.sortByKey());

}



TEST_F(IptcDataTest_694, SortByTagDoesNotThrow_694) {

    IptcKey key1(10, 2);

    Value* value1 = new StringValue("value1");

    iptcData.add(key1, value1);



    IptcKey key2(5, 3);

    Value* value2 = new StringValue("value2");

    iptcData.add(key2, value2);



    EXPECT_NO_THROW(iptcData.sortByTag());

}
