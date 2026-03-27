#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/MarkedContentOutputDev.h"

#include <gmock/gmock.h>



using namespace testing;



class MarkedContentOutputDevTest_1679 : public Test {

protected:

    std::unique_ptr<MarkedContentOutputDev> markedContentOutputDev;



    void SetUp() override {

        Object dummyObject;

        markedContentOutputDev = std::make_unique<MarkedContentOutputDev>(0, dummyObject);

    }

};



TEST_F(MarkedContentOutputDevTest_1679, needCharCount_ReturnsFalse_1679) {

    EXPECT_FALSE(markedContentOutputDev->needCharCount());

}



TEST_F(MarkedContentOutputDevTest_1679, startPage_NormalOperation_1679) {

    GfxState dummyState;

    XRef dummyXRef;

    markedContentOutputDev->startPage(1, &dummyState, &dummyXRef);

    // Assuming no observable side effects other than the method call

}



TEST_F(MarkedContentOutputDevTest_1679, endPage_NormalOperation_1679) {

    markedContentOutputDev->endPage();

    // Assuming no observable side effects other than the method call

}



TEST_F(MarkedContentOutputDevTest_1679, beginForm_NormalOperation_1679) {

    Object dummyObject;

    Ref dummyRef;

    markedContentOutputDev->beginForm(&dummyObject, dummyRef);

    // Assuming no observable side effects other than the method call

}



TEST_F(MarkedContentOutputDevTest_1679, endForm_NormalOperation_1679) {

    Object dummyObject;

    Ref dummyRef;

    markedContentOutputDev->endForm(&dummyObject, dummyRef);

    // Assuming no observable side effects other than the method call

}



TEST_F(MarkedContentOutputDevTest_1679, drawChar_NormalOperation_1679) {

    GfxState dummyState;

    Unicode unicodeArray[] = {0x41};

    markedContentOutputDev->drawChar(&dummyState, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 65, 1, unicodeArray, 1);

    // Assuming no observable side effects other than the method call

}



TEST_F(MarkedContentOutputDevTest_1679, beginMarkedContent_NormalOperation_1679) {

    Dict dummyDict;

    markedContentOutputDev->beginMarkedContent("dummyName", &dummyDict);

    // Assuming no observable side effects other than the method call

}



TEST_F(MarkedContentOutputDevTest_1679, endMarkedContent_NormalOperation_1679) {

    GfxState dummyState;

    markedContentOutputDev->endMarkedContent(&dummyState);

    // Assuming no observable side effects other than the method call

}



TEST_F(MarkedContentOutputDevTest_1679, getTextSpans_ReturnsZeroInitially_1679) {

    EXPECT_EQ(markedContentOutputDev->getTextSpans(), 0);

}



TEST_F(MarkedContentOutputDevTest_1679, isOk_NormalOperation_1679) {

    EXPECT_TRUE(markedContentOutputDev->isOk());

}



TEST_F(MarkedContentOutputDevTest_1679, upsideDown_ReturnsFalseInitially_1679) {

    EXPECT_FALSE(markedContentOutputDev->upsideDown());

}



TEST_F(MarkedContentOutputDevTest_1679, useDrawChar_ReturnsTrueInitially_1679) {

    EXPECT_TRUE(markedContentOutputDev->useDrawChar());

}



TEST_F(MarkedContentOutputDevTest_1679, interpretType3Chars_ReturnsFalseInitially_1679) {

    EXPECT_FALSE(markedContentOutputDev->interpretType3Chars());

}



TEST_F(MarkedContentOutputDevTest_1679, needNonText_ReturnsTrueInitially_1679) {

    EXPECT_TRUE(markedContentOutputDev->needNonText());

}
