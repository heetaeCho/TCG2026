#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "panasonicmn_int.cpp"



namespace Exiv2 { namespace Internal {



class PanasonicMakerNoteTest_709 : public ::testing::Test {

protected:

    PanasonicMakerNote panasonicMakerNote;

    std::ostringstream os;

};



TEST_F(PanasonicMakerNoteTest_709, Print0x0029_NormalOperation_709) {

    Value value;

    value._content = 366100; // Represents 01:01:01.00

    const ExifData* exifData = nullptr;



    std::ostream& resultStream = panasonicMakerNote.print0x0029(os, value, exifData);



    EXPECT_EQ(resultStream.str(), "01:01:01.00");

}



TEST_F(PanasonicMakerNoteTest_709, Print0x0029_BoundaryCondition_ZeroTime_709) {

    Value value;

    value._content = 0; // Represents 00:00:00.00

    const ExifData* exifData = nullptr;



    std::ostream& resultStream = panasonicMakerNote.print0x0029(os, value, exifData);



    EXPECT_EQ(resultStream.str(), "00:00:00.00");

}



TEST_F(PanasonicMakerNoteTest_709, Print0x0029_BoundaryCondition_MaxTime_709) {

    Value value;

    value._content = 8639999; // Represents 23:59:59.99

    const ExifData* exifData = nullptr;



    std::ostream& resultStream = panasonicMakerNote.print0x0029(os, value, exifData);



    EXPECT_EQ(resultStream.str(), "23:59:59.99");

}



TEST_F(PanasonicMakerNoteTest_709, Print0x0029_ExceptionalCase_NegativeTime_709) {

    Value value;

    value._content = -1; // Represents a negative time

    const ExifData* exifData = nullptr;



    std::ostream& resultStream = panasonicMakerNote.print0x0029(os, value, exifData);



    EXPECT_EQ(resultStream.str(), "23:59:59.99"); // Assuming wrap-around behavior

}



}} // namespace Exiv2::Internal
