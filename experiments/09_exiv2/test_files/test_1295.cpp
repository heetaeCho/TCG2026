#include <gtest/gtest.h>

#include "exiv2/xmp_exiv2.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;



class XmpdatumTest : public ::testing::Test {

protected:

    std::unique_ptr<XmpKey> key;

    std::unique_ptr<Value> value;

    Xmpdatum xmpDatum;



    void SetUp() override {

        key = std::make_unique<XmpKey>("Xmp.dc.title");

        value = std::make_unique<StringValue>(ValueType::xmpText);

        xmpDatum = Xmpdatum(*key, value.get());

    }

};



TEST_F(XmpdatumTest_1295, ToRationalDefaultCase_1295) {

    Rational result = xmpDatum.toRational(0);

    EXPECT_EQ(result.first, -1);

    EXPECT_EQ(result.second, 1);

}



TEST_F(XmpdatumTest_1295, ToRationalIndexOutOfRange_1295) {

    // Assuming the value has no elements, thus any index is out of range

    Rational result = xmpDatum.toRational(10);

    EXPECT_EQ(result.first, -1);

    EXPECT_EQ(result.second, 1);

}



TEST_F(XmpdatumTest_1295, ToRationalNormalOperation_1295) {

    // Set a rational value for testing

    std::vector<Rational> rationalValues = {{1, 2}};

    value->setValue(rationalValues);



    Rational result = xmpDatum.toRational(0);

    EXPECT_EQ(result.first, 1);

    EXPECT_EQ(result.second, 2);

}



TEST_F(XmpdatumTest_1295, ToRationalBoundaryCondition_1295) {

    // Test with boundary condition where n is zero

    std::vector<Rational> rationalValues = {{3, 4}};

    value->setValue(rationalValues);



    Rational result = xmpDatum.toRational(0);

    EXPECT_EQ(result.first, 3);

    EXPECT_EQ(result.second, 4);

}



TEST_F(XmpdatumTest_1295, ToRationalInvalidIndex_1295) {

    // Assuming the value has one element, thus index 1 is out of range

    std::vector<Rational> rationalValues = {{5, 6}};

    value->setValue(rationalValues);



    Rational result = xmpDatum.toRational(1);

    EXPECT_EQ(result.first, -1);

    EXPECT_EQ(result.second, 1);

}
