#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/nikonmn_int.hpp"

#include "exiv2/value.hpp"

#include "exiv2/exif.hpp"



namespace Exiv2 {

namespace Internal {



class Nikon3MakerNoteTests_491 : public ::testing::Test {

protected:

    Nikon3MakerNote nikon3MakerNote;

    std::ostringstream os;

    Value value;

    const ExifData* data = nullptr;



    void SetUp() override {

        // Initialize any common objects or states here

        value = Value(TypeId::unsignedByte);

    }

};



TEST_F(Nikon3MakerNoteTests_491, NormalOperation_TypeUnsignedByte_CountOne_491) {

    value.setDataArea(reinterpret_cast<const byte*>(&static_cast<uint8_t>(0x0F)), 1);

    nikon3MakerNote.printFlashGroupAControlData(os, value, data);

    EXPECT_EQ(os.str(), "TTL");

}



TEST_F(Nikon3MakerNoteTests_491, BoundaryCondition_TypeUnsignedByte_CountZero_491) {

    value.setDataArea(reinterpret_cast<const byte*>(&static_cast<uint8_t>(0x0F)), 0);

    nikon3MakerNote.printFlashGroupAControlData(os, value, data);

    EXPECT_EQ(os.str(), "(Exiv2::Value())");

}



TEST_F(Nikon3MakerNoteTests_491, BoundaryCondition_TypeUnsignedByte_CountTwo_491) {

    value.setDataArea(reinterpret_cast<const byte*>(&static_cast<uint8_t>(0x0F)), 2);

    nikon3MakerNote.printFlashGroupAControlData(os, value, data);

    EXPECT_EQ(os.str(), "(Exiv2::Value())");

}



TEST_F(Nikon3MakerNoteTests_491, ExceptionalCase_TypeNotUnsignedByte_491) {

    value = Value(TypeId::asciiString);

    nikon3MakerNote.printFlashGroupAControlData(os, value, data);

    EXPECT_EQ(os.str(), "(Exiv2::Value())");

}



TEST_F(Nikon3MakerNoteTests_491, NormalOperation_TypeUnsignedByte_ValueZero_491) {

    value.setDataArea(reinterpret_cast<const byte*>(&static_cast<uint8_t>(0x00)), 1);

    nikon3MakerNote.printFlashGroupAControlData(os, value, data);

    EXPECT_EQ(os.str(), "Off");

}



TEST_F(Nikon3MakerNoteTests_491, NormalOperation_TypeUnsignedByte_ValueSeven_491) {

    value.setDataArea(reinterpret_cast<const byte*>(&static_cast<uint8_t>(0x07)), 1);

    nikon3MakerNote.printFlashGroupAControlData(os, value, data);

    EXPECT_EQ(os.str(), "Repeating Flash");

}



TEST_F(Nikon3MakerNoteTests_491, ExceptionalCase_TypeUnsignedByte_ValueOutOfRange_491) {

    value.setDataArea(reinterpret_cast<const byte*>(&static_cast<uint8_t>(0x0F)), 1);

    nikon3MakerNote.printFlashGroupAControlData(os, value, data);

    EXPECT_EQ(os.str(), "TTL");

}



} // namespace Internal

} // namespace Exiv2
