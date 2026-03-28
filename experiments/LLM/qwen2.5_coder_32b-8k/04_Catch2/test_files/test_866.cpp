#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/reporters/catch_reporter_json.cpp"

#include "./TestProjects/Catch2/src/catch2/catch_totals.hpp"

#include "./TestProjects/Catch2/src/catch2/internal/catch_jsonwriter.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::StrEq;



class MockJsonObjectWriter : public JsonObjectWriter {

public:

    MOCK_METHOD(JsonValueWriter, write, (StringRef key), (override));

};



TEST(writeCountsTest_866, WritesAllCountsCorrectly_866) {

    std::stringstream ss;

    MockJsonObjectWriter mockWriter(ss);

    JsonValueWriter mockValueWriter(mockWriter);



    EXPECT_CALL(mockWriter, write(StrEq("passed"_sr)))

        .WillOnce(testing::Return(ByMove(std::move(mockValueWriter))));

    EXPECT_CALL(mockWriter, write(StrEq("failed"_sr)))

        .WillOnce(testing::Return(ByMove(std::move(mockValueWriter))));

    EXPECT_CALL(mockWriter, write(StrEq("fail-but-ok"_sr)))

        .WillOnce(testing::Return(ByMove(std::move(mockValueWriter))));

    EXPECT_CALL(mockWriter, write(StrEq("skipped"_sr)))

        .WillOnce(testing::Return(ByMove(std::move(mockValueWriter))));



    Counts counts{10, 5, 3, 2};

    writeCounts(std::move(mockWriter), counts);

}



TEST(writeCountsTest_866, HandlesZeroCountsCorrectly_866) {

    std::stringstream ss;

    MockJsonObjectWriter mockWriter(ss);

    JsonValueWriter mockValueWriter(mockWriter);



    EXPECT_CALL(mockWriter, write(StrEq("passed"_sr)))

        .WillOnce(testing::Return(ByMove(std::move(mockValueWriter))));

    EXPECT_CALL(mockWriter, write(StrEq("failed"_sr)))

        .WillOnce(testing::Return(ByMove(std::move(mockValueWriter))));

    EXPECT_CALL(mockWriter, write(StrEq("fail-but-ok"_sr)))

        .WillOnce(testing::Return(ByMove(std::move(mockValueWriter))));

    EXPECT_CALL(mockWriter, write(StrEq("skipped"_sr)))

        .WillOnce(testing::Return(ByMove(std::move(mockValueWriter))));



    Counts counts{0, 0, 0, 0};

    writeCounts(std::move(mockWriter), counts);

}



TEST(writeCountsTest_866, WritesLargeCountsCorrectly_866) {

    std::stringstream ss;

    MockJsonObjectWriter mockWriter(ss);

    JsonValueWriter mockValueWriter(mockWriter);



    EXPECT_CALL(mockWriter, write(StrEq("passed"_sr)))

        .WillOnce(testing::Return(ByMove(std::move(mockValueWriter))));

    EXPECT_CALL(mockWriter, write(StrEq("failed"_sr)))

        .WillOnce(testing::Return(ByMove(std::move(mockValueWriter))));

    EXPECT_CALL(mockWriter, write(StrEq("fail-but-ok"_sr)))

        .WillOnce(testing::Return(ByMove(std::move(mockValueWriter))));

    EXPECT_CALL(mockWriter, write(StrEq("skipped"_sr)))

        .WillOnce(testing::Return(ByMove(std::move(mockValueWriter))));



    Counts counts{1000000, 999999, 500000, 250000};

    writeCounts(std::move(mockWriter), counts);

}
