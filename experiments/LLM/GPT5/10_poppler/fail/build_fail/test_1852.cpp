#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>

struct FILECloser {
public:
    void operator()(FILE *f) {
        fclose(f);
    }
};

// Test Fixture for FILECloser
class FILECloserTest_1852 : public ::testing::Test {
protected:
    FILE *file_ptr;

    void SetUp() override {
        file_ptr = fopen("test.txt", "w+");  // Create a test file
        ASSERT_NE(file_ptr, nullptr);  // Ensure file opened successfully
    }

    void TearDown() override {
        if (file_ptr) {
            fclose(file_ptr);
        }
    }
};

// Test for normal operation of FILECloser
TEST_F(FILECloserTest_1852, ClosesFileSuccessfully_1852) {
    FILECloser closer;
    
    // Ensure file is open
    ASSERT_TRUE(file_ptr != nullptr);

    // Call operator() to close the file
    closer(file_ptr);

    // Ensure file is closed
    ASSERT_EQ(fclose(file_ptr), EOF);  // fclose returns EOF when it fails
}

// Test for boundary condition where file pointer is nullptr
TEST_F(FILECloserTest_1852, DoesNotCrashWhenFileIsNull_1852) {
    FILECloser closer;

    // Passing a null pointer should not crash
    ASSERT_NO_THROW(closer(nullptr));
}

// Test for exceptional case (simulating invalid file pointer)
TEST_F(FILECloserTest_1852, DoesNotCrashOnInvalidFilePointer_1852) {
    FILECloser closer;

    // Use an invalid file pointer (garbage value)
    FILE *invalid_file = reinterpret_cast<FILE *>(0x12345678); // Random invalid address

    // Should not crash
    ASSERT_NO_THROW(closer(invalid_file));
}