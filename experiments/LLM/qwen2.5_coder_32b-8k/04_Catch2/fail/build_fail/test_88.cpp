#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/catch_tostring.hpp"



namespace Catch {

    namespace Detail {

        class ReusableStringStreamMock : public ReusableStringStream {

        public:

            MOCK_METHOD(std::ostream&, get, (), (override));

            MOCK_METHOD(const std::string, str, (), (const, override));

            MOCK_METHOD(void, str, (const std::string &), (override));

            template<typename T>

            MOCK_METHOD(ReusableStringStream&, operator<<, (T const& value), (override));

        };

    }

}



using namespace Catch;

using namespace Catch::Detail;



class RangeToStringTest_88 : public ::testing::Test {

protected:

    void SetUp() override {

        mockStream = std::make_unique<ReusableStringStreamMock>();

        ON_CALL(*mockStream, get()).WillByDefault(testing::ReturnRef(os));

        ON_CALL(*mockStream, str()).WillByDefault(testing::Invoke(mockStream.get(), &ReusableStringStream::str));

        ON_CALL(*mockStream, str(testing::_)).WillByDefault(testing::Invoke(mockStream.get(), &ReusableStringStream::str));

    }



    std::unique_ptr<ReusableStringStreamMock> mockStream;

    std::ostringstream os;

};



TEST_F(RangeToStringTest_88, EmptyRange_88) {

    std::vector<int> vec;

    EXPECT_EQ(rangeToString(vec.begin(), vec.end()), "{ }");

}



TEST_F(RangeToStringTest_88, SingleElement_88) {

    std::vector<int> vec = {1};

    EXPECT_EQ(rangeToString(vec.begin(), vec.end()), "{ 1 }");

}



TEST_F(RangeToStringTest_88, MultipleElements_88) {

    std::vector<int> vec = {1, 2, 3};

    EXPECT_EQ(rangeToString(vec.begin(), vec.end()), "{ 1, 2, 3 }");

}



TEST_F(RangeToStringTest_88, DifferentTypes_88) {

    std::vector<std::string> vec = {"a", "b", "c"};

    EXPECT_EQ(rangeToString(vec.begin(), vec.end()), "{ \"a\", \"b\", \"c\" }");

}



TEST_F(RangeToStringTest_88, SentinelDifferentFromIterator_88) {

    std::array<int, 3> arr = {1, 2, 3};

    EXPECT_EQ(rangeToString(arr.begin(), arr.end()), "{ 1, 2, 3 }");

}
