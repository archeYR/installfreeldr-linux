/*
 * PROJECT:     ReactOS FreeLoader installer for Linux
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     Installation functions
 * COPYRIGHT:   Copyright 2001 Brian Palmer (brianp@sginet.com)
 *              Copyright 2019 Arnav Bhatt (arnavbhatt2004@gmail.com)
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h> 
#include "install.h"
#include "volume.h"

/* fat32_data and fat_data arrays */

unsigned char fat32_data[] =
{
    0xeb, 0x58, 0x90, 0x46, 0x72, 0x4c, 0x64, 0x72, 0x31, 0x2e, 0x30, 0x00, 0x02, 0x00, 0x20, 0x00,
    0x02, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x29, 0x00, 0x00, 0x00, 0x00, 0x4e, 0x4f, 0x20, 0x4e, 0x41, 0x4d, 0x45, 0x20, 0x20,
    0x20, 0x20, 0x46, 0x41, 0x54, 0x33, 0x32, 0x20, 0x20, 0x20, 0x31, 0xc0, 0x8e, 0xd8, 0x8e, 0xc0,
    0x8e, 0xd0, 0xbd, 0x00, 0x7c, 0xbc, 0x00, 0x7c, 0x80, 0xbe, 0x40, 0x00, 0xff, 0x75, 0x04, 0x88,
    0x96, 0x40, 0x00, 0x83, 0xbe, 0x16, 0x00, 0x00, 0x75, 0x0f, 0x66, 0x83, 0xbe, 0x11, 0x00, 0x00,
    0x75, 0x07, 0x83, 0xbe, 0x2a, 0x00, 0x00, 0x76, 0x03, 0xe9, 0x08, 0x01, 0xb8, 0x00, 0x08, 0x8a,
    0x96, 0x40, 0x00, 0xcd, 0x13, 0x73, 0x05, 0xb9, 0xff, 0xff, 0x88, 0xce, 0x88, 0xeb, 0x88, 0xcf,
    0xc0, 0xef, 0x06, 0x80, 0xe1, 0x3f, 0x66, 0x0f, 0xb6, 0xc6, 0x66, 0x0f, 0xb7, 0xdb, 0x66, 0x0f,
    0xb6, 0xc9, 0x66, 0x40, 0x66, 0x43, 0x66, 0xf7, 0xe1, 0x66, 0xf7, 0xe3, 0x66, 0xa3, 0xb5, 0x7d,
    0x66, 0xb8, 0x0e, 0x00, 0x00, 0x00, 0x66, 0x03, 0x86, 0x1c, 0x00, 0xb9, 0x01, 0x00, 0x31, 0xdb,
    0x8e, 0xc3, 0xbb, 0x00, 0x7e, 0xe8, 0x03, 0x00, 0xe9, 0x25, 0x01, 0x06, 0x66, 0x3b, 0x06, 0xb5,
    0x7d, 0x73, 0x1c, 0x66, 0x60, 0xb4, 0x41, 0xbb, 0xaa, 0x55, 0x8a, 0x96, 0x40, 0x00, 0xcd, 0x13,
    0x72, 0x57, 0x81, 0xfb, 0x55, 0xaa, 0x75, 0x51, 0xf6, 0xc1, 0x01, 0x74, 0x4c, 0x66, 0x61, 0x66,
    0x60, 0x83, 0xf9, 0x40, 0x76, 0x03, 0xb9, 0x40, 0x00, 0x89, 0x0e, 0x45, 0x7d, 0x6a, 0x00, 0x6a,
    0x00, 0x66, 0x50, 0x06, 0x53, 0x51, 0x6a, 0x10, 0x89, 0xe6, 0x8a, 0x96, 0x40, 0x00, 0xb4, 0x42,
    0xcd, 0x13, 0x72, 0x68, 0x83, 0xc4, 0x10, 0x66, 0x61, 0x53, 0x66, 0x8b, 0x1e, 0x45, 0x7d, 0x66,
    0x01, 0xd8, 0x66, 0xc1, 0xe3, 0x05, 0x8c, 0xc2, 0x01, 0xda, 0x8e, 0xc2, 0x5b, 0x2b, 0x0e, 0x45,
    0x7d, 0x75, 0xbc, 0x07, 0xc3, 0x00, 0x00, 0x00, 0x00, 0x66, 0x61, 0x66, 0x60, 0x66, 0x31, 0xd2,
    0x66, 0x0f, 0xb7, 0x8e, 0x18, 0x00, 0x66, 0xf7, 0xf1, 0xfe, 0xc2, 0x88, 0xd1, 0x66, 0x89, 0xc2,
    0x66, 0xc1, 0xea, 0x10, 0xf7, 0xb6, 0x1a, 0x00, 0x88, 0xd6, 0x8a, 0x96, 0x40, 0x00, 0x88, 0xc5,
    0xd0, 0xcc, 0xd0, 0xcc, 0x08, 0xe1, 0xb8, 0x01, 0x02, 0xcd, 0x13, 0x72, 0x0f, 0x66, 0x61, 0x66,
    0x40, 0x8c, 0xc2, 0x83, 0xc2, 0x20, 0x8e, 0xc2, 0xe2, 0xc1, 0x07, 0xc3, 0xbe, 0xb9, 0x7d, 0xe8,
    0x14, 0x00, 0xeb, 0x06, 0xbe, 0xc6, 0x7d, 0xe8, 0x0c, 0x00, 0xbe, 0xda, 0x7d, 0xe8, 0x06, 0x00,
    0x31, 0xc0, 0xcd, 0x16, 0xcd, 0x19, 0xac, 0x08, 0xc0, 0x74, 0x09, 0xb4, 0x0e, 0xbb, 0x07, 0x00,
    0xcd, 0x10, 0xeb, 0xf2, 0xc3, 0x00, 0x00, 0x00, 0x00, 0x44, 0x69, 0x73, 0x6b, 0x20, 0x65, 0x72,
    0x72, 0x6f, 0x72, 0x0d, 0x0a, 0x00, 0x46, 0x69, 0x6c, 0x65, 0x20, 0x73, 0x79, 0x73, 0x74, 0x65,
    0x6d, 0x20, 0x65, 0x72, 0x72, 0x6f, 0x72, 0x0d, 0x0a, 0x00, 0x50, 0x72, 0x65, 0x73, 0x73, 0x20,
    0x61, 0x6e, 0x79, 0x20, 0x6b, 0x65, 0x79, 0x20, 0x74, 0x6f, 0x20, 0x72, 0x65, 0x73, 0x74, 0x61,
    0x72, 0x74, 0x0d, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xaa,
    0x66, 0x8b, 0x86, 0x2c, 0x00, 0x66, 0x3d, 0xf8, 0xff, 0xff, 0x0f, 0x72, 0x03, 0xe9, 0x6c, 0x01,
    0xbb, 0x00, 0x20, 0x8e, 0xc3, 0xe8, 0x26, 0x01, 0x31, 0xdb, 0x8a, 0x9e, 0x0d, 0x00, 0xc1, 0xe3,
    0x04, 0xb8, 0x00, 0x20, 0x8e, 0xc0, 0x31, 0xff, 0xbe, 0x9d, 0x7f, 0xb9, 0x0b, 0x00, 0xf3, 0xa6,
    0x74, 0x2b, 0x4b, 0x75, 0x03, 0xe9, 0x44, 0x01, 0x8c, 0xc0, 0x83, 0xc0, 0x02, 0x8e, 0xc0, 0x31,
    0xff, 0xbe, 0x9d, 0x7f, 0xb9, 0x0b, 0x00, 0xf3, 0xa6, 0x74, 0x12, 0x4b, 0x75, 0xea, 0x66, 0x8b,
    0x86, 0x2c, 0x00, 0xe8, 0x6c, 0x00, 0x66, 0x89, 0x86, 0x2c, 0x00, 0xeb, 0xa3, 0xbe, 0xa8, 0x7f,
    0xe8, 0x43, 0xff, 0x31, 0xff, 0x31, 0xd2, 0x26, 0x8b, 0x45, 0x14, 0x66, 0xc1, 0xe0, 0x10, 0x26,
    0x8b, 0x45, 0x1a, 0x66, 0x83, 0xf8, 0x02, 0x73, 0x03, 0xe9, 0x18, 0xff, 0x66, 0x3d, 0xf8, 0xff,
    0xff, 0x0f, 0x72, 0x03, 0xe9, 0x0d, 0xff, 0xbb, 0x80, 0x0f, 0x8e, 0xc3, 0x66, 0x3d, 0xf8, 0xff,
    0xff, 0x0f, 0x73, 0x21, 0x66, 0x50, 0x31, 0xdb, 0x06, 0xe8, 0xa2, 0x00, 0x07, 0x31, 0xdb, 0x8a,
    0x9e, 0x0d, 0x00, 0xc1, 0xe3, 0x05, 0x8c, 0xc0, 0x01, 0xd8, 0x8e, 0xc0, 0x66, 0x58, 0x06, 0xe8,
    0x10, 0x00, 0x07, 0xeb, 0xd7, 0x8a, 0x96, 0x40, 0x00, 0x8a, 0x36, 0xfd, 0x7d, 0xea, 0x00, 0xf8,
    0x00, 0x00, 0x66, 0xc1, 0xe0, 0x02, 0x66, 0x89, 0xc1, 0x66, 0x31, 0xd2, 0x66, 0x0f, 0xb7, 0x9e,
    0x0b, 0x00, 0x66, 0x53, 0x66, 0xf7, 0xf3, 0x66, 0x0f, 0xb7, 0x9e, 0x0e, 0x00, 0x66, 0x01, 0xd8,
    0x66, 0x8b, 0x9e, 0x1c, 0x00, 0x66, 0x01, 0xd8, 0x66, 0x5b, 0x66, 0x4b, 0x66, 0x21, 0xd9, 0x66,
    0x0f, 0xb7, 0x9e, 0x28, 0x00, 0x83, 0xe3, 0x0f, 0x74, 0x18, 0x3a, 0x9e, 0x10, 0x00, 0x72, 0x03,
    0xe9, 0x91, 0xfe, 0x66, 0x50, 0x66, 0x8b, 0x86, 0x24, 0x00, 0x66, 0xf7, 0xe3, 0x66, 0x5a, 0x66,
    0x01, 0xd0, 0x66, 0x51, 0xbb, 0x00, 0x90, 0x8e, 0xc3, 0x66, 0x3b, 0x06, 0x3a, 0x7f, 0x74, 0x0c,
    0x66, 0xa3, 0x3a, 0x7f, 0x31, 0xdb, 0xb9, 0x01, 0x00, 0xe8, 0xaf, 0xfd, 0x66, 0x59, 0x26, 0x67,
    0x66, 0x8b, 0x01, 0x66, 0x25, 0xff, 0xff, 0xff, 0x0f, 0xc3, 0xff, 0xff, 0xff, 0xff, 0x66, 0x48,
    0x66, 0x48, 0x66, 0x31, 0xd2, 0x66, 0x0f, 0xb6, 0x9e, 0x0d, 0x00, 0x66, 0xf7, 0xe3, 0x66, 0x50,
    0x66, 0x31, 0xd2, 0x66, 0x0f, 0xb6, 0x86, 0x10, 0x00, 0x66, 0xf7, 0xa6, 0x24, 0x00, 0x66, 0x0f,
    0xb7, 0x9e, 0x0e, 0x00, 0x66, 0x01, 0xd8, 0x66, 0x03, 0x86, 0x1c, 0x00, 0x66, 0x5b, 0x66, 0x01,
    0xd8, 0x31, 0xdb, 0x0f, 0xb6, 0x8e, 0x0d, 0x00, 0xe8, 0x60, 0xfd, 0xc3, 0xbe, 0x85, 0x7f, 0xe8,
    0x24, 0xfe, 0xe9, 0x15, 0xfe, 0x66, 0x72, 0x65, 0x65, 0x6c, 0x64, 0x72, 0x2e, 0x73, 0x79, 0x73,
    0x20, 0x6e, 0x6f, 0x74, 0x20, 0x66, 0x6f, 0x75, 0x6e, 0x64, 0x0d, 0x0a, 0x00, 0x46, 0x52, 0x45,
    0x45, 0x4c, 0x44, 0x52, 0x20, 0x53, 0x59, 0x53, 0x4c, 0x6f, 0x61, 0x64, 0x69, 0x6e, 0x67, 0x20,
    0x46, 0x72, 0x65, 0x65, 0x4c, 0x6f, 0x61, 0x64, 0x65, 0x72, 0x2e, 0x2e, 0x2e, 0x0d, 0x0a, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xaa,
};

