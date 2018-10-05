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
    string testString = "  .data\n  constantC = 352";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_TRUE(testParser.parseStream());
}

TEST(declarationParserTest, constant_fail)
{
    string testString = ".data\nconstantA = H2";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(declarationParserTest, constant_fail_splitByEOL)
{
    string testString = ".data\nconstantA = \nH2";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(declarationParserTest, constant_fail_digitFirstChar)
{
    string testString = ".data\n3BonstantA = H2";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(declarationParserTest, label_pass)
{
    string testString = ".data\n    testLabel:";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_TRUE(testParser.parseStream());
}

TEST(declarationParserTest, label_fail_noColonChar)
{
    string testString = ".data\n    testLabel";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(declarationParserTest, label_fail_spaceBetweenTextAndColonChar)
{
    string testString = ".data\n    testLabel :";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(declarationParserTest, label_fail_digitFirstChar)
{
    string testString = ".data\n    44testLabel";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(declarationParserTest, layout_intLayout_word_pass)
{
    string testString = ".data\n    .word 10";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_TRUE(testParser.parseStream());
}

TEST(declarationParserTest, layout_intLayout_word_fail)
{
    string testString = ".data\n    .word A";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(declarationParserTest, layout_intLayout_half_pass)
{
    string testString = ".data\n    .half 4";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_TRUE(testParser.parseStream());
}

TEST(declarationParserTest, layout_intLayout_half_fail)
{
    string testString = ".data\n    .half @";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(declarationParserTest, layout_intLayout_byte_pass)
{
    string testString = ".data\n    .byte 1";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_TRUE(testParser.parseStream());
}

TEST(declarationParserTest, layout_intLayout_byte_fail)
{
    string testString = ".data\n    .byte byte";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(declarationParserTest, layout_intLayout_space_pass)
{
    string testString = ".data\n    .space 12";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_TRUE(testParser.parseStream());
}

TEST(declarationParserTest, layout_intLayout_space_fail)
{
    string testString = ".data\n    .space (10)";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(declarationParserTest, layout_intLayout_fail_invalidLayoutKeyword_1)
{
    string testString = ".data\n    .spice 10";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(declarationParserTest, layout_intLayout_fail_invalidLayoutKeyword_2)
{
    string testString = ".data\n    word 3";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(declarationParserTest, layout_stringLayout_ascii_pass)
{
    string testString = ".data\n    .ascii \"test string goes here\"";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_TRUE(testParser.parseStream());
}

TEST(declarationParserTest, layout_stringLayout_asciiz_pass)
{
    string testString = ".data\n    .asciiz \"test string with null terminator goes here\"";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_TRUE(testParser.parseStream());
}

TEST(declarationParserTest, layout_stringLayout_ascii_fail_missingClosingStringDelimChar)
{
    string testString = ".data\n    .ascii \"test string goes here";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(declarationParserTest, layout_stringLayout_asciiz_fail_missingOpeningStringDelimChar)
{
    string testString = ".data\n    .asciiz test string with null terminator goes here\"";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(declarationParserTest, layout_stringLayout_ascii_fail_missingBothStringDelimChars)
{
    string testString = ".data\n    .ascii test string goes here";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(declarationParserTest, layout_stringLayout_asciiz_fail_oddNumberOfStringDelimChars)
{
    string testString = ".data\n    .asciiz \"test string with null \"terminator goes here\"";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}














