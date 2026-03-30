#include <gtest/gtest.h>

#include <gmock/gmock.h>



extern "C" {

    int Gfseek(FILE *f, Goffset offset, int whence);

}



class GfileTest_42 : public ::testing::Test {

protected:

    FILE* mockFile;



    void SetUp() override {

        mockFile = fopen("dummy.txt", "w+");

        if (!mockFile) {

            FAIL() << "Failed to create a dummy file for testing";

        }

    }



    void TearDown() override {

        fclose(mockFile);

        remove("dummy.txt");

    }

};



TEST_F(GfileTest_42, Gfseek_SeekToBeginningOfFile_42) {

    int result = Gfseek(mockFile, 0, SEEK_SET);

    EXPECT_EQ(result, 0);

}



TEST_F(GfileTest_42, Gfseek_SeekToEndOfFile_42) {

    fputs("Hello", mockFile);

    fflush(mockFile);



    int result = Gfseek(mockFile, 0, SEEK_END);

    EXPECT_EQ(result, 0);

}



TEST_F(GfileTest_42, Gfseek_SeekWithOffset_42) {

    fputs("Hello", mockFile);

    fflush(mockFile);



    int result = Gfseek(mockFile, 3, SEEK_SET);

    EXPECT_EQ(result, 0);



    long pos = ftell(mockFile);

    EXPECT_EQ(pos, 3L);

}



TEST_F(GfileTest_42, Gfseek_SeekWithNegativeOffset_42) {

    fputs("Hello", mockFile);

    fflush(mockFile);



    int result = Gfseek(mockFile, -1, SEEK_END);

    EXPECT_EQ(result, 0);



    long pos = ftell(mockFile);

    EXPECT_EQ(pos, 4L); // Length of "Hello" is 5, so position should be at 'o'

}



TEST_F(GfileTest_42, Gfseek_SeekPastEndOfFile_42) {

    int result = Gfseek(mockFile, 10, SEEK_SET);

    EXPECT_EQ(result, 0);



    long pos = ftell(mockFile);

    EXPECT_EQ(pos, 10L);

}



TEST_F(GfileTest_42, Gfseek_InvalidWhence_42) {

    int result = Gfseek(mockFile, 0, 99); // Invalid whence value

    EXPECT_NE(result, 0);

}
