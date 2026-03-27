#include <gtest/gtest.h>

#include "exiv2/datasets.hpp"



using namespace Exiv2;



class IptcKeyTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(IptcKeyTest_2159, ConstructorWithTagAndRecord_2159) {

    IptcKey key(0x01, 0x02);

    EXPECT_EQ(key.tag(), 0x01);

    EXPECT_EQ(key.record(), 0x02);

}



TEST_F(IptcKeyTest_2159, ConstructorWithKeyString_2159) {

    IptcKey key("IPTC.Envelope.CodedCharacterSet");

    EXPECT_EQ(key.key(), "IPTC.Envelope.CodedCharacterSet");

}



TEST_F(IptcKeyTest_2159, KeyMethodReturnsCorrectValue_2159) {

    IptcKey key(0x01, 0x02);

    std::string expected_key = "iptc.0102"; // Assuming makeKey constructs this format

    EXPECT_EQ(key.key(), expected_key);

}



TEST_F(IptcKeyTest_2159, FamilyNameReturnsCorrectValue_2159) {

    IptcKey key(0x01, 0x02);

    EXPECT_STREQ(key.familyName(), "IPTC");

}



TEST_F(IptcKeyTest_2159, GroupNameReturnsCorrectValue_2159) {

    IptcKey key("IPTC.Envelope.CodedCharacterSet");

    EXPECT_EQ(key.groupName(), "Envelope");

}



TEST_F(IptcKeyTest_2159, TagNameReturnsCorrectValue_2159) {

    IptcKey key("IPTC.Envelope.CodedCharacterSet");

    EXPECT_EQ(key.tagName(), "CodedCharacterSet");

}



TEST_F(IptcKeyTest_2159, TagLabelAndDescReturnNonEmptyStrings_2159) {

    IptcKey key(0x01, 0x02);

    EXPECT_FALSE(key.tagLabel().empty());

    EXPECT_FALSE(key.tagDesc().empty());

}



TEST_F(IptcKeyTest_2159, RecordNameReturnsCorrectValue_2159) {

    IptcKey key(0x01, 0x02);

    std::string expected_record_name = "Record"; // Assuming recordName constructs this format

    EXPECT_EQ(key.recordName(), expected_record_name);

}



TEST_F(IptcKeyTest_2159, CloneMethodReturnsValidInstance_2159) {

    IptcKey key(0x01, 0x02);

    auto cloned_key = key.clone();

    ASSERT_NE(cloned_key.get(), nullptr);

    EXPECT_EQ(cloned_key->key(), key.key());

}



TEST_F(IptcKeyTest_2159, BoundaryConditionForTagAndRecord_2159) {

    IptcKey key(0x00, 0xFF);

    EXPECT_EQ(key.tag(), 0x00);

    EXPECT_EQ(key.record(), 0xFF);

}



TEST_F(IptcKeyTest_2159, BoundaryConditionForKeyString_2159) {

    IptcKey key("IPTC.Application2.By-line");

    EXPECT_EQ(key.key(), "IPTC.Application2.By-line");

}
