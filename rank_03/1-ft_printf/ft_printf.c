/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 22:58:36 by nchairun          #+#    #+#             */
/*   Updated: 2025/04/10 05:50:40 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

int	print_str(char *str)
{
	int	i = 0;

	if (!str)
		str = "(null)";
	while (str[i])
	{
		write (1, &str[i], 1);
		i++;
	}
    return(i);
}

int print_num(long long num, int base)
{
    char *digits = "0123456789abcdef";
    char result[64];
	int i = 0, len = 0;

	if (num == 0)
		return(write(1, "0", 1));
    if (num < 0)
    {
        len += write(1, "-", 1);
        num = -num;
    }
    while (num > 0)
    {
        result[i++] = digits[num % base];
        num = num / base;
    }
    while (i > 0)
        len += write(1, &result[--i], 1);
    return(len);
}

int	ft_printf(const char *str, ... )
{
	va_list	arg_ptr;
	int i = 0, result = 0;

	va_start(arg_ptr, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			i++;
			if (str[i] == 's')
				result += print_str(va_arg(arg_ptr, char *));
			else if (str[i] == 'd')
				result += print_num((long long)va_arg(arg_ptr, int), 10);
			else if (str[i] == 'x')
				result += print_num((long long)va_arg(arg_ptr, unsigned int), 16);
		}
		else
			result += write(1, &str[i], 1);
		i++;
	}
	va_end(arg_ptr);
	return(result);
}

// #include <stdio.h>
// int	main(void)
// {
//     // Test case 1: String and number formatting
//     int ret1 = ft_printf("Test 10: %s %d %x %s\n", "Hello", 42, 255, "A");
//     int ret2 = printf("Test 10: %s %d %x %s\n", "Hello", 42, 255, "A");
//     printf("Returned: ft = %d | real = %d\n", ret1, ret2);

//     // Test case 2: Negative number, zero, and large number
//     int ret3 = ft_printf("Test 11: %d %d %d\n", -42, 0, 123456789);
//     int ret4 = printf("Test 11: %d %d %d\n", -42, 0, 123456789);
//     printf("Returned: ft = %d | real = %d\n", ret3, ret4);

//     // Test case 3: Hexadecimal format
//     int ret5 = ft_printf("Test 12: %x %x %x\n", 255, 123456, 0);
//     int ret6 = printf("Test 12: %x %x %x\n", 255, 123456, 0);
//     printf("Returned: ft = %d | real = %d\n", ret5, ret6);

//     // Test case 4: Testing a null string
//     int ret7 = ft_printf("Test 13: %s\n", NULL);
//     int ret8 = printf("Test 13: %s\n", NULL);
//     printf("Returned: ft = %d | real = %d\n", ret7, ret8);
// 	return (0);
// }
