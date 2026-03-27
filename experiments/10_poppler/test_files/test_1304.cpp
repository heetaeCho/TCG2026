#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "PSOutputDev.h"

#include <functional>



using namespace testing;



// Mock callback function for underlayCbk

class MockUnderlayCallback {

public:

    MOCK_METHOD2(Call, void(PSOutputDev*, void*));

};



void mockUnderlayCallbackWrapper(PSOutputDev* psOut, void* data) {

    static_cast<MockUnderlayCallback*>(data)->Call(psOut, nullptr);

}



TEST_F(PSOutputDevTest_1304, SetUnderlayCbk_NormalOperation_1304) {

    PSOutputDev psOut(nullptr, nullptr, nullptr, 0, psModeNormal, 0, 0, false, false, 0, 0, 0, 0, psForceRasterizeNone, false, nullptr, nullptr, psLevel2);

    MockUnderlayCallback mockCbk;



    EXPECT_CALL(mockCbk, Call(&psOut, nullptr)).Times(1);



    psOut.setUnderlayCbk(mockUnderlayCallbackWrapper, &mockCbk);

}



TEST_F(PSOutputDevTest_1304, SetUnderlayCbk_WithNullData_1304) {

    PSOutputDev psOut(nullptr, nullptr, nullptr, 0, psModeNormal, 0, 0, false, false, 0, 0, 0, 0, psForceRasterizeNone, false, nullptr, nullptr, psLevel2);

    MockUnderlayCallback mockCbk;



    EXPECT_CALL(mockCbk, Call(&psOut, nullptr)).Times(1);



    psOut.setUnderlayCbk(mockUnderlayCallbackWrapper, &mockCbk);

}



TEST_F(PSOutputDevTest_1304, SetUnderlayCbk_WithNonNullData_1304) {

    PSOutputDev psOut(nullptr, nullptr, nullptr, 0, psModeNormal, 0, 0, false, false, 0, 0, 0, 0, psForceRasterizeNone, false, nullptr, nullptr, psLevel2);

    MockUnderlayCallback mockCbk;

    int data = 42;



    EXPECT_CALL(mockCbk, Call(&psOut, &data)).Times(1);



    psOut.setUnderlayCbk(mockUnderlayCallbackWrapper, &mockCbk);

}



TEST_F(PSOutputDevTest_1304, SetUnderlayCbk_MultipleCalls_1304) {

    PSOutputDev psOut(nullptr, nullptr, nullptr, 0, psModeNormal, 0, 0, false, false, 0, 0, 0, 0, psForceRasterizeNone, false, nullptr, nullptr, psLevel2);

    MockUnderlayCallback mockCbk1;

    MockUnderlayCallback mockCbk2;



    EXPECT_CALL(mockCbk1, Call(&psOut, nullptr)).Times(1);

    EXPECT_CALL(mockCbk2, Call(&psOut, nullptr)).Times(1);



    psOut.setUnderlayCbk(mockUnderlayCallbackWrapper, &mockCbk1);

    psOut.setUnderlayCbk(mockUnderlayCallbackWrapper, &mockCbk2);

}



TEST_F(PSOutputDevTest_1304, SetUnderlayCbk_NoCallback_1304) {

    PSOutputDev psOut(nullptr, nullptr, nullptr, 0, psModeNormal, 0, 0, false, false, 0, 0, 0, 0, psForceRasterizeNone, false, nullptr, nullptr, psLevel2);



    // Setting callback to null

    psOut.setUnderlayCbk(nullptr, nullptr);

}



TEST_F(PSOutputDevTest_1304, SetOverlayCbk_NormalOperation_1304) {

    PSOutputDev psOut(nullptr, nullptr, nullptr, 0, psModeNormal, 0, 0, false, false, 0, 0, 0, 0, psForceRasterizeNone, false, nullptr, nullptr, psLevel2);

    MockUnderlayCallback mockCbk;



    EXPECT_CALL(mockCbk, Call(&psOut, nullptr)).Times(1);



    psOut.setOverlayCbk(mockUnderlayCallbackWrapper, &mockCbk);

}
