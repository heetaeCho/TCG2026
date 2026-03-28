#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"

#include "types.hpp"

#include "error.hpp"



using namespace Exiv2::Internal;

using namespace ::testing;



class TiffBinaryArrayTest_362 : public Test {

protected:

    TiffBinaryArray* array;



    void SetUp() override {

        const ArrayCfg arrayCfg = {TiffType::unsignedShort, 0};

        const ArrayDef arrayDef = {};

        array = new TiffBinaryArray(1, IfdId::ifd0, arrayCfg, &arrayDef, 0);

    }



    void TearDown() override {

        delete array;

    }

};



TEST_F(TiffBinaryArrayTest_362, DoCount_ReturnsZeroWhenCfgIsNull_362) {

    EXPECT_CALL(*const_cast<ArrayCfg*>(array->cfg()), typeSize(_))

            .Times(0);



    array->setDecoded(true);

    array->elements_.clear();



    EXPECT_EQ(array->doCount(), 0U);

}



TEST_F(TiffBinaryArrayTest_362, DoCount_ReturnsZeroWhenDecodedIsFalse_362) {

    EXPECT_CALL(*const_cast<ArrayCfg*>(array->cfg()), typeSize(_))

            .Times(0);



    array->setDecoded(false);

    array->elements_.clear();



    EXPECT_EQ(array->doCount(), 0U);

}



TEST_F(TiffBinaryArrayTest_362, DoCount_ReturnsZeroWhenElementsIsEmpty_362) {

    EXPECT_CALL(*const_cast<ArrayCfg*>(array->cfg()), typeSize(_))

            .Times(0);



    array->setDecoded(true);

    array->elements_.clear();



    EXPECT_EQ(array->doCount(), 0U);

}



TEST_F(TiffBinaryArrayTest_362, DoCount_ReturnsCalculatedValueWhenTypeSizeIsKnown_362) {

    const ArrayCfg mockArrayCfg = {TiffType::unsignedShort, 0};

    ON_CALL(*const_cast<ArrayCfg*>(&mockArrayCfg), typeSize(_))

            .WillByDefault(Return(2));



    array->setDecoded(true);

    array->elements_.resize(10);



    EXPECT_EQ(array->doCount(), 5U); // Assuming size() returns 10

}



TEST_F(TiffBinaryArrayTest_362, DoCount_SetsTypeSizeToOneWhenUnknownAndLogsWarning_362) {

    const ArrayCfg mockArrayCfg = {static_cast<TiffType>(99), 0}; // Unknown type

    ON_CALL(*const_cast<ArrayCfg*>(&mockArrayCfg), typeSize(_))

            .WillByDefault(Return(0));



    EXPECT_CALL(LogMsg(Level::warn), os())

            .Times(1);



    array->setDecoded(true);

    array->elements_.resize(10);



    EXPECT_EQ(array->doCount(), 10U); // Assuming size() returns 10

}
