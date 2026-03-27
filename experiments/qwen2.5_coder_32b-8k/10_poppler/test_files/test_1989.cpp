#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "DCTStream.h"



class MockJpegSourceMgr : public jpeg_source_mgr {

public:

    MOCK_METHOD(void, fill_input_buffer, (j_decompress_ptr), ());

};



struct str_src_mgr_test : str_src_mgr {

    MockJpegSourceMgr mock_pub;

};



TEST(str_skip_input_data_Test_1989, SkipZeroBytes_1989) {

    j_decompress_struct cinfo{};

    str_src_mgr_test src{};

    cinfo.src = (jpeg_source_mgr*)&src.mock_pub;



    src.pub.bytes_in_buffer = 100;

    src.pub.next_input_byte = &src.buffer;



    str_skip_input_data(&cinfo, 0);



    EXPECT_EQ(src.pub.next_input_byte, &src.buffer);

    EXPECT_EQ(src.pub.bytes_in_buffer, 100);

}



TEST(str_skip_input_data_Test_1989, SkipLessThanBuffer_1989) {

    j_decompress_struct cinfo{};

    str_src_mgr_test src{};

    cinfo.src = (jpeg_source_mgr*)&src.mock_pub;



    src.pub.bytes_in_buffer = 100;

    src.pub.next_input_byte = &src.buffer;



    str_skip_input_data(&cinfo, 50);



    EXPECT_EQ(src.pub.next_input_byte, &src.buffer + 50);

    EXPECT_EQ(src.pub.bytes_in_buffer, 50);

}



TEST(str_skip_input_data_Test_1989, SkipExactBuffer_1989) {

    j_decompress_struct cinfo{};

    str_src_mgr_test src{};

    cinfo.src = (jpeg_source_mgr*)&src.mock_pub;



    src.pub.bytes_in_buffer = 100;

    src.pub.next_input_byte = &src.buffer;



    str_skip_input_data(&cinfo, 100);



    EXPECT_EQ(src.pub.next_input_byte, &src.buffer + 100);

    EXPECT_EQ(src.pub.bytes_in_buffer, 0);

}



TEST(str_skip_input_data_Test_1989, SkipMoreThanBuffer_1989) {

    j_decompress_struct cinfo{};

    str_src_mgr_test src{};

    cinfo.src = (jpeg_source_mgr*)&src.mock_pub;



    src.pub.bytes_in_buffer = 50;

    src.pub.next_input_byte = &src.buffer;



    EXPECT_CALL(src.mock_pub, fill_input_buffer(&cinfo)).Times(1);



    str_skip_input_data(&cinfo, 100);



    EXPECT_EQ(src.pub.next_input_byte, &src.buffer + 100);

    EXPECT_EQ(src.pub.bytes_in_buffer, 0);

}



TEST(str_skip_input_data_Test_1989, SkipMultipleBuffers_1989) {

    j_decompress_struct cinfo{};

    str_src_mgr_test src{};

    cinfo.src = (jpeg_source_mgr*)&src.mock_pub;



    src.pub.bytes_in_buffer = 50;

    src.pub.next_input_byte = &src.buffer;



    EXPECT_CALL(src.mock_pub, fill_input_buffer(&cinfo)).Times(3);



    str_skip_input_data(&cinfo, 200);



    EXPECT_EQ(src.pub.next_input_byte, &src.buffer + 200);

    EXPECT_EQ(src.pub.bytes_in_buffer, 0);

}



TEST(str_skip_input_data_Test_1989, SkipNegativeBytes_1989) {

    j_decompress_struct cinfo{};

    str_src_mgr_test src{};

    cinfo.src = (jpeg_source_mgr*)&src.mock_pub;



    src.pub.bytes_in_buffer = 100;

    src.pub.next_input_byte = &src.buffer;



    str_skip_input_data(&cinfo, -50);



    EXPECT_EQ(src.pub.next_input_byte, &src.buffer);

    EXPECT_EQ(src.pub.bytes_in_buffer, 100);

}
