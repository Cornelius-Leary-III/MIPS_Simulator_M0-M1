#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "token.h"

using namespace testing;


TEST(tokenTest, tokenClassTypes)
{
    std::size_t testLine = 0;

    token testTokenEOL(EOL, testLine);
    EXPECT_EQ(testTokenEOL.type(), EOL);
    EXPECT_EQ(testTokenEOL.line(), 0);

    ++testLine;
    token testTokenSEP(SEP, testLine);
    EXPECT_EQ(testTokenSEP.type(), SEP);
    EXPECT_EQ(testTokenSEP.line(), 1);

    ++testLine;
    token testTokenEQUAL(EQUAL, testLine);
    EXPECT_EQ(testTokenEQUAL.type(), EQUAL);
    EXPECT_EQ(testTokenEQUAL.line(), 2);

    ++testLine;
    token testTokenOPEN_PAREN(OPEN_PAREN, testLine);
    EXPECT_EQ(testTokenOPEN_PAREN.type(), OPEN_PAREN);
    EXPECT_EQ(testTokenOPEN_PAREN.line(), 3);

    ++testLine;
    token testTokenCLOSE_PAREN(CLOSE_PAREN, testLine);
    EXPECT_EQ(testTokenCLOSE_PAREN.type(), CLOSE_PAREN);
    EXPECT_EQ(testTokenCLOSE_PAREN.line(), 4);

    ++testLine;
    token testTokenSTRING_DELIM(STRING_DELIM, testLine);
    EXPECT_EQ(testTokenSTRING_DELIM.type(), STRING_DELIM);
    EXPECT_EQ(testTokenSTRING_DELIM.line(), 5);

    ++testLine;
    token testTokenSTRING(STRING, testLine);
    EXPECT_EQ(testTokenSTRING.type(), STRING);
    EXPECT_EQ(testTokenSTRING.line(), 6);

    ++testLine;
    token testTokenERROR(ERROR, testLine);
    EXPECT_EQ(testTokenERROR.type(), ERROR);
    EXPECT_EQ(testTokenERROR.line(), 7);
}

TEST(tokenTest, tokenComparisons)
{
    std::size_t testLine = 0;

    token testTokenEOL(EOL, testLine);
    EXPECT_EQ(testTokenEOL.type(), EOL);
    EXPECT_EQ(testTokenEOL.line(), 0);

    ++testLine;
    token testTokenSEP(SEP, testLine);
    EXPECT_EQ(testTokenSEP.type(), SEP);
    EXPECT_EQ(testTokenSEP.line(), 1);

    ++testLine;
    token testTokenEQUAL(EQUAL, testLine);
    EXPECT_EQ(testTokenEQUAL.type(), EQUAL);
    EXPECT_EQ(testTokenEQUAL.line(), 2);

    EXPECT_FALSE(testTokenEOL == testTokenSEP);
    EXPECT_FALSE(testTokenEOL == testTokenEQUAL);
    EXPECT_FALSE(testTokenSEP == testTokenEQUAL);

    token testTokenIdentical(testTokenEQUAL.type(), testTokenEQUAL.line());
    EXPECT_TRUE(testTokenEQUAL == testTokenIdentical);
    EXPECT_TRUE(testTokenEQUAL == testTokenEQUAL);
    EXPECT_TRUE(testTokenIdentical.contents().empty());
}

TEST(tokenTest, tokenContentsTests)
{
    std::size_t testLine = 0;

    token testTokenEOL(EOL, testLine);
    EXPECT_EQ(testTokenEOL.type(), EOL);
    EXPECT_EQ(testTokenEOL.line(), 0);
    EXPECT_TRUE(testTokenEOL.contents().empty());

    ++testLine;
    token testTokenSEP(SEP, testLine);
    EXPECT_EQ(testTokenSEP.type(), SEP);
    EXPECT_EQ(testTokenSEP.line(), 1);
    EXPECT_TRUE(testTokenSEP.contents().empty());

    ++testLine;
    token testTokenEQUAL(EQUAL, testLine);
    EXPECT_EQ(testTokenEQUAL.type(), EQUAL);
    EXPECT_EQ(testTokenEQUAL.line(), 2);
    EXPECT_TRUE(testTokenEQUAL.contents().empty());

    ++testLine;
    token testTokenEQUALWithContents(EQUAL, testLine, "test string A");
    EXPECT_EQ(testTokenEQUALWithContents.type(), EQUAL);
    EXPECT_EQ(testTokenEQUALWithContents.line(), 3);
    EXPECT_FALSE(testTokenEQUALWithContents.contents().empty());
    EXPECT_EQ(testTokenEQUALWithContents.contents(), "test string A");
    EXPECT_NE(testTokenEQUALWithContents.contents(), "false test contents");
}







