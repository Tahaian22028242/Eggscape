# Eggscape
UET Advanced Programming Game Project in C++

# Giới thiệu bản thân:
- Họ và tên: Tạ Hải An

- Mã sinh viên: 22028242

- Lớp: K67-CA-CLC4

# Link video báo cáo + demo: https://drive.google.com/file/d/1CXJbhiCymGJsDoLBfEmC_GF2XW9IE4ul/view?usp=sharing

## Tổng quan
Game lấy bối cảnh một cuộc buổi nấu nướng, trong đó bạn sẽ vào vai... một quả trứng, thực phẩm chính của món ăn. Tuy nhiên, đây không phải là một quả trứng bình thường như bao quả trứng khác, nó quyết không cam chịu số phận bị nhấn chìm trong dầu nóng hay nước sôi để rồi phải lên đĩa, kết thúc cuộc đời một cách chóng vánh trong bụng các thực khách háu ăn. Với tư cách là một quả trứng đã kinh qua những thí nghiệm khoa học tối mật, giờ đây nó đã tiến hoá, có thể di chuyển, nhảy nhót như sinh vật sống. Nhưng vấn đề ở đây là trứng không thể tự định hướng hay kiểm soát sức bật của bản thân, và sứ mệnh của bạn là hãy điều khiển trứng, đưa ra những chỉ dẫn một cách nhanh chóng và chính xác nhất có thể để giúp nó thoát khỏi bàn tay tử thần, hướng đến một tương lai tươi sáng hơn.

## Cách tải và cài đặt
Bước 1: Chuẩn bị nền tảng->Cài đặt Visual Studio Code.

- Game này được tạo ra bằng phần mềm Visual Studio Code phiên bản 1.91. Link tải Visual Studio Code (cho các nền tảng khác nhau): https://code.visualstudio.com/Download

* Nếu bạn sử dụng Visual Studio Code(VSC) để chạy các chương trình viết bằng C/C++, bạn cần cấu hình lại VSC theo các bước trong link sau: https://code.visualstudio.com/docs/cpp/config-mingw

Bước 2: Tải game

- Cách 1: Clone repo này về bằng lệnh "git clone + link.git của repo này" trên terminal máy bạn
- Cách 2: Chọn Code -> Download Zip. Giải nén code ra 1 folder.

Bước 3: Cài đặt game

- Mở Visual Studio Code
- Thiết lập C/C++ Configuration(IntelliSense)
- Các thư viện SDL cần thiết đã được thêm vào project(trong thư mục SDL2)
- Thực hiện các chỉnh sửa về đường dẫn(nếu cần)

Bước 4: Chạy game-> chạy file main.cpp

## Cách chơi

- Nhấn giữ chuột và kéo con trỏ để tạo đường đi cũng như lực bật cần thiết cho quả trứng(thể hiện qua độ dài đường kẻ), sau đó thả chuột để trứng cất cánh! Các bệ đỡ sẽ hạ xuống dần cho trứng đứng lên để leo cao hơn. Dọc đường sẽ có vật phẩm hỗ trợ(khiên) và cầu lửa trồi lên từ dung nham(dầu sôi).

- Các nút bổ trợ: P để tạm dừng/tiếp tục game, R để tải lại game(chỉ khả dụng ở giao diện Game Over), Esc để thoát game nhanh(không cần click vào dấu x ở góc phải trên cửa sổ game).

- Bạn sẽ thua cuộc nếu để trứng nhảy trượt, rơi xuống dầu sôi lửa bỏng. Dầu sẽ không ngừng dâng lên đuổi theo trứng, vì vậy bạn sẽ phải thật tập trung. Dọc đường bỏ trốn sẽ có các xu điểm, hãy ăn được càng nhiều càng tốt để tăng điểm, trốn thoát và phá vỡ kỉ lục của bản thân!

## Chi tiết hoạt động game

- Màn hình game sau khi buid và run thành công.

