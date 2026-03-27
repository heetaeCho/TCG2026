#include <gtest/gtest.h>

#include "exiv2/iptc.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;



class IptcdatumTest : public ::testing::Test {

protected:

    Iptcdatum* iptcDatum;

    IptcKey key; // Assuming IptcKey has a default constructor



    void SetUp() override {

        iptcDatum = new Iptcdatum(key, nullptr);

    }



    void TearDown() override {

        delete iptcDatum;

    }

};



TEST_F(IptcdatumTest_687, AssignmentOperatorUint16_NormalOperation_687) {

    uint16_t value = 12345;

    *iptcDatum = value;

    EXPECT_EQ(iptcDatum->toInt64(0), static_cast<int64_t>(value));

}



TEST_F(IptcdatumTest_687, AssignmentOperatorUint16_BoundaryCondition_MaxValue_687) {

    uint16_t maxValue = std::numeric_limits<uint16_t>::max();

    *iptcDatum = maxValue;

    EXPECT_EQ(iptcDatum->toInt64(0), static_cast<int64_t>(maxValue));

}



TEST_F(IptcdatumTest_687, AssignmentOperatorUint16_BoundaryCondition_MinValue_687) {

    uint16_t minValue = std::numeric_limits<uint16_t>::min();

    *iptcDatum = minValue;

    EXPECT_EQ(iptcDatum->toInt64(0), static_cast<int64_t>(minValue));

}



TEST_F(IptcdatumTest_687, Count_ReturnsCorrectCount_687) {

    uint16_t value = 12345;

    *iptcDatum = value;

    EXPECT_EQ(iptcDatum->count(), 1);

}
