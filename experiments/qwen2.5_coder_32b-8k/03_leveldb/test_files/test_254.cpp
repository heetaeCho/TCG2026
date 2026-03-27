#include <gtest/gtest.h>

#include "db/c.cc"

#include "leveldb/options.h"



// Mock FilterPolicy for testing

class MockFilterPolicy : public leveldb_filterpolicy_t {

public:

    MOCK_METHOD(void, CreateFilter, (const Slice* keys, int n, std::string* dst) const, (override));

    MOCK_METHOD(bool, KeyMayMatch, (const Slice& key, const Slice& filter) const, (override));

    MOCK_METHOD(const char*, Name, (), (const override));

};



class LeveldbOptionsTest_254 : public ::testing::Test {

protected:

    leveldb_options_t options;

    MockFilterPolicy* mock_filter_policy;



    void SetUp() override {

        mock_filter_policy = new MockFilterPolicy();

    }



    void TearDown() override {

        delete mock_filter_policy;

    }

};



TEST_F(LeveldbOptionsTest_254, SetFilterPolicy_254) {

    leveldb_options_set_filter_policy(&options, mock_filter_policy);

    EXPECT_EQ(options.rep.filter_policy, static_cast<const FilterPolicy*>(mock_filter_policy));

}



TEST_F(LeveldbOptionsTest_254, SetNullFilterPolicy_254) {

    leveldb_options_set_filter_policy(&options, nullptr);

    EXPECT_EQ(options.rep.filter_policy, nullptr);

}
