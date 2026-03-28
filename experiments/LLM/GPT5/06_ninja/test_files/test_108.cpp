// File: ./TestProjects/ninja/tests/msvc_helper_test_108.cc

#include "msvc_helper.h"

#include <gtest/gtest.h>

class CLWrapperTest_108 : public ::testing::Test {
protected:
    CLWrapper wrapper_;
};

// Verifies that the default-constructed CLWrapper has a null env_block_.
TEST_F(CLWrapperTest_108, DefaultEnvBlockIsNull_108) {
    EXPECT_EQ(nullptr, wrapper_.env_block_);
}

// Verifies that SetEnvBlock stores the given non-null pointer.
TEST_F(CLWrapperTest_108, SetEnvBlockStoresNonNullPointer_108) {
    int dummy = 0;
    void* env = static_cast<void*>(&dummy);

    wrapper_.SetEnvBlock(env);

    EXPECT_EQ(env, wrapper_.env_block_);
}

// Verifies that SetEnvBlock can accept and store a nullptr.
TEST_F(CLWrapperTest_108, SetEnvBlockAcceptsNullptr_108) {
    // First set to some non-null pointer to ensure it actually changes.
    int dummy = 0;
    wrapper_.SetEnvBlock(static_cast<void*>(&dummy));
    ASSERT_NE(nullptr, wrapper_.env_block_);

    // Now set to nullptr and verify.
    wrapper_.SetEnvBlock(nullptr);

    EXPECT_EQ(nullptr, wrapper_.env_block_);
}

// Verifies that calling SetEnvBlock multiple times overwrites the previous value.
TEST_F(CLWrapperTest_108, SetEnvBlockOverwritesPreviousValue_108) {
    int first = 1;
    int second = 2;

    void* first_env = static_cast<void*>(&first);
    void* second_env = static_cast<void*>(&second);

    wrapper_.SetEnvBlock(first_env);
    ASSERT_EQ(first_env, wrapper_.env_block_);

    wrapper_.SetEnvBlock(second_env);

    EXPECT_EQ(second_env, wrapper_.env_block_);
    EXPECT_NE(first_env, wrapper_.env_block_);
}
