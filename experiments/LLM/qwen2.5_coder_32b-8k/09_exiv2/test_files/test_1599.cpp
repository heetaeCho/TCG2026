#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include <exiv2/value.hpp>

#include <exiv2/exifdata.hpp>



using namespace Exiv2;

using namespace Exiv2::Internal;



class SonyMakerNoteTest_1599 : public ::testing::Test {

protected:

    SonyMakerNote sonyMakerNote;

    std::ostringstream os;

};



TEST_F(SonyMakerNoteTest_1599, PrintFocalPlaneAFPointsUsed_NormalOperation_U85) {

    Value value(unsignedByte);

    value.makeArray(1);

    value[0] = 5;



    std::ostream& result = sonyMakerNote.printFocalPlaneAFPointsUsed(os, value, nullptr);



    EXPECT_EQ(result.str(), "(5)");

}



TEST_F(SonyMakerNoteTest_1599, PrintFocalPlaneAFPointsUsed_BoundaryCondition_ZeroValue_1599) {

    Value value(unsignedByte);

    value.makeArray(1);

    value[0] = 0;



    std::ostream& result = sonyMakerNote.printFocalPlaneAFPointsUsed(os, value, nullptr);



    EXPECT_EQ(result.str(), "None");

}



TEST_F(SonyMakerNoteTest_1599, PrintFocalPlaneAFPointsUsed_BoundaryCondition_EmptyArray_1599) {

    Value value(unsignedByte);

    value.makeArray(0);



    std::ostream& result = sonyMakerNote.printFocalPlaneAFPointsUsed(os, value, nullptr);



    EXPECT_EQ(result.str(), "(Exiv2::Value())");

}



TEST_F(SonyMakerNoteTest_1599, PrintFocalPlaneAFPointsUsed_ExceptionalCase_WrongType_1599) {

    Value value(short);

    value.makeArray(1);

    value[0] = 5;



    std::ostream& result = sonyMakerNote.printFocalPlaneAFPointsUsed(os, value, nullptr);



    EXPECT_EQ(result.str(), "(Exiv2::Value())");

}
