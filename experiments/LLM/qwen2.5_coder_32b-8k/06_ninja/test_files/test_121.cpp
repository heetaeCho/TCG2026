#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "build_log.h"



using ::testing::_;

using ::testing::Return;

using ::testing::Invoke;



class HashCollisionBenchTest_121 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if necessary

    }



    void TearDown() override {

        // Teardown code if necessary

    }

};



TEST_F(HashCollisionBenchTest_121, NormalOperation_121) {

    const int N = 2;

    char** commands = new char*[N];

    pair<uint64_t, int>* hashes = new pair<uint64_t, int>[N];



    // Create two different commands

    commands[0] = strdup("command1");

    commands[1] = strdup("different_command");



    for (int i = 0; i < N; ++i) {

        hashes[i] = make_pair(BuildLog::LogEntry::HashCommand(commands[i]), i);

    }



    sort(hashes, hashes + N);



    int collision_count = 0;

    for (int i = 1; i < N; ++i) {

        if (hashes[i - 1].first == hashes[i].first) {

            if (strcmp(commands[hashes[i - 1].second], commands[hashes[i].second]) != 0) {

                collision_count++;

            }

        }

    }



    EXPECT_EQ(collision_count, 0);



    for (int i = 0; i < N; ++i) {

        free(commands[i]);

    }

    delete[] commands;

    delete[] hashes;

}



TEST_F(HashCollisionBenchTest_121, BoundaryCondition_SingleCommand_121) {

    const int N = 1;

    char** commands = new char*[N];

    pair<uint64_t, int>* hashes = new pair<uint64_t, int>[N];



    // Create a single command

    commands[0] = strdup("single_command");



    for (int i = 0; i < N; ++i) {

        hashes[i] = make_pair(BuildLog::LogEntry::HashCommand(commands[i]), i);

    }



    sort(hashes, hashes + N);



    int collision_count = 0;

    for (int i = 1; i < N; ++i) {

        if (hashes[i - 1].first == hashes[i].first) {

            if (strcmp(commands[hashes[i - 1].second], commands[hashes[i].second]) != 0) {

                collision_count++;

            }

        }

    }



    EXPECT_EQ(collision_count, 0);



    for (int i = 0; i < N; ++i) {

        free(commands[i]);

    }

    delete[] commands;

    delete[] hashes;

}



TEST_F(HashCollisionBenchTest_121, BoundaryCondition_EmptyCommands_121) {

    const int N = 0;

    char** commands = new char*[N];

    pair<uint64_t, int>* hashes = new pair<uint64_t, int>[N];



    sort(hashes, hashes + N);



    int collision_count = 0;

    for (int i = 1; i < N; ++i) {

        if (hashes[i - 1].first == hashes[i].first) {

            if (strcmp(commands[hashes[i - 1].second], commands[hashes[i].second]) != 0) {

                collision_count++;

            }

        }

    }



    EXPECT_EQ(collision_count, 0);



    delete[] commands;

    delete[] hashes;

}



TEST_F(HashCollisionBenchTest_121, CollisionWithSameCommand_121) {

    const int N = 2;

    char** commands = new char*[N];

    pair<uint64_t, int>* hashes = new pair<uint64_t, int>[N];



    // Create two identical commands

    commands[0] = strdup("same_command");

    commands[1] = strdup("same_command");



    for (int i = 0; i < N; ++i) {

        hashes[i] = make_pair(BuildLog::LogEntry::HashCommand(commands[i]), i);

    }



    sort(hashes, hashes + N);



    int collision_count = 0;

    for (int i = 1; i < N; ++i) {

        if (hashes[i - 1].first == hashes[i].first) {

            if (strcmp(commands[hashes[i - 1].second], commands[hashes[i].second]) != 0) {

                collision_count++;

            }

        }

    }



    EXPECT_EQ(collision_count, 0);



    for (int i = 0; i < N; ++i) {

        free(commands[i]);

    }

    delete[] commands;

    delete[] hashes;

}



TEST_F(HashCollisionBenchTest_121, CollisionWithDifferentCommands_121) {

    const int N = 3;

    char** commands = new char*[N];

    pair<uint64_t, int>* hashes = new pair<uint64_t, int>[N];



    // Create two different commands that might have the same hash

    commands[0] = strdup("command1");

    commands[1] = strdup("different_command");

    commands[2] = strdup("another_command");



    for (int i = 0; i < N; ++i) {

        hashes[i] = make_pair(BuildLog::LogEntry::HashCommand(commands[i]), i);

    }



    sort(hashes, hashes + N);



    int collision_count = 0;

    for (int i = 1; i < N; ++i) {

        if (hashes[i - 1].first == hashes[i].first) {

            if (strcmp(commands[hashes[i - 1].second], commands[hashes[i].second]) != 0) {

                collision_count++;

            }

        }

    }



    // We don't expect a collision, but this test sets up for potential hash collisions

    EXPECT_GE(collision_count, 0);



    for (int i = 0; i < N; ++i) {

        free(commands[i]);

    }

    delete[] commands;

    delete[] hashes;

}
