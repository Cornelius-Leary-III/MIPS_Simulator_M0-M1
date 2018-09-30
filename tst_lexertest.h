#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "lexer.h"

using namespace testing;

//class LexerTest : public ::testing::Test
//{
//protected:

//    void SetUp() override
//    {

//    }
//};


TEST(lexerTest, lexerTestSet)
{
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}

TEST(lexerTest, lexerConstructor)
{
    lexer testLexer;

    EXPECT_FALSE(testLexer.isStringDelimiterErrorPresent());
    EXPECT_FALSE(testLexer.isParenthesesErrorPresent());
    EXPECT_TRUE(testLexer.getTokens().empty());
}

TEST(lexerTest, emptyStream)
{
    std::stringstream testSS;
    testSS << "";

    lexer testLexer;
    testLexer.tokenizeStream(testSS);

    EXPECT_FALSE(testLexer.isStringDelimiterErrorPresent());
    EXPECT_FALSE(testLexer.isParenthesesErrorPresent());
    EXPECT_TRUE(testLexer.getTokens().empty());
}

TEST(lexerTest, onlyEOLChar)
{
    std::stringstream testSS;
    testSS << "\n";

    lexer testLexer;
    testLexer.tokenizeStream(testSS);

    EXPECT_FALSE(testLexer.isStringDelimiterErrorPresent());
    EXPECT_FALSE(testLexer.isParenthesesErrorPresent());

    EXPECT_FALSE(testLexer.getTokens().empty());
    EXPECT_EQ(testLexer.getTokens().size(), 1);

    EXPECT_EQ(testLexer.getTokens().front().type(), EOL);
    EXPECT_NE(testLexer.getTokens().back().type(), ERROR);
}

TEST(lexerTest, onlySEPChar)
{
    std::stringstream testSS;
    testSS << ",";

    lexer testLexer;
    testLexer.tokenizeStream(testSS);

    EXPECT_FALSE(testLexer.isStringDelimiterErrorPresent());
    EXPECT_FALSE(testLexer.isParenthesesErrorPresent());

    EXPECT_FALSE(testLexer.getTokens().empty());
    EXPECT_EQ(testLexer.getTokens().size(), 1);

    EXPECT_EQ(testLexer.getTokens().front().type(), SEP);
    EXPECT_NE(testLexer.getTokens().back().type(), ERROR);
}

TEST(lexerTest, onlyEQUALChar)
{
    std::stringstream testSS;
    testSS << "=";

    lexer testLexer;
    testLexer.tokenizeStream(testSS);

    EXPECT_FALSE(testLexer.isStringDelimiterErrorPresent());
    EXPECT_FALSE(testLexer.isParenthesesErrorPresent());

    EXPECT_FALSE(testLexer.getTokens().empty());
    EXPECT_EQ(testLexer.getTokens().size(), 1);

    EXPECT_EQ(testLexer.getTokens().front().type(), EQUAL);
    EXPECT_NE(testLexer.getTokens().back().type(), ERROR);
}

TEST(lexerTest, oneSTRING_DELIMCharOnly)
{
    std::stringstream testSS;
    testSS << "\"";

    lexer testLexer;
    testLexer.tokenizeStream(testSS);

    EXPECT_TRUE(testLexer.isStringDelimiterErrorPresent());
    EXPECT_FALSE(testLexer.isParenthesesErrorPresent());

    EXPECT_FALSE(testLexer.getTokens().empty());
    EXPECT_EQ(testLexer.getTokens().size(), 2);

    EXPECT_EQ(testLexer.getTokens().front().type(), STRING_DELIM);
    EXPECT_EQ(testLexer.getTokens().back().type(), ERROR);
    EXPECT_EQ(testLexer.getTokens().back().contents().substr(0, 7), "ERROR: ");
}

TEST(lexerTest, twoSTRING_DELIMCharsOnly)
{
    std::stringstream testSS;
    testSS << "\"\"";

    lexer testLexer;
    testLexer.tokenizeStream(testSS);

    EXPECT_FALSE(testLexer.isStringDelimiterErrorPresent());
    EXPECT_FALSE(testLexer.isParenthesesErrorPresent());

    auto tokenSet = testLexer.getTokens();
    EXPECT_FALSE(tokenSet.empty());
    EXPECT_EQ(tokenSet.size(), 2);

    auto tokensIter = tokenSet.begin();
    EXPECT_EQ(tokensIter->type(), STRING_DELIM);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), STRING_DELIM);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());
}

TEST(lexerTest, textMissingOneSTRING_DELIMChar)
{
    std::stringstream testSS;
    testSS << "\"test text goes here 12345!@?#$% 09876)(*&^";

    lexer testLexer;
    testLexer.tokenizeStream(testSS);

    EXPECT_TRUE(testLexer.isStringDelimiterErrorPresent());
    EXPECT_FALSE(testLexer.isParenthesesErrorPresent());

    auto tokenSet = testLexer.getTokens();
    EXPECT_FALSE(tokenSet.empty());
    EXPECT_EQ(tokenSet.size(), 3);

    auto tokensIter = tokenSet.begin();
    EXPECT_EQ(tokensIter->type(), STRING_DELIM);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), STRING);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_FALSE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), ERROR);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_EQ(tokensIter->contents().substr(0, 7), "ERROR: ");
}


