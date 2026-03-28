#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"



using namespace Exiv2;

using ::testing::Return;



class XmpArrayValueTest_851 : public ::testing::Test {

protected:

    XmpArrayValue xmpArrayValue_{TypeId::xmpText};



    void SetUp() override {

        // Initialize the object if necessary

    }



    void TearDown() override {

        // Clean up if necessary

    }

};



TEST_F(XmpArrayValueTest_851, Count_ReturnsZeroForEmpty_851) {

    EXPECT_EQ(xmpArrayValue_.count(), 0);

}



TEST_F(XmpArrayValueTest_851, ToRational_ThrowsIfIndexOutOfRange_851) {

    EXPECT_THROW(xmpArrayValue_.toRational(0), std::out_of_range);

}



TEST_F(XmpArrayValueTest_851, Read_SuccessfulReadIncreasesCount_851) {

    std::string sampleData = "R0lGODlhAQABAIAAAP///wAAACH5BAEAAAAALAAAAAABAAEAAAICRAEAOw==";

    EXPECT_EQ(xmpArrayValue_.read(sampleData), 0);

    EXPECT_GT(xmpArrayValue_.count(), 0);

}



TEST_F(XmpArrayValueTest_851, ToRational_ReturnsValidRational_851) {

    std::string sampleData = "3/4";

    xmpArrayValue_.read(sampleData);

    Rational result = xmpArrayValue_.toRational(0);

    EXPECT_EQ(result.first, 3);

    EXPECT_EQ(result.second, 4);

}



TEST_F(XmpArrayValueTest_851, ToRational_ReturnsDefaultRationalIfParsingFails_851) {

    std::string invalidData = "not_a_rational";

    xmpArrayValue_.read(invalidData);

    Rational result = xmpArrayValue_.toRational(0);

    EXPECT_EQ(result.first, 0);

    EXPECT_EQ(result.second, 0);

}
