#include "gtest/gtest.h"

#include "gmock/gmock.h"

#include "db/db_impl.h"

#include "leveldb/slice.h"



using namespace leveldb;



class DBImplTest : public ::testing::Test {

protected:

    Options options;

    std::string dbname = "test_db";

    DBImpl* db;



    void SetUp() override {

        db = new DBImpl(options, dbname);

    }



    void TearDown() override {

        delete db;

    }

};



TEST_F(DBImplTest_314, GetProperty_InvalidPrefix_ReturnsFalse_314) {

    std::string value;

    EXPECT_FALSE(db->GetProperty(Slice("invalid.prefix"), &value));

}



TEST_F(DBImplTest_314, GetProperty_NumFilesAtLevel_NormalOperation_ReturnsTrue_314) {

    std::string value;

    EXPECT_TRUE(db->GetProperty(Slice("leveldb.num-files-at-level0"), &value));

}



TEST_F(DBImplTest_314, GetProperty_NumFilesAtLevel_OutOfBounds_ReturnsFalse_314) {

    std::string value;

    EXPECT_FALSE(db->GetProperty(Slice("leveldb.num-files-at-level7"), &value));

}



TEST_F(DBImplTest_314, GetProperty_Stats_NormalOperation_ReturnsTrue_314) {

    std::string value;

    EXPECT_TRUE(db->GetProperty(Slice("leveldb.stats"), &value));

}



TEST_F(DBImplTest_314, GetProperty_Sstables_NormalOperation_ReturnsTrue_314) {

    std::string value;

    EXPECT_TRUE(db->GetProperty(Slice("leveldb.sstables"), &value));

}



TEST_F(DBImplTest_314, GetProperty_ApproximateMemoryUsage_NormalOperation_ReturnsTrue_314) {

    std::string value;

    EXPECT_TRUE(db->GetProperty(Slice("leveldb.approximate-memory-usage"), &value));

}
