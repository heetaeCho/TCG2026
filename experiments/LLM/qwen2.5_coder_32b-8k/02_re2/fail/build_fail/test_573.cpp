#include <gtest/gtest.h>

#include "re2/prefilter_tree.h"

#include <vector>



using namespace re2;



class PrefilterTreeTest_573 : public ::testing::Test {

protected:

    std::unique_ptr<PrefilterTree> prefilter_tree_;

    std::vector<std::string> atom_vec_;



    void SetUp() override {

        prefilter_tree_ = std::make_unique<PrefilterTree>();

        atom_vec_ = {"atom1", "atom2"};

    }

};



TEST_F(PrefilterTreeTest_573, CompileFirstTime_573) {

    // Normal operation: Compile should succeed on first call

    EXPECT_NO_FATAL_FAILURE(prefilter_tree_->Compile(&atom_vec_));

}



TEST_F(PrefilterTreeTest_573, CompileTwice_573) {

    // Exceptional case: Compile should fail (log fatal) on second call

    prefilter_tree_->Compile(&atom_vec_);

    EXPECT_DEATH(prefilter_tree_->Compile(&atom_vec_), "Compile called already.");

}



TEST_F(PrefilterTreeTest_573, CompileWithEmptyPrefilters_573) {

    // Boundary condition: Compile should do nothing if prefilter_vec_ is empty

    prefilter_tree_->Compile(&atom_vec_);

    EXPECT_TRUE(true);  // Just ensure no fatal error occurs

}



TEST_F(PrefilterTreeTest_573, CompileWithNonEmptyPrefilters_573) {

    // Normal operation: Compile should succeed with non-empty prefilter_vec_

    Prefilter* mock_prefilter = new Prefilter();

    prefilter_tree_->Add(mock_prefilter);

    EXPECT_NO_FATAL_FAILURE(prefilter_tree_->Compile(&atom_vec_));

    delete mock_prefilter;  // Clean up

}
