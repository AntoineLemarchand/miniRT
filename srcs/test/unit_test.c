/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:32:25 by alemarch          #+#    #+#             */
/*   Updated: 2022/05/11 11:52:39 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "unit_test.h"

int	ft_slen(char *s)
{
	int	size;

	size = 0;
	while (s[size])
		size++;
	return (size);
}

int	almost_equal(float f1, float f2, float precision)
{
	return ( f1 > f2 - precision && f1 < f2 + precision);
}

int	run_test(int (*f)( void ))
{
	int	status;

	status = f();
	if (status)
		write(1, "√", ft_slen("√"));
	else
		write(1, "×", ft_slen("×"));
	write(1, "\n", 1);
	return (status);
}
