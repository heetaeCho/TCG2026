#include <gtest/gtest.h>

#include "db/db_impl.h"

#include "leveldb/status.h"



using namespace leveldb;



class DBImplTest_302 : public ::testing::Test {

protected:

    Options options;

    std::string dbname = "/tmp/testdb";

    DBImpl db_impl{options, dbname};



    Slice key1 = Slice("key1");

    Slice value1 = Slice("value1");

    Slice key2 = Slice("key2");

    Slice value2 = Slice("value2");



    void SetUp() override {

        // Setup any state before each test

        DestroyDB(dbname, options);

        DB::Open(options, dbname, &db_impl).ok();

    }



    void TearDown() override {

        // Cleanup any state after each test

        db_impl.Close();

        DestroyDB(dbname, options);

    }

};



TEST_F(DBImplTest_302, TEST_CompactRange_ValidLevel_302) {

    int level = 0;

    db_impl.TEST_CompactRange(level, nullptr, nullptr);

}



TEST_F(DBImplTest_302, TEST_CompactRange_BoundaryLevel_302) {

    int max_level = config::kNumLevels - 1;

    db_impl.TEST_CompactRange(max_level, nullptr, nullptr);

}



TEST_F(DBImplTest_302, TEST_CompactRange_OutOfBoundsLevel_Negative_302) {

    EXPECT_DEATH({ db_impl.TEST_CompactRange(-1, nullptr, nullptr); }, "");

}



TEST_F(DBImplTest_302, TEST_CompactRange_OutOfBoundsLevel_TooHigh_302) {

    EXPECT_DEATH({ db_impl.TEST_CompactRange(config::kNumLevels, nullptr, nullptr); }, "");

}



TEST_F(DBImplTest_302, TEST_CompactRange_ValidBeginEnd_302) {

    int level = 0;

    Slice begin("begin");

    Slice end("end");

    db_impl.TEST_CompactRange(level, &begin, &end);

}



TEST_F(DBImplTest_302, TEST_CompactRange_NullBegin_302) {

    int level = 0;

    Slice end("end");

    db_impl.TEST_CompactRange(level, nullptr, &end);

}



TEST_F(DBImplTest_302, TEST_CompactRange_NullEnd_302) {

    int level = 0;

    Slice begin("begin");

    db_impl.TEST_CompactRange(level, &begin, nullptr);

}
