#include <gtest/gtest.h>

#include "exiv2/iptc.hpp"



class IptcDataTest_44 : public ::testing::Test {

protected:

    Exiv2::IptcData iptcData;

};



TEST_F(IptcDataTest_44, ClearRemovesAllEntries_44) {

    // Assuming add function works correctly and adds at least one entry

    iptcData.add(Exiv2::IptcKey("Iptc.Application2.Caption"), new Exiv2::Value);

    iptcData.clear();

    EXPECT_TRUE(iptcData.empty());

}



TEST_F(IptcDataTest_44, SizeReturnsCorrectCount_44) {

    // Assuming add function works correctly and adds at least one entry

    iptcData.add(Exiv2::IptcKey("Iptc.Application2.Caption"), new Exiv2::Value);

    EXPECT_EQ(iptcData.size(), 1u);

}



TEST_F(IptcDataTest_44, EmptyReturnsTrueWhenNoEntries_44) {

    EXPECT_TRUE(iptcData.empty());

}



TEST_F(IptcDataTest_44, EmptyReturnsFalseWhenEntriesExist_44) {

    iptcData.add(Exiv2::IptcKey("Iptc.Application2.Caption"), new Exiv2::Value);

    EXPECT_FALSE(iptcData.empty());

}



TEST_F(IptcDataTest_44, FindKeyReturnsEndWhenNotFound_44) {

    auto it = iptcData.findKey(Exiv2::IptcKey("Non.Existing.Key"));

    EXPECT_EQ(it, iptcData.end());

}



TEST_F(IptcDataTest_44, FindIdReturnsEndWhenNotFound_44) {

    auto it = iptcData.findId(0xFFFF, 0xFFFF);

    EXPECT_EQ(it, iptcData.end());

}



TEST_F(IptcDataTest_44, SortByKeyDoesNotThrowException_44) {

    EXPECT_NO_THROW(iptcData.sortByKey());

}



TEST_F(IptcDataTest_44, SortByTagDoesNotThrowException_44) {

    EXPECT_NO_THROW(iptcData.sortByTag());

}



TEST_F(IptcDataTest_44, EraseRemovesEntryWhenValidIterator_44) {

    iptcData.add(Exiv2::IptcKey("Iptc.Application2.Caption"), new Exiv2::Value);

    auto it = iptcData.begin();

    iptcData.erase(it);

    EXPECT_TRUE(iptcData.empty());

}



TEST_F(IptcDataTest_44, DetectCharsetReturnsNonNullPointer_44) {

    const char* charset = iptcData.detectCharset();

    EXPECT_NE(charset, nullptr);

}
