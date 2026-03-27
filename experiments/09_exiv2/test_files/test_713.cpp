#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include <exiv2/exif.hpp>



using namespace Exiv2;

using namespace Exiv2::Internal;



class PanasonicMakerNoteTest_713 : public ::testing::Test {

protected:

    PanasonicMakerNote panasonicMakerNote_;

};



TEST_F(PanasonicMakerNoteTest_713, PrintPanasonicText_NormalOperation_713) {

    ExifData exifData;

    Value value = Value::create(Exiv2::unsignedLong);

    value.modify(0, 72);  // 'H'

    value.modify(1, 101); // 'e'

    value.modify(2, 108); // 'l'

    value.modify(3, 108); // 'l'

    value.modify(4, 111); // 'o'



    std::ostringstream oss;

    panasonicMakerNote_.printPanasonicText(oss, value, &exifData);



    EXPECT_EQ("Hello", oss.str());

}



TEST_F(PanasonicMakerNoteTest_713, PrintPanasonicText_EmptyValue_713) {

    ExifData exifData;

    Value value = Value::create(Exiv2::unsignedLong);



    std::ostringstream oss;

    panasonicMakerNote_.printPanasonicText(oss, value, &exifData);



    EXPECT_EQ("", oss.str());

}



TEST_F(PanasonicMakerNoteTest_713, PrintPanasonicText_ZeroTermination_713) {

    ExifData exifData;

    Value value = Value::create(Exiv2::unsignedLong);

    value.modify(0, 72);  // 'H'

    value.modify(1, 101); // 'e'

    value.modify(2, 0);   // '\0'



    std::ostringstream oss;

    panasonicMakerNote_.printPanasonicText(oss, value, &exifData);



    EXPECT_EQ("He", oss.str());

}



TEST_F(PanasonicMakerNoteTest_713, PrintPanasonicText_WrongType_713) {

    ExifData exifData;

    Value value = Value::create(Exiv2::undefined);

    value.modify(0, 72);  // 'H'

    value.modify(1, 101); // 'e'



    std::ostringstream oss;

    panasonicMakerNote_.printPanasonicText(oss, value, &exifData);



    EXPECT_EQ(value.toString(), oss.str());

}



TEST_F(PanasonicMakerNoteTest_713, PrintPanasonicText_LargeValue_713) {

    ExifData exifData;

    Value value = Value::create(Exiv2::unsignedLong);

    for (int i = 0; i < 50; ++i) {

        value.modify(i, 65 + i % 26); // 'A' to 'Z'

    }



    std::ostringstream oss;

    panasonicMakerNote_.printPanasonicText(oss, value, &exifData);



    EXPECT_EQ("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRST", oss.str());

}
