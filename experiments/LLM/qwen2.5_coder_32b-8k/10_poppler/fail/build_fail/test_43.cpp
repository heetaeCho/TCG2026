#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <cstdio>



// Assuming Goffset and Gftell are defined in a header file that we include

extern "C" {

    typedef long long Goffset;

    Goffset Gftell(FILE *f);

}



class GftellTest_43 : public ::testing::Test {

protected:

    FILE* tempFile;



    void SetUp() override {

        // Create a temporary file for testing

        tempFile = tmpfile();

        ASSERT_NE(tempFile, nullptr) << "Failed to create temporary file";

    }



    void TearDown() override {

        if (tempFile) {

            fclose(tempFile);

        }

    }

};



TEST_F(GftellTest_43, InitialPositionIsZero_43) {

    Goffset position = Gftell(tempFile);

    EXPECT_EQ(position, 0) << "Initial file position should be zero";

}



TEST_F(GftellTest_43, PositionAfterWrite_43) {

    const char* data = "Hello, world!";

    size_t dataSize = strlen(data);



    // Write data to the temporary file

    fwrite(data, 1, dataSize, tempFile);

    fflush(tempFile);  // Ensure all data is written



    Goffset position = Gftell(tempFile);

    EXPECT_EQ(position, static_cast<Goffset>(dataSize)) << "Position should be equal to the number of bytes written";

}



TEST_F(GftellTest_43, PositionAfterSeek_43) {

    const char* data = "Hello, world!";

    size_t dataSize = strlen(data);



    // Write data to the temporary file

    fwrite(data, 1, dataSize, tempFile);

    fflush(tempFile);  // Ensure all data is written



    // Seek to a specific position in the file

    fseek(tempFile, 7, SEEK_SET);



    Goffset position = Gftell(tempFile);

    EXPECT_EQ(position, 7) << "Position should be equal to the seeked position";

}



TEST_F(GftellTest_43, PositionAfterRewind_43) {

    const char* data = "Hello, world!";

    size_t dataSize = strlen(data);



    // Write data to the temporary file

    fwrite(data, 1, dataSize, tempFile);

    fflush(tempFile);  // Ensure all data is written



    // Rewind the file position

    rewind(tempFile);



    Goffset position = Gftell(tempFile);

    EXPECT_EQ(position, 0) << "Position should be zero after rewinding";

}



TEST_F(GftellTest_43, InvalidFileHandle_43) {

    FILE* invalidFile = nullptr;

    Goffset position = Gftell(invalidFile);

    // Behavior is undefined for an invalid file handle, but we can check if it returns a specific value or not

    // Here we assume it should return -1 as per common practice in C

    EXPECT_EQ(position, static_cast<Goffset>(-1)) << "Position should be -1 for invalid file handle";

}
