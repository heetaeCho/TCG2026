#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/env.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Invoke;

using ::testing::Return;



class MockEnv : public Env {

public:

    MOCK_METHOD(void, StartThread, (void (*f)(void*), void* a), (override));

};



class EnvWrapperTest_120 : public ::testing::Test {

protected:

    MockEnv mock_env;

    EnvWrapper env_wrapper{&mock_env};

};



TEST_F(EnvWrapperTest_120, StartThread_CallsTargetStartThread_120) {

    void (*test_func)(void*) = [](void*) {};

    EXPECT_CALL(mock_env, StartThread(test_func, _));

    env_wrapper.StartThread(test_func, nullptr);

}
