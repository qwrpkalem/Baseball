#include "gmock/gmock.h"
#include "baseball.cpp"
#include "baseball_test.h"

class BaseballFixture : public testing::Test {
public:
	Baseball game{"123"};
	void assertIllegalArgument(string guessNumber) {
		try {
			game.guess(guessNumber);
			FAIL();
		}
		catch (exception e) {
			//PASS
		}
	}
	void checkgameresulttrue(string guessNumber, int strikes, int balls) {
		GuessResult result = game.guess(guessNumber);

		EXPECT_TRUE(result.solved);
		EXPECT_EQ(strikes, result.strikes);
		EXPECT_EQ(balls, result.balls);
	}
	void checkgameresultfalse(string guessNumber, int strikes, int balls) {
		GuessResult result = game.guess(guessNumber);

		EXPECT_FALSE(result.solved);
		EXPECT_EQ(strikes, result.strikes);
		EXPECT_EQ(balls, result.balls);
	}
};

TEST_F(BaseballFixture, ThrowExceptionWhenInvalidCase)
{
	assertIllegalArgument("12");
	assertIllegalArgument("12s");
	assertIllegalArgument("121");
}
TEST_F(BaseballFixture, ReturnSolvedResultIfMatchedNumber)
{
	checkgameresulttrue("123", 3, 0);
}

TEST_F(BaseballFixture, ReturnSolvedResultIfTwoStrikesNoBall)
{
	checkgameresultfalse("125", 2, 0);
}

TEST_F(BaseballFixture, ReturnSolvedResultIfOneStrikesTwoBall)
{
	checkgameresultfalse("132", 1, 2);
}

int main()
{
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}