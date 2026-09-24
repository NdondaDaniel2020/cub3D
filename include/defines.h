/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:55:53 by aquissan          #+#    #+#             */
/*   Updated: 2026/09/24 17:00:00 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

/* Terminal Colors */
# define RESET "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"
# define BLOCK "█"

/* File Descriptors */
# define READ O_RDONLY
# define WRITE O_WRONLY

/* Texture Counts */
# define QTD_TEXTURE 174
# define WEAPON_TYPES 6
# define ACTION_TYPES 3
# define IMAGE_COUNT 14

/* Screen & Rendering Defaults */
# if !defined SCREEN_WIDTH
#  define SCREEN_WIDTH 800
# endif
# if !defined SCREEN_HEIGHT
#  define SCREEN_HEIGHT 600
# endif
# if !defined SPEED
#  define SPEED 0.010
# endif
# if !defined PIXEL_SIZE
#  define PIXEL_SIZE 10
# endif
# define PI 3.14
# define ROTATE_SPEED 500
# define LIMIT_HIGH_VIEW 400

/* Linux Keycodes */
# define ESC 65307
# define RRIGHT 65363
# define RUP 65362
# define RDOWN 65364
# define RLEFT 65361
# define UP 119
# define LEFT 97
# define RIGHT 100
# define DOWN 115

/* Bonus Keycodes & Controls */
# define ONE 49
# define TWO 50
# define THREE 51
# define FOUR 52
# define FIVE 53
# define SIX 54
# define SEVEN 55
# define EIGHT 56
# define SZERO 65438
# define LCTRL 65508
# define OPENDOR 101
# define SPACE 32
# define ENTER 65293
# define CTRL 65507

/* Audio & Actions */
# define RESTART 1
# define NO_RESTART 0
# define FIRE 0
# define WALK 1
# define STOP 2

/* Cardinal Directions */
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

#endif
