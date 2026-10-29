/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 21:40:46 by nchairun          #+#    #+#             */
/*   Updated: 2026/03/12 21:41:04 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

static const char *g_s;
static size_t      g_i;

static void panic_unexpected(char c)
{
    if (c == '\0')
        printf("Unexpected end of input\n");
    else
        printf("Unexpected token '%c'\n", c);
    exit(1);
}

static char cur(void)
{
    return(g_s[g_i]);
}

static long long parse_expr(void);
static long long parse_term(void);
static long long parse_factor(void);

static long long parse_factor(void)
{
    char c = cur();

    if (c == '\0')
        panic_unexpected('\0');

    if (isdigit((unsigned char)c))
    {
        g_i++;
        return ((long long)(c - '0'));
    }

    if (c == '(')
    {
        long long value;

        g_i++;
        value = parse_expr();

        if (cur() == '\0')
            panic_unexpected('\0');
        if (cur() != ')')
            panic_unexpected(cur());
        g_i++;
        return(value);
    } 

    panic_unexpected(c);
    return(0);
}


static long long parse_term(void)
{
    long long value = parse_factor();

    while (cur() == '*')
    {
        g_i++;
        value *= parse_factor();
    } 
    return (value); 
}

static long long parse_expr(void)
{
    long long value = parse_term();

    while (cur() == '+')
    {
        g_i++;
        value += parse_term();
    }
    return (value);
}

int main(int argc, char *argv[])
{
    long long result;

    if (argc != 2 || !argv[1])
        return(1);
    
    g_s = argv[1];
    g_i = 0;

    result = parse_expr();

    if (cur() != '\0')
        panic_unexpected(cur());

    printf("%lld\n", result);

    return(0);
}