#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/nikonmn_int.cpp"

#include <sstream>



using namespace Exiv2::Internal;



class Nikon3MakerNoteTest_507 : public ::testing::Test {

protected:

    Nikon3MakerNote nikon3MakerNote;

    Value value;

};



TEST_F(Nikon3MakerNoteTest_507, PrintApertureLd4_NormalOperation_507) {

    std::ostringstream os;

    value.setValue(12288); // Example value that should convert to a valid aperture

    nikon3MakerNote.printApertureLd4(os, value, nullptr);

    EXPECT_EQ(os.str(), "F2.8");

}



TEST_F(Nikon3MakerNoteTest_507, PrintApertureLd4_ZeroValue_507) {

    std::ostringstream os;

    value.setValue(0); // Zero should return "n/a"

    nikon3MakerNote.printApertureLd4(os, value, nullptr);

    EXPECT_EQ(os.str(), "n/a");

}



TEST_F(Nikon3MakerNoteTest_507, PrintApertureLd4_InvalidCount_507) {

    std::ostringstream os;

    Value invalidValue;

    invalidValue.setValue(12288);

    invalidValue.setSize(2); // Invalid count

    nikon3MakerNote.printApertureLd4(os, invalidValue, nullptr);

    EXPECT_EQ(os.str(), "(12288)");

}



TEST_F(Nikon3MakerNoteTest_507, PrintApertureLd4_InvalidTypeId_507) {

    std::ostringstream os;

    Value invalidValue;

    invalidValue.setValue(12288);

    invalidValue.setType(TypeId::tString); // Invalid type

    nikon3MakerNote.printApertureLd4(os, invalidValue, nullptr);

    EXPECT_EQ(os.str(), "(12288)");

}
