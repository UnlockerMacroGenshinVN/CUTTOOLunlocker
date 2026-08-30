# Hướng Dẫn Biến Dịch Dự Án (Build Guide)

Tài liệu này hướng dẫn chi tiết cách biên dịch (build) dự án **CUTTOOL.UnlockerIsland (Lite)** từ mã nguồn tại thư mục này.

---

## 📋 Yêu Cầu Tiền Trạm (Prerequisites)

1. **Hệ điều hành**: Windows 10/11 (64-bit).
2. **Trình biên dịch**: Microsoft Visual Studio 2022 (hoặc Visual Studio 2019/2026) đã cài đặt bộ công cụ **Desktop development with C++** (C++ v143 / v145 toolset).
3. **C++ Standard**: Dự án sử dụng chuẩn **C++17** / **C++20**.
4. **Kiến trúc mục tiêu**: **x64** (64-bit).

---

## 🛠️ Phương Pháp 1: Biên Dịch Bằng MSBuild (Dòng Lệnh / CLI)

Đây là cách nhanh nhất để build dự án bằng PowerShell hoặc Command Prompt.

### Bước 1: Mở Developer Command Prompt hoặc PowerShell
Mở **Developer Command Prompt for VS 2022** (hoặc mở PowerShell nếu đã cấu hình đường dẫn `msbuild`).

### Bước 2: Chuyển đến thư mục dự án
```powershell
cd D:\UnlockerIsland.new
```

### Bước 3: Biên dịch toàn bộ Solution (Release x64)
```powershell
msbuild Genshin.Fps.UnlockerIsland.sln /t:Build /p:Configuration=Release /p:Platform=x64
```

### Bước 4: Kiểm tra kết quả đầu ra
Sau khi biên dịch thành công, các tệp kết quả sẽ nằm tại các thư mục:
- `D:\UnlockerIsland.new\x64\Release\CUTTOOL.UnlockerIsland.dll` (Tệp DLL Unlocker chính)
- `D:\UnlockerIsland.new\x64\Release\Launcher.dll` (Tệp DLL Launcher)
- `D:\UnlockerIsland.new\x64\Release\Launcher_2.exe` (Tệp thực thi Launcher EXE)

---

## 💻 Phương Pháp 2: Biên Dịch Bằng Giao Diện Visual Studio IDE

### Bước 1: Mở Solution
1. Nhấp kép vào tệp `Genshin.Fps.UnlockerIsland.sln` tại thư mục `D:\UnlockerIsland.new\`.
2. Hoặc mở Visual Studio -> chọn **File** -> **Open** -> **Project/Solution...** -> chọn `Genshin.Fps.UnlockerIsland.sln`.

### Bước 2: Chọn Cấu Hình & Kiến Trúc
1. Trên thanh công cụ phía trên của Visual Studio, chọn cấu hình: **Release**.
2. Chọn nền tảng mục tiêu: **x64**.

### Bước 3: Tiến Hành Build
1. Nhấp chuột vào menu **Build** ở thanh trên cùng.
2. Chọn **Build Solution** (hoặc nhấn phím tắt `Ctrl + Shift + B`).

---

## ⚙️ Cấu Hình Tệp `config.ini` Đi Kèm

Sau khi build tệp DLL, tạo một tệp `config.ini` nằm cùng thư mục với `CUTTOOL.UnlockerIsland.dll` với nội dung mẫu bên dưới để kích hoạt các tính năng:

```ini
[DebugConsole]
Value=0

[FpsUnlock]
Value=1

[TargetFps]
Value=120

[VSync]
Value=0

[FovUnlock]
Value=1

[FovValue]
Value=55.0

[FovLimitCheck]
Value=1

[DisableCameraMove]
Value=1

[RemoveTeamAnim]
Value=1

[DisableBurstBlackscreen]
Value=1

[HideGrass]
Value=1

[HideGrassIndiscriminate]
Value=0

[DisableFog]
Value=1

[DumpOffsets]
Value=0
```

---

## 📂 Danh Sách 5 Tính Năng Được Tích Hợp

| Tính Năng | Cờ Cấu Hình (`config.ini`) | Mô Tả |
|---|---|---|
| **1. Loại bỏ di chuyển camera tự động** | `DisableCameraMove=1` | Tắt chuyển động camera tự động khi kích hoạt kỹ năng/event |
| **2. Mở giao diện đội hình bỏ qua chờ** | `RemoveTeamAnim=1` | Mở trực tiếp màn hình chỉnh đội hình không cần chờ hoạt ảnh |
| **3. Ẩn cỏ & Màn hình đen kỹ năng nổ** | `HideGrass=1`, `DisableBurstBlackscreen=1` | Ẩn cỏ và ngăn hiệu ứng màn hình đen / sương mù khi Burst |
| **4. Xóa bỏ sương mù môi trường** | `DisableFog=1` | Vô hiệu hóa lớp sương mù môi trường trong game |
| **5. Mở khóa FPS và FOV** | `FpsUnlock=1`, `FovUnlock=1` | Mở khóa giới hạn tốc độ khung hình (FPS) và tùy chỉnh FOV |
