#include <gtest/gtest.h>

#include "exiv2/iptc.hpp"

#include <vector>



using namespace Exiv2;



class IptcDataTest_699 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary data or state before each test.

        iptcData.clear();

    }



    void TearDown() override {

        // Clean up any resources after each test, if needed.

        iptcData.clear();

    }



    IptcData iptcData;

};



TEST_F(IptcDataTest_699, SortByTag_EmptyList_699) {

    // Test sorting an empty list

    iptcData.sortByTag();

    EXPECT_TRUE(iptcData.empty());

}



TEST_F(IptcDataTest_699, SortByTag_SingleElement_699) {

    // Test sorting a single element list

    Iptcdatum datum("Iptc.Application2.Caption", "Caption text");

    iptcData.add(datum);

    iptcData.sortByTag();

    EXPECT_EQ(iptcData.size(), 1U);

}



TEST_F(IptcDataTest_699, SortByTag_MultipleElementsSorted_699) {

    // Test sorting multiple elements that are already sorted

    Iptcdatum datum1("Iptc.Application2.Caption", "Caption text");

    Iptcdatum datum2("Iptc.Application2.Keywords", "Keyword1");

    iptcData.add(datum1);

    iptcData.add(datum2);

    iptcData.sortByTag();

    auto it = iptcData.begin();

    EXPECT_EQ(it->key(), "Iptc.Application2.Caption");

    ++it;

    EXPECT_EQ(it->key(), "Iptc.Application2.Keywords");

}



TEST_F(IptcDataTest_699, SortByTag_MultipleElementsUnsorted_699) {

    // Test sorting multiple elements that are not sorted

    Iptcdatum datum1("Iptc.Application2.Keywords", "Keyword1");

    Iptcdatum datum2("Iptc.Application2.Caption", "Caption text");

    iptcData.add(datum1);

    iptcData.add(datum2);

    iptcData.sortByTag();

    auto it = iptcData.begin();

    EXPECT_EQ(it->key(), "Iptc.Application2.Caption");

    ++it;

    EXPECT_EQ(it->key(), "Iptc.Application2.Keywords");

}



TEST_F(IptcDataTest_699, SortByTag_LargeDataSet_699) {

    // Test sorting a large data set

    for (int i = 0; i < 100; ++i) {

        std::string key = "Iptc.Application2.Keyword" + std::to_string(i);

        Iptcdatum datum(key, "Value");

        iptcData.add(datum);

    }

    iptcData.sortByTag();

    auto it = iptcData.begin();

    for (int i = 0; i < 100; ++i) {

        std::string expectedKey = "Iptc.Application2.Keyword" + std::to_string(i);

        EXPECT_EQ(it->key(), expectedKey);

        ++it;

    }

}
