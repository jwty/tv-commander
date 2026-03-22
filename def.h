#ifndef _DEF_H_
#define _DEF_H_

//~ #define INHIBIT(X) X
#define INHIBIT(X) /* X */

#ifndef FONT_PRIMARY_SIZE
#define FONT_PRIMARY_SIZE 8
#endif

#ifndef FONT_FALLBACK_SIZE
#define FONT_FALLBACK_SIZE 7
#endif

// Panel
#define HEADER_H 17
#define HEADER_H_PHYS static_cast<int>(HEADER_H * screen.ppu_y)
#define HEADER_PADDING_TOP 3
#define HEADER_PADDING_TOP_PHYS static_cast<int>(HEADER_PADDING_TOP * screen.ppu_y)

#define FOOTER_H 13
#define FOOTER_H_PHYS static_cast<int>(FOOTER_H * screen.ppu_y)
#define FOOTER_PADDING_TOP 1
#define FOOTER_PADDING_TOP_PHYS static_cast<int>(FOOTER_PADDING_TOP * screen.ppu_y)

#define Y_LIST HEADER_H
#define Y_LIST_PHYS static_cast<int>(Y_LIST * screen.ppu_y)

#define LINE_HEIGHT 15
#define LINE_HEIGHT_PHYS static_cast<int>(LINE_HEIGHT * screen.ppu_y)
#define NB_VISIBLE_LINES ((screen.actual_h - FOOTER_H_PHYS - HEADER_H_PHYS - 1) / LINE_HEIGHT_PHYS + 1)
#define NB_FULLY_VISIBLE_LINES ((screen.actual_h - FOOTER_H_PHYS - HEADER_H_PHYS) / LINE_HEIGHT_PHYS)

// Dialogs
#define DIALOG_BORDER 2
#define DIALOG_PADDING 8

#endif // _DEF_H_
