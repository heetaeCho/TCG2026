#include <gtest/gtest.h>
#include <unordered_map>
#include <unordered_set>

#include "glomap/scene/view_graph.h"
#include "glomap/scene/frame.h"
#include "glomap/scene/image.h"

using namespace glomap;

class ViewGraphTest_94 : public ::testing::Test {
protected:
    ViewGraph view_graph;

    Frame MakeFrame() {
        Frame f;
        f.cluster_id = -1;
        return f;
    }

    Image MakeImage() {
        Image img;
        return img;
    }
};
