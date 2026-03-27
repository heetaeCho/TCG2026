#include <gtest/gtest.h>

#include "leveldb/iterator.h"

#include "db/c.cc"



using namespace leveldb;



class LevelDBIteratorTest_241 : public ::testing::Test {

protected:

    void SetUp() override {

        mock_iterator = std::make_unique<MockIterator>();

        iterator_t.rep = mock_iterator.get();

    }



    struct leveldb_iterator_t iterator_t;

    std::unique_ptr<MockIterator> mock_iterator;



    class MockIterator : public Iterator {

    public:

        MOCK_CONST_METHOD0(Valid, bool());

        MOCK_METHOD0(SeekToFirst, void());

        MOCK_METHOD0(SeekToLast, void());

        MOCK_METHOD1(Seek, void(const Slice& target));

        MOCK_METHOD0(Next, void());

        MOCK_METHOD0(Prev, void());

        MOCK_CONST_METHOD0(key, Slice());

        MOCK_CONST_METHOD0(value, Slice());

        MOCK_CONST_METHOD0(status, Status());

    };

};



TEST_F(LevelDBIteratorTest_241, KeyReturnsCorrectData_241) {

    const char* expected_key = "test_key";

    size_t expected_size = strlen(expected_key);

    EXPECT_CALL(*mock_iterator, key()).WillOnce(testing::Return(Slice(expected_key)));



    size_t klen;

    const char* result = leveldb_iter_key(&iterator_t, &klen);



    ASSERT_EQ(klen, expected_size);

    ASSERT_STREQ(result, expected_key);

}



TEST_F(LevelDBIteratorTest_241, KeyReturnsEmptySliceWhenNoData_241) {

    EXPECT_CALL(*mock_iterator, key()).WillOnce(testing::Return(Slice()));



    size_t klen;

    const char* result = leveldb_iter_key(&iterator_t, &klen);



    ASSERT_EQ(klen, 0);

    ASSERT_STREQ(result, "");

}



TEST_F(LevelDBIteratorTest_241, KeyHandlesLargeDataCorrectly_241) {

    std::string large_data(1024, 'a'); // Large string of 'a's

    const char* expected_key = large_data.c_str();

    size_t expected_size = large_data.size();

    EXPECT_CALL(*mock_iterator, key()).WillOnce(testing::Return(Slice(expected_key)));



    size_t klen;

    const char* result = leveldb_iter_key(&iterator_t, &klen);



    ASSERT_EQ(klen, expected_size);

    ASSERT_STREQ(result, expected_key);

}
