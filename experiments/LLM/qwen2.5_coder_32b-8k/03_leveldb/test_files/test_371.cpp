#include <gtest/gtest.h>

#include "table/filter_block.h"

#include <string>



using namespace leveldb;



class MockFilterPolicy : public FilterPolicy {

public:

    MOCK_METHOD2(CreateFilter, void(const Slice* keys, int n, std::string* dst));

    MOCK_CONST_METHOD3(KeyMayMatch, bool(const Slice& key, const Slice& filter));

};



class FilterBlockBuilderTest_371 : public ::testing::Test {

protected:

    MockFilterPolicy mock_policy;

    FilterBlockBuilder builder;



    FilterBlockBuilderTest_371() : builder(&mock_policy) {}

};



TEST_F(FilterBlockBuilderTest_371, StartBlock_GeneratesFiltersForBoundaryOffsets_371) {

    EXPECT_CALL(mock_policy, CreateFilter).Times(2);

    builder.StartBlock(kFilterBase - 1); // This should not generate a filter

    builder.StartBlock(kFilterBase);     // This should generate one filter

    builder.StartBlock(2 * kFilterBase);   // This should generate another filter

}



TEST_F(FilterBlockBuilderTest_371, StartBlock_DoesNotGenerateFiltersForSameOffset_371) {

    EXPECT_CALL(mock_policy, CreateFilter).Times(1);

    builder.StartBlock(kFilterBase);

    builder.StartBlock(kFilterBase); // Should not generate a second filter for the same offset

}



TEST_F(FilterBlockBuilderTest_371, StartBlock_GeneratesFiltersForIncreasingOffsets_371) {

    EXPECT_CALL(mock_policy, CreateFilter).Times(5);

    for (size_t i = 1; i <= 5; ++i) {

        builder.StartBlock(i * kFilterBase); // Should generate a filter each time

    }

}



TEST_F(FilterBlockBuilderTest_371, StartBlock_NoFiltersGeneratedForDecreasingOffsets_371) {

    EXPECT_CALL(mock_policy, CreateFilter).Times(0);

    builder.StartBlock(2 * kFilterBase);

    builder.StartBlock(kFilterBase); // Should not generate a filter for a smaller offset

}



TEST_F(FilterBlockBuilderTest_371, StartBlock_NoFiltersGeneratedForZeroOffset_371) {

    EXPECT_CALL(mock_policy, CreateFilter).Times(0);

    builder.StartBlock(0); // Zero offset should not generate a filter

}
