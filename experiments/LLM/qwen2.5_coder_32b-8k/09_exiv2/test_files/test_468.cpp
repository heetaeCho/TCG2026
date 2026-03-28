#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include <exiv2/exif.hpp>

#include <exiv2/value.hpp>

#include <TestProjects/exiv2/src/nikonmn_int.hpp>



using namespace Exiv2;

using namespace Exiv2::Internal;



class Nikon3MakerNoteTest_468 : public ::testing::Test {

protected:

    std::ostringstream os_;

    Value value_;

    ExifData metadata_;



    void SetUp() override {

        // Initialize a default ValueType<uint16_t> for testing

        value_ = ValueType<uint16_t>(0, unsignedShort);

    }

};



TEST_F(Nikon3MakerNoteTest_468, PrintAfPointsInFocus_NormalOperation_468) {

    static_cast<ValueType<uint16_t>&>(value_).value_.push_back(0x000F); // Center, Top, Bottom, Mid-left

    Nikon3MakerNote::printAfPointsInFocus(os_, value_, &metadata_);

    EXPECT_EQ(os_.str(), "Center, Top, Bottom, Mid-left");

}



TEST_F(Nikon3MakerNoteTest_468, PrintAfPointsInFocus_AllPoints_468) {

    static_cast<ValueType<uint16_t>&>(value_).value_.push_back(0x07FF); // All points

    Nikon3MakerNote::printAfPointsInFocus(os_, value_, &metadata_);

    EXPECT_EQ(os_.str(), "All 11 Points");

}



TEST_F(Nikon3MakerNoteTest_468, PrintAfPointsInFocus_BoundaryCondition_468) {

    static_cast<ValueType<uint16_t>&>(value_).value_.push_back(0x0000); // No points in focus

    Nikon3MakerNote::printAfPointsInFocus(os_, value_, &metadata_);

    EXPECT_EQ(os_.str(), "()");

}



TEST_F(Nikon3MakerNoteTest_468, PrintAfPointsInFocus_WrongTypeId_468) {

    Value wrongTypeValue = ValueType<int16_t>(0, signedShort);

    Nikon3MakerNote::printAfPointsInFocus(os_, wrongTypeValue, &metadata_);

    EXPECT_EQ(os_.str(), "(0)");

}



TEST_F(Nikon3MakerNoteTest_468, PrintAfPointsInFocus_NikonDModel_468) {

    static_cast<ValueType<uint16_t>&>(value_).value_.push_back(0x0F00); // Should be transformed to 0x000F

    Exifdatum modelDatum(ExifKey("Exif.Image.Model"), "NIKON D500");

    metadata_.add(modelDatum);

    Nikon3MakerNote::printAfPointsInFocus(os_, value_, &metadata_);

    EXPECT_EQ(os_.str(), "Center, Top, Bottom, Mid-left");

}



TEST_F(Nikon3MakerNoteTest_468, PrintAfPointsInFocus_NonNikonDModel_468) {

    static_cast<ValueType<uint16_t>&>(value_).value_.push_back(0x0F00); // Should remain 0x0F00

    Exifdatum modelDatum(ExifKey("Exif.Image.Model"), "CANON EOS R5");

    metadata_.add(modelDatum);

    Nikon3MakerNote::printAfPointsInFocus(os_, value_, &metadata_);

    EXPECT_EQ(os_.str(), "(3840)");

}
