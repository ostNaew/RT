/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quadratic_equation.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 18:09:27 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/02/09 14:51:24 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "worthless_geometry.h"

int	solve_quadratic_equation(t_quadratic_equation equation, double *t0,
	double *t1)
{
	double	discr;
	double	r0;
	double	r1;

	discr = equation.b * equation.b - 4 * equation.a * equation.c;
	if (discr < 0)
		return (0);
	discr = sqrt(discr);
	r0 = (-equation.b - discr) / (2. * equation.a);
	r1 = (-equation.b + discr) / (2. * equation.a);
	*t0 = (r0 < r1) ? r0 : r1;
	*t1 = (r0 < r1) ? r1 : r0;
	return (1);
}
