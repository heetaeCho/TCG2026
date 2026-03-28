#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "JBIG2Stream.hh"



using namespace testing;



class JBIG2PatternDictTest : public ::testing::Test {

protected:

    JBIG2PatternDict* pattern_dict;

    

    void SetUp() override {

        pattern_dict = new JBIG2PatternDict(1, 10);

    }

    

    void TearDown() override {

        delete pattern_dict;

    }

};



TEST_F(JBIG2PatternDictTest_1835, GetBitmapWithValidIndex_1835) {

    unsigned int idx = 0;

    JBIG2Bitmap* bitmap = new JBIG2Bitmap();

    pattern_dict->setBitmap(idx, std::unique_ptr<JBIG2Bitmap>(bitmap));

    

    EXPECT_EQ(pattern_dict->getBitmap(idx), bitmap);

}



TEST_F(JBIG2PatternDictTest_1835, GetBitmapWithInvalidIndex_1835) {

    unsigned int idx = 10; // Out of bounds index

    

    EXPECT_EQ(pattern_dict->getBitmap(idx), nullptr);

}



TEST_F(JBIG2PatternDictTest_1835, GetBitmapBoundaryCondition_1835) {

    unsigned int idx = 9; // Last valid index

    JBIG2Bitmap* bitmap = new JBIG2Bitmap();

    pattern_dict->setBitmap(idx, std::unique_ptr<JBIG2Bitmap>(bitmap));

    

    EXPECT_EQ(pattern_dict->getBitmap(idx), bitmap);

}



TEST_F(JBIG2PatternDictTest_1835, GetBitmapBoundaryConditionInvalid_1835) {

    unsigned int idx = 10; // Just out of bounds

    

    EXPECT_EQ(pattern_dict->getBitmap(idx), nullptr);

}
