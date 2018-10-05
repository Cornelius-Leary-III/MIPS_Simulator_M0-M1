#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "lexer.h"

using namespace testing;

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
    EXPECT_EQ(testLexer.getTokens().front().id(), 1);
    EXPECT_EQ(testLexer.getTokens().front().line(), 1);
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
    EXPECT_EQ(testLexer.getTokens().size(), 2);

    EXPECT_EQ(testLexer.getTokens().front().type(), SEP);
    EXPECT_EQ(testLexer.getTokens().front().id(), 1);
    EXPECT_EQ(testLexer.getTokens().front().line(), 1);
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
    EXPECT_EQ(testLexer.getTokens().size(), 2);

    EXPECT_EQ(testLexer.getTokens().front().type(), EQUAL);
    EXPECT_EQ(testLexer.getTokens().front().id(), 1);
    EXPECT_EQ(testLexer.getTokens().front().line(), 1);
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
    EXPECT_EQ(testLexer.getTokens().size(), 3);

    EXPECT_EQ(testLexer.getTokens().front().type(), STRING_DELIM);
    EXPECT_EQ(testLexer.getTokens().front().id(), 1);
    EXPECT_EQ(testLexer.getTokens().front().line(), 1);
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
    EXPECT_EQ(tokenSet.size(), 3);

    auto tokensIter = tokenSet.begin();
    EXPECT_EQ(tokensIter->type(), STRING_DELIM);
    EXPECT_EQ(tokensIter->id(), 1);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), STRING_DELIM);
    EXPECT_EQ(tokensIter->id(), 2);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), EOL);
    EXPECT_EQ(tokensIter->id(), 3);
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
    EXPECT_EQ(tokenSet.size(), 4);

    auto tokensIter = tokenSet.begin();
    EXPECT_EQ(tokensIter->type(), STRING_DELIM);
    EXPECT_EQ(tokensIter->id(), 1);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), STRING);
    EXPECT_EQ(tokensIter->id(), 2);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_FALSE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), EOL);
    EXPECT_EQ(tokensIter->id(), 3);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), ERROR);
    EXPECT_EQ(tokensIter->id(), 4);
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
    EXPECT_EQ(tokenSet.size(), 4);

    auto tokensIter = tokenSet.begin();
    EXPECT_EQ(tokensIter->type(), STRING_DELIM);
    EXPECT_EQ(tokensIter->id(), 1);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), STRING);
    EXPECT_EQ(tokensIter->id(), 2);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_FALSE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), STRING_DELIM);
    EXPECT_EQ(tokensIter->id(), 3);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), EOL);
    EXPECT_EQ(tokensIter->id(), 4);
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

