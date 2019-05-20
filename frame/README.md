Welcome!!!
==========

Thank u for coming to watch my 1st idea.
This is a library for frame read/write in micro systerms, it won't `new` any memory in class, and it only cost a little memory(10byte? or 20 byte in later version), and u can get any part in frame easily by use this library!


Example
=======
```cpp
#include <frame.h>
int main () {
    // test frame array
    uint8_t arr[] = {
        1,2,3,0,
        4,5,6,0,
        7,8,9,0,
        11,12,13,0,
        14,15,16,0,
        17,18,19,0
    };
    frame<3,4,2> p_arr(arr);                // construct a frame from arr
    rectangle rect = {1, 0, 2, 3};          // a rectangle, stat from [x=1,y=0], and [width=2,height=3]
    frame<3,4,2> frame_part(p_arr, &rect);  // get a part of frame form p_arr
    printf("p_arr = \n");
    p_arr.printFrame();
    printf("\nframe_part = \n");
    frame_part.printFrame();
}
```
you can see print in terminal:
```
>>>> p_arr = 
1,2,3,0,
4,5,6,0,
7,8,9,0,
11,12,13,0,
14,15,16,0,
17,18,19,0,

frame_part = 
2,3,
5,6,
8,9,
12,13,
15,16,
18,19,
```
And u can get pixel easily by:
```cpp
// test frame array
uint8_t arr[] = {
    1,2,3,0,
    4,5,6,0,
    7,8,9,0,
    11,12,13,0,
    14,15,16,0,
    17,18,19,0
};
frame<3,4,2> p_arr(arr);                // construct a frame from arr
printf(p_arr[0][2][1]);                 // p_arr[channel][row][col]
```
return in terminal
```
>>>> 8
```
This way is as faster get value from `arr` directly, see this example:
```cpp
  uint8_t arr[] = {
      1,2,3,0,
      4,5,6,0,
      7,8,9,0,
      11,12,13,0,
      14,15,16,0,
      17,18,19,0,
      21,22,23,0,
      24,25,26,0,
      27,28,29,0
  };
  const uint32_t channel = 3;
  const uint32_t width = 4;
  const uint32_t height = 3;
  uint8_t (*arr_)[height][width] = (uint8_t (*)[height][width]) arr;
  frame<height,width,channel> p_arr(arr);
  rectangle rect = {1, 0, 2, 3};
  frame<height,width,channel> frame_part(p_arr, &rect);
  uint32_t test_count = 50000;
  volatile unsigned int num = 0;
  pixel8 pixels;
  size_t k,h,w;
  uint32_t c;
  size_t i;
  printf("start========================\n");
  unsigned long start_time = millis();
  for (c = 0; c < test_count; ++c) {
    num = 0;
    for (k = 0; k < channel; ++k) {
      for (h = 0; h < height; ++h ) {
        for (w = 0; w < width; ++w ) {
          num += p_arr[k][h][w];
        }
      }
    }
  }
  printf("ret arr[][][] time = %lu, num = %u\n", millis()-start_time, num);
  start_time = millis();
  for (c = 0; c < test_count; ++c) {
    num = 0;
    for (i = 0; i < sizeof(arr); ++i) {
      num += arr[i];
    }
  }
  printf("arr[i] time = %lu, num = %u\n", millis()-start_time, num);
  start_time = millis();
  for (c = 0; c < test_count; ++c) {
    num = 0;
    for (k = 0; k < channel; ++k) {
      for (h = 0; h < height; ++h ) {
        for (w = 0; w < width; ++w ) {
          num += arr[k*width*height+w+h*width];
        }
      }
    }
  }
  printf("arr[w*3+h] time = %lu, num = %u\n", millis()-start_time, num);
  start_time = millis();
  for (c = 0; c < test_count; ++c) {
    num = 0;
    for (k = 0; k < channel; ++k) {
      for (h = 0; h < height; ++h ) {
        for (w = 0; w < width; ++w ) {
          num += arr_[k][h][w];
        }
      }
    }
  }
  printf("arr_[][][] time = %lu, num = %u\n", millis()-start_time, num);
  start_time = millis();
  for (c = 0; c < test_count; ++c) {
    num = 0;
    for (k = 0; k < channel; ++k) {
      for (h = 0; h < height; ++h ) {
        for (w = 0; w < width; ++w ) {
          num += getValue(arr_, k,h,w);
        }
      }
    }
  }
  printf("getValue time = %lu, num = %u\n", millis()-start_time, num);
```
and return(test in arduino mega1280):
```
>>>> start========================
ret arr[][][] time = 2672, num = 405
arr[i] time = 1852, num = 405
arr[w*3+h] time = 3670, num = 405
arr_[][][] time = 2673, num = 405
getValue time = 2672, num = 405
```
It's faster than `arr[channel*frame_size+h*width+w]`
