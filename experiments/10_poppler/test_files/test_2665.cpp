#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking GooString for necessary interactions

class MockGooString : public GooString {

public:

    MOCK_METHOD(void, print, (FILE *), (const));

};



// Mocking UnicodeMap for necessary interactions

class MockUnicodeMap : public UnicodeMap {

public:

    using UnicodeMap::UnicodeMap;

    MOCK_METHOD(int, mapUnicode, (Unicode u, char * buf, int bufSize), (override));

};



// Test Fixture

class PrintInfoDateTest_2665 : public ::testing::Test {

protected:

    Dict infoDict;

    MockUnicodeMap mockUMap;

    testing::StrictMock<MockGooString> mockGooString;



    PrintInfoDateTest_2665() : mockUMap("testEncoding", false, 0) {}



    void SetUp() override {

        // Set up any common state before tests (if needed)

    }



    void TearDown() override {

        // Clean up any common state after tests (if needed)

    }

};



// Test for normal operation with a valid date string

TEST_F(PrintInfoDateTest_2665, ValidDateString_2665) {

    EXPECT_CALL(mockGooString, print(stdout)).Times(1);



    Object obj(std::make_unique<MockGooString>("D:20231005143000Z"));

    infoDict.dictAdd("CreationDate", std::move(obj));



    testing::internal::CaptureStdout();

    printInfoDate(&infoDict, "CreationDate", "Creation Date: ", &mockUMap);

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_THAT(output, ::testing::HasSubstr("Thu Oct  5 14:30:00"));

}



// Test for a boundary condition with minimum date string

TEST_F(PrintInfoDateTest_2665, MinimumDateString_2665) {

    EXPECT_CALL(mockGooString, print(stdout)).Times(1);



    Object obj(std::make_unique<MockGooString>("D:00000101000000Z"));

    infoDict.dictAdd("CreationDate", std::move(obj));



    testing::internal::CaptureStdout();

    printInfoDate(&infoDict, "CreationDate", "Creation Date: ", &mockUMap);

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_THAT(output, ::testing::HasSubstr("Thu Jan  1 00:00:00"));

}



// Test for a boundary condition with maximum date string

TEST_F(PrintInfoDateTest_2665, MaximumDateString_2665) {

    EXPECT_CALL(mockGooString, print(stdout)).Times(1);



    Object obj(std::make_unique<MockGooString>("D:99991231235959Z"));

    infoDict.dictAdd("CreationDate", std::move(obj));



    testing::internal::CaptureStdout();

    printInfoDate(&infoDict, "CreationDate", "Creation Date: ", &mockUMap);

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_THAT(output, ::testing::HasSubstr("Fri Dec 31 23:59:59"));

}



// Test for invalid date string

TEST_F(PrintInfoDateTest_2665, InvalidDateString_2665) {

    EXPECT_CALL(mockGooString, print(stdout)).Times(1);



    Object obj(std::make_unique<MockGooString>("InvalidDateString"));

    infoDict.dictAdd("CreationDate", std::move(obj));



    testing::internal::CaptureStdout();

    printInfoDate(&infoDict, "CreationDate", "Creation Date: ", &mockUMap);

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "Creation Date: InvalidDateString\n");

}



// Test for non-string object type

TEST_F(PrintInfoDateTest_2665, NonStringObjectType_2665) {

    Object obj(42); // Integer instead of string

    infoDict.dictAdd("CreationDate", std::move(obj));



    testing::internal::CaptureStdout();

    printInfoDate(&infoDict, "CreationDate", "Creation Date: ", &mockUMap);

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "\n");

}



// Test for non-existing key

TEST_F(PrintInfoDateTest_2665, NonExistingKey_2665) {

    testing::internal::CaptureStdout();

    printInfoDate(&infoDict, "NonExistingKey", "Creation Date: ", &mockUMap);

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "\n");

}
