/*
 * This file is part of the Peripheral Template Library project.
 *
 * Copyright (c) 2012 Paul Sokolovsky <pfalcon@users.sourceforge.net>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */
#if defined(__MSP430__)
#include <delay_static_msp430.hpp>
#elif defined(__AVR__)
#include <delay_static_avr.hpp>
#elif defined(__STM32__)
#include <delay_static_stm32.hpp>
#elif defined(__EFM32__)
#include <delay_static_efm32.hpp>
#else
#error Unknown platform in delay_static.hpp
#endif
