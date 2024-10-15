#include<stdio.h>
#include <time.h>
#include<string.h>
#include <windows.h>
#include <conio.h>

struct gym{
	char pembeli[255];
	long long harga;
	long long total_harga;
	char barang[255];
	char jenis[255];
	long int tanggal;
	int jumlah_barang;
	bool available;
};

struct temp_data_info { 
	char pembeli[255];
	long long harga;
	long long total_harga;
	char barang[255];
	char jenis[255];
	long int tanggal;
	int jumlah_barang;
	bool available;
};

temp_data_info temps[1000];
gym data[500];
int tempCount = 0;
int total_data=0;
FILE *sales;

void dataPenjualan();
void cetakLaporan();
void updateLaporan();
void carilaporan();
void dapen();
void menu();
void login();
void loading();
void jam();
void readData();
void updateMenuChoice (int res);

int main(){  
    system ("color A"); 
    loading();
    login();
    readData();
	menu();
	fclose(sales);
 	return 0;
}

void readData(){
	FILE *sales;
	sales=fopen("sales.txt","r");
	while(fscanf(sales,"%ld-%[^-]-%[^-]-%[^-]-%d-%d-%d\r\n",&data[total_data].tanggal,data[total_data].pembeli,data[total_data].jenis,
	data[total_data].barang,&data[total_data].jumlah_barang,&data[total_data].harga,&data[total_data].total_harga)!=EOF){
        total_data++;
    }
}

