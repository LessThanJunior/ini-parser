#include "parser.hpp"
#include <cstdint>
#include <gtest/gtest.h>
#include <stdexcept>
#include "ini_exception.hpp"

class ParserTest : public ::testing::Test {
protected:
    IniParser parser{"examples/config.ini"};
    IniParser unformatted{"examples/unformatted.ini"};
};

TEST_F(ParserTest, HasSectionReturnFalseWhenMissing){
    EXPECT_FALSE(parser.hasSection("window"));
}

TEST_F(ParserTest, HasKeyReturnFalseWhenMissing){
    EXPECT_FALSE(parser.hasKey("Window", "Widh"));
    EXPECT_FALSE(parser.hasKey("General", "Width"));
}

TEST_F(ParserTest, InvalidTypeCasting){
    EXPECT_THROW(parser.get<bool>("Window", "Width"), TypeException);
    EXPECT_THROW(parser.get<const char*>("Window", "Width"), TypeException);
    EXPECT_NO_THROW(parser.get<std::string>("Window", "Width"));
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

TEST_F(ParserTest, ParseUnformattedFile){
    EXPECT_NO_THROW(unformatted);
    EXPECT_EQ(unformatted.get<uint16_t>("Window", "Width"), 1284);
}

TEST_F(ParserTest, CheckingCommentSection){
    EXPECT_EQ(parser.get<uint16_t>("Window","Height"), 720);
    parser.set("Window","Height",720);
}

TEST_F(ParserTest, ThrowExceptionWhenFileIsEmpty){
    EXPECT_THROW(IniParser("examples/empty.ini"), EmptyFileException);
}