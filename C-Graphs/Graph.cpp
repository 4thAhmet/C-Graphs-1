// !! matris.txt dosyasının en alt satırı boş olacak hata almamak için !!
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define satir 5
#define sutun 5 


struct node{ // Graf 
    int label;
    int counter;
    struct node *komsular[100];
    struct maliyet *maliyet[100];
    struct node *next;
};

struct maliyet // Maliyetler
{
    int maliyet;
    struct node* src;
    struct node* dest;
    struct maliyet* next;
};

// ----- Global Degiskenler ------ //
int matris[5][5];
FILE *fp;
struct node *bas=NULL;
struct node *son=NULL;
struct node *gecici;
struct node *onemli;
struct maliyet *maliyetbas;
struct maliyet *maliyetson;
// --------- -------------------- //


struct maliyet* maliyetekle(struct node* src,struct node* dest,int w) // 
{
    struct maliyet* current=(struct maliyet*)malloc(sizeof(struct maliyet));
    current->src=src;
    current->dest=dest;
    current->maliyet=w;
    current->next=NULL;
    if(maliyetbas==NULL)
    {
        maliyetbas=current;
        maliyetson=current;
    }
    else{
        maliyetson->next=current;
        maliyetson=current;
    }
    return current;
}

void addfrommatrisarray() //dugum ekle
{
    for (int i = 0; i < satir; i++)
    {

        struct node* current=(struct node*)malloc(sizeof(struct node));
        current->label=i;
        current->counter=0;
        current->next=NULL;
        if(bas==NULL)
        {
            bas=current;
            son=current;
        }
        else{
            son->next=current;
            son=current;
        }     
    }
    
}

void printNodes() // Dugumler listele
{
    gecici=bas;
    while (gecici->next!=NULL)
    {
        printf("%d ",gecici->label);
        gecici=gecici->next;
    }
    printf("%d",gecici->label);
}

int searchNode(int v) // 
{
    
    gecici=bas;
    while (gecici->label!=v)
    {
        if(gecici->next==NULL) return -1;
        gecici=gecici->next;
    }
    onemli=gecici;   
    return 1;
}

void komsuEkle(int src,int dest,int W) //komsulari ekle
{
    struct node* source;
    struct maliyet* maliyet;
    if(searchNode(src)==-1){ printf("Hatali Dugum"); return;}
    searchNode(src);
    source=onemli;
    struct node* destination;
    if(searchNode(dest)==-1){ printf("Hatali Dugum"); return;}
    searchNode(dest);
    destination=onemli;
    source->komsular[source->counter]=destination;
    struct maliyet* gelen;
    gelen=maliyetekle(source,destination,W);
    source->maliyet[source->counter]=gelen;
    source->counter++;
}

void komsuyazdir(int hedef) // komsu listele
{
    if(searchNode(hedef)==-1){ printf("Hatali Dugum"); return;}
    searchNode(hedef);
    for (int i = 0; i < onemli->counter; i++)
    {
        printf(" %d -> %d Maliyet: %d \n",hedef,onemli->komsular[i]->label,onemli->maliyet[i]->maliyet);
    }
}

void fromtxttoarray() // metin belgesinden matrise aktar
{
    fp=fopen("matris.txt","r");
    char read[11];
    int sayac=0;
    for (int i = 0; i < satir; i++)
    {
        fgets(read,11,fp);
        for (int j = 0; j < 11; j++)
        {
            if(read[j]!=' ' && read[j]!='\n')
            {
                matris[i][sayac]=read[j]-'0';
                sayac++;
            }
            else{
                if (read[j]=='\n')
                {   
                    sayac=0;
                    break;
                }
            }
                
        }
    }   
    fclose(fp);
}

void PrintMatris() // Matrisi listele
{
    for (int i = 0; i < satir; i++)
    {
        printf("\n");
        for (int j = 0; j < sutun; j++)
        {
            printf("%d ",matris[i][j]);
        }
        
    }   
}

int CalculateEdgeFull()
{
    int sumEdge=0;
    for (int i = 0; i < satir; i++)
    {
        if (searchNode(i)==-1) return -1;
        searchNode(i);
        for (int j = 0; j < onemli->counter; j++)
        {
            sumEdge+=onemli->maliyet[j]->maliyet;
        }  
    }
    return sumEdge;
}




void matrisCoz()  // 
{
    int jSayac=0;
    for (int k = 0; k < satir; k++)
    {
        for (int j = 0; j < sutun; j++)
        {
            
            if(matris[k][j]!=0)
            {
                jSayac=matris[k][j];
                komsuEkle(k,j,jSayac);
            }
        }
        
    }
    
}

void CalculateIO(int x)  //
{
    int girissay=0;
    int cikissay=0;
     if(searchNode(x)!=-1)
     {
         searchNode(x);
         gecici=onemli;
         cikissay=gecici->counter;
         for (int i = 0; i < satir; i++)
         {
             if(i!=x)
             {
                 
                 searchNode(i);
                 for (int j = 0; j < onemli->counter; j++)
                 {
                     if(onemli->komsular[j]->label==x) {girissay++; break; }
                 }
             }
         }
         printf("\n Secilen Dugumun Giris Derecesi: %d Cikis Derecesi: %d",girissay,cikissay);
         girissay=0;
         cikissay=0;
     }
     else printf("Girilen Ddugum Bulunamadi !!");
}

int CalculateEdge() // 
{
    int calculate=0;
    for (int i = 0; i < satir; i++)
    {
        searchNode(i);
        for (int j = 0; j < onemli->counter; j++)
        {
            calculate++;
        }
        
    }
    return calculate;
}

int main()
{
    addfrommatrisarray(); 
    fromtxttoarray(); 
    matrisCoz(); 
    int secim,Iodugum;
    int komsusayi;
    while(true){
    printf("\n\n 0- Cikis");
    printf("\n 1- Matris Listele");
    printf("\n 2- Giris Cikis Dereceleri Hesaplama");
    printf("\n 3- Toplam Kenar Sayisi Hesaplama");
    printf("\n 4- Grafin Toplam Kenar Maliyeti");
    printf("\n 5- Secilen Dugumun Komsularini Listele");
    printf("\n Secim Yapiniz: ");
    scanf("%d",&secim);
    switch(secim)
    {
        case 0:
            exit(1);
            break;
        case 1: //
            PrintMatris();
            break;
        case 2: // 
            printf("Giris Cikis Derecesi Hesaplanacak Dugumu Giriniz: ");
            scanf("%d",&Iodugum);
            CalculateIO(Iodugum);
            break;
        case 3: // 
            printf("\nGrafda Toplam Kenar Sayisi: %d",CalculateEdge());
            break;
        case 4:
            printf("Grafin Toplam Kenar Maliyeti: %d ",CalculateEdgeFull());
            break;
        case 5: // 
            printf("\n Hangi Dugumun Komsularini gormek istersiniz: ");
            printf("(");printNodes();printf("): ");
            scanf("%d",&komsusayi);
            komsuyazdir(komsusayi);
            break;
        default:
            printf("\n\nYanlis Deger!!\n");
            break;
    }
    }
    return 1;
}
