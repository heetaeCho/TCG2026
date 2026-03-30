#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "glomap/scene/view_graph.h"

#include "glomap/estimators/global_rotation_averaging.h"



namespace glomap {

namespace testing {



using ::testing::UnorderedElementsAre;

using ::testing::Pair;



class RotationEstimatorTest_26 : public ::testing::Test {

protected:

    ViewGraph view_graph_;

    std::unordered_map<rig_t, Rig> rigs_;

    std::unordered_map<frame_t, Frame> frames_;

    std::unordered_map<image_t, Image> images_;

    RotationEstimatorOptions options_;

    RotationEstimator rotation_estimator_;



    RotationEstimatorTest_26()

        : options_(), rotation_estimator_(options_) {}



    void SetUp() override {

        // Setup initial state if necessary

    }

};



TEST_F(RotationEstimatorTest_26, EstimateRotations_Success_26) {

    // Arrange

    // Initialize view_graph_, rigs_, frames_, images_ with valid data



    // Act

    bool result = rotation_estimator_.EstimateRotations(view_graph_, rigs_, frames_, images_);



    // Assert

    EXPECT_TRUE(result);

}



TEST_F(RotationEstimatorTest_26, EstimateRotations_Gravity_NoSensor_26) {

    // Arrange

    options_.use_gravity = true;

    Rig rig_with_missing_sensor;

    rig_with_missing_sensor.NonRefSensors().insert({sensor_t(1), std::nullopt});

    rigs_.insert({rig_t(1), rig_with_missing_sensor});



    // Act & Assert

    EXPECT_FALSE(rotation_estimator_.EstimateRotations(view_graph_, rigs_, frames_, images_));

}



TEST_F(RotationEstimatorTest_26, EstimateRotations_L1Regression_Failure_26) {

    // Arrange

    options_.max_num_l1_iterations = 1;

    ON_CALL(*this, SolveL1Regression).WillByDefault(::testing::Return(false));



    // Act & Assert

    EXPECT_FALSE(rotation_estimator_.EstimateRotations(view_graph_, rigs_, frames_, images_));

}



TEST_F(RotationEstimatorTest_26, EstimateRotations_IRLS_Failure_26) {

    // Arrange

    options_.max_num_irls_iterations = 1;

    ON_CALL(*this, SolveIRLS).WillByDefault(::testing::Return(false));



    // Act & Assert

    EXPECT_FALSE(rotation_estimator_.EstimateRotations(view_graph_, rigs_, frames_, images_));

}



TEST_F(RotationEstimatorTest_26, EstimateRotations_NoIterations_26) {

    // Arrange

    options_.max_num_l1_iterations = 0;

    options_.max_num_irls_iterations = 0;



    // Act

    bool result = rotation_estimator_.EstimateRotations(view_graph_, rigs_, frames_, images_);



    // Assert

    EXPECT_TRUE(result);

}



TEST_F(RotationEstimatorTest_26, EstimateRotations_SkipInitialization_26) {

    // Arrange

    options_.skip_initialization = true;



    // Act

    bool result = rotation_estimator_.EstimateRotations(view_graph_, rigs_, frames_, images_);



    // Assert

    EXPECT_TRUE(result);

}



}  // namespace testing

}  // namespace glomap

```



**Note:** The above test cases assume that `SolveL1Regression` and `SolveIRLS` can be mocked, which they cannot based on the constraints. Since we cannot mock internal behavior or functions not passed as parameters, these tests should be revised to remove the mocking parts if it is strictly adhered to the given constraints. Here's a corrected version:



```cpp

#include <gtest/gtest.h>

#include "glomap/scene/view_graph.h"

#include "glomap/estimators/global_rotation_averaging.h"



namespace glomap {

namespace testing {



class RotationEstimatorTest_26 : public ::testing::Test {

protected:

    ViewGraph view_graph_;

    std::unordered_map<rig_t, Rig> rigs_;

    std::unordered_map<frame_t, Frame> frames_;

    std::unordered_map<image_t, Image> images_;

    RotationEstimatorOptions options_;

    RotationEstimator rotation_estimator_;



    RotationEstimatorTest_26()

        : options_(), rotation_estimator_(options_) {}



    void SetUp() override {

        // Setup initial state if necessary

    }

};



TEST_F(RotationEstimatorTest_26, EstimateRotations_Success_26) {

    // Arrange

    // Initialize view_graph_, rigs_, frames_, images_ with valid data



    // Act

    bool result = rotation_estimator_.EstimateRotations(view_graph_, rigs_, frames_, images_);



    // Assert

    EXPECT_TRUE(result);

}



TEST_F(RotationEstimatorTest_26, EstimateRotations_Gravity_NoSensor_26) {

    // Arrange

    options_.use_gravity = true;

    Rig rig_with_missing_sensor;

    rig_with_missing_sensor.NonRefSensors().insert({sensor_t(1), std::nullopt});

    rigs_.insert({rig_t(1), rig_with_missing_sensor});



    // Act & Assert

    EXPECT_FALSE(rotation_estimator_.EstimateRotations(view_graph_, rigs_, frames_, images_));

}



TEST_F(RotationEstimatorTest_26, EstimateRotations_NoIterations_26) {

    // Arrange

    options_.max_num_l1_iterations = 0;

    options_.max_num_irls_iterations = 0;



    // Act

    bool result = rotation_estimator_.EstimateRotations(view_graph_, rigs_, frames_, images_);



    // Assert

    EXPECT_TRUE(result);

}



TEST_F(RotationEstimatorTest_26, EstimateRotations_SkipInitialization_26) {

    // Arrange

    options_.skip_initialization = true;



    // Act

    bool result = rotation_estimator_.EstimateRotations(view_graph_, rigs_, frames_, images_);



    // Assert

    EXPECT_TRUE(result);

}



}  // namespace testing

}  // namespace glomap
