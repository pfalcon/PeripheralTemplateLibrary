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
#include <msp430/cpu_msp430.hpp>
#elif defined(__AVR__)
#include <avr/cpu_avr.hpp>
#elif defined(__STM32__)
#include <stm32/cpu_stm32.hpp>
#elif defined(__EFM32__)
#include <efm32/cpu_efm32.hpp>
#elif defined(__thumb__) || defined(__thumb2__)
#include <cortex-m/cpu_cortexm.hpp>
namespace PTL {
typedef CPU<CortexMCPU> cpu;
} // namespace
#else
#error Unknown platform in cpu.hpp
#endif
