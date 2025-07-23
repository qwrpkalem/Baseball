#include "stdexcept"
using namespace std;

struct GuessResult {
	bool solved;
	int strikes;
	int balls;
};

class Baseball {
public:
	explicit Baseball(const string& question)
		: question(question){
		result.strikes = 0;
		result.balls = 0;
		result.solved = false;
	}

	GuessResult guess(const string& guessNumber) {
		assertIllegalArgument(guessNumber);

		InitResultInfo();

		// strike check
		result.strikes = GetStrikeCount(guessNumber);

		// ball check
		result.balls = GetBallCount(guessNumber);

		// Ans Check
		result.solved = GetIsAns();

		return result;
	}
	bool GetIsAns()
	{
		if (result.strikes == 3) {
			return true;
		}
		return false;
	}
	int GetBallCount(const std::string& guessNumber)
	{
		int ret = 0;
		for (int GuessNumIdx = 0; GuessNumIdx < guessNumber.size(); GuessNumIdx++) {
			for (int QuestionIdx = 0; QuestionIdx < question.size(); QuestionIdx++)
			{
				if (GuessNumIdx == QuestionIdx) continue;

				if (guessNumber[GuessNumIdx] == question[QuestionIdx]) {
					ret++;
				}
			}
		}
		return ret;
	}
	int GetStrikeCount(const std::string& guessNumber)
	{
		int ret = 0;
		for (int GuessNumIdx = 0; GuessNumIdx < guessNumber.size(); GuessNumIdx++) {

			if (guessNumber[GuessNumIdx] == question[GuessNumIdx]) {
				ret++;
			}
		}
		return ret;
	}
	void InitResultInfo()
	{
		result.strikes = 0;
		result.balls = 0;
		result.solved = false;
	}
	void assertIllegalArgument(const std::string& guessNumber)
	{
		if (guessNumber.length() != 3) {
			throw length_error("Must be three letters...");
		}
		for (char ch : guessNumber) {
			if (ch >= '0' && ch <= '9') continue;
			throw invalid_argument("Must be number");
		}

		if (isDuplicatedNumber(guessNumber)) {
			throw invalid_argument("Must not have the same number");
		}
	}
private:
	string question;
	GuessResult result;

	bool isDuplicatedNumber(const std::string& guessNumber)
	{
		return guessNumber[0] == guessNumber[1]
			|| guessNumber[0] == guessNumber[2]
			|| guessNumber[1] == guessNumber[2];
	}
};