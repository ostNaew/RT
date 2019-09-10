# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/16 13:48:41 by ajaehaer          #+#    #+#              #
#    Updated: 2019/03/30 15:46:37 by ejommy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT
GCC = gcc -Wall -Wextra -Werror

SRC = check_images.c \
	  circles.c \
	  clear_pixels_buffer.c \
	  color.c \
	  cones.c \
	  paraboloids.c \
	  toruses.c \
	  cylinders.c \
	  get_rays.c \
	  helpers.c \
	  init.c \
	  light.c \
	  load_intermediate_result.c \
	  main.c \
	  main_loop.c \
	  map_normal_circle.c \
	  map_normal_cone.c \
	  map_normal_cylinder.c \
	  map_normal_plane.c \
	  map_normal_sphere.c \
	  map_normal_triangle.c \
	  map_normal_torus.c \
	  map_normal_paraboloid.c \
	  normal_mapping.c \
	  path_tracing.c \
	  primitive_intersection.c \
	  process_directional_light.c \
	  process_parallel_light.c \
	  process_point_light.c \
	  ray_circle_intersection.c \
	  ray_paraboloid_intersection.c \
	  ray_torus_intersection.c \
	  ray_cone_intersection.c \
	  ray_cylinder_intersection.c \
	  ray_plane_intersection.c \
	  ray_sphere_intersection.c \
	  ray_tracing.c \
	  ray_triangle_intersection.c \
	  read_map.c \
	  reflect.c \
	  refract.c \
	  render.c \
	  refresh_screen.c \
	  process_task.c \
	  save_intermediate_result.c \
	  scene_intersection.c \
	  spheres.c \
	  texture.c \
	  trace_path.c \
	  trace_path_helpers.c \
	  trace_ray.c \
	  triangles.c \
	  key_hooks.c

GEOMETRY = change_basis.c \
		   get_plane_equation.c \
		   identity_matrix.c \
		   is_valid_vector.c \
		   matrix_operations.c \
		   norm.c \
		   point_in_triangle_2d.c \
		   ray_view_matrix.c \
		   rotation_matrices.c \
		   solve_plane.c \
		   solve_quadratic_equation.c \
		   transformation_matrices.c \
		   vector_matrix_multiply.c \
		   vector_operations.c \
		   vector_operations2.c \
		   transpose_matrix.c \
		   invert_matrix.c

JSON = element_lack.c \
	   get_string.c \
	   json_del.c \
	   json_destroy.c \
	   json_parse.c \
	   json_value_by_index.c \
	   json_value_by_key.c \
	   new_json.c \
	   parse_array.c \
	   parse_bool.c \
	   parse_element.c \
	   parse_null.c \
	   parse_number.c \
	   parse_object.c \
	   parse_string.c \
	   skip_spaces.c

PARSER = add_boundary.c \
		 atoi_hex.c \
		 destroy_objects.c \
		 get_cone.c \
		 get_paraboloid.c \
		 get_torus.c \
		 get_cylinder.c \
		 get_general_properties.c \
		 get_plane_triangle_circle.c \
		 get_rotation_matrix.c \
		 get_sphere.c \
		 json2vec.c \
		 process_camera.c \
		 process_images.c \
		 process_lights.c \
		 process_map.c \
		 process_materials.c \
		 process_object.c \
		 process_transform_primitives.c \
		 process_transformation.c

NETPBM = netpbm_helpers.c \
		 read_image.c \
		 read_meta.c \
		 read_ppm_ascii.c \
		 read_ppm_binary.c

FILTERS = active_filter.c \
		  apply_filters.c \
		  blur.c \
		  get_color_from_pixel.c \
		  gray.c \
		  index_brightness.c \
		  median.c \
		  negative.c \
		  sepia.c

DYAD = dyad.c

NETWORK = check_validity.c \
		  csiphash.c \
		  data_hook.c \
		  hooks.c \
		  get_nonce.c \
		  network_init.c \
		  master_data_hook.c \
		  networking.c \
		  receive_task.c \
		  slave_data_hook.c \
		  data_singleton.c \
		  send_task.c \
		  send_result.c \
		  request_task.c \
		  receive_result.c \
		  get_num_samples_in_task.c

WRITE_WRAPPER = ft_fd_write_wrapper.c \
				ft_write_wrapper.c

SDL_PATH = sdl2
SDL2 = `$(SDL_PATH)/sdl2-config --cflags --libs`

