#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tags_int.cpp"  // Include the file containing the function to test



using namespace Exiv2;

using namespace Exiv2::Internal;

using testing::HasSubstr;



class Print0xa404Test_1414 : public ::testing::Test {

protected:

    Value value;

    std::ostringstream os;

};



TEST_F(Print0xa404Test_1414, DigitalZoomNotUsedWhenDenominatorIsZero_1414) {

    Rational zoom(5, 0); // Simulate digital zoom not used

    value = Value(zoom);

    print0xa404(os, value, nullptr);

    EXPECT_THAT(os.str(), HasSubstr("Digital zoom not used"));

}



TEST_F(Print0xa404Test_1414, NormalZoomValue_1414) {

    Rational zoom(5, 2); // Simulate a normal digital zoom

    value = Value(zoom);

    print0xa404(os, value, nullptr);

    EXPECT_EQ(os.str(), "2.5");

}



TEST_F(Print0xa404Test_1414, ZeroNumerator_1414) {

    Rational zoom(0, 3); // Simulate zero numerator

    value = Value(zoom);

    print0xa404(os, value, nullptr);

    EXPECT_EQ(os.str(), "0.0");

}



TEST_F(Print0xa404Test_1414, LargeZoomValue_1414) {

    Rational zoom(9999, 4); // Simulate a large digital zoom

    value = Value(zoom);

    print0xa404(os, value, nullptr);

    EXPECT_EQ(os.str(), "2500.0");

}



TEST_F(Print0xa404Test_1414, SmallZoomValue_1414) {

    Rational zoom(1, 9999); // Simulate a small digital zoom

    value = Value(zoom);

    print0xa404(os, value, nullptr);

    EXPECT_EQ(os.str(), "0.0");

}



TEST_F(Print0xa404Test_1414, NegativeZoomValue_1414) {

    Rational zoom(-5, 2); // Simulate a negative digital zoom

    value = Value(zoom);

    print0xa404(os, value, nullptr);

    EXPECT_EQ(os.str(), "-2.5");

}
