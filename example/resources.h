/** Generated with MiniRC */

#ifndef __RESOURCES__H__
#define __RESOURCES__H__

#include <stddef.h>

/**
* @brief Restores binary file in file system to specified location
* @param[in] fname Full file name for saving in file system
* @param[in] content Saved with resource compiler hex content of a binary file
* @@return 1 if everything went well, 0 if `fname` is invalid or 
*            error occured during hex to bin conversion.
*/
int rc_restore(const char* fname, const int* content, size_t length);

/* data/lena.jpg */
extern const int data_lena_jpg[];
extern const size_t data_lena_jpg_len;

#endif /* __RESOURCES__H__ */
