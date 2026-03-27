#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include <sstream>

#include <Exiv2/exiv2.hpp>



using namespace Exiv2;

using namespace Exiv2::Internal;



class Nikon3MakerNoteTest : public ::testing::Test {

protected:

    Nikon3MakerNote nikonMakerNote;

    Value mockValue;

};



TEST_F(Nikon3MakerNoteTest_470, Print0x008b_NormalOperation_470) {

    std::ostringstream os;

    ExifData exifData;



    // Set up a normal case where value.size() == 4 and value.typeId() is not undefined

    mockValue.setValue(std::vector<uint8_t>({0x3F, 0x80, 0x00, 0x00})); // float(1.0) in IEEE 754

    mockValue.setType(TypeId::tFloat);

    mockValue.setSize(4);



    os << std::hexfloat;

    nikonMakerNote.print0x008b(os, mockValue, &exifData);



    EXPECT_EQ(os.str(), "1");

}



TEST_F(Nikon3MakerNoteTest_470, Print0x008b_ValueSizeNotFour_470) {

    std::ostringstream os;

    ExifData exifData;



    // Set up a case where value.size() != 4

    mockValue.setValue(std::vector<uint8_t>({0x3F, 0x80, 0x00})); // float(1.0) in IEEE 754 but size is not 4

    mockValue.setType(TypeId::tFloat);

    mockValue.setSize(3);



    os << std::hexfloat;

    nikonMakerNote.print0x008b(os, mockValue, &exifData);



    EXPECT_EQ(os.str(), "(1.0)");

}



TEST_F(Nikon3MakerNoteTest_470, Print0x008b_ValueTypeIdUndefined_470) {

    std::ostringstream os;

    ExifData exifData;



    // Set up a case where value.typeId() is undefined

    mockValue.setValue(std::vector<uint8_t>({0x3F, 0x80, 0x00, 0x00})); // float(1.0) in IEEE 754

    mockValue.setType(TypeId::tUndefined);

    mockValue.setSize(4);



    os << std::hexfloat;

    nikonMakerNote.print0x008b(os, mockValue, &exifData);



    EXPECT_EQ(os.str(), "(1.0)");

}



TEST_F(Nikon3MakerNoteTest_470, Print0x008b_CIsZero_470) {

    std::ostringstream os;

    ExifData exifData;



    // Set up a case where c == 0

    mockValue.setValue(std::vector<uint8_t>({0x3F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00})); // float(1.0) in IEEE 754 and int64(0)

    mockValue.setType(TypeId::tFloat | TypeId::tLong);

    mockValue.setSize(12);



    os << std::hexfloat;

    nikonMakerNote.print0x008b(os, mockValue, &exifData);



    EXPECT_EQ(os.str(), "(1.0)");

}



TEST_F(Nikon3MakerNoteTest_470, Print0x008b_NonZeroCalculation_470) {

    std::ostringstream os;

    ExifData exifData;



    // Set up a case where calculation should be done

    mockValue.setValue(std::vector<uint8_t>({0x3F, 0x80, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00})); // float(1.0), int64(1), int64(2)

    mockValue.setType(TypeId::tFloat | TypeId::tLong);

    mockValue.setSize(12);



    os << std::hexfloat;

    nikonMakerNote.print0x008b(os, mockValue, &exifData);



    EXPECT_EQ(os.str(), "0.5");

}
