#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "global_mapper.cc"

#include "option_manager.h"

#include "view_graph.h"

#include "global_positioning.h"

#include "global_mapper.h"



using namespace glomap;

using ::testing::_;

using ::testing::NiceMock;



// Mock OptionManager for testing

class MockOptionManager : public OptionManager {

public:

    MOCK_METHOD(void, AddRequiredOption, (const std::string &, std::string *, const std::string &), (override));

    MOCK_METHOD(void, AddDefaultOption, (const std::string &, std::string *, const std::string &), (override));

    MOCK_METHOD(void, Parse, (int argc, char ** argv), (override));

};



// Mock GlobalMapper for testing Solve method

class MockGlobalMapper : public GlobalMapper {

public:

    using GlobalMapper::GlobalMapper;

    MOCK_METHOD(bool, Solve, (const colmap::Database &, ViewGraph &, std::unordered_map<rig_t, Rig> &, 

                              std::unordered_map<camera_t, Camera> &, std::unordered_map<frame_t, Frame> &, 

                              std::unordered_map<image_t, Image> &, std::unordered_map<track_t, Track> &), (override));

};



// Test fixture for RunMapper function

class RunMapperTest_58 : public ::testing::Test {

protected:

    MockOptionManager mock_option_manager;

    GlobalMapperOptions mapper_options;

    MockGlobalMapper mock_global_mapper{mapper_options};

    std::string database_path = "test_database.db";

    std::string output_path = "output.bin";



    void SetUp() override {

        char* argv[] = {const_cast<char*>("dummy"), const_cast<char*>("--database_path=test_database.db"),

                        const_cast<char*>("--output_path=output.bin")};

        mock_option_manager.AddRequiredOption("database_path", &database_path, "");

        mock_option_manager.AddRequiredOption("output_path", &output_path, "");

        mock_option_manager.Parse(3, argv);

    }

};



TEST_F(RunMapperTest_58, NormalOperation_58) {

    EXPECT_CALL(mock_option_manager, AddRequiredOption(_, _, _)).Times(2);

    EXPECT_CALL(mock_option_manager, Parse(_, _));



    colmap::Database database(database_path);

    ViewGraph view_graph;

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<camera_t, Camera> cameras;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;

    std::unordered_map<track_t, Track> tracks;



    EXPECT_CALL(mock_global_mapper, Solve(_, _, _, _, _, _, _)).WillOnce(::testing::Return(true));



    int result = RunMapper(3, nullptr);

    EXPECT_EQ(result, EXIT_SUCCESS);

}



TEST_F(RunMapperTest_58, InvalidDatabasePath_58) {

    EXPECT_CALL(mock_option_manager, AddRequiredOption(_, _, _)).Times(2);

    EXPECT_CALL(mock_option_manager, Parse(_, _));



    database_path = "nonexistent.db";



    int result = RunMapper(3, nullptr);

    EXPECT_EQ(result, EXIT_FAILURE);

}



TEST_F(RunMapperTest_58, InvalidConstraintType_58) {

    EXPECT_CALL(mock_option_manager, AddRequiredOption(_, _, _)).Times(2);

    EXPECT_CALL(mock_option_manager, Parse(_, _));



    char* argv[] = {const_cast<char*>("dummy"), const_cast<char*>("--database_path=test_database.db"),

                    const_cast<char*>("--output_path=output.bin"), const_cast<char*>("--constraint_type=INVALID_TYPE")};

    mock_option_manager.Parse(4, argv);



    int result = RunMapper(4, nullptr);

    EXPECT_EQ(result, EXIT_FAILURE);

}



TEST_F(RunMapperTest_58, InvalidOutputFormat_58) {

    EXPECT_CALL(mock_option_manager, AddRequiredOption(_, _, _)).Times(2);

    EXPECT_CALL(mock_option_manager, Parse(_, _));



    char* argv[] = {const_cast<char*>("dummy"), const_cast<char*>("--database_path=test_database.db"),

                    const_cast<char*>("--output_path=output.bin"), const_cast<char*>("--output_format=invalid")};

    mock_option_manager.Parse(4, argv);



    int result = RunMapper(4, nullptr);

    EXPECT_EQ(result, EXIT_FAILURE);

}



TEST_F(RunMapperTest_58, NoImagePairs_58) {

    EXPECT_CALL(mock_option_manager, AddRequiredOption(_, _, _)).Times(2);

    EXPECT_CALL(mock_option_manager, Parse(_, _));



    colmap::Database database(database_path);

    ViewGraph view_graph;

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<camera_t, Camera> cameras;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;

    std::unordered_map<track_t, Track> tracks;



    EXPECT_CALL(mock_global_mapper, Solve(_, _, _, _, _, _, _)).WillOnce(::testing::Return(false));



    int result = RunMapper(3, nullptr);

    EXPECT_EQ(result, EXIT_FAILURE);

}
