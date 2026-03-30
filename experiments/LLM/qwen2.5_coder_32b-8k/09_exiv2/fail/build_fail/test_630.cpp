#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/datasets.hpp"



using namespace Exiv2;



class IptcDataSetsTest : public ::testing::Test {

protected:

    // No additional setup or teardown required for this test suite.

};



TEST_F(IptcDataSetsTest_630, NormalOperation_DataSetNameFound_630) {

    EXPECT_EQ(IptcDataSets::dataSetName(0x0052, 2), "ObjectName");

}



TEST_F(IptcDataSetsTest_630, NormalOperation_DataSetNameNotFound_ReturnsHex_630) {

    EXPECT_EQ(IptcDataSets::dataSetName(0xFFFF, 99), "0xffff");

}



TEST_F(IptcDataSetsTest_630, BoundaryCondition_ZeroRecordId_630) {

    EXPECT_EQ(IptcDataSets::dataSetName(0x0052, 0), "ObjectName");

}



TEST_F(IptcDataSetsTest_630, ExceptionalCase_InvalidDataSetNumber_ReturnsHex_630) {

    EXPECT_EQ(IptcDataSets::dataSetName(0xFFFF, 2), "0xffff");

}



TEST_F(IptcDataSetsTest_630, BoundaryCondition_MaxRecordId_630) {

    // Assuming there is no record with ID 99 in the implementation

    EXPECT_EQ(IptcDataSets::dataSetName(0x0052, 99), "0x0052");

}



TEST_F(IptcDataSetsTest_630, BoundaryCondition_ZeroDataSetNumber_630) {

    // Assuming there is no dataset with number 0 in the implementation

    EXPECT_EQ(IptcDataSets::dataSetName(0x0000, 2), "0x0000");

}



TEST_F(IptcDataSetsTest_630, NormalOperation_DataSetTitleFound_630) {

    EXPECT_STREQ(IptcDataSets::dataSetTitle(0x0052, 2), "Object Name");

}



TEST_F(IptcDataSetsTest_630, ExceptionalCase_DataSetTitleNotFound_ReturnsNull_630) {

    EXPECT_STREQ(IptcDataSets::dataSetTitle(0xFFFF, 99), nullptr);

}



TEST_F(IptcDataSetsTest_630, NormalOperation_DataSetDescFound_630) {

    std::string expected = "The name given to the image file by the creator or owner.";

    EXPECT_STREQ(IptcDataSets::dataSetDesc(0x0052, 2), expected.c_str());

}



TEST_F(IptcDataSetsTest_630, ExceptionalCase_DataSetDescNotFound_ReturnsNull_630) {

    EXPECT_STREQ(IptcDataSets::dataSetDesc(0xFFFF, 99), nullptr);

}



TEST_F(IptcDataSetsTest_630, NormalOperation_DataSetPsNameFound_630) {

    EXPECT_STREQ(IptcDataSets::dataSetPsName(0x0052, 2), "ObjectName");

}



TEST_F(IptcDataSetsTest_630, ExceptionalCase_DataSetPsNameNotFound_ReturnsNull_630) {

    EXPECT_STREQ(IptcDataSets::dataSetPsName(0xFFFF, 99), nullptr);

}



TEST_F(IptcDataSetsTest_630, NormalOperation_DataSetRepeatableTrue_630) {

    EXPECT_TRUE(IptcDataSets::dataSetRepeatable(0x005A, 2));

}



TEST_F(IptcDataSetsTest_630, NormalOperation_DataSetRepeatableFalse_630) {

    EXPECT_FALSE(IptcDataSets::dataSetRepeatable(0x0052, 2));

}



TEST_F(IptcDataSetsTest_630, ExceptionalCase_DataSetRepeatableNotFound_ReturnsFalse_630) {

    EXPECT_FALSE(IptcDataSets::dataSetRepeatable(0xFFFF, 99));

}



TEST_F(IptcDataSetsTest_630, NormalOperation_RecordNameFound_630) {

    EXPECT_EQ(IptcDataSets::recordName(2), "Envelope Record");

}



TEST_F(IptcDataSetsTest_630, ExceptionalCase_RecordNameNotFound_ReturnsEmptyString_630) {

    EXPECT_EQ(IptcDataSets::recordName(99), "");

}



TEST_F(IptcDataSetsTest_630, NormalOperation_RecordDescFound_630) {

    std::string expected = "Includes data about the image file itself.";

    EXPECT_STREQ(IptcDataSets::recordDesc(2), expected.c_str());

}



TEST_F(IptcDataSetsTest_630, ExceptionalCase_RecordDescNotFound_ReturnsNull_630) {

    EXPECT_STREQ(IptcDataSets::recordDesc(99), nullptr);

}
