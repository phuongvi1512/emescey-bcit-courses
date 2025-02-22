
#include "md5.h"

#ifdef WIN32
   typedef unsigned long caddr_t ;
#else
#
#  include <sys/types.h>
#
#  ifdef HAVE_MD5GLOBAL_H
#    include <md5global.h>
#  endif
#
#  ifdef HAVE_MD5_H
#    include <md5.h>
#  else
#    ifdef HAVE_OPENSSL_MD5_H
#      include <openssl/md5.h>
#    else
#      ifdef HAVE_INN_MD5_H
#        include <inn/md5.h>
#      endif
#    endif
#  endif
#
#endif  /* ! WIN32 */

#include <string.h>


#ifndef bzero
#  define bzero(addr,n)  memset(addr,0,n)
#endif
#ifndef bcopy
#  define bcopy(src,dest,n)  memcpy(dest,src,n)
#endif


/*-------------------------------------------------*
 *
 *  The following code has been copied from the
 *  appendix of RFC2104 by Krawczyk, et. al.
 * 
 *-------------------------------------------------*/

/*
** Function: hmac_md5
*/

void
hmac_md5 (text, text_len, key, key_len, digest)
    unsigned char*  text;        /* pointer to data stream */
    int             text_len;    /* length of data stream */
    unsigned char*  key;         /* pointer to authentication key */
    int             key_len;     /* length of authentication key */
    caddr_t         digest;      /* caller digest to be filled in */

{
    MD5_CTX context;
    unsigned char k_ipad[65];    /* inner padding -
                                  * key XORd with ipad
                                  */
    unsigned char k_opad[65];    /* outer padding -
                                  * key XORd with opad
                                  */
    unsigned char tk[16];
    int i;
    /* if key is longer than 64 bytes reset it to key=MD5(key) */
    if (key_len > 64) {

        MD5_CTX      tctx;

        MD5Init(&tctx);
        MD5Update(&tctx, key, key_len);
        MD5Final(tk, &tctx);

        key = tk;
        key_len = 16;
    }

    /*
     * the HMAC_MD5 transform looks like:
     *
     * MD5(K XOR opad, MD5(K XOR ipad, text))
     *
     * where K is an n byte key
     * ipad is the byte 0x36 repeated 64 times

     * opad is the byte 0x5c repeated 64 times
     * and text is the data being protected
     */

    /* start out by storing key in pads */
    bzero( k_ipad, sizeof k_ipad);
    bzero( k_opad, sizeof k_opad);
    bcopy( key, k_ipad, key_len);
    bcopy( key, k_opad, key_len);

    /* XOR key with ipad and opad values */
    for (i=0; i<64; i++) {
        k_ipad[i] ^= 0x36;
        k_opad[i] ^= 0x5c;
    }
    /*
     * perform inner MD5
     */
    MD5Init(&context);                   /* init context for 1st
                                          * pass */
    MD5Update(&context, k_ipad, 64);     /* start with inner pad */
    MD5Update(&context, text, text_len); /* then text of datagram */
    MD5Final(digest, &context);          /* finish up 1st pass */
    /*
     * perform outer MD5
     */
    MD5Init(&context);                   /* init context for 2nd
                                          * pass */
    MD5Update(&context, k_opad, 64);     /* start with outer pad */
    MD5Update(&context, digest, 16);     /* then results of 1st
                                          * hash */
    MD5Final(digest, &context);          /* finish up 2nd pass */

}
