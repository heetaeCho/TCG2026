#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/datasets.hpp"



using namespace Exiv2;



class IptcDataSetsTest_636 : public ::testing::Test {

protected:

    IptcDataSets iptcDataSets;

};



TEST_F(IptcDataSetsTest_636, RecordNameEnvelope_636) {

    EXPECT_EQ(iptcDataSets.recordName(envelope), "Envelope");

}



TEST_F(IptcDataSetsTest_636, RecordNameApplication2_636) {

    EXPECT_EQ(iptcDataSets.recordName(application2), "Application2");

}



TEST_F(IptcDataSetsTest_636, RecordNameUnknown_636) {

    EXPECT_EQ(iptcDataSets.recordName(0x1234), "0x1234");

}



TEST_F(IptcDataSetsTest_636, RecordNameBoundaryLow_636) {

    EXPECT_EQ(iptcDataSets.recordName(0), "0x0000");

}



TEST_F(IptcDataSetsTest_636, RecordNameBoundaryHigh_636) {

    EXPECT_EQ(iptcDataSets.recordName(0xFFFF), "0xffff");

}
