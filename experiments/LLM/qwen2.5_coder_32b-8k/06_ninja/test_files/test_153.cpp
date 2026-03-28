#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming readCount is a function that we can mock since it's not part of the class but an external dependency

std::pair<int64_t, bool> readCount(const std::string& path);



class MockFileReader {

public:

    MOCK_METHOD1(readCountMock, std::pair<int64_t, bool>(const std::string& path));

};



std::pair<int64_t, bool> readCount(const std::string& path) {

    static MockFileReader mock;

    return mock.readCountMock(path);

}



TEST(ParseCgroupV1Test_153, NormalOperation_153) {

    MockFileReader* mock = new MockFileReader();

    EXPECT_CALL(*mock, readCountMock(::testing::EndsWith("/cpu.cfs_quota_us"))).WillOnce(::testing::Return(std::make_pair(200000LL, true)));

    EXPECT_CALL(*mock, readCountMock(::testing::EndsWith("/cpu.cfs_period_us"))).WillOnce(::testing::Return(std::make_pair(100000LL, true)));



    std::string path = "/some/path";

    int result = ParseCgroupV1(path);

    EXPECT_EQ(result, 2);



    delete mock;

}



TEST(ParseCgroupV1Test_153, QuotaReadFailure_153) {

    MockFileReader* mock = new MockFileReader();

    EXPECT_CALL(*mock, readCountMock(::testing::EndsWith("/cpu.cfs_quota_us"))).WillOnce(::testing::Return(std::make_pair(200000LL, false)));

    EXPECT_CALL(*mock, readCountMock(::testing::EndsWith("/cpu.cfs_period_us"))).Times(0);



    std::string path = "/some/path";

    int result = ParseCgroupV1(path);

    EXPECT_EQ(result, -1);



    delete mock;

}



TEST(ParseCgroupV1Test_153, QuotaValueNegative_153) {

    MockFileReader* mock = new MockFileReader();

    EXPECT_CALL(*mock, readCountMock(::testing::EndsWith("/cpu.cfs_quota_us"))).WillOnce(::testing::Return(std::make_pair(-1LL, true)));

    EXPECT_CALL(*mock, readCountMock(::testing::EndsWith("/cpu.cfs_period_us"))).Times(0);



    std::string path = "/some/path";

    int result = ParseCgroupV1(path);

    EXPECT_EQ(result, -1);



    delete mock;

}



TEST(ParseCgroupV1Test_153, PeriodReadFailure_153) {

    MockFileReader* mock = new MockFileReader();

    EXPECT_CALL(*mock, readCountMock(::testing::EndsWith("/cpu.cfs_quota_us"))).WillOnce(::testing::Return(std::make_pair(200000LL, true)));

    EXPECT_CALL(*mock, readCountMock(::testing::EndsWith("/cpu.cfs_period_us"))).WillOnce(::testing::Return(std::make_pair(100000LL, false)));



    std::string path = "/some/path";

    int result = ParseCgroupV1(path);

    EXPECT_EQ(result, -1);



    delete mock;

}



TEST(ParseCgroupV1Test_153, PeriodValueZero_153) {

    MockFileReader* mock = new MockFileReader();

    EXPECT_CALL(*mock, readCountMock(::testing::EndsWith("/cpu.cfs_quota_us"))).WillOnce(::testing::Return(std::make_pair(200000LL, true)));

    EXPECT_CALL(*mock, readCountMock(::testing::EndsWith("/cpu.cfs_period_us"))).WillOnce(::testing::Return(std::make_pair(0LL, true)));



    std::string path = "/some/path";

    int result = ParseCgroupV1(path);

    EXPECT_EQ(result, -1);



    delete mock;

}



TEST(ParseCgroupV1Test_153, BothReadFailures_153) {

    MockFileReader* mock = new MockFileReader();

    EXPECT_CALL(*mock, readCountMock(::testing::EndsWith("/cpu.cfs_quota_us"))).WillOnce(::testing::Return(std::make_pair(200000LL, false)));

    EXPECT_CALL(*mock, readCountMock(::testing::EndsWith("/cpu.cfs_period_us"))).Times(0);



    std::string path = "/some/path";

    int result = ParseCgroupV1(path);

    EXPECT_EQ(result, -1);



    delete mock;

}
