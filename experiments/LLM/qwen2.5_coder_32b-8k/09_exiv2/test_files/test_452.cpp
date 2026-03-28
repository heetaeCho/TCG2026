#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/nikonmn_int.cpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::HasSubstr;



class Nikon1MakerNoteTest_452 : public ::testing::Test {

protected:

    Nikon1MakerNote nikonMakerNote;

    std::ostringstream os;

};



TEST_F(Nikon1MakerNoteTest_452, PutAF_C_ReturnsContinuousAutofocus_452) {

    Exiv2::Value value("AF-C ");

    nikonMakerNote.print0x0007(os, value, nullptr);

    EXPECT_THAT(os.str(), HasSubstr("Continuous autofocus"));

}



TEST_F(Nikon1MakerNoteTest_452, PutAF_S_ReturnsSingleAutofocus_452) {

    Exiv2::Value value("AF-S ");

    nikonMakerNote.print0x0007(os, value, nullptr);

    EXPECT_THAT(os.str(), HasSubstr("Single autofocus"));

}



TEST_F(Nikon1MakerNoteTest_452, PutAF_A_ReturnsAutomatic_452) {

    Exiv2::Value value("AF-A ");

    nikonMakerNote.print0x0007(os, value, nullptr);

    EXPECT_THAT(os.str(), HasSubstr("Automatic"));

}



TEST_F(Nikon1MakerNoteTest_452, PutUnknownValue_ReturnsEncodedValue_452) {

    Exiv2::Value value("UNKNOWN");

    nikonMakerNote.print0x0007(os, value, nullptr);

    EXPECT_THAT(os.str(), HasSubstr("(UNKNOWN)"));

}



TEST_F(Nikon1MakerNoteTest_452, PutEmptyString_ReturnsEncodedEmpty_452) {

    Exiv2::Value value("");

    nikonMakerNote.print0x0007(os, value, nullptr);

    EXPECT_THAT(os.str(), HasSubstr("()"));

}
