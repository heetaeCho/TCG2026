#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "util.h"  // Assuming the header file where SpellcheckString is declared



// Mocking the external function SpellcheckStringV for testing purposes

extern "C" {

    const char* SpellcheckStringV(const char* text, const std::vector<const char*>& words);

}



class MockSpellchecker {

public:

    MOCK_CONST_METHOD2(SpellcheckStringVMock, const char*(const char*, const std::vector<const char*>&));

};



// Using a global mock object for simplicity

MockSpellchecker g_mock_spellchecker;



extern "C" {

    const char* SpellcheckStringV(const char* text, const std::vector<const char*>& words) {

        return g_mock_spellchecker.SpellcheckStringVMock(text, words);

    }

}



class SpellcheckTest_144 : public ::testing::Test {

protected:

    void SetUp() override {

        // Reset expectations between tests

        ::testing::Mock::VerifyAndClear(&g_mock_spellchecker);

    }



    void TearDown() override {

        // Ensure no unexpected calls were made

        EXPECT_TRUE(::testing::Mock::VerifyAndClearExpectations(&g_mock_spellchecker));

    }

};



TEST_F(SpellcheckTest_144, SingleWordCorrect_144) {

    EXPECT_CALL(g_mock_spellchecker, SpellcheckStringVMock("hello", std::vector<const char*>{"hello"}))

        .WillOnce(::testing::Return("hello"));

    

    const char* result = SpellcheckString("hello", "hello", nullptr);

    EXPECT_STREQ(result, "hello");

}



TEST_F(SpellcheckTest_144, MultipleWordsCorrect_144) {

    EXPECT_CALL(g_mock_spellchecker, SpellcheckStringVMock("hello world", std::vector<const char*>{"hello", "world"}))

        .WillOnce(::testing::Return("hello world"));

    

    const char* result = SpellcheckString("hello world", "hello", "world", nullptr);

    EXPECT_STREQ(result, "hello world");

}



TEST_F(SpellcheckTest_144, SingleWordIncorrect_144) {

    EXPECT_CALL(g_mock_spellchecker, SpellcheckStringVMock("helo", std::vector<const char*>{"helo"}))

        .WillOnce(::testing::Return("hello"));

    

    const char* result = SpellcheckString("helo", "helo", nullptr);

    EXPECT_STREQ(result, "hello");

}



TEST_F(SpellcheckTest_144, MultipleWordsIncorrect_144) {

    EXPECT_CALL(g_mock_spellchecker, SpellcheckStringVMock("helo wrld", std::vector<const char*>{"helo", "wrld"}))

        .WillOnce(::testing::Return("hello world"));

    

    const char* result = SpellcheckString("helo wrld", "helo", "wrld", nullptr);

    EXPECT_STREQ(result, "hello world");

}



TEST_F(SpellcheckTest_144, NoWordsProvided_144) {

    EXPECT_CALL(g_mock_spellchecker, SpellcheckStringVMock("", std::vector<const char*>{}))

        .WillOnce(::testing::Return(""));

    

    const char* result = SpellcheckString("", nullptr);

    EXPECT_STREQ(result, "");

}



TEST_F(SpellcheckTest_144, EmptyStringAsWord_144) {

    EXPECT_CALL(g_mock_spellchecker, SpellcheckStringVMock(" ", std::vector<const char*>{"", ""}))

        .WillOnce(::testing::Return(" "));

    

    const char* result = SpellcheckString(" ", "", "", nullptr);

    EXPECT_STREQ(result, " ");

}
