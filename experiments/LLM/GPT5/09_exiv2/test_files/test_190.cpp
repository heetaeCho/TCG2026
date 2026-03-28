#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include "pentaxmn_int.cpp"  // Include the file containing the class

using namespace Exiv2::Internal;

class MockExifData : public ExifData {
    // Mock ExifData class if it's needed, add mock methods if required.
};

class PentaxMakerNoteTest_190 : public ::testing::Test {
protected:
    PentaxMakerNote pentaxMakerNote;
    std::ostringstream os;
    MockExifData mockExifData;  // Create a mock object for ExifData
};

TEST_F(PentaxMakerNoteTest_190, PrintResolution_HandlesValidValue_190) {
    // Setup: Prepare a valid Value object
    Value value("1920 1080");  // Test case with space between numbers
    // Execute: Call the method under test
    pentaxMakerNote.printResolution(os, value, &mockExifData);
    // Verify: Check if the output has replaced space with 'x' as expected
    EXPECT_EQ(os.str(), "1920x1080");
}

TEST_F(PentaxMakerNoteTest_190, PrintResolution_HandlesSingleValue_190) {
    // Setup: Prepare a single value
    Value value("720");
    // Execute: Call the method under test
    pentaxMakerNote.printResolution(os, value, &mockExifData);
    // Verify: Ensure that there is no modification to a single value
    EXPECT_EQ(os.str(), "720");
}

TEST_F(PentaxMakerNoteTest_190, PrintResolution_HandlesEmptyString_190) {
    // Setup: Prepare an empty value
    Value value("");
    // Execute: Call the method under test
    pentaxMakerNote.printResolution(os, value, &mockExifData);
    // Verify: The result should still be an empty string
    EXPECT_EQ(os.str(), "");
}

TEST_F(PentaxMakerNoteTest_190, PrintResolution_HandlesMultipleSpaces_190) {
    // Setup: Prepare a value with multiple spaces
    Value value("1280  720");  // Two spaces between numbers
    // Execute: Call the method under test
    pentaxMakerNote.printResolution(os, value, &mockExifData);
    // Verify: Ensure the spaces are replaced with 'x'
    EXPECT_EQ(os.str(), "1280x720");
}

TEST_F(PentaxMakerNoteTest_190, PrintResolution_HandlesEdgeCase_190) {
    // Setup: Prepare a very long string with spaces
    Value value("1000000 5000000");
    // Execute: Call the method under test
    pentaxMakerNote.printResolution(os, value, &mockExifData);
    // Verify: Check if spaces are replaced with 'x' and the result is correct
    EXPECT_EQ(os.str(), "1000000x5000000");
}