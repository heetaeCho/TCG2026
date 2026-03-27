#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Link.h"

#include <memory>



class MockSound : public Sound {

public:

    MOCK_METHOD(void, someMethod, (), (override));

};



TEST_F(LinkSoundTest_315, IsOk_ReturnsTrueWhenSoundIsNotNull_315) {

    auto sound = std::make_unique<MockSound>();

    LinkSound linkSound(nullptr);

    linkSound.sound = std::move(sound);



    EXPECT_TRUE(linkSound.isOk());

}



TEST_F(LinkSoundTest_315, IsOk_ReturnsFalseWhenSoundIsNull_315) {

    LinkSound linkSound(nullptr);

    linkSound.sound = nullptr;



    EXPECT_FALSE(linkSound.isOk());

}

```


