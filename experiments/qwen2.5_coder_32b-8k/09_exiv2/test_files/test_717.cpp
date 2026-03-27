#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/panasonicmn_int.cpp"

#include <sstream>



namespace Exiv2 { namespace Internal {



class PanasonicMakerNoteTest_717 : public ::testing::Test {

protected:

    PanasonicMakerNote makerNote;

};



TEST_F(PanasonicMakerNoteTest_717, PrintPitchAngle_NormalOperation_717) {

    Value value(50);

    std::ostringstream os;

    makerNote.printPitchAngle(os, value, nullptr);

    EXPECT_EQ("-5.0", os.str());

}



TEST_F(PanasonicMakerNoteTest_717, PrintPitchAngle_BoundaryConditionZero_717) {

    Value value(0);

    std::ostringstream os;

    makerNote.printPitchAngle(os, value, nullptr);

    EXPECT_EQ("0.0", os.str());

}



TEST_F(PanasonicMakerNoteTest_717, PrintPitchAngle_NegativeValue_717) {

    Value value(-50);

    std::ostringstream os;

    makerNote.printPitchAngle(os, value, nullptr);

    EXPECT_EQ("5.0", os.str());

}



TEST_F(PanasonicMakerNoteTest_717, PrintPitchAngle_MaxInt16Value_717) {

    Value value(32767);

    std::ostringstream os;

    makerNote.printPitchAngle(os, value, nullptr);

    EXPECT_EQ("-3276.7", os.str());

}



TEST_F(PanasonicMakerNoteTest_717, PrintPitchAngle_MinInt16Value_717) {

    Value value(-32768);

    std::ostringstream os;

    makerNote.printPitchAngle(os, value, nullptr);

    EXPECT_EQ("3276.8", os.str());

}



}  // namespace Internal

}  // namespace Exiv2
