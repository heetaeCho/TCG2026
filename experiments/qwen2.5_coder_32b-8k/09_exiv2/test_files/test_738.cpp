#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;



class ExifdatumTest : public ::testing::Test {

protected:

    ExifKey key;

    Value value;

    Exifdatum exifDatum;



    ExifdatumTest() : key("Exif.Image.Artist"), value(TypeId::asciiString), exifDatum(key, &value) {}

};



TEST_F(ExifdatumTest_NormalOperation_738, AssignmentOperatorWithValue_738) {

    Value newValue(TypeId::asciiString);

    exifDatum = newValue;

}



TEST_F(ExifdatumTest_BoundaryConditions_738, AssignmentOperatorWithEmptyValue_738) {

    Value emptyValue(TypeId::undefined);

    exifDatum = emptyValue;

}



TEST_F(ExifdatumTest_ExceptionalCases_738, AssignmentOperatorWithInvalidType_738) {

    // Assuming there is no invalid type, but if there were, we could test for it here.

    Value newValue(TypeId::asciiString);

    exifDatum = newValue;  // This should not throw an exception with a valid type

}



TEST_F(ExifdatumTest_NormalOperation_738, AssignmentOperatorWithUInt16Value_738) {

    uint16_t newValue = 123;

    exifDatum = newValue;

}



TEST_F(ExifdatumTest_BoundaryConditions_738, AssignmentOperatorWithMaxUInt16Value_738) {

    uint16_t maxValue = std::numeric_limits<uint16_t>::max();

    exifDatum = maxValue;

}



TEST_F(ExifdatumTest_NormalOperation_738, AssignmentOperatorWithUInt32Value_738) {

    uint32_t newValue = 123456;

    exifDatum = newValue;

}



TEST_F(ExifdatumTest_BoundaryConditions_738, AssignmentOperatorWithMaxUInt32Value_738) {

    uint32_t maxValue = std::numeric_limits<uint32_t>::max();

    exifDatum = maxValue;

}



TEST_F(ExifdatumTest_NormalOperation_738, AssignmentOperatorWithStringValue_738) {

    std::string newValue = "New Artist";

    exifDatum = newValue;

}



TEST_F(ExifdatumTest_BoundaryConditions_738, AssignmentOperatorWithEmptyStringValue_738) {

    std::string emptyString = "";

    exifDatum = emptyString;

}
