#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <colmap/util/timer.h>

#include <colmap/database/database.h>

#include <glomap/scene/view_graph.h>

#include <glomap/controllers/option_manager.h>

#include <glomap/controllers/global_mapper.h>

#include <string>

#include <unordered_map>



namespace glomap {

namespace {



using ::testing::_;

using ::testing::Return;

using ::testing::MockFunction;



class MockDatabase : public colmap::Database {

public:

    MOCK_METHOD(void, Read, (const std::string& path), (override));

};



TEST_F(RunMapperResumeTest_59, NormalOperationWithBinaryOutput_59) {

    int argc = 7;

    char* argv[] = { "program", "--input_path", "/path/to/input", "--output_path", "/path/to/output", "--image_path", "/path/to/image" };

    

    OptionManager options(true);

    EXPECT_CALL(options, Parse(argc, argv)).Times(1);



    MockDatabase mock_db;

    ViewGraph view_graph;

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<camera_t, Camera> cameras;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;

    std::unordered_map<track_t, Track> tracks;



    EXPECT_CALL(mock_db, Read("/path/to/input")).Times(1);



    GlobalMapper global_mapper(*options.mapper);

    colmap::Timer run_timer;

    run_timer.Start();

    bool result = global_mapper.Solve(mock_db, view_graph, rigs, cameras, frames, images, tracks);

    run_timer.Pause();



    EXPECT_TRUE(result);

}



TEST_F(RunMapperResumeTest_59, NormalOperationWithTextOutput_59) {

    int argc = 8;

    char* argv[] = { "program", "--input_path", "/path/to/input", "--output_path", "/path/to/output", "--image_path", "/path/to/image", "--output_format", "txt" };

    

    OptionManager options(true);

    EXPECT_CALL(options, Parse(argc, argv)).Times(1);



    MockDatabase mock_db;

    ViewGraph view_graph;

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<camera_t, Camera> cameras;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;

    std::unordered_map<track_t, Track> tracks;



    EXPECT_CALL(mock_db, Read("/path/to/input")).Times(1);



    GlobalMapper global_mapper(*options.mapper);

    colmap::Timer run_timer;

    run_timer.Start();

    bool result = global_mapper.Solve(mock_db, view_graph, rigs, cameras, frames, images, tracks);

    run_timer.Pause();



    EXPECT_TRUE(result);

}



TEST_F(RunMapperResumeTest_59, InputPathNotDirectory_59) {

    int argc = 7;

    char* argv[] = { "program", "--input_path", "/path/to/nonexistent", "--output_path", "/path/to/output", "--image_path", "/path/to/image" };

    

    OptionManager options(true);

    EXPECT_CALL(options, Parse(argc, argv)).Times(1);



    EXPECT_EQ(RunMapperResume(argc, argv), EXIT_FAILURE);

}



TEST_F(RunMapperResumeTest_59, InvalidOutputFormat_59) {

    int argc = 8;

    char* argv[] = { "program", "--input_path", "/path/to/input", "--output_path", "/path/to/output", "--image_path", "/path/to/image", "--output_format", "invalid" };

    

    OptionManager options(true);

    EXPECT_CALL(options, Parse(argc, argv)).Times(1);



    EXPECT_EQ(RunMapperResume(argc, argv), EXIT_FAILURE);

}



TEST_F(RunMapperResumeTest_59, MissingRequiredOptions_59) {

    int argc = 3;

    char* argv[] = { "program", "--input_path", "/path/to/input" };

    

    OptionManager options(true);

    EXPECT_CALL(options, Parse(argc, argv)).Times(1);



    EXPECT_EQ(RunMapperResume(argc, argv), EXIT_FAILURE);

}



TEST_F(RunMapperResumeTest_59, ValidOptionsButParseFailure_59) {

    int argc = 7;

    char* argv[] = { "program", "--input_path", "/path/to/input", "--output_path", "/path/to/output", "--image_path", "/path/to/image" };

    

    OptionManager options(true);

    EXPECT_CALL(options, Parse(argc, argv)).WillOnce(testing::Throw(std::runtime_error("Parse error")));



    EXPECT_EQ(RunMapperResume(argc, argv), EXIT_FAILURE);

}



}  // namespace

}  // namespace glomap