TEST(lexerTest, commentFollowedByEOL)
{
    std::stringstream testSS;
    testSS << "# test comment \n";

    lexer testLexer;
    testLexer.tokenizeStream(testSS);

    EXPECT_FALSE(testLexer.isStringDelimiterErrorPresent());
    EXPECT_FALSE(testLexer.isParenthesesErrorPresent());

    auto tokenSet = testLexer.getTokens();
    EXPECT_FALSE(tokenSet.empty());
    EXPECT_EQ(tokenSet.size(), 1);

    auto tokensIter = tokenSet.begin();
    EXPECT_EQ(tokensIter->type(), EOL);
    EXPECT_EQ(tokensIter->id(), 1);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());
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
    EXPECT_EQ(tokenSet.size(), 3);

    auto tokensIter = tokenSet.begin();
    EXPECT_EQ(tokensIter->type(), OPEN_PAREN);
    EXPECT_EQ(tokensIter->id(), 1);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), EOL);
    EXPECT_EQ(tokensIter->id(), 2);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), ERROR);
    EXPECT_EQ(tokensIter->id(), 3);
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
    EXPECT_EQ(tokenSet.size(), 4);

    auto tokensIter = tokenSet.begin();
    EXPECT_EQ(tokensIter->type(), OPEN_PAREN);
    EXPECT_EQ(tokensIter->id(), 1);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), OPEN_PAREN);
    EXPECT_EQ(tokensIter->id(), 2);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), EOL);
    EXPECT_EQ(tokensIter->id(), 3);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), ERROR);
    EXPECT_EQ(tokensIter->id(), 4);
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
    EXPECT_EQ(tokenSet.size(), 4);

    auto tokensIter = tokenSet.begin();
    EXPECT_EQ(tokensIter->type(), CLOSE_PAREN);
    EXPECT_EQ(tokensIter->id(), 1);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), CLOSE_PAREN);
    EXPECT_EQ(tokensIter->id(), 2);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), EOL);
    EXPECT_EQ(tokensIter->id(), 3);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), ERROR);
    EXPECT_EQ(tokensIter->id(), 4);
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
    EXPECT_EQ(tokenSet.size(), 3);

    auto tokensIter = tokenSet.begin();
    EXPECT_EQ(tokensIter->type(), OPEN_PAREN);
    EXPECT_EQ(tokensIter->id(), 1);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), CLOSE_PAREN);
    EXPECT_EQ(tokensIter->id(), 2);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), EOL);
    EXPECT_EQ(tokensIter->id(), 3);
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
    EXPECT_EQ(tokenSet.size(), 3);

    auto tokensIter = tokenSet.begin();
    EXPECT_EQ(tokensIter->type(), CLOSE_PAREN);
    EXPECT_EQ(tokensIter->id(), 1);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), OPEN_PAREN);
    EXPECT_EQ(tokensIter->id(), 2);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), EOL);
    EXPECT_EQ(tokensIter->id(), 3);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());
}

TEST(lexerTest, oneOPEN_PARENCharFollowedByEOL)
{
    std::stringstream testSS;
    testSS << "(\n";

    lexer testLexer;
    testLexer.tokenizeStream(testSS);

    EXPECT_FALSE(testLexer.isStringDelimiterErrorPresent());
    EXPECT_TRUE(testLexer.isParenthesesErrorPresent());

    auto tokenSet = testLexer.getTokens();
    EXPECT_FALSE(tokenSet.empty());
    EXPECT_EQ(tokenSet.size(), 3);

    auto tokensIter = tokenSet.begin();
    EXPECT_EQ(tokensIter->type(), OPEN_PAREN);
    EXPECT_EQ(tokensIter->id(), 1);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), EOL);
    EXPECT_EQ(tokensIter->id(), 2);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), ERROR);
    EXPECT_EQ(tokensIter->id(), 3);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_EQ(tokensIter->contents().substr(0, 7), "ERROR: ");
}

TEST(lexerTest, oneCLOSE_PARENCharFollowedByEOL)
{
    std::stringstream testSS;
    testSS << ")\n";

    lexer testLexer;
    testLexer.tokenizeStream(testSS);

    EXPECT_FALSE(testLexer.isStringDelimiterErrorPresent());
    EXPECT_TRUE(testLexer.isParenthesesErrorPresent());

    auto tokenSet = testLexer.getTokens();
    EXPECT_FALSE(tokenSet.empty());
    EXPECT_EQ(tokenSet.size(), 3);

    auto tokensIter = tokenSet.begin();
    EXPECT_EQ(tokensIter->type(), CLOSE_PAREN);
    EXPECT_EQ(tokensIter->id(), 1);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), EOL);
    EXPECT_EQ(tokensIter->id(), 2);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), ERROR);
    EXPECT_EQ(tokensIter->id(), 3);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_EQ(tokensIter->contents().substr(0, 7), "ERROR: ");
}

TEST(lexerTest, parenthesesPairSplitByEOL)
{
    std::stringstream testSS;
    testSS << "(\n)";

    lexer testLexer;
    testLexer.tokenizeStream(testSS);

    EXPECT_FALSE(testLexer.isStringDelimiterErrorPresent());
    EXPECT_TRUE(testLexer.isParenthesesErrorPresent());

    auto tokenSet = testLexer.getTokens();
    EXPECT_FALSE(tokenSet.empty());
    EXPECT_EQ(tokenSet.size(), 5);

    auto tokensIter = tokenSet.begin();
    EXPECT_EQ(tokensIter->type(), OPEN_PAREN);
    EXPECT_EQ(tokensIter->id(), 1);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), EOL);
    EXPECT_EQ(tokensIter->id(), 2);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), CLOSE_PAREN);
    EXPECT_EQ(tokensIter->id(), 3);
    EXPECT_EQ(tokensIter->line(), 2);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), EOL);
    EXPECT_EQ(tokensIter->id(), 4);
    EXPECT_EQ(tokensIter->line(), 2);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), ERROR);
    EXPECT_EQ(tokensIter->id(), 5);
    EXPECT_EQ(tokensIter->line(), 2);
    EXPECT_EQ(tokensIter->contents().substr(0, 7), "ERROR: ");
}

