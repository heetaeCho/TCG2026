#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "TestProjects/exiv2/src/nikonmn_int.cpp"



namespace Exiv2 { namespace Internal {



class Nikon3MakerNoteTest : public ::testing::Test {

protected:

    Nikon3MakerNote nikon3MakerNote;

    std::ostringstream os;

};



TEST_F(Nikon3MakerNoteTest_459, PrintIiIso_ValidValue_ReturnsCorrectString_459) {

    Exiv2::Value value;

    value.makeArray(Exiv2::unsignedShort);

    value[0] = 12; // Example value



    nikon3MakerNote.printIiIso(os, value, nullptr);



    EXPECT_EQ("100", os.str());

}



TEST_F(Nikon3MakerNoteTest_459, PrintIiIso_ZeroValue_ReturnsCorrectString_459) {

    Exiv2::Value value;

    value.makeArray(Exiv2::unsignedShort);

    value[0] = 0;



    nikon3MakerNote.printIiIso(os, value, nullptr);



    EXPECT_EQ("6", os.str());

}



TEST_F(Nikon3MakerNoteTest_459, PrintIiIso_MaxValue_ReturnsCorrectString_459) {

    Exiv2::Value value;

    value.makeArray(Exiv2::unsignedShort);

    value[0] = 768; // This should give a large ISO value



    nikon3MakerNote.printIiIso(os, value, nullptr);



    EXPECT_EQ("1048576", os.str());

}



TEST_F(Nikon3MakerNoteTest_459, PrintIiIso_NegativeValue_ReturnsCorrectString_459) {

    Exiv2::Value value;

    value.makeArray(Exiv2::unsignedShort);

    value[0] = -12; // Negative values are possible with signed types



    nikon3MakerNote.printIiIso(os, value, nullptr);



    EXPECT_EQ("0", os.str());

}



TEST_F(Nikon3MakerNoteTest_459, PrintIiIso_LargeValue_ReturnsCorrectString_459) {

    Exiv2::Value value;

    value.makeArray(Exiv2::unsignedShort);

    value[0] = 1000; // Large value



    nikon3MakerNote.printIiIso(os, value, nullptr);



    EXPECT_EQ("8388608", os.str());

}



}} // namespace Exiv2::Internal
