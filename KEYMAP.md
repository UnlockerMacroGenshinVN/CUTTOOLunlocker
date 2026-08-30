# Bảng Tra Cứu Mã Phím (Windows Virtual-Key Code Map)

Tài liệu này cung cấp danh sách đầy đủ các mã phím ảo (**Virtual-Key Codes**) sử dụng cho các mục cấu hình phím trong file `config.ini` (ví dụ: `[NetworkToggleKey]` để bật/tắt mạng, `[ToggleKey]` để nạp lại cấu hình).

> **Lưu ý:** Khi điền vào file `config.ini`, hãy sử dụng giá trị ở cột **Mã Thập Phân (Decimal)**.

---

## 1. Phím Chức Năng (Function Keys)

| Tên Phím | Virtual-Key Code (C++) | Mã Thập Phân (Điền vào config.ini) | Mã Hex |
| :--- | :--- | :---: | :---: |
| **F1** | `VK_F1` | **112** | `0x70` |
| **F2** | `VK_F2` | **113** | `0x71` |
| **F3** | `VK_F3` | **114** | `0x72` |
| **F4** | `VK_F4` | **115** | `0x73` |
| **F5** | `VK_F5` | **116** | `0x74` |
| **F6** | `VK_F6` | **117** | `0x75` |
| **F7** | `VK_F7` | **118** | `0x76` |
| **F8** | `VK_F8` | **119** | `0x77` |
| **F9** | `VK_F9` | **120** | `0x78` |
| **F10** | `VK_F10` | **121** | `0x79` |
| **F11** | `VK_F11` | **122** | `0x7A` |
| **F12** | `VK_F12` | **123** | `0x7B` |

---

## 2. Phím Điều Hướng & Điều Khiển (Control & Navigation Keys)

