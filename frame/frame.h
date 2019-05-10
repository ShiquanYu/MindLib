/*
 * frame.h
 *
 *  Created on: 2019年5月10日
 *      Author: ysq
 */

#ifndef PRODUCTS_YSQ_FRAME_H_
#define PRODUCTS_YSQ_FRAME_H_

#include <stdio.h>

extern "C" {
// use this in .c file
struct frame8 {
  uint8_t* pixel;
  unsigned int col;
  unsigned int row;
  unsigned int channel;
};
struct line {
  unsigned int start_x;
  unsigned int start_y;
  unsigned int stop_x;
  unsigned int stop_y;
};
struct rectangle {
  unsigned int start_x;
  unsigned int start_y;
  unsigned int width;
  unsigned int height;
};
}

template<unsigned int rows, unsigned int cols, unsigned int channel=3>
class frame {
 protected:
  frame8 frame_src_;                          // source frame
  uint8_t (* pixel_)[rows][cols];

 public:
  frame(uint8_t* pixel)
      : frame_src_( { pixel, cols, rows, channel }),
        pixel_((uint8_t (*)[rows][cols]) pixel) {
  }
  frame(frame& ext_frame, rectangle* ext_rec = nullptr)
      : frame_src_(ext_frame.frame_src_) {
    if (ext_rec) {
      rec_ = *ext_rec;
      pixel_ = (uint8_t (*)[rows][cols])&ext_frame.pixel_[0][ext_rec->start_y][ext_rec->start_x];
    } else {
      rec_ = ext_frame.rec_;
      pixel_ = ext_frame.pixel_;
    }
  }
  frame(frame8& ext_frame8, rectangle* ext_rec = nullptr)
      : frame_src_(ext_frame8),
        pixel_(ext_frame8.pixel) {
    if (ext_rec) {
      rec_ = *ext_rec;
      pixel_ = (uint8_t (*)[rows][cols])(ext_frame8.pixel+ext_rec->start_y*cols+ext_rec->start_x);
    }
  }
  ~frame();

  auto operator[](const int n)->decltype(pixel_[0]) {
    // too slow
    return pixel_[n];
  }
  frame8& getSrcFrame() {return frame_src_;}
  void printFrame() {
    for (size_t c = 0; c < channel; ++c) {
      for (size_t row = 0; row < rec_.height; ++row) {
        for (size_t col = 0; col < rec_.width; ++col) {
          printf("%hhu,", pixel_[c][row][col]);
        }
        printf("\n");
      }
    }
  }

  rectangle rec_ = { 0, 0, cols, rows};

};

uint8_t getValue(uint8_t (*p)[3][4], int k, int h, int w);



#endif /* PRODUCTS_YSQ_FRAME_H_ */
