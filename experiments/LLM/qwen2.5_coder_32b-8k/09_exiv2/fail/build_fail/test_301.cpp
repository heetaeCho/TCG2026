#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"

#include "value.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class TiffEntryBaseTest : public ::testing::Test {

protected:

    TiffEntryBase* tiffEntryBase;

    TypeId sampleTypeId = static_cast<TypeId>(1);

    Value::UniquePtr sampleValue;



    void SetUp() override {

        tiffEntryBase = new TiffEntryBase(0x123, ifdExif, ttLong);

        sampleValue = Value::create(sampleTypeId);

    }



    void TearDown() override {

        delete tiffEntryBase;

    }

};



TEST_F(TiffEntryBaseTest_301, SetValueWithValidValue_301) {

    tiffEntryBase->setValue(std::move(sampleValue));

    EXPECT_NE(tiffEntryBase->pValue(), nullptr);

}



TEST_F(TiffEntryBaseTest_301, SetValueWithNullValue_301) {

    Value::UniquePtr nullValue;

    tiffEntryBase->setValue(std::move(nullValue));

    EXPECT_EQ(tiffEntryBase->pValue(), nullptr);

}



TEST_F(TiffEntryBaseTest_301, SetValueUpdatesCountAndType_301) {

    sampleValue->count() = 5;

    tiffEntryBase->setValue(std::move(sampleValue));

    EXPECT_EQ(tiffEntryBase->pValue()->count(), 5);

    EXPECT_EQ(static_cast<TiffType>(tiffEntryBase->tiffType()), toTiffType(sampleTypeId));

}



TEST_F(TiffEntryBaseTest_301, SetValueWithDifferentTypes_301) {

    TypeId anotherTypeId = static_cast<TypeId>(2);

    Value::UniquePtr anotherValue = Value::create(anotherTypeId);

    tiffEntryBase->setValue(std::move(anotherValue));

    EXPECT_EQ(static_cast<TiffType>(tiffEntryBase->tiffType()), toTiffType(anotherTypeId));

}



TEST_F(TiffEntryBaseTest_301, SetValueWithZeroCount_301) {

    sampleValue->count() = 0;

    tiffEntryBase->setValue(std::move(sampleValue));

    EXPECT_EQ(tiffEntryBase->pValue()->count(), 0);

}
