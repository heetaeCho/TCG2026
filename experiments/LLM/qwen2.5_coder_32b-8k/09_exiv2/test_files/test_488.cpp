#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "exiv2/value.hpp"

#include "exiv2/exif.hpp"

#include "./TestProjects/exiv2/src/nikonmn_int.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class Nikon3MakerNoteTest_488 : public ::testing::Test {

protected:

    Value createValue(TypeId typeId, uint32_t value) {

        Value v(typeId);

        v.setDataArea(reinterpret_cast<const byte*>(&value), sizeof(value));

        return v;

    }



    ExifData metadata;

};



TEST_F(Nikon3MakerNoteTest_488, NormalOperation_488) {

    std::ostringstream os;

    Value value = createValue(unsignedByte, 0x0F);

    Nikon3MakerNote::printExternalFlashData2(os, value, &metadata);



    EXPECT_EQ(os.str(), "Repeating Flash");

}



TEST_F(Nikon3MakerNoteTest_488, BoundaryConditionZero_488) {

    std::ostringstream os;

    Value value = createValue(unsignedByte, 0x00);

    Nikon3MakerNote::printExternalFlashData2(os, value, &metadata);



    EXPECT_EQ(os.str(), "Off");

}



TEST_F(Nikon3MakerNoteTest_488, BoundaryConditionMaxValid_488) {

    std::ostringstream os;

    Value value = createValue(unsignedByte, 0x07);

    Nikon3MakerNote::printExternalFlashData2(os, value, &metadata);



    EXPECT_EQ(os.str(), "Repeating Flash");

}



TEST_F(Nikon3MakerNoteTest_488, BoundaryConditionInvalidType_488) {

    std::ostringstream os;

    Value value = createValue(signedByte, 0x0F);

    Nikon3MakerNote::printExternalFlashData2(os, value, &metadata);



    EXPECT_EQ(os.str(), "(signedByte value)");

}



TEST_F(Nikon3MakerNoteTest_488, BoundaryConditionCountNotOne_488) {

    std::ostringstream os;

    Value value = createValue(unsignedByte, 0x0F);

    value.ok_ = false; // Simulate a situation where count() might not return 1

    Nikon3MakerNote::printExternalFlashData2(os, value, &metadata);



    EXPECT_EQ(os.str(), "(unsignedByte value)");

}
