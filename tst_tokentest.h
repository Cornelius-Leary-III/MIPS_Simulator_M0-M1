#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "token.h"

using namespace testing;


TEST(tokenTest, tokenClassTypes)
{
    std::size_t testLine = 0;
    std::size_t testId = 1;

    token testTokenEOL(EOL, testId, testLine);
    EXPECT_EQ(testTokenEOL.type(), EOL);
    EXPECT_EQ(testTokenEOL.id(), 1);
    EXPECT_EQ(testTokenEOL.line(), 0);

    ++testLine;
    ++testId;
    token testTokenSEP(SEP, testId, testLine);
    EXPECT_EQ(testTokenSEP.type(), SEP);
    EXPECT_EQ(testTokenSEP.id(), 2);
    EXPECT_EQ(testTokenSEP.line(), 1);

    ++testLine;
    ++testId;
    token testTokenEQUAL(EQUAL, testId, testLine);
    EXPECT_EQ(testTokenEQUAL.type(), EQUAL);
    EXPECT_EQ(testTokenEQUAL.id(), 3);
    EXPECT_EQ(testTokenEQUAL.line(), 2);

    ++testLine;
    ++testId;
    token testTokenOPEN_PAREN(OPEN_PAREN, testId, testLine);
    EXPECT_EQ(testTokenOPEN_PAREN.type(), OPEN_PAREN);
    EXPECT_EQ(testTokenOPEN_PAREN.id(), 4);
    EXPECT_EQ(testTokenOPEN_PAREN.line(), 3);

    ++testLine;
    ++testId;
    token testTokenCLOSE_PAREN(CLOSE_PAREN, testId, testLine);
    EXPECT_EQ(testTokenCLOSE_PAREN.type(), CLOSE_PAREN);
    EXPECT_EQ(testTokenCLOSE_PAREN.id(), 5);
    EXPECT_EQ(testTokenCLOSE_PAREN.line(), 4);

    ++testLine;
    ++testId;
    token testTokenSTRING_DELIM(STRING_DELIM, testId, testLine);
    EXPECT_EQ(testTokenSTRING_DELIM.type(), STRING_DELIM);
    EXPECT_EQ(testTokenSTRING_DELIM.id(), 6);
    EXPECT_EQ(testTokenSTRING_DELIM.line(), 5);

    ++testLine;
    ++testId;
    token testTokenSTRING(STRING, testId, testLine);
    EXPECT_EQ(testTokenSTRING.type(), STRING);
    EXPECT_EQ(testTokenSTRING.id(), 7);
    EXPECT_EQ(testTokenSTRING.line(), 6);

    ++testLine;
    ++testId;
    token testTokenERROR(ERROR, testId, testLine);
    EXPECT_EQ(testTokenERROR.type(), ERROR);
    EXPECT_EQ(testTokenERROR.id(), 8);
    EXPECT_EQ(testTokenERROR.line(), 7);
}

TEST(tokenTest, tokenComparisons)
{
    std::size_t testLine = 0;
    std::size_t testId = 1;

    token testTokenEOL(EOL, testId, testLine);
    EXPECT_EQ(testTokenEOL.type(), EOL);
    EXPECT_EQ(testTokenEOL.id(), 1);
    EXPECT_EQ(testTokenEOL.line(), 0);

    ++testLine;
    ++testId;
    token testTokenSEP(SEP, testId, testLine);
    EXPECT_EQ(testTokenSEP.type(), SEP);
    EXPECT_EQ(testTokenSEP.id(), 2);
    EXPECT_EQ(testTokenSEP.line(), 1);

    ++testLine;
    ++testId;
    token testTokenEQUAL(EQUAL, testId, testLine);
    EXPECT_EQ(testTokenEQUAL.type(), EQUAL);
    EXPECT_EQ(testTokenEQUAL.id(), 3);
    EXPECT_EQ(testTokenEQUAL.line(), 2);

    EXPECT_FALSE(testTokenEOL == testTokenSEP);
    EXPECT_FALSE(testTokenEOL == testTokenEQUAL);
    EXPECT_FALSE(testTokenSEP == testTokenEQUAL);

    token testTokenIdentical(testTokenEQUAL.type(), testTokenEQUAL.id(), testTokenEQUAL.line());
    EXPECT_TRUE(testTokenEQUAL == testTokenIdentical);
    EXPECT_TRUE(testTokenEQUAL == testTokenEQUAL);
    EXPECT_TRUE(testTokenIdentical.contents().empty());
}

TEST(tokenTest, tokenContentsTests)
{
    std::size_t testLine = 0;
    std::size_t testId = 1;

    token testTokenEOL(EOL, testId, testLine);
    EXPECT_EQ(testTokenEOL.type(), EOL);
    EXPECT_EQ(testTokenEOL.id(), 1);
    EXPECT_EQ(testTokenEOL.line(), 0);
    EXPECT_TRUE(testTokenEOL.contents().empty());

    ++testLine;
    ++testId;
    token testTokenSEP(SEP, testId, testLine);
    EXPECT_EQ(testTokenSEP.type(), SEP);
    EXPECT_EQ(testTokenSEP.id(), 2);
    EXPECT_EQ(testTokenSEP.line(), 1);
    EXPECT_TRUE(testTokenSEP.contents().empty());

    ++testLine;
    ++testId;
    token testTokenEQUAL(EQUAL, testId, testLine);
    EXPECT_EQ(testTokenEQUAL.type(), EQUAL);
    EXPECT_EQ(testTokenEQUAL.id(), 3);
    EXPECT_EQ(testTokenEQUAL.line(), 2);
    EXPECT_TRUE(testTokenEQUAL.contents().empty());

    ++testLine;
    ++testId;
    token testTokenEQUALWithContents(EQUAL, testId, testLine, "test string A");
    EXPECT_EQ(testTokenEQUALWithContents.type(), EQUAL);
    EXPECT_EQ(testTokenEQUALWithContents.id(), 4);
    EXPECT_EQ(testTokenEQUALWithContents.line(), 3);
    EXPECT_FALSE(testTokenEQUALWithContents.contents().empty());
    EXPECT_EQ(testTokenEQUALWithContents.contents(), "test string A");
    EXPECT_NE(testTokenEQUALWithContents.contents(), "false test contents");
}







