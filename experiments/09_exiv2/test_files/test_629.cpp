#include <gtest/gtest.h>

#include "exiv2/datasets.hpp"



namespace {



class IptcDataSetsTest_629 : public ::testing::Test {

protected:

    Exiv2::IptcDataSets iptcDataSets;

};



TEST_F(IptcDataSetsTest_629, dataSetType_NormalOperation_629) {

    uint16_t number = 2; // Example valid number

    uint16_t recordId = 0; // Example valid record ID

    Exiv2::TypeId expectedType = Exiv2::string;

    EXPECT_EQ(iptcDataSets.dataSetType(number, recordId), expectedType);

}



TEST_F(IptcDataSetsTest_629, dataSetType_BoundaryCondition_LowerBound_629) {

    uint16_t number = 0; // Lower bound for number

    uint16_t recordId = 0; // Lower bound for record ID

    Exiv2::TypeId expectedType = Exiv2::unknownDataSet.type_;

    EXPECT_EQ(iptcDataSets.dataSetType(number, recordId), expectedType);

}



TEST_F(IptcDataSetsTest_629, dataSetType_BoundaryCondition_UpperBound_629) {

    uint16_t number = 65535; // Upper bound for number

    uint16_t recordId = 65535; // Upper bound for record ID

    Exiv2::TypeId expectedType = Exiv2::unknownDataSet.type_;

    EXPECT_EQ(iptcDataSets.dataSetType(number, recordId), expectedType);

}



TEST_F(IptcDataSetsTest_629, dataSetType_ExceptionalCase_InvalidNumber_629) {

    uint16_t number = 999; // Invalid number

    uint16_t recordId = 0;

    Exiv2::TypeId expectedType = Exiv2::unknownDataSet.type_;

    EXPECT_EQ(iptcDataSets.dataSetType(number, recordId), expectedType);

}



TEST_F(IptcDataSetsTest_629, dataSetType_ExceptionalCase_InvalidRecordId_629) {

    uint16_t number = 0;

    uint16_t recordId = 999; // Invalid record ID

    Exiv2::TypeId expectedType = Exiv2::unknownDataSet.type_;

    EXPECT_EQ(iptcDataSets.dataSetType(number, recordId), expectedType);

}



} // namespace
