#include "minirt.h"

t_world	ft_default_world(void)
{
	t_world	w;

	w.objlst = ft_objnew(OT_SPHERE);
	w.objlst->material.color = g_red;
	ft_objadd_back(&w.objlst, ft_objnew(OT_SPHERE));
	w.objlst->next->material.color = g_green;
	w.objlst->next->transform_inverse = ft_inverse(ft_scale(.5, .5, .5));
	w.light = ft_point_light(ft_point(-10, 10, -10), ft_color(1, 1, 1));
	return (w);
}
