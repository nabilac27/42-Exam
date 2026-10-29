#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

static const char *g_s;
static size_t      g_i;

static void	panic_unexpected(char c)
{
	if (c == '\0')
		printf("Unexpected end of input\n");
	else
		printf("Unexpected token '%c'\n", c);
	exit(1);
}

static char	cur(void)
{
	return g_s[g_i];
}

static long long	parse_expr(void); 
static long long	parse_term(void);
static long long	parse_factor(void);

static long long	parse_factor(void)
{
	char c = cur();

	if (c == '\0')
		panic_unexpected('\0');
	if (isdigit((unsigned char)c))
	{
		g_i++;
		return (long long)(c - '0');
	}
	if (c == '(')
	{
		long long v;

		g_i++; 
		v = parse_expr();
		if (cur() == '\0')
			panic_unexpected('\0');
		if (cur() != ')')
			panic_unexpected(cur());
		g_i++;
		return v;
	}
	panic_unexpected(c);
	return 0;
}

static long long	parse_term(void)
{
	long long v = parse_factor();

	while (cur() == '*')
	{
		g_i++; 
		v *= parse_factor();
	}
	return v;
}

static long long	parse_expr(void)
{
	long long v = parse_term();

	while (cur() == '+')
	{
		g_i++; 
		v += parse_term();
	}
	return v;
}

int	main(int argc, char **argv)
{
	long long result;

	if (argc != 2 || !argv[1])
		return 1;
	g_s = argv[1];
	g_i = 0;

	result = parse_expr();

	if (cur() != '\0')
		panic_unexpected(cur());

	printf("%lld\n", result);
	return 0;
}
