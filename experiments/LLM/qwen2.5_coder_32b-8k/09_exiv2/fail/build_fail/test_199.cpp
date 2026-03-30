#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include <sstream>

#include <Exiv2/value.hpp>

#include <Exiv2/exif.hpp>



using namespace Exiv2;

using namespace Exiv2::Internal;



class PentaxMakerNoteTest : public ::testing::Test {

protected:

    PentaxMakerNote pentaxMakerNote;

    std::ostringstream os;

};



TEST_F(PentaxMakerNoteTest_199, PrintBracketing_NormalOperation_LessThanTen_199) {

    Value value;

    value.makeArray(1);

    value[0] = 3; // l0 < 10

    pentaxMakerNote.printBracketing(os, value, nullptr);

    EXPECT_EQ("1.00 EV", os.str());

}



TEST_F(PentaxMakerNoteTest_199, PrintBracketing_NormalOperation_GreaterThanOrEqualToTen_199) {

    Value value;

    value.makeArray(1);

    value[0] = 15; // l0 >= 10

    pentaxMakerNote.printBracketing(os, value, nullptr);

    EXPECT_EQ("5.50 EV", os.str());

}



TEST_F(PentaxMakerNoteTest_199, PrintBracketing_BoundaryCondition_Zero_199) {

    Value value;

    value.makeArray(1);

    value[0] = 0; // l0 == 0

    pentaxMakerNote.printBracketing(os, value, nullptr);

    EXPECT_EQ("0.00 EV", os.str());

}



TEST_F(PentaxMakerNoteTest_199, PrintBracketing_BoundaryCondition_Ten_199) {

    Value value;

    value.makeArray(1);

    value[0] = 10; // l0 == 10

    pentaxMakerNote.printBracketing(os, value, nullptr);

    EXPECT_EQ("0.50 EV", os.str());

}



TEST_F(PentaxMakerNoteTest_199, PrintBracketing_ExtendedBracketing_NoType_199) {

    Value value;

    value.makeArray(2);

    value[0] = 15; // l0 >= 10

    value[1] = 0;  // No extended bracketing

    pentaxMakerNote.printBracketing(os, value, nullptr);

    EXPECT_EQ("5.50 EV (No extended bracketing)", os.str());

}



TEST_F(PentaxMakerNoteTest_199, PrintBracketing_ExtendedBracketing_TypeWBBA_199) {

    Value value;

    value.makeArray(2);

    value[0] = 15; // l0 >= 10

    value[1] = (1 << 8) + 3; // WB-BA with range 3

    pentaxMakerNote.printBracketing(os, value, nullptr);

    EXPECT_EQ("5.50 EV (WB-BA 3)", os.str());

}



TEST_F(PentaxMakerNoteTest_199, PrintBracketing_ExtendedBracketing_TypeWBGm_199) {

    Value value;

    value.makeArray(2);

    value[0] = 15; // l0 >= 10

    value[1] = (2 << 8) + 3; // WB-GM with range 3

    pentaxMakerNote.printBracketing(os, value, nullptr);

    EXPECT_EQ("5.50 EV (WB-GM 3)", os.str());

}



TEST_F(PentaxMakerNoteTest_199, PrintBracketing_ExtendedBracketing_TypeSaturation_199) {

    Value value;

    value.makeArray(2);

    value[0] = 15; // l0 >= 10

    value[1] = (3 << 8) + 3; // Saturation with range 3

    pentaxMakerNote.printBracketing(os, value, nullptr);

    EXPECT_EQ("5.50 EV (Saturation 3)", os.str());

}



TEST_F(PentaxMakerNoteTest_199, PrintBracketing_ExtendedBracketing_TypeSharpness_199) {

    Value value;

    value.makeArray(2);

    value[0] = 15; // l0 >= 10

    value[1] = (4 << 8) + 3; // Sharpness with range 3

    pentaxMakerNote.printBracketing(os, value, nullptr);

    EXPECT_EQ("5.50 EV (Sharpness 3)", os.str());

}



TEST_F(PentaxMakerNoteTest_199, PrintBracketing_ExtendedBracketing_TypeContrast_199) {

    Value value;

    value.makeArray(2);

    value[0] = 15; // l0 >= 10

    value[1] = (5 << 8) + 3; // Contrast with range 3

    pentaxMakerNote.printBracketing(os, value, nullptr);

    EXPECT_EQ("5.50 EV (Contrast 3)", os.str());

}



TEST_F(PentaxMakerNoteTest_199, PrintBracketing_ExtendedBracketing_TypeUnknown_199) {

    Value value;

    value.makeArray(2);

    value[0] = 15; // l0 >= 10

    value[1] = (6 << 8) + 3; // Unknown type with range 3

    pentaxMakerNote.printBracketing(os, value, nullptr);

    EXPECT_EQ("5.50 EV (Unknown 6 3)", os.str());

}
