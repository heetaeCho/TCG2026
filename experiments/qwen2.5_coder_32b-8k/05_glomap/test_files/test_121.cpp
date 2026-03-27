#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <unordered_map>

#include "colmap/reconstruction.h"

#include "glomap/scene/track.h"

#include "glomap/io/colmap_converter.h"



using namespace glomap;

using namespace colmap;



class ColmapConverterTest_121 : public ::testing::Test {

protected:

    Reconstruction reconstruction;

    std::unordered_map<track_t, Track> tracks;



    void AddPoint3DToReconstruction(point3D_t point3d_id, const Eigen::Vector3d& xyz, const Eigen::Vector3ub& color, const std::vector<TrackElement>& elements) {

        colmap::Point3D point3D;

        point3D.xyz = xyz;

        point3D.color = color;

        for (const auto& element : elements) {

            point3D.track.AddElement(element);

        }

        reconstruction.AddPoint3D(point3D);

    }

};



TEST_F(ColmapConverterTest_121, EmptyReconstruction_121) {

    ConvertColmapPoints3DToGlomapTracks(reconstruction, tracks);

    EXPECT_TRUE(tracks.empty());

}



TEST_F(ColmapConverterTest_121, SinglePoint3D_121) {

    AddPoint3DToReconstruction(1, Eigen::Vector3d(1.0, 2.0, 3.0), Eigen::Vector3ub(255, 0, 0), {{1, 1}});

    ConvertColmapPoints3DToGlomapTracks(reconstruction, tracks);

    EXPECT_EQ(tracks.size(), 1);

    const auto& track = tracks[1];

    EXPECT_EQ(track.xyz, Eigen::Vector3d(1.0, 2.0, 3.0));

    EXPECT_EQ(track.color, Eigen::Vector3ub(255, 0, 0));

    EXPECT_TRUE(track.is_initialized);

    EXPECT_EQ(track.observations.size(), 1);

    EXPECT_EQ(track.observations[0], Observation(1, 1));

}



TEST_F(ColmapConverterTest_121, MultiplePoints3D_121) {

    AddPoint3DToReconstruction(1, Eigen::Vector3d(1.0, 2.0, 3.0), Eigen::Vector3ub(255, 0, 0), {{1, 1}});

    AddPoint3DToReconstruction(2, Eigen::Vector3d(4.0, 5.0, 6.0), Eigen::Vector3ub(0, 255, 0), {{2, 2}});

    ConvertColmapPoints3DToGlomapTracks(reconstruction, tracks);

    EXPECT_EQ(tracks.size(), 2);



    const auto& track1 = tracks[1];

    EXPECT_EQ(track1.xyz, Eigen::Vector3d(1.0, 2.0, 3.0));

    EXPECT_EQ(track1.color, Eigen::Vector3ub(255, 0, 0));

    EXPECT_TRUE(track1.is_initialized);

    EXPECT_EQ(track1.observations.size(), 1);

    EXPECT_EQ(track1.observations[0], Observation(1, 1));



    const auto& track2 = tracks[2];

    EXPECT_EQ(track2.xyz, Eigen::Vector3d(4.0, 5.0, 6.0));

    EXPECT_EQ(track2.color, Eigen::Vector3ub(0, 255, 0));

    EXPECT_TRUE(track2.is_initialized);

    EXPECT_EQ(track2.observations.size(), 1);

    EXPECT_EQ(track2.observations[0], Observation(2, 2));

}



TEST_F(ColmapConverterTest_121, Point3DWithMultipleObservations_121) {

    AddPoint3DToReconstruction(1, Eigen::Vector3d(1.0, 2.0, 3.0), Eigen::Vector3ub(255, 0, 0), {{1, 1}, {2, 2}});

    ConvertColmapPoints3DToGlomapTracks(reconstruction, tracks);

    EXPECT_EQ(tracks.size(), 1);



    const auto& track = tracks[1];

    EXPECT_EQ(track.xyz, Eigen::Vector3d(1.0, 2.0, 3.0));

    EXPECT_EQ(track.color, Eigen::Vector3ub(255, 0, 0));

    EXPECT_TRUE(track.is_initialized);

    EXPECT_EQ(track.observations.size(), 2);

    EXPECT_EQ(track.observations[0], Observation(1, 1));

    EXPECT_EQ(track.observations[1], Observation(2, 2));

}
