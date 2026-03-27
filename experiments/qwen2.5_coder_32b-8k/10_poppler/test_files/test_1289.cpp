#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-private.h"



using namespace Poppler;

using ::testing::_;

using ::testing::InvokeWithoutArgs;



class DocumentDataTest : public ::testing::Test {

protected:

    DocumentData* docData;

    std::function<void(void)> mockCallback;



    void SetUp() override {

        docData = new DocumentData("dummy_path", std::nullopt, std::nullopt);

        mockCallback = nullptr;

        docData->xrefReconstructedCallback = mockCallback;

    }



    void TearDown() override {

        delete docData;

    }

};



TEST_F(DocumentDataTest_1289, InitialState_NoCallbackCalled_1289) {

    EXPECT_FALSE(docData->xrefReconstructed);

    ASSERT_EQ(mockCallback, nullptr);

}



TEST_F(DocumentDataTest_1289, NotifyXRefReconstructed_CallbackCalledOnce_1289) {

    bool callbackWasCalled = false;

    docData->xrefReconstructedCallback = [&callbackWasCalled] { callbackWasCalled = true; };



    docData->notifyXRefReconstructed();

    EXPECT_TRUE(callbackWasCalled);

    EXPECT_TRUE(docData->xrefReconstructed);

}



TEST_F(DocumentDataTest_1289, NotifyXRefReconstructed_Idempotent_1289) {

    bool callbackCallCount = 0;

    docData->xrefReconstructedCallback = [&callbackCallCount] { ++callbackCallCount; };



    docData->notifyXRefReconstructed();

    EXPECT_EQ(callbackCallCount, 1);



    docData->notifyXRefReconstructed(); // Should not call again

    EXPECT_EQ(callbackCallCount, 1);

}



TEST_F(DocumentDataTest_1289, NotifyXRefReconstructed_NoCallbackSet_NoError_1289) {

    docData->xrefReconstructedCallback = nullptr;



    EXPECT_NO_THROW(docData->notifyXRefReconstructed());

    EXPECT_TRUE(docData->xrefReconstructed);

}
