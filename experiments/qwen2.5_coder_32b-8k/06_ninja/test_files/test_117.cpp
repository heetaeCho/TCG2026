#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/ninja/src/build_log.h"



using namespace testing;



// Fixture for BuildLog::LogEntry tests.

class LogEntryTest_117 : public ::testing::Test {

protected:

    using TimeStamp = int64_t; // Assuming TimeStamp is an alias for some integer type like int64_t

};



// Test normal operation of the equality operator.

TEST_F(LogEntryTest_117, EqualityOperator_NormalOperation_117) {

    BuildLog::LogEntry entry1("output", 12345, 10, 20, 100);

    BuildLog::LogEntry entry2("output", 12345, 10, 20, 100);



    EXPECT_TRUE(entry1 == entry2);

}



// Test boundary conditions of the equality operator with different outputs.

TEST_F(LogEntryTest_117, EqualityOperator_DifferentOutputs_117) {

    BuildLog::LogEntry entry1("output1", 12345, 10, 20, 100);

    BuildLog::LogEntry entry2("output2", 12345, 10, 20, 100);



    EXPECT_FALSE(entry1 == entry2);

}



// Test boundary conditions of the equality operator with different command hashes.

TEST_F(LogEntryTest_117, EqualityOperator_DifferentCommandHashes_117) {

    BuildLog::LogEntry entry1("output", 12345, 10, 20, 100);

    BuildLog::LogEntry entry2("output", 67890, 10, 20, 100);



    EXPECT_FALSE(entry1 == entry2);

}



// Test boundary conditions of the equality operator with different start times.

TEST_F(LogEntryTest_117, EqualityOperator_DifferentStartTimes_117) {

    BuildLog::LogEntry entry1("output", 12345, 10, 20, 100);

    BuildLog::LogEntry entry2("output", 12345, 15, 20, 100);



    EXPECT_FALSE(entry1 == entry2);

}



// Test boundary conditions of the equality operator with different end times.

TEST_F(LogEntryTest_117, EqualityOperator_DifferentEndTimes_117) {

    BuildLog::LogEntry entry1("output", 12345, 10, 20, 100);

    BuildLog::LogEntry entry2("output", 12345, 10, 25, 100);



    EXPECT_FALSE(entry1 == entry2);

}



// Test boundary conditions of the equality operator with different mtime values.

TEST_F(LogEntryTest_117, EqualityOperator_DifferentMTimes_117) {

    BuildLog::LogEntry entry1("output", 12345, 10, 20, 100);

    BuildLog::LogEntry entry2("output", 12345, 10, 20, 150);



    EXPECT_FALSE(entry1 == entry2);

}



// Test construction with single argument.

TEST_F(LogEntryTest_117, Constructor_SingleArgument_117) {

    BuildLog::LogEntry entry("output");



    EXPECT_EQ(entry.output, "output");

    EXPECT_EQ(entry.command_hash, 0);

    EXPECT_EQ(entry.start_time, 0);

    EXPECT_EQ(entry.end_time, 0);

    EXPECT_EQ(entry.mtime, 0);

}



// Test construction with all arguments.

TEST_F(LogEntryTest_117, Constructor_AllArguments_117) {

    BuildLog::LogEntry entry("output", 12345, 10, 20, 100);



    EXPECT_EQ(entry.output, "output");

    EXPECT_EQ(entry.command_hash, 12345);

    EXPECT_EQ(entry.start_time, 10);

    EXPECT_EQ(entry.end_time, 20);

    EXPECT_EQ(entry.mtime, 100);

}
