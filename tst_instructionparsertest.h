#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "parser.h"

using namespace testing;

//TEST(instructionParserTest, constructorTest)
//{
//}

TEST(instructionParserTest, load_word_register_pass)
{
    string testString = "  .text\n  lw $t5, $t4";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_TRUE(testParser.parseStream());
}

TEST(instructionParserTest, load_word_register_fail)
{
    string testString = "  .text\n  lw $t5, _t4";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(instructionParserTest, load_word_offset_register_pass)
{
    string testString = "  .text\n  lw $t5, 8($t4)";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_TRUE(testParser.parseStream());
}

TEST(instructionParserTest, load_word_offset_register_fail)
{
    string testString = "  .text\n  lw $t5, 8$t4)";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(instructionParserTest, label_pass)
{
    string testString = ".text\n    testLabel:";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_TRUE(testParser.parseStream());
}














