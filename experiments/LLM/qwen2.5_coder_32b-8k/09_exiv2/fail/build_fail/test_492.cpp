#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/nikonmn_int.hpp"

#include "exiv2/value.hpp"

#include <sstream>



using namespace Exiv2;

using namespace Exiv2::Internal;



class Nikon3MakerNoteTest_492 : public ::testing::Test {

protected:

    Nikon3MakerNote nikonMakerNote;

    std::ostringstream os;

    Value value;

    const ExifData* data = nullptr;  // Assuming no interaction with ExifData in this context

};



TEST_F(Nikon3MakerNoteTest_492, NormalOperation_492) {

    value = Value(unsignedByte);

    value.setDataArea(reinterpret_cast<const byte*>(&0x5A), 1);  // Example value: 01011010



    nikonMakerNote.printFlashGroupBCControlData(os, value, data);



    EXPECT_EQ(os.str(), "iTTL, TTL");

}



TEST_F(Nikon3MakerNoteTest_492, BoundaryCondition_ValueCountNotOne_492) {

    value = Value(unsignedByte);

    value.setDataArea(reinterpret_cast<const byte*>(&0x5A), 2);  // Example value with count not one



    nikonMakerNote.printFlashGroupBCControlData(os, value, data);



    EXPECT_EQ(os.str(), "(Exiv2::Value)");

}



TEST_F(Nikon3MakerNoteTest_492, BoundaryCondition_WrongTypeId_492) {

    value = Value(asciiString);  // Wrong type ID

    value.setDataArea(reinterpret_cast<const byte*>(&0x5A), 1);



    nikonMakerNote.printFlashGroupBCControlData(os, value, data);



    EXPECT_EQ(os.str(), "(Exiv2::Value)");

}



TEST_F(Nikon3MakerNoteTest_492, ExceptionalCase_ValueNotOk_492) {

    Value badValue(unsignedByte);

    badValue.ok_ = false;  // Simulate a non-ok value



    nikonMakerNote.printFlashGroupBCControlData(os, badValue, data);



    EXPECT_EQ(os.str(), "(Exiv2::Value)");

}



TEST_F(Nikon3MakerNoteTest_492, ZeroValue_492) {

    value = Value(unsignedByte);

    value.setDataArea(reinterpret_cast<const byte*>(&0x00), 1);  // Example value: 00000000



    nikonMakerNote.printFlashGroupBCControlData(os, value, data);



    EXPECT_EQ(os.str(), "Off, Off");

}



TEST_F(Nikon3MakerNoteTest_492, MaxValue_492) {

    value = Value(unsignedByte);

    value.setDataArea(reinterpret_cast<const byte*>(&0xFF), 1);  // Example value: 11111111



    nikonMakerNote.printFlashGroupBCControlData(os, value, data);



    EXPECT_EQ(os.str(), "Repeating Flash, Repeating Flash");

}
