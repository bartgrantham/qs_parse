/*  Licensed under the MIT License by Bart Grantham, 2010.  See ./LICENSE or
 *  http://www.opensource.org/licenses/mit-license.php
 */
#include <stdio.h>
#include "qs.h"

int main(int argc, char * argv[])
{
    int i,j;
    char * kvpairs[256];
    char value[256];

    char foo[]        = "foo";
    char foobar[]     = "foobar";
    char foo_enc[]    = "fo%6f";
    char foobar_enc[] = "fo%6fbar";
    char foo_mal[]    = "fo%6";
    char foo_mal2[]    = "foo%6";
    char foo_end[]     = "foo&";

    /*  This test query string includes:
     *  - URL encoded values (percent-encoded and +-as-space)
     *  - URL encoded keys (percent-encoded +-as-space)
     *  - Incorrectly encoded values (FFFFFF%f)
     *  - A trailing anchor
     *  - null (0-char) values
     *
     *  I should add:
     *  - leading URL junk (before a ?)
     */
    char getstring[] = "FUNNYJUNK://@?t%65xt=bleh+bleh%20!&font=Vera.ttf&size=40.3&fg=FFFFFF%f&debug1&bg=000&hash=24a%62cdef%7a&rot=123.1&tr+i=cky&debug2#don'tparseme,bro";

    printf("Testing qs_* functions\n");

    printf("    Testing qs_strncmp():\n");
    printf("        %s, %s, 3         should be 0 : %d\n", foo, foo, qs_strncmp(foo, foo, 3));
    printf("        %s, %s, 4         should be 0 : %d\n", foo, foo, qs_strncmp(foo, foo, 4));
    printf("        %s, %s, 99        should be 0 : %d\n", foo, foo, qs_strncmp(foo, foo, 99));
    printf("        %s, %s, 3       should be 0 : %d\n", foo, foo_enc, qs_strncmp(foo, foo_enc, 3));
    printf("        %s, %s, 4       should be 0 : %d\n", foo, foo_enc, qs_strncmp(foo, foo_enc, 4));
    printf("        %s, %s, 99      should be 0 : %d\n", foo, foo_enc, qs_strncmp(foo, foo_enc, 99));
    printf("        %s, %s, 3     should be 0 : %d\n", foo_enc, foo_enc, qs_strncmp(foo_enc, foo_enc, 3));
    printf("        %s, %s, 4     should be 0 : %d\n", foo_enc, foo_enc, qs_strncmp(foo_enc, foo_enc, 4));
    printf("        %s, %s, 99    should be 0 : %d\n", foo_enc, foo_enc, qs_strncmp(foo_enc, foo_enc, 99));
    printf("        %s, %s, 3      should be 0 : %d\n", foo, foobar, qs_strncmp(foo, foobar, 3));
    printf("        %s, %s, 4      should be - : %d\n", foo, foobar, qs_strncmp(foo, foobar, 4));
    printf("        %s, %s, 99     should be - : %d\n", foo, foobar, qs_strncmp(foo, foobar, 99));
    printf("        %s, %s, 3    should be 0 : %d\n", foo, foobar_enc, qs_strncmp(foo, foobar_enc, 3));
    printf("        %s, %s, 4    should be - : %d\n", foo, foobar_enc, qs_strncmp(foo, foobar_enc, 4));
    printf("        %s, %s, 99   should be - : %d\n", foo, foobar_enc, qs_strncmp(foo, foobar_enc, 99));
    printf("        %s, %s, 3  should be 0 : %d\n", foo_enc, foobar_enc, qs_strncmp(foo_enc, foobar_enc, 3));
    printf("        %s, %s, 4  should be - : %d\n", foo_enc, foobar_enc, qs_strncmp(foo_enc, foobar_enc, 4));
    printf("        %s, %s, 99 should be - : %d\n", foo_enc, foobar_enc, qs_strncmp(foo_enc, foobar_enc, 99));
    printf("        %s, %s, 2        should be 0 : %d\n", foo, foo_mal, qs_strncmp(foo, foo_mal, 2));
    printf("        %s, %s, 3        should be + : %d\n", foo, foo_mal, qs_strncmp(foo, foo_mal, 3));
    printf("        %s, %s, 99       should be + : %d\n", foo, foo_mal, qs_strncmp(foo, foo_mal, 99));
    printf("        %s, %s, 2       should be 0 : %d\n", foo, foo_mal2, qs_strncmp(foo, foo_mal2, 2));
    printf("        %s, %s, 3       should be 0 : %d\n", foo, foo_mal2, qs_strncmp(foo, foo_mal2, 3));
    printf("        %s, %s, 4       should be 0 : %d\n", foo, foo_mal2, qs_strncmp(foo, foo_mal2, 4));
    printf("        %s, %s, 99      should be 0 : %d\n", foo, foo_mal2, qs_strncmp(foo, foo_mal2, 99));
    printf("        %s, %s, 2        should be 0 : %d\n", foo, foo_end, qs_strncmp(foo, foo_end, 2));
    printf("        %s, %s, 3        should be 0 : %d\n", foo, foo_end, qs_strncmp(foo, foo_end, 3));
    printf("        %s, %s, 4        should be 0 : %d\n", foo, foo_end, qs_strncmp(foo, foo_end, 4));
    printf("        %s, %s, 99       should be 0 : %d\n", foo, foo_end, qs_strncmp(foo, foo_end, 99));

    printf("\n");

    char end_foo[]     = "foo&";



    printf("    Testing qs_scanvalue() with query string:\n        %s\n", getstring);
    printf("        The following should say \"bleh bleh !\" : \"%s\"\n", qs_scanvalue("text", getstring, value, 256));
    printf("        The following should say \"Vera.ttf\"    : \"%s\"\n", qs_scanvalue("font", getstring, value, 256));
    printf("        The following should say \"40.3\"        : \"%s\"\n", qs_scanvalue("size", getstring, value, 256));
    printf("        The following should say \"FFFFFF\"      : \"%s\"\n", qs_scanvalue("fg", getstring, value, 256));
    printf("        The following should say \"\"            : \"%s\"\n", qs_scanvalue("debug1", getstring, value, 256));
    printf("        The following should say \"000\"         : \"%s\"\n", qs_scanvalue("bg", getstring, value, 256));
    printf("        The following should say \"24abcdefz\"   : \"%s\"\n", qs_scanvalue("hash", getstring, value, 256));
    printf("        The following should say \"123.1\"       : \"%s\"\n", qs_scanvalue("rot", getstring, value, 256));
    printf("        The following should say \"cky\"         : \"%s\"\n", qs_scanvalue("tr i", getstring, value, 256));
    printf("        The following should say \"\"            : \"%s\"\n", qs_scanvalue("debug2", getstring, value, 256));
    printf("\n");

    printf("    Running qs_parse() against query string (also exersizes qs_decode()):\n        %s\n", getstring);
    i = qs_parse(getstring, kvpairs, 256);
    printf("        I should have found 10 k/v substrings, actually found: %d\n", i);
    printf("\n");

    printf("    Testing qs_k2v() against our kv pair substrings:\n");
    printf("        The following should say \"bleh bleh !\" : \"%s\"\n", qs_k2v("text", kvpairs, i));
    printf("        The following should say \"Vera.ttf\"    : \"%s\"\n", qs_k2v("font", kvpairs, i));
    printf("        The following should say \"40.3\"        : \"%s\"\n", qs_k2v("size", kvpairs, i));
    printf("        The following should say \"FFFFFF\"      : \"%s\"\n", qs_k2v("fg", kvpairs, i));
    printf("        The following should say \"\"            : \"%s\"\n", qs_k2v("debug1", kvpairs, i));
    printf("        The following should say \"000\"         : \"%s\"\n", qs_k2v("bg", kvpairs, i));
    printf("        The following should say \"24abcdefz\"   : \"%s\"\n", qs_k2v("hash", kvpairs, i));
    printf("        The following should say \"123.1\"       : \"%s\"\n", qs_k2v("rot", kvpairs, i));
    printf("        The following should say \"cky\"         : \"%s\"\n", qs_k2v("tr i", kvpairs, i));
    printf("        The following should say \"\"            : \"%s\"\n", qs_k2v("debug2", kvpairs, i));
    printf("\n");

    return 0;
}
