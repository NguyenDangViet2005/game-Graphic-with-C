#ifndef RHINO_H
#define RHINO_H

#include <graphics.h>

// Vẽ con tê giác
void drawRhino(int x, int y) {
    setlinestyle(SOLID_LINE, 0, 1);
    
    // Bảng màu
    int bodyColor = COLOR(180, 185, 205);      // Xám xanh nhạt
    int shadowColor = COLOR(110, 115, 145);    // Bóng đậm
    int midShadow = COLOR(145, 150, 175);      // Bóng trung gian
    int lightShadow = COLOR(165, 170, 190);    // Bóng nhạt
    int highlightColor = COLOR(220, 225, 240); // Điểm sáng
    int brightHighlight = COLOR(235, 240, 250);// Điểm sáng cực độ
    int hornColor = COLOR(235, 230, 210);      // Sừng màu ngà
    int hornShadow = COLOR(190, 180, 160);     // Bóng sừng
    int hornDark = COLOR(160, 150, 135);       // Bóng sừng đậm
    int nailColor = COLOR(60, 65, 85);         // Móng chân
    int outlineColor = COLOR(30, 25, 40);      // Viền đen/tím đậm
    
    // Chân sau - Vẽ body trước
    setfillstyle(SOLID_FILL, shadowColor);
    bar(x + 26, y - 24, x + 34, y - 2);
    setfillstyle(SOLID_FILL, lightShadow);
    bar(x + 26, y - 24, x + 30, y - 8); // Highlight mặt trước chân
    // Khớp gối
    setfillstyle(SOLID_FILL, midShadow);
    bar(x + 26, y - 16, x + 34, y - 14);
    // Móng
    setfillstyle(SOLID_FILL, nailColor);
    bar(x + 26, y - 6, x + 34, y - 1);
    setfillstyle(SOLID_FILL, outlineColor);
    bar(x + 29, y - 7, x + 31, y - 1); // Khe móng
    // Viền chân sau xa (chỉ 3 cạnh)
    bar(x + 24, y - 24, x + 26, y);
    bar(x + 26, y - 2, x + 34, y); 
    bar(x + 34, y - 24, x + 36, y);

    // Chân trước - Vẽ body trước
    setfillstyle(SOLID_FILL, shadowColor);
    bar(x - 18, y - 24, x - 10, y - 2);
    setfillstyle(SOLID_FILL, lightShadow);
    bar(x - 18, y - 24, x - 14, y - 8); // Highlight mặt trước
    // Khớp khuỷu
    setfillstyle(SOLID_FILL, midShadow);
    bar(x - 18, y - 18, x - 10, y - 16);
    // Móng
    setfillstyle(SOLID_FILL, nailColor);
    bar(x - 18, y - 6, x - 10, y - 1);
    setfillstyle(SOLID_FILL, outlineColor);
    bar(x - 15, y - 7, x - 13, y - 1); // Khe móng
    // Viền chân trước
    bar(x - 20, y - 24, x - 18, y); 
    bar(x - 18, y - 2, x - 10, y);   
    bar(x - 10, y - 24, x - 8, y);  

    // === 2. ĐUÔI (Cong mượt hơn) ===
    setcolor(outlineColor);
    setlinestyle(SOLID_LINE, 0, 3);
    line(x + 40, y - 40, x + 48, y - 26);
    line(x + 48, y - 26, x + 50, y - 22);
    setfillstyle(SOLID_FILL, outlineColor);
    fillellipse(x + 50, y - 20, 3, 6); // Chóp lông dài hơn
    // Lông đuôi chi tiết
    setlinestyle(SOLID_LINE, 0, 2);
    setcolor(midShadow);
    line(x + 49, y - 22, x + 51, y - 18);
    line(x + 48, y - 23, x + 52, y - 20);
    setlinestyle(SOLID_LINE, 0, 1);

    // thân
    // Vẽ outline thân với đường cong lưng
    setcolor(outlineColor);
    setfillstyle(SOLID_FILL, outlineColor);
    
    // Phần vai
    int backCurveVai[] = {
        x - 45, y - 12,    // Điểm dưới trái
        x - 45, y - 62,    // Lên cổ trái
        x - 40, y - 68,    // Đỉnh vai trái (cao nhất)
        x - 20, y - 70,    // Đỉnh lưng giữa val (cong cao)
        x - 5, y - 68,     // Đỉnh vai phải
        x + 0, y - 64,     // Xuống vai phải
        x + 6, y - 56,     // Xuống chỗ nối
        x + 6, y - 12,     // Xuống bụng phải
        x - 45, y - 12     // Đóng polygon
    };
    fillpoly(9, backCurveVai);
    
    // Phần mông
    int backCurveMong[] = {
        x + 6, y - 12,     // Điểm dưới trái (nối vai)
        x + 6, y - 56,     // Lên chỗ nối
        x + 10, y - 52,    // Lên lưng mông trái
        x + 20, y - 53,    // Đỉnh lưng mông giữa (cong nhẹ)
        x + 32, y - 52,    // Đỉnh lưng mông phải
        x + 40, y - 48,    // Xuống mông phải
        x + 44, y - 40,    // Xuống mông phải thấp
        x + 44, y - 12,    // Xuống bụng phải
        x + 6, y - 12      // Đóng polygon
    };
    fillpoly(9, backCurveMong);
    
    // Điền màu thân với gradient
    setfillstyle(SOLID_FILL, bodyColor);
    
    // Vai cao với đường cong
    int bodyVai[] = {
        x - 43, y - 16,
        x - 43, y - 60,
        x - 38, y - 66,
        x - 20, y - 68,
        x - 5, y - 66,
        x + 2, y - 62,
        x + 4, y - 54,
        x + 4, y - 16,
        x - 43, y - 16
    };
    fillpoly(9, bodyVai);
    
    // Mông thấp với đường cong
    int bodyMong[] = {
        x + 8, y - 16,
        x + 8, y - 54,
        x + 12, y - 50,
        x + 20, y - 51,
        x + 32, y - 50,
        x + 38, y - 46,
        x + 42, y - 38,
        x + 42, y - 16,
        x + 8, y - 16
    };
    fillpoly(9, bodyMong);

    // Bóng dưới bụng (nhiều lớp)
    setfillstyle(SOLID_FILL, shadowColor);
    bar(x - 40, y - 22, x + 40, y - 16);
    setfillstyle(SOLID_FILL, midShadow);
    bar(x - 40, y - 28, x + 40, y - 22);
    setfillstyle(SOLID_FILL, lightShadow);
    bar(x - 40, y - 34, x + 40, y - 28);
    
    // Highlight trên lưng cong (theo đường cong)
    setfillstyle(SOLID_FILL, brightHighlight);
    // Đỉnh vai cong
    int highlightVai1[] = {
        x - 38, y - 64,
        x - 34, y - 66,
        x - 20, y - 68,
        x - 12, y - 66,
        x - 8, y - 64,
        x - 12, y - 62,
        x - 20, y - 64,
        x - 34, y - 62,
        x - 38, y - 64
    };
    fillpoly(9, highlightVai1);
    
    setfillstyle(SOLID_FILL, highlightColor);
    // Vai sáng rộng hơn
    int highlightVai2[] = {
        x - 40, y - 62,
        x - 36, y - 64,
        x - 20, y - 66,
        x - 5, y - 64,
        x + 2, y - 60,
        x + 0, y - 58,
        x - 8, y - 60,
        x - 20, y - 62,
        x - 36, y - 60,
        x - 40, y - 62
    };
    fillpoly(10, highlightVai2);
    
    // Mông sáng
    int highlightMong[] = {
        x + 12, y - 48,
        x + 20, y - 49,
        x + 32, y - 48,
        x + 36, y - 46,
        x + 32, y - 46,
        x + 20, y - 47,
        x + 12, y - 46,
        x + 12, y - 48
    };
    fillpoly(8, highlightMong);
    
    setfillstyle(SOLID_FILL, lightShadow);
    int highlightMong2[] = {
        x + 10, y - 46,
        x + 20, y - 47,
        x + 32, y - 46,
        x + 38, y - 44,
        x + 38, y - 42,
        x + 32, y - 44,
        x + 20, y - 45,
        x + 10, y - 44,
        x + 10, y - 46
    };
    fillpoly(9, highlightMong2);
    
    // Các chấm texture da (Skin spots)
    setfillstyle(SOLID_FILL, midShadow);
    bar(x - 35, y - 58, x - 33, y - 56);
    bar(x - 20, y - 62, x - 18, y - 60);
    bar(x - 8, y - 56, x - 6, y - 54);
    bar(x + 15, y - 48, x + 17, y - 46);
    bar(x + 25, y - 44, x + 27, y - 42);
    bar(x + 35, y - 40, x + 37, y - 38);
    
    // đầu và cổ
    // Khối đầu chính
    setfillstyle(SOLID_FILL, outlineColor);
    bar(x - 62, y - 50, x - 35, y - 22);
    setfillstyle(SOLID_FILL, bodyColor);
    bar(x - 60, y - 48, x - 37, y - 24);
    
    // Mũi với đường cong
    setfillstyle(SOLID_FILL, outlineColor);
    bar(x - 70, y - 40, x - 58, y - 26);
    bar(x - 72, y - 38, x - 70, y - 30); // Mở rộng mũi
    setfillstyle(SOLID_FILL, bodyColor);
    bar(x - 68, y - 38, x - 60, y - 28);
    
    // Phần nối cổ mượt mại
    setfillstyle(SOLID_FILL, bodyColor);
    bar(x - 38, y - 38, x - 35, y - 24); // Nối cổ-vai
    setfillstyle(SOLID_FILL, midShadow);
    bar(x - 36, y - 36, x - 35, y - 28); // Bóng cổ
    
    // Bóng dưới đầu/cằm
    setfillstyle(SOLID_FILL, shadowColor);
    bar(x - 66, y - 28, x - 37, y - 24);
    setfillstyle(SOLID_FILL, midShadow);
    bar(x - 66, y - 32, x - 37, y - 28);
    setfillstyle(SOLID_FILL, lightShadow);
    bar(x - 66, y - 36, x - 40, y - 32);
    
    // Highlight trán
    setfillstyle(SOLID_FILL, brightHighlight);
    bar(x - 54, y - 48, x - 46, y - 46);
    setfillstyle(SOLID_FILL, highlightColor);
    bar(x - 58, y - 48, x - 42, y - 44);
    
    // Nếp nhăn da đầu
    setcolor(midShadow);
    line(x - 52, y - 42, x - 44, y - 42);
    line(x - 54, y - 38, x - 46, y - 38);

    // Sừng
    // Sừng lớn
    setcolor(outlineColor);
    setfillstyle(SOLID_FILL, WHITE);
    int bigHorn[] = {x-64, y-32, x-70, y-46, x-67, y-48, x-62, y-32};
    fillpoly(4, bigHorn);
    drawpoly(4, bigHorn);
    
    // Lớp màu sừng với gradient sáng
    setfillstyle(SOLID_FILL, COLOR(255, 255, 255)); // Highlight sừng trắng sáng
    int bigHornHi[] = {x-64, y-32, x-67, y-40, x-66, y-42, x-63, y-32};
    fillpoly(4, bigHornHi);
    
    // Bóng sừng nhẹ 
    setfillstyle(SOLID_FILL, COLOR(220, 220, 230));
    int bigHornSh[] = {x-63, y-33, x-69, y-46, x-67, y-48, x-62, y-34};
    fillpoly(4, bigHornSh);

    // Sừng nhỏ (Còn nhỏ hơn, có vân) - MÀU TRẮNG
    setcolor(outlineColor);
    setfillstyle(SOLID_FILL, WHITE);
    int smallHorn[] = {x-56, y-36, x-60, y-44, x-58, y-46, x-54, y-36};
    fillpoly(4, smallHorn);
    drawpoly(4, smallHorn);
    
    // Highlight sừng nhỏ
    setfillstyle(SOLID_FILL, COLOR(255, 255, 255));
    int smallHornHi[] = {x-56, y-36, x-58, y-40, x-57, y-42, x-55, y-36};
    fillpoly(4, smallHornHi);
    
    // Bóng sừng nhỏ
    setfillstyle(SOLID_FILL, COLOR(220, 220, 230));
    int smallHornSh[] = {x-55, y-37, x-60, y-44, x-58, y-46, x-54, y-38};
    fillpoly(4, smallHornSh);

    // Tai 
    setfillstyle(SOLID_FILL, outlineColor);
    bar(x - 46, y - 62, x - 37, y - 48);
    setfillstyle(SOLID_FILL, shadowColor); // Tai xa
    bar(x - 52, y - 56, x - 47, y - 48); 
    setfillstyle(SOLID_FILL, bodyColor); // Tai gần
    bar(x - 44, y - 60, x - 39, y - 50);
    // Bên trong tai
    setfillstyle(SOLID_FILL, shadowColor);
    bar(x - 43, y - 58, x - 41, y - 52);
    // Highlight tai
    setfillstyle(SOLID_FILL, highlightColor);
    bar(x - 42, y - 60, x - 40, y - 56);
    
    // Lông mày giận dữ
    setfillstyle(SOLID_FILL, outlineColor);
    bar(x - 54, y - 46, x - 46, y - 45);
    
    // Mắt lớn hơn, sắc sảo
    setfillstyle(SOLID_FILL, shadowColor); // Hốc mắt sâu
    bar(x - 53, y - 45, x - 45, y - 40);
    setfillstyle(SOLID_FILL, outlineColor); // Nhãn cầu
    bar(x - 52, y - 44, x - 47, y - 41);
    setfillstyle(SOLID_FILL, WHITE); // Ánh mắt
    bar(x - 50, y - 43, x - 49, y - 42);
    bar(x - 48, y - 42, x - 47, y - 41); // Ánh sáng phụ
    
    // Lỗ mũi to hơn, rõ hơn
    setfillstyle(SOLID_FILL, outlineColor);
    bar(x - 67, y - 35, x - 64, y - 32);
    bar(x - 66, y - 31, x - 65, y - 30); // Lỗ mũi sâu
    
    // Miệng/hàm
    setfillstyle(SOLID_FILL, outlineColor);
    bar(x - 68, y - 28, x - 62, y - 27);

    // Chân trước gần - Vẽ body trước
    setfillstyle(SOLID_FILL, bodyColor);
    bar(x - 36, y - 26, x - 24, y - 2);
    
    // Cơ bắp chân (Highlight mặt trước)
    setfillstyle(SOLID_FILL, highlightColor);
    bar(x - 35, y - 26, x - 30, y - 10);
    setfillstyle(SOLID_FILL, lightShadow);
    bar(x - 30, y - 26, x - 26, y - 10);
    
    // Bóng chân
    setfillstyle(SOLID_FILL, midShadow);
    bar(x - 30, y - 24, x - 24, y - 8);
    setfillstyle(SOLID_FILL, shadowColor);
    bar(x - 28, y - 20, x - 24, y - 10);
    
    // Khớp khuỷu/đầu gối
    setfillstyle(SOLID_FILL, outlineColor);
    bar(x - 36, y - 18, x - 24, y - 16);
    setfillstyle(SOLID_FILL, midShadow);
    bar(x - 35, y - 17, x - 25, y - 16);
    
    // Móng chân
    setfillstyle(SOLID_FILL, nailColor);
    bar(x - 36, y - 8, x - 24, y - 2);
    setfillstyle(SOLID_FILL, COLOR(80, 85, 105)); // Highlight móng
    bar(x - 35, y - 8, x - 30, y - 4);
    // Khe móng rõ ràng
    setfillstyle(SOLID_FILL, outlineColor);
    bar(x - 31, y - 9, x - 29, y);
    
    // Viền chân trước
    setfillstyle(SOLID_FILL, outlineColor);
    bar(x - 38, y - 26, x - 36, y); 
    bar(x - 36, y - 2, x - 24, y);  
    bar(x - 24, y - 26, x - 22, y); 

    // Chân sau gần - Vẽ body trước
    setfillstyle(SOLID_FILL, bodyColor);
    bar(x + 14, y - 26, x + 26, y - 2);
    
    // Cơ bắp chân
    setfillstyle(SOLID_FILL, highlightColor);
    bar(x + 15, y - 26, x + 20, y - 10);
    setfillstyle(SOLID_FILL, lightShadow);
    bar(x + 20, y - 26, x + 24, y - 10);
    
    // Bóng chân
    setfillstyle(SOLID_FILL, midShadow);
    bar(x + 20, y - 24, x + 26, y - 8);
    setfillstyle(SOLID_FILL, shadowColor);
    bar(x + 22, y - 20, x + 26, y - 10);
    
    // Khớp gối
    setfillstyle(SOLID_FILL, outlineColor);
    bar(x + 14, y - 18, x + 26, y - 16);
    setfillstyle(SOLID_FILL, midShadow);
    bar(x + 15, y - 17, x + 25, y - 16);
    
    // Móng chân
    setfillstyle(SOLID_FILL, nailColor);
    bar(x + 14, y - 8, x + 26, y - 2);
    setfillstyle(SOLID_FILL, COLOR(80, 85, 105));
    bar(x + 15, y - 8, x + 20, y - 4);
    // Khe móng
    setfillstyle(SOLID_FILL, outlineColor);
    bar(x + 19, y - 9, x + 21, y);
    
    // Viền chân sau 
    setfillstyle(SOLID_FILL, outlineColor);
    bar(x + 12, y - 26, x + 14, y); 
    bar(x + 14, y - 2, x + 26, y);  
    bar(x + 26, y - 26, x + 28, y); 

    // đường gân da
    // Gân chia 2 tầng thân cong theo lưng
    setcolor(outlineColor);
    setlinestyle(SOLID_LINE, 0, 3);
    // Đường gân cong nhẹ từ vai xuống mông
    line(x + 6, y - 56, x + 6, y - 18);  // Phần thẳng dưới
    line(x + 4, y - 60, x + 6, y - 56);  // Cong vào chỗ nối
    line(x + 2, y - 64, x + 4, y - 60);  // Cong lên vai
    setlinestyle(SOLID_LINE, 0, 1);
    
    // Shadow cho gân (cũng cong)
    setcolor(shadowColor);
    line(x + 5, y - 56, x + 5, y - 20);
    line(x + 3, y - 60, x + 5, y - 56);
    line(x + 1, y - 62, x + 3, y - 60);
    line(x + 7, y - 56, x + 7, y - 20);
    line(x + 5, y - 60, x + 7, y - 56);
    line(x + 3, y - 62, x + 5, y - 60);
}

#endif 
