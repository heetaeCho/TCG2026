#include <gtest/gtest.h>

#include "db/memtable.cc"

#include "leveldb/slice.h"



// Mocking external collaborators if needed, but in this case, we don't need to mock any since we treat MemTableIterator as a black box.



class MemTableIteratorTest : public ::testing::Test {

protected:

    leveldb::MemTable* memtable_;

    leveldb::MemTableIterator* iterator_;



    void SetUp() override {

        memtable_ = new leveldb::MemTable(leveldb::InternalKeyComparator(leveldb::BytewiseComparator()));

        iterator_ = new leveldb::MemTableIterator(memtable_);

    }



    void TearDown() override {

        delete iterator_;

        delete memtable_;

    }

};



// Test if value() returns an empty Slice when the iterator is not valid

TEST_F(MemTableIteratorTest_364, ValueEmptyWhenInvalid_364) {

    ASSERT_FALSE(iterator_->Valid());

    leveldb::Slice value = iterator_->value();

    EXPECT_TRUE(value.empty());

}



// Test if value() returns a non-empty Slice when the iterator is valid

TEST_F(MemTableIteratorTest_364, ValueNonEmptyWhenValid_364) {

    std::string key = "test_key";

    std::string val = "test_value";

    memtable_->Add(leveldb::kTypeValue, leveldb::Slice(key), leveldb::Slice(val));

    iterator_->SeekToFirst();

    ASSERT_TRUE(iterator_->Valid());

    leveldb::Slice value = iterator_->value();

    EXPECT_FALSE(value.empty());

    EXPECT_EQ(std::string(value.data(), value.size()), val);

}



// Test if the value() method correctly handles boundary conditions with empty strings

TEST_F(MemTableIteratorTest_364, ValueWithEmptyString_364) {

    std::string key = "test_key";

    memtable_->Add(leveldb::kTypeValue, leveldb::Slice(key), leveldb::Slice(""));

    iterator_->SeekToFirst();

    ASSERT_TRUE(iterator_->Valid());

    leveldb::Slice value = iterator_->value();

    EXPECT_EQ(value.empty(), true);

}



// Test if the value() method returns consistent results across multiple calls

TEST_F(MemTableIteratorTest_364, ValueConsistencyAcrossCalls_364) {

    std::string key = "test_key";

    std::string val = "consistent_value";

    memtable_->Add(leveldb::kTypeValue, leveldb::Slice(key), leveldb::Slice(val));

    iterator_->SeekToFirst();

    ASSERT_TRUE(iterator_->Valid());

    leveldb::Slice value1 = iterator_->value();

    leveldb::Slice value2 = iterator_->value();

    EXPECT_EQ(std::string(value1.data(), value1.size()), val);

    EXPECT_EQ(std::string(value2.data(), value2.size()), val);

}



// Test if the value() method returns correct results after a Seek operation

TEST_F(MemTableIteratorTest_364, ValueAfterSeekOperation_364) {

    std::string key = "test_key";

    std::string val = "seek_value";

    memtable_->Add(leveldb::kTypeValue, leveldb::Slice(key), leveldb::Slice(val));

    iterator_->Seek(leveldb::Slice(key));

    ASSERT_TRUE(iterator_->Valid());

    leveldb::Slice value = iterator_->value();

    EXPECT_EQ(std::string(value.data(), value.size()), val);

}



// Test if the value() method returns correct results after multiple Next operations

TEST_F(MemTableIteratorTest_364, ValueAfterMultipleNextOperations_364) {

    std::vector<std::pair<std::string, std::string>> entries = {{"key1", "value1"}, {"key2", "value2"}, {"key3", "value3"}};

    for (const auto& entry : entries) {

        memtable_->Add(leveldb::kTypeValue, leveldb::Slice(entry.first), leveldb::Slice(entry.second));

    }

    iterator_->SeekToFirst();

    int count = 0;

    while (iterator_->Valid()) {

        leveldb::Slice value = iterator_->value();

        EXPECT_EQ(std::string(value.data(), value.size()), entries[count].second);

        iterator_->Next();

        ++count;

    }

    EXPECT_EQ(count, entries.size());

}



// Test if the value() method returns correct results after multiple Prev operations

TEST_F(MemTableIteratorTest_364, ValueAfterMultiplePrevOperations_364) {

    std::vector<std::pair<std::string, std::string>> entries = {{"key1", "value1"}, {"key2", "value2"}, {"key3", "value3"}};

    for (const auto& entry : entries) {

        memtable_->Add(leveldb::kTypeValue, leveldb::Slice(entry.first), leveldb::Slice(entry.second));

    }

    iterator_->SeekToLast();

    int count = entries.size() - 1;

    while (iterator_->Valid()) {

        leveldb::Slice value = iterator_->value();

        EXPECT_EQ(std::string(value.data(), value.size()), entries[count].second);

        iterator_->Prev();

        --count;

    }

    EXPECT_EQ(count, -1);

}
