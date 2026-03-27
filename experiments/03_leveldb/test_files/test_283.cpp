#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking Env class to verify interactions if needed

class Env {

public:

    virtual ~Env() {}

};



// Assuming leveldb_env_t is defined in a header file included here

struct leveldb_env_t { 

    public: Env * rep; 

    public: bool is_default; 

};



extern "C" void leveldb_env_destroy(leveldb_env_t* env);



class LevelDBEnvTest_283 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup for each test

        env = new leveldb_env_t;

        env->rep = new Env();

        env->is_default = false;

    }



    void TearDown() override {

        // Cleanup after each test

        delete env;

    }



    leveldb_env_t* env;

};



TEST_F(LevelDBEnvTest_283, DestroyNonDefaultEnvironment_283) {

    // Test normal operation for destroying a non-default environment

    leveldb_env_destroy(env);

    SUCCEED();

}



TEST_F(LevelDBEnvTest_283, DestroyDefaultEnvironment_283) {

    // Test normal operation for destroying a default environment

    env->is_default = true;

    leveldb_env_destroy(env);

    SUCCEED();

}



TEST_F(LevelDBEnvTest_283, DestroyNullPointer_283) {

    // Test boundary condition: destroy with null pointer

    leveldb_env_destroy(nullptr);

    SUCCEED();

}
