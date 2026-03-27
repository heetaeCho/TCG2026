#include <gtest/gtest.h>

#include "exiv2/datasets.hpp"



namespace Exiv2 {

    class IptcDataSets;

}



class IptcDataSetsTest_633 : public ::testing::Test {

protected:

    Exiv2::IptcDataSets iptcDataSets;

};



TEST_F(IptcDataSetsTest_633, DataSetPsName_ReturnsPhotoshopNameForKnownDataSet_633) {

    // Arrange

    uint16_t number = 2; // Example known dataset number

    uint16_t recordId = 0; // Example known record ID



    // Act

    const char* result = iptcDataSets.dataSetPsName(number, recordId);



    // Assert

    EXPECT_STREQ(result, "PhotoshopName"); // Replace with actual expected string if known

}



TEST_F(IptcDataSetsTest_633, DataSetPsName_ReturnsUnknownDataSetForInvalidNumber_633) {

    // Arrange

    uint16_t number = 9999; // Invalid dataset number

    uint16_t recordId = 0;



    // Act

    const char* result = iptcDataSets.dataSetPsName(number, recordId);



    // Assert

    EXPECT_STREQ(result, "Unknown dataset");

}



TEST_F(IptcDataSetsTest_633, DataSetPsName_ReturnsUnknownDataSetForInvalidRecordId_633) {

    // Arrange

    uint16_t number = 2; // Example known dataset number

    uint16_t recordId = 9999; // Invalid record ID



    // Act

    const char* result = iptcDataSets.dataSetPsName(number, recordId);



    // Assert

    EXPECT_STREQ(result, "Unknown dataset");

}



TEST_F(IptcDataSetsTest_633, DataSetPsName_ReturnsUnknownDataSetForBothInvalidNumberAndRecordId_633) {

    // Arrange

    uint16_t number = 9999; // Invalid dataset number

    uint16_t recordId = 9999; // Invalid record ID



    // Act

    const char* result = iptcDataSets.dataSetPsName(number, recordId);



    // Assert

    EXPECT_STREQ(result, "Unknown dataset");

}
