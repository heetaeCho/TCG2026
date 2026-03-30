#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffvisitor_int.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::HasSubstr;



class TiffReaderTest_1700 : public ::testing::Test {

protected:

    TiffReaderTest_1700() : tiffReader(nullptr, 0, nullptr, TiffRwState()) {}



    TiffReader tiffReader;

};



TEST_F(TiffReaderTest_1700, CircularReference_DifferentPointers_ReturnsFalse_1700) {

    const byte* start1 = reinterpret_cast<const byte*>(0x1);

    IfdId group1 = 1;



    EXPECT_FALSE(tiffReader.circularReference(start1, group1));

}



TEST_F(TiffReaderTest_1700, CircularReference_SamePointer_ReturnsTrue_1700) {

    const byte* start1 = reinterpret_cast<const byte*>(0x1);

    IfdId group1 = 1;



    tiffReader.circularReference(start1, group1);



    EXPECT_TRUE(tiffReader.circularReference(start1, group1));

}



TEST_F(TiffReaderTest_1700, CircularReference_DifferentGroups_ReturnsFalse_1700) {

    const byte* start1 = reinterpret_cast<const byte*>(0x1);

    IfdId group1 = 1;

    IfdId group2 = 2;



    tiffReader.circularReference(start1, group1);



    EXPECT_FALSE(tiffReader.circularReference(start1, group2));

}



TEST_F(TiffReaderTest_1700, CircularReference_MultiplePointers_ReturnsFalse_1700) {

    const byte* start1 = reinterpret_cast<const byte*>(0x1);

    const byte* start2 = reinterpret_cast<const byte*>(0x2);

    IfdId group1 = 1;



    tiffReader.circularReference(start1, group1);



    EXPECT_FALSE(tiffReader.circularReference(start2, group1));

}



TEST_F(TiffReaderTest_1700, CircularReference_SamePointerDifferentGroups_ReturnsTrue_1700) {

    const byte* start1 = reinterpret_cast<const byte*>(0x1);

    IfdId group1 = 1;

    IfdId group2 = 2;



    tiffReader.circularReference(start1, group1);



    EXPECT_TRUE(tiffReader.circularReference(start1, group2));

}



TEST_F(TiffReaderTest_1700, CircularReference_LogsWarningOnCircularReference_1700) {

    const byte* start1 = reinterpret_cast<const byte*>(0x1);

    IfdId group1 = 1;



    testing::internal::CaptureStderr();

    tiffReader.circularReference(start1, group1);

    tiffReader.circularReference(start1, group1);

    std::string output = testing::internal::GetCapturedStderr();



    EXPECT_THAT(output, HasSubstr("pointer references previously read"));

}



TEST_F(TiffReaderTest_1700, CircularReference_LogsCorrectGroupNames_1700) {

    const byte* start1 = reinterpret_cast<const byte*>(0x1);

    IfdId group1 = 1;

    IfdId group2 = 2;



    testing::internal::CaptureStderr();

    tiffReader.circularReference(start1, group1);

    tiffReader.circularReference(start1, group2);

    std::string output = testing::internal::GetCapturedStderr();



    EXPECT_THAT(output, HasSubstr("IFD0"));

}
