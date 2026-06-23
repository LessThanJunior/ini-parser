#include "parser.hpp"
#include <cstdint>
#include <gtest/gtest.h>
#include <stdexcept>

class ParserTest : public ::testing::Test {
protected:
    IniParser parser{"examples/config.ini"};
};

TEST_F(ParserTest, HasSectionReturnFalseWhenMissing){
    EXPECT_FALSE(parser.hasSection("window"));
}

TEST_F(ParserTest, HasKeyReturnFalseWhenMissing){
    EXPECT_FALSE(parser.hasKey("Window", "Widh"));
    EXPECT_FALSE(parser.hasKey("General", "Width"));
}

TEST_F(ParserTest, GetBoolAsInvalidType){
    EXPECT_THROW(parser.get<bool>("Window", "Width"), std::runtime_error);
}

TEST_F(ParserTest, UpdateValue){
    uint16_t width = parser.get<uint16_t>("Window", "Width");
    parser.set("Window", "Width", width + 1);
    EXPECT_EQ(width + 1, parser.get<uint16_t>("Window", "Width"));
}

TEST_F(ParserTest, DontModifyDataWhenMissingKey){
    EXPECT_THROW(parser.set("Window", "Widh", 1280), std::out_of_range);
    EXPECT_FALSE(parser.hasKey("Window", "Widh"));
    EXPECT_THROW(parser.set("General", "Width", 1280), std::out_of_range);
    EXPECT_FALSE(parser.hasKey("General", "Width"));
}