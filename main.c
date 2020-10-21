#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Bagli listenin dugumunu olusturacak struct
// Struct to create the node of the linked list
typedef struct node {
	int val;		// val: ogrenci numaralarinin rakamlari icin
					// val: for the numbers of the student id numbers
	struct node * next; // sonraki dugum pointer
						// next node pointer
} node_t;

// Asil Yigin
// Main Stack
struct StackNode{
	struct node_t* s_node;
	struct StackNode* next;
};

// Uzerinde islem yapacagimiz Yigin
// stack that we'll operate on
struct StackOfPtrs{
	struct node_t* sop_node;
	struct StackOfPtrs* next;
};

// Yigin'da yeni bir node yaratip o adrese donuyor
// creates a new node on the "Stack" and returns to it
struct StackNode* newNode(){
	struct StackNode* stackNode =
		(struct StackNode*) malloc(sizeof(struct StackNode));

	stackNode->next = NULL;
	return stackNode;
}

// Gecici Yigin'da yeni bir node yaratip o adrese donuyor
// Creates a new node in "Temporary Stack" and freezes to that address
struct StackOfPtrs* yeniNode(){
	struct StackOfPtrs* ptrStackNode =
		(struct StackOfPtrs*) malloc(sizeof(struct StackOfPtrs));

	ptrStackNode->next = NULL;
	return ptrStackNode;
}

// Yigin Tanimi
// Stack Declaration
struct StackNode* root = NULL;

// gecici yigin tanimi
// Temporary Stack Declaration
struct StackOfPtrs* gecici_root = NULL;

// Ogrenci numarasi sayac degiskeni
// Student number counter variable
int ogr_no_sayi = 0;

// Eger yigin'da herhangi bir node yoksa 1 donuyor
// Returns 1 if the stack has no node in it
int isEmpty(struct StackNode *root){
	return !root;
}

// Eger gecici yigin'da herhangi bir node yoksa 1 donuyor
// Returns 1 if the stack has no node in it
int isEmptyOfPtrs(struct StackOfPtrs *root){
	return !root;
}

// root'a (yigin'a) node ekleme fonksiyonu
// adding a node to the stack 
void push(struct StackNode** root, node_t * head){
	
	struct StackNode* stackNode = newNode();
	stackNode->s_node = (head);
	
	stackNode->next = *root;
	*root = stackNode;
	
	/*
	node_t * current = head;
	current = current->next;
	*/
}

// gecici yigin'a node ekleme
// adding a node to the temporary stack 
void push_gecici(struct StackOfPtrs** root, node_t * head){
	
	struct StackOfPtrs* ptrStackNode = yeniNode();
	ptrStackNode->sop_node = &(*head);
	
	ptrStackNode->next = *root;
	*root = ptrStackNode;
	
	/*
	node_t * current = head;
	current = current->next;
	*/
}

// bagli listedeki elemanlari yazdırmak icin
// print the elements in the linked list
void print_list(node_t * head){
	node_t * current = head;
	current = current->next;
	
	while (current != NULL) {
		printf("%d ", current->val);
		current = current->next;
	}
}

// bagli listenin sonuna yeni node ile eleman ekleme
// adding a new element at the end of the linked list
void add_end(node_t * head, int val){
	node_t * current = head;
	while (current->next != NULL){
		current = current->next;
	}
	current->next = malloc(sizeof(node_t));
	current->next->val = val;
	current->next->next = NULL;
}

// yeni ogrenci sayisini bir node_t node'una sondan ekliyoruz
// adding new student number to node_t's node from tail
void num_ekle(node_t * head, int num[]){
	
	head->next = NULL;
	
	for(int i = 0; i < 9; i++){
		add_end(head, num[i]);
	}
}

