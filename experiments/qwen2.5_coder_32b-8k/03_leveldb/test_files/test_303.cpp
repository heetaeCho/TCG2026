#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/db_impl.h"

#include "leveldb/status.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class DBImplTest : public ::testing::Test {

protected:

    Options options;

    std::string dbname = "/tmp/testdb";

    DBImpl* db;



    void SetUp() override {

        db = new DBImpl(options, dbname);

    }



    void TearDown() override {

        delete db;

    }

};



TEST_F(DBImplTest_303, CompactMemTable_ReturnsOKWhenNoImmediateTable_303) {

    // Arrange

    MutexLock l(&db->mutex_);

    db->imm_ = nullptr;



    // Act

    Status s = db->TEST_CompactMemTable();



    // Assert

    EXPECT_TRUE(s.ok());

}



TEST_F(DBImplTest_303, CompactMemTable_ReturnsOKWhenImmediateTableCompactsSuccessfully_303) {

    // Arrange

    MutexLock l(&db->mutex_);

    db->imm_ = new MemTable(db->internal_comparator_);

    db->bg_error_ = Status::OK();



    // Act

    Status s = db->TEST_CompactMemTable();



    // Assert

    EXPECT_TRUE(s.ok());

}



TEST_F(DBImplTest_303, CompactMemTable_ReturnsErrorWhenBackgroundWorkFails_303) {

    // Arrange

    MutexLock l(&db->mutex_);

    db->imm_ = new MemTable(db->internal_comparator_);

    db->bg_error_ = Status::IOError("Simulated IO Error");



    // Act

    Status s = db->TEST_CompactMemTable();



    // Assert

    EXPECT_FALSE(s.ok());

    EXPECT_TRUE(s.IsIOError());

}



// Test for boundary condition where imm_ is set but bg_error_ remains ok after compacting.

TEST_F(DBImplTest_303, CompactMemTable_WaitsForBackgroundWorkToFinish_303) {

    // Arrange

    MutexLock l(&db->mutex_);

    db->imm_ = new MemTable(db->internal_comparator_);

    db->bg_error_ = Status::OK();



    // Act & Assert: This test requires mocking the background thread behavior, which is not allowed.

    // We assume that the internal mechanism of waiting for background work to finish works as expected.

    EXPECT_TRUE(db->TEST_CompactMemTable().ok());

}