unsigned char fat_data[] =
{
    0xeb, 0x3c, 0x90, 0x46, 0x72, 0x4c, 0x64, 0x72, 0x31, 0x2e, 0x30, 0x00, 0x02, 0x01, 0x01, 0x00,
    0x02, 0xe0, 0x00, 0x40, 0x0b, 0xf0, 0x09, 0x00, 0x12, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x29, 0x00, 0x00, 0x00, 0x00, 0x4e, 0x4f, 0x20, 0x4e, 0x41,
    0x4d, 0x45, 0x20, 0x20, 0x20, 0x20, 0x46, 0x41, 0x54, 0x31, 0x32, 0x20, 0x20, 0x20, 0x31, 0xc0,
    0x8e, 0xd0, 0xbd, 0x00, 0x7c, 0xbc, 0xf0, 0x7b, 0x8e, 0xd8, 0x8e, 0xc0, 0x80, 0xbe, 0x24, 0x00,
    0xff, 0x75, 0x04, 0x88, 0x96, 0x24, 0x00, 0xb4, 0x08, 0x8a, 0x96, 0x24, 0x00, 0xcd, 0x13, 0x73,
    0x05, 0xb9, 0xff, 0xff, 0x88, 0xce, 0x88, 0xeb, 0x88, 0xcf, 0xc0, 0xef, 0x06, 0x80, 0xe1, 0x3f,
    0x66, 0x0f, 0xb6, 0xc6, 0x66, 0x0f, 0xb7, 0xdb, 0x66, 0x0f, 0xb6, 0xc9, 0x66, 0x40, 0x66, 0x43,
    0x66, 0xf7, 0xe1, 0x66, 0xf7, 0xe3, 0x66, 0x89, 0x46, 0xf8, 0x31, 0xc0, 0x31, 0xc9, 0x8a, 0x86,
    0x10, 0x00, 0xf7, 0xa6, 0x16, 0x00, 0x03, 0x86, 0x1c, 0x00, 0x13, 0x96, 0x1e, 0x00, 0x03, 0x86,
    0x0e, 0x00, 0x11, 0xca, 0x89, 0x46, 0xfc, 0x89, 0x56, 0xfe, 0x8b, 0xb6, 0x11, 0x00, 0x60, 0x31,
    0xd2, 0xb8, 0x20, 0x00, 0xf7, 0xe6, 0x8b, 0x9e, 0x0b, 0x00, 0x01, 0xd8, 0x48, 0xf7, 0xf3, 0x01,
    0x46, 0xfc, 0x11, 0x4e, 0xfe, 0x61, 0xbb, 0xe0, 0x07, 0x8e, 0xc3, 0x31, 0xdb, 0x31, 0xc9, 0x41,
    0x31, 0xff, 0x06, 0xe8, 0x75, 0x00, 0x07, 0x26, 0x38, 0x2d, 0x74, 0x3a, 0x60, 0xb1, 0x0b, 0xbe,
    0xe6, 0x7d, 0xf3, 0xa6, 0x61, 0x74, 0x0e, 0x4e, 0x74, 0x2c, 0x83, 0xc7, 0x20, 0x81, 0xff, 0x00,
    0x02, 0x72, 0xe4, 0xeb, 0xd1, 0x26, 0x8b, 0x45, 0x1a, 0x50, 0x68, 0x80, 0x0f, 0x07, 0xe8, 0x38,
    0x00, 0x58, 0xc7, 0x46, 0xf6, 0x4b, 0x7d, 0xc7, 0x46, 0xf4, 0x39, 0x7d, 0xc7, 0x46, 0xf2, 0x22,
    0x7d, 0xea, 0x03, 0xf8, 0x00, 0x00, 0xbe, 0xd6, 0x7d, 0xe8, 0x06, 0x00, 0x31, 0xc0, 0xcd, 0x16,
    0xcd, 0x19, 0xac, 0x08, 0xc0, 0x74, 0x09, 0xb4, 0x0e, 0xbb, 0x07, 0x00, 0xcd, 0x10, 0xeb, 0xf2,
    0xc3, 0xbe, 0xc9, 0x7d, 0xe8, 0xeb, 0xff, 0xeb, 0xe3, 0x48, 0x48, 0x30, 0xed, 0x8a, 0x8e, 0x0d,
    0x00, 0xf7, 0xe1, 0x03, 0x46, 0xfc, 0x13, 0x56, 0xfe, 0x31, 0xdb, 0x60, 0x49, 0x01, 0xc8, 0x83,
    0xd2, 0x00, 0x3b, 0x56, 0xfa, 0x77, 0x07, 0x72, 0x33, 0x3b, 0x46, 0xf8, 0x76, 0x2e, 0x61, 0x60,
    0x6a, 0x00, 0x6a, 0x00, 0x52, 0x50, 0x06, 0x53, 0x6a, 0x01, 0x6a, 0x10, 0x89, 0xe6, 0x8a, 0x96,
    0x24, 0x00, 0xb4, 0x42, 0xcd, 0x13, 0x72, 0xb9, 0x83, 0xc4, 0x10, 0x61, 0x40, 0x83, 0xd2, 0x00,
    0x53, 0x8c, 0xc3, 0x83, 0xc3, 0x20, 0x8e, 0xc3, 0x5b, 0xe2, 0xd4, 0xc3, 0x61, 0x60, 0x91, 0x92,
    0x31, 0xd2, 0xf7, 0xb6, 0x18, 0x00, 0x91, 0xf7, 0xb6, 0x18, 0x00, 0x42, 0x87, 0xd1, 0xf7, 0xb6,
    0x1a, 0x00, 0x88, 0xd6, 0x8a, 0x96, 0x24, 0x00, 0x88, 0xc5, 0xc0, 0xcc, 0x02, 0x08, 0xe1, 0xb8,
    0x01, 0x02, 0xcd, 0x13, 0x0f, 0x82, 0x79, 0xff, 0x61, 0x40, 0x75, 0x01, 0x42, 0x53, 0x8c, 0xc3,
    0x83, 0xc3, 0x20, 0x8e, 0xc3, 0x5b, 0xe2, 0xc5, 0xc3, 0x44, 0x69, 0x73, 0x6b, 0x20, 0x65, 0x72,
    0x72, 0x6f, 0x72, 0x0d, 0x0a, 0x00, 0x4c, 0x64, 0x72, 0x20, 0x6e, 0x6f, 0x74, 0x20, 0x66, 0x6f,
    0x75, 0x6e, 0x64, 0x0d, 0x0a, 0x00, 0x46, 0x52, 0x45, 0x45, 0x4c, 0x44, 0x52, 0x20, 0x53, 0x59,
    0x53, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xaa,
};



