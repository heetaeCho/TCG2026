#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_context.hpp"



using namespace Catch;

using namespace testing;



class MockIConfig : public IConfig {

public:

    MOCK_METHOD0(someConfigMethod, void());

};



class MockIResultCapture : public IResultCapture {

public:

    MOCK_METHOD0(someResultCaptureMethod, void());

};



class ContextTest_253 : public Test {

protected:

    Context context;

    std::unique_ptr<MockIConfig> mockConfig = std::make_unique<MockIConfig>();

    std::unique_ptr<MockIResultCapture> mockResultCapture = std::make_unique<MockIResultCapture>();



    void SetUp() override {

        context.setConfig(mockConfig.get());

        context.setResultCapture(mockResultCapture.get());

    }

};



TEST_F(ContextTest_253, GetConfig_ReturnsPreviouslySetConfig_253) {

    EXPECT_EQ(context.getConfig(), mockConfig.get());

}



TEST_F(ContextTest_253, GetResultCapture_ReturnsPreviouslySetResultCapture_253) {

    EXPECT_EQ(context.getResultCapture(), mockResultCapture.get());

}



TEST_F(ContextTest_253, SetConfig_AcceptsNullptrWithoutError_253) {

    context.setConfig(nullptr);

    EXPECT_EQ(context.getConfig(), nullptr);

}



TEST_F(ContextTest_253, SetResultCapture_AcceptsNullptrWithoutError_253) {

    context.setResultCapture(nullptr);

    EXPECT_EQ(context.getResultCapture(), nullptr);

}
