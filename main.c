#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

struct harfsiklik {
	char harf;
	int siklik;
	struct harfsiklik *prev,*next,*left,*right;
	
};
typedef struct harfsiklik HRF;
static HRF *head,*tail;


void siklikhesapla(char []);
HRF* elemanolustur();
void listeninsonunabagla(HRF *);
void yazdir();

void insertionSort();
void agacolustur();
void sunusil(HRF*);


int getLevelCount(HRF *node)
{
    if (node == NULL)
    {
        return 0;
    }
    int leftMaxLevel = 1 + getLevelCount(node->left);
    int rightMaxLevel = 1 + getLevelCount(node->right);
    if (leftMaxLevel > rightMaxLevel)
    {
        return leftMaxLevel;
    }
    else
    {
        return rightMaxLevel;
    }
}

void printLevel(HRF *node, int level)
{
    if (node != NULL && level == 0)
    { 
	    printf("(%d)",node->siklik);
        printf("%c ",node->harf);
	
    }   
    else if (node != NULL)
    {
        printLevel(node->left, level - 1);
        printLevel(node->right, level - 1);
		
    }
}


void printElements(HRF *node)
{
    int i,j;
    int levelCount = getLevelCount(node);    
        
        
    for (i = 0; i < levelCount; i++)
    {
        printf("\nLevel(%d)\t",i);
		printLevel(node, i);
		printf("\n");
    }
}


int main() {
	
	char metin[SIZE];
	
	printf("Enter the text (with lowercase) which you want to compress.\n");
	gets(metin);
	
	
	siklikhesapla(metin);

	yazdir();
	
	agacolustur();
	
	 printElements(head);

	
	return 0;
}





//huffman
void agacolustur(){
	if(head==NULL||head->next==NULL){
		printf("Veri yok, agac olusturulamaz.");
		return;
	}
	HRF *k1,*k2,*nw;
	
		
    while(head!=tail){

	k1=head;
	k2=head->next;
	nw=elemanolustur();
	listeninsonunabagla(nw);
	nw->harf=-2;
	nw->siklik=(k1->siklik)+(k2->siklik);
	
	insertionSort();
	
	nw->left=k1;
	
	nw->right=k2;
	
	
	
	head=k2->next;
	head->prev=NULL;
    
	
	
	yazdir();

		}

}




void siklikhesapla(char string[]){
	int c = 0;
	int bosluk=0;
	static int count[26];
	int x;
	
	HRF *eris;
	int i=0;
	//while(i<strlen(string)){
	
	while(string[c]!= '\0'){
	if(string[c]==32)
	bosluk++;
	c++;
	}
	c=0;	
	while (string[c] != '\0') {
   /** Considering characters from 'a' to 'z' only and ignoring others. */

      if (string[c] >= 'a' && string[c] <= 'z') {
         x = string[c] - 'a';
        count[x]++; 
				 
    
        int bulundu=0;
        HRF *temp;
           for(eris=head;eris!=NULL;eris=eris->next){
           	    if (eris->harf == string[c]){
           	    	bulundu=1;
           	    	temp=eris;
				   }
		   }
          
		  if(head==NULL || bulundu==0){
          	listeninsonunabagla(elemanolustur());
            eris=tail;
            eris->harf=string[c];
		    eris->siklik=count[x]; 
          	
          	}
		  
		  else{
		  	temp->harf=string[c];
		  	temp->siklik=count[x];
		  	
		  	
		 } 
      }
      
      
      c++;
      
   }
        if (bosluk!=0){
	  listeninsonunabagla(elemanolustur());
            eris=tail;
            eris->harf=32;
		    eris->siklik=bosluk; 
	    	}
      	           
        
	
	
	return;
}

HRF* elemanolustur(){
	HRF *b;
	b=(HRF*)malloc(sizeof(HRF));
	if (b==NULL){
	  printf("Allocation failed");
	  exit(0);
    } 
   
    b->next=NULL;
    b->prev=NULL;
    b->left=NULL;
    b->right=NULL;
    b->harf=-1;
    b->siklik=0;
    
	return b;
}

void listeninsonunabagla(HRF *p){
	if (head==NULL){
		p->prev=NULL;
		p->next=NULL;
		p->left=NULL;
		p->right=NULL;
		head=p;
		tail=p;
	}
	else{
		if(tail==NULL){
		 printf("Error, last nonexist.\n");
		 return;	
		}
		tail->next=p;
		p->prev=tail;
		p->next=NULL;
		p->left=NULL;
		p->right=NULL;
		tail=p;
	}
	
}

void sunusil(HRF *e){
	HRF *tmp1,*tmp2,*b;
	
	if ((head==tail)&&(e==head)){
     	free(e);
        head=NULL;
	    tail=NULL;
	    return;
    }
    
   if(e==head){
   	   
   	    b=head;
	
	    if (head==NULL) {
		    printf("Error, head cannot be NULL\n");
		    exit(0);
	    }
	
	    head=head->next;
	    head->prev=NULL;
	    free(b);
	
	    for(b=head;b->next!=NULL;b=b->next);
	    tail=b;
	
       return;
   }
   
   if(e==tail){
   	   	HRF *tmp;
	
	    if (head==NULL) {
		printf("Error, head cannot be NULL\n");
		exit(0);
	    }
    
	    tmp=tail;
    	b=tail->prev;
    	b->next=NULL;
	    free(tmp);
	    tail=b;
	
       return;
   } 
   	
	tmp1=e->prev;
	tmp2=e->next;	
	tmp1->next=tmp2;
	tmp2->prev=tmp1;
    free(e);
	
	for(b=head;b->next!=NULL;b=b->next);
	tail=b;			
}

void yazdir (){
	HRF *b;
	if (head==NULL){
		printf("Su anda data yok.\n");
		return;
	}
	
	for (b=head;b!=NULL;b=b->next){
		printf("%c",b->harf);
		printf("(%d) ",b->siklik);
		if (b->next!=NULL) printf("--> ");
		else printf("\n");
	}		
}

void insertionSort() {
        HRF *ptr1, *ptr2;
        int i, j, temp;
        char temp2;
        ptr1 = ptr2 = head;

    int node_count=0;
    HRF *b;
	for(b=head;b!=NULL;b=b->next)
	    node_count++;
  	    

        for (i = 0; i < node_count; i++) {
                temp = ptr1->siklik;
                temp2 = ptr1->harf;
                for (j = 0; j < i; j++)
                        ptr2 = ptr2->next;
                for (j = i; j > 0 && ptr2->prev->siklik > temp; j--) {
                        ptr2->siklik = ptr2->prev->siklik;
                        ptr2->harf = ptr2->prev->harf;
                        ptr2 = ptr2->prev;
                }
                ptr2->siklik = temp;
                ptr2->harf = temp2;
                ptr2 = head;
                ptr1 = ptr1->next;
        }
  }
