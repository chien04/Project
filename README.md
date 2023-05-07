# LEGACY FANTASY

## Giới thiệu

- Họ và tên : Bằng Văn Chiến 
- Mã sinh viên : 22021195
- Trường Đại học Công Nghệ - Đại Học Quốc Gia Hà Nội 

LEGACY FANTASY là một tựa game 2D được viết bằng ngôn ngữ C++ và sử dụng đồ hoạ SDL2 . Bạn sẽ được hoá thân vào một hiệp sĩ để thực hiện các thử thách bằng cách tiêu diệt quái và né các bẫy được tạo ra để hoàn thành thử thánh cho chính mình.
## Cách cài đặt game 
- Bước 1 : Clone hoặc tải file zip về [tại đây](https://github.com/chien04/Project/archive/refs/heads/master.zip)
- Bước 2 : Tải codeblock hoặc app viết code
- Bước 2 : Giải nén file zip và click vào file "game_test.exe" để chạy chương trình và chơi

## Gameplay
### Control
- ⬅ : Sang trái (Key left)
- ➡ : Sang phải (Key right)
- ⬆  : Đi lên (Key up)
- `A` : Tấn công
- `W` : Tấn công đặc biệt
- `E` : Sử dụng iTem HP
- `R` : Sử dụng iTem EP
### Các nhân vật trong game
**Player**

![player_sheet](https://github.com/chien04/Project/blob/master/image/playergit.png)

**Enemies**
- xuno: 

![player_sheet](https://github.com/chien04/Project/blob/master/image/xuno.png)

- wizard:

![player_sheet](https://github.com/chien04/Project/blob/master/image/wizardgit.png)

- boss:

![player_sheet](https://github.com/chien04/Project/blob/master/image/bossgit.png)

**chest**

![player_sheet](https://github.com/chien04/Project/blob/master/image/chest.png)

### Một số hình ảnh trong game
![Screenshot 2023-05-07 174847](https://user-images.githubusercontent.com/127939164/236673425-323c55e1-9af4-44dc-a6c4-78285ef56087.png)
![Screenshot 2023-05-07 174934](https://user-images.githubusercontent.com/127939164/236673433-fa0aa122-007b-4f77-8fe7-5f36434ecd74.png)
![Screenshot 2023-05-07 175008](https://user-images.githubusercontent.com/127939164/236673438-6e4359e1-c541-4d63-9ffe-66b7f937effb.png)
![Screenshot 2023-05-07 175042](https://user-images.githubusercontent.com/127939164/236673442-f8847acd-9670-4148-bc10-f0f12e2cd837.png)
![Screenshot 2023-05-07 175110](https://user-images.githubusercontent.com/127939164/236673447-83467845-fd87-4859-8131-c4c5cb4e6897.png)

### Battle
- Nhân vật có một thanh máu trên màn hình nếu thanh máu đó hết tức là người chơi sẽ thua cuộc
- Nhân vật sẽ được sử dụng chiêu thức tấn công đặc biệt khi đã đầy thanh Ep trên màn hình
  - Để có được Ep người chơi cần tấn công 3 lần vào quái hoặc dùng iTem Ep

### Setting
- Trong menu gồm có `Play`, `Guide` và `Quit`
  - `Play` bắt đầu trò chơi 
  - `Guide` xem hướng dẫn 
  - `Quit` thoát trò chơi
- Khi bắt đầu trò chơi
  - Bấm nút `ESC` hoặc nút dừng hiển thị trên màn hình để dừng
    - Khi dừng người chơi sẽ có các biểu tượng hiển thị trên màn hình và click chuột theo ý của mình
  - Khi người chơi thất bại hoặc đã giành chiến thắng 
    - Tương tự cũng sẽ hiện các biểu tượng trên màn hình và người chơi có thể click chuột vào theo ý mình 
    
## Kết luận
## Các kĩ thuật code
- Các kĩ thuật cơ bản : mảng , hàm , con trỏ, class, nhập xuất file,...
- Các kiểu dữ liệu cơ bản : int, set, vector,...
- Cách thuật toán : đánh dấu, ramdom, sử lý va chạm, tấn công kẻ thù khi vào phạm vi,... 
- modul hoá code, clean code.
- Sử dụng tối đa thư viện đồ hoạ SDL2 : SDL.h, SDL_image.h, SDL_mixel.h, SDL_ttf.h,..
## Bài học
- Hiểu sâu hơn về chia file và class 
- Phân chia thời gian hiệu quả hơn trong một project
- Học thêm các kĩ năng sử lý ảnh 
- ...
## Bổ sung
- Có thể sẽ cập nhật thêm các quái mới 
- Thêm kĩ năng tấn công mới 
- tạo level cho game 
- ...
