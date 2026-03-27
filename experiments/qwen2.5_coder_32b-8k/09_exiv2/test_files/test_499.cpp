#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "./TestProjects/exiv2/src/nikonmn_int.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class Nikon3MakerNoteTest_499 : public ::testing::Test {

protected:

    Nikon3MakerNote maker_note_;

    std::ostringstream os_;

    Value value_{TypeId::unsignedByte};

    const ExifData exif_data_{};



    void SetUp() override {

        value_.setDataArea(reinterpret_cast<const byte*>(&value_data_), sizeof(value_data_));

    }



    uint8_t value_data_ = 0;

};



TEST_F(Nikon3MakerNoteTest_499, NormalOperationBackgroundOnly_499) {

    value_data_ = 4; // Background Only

    maker_note_.printExternalFlashData3(os_, value_, &exif_data_);

    EXPECT_EQ(os_.str(), "Exposure Comp.: Background Only");

}



TEST_F(Nikon3MakerNoteTest_499, NormalOperationEntireFrame_499) {

    value_data_ = 0; // Entire frame

    maker_note_.printExternalFlashData3(os_, value_, &exif_data_);

    EXPECT_EQ(os_.str(), "Exposure Comp.: Entire frame");

}



TEST_F(Nikon3MakerNoteTest_499, BoundaryConditionZeroValue_499) {

    value_data_ = 0; // Minimum valid value

    maker_note_.printExternalFlashData3(os_, value_, &exif_data_);

    EXPECT_EQ(os_.str(), "Exposure Comp.: Entire frame");

}



TEST_F(Nikon3MakerNoteTest_499, BoundaryConditionFourValue_499) {

    value_data_ = 4; // Maximum valid value

    maker_note_.printExternalFlashData3(os_, value_, &exif_data_);

    EXPECT_EQ(os_.str(), "Exposure Comp.: Background Only");

}



TEST_F(Nikon3MakerNoteTest_499, InvalidTypeId_499) {

    Value invalid_type_value{TypeId::asciiString};

    maker_note_.printExternalFlashData3(os_, invalid_type_value, &exif_data_);

    EXPECT_EQ(os_.str(), "(Exiv2::Value (asciiString))");

}



TEST_F(Nikon3MakerNoteTest_499, CountNotOne_499) {

    value_.setDataArea(reinterpret_cast<const byte*>(&value_data_), 2); // Setting count to 2

    maker_note_.printExternalFlashData3(os_, value_, &exif_data_);

    EXPECT_EQ(os_.str(), "(Exiv2::Value (unsignedByte))");

}
