#include <gtest/gtest.h>

#include "db/c.cc"

#include "leveldb/options.h"



class LeveldbOptionsTest_258 : public ::testing::Test {

protected:

    leveldb_options_t* options;

    leveldb_env_t* env;



    void SetUp() override {

        options = new leveldb_options_t();

        env = new leveldb_env_t();

        env->rep = nullptr;  // Initialize to a known state

        env->is_default = false;

    }



    void TearDown() override {

        delete options;

        delete env;

    }

};



TEST_F(LeveldbOptionsTest_258, SetEnvToNonNull_258) {

    Env* mock_env = new Env();

    env->rep = mock_env;



    leveldb_options_set_env(options, env);



    EXPECT_EQ(options->rep.env, mock_env);

    delete mock_env;

}



TEST_F(LeveldbOptionsTest_258, SetEnvToNull_258) {

    leveldb_options_set_env(options, nullptr);



    EXPECT_EQ(options->rep.env, nullptr);

}



TEST_F(LeveldbOptionsTest_258, SetEnvTwice_258) {

    Env* mock_env1 = new Env();

    Env* mock_env2 = new Env();

    env->rep = mock_env1;



    leveldb_options_set_env(options, env);

    EXPECT_EQ(options->rep.env, mock_env1);



    env->rep = mock_env2;

    leveldb_options_set_env(options, env);

    EXPECT_EQ(options->rep.env, mock_env2);



    delete mock_env1;

    delete mock_env2;

}



TEST_F(LeveldbOptionsTest_258, SetEnvWithDefault_258) {

    Env* default_env = Env::Default();

    leveldb_options_set_env(options, nullptr);

    EXPECT_EQ(options->rep.env, nullptr);



    env->rep = default_env;

    leveldb_options_set_env(options, env);

    EXPECT_EQ(options->rep.env, default_env);

}
