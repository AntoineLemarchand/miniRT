/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_test.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:08:38 by alemarch          #+#    #+#             */
/*   Updated: 2022/05/11 11:52:34 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef UNIT_TEST_H
# define UNIT_TEST_H

int	ft_slen(char *s);
int	almost_equal(float f1, float f2, float precision);
int	run_test(int (*f)( void ));

#endif
