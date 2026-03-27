#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "glomap/exe/rotation_averager.cc"

#include "glomap/controllers/option_manager.h"

#include "glomap/scene/view_graph.h"

#include "glomap/estimators/gravity_refinement.h"



using ::testing::_;

using ::testing::MockFunction;

using ::testing::NiceMock;



namespace glomap {



class MockGravityRefiner : public GravityRefiner {

public:

    MOCK_METHOD3(RefineGravity, void(const ViewGraph&, std::unordered_map<frame_t, Frame>&, std::unordered_map<image_t, Image>&));

};



class RotationAveragerTest_57 : public ::testing::Test {

protected:

    OptionManager options_{false};

    std::vector<char*> args_;

    MockGravityRefiner mock_gravity_refiner;

};



TEST_F(RotationAveragerTest_57, RequiredArgumentsMissing_57) {

    int argc = 1;

    char* argv[] = {strdup("rotation_averager")};

    EXPECT_EQ(RunRotationAverager(argc, argv), EXIT_FAILURE);

}



TEST_F(RotationAveragerTest_57, RelposePathNotFile_57) {

    args_.clear();

    args_.push_back(strdup("rotation_averager"));

    args_.push_back(strdup("--relpose_path=nonexistent_file.txt"));

    args_.push_back(strdup("--output_path=output_file.txt"));



    int argc = args_.size();

    char** argv = args_.data();



    EXPECT_EQ(RunRotationAverager(argc, argv), EXIT_FAILURE);

}



TEST_F(RotationAveragerTest_57, GravityPathNotFile_57) {

    std::ofstream relpose_path("relpose_file.txt");

    relpose_path.close();



    args_.clear();

    args_.push_back(strdup("rotation_averager"));

    args_.push_back(strdup("--relpose_path=relpose_file.txt"));

    args_.push_back(strdup("--output_path=output_file.txt"));

    args_.push_back(strdup("--gravity_path=nonexistent_gravity_file.txt"));



    int argc = args_.size();

    char** argv = args_.data();



    EXPECT_EQ(RunRotationAverager(argc, argv), EXIT_FAILURE);

}



TEST_F(RotationAveragerTest_57, WeightPathNotFileWhenUseWeightTrue_57) {

    std::ofstream relpose_path("relpose_file.txt");

    relpose_path.close();



    args_.clear();

    args_.push_back(strdup("rotation_averager"));

    args_.push_back(strdup("--relpose_path=relpose_file.txt"));

    args_.push_back(strdup("--output_path=output_file.txt"));

    args_.push_back(strdup("--use_weight=true"));



    int argc = args_.size();

    char** argv = args_.data();



    EXPECT_EQ(RunRotationAverager(argc, argv), EXIT_FAILURE);

}



TEST_F(RotationAveragerTest_57, WeightPathProvidedWhenUseWeightFalse_57) {

    std::ofstream relpose_path("relpose_file.txt");

    relpose_path.close();

    std::ofstream weight_path("weight_file.txt");

    weight_path.close();



    args_.clear();

    args_.push_back(strdup("rotation_averager"));

    args_.push_back(strdup("--relpose_path=relpose_file.txt"));

    args_.push_back(strdup("--output_path=output_file.txt"));

    args_.push_back(strdup("--weight_path=weight_file.txt"));



    int argc = args_.size();

    char** argv = args_.data();



    EXPECT_EQ(RunRotationAverager(argc, argv), EXIT_SUCCESS);

}



TEST_F(RotationAveragerTest_57, NormalOperation_57) {

    std::ofstream relpose_path("relpose_file.txt");

    relpose_path.close();

    std::ofstream output_path("output_file.txt");

    output_path.close();



    args_.clear();

    args_.push_back(strdup("rotation_averager"));

    args_.push_back(strdup("--relpose_path=relpose_file.txt"));

    args_.push_back(strdup("--output_path=output_file.txt"));



    int argc = args_.size();

    char** argv = args_.data();



    EXPECT_EQ(RunRotationAverager(argc, argv), EXIT_SUCCESS);

}



TEST_F(RotationAveragerTest_57, GravityRefinerCalledWhenRefineGravityTrue_57) {

    std::ofstream relpose_path("relpose_file.txt");

    relpose_path.close();

    std::ofstream gravity_path("gravity_file.txt");

    gravity_path.close();



    args_.clear();

    args_.push_back(strdup("rotation_averager"));

    args_.push_back(strdup("--relpose_path=relpose_file.txt"));

    args_.push_back(strdup("--output_path=output_file.txt"));

    args_.push_back(strdup("--gravity_path=gravity_file.txt"));

    args_.push_back(strdup("--refine_gravity=true"));



    int argc = args_.size();

    char** argv = args_.data();



    options_.AddGravityRefinerOptions();

    options_.Parse(argc, argv);



    EXPECT_CALL(mock_gravity_refiner, RefineGravity(_, _, _)).Times(1);

}



} // namespace glomap
