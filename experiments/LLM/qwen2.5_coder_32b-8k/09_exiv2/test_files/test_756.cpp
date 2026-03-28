#include <gtest/gtest.h>

#include "exiv2/exif.hpp"



using namespace Exiv2;



class ExifdatumTest : public ::testing::Test {

protected:

    std::unique_ptr<ExifKey> key = std::make_unique<ExifKey>("key_name");

    Value dummyValue;

    Exifdatum exifDatum{*key, &dummyValue};

};



TEST_F(ExifdatumTest_Count_756, Count_ReturnsZeroWhenNoValueSet_756) {

    Exifdatum exifDatumWithoutValue{*key, nullptr};

    EXPECT_EQ(exifDatumWithoutValue.count(), 0);

}



TEST_F(ExifdatumTest_Count_756, Count_ReturnsNonZeroWhenValueSet_756) {

    EXPECT_NE(exifDatum.count(), 0); // Assuming dummyValue has a count > 0

}



TEST_F(ExifdatumTest_SetValue_756, SetValue_ChangesCountAppropriately_756) {

    size_t initialCount = exifDatum.count();

    Value newValue;

    exifDatum.setValue(&newValue);

    EXPECT_NE(exifDatum.count(), initialCount); // Assuming newValue has a different count

}



TEST_F(ExifdatumTest_SetValue_String_756, SetValueWithString_ChangesCountAppropriately_756) {

    size_t initialCount = exifDatum.count();

    exifDatum.setValue("new_value");

    EXPECT_NE(exifDatum.count(), initialCount); // Assuming setting a string changes count

}



TEST_F(ExifdatumTest_SetValue_UInt16_756, SetValueWithUInt16_ChangesCountAppropriately_756) {

    size_t initialCount = exifDatum.count();

    exifDatum = static_cast<uint16_t>(123);

    EXPECT_NE(exifDatum.count(), initialCount); // Assuming setting a uint16 changes count

}



TEST_F(ExifdatumTest_SetValue_UInt32_756, SetValueWithUInt32_ChangesCountAppropriately_756) {

    size_t initialCount = exifDatum.count();

    exifDatum = static_cast<uint32_t>(456);

    EXPECT_NE(exifDatum.count(), initialCount); // Assuming setting a uint32 changes count

}



TEST_F(ExifdatumTest_SetValue_Int16_756, SetValueWithInt16_ChangesCountAppropriately_756) {

    size_t initialCount = exifDatum.count();

    exifDatum = static_cast<int16_t>(-123);

    EXPECT_NE(exifDatum.count(), initialCount); // Assuming setting an int16 changes count

}



TEST_F(ExifdatumTest_SetValue_Int32_756, SetValueWithInt32_ChangesCountAppropriately_756) {

    size_t initialCount = exifDatum.count();

    exifDatum = static_cast<int32_t>(-456);

    EXPECT_NE(exifDatum.count(), initialCount); // Assuming setting an int32 changes count

}



TEST_F(ExifdatumTest_SetValue_Rational_756, SetValueWithRational_ChangesCountAppropriately_756) {

    size_t initialCount = exifDatum.count();

    Rational rationalValue(1, 2);

    exifDatum.setValue(rationalValue);

    EXPECT_NE(exifDatum.count(), initialCount); // Assuming setting a Rational changes count

}



TEST_F(ExifdatumTest_SetDataArea_756, SetDataArea_ReturnsSuccess_756) {

    byte buffer[] = {0x1, 0x2, 0x3};

    EXPECT_EQ(exifDatum.setDataArea(buffer, sizeof(buffer)), 0); // Assuming setDataArea returns 0 on success

}



TEST_F(ExifdatumTest_SetDataArea_InvalidSize_756, SetDataAreaWithZeroSize_ReturnsSuccess_756) {

    byte buffer[] = {};

    EXPECT_EQ(exifDatum.setDataArea(buffer, sizeof(buffer)), 0); // Assuming setDataArea returns 0 on success

}



TEST_F(ExifdatumTest_SetValue_ValuePtrNull_756, SetValueWithNullPointer_DoesNotCrash_756) {

    exifDatum.setValue(nullptr);

    EXPECT_EQ(exifDatum.count(), 0); // Assuming count is zero after setting null value

}
