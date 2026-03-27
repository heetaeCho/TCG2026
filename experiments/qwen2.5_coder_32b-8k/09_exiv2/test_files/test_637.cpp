#include <gtest/gtest.h>

#include <exiv2/datasets.hpp>



using namespace Exiv2;



class IptcDataSetsTest_637 : public ::testing::Test {

protected:

    IptcDataSets iptcDataSets;

};



TEST_F(IptcDataSetsTest_637, RecordDesc_Envelope_637) {

    EXPECT_STREQ(iptcDataSets.recordDesc(envelope), "IIM envelope record");

}



TEST_F(IptcDataSetsTest_637, RecordDesc_Application2_637) {

    EXPECT_STREQ(iptcDataSets.recordDesc(application2), "IIM application record 2");

}



TEST_F(IptcDataSetsTest_637, RecordDesc_UnknownRecord_637) {

    uint16_t invalidId = 999; // Assuming 999 is not envelope or application2

    EXPECT_STREQ(iptcDataSets.recordDesc(invalidId), "(invalid)");

}



TEST_F(IptcDataSetsTest_637, RecordDesc_BoundaryCondition_Lowest_637) {

    uint16_t lowestId = 0;

    EXPECT_STREQ(iptcDataSets.recordDesc(lowestId), "(invalid)");

}



TEST_F(IptcDataSetsTest_637, RecordDesc_BoundaryCondition_Highest_637) {

    uint16_t highestId = 65535; // Assuming this is outside the valid range

    EXPECT_STREQ(iptcDataSets.recordDesc(highestId), "(invalid)");

}
