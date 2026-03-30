#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/glomap/glomap/math/tree.cc"



using namespace glomap;

using testing::ElementsAre;



// Mock Image class to simulate behavior without accessing internal state

class MockImage : public Image {

public:

    MOCK_METHOD(bool, IsRegistered, (), (const));

};



TEST_F(MaximumSpanningTreeTest_61, SingleImage_ReturnsItself_61) {

    ViewGraph view_graph;

    std::unordered_map<image_t, Image> images = {{0, MockImage()}};

    std::unordered_map<image_t, image_t> parents;



    EXPECT_CALL(static_cast<const MockImage&>(images[0]), IsRegistered()).WillOnce(testing::Return(true));



    image_t result = MaximumSpanningTree(view_graph, images, parents, INLIER_RATIO);

    ASSERT_EQ(result, 0);

    ASSERT_TRUE(parents.empty());

}



TEST_F(MaximumSpanningTreeTest_61, TwoImages_ValidPair_ReturnsCorrectParent_61) {

    ViewGraph view_graph;

    view_graph.image_pairs = {{0, {0, 1, true, {}, 1.0}}};

    std::unordered_map<image_t, Image> images = {{0, MockImage()}, {1, MockImage()}};

    std::unordered_map<image_t, image_t> parents;



    EXPECT_CALL(static_cast<const MockImage&>(images[0]), IsRegistered()).WillOnce(testing::Return(true));

    EXPECT_CALL(static_cast<const MockImage&>(images[1]), IsRegistered()).WillOnce(testing::Return(true));



    image_t result = MaximumSpanningTree(view_graph, images, parents, INLIER_RATIO);

    ASSERT_EQ(result, 0);

    ASSERT_THAT(parents, ElementsAre(std::make_pair(1, 0)));

}



TEST_F(MaximumSpanningTreeTest_61, TwoImages_InvalidPair_ReturnsSingleImage_61) {

    ViewGraph view_graph;

    view_graph.image_pairs = {{0, {0, 1, false, {}, 1.0}}};

    std::unordered_map<image_t, Image> images = {{0, MockImage()}, {1, MockImage()}};

    std::unordered_map<image_t, image_t> parents;



    EXPECT_CALL(static_cast<const MockImage&>(images[0]), IsRegistered()).WillOnce(testing::Return(true));

    EXPECT_CALL(static_cast<const MockImage&>(images[1]), IsRegistered()).WillOnce(testing::Return(true));



    image_t result = MaximumSpanningTree(view_graph, images, parents, INLIER_RATIO);

    ASSERT_EQ(result, 0);

    ASSERT_TRUE(parents.empty());

}



TEST_F(MaximumSpanningTreeTest_61, MultipleImages_AllValidPairs_ReturnsCorrectParents_61) {

    ViewGraph view_graph;

    view_graph.image_pairs = {{0, {0, 1, true, {}, 1.0}}, {1, {1, 2, true, {}, 2.0}}, {2, {0, 2, true, {}, 3.0}}};

    std::unordered_map<image_t, Image> images = {{0, MockImage()}, {1, MockImage()}, {2, MockImage()}};

    std::unordered_map<image_t, image_t> parents;



    EXPECT_CALL(static_cast<const MockImage&>(images[0]), IsRegistered()).WillOnce(testing::Return(true)).WillOnce(testing::Return(true));

    EXPECT_CALL(static_cast<const MockImage&>(images[1]), IsRegistered()).WillOnce(testing::Return(true)).WillOnce(testing::Return(true));

    EXPECT_CALL(static_cast<const MockImage&>(images[2]), IsRegistered()).WillOnce(testing::Return(true)).WillOnce(testing::Return(true));



    image_t result = MaximumSpanningTree(view_graph, images, parents, INLIER_RATIO);

    ASSERT_EQ(result, 0);

    ASSERT_THAT(parents, testing::UnorderedElementsAre(std::make_pair(1, 0), std::make_pair(2, 0)));

}



TEST_F(MaximumSpanningTreeTest_61, MultipleImages_SomeInvalidPairs_ReturnsCorrectParents_61) {

    ViewGraph view_graph;

    view_graph.image_pairs = {{0, {0, 1, true, {}, 1.0}}, {1, {1, 2, false, {}, 2.0}}, {2, {0, 2, true, {}, 3.0}}};

    std::unordered_map<image_t, Image> images = {{0, MockImage()}, {1, MockImage()}, {2, MockImage()}};

    std::unordered_map<image_t, image_t> parents;



    EXPECT_CALL(static_cast<const MockImage&>(images[0]), IsRegistered()).WillOnce(testing::Return(true)).WillOnce(testing::Return(true));

    EXPECT_CALL(static_cast<const MockImage&>(images[1]), IsRegistered()).WillOnce(testing::Return(true));

    EXPECT_CALL(static_cast<const MockImage&>(images[2]), IsRegistered()).WillOnce(testing::Return(true));



    image_t result = MaximumSpanningTree(view_graph, images, parents, INLIER_RATIO);

    ASSERT_EQ(result, 0);

    ASSERT_THAT(parents, testing::UnorderedElementsAre(std::make_pair(1, 0), std::make_pair(2, 0)));

}



TEST_F(MaximumSpanningTreeTest_61, MultipleImages_UnregisteredImage_ReturnsCorrectParents_61) {

    ViewGraph view_graph;

    view_graph.image_pairs = {{0, {0, 1, true, {}, 1.0}}, {1, {1, 2, true, {}, 2.0}}, {2, {0, 2, true, {}, 3.0}}};

    std::unordered_map<image_t, Image> images = {{0, MockImage()}, {1, MockImage()}, {2, MockImage()}};

    std::unordered_map<image_t, image_t> parents;



    EXPECT_CALL(static_cast<const MockImage&>(images[0]), IsRegistered()).WillOnce(testing::Return(true)).WillOnce(testing::Return(true));

    EXPECT_CALL(static_cast<const MockImage&>(images[1]), IsRegistered()).WillOnce(testing::Return(false));

    EXPECT_CALL(static_cast<const MockImage&>(images[2]), IsRegistered()).WillOnce(testing::Return(true));



    image_t result = MaximumSpanningTree(view_graph, images, parents, INLIER_RATIO);

    ASSERT_EQ(result, 0);

    ASSERT_THAT(parents, testing::UnorderedElementsAre(std::make_pair(2, 0)));

}