| Tên Phím | Virtual-Key Code (C++) | Mã Thập Phân (Điền vào config.ini) | Mã Hex |
| :--- | :--- | :---: | :---: |
| **Tilde / Phím `~` / `\`** | `VK_OEM_3` | **192** | `0xC0` |
| **Tab** | `VK_TAB` | **9** | `0x09` |
| **Caps Lock** | `VK_CAPITAL` | **20** | `0x14` |
| **Space (Phím Cách)** | `VK_SPACE` | **32** | `0x20` |
| **Enter** | `VK_RETURN` | **13** | `0x0D` |
| **Escape (Esc)** | `VK_ESCAPE` | **27** | `0x1B` |
| **Backspace** | `VK_BACK` | **8** | `0x08` |
| **Home** | `VK_HOME` | **36** | `0x24` |
| **End** | `VK_END` | **35** | `0x23` |
| **Page Up** | `VK_PRIOR` | **33** | `0x21` |
| **Page Down** | `VK_NEXT` | **34** | `0x22` |
| **Insert** | `VK_INSERT` | **45** | `0x2D` |
| **Delete** | `VK_DELETE` | **46** | `0x2E` |
| **Mũi tên Trái (Left Arrow)** | `VK_LEFT` | **37** | `0x25` |
| **Mũi tên Lên (Up Arrow)** | `VK_UP` | **38** | `0x26` |
| **Mũi tên Phải (Right Arrow)** | `VK_RIGHT` | **39** | `0x27` |
| **Mũi tên Xuống (Down Arrow)** | `VK_DOWN` | **40** | `0x28` |

---

## 3. Phím Chuột (Mouse Buttons)

| Tên Nút Chuột | Virtual-Key Code (C++) | Mã Thập Phân (Điền vào config.ini) | Mã Hex |
| :--- | :--- | :---: | :---: |
| **Chuột Trái (Left Click)** | `VK_LBUTTON` | **1** | `0x01` |
| **Chuột Phải (Right Click)** | `VK_RBUTTON` | **2** | `0x02` |
| **Chuột Giữa (Middle Click)** | `VK_MBUTTON` | **4** | `0x04` |
| **Chuột Phụ 1 (XButton 1 - Back)** | `VK_XBUTTON1` | **5** | `0x05` |
| **Chuột Phụ 2 (XButton 2 - Forward)** | `VK_XBUTTON2` | **6** | `0x06` |

---

## 4. Phím Chữ Cái (Alphabet A - Z)

| Phím | Mã Thập Phân | Mã Hex | Phím | Mã Thập Phân | Mã Hex |
| :---: | :---: | :---: | :---: | :---: | :---: |
| **A** | **65** | `0x41` | **N** | **78** | `0x4E` |
| **B** | **66** | `0x42` | **O** | **79** | `0x4F` |
| **C** | **67** | `0x43` | **P** | **80** | `0x50` |
| **D** | **68** | `0x44` | **Q** | **81** | `0x51` |
| **E** | **69** | `0x45` | **R** | **82** | `0x52` |
| **F** | **70** | `0x46` | **S** | **83** | `0x53` |
| **G** | **71** | `0x47` | **T** | **84** | `0x54` |
| **H** | **72** | `0x48` | **U** | **85** | `0x55` |
| **I** | **73** | `0x49` | **V** | **86** | `0x56` |
| **J** | **74** | `0x4A` | **W** | **87** | `0x57` |
| **K** | **75** | `0x4B` | **X** | **88** | `0x58` |
| **L** | **76** | `0x4C` | **Y** | **89** | `0x59` |
| **M** | **77** | `0x4D` | **Z** | **90** | `0x5A` |

---

## 5. Phím Số Hàng Chính (Top Row Numbers 0 - 9)

| Phím | Virtual-Key Code (C++) | Mã Thập Phân (Điền vào config.ini) | Mã Hex |
| :---: | :--- | :---: | :---: |
| **0** | `'0'` | **48** | `0x30` |
| **1** | `'1'` | **49** | `0x31` |
| **2** | `'2'` | **50** | `0x32` |
| **3** | `'3'` | **51** | `0x33` |
| **4** | `'4'` | **52** | `0x34` |
| **5** | `'5'` | **53** | `0x35` |
| **6** | `'6'` | **54** | `0x36` |
| **7** | `'7'` | **55** | `0x37` |
| **8** | `'8'` | **56** | `0x38` |
| **9** | `'9'` | **57** | `0x39` |

---

## 6. Phím Bàn Phím Số (Numpad)

| Tên Phím | Virtual-Key Code (C++) | Mã Thập Phân (Điền vào config.ini) | Mã Hex |
| :--- | :--- | :---: | :---: |
| **Numpad 0** | `VK_NUMPAD0` | **96** | `0x60` |
| **Numpad 1** | `VK_NUMPAD1` | **97** | `0x61` |
| **Numpad 2** | `VK_NUMPAD2` | **98** | `0x62` |
| **Numpad 3** | `VK_NUMPAD3` | **99** | `0x63` |
| **Numpad 4** | `VK_NUMPAD4` | **100** | `0x64` |
| **Numpad 5** | `VK_NUMPAD5` | **101** | `0x65` |
| **Numpad 6** | `VK_NUMPAD6` | **102** | `0x66` |
| **Numpad 7** | `VK_NUMPAD7` | **103** | `0x67` |
| **Numpad 8** | `VK_NUMPAD8` | **104** | `0x68` |
| **Numpad 9** | `VK_NUMPAD9` | **105** | `0x69` |
| **Numpad \*** | `VK_MULTIPLY` | **106** | `0x6A` |
| **Numpad +** | `VK_ADD` | **107** | `0x6B` |
| **Numpad -** | `VK_SUBTRACT` | **109** | `0x6D` |
| **Numpad . (Dấu chấm)** | `VK_DECIMAL` | **110** | `0x6E` |
| **Numpad /** | `VK_DIVIDE` | **111** | `0x6F` |

---

## 7. Ký Tự Đặc Biệt & Dấu Câu (OEM Keys)

| Ký Tự | Tên Phím | Virtual-Key Code (C++) | Mã Thập Phân | Mã Hex |
| :---: | :--- | :--- | :---: | :---: |
| **`-`** | Dấu trừ / Gạch ngang | `VK_OEM_MINUS` | **189** | `0xBD` |
| **`=`** | Dấu bằng | `VK_OEM_PLUS` | **187** | `0xBB` |
| **`[`** | Ngoặc vuông mở | `VK_OEM_4` | **219** | `0xDB` |
| **`]`** | Ngoặc vuông đóng | `VK_OEM_6` | **221** | `0xDD` |
| **`\`** | Gạch chéo ngược | `VK_OEM_5` | **220** | `0xDC` |
| **`;`** | Chấm phẩy | `VK_OEM_1` | **186** | `0xBA` |
| **`'`** | Nháy đơn | `VK_OEM_7` | **222** | `0xDE` |
| **`,`** | Dấu phẩy | `VK_OEM_COMMA` | **188** | `0xBC` |
| **`.`** | Dấu chấm | `VK_OEM_PERIOD` | **190** | `0xBE` |
| **`/`** | Gạch chéo | `VK_OEM_2` | **191** | `0xBF` |

---

## 8. Ví dụ cấu hình trong `config.ini`

```ini
[EnableNetworkToggle]
Value=1

; Sử dụng phím F11 (122) để bật/tắt mạng
[NetworkToggleKey]
Value=122

; Sử dụng phím Home (36) để nạp lại config
[ToggleKey]
Value=36
```
