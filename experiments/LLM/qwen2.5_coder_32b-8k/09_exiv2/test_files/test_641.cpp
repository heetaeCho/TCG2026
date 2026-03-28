#include <gtest/gtest.h>

#include "exiv2/datasets.hpp"



using namespace Exiv2;



class IptcKeyTest_641 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialization code if needed

    }



    void TearDown() override {

        // Cleanup code if needed

    }

};



TEST_F(IptcKeyTest_641, FamilyName_ReturnsCorrectValue_641) {

    IptcKey key("test");

    EXPECT_STREQ(key.familyName(), "Iptc");

}



TEST_F(IptcKeyTest_641, ConstructorWithString_CreatesValidObject_641) {

    IptcKey key("test");

    EXPECT_EQ(key.key(), "test");

}



TEST_F(IptcKeyTest_641, ConstructorWithTagAndRecord_CreatesValidObject_641) {

    IptcKey key(123, 456);

    EXPECT_EQ(key.tag(), 123);

    EXPECT_EQ(key.record(), 456);

}



TEST_F(IptcKeyTest_641, Clone_ReturnsNewInstanceWithSameData_641) {

    IptcKey original(789, 012);

    auto cloned = original.clone();

    EXPECT_EQ(cloned->tag(), 789);

    EXPECT_EQ(cloned->record(), 012);

}



TEST_F(IptcKeyTest_641, FamilyName_IsConsistentAcrossInstances_641) {

    IptcKey key1("test1");

    IptcKey key2(345, 678);

    EXPECT_STREQ(key1.familyName(), "Iptc");

    EXPECT_STREQ(key2.familyName(), "Iptc");

}
