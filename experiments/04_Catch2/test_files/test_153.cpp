#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the class to be tested is named `WriteBatch` and has the following interface:

class WriteBatch {

public:

    virtual ~WriteBatch() = default;

    virtual void Put(const std::string& key, const std::string& value) = 0;

    virtual size_t Count() const = 0;

    virtual void Clear() = 0;

};



// Mocking the WriteBatch interface for testing

class MockWriteBatch : public WriteBatch {

public:

    MOCK_METHOD(void, Put, (const std::string& key, const std::string& value), (override));

    MOCK_METHOD(size_t, Count, (), (const, override));

    MOCK_METHOD(void, Clear, (), (override));

};



// Test fixture for WriteBatch tests

class WriteBatchTest_153 : public ::testing::Test {

protected:

    MockWriteBatch mock_batch;

};



TEST_F(WriteBatchTest_153, PutIncreasesCount_153) {

    EXPECT_CALL(mock_batch, Count()).WillOnce(::testing::Return(0)).WillOnce(::testing::Return(1));

    mock_batch.Put("key1", "value1");

    EXPECT_EQ(mock_batch.Count(), 1);

}



TEST_F(WriteBatchTest_153, ClearResetsCount_153) {

    EXPECT_CALL(mock_batch, Count()).WillOnce(::testing::Return(1)).WillOnce(::testing::Return(0));

    mock_batch.Put("key1", "value1");

    mock_batch.Clear();

    EXPECT_EQ(mock_batch.Count(), 0);

}



TEST_F(WriteBatchTest_153, MultiplePutsIncreaseCount_153) {

    EXPECT_CALL(mock_batch, Count())

        .WillOnce(::testing::Return(0))

        .WillOnce(::testing::Return(1))

        .WillOnce(::testing::Return(2));

    mock_batch.Put("key1", "value1");

    mock_batch.Put("key2", "value2");

    EXPECT_EQ(mock_batch.Count(), 2);

}



TEST_F(WriteBatchTest_153, ClearAfterMultiplePutsResetsCount_153) {

    EXPECT_CALL(mock_batch, Count())

        .WillOnce(::testing::Return(0))

        .WillOnce(::testing::Return(1))

        .WillOnce(::testing::Return(2))

        .WillOnce(::testing::Return(0));

    mock_batch.Put("key1", "value1");

    mock_batch.Put("key2", "value2");

    mock_batch.Clear();

    EXPECT_EQ(mock_batch.Count(), 0);

}



TEST_F(WriteBatchTest_153, PutSameKeyTwiceIncreasesCount_153) {

    EXPECT_CALL(mock_batch, Count())

        .WillOnce(::testing::Return(0))

        .WillOnce(::testing::Return(1))

        .WillOnce(::testing::Return(2));

    mock_batch.Put("key1", "value1");

    mock_batch.Put("key1", "value2");

    EXPECT_EQ(mock_batch.Count(), 2);

}



// Assuming there are no observable exceptional/error cases in the provided interface

```