![Screenshot 2024-08-18 225514](https://github.com/user-attachments/assets/cba04cd6-80fe-461e-885e-228b864aab66)

- Sau khi chờ một lúc(thời gian được cài đặt trong game), màn hình chính hiện lên, bao gồm nút Start để bắt đầu game và nút Settings để cài đặt game.

![Screenshot 2024-08-18 213940](https://github.com/user-attachments/assets/87f1198b-0885-4d1b-b8a0-6f2eaeb5089b)

- Bấm chọn Settings, giao diện cài đặt hiện lên, bao gồm chọn nhạc nền(có sẵn 2 nhạc trong project), điều chỉnh âm lượng nhạc và âm thanh bằng thanh kéo(nhấn giữ chuột và kéo). Ngoài ra còn có tuỳ chỉnh Border: On(có biên trái phải), off(không có biên) và nút Back để trở lại giao diện trước đó.

![Screenshot 2024-08-18 225602](https://github.com/user-attachments/assets/e440875b-cdbf-420c-8deb-985402033cf5)

![Screenshot 2024-08-18 225708](https://github.com/user-attachments/assets/735e32cb-ca69-4c25-be30-4b9ab03ac28e)

- Bấm chọn Start ở màn hình chính, màn hình game hiện lên gồm nhân vật chính là một quả trứng, các bệ đỡ để người chơi điều khiển quả trứng nhảy lên bằng chuột, các đối tượng khác như khiên, cầu lửa với các vai trò tương ứng(cụ thể hơn trong video báo cáo) xuất hiện và di chuyển ngẫu nhiên theo thuật toán đã được cài đặt trước. Ngoài ra còn có hộp điểm hiện điểm số hiện tại và điểm cao nhất hiện tại.

![Screenshot 2024-08-18 225837](https://github.com/user-attachments/assets/b97e5c62-3ea4-46d0-8a6b-c6afe4778c02)

![Screenshot 2024-08-18 225942](https://github.com/user-attachments/assets/039f588f-08f7-4a16-ac7f-7898b526433c)

![Screenshot 2024-08-18 230032](https://github.com/user-attachments/assets/d394bdb0-144f-4349-bbf8-c427505f5d6c)

![Screenshot 2024-08-18 230258](https://github.com/user-attachments/assets/d7fdebd4-3a65-4e29-862f-d0601114fa4b)

- Nhấn P để tạm dừng game nếu game đang chạy và tiếp tục nếu đang tạm dừng. Khi đó giao diện tạm dừng hiện lên, có các nút chỉ dẫn "Nhấn P để tiếp tục", nút Settings để chuyển đến cài đặt và restart để khởi động lại game nếu muốn.

![Screenshot 2024-08-18 230158](https://github.com/user-attachments/assets/866578f2-5e1f-4c09-a9cf-3fe9016c861c)

- Khi nhân vật chính hết sinh lực(do rơi xuống dung nham hoặc va chạm với cầu lửa với số lần bằng số mạng), màn hình hiển thị giao diện Game Over, bao gồm điểm cao nhất đạt được, nút chỉ dẫn "Nhấn R để tải lại game" nhấp nháy(người chơi có thể bấm nút R) hoặc click chọn restart để khởi động lại, nút Home để trở về màn hình chính ban đầu.

![Screenshot 2024-08-18 230055](https://github.com/user-attachments/assets/76e2e59a-dab6-4969-a452-fadf749c5f40)

- Người chơi cũng có thể nhấn nút Esc trên bàn phím để thoát game nhanh hơn.
  
# Source code

.vscode: các file cần thiết để config Visual Studio Code để chạy được game.

resources: các tài nguyên dùng trong game, gồm các hình ảnh, icon, âm thanh và phông chữ
  
- Nhân vật chính: một quả trứng.
  ![egg](https://github.com/user-attachments/assets/5ca54b34-b56e-49e6-9906-dfe5efb98a41)

- Nền: bệ đỡ cho trứng đặt chân và leo lên(bằng cách nhảy), di chuyển theo quy luật ngẫu nhiên và sẽ trôi dần xuống dầu nóng(dung nham).
  ![platform](https://github.com/user-attachments/assets/c9150d42-1ffa-4e90-b215-c260ddfbec3e)

- Xu: dùng để tăng điểm khi va chạm với trứng.
  ![coin](https://github.com/user-attachments/assets/5dc08e54-969c-4449-86d1-aea25a4c6fb3)

- Cầu lửa: chướng ngại vật, mối đe doạ với trứng, di chuyển theo quy luật ngẫu nhiên và giảm mạng của trứng đi 1 nếu va chạm
  ![fireball](https://github.com/user-attachments/assets/191ce164-8d66-46aa-a3c4-c85e0c629741)

- Khiên: tạo lớp bảo vệ cho trứng khi va chạm, chịu được 1 lần va chạm của cầu lửa để bảo vệ trứng không mất mạng, di chuyển theo quy luật ngẫu nhiên để trứng nếu khéo léo có thể lấy được.
  ![splash_egg](https://github.com/user-attachments/assets/40b03672-befc-4464-b5a8-ec4b47808cd8)

- Hộp điểm: chứa điểm được viết bằng text.
  ![scorebox](https://github.com/user-attachments/assets/0fec9f35-242d-4678-89e2-58ec1ec842e6)

Cùng các hình ảnh khác có thể sử dụng nếu muốn.

- Các file âm thanh .wav dùng cho việc tạo âm thanh tương ứng trong game.
- 2 nhạc nền có sẵn(tên chuẩn).
- Font chữ hiện có: font.otf

SDL2: tài nguyên SDL thiết yếu cần để làm game.

src: các file C/C++(.hpp trong header và .cpp tương ứng) để xây dựng và chạy game.
- cleanupp: dọn dẹp tài nguyên, giải phóng bộ nhớ sau khi thoát game.
- init: khởi tạo SDL(hình ảnh, âm thanh, phông chữ)).
- platform: quản lý việc tạo và xử lý đối tượng bệ đỡ.
- player: quản lý việc tạo và xử lý đối tượng người chơi(quả trứng).
- resourcesManager: quản lý tài nguyên(tải hình ảnh, âm thanh, vẽ ảnh, viết chữ).
- resourcesPath: các đường dẫn đến các file tài nguyên(cần sửa cho phù hợp khi tải source về).
- scoreManager: quản lý điểm.
- shield: quản lý việc tạo và xử lý đối tượng khiên.
- threat: quản lý việc tạo và xử lý đối tượng khiên.
- main: file chính để vận hành game, quản lý tất cả các tính năng chính(xử lý va chạm, chơi lại, cài đặt, tạm dừng... và nhiều công việc nữa).

highscore.bin: file nhị phân lưu điểm và tải điểm.

main.exe: file .exe vận hành game.

Các file .dll phục vụ việc chạy main.exe

# Nguồn tham khảo

- Tham khảo trên trang lazyfoo: https://lazyfoo.net/tutorials/SDL/

- Tham khảo code mẫu, tài nguyên và lấy cơ sở phát triển từ github(và cả video youtube với keyword cùng tên) của dev Polymars: https://github.com/PolyMarsDev/Terri-Fried

- Sự tự tìm tòi nghiên cứu phát triển thêm và thiết kế thêm một số hình ảnh của bản thân sinh viên(chi tiết thầy có thể xem lịch sử commit ạ).

# Tự đánh giá:

Ưu điểm:
- Bước đầu biết sử dụng thư viện SDL để làm game.
- Bước đầu biết chia file, tạo lớp, hàm, cấu trúc, mô đun hoá dự án, tuy còn sơ sài.
- Có thể tư duy logic để chỉnh sửa game cho hợp lý, sử dụng được kĩ thuật debug cơ bản và fix được các bug, các lỗi từ phổ thông đến chuyên môn.
- Phát triên được thêm một số tính năng quan trọng cho game.
- Bước đầu biết tự thiết kế hình ảnh(threat, plate...).

Nhược điểm:
- Tính đến thời điểm nộp bài, vẫn chưa kịp phát triển thêm được các tính năng đã dự định hoặc mong muốn(hiển thị mạng, thêm cửa hàng bán skin hoặc mở khoá đồ phụ trợ sử dụng xu kiếm được làm phương tiện trao đổi, thêm tuỳ chỉnh và chọn mức độ khó, thêm loại threat mới...).
- File main.cpp còn tương đối to và hơi lộn xộn, cần phải chia ra thêm các file xử lý để gọn hơn.
- Đồ hoạ nói chung còn sơ sài, chưa cuốn hút, background vẽ bằng SDL nên không hấp dẫn, chưa nhiều âm thanh đa dạng.g
- ReadMe và video báo cáo demo chưa thật sự rõ ràng đầy đủ và lôi cuốn, trình bày còn thiếu sót, ngắc ngứ.

# Tổng kết:
- Em xin gửi lời cảm ơn sâu sắc đến những kiến thức, kĩ năng mà thầy Lê Đức Trọng đã truyền dạy cho chúng em cùng sự đôn đốc, sát sao của thầy với bài tập lớn ạ.
- Do kĩ năng của bản thân còn non kém và quỹ thời gian khá eo hẹp, nên còn nhiều điều em muốn làm thêm với dự án mà chưa thể làm được. Vì vậy, em kính mong thầy hết sức thông cảm và châm chước cho những thiếu sót còn tồn tại trong bài tập lớn của em ạ. Nếu có thể em rất mong thầy có thể nới thêm deadline để em có thể phát triển game hơn nữa ạ.

# Em xin chân thành cảm ơn thầy ạ!














