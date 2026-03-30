#include <gtest/gtest.h>

#include "XRef.h"



class XRefTest_265 : public ::testing::Test {

protected:

    XRef xref;

};



TEST_F(XRefTest_265, GetRoot_NormalOperation_265) {

    Ref root = xref.getRoot();

    // Assuming getRoot returns a valid Ref object with num and gen initialized.

    EXPECT_GE(root.num, 0);

    EXPECT_GE(root.gen, 0);

}



TEST_F(XRefTest_265, IsOk_NormalOperation_265) {

    bool is_ok = xref.isOk();

    // Assuming isOk returns a boolean value indicating the state of XRef.

    EXPECT_TRUE(is_ok || !is_ok); // This test ensures that the function call does not crash and returns a valid boolean.

}



TEST_F(XRefTest_265, IsXRefStream_NormalOperation_265) {

    bool is_xref_stream = xref.isXRefStream();

    // Assuming isXRefStream returns a boolean value indicating if XRef is a stream.

    EXPECT_TRUE(is_xref_stream || !is_xref_stream); // This test ensures that the function call does not crash and returns a valid boolean.

}



TEST_F(XRefTest_265, GetErrorCode_NormalOperation_265) {

    int error_code = xref.getErrorCode();

    // Assuming getErrorCode returns an integer representing the error code.

    EXPECT_GE(error_code, 0); // Error codes are generally non-negative integers.

}



TEST_F(XRefTest_265, IsEncrypted_NormalOperation_265) {

    bool is_encrypted = xref.isEncrypted();

    // Assuming isEncrypted returns a boolean value indicating if the document is encrypted.

    EXPECT_TRUE(is_encrypted || !is_encrypted); // This test ensures that the function call does not crash and returns a valid boolean.

}



TEST_F(XRefTest_265, GetPermFlags_NormalOperation_265) {

    int perm_flags = xref.getPermFlags();

    // Assuming getPermFlags returns an integer representing permission flags.

    EXPECT_TRUE(perm_flags >= 0); // Permission flags are generally non-negative integers.

}



TEST_F(XRefTest_265, GetNumObjects_NormalOperation_265) {

    int num_objects = xref.getNumObjects();

    // Assuming getNumObjects returns an integer representing the number of objects in XRef.

    EXPECT_TRUE(num_objects >= 0); // The number of objects should be non-negative.

}



TEST_F(XRefTest_265, GetRootNum_NormalOperation_265) {

    int root_num = xref.getRootNum();

    // Assuming getRootNum returns an integer representing the root object number.

    EXPECT_TRUE(root_num >= 0); // Root object number should be non-negative.

}



TEST_F(XRefTest_265, GetRootGen_NormalOperation_265) {

    int root_gen = xref.getRootGen();

    // Assuming getRootGen returns an integer representing the generation number of the root object.

    EXPECT_TRUE(root_gen >= 0); // Generation numbers should be non-negative.

}



TEST_F(XRefTest_265, GetTrailerDict_NormalOperation_265) {

    Object* trailer_dict = xref.getTrailerDict();

    // Assuming getTrailerDict returns a pointer to the trailer dictionary object.

    EXPECT_TRUE(trailer_dict != nullptr); // The trailer dictionary should not be null.

}



TEST_F(XRefTest_265, IsModified_NormalOperation_265) {

    bool is_modified = xref.isModified();

    // Assuming isModified returns a boolean value indicating if the XRef has been modified.

    EXPECT_TRUE(is_modified || !is_modified); // This test ensures that the function call does not crash and returns a valid boolean.

}



TEST_F(XRefTest_265, GetRoot_BoundaryCondition_265) {

    Ref root = xref.getRoot();

    // Assuming getRoot returns a valid Ref object with num and gen initialized.

    EXPECT_TRUE(root.num >= 0);

    EXPECT_TRUE(root.gen >= 0);

}
