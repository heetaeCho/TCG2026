#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/image.hpp"

#include "exiv2/basicio.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte * data, size_t wcount), (override));

    MOCK_METHOD(size_t, read, (byte * buf, size_t rcount), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(bool, isopen, () const, (override));

    MOCK_METHOD(int, error, () const, (override));

};



class ImageFactoryTest_1104 : public ::testing::Test {

protected:

    MockBasicIo mockIo;

    ImageFactory imageFactory;

};



TEST_F(ImageFactoryTest_1104, GetType_SuccessfulOpenAndMatch_1104) {

    EXPECT_CALL(mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(mockIo, isopen()).WillRepeatedly(Return(true));



    for (const auto& r : Anonimous_id_0::registry) {

        if (r.imageType_ == ImageType::jpeg) {

            EXPECT_CALL(mockIo, read(_, _))

                .WillOnce([r](byte * buf, size_t rcount) -> size_t {

                    // Simulate reading data that matches the type

                    memcpy(buf, "JFIF", 4);

                    return 4;

                });

        } else {

            EXPECT_CALL(mockIo, read(_, _))

                .WillOnce(Return(0)); // Return 0 bytes read to simulate no match

        }

    }



    ImageType result = imageFactory.getType(mockIo);

    EXPECT_EQ(result, ImageType::jpeg);

}



TEST_F(ImageFactoryTest_1104, GetType_UnsuccessfulOpen_1104) {

    EXPECT_CALL(mockIo, open()).WillOnce(Return(-1));



    ImageType result = imageFactory.getType(mockIo);

    EXPECT_EQ(result, ImageType::none);

}



TEST_F(ImageFactoryTest_1104, GetType_NoMatchFound_1104) {

    EXPECT_CALL(mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(mockIo, isopen()).WillRepeatedly(Return(true));



    for (const auto& r : Anonimous_id_0::registry) {

        EXPECT_CALL(mockIo, read(_, _))

            .WillOnce(Return(0)); // Return 0 bytes read to simulate no match

    }



    ImageType result = imageFactory.getType(mockIo);

    EXPECT_EQ(result, ImageType::none);

}



TEST_F(ImageFactoryTest_1104, GetType_CloseCalledAfterOpen_1104) {

    EXPECT_CALL(mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(mockIo, isopen()).WillRepeatedly(Return(true));

    EXPECT_CALL(mockIo, close()).Times(1);



    for (const auto& r : Anonimous_id_0::registry) {

        if (r.imageType_ == ImageType::jpeg) {

            EXPECT_CALL(mockIo, read(_, _))

                .WillOnce([r](byte * buf, size_t rcount) -> size_t {

                    // Simulate reading data that matches the type

                    memcpy(buf, "JFIF", 4);

                    return 4;

                });

        } else {

            EXPECT_CALL(mockIo, read(_, _))

                .WillOnce(Return(0)); // Return 0 bytes read to simulate no match

        }

    }



    ImageType result = imageFactory.getType(mockIo);

    EXPECT_EQ(result, ImageType::jpeg);

}
