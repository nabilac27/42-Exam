#include "./5-argo.h"
#include <stdio.h>   
#include <stdlib.h>   
#include <ctype.h>    
#include <unistd.h>   

static const char *g_buf;
static size_t      g_len;
static size_t      g_i;

static int unexpected(int c)
{
	if (c < 0)
		printf("Unexpected end of input\n");
	else
		printf("Unexpected token '%c'\n", c);
	return -1;
}

static int peek(void)
{
	return (g_i < g_len) ? (unsigned char)g_buf[g_i] : -1;
}

static int getc_buf(void)
{
	return (g_i < g_len) ? (unsigned char)g_buf[g_i++] : -1;
}

static int parse_value(void);

static int parse_string(void)
{
	int c;

	if (getc_buf() != '"')
		return unexpected(peek());
	while (1)
	{
		c = getc_buf();
		if (c < 0)
			return unexpected(-1);
		if (c == '"')
			return 1;
		if (c == '\\')
		{
			int e = getc_buf();
			if (e < 0)
				return unexpected(-1);
			if (e != '\\' && e != '"')
				return unexpected(e);
		}
	}
}

static int parse_number(void)
{
	int c = peek();
	int digits = 0;

	if (c == '-')
	{
		getc_buf();
		c = peek();
	}
	if (c < 0)
		return unexpected(-1);
	if (!isdigit(c))
		return unexpected(c);
	while ((c = peek()) >= 0 && isdigit(c))
	{
		getc_buf();
		digits = 1;
	}
	(void)digits;
	return 1;
}

static int parse_object(void)
{
	int c;

	if (getc_buf() != '{')
		return unexpected(peek());
	c = peek();
	if (c < 0)
		return unexpected(-1);
	if (c == '}')
	{
		getc_buf();
		return 1;
	}
	while (1)
	{
		if (peek() != '"')
			return unexpected(peek());
		if (parse_string() < 0)
			return -1;

		c = getc_buf();
		if (c < 0)
			return unexpected(-1);
		if (c != ':')
			return unexpected(c);

		if (parse_value() < 0)
			return -1;

		c = peek();
		if (c < 0)
			return unexpected(-1);
		if (c == ',')
		{
			getc_buf();
			continue;
		}
		if (c == '}')
		{
			getc_buf();
			return 1;
		}
		return unexpected(c);
	}
}

static int parse_value(void)
{
	int c = peek();

	if (c < 0)
		return unexpected(-1);
	if (c == '"')
		return parse_string();
	if (c == '{')
		return parse_object();
	if (c == '-' || isdigit(c))
		return parse_number();
	return unexpected(c);
}

static char *read_all(FILE *stream, size_t *out_len)
{
	size_t cap = 256, len = 0;
	char *buf = (char *)malloc(cap);
	int ch;

	if (!buf)
		return NULL;
	while ((ch = getc(stream)) != EOF)
	{
		if (len == cap)
		{
			cap <<= 1;
			char *nb = (char *)realloc(buf, cap);
			if (!nb)
			{
				free(buf);
				return NULL;
			}
			buf = nb;
		}
		buf[len++] = (char)ch;
	}
	*out_len = len;
	return buf;
}

int argo(void *dst, FILE *stream)
{
	char   *buf;
	size_t  len;
	int     r;

	(void)dst;
	buf = read_all(stream, &len);
	if (!buf)
		return -1;

	g_buf = buf;
	g_len = len;
	g_i   = 0;

	r = parse_value();
	if (r >= 0)
	{
		if (g_i != g_len)
			r = unexpected(peek());
	}
	if (r >= 0)
	{
		if (len)
			write(1, buf, len);
		free(buf);
		return 1;
	}
	free(buf);
	return -1;
}
