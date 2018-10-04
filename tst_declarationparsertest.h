#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "parser.h"

using namespace testing;

//TEST(declarationParserTest, constructorTest)
//{
//}

TEST(declarationParserTest, constant_pass)
{
    parser testParser;
    string testString = "  .data\n  constantC = 352";

    stringstream testSS;
    testSS << testString;

    EXPECT_TRUE(testParser.parseStream(testSS));
}

TEST(declarationParserTest, constant_fail)
{
    parser testParser;
    string testString = ".data\nconstantA = H2";

    stringstream testSS;
    testSS << testString;

    EXPECT_FALSE(testParser.parseStream(testSS));
}

TEST(declarationParserTest, constant_fail_splitByEOL)
{
    parser testParser;
    string testString = ".data\nconstantA = \nH2";

    stringstream testSS;
    testSS << testString;

    EXPECT_FALSE(testParser.parseStream(testSS));
}

TEST(declarationParserTest, constant_fail_digitFirstChar)
{
    parser testParser;
    string testString = ".data\n3BonstantA = H2";

    stringstream testSS;
    testSS << testString;

    EXPECT_FALSE(testParser.parseStream(testSS));
}

TEST(declarationParserTest, label_pass)
{
    parser testParser;
    string testString = ".data\n    testLabel:";

    stringstream testSS;
    testSS << testString;

    EXPECT_TRUE(testParser.parseStream(testSS));
}

TEST(declarationParserTest, label_fail_noColonChar)
{
    parser testParser;
    string testString = ".data\n    testLabel";

    stringstream testSS;
    testSS << testString;

    EXPECT_FALSE(testParser.parseStream(testSS));
}

TEST(declarationParserTest, label_fail_spaceBetweenTextAndColonChar)
{
    parser testParser;
    string testString = ".data\n    testLabel :";

    stringstream testSS;
    testSS << testString;

    EXPECT_FALSE(testParser.parseStream(testSS));
}

TEST(declarationParserTest, label_fail_digitFirstChar)
{
    parser testParser;
    string testString = ".data\n    44testLabel";

    stringstream testSS;
    testSS << testString;

    EXPECT_FALSE(testParser.parseStream(testSS));
}

TEST(declarationParserTest, layout_intLayout_word_pass)
{
    parser testParser;
    string testString = ".data\n    .word 10";

    stringstream testSS;
    testSS << testString;

    EXPECT_TRUE(testParser.parseStream(testSS));
}

TEST(declarationParserTest, layout_intLayout_word_fail)
{
    parser testParser;
    string testString = ".data\n    .word A";

    stringstream testSS;
    testSS << testString;

    EXPECT_FALSE(testParser.parseStream(testSS));
}

TEST(declarationParserTest, layout_intLayout_half_pass)
{
    parser testParser;
    string testString = ".data\n    .half 4";

    stringstream testSS;
    testSS << testString;

    EXPECT_TRUE(testParser.parseStream(testSS));
}

TEST(declarationParserTest, layout_intLayout_half_fail)
{
    parser testParser;
    string testString = ".data\n    .half @";

    stringstream testSS;
    testSS << testString;

    EXPECT_FALSE(testParser.parseStream(testSS));
}

TEST(declarationParserTest, layout_intLayout_byte_pass)
{
    parser testParser;
    string testString = ".data\n    .byte 1";

    stringstream testSS;
    testSS << testString;

    EXPECT_TRUE(testParser.parseStream(testSS));
}

TEST(declarationParserTest, layout_intLayout_byte_fail)
{
    parser testParser;
    string testString = ".data\n    .byte byte";

    stringstream testSS;
    testSS << testString;

    EXPECT_FALSE(testParser.parseStream(testSS));
}

TEST(declarationParserTest, layout_intLayout_space_pass)
{
    parser testParser;
    string testString = ".data\n    .space 12";

    stringstream testSS;
    testSS << testString;

    EXPECT_TRUE(testParser.parseStream(testSS));
}

TEST(declarationParserTest, layout_intLayout_space_fail)
{
    parser testParser;
    string testString = ".data\n    .space (10)";

    stringstream testSS;
    testSS << testString;

    EXPECT_FALSE(testParser.parseStream(testSS));
}

TEST(declarationParserTest, layout_intLayout_fail_invalidLayoutKeyword_1)
{
    parser testParser;
    string testString = ".data\n    .spice 10";

    stringstream testSS;
    testSS << testString;

    EXPECT_FALSE(testParser.parseStream(testSS));
}

TEST(declarationParserTest, layout_intLayout_fail_invalidLayoutKeyword_2)
{
    parser testParser;
    string testString = ".data\n    word 3";

    stringstream testSS;
    testSS << testString;

    EXPECT_FALSE(testParser.parseStream(testSS));
}

TEST(declarationParserTest, layout_stringLayout_ascii_pass)
{
    parser testParser;
    string testString = ".data\n    .ascii \"test string goes here\"";

    stringstream testSS;
    testSS << testString;

    EXPECT_TRUE(testParser.parseStream(testSS));
}

TEST(declarationParserTest, layout_stringLayout_asciiz_pass)
{
    parser testParser;
    string testString = ".data\n    .asciiz \"test string with null terminator goes here\"";

    stringstream testSS;
    testSS << testString;

    EXPECT_TRUE(testParser.parseStream(testSS));
}

TEST(declarationParserTest, layout_stringLayout_ascii_fail_missingClosingStringDelimChar)
{
    parser testParser;
    string testString = ".data\n    .ascii \"test string goes here";

    stringstream testSS;
    testSS << testString;

    EXPECT_FALSE(testParser.parseStream(testSS));
}

TEST(declarationParserTest, layout_stringLayout_asciiz_fail_missingOpeningStringDelimChar)
{
    parser testParser;
    string testString = ".data\n    .asciiz test string with null terminator goes here\"";

    stringstream testSS;
    testSS << testString;

    EXPECT_FALSE(testParser.parseStream(testSS));
}

TEST(declarationParserTest, layout_stringLayout_ascii_fail_missingBothStringDelimChars)
{
    parser testParser;
    string testString = ".data\n    .ascii test string goes here";

    stringstream testSS;
    testSS << testString;

    EXPECT_FALSE(testParser.parseStream(testSS));
}

TEST(declarationParserTest, layout_stringLayout_asciiz_fail_oddNumberOfStringDelimChars)
{
    parser testParser;
    string testString = ".data\n    .asciiz \"test string with null \"terminator goes here\"";

    stringstream testSS;
    testSS << testString;

    EXPECT_FALSE(testParser.parseStream(testSS));
}

//TODO: failing these integer unit tests, so I need to figure out if I'm dropping a token somewhere due to iterators.

TEST(declarationParserTest, integer_unsigned_pass)
{
    parser testParser;
    string testString = ".data\n    100";

    stringstream testSS;
    testSS << testString;

    EXPECT_TRUE(testParser.parseStream(testSS));
}

TEST(declarationParserTest, integer_positiveSign_pass)
{
    parser testParser;
    string testString = ".data\n    +55";

    stringstream testSS;
    testSS << testString;

    EXPECT_TRUE(testParser.parseStream(testSS));
}

TEST(declarationParserTest, integer_negativeSign_pass)
{
    parser testParser;
    string testString = ".data\n    -822";

    stringstream testSS;
    testSS << testString;

    EXPECT_TRUE(testParser.parseStream(testSS));
}
















