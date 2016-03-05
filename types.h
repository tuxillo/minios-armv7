/*
 * Copyright (c) 2016, Antonio Huete Jimenez <tuxillo@quantumachine.net>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES ;
 * LOSS OF USE, DATA, OR PROFITS ; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of the author.
 */

#ifndef _TYPES_H_
#define _TYPES_H_

typedef unsigned short	u_short;
typedef unsigned long	u_long;
typedef unsigned int	u_int;
typedef	long int	intptr_t;
typedef	long unsigned int	uintptr_t;
typedef long unsigned int	size_t;
typedef long int		ssize_t;
typedef long int	intmax_t;
typedef long unsigned int	uintmax_t;
typedef intptr_t	ptrdiff_t;
typedef unsigned long	uint64_t;
typedef long		int64_t;
typedef unsigned int	uint32_t;
typedef int		int32_t;
typedef unsigned short	uint16_t;
typedef short		int16_t;
typedef unsigned char	uint8_t;
typedef char		int8_t;
typedef uint64_t	u_int64_t;
typedef uint64_t	quad_t;
typedef int		bool;

#define NULL ((void *)0)

typedef unsigned char u_char;

#define TRUE	1
#define FALSE	!TRUE

#endif /* _TYPES_H_ */
