#include <gtest/gtest.h>

#include "exiv2/datasets.hpp"



using namespace Exiv2;



class IptcDataSetsTest_632 : public ::testing::Test {

protected:

    IptcDataSets iptcDataSets;

};



TEST_F(IptcDataSetsTest_632, dataSetDesc_ValidNumberAndRecordId_632) {

    const char* desc = iptcDataSets.dataSetDesc(2, 0); // Example valid number and record ID

    EXPECT_NE(desc, unknownDataSet.desc_);

}



TEST_F(IptcDataSetsTest_632, dataSetDesc_InvalidNumberAndRecordId_632) {

    const char* desc = iptcDataSets.dataSetDesc(9999, 9999); // Example invalid number and record ID

    EXPECT_STREQ(desc, unknownDataSet.desc_);

}



TEST_F(IptcDataSetsTest_632, dataSetDesc_BoundaryCondition_MinNumberAndRecordId_632) {

    const char* desc = iptcDataSets.dataSetDesc(0, 0); // Minimum valid number and record ID

    EXPECT_NE(desc, unknownDataSet.desc_);

}



TEST_F(IptcDataSetsTest_632, dataSetDesc_BoundaryCondition_MaxNumberAndRecordId_632) {

    const char* desc = iptcDataSets.dataSetDesc(65534, 1); // Example of a high number and valid record ID

    EXPECT_NE(desc, unknownDataSet.desc_);

}



TEST_F(IptcDataSetsTest_632, dataSetDesc_BoundaryCondition_MaxRecordId_632) {

    const char* desc = iptcDataSets.dataSetDesc(2, 5); // Example of a valid number and high record ID

    EXPECT_NE(desc, unknownDataSet.desc_);

}



TEST_F(IptcDataSetsTest_632, dataSetDesc_UnknownDataSet_ReturnsDefaultDescription_632) {

    const char* desc = iptcDataSets.dataSetDesc(9999, 0); // Invalid number but valid record ID

    EXPECT_STREQ(desc, unknownDataSet.desc_);

}
