#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
    printf("\n--- KIEM TRA THUAT TOAN COPY-ON-WRITE ---\n");
    
    uint64 ram_ban_dau = freemem();
    printf("RAM trong ban dau: %ld bytes\n", ram_ban_dau);

    // Xin 4MB RAM (1000 trang)
    int n = 1000;
    char *arr[1000]; // Khai báo cứng 1000 để an toàn với mọi phiên bản gcc
    for(int i = 0; i < n; i++) {
        arr[i] = malloc(4096);
        arr[i][0] = 'X'; // Ep ghi de he he thong cap RAM that
    }

    uint64 ram_sau_khi_xin = freemem();
    printf("RAM trong sau khi xin 4MB: %ld bytes\n", ram_sau_khi_xin);
    printf("-> Da tieu hao: %ld bytes\n\n", ram_ban_dau - ram_sau_khi_xin);

    printf("Bat dau fork()...\n");
    
    // BẮT ĐẦU BẤM GIỜ
    int thoi_gian_bat_dau = uptime();
    
    int pid = fork();
    
    // KẾT THÚC BẤM GIỜ LỆNH FORK
    int thoi_gian_ket_thuc = uptime();

    if(pid == 0) {
        // TIẾN TRÌNH CON
        uint64 ram_cua_con = freemem();
        printf("\n[Tien trinh CON]\n");
        printf(" - RAM trong hien tai: %ld bytes\n", ram_cua_con);
        exit(0);
    } else {
        // TIẾN TRÌNH CHA
        wait(0);
        printf("[Tien trinh CHA]\n");
        printf(" - Thoi gian de thuc thi lenh fork(): %d ticks\n", thoi_gian_ket_thuc - thoi_gian_bat_dau);
        printf("Hoan tat!\n");
    }

    exit(0);
}
