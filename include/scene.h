#ifndef SCENE_H
#define SCENE_H

t_world		ft_default_world(void);
t_matrix	ft_view_transform_inverse(t_tuple from, t_tuple forward);
t_camera	ft_camera(t_camera raw_camera);
t_ray		ft_ray_for_pixel(int x, int y, t_camera c);
t_canvas	ft_render(t_world *w, t_camera c);
t_xnode		*ft_intersect_world(t_world *w, t_ray r);

#endif