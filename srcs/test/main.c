/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:32:45 by alemarch          #+#    #+#             */
/*   Updated: 2022/05/12 23:39:13 by alemarch         ###   ########.fr       */
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

int	ft_atof_test( void );

void	test_vec_basic( void )
{
	write(1, "━ vec_basic ━━━━\n", ft_slen("━ vec_basic ━━━━\n"));
	run_test(test_vec_init);
	run_test(test_vec_mult);
	run_test(test_vec_divide);
}

void	test_vec_alg( void )
{
	write(1, "━ vec_alg ━━━━━━\n", ft_slen("━ vec_alg ━━━━━━\n"));
	run_test(test_vec_normalize);
	run_test(test_vec_dot_product);
	run_test(test_vec_cross_product);
}

int	main( void )
{
	test_vec_basic();
	test_vec_alg();
	run_test(ft_atof_test);
	return (0);
}
