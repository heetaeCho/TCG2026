#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/sigmamn_int.cpp"

#include <sstream>

#include <string>



using namespace Exiv2::Internal;

using ::testing::HasSubstr;



class SigmaMakerNoteTest_1727 : public ::testing::Test {

protected:

    SigmaMakerNote sigmaMakerNote_;

};



TEST_F(SigmaMakerNoteTest_1727, Print0x0009_A_ReturnsAverage_1727) {

    std::ostringstream os;

    Value value("A");

    sigmaMakerNote_.print0x0009(os, value, nullptr);

    EXPECT_EQ(os.str(), "Average");

}



TEST_F(SigmaMakerNoteTest_1727, Print0x0009_C_ReturnsCenter_1727) {

    std::ostringstream os;

    Value value("C");

    sigmaMakerNote_.print0x0009(os, value, nullptr);

    EXPECT_EQ(os.str(), "Center");

}



TEST_F(SigmaMakerNoteTest_1727, Print0x0009_8_Returns8Segment_1727) {

    std::ostringstream os;

    Value value("8");

    sigmaMakerNote_.print0x0009(os, value, nullptr);

    EXPECT_EQ(os.str(), "8-Segment");

}



TEST_F(SigmaMakerNoteTest_1727, Print0x0009_Default_ReturnsFormattedValue_1727) {

    std::ostringstream os;

    Value value("X");

    sigmaMakerNote_.print0x0009(os, value, nullptr);

    EXPECT_EQ(os.str(), "(X)");

}



TEST_F(SigmaMakerNoteTest_1727, Print0x0009_EmptyString_ReturnsFormattedValue_1727) {

    std::ostringstream os;

    Value value("");

    sigmaMakerNote_.print0x0009(os, value, nullptr);

    EXPECT_EQ(os.str(), "()");

}



TEST_F(SigmaMakerNoteTest_1727, Print0x0009_LongString_ReturnsFormattedValue_1727) {

    std::ostringstream os;

    Value value("ABCDEFG");

    sigmaMakerNote_.print0x0009(os, value, nullptr);

    EXPECT_EQ(os.str(), "(ABCDEFG)");

}
