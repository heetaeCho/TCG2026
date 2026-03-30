#include <gtest/gtest.h>

#include "exiv2/datasets.hpp"



using namespace Exiv2;



class IptcDataSetsTest_631 : public ::testing::Test {

protected:

    IptcDataSets iptcDataSets;

};



TEST_F(IptcDataSetsTest_631, dataSetTitle_ReturnsKnownTitleForValidNumberAndRecordId_631) {

    uint16_t number = 2; // Example valid number

    uint16_t recordId = 0; // Example valid record ID



    const char* title = iptcDataSets.dataSetTitle(number, recordId);

    EXPECT_STREQ(title, "Object Attribute Reference");

}



TEST_F(IptcDataSetsTest_631, dataSetTitle_ReturnsUnknownDataSetForInvalidNumberAndRecordId_631) {

    uint16_t number = 65534; // Example invalid number

    uint16_t recordId = 9999; // Example invalid record ID



    const char* title = iptcDataSets.dataSetTitle(number, recordId);

    EXPECT_STREQ(title, "Unknown dataset");

}



TEST_F(IptcDataSetsTest_631, dataSetTitle_ReturnsKnownTitleForAnotherValidNumberAndRecordId_631) {

    uint16_t number = 5; // Another example valid number

    uint16_t recordId = 0; // Example valid record ID



    const char* title = iptcDataSets.dataSetTitle(number, recordId);

    EXPECT_STREQ(title, "Coded Character Set");

}



TEST_F(IptcDataSetsTest_631, dataSetTitle_ReturnsUnknownDataSetForValidNumberAndInvalidRecordId_631) {

    uint16_t number = 2; // Example valid number

    uint16_t recordId = 9999; // Example invalid record ID



    const char* title = iptcDataSets.dataSetTitle(number, recordId);

    EXPECT_STREQ(title, "Unknown dataset");

}



TEST_F(IptcDataSetsTest_631, dataSetTitle_ReturnsKnownTitleForValidNumberAndAnotherInvalidRecordId_631) {

    uint16_t number = 5; // Another example valid number

    uint16_t recordId = 9998; // Example another invalid record ID



    const char* title = iptcDataSets.dataSetTitle(number, recordId);

    EXPECT_STREQ(title, "Unknown dataset");

}
