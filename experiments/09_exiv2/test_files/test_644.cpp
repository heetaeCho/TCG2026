#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/datasets.hpp"



using namespace Exiv2;



class IptcKeyTest_644 : public ::testing::Test {

protected:

    uint16_t tag = 2;  // Example tag value

    uint16_t record = 3;  // Example record value

    IptcKey iptcKey = IptcKey(tag, record);

};



TEST_F(IptcKeyTest_644, TagLabelReturnsCorrectValue_644) {

    EXPECT_EQ(iptcKey.tagLabel(), IptcDataSets::dataSetTitle(tag, record));

}



TEST_F(IptcKeyTest_644, TagLabelBoundaryConditionZeroTag_644) {

    IptcKey iptcKeyWithZeroTag = IptcKey(0, record);

    EXPECT_EQ(iptcKeyWithZeroTag.tagLabel(), IptcDataSets::dataSetTitle(0, record));

}



TEST_F(IptcKeyTest_644, TagLabelBoundaryConditionZeroRecord_644) {

    IptcKey iptcKeyWithZeroRecord = IptcKey(tag, 0);

    EXPECT_EQ(iptcKeyWithZeroRecord.tagLabel(), IptcDataSets::dataSetTitle(tag, 0));

}



TEST_F(IptcKeyTest_644, TagLabelBoundaryConditionMaxValues_644) {

    uint16_t maxTag = std::numeric_limits<uint16_t>::max();

    uint16_t maxRecord = std::numeric_limits<uint16_t>::max();

    IptcKey iptcKeyWithMaxValues = IptcKey(maxTag, maxRecord);

    EXPECT_EQ(iptcKeyWithMaxValues.tagLabel(), IptcDataSets::dataSetTitle(maxTag, maxRecord));

}
