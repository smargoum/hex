#ifndef _HEX_MOVE_H_
#define _HEX_MOVE_H_

#include <stdlib.h>

/* Players */
enum color_t { BLACK=0, WHITE=1, NO_COLOR=2 };

/*positions*/
struct move_t {
  size_t m;
  enum color_t c;
};

#endif // _HEX_MOVE_H_
