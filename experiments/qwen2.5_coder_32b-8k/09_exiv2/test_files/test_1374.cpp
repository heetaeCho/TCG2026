#include <gtest/gtest.h>

#include <cmath>



namespace Exiv2 {

namespace Internal {



float fnumber(float apertureValue);



}  // namespace Internal

}  // namespace Exiv2



using namespace Exiv2::Internal;



TEST(fnumberTest_1374, NormalOperation_1374) {

    EXPECT_FLOAT_EQ(fnumber(0.0F), 1.0F);

    EXPECT_FLOAT_EQ(fnumber(1.0F), std::sqrt(2.F));

    EXPECT_FLOAT_EQ(fnumber(2.0F), 2.0F);

}



TEST(fnumberTest_1374, BoundaryConditions_1374) {

    EXPECT_FLOAT_EQ(fnumber(-std::numeric_limits<float>::infinity()), 0.0F);

    EXPECT_FLOAT_EQ(fnumber(std::numeric_limits<float>::infinity()), std::numeric_limits<float>::infinity());

}



TEST(fnumberTest_1374, ExceptionalCases_1374) {

    // No exceptional cases observable through the interface for this function

}



TEST(fnumberTest_1374, RoundingTo3_5_1374) {

    EXPECT_FLOAT_EQ(fnumber(5.64F), 3.5F);  // 5.64 should round to 3.5

    EXPECT_FLOAT_EQ(fnumber(5.65F), 3.5F);  // 5.65 should round to 3.5

    EXPECT_FLOAT_EQ(fnumber(5.66F), std::exp2(5.66F / 2.F));  // 5.66 should not round to 3.5

}



TEST(fnumberTest_1374, NegativeApertureValue_1374) {

    EXPECT_FLOAT_EQ(fnumber(-1.0F), std::exp2(-1.0F / 2.F));

    EXPECT_FLOAT_EQ(fnumber(-2.0F), std::exp2(-2.0F / 2.F));

}



TEST(fnumberTest_1374, LargeApertureValue_1374) {

    EXPECT_FLOAT_EQ(fnumber(10.0F), std::exp2(10.0F / 2.F));

    EXPECT_FLOAT_EQ(fnumber(20.0F), std::exp2(20.0F / 2.F));

}
