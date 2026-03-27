#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "panasonicmn_int.cpp" // Assuming this is how we include the partial implementation



using namespace ::testing;

using namespace Exiv2::Internal;



class PanasonicMakerNoteTest_712 : public Test {

protected:

    PanasonicMakerNote panasonicMakerNote;

    std::ostringstream os;

    Value value;

};



TEST_F(PanasonicMakerNoteTest_712, Print0x003c_NormalIntelligentISO_712) {

    value = 65534; // Set the value to 65534 which corresponds to "Intelligent ISO"

    panasonicMakerNote.print0x003c(os, value, nullptr);

    EXPECT_EQ("Intelligent ISO", os.str());

}



TEST_F(PanasonicMakerNoteTest_712, Print0x003c_NormalNa_712) {

    value = 65535; // Set the value to 65535 which corresponds to "n/a"

    panasonicMakerNote.print0x003c(os, value, nullptr);

    EXPECT_EQ("n/a", os.str());

}



TEST_F(PanasonicMakerNoteTest_712, Print0x003c_DefaultValue_712) {

    value = 12345; // Set the value to a default integer which should print as is

    panasonicMakerNote.print0x003c(os, value, nullptr);

    EXPECT_EQ("12345", os.str());

}



TEST_F(PanasonicMakerNoteTest_712, Print0x003c_ZeroValue_712) {

    value = 0; // Set the value to zero which should print as is

    panasonicMakerNote.print0x003c(os, value, nullptr);

    EXPECT_EQ("0", os.str());

}



TEST_F(PanasonicMakerNoteTest_712, Print0x003c_NegativeValue_712) {

    value = -1; // Set the value to a negative integer which should print as is

    panasonicMakerNote.print0x003c(os, value, nullptr);

    EXPECT_EQ("-1", os.str());

}
