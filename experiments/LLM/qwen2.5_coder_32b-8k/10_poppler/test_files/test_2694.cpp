#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "pdftocairo.cc"

#include "CairoOutputDev.h"



using ::testing::_;

using ::testing::NiceMock;



class MockCairoOutputDev : public CairoOutputDev {

public:

    MOCK_METHOD(void, setCairo, (int* cr), (override));

    MOCK_METHOD(void, setPrinting, (bool printingA), (override));

    MOCK_METHOD(void, emitStructTree, (), (override));

    MOCK_METHOD(void, endPage, (), (override));

};



class EndPageTest_2694 : public ::testing::Test {

protected:

    NiceMock<MockCairoOutputDev> cairoOut;

    GooString imageFileName{"test_image.png"};

    bool isLastPage{false};

};



TEST_F(EndPageTest_2694, NormalOperation_NotLastPage_PrintingTrue_2694) {

    ::printing = true;

    isLastPage = false;



    EXPECT_CALL(cairoOut, setCairo(_)).Times(0);

    EXPECT_CALL(cairoOut, setPrinting(_)).Times(1);

    EXPECT_CALL(cairoOut, emitStructTree()).Times(0);

    EXPECT_CALL(cairoOut, endPage()).Times(1);



    endPage(&imageFileName, &cairoOut, isLastPage);

}



TEST_F(EndPageTest_2694, NormalOperation_IsLastPage_PrintingTrue_2694) {

    ::printing = true;

    isLastPage = true;



    EXPECT_CALL(cairoOut, setCairo(_)).Times(1);

    EXPECT_CALL(cairoOut, setPrinting(true)).Times(1);

    EXPECT_CALL(cairoOut, emitStructTree()).Times(1);

    EXPECT_CALL(cairoOut, endPage()).Times(1);



    endPage(&imageFileName, &cairoOut, isLastPage);

}



TEST_F(EndPageTest_2694, NormalOperation_NotLastPage_PrintingFalse_2694) {

    ::printing = false;

    isLastPage = false;



    EXPECT_CALL(cairoOut, setCairo(_)).Times(0);

    EXPECT_CALL(cairoOut, setPrinting(_)).Times(0);

    EXPECT_CALL(cairoOut, emitStructTree()).Times(0);

    EXPECT_CALL(cairoOut, endPage()).Times(1);



    endPage(&imageFileName, &cairoOut, isLastPage);

}



TEST_F(EndPageTest_2694, NormalOperation_IsLastPage_PrintingFalse_2694) {

    ::printing = false;

    isLastPage = true;



    EXPECT_CALL(cairoOut, setCairo(_)).Times(0);

    EXPECT_CALL(cairoOut, setPrinting(_)).Times(0);

    EXPECT_CALL(cairoOut, emitStructTree()).Times(0);

    EXPECT_CALL(cairoOut, endPage()).Times(1);



    endPage(&imageFileName, &cairoOut, isLastPage);

}



TEST_F(EndPageTest_2694, BoundaryCondition_ImageFileNameNull_PrintingTrue_2694) {

    ::printing = true;

    GooString* nullImageFileName = nullptr;



    EXPECT_CALL(cairoOut, setCairo(_)).Times(isLastPage ? 1 : 0);

    EXPECT_CALL(cairoOut, setPrinting(true)).Times(1);

    EXPECT_CALL(cairoOut, emitStructTree()).Times(isLastPage ? 1 : 0);

    EXPECT_CALL(cairoOut, endPage()).Times(1);



    endPage(nullImageFileName, &cairoOut, isLastPage);

}



TEST_F(EndPageTest_2694, BoundaryCondition_ImageFileNameNull_PrintingFalse_2694) {

    ::printing = false;

    GooString* nullImageFileName = nullptr;



    EXPECT_CALL(cairoOut, setCairo(_)).Times(0);

    EXPECT_CALL(cairoOut, setPrinting(_)).Times(0);

    EXPECT_CALL(cairoOut, emitStructTree()).Times(0);

    EXPECT_CALL(cairoOut, endPage()).Times(1);



    endPage(nullImageFileName, &cairoOut, isLastPage);

}



// Note: The following test cases assume that the cairo functions are expected to handle nullptr gracefully,

// as there is no direct way to simulate a cairo error condition without internal access or additional mocking.
