/*
 * Copyright (c) 2024 YASUOKA Masahiko <yasuoka@yasuoka.net>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#include <sys/types.h>

int
check_utf8(const char *str, size_t strlen)
{
	int		 i, bytes;
	unsigned int	 oct, ch;
	const char	*pos, *end;

	pos = str;
	end = str + strlen;
	while (pos < end) {
		oct = *pos;
		if ((oct & 0x80) == 0) {
			bytes = 1;
			ch = oct & 0x7f;
		} else if ((oct & 0xe0) == 0xc0) {
			bytes = 2;
			ch = oct & 0x1f;
		} else if ((oct & 0xf0) == 0xe0) {
			bytes = 3;
			ch = oct & 0xf;
		} else if ((oct & 0xf8) == 0xf0) {
			bytes = 4;
			ch = oct & 0x7;
		} else
			return (0);
		if (pos + bytes > end)
			return (0);
		for (i = 1; i < bytes; i++) {
			oct = pos[i];
			if ((oct & 0xc0) != 0x80)
				return (0);
			ch = ch << 6 | (oct & 0x3F);
		}
		if (!(bytes == 1 || (bytes == 2 && ch >= 0x80) ||
		    (bytes == 3 && ch >= 0x800) ||
		    (bytes == 4 && ch >= 0x10000)))
			return (0);
		pos += bytes;
	}

	return (1);
}
