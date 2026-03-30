#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/iptc.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;



class MockValue : public Value {

public:

    MOCK_CONST_METHOD0(count, size_t());

};



TEST_F(MockValueTest_677, Count_ReturnsZero_WhenNoValueSet_677) {

    MockValue mockValue(TypeId::asciiString);

    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(0));



    Iptcdatum iptcDatum(IptcKey("Iptc.EnvelopeModel.Version"), &mockValue);

    EXPECT_EQ(iptcDatum.count(), 0);

}



TEST_F(MockValueTest_677, Count_ReturnsOne_WhenSingleValueSet_677) {

    MockValue mockValue(TypeId::asciiString);

    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(1));



    Iptcdatum iptcDatum(IptcKey("Iptc.EnvelopeModel.Version"), &mockValue);

    EXPECT_EQ(iptcDatum.count(), 1);

}



TEST_F(MockValueTest_677, Count_ReturnsMultiple_WhenMultipleValuesSet_677) {

    MockValue mockValue(TypeId::asciiString);

    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(5));



    Iptcdatum iptcDatum(IptcKey("Iptc.EnvelopeModel.Version"), &mockValue);

    EXPECT_EQ(iptcDatum.count(), 5);

}



TEST_F(MockValueTest_677, Count_ReturnsZero_WhenNullptrPassed_677) {

    Iptcdatum iptcDatum(IptcKey("Iptc.EnvelopeModel.Version"), nullptr);

    EXPECT_EQ(iptcDatum.count(), 0);

}
