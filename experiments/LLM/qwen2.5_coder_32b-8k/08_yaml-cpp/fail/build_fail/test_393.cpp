#include <gtest/gtest.h>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox {



using namespace detail::stdr;



struct CacheEntry {

    uint_least64_t value;

};



TEST_F(DragonboxComputeDeltaTest_393, NormalOperation_393) {
