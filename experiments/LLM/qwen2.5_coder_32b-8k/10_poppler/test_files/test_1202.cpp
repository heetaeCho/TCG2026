#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/TextOutputDev.h"



class TextLineTest : public ::testing::Test {

protected:

    TextBlock* blk;

    TextWord* word1;

    TextWord* word2;



    void SetUp() override {

        blk = new TextBlock();

        word1 = new TextWord();

        word2 = new TextWord();

    }



    void TearDown() override {

        delete blk;

        delete word1;

        delete word2;

    }

};



TEST_F(TextLineTest_1202, ConstructorAndGetWords_1202) {

    TextLine line(blk, 0, 0.0);

    EXPECT_EQ(line.getWords(), nullptr);

}



TEST_F(TextLineTest_1202, AddWordAndGetWords_1202) {

    TextLine line(blk, 0, 0.0);

    line.addWord(word1);

    EXPECT_EQ(line.getWords(), word1);



    line.addWord(word2);

    // Assuming addWord appends to the end, this will still point to the first word

    EXPECT_EQ(line.getWords(), word1);

}



TEST_F(TextLineTest_1202, AddMultipleWordsAndGetWords_1202) {

    TextLine line(blk, 0, 0.0);

    line.addWord(word1);

    line.addWord(word2);

    // Assuming addWord appends to the end, this will still point to the first word

    EXPECT_EQ(line.getWords(), word1);

}



TEST_F(TextLineTest_1202, GetNextInitiallyNull_1202) {

    TextLine line(blk, 0, 0.0);

    EXPECT_EQ(line.getNext(), nullptr);

}



// Assuming there's a way to set the next line or this is tested elsewhere

// TEST_F(TextLineTest_1202, SetAndGetNext_1202) {

//     TextLine line1(blk, 0, 0.0);

//     TextLine line2(blk, 0, 0.0);

//     line1.setNext(&line2);

//     EXPECT_EQ(line1.getNext(), &line2);

// }



TEST_F(TextLineTest_1202, IsHyphenatedInitiallyFalse_1202) {

    TextLine line(blk, 0, 0.0);

    EXPECT_FALSE(line.isHyphenated());

}



// Assuming there's a way to set hyphenation or this is tested elsewhere

// TEST_F(TextLineTest_1202, SetAndGetIsHyphenated_1202) {

//     TextLine line(blk, 0, 0.0);

//     line.setHyphenated(true);

//     EXPECT_TRUE(line.isHyphenated());

// }



TEST_F(TextLineTest_1202, BoundaryConditionNoWords_1202) {

    TextLine line(blk, 0, 0.0);

    EXPECT_EQ(line.getWords(), nullptr);

}



TEST_F(TextLineTest_1202, BoundaryConditionSingleWord_1202) {

    TextLine line(blk, 0, 0.0);

    line.addWord(word1);

    EXPECT_EQ(line.getWords(), word1);

}



// Assuming there are no exceptional cases that can be triggered by the interface alone

// TEST_F(TextLineTest_1202, ExceptionalCaseInvalidInput_1202) {

//     // This test case would depend on specific implementation behavior which is not allowed.

// }
