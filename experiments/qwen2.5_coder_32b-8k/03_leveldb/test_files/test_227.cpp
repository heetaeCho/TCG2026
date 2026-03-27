#include <gtest/gtest.h>

#include "db/c.cc"

#include "leveldb/db.h"



class DBMock : public leveldb::DB {

public:

    MOCK_METHOD0(GetSnapshot, const leveldb::Snapshot*());

};



struct TestEnv {

    TestEnv() {

        db = new DBMock();

        c_db.rep = db;

    }



    ~TestEnv() {

        delete db;

    }



    DBMock* db;

    leveldb_t c_db;

};



class SnapshotTest_227 : public ::testing::Test {

protected:

    void SetUp() override {

        env = new TestEnv();

    }



    void TearDown() override {

        delete env;

    }



    TestEnv* env;

};



TEST_F(SnapshotTest_227, CreateSnapshot_ReturnsNonNullPointer_227) {

    leveldb_snapshot_t* snapshot = leveldb_create_snapshot(&env->c_db);

    ASSERT_NE(snapshot, nullptr);

    delete snapshot;

}



TEST_F(SnapshotTest_227, CreateSnapshot_DelegatesToDBGetSnapshot_227) {

    const leveldb::Snapshot* mock_snapshot = new leveldb::Snapshot();

    EXPECT_CALL(*env->db, GetSnapshot()).WillOnce(::testing::Return(mock_snapshot));



    leveldb_snapshot_t* snapshot = leveldb_create_snapshot(&env->c_db);

    ASSERT_NE(snapshot, nullptr);

    EXPECT_EQ(snapshot->rep, mock_snapshot);



    delete snapshot;

    delete mock_snapshot;

}



TEST_F(SnapshotTest_227, CreateSnapshot_HandlesNullDBPointer_227) {

    leveldb_t* null_db = nullptr;

    leveldb_snapshot_t* snapshot = leveldb_create_snapshot(null_db);

    EXPECT_EQ(snapshot, nullptr);

}
