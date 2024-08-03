# Eggscape
UET Advanced Programming Game Project in C++

## Tổng quan
Game lấy bối cảnh một cuộc buổi nấu nướng, trong đó bạn sẽ vào vai... một quả trứng, thực phẩm chính của món ăn. Tuy nhiên, đây không phải là một quả trứng bình thường như bao quả trứng khác, nó quyết không cam chịu số phận bị nhấn chìm trong dầu nóng hay nước sôi để rồi phải lên đĩa, kết thúc cuộc đời một cách chóng vánh trong bụng các thực khách háu ăn. Với tư cách là một quả trứng đã kinh qua những thí nghiệm khoa học tối mật, giờ đây nó đã tiến hoá, có thể di chuyển, nhảy nhót như sinh vật sống. Nhưng vấn đề ở đây là trứng không thể tự định hướng hay kiểm soát sức bật của bản thân, và sứ mệnh của bạn là hãy điều khiển trứng, đưa ra những chỉ dẫn một cách nhanh chóng và chính xác nhất có thể để giúp nó thoát khỏi bàn tay tử thần, hướng đến một tương lai tươi sáng hơn.

## Cách tải và cài đặt
Bước 1: Chuẩn bị nền tảng->Cài đặt Visual Studio Code.

- Game này được tạo ra bằng phần mềm Visual Studio Code phiên bản 1.91.
Link tải Visual Studio Code (cho các nền tảng khác nhau): https://code.visualstudio.com/Download

- Nếu bạn sử dụng Visual Studio Code(VSC) để chạy các chương trình viết bằng C/C++, bạn cần cấu hình lại VSC theo các bước trong link sau: https://code.visualstudio.com/docs/cpp/config-mingw

Bước 2: Tải game

- Cách 1: Clone repo này về bằng lệnh "git clone + link.git của repo này" trên terminal máy bạn
- Cách 2: Chọn Code -> Download Zip. Giải nén code ra 1 folder.

Bước 3: Cài đặt game

- Mở Visual Studio Code
- Thiết lập C/C++ Configuration(Intellisense)
- Các thư viện SDL cần thiết đã được thêm vào project(trong thư mục SDL2)
- Thực hiện các chỉnh sửa về đường dẫn(nếu cần)

Bước 4: Chạy game-> chạy file main.cpp

## Cách chơi

- Nhấn giữ chuột và kéo con trỏ để tạo đường đi cũng như lực bật cần thiết cho quả trứng(thể hiện qua độ dài đường kẻ), sau đó thả chuột để trứng cất cánh! Các bệ đỡ sẽ hạ xuống dần cho trứng đứng lên để leo cao hơn.
- Bạn sẽ thua cuộc nếu để trứng nhảy trượt, rơi xuống dầu sôi lửa bỏng. Dầu sẽ không ngừng dâng lên đuổi theo trứng, vì vậy bạn sẽ phải thật tập trung. Dọc đường bỏ trốn sẽ có các xu điểm, hãy ăn được càng nhiều càng tốt để tăng điểm, trốn thoát và phá vỡ kỉ lục của bản thân!