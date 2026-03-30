#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <cstdio>



struct FILECloser {

    public: void operator()(FILE *f);

};



class FILECloserTest : public ::testing::Test {

protected:

    FILE* tempFile;



    void SetUp() override {

        tempFile = tmpfile();

        ASSERT_NE(tempFile, nullptr) << "Temporary file creation failed";

    }



    void TearDown() override {

        if (tempFile) {

            fclose(tempFile);

        }

    }

};



TEST_F(FILECloserTest_NormalOperation_1852, ClosesFilePointer_1852) {

    FILE* file = tmpfile();

    ASSERT_NE(file, nullptr) << "Temporary file creation failed";



    FILECloser closer;

    closer(file);



    // Check if the file is closed by attempting to read from it

    int ch = fgetc(file);

    EXPECT_EQ(ch, EOF) << "File should be closed";

}



TEST_F(FILECloserTest_BoundaryConditions_1852, NullPointerHandling_1852) {

    FILE* nullFile = nullptr;



    FILECloser closer;

    // Expect no crash or error when a null pointer is passed

    EXPECT_NO_THROW(closer(nullFile));

}
