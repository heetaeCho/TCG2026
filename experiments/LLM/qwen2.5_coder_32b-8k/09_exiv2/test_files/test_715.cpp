#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include <sstream>

#include <exiv2/value.hpp>



namespace Exiv2 { namespace Internal {



class PanasonicMakerNoteTest : public ::testing::Test {

protected:

    PanasonicMakerNote panasonicMakerNote;

    ExifData exifData; // Mocked dependency, not used in this case

};



TEST_F(PanasonicMakerNoteTest_715, PrintAccelerometer_NormalOperation_715) {

    Value value(0x7FFF); // Example value representing int16_t max

    std::ostringstream os;

    panasonicMakerNote.printAccelerometer(os, value, &exifData);

    EXPECT_EQ(os.str(), "32767");

}



TEST_F(PanasonicMakerNoteTest_715, PrintAccelerometer_MinValue_715) {

    Value value(0x8000); // Example value representing int16_t min

    std::ostringstream os;

    panasonicMakerNote.printAccelerometer(os, value, &exifData);

    EXPECT_EQ(os.str(), "-32768");

}



TEST_F(PanasonicMakerNoteTest_715, PrintAccelerometer_ZeroValue_715) {

    Value value(0x0000); // Example value representing zero

    std::ostringstream os;

    panasonicMakerNote.printAccelerometer(os, value, &exifData);

    EXPECT_EQ(os.str(), "0");

}



TEST_F(PanasonicMakerNoteTest_715, PrintAccelerometer_NegativeValue_715) {

    Value value(0xFFFF); // Example value representing -1 in int16_t

    std::ostringstream os;

    panasonicMakerNote.printAccelerometer(os, value, &exifData);

    EXPECT_EQ(os.str(), "-1");

}



TEST_F(PanasonicMakerNoteTest_715, PrintAccelerometer_PositiveValue_715) {

    Value value(0x0001); // Example value representing 1 in int16_t

    std::ostringstream os;

    panasonicMakerNote.printAccelerometer(os, value, &exifData);

    EXPECT_EQ(os.str(), "1");

}



}} // namespace Exiv2::Internal
