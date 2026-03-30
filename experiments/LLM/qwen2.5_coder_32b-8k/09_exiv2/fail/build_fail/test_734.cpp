#include <gtest/gtest.h>

#include "exiv2/exif.hpp"



using namespace Exiv2;



class ExifdatumTest_734 : public ::testing::Test {

protected:

    URational urationalValue;

    ExifKey exifKey("Exif.Image.Artist");

    Value* pValue = nullptr;

    Exifdatum exifdatum{exifKey, pValue};



    void SetUp() override {

        urationalValue.numerator(1);

        urationalValue.denominator(2);

    }



    void TearDown() override {

        delete pValue;

    }

};



TEST_F(ExifdatumTest_734, AssignmentOperatorURational_NormalOperation_734) {

    Exifdatum& result = exifdatum = urationalValue;

    EXPECT_EQ(&result, &exifdatum);

}



TEST_F(ExifdatumTest_734, AssignmentOperatorURational_BoundaryCondition_734) {

    URational boundaryValue;

    boundaryValue.numerator(std::numeric_limits<uint32_t>::max());

    boundaryValue.denominator(std::numeric_limits<uint32_t>::max());

    Exifdatum& result = exifdatum = boundaryValue;

    EXPECT_EQ(&result, &exifdatum);

}



TEST_F(ExifdatumTest_734, AssignmentOperatorURational_ExceptionalCase_734) {

    URational invalidRational;

    invalidRational.denominator(0); // Setting denominator to zero is likely an error

    try {

        exifdatum = invalidRational;

        FAIL() << "Expected exception not thrown";

    } catch (const Error&) {

        SUCCEED();

    }

}



TEST_F(ExifdatumTest_734, AssignmentOperatorURational_VerifyInternalState_734) {

    exifdatum = urationalValue;

    Rational rationalResult = exifdatum.toRational(0);

    EXPECT_EQ(rationalResult.numerator(), urationalValue.numerator());

    EXPECT_EQ(rationalResult.denominator(), urationalValue.denominator());

}
