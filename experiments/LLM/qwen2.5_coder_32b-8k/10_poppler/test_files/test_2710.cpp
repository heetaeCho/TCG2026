#include <gtest/gtest.h>

#include "TestProjects/poppler/utils/HtmlOutputDev.h"

#include <gmock/gmock.h>



using namespace testing;



// Mock classes and functions if necessary

class MockPage : public Page {

public:

    MOCK_METHOD0(getNum, int());

};



TEST_F(HtmlOutputDevTest_2710, CheckPageSlice_ReturnsTrue_2710) {

    MockPage mockPage;

    HtmlOutputDev htmlOutputDev;



    EXPECT_CALL(mockPage, getNum()).Times(0); // Ensure no internal calls to Page methods



    bool result = htmlOutputDev.checkPageSlice(&mockPage, 300.0, 300.0, 0, true, false, 0, 0, 100, 100, false);

    EXPECT_TRUE(result);

}



TEST_F(HtmlOutputDevTest_2710, CheckPageSlice_CallWithAbortCheckCbk_ReturnsTrue_2710) {

    MockPage mockPage;

    HtmlOutputDev htmlOutputDev;



    bool (*abortCheckCbk)(void*) = [](void*) { return false; };

    void* abortCheckCbkData = nullptr;



    EXPECT_CALL(mockPage, getNum()).Times(0); // Ensure no internal calls to Page methods



    bool result = htmlOutputDev.checkPageSlice(&mockPage, 300.0, 300.0, 0, true, false, 0, 0, 100, 100, false, abortCheckCbk, abortCheckCbkData);

    EXPECT_TRUE(result);

}



TEST_F(HtmlOutputDevTest_2710, CheckPageSlice_CallWithAnnotDisplayDecideCbk_ReturnsTrue_2710) {

    MockPage mockPage;

    HtmlOutputDev htmlOutputDev;



    bool (*annotDisplayDecideCbk)(Annot*, void*) = [](Annot*, void*) { return true; };

    void* annotDisplayDecideCbkData = nullptr;



    EXPECT_CALL(mockPage, getNum()).Times(0); // Ensure no internal calls to Page methods



    bool result = htmlOutputDev.checkPageSlice(&mockPage, 300.0, 300.0, 0, true, false, 0, 0, 100, 100, false, nullptr, nullptr, annotDisplayDecideCbk, annotDisplayDecideCbkData);

    EXPECT_TRUE(result);

}



TEST_F(HtmlOutputDevTest_2710, CheckPageSlice_CallWithAllCallbacks_ReturnsTrue_2710) {

    MockPage mockPage;

    HtmlOutputDev htmlOutputDev;



    bool (*abortCheckCbk)(void*) = [](void*) { return false; };

    void* abortCheckCbkData = nullptr;



    bool (*annotDisplayDecideCbk)(Annot*, void*) = [](Annot*, void*) { return true; };

    void* annotDisplayDecideCbkData = nullptr;



    EXPECT_CALL(mockPage, getNum()).Times(0); // Ensure no internal calls to Page methods



    bool result = htmlOutputDev.checkPageSlice(&mockPage, 300.0, 300.0, 0, true, false, 0, 0, 100, 100, false, abortCheckCbk, abortCheckCbkData, annotDisplayDecideCbk, annotDisplayDecideCbkData);

    EXPECT_TRUE(result);

}
