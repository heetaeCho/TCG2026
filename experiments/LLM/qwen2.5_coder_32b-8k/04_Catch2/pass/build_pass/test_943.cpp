#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the provided function is part of a utility class or namespace

namespace Catch { namespace Detail {



template <typename ForwardIter, typename Sentinel, typename T, typename Comparator>

constexpr ForwardIter find_sentinel(ForwardIter start, Sentinel sentinel, T const& value, Comparator cmp) {

    while (start != sentinel) {

        if (cmp(*start, value)) {

            break;

        }

        ++start;

    }

    return start;

}



} } // namespace Catch::Detail



// Mock comparator for testing

class MockComparator {

public:

    MOCK_CONST_METHOD2(compare, bool(const int&, const int&));

};



TEST(find_sentinel_Test_943, NormalOperation_943) {

    std::vector<int> vec = {1, 2, 3, 4, 5};

    MockComparator mock_cmp;

    

    EXPECT_CALL(mock_cmp, compare(1, 3)).WillOnce(testing::Return(false));

    EXPECT_CALL(mock_cmp, compare(2, 3)).WillOnce(testing::Return(false));

    EXPECT_CALL(mock_cmp, compare(3, 3)).WillOnce(testing::Return(true));



    auto result = Catch::Detail::find_sentinel(vec.begin(), vec.end(), 3, [&mock_cmp](const int& a, const int& b) {

        return mock_cmp.compare(a, b);

    });



    EXPECT_EQ(*result, 3);

}



TEST(find_sentinel_Test_943, BoundaryCondition_StartEqualsEnd_943) {

    std::vector<int> vec = {1, 2, 3, 4, 5};

    MockComparator mock_cmp;



    auto result = Catch::Detail::find_sentinel(vec.end(), vec.end(), 3, [&mock_cmp](const int& a, const int& b) {

        return mock_cmp.compare(a, b);

    });



    EXPECT_EQ(result, vec.end());

}



TEST(find_sentinel_Test_943, BoundaryCondition_ValueNotFound_943) {

    std::vector<int> vec = {1, 2, 3, 4, 5};

    MockComparator mock_cmp;



    EXPECT_CALL(mock_cmp, compare(1, 6)).WillOnce(testing::Return(false));

    EXPECT_CALL(mock_cmp, compare(2, 6)).WillOnce(testing::Return(false));

    EXPECT_CALL(mock_cmp, compare(3, 6)).WillOnce(testing::Return(false));

    EXPECT_CALL(mock_cmp, compare(4, 6)).WillOnce(testing::Return(false));

    EXPECT_CALL(mock_cmp, compare(5, 6)).WillOnce(testing::Return(false));



    auto result = Catch::Detail::find_sentinel(vec.begin(), vec.end(), 6, [&mock_cmp](const int& a, const int& b) {

        return mock_cmp.compare(a, b);

    });



    EXPECT_EQ(result, vec.end());

}



TEST(find_sentinel_Test_943, ExceptionalCase_EmptyRange_943) {

    std::vector<int> vec;

    MockComparator mock_cmp;



    auto result = Catch::Detail::find_sentinel(vec.begin(), vec.end(), 3, [&mock_cmp](const int& a, const int& b) {

        return mock_cmp.compare(a, b);

    });



    EXPECT_EQ(result, vec.end());

}