// Asil Yigin'daki tum ogrenci numaralarini gorme
// Seeing all the student numbers in the Main Stack
void list_all_numbers(struct StackNode** root)
{
	struct StackNode* temp = *root;
	
	if (isEmpty(*root)){
		printf("root is empty.\n");
	}
	else{
		//printf("root is not empty.\n");
		while(temp != NULL){
			print_list(temp->s_node);
			printf("\t temp: %p \t temp->s_node: %p\n", &(temp), &(temp->s_node));
			temp = temp->next;
		}
	}
}

// Gecici Yigin'daki tum ogrenci numaralarini gorme
// Seeing all the student numbers in the Temporary Stack
void list_all_numbers_gecici(struct StackOfPtrs** root)
{
	struct StackOfPtrs* temp = *root;
	
	if (isEmpty(*root)){
		printf("root is empty.\n");
	}
	else{
		//printf("root is not empty.\n");
		while(temp != NULL){
			print_list(temp->sop_node);
			printf("\n");
			temp = temp->next;
		}
	}
}

/*	// Gosterilen 'head'deki son 4 basamak rakamlarini 4 basamakli bir sayi
* 		olusturacak sekilde birlestiriyoruz
*	// Combining the last 4 digits of the current "head's" in order to create
*		a 4-digit number
*/
int sayiyi_al_son4(node_t * head){
	
	node_t * current = head;
	int num_4 = 0;
	
	current = current->next;
		
	for(int i = 0; i < 9; i++){
		switch(i){
			case 5:
				num_4 = num_4 + 1000*(current->val);
				current = current->next;
				break;
			case 6:
				num_4 = num_4 + 100*(current->val);
				current = current->next;
				break;
			case 7:
				num_4 = num_4 + 10*(current->val);
				current = current->next;
				break;
			case 8:
				num_4 = num_4 + current->val;
				current = current->next;
				break;
			default:
				current = current->next;
			}
		}
		
	//current = current->next;
	return num_4;
}

/*	// Gosterilen 'head'deki ortadaki yil kodu rakamlarini 2 basamakli bir sayi
* 		olusturacak sekilde birlestiriyoruz
*	// Combining the middle 2 digits of the current "head's" in order to create
*		a year code for the classification
*/
int sayiyi_al_yilkodu(node_t * head){
	
	node_t * current = head;
	int yil = 0;
	
	current = current->next;
		
	for(int i = 0; i < 9; i++){
		switch(i){
			case 3:
				yil = yil + 10*(current->val);
				current = current->next;
				break;
			case 4:
				yil = yil + (current->val);
				current = current->next;
				break;
			default:
				current = current->next;
			}
		}
		
	return yil;
}


// artan siralama seklinde print fonksiyonu
// ascending print function 
void artan_sirala_gecici(struct StackOfPtrs** root){
	
	struct StackOfPtrs* temp1 = *root;
	struct StackOfPtrs* temp2 = *root;
	node_t * gecici_head = NULL;
	int temp2_num, temp1_num;
	
	
	/*	Burada 2 pointer ile sırayla ardarda 'node'lara bakarak
	*	ilgili fonksiyonlarla degerlendirecegimiz sayilari alip
	*	bir karsilastirma yapiyoruz. Eger karsilastirma uygun ise
	*	pointer'larin gosterdikleri node'lari degistiriyoruz.
	*/	
	for(int i = 0; i<ogr_no_sayi; i++){
	
		if((temp2->next) == NULL){
			return -1;
		}
		temp2 = temp2->next;
		temp2_num = sayiyi_al_son4(temp2->sop_node);
		temp1_num = sayiyi_al_son4(temp1->sop_node);
		if(temp1_num > temp2_num){
			gecici_head = temp1->sop_node;
			temp1->sop_node = temp2->sop_node;
		temp2->sop_node = gecici_head;
		}
		
		temp1 = temp1->next;
		
	}
	temp1 = *root;
	temp2 = *root;
	
}

