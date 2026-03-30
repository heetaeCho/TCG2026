#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/iptc.hpp"

#include "exiv2/datasets.hpp"



using namespace Exiv2;

using ::testing::Eq;



class IptcDataTest_696 : public ::testing::Test {

protected:

    IptcData iptc_data;

    IptcKey key1{1, 1};

    IptcKey key2{2, 2};



    void SetUp() override {

        // Setup any state here if needed

    }

};



TEST_F(IptcDataTest_696, FindExistingKey_696) {

    iptc_data.add(key1, nullptr);

    auto it = iptc_data.findKey(key1);

    EXPECT_NE(it, iptc_data.end());

}



TEST_F(IptcDataTest_696, FindNonexistentKey_696) {

    auto it = iptc_data.findKey(key1);

    EXPECT_EQ(it, iptc_data.end());

}



TEST_F(IptcDataTest_696, FindMultipleKeys_696) {

    iptc_data.add(key1, nullptr);

    iptc_data.add(key2, nullptr);



    auto it1 = iptc_data.findKey(key1);

    EXPECT_NE(it1, iptc_data.end());



    auto it2 = iptc_data.findKey(key2);

    EXPECT_NE(it2, iptc_data.end());

}



TEST_F(IptcDataTest_696, FindKeyAfterAddingMultipleKeys_696) {

    iptc_data.add(key1, nullptr);

    iptc_data.add(key2, nullptr);



    auto it = iptc_data.findKey(key1);

    EXPECT_NE(it, iptc_data.end());



    it = iptc_data.findKey(key2);

    EXPECT_NE(it, iptc_data.end());

}



TEST_F(IptcDataTest_696, FindKeyAfterClearing_696) {

    iptc_data.add(key1, nullptr);

    iptc_data.clear();



    auto it = iptc_data.findKey(key1);

    EXPECT_EQ(it, iptc_data.end());

}
