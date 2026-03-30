#include <gtest/gtest.h>

#include "exiv2/xmp_exiv2.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;



class XmpdatumTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Create a mock Value object

        auto value = Value::create(string);

        value->setDataArea(reinterpret_cast<const byte*>("123.45"), 7);



        // Initialize the Xmpdatum with a key and value

        xmpDatum_ = Xmpdatum(XmpKey("Xmp.test.key"), value.get());

    }



    Xmpdatum xmpDatum_;

};



TEST_F(XmpdatumTest_1294, ToFloat_ReturnsCorrectValueForValidIndex_1294) {

    EXPECT_FLOAT_EQ(xmpDatum_.toFloat(0), 123.45f);

}



TEST_F(XmpdatumTest_1294, ToFloat_ReturnsNegativeOneForInvalidIndex_1294) {

    EXPECT_FLOAT_EQ(xmpDatum_.toFloat(1), -1.0f);

}



TEST_F(XmpdatumTest_1294, ToFloat_HandlesBoundaryConditionAtZero_1294) {

    EXPECT_FLOAT_EQ(xmpDatum_.toFloat(0), 123.45f);

}
