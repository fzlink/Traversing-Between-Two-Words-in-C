#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 2500 //Dizi buyuklugu
#define charCol 6 // String genisli


typedef struct queue{
    int queue[N]; // Kuyruk yapisinin tutuldugu dizi
    int front; // Kuyrugun bas elemaninin indisi
    int rear; // Kuyrugun arka elemaninin indisi
}QUEUE;

void enqueue(QUEUE *q,int val){
    q->rear++;
    q->queue[q->rear] = val;
}
int dequeue(QUEUE *q){
    if(!isEmpty(q)){
        q->front++;
        return q->queue[q->front-1];
    }

    else
        printf("Kuyruk Bos,Eleman Cikartilamaz.");
}

int isEmpty(QUEUE*q){
    if(q->front>q->rear)
        return 1;
    return 0;
}



void fillAdjacencyMatrix(char **A,char **words,int totalWords){
    int i; // Dongu degiskeni
    int j; // Dongu degiskeni
    int k; // Dongu degiskeni
    int dif; // Kelimeler arasi harf farki sayisi
    for(i=0;i<totalWords;i++){
        for(j=0;j<totalWords;j++){
                dif=k=0;
                while( (k<5) && (dif<2) ){
                    if(words[i][k] != words[j][k])
                        dif++;
                    k++;
                }
                if(dif==1)
                    A[i][j] = 1;
                else
                    A[i][j] = 0;
        }
    }
    printf("Matrisin 10 x 10 bolumu\nToplam Kelime Sayisi: %d\n",totalWords);
    for(i=0;i<10;i++){
        for(j=0;j<10;j++){
            printf(" %d ",A[i][j]);
        }
        printf("\n");
    }
}

int *findConnection(char **A,char **words,char *word1,char *word2,int totalWords,char returnCon){
    int i=0; // Dongu degiskeni
    int j=-1; // Birinci kelimenin indisi
    int k=-1; // Ikinci kelimenin indisi
    int *index; // Bulunan kelimelerin indislerinin tutuldugu dizi
    while( (i<=totalWords) && ( (j==-1) || (k==-1)) ){
        if(strcmp(words[i],word1)==0){
            j=i;
        }
        if(strcmp(words[i],word2)==0){
            k=i;
        }
        i++;
    }
    if(i>totalWords){
        if((j==-1) && (k==-1))
            printf("Aradiginiz 1.kelime ve 2. kelime Matriste bulunamadi.\n");
        else if(j==-1)
            printf("Aradiginiz 1. kelime Matriste bulunamadi.\n");
        else if(k==-1)
            printf("Aradiginiz 2. kelime Matriste bulunamadi.\n");
        return NULL;
    }
    else{
            if(returnCon){
                index = (int *) malloc(sizeof(int)*2);
                index[0] = j;
                index[1] = k;
                return index;
            }

        printf("1.Kelimenin indisi: %d\n",j);
        printf("2.Kelimenin indisi: %d\n",k);
        if(A[j][k]==1)
            printf("Baglanti var.\n");
        else
            printf("Baglanti yok.\n");
    }
}



void printShortest(int parent[],int word1,int word2,char **words){
    int i=word2; //word1 e gelene kadar parent duðumune gidilen indis
    int j=0; // Dongu degiskeni
    int reverse[N]; // Gecislerin tutuldugu dizi
    int step=-1; // Gecis sayisi
    while(i != word1){
        reverse[j++] = i;
        i = parent[i];
    }
    reverse[j] = word1;
    printf("\nDonusum : \n");
    while(j>=0){
    	step++;
        if(j==0)
             printf(" %s",words[reverse[j--]]);
        else
            printf(" %s -> ",words[reverse[j--]]);
    }
    printf("\n%d harf gecisi\n",step);

}

void bfs(char **A,char **words,int word1,int word2,int totalWords){
    int visited[N]; // Ziyaret edilen dugumlerin dizisi
    int parent[N]; // Duðumlerin parentlarinin tutuldugu dizi
    int i; // Dongu degiskeni
    int j; // Dongu degiskeni
    int val; // Kuyruktan push pop edilen dugumun tutuldugu degisken
    int stop; // Durma flagi

    QUEUE *q;
    q= malloc(sizeof(QUEUE));
    q->front=0;
    q->rear=-1;

    for(i=0;i<N;i++){
        visited[i]=0;
        parent[i] = 0;
    }
    visited[word1] = 1;
    enqueue(q,word1);
    stop = 0;
    while(!isEmpty(q) && !stop){

        /*printf("%d. adimda kuyruk: ",q->front+1);           // Adim adim Kuyrugun icerigini gormek icin bu satirlarin commentlerini siliniz.
        for(i=q->front;i<=q->rear;i++){
            printf("%s-",words[q->queue[i]]);
        }
        printf("\n");*/                                       //

        val = dequeue(q);
        if(val == word2){
            stop =1;
            printShortest(parent,word1,word2,words);

        }
        else{
            for(i=0;i<totalWords;i++){
                if( (A[val][i]==1) && (visited[i]==0) ){
                    enqueue(q,i);
                    parent[i] = val;
                    visited[i] = 1;
                    //printf("%s ",words[i]);
                }

            }
        }

    }
    if(!stop){
        printf("\n Iki Kelime Arasinda Donusum Yoktur.");
    }
    else{
        printf("\nDonusum Basarili.");
    }
}

