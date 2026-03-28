#include <gtest/gtest.h>

#include "table/format.h"

#include "leveldb/slice.h"



namespace leveldb {



class FooterTest_399 : public ::testing::Test {

protected:

    Footer footer;

};



TEST_F(FooterTest_399, DecodeFrom_SuccessfulDecode_399) {

    std::string data = "SomeInitialData";

    uint64_t magic_number = kTableMagicNumber;

    data.append(reinterpret_cast<const char*>(&magic_number), sizeof(magic_number));

    BlockHandle bh1, bh2;

    std::string encoded_bh1, encoded_bh2;

    bh1.EncodeTo(&encoded_bh1);

    bh2.EncodeTo(&encoded_bh2);

    data.insert(data.size() - 8, encoded_bh2);

    data.insert(data.size() - 8 - encoded_bh2.size(), encoded_bh1);



    Slice slice(data.data(), data.size());

    Status status = footer.DecodeFrom(&slice);



    EXPECT_TRUE(status.ok());

}



TEST_F(FooterTest_399, DecodeFrom_TooShortInput_399) {

    std::string data = "TooShort";

    Slice slice(data.data(), data.size());

    Status status = footer.DecodeFrom(&slice);



    EXPECT_EQ(Status::Corruption("not an sstable (footer too short)").code(), status.code());

}



TEST_F(FooterTest_399, DecodeFrom_BadMagicNumber_399) {

    std::string data = "SomeInitialData";

    uint64_t bad_magic_number = kTableMagicNumber + 1;

    data.append(reinterpret_cast<const char*>(&bad_magic_number), sizeof(bad_magic_number));

    BlockHandle bh1, bh2;

    std::string encoded_bh1, encoded_bh2;

    bh1.EncodeTo(&encoded_bh1);

    bh2.EncodeTo(&encoded_bh2);

    data.insert(data.size() - 8, encoded_bh2);

    data.insert(data.size() - 8 - encoded_bh2.size(), encoded_bh1);



    Slice slice(data.data(), data.size());

    Status status = footer.DecodeFrom(&slice);



    EXPECT_EQ(Status::Corruption("not an sstable (bad magic number)").code(), status.code());

}



TEST_F(FooterTest_399, DecodeFrom_MetaindexDecodeFailure_399) {

    std::string data = "SomeInitialData";

    uint64_t magic_number = kTableMagicNumber;

    data.append(reinterpret_cast<const char*>(&magic_number), sizeof(magic_number));

    BlockHandle bh1, bh2;

    bh1.set_offset(~static_cast<uint64_t>(0)); // Invalid offset

    std::string encoded_bh1, encoded_bh2;

    bh1.EncodeTo(&encoded_bh1);

    bh2.EncodeTo(&encoded_bh2);

    data.insert(data.size() - 8, encoded_bh2);

    data.insert(data.size() - 8 - encoded_bh2.size(), encoded_bh1);



    Slice slice(data.data(), data.size());

    Status status = footer.DecodeFrom(&slice);



    EXPECT_FALSE(status.ok());

}



TEST_F(FooterTest_399, DecodeFrom_IndexDecodeFailure_399) {

    std::string data = "SomeInitialData";

    uint64_t magic_number = kTableMagicNumber;

    data.append(reinterpret_cast<const char*>(&magic_number), sizeof(magic_number));

    BlockHandle bh1, bh2;

    bh2.set_offset(~static_cast<uint64_t>(0)); // Invalid offset

    std::string encoded_bh1, encoded_bh2;

    bh1.EncodeTo(&encoded_bh1);

    bh2.EncodeTo(&encoded_bh2);

    data.insert(data.size() - 8, encoded_bh2);

    data.insert(data.size() - 8 - encoded_bh2.size(), encoded_bh1);



    Slice slice(data.data(), data.size());

    Status status = footer.DecodeFrom(&slice);



    EXPECT_FALSE(status.ok());

}



} // namespace leveldb
