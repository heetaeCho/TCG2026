#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/iptc.hpp"



using namespace Exiv2;



class IptcDataTest_47 : public ::testing::Test {

protected:

    IptcData iptcData;

};



TEST_F(IptcDataTest_47, InitiallyEmpty_47) {

    EXPECT_TRUE(iptcData.empty());

}



TEST_F(IptcDataTest_47, SizeInitiallyZero_47) {

    EXPECT_EQ(iptcData.size(), 0);

}



TEST_F(IptcDataTest_47, CountInitiallyZero_47) {

    EXPECT_EQ(iptcData.count(), 0);

}



TEST_F(IptcDataTest_47, AddSingleElement_NotEmpty_47) {

    IptcKey key("Iptc.Envelope.ModelVersion");

    Value* value = new StringValue("1.2");

    iptcData.add(key, value);

    EXPECT_FALSE(iptcData.empty());

}



TEST_F(IptcDataTest_47, AddSingleElement_SizeOne_47) {

    IptcKey key("Iptc.Envelope.ModelVersion");

    Value* value = new StringValue("1.2");

    iptcData.add(key, value);

    EXPECT_EQ(iptcData.size(), 1);

}



TEST_F(IptcDataTest_47, AddMultipleElements_SizeCorrect_47) {

    IptcKey key1("Iptc.Envelope.ModelVersion");

    Value* value1 = new StringValue("1.2");

    iptcData.add(key1, value1);



    IptcKey key2("Iptc.Application2.Headline");

    Value* value2 = new StringValue("Test Headline");

    iptcData.add(key2, value2);



    EXPECT_EQ(iptcData.size(), 2);

}



TEST_F(IptcDataTest_47, AddDuplicateKey_SizeUnchanged_47) {

    IptcKey key("Iptc.Envelope.ModelVersion");

    Value* value1 = new StringValue("1.2");

    iptcData.add(key, value1);



    Value* value2 = new StringValue("3.4");

    iptcData.add(key, value2);



    EXPECT_EQ(iptcData.size(), 1);

}



TEST_F(IptcDataTest_47, FindKeyFound_ReturnsIterator_47) {

    IptcKey key("Iptc.Envelope.ModelVersion");

    Value* value = new StringValue("1.2");

    iptcData.add(key, value);



    auto it = iptcData.findKey(key);

    EXPECT_NE(it, iptcData.end());

}



TEST_F(IptcDataTest_47, FindKeyNotFound_ReturnsEndIterator_47) {

    IptcKey key("Iptc.Envelope.ModelVersion");

    Value* value = new StringValue("1.2");

    iptcData.add(key, value);



    IptcKey nonExistentKey("Iptc.Application2.Headline");

    auto it = iptcData.findKey(nonExistentKey);

    EXPECT_EQ(it, iptcData.end());

}



TEST_F(IptcDataTest_47, EraseElement_SizeDecreases_47) {

    IptcKey key("Iptc.Envelope.ModelVersion");

    Value* value = new StringValue("1.2");

    iptcData.add(key, value);



    auto it = iptcData.findKey(key);

    iptcData.erase(it);



    EXPECT_TRUE(iptcData.empty());

}



TEST_F(IptcDataTest_47, Clear_SizeZero_47) {

    IptcKey key1("Iptc.Envelope.ModelVersion");

    Value* value1 = new StringValue("1.2");

    iptcData.add(key1, value1);



    IptcKey key2("Iptc.Application2.Headline");

    Value* value2 = new StringValue("Test Headline");

    iptcData.add(key2, value2);



    iptcData.clear();

    EXPECT_EQ(iptcData.size(), 0);

}



TEST_F(IptcDataTest_47, SortByKey_NoException_47) {

    EXPECT_NO_THROW(iptcData.sortByKey());

}



TEST_F(IptcDataTest_47, SortByTag_NoException_47) {

    EXPECT_NO_THROW(iptcData.sortByTag());

}
