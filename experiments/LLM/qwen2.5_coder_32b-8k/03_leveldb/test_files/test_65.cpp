#include <gtest/gtest.h>

#include "db/version_edit.h"



using namespace leveldb;



class VersionEditTest_65 : public ::testing::Test {

protected:

    VersionEdit version_edit_;

};



TEST_F(VersionEditTest_65, SetLastSequence_NormalOperation_65) {

    SequenceNumber seq = 12345;

    version_edit_.SetLastSequence(seq);

    // Since we cannot access private members directly, we rely on observable behavior.

    // Here, we assume that encoding and decoding can reflect the change.

    std::string encoded;

    version_edit_.EncodeTo(&encoded);



    VersionEdit decoded_version_edit;

    Status status = decoded_version_edit.DecodeFrom(Slice(encoded));

    ASSERT_TRUE(status.ok());

    

    // We check if the last sequence number is correctly set after decoding.

    // This assumes that DecodeFrom properly sets has_last_sequence_ and last_sequence_.

    std::string debug_string = decoded_version_edit.DebugString();

    EXPECT_NE(debug_string.find("Last sequence: 12345"), std::string::npos);

}



TEST_F(VersionEditTest_65, SetLastSequence_BoundaryCondition_65) {

    SequenceNumber max_seq = std::numeric_limits<SequenceNumber>::max();

    version_edit_.SetLastSequence(max_seq);

    std::string encoded;

    version_edit_.EncodeTo(&encoded);



    VersionEdit decoded_version_edit;

    Status status = decoded_version_edit.DecodeFrom(Slice(encoded));

    ASSERT_TRUE(status.ok());



    std::string debug_string = decoded_version_edit.DebugString();

    EXPECT_NE(debug_string.find("Last sequence: " + std::to_string(max_seq)), std::string::npos);

}



TEST_F(VersionEditTest_65, SetLastSequence_ZeroValue_65) {

    SequenceNumber zero_seq = 0;

    version_edit_.SetLastSequence(zero_seq);

    std::string encoded;

    version_edit_.EncodeTo(&encoded);



    VersionEdit decoded_version_edit;

    Status status = decoded_version_edit.DecodeFrom(Slice(encoded));

    ASSERT_TRUE(status.ok());



    std::string debug_string = decoded_version_edit.DebugString();

    EXPECT_NE(debug_string.find("Last sequence: 0"), std::string::npos);

}



TEST_F(VersionEditTest_65, Clear_ResetsLastSequence_65) {

    SequenceNumber seq = 12345;

    version_edit_.SetLastSequence(seq);

    version_edit_.Clear();



    std::string encoded;

    version_edit_.EncodeTo(&encoded);



    VersionEdit decoded_version_edit;

    Status status = decoded_version_edit.DecodeFrom(Slice(encoded));

    ASSERT_TRUE(status.ok());



    std::string debug_string = decoded_version_edit.DebugString();

    EXPECT_EQ(debug_string.find("Last sequence"), std::string::npos);

}
