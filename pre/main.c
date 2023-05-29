#include "hangul.h"
#include <stdio.h>

#include <wchar.h>
#include <locale.h>

int main() {
	HangulInputContext* hic = hangul_ic_new("2");

	char event[100] = "rlaehddbs\b\n";

	int i = 0;
	while (event[i]) {
		bool res;
		if (event[i] == '\b')
			res = hangul_ic_backspace(hic);
		else
			res = hangul_ic_process(hic, event[i]);

		const ucschar *commit;
		commit = hangul_ic_get_commit_string(hic);
		if (commit[0] != 0)
			printf("%d\n", *commit);

		const ucschar *preedit;
		preedit = hangul_ic_get_preedit_string(hic);
		printf("%d\n", *commit);

		i++;
	}

	hangul_ic_delete(hic);
}