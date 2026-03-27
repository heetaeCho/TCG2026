#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/iptc.hpp"



using namespace Exiv2;

using ::testing::Return;



class IptcDataTest : public ::testing::Test {

protected:

    IptcData iptcData;

};



TEST_F(IptcDataTest_46, EmptyInitially_46) {

    EXPECT_TRUE(iptcData.empty());

}



TEST_F(IptcDataTest_46, SizeZeroInitially_46) {

    EXPECT_EQ(0u, iptcData.size());

}



TEST_F(IptcDataTest_46, AddIncreasesSize_46) {

    IptcKey key("Iptc.Envelope.DateSent");

    Value* value = new StringValue("20231001");

    iptcData.add(key, value);

    EXPECT_EQ(1u, iptcData.size());

}



TEST_F(IptcDataTest_46, AddSameKeyTwiceIncreasesSize_46) {

    IptcKey key("Iptc.Envelope.DateSent");

    Value* value = new StringValue("20231001");

    iptcData.add(key, value);

    iptcData.add(key, value);

    EXPECT_EQ(2u, iptcData.size());

}



TEST_F(IptcDataTest_46, FindKeyFindsExistingKey_46) {

    IptcKey key("Iptc.Envelope.DateSent");

    Value* value = new StringValue("20231001");

    iptcData.add(key, value);

    EXPECT_NE(iptcData.end(), iptcData.findKey(key));

}



TEST_F(IptcDataTest_46, FindKeyReturnsEndForNonexistentKey_46) {

    IptcKey key("Iptc.Envelope.DateSent");

    EXPECT_EQ(iptcData.end(), iptcData.findKey(key));

}



TEST_F(IptcDataTest_46, EraseRemovesElement_46) {

    IptcKey key("Iptc.Envelope.DateSent");

    Value* value = new StringValue("20231001");

    iptcData.add(key, value);

    auto it = iptcData.findKey(key);

    iptcData.erase(it);

    EXPECT_EQ(0u, iptcData.size());

}



TEST_F(IptcDataTest_46, ClearRemovesAllElements_46) {

    IptcKey key1("Iptc.Envelope.DateSent");

    Value* value1 = new StringValue("20231001");

    iptcData.add(key1, value1);



    IptcKey key2("Iptc.Envelope.ModelVersion");

    Value* value2 = new UShortValue(4);

    iptcData.add(key2, value2);



    iptcData.clear();

    EXPECT_TRUE(iptcData.empty());

}



TEST_F(IptcDataTest_46, SortByKeyDoesNotChangeSize_46) {

    IptcKey key1("Iptc.Envelope.DateSent");

    Value* value1 = new StringValue("20231001");

    iptcData.add(key1, value1);



    IptcKey key2("Iptc.Envelope.ModelVersion");

    Value* value2 = new UShortValue(4);

    iptcData.add(key2, value2);



    size_t initialSize = iptcData.size();

    iptcData.sortByKey();

    EXPECT_EQ(initialSize, iptcData.size());

}



TEST_F(IptcDataTest_46, SortByTagDoesNotChangeSize_46) {

    IptcKey key1("Iptc.Envelope.DateSent");

    Value* value1 = new StringValue("20231001");

    iptcData.add(key1, value1);



    IptcKey key2("Iptc.Envelope.ModelVersion");

    Value* value2 = new UShortValue(4);

    iptcData.add(key2, value2);



    size_t initialSize = iptcData.size();

    iptcData.sortByTag();

    EXPECT_EQ(initialSize, iptcData.size());

}



TEST_F(IptcDataTest_46, DetectCharsetReturnsNullptrInitially_46) {

    EXPECT_EQ(nullptr, iptcData.detectCharset());

}
