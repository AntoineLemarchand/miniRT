/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:32:45 by alemarch          #+#    #+#             */
/*   Updated: 2022/05/11 14:00:13 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_test.h"
#include "miniRT.h"

int	test_vec_init( void );
int	test_vec_mult( void );
int	test_vec_divide( void );

int	test_vec_normalize( void );
int	test_vec_dot_product( void );
int	test_vec_cross_product( void );

int	main( void )
{
	int	success;
	int	total;

	success = 0;
	total = 3;
	write(1, "━ vec_basic ━━━━\n", ft_slen("━ vec_basic ━━━━\n"));
	success += run_test(test_vec_init) - 1;
	success += run_test(test_vec_mult);
	success += run_test(test_vec_divide);
	total += 2;
	write(1, "━ vec_alg ━━━━━━\n", ft_slen("━ vec_alg ━━━━━━\n"));
	success += run_test(test_vec_normalize);
	success += run_test(test_vec_dot_product);
	success += run_test(test_vec_cross_product);
	if (success == total)
	{
		write(1, "┏━━━━━━━━━━━━━━┓\n", ft_slen("┏━━━━━━━━━━━━━━┓\n"));
		write(1, "┃      OK      ┃\n", ft_slen("┃      OK      ┃\n"));
		write(1, "┗━━━━━━━━━━━━━━┛\n", ft_slen("┗━━━━━━━━━━━━━━┛\n"));
	}
	else
	{
		write(1, "┏━━━━━━━━━━━━━━┓\n", ft_slen("┏━━━━━━━━━━━━━━┓\n"));
		write(1, "┃      KO      ┃\n", ft_slen("┃      KO      ┃\n"));
		write(1, "┗━━━━━━━━━━━━━━┛\n", ft_slen("┗━━━━━━━━━━━━━━┛\n"));
	}
}
