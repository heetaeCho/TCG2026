#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"

#include "exiv2/exif.hpp"

#include "./TestProjects/exiv2/src/sonymn_int.hpp"



namespace Exiv2 {

namespace Internal {



using ::testing::_;

using ::testing::Return;



class SonyMakerNoteTest_1591 : public ::testing::Test {

protected:

    SonyMakerNote sonyMakerNote;

    Value value;

    const ExifData* metadata = nullptr;



    void SetUp() override {

        // Initialize the value with a type and data for testing

        value = Value(TypeId::unsignedLong);

    }

};



TEST_F(SonyMakerNoteTest_1591, InvalidCount_ReturnsFormattedString_1591) {

    std::ostringstream os;

    value = Value(TypeId::unsignedLong);

    value.setDataArea(reinterpret_cast<const byte*>(&uint32_t{0}), sizeof(uint32_t));

    

    // Set an invalid count

    EXPECT_CALL(value, count()).WillOnce(Return(2));



    auto result = sonyMakerNote.printAutoHDRStd(os, value, metadata);



    EXPECT_EQ(result.str(), "(Value 0)");

}



TEST_F(SonyMakerNoteTest_1591, InvalidTypeId_ReturnsFormattedString_1591) {

    std::ostringstream os;

    value = Value(TypeId::unsignedShort); // wrong type id

    value.setDataArea(reinterpret_cast<const byte*>(&uint32_t{0}), sizeof(uint32_t));



    auto result = sonyMakerNote.printAutoHDRStd(os, value, metadata);



    EXPECT_EQ(result.str(), "(Value 0)");

}



TEST_F(SonyMakerNoteTest_1591, ValidInput_ReturnsCorrectString_1591) {

    std::ostringstream os;

    uint32_t data = 0x170001; // part1 = 1 (Auto), part2 = 0 (Uncorrected image)

    value.setDataArea(reinterpret_cast<const byte*>(&data), sizeof(uint32_t));



    auto result = sonyMakerNote.printAutoHDRStd(os, value, metadata);



    EXPECT_EQ(result.str(), "Auto, Uncorrected image");

}



TEST_F(SonyMakerNoteTest_1591, BoundaryCondition_Part1_MaxValue_ReturnsCorrectString_1591) {

    std::ostringstream os;

    uint32_t data = 0x1A0001; // part1 = 26 (6.0 EV), part2 = 0 (Uncorrected image)

    value.setDataArea(reinterpret_cast<const byte*>(&data), sizeof(uint32_t));



    auto result = sonyMakerNote.printAutoHDRStd(os, value, metadata);



    EXPECT_EQ(result.str(), "6.0 EV, Uncorrected image");

}



TEST_F(SonyMakerNoteTest_1591, BoundaryCondition_Part2_MaxValue_ReturnsCorrectString_1591) {

    std::ostringstream os;

    uint32_t data = 0x170003; // part1 = 1 (Auto), part2 = 3 (HDR (fail 2))

    value.setDataArea(reinterpret_cast<const byte*>(&data), sizeof(uint32_t));



    auto result = sonyMakerNote.printAutoHDRStd(os, value, metadata);



    EXPECT_EQ(result.str(), "Auto, HDR (fail 2)");

}



TEST_F(SonyMakerNoteTest_1591, Part1_UnknownValue_ReturnsFormattedString_1591) {

    std::ostringstream os;

    uint32_t data = 0x1F0001; // part1 = 31 (unknown), part2 = 0 (Uncorrected image)

    value.setDataArea(reinterpret_cast<const byte*>(&data), sizeof(uint32_t));



    auto result = sonyMakerNote.printAutoHDRStd(os, value, metadata);



    EXPECT_EQ(result.str(), "15, Uncorrected image");

}



TEST_F(SonyMakerNoteTest_1591, Part2_UnknownValue_ReturnsFormattedString_1591) {

    std::ostringstream os;

    uint32_t data = 0x170004; // part1 = 1 (Auto), part2 = 4 (unknown)

    value.setDataArea(reinterpret_cast<const byte*>(&data), sizeof(uint32_t));



    auto result = sonyMakerNote.printAutoHDRStd(os, value, metadata);



    EXPECT_EQ(result.str(), "Auto, 4");

}



} // namespace Internal

} // namespace Exiv2