TEST(lexerTest, STRING_DELIMPairSplitByEOL)
{
    std::stringstream testSS;
    testSS << "\"\n\"";

    lexer testLexer;
    testLexer.tokenizeStream(testSS);

    EXPECT_TRUE(testLexer.isStringDelimiterErrorPresent());
    EXPECT_FALSE(testLexer.isParenthesesErrorPresent());

    auto tokenSet = testLexer.getTokens();
    EXPECT_FALSE(tokenSet.empty());
    EXPECT_EQ(tokenSet.size(), 5);

    auto tokensIter = tokenSet.begin();
    EXPECT_EQ(tokensIter->type(), STRING_DELIM);
    EXPECT_EQ(tokensIter->id(), 1);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), EOL);
    EXPECT_EQ(tokensIter->id(), 2);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), STRING_DELIM);
    EXPECT_EQ(tokensIter->id(), 3);
    EXPECT_EQ(tokensIter->line(), 2);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), EOL);
    EXPECT_EQ(tokensIter->id(), 4);
    EXPECT_EQ(tokensIter->line(), 2);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), ERROR);
    EXPECT_EQ(tokensIter->id(), 5);
    EXPECT_EQ(tokensIter->line(), 2);
    EXPECT_EQ(tokensIter->contents().substr(0, 7), "ERROR: ");
}

TEST(lexerTest, twoStrings)
{
    std::stringstream testSS;
    testSS << "test strings";

    lexer testLexer;
    testLexer.tokenizeStream(testSS);

    EXPECT_FALSE(testLexer.isStringDelimiterErrorPresent());
    EXPECT_FALSE(testLexer.isParenthesesErrorPresent());

    auto tokenSet = testLexer.getTokens();
    EXPECT_FALSE(tokenSet.empty());
    EXPECT_EQ(tokenSet.size(), 3);

    auto tokensIter = tokenSet.begin();
    EXPECT_EQ(tokensIter->type(), STRING);
    EXPECT_EQ(tokensIter->id(), 1);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_FALSE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), STRING);
    EXPECT_EQ(tokensIter->id(), 2);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_FALSE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), EOL);
    EXPECT_EQ(tokensIter->id(), 3);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());
}

TEST(lexerTest, fiveStrings)
{
    std::stringstream testSS;
    testSS << "test strings can be useful";

    lexer testLexer;
    testLexer.tokenizeStream(testSS);

    EXPECT_FALSE(testLexer.isStringDelimiterErrorPresent());
    EXPECT_FALSE(testLexer.isParenthesesErrorPresent());

    auto tokenSet = testLexer.getTokens();
    EXPECT_FALSE(tokenSet.empty());
    EXPECT_EQ(tokenSet.size(), 6);

    auto tokensIter = tokenSet.begin();
    EXPECT_EQ(tokensIter->type(), STRING);
    EXPECT_EQ(tokensIter->id(), 1);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_FALSE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), STRING);
    EXPECT_EQ(tokensIter->id(), 2);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_FALSE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), STRING);
    EXPECT_EQ(tokensIter->id(), 3);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_FALSE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), STRING);
    EXPECT_EQ(tokensIter->id(), 4);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_FALSE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), STRING);
    EXPECT_EQ(tokensIter->id(), 5);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_FALSE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), EOL);
    EXPECT_EQ(tokensIter->id(), 6);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());
}

