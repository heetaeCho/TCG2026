#include <gtest/gtest.h>

#include "exiv2/datasets.hpp"



using namespace Exiv2;



class IptcDataSetsTest_627 : public ::testing::Test {

protected:

    IptcDataSets iptcDataSets;

};



TEST_F(IptcDataSetsTest_627, EnvelopeRecordList_ReturnsValidPointer_627) {

    const DataSet* records = iptcDataSets.envelopeRecordList();

    EXPECT_NE(records, nullptr);

}



TEST_F(IptcDataSetsTest_627, EnvelopeRecordList_ReturnsFirstElementCorrectly_627) {

    const DataSet* records = iptcDataSets.envelopeRecordList();

    if (records != nullptr) {

        EXPECT_EQ(records[0].number_, IptcDataSets::ModelVersion);

        EXPECT_STREQ(records[0].name_, "ModelVersion");

        EXPECT_STREQ(records[0].title_, "Model Version");

    }

}



TEST_F(IptcDataSetsTest_627, EnvelopeRecordList_LastElementIsInvalid_627) {

    const DataSet* records = iptcDataSets.envelopeRecordList();

    if (records != nullptr) {

        while (records->number_ != 65535) {

            ++records;

        }

        EXPECT_EQ(records->number_, 65535);

        EXPECT_STREQ(records->name_, "(Invalid)");

        EXPECT_STREQ(records->title_, "(Invalid)");

    }

}



TEST_F(IptcDataSetsTest_627, EnvelopeRecordList_HandlesBoundaryConditions_627) {

    const DataSet* records = iptcDataSets.envelopeRecordList();

    if (records != nullptr) {

        // Test the first element

        EXPECT_EQ(records[0].number_, IptcDataSets::ModelVersion);

        

        // Navigate to the last element and test it

        while (records->number_ != 65535) {

            ++records;

        }

        EXPECT_STREQ(records->name_, "(Invalid)");

    }

}