// yilina gore siralama
// year based print function
void yila_gore_sirala(struct StackOfPtrs** root){
	
	struct StackOfPtrs* temp1 = *root;
	struct StackOfPtrs* temp2 = *root;
	node_t * gecici_head = NULL;
	int temp2_num, temp1_num;
	
	/*	Burada 2 pointer ile sırayla ardarda 'node'lara bakarak
	*	ilgili fonksiyonlarla degerlendirecegimiz sayilari alip
	*	bir karsilastirma yapiyoruz. Eger karsilastirma uygun ise
	*	pointer'larin gosterdikleri node'lari degistiriyoruz.
	*/	
	for(int i = 0; i<ogr_no_sayi; i++){
	
		if((temp2->next) == NULL){
			return -1;
		}
		temp2 = temp2->next;
		
		temp2_num = sayiyi_al_yilkodu(temp2->sop_node);
		temp1_num = sayiyi_al_yilkodu(temp1->sop_node);
		if(temp1_num > temp2_num){
			gecici_head = temp1->sop_node;
			temp1->sop_node = temp2->sop_node;
		temp2->sop_node = gecici_head;
		}
		
		temp1 = temp1->next;
		
	}
	temp1 = *root;
	temp2 = *root;
	
}


/*	// String olarak aldigimiz ogrenci numarasini ASCII 
*	degerleri ile oynayarak dogru rakamlari bulup 
*	belirli bir node icin 'add_end' ile ekliyoruz.
*	Ardindan bu node'lari asil ve gecici yigin'imiza
*	'push' ve 'push_gecici' ekliyoruz.
*
* 	// We find the correct numbers by playing with the ASCII 
*	values of the student number we get as a string and add it 
*	with 'add_end' for a specific node. Then we add these nodes
*	'push' and 'push_gecici' to our primary and temporary stack.
*/	
void ogr_num_al(){
	char num_str[9] = {};
	int num[9];
	
	printf("\t9 haneli ogrenci numarasini giriniz:\t");
	scanf("%s", &num_str);
	
	for(int k=0;k<9;k++){
		num[k] = num_str[k] - '0';
	}
	
	node_t * head = NULL;
	head = malloc(sizeof(node_t));
	num_ekle(head, num);
	push(&root, head);
	push_gecici(&gecici_root, head);
		
	memset(num_str, '\0', 9);
	memset(num, '\0', 9);
	
}

/*	// 2 Yigin yerine 1 Yigin ile de ayni islemler yapilabilir,
*	fakat islem kolayligi ve kontrolu acisindan 2 Yigin sectim.
*	// Same operations can be done with 1 Stack instead of 2,
*	but for the simplicity and easy control I've chosen 2.
*/
int main(void)
{
	int tercih = 0;
	printf("ITU - EHB208 - Veri Yapilari - Proje");
	printf("\n---------------------------------------\n\n");
	printf("1 - Ogrenci numarasi gir\n");
	printf("2 - Tum okul numaralarini artan sirayla goster\n");
	printf("3 - Tum okul numaralarini yillara gore gruplayip goster\n");
	printf("4 - Cik\n\n");
	
	while(tercih != 4){
		printf("Bir tercih giriniz: ");
		
		// tercihi aliyoruz
		// get the option
		scanf("%d", &tercih);
		
		switch(tercih)
		{
			case 1:
				printf(" Tercih: 1\n");
				ogr_num_al();
				printf("\n");
				ogr_no_sayi++;
				break;
			case 2:
				printf(" Tercih: 2\n");
				for(int h=0; h<ogr_no_sayi; h++){
					artan_sirala_gecici(&gecici_root);
				}
				list_all_numbers_gecici(&gecici_root);
				printf("\n");
				break;
			case 3:
				printf(" Tercih: 3\n");
				for(int h=0; h<ogr_no_sayi; h++){
					yila_gore_sirala(&gecici_root);
				}
				list_all_numbers_gecici(&gecici_root);
				printf("\n");
				break;
			case 4:
				printf(" Tercih: 4\n");
				printf("\n-------------------------\n\tCikiliyor...\n");
				printf("\t\t\tIyi gunler.\n");
				return 0;
				break;
			default:
            printf("gecersiz tercih!\n");			
			
		}
		
	}
	getchar();
	return 0;
}
