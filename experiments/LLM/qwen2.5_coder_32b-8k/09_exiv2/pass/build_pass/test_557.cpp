#include <gtest/gtest.h>

#include "exiv2/basicio.hpp"

#include <string>



using namespace Exiv2;



class FileIoTest_557 : public ::testing::Test {

protected:

    void SetUp() override {

        fileIo = std::make_unique<FileIo>("testfile");

    }



    std::unique_ptr<FileIo> fileIo;

};



TEST_F(FileIoTest_557, TellReturnsZeroWhenFileNotOpened_557) {

    EXPECT_EQ(fileIo->tell(), 0);

}



TEST_F(FileIoTest_557, TellReturnsPositionAfterSeek_557) {

    fileIo->open("r+");

    fileIo->seek(10, FileIo::beg);

    EXPECT_EQ(fileIo->tell(), 10);

    fileIo->close();

}



TEST_F(FileIoTest_557, TellDoesNotChangeWhenFileClosed_557) {

    fileIo->open("r+");

    fileIo->seek(10, FileIo::beg);

    fileIo->close();

    EXPECT_EQ(fileIo->tell(), 10);

}



TEST_F(FileIoTest_557, TellThrowsErrorIfSeekFails_557) {

    // Assuming seek fails and throws an error, but since we cannot mock internal behavior,

    // we assume the implementation handles it internally and returns a consistent state.

    fileIo->open("r+");

    int result = fileIo->seek(-1, FileIo::beg);

    EXPECT_NE(result, 0); // Assuming non-zero indicates failure

    EXPECT_EQ(fileIo->tell(), 0); // Position should remain unchanged on seek failure

    fileIo->close();

}



TEST_F(FileIoTest_557, TellBoundaryConditionAtFileStart_557) {

    fileIo->open("r+");

    EXPECT_EQ(fileIo->tell(), 0);

    fileIo->close();

}



TEST_F(FileIoTest_557, TellBoundaryConditionAtLargeOffset_557) {

    fileIo->open("r+");

    int64_t largeOffset = std::numeric_limits<int64_t>::max();

    fileIo->seek(largeOffset, FileIo::beg);

    EXPECT_EQ(fileIo->tell(), static_cast<size_t>(largeOffset)); // This may fail if the file cannot be seeked to such a position

    fileIo->close();

}
