/*
 * frame.cpp
 *
 *  Created on: 2019年5月10日
 *      Author: ysq
 */

#include "frame.h"
//template<unsigned int rows, unsigned int cols, unsigned int channel>
//frame<rows, cols, channel>::frame(uint8_t* pixel)
//    : frame_src_({pixel, cols, rows, channel}),
//      pixel_((uint8_t (*)[rows][cols])pixel) {
//}
//
//template<unsigned int rows, unsigned int cols, unsigned int channel>
//frame<rows, cols, channel>::frame(frame& ext_frame, rectangle* ext_rec)
//    : frame_src_(ext_frame.frame_src_) {
//  if (ext_rec) {
//    rec_ = *ext_rec;
//    pixel_ = &ext_frame.pixel_[0][ext_rec->height][ext_rec->width];
//  } else {
//    rec_ = ext_frame.rec_;
//    pixel_ = ext_frame.pixel_;
//  }
//}
//
//template<unsigned int rows, unsigned int cols, unsigned int channel>
//frame<rows, cols, channel>::frame(frame8& ext_frame8, rectangle* ext_rec)
//    : frame_src_(ext_frame8),
//      pixel_(ext_frame8.pixel) {
//  if (ext_rec) {
//    rec_ = *ext_rec;
//    pixel_ = (uint8_t (*)[rows][cols])ext_frame8.pixel;
//  }
//}
//
//template<unsigned int rows, unsigned int cols, unsigned int channel>
//frame<rows, cols, channel>::~frame() {}


uint8_t getValue(uint8_t (*p)[3][4], int k, int h, int w) {
  return p[k][h][w];
}

