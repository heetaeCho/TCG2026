#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/exiv2/src/olympusmn_int.cpp" // Include the file where OlympusMakerNote is defined.

namespace Exiv2 { namespace Internal {

class OlympusMakerNoteTest_899 : public testing::Test {
protected:
    OlympusMakerNote makerNote;
    std::ostringstream os;
    Value value;
    ExifData* exifData = nullptr;
};

TEST_F(OlympusMakerNoteTest_899, TestAutoWhenCountIsOne_899) {
    // Test: Check if the value "Auto" is printed when the first element is 1 and count is 1.
    value = Value(1, unsignedShort);  // Assuming Value can be constructed like this.
    EXPECT_CALL(value, typeId()).WillOnce(testing::Return(unsignedShort));
    EXPECT_CALL(value, count()).WillOnce(testing::Return(1));
    EXPECT_CALL(value, toInt64(0)).WillOnce(testing::Return(1));

    makerNote.print0x1015(os, value, exifData);

    EXPECT_EQ(os.str(), "Auto");
}

TEST_F(OlympusMakerNoteTest_899, TestAutoWithCountTwo_899) {
    // Test: When count is 2 and the first element is 1 and second element is 0, expect "Auto".
    value = Value(2, unsignedShort);  // Assuming Value can be constructed with a count of 2.
    EXPECT_CALL(value, typeId()).WillOnce(testing::Return(unsignedShort));
    EXPECT_CALL(value, count()).WillOnce(testing::Return(2));
    EXPECT_CALL(value, toInt64(0)).WillOnce(testing::Return(1));
    EXPECT_CALL(value, toInt64(1)).WillOnce(testing::Return(0));

    makerNote.print0x1015(os, value, exifData);

    EXPECT_EQ(os.str(), "Auto");
}

TEST_F(OlympusMakerNoteTest_899, TestAutoWithCountTwoAndNonZeroKelvin_899) {
    // Test: When count is 2 and first element is 2 (Kelvin temperature setting), 
    // and second element is 4 (4000 Kelvin), expect the string "4000 Kelvin".
    value = Value(2, unsignedShort);
    EXPECT_CALL(value, typeId()).WillOnce(testing::Return(unsignedShort));
    EXPECT_CALL(value, count()).WillOnce(testing::Return(2));
    EXPECT_CALL(value, toInt64(0)).WillOnce(testing::Return(2));
    EXPECT_CALL(value, toInt64(1)).WillOnce(testing::Return(4));

    makerNote.print0x1015(os, value, exifData);

    EXPECT_EQ(os.str(), "4000 Kelvin");
}

TEST_F(OlympusMakerNoteTest_899, TestOneTouchWithCountTwo_899) {
    // Test: When count is 2 and first element is 3 (One-touch), and second element is 0,
    // expect "One-touch".
    value = Value(2, unsignedShort);
    EXPECT_CALL(value, typeId()).WillOnce(testing::Return(unsignedShort));
    EXPECT_CALL(value, count()).WillOnce(testing::Return(2));
    EXPECT_CALL(value, toInt64(0)).WillOnce(testing::Return(3));
    EXPECT_CALL(value, toInt64(1)).WillOnce(testing::Return(0));

    makerNote.print0x1015(os, value, exifData);

    EXPECT_EQ(os.str(), "One-touch");
}

TEST_F(OlympusMakerNoteTest_899, TestUnhandledValueWithCountGreaterThanTwo_899) {
    // Test: When count is greater than 2 or an unexpected combination of values occurs,
    // the original value is printed.
    value = Value(3, unsignedShort);
    EXPECT_CALL(value, typeId()).WillOnce(testing::Return(unsignedShort));
    EXPECT_CALL(value, count()).WillOnce(testing::Return(3));
    EXPECT_CALL(value, toInt64(0)).WillOnce(testing::Return(5));

    makerNote.print0x1015(os, value, exifData);

    EXPECT_EQ(os.str(), value.toString());
}

} }