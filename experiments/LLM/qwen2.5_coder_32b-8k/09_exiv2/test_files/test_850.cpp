#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"



using namespace Exiv2;

using testing::Eq;



class XmpArrayValueTest_850 : public ::testing::Test {

protected:

    XmpArrayValue xmpArrayValue_{TypeId::tFloat};



    void SetUp() override {

        // Initialize with some known values for testing

        std::string buffer = "1.1 2.2 3.3";

        xmpArrayValue_.read(buffer);

    }

};



TEST_F(XmpArrayValueTest_850, toFloat_ReturnsCorrectValueForValidIndex_850) {

    EXPECT_FLOAT_EQ(xmpArrayValue_.toFloat(0), 1.1f);

    EXPECT_FLOAT_EQ(xmpArrayValue_.toFloat(1), 2.2f);

    EXPECT_FLOAT_EQ(xmpArrayValue_.toFloat(2), 3.3f);

}



TEST_F(XmpArrayValueTest_850, toFloat_ReturnsZeroForOutofBoundsIndex_850) {

    EXPECT_FLOAT_EQ(xmpArrayValue_.toFloat(3), 0.0f); // Out of bounds

}



TEST_F(XmpArrayValueTest_850, count_ReturnsCorrectNumberOfElements_850) {

    EXPECT_EQ(xmpArrayValue_.count(), 3);

}



TEST_F(XmpArrayValueTest_850, toFloat_ThrowsNoExceptionForValidIndex_850) {

    ASSERT_NO_THROW({

        xmpArrayValue_.toFloat(0);

        xmpArrayValue_.toFloat(1);

        xmpArrayValue_.toFloat(2);

    });

}



TEST_F(XmpArrayValueTest_850, toFloat_ReturnsZeroWhenOkIsFalse_850) {

    xmpArrayValue_.ok_ = false;

    EXPECT_FLOAT_EQ(xmpArrayValue_.toFloat(0), 0.0f);

}
