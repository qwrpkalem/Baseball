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
		result.strikes = 0;
		result.balls = 0;
		result.solved = false;
		for (int GuessNumIdx = 0; GuessNumIdx < guessNumber.size(); GuessNumIdx++) {

			if (guessNumber[GuessNumIdx] == question[GuessNumIdx]) {
				result.strikes++;
				continue;
			}

			for (int QuestionIdx = 0; QuestionIdx < question.size(); QuestionIdx++)
			{
				if (guessNumber[QuestionIdx] == question[QuestionIdx]) {
					result.balls++;
					continue;
				}
			}
		}

		if (result.strikes == 3) {
			result.solved = true;
		}

		return { result.solved , result.strikes, result.balls };
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
	bool isDuplicatedNumber(const std::string& guessNumber)
	{
		return guessNumber[0] == guessNumber[1]
			|| guessNumber[0] == guessNumber[2]
			|| guessNumber[1] == guessNumber[2];
	}
private:
	string question;
	GuessResult result;
};