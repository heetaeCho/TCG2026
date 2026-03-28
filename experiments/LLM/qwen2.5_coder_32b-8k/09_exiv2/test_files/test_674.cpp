#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/iptc.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;



class IptcdatumTest : public ::testing::Test {

protected:

    Value* mockValue;

    Iptcdatum* iptcDatum;



    void SetUp() override {

        mockValue = new Value(asciiString);

        iptcDatum = new Iptcdatum(IptcKey("IPTC", 2, 0x0005), mockValue);

    }



    void TearDown() override {

        delete iptcDatum;

        delete mockValue;

    }

};



TEST_F(IptcdatumTest_674, TypeId_ReturnsCorrectTypeForAsciiString_674) {

    EXPECT_EQ(iptcDatum->typeId(), asciiString);

}



TEST_F(IptcdatumTest_674, TypeId_ReturnsInvalidTypeIdWhenValueIsNull_674) {

    iptcDatum->setValue(nullptr);

    EXPECT_EQ(iptcDatum->typeId(), invalidTypeId);

}



TEST_F(IptcdatumTest_674, TypeId_ReturnsCorrectTypeForUnsignedByte_674) {

    delete mockValue;

    mockValue = new Value(unsignedByte);

    iptcDatum->setValue(mockValue);

    EXPECT_EQ(iptcDatum->typeId(), unsignedByte);

}



TEST_F(IptcdatumTest_674, TypeId_ReturnsCorrectTypeForSignedShort_674) {

    delete mockValue;

    mockValue = new Value(signedShort);

    iptcDatum->setValue(mockValue);

    EXPECT_EQ(iptcDatum->typeId(), signedShort);

}



TEST_F(IptcdatumTest_674, TypeId_ReturnsCorrectTypeForUndefined_674) {

    delete mockValue;

    mockValue = new Value(undefined);

    iptcDatum->setValue(mockValue);

    EXPECT_EQ(iptcDatum->typeId(), undefined);

}
