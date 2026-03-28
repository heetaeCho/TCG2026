#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming TextWord and related classes are included via some header file

// #include "TextOutputDev.h"



using ::testing::Return;



class MockTextFontInfo : public TextFontInfo {

public:

    MOCK_METHOD(bool, matches, (const TextFontInfo* other) const, (override));

};



class TextWordTest_2502 : public ::testing::Test {

protected:

    std::unique_ptr<TextWord> textWordA;

    std::unique_ptr<TextWord> textWordB;

    MockTextFontInfo mockFontInfoA;

    MockTextFontInfo mockFontInfoB;



    void SetUp() override {

        // Initialize TextWords with default parameters

        textWordA = std::make_unique<TextWord>(nullptr, 0, 12.0);

        textWordB = std::make_unique<TextWord>(nullptr, 0, 12.0);



        // Set up font info for both words to point to mock objects

        EXPECT_CALL(mockFontInfoA, matches(&mockFontInfoB)).WillOnce(Return(true));

    }

};



TEST_F(TextWordTest_2502, FontInfoMatch_ReturnsTrue_2502) {

    EXPECT_TRUE(word_text_attributes_equal(textWordA.get(), 0, textWordB.get(), 0));

}



TEST_F(TextWordTest_2502, FontInfoMismatch_ReturnsFalse_2502) {

    EXPECT_CALL(mockFontInfoA, matches(&mockFontInfoB)).WillOnce(Return(false));

    EXPECT_FALSE(word_text_attributes_equal(textWordA.get(), 0, textWordB.get(), 0));

}



TEST_F(TextWordTest_2502, FontSizeMismatch_ReturnsFalse_2502) {

    textWordB->addChar(&mockFontInfoB, 0, 0, 1, 1, 0, 1, 'b', 'b', Matrix());

    EXPECT_CALL(mockFontInfoA, matches(&mockFontInfoB)).WillOnce(Return(true));

    EXPECT_FALSE(word_text_attributes_equal(textWordA.get(), 0, textWordB.get(), 0));

}



TEST_F(TextWordTest_2502, UnderlineMismatch_ReturnsFalse_2502) {

    textWordA->addChar(&mockFontInfoA, 0, 0, 1, 1, 0, 1, 'a', 'a', Matrix());

    textWordB->addChar(&mockFontInfoB, 0, 0, 1, 1, 0, 1, 'b', 'b', Matrix());



    EXPECT_CALL(mockFontInfoA, matches(&mockFontInfoB)).WillOnce(Return(true));

    textWordA->setColor(1.0, 0.0, 0.0);

    textWordB->setColor(1.0, 0.0, 0.0);



    textWordA->setUnderlined(true);

    EXPECT_FALSE(word_text_attributes_equal(textWordA.get(), 0, textWordB.get(), 0));

}



TEST_F(TextWordTest_2502, ColorMismatch_ReturnsFalse_2502) {

    textWordA->addChar(&mockFontInfoA, 0, 0, 1, 1, 0, 1, 'a', 'a', Matrix());

    textWordB->addChar(&mockFontInfoB, 0, 0, 1, 1, 0, 1, 'b', 'b', Matrix());



    EXPECT_CALL(mockFontInfoA, matches(&mockFontInfoB)).WillOnce(Return(true));

    textWordA->setColor(1.0, 0.0, 0.0);

    textWordB->setColor(0.0, 1.0, 0.0);



    EXPECT_FALSE(word_text_attributes_equal(textWordA.get(), 0, textWordB.get(), 0));

}



TEST_F(TextWordTest_2502, IdenticalAttributes_ReturnsTrue_2502) {

    textWordA->addChar(&mockFontInfoA, 0, 0, 1, 1, 0, 1, 'a', 'a', Matrix());

    textWordB->addChar(&mockFontInfoB, 0, 0, 1, 1, 0, 1, 'b', 'b', Matrix());



    EXPECT_CALL(mockFontInfoA, matches(&mockFontInfoB)).WillOnce(Return(true));

    textWordA->setColor(1.0, 0.0, 0.0);

    textWordB->setColor(1.0, 0.0, 0.0);



    EXPECT_TRUE(word_text_attributes_equal(textWordA.get(), 0, textWordB.get(), 0));

}



TEST_F(TextWordTest_2502, UnderlineMatch_ReturnsTrue_2502) {

    textWordA->addChar(&mockFontInfoA, 0, 0, 1, 1, 0, 1, 'a', 'a', Matrix());

    textWordB->addChar(&mockFontInfoB, 0, 0, 1, 1, 0, 1, 'b', 'b', Matrix());



    EXPECT_CALL(mockFontInfoA, matches(&mockFontInfoB)).WillOnce(Return(true));

    textWordA->setColor(1.0, 0.0, 0.0);

    textWordB->setColor(1.0, 0.0, 0.0);



    textWordA->setUnderlined(true);

    textWordB->setUnderlined(true);



    EXPECT_TRUE(word_text_attributes_equal(textWordA.get(), 0, textWordB.get(), 0));

}
