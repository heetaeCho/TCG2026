#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include "nikonmn_int.hpp"  // Assuming the relevant header is included

namespace Exiv2 {
    namespace Internal {
        class MockExifData : public ExifData {
        public:
            MOCK_METHOD(int, count, (), (const, override));
            MOCK_METHOD(int, typeId, (), (const, override));
            MOCK_METHOD(int64_t, toInt64, (), (const, override));
        };
    }
}

using namespace Exiv2::Internal;

TEST_F(Nikon3MakerNoteTest_481, PrintExitPupilPosition_NormalCase_481) {
    std::ostringstream os;
    Nikon3MakerNote makerNote;
    Value value(2048); // Assuming a constructor of Value for simplicity
    MockExifData exifData;
    
    // Setting up mock behavior
    EXPECT_CALL(exifData, count()).WillOnce(testing::Return(1));
    EXPECT_CALL(exifData, typeId()).WillOnce(testing::Return(unsignedByte));
    EXPECT_CALL(exifData, toInt64()).WillOnce(testing::Return(1024));

    // Run the method under test
    makerNote.printExitPupilPosition(os, value, &exifData);

    // Validate the output
    EXPECT_EQ(os.str(), "2.0 mm");
}

TEST_F(Nikon3MakerNoteTest_482, PrintExitPupilPosition_ZeroPosition_482) {
    std::ostringstream os;
    Nikon3MakerNote makerNote;
    Value value(0);  // Invalid value for exit pupil position
    MockExifData exifData;
    
    // Setting up mock behavior
    EXPECT_CALL(exifData, count()).WillOnce(testing::Return(1));
    EXPECT_CALL(exifData, typeId()).WillOnce(testing::Return(unsignedByte));
    EXPECT_CALL(exifData, toInt64()).WillOnce(testing::Return(0));

    // Run the method under test
    makerNote.printExitPupilPosition(os, value, &exifData);

    // Validate the output
    EXPECT_EQ(os.str(), "(0)");
}

TEST_F(Nikon3MakerNoteTest_483, PrintExitPupilPosition_InvalidCount_483) {
    std::ostringstream os;
    Nikon3MakerNote makerNote;
    Value value(2048); // Valid value for exit pupil position
    MockExifData exifData;
    
    // Setting up mock behavior for invalid count
    EXPECT_CALL(exifData, count()).WillOnce(testing::Return(0));  // Invalid count
    EXPECT_CALL(exifData, typeId()).WillOnce(testing::Return(unsignedByte));
    EXPECT_CALL(exifData, toInt64()).WillOnce(testing::Return(1024));

    // Run the method under test
    makerNote.printExitPupilPosition(os, value, &exifData);

    // Validate the output
    EXPECT_EQ(os.str(), "(2048)");
}

TEST_F(Nikon3MakerNoteTest_484, PrintExitPupilPosition_InvalidTypeId_484) {
    std::ostringstream os;
    Nikon3MakerNote makerNote;
    Value value(2048); // Valid value for exit pupil position
    MockExifData exifData;
    
    // Setting up mock behavior for invalid typeId
    EXPECT_CALL(exifData, count()).WillOnce(testing::Return(1));
    EXPECT_CALL(exifData, typeId()).WillOnce(testing::Return(999));  // Invalid typeId
    EXPECT_CALL(exifData, toInt64()).WillOnce(testing::Return(1024));

    // Run the method under test
    makerNote.printExitPupilPosition(os, value, &exifData);

    // Validate the output
    EXPECT_EQ(os.str(), "(2048)");
}

TEST_F(Nikon3MakerNoteTest_485, PrintExitPupilPosition_InvalidInt64Value_485) {
    std::ostringstream os;
    Nikon3MakerNote makerNote;
    Value value(2048); // Valid value for exit pupil position
    MockExifData exifData;
    
    // Setting up mock behavior for invalid toInt64() return value
    EXPECT_CALL(exifData, count()).WillOnce(testing::Return(1));
    EXPECT_CALL(exifData, typeId()).WillOnce(testing::Return(unsignedByte));
    EXPECT_CALL(exifData, toInt64()).WillOnce(testing::Return(-1));  // Invalid int64 value

    // Run the method under test
    makerNote.printExitPupilPosition(os, value, &exifData);

    // Validate the output
    EXPECT_EQ(os.str(), "(2048)");
}