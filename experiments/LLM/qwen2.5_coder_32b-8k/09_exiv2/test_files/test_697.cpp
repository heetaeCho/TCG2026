#include <gtest/gtest.h>

#include "exiv2/iptc.hpp"

#include <vector>



using namespace Exiv2;



class IptcDataTest_697 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary data or state before each test.

        iptcData = IptcData();

        

        // Adding some dummy data for testing

        iptcData.add(IptcKey("Iptc.Application2.Caption"), new Value(std::string("Test Caption")));

        iptcData.add(IptcKey("Iptc.Application2.WriterEditor"), new Value(std::string("John Doe")));

    }



    IptcData iptcData;

};



TEST_F(IptcDataTest_697, FindId_NormalOperation_697) {

    // Test finding a valid ID

    uint16_t dataset = 0x54; // Application2

    uint16_t record = 0x02; // Caption

    auto it = iptcData.findId(dataset, record);

    ASSERT_NE(it, iptcData.end());

}



TEST_F(IptcDataTest_697, FindId_NotFound_697) {

    // Test finding a non-existent ID

    uint16_t dataset = 0x54; // Application2

    uint16_t record = 0xFF; // Non-existent record

    auto it = iptcData.findId(dataset, record);

    ASSERT_EQ(it, iptcData.end());

}



TEST_F(IptcDataTest_697, FindId_BoundaryConditions_697) {

    // Test finding with boundary values for dataset and record

    uint16_t minDataset = 0x00;

    uint16_t maxRecord = 0xFFFF;

    auto it = iptcData.findId(minDataset, maxRecord);

    ASSERT_EQ(it, iptcData.end());



    uint16_t maxDataset = 0xFF;

    uint16_t minRecord = 0x00;

    it = iptcData.findId(maxDataset, minRecord);

    ASSERT_EQ(it, iptcData.end());

}



TEST_F(IptcDataTest_697, FindId_EmptyIptcData_697) {

    // Test finding in an empty IptcData

    IptcData emptyIptcData;

    uint16_t dataset = 0x54; // Application2

    uint16_t record = 0x02; // Caption

    auto it = emptyIptcData.findId(dataset, record);

    ASSERT_EQ(it, emptyIptcData.end());

}
