#include <gtest/gtest.h>

#include <string>

#include "util.cc"

#include "string_piece.h"



using namespace std;



class MountPointTest : public ::testing::Test {

protected:

    MountPoint mp;

    void SetUp() override {

        // Initialize the mount point with a sample root path.

        mp.root = StringPiece("/mnt/ninja");

        mp.mountPoint = StringPiece("/dev/sda1");

    }

};



TEST_F(MountPointTest_149, Translate_NormalPath_149) {

    string path = "/mnt/ninja/file.txt";

    string result = mp.translate(path);

    EXPECT_EQ(result, "/dev/sda1/file.txt");

}



TEST_F(MountPointTest_149, Translate_RelativePath_149) {

    string path = "file.txt";

    string result = mp.translate(path);

    EXPECT_EQ(result, "");

}



TEST_F(MountPointTest_149, Translate_OutsideRoot_149) {

    string path = "/other/path/file.txt";

    string result = mp.translate(path);

    EXPECT_EQ(result, "");

}



TEST_F(MountPointTest_149, Translate_EmptyPath_149) {

    string path = "";

    string result = mp.translate(path);

    EXPECT_EQ(result, "");

}



TEST_F(MountPointTest_149, Translate_ParentDirectorySimple_149) {

    string path = "..";

    string result = mp.translate(path);

    EXPECT_EQ(result, "");

}



TEST_F(MountPointTest_149, Translate_ParentDirectoryNested_149) {

    string path = "../file.txt";

    string result = mp.translate(path);

    EXPECT_EQ(result, "");

}



TEST_F(MountPointTest_149, Translate_ParentDirectoryComplex_149) {

    string path = "/mnt/ninja/../file.txt";

    string result = mp.translate(path);

    EXPECT_EQ(result, "");

}
