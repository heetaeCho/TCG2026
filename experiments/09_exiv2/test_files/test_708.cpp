#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/panasonicmn_int.cpp"

#include <sstream>



using namespace Exiv2::Internal;



class PanasonicMakerNoteTest_708 : public ::testing::Test {

protected:

    PanasonicMakerNote panasonicMakerNote;

};



TEST_F(PanasonicMakerNoteTest_708, Print0x0023_NormalOperation_708) {

    std::ostringstream os;

    Exiv2::Value value;

    value = static_cast<int64_t>(9); // 9 / 3 = 3 EV

    panasonicMakerNote.print0x0023(os, value, nullptr);

    EXPECT_EQ(os.str(), "3 EV");

}



TEST_F(PanasonicMakerNoteTest_708, Print0x0023_ZeroValue_708) {

    std::ostringstream os;

    Exiv2::Value value;

    value = static_cast<int64_t>(0); // 0 / 3 = 0 EV

    panasonicMakerNote.print0x0023(os, value, nullptr);

    EXPECT_EQ(os.str(), "0 EV");

}



TEST_F(PanasonicMakerNoteTest_708, Print0x0023_NegativeValue_708) {

    std::ostringstream os;

    Exiv2::Value value;

    value = static_cast<int64_t>(-9); // -9 / 3 = -3 EV

    panasonicMakerNote.print0x0023(os, value, nullptr);

    EXPECT_EQ(os.str(), "-3 EV");

}



TEST_F(PanasonicMakerNoteTest_708, Print0x0023_BoundaryConditionMax_708) {

    std::ostringstream os;

    Exiv2::Value value;

    value = static_cast<int64_t>(INT64_MAX); // INT64_MAX / 3

    panasonicMakerNote.print0x0023(os, value, nullptr);

    EXPECT_EQ(os.str(), (std::to_string(INT64_MAX / 3) + " EV"));

}



TEST_F(PanasonicMakerNoteTest_708, Print0x0023_BoundaryConditionMin_708) {

    std::ostringstream os;

    Exiv2::Value value;

    value = static_cast<int64_t>(INT64_MIN); // INT64_MIN / 3

    panasonicMakerNote.print0x0023(os, value, nullptr);

    EXPECT_EQ(os.str(), (std::to_string(INT64_MIN / 3) + " EV"));

}
