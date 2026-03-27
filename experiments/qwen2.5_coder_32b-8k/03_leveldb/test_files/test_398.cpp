#include <gtest/gtest.h>

#include "table/format.h"



namespace leveldb {



class FooterTest_398 : public ::testing::Test {

protected:

    Footer footer;

};



TEST_F(FooterTest_398, EncodeTo_NormalOperation_398) {

    std::string dst;

    footer.EncodeTo(&dst);

    EXPECT_EQ(dst.size(), Footer::kEncodedLength);

}



TEST_F(FooterTest_398, EncodeTo_BoundaryCondition_EmptyString_398) {

    std::string dst;

    dst.clear();

    footer.EncodeTo(&dst);

    EXPECT_EQ(dst.size(), Footer::kEncodedLength);

}



TEST_F(FooterTest_398, EncodeTo_VerifyMagicNumber_398) {

    std::string dst;

    footer.EncodeTo(&dst);

    uint64_t magic_number = DecodeFixed64(dst.data() + Footer::kEncodedLength - 8);

    EXPECT_EQ(magic_number, kTableMagicNumber);

}



TEST_F(FooterTest_398, EncodeTo_VerifyPadding_398) {

    std::string dst;

    footer.EncodeTo(&dst);

    for (size_t i = 2 * BlockHandle::kMaxEncodedLength; i < Footer::kEncodedLength - 8; ++i) {

        EXPECT_EQ(dst[i], '\0');

    }

}



TEST_F(FooterTest_398, EncodeTo_VerifyBlockHandles_398) {

    BlockHandle test_handle;

    test_handle.set_offset(12345);

    test_handle.set_size(67890);



    footer.set_metaindex_handle(test_handle);

    footer.set_index_handle(test_handle);



    std::string dst;

    footer.EncodeTo(&dst);



    std::string expected_dst;

    test_handle.EncodeTo(&expected_dst);

    expected_dst += expected_dst; // Append twice for metaindex and index handles

    expected_dst.resize(2 * BlockHandle::kMaxEncodedLength); // Padding



    uint64_t magic_number = kTableMagicNumber;

    PutFixed32(&expected_dst, static_cast<uint32_t>(magic_number & 0xffffffffu));

    PutFixed32(&expected_dst, static_cast<uint32_t>(magic_number >> 32));



    EXPECT_EQ(dst, expected_dst);

}



} // namespace leveldb