TEST(lexerTest, fiveStringsSeparateLines)
{
    std::stringstream testSS;
    testSS << "test\nstrings\ncan\nbe\nuseful";

    lexer testLexer;
    testLexer.tokenizeStream(testSS);

    EXPECT_FALSE(testLexer.isStringDelimiterErrorPresent());
    EXPECT_FALSE(testLexer.isParenthesesErrorPresent());

    auto tokenSet = testLexer.getTokens();
    EXPECT_FALSE(tokenSet.empty());
    EXPECT_EQ(tokenSet.size(), 10);

    auto tokensIter = tokenSet.begin();
    EXPECT_EQ(tokensIter->type(), STRING);
    EXPECT_EQ(tokensIter->id(), 1);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_FALSE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), EOL);
    EXPECT_EQ(tokensIter->id(), 2);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), STRING);
    EXPECT_EQ(tokensIter->id(), 3);
    EXPECT_EQ(tokensIter->line(), 2);
    EXPECT_FALSE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), EOL);
    EXPECT_EQ(tokensIter->id(), 4);
    EXPECT_EQ(tokensIter->line(), 2);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), STRING);
    EXPECT_EQ(tokensIter->id(), 5);
    EXPECT_EQ(tokensIter->line(), 3);
    EXPECT_FALSE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), EOL);
    EXPECT_EQ(tokensIter->id(), 6);
    EXPECT_EQ(tokensIter->line(), 3);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), STRING);
    EXPECT_EQ(tokensIter->id(), 7);
    EXPECT_EQ(tokensIter->line(), 4);
    EXPECT_FALSE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), EOL);
    EXPECT_EQ(tokensIter->id(), 8);
    EXPECT_EQ(tokensIter->line(), 4);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), STRING);
    EXPECT_EQ(tokensIter->id(), 9);
    EXPECT_EQ(tokensIter->line(), 5);
    EXPECT_FALSE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), EOL);
    EXPECT_EQ(tokensIter->id(), 10);
    EXPECT_EQ(tokensIter->line(), 5);
    EXPECT_TRUE(tokensIter->contents().empty());
}

TEST(lexerTest, fiveStringsSeparateLinesEndsWithEOL)
{
    std::stringstream testSS;
    testSS << "test\nstrings\ncan\nbe\nuseful\n";

    lexer testLexer;
    testLexer.tokenizeStream(testSS);

    EXPECT_FALSE(testLexer.isStringDelimiterErrorPresent());
    EXPECT_FALSE(testLexer.isParenthesesErrorPresent());

    auto tokenSet = testLexer.getTokens();
    EXPECT_FALSE(tokenSet.empty());
    EXPECT_EQ(tokenSet.size(), 10);

    auto tokensIter = tokenSet.begin();
    EXPECT_EQ(tokensIter->type(), STRING);
    EXPECT_EQ(tokensIter->id(), 1);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_FALSE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), EOL);
    EXPECT_EQ(tokensIter->id(), 2);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), STRING);
    EXPECT_EQ(tokensIter->id(), 3);
    EXPECT_EQ(tokensIter->line(), 2);
    EXPECT_FALSE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), EOL);
    EXPECT_EQ(tokensIter->id(), 4);
    EXPECT_EQ(tokensIter->line(), 2);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), STRING);
    EXPECT_EQ(tokensIter->id(), 5);
    EXPECT_EQ(tokensIter->line(), 3);
    EXPECT_FALSE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), EOL);
    EXPECT_EQ(tokensIter->id(), 6);
    EXPECT_EQ(tokensIter->line(), 3);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), STRING);
    EXPECT_EQ(tokensIter->id(), 7);
    EXPECT_EQ(tokensIter->line(), 4);
    EXPECT_FALSE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), EOL);
    EXPECT_EQ(tokensIter->id(), 8);
    EXPECT_EQ(tokensIter->line(), 4);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), STRING);
    EXPECT_EQ(tokensIter->id(), 9);
    EXPECT_EQ(tokensIter->line(), 5);
    EXPECT_FALSE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), EOL);
    EXPECT_EQ(tokensIter->id(), 10);
    EXPECT_EQ(tokensIter->line(), 5);
    EXPECT_TRUE(tokensIter->contents().empty());

}

