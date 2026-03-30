#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/db_impl.h"

#include "db/version_set.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Mock;



class MockVersionSet : public VersionSet {

public:

    MOCK_METHOD(uint64_t, ApproximateOffsetOf, (const Version* v, const InternalKey& ikey), (override));

    MOCK_CONST_METHOD0(current, Version*());

};



class DBImplTest_315 : public ::testing::Test {

protected:

    void SetUp() override {

        options = new Options();

        dbname = "testdb";

        versions = new MockVersionSet(dbname, options, nullptr, nullptr);

        db_impl = new DBImpl(*options, dbname);

        static_cast<DBImpl*>(db_impl)->versions_ = versions;

    }



    void TearDown() override {

        delete db_impl;

        delete versions;

        delete options;

    }



    Options* options;

    std::string dbname;

    MockVersionSet* versions;

    DB* db_impl;

};



TEST_F(DBImplTest_315, GetApproximateSizes_OneRange_315) {

    Range range[] = {Range(Slice("start"), Slice("limit"))};

    uint64_t sizes[1];

    Version mock_version;

    InternalKey k1(Slice("start"), kMaxSequenceNumber, kValueTypeForSeek);

    InternalKey k2(Slice("limit"), kMaxSequenceNumber, kValueTypeForSeek);



    EXPECT_CALL(*versions, current()).WillOnce(::testing::Return(&mock_version));

    EXPECT_CALL(*versions, ApproximateOffsetOf(&mock_version, k1)).WillOnce(::testing::Return(100U));

    EXPECT_CALL(*versions, ApproximateOffsetOf(&mock_version, k2)).WillOnce(::testing::Return(200U));



    db_impl->GetApproximateSizes(range, 1, sizes);



    ASSERT_EQ(sizes[0], 100U);

}



TEST_F(DBImplTest_315, GetApproximateSizes_MultipleRanges_315) {

    Range ranges[] = {Range(Slice("start1"), Slice("limit1")), Range(Slice("start2"), Slice("limit2"))};

    uint64_t sizes[2];

    Version mock_version;

    InternalKey k1_1(Slice("start1"), kMaxSequenceNumber, kValueTypeForSeek);

    InternalKey k2_1(Slice("limit1"), kMaxSequenceNumber, kValueTypeForSeek);

    InternalKey k1_2(Slice("start2"), kMaxSequenceNumber, kValueTypeForSeek);

    InternalKey k2_2(Slice("limit2"), kMaxSequenceNumber, kValueTypeForSeek);



    EXPECT_CALL(*versions, current()).WillOnce(::testing::Return(&mock_version));

    EXPECT_CALL(*versions, ApproximateOffsetOf(&mock_version, k1_1)).WillOnce(::testing::Return(50U));

    EXPECT_CALL(*versions, ApproximateOffsetOf(&mock_version, k2_1)).WillOnce(::testing::Return(150U));

    EXPECT_CALL(*versions, ApproximateOffsetOf(&mock_version, k1_2)).WillOnce(::testing::Return(200U));

    EXPECT_CALL(*versions, ApproximateOffsetOf(&mock_version, k2_2)).WillOnce(::testing::Return(300U));



    db_impl->GetApproximateSizes(ranges, 2, sizes);



    ASSERT_EQ(sizes[0], 100U);

    ASSERT_EQ(sizes[1], 100U);

}



TEST_F(DBImplTest_315, GetApproximateSizes_ZeroRanges_315) {

    Range ranges[] = {};

    uint64_t sizes[0];



    EXPECT_CALL(*versions, current()).Times(0);



    db_impl->GetApproximateSizes(ranges, 0, sizes);

}



TEST_F(DBImplTest_315, GetApproximateSizes_LimitBeforeStart_315) {

    Range range[] = {Range(Slice("limit"), Slice("start"))};

    uint64_t sizes[1];

    Version mock_version;

    InternalKey k1(Slice("limit"), kMaxSequenceNumber, kValueTypeForSeek);

    InternalKey k2(Slice("start"), kMaxSequenceNumber, kValueTypeForSeek);



    EXPECT_CALL(*versions, current()).WillOnce(::testing::Return(&mock_version));

    EXPECT_CALL(*versions, ApproximateOffsetOf(&mock_version, k1)).WillOnce(::testing::Return(200U));

    EXPECT_CALL(*versions, ApproximateOffsetOf(&mock_version, k2)).WillOnce(::testing::Return(100U));



    db_impl->GetApproximateSizes(range, 1, sizes);



    ASSERT_EQ(sizes[0], 0U);

}
