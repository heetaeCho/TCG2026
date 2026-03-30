#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page.h"



using namespace Poppler;

using ::testing::_;

using ::testing::Return;



class MockCallbackHandler {

public:

    MOCK_METHOD2(partialUpdateCallback, void(QImage, void*));

};



class Qt5SplashOutputDevTest_1436 : public ::testing::Test {

protected:

    MockCallbackHandler mockHandler;

    void* payload = reinterpret_cast<void*>(0x1234);

    QImage image;



    Qt5SplashOutputDevTest_1436() 

        : splashOutputDev(SplashColorModeRGB8, 0, false, nullptr, false, splashThinLineDefault, false) {

        splashOutputDev.partialUpdateCallback = &MockCallbackHandler::partialUpdateCallback;

        splashOutputDev.payload = payload;

    }



    Qt5SplashOutputDevTest_1436(const Qt5SplashOutputDevTest_1436&) = delete;

    Qt5SplashOutputDevTest_1436& operator=(const Qt5SplashOutputDevTest_1436&) = delete;



    ~Qt5SplashOutputDevTest_1436() override {}



    Qt5SplashOutputDev splashOutputDev;

};



TEST_F(Qt5SplashOutputDevTest_1436, DumpCallsCallbackIfConditionMet_1436) {

    EXPECT_CALL(mockHandler, partialUpdateCallback(_, payload));

    splashOutputDev.shouldDoPartialUpdateCallback = [](void*) { return true; };

    splashOutputDev.dump();

}



TEST_F(Qt5SplashOutputDevTest_1436, DumpDoesNotCallCallbackIfConditionNotMet_1436) {

    EXPECT_CALL(mockHandler, partialUpdateCallback(_, _)).Times(0);

    splashOutputDev.shouldDoPartialUpdateCallback = [](void*) { return false; };

    splashOutputDev.dump();

}



TEST_F(Qt5SplashOutputDevTest_1436, DumpPassesCorrectImageAndPayload_1436) {

    QImage expectedImage = splashOutputDev.getXBGRImage(false);

    EXPECT_CALL(mockHandler, partialUpdateCallback(expectedImage, payload));

    splashOutputDev.shouldDoPartialUpdateCallback = [](void*) { return true; };

    splashOutputDev.dump();

}



TEST_F(Qt5SplashOutputDevTest_1436, GetXBGRImageReturnsValidQImage_1436) {

    QImage image = splashOutputDev.getXBGRImage(false);

    EXPECT_FALSE(image.isNull());

}
