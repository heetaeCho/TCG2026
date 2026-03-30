#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/datasets.hpp"



namespace {



using namespace Exiv2;



class IptcKeyTest : public ::testing::Test {

protected:

    IptcKey key1;

    IptcKey key2;



    IptcKeyTest() 

        : key1(0x50, 0x02), // Example tag and record

          key2("Iptc.Envelope.DateCreated") {} // Example key string



    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(IptcKeyTest_651, MakeKeyConstructsCorrectly_651) {

    key1.makeKey();

    EXPECT_EQ(key1.key(), "Iptc.Envelope.DateCreated");

}



TEST_F(IptcKeyTest_651, ConstructWithTagRecord_651) {

    EXPECT_EQ(key1.recordName(), IptcDataSets::recordName(0x02));

    EXPECT_EQ(key1.tagName(), IptcDataSets::dataSetName(0x50, 0x02));

}



TEST_F(IptcKeyTest_651, ConstructWithKeyString_651) {

    EXPECT_EQ(key2.recordName(), IptcDataSets::recordName(0x02));

    EXPECT_EQ(key2.tagName(), IptcDataSets::dataSetName(0x50, 0x02));

}



TEST_F(IptcKeyTest_651, FamilyNameConsistent_651) {

    EXPECT_STREQ(key1.familyName(), "Iptc");

    EXPECT_STREQ(key2.familyName(), "Iptc");

}



TEST_F(IptcKeyTest_651, BoundaryTagRecordValues_651) {

    IptcKey boundaryKey(0xFFFF, 0xFFFF);

    boundaryKey.makeKey();

    EXPECT_EQ(boundaryKey.key(), std::string("Iptc.") + IptcDataSets::recordName(0xFFFF) + "." + IptcDataSets::dataSetName(0xFFFF, 0xFFFF));

}



TEST_F(IptcKeyTest_651, InvalidKeyString_651) {

    IptcKey invalidKey("Invalid.Key.String");

    EXPECT_THROW(invalidKey.makeKey(), Error); // Assuming some error is thrown for invalid keys

}



} // namespace
