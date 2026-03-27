#include <gtest/gtest.h>

#include "table/filter_block.h"

#include "leveldb/slice.h"



namespace leveldb {



class MockFilterPolicy : public FilterPolicy {

public:

    virtual const char* Name() const override { return "MockFilterPolicy"; }

    virtual void CreateFilter(const Slice* keys, int n, std::string* dst) const override {}

    virtual bool KeyMayMatch(const Slice& key, const Slice& filter) const override { return false; }

};



class FilterBlockBuilderTest_372 : public ::testing::Test {

protected:

    MockFilterPolicy mock_policy;

    FilterBlockBuilder builder;



    FilterBlockBuilderTest_372() : builder(&mock_policy) {}

};



TEST_F(FilterBlockBuilderTest_372, AddKeyWithEmptySlice_372) {

    Slice empty_slice;

    builder.AddKey(empty_slice);

}



TEST_F(FilterBlockBuilderTest_372, AddKeyWithNonEmptySlice_372) {

    Slice key("test_key");

    builder.AddKey(key);

}



TEST_F(FilterBlockBuilderTest_372, AddMultipleKeys_372) {

    Slice key1("key1");

    Slice key2("key2");

    builder.AddKey(key1);

    builder.AddKey(key2);

}



TEST_F(FilterBlockBuilderTest_372, FinishReturnsNonEmptySlice_372) {

    Slice key("test_key");

    builder.AddKey(key);

    Slice result = builder.Finish();

    EXPECT_FALSE(result.empty());

}



TEST_F(FilterBlockBuilderTest_372, FinishCalledMultipleTimes_372) {

    Slice key1("key1");

    Slice key2("key2");

    builder.AddKey(key1);

    builder.AddKey(key2);



    Slice result1 = builder.Finish();

    EXPECT_FALSE(result1.empty());



    // After finishing, the internal state should be reset.

    builder.AddKey(key1);

    Slice result2 = builder.Finish();

    EXPECT_FALSE(result2.empty());

}



TEST_F(FilterBlockBuilderTest_372, AddKeyAfterFinishDoesNotAffectPreviousResult_372) {

    Slice key("test_key");

    builder.AddKey(key);



    Slice result1 = builder.Finish();

    EXPECT_FALSE(result1.empty());



    // Adding more keys after finishing should not affect the previous result.

    builder.AddKey(key);

    Slice result2 = builder.Finish();

    EXPECT_NE(result1.ToString(), result2.ToString());

}



}  // namespace leveldb
