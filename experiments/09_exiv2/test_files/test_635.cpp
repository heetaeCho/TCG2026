#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/datasets.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;



class IptcDataSetsTest : public ::testing::Test {

protected:

    IptcDataSets iptcDataSets;

};



TEST_F(IptcDataSetsTest_635, DataSetValidNameAndRecordId_635) {

    // Arrange

    std::string dataSetName = "SomeDataSet";

    uint16_t recordId = 2;



    // Act & Assert

    EXPECT_NO_THROW(iptcDataSets.dataSet(dataSetName, recordId));

}



TEST_F(IptcDataSetsTest_635, DataSetInvalidHexadecimalString_635) {

    // Arrange

    std::string dataSetName = "0xGHIJ";

    uint16_t recordId = 2;



    // Act & Assert

    EXPECT_THROW(iptcDataSets.dataSet(dataSetName, recordId), Error);

}



TEST_F(IptcDataSetsTest_635, DataSetValidHexadecimalString_635) {

    // Arrange

    std::string dataSetName = "0x1234";

    uint16_t recordId = 2;



    // Act & Assert

    EXPECT_NO_THROW(iptcDataSets.dataSet(dataSetName, recordId));

}



TEST_F(IptcDataSetsTest_635, DataSetBoundaryConditionZeroRecordId_635) {

    // Arrange

    std::string dataSetName = "SomeDataSet";

    uint16_t recordId = 0;



    // Act & Assert

    EXPECT_NO_THROW(iptcDataSets.dataSet(dataSetName, recordId));

}



TEST_F(IptcDataSetsTest_635, DataSetBoundaryConditionMaxRecordId_635) {

    // Arrange

    std::string dataSetName = "SomeDataSet";

    uint16_t recordId = UINT16_MAX;



    // Act & Assert

    EXPECT_NO_THROW(iptcDataSets.dataSet(dataSetName, recordId));

}



TEST_F(IptcDataSetsTest_635, DataSetInvalidEmptyString_635) {

    // Arrange

    std::string dataSetName = "";

    uint16_t recordId = 2;



    // Act & Assert

    EXPECT_THROW(iptcDataSets.dataSet(dataSetName, recordId), Error);

}
