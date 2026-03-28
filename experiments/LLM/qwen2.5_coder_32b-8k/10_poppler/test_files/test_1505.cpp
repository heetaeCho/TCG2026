#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <cstdio>



// Mock FILE structure for testing

class MockFile {

public:

    MOCK_METHOD(int, getCharFromFileMock, (), ());

};



extern "C" {

int getCharFromFile(void *data) {

    return static_cast<MockFile*>(data)->getCharFromFileMock();

}

}



class CMapTest_1505 : public ::testing::Test {

protected:

    MockFile mockFile;

    FILE* file;



    void SetUp() override {

        // Simulate a valid FILE pointer

        file = reinterpret_cast<FILE*>(&mockFile);

    }

};



TEST_F(CMapTest_1505, GetCharFromFile_ReturnsCharacter_1505) {

    EXPECT_CALL(mockFile, getCharFromFileMock()).WillOnce(::testing::Return('A'));

    int result = getCharFromFile(file);

    ASSERT_EQ(result, 'A');

}



TEST_F(CMapTest_1505, GetCharFromFile_EndOfFile_ReturnsEOF_1505) {

    EXPECT_CALL(mockFile, getCharFromFileMock()).WillOnce(::testing::Return(EOF));

    int result = getCharFromFile(file);

    ASSERT_EQ(result, EOF);

}



TEST_F(CMapTest_1505, GetCharFromFile_MultipleCalls_ReturnExpectedCharacters_1505) {

    EXPECT_CALL(mockFile, getCharFromFileMock())

        .WillOnce(::testing::Return('H'))

        .WillOnce(::testing::Return('e'))

        .WillOnce(::testing::Return('l'))

        .WillOnce(::testing::Return('l'))

        .WillOnce(::testing::Return('o'));



    ASSERT_EQ(getCharFromFile(file), 'H');

    ASSERT_EQ(getCharFromFile(file), 'e');

    ASSERT_EQ(getCharFromFile(file), 'l');

    ASSERT_EQ(getCharFromFile(file), 'l');

    ASSERT_EQ(getCharFromFile(file), 'o');

}
