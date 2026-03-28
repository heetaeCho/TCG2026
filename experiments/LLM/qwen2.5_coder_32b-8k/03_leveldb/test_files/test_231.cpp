#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/db.h"

#include "db/c.cc"



using namespace leveldb;

using ::testing::_;

using ::testing::Mock;



// Mock class for DB to verify interactions

class MockDB : public DB {

public:

    MOCK_METHOD(void, CompactRange, (const Slice* begin, const Slice* end), (override));

};



TEST_F(WriteBatchTest_231, CompactRangeWithValidKeys_231) {

    MockDB mock_db;

    leveldb_t db;

    db.rep = &mock_db;



    const char* start_key = "start";

    size_t start_key_len = strlen(start_key);

    const char* limit_key = "limit";

    size_t limit_key_len = strlen(limit_key);



    EXPECT_CALL(mock_db, CompactRange(_, _))

        .Times(1)

        .WillOnce([](const Slice* begin, const Slice* end) {

            ASSERT_NE(begin, nullptr);

            ASSERT_EQ(std::string(begin->data(), begin->size()), "start");

            ASSERT_NE(end, nullptr);

            ASSERT_EQ(std::string(end->data(), end->size()), "limit");

        });



    leveldb_compact_range(&db, start_key, start_key_len, limit_key, limit_key_len);

}



TEST_F(WriteBatchTest_231, CompactRangeWithNullStartKey_231) {

    MockDB mock_db;

    leveldb_t db;

    db.rep = &mock_db;



    const char* limit_key = "limit";

    size_t limit_key_len = strlen(limit_key);



    EXPECT_CALL(mock_db, CompactRange(_, _))

        .Times(1)

        .WillOnce([](const Slice* begin, const Slice* end) {

            ASSERT_EQ(begin, nullptr);

            ASSERT_NE(end, nullptr);

            ASSERT_EQ(std::string(end->data(), end->size()), "limit");

        });



    leveldb_compact_range(&db, nullptr, 0, limit_key, limit_key_len);

}



TEST_F(WriteBatchTest_231, CompactRangeWithNullLimitKey_231) {

    MockDB mock_db;

    leveldb_t db;

    db.rep = &mock_db;



    const char* start_key = "start";

    size_t start_key_len = strlen(start_key);



    EXPECT_CALL(mock_db, CompactRange(_, _))

        .Times(1)

        .WillOnce([](const Slice* begin, const Slice* end) {

            ASSERT_NE(begin, nullptr);

            ASSERT_EQ(std::string(begin->data(), begin->size()), "start");

            ASSERT_EQ(end, nullptr);

        });



    leveldb_compact_range(&db, start_key, start_key_len, nullptr, 0);

}



TEST_F(WriteBatchTest_231, CompactRangeWithBothKeysNull_231) {

    MockDB mock_db;

    leveldb_t db;

    db.rep = &mock_db;



    EXPECT_CALL(mock_db, CompactRange(_, _))

        .Times(1)

        .WillOnce([](const Slice* begin, const Slice* end) {

            ASSERT_EQ(begin, nullptr);

            ASSERT_EQ(end, nullptr);

        });



    leveldb_compact_range(&db, nullptr, 0, nullptr, 0);

}
