#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <iostream>

#include <sstream>

#include "exiv2/src/nikonmn_int.cpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::StrEq;



class Nikon3MakerNoteTest_462 : public ::testing::Test {

protected:

    Nikon3MakerNote nikon3MakerNote;

};



TEST_F(Nikon3MakerNoteTest_462, PutAF_C_ReturnsContinuousAutofocus_462) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue("AF-C ");

    nikon3MakerNote.print0x0007(os, value, nullptr);

    EXPECT_EQ(os.str(), "Continuous autofocus");

}



TEST_F(Nikon3MakerNoteTest_462, PutAF_S_ReturnsSingleAutofocus_462) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue("AF-S ");

    nikon3MakerNote.print0x0007(os, value, nullptr);

    EXPECT_EQ(os.str(), "Single autofocus");

}



TEST_F(Nikon3MakerNoteTest_462, PutAF_A_ReturnsAutomatic_462) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue("AF-A ");

    nikon3MakerNote.print0x0007(os, value, nullptr);

    EXPECT_EQ(os.str(), "Automatic");

}



TEST_F(Nikon3MakerNoteTest_462, PutUnknownValue_ReturnsFormattedString_462) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue("UNKNOWN");

    nikon3MakerNote.print0x0007(os, value, nullptr);

    EXPECT_EQ(os.str(), "(UNKNOWN)");

}



TEST_F(Nikon3MakerNoteTest_462, PutEmptyString_ReturnsFormattedString_462) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue("");

    nikon3MakerNote.print0x0007(os, value, nullptr);

    EXPECT_EQ(os.str(), "( )");

}
