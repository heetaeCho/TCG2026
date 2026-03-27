#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "catch2/interfaces/catch_interfaces_config.hpp"

#include "catch2/internal/catch_context.hpp"



using namespace Catch;

using ::testing::Return;

using ::testing::_;



class MockIConfig : public IConfig {

public:

    MOCK_CONST_METHOD0(rngSeed, uint32_t());

};



TEST(getSeedTest_710, ReturnsRngSeedFromConfig_710) {

    MockIConfig mockConfig;

    Context context;

    

    const uint32_t expectedSeed = 42;

    EXPECT_CALL(mockConfig, rngSeed()).WillOnce(Return(expectedSeed));

    

    context.setConfig(&mockConfig);

    

    EXPECT_EQ(getSeed(), expectedSeed);

}



TEST(getSeedTest_710, HandlesDefaultConfig_710) {

    Context context;

    

    // Assuming default config returns a seed of 0 if not set

    EXPECT_EQ(getSeed(), 0);

}
