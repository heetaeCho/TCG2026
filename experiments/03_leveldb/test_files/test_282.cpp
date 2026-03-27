#include <gtest/gtest.h>

#include "db/c.cc"

#include "leveldb/env.h"



class EnvTest_282 : public ::testing::Test {

protected:

    void SetUp() override {

        env_t = leveldb_create_default_env();

    }



    void TearDown() override {

        delete env_t;

    }



    leveldb_env_t* env_t;

};



TEST_F(EnvTest_282, CreateDefaultEnv_ReturnsNonNullPointer_282) {

    EXPECT_NE(env_t, nullptr);

}



TEST_F(EnvTest_282, CreateDefaultEnv_IsDefaultFlagSetTrue_282) {

    EXPECT_TRUE(env_t->is_default);

}



TEST_F(EnvTest_282, CreateDefaultEnv_RepIsNotNull_282) {

    EXPECT_NE(env_t->rep, nullptr);

}



TEST_F(EnvTest_282, DefaultEnv_ReturnsSameInstance_282) {

    leveldb_env_t* env_t2 = leveldb_create_default_env();

    EXPECT_EQ(env_t2->rep, env_t->rep);

    delete env_t2;

}
