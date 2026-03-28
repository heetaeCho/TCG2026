#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/casiomn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;



class Casio2MakerNoteTest_1353 : public ::testing::Test {

protected:

    std::ostringstream os;

    Value mockValue; // Assuming Value is a valid type in the context

    ExifData mockExifData; // Assuming ExifData is a valid type in the context

};



TEST_F(Casio2MakerNoteTest_1353, Print0x2001_NormalOperation_1353) {

    Casio2MakerNote::print0x2001(os, mockValue, &mockExifData);

    EXPECT_FALSE(os.str().empty()); // Assuming print0x2001 should produce some output

}



TEST_F(Casio2MakerNoteTest_1353, Print0x2022_NormalOperation_1353) {

    Casio2MakerNote::print0x2022(os, mockValue, &mockExifData);

    EXPECT_FALSE(os.str().empty()); // Assuming print0x2022 should produce some output

}



TEST_F(Casio2MakerNoteTest_1353, Print0x2001_EmptyValue_1353) {

    Casio2MakerNote::print0x2001(os, mockValue, &mockExifData);

    EXPECT_FALSE(os.str().empty()); // Assuming print0x2001 should handle empty value gracefully

}



TEST_F(Casio2MakerNoteTest_1353, Print0x2022_EmptyValue_1353) {

    Casio2MakerNote::print0x2022(os, mockValue, &mockExifData);

    EXPECT_FALSE(os.str().empty()); // Assuming print0x2022 should handle empty value gracefully

}



TEST_F(Casio2MakerNoteTest_1353, Print0x2001_NullExifData_1353) {

    Casio2MakerNote::print0x2001(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty()); // Assuming print0x2001 should handle null ExifData gracefully

}



TEST_F(Casio2MakerNoteTest_1353, Print0x2022_NullExifData_1353) {

    Casio2MakerNote::print0x2022(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty()); // Assuming print0x2022 should handle null ExifData gracefully

}



TEST_F(Casio2MakerNoteTest_1353, TagList_ReturnsNonNull_1353) {

    const auto* tagInfo = Casio2MakerNote::tagList();

    EXPECT_NE(tagInfo, nullptr); // Assuming tagList should return a non-null pointer

}
