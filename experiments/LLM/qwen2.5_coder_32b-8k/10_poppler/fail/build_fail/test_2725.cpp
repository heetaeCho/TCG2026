#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include <memory>

#include "TextOutputDev.h"



using namespace testing;



// Mock TextWord class to control its behavior in tests.

class MockTextWord : public TextWord {

public:

    MOCK_METHOD(const std::unique_ptr<std::string>, getText, (), (const, override));

    MOCK_METHOD(void, getBBox, (double*, double*, double*, double*), (const, override));

    MOCK_METHOD(const TextWord*, getNext, (), (const, override));



    MockTextWord(int rotA) : TextWord(nullptr, rotA, 0.0) {}

};



// Mock TextLine class to control its behavior in tests.

class MockTextLine : public TextLine {

public:

    MOCK_METHOD(const TextWord*, getWords, (), (const, override));

    MOCK_METHOD(const TextLine*, getNext, (), (const, override));



    MockTextLine(int rotA) : TextLine(nullptr, rotA, 0.0) {}

};



TEST_F(TestSuite_2725, PrintLine_EmptyLine_2725) {

    FILE *output = fopen("test_output.xml", "w");

    MockTextLine line(0);

    EXPECT_CALL(line, getWords()).WillOnce(Return(nullptr));



    printLine(output, &line);



    std::ifstream ifs("test_output.xml");

    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

    EXPECT_EQ(content, " <line xMin=\"0.000000\" yMin=\"0.000000\" xMax=\"0.000000\" yMax=\"0.000000\">\n </line>\n");

    fclose(output);

}



TEST_F(TestSuite_2725, PrintLine_SingleWord_2725) {

    FILE *output = fopen("test_output.xml", "w");

    MockTextLine line(0);

    MockTextWord word(0);



    EXPECT_CALL(line, getWords()).WillOnce(Return(&word));

    EXPECT_CALL(word, getText()).WillOnce(Return(std::make_unique<std::string>("Test")));

    EXPECT_CALL(word, getBBox(_, _, _, _)).WillOnce(DoAll(SetArgReferee<0>(1.0), SetArgReferee<1>(2.0), SetArgReferee<2>(3.0), SetArgReferee<3>(4.0)));

    EXPECT_CALL(word, getNext()).WillOnce(Return(nullptr));



    printLine(output, &line);



    std::ifstream ifs("test_output.xml");

    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

    EXPECT_EQ(content, " <line xMin=\"1.000000\" yMin=\"2.000000\" xMax=\"3.000000\" yMax=\"4.000000\">\n <word xMin=\"1.000000\" yMin=\"2.000000\" xMax=\"3.000000\" yMax=\"4.000000\">Test</word>\n </line>\n");

    fclose(output);

}



TEST_F(TestSuite_2725, PrintLine_MultipleWords_2725) {

    FILE *output = fopen("test_output.xml", "w");

    MockTextLine line(0);

    MockTextWord word1(0), word2(0);



    EXPECT_CALL(line, getWords()).WillOnce(Return(&word1));

    EXPECT_CALL(word1, getText()).WillOnce(Return(std::make_unique<std::string>("Hello")));

    EXPECT_CALL(word1, getBBox(_, _, _, _)).WillOnce(DoAll(SetArgReferee<0>(1.0), SetArgReferee<1>(2.0), SetArgReferee<2>(3.0), SetArgReferee<3>(4.0)));

    EXPECT_CALL(word1, getNext()).WillOnce(Return(&word2));



    EXPECT_CALL(word2, getText()).WillOnce(Return(std::make_unique<std::string>("World")));

    EXPECT_CALL(word2, getBBox(_, _, _, _)).WillOnce(DoAll(SetArgReferee<0>(4.0), SetArgReferee<1>(3.0), SetArgReferee<2>(5.0), SetArgReferee<3>(6.0)));

    EXPECT_CALL(word2, getNext()).WillOnce(Return(nullptr));



    printLine(output, &line);



    std::ifstream ifs("test_output.xml");

    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

    EXPECT_EQ(content, " <line xMin=\"1.000000\" yMin=\"2.000000\" xMax=\"5.000000\" yMax=\"6.000000\">\n <word xMin=\"1.000000\" yMin=\"2.000000\" xMax=\"3.000000\" yMax=\"4.000000\">Hello</word>\n <word xMin=\"4.000000\" yMin=\"3.000000\" xMax=\"5.000000\" yMax=\"6.000000\">World</word>\n </line>\n");

    fclose(output);

}



TEST_F(TestSuite_2725, PrintLine_WordWithSpecialChars_2725) {

    FILE *output = fopen("test_output.xml", "w");

    MockTextLine line(0);

    MockTextWord word(0);



    EXPECT_CALL(line, getWords()).WillOnce(Return(&word));

    EXPECT_CALL(word, getText()).WillOnce(Return(std::make_unique<std::string>("Hello&World")));

    EXPECT_CALL(word, getBBox(_, _, _, _)).WillOnce(DoAll(SetArgReferee<0>(1.0), SetArgReferee<1>(2.0), SetArgReferee<2>(3.0), SetArgReferee<3>(4.0)));

    EXPECT_CALL(word, getNext()).WillOnce(Return(nullptr));



    printLine(output, &line);



    std::ifstream ifs("test_output.xml");

    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

    EXPECT_EQ(content, " <line xMin=\"1.000000\" yMin=\"2.000000\" xMax=\"3.000000\" yMax=\"4.000000\">\n <word xMin=\"1.000000\" yMin=\"2.000000\" xMax=\"3.000000\" yMax=\"4.000000\">Hello&amp;World</word>\n </line>\n");

    fclose(output);

}
