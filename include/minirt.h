/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:59:57 by abelayad          #+#    #+#             */
/*   Updated: 2023/12/08 10:19:08 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <png.h>
# include <ctype.h>
# include <libft.h>
# include <pthread.h>
# include <png.h>
# include <pthread.h>
# include "minirt_types.h"
# include "tuples.h"
# include "canvas.h"
# include "matrices.h"
# include "ray_intersect.h"
# include "lsts.h"
# include "camera.h"
# include "light_shading.h"
# include "ft_png.h"
# include "ft_parse.h"

typedef struct s_chunk
{
	t_png_img	*img;
	t_world		*w;
	int			num;
	pthread_t	thread;
}	t_chunk;

#endif