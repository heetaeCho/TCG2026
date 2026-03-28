#include <gtest/gtest.h>

#include "Stream.h"



// Mock GooFile class if needed, but for this case, it's not required as we treat FileStream as a black box.



class FileStreamTest_151 : public ::testing::Test {

protected:

    virtual void SetUp() {

        // Initialize the GooFile mock or any other setup if necessary.

        gooFileMock = new GooFile(); // Assuming GooFile has a default constructor for this test

        fileStream = std::make_unique<FileStream>(gooFileMock, 0, false, 16384, Object());

    }



    virtual void TearDown() {

        // Clean up resources if necessary.

        fileStream.reset();

        delete gooFileMock;

    }



    GooFile* gooFileMock;

    std::unique_ptr<FileStream> fileStream;

};



TEST_F(FileStreamTest_151, InitialPositionIsZero_151) {

    EXPECT_EQ(fileStream->getPos(), 0);

}



TEST_F(FileStreamTest_151, SetAndGetPosWorksCorrectly_151) {

    Goffset newPos = 1024;

    fileStream->setPos(newPos, 0);

    EXPECT_EQ(fileStream->getPos(), newPos);

}



TEST_F(FileStreamTest_151, RewindResetsPositionToStart_151) {

    fileStream->setPos(1024, 0);

    fileStream->rewind();

    EXPECT_EQ(fileStream->getPos(), 0);

}



TEST_F(FileStreamTest_151, CloseDoesNotChangePosition_151) {

    Goffset initialPos = fileStream->getPos();

    fileStream->close();

    EXPECT_EQ(fileStream->getPos(), initialPos); // Assuming close does not change the position

}



TEST_F(FileStreamTest_151, MoveStartAdjustsPositionCorrectly_151) {

    Goffset delta = 2048;

    fileStream->moveStart(delta);

    EXPECT_EQ(fileStream->getPos(), delta);

}



// Since the exact behavior of these functions is not specified, we assume they do not affect position directly.

TEST_F(FileStreamTest_151, GetCharDoesNotChangePosition_151) {

    Goffset initialPos = fileStream->getPos();

    fileStream->getChar(); // Assuming getChar does not change the position

    EXPECT_EQ(fileStream->getPos(), initialPos);

}



TEST_F(FileStreamTest_151, LookCharDoesNotChangePosition_151) {

    Goffset initialPos = fileStream->getPos();

    fileStream->lookChar(); // Assuming lookChar does not change the position

    EXPECT_EQ(fileStream->getPos(), initialPos);

}



TEST_F(FileStreamTest_151, GetUnfilteredCharDoesNotChangePosition_151) {

    Goffset initialPos = fileStream->getPos();

    fileStream->getUnfilteredChar(); // Assuming getUnfilteredChar does not change the position

    EXPECT_EQ(fileStream->getPos(), initialPos);

}



TEST_F(FileStreamTest_151, UnfilteredRewindResetsPositionToStart_151) {

    fileStream->setPos(2048, 0);

    fileStream->unfilteredRewind();

    EXPECT_EQ(fileStream->getPos(), 0);

}

```