INC = -I . -I filters -I json_parser -I map_parser -I geometry -I libft -I netpbm -I $(SDL_PATH)/include -I dyad -I network -I write_wrapper

LIBFT = -L libft -lft

OBJ_DIR = obj

O_SRC = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
O_GEOMETRY = $(addprefix $(OBJ_DIR)/, $(GEOMETRY:.c=.o))
O_JSON = $(addprefix $(OBJ_DIR)/, $(JSON:.c=.o))
O_PARSER = $(addprefix $(OBJ_DIR)/, $(PARSER:.c=.o))
O_NETPBM = $(addprefix $(OBJ_DIR)/, $(NETPBM:.c=.o))
O_FILTERS = $(addprefix $(OBJ_DIR)/, $(FILTERS:.c=.o))
O_DYAD = $(addprefix $(OBJ_DIR)/, $(DYAD:.c=.o))
O_NETWORK = $(addprefix $(OBJ_DIR)/, $(NETWORK:.c=.o))
O_WRITE_WRAPPER = $(addprefix $(OBJ_DIR)/, $(WRITE_WRAPPER:.c=.o))

all: $(NAME)

$(NAME): $(O_SRC) $(O_GEOMETRY) $(O_JSON) $(O_PARSER) $(O_NETPBM) $(O_FILTERS) $(O_DYAD) $(O_NETWORK) $(O_WRITE_WRAPPER)
	if [ ! -d "$(SDL_PATH)/lib" ]; then \
		/bin/mkdir $(SDL_PATH)/lib; \
		cd $(SDL_PATH) ; ./configure --prefix=`pwd`/lib; \
		fi
	make -C $(SDL_PATH)
	make -C $(SDL_PATH) install >/dev/null
	make -C libft
	$(GCC) $(SDL2) -o $(NAME) $(O_SRC) $(O_GEOMETRY) $(O_JSON) $(O_PARSER) $(O_NETPBM) $(O_FILTERS)  $(O_DYAD) $(O_NETWORK) $(O_WRITE_WRAPPER) $(INC) $(LIBFT)

$(O_SRC): $(OBJ_DIR)/%.o : %.c
	/bin/mkdir -p $(OBJ_DIR)
	$(GCC) -c $< $(INC) -o $@

$(O_GEOMETRY): $(OBJ_DIR)/%.o : ./geometry/%.c
	/bin/mkdir -p $(OBJ_DIR)
	$(GCC) -c $< $(INC) -o $@

$(O_JSON): $(OBJ_DIR)/%.o : ./json_parser/%.c
	/bin/mkdir -p $(OBJ_DIR)
	$(GCC) -c $< $(INC) -o $@

$(O_PARSER): $(OBJ_DIR)/%.o : ./map_parser/%.c
	/bin/mkdir -p $(OBJ_DIR)
	$(GCC) -c $< $(INC) -o $@

$(O_NETPBM): $(OBJ_DIR)/%.o : ./netpbm/%.c
	/bin/mkdir -p $(OBJ_DIR)
	$(GCC) -c $< $(INC) -o $@

$(O_FILTERS): $(OBJ_DIR)/%.o : ./filters/%.c
	/bin/mkdir -p $(OBJ_DIR)
	$(GCC) -c $< $(INC) -o $@

$(O_DYAD): $(OBJ_DIR)/%.o : ./dyad/%.c
	/bin/mkdir -p $(OBJ_DIR)
	$(GCC) -c $< $(INC) -o $@

$(O_NETWORK): $(OBJ_DIR)/%.o : ./network/%.c
	/bin/mkdir -p $(OBJ_DIR)
	$(GCC) -c $< $(INC) -o $@

$(O_WRITE_WRAPPER): $(OBJ_DIR)/%.o : ./write_wrapper/%.c
	/bin/mkdir -p $(OBJ_DIR)
	$(GCC) -c $< $(INC) -o $@

clean:
	rm -rf $(OBJ_DIR)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	rm -rf $(SDL_PATH)/lib
	rm -rf $(SDL_PATH)/build
	rm -rf $(SDL_PATH)/Makefile
	rm -rf $(SDL_PATH)/Makefile.rules
	rm -rf $(SDL_PATH)/config.log
	rm -rf $(SDL_PATH)/config.status
	rm -rf $(SDL_PATH)/libtool
	rm -rf $(SDL_PATH)/sdl2-config
	rm -rf $(SDL_PATH)/sdl2-config.cmake
	rm -rf $(SDL_PATH)/sdl2.pc
	make -C libft fclean

re: fclean all
