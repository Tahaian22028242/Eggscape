# Eggscape
UET Advanced Programming Game Project in C++

# Giới thiệu bản thân:
- Họ và tên: Tạ Hải An

- Mã sinh viên: 22028242

- Lớp: K67-CA-CLC4

# Link video báo cáo + demo: https://drive.google.com/file/d/1CXJbhiCymGJsDoLBfEmC_GF2XW9IE4ul/view?usp=sharing

# Mô tả game

## Tổng quan
Game lấy bối cảnh một cuộc buổi nấu nướng, trong đó bạn sẽ vào vai... một quả trứng, thực phẩm chính của món ăn. Tuy nhiên, đây không phải là một quả trứng bình thường như bao quả trứng khác, nó quyết không cam chịu số phận bị nhấn chìm trong dầu nóng hay nước sôi để rồi phải lên đĩa, kết thúc cuộc đời một cách chóng vánh trong bụng các thực khách háu ăn. Với tư cách là một quả trứng đã kinh qua những thí nghiệm khoa học tối mật, giờ đây nó đã tiến hoá, có thể di chuyển, nhảy nhót như sinh vật sống. Nhưng vấn đề ở đây là trứng không thể tự định hướng hay kiểm soát sức bật của bản thân, và sứ mệnh của bạn là hãy điều khiển trứng, đưa ra những chỉ dẫn một cách nhanh chóng và chính xác nhất có thể để giúp nó thoát khỏi bàn tay tử thần, hướng đến một tương lai tươi sáng hơn.

## Cách tải và cài đặt
Bước 1: Chuẩn bị nền tảng->Cài đặt Visual Studio Code.

- Game này được tạo ra bằng phần mềm Visual Studio Code phiên bản 1.91. Link tải Visual Studio Code (cho các nền tảng khác nhau): https://code.visualstudio.com/Download

- Nếu bạn sử dụng Visual Studio Code(VSC) để chạy các chương trình viết bằng C/C++, bạn cần cấu hình lại VSC theo các bước trong link sau: https://code.visualstudio.com/docs/cpp/config-mingw

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

