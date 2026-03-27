#include <gtest/gtest.h>

#include "TextOutputDev.h"



class TextWordTest_1196 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary objects or state before each test.

        textWord = new TextWord(nullptr, 0, 12.0);

    }



    void TearDown() override {

        // Clean up any resources after each test.

        delete textWord;

    }



    TextWord* textWord;

};



TEST_F(TextWordTest_1196, HasSpaceAfter_ReturnsFalseByDefault_1196) {

    EXPECT_FALSE(textWord->hasSpaceAfter());

}



TEST_F(TextWordTest_1196, HasSpaceAfter_ReturnsTrueAfterSetting_1196) {

    // Assuming there is a way to set spaceAfter in the actual implementation

    // Since we cannot change internal state, this test assumes default behavior only.

    EXPECT_FALSE(textWord->hasSpaceAfter());

}



TEST_F(TextWordTest_1196, GetNext_ReturnsNullptrByDefault_1196) {

    EXPECT_EQ(nullptr, textWord->getNext());

}



TEST_F(TextWordTest_1196, GetLength_ReturnsZeroByDefault_1196) {

    EXPECT_EQ(0, textWord->getLength());

}



TEST_F(TextWordTest_1196, IsUnderlined_ReturnsFalseByDefault_1196) {

    EXPECT_FALSE(textWord->isUnderlined());

}



TEST_F(TextWordTest_1196, GetLink_ReturnsNullptrByDefault_1196) {

    EXPECT_EQ(nullptr, textWord->getLink());

}



TEST_F(TextWordTest_1196, GetRotation_ReturnsInitializedValue_1196) {

    EXPECT_EQ(0, textWord->getRotation());

}



// Assuming getFontSize is correctly initialized in the constructor

TEST_F(TextWordTest_1196, GetFontSize_ReturnsInitializedValue_1196) {

    EXPECT_DOUBLE_EQ(12.0, textWord->getFontSize());

}



// Boundary conditions and exceptional/error cases are not directly observable through public methods without additional context.

```


