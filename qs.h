/*  Licensed under the MIT License by Bart Grantham, 2010.  See ./LICENSE or
 *  http://www.opensource.org/licenses/mit-license.php
 */
#ifdef __cplusplus
extern "C" {
#endif


#ifndef BG_QS_H_
#define BG_QS_H_

/*  string.h needed for strcspn() and strlen()  */
#include <string.h>


/*  Similar to strncmp, but handles URL-encoding for either string  */
int qs_strncmp(const char * s, const char * qs, register size_t n);


/*  Finds the beginning of each key/value pair and stores a pointer in qs_kv.
 *  Also decodes the value portion of the k/v pair *in-place*.  In a future
 *  enhancement it will also have a compile-time option of sorting qs_kv
 *  alphabetically by key.  */
int qs_parse(char * qs, char * qs_kv[], int qs_kv_size);


/*  Used by qs_parse to decode the value portion of a k/v pair  */
int qs_decode(char * qs);


/*  Looks up the value according to the key on a pre-processed query string
 *  A future enhancement will be a compile-time option to look up the key
 *  in a pre-sorted qs_kv array via a binary search.  */
char * qs_k2v(const char * key, char * qs_kv[], int qs_kv_size);


/*  Non-destructive lookup of value, based on key.  User provides the
 *  destinaton string and length.  */
char * qs_scanvalue(const char * key, const char * qs, char * val, size_t val_len);

#endif  // BG_QS_H_


#ifdef __cplusplus
}
#endif 
