#include "gtest/gtest.h"
#include "msvc_helper.h"
#include <string>

class CLWrapperTest_108 : public ::testing::Test {
protected:
    CLWrapper wrapper_;
};

// Test that default construction sets env_block_ to NULL
TEST_F(CLWrapperTest_108, DefaultConstructorSetsEnvBlockToNull_108) {
    CLWrapper w;
    // After default construction, env_block_ should be NULL
    // We can verify this indirectly by checking the public member
    EXPECT_EQ(nullptr, w.env_block_);
}

// Test that SetEnvBlock sets the env_block_ member correctly
TEST_F(CLWrapperTest_108, SetEnvBlockSetsValue_108) {
    int dummy = 42;
    wrapper_.SetEnvBlock(&dummy);
    EXPECT_EQ(&dummy, wrapper_.env_block_);
}

// Test that SetEnvBlock can be called with NULL
TEST_F(CLWrapperTest_108, SetEnvBlockWithNull_108) {
    // First set to something non-null
    int dummy = 10;
    wrapper_.SetEnvBlock(&dummy);
    EXPECT_EQ(&dummy, wrapper_.env_block_);

    // Then set back to NULL
    wrapper_.SetEnvBlock(NULL);
    EXPECT_EQ(nullptr, wrapper_.env_block_);
}

// Test that SetEnvBlock can be called multiple times with different values
TEST_F(CLWrapperTest_108, SetEnvBlockMultipleTimes_108) {
    int dummy1 = 1;
    int dummy2 = 2;
    char dummy3 = 'a';

    wrapper_.SetEnvBlock(&dummy1);
    EXPECT_EQ(&dummy1, wrapper_.env_block_);

    wrapper_.SetEnvBlock(&dummy2);
    EXPECT_EQ(&dummy2, wrapper_.env_block_);

    wrapper_.SetEnvBlock(&dummy3);
    EXPECT_EQ(&dummy3, wrapper_.env_block_);
}

// Test that SetEnvBlock with nullptr works
TEST_F(CLWrapperTest_108, SetEnvBlockWithNullptr_108) {
    wrapper_.SetEnvBlock(nullptr);
    EXPECT_EQ(nullptr, wrapper_.env_block_);
}

// Test that env_block_ is accessible and consistent after SetEnvBlock
TEST_F(CLWrapperTest_108, EnvBlockConsistencyAfterSet_108) {
    char env_data[] = "KEY=VALUE\0OTHER=DATA\0";
    wrapper_.SetEnvBlock(env_data);
    EXPECT_EQ(static_cast<void*>(env_data), wrapper_.env_block_);
}

// Test that different CLWrapper instances have independent env_block_ values
TEST_F(CLWrapperTest_108, IndependentInstances_108) {
    CLWrapper wrapper1;
    CLWrapper wrapper2;

    int val1 = 100;
    int val2 = 200;

    wrapper1.SetEnvBlock(&val1);
    wrapper2.SetEnvBlock(&val2);

    EXPECT_EQ(&val1, wrapper1.env_block_);
    EXPECT_EQ(&val2, wrapper2.env_block_);
    EXPECT_NE(wrapper1.env_block_, wrapper2.env_block_);
}
