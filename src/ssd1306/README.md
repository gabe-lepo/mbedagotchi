# SSD1306 Datasheet Notes

## Notes

### Memory addressing modes

```C
#define SSD1306_SET_MEM_ADDR_MODE 0x20
#define SSD1306_MEM_ADDR_MODE_HORIZ 0x00
#define SSD1306_MEM_ADDR_MODE_VERTI 0x01
#define SSD1306_MEM_ADDR_MODE_PAGE 0x02
```

3 different modes: page, horizontal, and vertical. Page addressing mode is a
legacy method, use horizontal or vertical modes.

In horizontal addressing mode, after RAM is read/written:

1. COL address pointer is incremented automatically
2. Once COL addr pointer reaches COL end addr, pointer resets to COL start addr
3. Then page addr pointer increments
4. Once both COL and Page addr pointers reach end addr, both reset to start addr

### Set column address

> Set COL start and end addresses

```C
#define SSD1306_SET_COL_ADDR 0x21
#define SSD1306_COL_ADDR_START_RESET 0x00
#define SSD1306_COL_ADDR_END_RESET 0x7F
```

- Setting COL addr will also set the COL addr pointer

### Set page address

> Set Page start and end addresses

```C
#define SSD1306_SET_PAGE_ADDR 0x22
#define SSD1306_PAGE_ADDR_START_RESET 0x00
#define SSD1306_PAGE_ADDR_END_RESET 0x07
```

### Contrast control

> Changes contrast value 0-255 (0x00 - 0xFF)

```C

#define SSD1306_SET_CONTRAST_CTRL 0x81
#define SSD1306_CONTRAST_MIN 0x00
#define SSD1306_CONTRAST_MID 0x7F
#define SSD1306_CONTRAST_MAX 0xFF
```

### Display on, off, inversion controls

> Control display on, off, with or without RAM contents, invert display, etc.

```C

#define SSD1306_ALL_DISP_ON_FOLLOW_RAM 0xA4
#define SSD1306_ALL_DISP_ON_IGNORE_RAM 0xA5

#define SSD1306_SET_NORMAL_DISP 0xA6
#define SSD1306_SET_INVERSE_DISP 0xA7

#define SSD1306_SET_DISP_SLEEP 0xAE
#define SSD1306_SET_DISP_AWAKE 0xAF
```

- Start with `ALL_DISP_ON_IGNORE_RAM` follwed by `ALL_DISP_ON_FOLLOW_RAM`
- `SET_DISP_AWAKE` and `SET_DISP_SLEEP` are really just to control
  sleep (OFF) and take screen out of sleep
- Inversion controls simple flip the screen pixel states

## Command Sequence
