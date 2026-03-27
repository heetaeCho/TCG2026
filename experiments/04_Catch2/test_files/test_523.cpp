#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_run_context.hpp"

#include "catch2/interfaces/catch_interfaces_config.hpp"



using namespace Catch;

using ::testing::Return;



class MockConfig : public IConfig {

public:

    MOCK_CONST_METHOD0(rngSeed, uint32_t());

};



TEST_F(CatchRunContextTest_523, RngSeed_ReturnsValueFromConfig_523) {

    MockConfig mockConfig;

    Context context;

    context.setConfig(&mockConfig);



    const unsigned int expectedSeed = 12345;

    EXPECT_CALL(mockConfig, rngSeed()).WillOnce(Return(expectedSeed));



    unsigned int actualSeed = rngSeed();

    EXPECT_EQ(actualSeed, expectedSeed);

}



TEST_F(CatchRunContextTest_523, RngSeed_ConfigNotSet_ReturnsZero_523) {

    Context context;

    context.setConfig(nullptr);



    unsigned int actualSeed = rngSeed();

    EXPECT_EQ(actualSeed, 0U);

}
