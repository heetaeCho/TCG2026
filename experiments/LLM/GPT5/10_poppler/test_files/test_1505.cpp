#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <stdexcept>

extern "C" {
    static int getCharFromFile(void *data) { return fgetc((FILE *)data); }
}

// Mock file to simulate file reading
class MockFile {
public:
    MOCK_METHOD(int, fgetc, (FILE*), ());
};

// Test Fixture for testing getCharFromFile
class GetCharFromFileTest_1505 : public ::testing::Test {
protected:
    FILE* mockFile;

    void SetUp() override {
        // Open a temporary file for testing
        mockFile = tmpfile();
    }

    void TearDown() override {
        // Close the file after tests
        if (mockFile) {
            fclose(mockFile);
        }
    }
};

// Normal operation test: Test if getCharFromFile reads a character correctly from the file
TEST_F(GetCharFromFileTest_1505, ReadSingleCharacter_1505) {
    // Arrange: Write a character into the file
    fputc('A', mockFile);
    rewind(mockFile);  // Move the file pointer to the start

    // Act: Read the character from the file
    int result = getCharFromFile(mockFile);

    // Assert: Check if the result matches the expected character
    ASSERT_EQ(result, 'A');
}

// Boundary condition test: Test if getCharFromFile handles reading at EOF correctly
TEST_F(GetCharFromFileTest_1505, ReadEOF_1505) {
    // Arrange: Write nothing to the file
    rewind(mockFile);  // Move the file pointer to the start

    // Act: Try reading from an empty file
    int result = getCharFromFile(mockFile);

    // Assert: EOF should be returned when the file is empty
    ASSERT_EQ(result, EOF);
}

// Exceptional case: Test if getCharFromFile handles a null file pointer
TEST_F(GetCharFromFileTest_1505, NullFilePointer_1505) {
    // Act: Call getCharFromFile with a null pointer
    int result = getCharFromFile(nullptr);

    // Assert: The function should return EOF for a null pointer
    ASSERT_EQ(result, EOF);
}

// Test for exceptional case when file pointer is not valid
TEST_F(GetCharFromFileTest_1505, InvalidFilePointer_1505) {
    // Arrange: Set the file pointer to an invalid address
    FILE* invalidFile = (FILE*)0x12345678;

    // Act: Try reading from the invalid file pointer
    int result = getCharFromFile(invalidFile);

    // Assert: The function should return EOF for an invalid file pointer
    ASSERT_EQ(result, EOF);
}