#include "string.h"

#define UNALIGNED(X, Y) \
  (((long)X & (sizeof (long) - 1)) | ((long)Y & (sizeof (long) - 1)))

/* How many bytes are copied each iteration of the 4X unrolled loop.  */
#define BIGBLOCKSIZE    (sizeof (long) << 2)

/* How many bytes are copied each iteration of the word copy loop.  */
#define LITTLEBLOCKSIZE (sizeof (long))

/* Threshhold for punting to the byte copier.  */
#define TOO_SMALL(LEN)  ((LEN) < BIGBLOCKSIZE)

#define LBLOCKSIZE (sizeof(long))
#define UNALIGNED2(X) ((long)X & (LBLOCKSIZE - 1))

/* void * memcpy(void *dest, const void * src, size_t n)
{
	while (n-- )
	{
		*dest++ = *src++;
	}
	return dest;
} */

void * memcpy(void * dst0, const void *src0, size_t len0)
{
#if defined(PREFER_SIZE_OVER_SPEED) || defined(__OPTIMIZE_SIZE__)
  char *dst = (char *) dst0;
  char *src = (char *) src0;

  void * save = dst0;

  while (len0--)
    {
      *dst++ = *src++;
    }

  return save;
#else
  char *dst = dst0;
  const char *src = src0;
  long *aligned_dst;
  const long *aligned_src;
  int   len =  len0;

  /* If the size is small, or either SRC or DST is unaligned,
     then punt into the byte copy loop.  This should be rare.  */
  if (!TOO_SMALL(len) && !UNALIGNED (src, dst))
    {
      aligned_dst = (long*)dst;
      aligned_src = (long*)src;

      /* Copy 4X long words at a time if possible.  */
      while (len >= BIGBLOCKSIZE)
        {
          *aligned_dst++ = *aligned_src++;
          *aligned_dst++ = *aligned_src++;
          *aligned_dst++ = *aligned_src++;
          *aligned_dst++ = *aligned_src++;
          len -= BIGBLOCKSIZE;
        }

      /* Copy one long word at a time if possible.  */
      while (len >= LITTLEBLOCKSIZE)
        {
          *aligned_dst++ = *aligned_src++;
          len -= LITTLEBLOCKSIZE;
        }

       /* Pick up any residual with a byte copier.  */
      dst = (char*)aligned_dst;
      src = (char*)aligned_src;
    }

  while (len--)
    *dst++ = *src++;

  return dst0;
#endif /* not PREFER_SIZE_OVER_SPEED */
}

void * memset(void *m, int c, size_t n)
{
  char *s = (char *) m;

#if !defined(PREFER_SIZE_OVER_SPEED) && !defined(__OPTIMIZE_SIZE__)
  int i;
  unsigned long buffer;
  unsigned long *aligned_addr;
  unsigned int d = c & 0xff;	/* To avoid sign extension, copy C to an
				   unsigned variable.  */

  while (UNALIGNED2(s))
    {
      if (n--)
        *s++ = (char) c;
      else
        return m;
    }

  if (!TOO_SMALL (n))
    {
      /* If we get this far, we know that n is large and s is word-aligned. */
      aligned_addr = (unsigned long *) s;

      /* Store D into each char sized location in BUFFER so that
         we can set large blocks quickly.  */
      buffer = (d << 8) | d;
      buffer |= (buffer << 16);
      for (i = 32; i < LBLOCKSIZE * 8; i <<= 1)
        buffer = (buffer << i) | buffer;

      /* Unroll the loop.  */
      while (n >= LBLOCKSIZE*4)
        {
          *aligned_addr++ = buffer;
          *aligned_addr++ = buffer;
          *aligned_addr++ = buffer;
          *aligned_addr++ = buffer;
          n -= 4*LBLOCKSIZE;
        }

      while (n >= LBLOCKSIZE)
        {
          *aligned_addr++ = buffer;
          n -= LBLOCKSIZE;
        }
      /* Pick up the remainder with a bytewise loop.  */
      s = (char*)aligned_addr;
    }

#endif /* not PREFER_SIZE_OVER_SPEED */

  while (n--)
    *s++ = (char) c;

  return m;
}

void itoa(char *buf, unsigned long int n, int base)
{
	unsigned long int tmp;
	int i, j;

	tmp = n;
	i = 0;

	do {
		tmp = n%base;
		buf[i++] = (tmp < 10) ? (tmp + '0') : (tmp + 'a' - 10);
	} while (n /= base);
	buf[i--] = 0;

	for (j=0; j<i; j++, i--) {
		tmp = buf[j];
		buf[j] = buf[i];
		buf[i] = tmp;
	}
}

//pas besoin de l'optimiser ?
size_t strlen(const char *s)
{
	char * ptr=(char *) s;
	while (*ptr++);
	return ptr-s;
}
