#include <gtest/gtest.h>

#include "exiv2/iptc.hpp"

#include <vector>



using namespace Exiv2;



class IptcDataTest_698 : public ::testing::Test {

protected:

    IptcData iptcData;

};



TEST_F(IptcDataTest_698, SortByKey_EmptyList_698) {

    iptcData.sortByKey();

    EXPECT_EQ(iptcData.size(), 0);

}



TEST_F(IptcDataTest_698, SortByKey_SingleElement_698) {

    Iptcdatum datum;

    iptcData.add(datum);

    iptcData.sortByKey();

    EXPECT_EQ(iptcData.size(), 1);

}



TEST_F(IptcDataTest_698, SortByKey_MultipleElements_698) {

    Iptcdatum datum1;

    Iptcdatum datum2;

    iptcData.add(datum1);

    iptcData.add(datum2);

    iptcData.sortByKey();

    EXPECT_EQ(iptcData.size(), 2);

}



TEST_F(IptcDataTest_698, Add_SingleElement_698) {

    Iptcdatum datum;

    int result = iptcData.add(datum);

    EXPECT_EQ(result, 0);

    EXPECT_EQ(iptcData.size(), 1);

}



TEST_F(IptcDataTest_698, Add_MultipleElements_698) {

    Iptcdatum datum1;

    Iptcdatum datum2;

    iptcData.add(datum1);

    iptcData.add(datum2);

    EXPECT_EQ(iptcData.size(), 2);

}



TEST_F(IptcDataTest_698, Add_DuplicateKey_698) {

    Iptcdatum datum1;

    Iptcdatum datum2;

    datum2.key() = datum1.key(); // Assuming keys can be set and compared

    iptcData.add(datum1);

    int result = iptcData.add(datum2);

    EXPECT_EQ(result, 1); // Assuming add returns non-zero on failure

    EXPECT_EQ(iptcData.size(), 1);

}



TEST_F(IptcDataTest_698, Erase_SingleElement_698) {

    Iptcdatum datum;

    iptcData.add(datum);

    auto it = iptcData.begin();

    iptcData.erase(it);

    EXPECT_EQ(iptcData.size(), 0);

}



TEST_F(IptcDataTest_698, Erase_MultipleElements_698) {

    Iptcdatum datum1;

    Iptcdatum datum2;

    iptcData.add(datum1);

    iptcData.add(datum2);

    auto it = iptcData.begin();

    iptcData.erase(it);

    EXPECT_EQ(iptcData.size(), 1);

}



TEST_F(IptcDataTest_698, Clear_EmptyList_698) {

    iptcData.clear();

    EXPECT_EQ(iptcData.size(), 0);

}



TEST_F(IptcDataTest_698, Clear_NonEmptyList_698) {

    Iptcdatum datum1;

    Iptcdatum datum2;

    iptcData.add(datum1);

    iptcData.add(datum2);

    iptcData.clear();

    EXPECT_EQ(iptcData.size(), 0);

}



TEST_F(IptcDataTest_698, Size_EmptyList_698) {

    EXPECT_EQ(iptcData.size(), 0);

}



TEST_F(IptcDataTest_698, Size_NonEmptyList_698) {

    Iptcdatum datum;

    iptcData.add(datum);

    EXPECT_EQ(iptcData.size(), 1);

}



TEST_F(IptcDataTest_698, FindKey_NotFound_698) {

    IptcKey key("IPTC.KeyThatDoesNotExist");

    auto it = iptcData.findKey(key);

    EXPECT_TRUE(it == iptcData.end());

}



TEST_F(IptcDataTest_698, FindKey_Found_698) {

    Iptcdatum datum;

    IptcKey key("IPTC.KeyExists");

    datum.key() = key; // Assuming keys can be set

    iptcData.add(datum);

    auto it = iptcData.findKey(key);

    EXPECT_TRUE(it != iptcData.end());

}



TEST_F(IptcDataTest_698, Empty_EmptyList_698) {

    EXPECT_TRUE(iptcData.empty());

}



TEST_F(IptcDataTest_698, Empty_NonEmptyList_698) {

    Iptcdatum datum;

    iptcData.add(datum);

    EXPECT_FALSE(iptcData.empty());

}
