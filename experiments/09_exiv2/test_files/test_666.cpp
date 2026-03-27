#include <gtest/gtest.h>

#include "exiv2/iptc.hpp"



namespace Exiv2 {

    class MockIptcKey : public IptcKey {

    public:

        MOCK_CONST_METHOD0(recordName, std::string());

    };

}



class IptcdatumTest_666 : public ::testing::Test {

protected:

    Exiv2::MockIptcKey mockKey;

    Exiv2::Iptcdatum iptcdatum;



    IptcdatumTest_666() : iptcdatum(mockKey, nullptr) {}

};



TEST_F(IptcdatumTest_666, RecordName_ReturnsEmptyStringWhenKeyIsNull_666) {

    EXPECT_CALL(mockKey, recordName()).WillOnce(::testing::Return(""));

    EXPECT_EQ(iptcdatum.recordName(), "");

}



TEST_F(IptcdatumTest_666, RecordName_ReturnsExpectedValueFromKey_666) {

    EXPECT_CALL(mockKey, recordName()).WillOnce(::testing::Return("expectedRecordName"));

    EXPECT_EQ(iptcdatum.recordName(), "expectedRecordName");

}