![splash_screen_image](https://github.com/user-attachments/assets/307fb01e-2944-4725-9d8d-39bd1f64f88b)

- Sau khi chờ một lúc(thời gian được cài đặt trong game), màn hình chính hiện lên, bao gồm nút Start để bắt đầu game, nút Skins để đi đến giao diện tuỳ chọn skins, nút Tutorial để đi đến giao diện hướng dẫn chơi và nút Settings để cài đặt game.

![menu_home_image](https://github.com/user-attachments/assets/88821248-1617-41e2-82ff-7f6520b2e9af)

- Bấm chọn Settings, giao diện cài đặt hiện lên, bao gồm chọn nhạc nền(có sẵn 2 nhạc trong project), điều chỉnh âm lượng nhạc và âm thanh bằng thanh kéo(nhấn giữ chuột và kéo). Ngoài ra còn có tuỳ chỉnh Border: On(có biên trái phải), off(không có biên) và nút Back để trở lại giao diện trước đó.

![settings1_image](https://github.com/user-attachments/assets/58adccfe-606b-498d-9570-91edf9f8fc7d)

![settings2_image](https://github.com/user-attachments/assets/a9d784ad-69b0-42ad-b6f8-d456a50d835f)

- Bấm chọn Skins, giao diện skins hiện lên, hiển thị 3 skin đã được thiết kế sẵn, người chơi có thể chọn tuỳ thích, sau đó nhấn Back để quay lại giao diện menu/home.

![default_skin_image](https://github.com/user-attachments/assets/a87d402f-6dd5-44fd-b63d-bb8877eecd24)

![armed_skin_image](https://github.com/user-attachments/assets/38976fdd-c375-46fe-9bef-2faa1afbcd4a)

![killer_skin_image](https://github.com/user-attachments/assets/82c6e109-9cd1-4086-b7fb-98cf02b59acb)

- Bấm chọn Tutorial, giao diện hướng dẫn hiện lên, hiển thị hướng dẫn cụ thể, người chơi cần đọc kỹ để nắm rõ cách chơi.

![tutorial_image](https://github.com/user-attachments/assets/bc589179-0f81-4469-a3ee-aaa1321a7bc6)

- Bấm chọn Start ở màn hình chính, màn hình game hiện lên gồm nhân vật chính là một quả trứng, các bệ đỡ để người chơi điều khiển quả trứng nhảy lên bằng chuột, các đối tượng khác như khiên, cầu lửa với các vai trò tương ứng(cụ thể hơn trong video báo cáo) xuất hiện và di chuyển ngẫu nhiên theo thuật toán đã được cài đặt trước. Ngoài ra còn hiển thị hộp điểm hiện điểm số hiện tại, điểm cao nhất đã đạt được và số mạng hiện có của nhân vật.

![start_game_image](https://github.com/user-attachments/assets/0ab8cd6c-acda-435e-9d0c-9f356787bfd6)

![aim_to_launch_image](https://github.com/user-attachments/assets/3c7fcece-5dfa-40dc-881a-f4c7af943d5e)

![player_with_shield](https://github.com/user-attachments/assets/03d7ed69-381b-44e6-a938-e2876a0f84b3)

- Nhấn P để tạm dừng game nếu game đang chạy và tiếp tục nếu đang tạm dừng. Khi đó giao diện tạm dừng hiện lên, có các nút chỉ dẫn "Nhấn P để tiếp tục", nút Settings để chuyển đến cài đặt , Restart để khởi động lại game nếu muốn và Home để về màn hình menu/home.

![pause_game_image](https://github.com/user-attachments/assets/caa4c697-b049-4ee3-a610-cbba9f02a247)

- Khi nhân vật chính hết sinh lực(do rơi xuống dung nham hoặc va chạm với cầu lửa với số lần bằng số mạng), màn hình hiển thị giao diện Game Over, bao gồm điểm cao nhất đạt được, nút chỉ dẫn "Nhấn R để tải lại game" nhấp nháy(người chơi có thể bấm nút R) hoặc click chọn Restart để bắt đầu ván mới, Home để trở về màn hình menu/home.

![game_over_image](https://github.com/user-attachments/assets/e50f8145-653c-4adc-8301-8dac63c42800)

- Người chơi cũng có thể nhấn nút Esc trên bàn phím để thoát game nhanh hơn.
  
# Source code

.vscode: các file cần thiết để config Visual Studio Code để chạy được game.

resources: các tài nguyên dùng trong game, gồm các hình ảnh, icon, âm thanh và phông chữ
  
- Nhân vật chính: một quả trứng.
  ![egg](https://github.com/user-attachments/assets/5ca54b34-b56e-49e6-9906-dfe5efb98a41)

- Các skin khác của nhân vật chính.
  ![armed_egg](https://github.com/user-attachments/assets/1128e0c3-7494-493b-a0d2-f714e0a1ff6c)
  ![killer_egg](https://github.com/user-attachments/assets/c15e664d-9908-400f-a36d-2b9de789c06e)
  
- Nền: bệ đỡ cho trứng đặt chân và leo lên(bằng cách nhảy), di chuyển theo quy luật ngẫu nhiên và sẽ trôi dần xuống dầu nóng(dung nham).
  ![platform](https://github.com/user-attachments/assets/c9150d42-1ffa-4e90-b215-c260ddfbec3e)
  ![plate](https://github.com/user-attachments/assets/17417145-fb52-45e0-9c1f-b76ce101c187) (chưa dùng)

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

build:
- main.exe: file .exe vận hành game.
- Các file .dll phục vụ việc chạy main.exe

demo_image: các hình ảnh demo game tương ứng.

# Nguồn tham khảo

- Tham khảo trên trang lazyfoo: https://lazyfoo.net/tutorials/SDL/

- Tham khảo code mẫu, tài nguyên và lấy cơ sở phát triển từ github(và cả video youtube với keyword cùng tên) của dev Polymars: https://github.com/PolyMarsDev/Terri-Fried

- Sự tự tìm tòi nghiên cứu phát triển thêm và thiết kế thêm một số hình ảnh của bản thân sinh viên(chi tiết thầy có thể xem lịch sử commit ạ).

# Tự đánh giá

## Các tính năng mới và thành tựu đã đạt được so với game gốc
= Tạo được thêm các giao diện mới: menu-home, tuỳ chọn skin, hướng dẫn tutorial, cài đặt settings, tạm dừng pause, thua cuộc game over.
- Có thể chuyển đổi từ giao diện này sang giao diện khác một cách linh hoạt.
- Thêm tính năng linh hoạt đổi skin ở giao diện skin, có thể thay đổi bất cứ lúc nào trong khi chơi game.
- Thêm nhạc nền và tuỳ chọn nhạc nền trong cài đặt(chủ động chọn nhạc, tăng giảm âm lượng).
- Thêm tính năng bật/tắt biên để xử lý va chạm khi nhảy cho người chơi, giúp người chơi có thêm phương án di chuyển và tiếp đất.
- Thêm bệ(platform) di chuyển, đối tượng hỗ trợ khiên(shield) và mối đe doạ(threat) được sinh ngẫu nhiên và di chuyển trên màn hình theo quy luật ngẫu nhiên, giúp game thêm phần thú vị.
- Thêm hệ thống sinh mạng và quản lý sinh mạng cho người chơi, giúp giảm bớt độ khó(có nhiều lần thử hơn).
- Thêm chức năng tạm dừng, chơi lại, truy cập đến các tính năng khác tại phần tạm dừng.

## Ưu điểm
- Bước đầu biết sử dụng thư viện SDL để làm game.
- Bước đầu biết chia file, tạo lớp, hàm, cấu trúc, mô đun hoá dự án, tuy còn sơ sài.
- Có thể tư duy logic để chỉnh sửa game cho hợp lý, sử dụng được kĩ thuật debug cơ bản và fix được các bug, các lỗi từ phổ thông đến chuyên môn.
- Phát triên được thêm một số tính năng quan trọng cho game.
- Bước đầu biết tự thiết kế hình ảnh(threat, plate...).

## Nhược điểm
- Tính đến thời điểm nộp bài, vẫn chưa kịp phát triển thêm được các tính năng đã dự định hoặc mong muốn(hiển thị mạng, thêm hướng dẫn, thêm cửa hàng bán skin hoặc mở khoá đồ phụ trợ sử dụng xu kiếm được làm phương tiện trao đổi, thêm tuỳ chỉnh và chọn mức độ khó, thêm loại threat mới...).
  - **Cập nhật: Đã có thêm các tính năng: hiển thị mạng, hướng dẫn, thay đổi skin.
- File main.cpp còn tương đối to và hơi lộn xộn, cần phải chia ra thêm các file xử lý để gọn hơn.
- Đồ hoạ nói chung còn sơ sài, chưa cuốn hút, background vẽ bằng SDL nên không hấp dẫn, chưa nhiều âm thanh đa dạng.g
- ReadMe và video báo cáo demo chưa thật sự rõ ràng đầy đủ và lôi cuốn, trình bày còn thiếu sót, ngắc ngứ.

# Tổng kết
- Em xin gửi lời cảm ơn sâu sắc đến những kiến thức, kĩ năng mà thầy Lê Đức Trọng đã truyền dạy cho chúng em cùng sự đôn đốc, sát sao của thầy với bài tập lớn ạ.
- Do kĩ năng của bản thân còn non kém và quỹ thời gian khá eo hẹp, nên còn nhiều điều em muốn làm thêm với dự án mà chưa thể làm được. Vì vậy, em kính mong thầy hết sức thông cảm và châm chước cho những thiếu sót còn tồn tại trong bài tập lớn của em ạ. Nếu có thể em rất mong thầy có thể nới thêm deadline để em có thể phát triển game hơn nữa ạ.
  - **Cập nhật ReadMe: Game đã hoàn thiện hơn trước ạ.

# Em xin chân thành cảm ơn thầy ạ!














