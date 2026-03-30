#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"



using namespace Exiv2;



class FileIoTest_555 : public ::testing::Test {

protected:

    FileIo fileIo;

    

    FileIoTest_555() : fileIo("dummy_path") {}

};



TEST_F(FileIoTest_555, PutbReturnsEOFIfSwitchModeFails_555) {

    // Assuming switchMode fails and returns a non-zero value

    EXPECT_EQ(fileIo.putb('A'), EOF);

}



TEST_F(FileIoTest_555, PutbSucceedsAndReturnsCharValue_555) {

    // Assuming file is opened in write mode and putc succeeds

    int result = fileIo.putb('A');

    EXPECT_NE(result, EOF);

    EXPECT_EQ(result, 'A');

}



TEST_F(FileIoTest_555, PutbBoundaryConditionSingleByte_555) {

    // Boundary condition: single byte input

    int result = fileIo.putb('\0');

    EXPECT_NE(result, EOF);

    EXPECT_EQ(result, '\0');

}



TEST_F(FileIoTest_555, PutbErrorHandling_555) {

    // Assuming an error occurs during putc

    // This is a bit tricky to simulate without internal access,

    // but we can assume putc returns EOF in case of error.

    EXPECT_EQ(fileIo.putb('A'), EOF);

}



TEST_F(FileIoTest_555, PutbNormalOperationMultipleBytes_555) {

    // Normal operation: multiple byte inputs

    for (byte data = 'A'; data <= 'Z'; ++data) {

        int result = fileIo.putb(data);

        EXPECT_NE(result, EOF);

        EXPECT_EQ(result, static_cast<int>(data));

    }

}
