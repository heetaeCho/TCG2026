#include <gtest/gtest.h>

#include "db/c.cc"  // Assuming the header file is in the same location or included properly



class ReadOptionsTest_273 : public ::testing::Test {

protected:

    void SetUp() override {

        options = leveldb_readoptions_create();

    }



    void TearDown() override {

        if (options) {

            leveldb_readoptions_destroy(options);

            options = nullptr;

        }

    }



    leveldb_readoptions_t* options;

};



TEST_F(ReadOptionsTest_273, CreateAndDestroy_273) {

    // Test normal operation: create and destroy

    ASSERT_NE(options, nullptr);

}



// Since the interface only provides a destroy function, there are no boundary conditions or exceptional cases to test.
