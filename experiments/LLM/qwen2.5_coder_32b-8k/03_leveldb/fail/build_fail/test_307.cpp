#include <gtest/gtest.h>

#include "db/db_impl.h"

#include "leveldb/options.h"

#include "leveldb/iterator.h"



using namespace leveldb;



class DBImplTest_307 : public ::testing::Test {

protected:

    Options options;

    std::string dbname = "/tmp/testdb";

    DBImpl* dbimpl;



    void SetUp() override {

        dbimpl = new DBImpl(options, dbname);

    }



    void TearDown() override {

        delete dbimpl;

    }

};



TEST_F(DBImplTest_307, NewIterator_NormalOperation_307) {

    ReadOptions read_options;

    Iterator* iter = dbimpl->NewIterator(read_options);

    EXPECT_NE(iter, nullptr);

    iter->SeekToFirst();

    delete iter;

}



TEST_F(DBImplTest_307, NewIterator_WithSnapshot_307) {

    const Snapshot* snapshot = dbimpl->GetSnapshot();

    ReadOptions read_options;

    read_options.snapshot = snapshot;

    Iterator* iter = dbimpl->NewIterator(read_options);

    EXPECT_NE(iter, nullptr);

    iter->SeekToFirst();

    delete iter;

    dbimpl->ReleaseSnapshot(snapshot);

}



TEST_F(DBImplTest_307, NewIterator_VerifyChecksumsEnabled_307) {

    ReadOptions read_options;

    read_options.verify_checksums = true;

    Iterator* iter = dbimpl->NewIterator(read_options);

    EXPECT_NE(iter, nullptr);

    iter->SeekToFirst();

    delete iter;

}



TEST_F(DBImplTest_307, NewIterator_FillCacheDisabled_307) {

    ReadOptions read_options;

    read_options.fill_cache = false;

    Iterator* iter = dbimpl->NewIterator(read_options);

    EXPECT_NE(iter, nullptr);

    iter->SeekToFirst();

    delete iter;

}



TEST_F(DBImplTest_307, NewIterator_NoSnapshot_307) {

    ReadOptions read_options;

    read_options.snapshot = nullptr;

    Iterator* iter = dbimpl->NewIterator(read_options);

    EXPECT_NE(iter, nullptr);

    iter->SeekToFirst();

    delete iter;

}



TEST_F(DBImplTest_307, NewIterator_SnapshotInvalidated_307) {

    const Snapshot* snapshot = dbimpl->GetSnapshot();

    ReadOptions read_options;

    read_options.snapshot = snapshot;

    dbimpl->ReleaseSnapshot(snapshot);

    Iterator* iter = dbimpl->NewIterator(read_options);

    EXPECT_NE(iter, nullptr);

    iter->SeekToFirst();

    delete iter;

}
