#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <string>

#include <vector>

#include <set>



namespace {

    bool pushPath(const std::string& path, std::vector<std::string>& libs, std::set<std::string>& paths);

}



// Mock for fileExists function

class FileExistsMock {

public:

    MOCK_CONST_METHOD1(fileExists, bool(const std::string&));

};



FileExistsMock* mockFileExists = nullptr;



bool Exiv2::fileExists(const std::string& path) {

    return mockFileExists->fileExists(path);

}



class PushPathTest_993 : public ::testing::Test {

protected:

    void SetUp() override {

        mockFileExists = new FileExistsMock();

    }



    void TearDown() override {

        delete mockFileExists;

    }

};



TEST_F(PushPathTest_993, NormalOperation_FileExistsAndNotInPaths_993) {

    std::string path = "/some/path";

    std::vector<std::string> libs;

    std::set<std::string> paths;



    EXPECT_CALL(*mockFileExists, fileExists(path)).WillOnce(::testing::Return(true));



    bool result = pushPath(path, libs, paths);



    EXPECT_TRUE(result);

    EXPECT_EQ(libs.size(), 1);

    EXPECT_EQ(paths.size(), 1);

    EXPECT_EQ(libs[0], path);

    EXPECT_NE(paths.find(path), paths.end());

}



TEST_F(PushPathTest_993, FileDoesNotExist_993) {

    std::string path = "/some/path";

    std::vector<std::string> libs;

    std::set<std::string> paths;



    EXPECT_CALL(*mockFileExists, fileExists(path)).WillOnce(::testing::Return(false));



    bool result = pushPath(path, libs, paths);



    EXPECT_FALSE(result);

    EXPECT_EQ(libs.size(), 0);

    EXPECT_EQ(paths.size(), 0);

}



TEST_F(PushPathTest_993, PathAlreadyInPaths_993) {

    std::string path = "/some/path";

    std::vector<std::string> libs;

    std::set<std::string> paths;



    paths.insert(path);



    EXPECT_CALL(*mockFileExists, fileExists(path)).WillOnce(::testing::Return(true));



    bool result = pushPath(path, libs, paths);



    EXPECT_FALSE(result);

    EXPECT_EQ(libs.size(), 0);

    EXPECT_EQ(paths.size(), 1);

}



TEST_F(PushPathTest_993, PathIsRoot_993) {

    std::string path = "/";

    std::vector<std::string> libs;

    std::set<std::string> paths;



    EXPECT_CALL(*mockFileExists, fileExists(path)).WillOnce(::testing::Return(true));



    bool result = pushPath(path, libs, paths);



    EXPECT_FALSE(result);

    EXPECT_EQ(libs.size(), 0);

    EXPECT_EQ(paths.size(), 0);

}



TEST_F(PushPathTest_993, BoundaryCondition_EmptyPath_993) {

    std::string path = "";

    std::vector<std::string> libs;

    std::set<std::string> paths;



    EXPECT_CALL(*mockFileExists, fileExists(path)).WillOnce(::testing::Return(true));



    bool result = pushPath(path, libs, paths);



    EXPECT_FALSE(result);

    EXPECT_EQ(libs.size(), 0);

    EXPECT_EQ(paths.size(), 0);

}
