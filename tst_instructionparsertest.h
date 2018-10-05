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

TEST(instructionParserTest, move_2_args_pass)
{
    string testString = "  .text\n  move $t6, $t2";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_TRUE(testParser.parseStream());
}

TEST(instructionParserTest, move_1_arg_pass)
{
    string testString = "  .text\n  mtlo $t2";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_TRUE(testParser.parseStream());
}

TEST(instructionParserTest, label_pass)
{
    string testString = ".text\n    testLabel:";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_TRUE(testParser.parseStream());
}

TEST(instructionParserTest, add_register_pass)
{
    string testString = "  .text\n  add $t5, $t4, $t3";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_TRUE(testParser.parseStream());
}

TEST(instructionParserTest, mult_pass)
{
    string testString = "  .text\n  mult $t5, $t4";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_TRUE(testParser.parseStream());
}

TEST(instructionParserTest, div_2_args_pass)
{
    string testString = "  .text\n  div $t5, $t4";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_TRUE(testParser.parseStream());
}

TEST(instructionParserTest, div_3_args_register_pass)
{
    string testString = "  .text\n  div $t5, $t4, $t7";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_TRUE(testParser.parseStream());
}

TEST(instructionParserTest, div_3_args_immediate_pass)
{
    string testString = "  .text\n  div $t5, $t4, 17";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_TRUE(testParser.parseStream());
}

TEST(instructionParserTest, and_3_args_register_pass)
{
    string testString = "  .text\n  and $t5, $t4, $t7";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_TRUE(testParser.parseStream());
}

TEST(instructionParserTest, and_3_args_immediate_pass)
{
    string testString = "  .text\n  and $t5, $t4, 17";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_TRUE(testParser.parseStream());
}

TEST(instructionParserTest, not_register_pass)
{
    string testString = "  .text\n  not $t5, $t4";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_TRUE(testParser.parseStream());
}

TEST(instructionParserTest, not_immediate_pass)
{
    string testString = "  .text\n  not $t5, 24";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_TRUE(testParser.parseStream());
}

TEST(instructionParserTest, jump_pass)
{
    string testString = "  .text\n  j Steve:";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_TRUE(testParser.parseStream());
}

TEST(instructionParserTest, branch_equal_register_pass)
{
    string testString = "  .text\n  beq $t2, $t6, success:";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_TRUE(testParser.parseStream());
}

TEST(instructionParserTest, branch_equal_immediate_pass)
{
    string testString = "  .text\n  beq $t2, 12, success:";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_TRUE(testParser.parseStream());
}

TEST(instructionParserTest, move_2_args_fail)
{
    string testString = "  .text\n  move $t6, t2";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(instructionParserTest, move_1_arg_fail)
{
    string testString = "  .text\n  mtlo 2";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(instructionParserTest, label_fail)
{
    string testString = ".text\n    testLabel___";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(instructionParserTest, add_register_fail)
{
    string testString = "  .text\n  add $t5, t4, $t3";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(instructionParserTest, mult_fail)
{
    string testString = "  .text\n  mult $t5, $@";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(instructionParserTest, div_2_args_fail)
{
    string testString = "  .text\n  div $t5, $t4, ";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(instructionParserTest, div_3_args_register_fail)
{
    string testString = "  .text\n  div alpha, $t4, $t7";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(instructionParserTest, div_3_args_immediate_fail)
{
    string testString = "  .text\n  div $t5, $t4, $$";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(instructionParserTest, and_3_args_register_fail)
{
    string testString = "  .text\n  and $t5, $t4, ";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(instructionParserTest, and_3_args_immediate_fail)
{
    string testString = "  .text\n  and $t5, $t4, 5/4";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(instructionParserTest, not_register_fail)
{
    string testString = "  .text\n  not $t5, $_";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(instructionParserTest, not_immediate_fail)
{
    string testString = "  .text\n  not $t5, //";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(instructionParserTest, jump_fail)
{
    string testString = "  .text\n  j ";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(instructionParserTest, branch_equal_register_fail)
{
    string testString = "  .text\n  beq $t2, $t6";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(instructionParserTest, branch_equal_immediate_fail)
{
    string testString = "  .text\n  beq $t2, 12, success$$";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}
