#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include "nikonmn_int.hpp" // Assuming this header contains the declaration of Nikon3MakerNote and Value

namespace Exiv2 { namespace Internal {

    class Nikon3MakerNoteTest : public ::testing::Test {
    protected:
        Nikon3MakerNote makerNote;
    };

    // Mocking the Value class for the tests
    class MockValue : public Value {
    public:
        MOCK_METHOD(int, count, (), (const, override));
        MOCK_METHOD(int, typeId, (), (const, override));
        MOCK_METHOD(int64_t, toInt64, (), (const, override));
    };

    TEST_F(Nikon3MakerNoteTest, PrintFocusDistance_ValidValue_477) {
        MockValue mockValue;
        std::ostringstream oss;
        
        // Mock behavior for a valid count and typeId
        EXPECT_CALL(mockValue, count()).WillOnce(testing::Return(1));
        EXPECT_CALL(mockValue, typeId()).WillOnce(testing::Return(unsignedByte));
        EXPECT_CALL(mockValue, toInt64()).WillOnce(testing::Return(120));

        // Capture the output
        makerNote.printFocusDistance(oss, mockValue, nullptr);

        // Verify the output format
        EXPECT_EQ(oss.str(), "1.50 m");
    }

    TEST_F(Nikon3MakerNoteTest, PrintFocusDistance_InvalidCount_478) {
        MockValue mockValue;
        std::ostringstream oss;

        // Mock behavior for an invalid count
        EXPECT_CALL(mockValue, count()).WillOnce(testing::Return(0));

        // Capture the output
        makerNote.printFocusDistance(oss, mockValue, nullptr);

        // Verify the output for invalid count
        EXPECT_EQ(oss.str(), "(0)");
    }

    TEST_F(Nikon3MakerNoteTest, PrintFocusDistance_InvalidType_479) {
        MockValue mockValue;
        std::ostringstream oss;

        // Mock behavior for an invalid typeId
        EXPECT_CALL(mockValue, count()).WillOnce(testing::Return(1));
        EXPECT_CALL(mockValue, typeId()).WillOnce(testing::Return(999)); // invalid typeId

        // Capture the output
        makerNote.printFocusDistance(oss, mockValue, nullptr);

        // Verify the output for invalid typeId
        EXPECT_EQ(oss.str(), "(0)");
    }

    TEST_F(Nikon3MakerNoteTest, PrintFocusDistance_ZeroValue_480) {
        MockValue mockValue;
        std::ostringstream oss;

        // Mock behavior for a value that translates to 0
        EXPECT_CALL(mockValue, count()).WillOnce(testing::Return(1));
        EXPECT_CALL(mockValue, typeId()).WillOnce(testing::Return(unsignedByte));
        EXPECT_CALL(mockValue, toInt64()).WillOnce(testing::Return(0));

        // Capture the output
        makerNote.printFocusDistance(oss, mockValue, nullptr);

        // Verify the output for zero value
        EXPECT_EQ(oss.str(), "n/a");
    }

    TEST_F(Nikon3MakerNoteTest, PrintFocusDistance_InvalidReturnValue_481) {
        MockValue mockValue;
        std::ostringstream oss;

        // Mock behavior for a value that is neither valid nor zero
        EXPECT_CALL(mockValue, count()).WillOnce(testing::Return(1));
        EXPECT_CALL(mockValue, typeId()).WillOnce(testing::Return(unsignedByte));
        EXPECT_CALL(mockValue, toInt64()).WillOnce(testing::Return(99999));

        // Capture the output
        makerNote.printFocusDistance(oss, mockValue, nullptr);

        // Check the returned string format
        EXPECT_EQ(oss.str(), "10.00 m");
    }
}