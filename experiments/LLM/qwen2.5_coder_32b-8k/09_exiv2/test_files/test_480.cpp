#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include <Exiv2/value.hpp>

#include <Exiv2/exif.hpp>



namespace Exiv2 { namespace Internal {



class Nikon3MakerNoteTest : public ::testing::Test {

protected:

    Nikon3MakerNote nikonMakerNote;

};



TEST_F(Nikon3MakerNoteTest_480, PrintFStops_NormalOperation_480) {

    std::ostringstream os;

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedByte);

    value.modify(1, static_cast<uint8_t>(12)); // F-stop value 1.0



    nikonMakerNote.printFStops(os, value, nullptr);



    EXPECT_EQ("F1.0", os.str());

}



TEST_F(Nikon3MakerNoteTest_480, PrintFStops_BoundaryCondition_ZeroValue_480) {

    std::ostringstream os;

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedByte);

    value.modify(1, static_cast<uint8_t>(0)); // F-stop value 0.0



    nikonMakerNote.printFStops(os, value, nullptr);



    EXPECT_EQ("F0.0", os.str());

}



TEST_F(Nikon3MakerNoteTest_480, PrintFStops_BoundaryCondition_MaxValue_480) {

    std::ostringstream os;

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedByte);

    value.modify(1, static_cast<uint8_t>(255)); // F-stop value 21.3



    nikonMakerNote.printFStops(os, value, nullptr);



    EXPECT_EQ("F21.3", os.str());

}



TEST_F(Nikon3MakerNoteTest_480, PrintFStops_ErrorCase_CountNotOne_480) {

    std::ostringstream os;

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedByte);

    value.modify(2, static_cast<uint8_t>(12), static_cast<uint8_t>(12)); // Two values



    nikonMakerNote.printFStops(os, value, nullptr);



    EXPECT_EQ("(0 12)", os.str());

}



TEST_F(Nikon3MakerNoteTest_480, PrintFStops_ErrorCase_WrongTypeId_480) {

    std::ostringstream os;

    Exiv2::Value value = Exiv2::Value::create(Exiv2::asciiString);

    value.modify(1, "12"); // Incorrect type



    nikonMakerNote.printFStops(os, value, nullptr);



    EXPECT_EQ("(\"12\")", os.str());

}



}} // namespace Exiv2::Internal