TEST(lexerTest, textBetweenTwoSTRING_DELIMChars)
{
    std::stringstream testSS;
    testSS << "\"test text goes here 12345!@?#$% 09876)(*&^\"";

    lexer testLexer;
    testLexer.tokenizeStream(testSS);

    EXPECT_FALSE(testLexer.isStringDelimiterErrorPresent());
    EXPECT_FALSE(testLexer.isParenthesesErrorPresent());

    auto tokenSet = testLexer.getTokens();
    EXPECT_FALSE(tokenSet.empty());
    EXPECT_EQ(tokenSet.size(), 3);

    auto tokensIter = tokenSet.begin();
    EXPECT_EQ(tokensIter->type(), STRING_DELIM);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), STRING);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_FALSE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), STRING_DELIM);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());
}

TEST(lexerTest, onlyCommentChar)
{
    std::stringstream testSS;
    testSS << "#";

    lexer testLexer;
    testLexer.tokenizeStream(testSS);

    EXPECT_FALSE(testLexer.isStringDelimiterErrorPresent());
    EXPECT_FALSE(testLexer.isParenthesesErrorPresent());
    EXPECT_TRUE(testLexer.getTokens().empty());
}

TEST(lexerTest, oneOPEN_PARENCharOnly)
{
    std::stringstream testSS;
    testSS << "(";

    lexer testLexer;
    testLexer.tokenizeStream(testSS);

    EXPECT_FALSE(testLexer.isStringDelimiterErrorPresent());
    EXPECT_TRUE(testLexer.isParenthesesErrorPresent());

    auto tokenSet = testLexer.getTokens();
    EXPECT_FALSE(tokenSet.empty());
    EXPECT_EQ(tokenSet.size(), 2);

    auto tokensIter = tokenSet.begin();
    EXPECT_EQ(tokensIter->type(), OPEN_PAREN);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), ERROR);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_EQ(tokensIter->contents().substr(0, 7), "ERROR: ");
}

TEST(lexerTest, twoOPEN_PARENCharOnly)
{
    std::stringstream testSS;
    testSS << "((";

    lexer testLexer;
    testLexer.tokenizeStream(testSS);

    EXPECT_FALSE(testLexer.isStringDelimiterErrorPresent());
    EXPECT_TRUE(testLexer.isParenthesesErrorPresent());

    auto tokenSet = testLexer.getTokens();
    EXPECT_FALSE(tokenSet.empty());
    EXPECT_EQ(tokenSet.size(), 3);

    auto tokensIter = tokenSet.begin();
    EXPECT_EQ(tokensIter->type(), OPEN_PAREN);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), OPEN_PAREN);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), ERROR);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_EQ(tokensIter->contents().substr(0, 7), "ERROR: ");
}

TEST(lexerTest, twoCLOSE_PARENCharOnly)
{
    std::stringstream testSS;
    testSS << "))";

    lexer testLexer;
    testLexer.tokenizeStream(testSS);

    EXPECT_FALSE(testLexer.isStringDelimiterErrorPresent());
    EXPECT_TRUE(testLexer.isParenthesesErrorPresent());

    auto tokenSet = testLexer.getTokens();
    EXPECT_FALSE(tokenSet.empty());
    EXPECT_EQ(tokenSet.size(), 3);

    auto tokensIter = tokenSet.begin();
    EXPECT_EQ(tokensIter->type(), CLOSE_PAREN);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), CLOSE_PAREN);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), ERROR);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_EQ(tokensIter->contents().substr(0, 7), "ERROR: ");
}

TEST(lexerTest, parenthesesPairCorrectOrder)
{
    std::stringstream testSS;
    testSS << "()";

    lexer testLexer;
    testLexer.tokenizeStream(testSS);

    EXPECT_FALSE(testLexer.isStringDelimiterErrorPresent());
    EXPECT_FALSE(testLexer.isParenthesesErrorPresent());

    auto tokenSet = testLexer.getTokens();
    EXPECT_FALSE(tokenSet.empty());
    EXPECT_EQ(tokenSet.size(), 2);

    auto tokensIter = tokenSet.begin();
    EXPECT_EQ(tokensIter->type(), OPEN_PAREN);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), CLOSE_PAREN);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());
}

TEST(lexerTest, parenthesesPairReverseOrder)
{
    std::stringstream testSS;
    testSS << ")(";

    lexer testLexer;
    testLexer.tokenizeStream(testSS);

    EXPECT_FALSE(testLexer.isStringDelimiterErrorPresent());
    EXPECT_FALSE(testLexer.isParenthesesErrorPresent());

    auto tokenSet = testLexer.getTokens();
    EXPECT_FALSE(tokenSet.empty());
    EXPECT_EQ(tokenSet.size(), 2);

    auto tokensIter = tokenSet.begin();
    EXPECT_EQ(tokensIter->type(), CLOSE_PAREN);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), OPEN_PAREN);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());
}









