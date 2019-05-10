Welcome!!!
==========

Thank u for coming to watch my 1st idea.
This is a library for frame read/write in micro systerms, it won't `new` any thing in class, and it cost little memory, and u can get any part in frame easily by use this library!


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
p_arr = 
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
8
```
***BUT!!!*** this way is so ***slow***, it's 1.5 times slower(test in Arduino) than get value from `arr` directly, like:
```cpp
printf(arr[9]);
```

