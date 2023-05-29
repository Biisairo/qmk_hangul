#include "hangul.h"

typedef struct hangulBuffer {
	ucschar choseong;
	ucschar jungseong;
	ucschar jongseong;
} hangulBuffer;

struct *hangulBuffer getHangulBuffer() {
	static hangulBuffer buf;
	return &buf;
}

void clearBuffer() {
	hangulBuffer *buffer = getHangulBuffer();
	buffer->choseong = 0;
	buffer->jungseong = 0;
	buffer->jongseong = 0;
}

ucschar output(char c) {
	hangulBuffer *buffer = getHangulBuffer();

	ucschar tmp;

	ucschar cho = buffer->choseong;
	ucschar jung = buffer->jungseong;
	ucschar jong = buffer->jongseong;

	if (cho) {
		if (jung) {
			if (jong) {

			}
		}
		tmp = getChoseong(c);
		if (hangul_is_choseong(tmp))
			buffer->choseong = tmp;
		return tmp;
	}

	if (*choseong && !(*jungseong)) {
		if ()
	}
}