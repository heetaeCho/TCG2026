#include <gtest/gtest.h>

#include "exiv2/datasets.hpp"



namespace {



class IptcDataSetsTest : public ::testing::Test {

protected:

    Exiv2::IptcDataSets iptcDataSets;

};



TEST_F(IptcDataSetsTest_628, Application2RecordList_ReturnsNonNullPointer_628) {

    const auto* recordList = iptcDataSets.application2RecordList();

    EXPECT_NE(recordList, nullptr);

}



TEST_F(IptcDataSetsTest_628, Application2RecordList_ReturnsValidFirstElement_628) {

    const auto* recordList = iptcDataSets.application2RecordList();

    EXPECT_STREQ(recordList->name_, "RecordVersion");

}



TEST_F(IptcDataSetsTest_628, Application2RecordList_ReturnsCorrectNumberOfElements_628) {

    const auto* recordList = iptcDataSets.application2RecordList();

    int count = 0;

    for (; recordList[count].recordId_ != 65535; ++count);

    EXPECT_EQ(count, 57); // Last element is a sentinel with number 65535

}



TEST_F(IptcDataSetsTest_628, Application2RecordList_EndsWithInvalidSentinel_628) {

    const auto* recordList = iptcDataSets.application2RecordList();

    int count = 0;

    for (; recordList[count].recordId_ != 65535; ++count);

    EXPECT_STREQ(recordList[count].name_, "(Invalid)");

}



} // namespace
