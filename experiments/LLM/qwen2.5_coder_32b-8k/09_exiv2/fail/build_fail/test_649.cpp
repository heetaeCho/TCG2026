#include <gtest/gtest.h>

#include "exiv2/datasets.hpp"



using namespace Exiv2;



class IptcKeyTest : public ::testing::Test {

protected:

    std::string keyString = "IPTC.Application2.Caption";

    uint16_t tag = 5;

    uint16_t record = 2;



    IptcKeyTest() : iptcKeyFromStr(keyString), iptcKeyFromTagRecord(tag, record) {}



    IptcKey iptcKeyFromStr;

    IptcKey iptcKeyFromTagRecord;

};



TEST_F(IptcKeyTest_649, CloneReturnsNonNullPointer_649) {

    EXPECT_NE(iptcKeyFromStr.clone().get(), nullptr);

}



TEST_F(IptcKeyTest_649, ClonePreservesKeyString_649) {

    auto clonedKey = iptcKeyFromStr.clone();

    EXPECT_EQ(clonedKey->key(), keyString);

}



TEST_F(IptcKeyTest_649, ClonePreservesTagAndRecord_649) {

    auto clonedKey = iptcKeyFromTagRecord.clone();

    EXPECT_EQ(clonedKey->tag(), tag);

    EXPECT_EQ(clonedKey->record(), record);

}



TEST_F(IptcKeyTest_649, KeyStringConstructorSetsCorrectValues_649) {

    EXPECT_EQ(iptcKeyFromStr.key(), keyString);

}



TEST_F(IptcKeyTest_649, TagRecordConstructorSetsCorrectValues_649) {

    EXPECT_EQ(iptcKeyFromTagRecord.tag(), tag);

    EXPECT_EQ(iptcKeyFromTagRecord.record(), record);

}



TEST_F(IptcKeyTest_649, KeyMethodReturnsValidString_649) {

    EXPECT_FALSE(iptcKeyFromStr.key().empty());

}



TEST_F(IptcKeyTest_649, FamilyNameMethodReturnsValidString_649) {

    EXPECT_FALSE(iptcKeyFromStr.familyName() == nullptr);

}



TEST_F(IptcKeyTest_649, GroupNameMethodReturnsValidString_649) {

    EXPECT_FALSE(iptcKeyFromStr.groupName().empty());

}



TEST_F(IptcKeyTest_649, TagNameMethodReturnsValidString_649) {

    EXPECT_FALSE(iptcKeyFromStr.tagName().empty());

}



TEST_F(IptcKeyTest_649, TagLabelMethodReturnsValidString_649) {

    EXPECT_FALSE(iptcKeyFromStr.tagLabel().empty());

}



TEST_F(IptcKeyTest_649, TagDescMethodReturnsValidString_649) {

    EXPECT_FALSE(iptcKeyFromStr.tagDesc().empty());

}



TEST_F(IptcKeyTest_649, RecordNameMethodReturnsValidString_649) {

    EXPECT_FALSE(iptcKeyFromTagRecord.recordName().empty());

}
