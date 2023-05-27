#include "hangul.h"
#include <stdio.h>

#include <wchar.h>
#include <locale.h>

int main()
{
	char* input = "rlaehddbs";

	ucschar	 syll = 0xac01;
	ucschar choseong[1];
	ucschar jungseong[1];
	ucschar jongseong[1];

	hangul_syllable_to_jamo(syll, choseong, jungseong, jongseong);

	ucschar syll2 = hangul_jamo_to_syllable(*choseong, *jungseong, *jongseong);

	printf("%X\n", syll2);
}