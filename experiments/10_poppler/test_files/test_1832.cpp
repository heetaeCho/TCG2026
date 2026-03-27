#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "JBIG2Stream.cc"



using namespace testing;



class JBIG2PatternDictTest_1832 : public ::testing::Test {

protected:

    JBIG2PatternDict* pattern_dict;



    void SetUp() override {

        pattern_dict = new JBIG2PatternDict(1, 10);

    }



    void TearDown() override {

        delete pattern_dict;

    }

};



TEST_F(JBIG2PatternDictTest_1832, GetTypeReturnsCorrectType_1832) {

    EXPECT_EQ(pattern_dict->getType(), jbig2SegPatternDict);

}



TEST_F(JBIG2PatternDictTest_1832, GetSizeReturnsCorrectSize_1832) {

    EXPECT_EQ(pattern_dict->getSize(), 10u);

}



TEST_F(JBIG2PatternDictTest_1832, SetAndGetBitmapWorksProperly_1832) {

    auto bitmap = std::make_unique<JBIG2Bitmap>();

    pattern_dict->setBitmap(0, std::move(bitmap));

    EXPECT_NE(pattern_dict->getBitmap(0), nullptr);

}



TEST_F(JBIG2PatternDictTest_1832, GetNonSetBitmapReturnsNullptr_1832) {

    EXPECT_EQ(pattern_dict->getBitmap(5), nullptr);

}



TEST_F(JBIG2PatternDictTest_1832, SetBitmapOutsideBoundsThrowsOrDoesNothing_1832) {

    auto bitmap = std::make_unique<JBIG2Bitmap>();

    // Assuming setting out of bounds does not throw but simply does nothing

    pattern_dict->setBitmap(10, std::move(bitmap));

    EXPECT_EQ(pattern_dict->getBitmap(10), nullptr);

}



TEST_F(JBIG2PatternDictTest_1832, GetBitmapOutsideBoundsReturnsNullptr_1832) {

    EXPECT_EQ(pattern_dict->getBitmap(10), nullptr);

}
