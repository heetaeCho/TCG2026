#include <gtest/gtest.h>

#include "exiv2/iptc.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;



// Mock class for Value

class MockValue : public Value {

public:

    MOCK_METHOD(int64_t, toInt64, (size_t n) const, (override));

};



TEST_F(IptcdatumTest_681, ToInt64_ReturnsCorrectValue_681) {

    MockValue mockValue;

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(42));



    Iptcdatum iptcDatum(IptcKey(), &mockValue);



    int64_t result = iptcDatum.toInt64(0);

    EXPECT_EQ(result, 42);

}



TEST_F(IptcdatumTest_681, ToInt64_ReturnsNegativeOneWhenNoValue_681) {

    Iptcdatum iptcDatum(IptcKey(), nullptr);



    int64_t result = iptcDatum.toInt64(0);

    EXPECT_EQ(result, -1);

}



TEST_F(IptcdatumTest_681, ToInt64_BoundaryConditionZeroIndex_681) {

    MockValue mockValue;

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(0));



    Iptcdatum iptcDatum(IptcKey(), &mockValue);



    int64_t result = iptcDatum.toInt64(0);

    EXPECT_EQ(result, 0);

}



TEST_F(IptcdatumTest_681, ToInt64_BoundaryConditionLargeIndex_681) {

    MockValue mockValue;

    EXPECT_CALL(mockValue, toInt64(1000000)).WillOnce(::testing::Return(12345));



    Iptcdatum iptcDatum(IptcKey(), &mockValue);



    int64_t result = iptcDatum.toInt64(1000000);

    EXPECT_EQ(result, 12345);

}