int main()
{
    FILE *file; //Dosya pointeri
    char word[10]; // Dosyadan okunan bir kelimenin tutuldugu string
    char **words; // Dosyadaki tum kelimelerin tutuldugu string dizisi
    char word1[7]; // Kullanicidan  alinan birinci kelime
    char word2[7]; // Kullanicidan  alinan ikinci kelime
    char **adjMatrix; // Adjacency Matrix
    char secim; // Menu secimi degiskeni
    char alreadyRead=0; // Dosyanin okunup okunmadigini tutan degisken
    int i; // Dongu degiskeni
    int j; // Dongu degiskeni
    int totalWords=0; // Toplam kelime sayisini tutan degisken
    int stop=0; // Durma flagi
    int *index; // Find Connection'dan donen indislerin tutulacagi dizi
    while(1){
        system("cls");
        printf("Graf Sistemine Hosgeldiniz.\nIstediginiz islemin numarasini giriniz.\n\n"
            "0- Dosyayi oku ve Adjacency Matris olustur('kelime.txt')\n"
            "1- Baglanti Bilgisi (Iki kelime arasinda tek harf degisimi olup olmadigini bulur.)\n"
            "2- Donusum Bul\n"
            "3- Cikis");
            secim = getch();
            switch(secim){
                case '0':
                    system("cls");
                    if(alreadyRead){
                        printf("Dosya zaten okundu.\n");
                    }
                    else{

                    file = fopen("kelime.txt","r");
                    if(file==NULL){
                        printf("ERROR Opening File...");
                        exit(1);
                    }
                    adjMatrix = (char**)malloc(N * sizeof(char *));
                    for(i=0;i<N;i++){
                        adjMatrix[i] = (char *)malloc(N*sizeof(char));
                    }

                    words = (char **) malloc(N*sizeof(char*));
                    for(j=0;j<N;j++){
                        words[j] = (char *)malloc(charCol*sizeof(char));
                    }
                    i=j=0;
                    while(!feof(file)){
                        totalWords++;
                        fscanf(file,"%s",word);
                        strcpy(words[i],word);
                        i++;
                    }

                    fillAdjacencyMatrix(adjMatrix,words,totalWords);
                    printf("Matris Basariyla Olusturuldu.\n");
                    alreadyRead=1;
                    }

                    break;

                case '1':
                    system("cls");
                    if(alreadyRead){
                        printf("Baglanti aradiginiz 1.kelimeyi giriniz.");
                        scanf("%s",word1);
                        printf("Baglanti aradiginiz 2.kelimeyi giriniz.");
                        scanf("%s",word2);
                        findConnection(adjMatrix,words,word1,word2,totalWords,0);
                    }
                    else{
                        printf("Once dosyayi okumaniz gerekmekte.\n");
                    }

                    break;

                case '2':
                    system("cls");
                    if(alreadyRead){
                        printf("Donusum istediginiz 1.kelimeyi giriniz.");
                        scanf("%s",word1);
                        printf("Donusum istediginiz 2.kelimeyi giriniz.");
                        scanf("%s",word2);
                        index = findConnection(adjMatrix,words,word1,word2,totalWords,1);
                        if(index!=NULL){
                        printf("Indis 1: %d  Indis 2: %d\n\n",index[0],index[1]);
                        bfs(adjMatrix,words,index[0],index[1],totalWords);
                        }
                    }
                    else{
                        printf("Once dosyayi okumaniz gerekmekte.\n");
                    }
                    break;

                case '3':
                    system("cls");
                    exit(0);
                    break;
                default:
                     system("cls");
                     printf("Lutfen yazili islemlerden seciniz.\n");
                     break;
            }
            printf("\nMenuye donmek icin 'f' tusuna basiniz");
            stop = 0;
            while(!stop){
                if(getch() == 'f')
                    stop=1;
            }
    }
    return 0;
}
