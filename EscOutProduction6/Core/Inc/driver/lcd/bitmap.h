/*
 * bitmap.h
 *
 *  Created on: Oct 9, 2024
 *      Author: Artur
 */

#ifndef INC_DRIVER_LCD_BITMAP_H_
#define INC_DRIVER_LCD_BITMAP_H_

#define IMG_WIDTH  (64)
#define IMG_HEIGHT (64)

const uint16_t eye_img_64x64 [] = {
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x5def, 0x7def, 0x7def, 0x9ef7, 0x9ef7, 0x9ef7, 0x9ef7, 0x7def, 0x7def, 0x5def, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x5def, 0x9ef7, 0xdfff, 0xffff, 0x3cef, 0xf7c5, 0x13ad, 0x7194, 0x508c, 0x3084, 0x718c, 0x13a5, 0xf7c5, 0x3cef, 0xffff, 0xdfff, 0x9ef7, 0x5def, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x5def, 0xbef7, 0xffff, 0x58ce, 0xce7b, 0xa639, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0008, 0xa641, 0xef83, 0x79ce, 0xffff, 0xbef7, 0x5def, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x5def, 0xdfff, 0x3cef, 0x6d73, 0x2008, 0x0000, 0x0000, 0x0000, 0x0008, 0x2008, 0x2008, 0x2008, 0x2008, 0x2008, 0x2008, 0x2008, 0x2010, 0x2010, 0x4010, 0x2010, 0x0008, 0x0000, 0x0000, 0x4010, 0x8d7b, 0xfbe6, 0xdfff, 0x5def, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x5def, 0xffff, 0x99d6, 0x0742, 0x0000, 0x0000, 0x0000, 0x2008, 0x2008, 0x2008, 0x2008, 0x2008, 0x2010, 0x2008, 0x2010, 0x4110, 0x4010, 0x4010, 0x4010, 0x6118, 0x6118, 0x6118, 0x4110, 0x4110, 0x4110, 0x4010, 0x0008, 0x0000, 0x074a, 0x79d6, 0xffff, 0x5def, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x9ef7, 0x9df7, 0x4852, 0x0000, 0x0000, 0x2008, 0x2008, 0x2008, 0x2008, 0x2008, 0x2008, 0x6118, 0x6118, 0x8120, 0x6118, 0x6118, 0xc220, 0xa220, 0x6118, 0x6118, 0xa220, 0xe330, 0x8120, 0xc228, 0x8120, 0x6118, 0x6118, 0x6120, 0x6120, 0x2010, 0x0000, 0x695a, 0x5def, 0x9ef7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0xffff, 0xd29c, 0x0000, 0x0000, 0x0008, 0x2008, 0x2008, 0x2008, 0x2008, 0x2008, 0x4010, 0x4110, 0x8120, 0xc228, 0xc228, 0xc228, 0x4441, 0x4449, 0x4441, 0xc230, 0x8120, 0x2339, 0xe230, 0x0339, 0xe330, 0x6118, 0x6118, 0x6120, 0x8128, 0x8120, 0x8120, 0x6120, 0x2018, 0x0008, 0x919c, 0xffff, 0x5def, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x5def, 0xffff, 0xc641, 0x0000, 0x0008, 0x2008, 0x2008, 0x2008, 0x2010, 0x4110, 0x4110, 0x6118, 0x6118, 0x4110, 0xa228, 0x6449, 0x8451, 0xa551, 0xa551, 0xc551, 0x0339, 0x8128, 0xe338, 0x8549, 0xa230, 0xe238, 0x8128, 0x6120, 0x6128, 0x8128, 0x8228, 0x8128, 0x6120, 0x8128, 0x8128, 0x6128, 0x0008, 0xe749, 0x9ef7, 0x5def, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x7def, 0x3cef, 0x2008, 0x0000, 0x2008, 0x2008, 0x2008, 0x2008, 0x4010, 0x6118, 0x6118, 0x8120, 0xc228, 0xe330, 0x0339, 0x2249, 0x6349, 0xe559, 0x0662, 0x8551, 0x4449, 0x6449, 0x4120, 0xc551, 0xa551, 0x8230, 0x2249, 0x0241, 0xa230, 0x8230, 0xc238, 0xa238, 0x8128, 0x8230, 0x6128, 0x6128, 0x8228, 0x8128, 0x2018, 0x6120, 0xfbe6, 0x7eef, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x9ef7, 0xdade, 0x0000, 0x0000, 0x2008, 0x2008, 0x2008, 0x2008, 0x4110, 0x8118, 0x6118, 0x8118, 0xa228, 0x0339, 0x2441, 0x6449, 0xa351, 0xe361, 0x6351, 0xa451, 0x476a, 0x256a, 0x4349, 0xc238, 0xe659, 0xa551, 0xe238, 0xc359, 0x2249, 0xc238, 0x2241, 0x0241, 0xe238, 0x8230, 0xe238, 0x2341, 0xc238, 0x6128, 0x8128, 0x8128, 0x4120, 0x0010, 0xbad6, 0x9eef, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x7def, 0xdade, 0x0000, 0x0000, 0x2008, 0x2008, 0x2008, 0x2008, 0x4010, 0x6118, 0x6118, 0xa220, 0xa220, 0x8220, 0x2441, 0x8551, 0xc651, 0xe461, 0x236a, 0xe361, 0xc459, 0x8772, 0x8572, 0xc359, 0x2249, 0x8451, 0x8451, 0xe238, 0x0362, 0x6449, 0xe238, 0xa359, 0x2249, 0x2349, 0xa130, 0x2341, 0x476a, 0xc551, 0xe238, 0x8130, 0x6128, 0x6128, 0x6128, 0x0010, 0x79d6, 0x7def, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x5def, 0x5def, 0x0000, 0x0000, 0x2008, 0x2008, 0x2008, 0x2008, 0x4010, 0x4010, 0x8118, 0x8120, 0xa220, 0xe230, 0xc230, 0xa451, 0xe659, 0x2762, 0x6572, 0xc77a, 0xc682, 0xc77a, 0x8872, 0x0562, 0x246a, 0x8351, 0xc459, 0xa551, 0x4249, 0x446a, 0xc459, 0x8351, 0xc359, 0xa57a, 0x2249, 0x6449, 0x2762, 0x2762, 0xc551, 0x8549, 0x0341, 0xe338, 0xc230, 0x8128, 0x6128, 0x0018, 0x1be7, 0x7def, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0xffff, 0x4010, 0x0000, 0x2008, 0x2008, 0x2008, 0x2010, 0x4110, 0x4010, 0x6118, 0x8220, 0x0331, 0xc228, 0xe238, 0xe238, 0x0339, 0xe659, 0x4a83, 0xeb9b, 0xee93, 0xec9b, 0x2ca4, 0x6a8b, 0x8872, 0x068b, 0xc57a, 0xc682, 0x4249, 0x2341, 0x6349, 0x456a, 0xa57a, 0x246a, 0xe58a, 0x456a, 0xc651, 0x2762, 0xe659, 0x686a, 0x686a, 0xe659, 0x0341, 0x8230, 0x8230, 0xa230, 0x6128, 0x8228, 0x9ef7, 0x5def, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0xffff, 0xe741, 0x0000, 0x2008, 0x2008, 0x2008, 0x4010, 0x6118, 0x6118, 0x6118, 0x8118, 0x8220, 0xe330, 0x6449, 0xc230, 0x2341, 0x2762, 0x4f9c, 0x12ad, 0xb5c5, 0x37ce, 0x17ce, 0xd4cd, 0x30bd, 0x2a83, 0x478b, 0xe582, 0x478b, 0xa259, 0x2562, 0x6349, 0x6472, 0x466a, 0x278b, 0x4793, 0x676a, 0x2762, 0x065a, 0x486a, 0x2762, 0x8551, 0x6128, 0xc551, 0x4441, 0xe238, 0xa238, 0x8128, 0x2020, 0x285a, 0xffff, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x9ef7, 0xf3a4, 0x0000, 0x2008, 0x2008, 0x2008, 0x4010, 0x8118, 0xa220, 0xc228, 0x6118, 0xa228, 0xe238, 0xc228, 0x8549, 0xc97a, 0xad8b, 0xf2ac, 0x17c6, 0x78d6, 0xbade, 0xfbde, 0x1be7, 0xfbde, 0x16ce, 0x8c8b, 0x4693, 0xa7a3, 0x278b, 0x236a, 0xe682, 0x679b, 0x879b, 0xa67a, 0xc482, 0xc582, 0xe97a, 0x065a, 0x2762, 0x686a, 0x2341, 0xa130, 0xc559, 0xa87a, 0xe659, 0xc659, 0x4449, 0xa230, 0x6128, 0x0010, 0xf3a4, 0x9ef7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x5def, 0xbef7, 0x0000, 0x0008, 0x2008, 0x2008, 0x2008, 0x6118, 0xa220, 0xe330, 0xe330, 0x0341, 0xc238, 0xc230, 0xe230, 0xa551, 0x90a4, 0xd6c5, 0x58d6, 0xbade, 0xfade, 0xfbe6, 0x3ce7, 0x3ce7, 0x5def, 0x79d6, 0x90a4, 0x29ac, 0xa6a3, 0xc57a, 0x0683, 0xa79b, 0x28b4, 0x889b, 0x09a4, 0x6793, 0x278b, 0xa872, 0xe87a, 0x2762, 0x4449, 0xa359, 0x0783, 0xc97a, 0xc97a, 0xc97a, 0x686a, 0xe659, 0x8549, 0x8130, 0x6128, 0x0018, 0x9ef7, 0x5def, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0xffff, 0x8952, 0x0000, 0x2008, 0x2008, 0x2010, 0x4010, 0x4110, 0xa220, 0x4441, 0x6449, 0x6451, 0x2341, 0xa230, 0xa551, 0x0a7b, 0x34b5, 0x99de, 0xdade, 0xfbde, 0x1ce7, 0x3ce7, 0x3ce7, 0x5def, 0x7def, 0xdbde, 0xf1b4, 0x08ac, 0x879b, 0xc582, 0x09a4, 0x09ac, 0x288b, 0x6793, 0x498b, 0x6793, 0x278b, 0xe461, 0x686a, 0xa551, 0xa551, 0x676a, 0xa77a, 0xc67a, 0xe659, 0x8872, 0x8872, 0x0762, 0xa551, 0x2341, 0x8128, 0x2020, 0xaa62, 0xdfff, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x5def, 0xdbde, 0x0000, 0x2008, 0x2008, 0x2008, 0x6118, 0x8120, 0x4010, 0x6118, 0x0331, 0x8451, 0xc559, 0xa359, 0x6449, 0x0662, 0xcd93, 0x37ce, 0xfbde, 0xfbe6, 0x1ce7, 0x3ce7, 0x5def, 0x5def, 0x7def, 0x9ef7, 0xfbde, 0xb3cd, 0x4ab4, 0xe582, 0xa872, 0xe682, 0x0562, 0x236a, 0x0462, 0xa772, 0xa7a3, 0x246a, 0xa259, 0x8872, 0xa259, 0x6772, 0xc97a, 0xc659, 0xc77a, 0x488b, 0x6772, 0x8772, 0x065a, 0x4762, 0xe659, 0xc238, 0x6128, 0x0010, 0xdbde, 0x5def, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0xdfff, 0x484a, 0x0000, 0x2008, 0x2008, 0x2010, 0x8118, 0xe328, 0x8220, 0x6118, 0xc228, 0x4441, 0x2341, 0x6672, 0x6349, 0xa872, 0x0f94, 0x99d6, 0x1ce7, 0x3ce7, 0x3ce7, 0x5def, 0x7def, 0x7def, 0x7def, 0x9ef7, 0x3ce7, 0x15d6, 0x6cb4, 0x8472, 0x075a, 0xe582, 0x6472, 0xc57a, 0xa551, 0x268b, 0xe7ab, 0x6472, 0x268b, 0xa79b, 0xe461, 0xc559, 0x8872, 0xa459, 0x4349, 0x476a, 0xa772, 0xa77a, 0xc459, 0xe240, 0xc230, 0x8128, 0x8128, 0x2020, 0x8962, 0xdfff, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x5def, 0x7df7, 0x0000, 0x2008, 0x2008, 0x2010, 0x8118, 0xc228, 0xe230, 0x6449, 0x2339, 0xe330, 0x0339, 0xc651, 0x266a, 0x268b, 0x6572, 0x6dac, 0x37ce, 0x5def, 0x5def, 0x5def, 0x7def, 0x7def, 0x7def, 0x7def, 0x9ef7, 0x9ef7, 0x15d6, 0x2dcd, 0x0362, 0xc459, 0x068b, 0x6472, 0x456a, 0x0883, 0x879b, 0x659b, 0x68bc, 0x8abc, 0x2883, 0xc77a, 0x6672, 0x6672, 0xe659, 0x2762, 0xe659, 0x2341, 0xc359, 0x676a, 0xc87a, 0x476a, 0x0241, 0x6128, 0x8128, 0x0010, 0x5def, 0x5def, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x9ef7, 0xcf7b, 0x0000, 0x2008, 0x2010, 0x4010, 0xa220, 0x0339, 0x6449, 0xe559, 0xa551, 0xa551, 0x8449, 0x0662, 0x466a, 0xa259, 0x847a, 0x6793, 0x10bd, 0x5de7, 0x7def, 0x7def, 0x7def, 0x7def, 0x9ef7, 0x9ef7, 0x9ef7, 0xbff7, 0x51c5, 0xe9a3, 0xe582, 0x847a, 0xe582, 0xa57a, 0x6793, 0xc582, 0x859b, 0x49b4, 0xc8a3, 0xe559, 0xc99b, 0xc7a3, 0x058b, 0xc559, 0x2762, 0x2341, 0xe140, 0x6572, 0xe882, 0x4a8b, 0xe87a, 0xa551, 0xa230, 0x8128, 0x8128, 0x0020, 0xef8b, 0x9ef7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0xffff, 0x6110, 0x0008, 0x2010, 0x4010, 0x4118, 0x8120, 0xc230, 0x4449, 0x6449, 0xa551, 0xe659, 0x2762, 0x857a, 0x0783, 0xc77a, 0xc361, 0x268b, 0x29ac, 0x72c5, 0xbff7, 0x7def, 0x7def, 0x9ef7, 0x9ef7, 0x9ef7, 0x9ef7, 0xbff7, 0x15d6, 0xa6ab, 0xe7ab, 0x48bc, 0x6693, 0x058b, 0x27b4, 0xeebc, 0x1be7, 0xdff7, 0x0d9c, 0xe87a, 0xe7ab, 0x07ac, 0xc359, 0x476a, 0x8230, 0xe240, 0xc67a, 0x8972, 0xa972, 0xc559, 0xc461, 0x4349, 0x8230, 0x6128, 0x6128, 0x6128, 0xc230, 0xffff, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x5def, 0xbade, 0x0000, 0x2008, 0x2008, 0x4110, 0x4110, 0x6118, 0xa228, 0x4341, 0x8130, 0x8451, 0x8872, 0xc459, 0x6572, 0xe682, 0x857a, 0xc57a, 0x2562, 0xa67a, 0x4ab4, 0xb4c5, 0xdff7, 0x9ef7, 0x9ef7, 0x9ef7, 0x9ef7, 0x9ef7, 0xdff7, 0x16ce, 0x0000, 0x0000, 0xe128, 0x8572, 0x07b4, 0x69bc, 0x3ce7, 0xdff7, 0xffff, 0x75bd, 0x847a, 0x859b, 0x869b, 0x2883, 0x075a, 0xc459, 0x466a, 0xa872, 0x0983, 0x676a, 0x666a, 0x4349, 0xa238, 0x6128, 0xc238, 0x0341, 0x8128, 0x0010, 0xdade, 0x5def, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x9ef7, 0x308c, 0x0000, 0x2008, 0x4010, 0x4110, 0x6118, 0x6120, 0x8220, 0xa228, 0xc230, 0xc238, 0x046a, 0xa57a, 0x236a, 0x268b, 0x4693, 0x847a, 0xe58a, 0x0462, 0xa57a, 0x49bc, 0xb8e6, 0xdff7, 0x9ef7, 0x9ef7, 0x9ef7, 0x9ef7, 0xffff, 0x17ce, 0x0000, 0x0000, 0x0000, 0x0000, 0x0008, 0x57de, 0xbff7, 0x9ef7, 0xdff7, 0x15ce, 0x669b, 0x4793, 0x0983, 0xa459, 0xa99b, 0xc67a, 0x4472, 0xc582, 0x8351, 0x6449, 0xa451, 0x4449, 0xa238, 0xa551, 0x2762, 0x8549, 0x8128, 0x0020, 0x5094, 0x9ef7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0xdfff, 0x074a, 0x0000, 0x4010, 0x4010, 0x4110, 0x6120, 0x6120, 0x8128, 0xa228, 0xa230, 0xe240, 0xe361, 0x488b, 0xc57a, 0xc482, 0x4693, 0x6793, 0x869b, 0x4593, 0xa7a3, 0x89c4, 0x89d4, 0xf9ee, 0xffff, 0xffff, 0xffff, 0xffff, 0xdae6, 0xa541, 0x0000, 0x0000, 0x0000, 0x0000, 0xaa6a, 0xffff, 0x9ef7, 0xbef7, 0x3bef, 0xa89b, 0xe559, 0x2562, 0x4572, 0x4472, 0x4693, 0x6472, 0x4349, 0x8549, 0x4349, 0x4449, 0x6349, 0xa551, 0xc551, 0x686a, 0x476a, 0xe659, 0xa230, 0x2020, 0x485a, 0xdff7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0xffff, 0x2008, 0x2008, 0x4010, 0x4110, 0x6118, 0xa230, 0xa228, 0x6351, 0x4349, 0x246a, 0xa359, 0xe361, 0x268b, 0x065a, 0x6449, 0xe361, 0xa79b, 0xe682, 0x28ac, 0x08ac, 0xe7ab, 0xcad4, 0x0010, 0xc649, 0xae83, 0x2b73, 0x485a, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8d83, 0xffff, 0xffff, 0xffff, 0xaeb4, 0xa130, 0xa67a, 0x879b, 0xa79b, 0xa57a, 0x669b, 0x2249, 0xc551, 0xe659, 0xa551, 0xc551, 0x476a, 0x8872, 0xa872, 0x686a, 0x686a, 0xc659, 0x8128, 0x6128, 0x8128, 0xffff, 0x3ce7, 0x3ce7,
		0x3ce7, 0x5de7, 0x7df7, 0x0000, 0x4010, 0x4110, 0x6118, 0x6118, 0x8128, 0xc230, 0xa459, 0x8251, 0x2241, 0x8351, 0x6349, 0x4349, 0xe682, 0xa67a, 0x6449, 0xa359, 0x6693, 0x879b, 0x28b4, 0xc582, 0xa351, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0f94, 0xf7cd, 0x32b5, 0x236a, 0x847a, 0xe8ab, 0xa89b, 0x69bc, 0xa9c4, 0x4ce5, 0x09ac, 0x466a, 0xc97a, 0xa972, 0xc972, 0x0a7b, 0xa87a, 0xa972, 0xe97a, 0xa551, 0xa230, 0x8128, 0x8128, 0x0010, 0xbef7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x7def, 0x18c6, 0x0000, 0x4110, 0x4110, 0x8120, 0x6120, 0x6120, 0xe238, 0x6251, 0x4449, 0x0562, 0xa359, 0x6349, 0x8351, 0x4249, 0xa57a, 0xc582, 0xc47a, 0xe7ab, 0xa9c4, 0x869b, 0x27b4, 0xe238, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4249, 0x869b, 0xc8a3, 0xe8a3, 0x07ac, 0xc582, 0xe682, 0xe582, 0x6351, 0x065a, 0xe659, 0x476a, 0x8872, 0xa972, 0x0662, 0x2762, 0x476a, 0x065a, 0xe238, 0x6128, 0x0018, 0x79d6, 0x5def, 0x3ce7,
		0x3ce7, 0x7def, 0x14ad, 0x0000, 0x4110, 0x6118, 0x8120, 0x4341, 0xa230, 0x8230, 0xc230, 0x0339, 0x8451, 0xa359, 0x446a, 0xa47a, 0x6472, 0x4472, 0x857a, 0x6693, 0xc7a3, 0x08b4, 0x07ac, 0xa7a3, 0x4010, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xe238, 0xc361, 0xe582, 0xe8a3, 0xe8a3, 0xa89b, 0xe682, 0xe238, 0x0241, 0xe461, 0xa872, 0x676a, 0x686a, 0x2762, 0x0662, 0x476a, 0x686a, 0xc651, 0x2341, 0x8128, 0x0018, 0x95b5, 0x7def, 0x3ce7,
		0x3ce7, 0x9ef7, 0x7194, 0x0000, 0x6118, 0x6118, 0x8120, 0x2341, 0xe238, 0xc238, 0x8130, 0xe240, 0x0241, 0x2249, 0x857a, 0xe58a, 0xa6a3, 0x869b, 0x48bc, 0x89c4, 0x68bc, 0x48b4, 0x89c4, 0xc582, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4018, 0x857a, 0xc582, 0x847a, 0x0583, 0x0462, 0x4541, 0x0662, 0xc559, 0xc359, 0xc361, 0xe361, 0x246a, 0xc459, 0xa551, 0x6449, 0x6449, 0x0339, 0xa230, 0x8128, 0x0018, 0xf3a4, 0x7eef, 0x3ce7,
		0x3ce7, 0x9ef7, 0x308c, 0x0008, 0x6118, 0x6118, 0xa228, 0x2341, 0x065a, 0xa551, 0xa551, 0x8451, 0xe338, 0x6349, 0xa359, 0xe682, 0x8893, 0x8793, 0x068b, 0x48bc, 0x28b4, 0x6693, 0xe7ab, 0x0239, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xa128, 0x869b, 0xc7a3, 0x4693, 0xe682, 0xa359, 0x8251, 0x236a, 0xc57a, 0xc582, 0x256a, 0x6451, 0x0241, 0x0341, 0x2341, 0xa230, 0x8130, 0x0341, 0xc238, 0x6128, 0x0020, 0xb29c, 0x9eef, 0x3ce7,
		0x3ce7, 0x9ef7, 0x308c, 0x0008, 0x6118, 0x6120, 0x6120, 0xe338, 0x6449, 0xe659, 0x0762, 0xc230, 0x8549, 0x4762, 0x2762, 0xe659, 0xc67a, 0x058b, 0xe582, 0x28b4, 0x879b, 0x4693, 0xe582, 0x8120, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4118, 0xc582, 0xc9a3, 0x09ac, 0x4893, 0x246a, 0x456a, 0x6572, 0x246a, 0x2562, 0x266a, 0x476a, 0x0762, 0x8872, 0x8872, 0xa972, 0x8549, 0x6449, 0xa230, 0x8130, 0x0018, 0xb29c, 0x9eef, 0x3ce7,
		0x3ce7, 0x9ef7, 0x7194, 0x0008, 0x6118, 0x6120, 0x8128, 0xa230, 0x8128, 0x6128, 0x8130, 0x8130, 0x8130, 0x6128, 0xe461, 0x857a, 0xe582, 0x4693, 0xe6ab, 0x869b, 0x48b4, 0xe9cc, 0xa7a3, 0x2010, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xa359, 0x869b, 0x4693, 0xe8a3, 0x0783, 0xe97a, 0xe659, 0x6541, 0x6449, 0x4349, 0xa359, 0xc359, 0x256a, 0xe461, 0xe659, 0xe659, 0x0562, 0x2762, 0x6449, 0x6128, 0x0018, 0xf3a4, 0x7def, 0x3ce7,
		0x3ce7, 0x7def, 0x34ad, 0x0008, 0x6120, 0x6120, 0x8128, 0x8551, 0x2662, 0x0662, 0x0662, 0x6349, 0x4149, 0xc461, 0x4572, 0x4249, 0x446a, 0x669b, 0xe582, 0x4593, 0x69bc, 0xc582, 0x046a, 0x246a, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xa128, 0xa9c4, 0xe9a3, 0x8bbc, 0x6abc, 0x889b, 0x478b, 0x879b, 0xc559, 0x4441, 0x8549, 0xc651, 0x2341, 0xe238, 0xa238, 0x8130, 0x0562, 0x8449, 0xc238, 0x8128, 0x0018, 0x75b5, 0x7def, 0x3ce7,
		0x3ce7, 0x7def, 0x17c6, 0x0008, 0x8120, 0x6120, 0x8128, 0x065a, 0x0983, 0x2662, 0x0562, 0x8772, 0x266a, 0x676a, 0x0562, 0xa359, 0xa359, 0xc361, 0x058b, 0xe361, 0xa57a, 0x6693, 0x847a, 0x4251, 0x4010, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x6118, 0x058b, 0xa89b, 0xe782, 0xab93, 0xabbc, 0x0dc5, 0xacbc, 0xe659, 0xc651, 0x0562, 0xe659, 0xa551, 0x6449, 0x0341, 0x2249, 0x4251, 0xa359, 0x8872, 0x2341, 0x6128, 0x0018, 0x79ce, 0x5def, 0x3ce7,
		0x3ce7, 0x5def, 0x5def, 0x0008, 0x8120, 0x6128, 0x6128, 0x4441, 0xa872, 0xe659, 0x2762, 0x8872, 0xc97a, 0xa872, 0x466a, 0x666a, 0x857a, 0x669b, 0xc7a3, 0x68bc, 0xc7a3, 0xe682, 0xc7a3, 0xe7ab, 0xc359, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0008, 0x0231, 0xe7ab, 0xe9a3, 0x0aac, 0xea9b, 0x4a83, 0x0983, 0x0ec5, 0x0ba4, 0xe659, 0x075a, 0xc551, 0xe659, 0x686a, 0xe659, 0xe238, 0x0241, 0x0241, 0x0341, 0x0339, 0x6128, 0x0010, 0x7def, 0x3de7, 0x3ce7,
		0x3ce7, 0x3ce7, 0xffff, 0x4020, 0x6120, 0x8128, 0x6128, 0xa230, 0x676a, 0xa872, 0x686a, 0x2762, 0xc551, 0x4449, 0x4349, 0x6351, 0x6349, 0xc459, 0x456a, 0xa77a, 0x6793, 0xc7a3, 0x48bc, 0xa6a3, 0xc359, 0x2010, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0008, 0x4110, 0xe58a, 0xc89b, 0xacbc, 0xacbc, 0xccbc, 0xeb9b, 0xcb9b, 0x2ca4, 0x91d5, 0xedc4, 0x8772, 0xe659, 0x8549, 0x4449, 0x065a, 0x0341, 0xe238, 0x8230, 0x8128, 0xa230, 0x6128, 0x6120, 0xffff, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0xdff7, 0x0752, 0x4020, 0x8128, 0x8128, 0x0341, 0x065a, 0x8872, 0xe659, 0x6449, 0xe238, 0x0241, 0xe238, 0xa230, 0x6120, 0x2249, 0x8251, 0xa47a, 0xe7ab, 0xa7a3, 0x879b, 0xe7a3, 0x6693, 0x6472, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0008, 0x2008, 0x0008, 0xa57a, 0xaacc, 0x2aac, 0x4bac, 0xedc4, 0xeebc, 0x2e9c, 0x6ea4, 0x2d9c, 0x6dac, 0x70cd, 0x2ba4, 0xa872, 0x4762, 0xc651, 0xc559, 0xe238, 0xa230, 0x8128, 0x8228, 0x8230, 0x4120, 0x285a, 0xdff7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x9ef7, 0x308c, 0x0018, 0x8128, 0x8128, 0x0241, 0x2662, 0xc651, 0x8351, 0x2341, 0xc238, 0xc230, 0x8128, 0xc230, 0xa238, 0xe461, 0x89bc, 0x48b4, 0x0783, 0x48b4, 0x69bc, 0x29b4, 0x28b4, 0x68bc, 0x246a, 0x4118, 0x2008, 0x0008, 0x0000, 0x0000, 0x0000, 0x0008, 0x0008, 0x0000, 0xa120, 0xe58a, 0xa79b, 0x6bbc, 0x2de5, 0x2ecd, 0x6dac, 0x8dac, 0xcfb4, 0x30c5, 0x2da4, 0xefbc, 0xefbc, 0x4dac, 0x686a, 0x2762, 0x8872, 0x8551, 0xe238, 0x8230, 0x8230, 0x8228, 0x8228, 0x0020, 0x308c, 0x9ef7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x5def, 0x99d6, 0x0010, 0x8128, 0x8128, 0xa230, 0x4349, 0x8351, 0x8251, 0x2341, 0xa551, 0xc659, 0x6449, 0x4449, 0x6449, 0xe87a, 0x69bc, 0xa89b, 0xe7ab, 0xe8ab, 0xa99b, 0x08ac, 0xcacc, 0x69bc, 0xe58a, 0x036a, 0xe582, 0x6118, 0x8120, 0x2010, 0x2010, 0x0008, 0x0231, 0x857a, 0xc482, 0x6693, 0xccd4, 0x4a8b, 0x8cb4, 0x6cac, 0x0fbd, 0x6fa4, 0x6fa4, 0x91d5, 0x51c5, 0xcfb4, 0x6dac, 0x0fbd, 0x0983, 0x686a, 0x8549, 0x6449, 0x2341, 0x0241, 0xa230, 0x8128, 0x8228, 0x0010, 0x9ad6, 0x5def, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0xffff, 0xa228, 0x6128, 0x8128, 0x8128, 0x8128, 0xe240, 0xc359, 0x436a, 0x2662, 0x886a, 0xa972, 0xe659, 0xe238, 0x036a, 0x6abc, 0x49b4, 0x28b4, 0x0783, 0xc8a3, 0xcbcc, 0x899b, 0x6ab4, 0x8993, 0xa67a, 0x48b4, 0x07ac, 0xe58a, 0x847a, 0xe7ab, 0x07b4, 0x046a, 0x28b4, 0xc8a3, 0x0dcd, 0x6993, 0x0aac, 0x4bac, 0xacb4, 0x0ebd, 0xf0b4, 0x509c, 0xb1a4, 0xd2d5, 0x90a4, 0x4e9c, 0xceb4, 0xeebc, 0xa872, 0x0783, 0x6572, 0x0241, 0x2249, 0x8230, 0x8128, 0x6128, 0x8228, 0xffff, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x9ef7, 0xce83, 0x0020, 0x8228, 0x8128, 0x8128, 0x0241, 0x2662, 0xa77a, 0xc9a3, 0x686a, 0x6449, 0xa230, 0xc238, 0x8893, 0x468b, 0x889b, 0x4ded, 0xcccc, 0xca9b, 0x2ba4, 0x2ba4, 0xacbc, 0xa972, 0x8893, 0xacbc, 0xc7a3, 0x6693, 0x268b, 0x89c4, 0xcacc, 0xc8a3, 0x6bb4, 0xeb9b, 0x4cac, 0x2ca4, 0xedc4, 0x4fcd, 0x50cd, 0xefbc, 0xd2d5, 0xafac, 0xad8b, 0xd1b4, 0x30c5, 0x10bd, 0xaeb4, 0xadb4, 0xacb4, 0x2bac, 0x666a, 0x4449, 0x0341, 0x8128, 0x8128, 0x0020, 0xae83, 0x9ef7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x5def, 0x5def, 0x0010, 0x8128, 0x8228, 0x8128, 0xa230, 0x0662, 0xa972, 0x0983, 0x6572, 0xa230, 0xa551, 0x686a, 0x0883, 0xea9b, 0x8bbc, 0x2ecd, 0xadbc, 0x4cac, 0x4dac, 0x6a8b, 0xab8b, 0x6b8b, 0x8cb4, 0xedcc, 0x6bb4, 0x8bb4, 0xaa9b, 0xabbc, 0xacbc, 0xeb9b, 0x2ca4, 0xca9b, 0x8b8b, 0xaeb4, 0x6eac, 0x30c5, 0x71cd, 0xf0bc, 0xb1d5, 0xd2d5, 0xb2d5, 0x51c5, 0x70cd, 0x0d94, 0x6eac, 0xedbc, 0xab93, 0xe9a3, 0x8872, 0x686a, 0x8130, 0x8128, 0x8128, 0x0010, 0x3ce7, 0x5def, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0xffff, 0x695a, 0x2020, 0x8228, 0x8128, 0x8230, 0xa359, 0x8451, 0x4249, 0x058b, 0x8672, 0x2762, 0x2662, 0x288b, 0xa99b, 0x2983, 0x2fc5, 0x8dac, 0x6eac, 0xcb9b, 0xec9b, 0xed93, 0x4da4, 0xedc4, 0xadbc, 0x2ed5, 0x8cb4, 0xadbc, 0x2ed5, 0x4cac, 0x498b, 0xcdbc, 0x8cb4, 0x90d5, 0x70cd, 0x10bd, 0x30bd, 0x71cd, 0x50c5, 0x30c5, 0x51c5, 0x10bd, 0x91cd, 0xaeb4, 0xcd93, 0x686a, 0x0762, 0x676a, 0x886a, 0x8772, 0x0562, 0x6128, 0x8128, 0x2020, 0x485a, 0xffff, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x5def, 0xbade, 0x0010, 0x8128, 0x8128, 0x6128, 0x0241, 0xa459, 0xc559, 0x8672, 0xe682, 0x065a, 0x476a, 0x8993, 0xeb9b, 0xea9b, 0xccbc, 0x6ea4, 0x2ec5, 0x8eac, 0xafb4, 0x10bd, 0x6cac, 0x10bd, 0xefbc, 0x70cd, 0x0ca4, 0x2ea4, 0x0ec5, 0x6dac, 0xaeb4, 0xac8b, 0xceb4, 0x10bd, 0xd2d5, 0x50c5, 0x71cd, 0xb2cd, 0xcfb4, 0x30c5, 0x0fbd, 0xaeb4, 0x6da4, 0x6dac, 0xab93, 0x0762, 0x8872, 0x4449, 0xe659, 0x2341, 0xa230, 0x8128, 0x8128, 0x0010, 0xbad6, 0x5def, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0xffff, 0x8962, 0x2020, 0x8228, 0x8128, 0x8230, 0x0241, 0x2341, 0xa451, 0x256a, 0x456a, 0xc559, 0x8a93, 0x0ba4, 0x0dc5, 0xeba3, 0x0fc5, 0x50c5, 0x30c5, 0x71cd, 0xd2d5, 0x50cd, 0x10bd, 0xb1d5, 0x30c5, 0x6fa4, 0x50c5, 0x50cd, 0x10bd, 0x50cd, 0xefbc, 0x10bd, 0xcfb4, 0x91cd, 0x51c5, 0x91cd, 0xf2ac, 0xb0ac, 0xcfb4, 0x70cd, 0x8db4, 0xe97a, 0x6b8b, 0xa972, 0xab93, 0x4793, 0xa872, 0xe338, 0x0341, 0x8130, 0x8228, 0x2020, 0x695a, 0xffff, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x5def, 0x7def, 0x0010, 0x6128, 0x8128, 0x8128, 0xa230, 0x2349, 0xa451, 0xc459, 0x2662, 0x8772, 0x2762, 0xacbc, 0xacbc, 0x0fbd, 0x50cd, 0x91cd, 0x71cd, 0x91cd, 0xb2d5, 0xb2d5, 0xb2cd, 0xd2d5, 0xf0b4, 0x2f9c, 0x30c5, 0xf0b4, 0x90a4, 0x50c5, 0x91cd, 0xb1ac, 0x50c5, 0x71c5, 0x70a4, 0x10bd, 0x52c5, 0xd0b4, 0xcd93, 0x6c83, 0xcc93, 0xa872, 0xe659, 0xe97a, 0x2ba4, 0x2ba4, 0x676a, 0xa230, 0xa238, 0x8230, 0x6128, 0x0010, 0x7def, 0x5def, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x9ef7, 0xb29c, 0x0018, 0x8128, 0xa230, 0xa238, 0xe238, 0x2341, 0xc459, 0xc559, 0x476a, 0xe682, 0x49b4, 0x0dcd, 0xac8b, 0xcd8b, 0x71cd, 0x50c5, 0x91cd, 0x91cd, 0xd3d5, 0xb2d5, 0x91cd, 0x8fac, 0x919c, 0x50c5, 0xb0ac, 0x91a4, 0xafb4, 0xf1b4, 0x91a4, 0x51c5, 0x92cd, 0x509c, 0xcd93, 0x10bd, 0x11bd, 0x4ea4, 0xc972, 0xa872, 0x686a, 0x0562, 0x8893, 0x8a8b, 0x0983, 0x8351, 0x0241, 0xa230, 0x8130, 0x0018, 0x929c, 0xbef7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x1ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0xffff, 0xc749, 0x2020, 0xa230, 0xa230, 0xa238, 0xe240, 0x6449, 0x8549, 0x4249, 0xc682, 0xabbc, 0xeb9b, 0x2ca4, 0x6dac, 0x0e94, 0x8eac, 0x70cd, 0x71cd, 0x91cd, 0x91cd, 0xd0b4, 0xee93, 0x92cd, 0x50cd, 0xd0ac, 0xb2cd, 0x50c5, 0xf0bc, 0xd2a4, 0x10bd, 0xd0b4, 0xb0ac, 0x6ea4, 0xcc93, 0x6ea4, 0x30c5, 0xab93, 0x676a, 0x4762, 0x4762, 0x0462, 0x0a83, 0xe659, 0x2249, 0xc238, 0x8228, 0x2020, 0xc649, 0xffff, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x1be7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3de7, 0xdef7, 0x6120, 0x6128, 0x8128, 0x8228, 0x8230, 0xa230, 0x4349, 0x6351, 0x0662, 0x2aac, 0x2983, 0x2983, 0xedbc, 0x6cac, 0xcc93, 0x6eac, 0x30c5, 0x10bd, 0x30c5, 0xcfb4, 0xf0bc, 0xb1d5, 0x10bd, 0x90a4, 0x31bd, 0x10bd, 0x91d5, 0x509c, 0x50cd, 0xb0ac, 0xee93, 0x2d9c, 0x4a8b, 0x4a8b, 0x6cb4, 0x0dc5, 0xeb9b, 0x0762, 0xa551, 0x0341, 0xc659, 0x0341, 0xa230, 0x8128, 0x6128, 0x4120, 0xbef7, 0x5de7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x7def, 0x1ce7, 0x0010, 0x6128, 0x8128, 0x8128, 0x8230, 0xc238, 0x6449, 0x686a, 0x4762, 0xa87a, 0x6a8b, 0x298b, 0x0dc5, 0xcb9b, 0x8b8b, 0xac8b, 0xeebc, 0x2fc5, 0x8eac, 0x30c5, 0x91cd, 0x8eac, 0x30c5, 0x50c5, 0x30c5, 0x30c5, 0x8fa4, 0x6dac, 0x2e9c, 0xad8b, 0x8c8b, 0xea7a, 0x8772, 0xacb4, 0xacb4, 0x4bac, 0x2762, 0x0339, 0x0339, 0xa230, 0xa230, 0x6128, 0x6128, 0x0010, 0x1ce7, 0x7def, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x9eef, 0x79d6, 0x0010, 0x6128, 0x8228, 0x8128, 0x8130, 0x0241, 0x8451, 0x676a, 0x8872, 0x6772, 0x8893, 0x8a93, 0xc87a, 0x498b, 0x498b, 0x0ba4, 0x8cb4, 0xab93, 0x8db4, 0x0ebd, 0x2a83, 0xed9b, 0xefb4, 0x0fbd, 0x4ea4, 0x6c83, 0x2a83, 0x6c83, 0x8c8b, 0x4b83, 0xeb9b, 0x278b, 0xea9b, 0x2aac, 0x498b, 0x8872, 0x2341, 0x8130, 0x8128, 0x8128, 0x6128, 0x0010, 0x79ce, 0x9eef, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x9ef7, 0x79d6, 0x0010, 0x6128, 0x8228, 0x8128, 0x8128, 0xc238, 0x8451, 0xa551, 0xc459, 0x48b4, 0x456a, 0x0562, 0x0883, 0x8872, 0xaa9b, 0x6cb4, 0x6bac, 0x6cb4, 0xedc4, 0x2bac, 0xacb4, 0x6dac, 0x4da4, 0x4b83, 0x2a83, 0xc87a, 0xab93, 0x0a83, 0x8872, 0x6b8b, 0xa772, 0xc659, 0xe87a, 0x8872, 0xa451, 0xc238, 0x8128, 0x8128, 0x6128, 0x0010, 0x79d6, 0x9ef7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x9eef, 0xfbde, 0x4020, 0x2020, 0x8228, 0x8128, 0x8128, 0x8130, 0x8130, 0xa359, 0x6472, 0x4349, 0xa459, 0x456a, 0x0662, 0xa67a, 0x488b, 0x29ac, 0x2bac, 0xadbc, 0xa89b, 0x6bac, 0x8993, 0x4bac, 0x4bac, 0x2ba4, 0x8993, 0x6893, 0x686a, 0x2762, 0x476a, 0xe659, 0x2441, 0xa551, 0xa351, 0x6349, 0xa230, 0x8128, 0x2020, 0x4020, 0xfbde, 0x9eef, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x7def, 0xdef7, 0xa641, 0x0018, 0x8128, 0x8128, 0x8128, 0x8128, 0xa230, 0x0241, 0xe238, 0x4349, 0x6351, 0x2341, 0x6349, 0x6572, 0xc682, 0x8cb4, 0x6bb4, 0x268b, 0xc99b, 0x0ba4, 0xea9b, 0x0983, 0x498b, 0x8872, 0x246a, 0x4349, 0x4441, 0x0341, 0x0341, 0xc238, 0xa230, 0xa230, 0x8130, 0x8128, 0x0018, 0xa649, 0xbef7, 0x7def, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x5de7, 0xffff, 0x7194, 0x0010, 0x4020, 0x8228, 0x8128, 0x8128, 0x6128, 0xa238, 0xa238, 0xe238, 0x2249, 0xa359, 0x288b, 0x278b, 0xa89b, 0x6793, 0xe582, 0xc99b, 0x2aa4, 0x498b, 0x6772, 0xc87a, 0x2762, 0x6449, 0xc238, 0xa230, 0x8128, 0x8130, 0x8128, 0x8128, 0x6128, 0x2020, 0x0010, 0x7194, 0xffff, 0x5def, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0xbef7, 0x5def, 0x2852, 0x0010, 0x4128, 0x8228, 0x8228, 0x8230, 0xa230, 0xa230, 0xe238, 0xc459, 0xa359, 0xc582, 0x0562, 0x0362, 0x6472, 0xc559, 0xe659, 0x6449, 0xe338, 0x4441, 0x0339, 0xe238, 0x0241, 0xa238, 0x8128, 0x8128, 0x8228, 0x4120, 0x0010, 0x0852, 0x5cef, 0xbef7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x5def, 0xffff, 0x79ce, 0xe751, 0x0010, 0x2020, 0x6128, 0x8228, 0x8228, 0xa230, 0xa230, 0xa230, 0xa230, 0x6128, 0x8230, 0xa230, 0xa238, 0xc238, 0xa230, 0x8130, 0x8230, 0x8128, 0x6128, 0x8128, 0x8128, 0x6128, 0x2020, 0x0010, 0xc749, 0x59ce, 0xffff, 0x5def, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x5def, 0xffff, 0xfbde, 0x4c7b, 0x2020, 0x0018, 0x2020, 0x6128, 0xa230, 0x8230, 0x8128, 0x8228, 0x8230, 0x8230, 0x8230, 0x8230, 0x8228, 0x8228, 0x8228, 0x8128, 0x4128, 0x2020, 0x0018, 0x2020, 0x4c73, 0xdbde, 0xffff, 0x5def, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x5def, 0xbef7, 0xffff, 0x18c6, 0xae83, 0x8541, 0x0018, 0x0010, 0x0018, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0018, 0x0010, 0x0018, 0x8541, 0xae83, 0x18c6, 0xffff, 0xbef7, 0x5def, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x7def, 0x9ef7, 0xffff, 0xffff, 0xfbde, 0xb6bd, 0xd3a4, 0x5094, 0x0f8c, 0x0f8c, 0x5194, 0xd3a4, 0xb6bd, 0xfbde, 0xffff, 0xffff, 0x9ef7, 0x7def, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x5def, 0x7def, 0x9eef, 0x9ef7, 0x9ef7, 0x9ef7, 0x9ef7, 0x9eef, 0x7def, 0x5def, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7,
		0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7, 0x3ce7
};


#endif /* INC_DRIVER_LCD_BITMAP_H_ */