#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/datasets.hpp"



using namespace Exiv2;



class IptcKeyTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(IptcKeyTest_642, ConstructorWithString_642) {

    IptcKey iptcKey("testKey");

    EXPECT_EQ(iptcKey.key(), "testKey");

}



TEST_F(IptcKeyTest_642, ConstructorWithTagAndRecord_642) {

    IptcKey iptcKey(1, 2);

    EXPECT_EQ(iptcKey.tag(), 1);

    EXPECT_EQ(iptcKey.record(), 2);

}



TEST_F(IptcKeyTest_642, GroupNameEqualsRecordName_642) {

    IptcKey iptcKey("testKey");

    EXPECT_EQ(iptcKey.groupName(), iptcKey.recordName());

}



TEST_F(IptcKeyTest_642, CloneReturnsNewInstance_642) {

    IptcKey iptcKey("testKey");

    auto clonedKey = iptcKey.clone();

    EXPECT_NE(&iptcKey, clonedKey.get());

    EXPECT_EQ(clonedKey->key(), "testKey");

}



TEST_F(IptcKeyTest_642, CloneWithTagAndRecord_642) {

    IptcKey iptcKey(1, 2);

    auto clonedKey = iptcKey.clone();

    EXPECT_NE(&iptcKey, clonedKey.get());

    EXPECT_EQ(clonedKey->tag(), 1);

    EXPECT_EQ(clonedKey->record(), 2);

}



TEST_F(IptcKeyTest_642, BoundaryConditionEmptyString_642) {

    IptcKey iptcKey("");

    EXPECT_EQ(iptcKey.key(), "");

    EXPECT_EQ(iptcKey.groupName(), iptcKey.recordName());

}



TEST_F(IptcKeyTest_642, BoundaryConditionMaxUint16Tag_642) {

    IptcKey iptcKey(std::numeric_limits<uint16_t>::max(), 0);

    EXPECT_EQ(iptcKey.tag(), std::numeric_limits<uint16_t>::max());

}



TEST_F(IptcKeyTest_642, BoundaryConditionMaxUint16Record_642) {

    IptcKey iptcKey(0, std::numeric_limits<uint16_t>::max());

    EXPECT_EQ(iptcKey.record(), std::numeric_limits<uint16_t>::max());

}
