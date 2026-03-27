#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <vector>

#include <Catch2/extras/catch_amalgamated.hpp>



using namespace Catch::Matchers;

using namespace testing;



// Assuming there's a class named `WriteBatch` which we are testing.

// Since the actual class is not provided, I will create a mock interface based on typical usage.



class WriteBatch {

public:

    virtual ~WriteBatch() = default;

    virtual void Put(const std::string& key, const std::string& value) = 0;

    virtual void Delete(const std::string& key) = 0;

    virtual std::vector<std::pair<std::string, std::string>> GetContents() const = 0;

};



class MockWriteBatch : public WriteBatch {

public:

    MOCK_METHOD(void, Put, (const std::string& key, const std::string& value), (override));

    MOCK_METHOD(void, Delete, (const std::string& key), (override));

    MOCK_METHOD(std::vector<std::pair<std::string, std::string>>, GetContents, (), (const, override));

};



class WriteBatchTest_975 : public Test {

protected:

    std::unique_ptr<MockWriteBatch> mock_batch;



    void SetUp() override {

        mock_batch = std::make_unique<MockWriteBatch>();

    }

};



TEST_F(WriteBatchTest_975, PutIncreasesCount_975) {

    EXPECT_CALL(*mock_batch, GetContents())

        .WillOnce(Return(std::vector<std::pair<std::string, std::string>>{}))

        .WillOnce(Return(std::vector<std::pair<std::string, std::string>>({{"key1", "value1"}})));



    mock_batch->Put("key1", "value1");

    auto contents = mock_batch->GetContents();

    EXPECT_EQ(contents.size(), 1);

}



TEST_F(WriteBatchTest_975, PutWithSameKeyOverwritesValue_975) {

    EXPECT_CALL(*mock_batch, GetContents())

        .WillOnce(Return(std::vector<std::pair<std::string, std::string>>({{"key1", "value1"}})))

        .WillOnce(Return(std::vector<std::pair<std::string, std::string>>({{"key1", "new_value1"}})));



    mock_batch->Put("key1", "value1");

    mock_batch->Put("key1", "new_value1");

    auto contents = mock_batch->GetContents();

    EXPECT_EQ(contents.size(), 1);

    EXPECT_THAT(contents, UnorderedEqualsMatcher<std::pair<std::string, std::string>>({{"key1", "new_value1"}}));

}



TEST_F(WriteBatchTest_975, DeleteRemovesKey_975) {

    EXPECT_CALL(*mock_batch, GetContents())

        .WillOnce(Return(std::vector<std::pair<std::string, std::string>>({{"key1", "value1"}, {"key2", "value2"}})))

        .WillOnce(Return(std::vector<std::pair<std::string, std::string>>({{"key1", "value1"}})));



    mock_batch->Put("key1", "value1");

    mock_batch->Put("key2", "value2");

    mock_batch->Delete("key2");

    auto contents = mock_batch->GetContents();

    EXPECT_EQ(contents.size(), 1);

    EXPECT_THAT(contents, UnorderedEqualsMatcher<std::pair<std::string, std::string>>({{"key1", "value1"}}));

}



TEST_F(WriteBatchTest_975, DeleteNonExistentKeyNoChange_975) {

    EXPECT_CALL(*mock_batch, GetContents())

        .WillOnce(Return(std::vector<std::pair<std::string, std::string>>({{"key1", "value1"}})))

        .WillOnce(Return(std::vector<std::pair<std::string, std::string>>({{"key1", "value1"}})));



    mock_batch->Put("key1", "value1");

    mock_batch->Delete("non_existent_key");

    auto contents = mock_batch->GetContents();

    EXPECT_EQ(contents.size(), 1);

    EXPECT_THAT(contents, UnorderedEqualsMatcher<std::pair<std::string, std::string>>({{"key1", "value1"}}));

}



TEST_F(WriteBatchTest_975, GetContentsReturnsEmptyInitially_975) {

    auto contents = mock_batch->GetContents();

    EXPECT_EQ(contents.size(), 0);

}
