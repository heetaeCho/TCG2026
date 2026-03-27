#include <gtest/gtest.h>

#include <exiv2/datasets.hpp>



using namespace Exiv2;



class IptcDataSetsTest_634 : public ::testing::Test {

protected:

    IptcDataSets iptcDataSets;

};



TEST_F(IptcDataSetsTest_634, NormalOperation_ReturnsRepeatable_True_634) {

    // Assuming a known dataset number and recordId that is repeatable

    uint16_t number = 2; // Example value

    uint16_t recordId = 10; // Example value

    EXPECT_TRUE(iptcDataSets.dataSetRepeatable(number, recordId));

}



TEST_F(IptcDataSetsTest_634, NormalOperation_ReturnsRepeatable_False_634) {

    // Assuming a known dataset number and recordId that is not repeatable

    uint16_t number = 3; // Example value

    uint16_t recordId = 20; // Example value

    EXPECT_FALSE(iptcDataSets.dataSetRepeatable(number, recordId));

}



TEST_F(IptcDataSetsTest_634, BoundaryCondition_RecordId_Zero_634) {

    // Test with recordId at the boundary (0)

    uint16_t number = 2; // Example value

    uint16_t recordId = 0;

    EXPECT_EQ(iptcDataSets.dataSetRepeatable(number, recordId), unknownDataSet.repeatable_);

}



TEST_F(IptcDataSetsTest_634, BoundaryCondition_RecordId_MaxValue_634) {

    // Test with recordId at the boundary (max uint16_t value)

    uint16_t number = 2; // Example value

    uint16_t recordId = UINT16_MAX;

    EXPECT_EQ(iptcDataSets.dataSetRepeatable(number, recordId), unknownDataSet.repeatable_);

}



TEST_F(IptcDataSetsTest_634, BoundaryCondition_Number_Zero_634) {

    // Test with number at the boundary (0)

    uint16_t number = 0;

    uint16_t recordId = 10; // Example value

    EXPECT_EQ(iptcDataSets.dataSetRepeatable(number, recordId), unknownDataSet.repeatable_);

}



TEST_F(IptcDataSetsTest_634, BoundaryCondition_Number_MaxValue_634) {

    // Test with number at the boundary (max uint16_t value)

    uint16_t number = UINT16_MAX;

    uint16_t recordId = 10; // Example value

    EXPECT_EQ(iptcDataSets.dataSetRepeatable(number, recordId), unknownDataSet.repeatable_);

}



TEST_F(IptcDataSetsTest_634, UnknownDataset_ReturnsDefaultRepeatable_True_634) {

    // Test with a non-existent dataset (should return the default repeatable value)

    uint16_t number = 9999; // Non-existent dataset number

    uint16_t recordId = 9999; // Non-existent recordId

    EXPECT_TRUE(iptcDataSets.dataSetRepeatable(number, recordId));

}
