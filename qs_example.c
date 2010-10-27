#include <stdio.h>
#include "qs.h"

#define NUMKVPAIRS 256
#define VALSIZE 256

int main(int argc, char * argv[])
{
    int i;
    char * kvpairs[NUMKVPAIRS];
    char value[VALSIZE];
    char * value_ptr;

    char getstring[] = "scheme://username:password@domain:port/path?foo=bar&frob&baz=quux#anchor";

    /********************************************************/
    /*  The easy, but not as efficient way: qs_scanvalue()  */
    /********************************************************/
    if ( qs_scanvalue("foo", getstring, value, sizeof(value)) != NULL )
        printf("Key %s is set, and the value is: \"%s\"\n", "foo", value);
    else
        printf("Key %s is NOT set\n", "foo");

    if ( qs_scanvalue("baz", getstring, value, sizeof(value)) != NULL )
        printf("Key %s is set, and the value is: \"%s\"\n", "baz", value);
    else
        printf("Key %s is NOT set\n", "baz");

    if ( qs_scanvalue("frob", getstring, value, sizeof(value)) != NULL )
        printf("Key %s is set, and the value is: \"%s\n", "frob", value);
    else
        printf("Key %s is NOT set\n", "frob");

    if ( qs_scanvalue("blah", getstring, value, sizeof(value)) != NULL )
        printf("Key %s is set, and the value is: \"%s\"\n", "blah", value);
    else
        printf("Key %s is NOT set\n", "blah");

    printf("\n");


    /*************************************************************************/
    /*  The faster, more complex, and destructive way: qs_parse() / qs_k2v() */
    /*************************************************************************/

    /*  ***THIS WILL ALTER getstring***  */
    i = qs_parse(getstring, kvpairs, 256);
    /*  At this point qs_scanvalue() will no longer work with this query string  */

    if ( (value_ptr = qs_k2v("foo", kvpairs, i)) != NULL )
        printf("Key %s is set, and the value is: \"%s\"\n", "foo", value_ptr);
    else
        printf("Key %s is NOT set\n", "foo");

    if ( (value_ptr = qs_k2v("baz", kvpairs, i)) != NULL )
        printf("Key %s is set, and the value is: \"%s\"\n", "baz", value_ptr);
    else
        printf("Key %s is NOT set\n", "baz");

    if ( (value_ptr = qs_k2v("frob", kvpairs, i)) != NULL )
        printf("Key %s is set, and the value is: \"%s\"\n", "frob", value_ptr);
    else
        printf("Key %s is NOT set\n", "frob");

    if ( (value_ptr = qs_k2v("blah", kvpairs, i)) != NULL )
        printf("Key %s is set, and the value is: \"%s\"\n", "blah", value_ptr);
    else
        printf("Key %s is NOT set\n", "blah");

    return 0;
}
