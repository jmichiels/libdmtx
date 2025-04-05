//
// Created by jacques on 05/04/25.
//

#include <stdio.h>
#include <string.h>

#include "dmtx.h"

#define DATA "ABC123"

int main(void) {
  DmtxEncode *enc;
  if ((enc = dmtxEncodeCreate()) == NULL) {
    printf("error: create");
    return -1;
  }

  const char *data = DATA;
  int err = dmtxEncodeDataMatrix(enc, (int)strlen(data), (unsigned char *)data);
  if (err != DmtxPass) {
    printf("error: encode");
    return -1;
  }

  int symbolRow, symbolCol;

  fputs("\n██", stdout);
  for (symbolCol = 0; symbolCol < enc->region.symbolCols; symbolCol++) {
    fputs("██", stdout);
  }
  fputs("██\n", stdout);

  for (symbolRow = enc->region.symbolRows - 1; symbolRow >= 0; symbolRow--) {

    fputs("██", stdout);
    for (symbolCol = 0; symbolCol < enc->region.symbolCols; symbolCol++) {
      fputs((dmtxSymbolModuleStatus(enc->message, enc->region.sizeIdx,
                                    symbolRow, symbolCol) &
             DmtxModuleOnRGB)
                ? "  "
                : "██",
            stdout);
    }
    fputs("██\n", stdout);
  }

  fputs("██", stdout);
  for (symbolCol = 0; symbolCol < enc->region.symbolCols; symbolCol++) {
    fputs("██", stdout);
  }
  fputs("██\n", stdout);

  return 0;
}