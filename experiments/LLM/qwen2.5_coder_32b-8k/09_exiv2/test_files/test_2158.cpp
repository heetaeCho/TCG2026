#include <gtest/gtest.h>

#include "exiv2/datasets.hpp"

#include "exiv2/metadatum.hpp"



using namespace Exiv2;



class IptcKeyTest_2158 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}



    std::string testKey = "Iptc.Application2.Caption";

};



TEST_F(IptcKeyTest_2158, ConstructorWithString_2158) {

    IptcKey key(testKey);

    EXPECT_EQ(key.key(), testKey);

}



TEST_F(IptcKeyTest_2158, KeyFunctionReturnsCorrectValue_2158) {

    IptcKey key(testKey);

    EXPECT_EQ(key.key(), testKey);

}



TEST_F(IptcKeyTest_2158, FamilyNameFunctionReturnsCorrectValue_2158) {

    IptcKey key(testKey);

    EXPECT_STREQ(key.familyName(), "Iptc");

}



TEST_F(IptcKeyTest_2158, GroupNameFunctionReturnsCorrectValue_2158) {

    IptcKey key(testKey);

    EXPECT_EQ(key.groupName(), "Application2");

}



TEST_F(IptcKeyTest_2158, TagNameFunctionReturnsCorrectValue_2158) {

    IptcKey key(testKey);

    EXPECT_EQ(key.tagName(), "Caption");

}



TEST_F(IptcKeyTest_2158, CloneFunctionCreatesValidObject_2158) {

    IptcKey key(testKey);

    auto clonedKey = key.clone();

    EXPECT_EQ(clonedKey->key(), testKey);

}



TEST_F(IptcKeyTest_2158, ConstructorWithTagAndRecord_2158) {

    uint16_t tag = 0x78;

    uint16_t record = 0x02;

    IptcKey key(tag, record);

    EXPECT_EQ(key.tag(), tag);

    EXPECT_EQ(key.record(), record);

}



TEST_F(IptcKeyTest_2158, BoundaryConditionEmptyString_2158) {

    IptcKey key("");

    EXPECT_EQ(key.key(), "");

}



TEST_F(IptcKeyTest_2158, ExceptionalCaseInvalidKeyFormat_2158) {

    // Assuming that the constructor does not throw for invalid format in this context

    std::string invalidKey = "Invalid.Key.Format";

    IptcKey key(invalidKey);

    EXPECT_EQ(key.key(), invalidKey);  // Check if it handles gracefully without throwing

}



TEST_F(IptcKeyTest_2158, RecordNameFunctionReturnsCorrectValueForKnownRecord_2158) {

    uint16_t record = 0x02;

    IptcKey key(0x78, record);

    EXPECT_EQ(key.recordName(), "Application2");

}



TEST_F(IptcKeyTest_2158, TagLabelAndTagDescReturnDefaultForUnknownTags_2158) {

    uint16_t tag = 9999; // Assuming this is an unknown tag

    IptcKey key(tag, 0x02);

    EXPECT_EQ(key.tagLabel(), "");

    EXPECT_EQ(key.tagDesc(), "");

}
