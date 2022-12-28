#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (){
    int m, n, i, j, k, food, move[2], eaten = 0, len = 1, flag = 0;
    char input;
    time_t t;
    //rand seed'ini değiştir
    srand((unsigned) time(&t));
    //oyun alanını oluştur
    printf("Oyun alanının boyutunu giriniz: ");
    scanf("%d%d", &m, &n);
    char game[m+2][n+2];
    for (i=0; i<(m+2); i++){
        for (j=0; j<(n+2); j++){
            if ((i>0 && i<(m+1)) && (j>0) & j<(n+1)){
                game[i][j] = ' ';
            }else {
                game[i][j] = '#';
            }
        }
    }
    //yemek sayısını al
    printf("Yemek sayısını giriniz: ");
    scanf("%d", &food);
    //yemekleri oluştururken sonsuz döngüyü engellemek için kontrol
    while (food >= (m*n) || food < 0){
        printf("Geçersiz girdi. Lütfen pozitif ve oyun alanına\nsığacak kadar yemek giriniz: ");
        scanf(" %d", &food);
    }
    int loc[food+1][2];
    //yılanı rastgele bir yere koy ve konumunu loc'a kaydet
    i = (rand()%m)+1;
    j = (rand()%n)+1;
    game [i][j] = '1';
    loc[0][0] = i;
    loc[0][1] = j;
    //yemekleri rastgele dağıt
    for (k=0; k<food; k++){
        i = (rand()%m)+1;
        j = (rand()%n)+1;
        if (game[i][j] == ' '){
            game[i][j] = '0';
        }else{
            k--;
        }
    }
    k = 0;
    while (food > 0 && flag == 0){
        //game'i ekrana yaz
        for (i=0; i<(m+2); i++){
            for (j=0; j<(n+2); j++){
                //renkler
                switch (game[i][j]){
                    case '#': printf("\033[1;31m"); break; //duvarlar: kırmızı
                    case '0': printf("\033[0;33m"); break; //yemekler: sarı
                    default: printf("\033[0;36m");         //yılan:    camgöbeği
                }
                if (game[i][j] > 83){
                    printf("%c ", game[i][j]-19);
                }else if (game[i][j] > '9'){
                    printf("%c ", game[i][j]+39);
                }else {
                    printf("%c ", game[i][j]);
                }
            }
            printf("\n");
        }
        printf("\033[0mYapılan hamle sayısı: %d\n", k);
        //hareket sistemi
        printf("Hamle (U/D/L/R): ");
        scanf(" %c", &input);
        printf("\n");
        //move'u temizle
        move[0] = 0;
        move[1] = 0;
        //input'u vektöre çevir'
        switch (input){
            case 'u': case 'U': move[0] = -1; break;
            case 'd': case 'D': move[0] =  1; break;
            case 'l': case 'L': move[1] = -1; break;
            case 'r': case 'R': move[1] =  1; break;
            default:
                printf("Hatalı girdi.\n");
                flag++;
        }
        if (flag == 0){
            k++;
            game[loc[len-1][0]][loc[len-1][1]] = ' ';
            //önceki hamlede yemek yendiyse yılanı büyüt
            if (eaten == 1){
                eaten--;
                len++;
            }else {
                game[loc[0][0]][loc[0][1]] = ' ';
            }
            for (i=len-1; i>0; i--){
                loc[i][0] = loc[i-1][0];
                loc[i][1] = loc[i-1][1];
            }
            loc[0][0] += move[0];
            loc[0][1] += move[1];
            //yemek kontrolü
            if (game[loc[0][0]][loc[0][1]] == '0'){
                eaten = 1;
                food--;
            }
            //duvar kontrolü
            if (game[loc[0][0]][loc[0][1]] == '#'){
                printf("Duvara çarptınız.\n");
                flag--;
            //kendine çarpma kontrolü
            }else if (game[loc[0][0]][loc[0][1]] > '0'){
                printf("Yılanı kendine çarptırdınız.\n");
                flag--;
            }
            //yılanın ilerlet
            for (i=0; i<len; i++){
                game[loc[i][0]][loc[i][1]] = '1'+i;
            }
        }else{
            flag = 0;
        }
    }
    if (food == 0){
        printf("Tebrikler, hamle sayınız: %d\n", k);
    }else {
        printf("Hamle sayınız:      %d\nYılanın büyüklüğü:  %d\nKalan yemek sayısı: %d\n", k, len, food);
    }
    return 0;
}
