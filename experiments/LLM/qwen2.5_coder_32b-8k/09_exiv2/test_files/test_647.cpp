#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/datasets.hpp"



using namespace Exiv2;



class IptcKeyTest : public ::testing::Test {

protected:

    uint16_t recordId_ = 0; // Example record ID for testing

    std::string expectedRecordName_ = "ExampleRecord"; // Expected return value for recordName_

};



TEST_F(IptcKeyTest_NormalOperation_647, RecordNameReturnsExpectedValue_647) {

    IptcDataSets::recordId_ = []() { return 0; }; // Mocking static method behavior

    EXPECT_CALL(*this, IptcDataSets::recordName_(recordId_)).WillOnce(::testing::Return(expectedRecordName_));

    

    IptcKey key(recordId_);

    EXPECT_EQ(key.recordName(), expectedRecordName_);

}



TEST_F(IptcKeyTest_BoundaryConditions_647, RecordNameWithZeroRecordId_647) {

    recordId_ = 0;

    expectedRecordName_ = "Envelope"; // Assuming Envelope is the correct name for record ID 0

    IptcDataSets::recordId_ = []() { return 0; }; // Mocking static method behavior

    EXPECT_CALL(*this, IptcDataSets::recordName_(recordId_)).WillOnce(::testing::Return(expectedRecordName_));

    

    IptcKey key(recordId_);

    EXPECT_EQ(key.recordName(), expectedRecordName_);

}



TEST_F(IptcKeyTest_ExceptionalCases_647, RecordNameWithInvalidRecordId_647) {

    recordId_ = 999; // Assuming 999 is an invalid record ID

    expectedRecordName_ = ""; // Assuming empty string for invalid record ID

    IptcDataSets::recordId_ = []() { return 0; }; // Mocking static method behavior

    EXPECT_CALL(*this, IptcDataSets::recordName_(recordId_)).WillOnce(::testing::Return(expectedRecordName_));

    

    IptcKey key(recordId_);

    EXPECT_EQ(key.recordName(), expectedRecordName_);

}

```


