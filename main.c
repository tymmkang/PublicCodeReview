#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <math.h>

#define _TOKENIZE(TOKEN) TOKEN
#define TOKENIZE(TOKEN) _TOKENIZE(TOKEN)
#define STRINGIFY(TOKEN) _STRINGIFY(TOKEN)
#define _STRINGIFY(TOKEN) #TOKEN
#define CONCAT(L, R) _CONCAT(L, R)
#define _CONCAT(L, R) L##R

#define INPUT_STRING_LENGTH 3
#define INPUT_STRING_FORMAT(LEN) %TOKENIZE(LEN)s

int GetJoystickInputCount(const char desiredNickname[INPUT_STRING_LENGTH])
{
	char inputState[INPUT_STRING_LENGTH + 1] = "AAA";
	const int numAlphabat = 'Z' - 'A' + 1;
	const int numNumeric = '9' - '0' + 1;
	const int numCharacter = numAlphabat + numNumeric;
	const int numericIndexOffset = 'Z' - '0' + 1;

	int joystickInputCount = 0;
	for (int i = 0; i < INPUT_STRING_LENGTH; i++)
	{
		int currentChar = inputState[i];
		int desiredChar = desiredNickname[i];

		if ('0' <= currentChar && currentChar <= '9') currentChar += numericIndexOffset;
		if ('0' <= desiredChar && desiredChar <= '9') desiredChar += numericIndexOffset;

		int less = (currentChar < desiredChar) ? currentChar : desiredChar;
		int greater = (currentChar > desiredChar) ? currentChar : desiredChar;

		greater -= less;
		less = 0;

		int downDistance = greater - less;
		int upDistance = numCharacter + less - greater;

		joystickInputCount += (upDistance < downDistance) ? upDistance : downDistance;
		inputState[i] = desiredNickname[i];

		if (strcmp(desiredNickname, inputState) == 0)
		{
			break;
		}

		joystickInputCount++;
	}

	return joystickInputCount;
}

int main()
{
	char inputBuffer[INPUT_STRING_LENGTH + 1];
	memset(inputBuffer, 0, INPUT_STRING_LENGTH + 1);
	
	while (1)
	{
		printf("닉네임 : ");
		(void)scanf(STRINGIFY(INPUT_STRING_FORMAT(INPUT_STRING_LENGTH)), inputBuffer);

		int isValid = 1;
		for (int i = 0; i < INPUT_STRING_LENGTH; i++)
		{
			if (('A' <= inputBuffer[i] && inputBuffer[i] <= 'Z' ||
				'0' <= inputBuffer[i] && inputBuffer[i] <= '9') == 0)
			{
				isValid = 0;
				break;
			}
		}

		if (isValid != 1)
		{
			printf("잘못된 입력입니다.\n");
			continue;
		}

		rewind(stdin);

		int inputCount = GetJoystickInputCount(inputBuffer);
		printf("조이스틱 조작 횟수 : %d\n", inputCount);
	}

	return 0;
}
