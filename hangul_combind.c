#include "hangul.h"

int isLowerCase(char c) {
	if ('a' <= c && c <= 'z')
		return 1;
	return 0;
}

ucschar output(char c) {
	static ucschar pre;

	ucschar choseong[1];
	ucschar jungseong[1];
	ucschar jongseong[1];

	hangul_syllable_to_jamo(pre, choseong, jungseong, jongseong);

	if (*choseong == 0) {
		pre = getChoseong(c);
		return pre;
	}


	if (*choseong && !(*jungseong)) {
		if ()
	}
}