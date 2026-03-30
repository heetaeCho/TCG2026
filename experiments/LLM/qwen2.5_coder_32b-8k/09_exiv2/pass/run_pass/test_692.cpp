#include <gtest/gtest.h>

#include "exiv2/iptc.hpp"



using namespace Exiv2;



class IptcDataTest_692 : public ::testing::Test {

protected:

    IptcData iptcData;

};



TEST_F(IptcDataTest_692, OperatorBracket_NewKey_692) {

    std::string key = "new_key";

    Iptcdatum& datum = iptcData[key];

    EXPECT_EQ(datum.key(), key);

}



TEST_F(IptcDataTest_692, OperatorBracket_ExistingKey_692) {

    std::string key = "existing_key";

    iptcData[key]; // Insert the key first

    Iptcdatum& datum = iptcData[key];

    EXPECT_EQ(datum.key(), key);

}



TEST_F(IptcDataTest_692, Size_IncreasesAfterAdd_692) {

    size_t initialSize = iptcData.size();

    std::string key = "new_key";

    iptcData[key];

    EXPECT_EQ(iptcData.size(), initialSize + 1);

}



TEST_F(IptcDataTest_692, Size_UnchangedForExistingKey_692) {

    std::string key = "existing_key";

    iptcData[key]; // Insert the key first

    size_t sizeAfterFirstInsert = iptcData.size();

    iptcData[key];

    EXPECT_EQ(iptcData.size(), sizeAfterFirstInsert);

}



TEST_F(IptcDataTest_692, FindKey_ReturnsIteratorToExistingKey_692) {

    std::string key = "existing_key";

    iptcData[key]; // Insert the key first

    IptcKey iptcKey(key);

    auto it = iptcData.findKey(iptcKey);

    EXPECT_NE(it, iptcData.end());

    EXPECT_EQ(it->key(), key);

}



TEST_F(IptcDataTest_692, FindKey_ReturnsEndForNonExistingKey_692) {

    std::string nonExistingKey = "non_existing_key";

    IptcKey iptcKey(nonExistingKey);

    auto it = iptcData.findKey(iptcKey);

    EXPECT_EQ(it, iptcData.end());

}



TEST_F(IptcDataTest_692, Empty_ReturnsTrueForEmptyData_692) {

    EXPECT_TRUE(iptcData.empty());

}



TEST_F(IptcDataTest_692, Empty_ReturnsFalseAfterInsert_692) {

    std::string key = "new_key";

    iptcData[key];

    EXPECT_FALSE(iptcData.empty());

}



TEST_F(IptcDataTest_692, Clear_ResetsSizeToZero_692) {

    std::string key = "new_key";

    iptcData[key];

    iptcData.clear();

    EXPECT_EQ(iptcData.size(), 0);

}



TEST_F(IptcDataTest_692, Clear_MakesEmptyTrue_692) {

    std::string key = "new_key";

    iptcData[key];

    iptcData.clear();

    EXPECT_TRUE(iptcData.empty());

}
