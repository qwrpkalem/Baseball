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
	void checkgameresult(string guessNumber) {
		GuessResult result = game.guess(guessNumber);

		EXPECT_TRUE(result.solved);
		EXPECT_EQ(3, result.strikes);
		EXPECT_EQ(0, result.balls);
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
	checkgameresult("123");
}

int main()
{
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}