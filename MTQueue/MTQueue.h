/*
 * MTQueue.h
 *
 *  Created on: 2020年1月22日
 *      Author: ysq
 *
 *    This library called Multiple-types Queue, this means u can push
 *  different types into the same queue, it's simple, small.
 *    This library may seem useless in many cases, but can be very
 *  effective in some cases ;)
 *  example:
 * size_t oneDevice(uint8_t* buf, size_t buf_len) {
 *   //<! generate data to the buffer
 *   MTQueue input_buf(buf, buf_len, 0, MTQueue::kBigEndian);
 *   input_buf.push<uint8_t>(32);
 *   input_buf.push<uint16_t>(0x1163);
 *   input_buf.push<uint32_t>(0x12345678);
 *   input_buf.push<char>('h');
 *   input_buf.push<char>('e');
 *   input_buf.push<char>('l');
 *   input_buf.push<char>('l');
 *   input_buf.push<char>('o');
 *   printf("input_buf.getDataRemainSize()=%u\n", input_buf.getDataRemainSize());
 *   return input_buf.getDataRemainSize();
 * }
 * void anotherDevice(uint8_t* buf, size_t buf_len, size_t data_size) {
 *   //<! analyze the buffer, and get data from the buffer
 *   MTQueue output_buf(buf, buf_len, data_size, MTQueue::kBigEndian);
 *   printf("[%hhu,", output_buf.pop<uint8_t>());
 *   printf("0x%x,", output_buf.pop<uint16_t>());
 *   printf("0x%x,", output_buf.pop<uint32_t>());
 *   printf("%c,", output_buf.pop<char>());
 *   printf("%c,", output_buf.pop<char>());
 *   printf("%c,", output_buf.pop<char>());
 *   printf("%c,", output_buf.pop<char>());
 *   printf("%c]\n", output_buf.pop<char>());
 * }
 * ATTENTION:
 *   Once you push data to the buffer, even you pop the data, the memory WILL NOT
 * be free,see this example:
 * int main () {
 *   uint8_t buf[20];
 *   MTQueue mtq(buf, 20);
 *   printf("free memory in queue:%d\n", mtq.getMemRemainSize());
 *   mtq.push<uint8_t>(0x01);
 *   printf("free memory in queue:%d\n", mtq.getMemRemainSize());
 *   mtq.pop<uint8_t>();
 *   printf("free memory in queue:%d\n", mtq.getMemRemainSize());
 * }
 * and this message will show:
 * free memory in queue:20
 * free memory in queue:19
 * free memory in queue:19
 */

#ifndef MTQUEUE_H_
#define MTQUEUE_H_

#include <stdint.h>

class MTQueue {
 public:
  enum byte_endian_t {
    kLittleEndian,
    kBigEndian,
  };
  /**
   * Constructor, this function will check system Byte-Endian.
   * param buf Queue buffer pointer
   * param size Size of queue buffer
   * param available Available data in buffer
   * param byte_endian Data Byte-Endian
   */
  MTQueue(uint8_t* buf, const size_t size, size_t available = 0,
          byte_endian_t byte_endian = kLittleEndian)
      : buf_(buf),
        size_(size),
        available_(available),
        data_byte_endian_(byte_endian) {
    uint16_t data = 0x0001;
    if (*((uint8_t *)&data)) {
      sys_byte_endian_ = kLittleEndian;
    } else {
      sys_byte_endian_ = kBigEndian;
    }
  }
  virtual ~MTQueue() {
  }
  /**
   * Get free memory in buffer.
   * retval Free memory size in byte
   */
  int getMemRemainSize(void) {
    return (int)size_-available_;
  }
  /**
   * Get availiable data in buffer.
   * retval Available data size in byte
   */
  int getDataRemainSize(void) {
    return (int)available_-offset_;
  }
  /**
   * Pop data, after this oprator the data will be deteled in the buffer.
   * retval first data in buffer(type of input)
   */
  template<class T>
  T pop(void) {
    size_t len = sizeof(T);
    if (data_byte_endian_ == sys_byte_endian_) {
      T* ret = (T*)(buf_+offset_);
      offset_ += len;
      return *ret;
    } else {
      T data = 0;
      if (kBigEndian == data_byte_endian_) {
        for (size_t i = len; i != 0; --i) {
          data |= buf_[offset_++]<<((i-1)*8);
        }
      } else {
        for (size_t i = 0; i < len; ++i) {
          data |= buf_[offset_++]<<(i*8);
        }
      }
      return data;
    }
  }
  /**
   * Push date into buffer.
   * param parameter Data you wants to input
   */
  template<class T>
  void push(const T parameter) {
    size_t len = sizeof(T);
    if (data_byte_endian_ == sys_byte_endian_) {
      T* data = (T*)&buf_[available_];
      *data = parameter;
      available_ += len;
    } else {
      if (kBigEndian == data_byte_endian_) {
        for (size_t i = len; i != 0; --i) {
          buf_[available_++] = (parameter>>((i-1)*8)) & 0xFF;
        }
      } else {
        for (size_t i = 0; i < len; ++i) {
          buf_[available_++] = (parameter>>(i*8)) & 0xFF;
        }
      }
    }
  }
  /**
   * Get the data in the index of offset. This oprator won't delete data in the 
   * buffer.
   */
  template<class T>
  T operator[](size_t offset) {
    return *((T*)(buf_+offset));
  }

 private:
  uint8_t* buf_;
  const size_t size_;
  size_t available_;
  size_t offset_ = 0;
  byte_endian_t sys_byte_endian_;
  byte_endian_t data_byte_endian_;
};

#endif /* MTQUEUE_H_ */
