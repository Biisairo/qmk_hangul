#ifndef HANGUL_H
#define HANGUL_H

#include <stdint.h>

typedef uint32_t ucschar;

ucschar getChoseong(char c);
ucschar getJongseong(char c);

int hangul_is_syllable(ucschar c);
int hangul_is_choseong(ucschar c);
int hangul_is_jungseong(ucschar c);
int hangul_is_jongseong(ucschar c);
void hangul_syllable_to_jamo(ucschar syllable, ucschar* choseong, ucschar* jungseong, ucschar* jongseong);
ucschar hangul_jamo_to_syllable(ucschar choseong, ucschar jungseong, ucschar jongseong);

#endif