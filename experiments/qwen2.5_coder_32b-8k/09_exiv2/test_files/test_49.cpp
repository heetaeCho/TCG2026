#include <gtest/gtest.h>

#include <exiv2/xmp_exiv2.hpp>



class XmpDataTest_49 : public ::testing::Test {

protected:

    Exiv2::XmpData xmpData;

};



TEST_F(XmpDataTest_49, DefaultConstructorDoesNotUsePacket_49) {

    EXPECT_FALSE(xmpData.usePacket());

}



TEST_F(XmpDataTest_49, SetPacketSetsCorrectly_49) {

    std::string packet = "<xmp></xmp>";

    xmpData.setPacket(packet);

    EXPECT_EQ(xmpData.xmpPacket(), packet);

}



TEST_F(XmpDataTest_49, UsePacketSetTrueAndGetTrue_49) {

    xmpData.usePacket(true);

    EXPECT_TRUE(xmpData.usePacket());

}



TEST_F(XmpDataTest_49, UsePacketSetFalseAndGetFalse_49) {

    xmpData.usePacket(false);

    EXPECT_FALSE(xmpData.usePacket());

}



TEST_F(XmpDataTest_49, ClearEmptiesData_49) {

    std::string packet = "<xmp></xmp>";

    xmpData.setPacket(packet);

    xmpData.clear();

    EXPECT_TRUE(xmpData.empty());

}



TEST_F(XmpDataTest_49, CountZeroAfterClear_49) {

    std::string packet = "<xmp></xmp>";

    xmpData.setPacket(packet);

    xmpData.clear();

    EXPECT_EQ(xmpData.count(), 0L);

}



TEST_F(XmpDataTest_49, AddAndCount_49) {

    // Assuming XmpKey and Value are properly defined elsewhere

    Exiv2::XmpKey key("dc:title");

    Exiv2::Value* value = new Exiv2::StringValue("Sample Title");

    xmpData.add(key, value);

    EXPECT_EQ(xmpData.count(), 1L);

}



TEST_F(XmpDataTest_49, AddDuplicateAndCount_49) {

    // Assuming XmpKey and Value are properly defined elsewhere

    Exiv2::XmpKey key("dc:title");

    Exiv2::Value* value = new Exiv2::StringValue("Sample Title");

    xmpData.add(key, value);

    xmpData.add(key, value);  // Adding duplicate

    EXPECT_EQ(xmpData.count(), 1L);

}



TEST_F(XmpDataTest_49, EraseAndCount_49) {

    // Assuming XmpKey and Value are properly defined elsewhere

    Exiv2::XmpKey key("dc:title");

    Exiv2::Value* value = new Exiv2::StringValue("Sample Title");

    xmpData.add(key, value);

    auto it = xmpData.begin();

    xmpData.erase(it);

    EXPECT_EQ(xmpData.count(), 0L);

}



TEST_F(XmpDataTest_49, FindKeyReturnsValidIterator_49) {

    // Assuming XmpKey and Value are properly defined elsewhere

    Exiv2::XmpKey key("dc:title");

    Exiv2::Value* value = new Exiv2::StringValue("Sample Title");

    xmpData.add(key, value);

    auto it = xmpData.findKey(key);

    EXPECT_NE(it, xmpData.end());

}



TEST_F(XmpDataTest_49, FindNonexistentKeyReturnsEndIterator_49) {

    // Assuming XmpKey and Value are properly defined elsewhere

    Exiv2::XmpKey key("dc:title");

    Exiv2::Value* value = new Exiv2::StringValue("Sample Title");

    xmpData.add(key, value);

    auto it = xmpData.findKey(Exiv2::XmpKey("nonexistent"));

    EXPECT_EQ(it, xmpData.end());

}



TEST_F(XmpDataTest_49, BeginEndIteratorsWork_49) {

    // Assuming XmpKey and Value are properly defined elsewhere

    Exiv2::XmpKey key("dc:title");

    Exiv2::Value* value = new Exiv2::StringValue("Sample Title");

    xmpData.add(key, value);

    auto itBegin = xmpData.begin();

    auto itEnd = xmpData.end();

    EXPECT_NE(itBegin, itEnd);

}



TEST_F(XmpDataTest_49, SortByKeyDoesNotThrow_49) {

    // Assuming XmpKey and Value are properly defined elsewhere

    Exiv2::XmpKey key("dc:title");

    Exiv2::Value* value = new Exiv2::StringValue("Sample Title");

    xmpData.add(key, value);

    EXPECT_NO_THROW(xmpData.sortByKey());

}



TEST_F(XmpDataTest_49, OperatorBracketSetsCorrectly_49) {

    // Assuming XmpKey and Value are properly defined elsewhere

    Exiv2::Xmpdatum& datum = xmpData["dc:title"];

    datum.setValue("Sample Title");

    EXPECT_EQ(xmpData.count(), 1L);

}



TEST_F(XmpDataTest_49, OperatorBracketOverwritesCorrectly_49) {

    // Assuming XmpKey and Value are properly defined elsewhere

    Exiv2::Xmpdatum& datum = xmpData["dc:title"];

    datum.setValue("Sample Title");

    datum.setValue("New Title");

    EXPECT_EQ(xmpData.count(), 1L);

}