void gotoxy(int x,int y){
	COORD coord = {0,0};
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void depan(){
	system ("cls");
	printf("\t==============================================================\t\n");
	printf("\t\t\t\tGYM COBOY JUNIOR !!!\t\t\t\n");
	printf("\t\t\t----------------------------------\n");
	jam();
	printf("\t==============================================================\t\n");
	printf("\n");
	printf("1. Pendataan Penjualan Alat Gym\n");
	printf("2. Pencetakan Laporan penjualan Alat Gym (Sort Menurut Tanggal Transaksi)\n");
	printf("3. Pencetakan Laporan penjualan Alat Gym (Sort Menurut Jumlah Terjual)\n");
	printf("4. Cari Laporan Penjualan\n");
	printf("5. Update Laporan Penjualan\n");
	printf("6. Exit\n");
	printf("");
}

void swap(gym* xp, gym* yp)
{
    gym temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void cetakLaporanTanggal(){
	printf("\t===============================================================\t\n");
	printf("\t\t CETAK LAPORAN PENJUALAN GYM SORT TANGGAL TRANSAKSI  \t\t\t\n");
	printf("\t\t\t----------------------------\n");
	jam();
	printf("\t===============================================================\t\n");
	printf("\n\n");
	printf("(%d) Available Data\n",total_data);
	if(!total_data){
			printf("\n");
            printf("\n\n\n\t\t\t\t- Belum Ada Data - \n");
		return;
	}
	int i, j;
	char min_idx;
    
    for (i = 0; i < total_data-1; i++){
        min_idx = i;
        for (j = i + 1; j < total_data; j++)
            if (data[j].tanggal < data[min_idx].tanggal)
                min_idx = j; 
                
        swap(&data[min_idx], &data[i]);
    }
	char *table[] ={" Tanggal Transaksi (YYYYMMDD)", "    Nama Pembeli    ", "    Jenis Barang    ", "    Nama  Barang    ", "   Jumlah  Barang   ", "    Harga Barang    ", "Total Pembayaran  "};
	printf("%*s | %*s | %*s | %*s | %*s |  %*s  | %*s\n",-3, table[0],-3,table[1],-3,table[2],-3,table[3],-3,table[4],-3,table[5],-3,table[6]);

	for(int i = 0; i < total_data; i++){
		gym temp = data[i];
			printf(" %06ld %21c | %-20s | %-20s | %-20s | %-20d | Rp%-20lld | Rp%-20lld\n",temp.tanggal,' ', temp.pembeli, temp.jenis, temp.barang, temp.jumlah_barang, temp.harga, temp.total_harga);
 	}

}

void cetakLaporanJumlah(){
	printf("\t================================================================\t\n");
	printf("\t  CETAK LAPORAN PENJUALAN GYM COBOY JUNIOR SORT JUMLAH TERJUAL  \t\t\t\n");
	printf("\t\t\t----------------------------\n");
	jam();
	puts("\t================================================================\t\n");
	printf("\n\n");
	printf("(%d) Available Data\n",total_data);
	if(!total_data){
			printf("\n");
            printf("\n\n\n\t\t\t\t- Belum Ada Data - \n");	
		return;
	}
	int i, j, max_idx;
	
    for (i = 0; i < total_data; i++) {
        max_idx = i;
        for (j = i + 1; j < total_data; j++)
            if (data[j].jumlah_barang > data[max_idx].jumlah_barang)
                max_idx = j; 

        swap(&data[max_idx], &data[i]);
    }
	char *table[] ={" Tanggal Transaksi (YYYYMMDD)", "    Nama Pembeli    ", "    Jenis Barang    ", "    Nama  Barang    ", "   Jumlah  Barang   ", "    Harga Barang    ", "Total Pembayaran  "};
	printf("%*s | %*s | %*s | %*s | %*s |  %*s  | %*s\n",-3, table[0],-3,table[1],-3,table[2],-3,table[3],-3,table[4],-3,table[5],-3,table[6]);

	for(int i = 0; i < total_data; i++){
		gym temp = data[i];
			printf(" %06ld %21c | %-20s | %-20s | %-20s | %-20d | Rp%-20lld | Rp%-20lld\n",temp.tanggal,' ', temp.pembeli, temp.jenis, temp.barang, temp.jumlah_barang, temp.harga, temp.total_harga);
 	}

}

void loading(){
	printf("\n\n\n\n\n\n\n");
    printf("\n\n\n\t\t\t\t\t Loading......");
    printf("\n\n");
    printf( "\t\t\t\t\t");
    for (int i=0; i<= 35; i++)
    {
        printf("%c", 178);
        Sleep(100);
    }
    printf ("\n\n\t\t\t\t\t 'PRESS ENTER TO LOGIN'");
    system ("pause>0");
    system ("cls");
}

void login(){
    	char username[10], password[8];
    	int ulang = 0;
	    for(int j=0; j<3; j++){
	    printf("\t\t\t\t\t________________________________\n");
        printf("\n");
        printf("\t\t\t\t        ======== LOGIN KARYAWAN ========\n");
        printf("\t\t\t\t\t________________________________\n");
        printf("\n");
        printf("\n");
        printf("Username: ");
        scanf ( "%s", &username);
        printf("\n");
        printf("Password: ");
        fflush(stdin);
            char ch;
        int i=0;
        int x=10;
        int y=8;
        while((ch = (char) _getch()) != '\r'){
    	if (ch == 8){
    		password[i] = '\0';
    		gotoxy(x-1,y);	
    		printf(" ");
    		x--;
    		i--;	
    		gotoxy(x,y);
		}
	
		else{
			password[i]=ch;
			gotoxy(x,y);
			printf("*");
			x++;
			i++;
		}
	}
        if ((strcmp(username,"CJR")==0)&&(strcmp(password,"EAEAEA")==0)) {
        	printf("\n\n\n\n\n\n\t\t\t\t\t\t BERHASIL...!!");
        	Sleep(1400);
        	break;
        } else {
        	ulang++;
        	if(ulang != 3){
            printf("\n\nPassword atau Username yang Anda Masukan Salah.");
            Sleep(500);
             system ("pause>0");
        }
            else if(ulang == 3){
            	printf("\n\nAnda Terlalu Banyak Mencoba, Silahkan Buka Progam Ini Kembali.\n");
            	Sleep(1400);
            	exit(0);
			}
        }
        system("cls");
    }
}

void jam(){///UNTUK MENAMPILKAN WAKTU 
    struct tm *waktu;
    time_t Timeval;
    Timeval = time(0);
    waktu = localtime(&Timeval); 
    printf("\t\t\t  %s", asctime(waktu));
}


void dataPenjualan(){
	puts("\t==============================================================\t\n");
	puts("\t\t     PENDATAAN PENJUALAN GYM COBOY JUNIOR  \t\t\t\n");
	puts("\t\t\t----------------------------\n");
	jam();
	puts("\t==============================================================\t\n");
	printf("Tanggal Transaksi (YYYYMMDD): ");
    scanf("%ld",&data[total_data].tanggal); 
    printf("Nama Pembeli : ");getchar();
    scanf("%[^\n]", data[total_data].pembeli); 
    printf("Jenis Barang : ");getchar();
    scanf("%[^\n]", data[total_data].jenis);
    printf("Nama Barang : ");getchar();
    scanf("%[^\n]", data[total_data].barang); 
    printf("Jumlah Barang : ");getchar();
    scanf("%d", &data[total_data].jumlah_barang);
    printf("Harga Barang: Rp ");getchar();
    scanf("%lld", &data[total_data].harga);
    data[total_data].total_harga=data[total_data].jumlah_barang*data[total_data].harga;
    printf("Total Pembayaran: Rp %lld",data[total_data].total_harga);
    data[total_data].available = true; 
    FILE *output = fopen ("sales.txt","a+");
  	if(fprintf(output,"%d-%s-%s-%s-%d-%lld-%lld\n",data[total_data].tanggal, data[total_data].pembeli, data[total_data].jenis, data[total_data].barang, data[total_data].jumlah_barang,data[total_data].harga,data[total_data].total_harga)){
		  printf ("\n\n\t\t\t\t\t - DATA BERHASIL DI INPUT -");;
		  Sleep(4000);
	  }
	fclose(output);
	total_data++;	
}

void carilaporan(){
	int start = 0;
	int end = total_data-1;
	char c[200];
	printf("\t==============================================================\t\n");
	printf("\t\t     CARI LAPORAN PENJUALAN GYM COBOY JUNIOR  \t\t\t\n");
	printf("\t\t\t----------------------------\n");
	jam();
	printf("\t==============================================================\t\n");
	printf("Masukkan Nama Pembeli Ingin Dicari (Pastikan Identik): ");
	scanf("%[^\n]", c);
	int res = -1;
	for(; start <=  end; ){
		int mid = (start+end) / 2;
		int temp = strcmp(c,data[mid].pembeli);
		if(temp == 0){
			res = mid;
			break;
		} else if(temp < 0){ 
			start = mid+1;
		} else {
			end = mid-1;
		}
	}
	if(res == -1) printf("\n\n - Data %s Tidak Ditemukan Di Daftar -\n",c);
	else {	
	gym temp = data[res];
	printf("\n\n\t - Data Di Temukan -\n\n\n");
	char *table[] ={"Tanggal Transaksi (YYYYMMDD)", "    Nama Pembeli    ", "    Jenis Barang    ", "    Nama  Barang    ", "   Jumlah  Barang   ", "     Harga Barang     ", "  Total Pembayaran  "};
    printf("%*s | %*s | %*s | %*s | %*s | %*s | %*s\n",-3, table[0],-3,table[1],-3,table[2],-3,table[3],-3,table[4],-3,table[5],-3,table[6]);
			printf(" %06ld %18c | %-20s | %-20s | %-20s | %-20d | Rp%-20lld | Rp%-20lld\n",temp.tanggal,' ', temp.pembeli, temp.jenis, temp.barang, temp.jumlah_barang, temp.harga, temp.total_harga);
		     system ("pause>0");
			}
			printf ("\n\n\t\t\t\t\t - KEMBALI KE MENU UTAMA -");;
			Sleep(4000);
			return;
		}
		
void updateLaporan() {
	int start = 0;
	int end = total_data-1;
	char c[200];
	printf("\t==============================================================\t\n");
	printf("\t\t    UPDATE LAPORAN GYM COBOY JUNIOR  \t\t\t\n");
	printf("\t\t\t----------------------------\n");
	jam();
	printf("\t==============================================================\t\n");
	printf("Masukkan Nama Pembeli yang Ingin Di Update (Pastikan Identik): ");
	scanf("%[^\n]", c);
	int res = -1;
	for(; start <=  end; ){
		int mid = (start+end) / 2;
		int temp = strcmp(c,data[mid].pembeli);
		if(temp == 0){
			res = mid;
			break;
		} else if(temp < 0){ 
			start = mid+1;
		} else {
			end = mid-1;
		}
	}
	if(res == -1) printf("\n\n - Data %s Tidak Ditemukan Di Daftar -\n",c);
	
	else{	
	gym temp = data[res];
	printf("\n\n\t - Data Di Temukan -\n\n\n");
	char *table[] ={"Tanggal Transaksi (YYMMDD)", "    Nama Pembeli    ", "    Jenis Barang    ", "    Nama  Barang    ", "   Jumlah  Barang   ", "     Harga Barang     ", "  Total Pembayaran  "};
    printf("%*s | %*s | %*s | %*s | %*s | %*s | %*s\n",-3, table[0],-3,table[1],-3,table[2],-3,table[3],-3,table[4],-3,table[5],-3,table[6]);
	printf("%06ld %19c | %-20s | %-20s | %-20s | %-20d | Rp%-20lld | Rp%-20lld\n",temp.tanggal,' ', temp.pembeli, temp.jenis, temp.barang, temp.jumlah_barang, temp.harga, temp.total_harga);
					updateMenuChoice(res);
			}
			printf ("\n\n\t\t\t\t\t - DATA BERHASIL DI UBAH -");;
			Sleep(4000);
			return;
		}
		
		    

void showUpdateChoices() {
	printf("\n\nData Mana Yang Ingin Di Update?\n");
	printf("1.Tanggal\n2.Nama Pembeli\n3.Jenis Barang\n4.Nama Barang\n5.Jumlah Barang\n6.Harga Barang\n7.Cancel");
	
}

void updateMenuChoice (int i) {
	  bool choosingUpdate = true;
	  
  while (choosingUpdate){
    showUpdateChoices();
    int updateChoice;

    do{
      printf(">> ");
      scanf("%d", &updateChoice);
      getchar();
    }
    while (updateChoice < 1 || updateChoice > 7);
	
	printf("Input Update Information");
	printf(">> ");

    if (updateChoice == 1){
    	scanf("%ld",&temps[tempCount].tanggal); getchar();
    	data[i].tanggal = temps[tempCount].tanggal;
    	tempCount++;
    	return;
    }
    else if (updateChoice == 2){
		scanf("%[^\n]", temps[tempCount].pembeli); getchar();
    	strcpy(data[i].pembeli, temps[tempCount].pembeli);
    	tempCount++;
    	return;
    }
    else if (updateChoice == 3){
		scanf("%[^\n]", temps[tempCount].jenis); getchar();
    	strcpy(data[i].jenis, temps[tempCount].jenis);
    	tempCount++;
    	return;
    }
    else if (updateChoice == 4){
		scanf("%[^\n]", temps[tempCount].barang); getchar();
    	strcpy(data[i].barang, temps[tempCount].barang);
    	tempCount++;
    	return;
    }
    else if (updateChoice == 5){
		scanf("%d", &temps[tempCount].jumlah_barang); getchar();
    	data[i].jumlah_barang = temps[tempCount].jumlah_barang;
    	data[i].total_harga=data[tempCount].jumlah_barang*data[tempCount].harga;
    	tempCount++;
    	return;
    }
    else if (updateChoice == 6){
    	scanf("%lld", &temps[tempCount].harga); getchar();
    	data[i].harga = temps[tempCount].harga;
    	data[i].total_harga=data[tempCount].jumlah_barang*data[tempCount].harga;
    	tempCount++;
    	return;
    }
    else if( updateChoice == 7){
    	printf("\n\n\t Kembali ke Menu Utama\n");
    	return;
	}
    
  }

}

void menu(){
	bool onApp = true;
    while(onApp) {
        depan();
        int choice = -1;
        do {
            printf(">> ");
            scanf("%d", &choice); getchar();
            system("cls");
        } 
		while(choice < 1 || choice > 6);
         	if(choice == 1) {
               dataPenjualan();
    		}else if(choice ==2){
    			cetakLaporanTanggal();
    			system ("pause>0");
    		}else if(choice ==3){
    			cetakLaporanJumlah();
    			system ("pause>0");
    		}else if(choice ==4){
    			carilaporan();
    		}else if(choice ==5){
    			updateLaporan();
			}else if(choice == 6) {
					system ("cls");
				printf("\t==============================================================\t\n");
				printf("\t\t\t\tGYM COBOY JUNIOR !!!\t\t\t\n");
				printf("\t\t\t----------------------------------\n");
				jam();
				printf("\t==============================================================\t\n");
				printf("\n");
                printf("\n\n\n\t\t\t\t   BYE BYE ...");
                printf("\n\t\t\t\tSELAMAT BEKERJA");
                printf("\n\n\n\n");
                printf( "\t\t\t\t\t");
            	onApp = false;
        }
	}
}
