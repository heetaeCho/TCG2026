#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "./TestProjects/exiv2/src/nikonmn_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Return;



class Nikon3MakerNoteTest_501 : public ::testing::Test {

protected:

    Nikon3MakerNote nikonMakerNote;

    std::ostringstream os;

    ExifData metadata;

};



TEST_F(Nikon3MakerNoteTest_501, NormalOperationWithUnsignedByteType_501) {

    Value value(unsignedByte);

    value.setDataArea(reinterpret_cast<const byte*>(&static_cast<uint8_t>(1)), 1);



    nikonMakerNote.printExternalFlashData4(os, value, &metadata);



    EXPECT_EQ(os.str(), "Illumination Pat.: Center-weighted");

}



TEST_F(Nikon3MakerNoteTest_501, BoundaryConditionWithZeroCount_501) {

    Value value(unsignedByte);

    value.setDataArea(reinterpret_cast<const byte*>(&static_cast<uint8_t>(1)), 0);



    nikonMakerNote.printExternalFlashData4(os, value, &metadata);



    EXPECT_EQ(os.str(), "(value)");

}



TEST_F(Nikon3MakerNoteTest_501, BoundaryConditionWithInvalidType_501) {

    Value value(asciiString);

    value.setDataArea(reinterpret_cast<const byte*>("test"), 4);



    nikonMakerNote.printExternalFlashData4(os, value, &metadata);



    EXPECT_EQ(os.str(), "(value)");

}



TEST_F(Nikon3MakerNoteTest_501, BoundaryConditionWithMaxUnsignedByteValue_501) {

    Value value(unsignedByte);

    value.setDataArea(reinterpret_cast<const byte*>(&static_cast<uint8_t>(2)), 1);



    nikonMakerNote.printExternalFlashData4(os, value, &metadata);



    EXPECT_EQ(os.str(), "Illumination Pat.: Even");

}



TEST_F(Nikon3MakerNoteTest_501, BoundaryConditionWithOutOfRangeValue_501) {

    Value value(unsignedByte);

    value.setDataArea(reinterpret_cast<const byte*>(&static_cast<uint8_t>(3)), 1);



    nikonMakerNote.printExternalFlashData4(os, value, &metadata);



    EXPECT_EQ(os.str(), "(value)");

}
