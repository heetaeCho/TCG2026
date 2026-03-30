#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/datasets.hpp"



using namespace Exiv2;



class IptcKeyTest_643 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup can be used to initialize objects or other resources if needed

    }



    void TearDown() override {

        // Cleanup can be handled here if necessary

    }

};



TEST_F(IptcKeyTest_643, TagName_ReturnsCorrectValueForValidTagAndRecord_643) {

    uint16_t tag = 2; // Example valid tag

    uint16_t record = 5; // Example valid record

    IptcKey key(tag, record);

    

    std::string expectedTagName = IptcDataSets::dataSetName(tag, record);

    EXPECT_EQ(key.tagName(), expectedTagName);

}



TEST_F(IptcKeyTest_643, TagName_ReturnsCorrectValueForConstructedFromString_643) {

    uint16_t tag = 2; // Example valid tag

    uint16_t record = 5; // Example valid record

    std::string keyString = "Iptc.Envelope." + IptcDataSets::dataSetName(tag, record);

    IptcKey key(keyString);

    

    EXPECT_EQ(key.tagName(), IptcDataSets::dataSetName(tag, record));

}



TEST_F(IptcKeyTest_643, TagName_ReturnsEmptyForInvalidTagAndRecord_643) {

    uint16_t tag = 0xFFFF; // Example invalid tag

    uint16_t record = 0xFFFF; // Example invalid record

    IptcKey key(tag, record);

    

    EXPECT_EQ(key.tagName(), "");

}



TEST_F(IptcKeyTest_643, TagName_ReturnsEmptyForInvalidConstructedString_643) {

    std::string invalidKeyString = "Iptc.InvalidTag";

    IptcKey key(invalidKeyString);

    

    EXPECT_EQ(key.tagName(), "");

}
