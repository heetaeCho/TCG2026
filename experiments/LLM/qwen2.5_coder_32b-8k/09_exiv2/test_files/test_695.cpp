#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/iptc.hpp"

#include "exiv2/datasets.hpp"



namespace Exiv2 {



class IptcDatumMock : public Iptcdatum {

public:

    MOCK_CONST_METHOD0(record, uint16_t());

    MOCK_CONST_METHOD0(tag, uint16_t());

};



class IptcDataTest_695 : public ::testing::Test {

protected:

    IptcData iptcData;

};



TEST_F(IptcDataTest_695, AddUniqueIptcdatum_ReturnsZero_695) {

    IptcDatumMock mockIptcDatum;

    EXPECT_CALL(mockIptcDatum, record()).WillOnce(::testing::Return(2));

    EXPECT_CALL(mockIptcDatum, tag()).WillOnce(::testing::Return(5));



    int result = iptcData.add(mockIptcDatum);

    ASSERT_EQ(result, 0);

}



TEST_F(IptcDataTest_695, AddDuplicateNonRepeatableIptcdatum_ReturnsSix_695) {

    IptcDatumMock mockIptcDatum;

    EXPECT_CALL(mockIptcDatum, record()).WillRepeatedly(::testing::Return(2));

    EXPECT_CALL(mockIptcDatum, tag()).WillRepeatedly(::testing::Return(5));



    iptcData.add(mockIptcDatum);

    int result = iptcData.add(mockIptcDatum);

    ASSERT_EQ(result, 6);

}



TEST_F(IptcDataTest_695, AddRepeatableIptcdatum_Allowed_695) {

    IptcDatumMock mockIptcDatum;

    EXPECT_CALL(mockIptcDatum, record()).WillRepeatedly(::testing::Return(2));

    EXPECT_CALL(mockIptcDatum, tag()).WillRepeatedly(::testing::Return(1));



    iptcData.add(mockIptcDatum);

    int result = iptcData.add(mockIptcDatum);

    ASSERT_EQ(result, 0);

}



TEST_F(IptcDataTest_695, AddBoundaryConditions_ReturnsZeroOrSix_695) {

    IptcDatumMock mockIptcDatum;

    EXPECT_CALL(mockIptcDatum, record()).WillOnce(::testing::Return(2));

    EXPECT_CALL(mockIptcDatum, tag()).WillOnce(::testing::Return(0));



    int result = iptcData.add(mockIptcDatum);

    ASSERT_TRUE(result == 0 || result == 6);



    IptcDatumMock mockIptcDatum2;

    EXPECT_CALL(mockIptcDatum2, record()).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockIptcDatum2, tag()).WillOnce(::testing::Return(5));



    result = iptcData.add(mockIptcDatum2);

    ASSERT_TRUE(result == 0 || result == 6);

}



} // namespace Exiv2
