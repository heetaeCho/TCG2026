#include <gtest/gtest.h>

#include "exiv2/basicio.hpp"

#include <string>



using namespace Exiv2;



class FileIoTest_551 : public ::testing::Test {

protected:

    void SetUp() override {

        fileIo = std::make_unique<FileIo>("initial_path");

    }



    std::unique_ptr<FileIo> fileIo;

};



TEST_F(FileIoTest_551, SetPathUpdatesPath_551) {

    const std::string newPath = "new_path";

    fileIo->setPath(newPath);

    EXPECT_EQ(fileIo->path(), newPath);

}



TEST_F(FileIoTest_551, SetPathHandlesEmptyString_551) {

    const std::string emptyPath = "";

    fileIo->setPath(emptyPath);

    EXPECT_EQ(fileIo->path(), emptyPath);

}



TEST_F(FileIoTest_551, SetPathHandlesLongPath_551) {

    // Assuming a long path can be up to 260 characters for Windows and much longer in Unix-like systems

    std::string longPath(260, 'a');

    fileIo->setPath(longPath);

    EXPECT_EQ(fileIo->path(), longPath);

}



TEST_F(FileIoTest_551, SetPathWithUnicode_551) {

#ifdef _WIN32

    const std::string unicodePath = u8"юникодный_путь";

#else

    const std::string unicodePath = "юникодный_путь";

#endif

    fileIo->setPath(unicodePath);

    EXPECT_EQ(fileIo->path(), unicodePath);

}



TEST_F(FileIoTest_551, SetPathDoesNotAffectOpenState_551) {

    int openResult = fileIo->open();

    const std::string newPath = "new_path";

    fileIo->setPath(newPath);

    EXPECT_EQ(fileIo->isopen(), openResult == 0);

}



TEST_F(FileIoTest_551, SetPathDoesNotAffectData_551) {

    // Assuming no data is initially present

    const std::string newPath = "new_path";

    fileIo->setPath(newPath);

    EXPECT_EQ(fileIo->size(), 0u);

}



TEST_F(FileIoTest_551, SetPathCallsClose_551) {

    // Mocking the close function would be needed here if it was visible.

    // Since we cannot mock internal behavior, we rely on observable side effects.

    fileIo->open();

    fileIo->setPath("new_path");

    EXPECT_EQ(fileIo->isopen(), false);

}
