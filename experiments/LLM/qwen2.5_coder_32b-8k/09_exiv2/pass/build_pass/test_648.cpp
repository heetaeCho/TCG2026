#include <gtest/gtest.h>

#include "exiv2/datasets.hpp"



using namespace Exiv2;



class IptcKeyTest_648 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}



    std::string testKey = "IPTC.Application2.Caption";

    uint16_t testTag = 0x0078;

    uint16_t testRecord = 0x0002;

};



TEST_F(IptcKeyTest_648, RecordReturnsCorrectValueFromStringConstructor_648) {

    IptcKey key(testKey);

    EXPECT_EQ(key.record(), 0u); // Assuming record is not set from string in this constructor

}



TEST_F(IptcKeyTest_648, RecordReturnsCorrectValueFromTagRecordConstructor_648) {

    IptcKey key(testTag, testRecord);

    EXPECT_EQ(key.record(), testRecord);

}



TEST_F(IptcKeyTest_648, BoundaryConditionForRecordFromTagRecordConstructor_648) {

    uint16_t maxRecord = std::numeric_limits<uint16_t>::max();

    IptcKey key(testTag, maxRecord);

    EXPECT_EQ(key.record(), maxRecord);

}



TEST_F(IptcKeyTest_648, BoundaryConditionForRecordFromTagRecordConstructor_Zero_648) {

    uint16_t zeroRecord = 0;

    IptcKey key(testTag, zeroRecord);

    EXPECT_EQ(key.record(), zeroRecord);

}