TEST(lexerTest, listOfStringsSeparatedByCommas)
{
    std::stringstream testSS;
    testSS << "test, strings,can, be,useful";

    lexer testLexer;
    testLexer.tokenizeStream(testSS);

    EXPECT_FALSE(testLexer.isStringDelimiterErrorPresent());
    EXPECT_FALSE(testLexer.isParenthesesErrorPresent());

    auto tokenSet = testLexer.getTokens();
    EXPECT_FALSE(tokenSet.empty());
    EXPECT_EQ(tokenSet.size(), 10);

    auto tokensIter = tokenSet.begin();
    EXPECT_EQ(tokensIter->type(), STRING);
    EXPECT_EQ(tokensIter->id(), 1);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_FALSE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), SEP);
    EXPECT_EQ(tokensIter->id(), 2);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), STRING);
    EXPECT_EQ(tokensIter->id(), 3);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_FALSE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), SEP);
    EXPECT_EQ(tokensIter->id(), 4);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), STRING);
    EXPECT_EQ(tokensIter->id(), 5);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_FALSE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), SEP);
    EXPECT_EQ(tokensIter->id(), 6);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), STRING);
    EXPECT_EQ(tokensIter->id(), 7);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_FALSE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), SEP);
    EXPECT_EQ(tokensIter->id(), 8);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), STRING);
    EXPECT_EQ(tokensIter->id(), 9);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_FALSE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), EOL);
    EXPECT_EQ(tokensIter->id(), 10);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());
}

TEST(lexerTest, multiplePairsOfParentheses)
{
    std::stringstream testSS;
    testSS << "((test) strings,can,) (((be,)useful)!)";

    lexer testLexer;
    testLexer.tokenizeStream(testSS);

    EXPECT_FALSE(testLexer.isStringDelimiterErrorPresent());
    EXPECT_FALSE(testLexer.isParenthesesErrorPresent());

    auto tokenSet = testLexer.getTokens();
    EXPECT_FALSE(tokenSet.empty());
    EXPECT_EQ(tokenSet.size(), 20);

    auto tokensIter = tokenSet.begin();
    EXPECT_EQ(tokensIter->type(), OPEN_PAREN);
    EXPECT_EQ(tokensIter->id(), 1);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), OPEN_PAREN);
    EXPECT_EQ(tokensIter->id(), 2);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), STRING);
    EXPECT_EQ(tokensIter->id(), 3);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_FALSE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), CLOSE_PAREN);
    EXPECT_EQ(tokensIter->id(), 4);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), STRING);
    EXPECT_EQ(tokensIter->id(), 5);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_FALSE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), SEP);
    EXPECT_EQ(tokensIter->id(), 6);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), STRING);
    EXPECT_EQ(tokensIter->id(), 7);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_FALSE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), SEP);
    EXPECT_EQ(tokensIter->id(), 8);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), CLOSE_PAREN);
    EXPECT_EQ(tokensIter->id(), 9);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), OPEN_PAREN);
    EXPECT_EQ(tokensIter->id(), 10);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), OPEN_PAREN);
    EXPECT_EQ(tokensIter->id(), 11);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), OPEN_PAREN);
    EXPECT_EQ(tokensIter->id(), 12);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), STRING);
    EXPECT_EQ(tokensIter->id(), 13);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_FALSE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), SEP);
    EXPECT_EQ(tokensIter->id(), 14);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), CLOSE_PAREN);
    EXPECT_EQ(tokensIter->id(), 15);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), STRING);
    EXPECT_EQ(tokensIter->id(), 16);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_FALSE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), CLOSE_PAREN);
    EXPECT_EQ(tokensIter->id(), 17);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), STRING);
    EXPECT_EQ(tokensIter->id(), 18);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_FALSE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), CLOSE_PAREN);
    EXPECT_EQ(tokensIter->id(), 19);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());

    EXPECT_EQ((++tokensIter)->type(), EOL);
    EXPECT_EQ(tokensIter->id(), 20);
    EXPECT_EQ(tokensIter->line(), 1);
    EXPECT_TRUE(tokensIter->contents().empty());
}