bool InstallBootSector(char* lpszVolumeType);

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		printf("syntax: installfreeldr /dev/[disk_device][partition_number] [fs_type] (fs_type can be fat or fat32)\n");
		return -1;
	}

	if (!OpenVolume(argv[1]))
	{
		printf("Exiting program...\n");
		return -1;
	}

	if (!InstallBootSector(argv[2]))
	{
		printf("Exiting program...\n");
		return -1;
	}

	CloseVolume();

	printf("You must now copy freeldr.sys, rosload.exe and freeldr.ini to %s.\n", argv[1]);

	return 0;
}


bool InstallBootSector(char* lpszVolumeType)
{
	unsigned char BootSectorBuffer[512];

	if (!ReadVolumeSector(0, BootSectorBuffer))
	{
		return false;
	}

	if (strcasecmp(lpszVolumeType, "fat32") == 0)
	{
		//
		// Update the BPB in the new boot sector
		//
		memcpy((fat32_data+3), (BootSectorBuffer+3), 87 /*fat32 BPB length*/);

		//
		// Write out new boot sector
		//
		if (!WriteVolumeSector(0, fat32_data))
		{
			return false;
		}

		//
		// Write out new extra sector
		//
		if (!WriteVolumeSector(14, (fat32_data+512)))
		{
			return false;
		}
    }

	else if (strcasecmp(lpszVolumeType, "fat") == 0)
	{
		//
		// Update the BPB in the new boot sector
 		//
		memcpy((fat_data+3), (BootSectorBuffer+3), 59 /*fat BPB length*/);

		//
		// Write out new boot sector
		//
		if (!WriteVolumeSector(0, fat_data))
		{
			return false;
		}
	}

	else
	{
		printf("%s:%d: ", __FILE__, __LINE__);
		printf("File system type %s unknown.\n", lpszVolumeType);
		return false;
	}

	printf("%s boot sector installed.\n", lpszVolumeType);

	return true;
}
