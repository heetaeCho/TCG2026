#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the class to be tested is named `WriteBatch` and has the following interface:

// class WriteBatch {

// public:

//     void Put(const std::string& key, const std::string& value);

//     size_t Count() const;

//     bool Delete(const std::string& key);

// };



class MockHandler {

public:

    MOCK_METHOD(void, OnPut, (const std::string&, const std::string&));

    MOCK_METHOD(void, OnDelete, (const std::string&));

};



class WriteBatchTest_80 : public ::testing::Test {

protected:

    WriteBatch write_batch;

    MockHandler mock_handler;

};



TEST_F(WriteBatchTest_80, PutIncreasesCount_80) {

    EXPECT_EQ(write_batch.Count(), 0);

    write_batch.Put("key1", "value1");

    EXPECT_EQ(write_batch.Count(), 1);

}



TEST_F(WriteBatchTest_80, DeleteDecreasesCount_80) {

    write_batch.Put("key1", "value1");

    EXPECT_EQ(write_batch.Count(), 1);

    bool result = write_batch.Delete("key1");

    EXPECT_TRUE(result);

    EXPECT_EQ(write_batch.Count(), 0);

}



TEST_F(WriteBatchTest_80, DeleteNonExistentKeyReturnsFalse_80) {

    bool result = write_batch.Delete("non_existent_key");

    EXPECT_FALSE(result);

}



TEST_F(WriteBatchTest_80, PutSameKeyTwiceDoesNotIncreaseCount_80) {

    write_batch.Put("key1", "value1");

    EXPECT_EQ(write_batch.Count(), 1);

    write_batch.Put("key1", "new_value");

    EXPECT_EQ(write_batch.Count(), 1);

}



TEST_F(WriteBatchTest_80, PutEmptyKeyAndValue_80) {

    write_batch.Put("", "");

    EXPECT_EQ(write_batch.Count(), 1);

}



TEST_F(WriteBatchTest_80, DeleteEmptyKeyReturnsFalse_80) {

    bool result = write_batch.Delete("");

    EXPECT_FALSE(result);

}
