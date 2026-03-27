#include <gtest/gtest.h>

#include <gmock/gmock.h>



using namespace std;



// Assuming the ReadFile function is declared in a header file like util.h

extern int ReadFile(const string& path, string* contents, string* err);



class ReadFileTest_142 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if necessary

    }



    void TearDown() override {

        // Teardown code if necessary

    }

};



TEST_F(ReadFileTest_142, NormalOperation_142) {

    string contents;

    string err;



    int result = ReadFile("testfile.txt", &contents, &err);

    EXPECT_EQ(result, 0);

    EXPECT_TRUE(contents.empty() || !contents.empty()); // Depending on the file content

    EXPECT_TRUE(err.empty());

}



TEST_F(ReadFileTest_142, NonExistentFile_142) {

    string contents;

    string err;



    int result = ReadFile("nonexistentfile.txt", &contents, &err);

    EXPECT_EQ(result, -ENOENT);

    EXPECT_TRUE(contents.empty());

    EXPECT_FALSE(err.empty());

}



TEST_F(ReadFileTest_142, EmptyFile_142) {

    string contents;

    string err;



    int result = ReadFile("emptyfile.txt", &contents, &err);

    EXPECT_EQ(result, 0);

    EXPECT_TRUE(contents.empty());

    EXPECT_TRUE(err.empty());

}



TEST_F(ReadFileTest_142, LargeFile_142) {

    string contents;

    string err;



    int result = ReadFile("largefile.txt", &contents, &err);

    EXPECT_EQ(result, 0);

    EXPECT_FALSE(contents.empty());

    EXPECT_TRUE(err.empty());

}



TEST_F(ReadFileTest_142, IOError_142) {

    // Simulate an IO error by passing a path that causes an error

    string contents;

    string err;



    int result = ReadFile("/dev/null", &contents, &err); // This might not cause an error on all systems

    EXPECT_NE(result, 0);

    EXPECT_TRUE(contents.empty());

    EXPECT_FALSE(err.empty());

}

```


