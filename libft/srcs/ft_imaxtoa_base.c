/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_imaxtoa_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 17:44:22 by jhache            #+#    #+#             */
/*   Updated: 2017/12/18 18:01:20 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*var_compute(uintmax_t *result, intmax_t n, int *len)
{
	char	*str;

	*len = 1;
	*result = (uintmax_t)((n < 0) ? (n * -1) : n);
	if (n < 0)
		++(*len);
	while (n > 9 || n < -9)
	{
		++(*len);
		n /= 10;
	}
	str = ft_strnew(*len);
	return (str);
}

char			*ft_imaxtoa_base(intmax_t n, char *base_from, char *base_to)
{
	uintmax_t	i;
	uintmax_t	result;
	int			len;
	char		*str;
	int			j;

	j = 0;
	i = 1;
	if ((str = var_compute(&result, n, &len)) == NULL)
		return (str);
	if (n < 0)
	{
		str[j++] = '-';
		--len;
	}
	while (--len > 0)
		i *= 10;
	while (i > 0)
	{
		str[j++] = (result / i) + 48;
		result %= i;
		i /= 10;
	}
	return (ft_convert_base(str, base_from, base_to));
}
